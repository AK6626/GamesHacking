
struct H2RECT;
struct tag_monsterInfo;
struct resourceVtable;
struct resource;
struct IconEntry;
struct icon;
struct sample;
struct SMonFrameInfo;
struct army;
struct managerVtable;
struct baseManager;
struct palette;
struct hexcell;
struct bitmap;
struct armyGroup;
struct town;
struct hero;
struct widgetVtable;
struct widget;
struct heroWindow;
struct combatManager;
struct townManager;
struct BuildingDisplay;
struct border;
struct bankBox;
struct strip;

enum CREATURE_FLAGS
{
  TWO_HEXER = 0x1,
  FLYER = 0x2,
  SHOOTER = 0x4,
  TWO_HEX_ATTACKER = 0x8,
  DEAD = 0x10,
  HAS_GOOD_MORALE = 0x20,
  RETALIATED = 0x40,
  MAYBE_NOT_LOST_TURN = 0x80,
  MIRROR_IMAGE = 0x100,
  CREATURE_RED = 0x200,
  UNDEAD = 0x400,
  CREATURE_BROWN = 0x2000,
  CREATURE_PETRIFIED = 0x4000,
};


enum RESOURCE_TYPE : __int16
{
  RESOURCE_TYPE_BITMAP = 0x0,
  RESOURCE_TYPE_ICN = 0x1,
  RESOURCE_TYPE_PALETTE = 0x2,
  RESOURCE_TYPE_TILESET = 0x3,
  RESOURCE_TYPE_FONT = 0x5,
  RESOURCE_TYPE_SAMPLE = 0x6,
};

enum SECONDARY_SKILL
{
  SECONDARY_SKILL_PATHFINDING = 0,
  SECONDARY_SKILL_ARCHERY = 1,
  SECONDARY_SKILL_LOGISTICS = 2,
  SECONDARY_SKILL_SCOUTING = 3,
  SECONDARY_SKILL_DIPLOMACY = 4,
  SECONDARY_SKILL_NAVIGATION = 5,
  SECONDARY_SKILL_LEADERSHIP = 6,
  SECONDARY_SKILL_WISDOM = 7,
  SECONDARY_SKILL_MYSTICISM = 8,
  SECONDARY_SKILL_LUCK = 9,
  SECONDARY_SKILL_BALLISTICS = 10,
  SECONDARY_SKILL_EAGLE_EYE = 11,
  SECONDARY_SKILL_NECROMANCY = 12,
  SECONDARY_SKILL_ESTATES = 13,
};

struct H2RECT
{
  LONG left;
  LONG right;
  LONG top;
  LONG bottom;
};

/*   43 */
enum CREATURE_ATTRIBUTES : __int8
{
  ATTR_MIRROR_IMAGE = 0x1,
  ATTR_BLOODLUST_RED = 0x2,
  ATTR_UNDEAD = 0x4,
  ATTR_BROWN = 0x20,
  ATTR_PETRIFY_GRAY = 0x40,
};

/*   44 */
enum CREATURES
{
  CREATURE_PEASANT = 0,
  CREATURE_ARCHER = 1,
  CREATURE_RANGER = 2,
  CREATURE_PIKEMAN = 3,
  CREATURE_VETERAN_PIKEMAN = 4,
  CREATURE_SWORDSMAN = 5,
  CREATURE_MASTER_SWORDSMAN = 6,
  CREATURE_CAVALRY = 7,
  CREATURE_CHAMPION = 8,
  CREATURE_PALADIN = 9,
  CREATURE_CRUSADER = 10,
  CREATURE_GOBLIN = 11,
  CREATURE_ORC = 12,
  CREATURE_ORC_CHIEF = 13,
  CREATURE_WOLF = 14,
  CREATURE_OGRE = 15,
  CREATURE_OGRE_LORD = 16,
  CREATURE_TROLL = 17,
  CREATURE_WAR_TROLL = 18,
  CREATURE_CYCLOPS = 19,
  CREATURE_SPRITE = 20,
  CREATURE_DWARF = 21,
  CREATURE_BATTLE_DWARF = 22,
  CREATURE_ELF = 23,
  CREATURE_GRAND_ELF = 24,
  CREATURE_DRUID = 25,
  CREATURE_GREATER_DRUID = 26,
  CREATURE_UNICORN = 27,
  CREATURE_PHOENIX = 28,
  CREATURE_CENTAUR = 29,
  CREATURE_GARGOYLE = 30,
  CREATURE_GRIFFIN = 31,
  CREATURE_MINOTAUR = 32,
  CREATURE_MINOTAUR_KING = 33,
  CREATURE_HYDRA = 34,
  CREATURE_GREEN_DRAGON = 35,
  CREATURE_RED_DRAGON = 36,
  CREATURE_BLACK_DRAGON = 37,
  CREATURE_HALFLING = 38,
  CREATURE_BOAR = 39,
  CREATURE_IRON_GOLEM = 40,
  CREATURE_STEEL_GOLEM = 41,
  CREATURE_ROC = 42,
  CREATURE_MAGE = 43,
  CREATURE_ARCHMAGE = 44,
  CREATURE_GIANT = 45,
  CREATURE_TITAN = 46,
  CREATURE_SKELETON = 47,
  CREATURE_ZOMBIE = 48,
  CREATURE_MUTANT_ZOMBIE = 49,
  CREATURE_MUMMY = 50,
  CREATURE_ROYAL_MUMMY = 51,
  CREATURE_VAMPIRE = 52,
  CREATURE_VAMPIRE_LORD = 53,
  CREATURE_LICH = 54,
  CREATURE_POWER_LICH = 55,
  CREATURE_BONE_DRAGON = 56,
  CREATURE_ROGUE = 57,
  CREATURE_NOMAD = 58,
  CREATURE_GHOST = 59,
  CREATURE_GENIE = 60,
  CREATURE_MEDUSA = 61,
  CREATURE_EARTH_ELEMENTAL = 62,
  CREATURE_AIR_ELEMENTAL = 63,
  CREATURE_FIRE_ELEMENTAL = 64,
  CREATURE_WATER_ELEMENTAL = 65,
};

/*   45 */
enum STACK_MODIFYING_EFFECT
{
  EFFECT_HASTE = 0,
  EFFECT_SLOW = 1,
  EFFECT_BLIND = 2,
  EFFECT_BLESS = 3,
  EFFECT_CURSE = 4,
  EFFECT_BERSERKER = 5,
  EFFECT_PARALYZE = 6,
  EFFECT_HYPNOTIZE = 7,
  EFFECT_DRAGON_SLAYER = 8,
  EFFECT_BLOOD_LUST = 9,
  EFFECT_SHIELD = 10,
  EFFECT_PETRIFY = 11,
  EFFECT_ANTI_MAGIC = 12,
  EFFECT_STONESKIN = 13,
  EFFECT_STEELSKIN = 14,
};

