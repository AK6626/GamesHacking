#include "../../include2021/patcher_x86.hpp"
#include "../../include2021/H2Structures.h"
#include <stdio.h>

Patcher* _P;
PatcherInstance* _PI;

static _bool_ plugin_On = 0;


int armyOtherArmyAdjacentProcAddress;
int AI_RawEffectSwitchReturnAddress;

int __stdcall AI_DragonSlayerBugFix(LoHook* h, HookContext* c)
{
    int hookAddress = h->GetAddress();
    combatManager* cm;
    combatManagerSW* cmSW;
    army* AIStack;

    if(hookAddress == 0x4B931A)
    {
        cmSW = *(combatManagerSW**)(c->ebp - 0x58);
    }

    if(hookAddress == 0x467575 || hookAddress == 0x488300)
    {
        cm = *(combatManager**)(c->ebp - 0x58);
    }

    if(hookAddress == 0x4974A2 || hookAddress == 0x496793 || hookAddress == 0x4959FE || hookAddress == 0x4950FE)
    {
        cm = *(combatManager**)(c->ebp - 0x54);
    }

    AIStack = *(army**)(c->ebp + 8);

    int numDragons = 0;
    bool isDragonsAdjacent = false;

    if(hookAddress != 0x4B931A)
    for(int i=0; i < cm->numCreatures[1 - AIStack->owningSide]; i++)
    {
        int creatureIdx = cm->creatures[1 - AIStack->owningSide][i].creatureIdx;
        if(creatureIdx == CREATURE_GREEN_DRAGON || creatureIdx == CREATURE_RED_DRAGON ||
            creatureIdx == CREATURE_BLACK_DRAGON || creatureIdx == CREATURE_BONE_DRAGON)
		if(cm->creatures[1 - AIStack->owningSide][i].quantity > 0)
        {
            numDragons += 1;
            if(CALL_3(signed int, __thiscall, armyOtherArmyAdjacentProcAddress, AIStack,
            cm->creatures[1 - AIStack->owningSide][i].owningSide,
            cm->creatures[1 - AIStack->owningSide][i].stackIdx))
                isDragonsAdjacent = true;
        }
    }

    if(hookAddress == 0x4B931A)
    for(int i=0; i < cmSW->numCreatures[1 - AIStack->owningSide]; i++)
    {
        int creatureIdx = cmSW->creatures[1 - AIStack->owningSide][i].creatureIdx;
        if(creatureIdx == CREATURE_GREEN_DRAGON || creatureIdx == CREATURE_RED_DRAGON ||
            creatureIdx == CREATURE_BLACK_DRAGON || creatureIdx == CREATURE_BONE_DRAGON)
		if(cmSW->creatures[1 - AIStack->owningSide][i].quantity > 0)
        {
            numDragons += 1;
            if(CALL_3(signed int, __thiscall, armyOtherArmyAdjacentProcAddress, AIStack,
            cmSW->creatures[1 - AIStack->owningSide][i].owningSide,
            cmSW->creatures[1 - AIStack->owningSide][i].stackIdx))
                isDragonsAdjacent = true;
        }
    }

    int fightValue = *(int*)(c->ebp - 0x1C);
    int weight;

    if(isDragonsAdjacent)
        weight = 0.28 * fightValue;
    else
    {
        if(hookAddress == 0x4B931A)
            weight = 0.28 * fightValue * (numDragons / cmSW->numCreatures[1 - AIStack->owningSide]);
        else
            weight = 0.28 * fightValue * (numDragons / cm->numCreatures[1 - AIStack->owningSide]);
    }

    if(hookAddress == 0x488300)
        *(int*)(c->ebp - 0x38) = weight;
    else
        *(int*)(c->ebp - 0x3C) = weight;

    c->return_address = AI_RawEffectSwitchReturnAddress;

    return NO_EXEC_DEFAULT;
}

