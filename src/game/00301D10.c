#include "include_asm.h"
#include "names.h"

typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef float f32;

extern s32 g_player_bolts;
extern s32 g_current_map_index __attribute__((sda));
extern s32 D_001A8C70;
extern u32 D_001B1B60 __attribute__((sda));
extern s32 D_0018D208[];

extern void level_forward_value(s32);
extern void vec_random_direction(f32 *, f32, f32);
extern void FastVecScale(f32 *, f32 *, f32);
extern void FastVecAdd(void *, void *, void *);
extern s32 math_random_int_below(s32);
extern f32 math_random_float_range(f32, f32);
extern void *part_spawn_ground_effect(void *, u32, u32, u32, s32, s32, s32, f32, f32, f32);

/* Adds the score of the kill class a0 + 0xAA (1, 5, 20, 50, 100, 500 or 1000 for classes
   0xD..0x13, 1 for any other) to the running total, and to the player's row of the table when
   the owner's flag is set or a counted owner is below the limit pointer, then plays the sound
   and throws two bursts of sparks from the object. */
/* Adds the value of a collected bolt to the bolt total, plays a sound and sprays sparks. */
void CollectBolts(u8 *obj) {
    f32 sparkDir[4];
    f32 sparkPos[4];
    s32 score;
    s32 sign;
    f32 sparkSpeed;

    switch ((short)(*(unsigned short *)(obj + 0xAA) - 0xD)) {
    default:
    case 0:
        score = 1;
        break;
    case 1:
        score = 5;
        break;
    case 2:
        score = 0x14;
        break;
    case 3:
        score = 0x32;
        break;
    case 4:
        score = 0x64;
        break;
    case 5:
        score = 0x1F4;
        break;
    case 6:
        score = 0x3E8;
        break;
    }
    g_player_bolts = g_player_bolts + score;
    if (*(u8 *)(*(u8 **)(obj + 0x68) + 0x40) != 0 || (D_001A8C70 != 0 && (u32)obj < D_001B1B60))
        D_0018D208[g_current_map_index] += score;
    level_forward_value(0xB4);
    vec_random_direction(sparkDir, 0.011666666716337204f, 0.016666668f);
    FastVecScale(sparkPos, sparkDir, 10.0f);
    FastVecAdd(sparkPos, sparkPos, obj + 0x10);
    sign = math_random_int_below(2);
    if (sign == 0)
        sign = sign - 1;
    sparkSpeed = math_random_float_range(0.4f, 0.5f);
    part_spawn_ground_effect(sparkPos, 0x19, 0x7F207F7F, 0, sign, (s32)sparkDir, 0, sparkSpeed * 0.2f, sparkSpeed, 0.0f);
    part_spawn_ground_effect(sparkPos, 0x19, 0x7F7F7F7F, 1, -sign, (s32)sparkDir, 0, sparkSpeed * 0.14f, sparkSpeed * 0.7f, 0.0f);
}