enum ARTIFACT
{
  ARTIFACT_ULTIMATE_BOOK_OF_KNOWLEDGE = 0,
  ARTIFACT_ULTIMATE_SWORD_OF_DOMINION = 1,
  ARTIFACT_ULTIMATE_CLOAK_OF_PROTECTION = 2,
  ARTIFACT_ULTIMATE_WAND_OF_MAGIC = 3,
  ARTIFACT_ULTIMATE_SHIELD = 4,
  ARTIFACT_ULTIMATE_STAFF = 5,
  ARTIFACT_ULTIMATE_CROWN = 6,
  ARTIFACT_GOLDEN_GOOSE = 7,
  ARTIFACT_ARCANE_NECKLACE_OF_MAGIC = 8,
  ARTIFACT_CASTERS_BRACELET_OF_MAGIC = 9,
  ARTIFACT_MAGES_RING_OF_POWER = 10,
  ARTIFACT_WITCHS_BROACH_OF_MAGIC = 11,
  ARTIFACT_MEDAL_OF_VALOR = 12,
  ARTIFACT_MEDAL_OF_COURAGE = 13,
  ARTIFACT_MEDAL_OF_HONOR = 14,
  ARTIFACT_MEDAL_OF_DISTINCTION = 15,
  ARTIFACT_FIZBIN_OF_MISFOURTUNE = 16,
  ARTIFACT_THUNDER_MACE_OF_DOMINION = 17,
  ARTIFACT_ARMORED_GAUNTLETS_OF_PROTECTION = 18,
  ARTIFACT_DEFENDER_HELM_OF_PROTECTION = 19,
  ARTIFACT_GIANT_FLAIL_OF_DOMINION = 20,
  ARTIFACT_BALLISTA_OF_QUICKNESS = 21,
  ARTIFACT_STEALTH_SHIELD_OF_PROTECTION = 22,
  ARTIFACT_DRAGON_SWORD_OF_DOMINION = 23,
  ARTIFACT_POWER_AXE_OF_DOMINION = 24,
  ARTIFACT_DIVINE_BREASTPLATE_OF_PROTECTION = 25,
  ARTIFACT_MINOR_SCROLL_OF_KNOWLEDGE = 26,
  ARTIFACT_MAJOR_SCROLL_OF_KNOWLEDGE = 27,
  ARTIFACT_SUPERIOR_SCROLL_OF_KNOWLEDGE = 28,
  ARTIFACT_FOREMOST_SCROLL_OF_KNOWLEDGE = 29,
  ARTIFACT_ENDLESS_SACK_OF_GOLD = 30,
  ARTIFACT_ENDLESS_BAG_OF_GOLD = 31,
  ARTIFACT_ENDLESS_PURSE_OF_GOLD = 32,
  ARTIFACT_NOMAD_BOOTS_OF_MOBILITY = 33,
  ARTIFACT_TRAVELERS_BOOTS_OF_MOBILITY = 34,
  ARTIFACT_LUCKY_RABBITS_FOOT = 35,
  ARTIFACT_GOLDEN_HORSESHOE = 36,
  ARTIFACT_GAMBLERS_LUCKY_COIN = 37,
  ARTIFACT_FOUR_LEAF_CLOVER = 38,
  ARTIFACT_TRUE_COMPASS_OF_MOBILITY = 39,
  ARTIFACT_SAILORS_ASTROLABE_OF_MOBILITY = 40,
  ARTIFACT_EVIL_EYE = 41,
  ARTIFACT_ENCHANTED_HOURGLASS = 42,
  ARTIFACT_GOLD_WATCH = 43,
  ARTIFACT_SKULLCAP = 44,
  ARTIFACT_ICE_CLOAK = 45,
  ARTIFACT_FIRE_CLOAK = 46,
  ARTIFACT_LIGHTNING_HELM = 47,
  ARTIFACT_EVERCOLD_ICICLE = 48,
  ARTIFACT_EVERHOT_LAVA_ROCK = 49,
  ARTIFACT_LIGHTNING_ROD = 50,
  ARTIFACT_SNAKE_RING = 51,
  ARTIFACT_ANKH = 52,
  ARTIFACT_BOOK_OF_ELEMENTS = 53,
  ARTIFACT_ELEMENTAL_RING = 54,
  ARTIFACT_HOLY_PENDANT = 55,
  ARTIFACT_PENDANT_OF_FREE_WILL = 56,
  ARTIFACT_PENDANT_OF_LIFE = 57,
  ARTIFACT_SERENITY_PENDANT = 58,
  ARTIFACT_SEEING_EYE_PENDANT = 59,
  ARTIFACT_KINETIC_PENDANT = 60,
  ARTIFACT_PENDANT_OF_DEATH = 61,
  ARTIFACT_WAND_OF_NEGATION = 62,
  ARTIFACT_GOLDEN_BOW = 63,
  ARTIFACT_TELESCOPE = 64,
  ARTIFACT_STATESMANS_QUILL = 65,
  ARTIFACT_WIZARDS_HAT = 66,
  ARTIFACT_POWER_RING = 67,
  ARTIFACT_AMMO_CART = 68,
  ARTIFACT_TAX_LIEN = 69,
  ARTIFACT_HIDEOUS_MASK = 70,
  ARTIFACT_ENDLESS_POUCH_OF_SULFUR = 71,
  ARTIFACT_ENDLESS_VIAL_OF_MERCURY = 72,
  ARTIFACT_ENDLESS_POUCH_OF_GEMS = 73,
  ARTIFACT_ENDLESS_CORD_OF_WOOD = 74,
  ARTIFACT_ENDLESS_CART_OF_ORE = 75,
  ARTIFACT_ENDLESS_POUCH_OF_CRYSTAL = 76,
  ARTIFACT_SPIKED_HELM = 77,
  ARTIFACT_SPIKED_SHIELD = 78,
  ARTIFACT_WHITE_PEARL = 79,
  ARTIFACT_BLACK_PEARL = 80,
  ARTIFACT_MAGIC_BOOK = 81,
  ARTIFACT_NONE1 = 82,
  ARTIFACT_NONE2 = 83,
  ARTIFACT_NONE3 = 84,
  ARTIFACT_NONE4 = 85,
  ARTIFACT_SPELL_SCROLL = 86,
  ARTIFACT_ARM_OF_THE_MARTYR = 87,
  ARTIFACT_BREASTPLATE_OF_ANDURAN = 88,
  ARTIFACT_BROACH_OF_SHIELDING = 89,
  ARTIFACT_BATTLE_GARB_OF_ANDURAN = 90,
  ARTIFACT_CRYSTAL_BALL = 91,
  ARTIFACT_HEART_OF_FIRE = 92,
  ARTIFACT_HEART_OF_ICE = 93,
  ARTIFACT_HELMET_OF_ANDURAN = 94,
  ARTIFACT_HOLY_HAMMER = 95,
  ARTIFACT_LEGENDARY_SCEPTER = 96,
  ARTIFACT_MASTHEAD = 97,
  ARTIFACT_SPHERE_OF_NEGATION = 98,
  ARTIFACT_STAFF_OF_WIZARDRY = 99,
  ARTIFACT_SWORD_BREAKER = 100,
  ARTIFACT_SWORD_OF_ANDURAN = 101,
  ARTIFACT_SPADE_OF_NECROMANCY = 102,
};

