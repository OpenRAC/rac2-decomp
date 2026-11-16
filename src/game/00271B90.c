#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    Vec pos; float z_vel; char pad14[12];
    Vec up, target, prev_target; float velocity[4];
    Vec prev_pos, delta, side, projection;
    float distance, side_distance, up_distance, yaw[5];
} Follow;
extern Follow g_camera_follow_state;
typedef struct {char prefix[0x80]; Vec pos, rot; char padA0[0x21f4]; int state; char pad2298[0x208]; int mode;} Hero;
extern char g_hero_state[], g_hero_state_block[];
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
/* Tracks the hero position and up direction smoothly so the camera can follow. */
void cam_update_follow_hero(void)
{
    Vec dir, projection;
    Follow *follow = &g_camera_follow_state;
    char *hero = g_hero_state_block;
    float d;
    int i;
    vec_scale_to_length(&dir, hero, -1.0f);
    follow->prev_target.q = follow->target.q;
    follow->target.q = dir.q;
    if (FastVecDot(&follow->up, &dir) < -0.98f) {
        dir.f[0] += 0.2f;
        dir.f[1] += 0.2f;
        dir.f[2] += 0.2f;
    }
    follow->up.f[0] = math_step_spring_damper_clamped(&follow->velocity[0], follow->up.f[0], dir.f[0], 0.015f, 0.2f, 0.0f);
    follow->up.f[1] = math_step_spring_damper_clamped(&follow->velocity[1], follow->up.f[1], dir.f[1], 0.015f, 0.2f, 0.0f);
    follow->up.f[2] = math_step_spring_damper_clamped(&follow->velocity[2], follow->up.f[2], dir.f[2], 0.015f, 0.2f, 0.0f);
    vec_scale_to_length(&follow->up, &follow->up, 1.0f);
    FastVecSub(&follow->delta, hero - 0x240, &follow->prev_pos);
    follow->distance = FastVecLength(&follow->delta);
    d = FastVecDot(&follow->delta, &dir);
    follow->up_distance = d;
    vec_scale_to_length(&projection, &dir, d);
    follow->projection.q = projection.q;
    FastVecSub(&follow->side, &follow->delta, &projection);
    follow->side_distance = FastVecLength(&follow->side);
    d = 1.0f / follow->side_distance;
    FastVecScale(&follow->side, &follow->side, d);
    follow->prev_pos.q = *(Quad *)(hero - 0x240);
    { Hero *heroState = (Hero *)(hero - 0x2c0);
    if (heroState->mode != 0x50 || heroState->state == 0x11) {
        follow->pos.f[0] = heroState->pos.f[0];
        follow->pos.f[1] = heroState->pos.f[1];
        follow->pos.f[2] = math_step_spring_damper_clamped(&follow->z_vel, follow->pos.f[2], heroState->pos.f[2], 0.0075f, 0.175f, 0.0f);
        follow->pos.f[3] = heroState->pos.f[2];
    } else {
        follow->pos.f[0] = heroState->pos.f[0];
        follow->pos.f[1] = heroState->pos.f[1];
    }
    }
    for (i = 0; i < 4; i++) follow->yaw[i] = follow->yaw[i + 1];
    follow->yaw[i] = ((Hero *)g_hero_state)->rot.f[2];
}
