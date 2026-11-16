#include "include_asm.h"
#include "names.h"

typedef int Quad_3f9368 __attribute__((mode(TI)));
typedef union { Quad_3f9368 q; float f[4]; } Vec_3f9368;
extern void moby_set_state(void *, int, int);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern void *part_spawn_object_following_effect(void *, void *, int, int, int, float, float, int, int, int);

/* Per frame for the twin trail effect: starts it, then spawns two following particle trails at fixed offsets on the object, scaled by its progress (PAL: same as v1.01). */
void twin_trail_effect_update_pal(char *self)
{
    Vec_3f9368 offset_a;
    Vec_3f9368 offset_b;
    char *vars;
    float scale;
    float fade_step;
    float lifetime_scale;
    float angle;

    if (*(unsigned char *)(self + 0x20) == 0) {
        *(int *)(self + 0x78) = 0x150000FF;
        moby_set_state(self, 1, -1);
    }
    if (*(unsigned char *)(self + 0x20) != 1) {
        return;
    }
    vars = *(char **)(self + 0x24);
    scale = *(float *)(self + 0x2C) / *(float *)(vars + 0x24);
    lifetime_scale = 243600.0f;
    fade_step = 0.1f;
    angle = FastAddRotations(*(float *)(self + 0xF4), 0.062831864f);
    *(float *)(self + 0xF4) = angle;

    offset_a.q = 0;
    offset_a.f[1] = 0.5378739833831787f;
    offset_a.f[2] = -0.3785569965839386f;
    FastVecScale(&offset_a, &offset_a, scale);
    part_spawn_object_following_effect(&offset_a, self, 0x150000FF, -1, 1, lifetime_scale, fade_step, 2, 1, -1);

    offset_b.q = 0;
    offset_b.f[1] = 0.5123069882392883f;
    offset_b.f[2] = 0.37711501121520996f;
    FastVecScale(&offset_b, &offset_b, scale);
    part_spawn_object_following_effect(&offset_b, self, 0x150000FF, -1, 1, lifetime_scale, fade_step, 2, 1, -1);
}