enum HERO_CONSTANTS
{
  MAX_ARTIFACTS = 14,
  MAX_TOTAL_HEROES = 48,
};

/*   40 */
enum COMBAT_CONSTANTS
{
  HEX_GRID_SIZE = 0x75,
};

enum SPELL_CONSTANTS
{
  NUM_SPELLS = 65,
};


/*   41 */
enum Spell
{
  SPELL_FIREBALL = 0,
  SPELL_FIREBLAST = 1,
  SPELL_LIGHTNING_BOLT = 2,
  SPELL_CHAIN_LIGHTNING = 3,
  SPELL_TELEPORT = 4,
  SPELL_CURE = 5,
  SPELL_MASS_CURE = 6,
  SPELL_RESURRECT = 7,
  SPELL_RESURRECT_TRUE = 8,
  SPELL_HASTE = 9,
  SPELL_MASS_HASTE = 10,
  SPELL_SLOW = 11,
  SPELL_MASS_SLOW = 12,
  SPELL_BLIND = 13,
  SPELL_BLESS = 14,
  SPELL_MASS_BLESS = 15,
  SPELL_STONESKIN = 16,
  SPELL_STEELSKIN = 17,
  SPELL_CURSE = 18,
  SPELL_MASS_CURSE = 19,
  SPELL_HOLY_WORD = 20,
  SPELL_HOLY_SHOUT = 21,
  SPELL_ANTI_MAGIC = 22,
  SPELL_DISPEL_MAGIC = 23,
  SPELL_MASS_DISPEL = 24,
  SPELL_MAGIC_ARROW = 25,
  SPELL_BERZERKER = 26,
  SPELL_ARMAGEDDON = 27,
  SPELL_ELEMENTAL_STORM = 28,
  SPELL_METEOR_SHOWER = 29,
  SPELL_PARALYZE = 30,
  SPELL_HYPNOTIZE = 31,
  SPELL_COLD_RAY = 32,
  SPELL_COLD_RING = 33,
  SPELL_DISRUPTING_RAY = 34,
  SPELL_DEATH_RIPPLE = 35,
  SPELL_DEATH_WAVE = 36,
  SPELL_DRAGON_SLAYER = 37,
  SPELL_BLOOD_LUST = 38,
  SPELL_ANIMATE_DEAD = 39,
  SPELL_MIRROR_IMAGE = 40,
  SPELL_SHIELD = 41,
  SPELL_MASS_SHIELD = 42,
  SPELL_SUMMON_EARTH_ELEMENTAL = 43,
  SPELL_SUMMON_AIR_ELEMENTAL = 44,
  SPELL_SUMMON_FIRE_ELEMENTAL = 45,
  SPELL_SUMMON_WATER_ELEMENTAL = 46,
  SPELL_EARTHQUAKE = 47,
  SPELL_VIEW_MINES = 48,
  SPELL_VIEW_RESOURCES = 49,
  SPELL_VIEW_ARTIFACTS = 50,
  SPELL_VIEW_TOWNS = 51,
  SPELL_VIEW_HEROES = 52,
  SPELL_VIEW_ALL = 53,
  SPELL_IDENTIFY = 54,
  SPELL_SUMMON_BOAT = 55,
  SPELL_DIMENSION_DOOR = 56,
  SPELL_TOWN_GATE = 57,
  SPELL_TOWN_PORTAL = 58,
  SPELL_VISIONS = 59,
  SPELL_HAUNT = 60,
  SPELL_SET_EARTH_GUARDIAN = 61,
  SPELL_SET_AIR_GUARDIAN = 62,
  SPELL_SET_FIRE_GUARDIAN = 63,
  SPELL_SET_WATER_GUARDIAN = 64,
  SPELL_MEDUSA_PETRIFY = 101,
  SPELL_ARCHMAGI_DISPEL = 102,
  SPELL_NONE = 4294967295,
};

enum SPELL_ATTRIBUTES
{
  ATTR_COMMON_SPELL = 0x1,
  ATTR_COMBAT_SPELL = 0x2,
  ATTR_ADVENTURE_SPELL = 0x4,
  ATTR_DURATIONED_SPELL = 0x8,
};

enum CREATURE_EVENT_CODE
{
  CREATURE_MOVED_CODE = 0,
  CREATURE_TOOK_TURN_EVENT_CODE = 1,
  CREATURE_TOOK_DAMAGE_CODE = 2,
};

enum SPELL_CATEGORY
{
  SPELL_CATEGORY_COMBAT = 0,
  SPELL_CATEGORY_ADVENTURE = 1,
  SPELL_CATEGORY_ALL = 2,
};

enum BUILDING_CODE : __int8
{
  BUILDING_MAGE_GUILD = 0x0,
  BUILDING_THIEVES_GUILD = 0x1,
  BUILDING_TAVERN = 0x2,
  BUILDING_DOCK = 0x3,
  BUILDING_WELL = 0x4,
  BUILDING_TENT = 0x5,
  BUILDING_CASTLE = 0x6,
  BUILDING_STATUE = 0x7,
  BUILDING_LEFT_TURRET = 0x8,
  BUILDING_RIGHT_TURRET = 0x9,
  BUILDING_MARKET = 0xA,
  BUILDING_SPECIAL_GROWTH = 0xB,
  BUILDING_MOAT = 0xC,
  BUILDING_SPECIAL = 0xD,
  BUILDING_BOAT = 0xE,
  BUILDING_CAPTAIN = 0xF,
  BUILDING_EXT_0 = 0x10,
  BUILDING_EXT_1 = 0x11,
  BUILDING_EXT_2 = 0x12,
  BUILDING_DWELLING_1 = 0x13,
  BUILDING_DWELLING_2 = 0x14,
  BUILDING_DWELLING_3 = 0x15,
  BUILDING_DWELLING_4 = 0x16,
  BUILDING_DWELLING_5 = 0x17,
  BUILDING_DWELLING_6 = 0x18,
  BUILDING_UPGRADE_1 = 0x19,
  BUILDING_UPGRADE_2 = 0x1A,
  BUILDING_UPGRADE_3 = 0x1B,
  BUILDING_UPGRADE_4 = 0x1C,
  BUILDING_UPGRADE_5 = 0x1D,
  BUILDING_UPGRADE_5B = 0x1E,
  BUILDING_EXT_3 = 0x1F,
};

