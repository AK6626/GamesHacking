The mod consists of several DLL files, some of which are bug fixes of the original game, and some of which modifies the original game in order to improve the gameplay and balance.
Technically, the user needs to download the archive (link), unpack it into the game folder. In addition, you need to replace the MSS32.dll file with the file of the same name from Heroes 3, or use GL Wrapper version 1.48 and newer (in this case, there is no need to replace the MSS32.dll file).
Download MSS file (if you do not use GL Wrapper) link
The folder Plugins contains DLL files with the required functionality. They work independently of each other and, if desired, some of them can be removed by the user. However, in my opinion, there is little point in using DLLs to improve gameplay without using bug fixes or AI enhancements.
Supported versions of the game (those versions for which I had an EXE file):
- English version Succession Wars 1.3 (1.3 Eng)
- English version Price of Loyalty 2.1 (2.1 Eng)
- English version Price of Loyalty 2.0 (2.0 Eng)
- Russian version Price of Loyalty 2.1 (2.1 Rus)
- Polish version Price of Loyalty 2.1 (2.1 Pl)
- Czech version Price of Loyalty 2.1 (2.1 Cz)

A set of DLL files:

Main modules:
--------------------------------------------------------------------------
1) H2_48_SpellsBugFixes – bug fixes related to spells:
- for the Bloodlust spell (duration is determined by the power of magic, not equal to 3)
- for massive spells (sometimes they did not work even for creatures without immunity, if there were creatures with immunity on the battlefield)
- for Earth Elemental creatures - invulnerability to Meteor Shower spell was removed (additional damage was already in the original code), added invulnerability to Elemental storm (according to NWC guidelines).
- for spellcasting by AI Dragon Slayer(there was a bug)
- for spellcasting by AI Shield/Mass shield(there was a bug)
- for spellcasting by AI Slow/Mass slow(there was a bug)
- for spellcasting by AI Haste/Mass haste(there was a bug)
- for spellcasting by AI Curse/Mass curse(there was a bug)
- in versions 2.0 Eng, 2.1 Rus, 2.1 Pl, 2.1 Cz – for spellcasting by AI Dispel/Cure/Antimagic(there was a bug)

2) H2_49_AI_NecromancyFix –correction of the number of skeletons raised after the battle with neutral monsters by AI heroes (in the original, only 1 skeleton was raised). This plugin should probably not be used if you are playing without a DLL to improve game balance (where the number of skeletons is reduced from 10/20/30% to 5/10/20%), as AI heroes often accumulate very large amounts skeletons.

3)H2_70_AI_Imrovements –AI improvements. The most significant is the increase in “AI thinking radius” for the choice of actions on the adventure map. In the original, this number was very small, and the AI heroes were "blind"because of this. After increasing this number, the AI heroes added great aggression (they became more similar in behavior to the AI heroes from Heroes 3), and the gameplay became more interesting. Also quite significant is the improvement of the algorithm for choosing a spell in battle - the algorithm has become more adequate and adaptive to changing conditions.

