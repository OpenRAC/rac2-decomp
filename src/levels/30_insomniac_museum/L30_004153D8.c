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

char *func_L30_004153D8(void *pos, float scale, int shake, int a2, int a3, int a4, int a5, int a6, int sound, int a8, int a9, int color) {
    float direction[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float sphere[4] __attribute__((aligned(16)));
    float towardPlayer[4] __attribute__((aligned(16)));
    char *obj = CreateMoby(0x11E5);
    State153 *st;
    if (obj) {
        st = *(State153 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        *(unsigned char *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        FastVecSub(direction, D_L30_001B9C80.position, obj + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        func_002AFFD8(obj + 0x10, normal, 1);
        qcopy(obj + 0xC0, direction);
        FastVecCross(obj + 0xD0, obj + 0xC0, normal);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, 1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        st->initialLife = st->life = 60;
        st->inner = scale + scale;
        st->outer = scale * 4.0f;
        st->a2 = a2;
        st->a3 = a3;
        st->a4 = a4;
        st->a5 = a5;
        st->a6 = a6;
        st->a8 = a8;
        st->flash = a9;
        st->sound = sound;
        st->color = color;
        st->scale = scale;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            st->duration = 10;
            st->strength = 0.1f;
            if (fast_vec_dist(pos, D_L30_001B9C80.position) < 48.0f && shake) {
                D_L30_001B9C80.shakeTimer = 0;
                D_L30_001B9C80.shakeDuration = 40;
                D_L30_001B9C80.shakeStrength = 0.075f;
            }
            if (st->sound) {
                FastVecSub(towardPlayer, obj + 0x10, D_L30_001B9C80.position);
                vec_scale_to_length(towardPlayer, towardPlayer, 1.0f);
                if (1.5707963705062866f - func_002831B0(FastVecDot(towardPlayer, D_L30_001B9C80.forward)) < 0.45378565788269043f)
                    st->sound = 1;
                else
                    st->sound = 0;
            }
        } else {
            st->duration = 0;
            st->sound = 0;
        }
        EmitMuseumExplosionParticles(obj, normal);
    }
    return obj;
}