enum BUILDINGS_BUILT
{
  BUILDING_MAGE_GUILD_BUILT = 0x1,
  BUILDING_THIEVES_GUILD_BUILT = 0x2,
  BUILDING_TAVERN_BUILT = 0x4,
  BUILDING_DOCK_BUILT = 0x8,
  BUILDING_WELL_BUILT = 0x10,
  BUILDING_TENT_BUILT = 0x20,
  BUILDING_CASTLE_BUILT = 0x40,
  BUILDING_STATUE_BUILT = 0x80,
  BUILDING_LEFT_TURRET_BUILT = 0x100,
  BUILDING_RIGHT_TURRET_BUILT = 0x200,
  BUILDING_MARKET_BUILT = 0x400,
  BUILDING_SPECIAL_GROWTH_BUILT = 0x800,
  BUILDING_MOAT_BUILT = 0x1000,
  BUILDING_SPECIAL_BUILT = 0x2000,
  BUILDING_BOAT_BUILT = 0x4000,
  BUILDING_CAPTAIN_BUILT = 0x8000,
  BUILDING_EXT_0_BUILT = 0x10000,
  BUILDING_EXT_1_BUILT = 0x20000,
  BUILDING_EXT_2_BUILT = 0x40000,
  BUILDING_DWELLING_1_BUILT = 0x80000,
  BUILDING_DWELLING_2_BUILT = 0x100000,
  BUILDING_DWELLING_3_BUILT = 0x200000,
  BUILDING_DWELLING_4_BUILT = 0x400000,
  BUILDING_DWELLING_5_BUILT = 0x800000,
  BUILDING_DWELLING_6_BUILT = 0x1000000,
  BUILDING_UPGRADE_1_BUILT = 0x2000000,
  BUILDING_UPGRADE_2_BUILT = 0x4000000,
  BUILDING_UPGRADE_3_BUILT = 0x8000000,
  BUILDING_UPGRADE_4_BUILT = 0x10000000,
  BUILDING_UPGRADE_5_BUILT = 0x20000000,
  BUILDING_UPGRADE_5B_BUILT = 0x40000000,
  BUILDING_EXT_3_BUILT = 0x80000000,  
};

enum PRIMARY_SKILL
{
  PRIMARY_SKILL_ATTACK = 0,
  PRIMARY_SKILL_DEFENSE = 1,
  PRIMARY_SKILL_SPELLPOWER = 2,
  PRIMARY_SKILL_KNOWLEDGE = 3,
};

enum RESOURCES
{
  RESOURCE_WOOD = 0x0,
  RESOURCE_MERCURY = 0x1,
  RESOURCE_ORE = 0x2,
  RESOURCE_SULFUR = 0x3,
  RESOURCE_CRYSTAL = 0x4,
  RESOURCE_GEMS = 0x5,
  RESOURCE_GOLD = 0x6,
};

enum FACTION
{
  FACTION_KNIGHT = 0x0,
  FACTION_BARBARIAN = 0x1,
  FACTION_SORCERESS = 0x2,
  FACTION_WARLOCK = 0x3,
  FACTION_WIZARD = 0x4,
  FACTION_NECROMANCER = 0x5,
  FACTION_MULTIPLE = 0x6,
  FACTION_RANDOM = 0x7,
};

struct building_cost
{
  int wood;
  int mercury;
  int ore;
  int sulfur;
  int crystal;
  int gems;
  int gold;
};

struct SSpellInfo
{
  char soundName[9];
  char level;
  char spriteIdx;
  char creatureEffectAnimationIdx;
  __int16 appearingChance;
  char cost;
  char nonMagicFactionAppearanceChance[6];
  unsigned __int8 attributes;
};

struct tag_monsterInfo // size 26
{
  __int16 cost; // 0
  int fight_value; // 2
  char fight_value_aux; // 6
  char growth; // 7
  __int16 hp; // 8
  char faction; // 10
  char speed; // 11
  char attack; //12
  char defense; // 13
  char min_damage; // 14
  char max_damage; // 15
  char shots; // 16
  char short_name[5]; // 17
  __int16 creature_flags; // 22
  __int16 _; // 24
};

struct resourceVtable
{
  //int (__thiscall *scalarDeletingDestructor)(resource *this, char);
  int scalarDeletingDestructor;
};

struct resource // size 16
{
  resourceVtable *vtable; // 0
  RESOURCE_TYPE resourceType; // 4
  __int16 referenceCount; // 6
  unsigned int fileID; // 8
  resource *next; // 12
};

struct IconEntry // size 13
{
  __int16 offsetX; // 0
  __int16 offsetY; // 2
  __int16 width; // 4
  __int16 height; // 6
  char someSortOfLength; // 8
  int off; // 9
};

struct icon // size 31
{
  resourceVtable *vtable; // 0
  RESOURCE_TYPE resourceType; // 4
  __int16 referenceCount; // 6
  int fileID; // 8
  resource *next; // 12
  __int16 numSprites; // 16
  IconEntry *headersAndImageData; // 18
};

struct sample // size 48
{
  resourceVtable *vtable; // 0
  __int16 resourceType; // 4
  __int16 referenceCount; // 6
  int fileID; // 8
  resource *next; // 12
  int field_10; // 16
  void *contents; // 20
  int nbytes; // 24
  int codeThing; //28
  unsigned int playbackRate; // 32
  unsigned int sampleType; // 36
  unsigned int volume; // 40
  int loopCount; // 44
};

struct SMonFrameInfo // size 821
{
  char firstByteIgnored; // 0
  __int16 offsetForBlind[2]; // 1
  char startMoveAnimInfoIgnored[16]; // 5
  char subStartMoveAnimInfoIgnored[16]; // 21
  char mainMoveAnimInfoIgnored[16]; // 37
  char subEndMoveAnimInfoIgnored[16]; // 53
  char endMoveAnimInfoIgnored[16]; // 69
  char fullMoveAnimInfoIgnored[16]; // 85
  char moveAnimInfoIgnored[16]; // 101
  char numberOfFidgets; // 117
  float fidgetProbabilities[5]; // 118
  int fidgetInfoIgnored[5]; // 138
  int maxFidgetDelay; // 158
  int stepTime; // 162
  int shootingTime; // 166
  int flightSpeed; // 170
  __int16 projectileStartOffset[3][2]; // 174
  char numMissileDirs; // 186
  float projDirAngle[12]; // 187
  int stackNumDispXShift[2]; // 235
  char animationLengths[34]; // 243
  char animationFrameToImgIdx[34][16]; // 277
};

