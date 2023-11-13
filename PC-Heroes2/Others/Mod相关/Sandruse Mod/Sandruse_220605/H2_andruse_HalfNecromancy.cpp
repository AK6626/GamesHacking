#include "patcher_x86.hpp"

Patcher* _P;
PatcherInstance* _PI;
static _bool_ plugin_On = 0;

int __stdcall changeNecromancy(LoHook* h, HookContext* c)
{
	c->eax /= 2;
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
            _PI = _P -> CreateInstance("H2_Sandruse_HalfNecromancy");
            
            //  从此往下就是十六进制修改的内容
			//  十六进制编辑器查看exe农民血量地址F0400，IDA打开exe查看Hex-view，该值地址位于4F2200，偏差401E00
			/*
            _PI -> WriteHexPatch(0x4F2200,"02000003");  //  农民血量改1为2，速度改2为3；原值01000002
			_PI -> WriteHexPatch(0x4F258D,"00");  //  绿龙自然增长量该1为0，下面红龙、黑龙、巨人、泰坦同；Hex地址F078D
			_PI -> WriteHexPatch(0x4F25A7,"00");
			_PI -> WriteHexPatch(0x4F25C1,"00");
			_PI -> WriteHexPatch(0x4F2691,"00");
			_PI -> WriteHexPatch(0x4F26AB,"00");
			_PI -> WriteHexPatch(0x4F3EEC,"7017");  //  地牢造价改3000为6000；原值B80B；Hex地址F20EC
			*/

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x4B3DC0, changeNecromancy);
				_PI->WriteLoHook(0x4B3E56, changeNecromancy);
				_PI->WriteLoHook(0x43F9F2, changeNecromancy);
				_PI->WriteByte(0x51C4AE, 0x20);
				_PI->WriteByte(0x51C4AF, 0x35);
				_PI->WriteByte(0x509308, 0x20);
				_PI->WriteByte(0x509309, 0x35);
				_PI->WriteByte(0x509396, 0x31);
				_PI->WriteByte(0x509422, 0x31);
				_PI->WriteByte(0x509423, 0x35);
        }
    }
    return TRUE;
}