int __stdcall AI_ShieldBugFix(LoHook* h, HookContext* c)
{
    int hookAddress = h->GetAddress();
    combatManager* cm;
    combatManagerSW* cmSW;
    army* AIStack;

    if(hookAddress == 0x4B944E) // Eng 1.3
    {
        cmSW = *(combatManagerSW**)(c->ebp - 0x58);
    }

    if(hookAddress == 0x4676A9 || hookAddress == 0x488434) // Eng 2.1, Eng 2.0
    {
        cm = *(combatManager**)(c->ebp - 0x58);
    }

    if(hookAddress == 0x4975AC || hookAddress == 0x49689D || hookAddress == 0x495B08 || hookAddress == 0x495208) // Rus 2.1, Pol 2.1, Cz 2.1
    {
        cm = *(combatManager**)(c->ebp - 0x54);
    }

    AIStack = *(army**)(c->ebp + 8);

    int numShooters = 0;
	double weightShooters;

    if(hookAddress != 0x4B944E) // Eng 1.3
	{
		for(int i=0; i < cm->numCreatures[1 - AIStack->owningSide]; i++)
		{
			if(cm->creatures[1 - AIStack->owningSide][i].creature.creature_flags & SHOOTER)
			if(cm->creatures[1 - AIStack->owningSide][i].quantity > 0)
			{
				numShooters += 1;
			}
		}

		weightShooters = (double)numShooters / (double)(cm->numCreatures[1 - AIStack->owningSide]);

		/*
		if(cm->isCastleBattle && !AIStack->owningSide)
		{
			weightShooters += 0.3;
			if(weightShooters > 1.0)
				weightShooters = 1.0;
		}
		*/

	}

    if(hookAddress == 0x4B944E) // Eng 1.3
	{
		for(int i=0; i < cmSW->numCreatures[1 - AIStack->owningSide]; i++)
		{
			if(cmSW->creatures[1 - AIStack->owningSide][i].creature.creature_flags & SHOOTER)
		    if(cmSW->creatures[1 - AIStack->owningSide][i].quantity > 0)
			{
				numShooters += 1;
			}
		}

		weightShooters = (double)numShooters / (double)(cmSW->numCreatures[1 - AIStack->owningSide]);

		/*
		if(cmSW->isCastleBattle && !AIStack->owningSide)
		{
			weightShooters += 0.3;
			if(weightShooters > 1.0)
				weightShooters = 1.0;
		}
		*/
	}

    int fightValue = *(int*)(c->ebp - 0x1C);
    int weight = 0.45 * weightShooters * fightValue;

    if(hookAddress == 0x488434) // Eng 2.0
        *(int*)(c->ebp - 0x38) = weight;
    else
        *(int*)(c->ebp - 0x3C) = weight;

    c->return_address = AI_RawEffectSwitchReturnAddress;

    return NO_EXEC_DEFAULT;
}

int __stdcall correctSlowWeightSign(LoHook* h, HookContext* c)
{
	c->eax = c->eax * (-1);

	return EXEC_DEFAULT;
}

int __stdcall correctTargetX(LoHook* h, HookContext* c)
{
	int hookAddress = h->GetAddress();
	army* targetStack = *(army**)(c->ebp + 8);

	if(hookAddress == 0x4672CA || hookAddress == 0x488004 || hookAddress == 0x4B906F)
	{
		if(targetStack->owningSide == 0)
			c->return_address += 20;
		else
			c->return_address += 6;
	}

	if(hookAddress == 0x497293 || hookAddress == 0x496584 || hookAddress == 0x4957EF || hookAddress == 0x494EEF)
	{
		if(targetStack->owningSide == 0)
			c->return_address += 13;
		else
			c->return_address += 2;
	}

	return NO_EXEC_DEFAULT;
}

int __stdcall cureFix(LoHook* h, HookContext* c)
{
	int effect;
	/*
	if(h->GetAddress() == 0x497AC8 || h->GetAddress() == 0x496024)
	{
		effect = *(int*)(c->ebp - 0x20);
		if(*(int*)(c->ebp + 0x14) == 1 && effect != EFFECT_SLOW && effect != EFFECT_CURSE)
			*(int*)(c->ebp - 0x40) = 0;

	}
	else
	{
		effect = *(int*)(c->ebp - 0x18);
		if(*(int*)(c->ebp + 0x14) == 1 && effect != EFFECT_SLOW && effect != EFFECT_CURSE)
			c->edx = 0;
	}
	*/

	if(h->GetAddress() == 0x488A81)
	{
		effect = *(int*)(c->ebp - 0x18);
		if(*(int*)(c->ebp + 0x14) == 1 && effect != EFFECT_SLOW && effect != EFFECT_CURSE)
			c->edx = 0;
	}
	else
	{
		effect = *(int*)(c->ebp - 0x20);
		if(*(int*)(c->ebp + 0x14) == 1 && effect != EFFECT_SLOW && effect != EFFECT_CURSE)
			*(int*)(c->ebp - 0x40) = 0;

	}

	return EXEC_DEFAULT;
}

