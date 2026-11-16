#include "include_asm.h"

#include "common.h"
extern char *CreateMoby(int);
struct EffectState98 {
    short timer, duration, delay, pad6;
    float scale2, scale4, fade, scale;
    int visible, pad1c, a2, a3, a4, a5, a6, pad34, pad38, a7;
};
struct Camera98 {
    char pad0[0x140];
    float position[4];
    char pad150[0x10];
    float shake;
    int pad164, duration, timer;
    char pad170[0x200];
    float forward[4];
};
extern struct Camera98 g_hero_l05_state;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void emit_scaled_particle_burst_pal(void *, void *);

/* Spawns an explosion effect at the position, with a camera shake when the hero is near, and starts
   its particles (PAL). */
char *moby_spawn_explosion_effect_pal(void *position, int shake, int a2, int a3, int a4, int a5, int a6, int a7, float scale)
{
    float direction[4], normal[4], sphere[4], delta[4];
    char *obj;
    struct EffectState98 *state;
    obj = CreateMoby(0x12e8);
    if (obj) {
        state = *(struct EffectState98 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 0xff;
        *(unsigned short *)(obj + 0x32) = 0xff;
        obj[0x20] = 0;
        qcopy(obj + 0x10, position);
        *(float *)(obj + 0x1c) = 1.0f;
        FastVecSub(direction, g_hero_l05_state.position, obj + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(obj + 0x10, normal, 1);
        qcopy(obj + 0xc0, direction);
        FastVecCross(obj + 0xd0, obj + 0xc0, normal);
        vec_scale_to_length(obj + 0xd0, obj + 0xd0, 1.0f);
        FastVecCross(obj + 0xe0, obj + 0xd0, obj + 0xc0);
        *(float *)(obj + 0xcc) = *(float *)(obj + 0xdc) = *(float *)(obj + 0xec) = 0.0f;
        state->duration = state->timer = 50;
        state->scale2 = scale * 2.0f;
        state->scale4 = scale * 4.0f;
        state->a2 = a2;
        state->a3 = a3;
        state->a4 = a4;
        state->a5 = a5;
        state->a6 = a6;
        state->a7 = a7;
        state->scale = scale;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 8;
            state->fade = 0.125f;
            if (fast_vec_dist(position, g_hero_l05_state.position) < 48.0f && shake) {
                char *camera = (char *)&g_hero_l05_state;
                *(int *)(camera + 0x16c) = 0;
                *(int *)(camera + 0x168) = 33;
                *(float *)(camera + 0x160) = 0.075f;
            }
            if (state->visible) {
                FastVecSub(delta, obj + 0x10, g_hero_l05_state.position);
                vec_scale_to_length(delta, delta, 1.0f);
                if (1.57079637f - math_fast_angle_helper(FastVecDot(delta, g_hero_l05_state.forward)) < 0.45378566f)
                    state->visible = 1;
                else
                    state->visible = 0;
            }
        } else {
            state->delay = 0;
            state->visible = 0;
        }
        emit_scaled_particle_burst_pal(obj, normal);
    }
    return obj;
}
