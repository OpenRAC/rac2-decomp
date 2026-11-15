#include "common.h"
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_L30_004158B0(void *, void *);
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
char *func_L30_004153D8(void *pos, float scale, int shake, int a2, int a3, int a4, int a5, int a6, int sound, int a8, int a9, int color) {
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
        FastVecSub(direction, D_L30_001B9C80.position, moby + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        ComputeViewDirection(moby + 0x10, normal, 1);
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
        if (FastMathHelperA(sphere, 128.0f) == 1) {
            state->duration = 10;
            state->strength = 0.1f;
            if (fast_vec_dist(pos, D_L30_001B9C80.position) < 48.0f && shake) {
                D_L30_001B9C80.shakeTimer = 0;
                D_L30_001B9C80.shakeDuration = 40;
                D_L30_001B9C80.shakeStrength = 0.075f;
            }
            if (state->sound) {
                FastVecSub(towardPlayer, moby + 0x10, D_L30_001B9C80.position);
                vec_scale_to_length(towardPlayer, towardPlayer, 1.0f);
                if (1.5707963705062866f - FastAngleHelper(FastVecDot(towardPlayer, D_L30_001B9C80.forward)) < 0.45378565788269043f)
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
