/*

Sandruse_Balance_20240310
1)	加强农民
2)	削弱地牢
3)	调整水井增益效果(按Ben80的逻辑修改)
4)	修改巨人、泰坦、绿龙、红龙和黑龙的产量(暂不启用)
5)	禁止招募鬼魂
6)	禁止学习征兵术(暂不启用)

*/	

#include "patcher_x86_gcc.hpp"

Patcher* _P;
PatcherInstance* _PI;
static _bool_ plugin_On = 0;

//	水井修改1，修改水井的显示信息
int __stdcall checkWellGrowth_1(LoHook* h, HookContext* c)
{
	int dwLevel;	//	建筑级别
	char faction;	//	种族
	
	dwLevel = *(int*)(c->ebp - 0x34);
	faction = *(char *)(*(char **)(*(char **)(c->ebp - 0xA4) + 54) + 3);

	//	如果建筑级别为6级巢穴，且种族是精灵或男巫，那么水井显示增加量-1
	if(dwLevel == 5 && (faction == 0x3 || faction == 0x4))
	{
		*(int*)(c->ebp - 0xA0) -= 1;
	}
	return EXEC_DEFAULT;
}

//	水井修改2，修改每周的增加量
int __stdcall checkWellGrowth_2(LoHook* h, HookContext* c)
{
	int dwID;		//	建筑种类
	int townID;		//	城镇ID
	char faction;	//	种族
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x14);
	faction = *(char *)(*(char **)(c->ebp - 0xDC) + 2899 + townID * 100 + 3);

	//	如果建筑种类是6级未升级巢穴或6级已升级巢穴，且种族是精灵或男巫，那么水井增加量+1, 并以此替代之前+2的逻辑
	if(faction == 0x3 || faction == 0x4)
	{
		if(dwID == 24 || dwID == 29 || dwID == 30)
		{
			c->return_address = 0x425303;
			*(int*)(c->ebp - 0x20) += 1;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

//	水井修改3，修改每月的增加量
int __stdcall checkWellGrowth_3(LoHook* h, HookContext* c)
{
	int dwID;
	int townID;
	char faction;
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x10);
	faction = *(char *)(*(char **)(c->ebp - 0x28) + 2899 + townID * 100 + 3);
	if(faction == 0x3 || faction == 0x4)
	{
		if(dwID == 24 || dwID == 29 || dwID == 30)
		{
			c->return_address = 0x426E4A;
			*(__int16*)(c->ebp - 0x4) += 1;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

//	禁止招募鬼魂
//	坟冢中可招募的鬼魂数量始终为0
int __stdcall GhostForbidden(LoHook* h, HookContext* c)
{
	*(__int16*)(c->ebp - 0x18) = 0;
	return EXEC_DEFAULT;
}

/*
//	禁止女巫小屋教授征兵术
//  如果地图指定该女巫教授的是征兵术，你访问时她会让你滚蛋
int __stdcall DiplomacyForbidden(LoHook* h, HookContext* c)
{
	if (c->eax == 4)
	{
		c->return_address = 0x486D74;
	}
	return EXEC_DEFAULT;
}
*/

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if ( DLL_PROCESS_ATTACH == ul_reason_for_call)
    {
        if (!plugin_On)
        {
            plugin_On = 1;
            _P = GetPatcher();
            _PI = _P -> CreateInstance((char *)"H2_Sandruse_20230815");
            
            //  以下是修改内容
			//	1)	加强农民
			//  农民的由1改为2，速度由2改为3，十六进制原始值为01000002
			//  exe中农民的HP数值的hex offset是F0400，IDA中显示offset是4F2200，相差401E00
            _PI -> WriteHexPatch(0x4F21FF,(char *)"0A02000003");
            
            //  2)	削弱地牢
            //  地牢的建造费用消耗黄金量由3000改为6000，exe偏移值为F20EC，十六进制原始值为B80B
			_PI -> WriteHexPatch(0x4F3EEC,(char *)"7017");
			
			//	3)	调整水井增益效果
			//	对于巨人、泰坦、绿龙、红龙和黑龙，水井的额外增加量改为1而不是游戏原先设定的2
			_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI->WriteLoHook(0x4252F5, checkWellGrowth_2);
			_PI->WriteLoHook(0x426E3C, checkWellGrowth_3);
			//	修改水井相关描述
			_PI -> WriteHexPatch(0x509733,(char *)"2E000000000000000000000000000000000000000000000000");
			
			/*
			//	4)	修改巨人、泰坦、绿龙、红龙和黑龙的产量
			//  Green Dragon's grouth from 1 to 0, same with Red Black Giant and Titan. Exe Hex offset is F078D
			_PI -> WriteHexPatch(0x4F258D,"00");
			_PI -> WriteHexPatch(0x4F25A7,"00");
			_PI -> WriteHexPatch(0x4F25C1,"00");
			_PI -> WriteHexPatch(0x4F2691,"00");
			_PI -> WriteHexPatch(0x4F26AB,"00");
			*/
			
			//	5)	禁止招募鬼魂
			//  Function RecruitSiteEvent  0x0048CE90
			_PI -> WriteLoHook(0x48CEE7, GhostForbidden);
			
			/*
			//	6)	禁止学习征兵术
			//	禁止女巫小屋教授征兵术
			//  Function DoEvent  0x00485EA0
			//  hook when switch to witch hut event
			_PI -> WriteLoHook(0x486D06, DiplomacyForbidden);
			//	升级时学习到征兵术的几率降低为0
			//  Diplomacy can't be learnt when levelup.
			//  The 4th secondary_skill_chances (Diplomacy) origin is 030202020202
			_PI -> WriteHexPatch(0x4F4BE8,"000000000000"); 
			*/
		}
    }
    return TRUE;
}
