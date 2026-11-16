#include "common.h"
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void EmitMuseumExplosionParticles(void *, void *);
extern struct Player153 {
    char pad[0x140];
    float position[4];
    char pad2[0x10];
    float shakeStrength;
    int pad3;
    int shakeDuration, shakeTimer;
    char pad4[0x200];
    float forward[4];
} D_L30_001B9C80;
typedef struct {
    short life, initialLife, duration;
    short pad;
    float inner, outer, strength, scale;
    int sound, flash, a2, a3, a4, a5, a6, a8, color;
} State153;

/* Spawns an explosion object at a position, aims it at the player, shakes the screen if close, then starts the particle burst. */
char *museum_explosion_spawn(void *pos, float scale, int shake, int a2, int a3, int a4, int a5, int a6, int sound, int a8, int a9, int color) {
    float direction[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float sphere[4] __attribute__((aligned(16)));
    float towardPlayer[4] __attribute__((aligned(16)));
    char *moby = CreateMoby(0x11E5 /* moby class 4581 */);
    State153 *state;
    if (moby) {
        state = *(State153 **)(moby + 0x68);
        *(unsigned char *)(moby + 0x30) = 255;
        *(unsigned short *)(moby + 0x32) = 255;
        *(unsigned char *)(moby + 0x20) = 0;
        qcopy(moby + 0x10, pos);
        *(float *)(moby + 0x1C) = 1.0f;
        FastVecSub(direction, g_camera_l30_state.position, moby + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(moby + 0x10, normal, 1);
        qcopy(moby + 0xC0, direction);
        FastVecCross(moby + 0xD0, moby + 0xC0, normal);
        vec_scale_to_length(moby + 0xD0, moby + 0xD0, 1.0f);
        FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
        *(float *)(moby + 0xCC) = *(float *)(moby + 0xDC) = *(float *)(moby + 0xEC) = 0.0f;
        state->initialLife = state->life = 60;
        state->inner = scale + scale;
        state->outer = scale * 4.0f;
        state->a2 = a2;
        state->a3 = a3;
        state->a4 = a4;
        state->a5 = a5;
        state->a6 = a6;
        state->a8 = a8;
        state->flash = a9;
        state->sound = sound;
        state->color = color;
        state->scale = scale;
        qcopy(sphere, moby + 0x10);
        sphere[3] = scale * 3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->duration = 10;
            state->strength = 0.1f;
            if (fast_vec_dist(pos, g_camera_l30_state.position) < 48.0f && shake) {
                g_camera_l30_state.shakeTimer = 0;
                g_camera_l30_state.shakeDuration = 40;
                g_camera_l30_state.shakeStrength = 0.075f;
            }
            if (state->sound) {
                FastVecSub(towardPlayer, moby + 0x10, g_camera_l30_state.position);
                vec_scale_to_length(towardPlayer, towardPlayer, 1.0f);
                if (1.5707963705062866f - math_fast_angle_helper(FastVecDot(towardPlayer, g_camera_l30_state.forward)) < 0.45378565788269043f)
                    state->sound = 1;
                else
                    state->sound = 0;
            }
        } else {
            state->duration = 0;
            state->sound = 0;
        }
        EmitMuseumExplosionParticles(moby, normal);
    }
    return moby;
}
