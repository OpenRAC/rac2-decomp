#include "common.h"

extern void curve_build_jittered_points_alt(void *, int, void *, float);
extern void gfx_l18_draw_lightning_ribbon(void *, int, int, int, int, float, float);
extern void vec_add_random_offset(void *, float);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void moby_transform_joint_to_world(void *, int, void *);
/* EE register-bank argument order is unchanged by the FP interleaving. */
extern void gfx_draw_aimed_effect_packet(void *, int, float, int, float, int, int);

/* The two records at state + 0x610/+0x6B0 share this layout. The updater
* at 0x434128 reads angles, angular steps and radii at +0x40/+0x60/+0x80;
* its initializer at 0x433460 writes both vectors of the last two fields. */
typedef struct {
    float endpoints[2][4];
    float tangents[2][4];
    float angles[2][4];
    float angularSteps[2][4];
    float radii[2][4];
} L18ArcControl;

/* Draws the crackling lightning on both sides of the Extermibot beam, with extra branches when the beam is strong, plus glows at both ends. */
void DrawPairedBranchingRibbonEffects(u8 *obj) {
    L18ArcControl control __attribute__((aligned(16)));
    float branch[6][4] __attribute__((aligned(16)));
    u8 *state  =  *(u8 **)(obj + 0x68);
    float width  =  0.02f;
    int active  =  (u16)(*(u16 *)(state + 0x806) - 2) < 3;
    int strong  =  (u16)(*(u16 *)(state + 0x806) - 2) < 2;
    int count;
    float (*path)[4];
    int life;
    float size, speed, scale, half;
    if (active) width  =  0.08f;
    count  =  active ? 12 : 8;
    path  =  __builtin_alloca(count * 16);
    life  =  strong ? math_random_int_range(48, 128) : math_random_int_range(48, 80);
    size  =  strong ? math_random_float_range(0.02f, 0.12f) : math_random_float_range(0.02f, 0.07f);
    speed  =  strong ? math_random_float_range(2.0f, 6.0f) : math_random_float_range(2.0f, 3.0f);
    curve_build_jittered_points_alt(path, count, state + 0x610, width);
    gfx_l18_draw_lightning_ribbon(path, count, life, 0x60FFFFFF, 0x30FF0000, size, speed);
    if ((unsigned)(*(u16 *)(state + 0x806) - 2) < 2) {
        qcopy(control.endpoints[0], path[math_random_int_range(count - 6, count - 3)]);
        qcopy(control.endpoints[1], path[count - 2]);
        vec_add_random_offset(control.endpoints[1], 1.0f);
        vec_random_direction(control.tangents[0], 1.0f, 2.0f);
        vec_random_direction(control.tangents[1], 1.0f, 2.0f);
        life = math_random_int_range(48, 96);
        size = math_random_float_range(0.02f, 0.08f);
        speed = math_random_float_range(2.0f, 3.0f);
        curve_build_jittered_points_alt(branch, 6, &control, 0.05f);
        gfx_l18_draw_lightning_ribbon(branch, 6, life, 0x60FF3030, 0x30FF0000, size, speed);
    }
    life  =  strong ? math_random_int_range(48, 128) : math_random_int_range(48, 80);
    size  =  strong ? math_random_float_range(0.02f, 0.12f) : math_random_float_range(0.02f, 0.07f);
    speed  =  strong ? math_random_float_range(2.0f, 6.0f) : math_random_float_range(2.0f, 3.0f);
    curve_build_jittered_points_alt(path, count, state + 0x6B0, width);
    gfx_l18_draw_lightning_ribbon(path, count, life, 0x60FFFFFF, 0x30FF0000, size, speed);
    if ((unsigned)(*(u16 *)(state + 0x806) - 2) < 2) {
        qcopy(control.endpoints[0], path[math_random_int_range(count - 6, count - 3)]);
        qcopy(control.endpoints[1], path[count - 2]);
        vec_add_random_offset(control.endpoints[1], 1.0f);
        vec_random_direction(control.tangents[0], 1.0f, 2.0f);
        vec_random_direction(control.tangents[1], 1.0f, 2.0f);
        life = math_random_int_range(48, 96);
        size = math_random_float_range(0.02f, 0.08f);
        speed = math_random_float_range(2.0f, 3.0f);
        curve_build_jittered_points_alt(branch, 6, &control, 0.05f);
        gfx_l18_draw_lightning_ribbon(branch, 6, life, 0x60FF3030, 0x30FF0000, size, speed);
    }
    scale  =  *(float *)(state + 0x7E0) * 2.0f + 1.0f;
    moby_transform_joint_to_world(*(void **)(state + 0x7C8), 0, control.endpoints[0]);
    moby_transform_joint_to_world(*(void **)(state + 0x7C8), 1, control.endpoints[1]);
    half = scale * 0.5f;
    {
        int glowLife = math_random_int_range(80, 96);
        float angle = math_random_angle();
        gfx_draw_aimed_effect_packet(control.endpoints[0], 0x807070, half, glowLife, angle, 49, 2);
    }
    scale = scale * 0.7f;
    {
        int glowLife = math_random_int_range(8, 22);
        float angle = math_random_angle();
        gfx_draw_aimed_effect_packet(control.endpoints[0], 0x802020, scale, glowLife, angle, 11, 2);
    }
    {
        int glowLife = math_random_int_range(80, 96);
        float angle = math_random_angle();
        gfx_draw_aimed_effect_packet(control.endpoints[1], 0x807070, half, glowLife, angle, 49, 2);
    }
    {
        int glowLife = math_random_int_range(8, 22);
        float angle = math_random_angle();
        gfx_draw_aimed_effect_packet(control.endpoints[1], 0x802020, scale, glowLife, angle, 11, 2);
    }
}
