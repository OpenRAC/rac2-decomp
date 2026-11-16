#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern char *moby_get_private_value_0(void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
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

/* Sets up a launched object: places it on a circle around its owner, starts its timer and plays the launch animation. */
void moby_init_launched_object_pal(unsigned char *moby, struct LaunchState *launch, int animation, int flags, int frames, float angle)
{
    int effect;
    int active;
    launch->direction[0] = math_fast_sin_or_cos_a(angle) * launch->radius;
    launch->direction[1] = math_fast_sin_or_cos_b(angle) * launch->radius;
    launch->direction[2] = launch->height;
    launch->direction[3] = 1.0f;
    {
        float heading = FastAddRotations(angle, 3.141593f);
        short lifetime = 250;
        active = 1;
        launch->age = 0;
        launch->delay = 0;
        launch->heading = heading;
        launch->lifetime = lifetime;
        launch->active = active;
    }
    effect = moby_get_private_value_0(moby);
    if (effect && *(float *)effect == 0.0f) {
        launch->flags |= 0x20;
        *(int *)(moby + 0x98) = 0;
    }
    if (launch->flags & 2)
        anim_start_blended_with_flags(moby, animation, frames, flags, active);
    else
        anim_start_blended_pal(moby, animation, frames, flags);
}

