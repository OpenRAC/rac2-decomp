#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int moby_get_private_value_0(void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
struct LaunchState {
    float direction[4];
    char gap10[8];
    float radius, height;
    char gap20[4];
    unsigned int flags;
    char gap28[4];
    short lifetime;
    char gap2e[14];
    unsigned char active;
    char gap3d;
    short delay;
    float heading;
    int age;
};

void func_PAL_L08_0032DFC0(unsigned char *m, struct LaunchState *p, int animation, int flags, int frames, float angle)
{
    int effect;
    int active;
    p->direction[0] = math_fast_sin_or_cos_a(angle) * p->radius;
    p->direction[1] = math_fast_sin_or_cos_b(angle) * p->radius;
    p->direction[2] = p->height;
    p->direction[3] = 1.0f;
    {
        float heading = FastAddRotations(angle, 3.141593f);
        short lifetime = 250;
        active = 1;
        p->age = 0;
        p->delay = 0;
        p->heading = heading;
        p->lifetime = lifetime;
        p->active = active;
    }
    effect = moby_get_private_value_0(m);
    if (effect && *(float *)effect == 0.0f) {
        p->flags |= 0x20;
        *(int *)(m + 0x98) = 0;
    }
    if (p->flags & 2)
        anim_start_blended_with_flags(m, animation, frames, flags, active);
    else
        func_PAL_002A7E68(m, animation, frames, flags);
}

