//#include <cstdint>
#include "patcher_x86_gcc.h"
#include "H2Structures_part.h"

/*
2025-11-11  所有修改内容：
农民 HP 1->2 Speed 2->3
水井对龙、泰坦的增长增益-1
水井说明
地牢建造消耗黄金调整 3000->6000
禁止玩家招募鬼魂
后勤术最大增益减少1/3, 即：1.0,  1.1,  1.2,  1.3 -> 1.0, 1.05, 1.1, 1.2
专家征兵术的怪物加入率调整：100% -> 75%
各级神秘术增益调整 +1 +2 +3 -> +3 +7 +11
鹰眼术获得高级时力量+1，获得专家级时力量+2（再+1）
SPELL_DIMENSION_DOOR cost 15
SPELL_TOWN_PORTAL cost 50
*/

static Patcher* _P;
static PatcherInstance* _PI;
static _bool_ plugin_On = 0;

static int aSSpellInfo;

/*//rand_fast
static uint32_t g_seed = 0;
static inline void seed_fast(uint32_t s) { g_seed = s; }
static inline uint32_t rand_fast(void)   // 返回 0-4294967295
{
    // LCG: a=1664525, c=1013904223, m=2^32
    g_seed = 1664525U * g_seed + 1013904223U;
    return g_seed;
}*/

// 鬼怪（破坏值4-6）杀死生物后，自身数量将会增长，增长量为：伤害值/50 然后除以1-5的随机数，最后保证不超过杀死生物的数量/同一个随机数。
/*__stdcall int GhostAddChange(LoHook* h, HookContext* c) {
  int creaturesKilled, AddNum;
  int damDone;
  int divNum;
  creaturesKilled = (int)c->eax;
  damDone = *(int*)(c->ebp - 0xF0);
  if (!g_seed) seed_fast((unsigned int)(damDone + creaturesKilled));
  divNum = (1 + rand_fast() % 5);
  
  creaturesKilled = creaturesKilled / divNum;
  AddNum = (damDone + 25) / 50 / divNum;
  if (AddNum > creaturesKilled) AddNum = creaturesKilled;
  
  c->eax = AddNum;
	return EXEC_DEFAULT;
}*/

static __stdcall int GhostAddChange(LoHook* h, HookContext* c) {
  int creaturesKilled, AddNum;
  int damDone; // damage casued by ghosts
  
  creaturesKilled = (int)c->eax;
  damDone = *(int*)(c->ebp - 0xF0);
  
  creaturesKilled = creaturesKilled * 3 / 5;
  AddNum = (damDone + 60) / 100;
  if (AddNum > creaturesKilled) AddNum = creaturesKilled;
  
  c->eax = AddNum;
	return EXEC_DEFAULT;
}

// well display
static __stdcall int checkWellGrowth_1(LoHook* h, HookContext* c)
{
	int dwLevel;	//	建筑级别
	char faction;	//	种族
	dwLevel = *(int*)(c->ebp - 0x34);
	faction = *(char *)(*(char **)(*(char **)(c->ebp - 0xA4) + 54) + 3);
	//	如果建筑级别为6级巢穴，且种族是精灵或男巫，那么水井显示增加量-1
	if(dwLevel == 5 && (faction == 0x3 || faction == 0x4)) {
    *(int*)(c->ebp - 0xA0) -= 1;
	}
	return EXEC_DEFAULT;
}

