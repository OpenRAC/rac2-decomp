#include "names.h"
/* Related hero layout and control flow adapted from OpenRAC/rac1-decomp
 * src/overlays/shared/hero_idle_and_animation.c (GPL-3.0). */

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x300];
    float f300;
    float f304;
    float f308;
    float f30C;
    float f310;
    float f314;
    unsigned char pad318[0x30];
    short f348;
    unsigned char pad34a[0x152];
    unsigned char f49C;
    unsigned char pad49d[0xdd3];
    int f1270;
    unsigned char pad1274[0x1bc];
    float f1430;
    float f1434;
    int f1438;
    short f143C;
    unsigned short f143E;
    unsigned char pad1440[0xe50];
    unsigned char *f2290;
    int f2294;
    unsigned char pad2298[0x4];
    int f229C;
} PointEffectHero;
extern PointEffectHero g_hero_state;
typedef struct {
    unsigned char pad0[0x320];
    float f320;
    float f324;
    unsigned char pad328[0x44];
    float f36C;
    unsigned char pad370[0x60];
    float f3D0;
    float f3D4;
    unsigned char pad3d8[0x44];
    float f41C;
    unsigned char pad420[0x60];
    float f480;
    unsigned char pad484[0xac];
    float f530;
} PointEffectJoints;
extern PointEffectJoints g_hero_item_attach_records;
extern int hero_is_in_special_kind_or_mode(void);
extern float math_fabs(float);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_set_level_clock_and_bytes(short, unsigned char, unsigned char, unsigned char, float, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern float math_random_float_range(float, float);
extern void part_spawn_spark_effect(void *, void *, float);

/* Drive articulated offsets and emit the active pair of joint effects. */
/* Swings the hero arms and body parts as the hero moves, and makes small effects at the hands when needed. */
void UpdateHeroEasingTargetsAndPointEffects(void)
{
    Quadword position;
    unsigned char *matrix;
    float left, right, draw;
    int index;

    if (g_hero_state.f1270) {
        g_hero_item_attach_records.f36C = 0.01f;
        g_hero_item_attach_records.f41C = 0.01f;
    }
    if (hero_is_in_special_kind_or_mode())
        return;
    if ((math_fabs(g_hero_state.f300) > 0.015f ||
         math_fabs(g_hero_state.f304) > 0.015f ||
         math_fabs(g_hero_state.f308) > 0.01745329424738884f ||
         math_fabs(g_hero_state.f30C) > 0.01745329424738884f ||
         math_fabs(g_hero_state.f310) > 0.01745329424738884f ||
         math_fabs(g_hero_state.f314) > 0.01745329424738884f) &&
        g_hero_state.f348 != 1) {
        g_hero_item_attach_records.f324 = -g_hero_state.f308;
        g_hero_item_attach_records.f3D4 = -g_hero_state.f30C;
        left = mat_fast_helper_a(0.2f, g_hero_state.f300) * 1.2f;
        right = -mat_fast_helper_a(0.2f, g_hero_state.f304) * 1.2f;
        if (left > 0.785398244857788f)
            left = 0.785398244857788f;
        if (left < -0.174532949924469f)
            left = -0.174532949924469f;
        if (right > 0.174532949924469f)
            right = 0.174532949924469f;
        if (right < -0.785398244857788f)
            right = -0.785398244857788f;
        g_hero_item_attach_records.f480 = left;
        g_hero_item_attach_records.f530 = right;
        g_hero_item_attach_records.f320 = -fast_subtract_rotations(g_hero_state.f310, -left);
        g_hero_item_attach_records.f3D0 = -fast_subtract_rotations(g_hero_state.f314, -right);
    }
    if (!(g_hero_state.f143E & 0x80)) {
        if (g_hero_state.f2294 == 3)
            hero_set_level_clock_and_bytes(1, 2, 1, 0, 0.021f, 0.002f);
        if (g_hero_state.f229C == 4 && g_hero_state.f49C && g_hero_state.f49C < 12)
            hero_set_level_clock_and_bytes(1, 2, 0, 1, 0.016f, 0.002f);
        if (g_hero_state.f1438 > 0 && g_hero_state.f143C) {
            matrix = 0;
            if (g_hero_state.f143E & 1)
                matrix = g_hero_state.f2290 + 0xC0;
            --g_hero_state.f1438;
            moby_transform_joint_to_world((char *)g_hero_state.f2290, 22, (char *)&position);
            for (index = 0; index < g_hero_state.f143C; ++index) {
                draw = math_random_float_range(-g_hero_state.f1434, g_hero_state.f1434);
                part_spawn_spark_effect(&position, matrix, g_hero_state.f1430 + draw);
            }
            moby_transform_joint_to_world((char *)g_hero_state.f2290, 23, (char *)&position);
            for (index = 0; index < g_hero_state.f143C; ++index) {
                draw = math_random_float_range(-g_hero_state.f1434, g_hero_state.f1434);
                part_spawn_spark_effect(&position, matrix, g_hero_state.f1430 + draw);
            }
        }
    } else {
        g_hero_state.f1438 = 0;
    }
}