struct army // 1154
{
  char mightBeIsAttacking; // 0
  char animatingRangedAttack; // 1
  char mightBeAttackAnimIdx; // 2
  char field_3; // 3
  char field_4; // 4
  char field_5; // 5
  int field_6; // 6
  H2RECT stackSizeDispBounds; // 10
  H2RECT field_1A; // 26
  H2RECT bounds; // 42
  H2RECT effectAnimationBounds; // 58
  int curFidget; // 74
  float field_4E; // 78
  int targetOwner; // 82
  int targetStackIdx; // 86
  int targetNeighborIdx; // 90
  int field_5E; // 94
  int targetHex; // 98
  int probablyIsNeedDrawSpellEffect; // 102
  int mirroredIdx; // 106
  int mirrorIdx; // 110
  int lifespan; // 114
  int creatureIdx; // 118
  int occupiedHex; // 122
  int animationType; // 126
  int animationFrame; // 130
  int facingRight; // 134
  int field_8A; // 138
  int field_8E; // 142
  int initialQuantity; // 146
  int quantity; // 150
  unsigned int previousQuantity; // 154
  int temporaryQty; // 158
  int damage; // 162
  int armyIdx; // 166
  int otherBadLuckThing; // 170
  int speed; // 174
  int field_B2; // 178
  int luckStatus; // 182
  tag_monsterInfo creature; // 186
  __int16 field_D4; // 212
  int damageTakenDuringSomeTimePeriod; // 214
  int hasTakenLosses; // 218
  int dead; // 222
  int spellEnemyCreatureAbilityIsCasting; // 226
  int owningSide; // 230
  int stackIdx; // 234
  int baseFidgetTime; // 238
  int morale; // 242
  int luck; // 246
  int field_FA; // 250
  int yDrawOffset; // 254
  int xDrawOffset; // 258
  int numActiveEffects; // 262
  char effectStrengths[19]; // 266
  int field_11D; // 285
  int hitByHydraAttack; // 289
  void *field_125; // 293
  SMonFrameInfo frameInfo; // 297
  icon *creatureIcon; // 1118
  icon *missileIcon; // 1122
  sample *combatSounds[7]; // 1126
};

struct managerVtable
{
  //int (__thiscall *Open)(baseManager *, int);
  //void (__thiscall *Close)(baseManager *);
  //int (__fastcall *Main)(baseManager *, tag_message *);
  int *Open;
  void *Close;
  int *Main;
};

struct baseManager
{
  managerVtable *vtable;
  baseManager *next;
  baseManager *prev;
  int type;
  int idx;
  char name[30];
  int ready;
};

struct palette // size 17
{
  resourceVtable *vtable; // 0
  __int16 resourceType; // 4
  __int16 referenceCount; // 6
  int fileID; // 8
  int next; // 12
  signed __int8 *contents; // 16
};

struct hexcell // size 98
{
  __int16 centerX; // 0
  __int16 occupyingCreatureBottomY; // 2
  __int16 leftX; // 4
  __int16 topY; // 6
  __int16 rightX; // 8
  __int16 otherY1; // 10
  __int16 otherY2; // 12
  char isBlocked; // 14
  char combatObjIdx; // 15
  char unitOwner; // 16
  signed __int8 stackIdx; // 17
  char occupiersOtherHexIsToLeft; // 18
  int numCorpses; // 19
  char corpseOwners[14]; // 23
  char corpseStackIndices[14]; // 37
  char corpseOtherHexIsToLeft[14]; //51
  char field_41; // 65
  H2RECT drawingBounds; // 66
  char field_52[16]; // 82
};

struct bitmap
{
  resourceVtable *vtable;
  RESOURCE_TYPE resourceType;
  __int16 referenceCount;
  int fileID;
  int next;
  __int16 setInConstructor;
  __int16 width;
  __int16 height;
  signed __int8 *contents;
};

struct armyGroup // size 15
{
  char creatureTypes[5]; // 0
  __int16 quantities[5]; // 5
};

struct town // size 100
{
  char idx; // 0
  char ownerIdx; // 1
  char alignment; // 2
  char factionID; // 3
  char x; // 4
  char y; // 5
  char buildDockRelated; // 6
  char field_7; // 7
  armyGroup garrison; // 8
  char visitingHeroIdx; // 23
  unsigned int buildingsBuiltFlags; // 24
  char mageGuildLevel; // 28
  char field_1D; // 29
  __int16 numCreaturesInDwelling[12]; // 30
  char exists; // 54
  char mayNotBeUpgradedToCastle; // 55
  char field_38; // 56
  char playerPos; // 57
  __int16 extraIdx;// 58
  char mageGuildSpells[5][4]; // 60
  char numSpellsOfLevel[5]; // 80
  __int16 field_55; // 85
  char name[12]; // 87
  char field_63; // 99
};

struct hero // size 250
{
  __int16 spellpoints; // 0
  char idx; // 2
  char ownerIdx; // 3
  char field_4; // 4
  char field_5; // 5
  char field_6; // 6
  char field_7; // 7
  char field_8; // 8
  char field_9; // 9
  char name[13]; // 10
  char factionID; // 23
  char heroID; // 24
  int x; // 25
  int y; // 29
  __int16 field_21; // 33
  __int16 field_23; // 35
  __int16 field_25; // 37
  __int16 field_27; // 39
  __int8 relatedToX; // 41
  __int8 relatedToY; // 42
  __int8 relatedToFactionID; // 43
  __int8 directionFacing; // 44
  __int16 occupiedObjType; // 45
  __int16 occupiedObjVal; // 47
  int mobility; // 49
  int remainingMobility; // 53
  int experience; // 57
  __int16 oldLevel; // 61
  char primarySkills[4]; // 63
  char field_43;// 67
  char tempMoraleBonuses; // 68
  char tempLuckBonuses; // 69
  char field_46; // 70
  int gazeboesVisited; // 71
  int fortsVisited; // 75
  int witchDoctorHutsVisited; // 79
  int mercenaryCampsVisited; // 83
  int standingStonesVisited; // 87
  int treesOfKnowledgeVisited; // 91
  int xanadusVisited; // 95
  char randomSeed; // 99
  char wisdomLastOffered; // 100
  armyGroup army; // 101
  char secondarySkillLevel[14]; // 116
  char skillIndex[14]; // 130
  int numSecSkillsKnown; // 144
  char spellsLearned[65]; // 148
  char artifacts[14]; // 213
  int flags; // 227
  char isCaptain; // 231
  int field_E8; // 232
  char scrollSpell[14]; // 236
};

struct heroSW // size 236
{
  __int16 spellpoints; // 0
  char idx; // 2
  char ownerIdx; // 3
  char field_4; // 4
  char field_5; // 5
  char field_6; // 6
  char field_7; // 7
  char field_8; // 8
  char field_9; // 9
  char name[13]; // 10
  char factionID; // 23
  char heroID; // 24
  int x; // 25
  int y; // 29
  __int16 field_21; // 33
  __int16 field_23; // 35
  __int16 field_25; // 37
  __int16 field_27; // 39
  __int8 relatedToX; // 41
  __int8 relatedToY; // 42
  __int8 relatedToFactionID; // 43
  __int8 directionFacing; // 44
  __int16 occupiedObjType; // 45
  __int16 occupiedObjVal; // 47
  int mobility; // 49
  int remainingMobility; // 53
  int experience; // 57
  __int16 oldLevel; // 61
  char primarySkills[4]; // 63
  char field_43;// 67
  char tempMoraleBonuses; // 68
  char tempLuckBonuses; // 69
  char field_46; // 70
  int gazeboesVisited; // 71
  int fortsVisited; // 75
  int witchDoctorHutsVisited; // 79
  int mercenaryCampsVisited; // 83
  int standingStonesVisited; // 87
  int treesOfKnowledgeVisited; // 91
  int xanadusVisited; // 95
  char randomSeed; // 99
  char wisdomLastOffered; // 100
  armyGroup army; // 101
  char secondarySkillLevel[14]; // 116
  char skillIndex[14]; // 130
  int numSecSkillsKnown; // 144
  char spellsLearned[65]; // 148
  char artifacts[14]; // 213
  int flags; // 227
  char isCaptain; // 231
  int field_E8; // 232
};