// well per week
static __stdcall int checkWellGrowth_2(LoHook* h, HookContext* c) {
	int dwID;     // 建筑种类
	int townID;   // 城镇ID
	char faction; // 种族
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x14);
	faction = *(char *)(*(char **)(c->ebp - 0xDC) + 2899 + townID * 100 + 3);
	// 如果建筑种类是6级未升级巢穴或6级已升级巢穴，且种族是精灵或男巫，那么水井增加量+1, 并以此替代之前+2的逻辑
	if(faction == 0x3 || faction == 0x4) {
		if(dwID == 24 || dwID == 29 || dwID == 30) {
			c->return_address = 0x425303;
			*(int*)(c->ebp - 0x20) += 1;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

// Well per mouth
static __stdcall int checkWellGrowth_3(LoHook* h, HookContext* c) {
	int dwID;
	int townID;
	char faction;
	dwID = *(int*)(c->ebp - 0x18);
	townID = *(int*)(c->ebp - 0x10);
	faction = *(char *)(*(char **)(c->ebp - 0x28) + 2899 + townID * 100 + 3);
	if(faction == 0x3 || faction == 0x4) {
		if(dwID == 24 || dwID == 29 || dwID == 30) {
			c->return_address = 0x426E4A;
			*(__int16*)(c->ebp - 0x4) += 1;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

static __stdcall int GhostForbidden(LoHook* h, HookContext* c) {
	*(__int16*)(c->ebp - 0x18) = 0;
	return EXEC_DEFAULT;
}

/*
__stdcall int DiplomacyForbidden(LoHook* h, HookContext* c) {
	if (c->eax == 4) {
		c->return_address = 0x486D74;
	}
	return EXEC_DEFAULT;
}*/

/*__stdcall int SSL3NewMap(LoHook* h, HookContext* c) {
  (signed int)c->eax = (signed int)c->eax * 2 - 1;
	return EXEC_DEFAULT;
}
__stdcall int SSL3MoveHero(LoHook* h, HookContext* c) {
  (signed int)c->ebx = (signed int)c->ebx * 2 - 1;
	return EXEC_DEFAULT;
}*/

static __stdcall int DiplomacyDoVision(LoHook* h, HookContext* c) {
  *(int*)(c->ebp - 0xFC) = (int)c->eax * 3 / 4;
	return EXEC_DEFAULT;
}
static __stdcall int DiplomacyPlayerMonsterInteract(LoHook* h, HookContext* c) {
  *(int*)(c->ebp - 0x1C) = (int)c->eax * 3 / 4;
	return EXEC_DEFAULT;
}

static __stdcall int MysticismPerDay(LoHook* h, HookContext* c) {
  char MysticismLevel;
  int ExtraMana;
  MysticismLevel = *(char*)(*(char**)(c->ebp - 0x20) + 124);
  switch (MysticismLevel){
    case 1: ExtraMana = 3; break; //1+1 +3=5
    case 2: ExtraMana = 7; break; //1+2 +7=10
    case 3: ExtraMana = 11; break; //1+3 +11=15
    default: ExtraMana = 0; break;
  }
  *(int*)(c->ebp - 0x1C) += ExtraMana;
	return EXEC_DEFAULT;
}

static __stdcall int EagleEyeAddPower(LoHook* h, HookContext* c) {
  int Skill, OldLevel, NewLevel, LevelDiff;
  char* Hero;
  
  Skill = *(int*)(c->ebp + 0x8);
  LevelDiff = (int)c->eax;
  OldLevel = *(int*)(c->ebp - 0x4);
  NewLevel = OldLevel + LevelDiff;
  Hero = (*(char**)(c->ebp - 0x8));
  
  if (Skill == 11) {
    if (NewLevel == 2 && LevelDiff > 0) *(Hero + 0x41) += 1;
    if (NewLevel == 3 && LevelDiff > 0) *(Hero + 0x41) += 2;
    if (NewLevel == 3 && LevelDiff > 1) *(Hero + 0x41) += 1;
  }
	return EXEC_DEFAULT;
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  if ( DLL_PROCESS_ATTACH == ul_reason_for_call) {
    if (!plugin_On) {
      plugin_On = 1;
      _P = GetPatcher();
      _PI = _P -> CreateInstance((char *)"H2_Sandruse_20260315");
      
      // H2 Eng PoL 2.1
      /*giCurPlayer = 0x5305D0;
      gpGame = 0x52477C;
      aTag_monsterInfo = 0x4F21F8;
      aDwellingCosts = 0x4F4288;
      aStandartBuildingCosts = 0x4F3F28;
      aSpecialBuildingCosts = 0x4F3E80;*/
      aSSpellInfo = 0x4F31C0;
      
      // 1）Creatures 
      // Peasant  HP 1->2 Speed 2->3
      _PI -> WriteHexPatch(0x4F21FF,(char *)"0A02000002");
      
			/*// Green Dragon's grouth from 1 to 0, same with Red Black Giant and Titan. Exe Hex offset is F078D
			_PI -> WriteHexPatch(0x4F258D,"00");
			_PI -> WriteHexPatch(0x4F25A7,"00");
			_PI -> WriteHexPatch(0x4F25C1,"00");
			_PI -> WriteHexPatch(0x4F2691,"00");
			_PI -> WriteHexPatch(0x4F26AB,"00");*/
			
			// GhostAddChange
			_PI -> WriteLoHook(0x47F281, GhostAddChange);
      
      
      
      
      // 2）Castle Buildings
      // Well
      // The growth bonus of the well for dragons and Titans is reduced by 1
			_PI -> WriteLoHook(0x41743D, checkWellGrowth_1);
			_PI -> WriteLoHook(0x4252F5, checkWellGrowth_2);
			_PI -> WriteLoHook(0x426E3C, checkWellGrowth_3);
			// The text description change
			_PI -> WriteHexPatch(0x509733,(char *)"2E000000000000000000000000000000000000000000000000");
			
      // Dungeon cost more gold 3000->6000
      _PI -> WriteHexPatch(0x4F3EEC,(char *)"7017");
			
			
			
      // 3）Map Buildings
			// Players are prohibited from recruiting ghosts
			// Function RecruitSiteEvent  0x0048CE90
			_PI -> WriteLoHook(0x48CEE7, GhostForbidden);
			
			/*// Diplomacy can't be taught by witch hut
			//  Function DoEvent  0x00485EA0
			//  hook when switch to witch hut event
			_PI -> WriteLoHook(0x486D06, DiplomacyForbidden);
			//  Diplomacy can't be learnt when levelup.
			//  The 4th secondary_skill_chances (Diplomacy) origin is 030202020202
			_PI -> WriteHexPatch(0x4F4BE8,"000000000000");*/
			
			
			
      // 4）SecondSkills
      // SECONDARY_SKILL_LOGISTICS = 2
      // float gfSSLogisticsMod[] = {  1.0,  1.1,  1.2,  1.3 };  exe hex：F1CD0 ram hex：4F3AD0
      // LOGISTICS calc ratio reduce about 1/3: 1.0,  1.1,  1.2,  1.3 -> 1.0, 1.05, 1.1, 1.2
      _PI -> WriteHexPatch(0x4F3AD0, (char *)"0000803F6666863FCDCC8C3F9A99993F");
			// The text description change
			_PI -> WriteHexPatch(0x5086C0,(char *)"352070657263656E742E00");
			_PI -> WriteHexPatch(0x50871E,(char *)"3130");
			_PI -> WriteHexPatch(0x50877A,(char *)"3230");
			
      // Sailor's Astrolabe move pointes bonus +1000 -> +700
			_PI -> WriteHexPatch(0x494C8F,(char *)"BC02");
			// Nomad's Boots move pointes bonus +600 -> +400
			_PI -> WriteHexPatch(0x494D52,(char *)"9001");
			// Traveler's Boots move pointes bonus +300 -> +200
			_PI -> WriteHexPatch(0x494D6B,(char *)"C800");
			// True Compass move pointes bonus +500 -> +350
			_PI -> WriteHexPatch(0x494D9B,(char *)"5E01");
      
      // SECONDARY_SKILL_SCOUTING = 3
      // +1 +2 +3 -> +1 +3 +5 uncompleted
			//_PI -> WriteLoHook(0x41CF3E, SSL3NewMap); //SSL3NewMap
			//_PI -> WriteLoHook(0x4C1099, SSL3MoveHero); //SSL3MoveHero
      
      // SECONDARY_SKILL_DIPLOMACY = 4
      // The monster joining rate of the Expert Diplomacy reduced: 100% -> 75%
			_PI -> WriteLoHook(0x458A60, DiplomacyDoVision);
			_PI -> WriteLoHook(0x492F90, DiplomacyPlayerMonsterInteract);
			// The text description change
			_PI -> WriteHexPatch(0x5088FA,(char *)"312F34206F662074686520637265617475726573206D6179206F6666657220746F206A6F696E20796F752E00");
			_PI -> WriteHexPatch(0x5089A4,(char *)"312F32206F662074686520637265617475726573206D6179206F6666657220746F206A6F696E20796F752E00");
			_PI -> WriteHexPatch(0x508A4C,(char *)"332F34");
      
      // SECONDARY_SKILL_MYSTICISM = 8
      // Mana get per day on each level: 2 3 4 -> 5 10 15
			_PI -> WriteLoHook(0x4250B9, MysticismPerDay);
			// The text description change
			_PI -> WriteHexPatch(0x508DAF,(char *)"35206F6620796F7572206865726F2773207370656C6C20706F696E747320706572206461792E00");
			_PI -> WriteHexPatch(0x508E0D,(char *)"3130206F6620796F7572206865726F2773207370656C6C20706F696E747320706572206461792E00");
			_PI -> WriteHexPatch(0x508E69,(char *)"3135206F6620796F7572206865726F2773207370656C6C20706F696E747320706572206461792E00");
      
      // SECONDARY_SKILL_EAGLE_EYE = 11
      // Get +1 Power when reach the advance level. Get +2 Power totally when reach the expert level.
			_PI -> WriteLoHook(0x498A33, EagleEyeAddPower);
			// The text description change
			//_PI -> WriteHexPatch(0x50912B,(char *)"00"); //10732B 401E00
			_PI -> WriteHexPatch(0x5091C6,(char *)"416476616E636564204561676C652045796520676976657320796F7572206865726F202B31205370656C6C20506F77657220616E6420612033302070657263656E74206368616E636520746F206C6561726E20616E7920337264206C6576656C207370656C6C20286F722062656C6F772920696E20636F6D6261742E00"); //1073C6 401E00
			_PI -> WriteHexPatch(0x50925C,(char *)"457870657274204561676C652045796520676976657320796F7572206865726F202B33205370656C6C20506F77657220616E6420612034302070657263656E74206368616E636520746F206C6561726E20616E7920347468206C6576656C207370656C6C20286F722062656C6F772920696E20636F6D6261742E00"); //10745C
			
			
      
      // 5）Magic
      ((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 15; // 10->15
      ((SSpellInfo*)aSSpellInfo)[SPELL_TOWN_PORTAL].cost = 50; // 20->50
		}
  }
  return TRUE;
}
