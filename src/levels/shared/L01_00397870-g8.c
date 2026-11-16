#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x60 - 0x1C];
    f32 f60;
    f32 f64;
    f32 f68;
} State_397870;

typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Class_397870;

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    u8 b20;
    u8 pad2[0x24 - 0x21];
    Class_397870 *cls;
    u8 pad3[0x2C - 0x28];
    f32 f2C;
    u8 pad4[0x68 - 0x30];
    State_397870 *st;
    u8 pad5[0xF0 - 0x6C];
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
} Obj_397870;

extern void part_spawn_sparkle_trail_above_ground(Obj_397870 *a0);
extern float g_collectible_height_scale __attribute__((sda));
extern float g_bob_base_height __attribute__((sda));
extern float g_bob_l01_amplitude __attribute__((sda));
extern float g_bolt_bob_spin_speed __attribute__((sda));
extern int g_sparkle_chance __attribute__((sda));
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int math_random_int_below(int);
extern void part_draw_bolt_glow_rings(Obj_397870 *);

/* Keeps a moby bobbing up and down and turning toward its target angles while it is in its running state. */
void bobbing_l01_moby_update(Obj_397870 *moby)
{
    State_397870 *vars = moby->st;
    float bob_sine;

    moby->f2C = moby->cls->f24 * g_collectible_height_scale;

    if (moby->b20 == 1) {
        bob_sine = math_fast_sin_or_cos_b(moby->fFC);
        moby->f18 = vars->f18 + g_bob_base_height + g_bob_l01_amplitude * bob_sine;
        moby->fF0 = FastAddRotations(moby->fF0, vars->f68);
        moby->fF4 = FastAddRotations(moby->fF4, vars->f64);
        moby->fF8 = FastAddRotations(moby->fF8, vars->f60);
        moby->fFC = FastAddRotations(moby->fFC, 0.0002908882452175021f * g_bolt_bob_spin_speed);
    }

    part_draw_bolt_glow_rings(moby);
    if (math_random_int_below(g_sparkle_chance) == 0)
        part_spawn_sparkle_trail_above_ground(moby);
}