struct widgetVtable
{
  //void (__thiscall *paint)(widget *);
  //void (__thiscall *cleanUp)(widget *, int);
  //int (__thiscall *handleEvent)(widget *, tag_message *x);
  void *paint;
  void *cleanUp;
  int *handleEvent;
};

struct widget // size 32
{
  widgetVtable *vtable; // 0
  heroWindow *parentWindow; // 4
  widget *nextInLinkedList; // 8
  widget *prevInLinkedList; // 12
  __int16 fieldID; // 16
  __int16 componentIndex; // 18
  __int16 field_14; // 20
  __int16 flags; // 22
  __int16 offsetX; // 24
  __int16 offsetY; // 26
  __int16 width; // 28
  __int16 height; // 30
};

struct heroWindow // size 68
{
  int idx; // 0
  heroWindow *nextWindow; // 4
  heroWindow *prevWindow; // 8
  char filename[20]; // 12
  int flags1; // 32
  int flags2; // 36
  int xOffset; // 40
  int yOffset; // 44
  int width; // 48
  int height; // 52
  widget *lastWidget; // 56
  widget *firstWidget; // 60
  bitmap *bitmap; // 64
};

struct combatManager
{
  managerVtable *vtable; // 0
  baseManager *next; // 4
  baseManager *prev; // 8
  int type; // 12
  int idx; // 16
  char name[30]; // 20
  int ready; // 50
  palette *palette; // 54
  char _1[768]; // 58
  char combatMessageRow1[120]; // 826
  char combatMessageRow2[120]; // 946
  char field_42A[117]; // 1066
  char field_49F[117]; // 1183
  hexcell combatGrid[117]; // 1300
  int terrainType; // 12766
  int combatFieldFringeID; // 12770
  int field_31E6; // 12774
  int field_31EA; // 12778
  int field_31EE; // 12782
  int combatFieldCoverID; // 12786
  icon *combatScreenIcons[15]; // 12790
  icon *combatObjIcons[8]; // 12850
  int numCombatObjs; // 12882
  __int16 eagleEyeSpellLearned[2]; // 12886
  int drawBridgePosition; // 12890
  int hasMoat; //12894
  char turretStatus[4]; // 12898
  char wallStatus[4]; // 12902
  char ballistaDestroyed; // 12906
  bitmap *couldBeBitmapForFieldItself; // 12907
  bitmap *probablyBitmapForCombatScreen; // 12911
  bitmap *bitmap1; // 12915
  int zeroedAfterAnimatingDeathAndHolySpells; // 12919
  int field_327B; // 12923
  town *castles[2]; // 12927
  hero *heroes[2]; // 12935
  hero captain; // 12943
  int heroSpellpowers[2]; // 13193
  armyGroup *armies[2]; // 13201
  int shadedHex; // 13209
  char shouldDoHeroFidget1[2]; // 13213
  char shouldDoHeroFidget2[2]; // 13215
  char field_33A1[2]; // 13217
  char field_33A3[2]; // 13219
  int heroAnimationType[2]; // 13221
  int heroAnimationFrameCount[2]; // 13229
  int heroType[2]; // 13237
  int lastHeroAnimationCompleteTime[2]; // 13245
  icon *heroIcon[2]; // 13253
  icon *heroFlagIcon[2]; // 13261
  int heroFlagIconIdx[2]; // 13269
  H2RECT heroBounds[2]; // 13277
  H2RECT heroFlagBounds[2]; // 13309
  H2RECT moatPartBounds[9]; // 13341
  int otherCombatMessageRelatedTime; // 13485
  int combatMessageRelatedTime; // 13489
  int couldBeShouldResetCombatMessage; // 13493
  char _7[100]; // 13497
  char summonedCreatureType[2]; // 13597
  int field_351F[2]; // 13599
  int involvedInBadMorale[2]; // 13607
  int playerID[2]; // 13615
  int experienceForDefeating[2]; // 13623
  int field_353F; // 13631
  int field_3543; // 13635
  int numCreatures[2]; // 13639
  army creatures[2][21]; // 13647
  int activeStackOwner; //
  int activeStack;
  int field_F2AB;
  int currentActionSide;
  int field_F2B3;
  int field_F2B7;
  int field_F2BB;
  int field_F2BF;
  int field_F2C3;
  int field_F2C7;
  int field_F2CB;
  int field_F2CF;
  H2RECT catapultBounds;
  H2RECT ballistaBounds;
  H2RECT drawbridgeBounds;
  H2RECT field_F303;
  int probablyCatapultImgIdx[2];
  char _11[8];
  int timesCatapultMustFire[2];
  int timesGarrisonMustFire[2];
  int isCastleBattle;
  char _12[20];
  int zeroedInHandleCatapult1;
  int zeroedInHandleCatapult2;
  float field_F353;
  int field_F357;
  int field_F35B;
  float ghostAndVampireAbilityStrength[2];
  heroWindow *window;
  int field_F36B;
  int field_F36F;
  int field_F373;
  int field_F377[2];
  signed int limitCreature[2][20];
  int field_F41F[2];
  int field_F427[2];
  int field_F42F;
  int casualtyRelatedTextWidgets[50];
  int field_F4FB;
  int field_F4FF;
  char field_F503[24];
  int field_F51B;
  int field_F51F;
  H2RECT field_F523;
  char _15[16];
  int field_F543;
  int field_F547;
  int field_F54B[2];
  int field_F553;
  int field_F557;
  char _16[28];
  char shouldVanish[2][20];
  char anyStacksShouldVanish;
  char combatBackgroundFilename[13];
  char hexNeighbors[117][6];
  heroWindow *combatEndWindow;
  int current_spell_id;
  int winningSide;
};

