/*

Sandruse_Balance_20240310
1)	��ǿũ��
2)	��������
3)	����ˮ������Ч��(��Ben80���߼��޸�)
4)	�޸ľ��ˡ�̩̹�������������ͺ����Ĳ���(�ݲ�����)
5)	��ֹ��ļ���
6)	��ֹѧϰ������(�ݲ�����)

*/	

#include "patcher_x86_gcc.hpp"

Patcher* _P;
PatcherInstance* _PI;
static _bool_ plugin_On = 0;

//	ˮ���޸�1���޸�ˮ������ʾ��Ϣ
int __stdcall checkWellGrowth_1(LoHook* h, HookContext* c)
{
	int dwLevel;	//	��������
	char faction;	//	����
	
	dwLevel = *(int*)(c->ebp - 0x34);
	faction = *(char *)(*(char **)(*(char **)(c->ebp - 0xA4) + 54) + 3);

	//	�����������Ϊ6����Ѩ���������Ǿ�������ף���ôˮ����ʾ������-1
	if(dwLevel == 5 && (faction == 0x3 || faction == 0x4))
	{
		*(int*)(c->ebp - 0xA0) -= 1;
	}
	return EXEC_DEFAULT;
}

//	ˮ���޸�2���޸�ÿ�ܵ�������
int __stdcall checkWellGrowth_2(LoHook* h, HookContext* c)
{
	int dwID;		//	��������
	int townID;		//	����ID
	char faction;	//	����
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x14);
	faction = *(char *)(*(char **)(c->ebp - 0xDC) + 2899 + townID * 100 + 3);

	//	�������������6��δ������Ѩ��6����������Ѩ���������Ǿ�������ף���ôˮ��������+1, ���Դ����֮ǰ+2���߼�
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

//	ˮ���޸�3���޸�ÿ�µ�������
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

//	��ֹ��ļ���
//	��ڣ�п���ļ�Ĺ������ʼ��Ϊ0
int __stdcall GhostForbidden(LoHook* h, HookContext* c)
{
	*(__int16*)(c->ebp - 0x18) = 0;
	return EXEC_DEFAULT;
}

/*
//	��ֹŮ��С�ݽ���������
//  �����ͼָ����Ů�׽��ڵ����������������ʱ�����������
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
            
            //  �������޸�����
			//	1)	��ǿũ��
			//  ũ�����1��Ϊ2���ٶ���2��Ϊ3��ʮ������ԭʼֵΪ01000002
			//  exe��ũ���HP��ֵ��hex offset��F0400��IDA����ʾoffset��4F2200�����401E00
            _PI -> WriteHexPatch(0x4F21FF,(char *)"0A02000003");
            
            //  2)	��������
            //  ���εĽ���������Ļƽ�����3000��Ϊ6000��exeƫ��ֵΪF20EC��ʮ������ԭʼֵΪB80B
			_PI -> WriteHexPatch(0x4F3EEC,(char *)"7017");
			
			//	3)	����ˮ������Ч��
			//	���ھ��ˡ�̩̹�������������ͺ�����ˮ���Ķ�����������Ϊ1��������Ϸԭ���趨��2
			_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI->WriteLoHook(0x4252F5, checkWellGrowth_2);
			_PI->WriteLoHook(0x426E3C, checkWellGrowth_3);
			//	�޸�ˮ���������
			_PI -> WriteHexPatch(0x509733,(char *)"2E000000000000000000000000000000000000000000000000");
			
			/*
			//	4)	�޸ľ��ˡ�̩̹�������������ͺ����Ĳ���
			//  Green Dragon's grouth from 1 to 0, same with Red Black Giant and Titan. Exe Hex offset is F078D
			_PI -> WriteHexPatch(0x4F258D,"00");
			_PI -> WriteHexPatch(0x4F25A7,"00");
			_PI -> WriteHexPatch(0x4F25C1,"00");
			_PI -> WriteHexPatch(0x4F2691,"00");
			_PI -> WriteHexPatch(0x4F26AB,"00");
			*/
			
			//	5)	��ֹ��ļ���
			//  Function RecruitSiteEvent  0x0048CE90
			_PI -> WriteLoHook(0x48CEE7, GhostForbidden);
			
			/*
			//	6)	��ֹѧϰ������
			//	��ֹŮ��С�ݽ���������
			//  Function DoEvent  0x00485EA0
			//  hook when switch to witch hut event
			_PI -> WriteLoHook(0x486D06, DiplomacyForbidden);
			//	����ʱѧϰ���������ļ��ʽ���Ϊ0
			//  Diplomacy can't be learnt when levelup.
			//  The 4th secondary_skill_chances (Diplomacy) origin is 030202020202
			_PI -> WriteHexPatch(0x4F4BE8,"000000000000"); 
			*/
		}
    }
    return TRUE;
}
