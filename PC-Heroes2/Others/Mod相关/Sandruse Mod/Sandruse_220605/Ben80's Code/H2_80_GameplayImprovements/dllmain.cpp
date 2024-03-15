#include "../../include2021/patcher_x86.hpp"
#include "../../include2021/H2Structures.h"
#include <stdio.h>

Patcher* _P;
PatcherInstance* _PI;

static _bool_ plugin_On = 0;

int aTag_monsterInfo;
int aSSpellInfo;
int aDwellingCosts;
int aStandartBuildingCosts;
int aSpecialBuildingCosts;

int giCurPlayer;
int gpGame;

int __stdcall calcTowerArchersAttack(LoHook* h, HookContext* c)
{
	if(h->GetAddress() == 0x4A4676)
		c->ecx *= 2;
	else
		c->eax *= 2;

	return EXEC_DEFAULT;
}

int __stdcall checkWellGrowth_1(LoHook* h, HookContext* c)
{
	townManager* tM;
	if(h->GetAddress() == 0x4AB2BE)
		tM = *(townManager**)(c->ebp - 0xA8);
	else
		tM = *(townManager**)(c->ebp - 0xA4);

	int dwLevel;

	if(h->GetAddress() == 0x41A701)
		dwLevel = *(int*)(c->ebp - 0x68);
	else
		dwLevel = *(int*)(c->ebp - 0x34);

	if(tM->castle->factionID == FACTION_WIZARD || tM->castle->factionID == FACTION_WARLOCK)
		if(dwLevel == 5)
		{
			*(int*)(c->ebp - 0xA0) -= 1;
		}

	return EXEC_DEFAULT;
}

int __stdcall checkWellGrowth_2(LoHook* h, HookContext* c)
{
	int factionID;
	int hookAddress = h->GetAddress();

	if(hookAddress == 0x457FE2 || hookAddress == 0x45856C || hookAddress == 0x457BFF || hookAddress == 0x4572EF)
		factionID = (*(game**)(c->ebp - 0xF8))->castles[*(int*)(c->ebp - 0x14)].factionID;
	if(hookAddress == 0x4252F5)
		factionID = (*(game**)(c->ebp - 0xDC))->castles[*(int*)(c->ebp - 0x14)].factionID;
	if(hookAddress == 0x47D220)
		factionID = (*(game**)(c->ebp - 0xDC))->castles[*(int*)(c->ebp - 0x10)].factionID;
	if(hookAddress == 0x477703)
		factionID = (*(gameSW**)(c->ebp - 0xD8))->castles[*(int*)(c->ebp - 0x14)].factionID;

	int buildingCode;
	if(hookAddress == 0x47D220)
		buildingCode = *(int*)(c->ebp - 0x14);
	else
		buildingCode = *(int*)(c->ebp - 0x18);

	if(factionID == FACTION_WIZARD || factionID == FACTION_WARLOCK)
	{
		if(buildingCode == BUILDING_DWELLING_6 || buildingCode == BUILDING_UPGRADE_5 ||
			buildingCode == BUILDING_UPGRADE_5B)
		{
			if(hookAddress == 0x477703)
				c->return_address = 0x477711;

			if(hookAddress == 0x457FE2)
				c->return_address = 0x457FEF;

			if(hookAddress == 0x4252F5)
				c->return_address = 0x425303;

			if(hookAddress == 0x47D220)
				c->return_address = 0x47D22E;

			if(hookAddress == 0x45856C)
				c->return_address = 0x458579;

			if(hookAddress == 0x457BFF)
				c->return_address = 0x457C0C;

			if(hookAddress == 0x4572EF)
				c->return_address = 0x4572FC;

			*(int*)(c->ebp - 0x20) += 1;
			return NO_EXEC_DEFAULT;
		}
	}

	return EXEC_DEFAULT;
}

int __stdcall checkWellGrowth_3(LoHook* h, HookContext* c)
{
	int factionID;
	int hookAddress = h->GetAddress();

	if(hookAddress == 0x459C33 || hookAddress == 0x45A1DA || hookAddress == 0x459850 || hookAddress == 0x458F40)
		factionID = (*(game**)(c->ebp - 0x20))->castles[*(int*)(c->ebp - 0x10)].factionID;
	if(hookAddress == 0x426E3C || hookAddress == 0x47ED60)
		factionID = (*(game**)(c->ebp - 0x28))->castles[*(int*)(c->ebp - 0x10)].factionID;
	if(hookAddress == 0x478FA3)
		factionID = (*(gameSW**)(c->ebp - 0x28))->castles[*(int*)(c->ebp - 0x10)].factionID;

	int buildingCode;
	if(hookAddress == 0x47ED60)
		buildingCode = *(int*)(c->ebp - 0x14);
	else
		buildingCode = *(int*)(c->ebp - 0x18);

	if(factionID == FACTION_WIZARD || factionID == FACTION_WARLOCK)
		if(buildingCode == BUILDING_DWELLING_6 || buildingCode == BUILDING_UPGRADE_5 ||
			buildingCode == BUILDING_UPGRADE_5B)
		{
			if(hookAddress == 0x47ED60)
				*(int*)(c->ebp - 0x18) += 1;
			else
				*(int*)(c->ebp - 4) += 1;

			if(hookAddress == 0x459C33)
				c->return_address = 0x459C40;
			
			if(hookAddress == 0x426E3C)
				c->return_address = 0x426E4A;
	
			if(hookAddress == 0x47ED60)
				c->return_address = 0x47ED6E;
			
			if(hookAddress == 0x478FA3)
				c->return_address = 0x478FB1;
			
			if(hookAddress == 0x45A1DA)
				c->return_address = 0x45A1E7;
			
			if(hookAddress == 0x459850)
				c->return_address = 0x45985D;
			
			if(hookAddress == 0x458F40)
				c->return_address = 0x458F4D;

			return NO_EXEC_DEFAULT;
		}

	return EXEC_DEFAULT;
}

