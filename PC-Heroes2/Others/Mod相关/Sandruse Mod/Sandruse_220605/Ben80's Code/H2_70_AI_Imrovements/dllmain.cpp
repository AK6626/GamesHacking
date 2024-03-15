#include "../../include2021/patcher_x86.hpp"
#include "../../include2021/H2Structures.h"

Patcher* _P;
PatcherInstance* _PI;

static _bool_ plugin_On = 0;

int attackerStrength;
int defenderStrength;

int gpGame;
int gpCurAIHero;

int __stdcall setGuardianManaCondition(LoHook* h, HookContext* c)
{
	c->eax *= 2;

    return EXEC_DEFAULT;
}

int __stdcall AI_saveTown(LoHook* h, HookContext* c)
{
	int nCastles;
	if(h->GetAddress() == 0x446B72 || h->GetAddress() == 0x4465C8)
		nCastles = (*(gameSW**)gpGame)->players[((heroSW*)gpCurAIHero)->ownerIdx].numCastles;
	else
		nCastles = (*(game**)gpGame)->players[((hero*)gpCurAIHero)->ownerIdx].numCastles;
	
	if(nCastles == 0)
		c->eax += 50000;

    return EXEC_DEFAULT;
}

int __stdcall getArmyStrengths(LoHook* h, HookContext* c)
{
	int fightValueOfStackProc;

	int hookAddress = h->GetAddress();
	
	if(hookAddress == 0x430202)
		fightValueOfStackProc = 0x43FED2;
	if(hookAddress == 0x440C6F)
		fightValueOfStackProc = 0x4B2AB0;
	if(hookAddress == 0x430A06)
		fightValueOfStackProc = 0x4859C8;
	if(hookAddress == 0x43116C)
		fightValueOfStackProc = 0x485230;
	if(hookAddress == 0x43082E)
		fightValueOfStackProc = 0x484824;
	if(hookAddress == 0x43025E)
		fightValueOfStackProc = 0x483F14;

	combatManager* cm = *(combatManager**)(c->ebp - 8);

	if(cm->heroes[0] && cm->heroes[1])
	{
		if(cm->isCastleBattle)
		{
			attackerStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[0], cm->heroes[0], 1, 0, 0, 1);
			defenderStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[1], cm->heroes[1], 1, 1, cm->castles[1]->idx, 0);
		}
		else
		{
			attackerStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[0], cm->heroes[0], 1, 0, 0, 0);
			defenderStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[1], cm->heroes[1], 1, 0, 0, 0);
		}
	}

	return EXEC_DEFAULT;
}

int __stdcall getArmyStrengthsSW(LoHook* h, HookContext* c)
{
	int fightValueOfStackProc;

	fightValueOfStackProc = 0x43FD1E;

	combatManagerSW* cm = *(combatManagerSW**)(c->ebp - 8);

	if(cm->heroes[0] && cm->heroes[1])
	{
		if(cm->isCastleBattle)
		{
			attackerStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[0], cm->heroes[0], 1, 0, 0, 1);
			defenderStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[1], cm->heroes[1], 1, 1, cm->castles[1]->idx, 0);
		}
		else
		{
			attackerStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[0], cm->heroes[0], 1, 0, 0, 0);
			defenderStrength = CALL_6(int, __stdcall, fightValueOfStackProc, cm->armies[1], cm->heroes[1], 1, 0, 0, 0);
		}
	}

	return EXEC_DEFAULT;
}

