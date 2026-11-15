#include "include_asm.h"
#include "names.h"

typedef int Quad_3f9368 __attribute__((mode(TI)));
typedef union { Quad_3f9368 q; float f[4]; } Vec_3f9368;
extern void moby_set_state(void *, int, int);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern void part_spawn_object_following_effect(void *, void *, int, int, int, float, float, int, int, int);

void func_PAL_L00_003FD928(char *self)
{
    Vec_3f9368 v1;
    Vec_3f9368 v2;
    char *p;
    float f20;
    float f21;
    float f22;
    float f;

    if (*(unsigned char *)(self + 0x20) == 0) {
        *(int *)(self + 0x78) = 0x150000FF;
        moby_set_state(self, 1, -1);
    }
    if (*(unsigned char *)(self + 0x20) != 1) {
        return;
    }
    p = *(char **)(self + 0x24);
    f20 = *(float *)(self + 0x2C) / *(float *)(p + 0x24);
    f22 = 243600.0f;
    f21 = 0.1f;
    f = FastAddRotations(*(float *)(self + 0xF4), 0.062831864f);
    *(float *)(self + 0xF4) = f;

    v1.q = 0;
    v1.f[1] = 0.5378739833831787f;
    v1.f[2] = -0.3785569965839386f;
    FastVecScale(&v1, &v1, f20);
    part_spawn_object_following_effect(&v1, self, 0x150000FF, -1, 1, f22, f21, 2, 1, -1);

    v2.q = 0;
    v2.f[1] = 0.5123069882392883f;
    v2.f[2] = 0.37711501121520996f;
    FastVecScale(&v2, &v2, f20);
    part_spawn_object_following_effect(&v2, self, 0x150000FF, -1, 1, f22, f21, 2, 1, -1);
}