int __stdcall fireballDamage(LoHook* h, HookContext* c)
{
	c->eax = c->eax * 1.5;

    return EXEC_DEFAULT;
}

int __stdcall fixAI_HypnotizeWeighting(LoHook* h, HookContext* c)
{
	c->eax = c->eax * 2.5;

    return EXEC_DEFAULT;
}

/*
int __stdcall giveEESpells(LoHook* h, HookContext* c)
{
	combatManager* cm;

	if(h->GetAddress() == 0x4218F8 || h->GetAddress() == 0x49E7FA)
		cm = *(combatManager**)(c->ebp - 0xA4);
	if(h->GetAddress() == 0x499782)
		cm = *(combatManager**)(c->ebp - 0x84);
	if(h->GetAddress() == 0x498AAF || h->GetAddress() == 0x497D78 || h->GetAddress() == 0x497478)
		cm = *(combatManager**)(c->ebp - 0x98);	
		
	int spellId = *(int*)(c->ebp + 8);

	cm->heroes[1 - cm->currentActionSide]->spellsLearned[spellId] = 1;

	return EXEC_DEFAULT;
}

int __stdcall giveEESpellsSW(LoHook* h, HookContext* c)
{
	combatManagerSW* cm;
	cm = *(combatManagerSW**)(c->ebp - 0xA4);

	int spellId = *(int*)(c->ebp + 8);

	cm->heroes[1 - cm->currentActionSide]->spellsLearned[spellId] = 1;

	return EXEC_DEFAULT;
}
*/

int __stdcall improvedEagleEye(LoHook* h, HookContext* c)
{
	int hookAddress = h->GetAddress();

	if(hookAddress == 0x499778 || hookAddress == 0x49746E || hookAddress == 0x497D6E || hookAddress == 0x498AA5)
		c->edx += 2;
	else
		c->ebx += 2;

	return EXEC_DEFAULT;
}

int __stdcall changeNecromancy(LoHook* h, HookContext* c)
{
	c->eax /= 2;

	return EXEC_DEFAULT;
}

