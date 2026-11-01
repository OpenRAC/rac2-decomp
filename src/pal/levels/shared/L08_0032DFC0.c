#include "include_asm.h"

#include "common.h"
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_002AB1F0(void *);
extern void func_002A75E0(void *, int, int, int, int);
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
    p->direction[0] = func_00283180(angle) * p->radius;
    p->direction[1] = func_00283198(angle) * p->radius;
    p->direction[2] = p->height;
    p->direction[3] = 1.0f;
    {
        float heading = func_00283B98(angle, 3.141593f);
        short lifetime = 250;
        active = 1;
        p->age = 0;
        p->delay = 0;
        p->heading = heading;
        p->lifetime = lifetime;
        p->active = active;
    }
    effect = func_002AB1F0(m);
    if (effect && *(float *)effect == 0.0f) {
        p->flags |= 0x20;
        *(int *)(m + 0x98) = 0;
    }
    if (p->flags & 2)
        func_002A75E0(m, animation, frames, flags, active);
    else
        func_PAL_002A7E68(m, animation, frames, flags);
}