int __stdcall fixCurseDivider(LoHook* h, HookContext* c)
{
	int hookAddress = h->GetAddress();

	if(*(int*)(c->ebp + 0xC) == EFFECT_CURSE)
	{
		army* targetStack = *(army**)(c->ebp + 8);
		double avgDamage = 0.5 * (double)(targetStack->creature.max_damage + targetStack->creature.min_damage);
		int weight = (int)(-0.45 * *(int*)(c->ebp - 0x1C) * ((double)(avgDamage - targetStack->creature.min_damage) / (double)targetStack->creature.min_damage));

		if(hookAddress == 0x488139) // Eng 2.0
			*(int*)(c->ebp - 0x38) = weight;
		else
			*(int*)(c->ebp - 0x3C) = weight;

		c->return_address = AI_RawEffectSwitchReturnAddress;

		return NO_EXEC_DEFAULT;
	}

	return EXEC_DEFAULT;
}

int __stdcall massSpellsCastFix(LoHook* h, HookContext* c)
{
	int spell;
	int hookAddress = h->GetAddress();

	if(hookAddress != 0x422172)
		spell = *(int*)(c->ebp - 0xC);
	else
		spell = *(int*)(c->ebp - 0x1C);

	
	if(spell == SPELL_MASS_CURE || spell == SPELL_MASS_HASTE || spell == SPELL_MASS_SLOW ||
	spell == SPELL_MASS_BLESS || spell == SPELL_MASS_CURSE || spell == SPELL_HOLY_WORD ||
	spell == SPELL_HOLY_SHOUT || spell == SPELL_MASS_DISPEL || spell == SPELL_DEATH_RIPPLE ||
	spell == SPELL_DEATH_WAVE || spell == SPELL_MASS_SHIELD)
	{
		if(hookAddress == 0x499F44 || hookAddress == 0x49927D || hookAddress == 0x498546 || hookAddress == 0x497C46)
		{
			c->return_address += 0x28;
		}
		else
		{
			c->return_address += 0x31;
		}
			return NO_EXEC_DEFAULT;
	}

	return EXEC_DEFAULT;
}