int __stdcall calcTavernHeroMobility(LoHook* h, HookContext* c)
{
	int hookAddress = h->GetAddress();
	int calcMobilityProc;

	if(hookAddress == 0x4763B0)
		calcMobilityProc = 0x40AF00;
	if(hookAddress == 0x47BEAC)
		calcMobilityProc = 0x46C526;
	if(hookAddress == 0x423F63)
		calcMobilityProc = 0x494BB0;
	if(hookAddress == 0x456D29)
		calcMobilityProc = 0x460F87;
	if(hookAddress == 0x457287)
		calcMobilityProc = 0x461330;
	if(hookAddress == 0x456927)
		calcMobilityProc = 0x460CD7;
	if(hookAddress == 0x456017)
		calcMobilityProc = 0x4603C7;

	if(hookAddress == 0x4763B0)
	{
		for(int i=0; i<54; i++)
		{
			if((*(gameSW**)gpGame)->heroes[i].ownerIdx < 0)
			{
				(*(gameSW**)gpGame)->heroes[i].mobility = CALL_1(int, __thiscall, calcMobilityProc, (int)&((*(gameSW**)gpGame)->heroes[i]));
				(*(gameSW**)gpGame)->heroes[i].remainingMobility = (*(gameSW**)gpGame)->heroes[i].mobility;
			}
		}
	}
	else
	{
		for(int i=0; i<54; i++)
		{
			if((*(game**)gpGame)->heroes[i].ownerIdx < 0)
			{
				(*(game**)gpGame)->heroes[i].mobility = CALL_1(int, __thiscall, calcMobilityProc, (int)&((*(game**)gpGame)->heroes[i]));
				(*(game**)gpGame)->heroes[i].remainingMobility = (*(game**)gpGame)->heroes[i].mobility;
			}
		}
	}

	return EXEC_DEFAULT;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    if ( DLL_PROCESS_ATTACH == ul_reason_for_call)
    {
        if (!plugin_On)
        {
            plugin_On = 1;       
            _P = GetPatcher();
			_PI = _P->CreateInstance("H2_80_GameplayImprovements");

			int check;

			// H2 Eng SW 1.3
            check = *(int*)(0x434317+6);
			if(check == 0x14000000)
			{
				gpGame = 0x520DA4;

				aTag_monsterInfo = 0x4F12B8;
				aDwellingCosts = 0x4F3340;
				aStandartBuildingCosts = 0x4F2FE0;
				aSpecialBuildingCosts = 0x4F2F38;
				aSSpellInfo = 0x4F2280;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;
				
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;
				
				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;			
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x47C3D2+3, 30);
				_PI->WriteByte(0x47C3E8+3, 50);
				_PI->WriteByte(0x47C3FE+3, 70);
				_PI->WriteByte(0x47C414+3, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x408985, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x4B9268, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x4B9E16+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x4B9E22+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x4B9E6A+3, 0xF);

				// fireball, fireblast, cold ring
				_PI->WriteLoHook(0x42B681, fireballDamage);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x43FDB3, "%n", 15);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x4A61BA, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x41DEA3, "90 E9");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x423E07, "%n", 24);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x47A282+4, 20); // peasants
				_PI->WriteByte(0x47A288+4, 40); // peasants
				_PI->WriteByte(0x47A294+4, 3); // archers
				_PI->WriteByte(0x47A29A+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x47A2B8+4, 10); // goblins
				_PI->WriteByte(0x47A2BE+4, 15); // goblins
				_PI->WriteByte(0x47A2CA+4, 3); // orcs
				_PI->WriteByte(0x47A2D0+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x47A2EE+4, 8); // sprites
				_PI->WriteByte(0x47A2F4+4, 12); // sprites
				_PI->WriteByte(0x47A300+4, 2); // dwarves
				_PI->WriteByte(0x47A306+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x47A324+4, 4); // centaures
				_PI->WriteByte(0x47A32A+4, 6); // centaures
				_PI->WriteByte(0x47A336+4, 2); // gargoyles
				_PI->WriteByte(0x47A33C+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x47A35A+4, 4); // halflings
				_PI->WriteByte(0x47A360+4, 6); // halflings
				_PI->WriteByte(0x47A36C+4, 2); // boars
				_PI->WriteByte(0x47A372+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x47A390+4, 4); // skeletons
				_PI->WriteByte(0x47A396+4, 6); // skeletons
				_PI->WriteByte(0x47A3A2+4, 2); // zombie
				_PI->WriteByte(0x47A3A8+4, 3); // zombie

				_PI->WriteLoHook(0x497A65, checkWellGrowth_1);
				_PI->WriteLoHook(0x477703, checkWellGrowth_2);
				_PI->WriteLoHook(0x478FA3, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x4294D9, giveEESpellsSW);
				//_PI->WriteCodePatch(0x49BCDC, "%n", 46);
				_PI->WriteLoHook(0x4294C2, improvedEagleEye);
				_PI->WriteByte(0x5065AD, 0x34);
				_PI->WriteByte(0x50664B, 0x35);
				_PI->WriteByte(0x5066DF, 0x36);

				// archers
				_PI->WriteByte(0x4714F6+1, 15);
				// goblins
				_PI->WriteByte(0x47152F+1, 25);
				// sprites
				_PI->WriteByte(0x471B38+1, 20);
				_PI->WriteByte(0x471B3D+1, 10);
				// dwarves
				_PI->WriteByte(0x471B71+1, 10);
				_PI->WriteByte(0x471B76+1, 7);
				// halflings
				_PI->WriteByte(0x471C55+1, 20);
				_PI->WriteByte(0x471C5A+1, 10);
				// skeletons
				_PI->WriteByte(0x471D5E+1, 20);

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x440FF6, changeNecromancy);
				_PI->WriteLoHook(0x441086, changeNecromancy);
				_PI->WriteLoHook(0x49D69F, changeNecromancy);
				_PI->WriteByte(0x506768, 0x20);
				_PI->WriteByte(0x506769, 0x35);
				_PI->WriteByte(0x5067F6, 0x31);
				_PI->WriteByte(0x506882, 0x31);
				_PI->WriteByte(0x506883, 0x35);

				_PI->WriteLoHook(0x4763B0, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x496C68, "90 90 90");
				_PI->WriteHexPatch(0x496C80, "90 90 90");

			}

			// H2 Eng PoL 2.0
            check = *(int*)(0x41BFB7+6);
			if(check == 0x14000000)
			{
				gpGame = 0x5290A8;

				aTag_monsterInfo = 0x4FAEB0;
				aDwellingCosts = 0x4FCF40;
				aStandartBuildingCosts = 0x4FCBE0;
				aSpecialBuildingCosts = 0x4FCB38;
				aSSpellInfo = 0x4FBE78;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;
				
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;
				
				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;			
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x482246+6, 30);
				_PI->WriteByte(0x48225F+6, 50);
				_PI->WriteByte(0x482278+6, 70);
				_PI->WriteByte(0x482291+6, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x451F1E, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x48824E, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x488DBA+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x488DC6+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x488E0E+3, 0xF);

				// fireball, fireblast, cold ring
				_PI->WriteLoHook(0x423AA0, fireballDamage);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x43FF67, "%n", 15);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x43332B, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x4955BF, "90 E9");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x4C139B, "%n", 24);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x4800E1+4, 20); // peasants
				_PI->WriteByte(0x4800E7+4, 40); // peasants
				_PI->WriteByte(0x4800F3+4, 3); // archers
				_PI->WriteByte(0x4800F9+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x480117+4, 10); // goblins
				_PI->WriteByte(0x48011D+4, 15); // goblins
				_PI->WriteByte(0x480129+4, 3); // orcs
				_PI->WriteByte(0x48012F+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x48014D+4, 8); // sprites
				_PI->WriteByte(0x480153+4, 12); // sprites
				_PI->WriteByte(0x48015F+4, 2); // dwarves
				_PI->WriteByte(0x480165+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x480183+4, 4); // centaures
				_PI->WriteByte(0x480189+4, 6); // centaures
				_PI->WriteByte(0x480195+4, 2); // gargoyles
				_PI->WriteByte(0x48019B+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x4801B9+4, 4); // halflings
				_PI->WriteByte(0x4801BF+4, 6); // halflings
				_PI->WriteByte(0x4801CB+4, 2); // boars
				_PI->WriteByte(0x4801D1+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x4801EF+4, 4); // skeletons
				_PI->WriteByte(0x4801F5+4, 6); // skeletons
				_PI->WriteByte(0x480201+4, 2); // zombie
				_PI->WriteByte(0x480207+4, 3); // zombie

				_PI->WriteLoHook(0x41A701, checkWellGrowth_1);
				_PI->WriteLoHook(0x47D220, checkWellGrowth_2);
				_PI->WriteLoHook(0x47ED60, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x4218F8, giveEESpells);
				//_PI->WriteCodePatch(0x42D5F8, "%n", 46);
				_PI->WriteLoHook(0x4218E1, improvedEagleEye);
				_PI->WriteByte(0x511E05, 0x34);
				_PI->WriteByte(0x511EA3, 0x35);
				_PI->WriteByte(0x511F37, 0x36);

				// archers
				_PI->WriteByte(0x476F07+1, 15);
				// goblins
				_PI->WriteByte(0x476F40+1, 25);
				// sprites
				_PI->WriteByte(0x477549+1, 20);
				_PI->WriteByte(0x47754E+1, 10);
				// dwarves
				_PI->WriteByte(0x477582+1, 10);
				_PI->WriteByte(0x477587+1, 7);
				// halflings
				_PI->WriteByte(0x477666+1, 20);
				_PI->WriteByte(0x47766B+1, 10);
				// skeletons
				_PI->WriteByte(0x47776F+1, 20);

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x4411F9, changeNecromancy);
				_PI->WriteLoHook(0x44128F, changeNecromancy);
				_PI->WriteLoHook(0x42EF9D, changeNecromancy);
				_PI->WriteByte(0x4F42E6, 0x20);
				_PI->WriteByte(0x4F42E7, 0x35);
				_PI->WriteByte(0x511FC0, 0x20);
				_PI->WriteByte(0x511FC1, 0x35);
				_PI->WriteByte(0x51204E, 0x31);
				_PI->WriteByte(0x5120DA, 0x31);
				_PI->WriteByte(0x5120DB, 0x35);

				_PI->WriteLoHook(0x47BEAC, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x419904, "90 90 90");
				_PI->WriteHexPatch(0x419910, "90 90 90");

			}

			// H2 Eng PoL 2.1
            check = *(int*)(0x484DC1+6);
			if(check == 0x14000000)
			{
				giCurPlayer = 0x5305D0;
				gpGame = 0x52477C;
				
				aTag_monsterInfo = 0x4F21F8;
				aDwellingCosts = 0x4F4288;
				aStandartBuildingCosts = 0x4F3F28;
				aSpecialBuildingCosts = 0x4F3E80;
				aSSpellInfo = 0x4F31C0;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;
				
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;
				
				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;			
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x42A42C+3, 30);
				_PI->WriteByte(0x42A442+3, 50);
				_PI->WriteByte(0x42A458+3, 70);
				_PI->WriteByte(0x42A46E+3, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x4825A6, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x4674C3, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x4680B2+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x4680BE+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x468106+3, 0xF);
				// fireball, fireblast, cold ring
				_PI->WriteLoHook(0x4A09AE, fireballDamage);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x4B2B45, "%n", 15);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x469F16, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x479D26, "90 E9");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x46AC14, "%n", 24);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x42821E+4, 20); // peasants
				_PI->WriteByte(0x428224+4, 40); // peasants
				_PI->WriteByte(0x428230+4, 3); // archers
				_PI->WriteByte(0x428236+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x428254+4, 10); // goblins
				_PI->WriteByte(0x42825A+4, 15); // goblins
				_PI->WriteByte(0x428266+4, 3); // orcs
				_PI->WriteByte(0x42826C+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x42828A+4, 8); // sprites
				_PI->WriteByte(0x428290+4, 12); // sprites
				_PI->WriteByte(0x42829C+4, 2); // dwarves
				_PI->WriteByte(0x4282A2+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x4282C0+4, 4); // centaures
				_PI->WriteByte(0x4282C6+4, 6); // centaures
				_PI->WriteByte(0x4282D2+4, 2); // gargoyles
				_PI->WriteByte(0x4282D8+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x4282F6+4, 4); // halflings
				_PI->WriteByte(0x4282FC+4, 6); // halflings
				_PI->WriteByte(0x428308+4, 2); // boars
				_PI->WriteByte(0x42830E+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x42832C+4, 4); // skeletons
				_PI->WriteByte(0x428332+4, 6); // skeletons
				_PI->WriteByte(0x42833E+4, 2); // zombie
				_PI->WriteByte(0x428344+4, 3); // zombie

				_PI->WriteLoHook(0x41743D, checkWellGrowth_1);
				_PI->WriteLoHook(0x4252F5, checkWellGrowth_2);
				_PI->WriteLoHook(0x426E3C, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x49E7FA, giveEESpells);
				//_PI->WriteCodePatch(0x43E006, "%n", 46);
				_PI->WriteLoHook(0x49E7E3, improvedEagleEye);
				_PI->WriteByte(0x50914D, 0x34);
				_PI->WriteByte(0x5091EB, 0x35);
				_PI->WriteByte(0x50927F, 0x36);

				// archers
				_PI->WriteByte(0x41EE0F+1, 15);
				// goblins
				_PI->WriteByte(0x41EE48+1, 25);
				// sprites
				_PI->WriteByte(0x41F451+1, 20);
				_PI->WriteByte(0x41F456+1, 10);
				// dwarves
				_PI->WriteByte(0x41F48A+1, 10);
				_PI->WriteByte(0x41F48F+1, 7);
				// halflings
				_PI->WriteByte(0x41F56E+1, 20);
				_PI->WriteByte(0x41F573+1, 10);
				// skeletons
				_PI->WriteByte(0x41F677+1, 20);

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

				_PI->WriteLoHook(0x423F63, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x416621, "90 90 90");
				_PI->WriteHexPatch(0x416639, "90 90 90");
			
			}

			// H2 Rus PoL 2.1
            check = *(int*)(0x4710BE+6);
			if(check == 0x14000000)
			{	
				gpGame = 0x526124;

				aDwellingCosts = 0x4FC46C;
				aTag_monsterInfo = 0x4FA460;
				aSSpellInfo = 0x4FB3B8;
				aStandartBuildingCosts = 0x4FC110;
				aSpecialBuildingCosts = 0x4FC068;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;

				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;

				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x45CBEC+3, 30);
				_PI->WriteByte(0x45CBFB+3, 50);
				_PI->WriteByte(0x45CC0A+3, 70);
				_PI->WriteByte(0x45CC19+3, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x41F888, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x49742C, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x497D85+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x497D8E+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x497DC4+3, 0xF);
				// fireball, fireblast, cold ring
				_PI->WriteByte(0x49B5A1+2, 0xF);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x485A4B, "%n", 11);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x4A4676, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x42AB17, "EB");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x4165AA, "%n", 20);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x45AD38+4, 20); // peasants
				_PI->WriteByte(0x45AD3E+4, 40); // peasants
				_PI->WriteByte(0x45AD4A+4, 3); // archers
				_PI->WriteByte(0x45AD50+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x45AD6E+4, 10); // goblins
				_PI->WriteByte(0x45AD74+4, 15); // goblins
				_PI->WriteByte(0x45AD80+4, 3); // orcs
				_PI->WriteByte(0x45AD86+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x45ADA4+4, 8); // sprites
				_PI->WriteByte(0x45ADAA+4, 12); // sprites
				_PI->WriteByte(0x45ADB6+4, 2); // dwarves
				_PI->WriteByte(0x45ADBC+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x45ADDA+4, 4); // centaures
				_PI->WriteByte(0x45ADE0+4, 6); // centaures
				_PI->WriteByte(0x45ADEC+4, 2); // gargoyles
				_PI->WriteByte(0x45ADF2+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x45AE10+4, 4); // halflings
				_PI->WriteByte(0x45AE16+4, 6); // halflings
				_PI->WriteByte(0x45AE22+4, 2); // boars
				_PI->WriteByte(0x45AE28+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x45AE46+4, 4); // skeletons
				_PI->WriteByte(0x45AE4C+4, 6); // skeletons
				_PI->WriteByte(0x45AE58+4, 2); // zombie
				_PI->WriteByte(0x45AE5E+4, 3); // zombie

				_PI->WriteLoHook(0x4AB2BE, checkWellGrowth_1);
				_PI->WriteLoHook(0x457FE2, checkWellGrowth_2);
				_PI->WriteLoHook(0x459C33, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x499782, giveEESpells);
				//_PI->WriteCodePatch(0x42DFFB, "%n", 47);
				_PI->WriteLoHook(0x499778, improvedEagleEye);
				_PI->WriteByte(0x510B2C, 0x34);
				_PI->WriteByte(0x510BC0, 0x35);
				_PI->WriteByte(0x510C5C, 0x36);

				// archers
				_PI->WriteByte(0x451EFA+1, 15);
				// goblins
				_PI->WriteByte(0x451F39+1, 25);
				// sprites
				_PI->WriteByte(0x45257B+1, 20);
				_PI->WriteByte(0x452580+1, 10);
				// dwarves
				_PI->WriteByte(0x4525BA+1, 10);
				_PI->WriteByte(0x4525BF+1, 7);
				// halflings
				_PI->WriteByte(0x4526B5+1, 20);
				_PI->WriteByte(0x4526BA+1, 10);
				// skeletons
				_PI->WriteByte(0x4527CF+1, 20);

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x48697C, changeNecromancy);
				_PI->WriteLoHook(0x4869FD, changeNecromancy);
				_PI->WriteLoHook(0x42F8DA, changeNecromancy);
				_PI->WriteByte(0x51D434, 0x20);
				_PI->WriteByte(0x51D435, 0x35);
				_PI->WriteByte(0x510CF0, 0x20);
				_PI->WriteByte(0x510CF1, 0x35);
				_PI->WriteByte(0x510D6C, 0x31);
				_PI->WriteByte(0x510DE8, 0x31);
				_PI->WriteByte(0x510DE9, 0x35);

				_PI->WriteLoHook(0x456D29, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x4AA4E2, "90 90 90");
				_PI->WriteHexPatch(0x4AA4FA, "90 90 90");

			}

			// H2 Pol PoL 2.1
            check = *(int*)(0x470C7C+6);
			if(check == 0x14000000)
			{
				gpGame = 0x51DD88;

				aTag_monsterInfo = 0x4EF2A8;
				aDwellingCosts = 0x4F12B4;
				aStandartBuildingCosts = 0x4F0F58;
				aSpecialBuildingCosts = 0x4F0EB0;
				aSSpellInfo = 0x4F0200;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;

				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_GIANT].fight_value_aux = 47;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_TITAN].fight_value_aux = 44;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;

				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x45D269+3, 30);
				_PI->WriteByte(0x45D278+3, 50);
				_PI->WriteByte(0x45D287+3, 70);
				_PI->WriteByte(0x45D296+3, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x41FBEA, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x49671D, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x4970A2+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x4970AB+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x4970E1+3, 0xF);

				// fireball, fireblast, cold ring
				_PI->WriteByte(0x49A934+2, 0xF);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x4852B3, "%n", 11);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x4A3AE3, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x42B138, "EB");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x4169AF, "%n", 20);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x45B328+4, 20); // peasants
				_PI->WriteByte(0x45B32E+4, 40); // peasants
				_PI->WriteByte(0x45B33A+4, 3); // archers
				_PI->WriteByte(0x45B340+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x45B35E+4, 10); // goblins
				_PI->WriteByte(0x45B364+4, 15); // goblins
				_PI->WriteByte(0x45B370+4, 3); // orcs
				_PI->WriteByte(0x45B376+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x45B394+4, 8); // sprites
				_PI->WriteByte(0x45B39A+4, 12); // sprites
				_PI->WriteByte(0x45B3A6+4, 2); // dwarves
				_PI->WriteByte(0x45B3AC+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x45B3CA+4, 4); // centaures
				_PI->WriteByte(0x45B3D0+4, 6); // centaures
				_PI->WriteByte(0x45B3DC+4, 2); // gargoyles
				_PI->WriteByte(0x45B3E2+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x45B400+4, 4); // halflings
				_PI->WriteByte(0x45B406+4, 6); // halflings
				_PI->WriteByte(0x45B412+4, 2); // boars
				_PI->WriteByte(0x45B418+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x45B436+4, 4); // skeletons
				_PI->WriteByte(0x45B43C+4, 6); // skeletons
				_PI->WriteByte(0x45B448+4, 2); // zombie
				_PI->WriteByte(0x45B44E+4, 3); // zombie

				_PI->WriteLoHook(0x4AA684, checkWellGrowth_1);
				_PI->WriteLoHook(0x45856C, checkWellGrowth_2);
				_PI->WriteLoHook(0x45A1DA, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x498AAF, giveEESpells);
				//_PI->WriteCodePatch(0x42E69E, "%n", 47);
				_PI->WriteLoHook(0x498AA5, improvedEagleEye);
				_PI->WriteByte(0x50795F, 0x34);
				_PI->WriteByte(0x5079F9, 0x35);
				_PI->WriteByte(0x507AA8, 0x36);

				// archers
				_PI->WriteByte(0x4523DB+1, 15);
				// goblins
				_PI->WriteByte(0x45241A+1, 25);
				// sprites
				_PI->WriteByte(0x452A5C+1, 20);
				_PI->WriteByte(0x452A61+1, 10);
				// dwarves
				_PI->WriteByte(0x452A9B+1, 10);
				_PI->WriteByte(0x452AA0+1, 7);
				// halflings
				_PI->WriteByte(0x452B96+1, 20);
				_PI->WriteByte(0x452B9B+1, 10);
				// skeletons
				_PI->WriteByte(0x452CB0+1, 20);

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x4861FE, changeNecromancy);
				_PI->WriteLoHook(0x48627F, changeNecromancy);
				_PI->WriteLoHook(0x430019, changeNecromancy);
				_PI->WriteByte(0x514DA9, 0x20);
				_PI->WriteByte(0x514DAA, 0x35);
				_PI->WriteByte(0x507B76, 0x20);
				_PI->WriteByte(0x507B77, 0x35);
				_PI->WriteByte(0x507BEC, 0x31);
				_PI->WriteByte(0x507C5F, 0x31);
				_PI->WriteByte(0x507C60, 0x35);

				_PI->WriteLoHook(0x457287, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x4A991A, "90 90 90");
				_PI->WriteHexPatch(0x4A9932, "90 90 90");
				
			}

			// H2 Cz PoL 2.1 New
            check = *(int*)(0x47091E+6);
			if(check == 0x14000000)
			{
				gpGame = 0x52187C;

				aTag_monsterInfo = 0x4F4690;
				aDwellingCosts = 0x4F66D8;
				aStandartBuildingCosts = 0x4F6378;
				aSpecialBuildingCosts = 0x4F62D0;
				aSSpellInfo = 0x4F5610;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;

				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;

				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x45C813+3, 30);
				_PI->WriteByte(0x45C822+3, 50);
				_PI->WriteByte(0x45C831+3, 70);
				_PI->WriteByte(0x45C840+3, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x41F70D, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x495988, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x4962F5+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x4962FE+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x496334+3, 0xF);

				// fireball, fireblast, cold ring
				_PI->WriteByte(0x499C1C+2, 0xF);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x4848A7, "%n", 11);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x4A2B46, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x42AB55, "EB");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x41623A, "%n", 20);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x45A955+4, 20); // peasants
				_PI->WriteByte(0x45A95B+4, 40); // peasants
				_PI->WriteByte(0x45A967+4, 3); // archers
				_PI->WriteByte(0x45A96D+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x45A98B+4, 10); // goblins
				_PI->WriteByte(0x45A991+4, 15); // goblins
				_PI->WriteByte(0x45A99D+4, 3); // orcs
				_PI->WriteByte(0x45A9A3+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x45A9C1+4, 8); // sprites
				_PI->WriteByte(0x45A9C7+4, 12); // sprites
				_PI->WriteByte(0x45A9D3+4, 2); // dwarves
				_PI->WriteByte(0x45A9D9+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x45A9F7+4, 4); // centaures
				_PI->WriteByte(0x45A9FD+4, 6); // centaures
				_PI->WriteByte(0x45AA09+4, 2); // gargoyles
				_PI->WriteByte(0x45AA0F+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x45AA2D+4, 4); // halflings
				_PI->WriteByte(0x45AA33+4, 6); // halflings
				_PI->WriteByte(0x45AA3F+4, 2); // boars
				_PI->WriteByte(0x45AA45+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x45AA63+4, 4); // skeletons
				_PI->WriteByte(0x45AA69+4, 6); // skeletons
				_PI->WriteByte(0x45AA75+4, 2); // zombie
				_PI->WriteByte(0x45AA7B+4, 3); // zombie

				_PI->WriteLoHook(0x4A9357, checkWellGrowth_1);
				_PI->WriteLoHook(0x457BFF, checkWellGrowth_2);
				_PI->WriteLoHook(0x459850, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x497D78, giveEESpells);
				//_PI->WriteCodePatch(0x42DFC9, "%n", 47);
				_PI->WriteLoHook(0x497D6E, improvedEagleEye);
				_PI->WriteByte(0x50BCEF, 0x34);
				_PI->WriteByte(0x50BD89, 0x35);
				_PI->WriteByte(0x50BE2B, 0x36);

				// archers
				_PI->WriteByte(0x451B88+1, 15);
				// goblins
				_PI->WriteByte(0x451BC7+1, 25);
				// sprites
				_PI->WriteByte(0x452209+1, 20);
				_PI->WriteByte(0x45220E+1, 10);
				// dwarves
				_PI->WriteByte(0x452248+1, 10);
				_PI->WriteByte(0x45224D+1, 7);
				// halflings
				_PI->WriteByte(0x452343+1, 20);
				_PI->WriteByte(0x452348+1, 10);
				// skeletons
				_PI->WriteByte(0x45245D+1, 20);

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x4857D8, changeNecromancy);
				_PI->WriteLoHook(0x485859, changeNecromancy);
				_PI->WriteLoHook(0x42F78E, changeNecromancy);
				_PI->WriteByte(0x518280, 0x20);
				_PI->WriteByte(0x518281, 0x35);
				_PI->WriteByte(0x50BECD, 0x20);
				_PI->WriteByte(0x50BECE, 0x35);
				_PI->WriteByte(0x50BF4F, 0x31);
				_PI->WriteByte(0x50BFD1, 0x31);
				_PI->WriteByte(0x50BFD2, 0x35);

				_PI->WriteLoHook(0x456927, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x4A863F, "90 90 90");
				_PI->WriteHexPatch(0x4A8657, "90 90 90");

			}

			// H2 Cz PoL 2.1 Old
            check = *(int*)(0x47000E+6);
			if(check == 0x14000000)
			{
				gpGame = 0x51C9DC;

				aTag_monsterInfo = 0x4F1538;
				aDwellingCosts = 0x4F3580;
				aStandartBuildingCosts = 0x4F3220;
				aSpecialBuildingCosts = 0x4F3178;
				aSSpellInfo = 0x4F24B8;

				((building_cost*)aStandartBuildingCosts)[BUILDING_SPECIAL_GROWTH].gold = 750;
				((building_cost*)aStandartBuildingCosts)[BUILDING_LEFT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_RIGHT_TURRET].gold = 1000;
				((building_cost*)aStandartBuildingCosts)[BUILDING_MOAT].gold = 500;

				((building_cost*)aSpecialBuildingCosts)[FACTION_KNIGHT].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_BARBARIAN].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_SORCERESS].gold = 1000;
				((building_cost*)aSpecialBuildingCosts)[FACTION_WARLOCK].gold = 4000;

				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_3 - 19].gold = 1500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_4 - 19].gold = 2500;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].crystal = 5;
				((building_cost*)aDwellingCosts)[12 * FACTION_KNIGHT + BUILDING_UPGRADE_5 - 19].wood = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_2 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].gold = 1000;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].mercury = 0;
				((building_cost*)aDwellingCosts)[12 * FACTION_SORCERESS + BUILDING_UPGRADE_3 - 19].ore = 5;

				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_DWELLING_6 - 19].gold = 12500;
				((building_cost*)aDwellingCosts)[12 * FACTION_NECROMANCER + BUILDING_UPGRADE_4 - 19].gold = 2500;

				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_4 - 19].gold = 3000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_DWELLING_6 - 19].gold = 8000;
				((building_cost*)aDwellingCosts)[12 * FACTION_WIZARD + BUILDING_UPGRADE_5 - 19].gold = 10000;
				
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].cost = 900;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].cost = 350;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].cost = 700;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].cost = 800;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].cost = 4000;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].cost = 4500;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_OGRE].fight_value_aux = 31;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_CRUSADER].fight_value_aux = 64;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_LICH].fight_value_aux = 30;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_POWER_LICH].fight_value_aux = 32;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_RED_DRAGON].fight_value_aux = 54;
				((tag_monsterInfo*)aTag_monsterInfo)[CREATURE_BLACK_DRAGON].fight_value_aux = 56;

				((SSpellInfo*)aSSpellInfo)[SPELL_DRAGON_SLAYER].appearingChance = 200;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_LIGHTNING_BOLT].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RAY].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_COLD_RING].nonMagicFactionAppearanceChance[i] = 6;
				for(int i=0; i<6; i++)
					((SSpellInfo*)aSSpellInfo)[SPELL_FIREBALL].nonMagicFactionAppearanceChance[i] = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_CHAIN_LIGHTNING].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_METEOR_SHOWER].appearingChance = 800;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT].appearingChance = 700;
				((SSpellInfo*)aSSpellInfo)[SPELL_RESURRECT_TRUE].appearingChance = 900;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_CURSE].appearingChance = 650;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANTI_MAGIC].appearingChance = 400;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].level = 3;
				((SSpellInfo*)aSSpellInfo)[SPELL_HYPNOTIZE].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_DIMENSION_DOOR].cost = 20;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].appearingChance = 200;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_SHIELD].level = 2;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].appearingChance = 500;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_SHIELD].cost = 10;
				((SSpellInfo*)aSSpellInfo)[SPELL_SLOW].cost = 6;
				((SSpellInfo*)aSSpellInfo)[SPELL_HASTE].cost = 5;
				((SSpellInfo*)aSSpellInfo)[SPELL_MASS_HASTE].cost = 12;
				((SSpellInfo*)aSSpellInfo)[SPELL_BLIND].cost = 7;
				((SSpellInfo*)aSSpellInfo)[SPELL_ANIMATE_DEAD].cost = 12;

				// magic arrow - 30%, ligh bolt - 20%, cold ray - 20%, cold ring 15%, fireball 15%
				_PI->WriteByte(0x45BF03+3, 30);
				_PI->WriteByte(0x45BF12+3, 50);
				_PI->WriteByte(0x45BF21+3, 70);
				_PI->WriteByte(0x45BF30+3, 85);

				// hypnotyze spell will not be cancel after strike
				_PI->WriteCodePatch(0x41F2BC, "%n", 10);
				// AI weights hypnotyze
				_PI->WriteLoHook(0x495088, fixAI_HypnotizeWeighting);

				// fireball damage
				_PI->WriteByte(0x4959F5+3, 0xF);
				// fireblast damage
				_PI->WriteByte(0x4959FE+3, 0xF);
				// cold ring damage
				_PI->WriteByte(0x495A34+3, 0xF);

				// fireball, fireblast, cold ring
				_PI->WriteByte(0x49931C+2, 0xF);

				// AI calculate archery penalty at siege battles (FightValueOfStack)
				_PI->WriteCodePatch(0x483F97, "%n", 11);

				// arrow tower attack (each magic guild +1 -> +2)
				_PI->WriteLoHook(0x4A2246, calcTowerArchersAttack);

				// archery penalty at siege battles
				_PI->WriteHexPatch(0x42A591, "EB");
				// AI calculate archery penalty at siege battles (DoCompAI)
				_PI->WriteCodePatch(0x41623A, "%n", 20);

				// Starting hero armies
				// Knight 20-40 peasants, 3-5 archers
				_PI->WriteByte(0x45A045+4, 20); // peasants
				_PI->WriteByte(0x45A04B+4, 40); // peasants
				_PI->WriteByte(0x45A057+4, 3); // archers
				_PI->WriteByte(0x45A05D+4, 5); // archers
				// Barbarian 10-15 goblins, 3-5 orcs
				_PI->WriteByte(0x45A07B+4, 10); // goblins
				_PI->WriteByte(0x45A081+4, 15); // goblins
				_PI->WriteByte(0x45A08D+4, 3); // orcs
				_PI->WriteByte(0x45A093+4, 5); // orcs
				// Sorceress 8-12 sprites, 2-3 dwarves
				_PI->WriteByte(0x45A0B1+4, 8); // sprites
				_PI->WriteByte(0x45A0B7+4, 12); // sprites
				_PI->WriteByte(0x45A0C3+4, 2); // dwarves
				_PI->WriteByte(0x45A0C9+4, 3); // dwarves
				// Warlock 4-6 centaures, 2-3 gargoyles
				_PI->WriteByte(0x45A0E7+4, 4); // centaures
				_PI->WriteByte(0x45A0ED+4, 6); // centaures
				_PI->WriteByte(0x45A0F9+4, 2); // gargoyles
				_PI->WriteByte(0x45A0FF+4, 3); // gargoyles
				// Wizard 4-6 halflings, 2-3 boars
				_PI->WriteByte(0x45A11D+4, 4); // halflings
				_PI->WriteByte(0x45A123+4, 6); // halflings
				_PI->WriteByte(0x45A12F+4, 2); // boars
				_PI->WriteByte(0x45A135+4, 3); // boars
				// Necromancer 4-6 skeletons, 2-3 zombie
				_PI->WriteByte(0x45A153+4, 4); // skeletons
				_PI->WriteByte(0x45A159+4, 6); // skeletons
				_PI->WriteByte(0x45A165+4, 2); // zombie
				_PI->WriteByte(0x45A16B+4, 3); // zombie

				_PI->WriteLoHook(0x4A8A57, checkWellGrowth_1);
				_PI->WriteLoHook(0x4572EF, checkWellGrowth_2);
				_PI->WriteLoHook(0x458F40, checkWellGrowth_3);

				// improved Eagle Eye (spells during battle immediately)
				//_PI->WriteLoHook(0x497478, giveEESpells);
				//_PI->WriteCodePatch(0x42D9F9, "%n", 47);
				_PI->WriteLoHook(0x49746E, improvedEagleEye);
				_PI->WriteByte(0x506DBF, 0x34);
				_PI->WriteByte(0x506E59, 0x35);
				_PI->WriteByte(0x506EFB, 0x36);

				// archers
				_PI->WriteByte(0x451278+1, 15);
				// goblins
				_PI->WriteByte(0x4512B7+1, 25);
				// sprites
				_PI->WriteByte(0x4518F9+1, 20);
				_PI->WriteByte(0x4518FE+1, 10);
				// dwarves
				_PI->WriteByte(0x451938+1, 10);
				_PI->WriteByte(0x45193D+1, 7);
				// halflings
				_PI->WriteByte(0x451A33+1, 20);
				_PI->WriteByte(0x451A38+1, 10);
				// skeletons
				_PI->WriteByte(0x451B4D+1, 20);

				// Necromancy 5/10/15%
				_PI->WriteLoHook(0x484EC8, changeNecromancy);
				_PI->WriteLoHook(0x484F49, changeNecromancy);
				_PI->WriteLoHook(0x42F1BE, changeNecromancy);
				_PI->WriteByte(0x513358, 0x20);
				_PI->WriteByte(0x513359, 0x35);
				_PI->WriteByte(0x506F9D, 0x20);
				_PI->WriteByte(0x506F9E, 0x35);
				_PI->WriteByte(0x50701F, 0x31);
				_PI->WriteByte(0x5070A1, 0x31);
				_PI->WriteByte(0x5070A2, 0x35);

				_PI->WriteLoHook(0x456017, calcTavernHeroMobility);
				_PI->WriteHexPatch(0x4A7D3F, "90 90 90");
				_PI->WriteHexPatch(0x4A7D57, "90 90 90");

			}

        }
    }

   return TRUE;
}

