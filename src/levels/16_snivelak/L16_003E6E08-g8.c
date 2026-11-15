#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern float D_L16_001B0C78 __attribute__((sda));
extern int D_L16_001B0CA8 __attribute__((sda));
extern int D_L16_001B0CAC __attribute__((sda));
extern char *D_L16_001BFF58[];
extern char D_L16_001A8F20[] __attribute__((sda));
extern void coll_sweep_from_object(float, float, float, void *, void *, int, int, int, int);
extern void moby_set_state(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern void *part_spawn_ground_effect(void *, int, int, int, int, void *, float, float, float, int);
extern void moby_mark_spawned(void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void gfx_draw_two_layered_sprites(void *);

/* Updates the moving object, handles impact/timeout, and emits its death particles. */
/* Moves a flying shot and removes it with a burst when it hits something or times out. */
void UpdateImpactProjectile(char *object)
{
    float position[4];
    char collision[48];
    float velocity[4];
    float direction[4];
    char *state = *(char **)(object + 104);
    float size;
    if (++*(int *)(state + 36) > 240) {
        coll_sweep_from_object(0.6f, *(float *)(state + 20), 0.0f, object, object + 16, 0x10001, 0, 1, 0);
        moby_set_state(object, 1, -1);
    }
    switch (*(unsigned char *)(object + 32)) {
    case 0:
        FastVecAdd(position, object + 16, state);
        make_hit_descriptor(collision, object, 1, state, *(float *)(state + 20));
        *(unsigned short *)(collision + 26) = *(unsigned short *)(object + 170);
        if ((CollLine(object + 16, position, 0, object, collision) ||
             coll_test_point(object + 16, 0, object, 0.3f)) &&
             (D_L16_001BFF58[0] == 0 || D_L16_001BFF58[0] != *(char **)(state + 16))) {
            coll_sweep_from_object(0.6f, *(float *)(state + 20), 0.0f, object, object + 16, 0x10001, 0, 1, 0);
            moby_set_state(object, 1, -1);
            return;
        }
        *(Quadword *)(object + 16) = *(Quadword *)position;
        FastVecScale(velocity, state, -0.5f);
        vec_clear_128(direction);
        break;
    case 1:
        size = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(object + 16, 15, D_L16_001B0CA8, 0, 10, D_L16_001A8F20, size * 0.3f, size, 0.0f, 0);
        part_spawn_ground_effect(object + 16, 15, D_L16_001B0CAC, 1, -10, D_L16_001A8F20, size * 0.04f, size * 0.4f, 0.0f, 0);
        moby_mark_spawned(object);
        return;
    }
    math_apply_axis_rotation_to_quat(object + 224, object + 224, object + 208, D_L16_001B0C78 * 0.017453294f);
    math_apply_axis_rotation_to_quat(object + 192, object + 192, object + 208, D_L16_001B0C78 * 0.017453294f);
    gfx_add_draw_callback_third(gfx_draw_two_layered_sprites, object);
}
