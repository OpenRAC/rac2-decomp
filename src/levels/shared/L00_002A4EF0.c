#include "include_asm.h"
#include "names.h"

/* Select one of three measured pointer slots for the requested kind. */
extern void *D_0018C0B0;

extern void *D_0018B134;

extern void *D_0018B040;

typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;

/* Player state fields used when adjusting health. */
typedef struct {
    u8 pad00[0x22B4];
    u8 mode;
    u8 pad01[0x24CC - 0x22B5];
    s32 health;
} PlayerHealthState;
extern PlayerHealthState D_00189E20;
/* The scaling index is a signed halfword at player-stats offset 0x18. */
extern s32 D_001A7A00[] __attribute__((sda));
/* Five damage multipliers copied into a local lookup table. */
typedef struct {
    f32 scale[5];
} PlayerDamageScale;
extern PlayerDamageScale D_L00_001A7F30;

extern f32 func_00283CE0(int value);
extern int func_00283CF0(f32 value);
extern void func_L00_0030C7F8(int argument);

/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long func_L00_002A4EF0(unsigned long value)
{
  return value;
}

/* Subtract scaled damage, clamp health to zero, and notify the registered handler. */
void func_L00_002A4EF8(int amount)
{
    u8 mode;
    int level;
    int damage;
    PlayerDamageScale scale;

    if (amount == 0)
        return;
    damage = amount;
    mode = gHeroState.mode;
    if (mode == 0 && amount > 0) {
        level = *(s16 *)((u8 *)D_001A7A00 + 0x18);
        level = level < 5 ? level : 4;
        level = level > -1 ? level : 0;
        scale = D_L00_001A7F30;
        damage = FloatToInt(IntToFloat(amount) * scale.scale[level] + 0.5f);
        damage = damage > mode ? damage : 1;
    }
    gHeroState.health -= damage;
    if (gHeroState.health < 0)
        gHeroState.health = 0;
    CallLoadedModuleHandlerWithArg_0034B000(360);
}

/* select primary pointer forkind0/2/3/4/5, secondary for1,tertiary for6; otherwiseNULL */
void *func_L00_002A4FE8(int kind)
{
    if (kind == 0 || kind == 2 || kind == 3 || kind == 4 || kind == 5)
        return gHeroMoby_0018C0B0;
    if (kind == 1)
        return D_0018B134;
    if (kind == 6)
        return D_0018B040;
    return 0;
}

