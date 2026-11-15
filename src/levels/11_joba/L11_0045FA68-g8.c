#include "common.h"

extern float FastAddRotations(float, float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(void *, int, char *, float);
extern void moby_set_state(char *, int, int);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern void part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern void coll_sweep_from_object(void *, void *, float, int, float, float, int, int, int);
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_mark_spawned(char *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void part_spawn_two_glow_effects(void);
extern float D_L11_001B22C8 __attribute__((sda));
extern int D_L11_001B22C0 __attribute__((sda));
extern char *D_L11_001C0D18 NOT_SDA;
extern int D_0018C0B4 NOT_SDA;

/* Updates a thrown projectile moby: it flies forward leaving a particle trail, then explodes on hitting something, running out of range, or when the level changes. Moby class 3707. */
void thrown_l11_projectile_update_2(char *moby)
{
    float next[4], velocity[4], zero[4];
    char *vars = *(char **)(moby + 0x68);
    char *target;
    float spread_a, spread_b;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), *(float *)(vars + 0x20) * 0.7f);
        *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(vars + 0x20) * 0.5f);
        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(vars + 0x20));
        FastVecAdd(next, moby + 0x10, vars);
        if (coll_test_point(next, 0, moby, D_L11_001B22C8) &&
            D_L11_001C0D18 && D_L11_001C0D18 != *(char **)(vars + 0x10)) {
            moby_set_state(moby, 1, -1);
            return;
        }
        qcopy(moby + 0x10, next);
        FastVecScale(velocity, vars, -0.5f);
        vec_clear_128(zero);
        spread_a = math_random_float_range(2.5f, 3.0f) * 210000.0f;
        spread_b = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        part_spawn_gravity_fade(moby + 0x10, velocity, 15, D_L11_001B22C0, 3, 80, 0, spread_a, spread_b, 0.0f, 0);
        if (*(float *)(vars + 0x24) < *(float *)(moby + 0x18) && *(float *)(vars + 0x24) > 0.0f)
            moby_set_state(moby, 2, -1);
        target = part_find_owned_effect_slot(moby, 0x10000, 0);
        if (target) {
            *(float *)(vars + 0x14) -= *(float *)(target + 0x2C);
            if (*(float *)(vars + 0x14) <= 0.0f) moby_set_state(moby, 1, -1);
        }
        if (D_0018C0B4 == 111) moby_set_state(moby, 2, -1);
        break;
    case 1:
        coll_sweep_from_object(moby, moby + 0x10, 3.0f, 0x10001, *(float *)(vars + 0x18), 1.0f, 0, 1, 0);
        SpawnExplosion(moby + 0x10, 1, 2, 2, 5, 10, 2, 1, 3.0f, 0.0f, 0, 1, 0, 0);
        moby_mark_spawned(moby);
        return;
    case 2:
        SpawnExplosion(moby + 0x10, 0, 10, 2, 10, 5, 2, 1, 2.0f, 0.0f, 0, 1, 0, 0);
        moby_mark_spawned(moby);
        return;
    }
    gfx_add_draw_callback_third(part_spawn_two_glow_effects, moby);
}
