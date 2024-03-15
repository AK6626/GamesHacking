#include "../../include2020_v1/patcher_x86.hpp"
#include "../../include2020_v1/H2Structures.h"

Patcher* _P;
PatcherInstance* _PI;

static _bool_ plugin_On = 0;

int __stdcall AI_NecromancyFix(LoHook* h, HookContext* c)
{
	int hookAddress = h->GetAddress();

	if(hookAddress == 0x441083) // Eng 2.0
		for(int i=0; i<5; i++)
		{
			if(*(_byte_*)(*(int*)(c->ebp + 0xC) + 101 + i) != -1)
				*(int*)(c->ebp - 8) += *(_word_*)(*(int*)(c->ebp + 0xC) + 106 + 2 * i);
			if(*(_byte_*)(*(int*)(c->ebp + 0x10) + i) != -1)
				*(int*)(c->ebp - 0x44) += *(_word_*)(*(int*)(c->ebp + 0x10) + 5 + 2 * i);
		}
	else
		for(int i=0; i<5; i++)
		{
			if(*(_byte_*)(*(int*)(c->ebp + 0xC) + 101 + i) != -1)
				*(int*)(c->ebp - 8) += *(_word_*)(*(int*)(c->ebp + 0xC) + 106 + 2 * i);
			if(*(_byte_*)(*(int*)(c->ebp + 0x10) + i) != -1)
				*(int*)(c->ebp - 0x28) += *(_word_*)(*(int*)(c->ebp + 0x10) + 5 + 2 * i);
		}

	if(hookAddress == 0x440E86) // Eng 1.3
		c->return_address = 0x440EE3;
	if(hookAddress == 0x441083) // Eng 2.0
		c->return_address = 0x4410E0;
	if(hookAddress == 0x4B3C4A) // Eng 2.1
		c->return_address = 0x4B3CA7;
	if(hookAddress == 0x486830) // Rus 2.1
		c->return_address = 0x486882;
	if(hookAddress == 0x4860B2) // Pl 2.1
		c->return_address = 0x486104;
	if(hookAddress == 0x48568C) // Cz 2.1 New
		c->return_address = 0x4856DE;
	if(hookAddress == 0x484D7C) // Cz 2.1 Old
		c->return_address = 0x484DCE;

	return NO_EXEC_DEFAULT;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    if ( DLL_PROCESS_ATTACH == ul_reason_for_call)
    {
        if (!plugin_On)
        {
            plugin_On = 1;       
            _P = GetPatcher();
			_PI = _P->CreateInstance("H2_AI_NecromancyFix");

			int check;

			// H2 Eng SW 1.3
            check = *(int*)(0x434317+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x440E86, AI_NecromancyFix);
			}

			// H2 Eng PoL 2.0
            check = *(int*)(0x41BFB7+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x441083, AI_NecromancyFix);
			}

			// H2 Eng PoL 2.1
            check = *(int*)(0x484DC1+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x4B3C4A, AI_NecromancyFix);
			}

			// H2 Rus PoL 2.1
            check = *(int*)(0x4710BE+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x486830, AI_NecromancyFix);	
			}

			// H2 Pol PoL 2.1
            check = *(int*)(0x470C7C+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x4860B2, AI_NecromancyFix);	
			}

			// H2 Cz PoL 2.1 New
            check = *(int*)(0x47091E+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x48568C, AI_NecromancyFix);
			}

			// H2 Cz PoL 2.1 Old
            check = *(int*)(0x47000E+6);
			if(check == 0x14000000)
			{
				_PI->WriteLoHook(0x484D7C, AI_NecromancyFix);
			}

        }
    }

   return TRUE;
}