int __stdcall AI_SpellsWeightImprovement(LoHook* h, HookContext* c)
{
	int spell;
	int hookAddress = h->GetAddress();

	if(hookAddress == 0x4869D7)
		spell = *(int*)(c->ebp - 0xC);
	else
		spell = *(int*)(c->ebp - 0x10);

	combatManager* cm = *(combatManager**)(c->ebp - 0x20);
	combatManagerSW* cmSW = *(combatManagerSW**)(c->ebp - 0x20);

	if(spell == SPELL_RESURRECT || spell == SPELL_RESURRECT_TRUE || spell == SPELL_ANIMATE_DEAD ||
	spell == SPELL_SUMMON_EARTH_ELEMENTAL || spell == SPELL_SUMMON_AIR_ELEMENTAL ||
	spell == SPELL_SUMMON_FIRE_ELEMENTAL || spell == SPELL_SUMMON_WATER_ELEMENTAL)
	{
		c->eax = c->eax * 4 / 3;
	}

	if(spell == SPELL_FIREBALL || spell == SPELL_FIREBLAST || spell == SPELL_LIGHTNING_BOLT ||
	spell == SPELL_CHAIN_LIGHTNING || spell == SPELL_HOLY_WORD || spell == SPELL_HOLY_SHOUT ||
	spell == SPELL_ARMAGEDDON || spell == SPELL_ELEMENTAL_STORM || spell == SPELL_METEOR_SHOWER ||
	spell == SPELL_COLD_RAY || spell == SPELL_COLD_RING || spell == SPELL_DEATH_RIPPLE ||
	spell == SPELL_DEATH_WAVE)
	{
		c->eax = c->eax * 4 / 3;

		double forcesRelation;

		int currentSide;
		if(hookAddress == 0x4B7A44)
			currentSide = cmSW->currentActionSide;
		else
			currentSide = cm->currentActionSide;
		
		if(currentSide)
			forcesRelation = (double)attackerStrength / (double)defenderStrength;
		else
			forcesRelation = (double)defenderStrength / (double)attackerStrength;

		double coef = 0.33 * forcesRelation * forcesRelation + 0.67;
		if(coef < 1.0)
			coef = 1.0;
		if(coef > 10.0)
			coef = 10.0;

		c->eax = coef * c->eax;

	}

	return EXEC_DEFAULT;
}

int __stdcall disableCastle_AI(LoHook* h, HookContext* c)
{
	town* townAI = *(town**)(c->ebp + 8);
	int returnAddress;

	int hookAddress = h->GetAddress();
	if(hookAddress == 0x43D750) // En 1.3
		returnAddress = 0x43D824;
	if(hookAddress == 0x43D734) // En 2.0
		returnAddress = 0x43D81E;
	if(hookAddress == 0x4B044D) // En 2.1
		returnAddress = 0x4B0521;
	if(hookAddress == 0x4837A9) // Rus 2.1
		returnAddress = 0x48386F;
	if(hookAddress == 0x482F6D) // Pl 2.1
		returnAddress = 0x483033;
	if(hookAddress == 0x482649) // Cz 2.1 New
		returnAddress = 0x48270F;
	if(hookAddress == 0x481D39) // Cz 2.1 Old
		returnAddress = 0x481DFF;

	int building;
	if(hookAddress == 0x43D734)
		building = *(int*)(c->ebp - 0x14);
	else
		building = *(int*)(c->ebp - 0x10);

	if(building == BUILDING_CASTLE)
	{
		if((*(game**)gpGame)->players[townAI->ownerIdx].numCastles == 1)
			return EXEC_DEFAULT;

		int doubleBuilds = 0;
		for(int i=0; i<72; i++)
		{
			if((*(game**)gpGame)->castles[i].factionID == townAI->factionID &&
			(*(game**)gpGame)->castles[i].ownerIdx == townAI->ownerIdx )
				doubleBuilds += 1;
		}


		if(doubleBuilds <= 1)
			if((*(game**)gpGame)->players[townAI->ownerIdx].resources[RESOURCE_GOLD] < 25000)
			{
				c->return_address = returnAddress;
				return NO_EXEC_DEFAULT;
			}

		if(doubleBuilds == 2)
			if((*(game**)gpGame)->players[townAI->ownerIdx].resources[RESOURCE_GOLD] < 15000)
			{
				c->return_address = returnAddress;
				return NO_EXEC_DEFAULT;
			}
	}

	return EXEC_DEFAULT;
}