struct combatManagerSW
{
  managerVtable *vtable; // 0
  baseManager *next; // 4
  baseManager *prev; // 8
  int type; // 12
  int idx; // 16
  char name[30]; // 20
  int ready; // 50
  palette *palette; // 54
  char _1[768]; // 58
  char combatMessageRow1[120]; // 826
  char combatMessageRow2[120]; // 946
  char field_42A[117]; // 1066
  char field_49F[117]; // 1183
  hexcell combatGrid[117]; // 1300
  int terrainType; // 12766
  int combatFieldFringeID; // 12770
  int field_31E6; // 12774
  int field_31EA; // 12778
  int field_31EE; // 12782
  int combatFieldCoverID; // 12786
  icon *combatScreenIcons[15]; // 12790
  icon *combatObjIcons[8]; // 12850
  int numCombatObjs; // 12882
  __int16 eagleEyeSpellLearned[2]; // 12886
  int drawBridgePosition; // 12890
  int hasMoat; //12894
  char turretStatus[4]; // 12898
  char wallStatus[4]; // 12902
  char ballistaDestroyed; // 12906
  bitmap *couldBeBitmapForFieldItself; // 12907
  bitmap *probablyBitmapForCombatScreen; // 12911
  bitmap *bitmap1; // 12915
  int zeroedAfterAnimatingDeathAndHolySpells; // 12919
  int field_327B; // 12923
  town *castles[2]; // 12927
  heroSW *heroes[2]; // 12935
  heroSW captain; // 12943
  int heroSpellpowers[2]; // 13193
  armyGroup *armies[2]; // 13201
  int shadedHex; // 13209
  char shouldDoHeroFidget1[2]; // 13213
  char shouldDoHeroFidget2[2]; // 13215
  char field_33A1[2]; // 13217
  char field_33A3[2]; // 13219
  int heroAnimationType[2]; // 13221
  int heroAnimationFrameCount[2]; // 13229
  int heroType[2]; // 13237
  int lastHeroAnimationCompleteTime[2]; // 13245
  icon *heroIcon[2]; // 13253
  icon *heroFlagIcon[2]; // 13261
  int heroFlagIconIdx[2]; // 13269
  H2RECT heroBounds[2]; // 13277
  H2RECT heroFlagBounds[2]; // 13309
  H2RECT moatPartBounds[9]; // 13341
  int otherCombatMessageRelatedTime; // 13485
  int combatMessageRelatedTime; // 13489
  int couldBeShouldResetCombatMessage; // 13493
  char _7[100]; // 13497
  char summonedCreatureType[2]; // 13597
  int field_351F[2]; // 13599
  int involvedInBadMorale[2]; // 13607
  int playerID[2]; // 13615
  int experienceForDefeating[2]; // 13623
  int field_353F; // 13631
  int field_3543; // 13635
  int numCreatures[2]; // 13639
  army creatures[2][21]; // 13647
  int activeStackOwner; //
  int activeStack;
  int field_F2AB;
  int currentActionSide;
  int field_F2B3;
  int field_F2B7;
  int field_F2BB;
  int field_F2BF;
  int field_F2C3;
  int field_F2C7;
  int field_F2CB;
  int field_F2CF;
  H2RECT catapultBounds;
  H2RECT ballistaBounds;
  H2RECT drawbridgeBounds;
  H2RECT field_F303;
  int probablyCatapultImgIdx[2];
  char _11[8];
  int timesCatapultMustFire[2];
  int timesGarrisonMustFire[2];
  int isCastleBattle;
  char _12[20];
  int zeroedInHandleCatapult1;
  int zeroedInHandleCatapult2;
  float field_F353;
  int field_F357;
  int field_F35B;
  float ghostAndVampireAbilityStrength[2];
  heroWindow *window;
  int field_F36B;
  int field_F36F;
  int field_F373;
  int field_F377[2];
  signed int limitCreature[2][20];
  int field_F41F[2];
  int field_F427[2];
  int field_F42F;
  int casualtyRelatedTextWidgets[50];
  int field_F4FB;
  int field_F4FF;
  char field_F503[24];
  int field_F51B;
  int field_F51F;
  H2RECT field_F523;
  char _15[16];
  int field_F543;
  int field_F547;
  int field_F54B[2];
  int field_F553;
  int field_F557;
  char _16[28];
  char shouldVanish[2][20];
  char anyStacksShouldVanish;
  char combatBackgroundFilename[13];
  char hexNeighbors[117][6];
  heroWindow *combatEndWindow;
  int current_spell_id;
  int winningSide;
};

struct fullMap // size 20
{
  void *tiles; // 0
  void *cellExtras; // 4
  int width; // 8
  int height; // 12
  int numCellExtras; // 16
};

struct SMapHeader // size 420
{
  int field_0; // 0
  __int16 field_4; // 4
  char width; // 6
  char height; // 7
  char hasPlayer[6]; // 8
  char playerMayBeHuman[6]; // 14
  char playerMayBeComp[6]; // 20
  char numPlayers; // 26
  char minHumans; // 27
  char maxHumans; // 28
  char winConditionType; // 29
  char relatedToWinConditionType; // 30
  char allowDefeatAllVictory; // 31
  __int16 winConditionArgumentOrLocX; // 32
  char lossConditionType; // 34
  char lossConditionArgumentOrLocX; // 35
  char field_24; // 36
  char noStartingHeroInCastle; // 37
  char playerFactions[6]; // 38
  __int16 winConditionArgumentOrLocY; // 44
  __int16 lossConditionArgumentOrLocY; // 46
  __int16 relatedToPlayerColorOrSide; // 48
  int field_32; // 50
  char field_36; // 54
  char field_37; // 55
  char nextTownName; // 56
  char field_39; // 57
  char name[60]; // 58
  char description[298]; // 118
  char field_1A0; // 416
  char field_1A1; // 417
  char numRumors; // 418
  char numEvents; // 419
};

struct playerData // size 283
{
  char color; // 0
  char numHeroes; // 1
  char curHeroIdx; // 2
  char relatedToSomeSortOfHeroCountOrIdx; // 3
  char heroesOwned[8]; // 4
  char heroesForPurchase[2]; // 12
  char relatedToMaxOrNumHeroes; // 14
  int personality; // 15
  char _3[45]; // 19
  char field_40; // 64
  char field_41; // 65
  char field_42; // 66
  char daysLeftWithoutCastle; // 67
  char numCastles; // 68
  __int8 mightBeCurCastleIdx; // 69
  char relatedToUnknown; // 70
  char castlesOwned[72]; // 71
  int resources[7]; // 143
  char hasEvilFaction; // 171
  char barrierTentsVisited; // 172
  char _4_2[58]; // 173
  int field_E7[7]; // 231
  char _5[12]; // 259
  float field_10F; // 271
  int field_113; // 275
  __int16 field_117; // 279
  char field_119; // 281
  char field_11A; // 282
};

struct mine // size 7
{
  char field_0; // 0
  char owner; // 1
  char type; // 2
  char guardianType; // 3
  char guardianQty; // 4
  char x; // 5
  char y; // 6
};

struct boat // size 8
{
  char idx; // 0
  char x; // 1
  char y; // 2
  char field_3; // 3
  char underlyingObjType; // 4
  char underlyingObjExtra; // 5
  char field_6; // 6
  char owner; // 7
};

