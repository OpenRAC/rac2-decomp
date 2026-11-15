#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;
typedef union { TI128 q; float f[4]; } EffectVector;
struct CollisionFilter { Quad16 direction; int owner, mode; u16 unknown18, objectType; float radius; int active; };
extern char *D_L11_001C0D18 NOT_SDA;
extern int D_L11_001B1CE4 __attribute__((sda));
extern u32 D_L11_001B1CE0 __attribute__((sda));
extern int coll_sweep_from_object(void *, float, float *, int, float, float, int, int, int);
extern void moby_set_state(u8 *, u8, int);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(char *, int, int, float, Quad16 *);
extern int CollLine(void *, void *, int, void *, struct CollisionFilter *);
extern int coll_test_point(void *, int, void *, float);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_gravity_fade(void *, void *, int, u32, int, int, int, float, float, float, int);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, void *, float, float);
extern void moby_mark_spawned(void *);
extern void part_draw_shot_glow_sprites(u8 *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);

/* Per-frame update of a moving shot (moby class 3545): flies it forward, explodes it on a hit or after
   240 frames, adds glow effects, and draws it. */
void shot_l11_update(u8 *object) {
    EffectVector destination;
    struct CollisionFilter filter;
    EffectVector backward, light;
    char *vars = *(char **)(object + 0x68);
    float size, growth, size2, growth2;
    *(int *)(vars + 0x24) += 1;
    if (*(int *)(vars + 0x24) > 240) {
        coll_sweep_from_object(object, 0.6f, (float *)(object + 0x10), 0x10001, *(float *)(vars + 0x14), 0.0f, 0, 1, 0);
        moby_set_state(object, 1, -1);
    }
    switch (object[0x20]) {
    case 0:
        FastVecAdd(&destination, object + 0x10, vars);
        make_hit_descriptor((char *)&filter, (int)object, 1, *(float *)(vars + 0x14), (Quad16 *)vars);
        filter.objectType = *(u16 *)(object + 0xAA);
        if (CollLine(object + 0x10, &destination, 0, object, &filter) || coll_test_point(object + 0x10, 0, object, 0.3f)) {
            if (!D_L11_001C0D18 || D_L11_001C0D18 != *(char **)(vars + 0x10)) {
                coll_sweep_from_object(object, 0.6f, (float *)(object + 0x10), 0x10001, *(float *)(vars + 0x14), 0.0f, 0, 1, 0);
                moby_set_state(object, 1, -1);
                return;
            }
        }
        qcopy(object + 0x10, &destination);
        FastVecScale(&backward, vars, -0.5f);
        if (D_L11_001B1CE4) {
            vec_scale_to_length(&light, vars, 0.5f);
            FastVecAdd(&light, object + 0x10, &light);
            size = math_random_float_range(1.2f, 1.45f) * 210000.0f;
            growth = math_random_float_range(0.1f, 0.2f);
            part_spawn_gravity_fade(&light, &backward, 2, D_L11_001B1CE0, 3, 127, 47, size, growth * 210000.0f, 0.0f, 0);
            vec_scale_to_length(&light, vars, -0.03f);
            FastVecAdd(&light, object + 0x10, &light);
            size2 = math_random_float_range(0.7f, 0.9f) * 210000.0f;
            growth2 = math_random_float_range(0.1f, 0.3f);
            part_spawn_gravity_fade(&light, &backward, 2, D_L11_001B1CE0, 7, 127, 47, size2, growth2 * 210000.0f, 0.0f, 0);
        }
        break;
    case 1:
        SpawnExplosion(object + 0x10, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0.25f, 20.0f);
        moby_mark_spawned(object);
        return;
    }
    gfx_add_draw_callback_third((void (*)(void *))part_draw_shot_glow_sprites, object);
}
