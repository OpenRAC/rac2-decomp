#include "include_asm.h"

#include "common.h"
extern f32 D_L16_001B1C40_gp[] SDATA(D_L16_001B1C40);
extern f32 D_L16_001B1C50_gp[] SDATA(D_L16_001B1C50);
extern f32 g_curved_projectile_weight_limit __attribute__((sda));
extern char g_scene_origin_transform[];
extern float math_step_value_toward_target(char *, char *, f32, f32, f32, f32);
extern void FastVecSub(char *, char *, char *);
extern void FastVecScale(char *, char *, f32);
extern void FastVecAdd(char *, char *, char *);
extern void emit_snivelak_falling_particles_pal(char *);
extern void *part_find_owned_effect_slot(char *, u32, s32);
extern char *SpawnExplosion_pal(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void moby_mark_spawned(char *);
extern s32 coll_test_point(char *, s32, char *, f32);
extern void moby_set_state(char *, s32, s32);
extern void vec_scale_to_length(char *, char *, f32);
extern char *part_spawn_blast_effect_moby_pal(char *, char *, char *, f32);
extern s32 coll_sweep_from_object(char *, char *, f32, u32, s32, s32, s32, f32, f32);

/* Blends three motion segments and finishes with the object's destruction effect. */
void snivelak_curved_projectile_update_pal(char *self) {
    char delta[16] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    char *current;
    char *next;
    f32 *weight, *rate;
    f32 *step_weight;
    s32 i;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        qcopy(self + 16, vars);
        i = 0;
        current = vars;
        next = vars + 16;
        weight = (f32 *)(vars + 0x40);
        rate = (f32 *)(vars + 0x50);
        step_weight = weight;
        for (; i < 3; current += 16, weight++, next += 16, rate++, step_weight++, i++) {
            if (i == 0 || weight[-1] > g_curved_projectile_weight_limit)
                math_step_value_toward_target((char *)step_weight, (char *)rate, 1.0f,
                              D_L16_001B1C40_gp[i] * 0.00040000002f,
                              D_L16_001B1C40_gp[i] * 0.00040000002f,
                              D_L16_001B1C50_gp[i] * 0.020000001f);
            FastVecSub(delta, next, current);
            FastVecScale(delta, delta, *weight);
            FastVecAdd(self + 16, self + 16, delta);
        }
        emit_snivelak_falling_particles_pal(self);
        if (part_find_owned_effect_slot(self, 0x10000, 0)) {
            SpawnExplosion_pal(self + 16, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 1.0f, 20.0f);
            moby_mark_spawned(self);
        } else if (*(f32 *)(vars + 0x48) >= 1.0f || (*(f32 *)(vars + 0x44) >= 0.5f && coll_test_point(self + 16, 0, self, 0.5f)))
            moby_set_state(self, 1, -1);
        break;
    case 1:
    {
        char *end_position = self + 16;
        FastVecSub(delta, g_scene_origin_transform, end_position);
        vec_scale_to_length(delta, delta, 1.0f);
        part_spawn_blast_effect_moby_pal(self, end_position, delta, 0.0f);
        /* radius 2.0f is the first FP argument: each register bank keeps its order */
        coll_sweep_from_object(self, end_position, 2.0f, 0x10001, 0, 1, 0, 5.0f, 1.0f);
        moby_mark_spawned(self);
        break;
    }
    }
}