int __stdcall fixQuickBattle(LoHook* h, HookContext* c)
{
	if(*(float*)(*(float**)(c->ebp + 0x28)) >= (float)0.92)
		*(float*)(*(float**)(c->ebp + 0x28)) = (float)1.0;
	else
		if(*(float*)(*(float**)(c->ebp + 0x28)) >= (float)0.88)
			*(float*)(*(float**)(c->ebp + 0x28)) += (float)0.07;
		else
			if(*(float*)(*(float**)(c->ebp + 0x28)) >= (float)0.80)
				*(float*)(*(float**)(c->ebp + 0x28)) += (float)0.05;
			else
				if(*(float*)(*(float**)(c->ebp + 0x28)) >= (float)0.70)
					*(float*)(*(float**)(c->ebp + 0x28)) += (float)0.04;
				else
					if(*(float*)(*(float**)(c->ebp + 0x28)) >= (float)0.60)
						*(float*)(*(float**)(c->ebp + 0x28)) += (float)0.02;

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
			_PI = _P->CreateInstance("H2_AI_Improvements");

			int check;

			// H2 Eng SW 1.3
            check = *(int*)(0x434317+6);
			if(check == 0x14000000)
			{
				gpCurAIHero = 0x4E4DA4;
				gpGame = 0x520DA4;

				_PI->WriteLoHook(0x4B7A44, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x49E8D8, getArmyStrengthsSW);

				// improve AI map radius thinking
				_PI->WriteDword(0x439AD2+1, 4000);

				_PI->WriteLoHook(0x48CA95, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x423801, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x423A54, "D0 03 4E 00");
				_PI->WriteHexPatch(0x423A69, "CD CC 4C 3E");

				_PI->WriteLoHook(0x4465C8, AI_saveTown);
				_PI->WriteLoHook(0x446B72, AI_saveTown);

				_PI->WriteLoHook(0x43D750, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x43A50A+6, "9A 99 99 3E");
				_PI->WriteByte(0x43A606+2, 24);
				_PI->WriteHexPatch(0x43A60F+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x43CA61, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x43DF14+1, 0x8C);

			}

			// H2 Eng PoL 2.0
            check = *(int*)(0x41BFB7+6);
			if(check == 0x14000000)
			{
				gpCurAIHero = 0x4F2110;
				gpGame = 0x5290A8;

				_PI->WriteLoHook(0x4869D7, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x430202, getArmyStrengths);

				// improve AI map radius thinking
				_PI->WriteDword(0x439A35+1, 4000);

				_PI->WriteLoHook(0x4B21F1, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x4C0DD5, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x4C0FDA, "48 B2 4E 00");
				_PI->WriteHexPatch(0x4C0FEC, "CD CC 4C 3E");

				_PI->WriteLoHook(0x446E77, AI_saveTown);
				_PI->WriteLoHook(0x447421, AI_saveTown);

				_PI->WriteLoHook(0x43D734, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x43A46D+6, "9A 99 99 3E");
				_PI->WriteByte(0x43A564+2, 24);
				_PI->WriteHexPatch(0x43A56D+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x43CA1D, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x43DF39+1, 0x8C);

			}

			// H2 Eng PoL 2.1
            check = *(int*)(0x484DC1+6);
			if(check == 0x14000000)
			{
				gpCurAIHero = 0x51D5BC;
				gpGame = 0x52477C;

				_PI->WriteLoHook(0x465C87, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x440C6F, getArmyStrengths);

				// improve AI map radius thinking
				_PI->WriteDword(0x4AC7C4+1, 4000);

				// human attack bonus
				//_PI->WriteHexPatch(0x4EA7F0, "0a d7 a3 70 3d 0a b7 3f");
				// comp. attack bonus
				//_PI->WriteHexPatch(0x4EA7F8, "33 33 33 33 33 33 c3 3f");

				_PI->WriteLoHook(0x48FCEE, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x46A603, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x46A856, "B0 AE 4E 00");
				_PI->WriteHexPatch(0x46A86B, "CD CC 4C 3E");

				_PI->WriteLoHook(0x4B9A31, AI_saveTown);
				_PI->WriteLoHook(0x4B9FE0, AI_saveTown);

				_PI->WriteLoHook(0x4B044D, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x4AD204+6, "9A 99 99 3E");
				_PI->WriteByte(0x4AD2FB+2, 24);
				_PI->WriteHexPatch(0x4AD304+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x4AF738, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x4B0C2E+1, 0x8C);
			
			}

			// H2 Rus PoL 2.1
            check = *(int*)(0x4710BE+6);
			if(check == 0x14000000)
			{
				gpCurAIHero = 0x5331F8;
				gpGame = 0x526124;

				_PI->WriteLoHook(0x495F60, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x430A06, getArmyStrengths);

				// improve AI map radius thinking
				_PI->WriteDword(0x4800B3+2, 4000);

				_PI->WriteLoHook(0x44515D, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x415FFA, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x416221, "98 A5 4E 00");
				_PI->WriteHexPatch(0x416232, "CD CC 4C 3E");

				_PI->WriteLoHook(0x48BC19, AI_saveTown);
				_PI->WriteLoHook(0x48C0EF, AI_saveTown);

				_PI->WriteLoHook(0x4837A9, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x4809E0+6, "9A 99 99 3E");
				_PI->WriteByte(0x480AC1+2, 24);
				_PI->WriteHexPatch(0x480AC6+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x482C44, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x483E72, 0x7C);

			}

			// H2 Pol PoL 2.1
            check = *(int*)(0x470C7C+6);
			if(check == 0x14000000)
			{
				gpCurAIHero = 0x52AE80;
				gpGame = 0x51DD88;

				_PI->WriteLoHook(0x495240, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x43116C, getArmyStrengths);

				// improve AI map radius thinking
				_PI->WriteDword(0x47F860+2, 4000);

				_PI->WriteLoHook(0x445B3A, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x4163FA, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x416621, "40 E5 4D 00");
				_PI->WriteHexPatch(0x416632, "CD CC 4C 3E");

				_PI->WriteLoHook(0x48B5BB, AI_saveTown);
				_PI->WriteLoHook(0x48BA95, AI_saveTown);

				_PI->WriteLoHook(0x482F6D, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x48018F+6, "9A 99 99 3E");
				_PI->WriteByte(0x480270+2, 24);
				_PI->WriteHexPatch(0x480275+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x48240B, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x483658, 0x7C);

			}

            // H2 Cz PoL 2.1 New
            check = *(int*)(0x47091E+6);
            if(check == 0x14000000)
            {
				gpCurAIHero = 0x52E9C0;
                gpGame = 0x52187C;

				_PI->WriteLoHook(0x494440, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x43082E, getArmyStrengths);

				// improve AI map radius thinking
				_PI->WriteDword(0x47EF43+2, 4000);

				_PI->WriteLoHook(0x4453BD, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x415C8A, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x415EB1, "38 56 4E 00");
				_PI->WriteHexPatch(0x415EC2, "CD CC 4C 3E");

				_PI->WriteLoHook(0x48AAE0, AI_saveTown);
				_PI->WriteLoHook(0x48AFBE, AI_saveTown);

				_PI->WriteLoHook(0x482649, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x47F870+6, "9A 99 99 3E");
				_PI->WriteByte(0x47F951+2, 24);
				_PI->WriteHexPatch(0x47F956+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x481AD4, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x482D12, 0x7C);

            }

            // H2 Cz PoL 2.1 Old
            check = *(int*)(0x47000E+6);
            if(check == 0x14000000)
            {
				gpCurAIHero = 0x529B20;
                gpGame = 0x51C9DC;

				_PI->WriteLoHook(0x493B40, AI_SpellsWeightImprovement);
				_PI->WriteLoHook(0x43025E, getArmyStrengths);

				// improve AI map radius thinking
				_PI->WriteDword(0x47E633+2, 4000);

				_PI->WriteLoHook(0x444AB6, setGuardianManaCondition);

				// AI should retreat earlier (0.2 instead of 0.16)
				_PI->WriteHexPatch(0x415C8A, "CD CC 4C 3E");
				_PI->WriteHexPatch(0x415EB1, "48 42 4E 00");
				_PI->WriteHexPatch(0x415EC2, "CD CC 4C 3E");

				_PI->WriteLoHook(0x48A1D0, AI_saveTown);
				_PI->WriteLoHook(0x48A6AE, AI_saveTown);

				_PI->WriteLoHook(0x481D39, disableCastle_AI);

				// defend town on first week
				_PI->WriteHexPatch(0x47EF60+6, "9A 99 99 3E");
				_PI->WriteByte(0x47F041+2, 24);
				_PI->WriteHexPatch(0x47F046+6, "00 00 00 3F");

				// quick battle fix
				_PI->WriteLoHook(0x4811C4, fixQuickBattle);

				// blue giant patch
				_PI->WriteByte(0x482402, 0x7C);

            }

        }
    }

   return TRUE;
}
