#include "patcher_x86.hpp"
//	#include "H2Structures.h"
//	#include <stdio.h>

Patcher* _P;
PatcherInstance* _PI;
static _bool_ plugin_On = 0;

//	修改水井的显示信息
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

//	修改每周的增加量
int __stdcall checkWellGrowth_2(LoHook* h, HookContext* c)
{
	int dwID;		//	建筑种类
	int townID;		//	城镇ID
	char faction;	//	种族
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x14);
	faction = *(char *)(*(char **)(c->ebp - 0xDC) + 2899 + townID * 100 + 3);

	//	如果建筑种类是6级未升级巢穴或6级已升级巢穴，且种族是精灵或男巫，那么水井增加量-1
	if(dwID == 24 || dwID == 29 || dwID == 30)
	{
		if(faction == 0x3 || faction == 0x4)
		{
			*(int*)(c->ebp - 0x20) -= 1;
		}
	}
	return EXEC_DEFAULT;
}

//	修改每月的增加量
int __stdcall checkWellGrowth_3(LoHook* h, HookContext* c)
{
	int dwID;
	int townID;
	char faction;
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x10);
	faction = *(char *)(*(char **)(c->ebp - 0x28) + 2899 + townID * 100 + 3);
	if(dwID == 24 || dwID == 29 || dwID == 30)
	{
		if(faction == 0x3 || faction == 0x4)
		{
			*(__int16*)(c->ebp - 0x4) -= 1;
		}
	}
	return EXEC_DEFAULT;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if ( DLL_PROCESS_ATTACH == ul_reason_for_call)
    {
        if (!plugin_On)
        {
            plugin_On = 1;
            _P = GetPatcher();
            _PI = _P -> CreateInstance("H2_Sandruse_WellChange_20230312");
            
            //  Well gives +1 growth (instead of +2) for Green Dragons, Red Dragons, Black Dragons, Giants, Titans.
			//	对于泰坦和龙，无论升级与否，水井的额外增加量改为1而不是游戏原先设定的2
            
			//	这个hook地址是用IDA自己找的
			_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI->WriteLoHook(0x4252FF, checkWellGrowth_2);
			_PI->WriteLoHook(0x426E46, checkWellGrowth_3);
			
			
			/*
			//	这个hook地址是Ben80参考文件给的，部分函数对返回地址有特殊要求
			_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI->WriteLoHook(0x4252F5, checkWellGrowth_2);
			_PI->WriteLoHook(0x426E3C, checkWellGrowth_3);
			*/

			//	修改文字描述 2改为a few，简略掉creatures
			//	_PI -> WriteHexPatch(0x509737,"612066657720706572207765656B2E000000000000");
			
			//	2改为1 or 2，简略掉creatures
			//	_PI -> WriteHexPatch(0x509737,"31206F72203220706572207765656B2E0000000000");

			//	简略掉by 2 creatures
			//	_PI -> WriteHexPatch(0x509734,"706572207765656B2E000000000000000000000000000000");
			_PI -> WriteHexPatch(0x509733,"2E000000000000000000000000000000000000000000000000");

		}
    }
    return TRUE;
}
