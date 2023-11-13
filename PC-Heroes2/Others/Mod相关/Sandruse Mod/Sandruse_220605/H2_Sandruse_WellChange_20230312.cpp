#include "patcher_x86.hpp"
//	#include "H2Structures.h"
//	#include <stdio.h>

Patcher* _P;
PatcherInstance* _PI;
static _bool_ plugin_On = 0;

//	�޸�ˮ������ʾ��Ϣ
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

//	�޸�ÿ�ܵ�������
int __stdcall checkWellGrowth_2(LoHook* h, HookContext* c)
{
	int dwID;		//	��������
	int townID;		//	����ID
	char faction;	//	����
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x14);
	faction = *(char *)(*(char **)(c->ebp - 0xDC) + 2899 + townID * 100 + 3);

	//	�������������6��δ������Ѩ��6����������Ѩ���������Ǿ�������ף���ôˮ��������-1
	if(dwID == 24 || dwID == 29 || dwID == 30)
	{
		if(faction == 0x3 || faction == 0x4)
		{
			*(int*)(c->ebp - 0x20) -= 1;
		}
	}
	return EXEC_DEFAULT;
}

//	�޸�ÿ�µ�������
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
			//	����̩̹�����������������ˮ���Ķ�����������Ϊ1��������Ϸԭ���趨��2
            
			//	���hook��ַ����IDA�Լ��ҵ�
			_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI->WriteLoHook(0x4252FF, checkWellGrowth_2);
			_PI->WriteLoHook(0x426E46, checkWellGrowth_3);
			
			
			/*
			//	���hook��ַ��Ben80�ο��ļ����ģ����ֺ����Է��ص�ַ������Ҫ��
			_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI->WriteLoHook(0x4252F5, checkWellGrowth_2);
			_PI->WriteLoHook(0x426E3C, checkWellGrowth_3);
			*/

			//	�޸��������� 2��Ϊa few�����Ե�creatures
			//	_PI -> WriteHexPatch(0x509737,"612066657720706572207765656B2E000000000000");
			
			//	2��Ϊ1 or 2�����Ե�creatures
			//	_PI -> WriteHexPatch(0x509737,"31206F72203220706572207765656B2E0000000000");

			//	���Ե�by 2 creatures
			//	_PI -> WriteHexPatch(0x509734,"706572207765656B2E000000000000000000000000000000");
			_PI -> WriteHexPatch(0x509733,"2E000000000000000000000000000000000000000000000000");

		}
    }
    return TRUE;
}