int __stdcall bloodlustFix(LoHook* h, HookContext* c)
{
	int hookAddress = h->GetAddress();

	if(hookAddress == 0x42ADC9) // Eng 1.3
	{
		CALL_3(signed int, __thiscall, 0x408BE6, *(int*)(c->ebp - 0x44), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x18));

	}

	if(hookAddress == 0x4231E8) // Eng 2.0
	{
		CALL_3(signed int, __thiscall, 0x45217F, *(int*)(c->ebp - 0x4), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x8));

	}

	if(hookAddress == 0x4A00EA) // Eng 2.1
	{
		CALL_3(signed int, __thiscall, 0x482810, *(int*)(c->ebp - 0x44), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x18));
	}

	if(hookAddress == 0x49A16D) // Pol
	{
		CALL_3(signed int, __thiscall, 0x41FDD0, *(int*)(c->ebp - 0x44), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x18));
	}
	
	if(hookAddress == 0x49ADFA) // Rus
	{
		CALL_3(signed int, __thiscall, 0x41FA5F, *(int*)(c->ebp - 0x40), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x10));
	}

	if(hookAddress == 0x499436) // Cz New
	{
		CALL_3(signed int, __thiscall, 0x41F8E4, *(int*)(c->ebp - 0x44), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x18));
	}

	if(hookAddress == 0x498B36) // Cz Old
	{
		CALL_3(signed int, __thiscall, 0x41F493, *(int*)(c->ebp - 0x44), EFFECT_BLOOD_LUST, *(int*)(c->ebp - 0x18));
	}

	c->return_address += 5;
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
			_PI = _P->CreateInstance("H2_SpellsBugFixes");

			int check;


			// H2 Eng SW 1.3
            check = *(int*)(0x434317+6);
			if(check == 0x14000000)
			{
				armyOtherArmyAdjacentProcAddress = 0x40AA07;
				AI_RawEffectSwitchReturnAddress = 0x4B95BC;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x4B931A, AI_DragonSlayerBugFix);

				// fix shield
				_PI->WriteLoHook(0x4B944E, AI_ShieldBugFix);

				// fix slow
				_PI->WriteLoHook(0x4B826B, correctSlowWeightSign);
				_PI->WriteLoHook(0x4B906F, correctTargetX);
				_PI->WriteHexPatch(0x4B82DB, "DE C1");

				// fix curse
				_PI->WriteHexPatch(0x4B846D, "DE C1");
				_PI->WriteLoHook(0x4B9166, fixCurseDivider);

				_PI->WriteLoHook(0x429D53, massSpellsCastFix);

				_PI->WriteLoHook(0x42ADC9, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x409CE6, 0x1C);
				
			}

            // H2 Eng PoL 2.0
            check = *(int*)(0x41BFB7+6);
            if(check == 0x14000000)
            {
				armyOtherArmyAdjacentProcAddress = 0x453FA6;
				AI_RawEffectSwitchReturnAddress = 0x4885A2;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x488300, AI_DragonSlayerBugFix);

				// fix shield
				_PI->WriteLoHook(0x488434, AI_ShieldBugFix);

				// fix slow
				_PI->WriteLoHook(0x4871FE, correctSlowWeightSign);
				_PI->WriteLoHook(0x488004, correctTargetX);
				_PI->WriteHexPatch(0x48726E, "DE C1");

				// fix curse
				_PI->WriteHexPatch(0x487402, "DE C1");
				_PI->WriteLoHook(0x488139, fixCurseDivider);

				// fix dispel, cure, antimagic
				_PI->WriteWord(0x488AEB, 0xE1DE);
				_PI->WriteHexPatch(0x488B3F, "00 00 01 00 00 01 01 01 00 00 00 01 06 00 00");
				_PI->WriteLoHook(0x488A81, cureFix);
				_PI->WriteCodePatch(0x488B58, "%n", 17);

				_PI->WriteLoHook(0x422172, massSpellsCastFix);

				_PI->WriteLoHook(0x4231E8, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x45327F, 0x1C);

            }

			// H2 Eng PoL 2.1
            check = *(int*)(0x484DC1+6);
			if(check == 0x14000000)
			{
				armyOtherArmyAdjacentProcAddress = 0x4846B0;
				AI_RawEffectSwitchReturnAddress = 0x467817;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x467575, AI_DragonSlayerBugFix);

				// fix shield
				_PI->WriteLoHook(0x4676A9, AI_ShieldBugFix);

				// fix slow
				_PI->WriteLoHook(0x4664B5, correctSlowWeightSign);
				_PI->WriteLoHook(0x4672CA, correctTargetX);
				_PI->WriteHexPatch(0x466525, "DE C1");

				// fix curse
				_PI->WriteHexPatch(0x4666B9, "DE C1");
				_PI->WriteLoHook(0x4673C1, fixCurseDivider);

				_PI->WriteLoHook(0x49F074, massSpellsCastFix);

				_PI->WriteLoHook(0x4A00EA, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x483945, 0x1C);
			}

            // H2 Rus PoL 2.1
            check = *(int*)(0x4710BE+6);
            if(check == 0x14000000)
            {
				armyOtherArmyAdjacentProcAddress = 0x4213BC;
				AI_RawEffectSwitchReturnAddress = 0x49769E;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x4974A2, AI_DragonSlayerBugFix);

				// fix shield
				_PI->WriteLoHook(0x4975AC, AI_ShieldBugFix);

				// fix slow
				_PI->WriteLoHook(0x496639, correctSlowWeightSign);
				_PI->WriteLoHook(0x497293, correctTargetX);
				_PI->WriteHexPatch(0x4966C2, "D8 85 74 FF FF FF");

				// fix curse
				_PI->WriteHexPatch(0x49686C, "D8 85 54 FF FF FF");
				_PI->WriteLoHook(0x497369, fixCurseDivider);

				// fix dispel, cure, antimagic
				_PI->WriteWord(0x497B38, 0x6DD8);
				_PI->WriteHexPatch(0x497BD5, "00 00 01 00 00 01 01 01 00 00 00 01 02 00 00");
				_PI->WriteLoHook(0x497AC8, cureFix);
				_PI->WriteCodePatch(0x497B4D, "%n", 13);

				_PI->WriteLoHook(0x499F44, massSpellsCastFix);

				_PI->WriteLoHook(0x49ADFA, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x42087D, 0x1C);
			
            }

			// H2 Pol PoL 2.1
            check = *(int*)(0x470C7C+6);
			if(check == 0x14000000)
			{
				armyOtherArmyAdjacentProcAddress = 0x4217A0;
				AI_RawEffectSwitchReturnAddress = 0x49698F;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x496793, AI_DragonSlayerBugFix);

				// fix shield
				_PI->WriteLoHook(0x49689D, AI_ShieldBugFix);

				// fix slow
				_PI->WriteLoHook(0x495925, correctSlowWeightSign);
				_PI->WriteLoHook(0x496584, correctTargetX);
				_PI->WriteHexPatch(0x4959AE, "D8 85 74 FF FF FF");

				// fix curse
				_PI->WriteHexPatch(0x495B58, "D8 85 54 FF FF FF");
				_PI->WriteLoHook(0x49665A, fixCurseDivider);

				// fix dispel, cure, antimagic
				_PI->WriteWord(0x496E4F, 0x6DD8);
				_PI->WriteHexPatch(0x496EEC, "00 00 01 00 00 01 01 01 00 00 00 01 02 00 00");
				_PI->WriteCodePatch(0x496E64, "%n", 13);
				_PI->WriteLoHook(0x496DDF, cureFix);

				_PI->WriteLoHook(0x49927D, massSpellsCastFix);

				_PI->WriteLoHook(0x49A16D, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x420C08, 0x1C);
			}

			// H2 Cz PoL 2.1 New
            check = *(int*)(0x47091E+6);
			if(check == 0x14000000)
			{
				armyOtherArmyAdjacentProcAddress = 0x421241;
				AI_RawEffectSwitchReturnAddress = 0x495BFA;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x4959FE, AI_DragonSlayerBugFix);
				
				// fix shield
				_PI->WriteLoHook(0x495B08, AI_ShieldBugFix);
	
				// fix slow
				_PI->WriteLoHook(0x494B19, correctSlowWeightSign);
				_PI->WriteLoHook(0x4957EF, correctTargetX);
				_PI->WriteHexPatch(0x494BA2, "D8 85 74 FF FF FF");

				// fix curse
				_PI->WriteHexPatch(0x494D4C, "D8 85 54 FF FF FF");
				_PI->WriteLoHook(0x4958C5, fixCurseDivider);

				// fix dispel, cure, antimagic
				_PI->WriteWord(0x496094, 0x6DD8);
				_PI->WriteHexPatch(0x496145, "00 00 01 00 00 01 01 01 00 00 00 01 07 00 00");
				_PI->WriteCodePatch(0x4960A9, "%n", 13);
				_PI->WriteLoHook(0x496024, cureFix);

				_PI->WriteLoHook(0x498546, massSpellsCastFix);

				_PI->WriteLoHook(0x499436, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x420702, 0x1C);
			}

			// H2 Cz PoL 2.1 Old
            check = *(int*)(0x47000E+6);
			if(check == 0x14000000)
			{
				armyOtherArmyAdjacentProcAddress = 0x420DF0;
				AI_RawEffectSwitchReturnAddress = 0x4952FA;

				// fix dragon slayer
				if(!(_P->GetInstance("H2_AI_DragonSlayerFix")))
					_PI->WriteLoHook(0x4950FE, AI_DragonSlayerBugFix);

				// fix shield
				_PI->WriteLoHook(0x495208, AI_ShieldBugFix);

				// fix slow
				_PI->WriteLoHook(0x494219, correctSlowWeightSign);
				_PI->WriteLoHook(0x494EEF, correctTargetX);
				_PI->WriteHexPatch(0x4942A2, "D8 85 74 FF FF FF");

				// fix curse
				_PI->WriteHexPatch(0x49444C, "D8 85 54 FF FF FF");
				_PI->WriteLoHook(0x494FC5, fixCurseDivider);

				// fix dispel, cure, antimagic
				_PI->WriteWord(0x495794, 0x6DD8);
				_PI->WriteHexPatch(0x495845, "00 00 01 00 00 01 01 01 00 00 00 01 07 00 00");
				_PI->WriteCodePatch(0x4957A9, "%n", 13);
				_PI->WriteLoHook(0x495724, cureFix);

				_PI->WriteLoHook(0x497C46, massSpellsCastFix);

				_PI->WriteLoHook(0x498B36, bloodlustFix);

				// fix earth elemental immunity
				_PI->WriteByte(0x4202B1, 0x1C);
			}

        }
    }

   return TRUE;
}