4)H2_80_GameplayImprovements –gameplay and balance improvements.
- Well gives +1 growth (instead of +2) for Green Dragons, Red Dragons, Black Dragons, Giants, Titans.
- secondary skill Necromancy gives 5/10/15% of skeletons (instead of 10/20/30%)
- secondary skill Eagle Eye gives a 40/50/60% chance to learn a spell (instead of 20/30/40%)
- secondary skill Archery does not allow you to avoid the penalty when shooting through the fortress walls
- changed the cost of buying Red Dragons (4000 gold instead of 3500), Black Dragons (4500 gold instead of 4000), Ogres (350 gold instead of 300), Crusaders (900 gold instead of 1000), Liches (700 gold instead of 750), Power Liches (800 gold instead of 900).
- changed Ogres (speed 2->3, health 40->45)
- changed Archmages (probability of spec.ability 20%->30%)
- changed the cost of upgrading buildings Armory (1500 gold instead of 2000), Jousting Arena (2500 gold instead of 3000), Cathedral (3000 gold, 5 crystals, 5 wood instead of 5000 gold, 10 crystals, 10 wood), Archery Range (1000 gold instead of 1500), Stonehenge (1000 gold, 5 stones instead of 1500 gold, 5 mercury), Mausoleum (2500 gold instead of 3000), Ivory Tower (3000 gold instead of 4000), Cloud Castle (10000 gold instead of 12500), Adobe (2000 gold instead of 3000)
- changed the cost of building Cloud Castle (8000 gold instead of 12500), Laboratory (12500 gold instead of 10000), Adobe (3000 gold instead of 2000), buildings to increase the growth of the 1st level (750 gold instead of 1000), special building of the Knight (1000 gold instead of 1500), special building of the Sorceress (1000 gold instead of 1500), special building Barbarian (1000 gold) instead of 2000), special building of the Warlock (4000 gold instead of 3000), building of the Left Turret (1000 gold instead of 1500), building of the Right Tower (1000 gold instead of 1500), Moat building (500 gold instead of 750)
- Hypnotize spell was moved from 5th level to 3, the spell does not end after an attack (as in Heroes 3)
- damage of Cold Ring, Fireball, Fireblast spells increased by one and a half times
- changed the chances of appearing in the Mage Guild of the spells Dragon Slayer (+), Cold Ring (-), Cold Ray (-), Fireball (-), Lightning Bolt (-), Magic Arrow (+), Anti magic (+)
- Shield spell was moved from level 1 to level 2 (this is done in order to “dilute” the 2 level of the Mage Guild, oversaturated with very useful spells)
- changed the cost of the spells Hypnotize (10 instead of 15), Dimension Door (20 instead of 10), Shield (5 instead of 3), Mass Shield (10 instead of 7), Slow (6 instead of 3), Haste (5 instead of 3), Mass Haste (12 instead of 10), Blind (7 instead of 6), Animate Dead (12 instead of 10), Town Gate (12 instead of 10), Town Portal (30 instead of 20), Set Guardian... (12 instead of 15)
- spell Haunt is disabled in Shrines on map
- shooting towers attack parameter was increased by 2, also damage was increased (from 2-3 to 2-4)
- the starting armies of heroes have been changed; the Knight has 20-40 Peasants and 3-5 Archers, the Barbarian has 10-15 Goblins and 3-5 Orcs, the Sorceress has 8-12 Sprites and 2-3 Dwarves, the Warlock has 4-6 Centaurs and 2-3 Gargoyles, and the Wizard 4-6 Halfling and 2-3 Boars, Necromancer 4-6 Skeleton and 2-3 Zombies
- the restoration of movement points for heroes fleeing the battlefield and redeemed on the same day was removed (now as in Heroes 3)
- the starting number of creatures that join free of charge at map objects has been changed; Halflings 15-30 instead of 20-40, Archers 10-20 instead of 10-25, Goblins 15-30 instead of 15-40, Sprites 10-20 instead of 15-25, Dwarves 8-15 instead of 10-20
- the starting number of creatures that join for charge at map objects has been changed; Trolls (Troll bridge) 4-8 instead of 4-6, Power Liches (Dead City)  4-8 instead of 4-6
- the week growth of creatures that join for charge at map objects has been changed; Trolls (Troll bridge) 2-4 instead of 1-3, Power Liches (Dead City)  2-4 instead of 1-3, Nomads (Desert Tent)  2-4 instead of 1-3, Rogues (Wagon Camp)  4-8 instead of 3-6.
- artifact Statesman's Quill moved from level 1 to level 3
- reduced prices for rare resources for the construction of magic guilds 2-5 (each by 1)

Auxiliary modules:
------------------------------------------------------------------
H2_42_ProperRandomArts - plugin for PoL 2.1 version - denied random appearance of so-called artifacts level 3+
(like PoL 2.0 game mechanics)
The author of the patch is AlexSpl

H2_71_AI_TeleportSpell - plugin that allows the AI ​​to use the Teleport spell in combat. The spell prob. in magic guilds has been increased compared to the original game.

H2_30_BugFixes_Misc
It includes various small fixes (module will be updated as soon as new fixes will be done):
- updating max. movement points of heroes when they go from shore to boat or vice versa (to better know where hero can go tomorrow)
- bugfix of AI interactions with monsters when AI have both Diplomacy SS and Necromancy (thanks to Arstahd)
- fix of Vision spell when hero have Diplomacy (proper number of joined monsters) (thanks to Arstahd)
- some bugfixes of Quick Combat

New modules with gameplay changes:
------------------------------------------------------------------
H2_83_Anti_RedRush.
- The weekly increase in the players' castles occurs only after the corresponding player has been given a turn. That is, if a player on the 1st day of the week captures castle of some player who play later, then he will not get newborn creatures.


It is possible that not all maps from the original game will be compatible with these changes (in the sense of an interesting game and the possibility of winning), although the vast majority will be compatible. Personally, I tested many maps and I can say that the game has become more thoughtful and interesting.