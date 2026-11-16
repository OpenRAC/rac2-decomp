#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;
typedef struct {
    u8 pad00[0x22B4];
    u8 mode;
    u8 pad01[0x24CC - 0x22B5];
    s32 health;
} PlayerHealthState;
extern PlayerHealthState g_hero_state;
extern s32 g_player_stats[] __attribute__((sda));
typedef struct {
    f32 scale[5];
} PlayerDamageScale;
extern PlayerDamageScale g_player_damage_scale;
extern f32 IntToFloat(int value);
extern int FloatToInt(f32 value);
extern void module_l00_call_handler_with_arg_4_pal(int argument);

/* Subtract scaled damage, clamp health to zero, and notify the registered handler. */
void AdjustPlayerHealth_pal(int amount)
{
    u8 mode;
    int level;
    int damage;
    PlayerDamageScale scale;

    if (amount == 0)
        return;
    damage = amount;
    mode = g_hero_state.mode;
    if (mode == 0 && amount > 0) {
        level = *(s16 *)((u8 *)g_player_stats + 0x18);
        level = level < 5 ? level : 4;
        level = level > -1 ? level : 0;
        scale = g_player_damage_scale;
        damage = FloatToInt(IntToFloat(amount) * scale.scale[level] + 0.5f);
        damage = damage > mode ? damage : 1;
    }
    g_hero_state.health -= damage;
    if (g_hero_state.health < 0)
        g_hero_state.health = 0;
    module_l00_call_handler_with_arg_4_pal(300);
}