struct game // size 26001
{
  __int16 gameDifficulty; // 0
  char relatedToCurViewSideOrCampaign; // 2
  char field_3; // 3
  char relatedToCampaignMap; // 4
  char _1[120]; // 5
  char field_7D; // 125
  char hasDwarfAlliance; // 126
  char maybeIsGoodCampaign; // 127
  char field_80; // 128
  char field_81; // 129
  char field_82; // 130
  char field_83; // 131
  char field_84; // 132
  char field_85; // 133
  char isDwarfbane; // 134
  char hasDragonAlliance; // 135
  char field_88; // 136
  char _11[193]; // 137
  char lastSaveFile[251]; // 330
  char _12[100]; // 581
  SMapHeader mapHeader; // 681
  char relatedToPlayerPosAndColor[6]; // 1101
  char playerHandicap[6]; // 1107
  char relatedToColorOfPlayerOrFaction[6]; // 1113
  char somePlayerCodeOr10IfMayBeHuman[6]; // 1119
  char difficulty; // 1125
  char mapFilename[40]; // 1126
  char numPlayers; // 1166
  char couldBeNumDefeatedPlayers; // 1167
  char playerDead[6]; // 1168
  __int16 day; // 1174
  __int16 week; // 1176
  __int16 month; // 1178
  playerData players[6]; // 1180
  fullMap map; // 2878
  char numObelisks; // 2898
  town castles[72]; // 2899
  char field_2773[72]; // 10099
  char field_27BB[9]; // 10171
  hero heroes[54]; // 10180
  char relatedToHeroForHireStatus[54]; // 23554
  mine mines[144]; // 23608
  char field_60A6[144]; // 24616
  char artifactGeneratedRandomly[103]; // 24760
  boat boats[48]; // 24863
  char boatBuilt[48]; // 25247
  char obeliskVisitedMasks[48]; // 25295
  char field_637D[24]; // 25343
  char ultimateArtifactLocX; // 25367 
  char ultimateArtifactLocY; // 25368
  char ultimateArtifactIdx; // 25369
  int field_6398; // 25370
  char _B[14]; // 25374
  char currentRumor[301]; // 25388
  __int16 numRumors; // 25689
  __int16 rumorIndices[30]; // 25691
  __int16 numEvents; // 25751
  char eventIndices[60]; // 25753
  char _C[40]; // 25813
  __int16 numMapEvents; // 25853
  __int16 mapEventIndices[70]; // 25855
  //int (__thiscall *callback)(tag_message *);
  int tag_message; // 25995
  char field_660D; // 25999
  char field_660E; // 26000
};

struct gameSW // size 25245
{
  __int16 gameDifficulty; // 0
  char relatedToCurViewSideOrCampaign; // 2
  char field_3; // 3
  char relatedToCampaignMap; // 4
  char _1[120]; // 5
  char field_7D; // 125
  char hasDwarfAlliance; // 126
  char maybeIsGoodCampaign; // 127
  char field_80; // 128
  char field_81; // 129
  char field_82; // 130
  char field_83; // 131
  char field_84; // 132
  char field_85; // 133
  char isDwarfbane; // 134
  char hasDragonAlliance; // 135
  char field_88; // 136
  char _11[193]; // 137
  char lastSaveFile[251]; // 330
  char _12[100]; // 581
  SMapHeader mapHeader; // 681
  char relatedToPlayerPosAndColor[6]; // 1101
  char playerHandicap[6]; // 1107
  char relatedToColorOfPlayerOrFaction[6]; // 1113
  char somePlayerCodeOr10IfMayBeHuman[6]; // 1119
  char difficulty; // 1125
  char mapFilename[40]; // 1126
  char numPlayers; // 1166
  char couldBeNumDefeatedPlayers; // 1167
  char playerDead[6]; // 1168
  __int16 day; // 1174
  __int16 week; // 1176
  __int16 month; // 1178
  playerData players[6]; // 1180
  fullMap map; // 2878
  char numObelisks; // 2898
  town castles[72]; // 2899
  char field_2773[72]; // 10099
  char field_27BB[9]; // 10171
  heroSW heroes[54]; // 10180
  char relatedToHeroForHireStatus[54]; // 22798
  mine mines[144]; // 22852
  char field_60A6[144]; // 23860
  char artifactGeneratedRandomly[103]; // 24004
  boat boats[48]; // 24107
  char boatBuilt[48]; // 24491
  char obeliskVisitedMasks[48]; // 24539
  char field_637D[24]; // 24587
  char ultimateArtifactLocX; // 24611
  char ultimateArtifactLocY; // 24612
  char ultimateArtifactIdx; // 24613
  int field_6398; // 24614
  char _B[14]; // 24618
  char currentRumor[301]; // 24632
  __int16 numRumors; // 24933
  __int16 rumorIndices[30]; // 24935
  __int16 numEvents; // 24995
  char eventIndices[60]; // 24997
  char _C[40]; // 25057
  __int16 numMapEvents; // 25097
  __int16 mapEventIndices[70]; // 25099
  //int (__thiscall *callback)(tag_message *);
  int tag_message; // 25239
  char field_660D; // 25243
  char field_660E; // 25244
};

struct border
{
  widgetVtable *vtable;
  heroWindow *parentWindow;
  widget *nextInLinkedList;
  int prevInLinkedList;
  __int16 fieldID;
  __int16 field_12;
  __int16 backgroundType;
  __int16 flagsRelatedToShouldDisplayAndPerhapsMouseCode;
  __int16 offsetX;
  __int16 offsetY;
  __int16 width;
  __int16 height;
  bitmap *bitmap;
  icon *icon;
  __int16 color;
};

struct BuildingDisplay
{
  int animationLength;
  int animationIdx;
  int built;
  int buildingCode;
  icon *icon;
  border *guiElement;
};

struct bankBox
{
  playerData *player;
  __int16 x;
  __int16 y;
  heroWindow *window;
};

struct strip
{
  heroWindow *window;
  char _1[24];
  int x;
  int y;
  int field_24;
  int drawBorder;
  void *field_2C[6];
  icon *stripIcon;
  icon *creaturePortraits[5];
  int creatureTypes[5];
  icon *portraitIcon;
  icon *portraitFlagIcon;
  int portraitIconIdx;
  int field_7C;
  armyGroup *army;
};

struct townManager
{
  managerVtable *vtable;
  baseManager *next;
  baseManager *prev;
  int type;
  int idx;
  char name[30];
  int ready;
  town *castle;
  icon *couldBeBackground;
  BuildingDisplay *buildingDisplays[32];
  int curBuilding;
  int factionID;
  int field_C6;
  heroWindow *townScreen;
  strip *garrisonDisplay;
  strip *visitingArmyDisplay;
  strip *field_D6;
  int field_DA;
  strip *field_DE;
  int field_E2;
  strip *field_E6;
  int field_EA;
  bankBox *bankbox;
  char infoMessage[80];
  int field_142;
  int field_146;
  int field_14A;
  int field_14E;
  int field_152;
  int field_156;
  int field_15A;
  int field_15E;
  heroWindow *curScreen;
  heroWindow *dialog;
  int field_16A;
  int field_16E;
  int recruitHeroConfirmed;
  hero *heroBeingRecruited;
};

