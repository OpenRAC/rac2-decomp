#include "common.h"

/* func_PAL_0032F7C8, the PAL copy of func_0032DD40: the same C at 50 Hz, with scaled rates, life spans and frame counts.
 * Its first two loops take separate counters. Uses -G8 small data and -g to retain the retail loop scheduling. */
typedef struct {
    char prefix[0x140];
    float position[4];
    char gap[0x10];
    float amplitude;
    int unknown;
    int duration;
    int flag;
} BurstCamera;
extern BurstCamera D_001B5200;
extern char D_0018A0E0[], D_L00_001FE940[];
extern char D_001A8BD0[] __attribute__((sda));
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern void func_PAL_00330020(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00283248(float, float), func_002A78D8(float, float);
extern float func_002A7878(float, float), func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern char *func_PAL_002BE9A8(void *, float, float, float, float, int, void *, int, int);
extern char *func_002C65A0(void *, void *, int, int, int, int, int, int, float, float, float);
/* Alternate typed interleavings preserve the EE integer and FP argument banks. */
extern char *func_002C65A0_layer(void *, void *, int, int, int, int, int,
                                   float, float, float, int) __asm__("func_002C65A0");
extern char *func_PAL_002BE9A8_smoke(void *, float, float, float, int, float,
                                   void *, int, int) __asm__("func_PAL_002BE9A8");
extern int func_002A7820(int, int), func_00283CF0(float);
extern float func_00283CE0(int), func_00283180(float), func_00283198(float);
extern float D_001B0804 __attribute__((sda));
extern float D_001B080C __attribute__((sda));
extern float D_001B0808 __attribute__((sda));
extern float D_001B079C __attribute__((sda));
extern float D_001B0780 __attribute__((sda));
extern float D_001B0784 __attribute__((sda));
extern float D_001B0788 __attribute__((sda));
extern float D_001B078C __attribute__((sda));
extern float D_001B0790 __attribute__((sda));
extern float D_001B0794 __attribute__((sda));
extern float D_001B0798 __attribute__((sda));
extern float D_001B07E4 __attribute__((sda));
extern float D_001B07E8 __attribute__((sda));
extern float D_001B07EC __attribute__((sda));
extern float D_001B07F0 __attribute__((sda));
extern float D_001B07F4 __attribute__((sda));
extern int D_001B0810 __attribute__((sda));
extern int D_001B07A0 __attribute__((sda));
extern int D_001B07A4 __attribute__((sda));
extern int D_001B07FC __attribute__((sda));
extern int D_001B0800 __attribute__((sda));
extern unsigned char D_001B07F8 __attribute__((sda));

/* Emits three particle groups around the object and sets camera shake when visible. */
void func_PAL_0032F7C8(char *self)
{
    float sphere[4], delta[4], center[4], position[4], velocity[4], other[4];
    int i, j, sign;
    float angle;
    float *eye;

    qcopy(sphere, self + 0x10);
    sphere[3] = 2;
    if (func_00283DB8(sphere, 48) == 1) {
        func_PAL_00330020(func_00282E48(self + 0x10, D_001B5200.position));
        D_001B5200.flag = 0;
        D_001B5200.duration = 33;
        D_001B5200.amplitude = 0.1f;
    }
    eye = D_001B5200.position;
    func_PAL_002AC718(self, D_001A8BD0, self + 0x10, 0, 0, 0, 0, 0, 0, 0, 9, 0, -1, 20, 0, 0, -1, 0, 0x810001);
    func_00282CF0(delta, eye, self + 0x10);
    func_00282F20(delta, delta, D_001B0804);
    func_00282CC0(center, self + 0x10, delta);
    qcopy(self + 0x10, center);
    angle = func_00283248(D_001B5200.position[0] - *(float *)(self + 0x10), D_001B5200.position[1] - *(float *)(self + 0x14));
    sign = 1;
    for (i = 0; i < 20; i++) {
        float speed, a, b;
        char *particle, *sub;

        sign = -sign;
        position[0] = center[0] + func_002A78D8(0, D_001B080C);
        position[1] = center[1] + func_002A78D8(0, D_001B080C);
        position[2] = center[2] + func_002A78D8(0, D_001B080C);
        speed = func_002A7878(0.020000001f, 0.040000003f);
        a = func_002A78D8(0, 1.3962636f);
        b = func_002A78D8(0, 1.5707964897155762f);
        func_002AF000(velocity, speed, func_00283B98(angle, b), a);
        particle = func_PAL_002BE9A8(position, 0, 1, 1.01f, D_001B0808 * 210000, sign, velocity, D_001B0810, 1);
        if (particle) {
            *(short *)(particle + 0xA) = ((s32)func_002A7820(40, 70) * 5 + 2) / 6;
            particle[9] = func_00283CF0(4) + 64;
            sub = particle + 0x20;
            *(int *)(sub + 4) = 3;
            *(float *)(sub + 0x1C) = func_00283CE0(((s32)func_002A7820(1, 10) * 5 + 2) / 6);
            sub[0xA] = 64;
            sub[0xB] = particle[0xA];
        }
    }
    for (j = 0; j < 32; j++) {
        float size, speed, a, energy;
        int count, kind;
        char *particle;
        int definitions = (int)D_L00_001FE940;

        count = func_00283CF0(func_002A78D8(2, 5));
        kind = func_002A7820(D_001B07A0, D_001B07A4);
        position[0] = center[0] + func_002A78D8(0, D_001B079C);
        position[1] = center[1] + func_002A78D8(0, D_001B079C);
        position[2] = center[2] + func_002A78D8(0, D_001B079C);
        size = func_002A7878(D_001B0780, D_001B0784);
        speed = func_002A7878(D_001B0788, D_001B078C);
        a = func_00283B98(angle, func_002A78D8(0, 1.3962636f));
        velocity[0] = func_00283180(a) * 0.020000001f * speed;
        velocity[1] = func_00283198(a) * 0.020000001f * speed;
        velocity[2] = 0;
        velocity[2] = func_002A7878(D_001B0790, D_001B0794) * 0.020000001f;
        energy = size * 210000;
        func_002C65A0(position, velocity, ((s32)kind * 5 + 2) / 6, 0x7F7F7F, count, 127, 127, 1, energy, 2100, D_001B0798 * 0.00040000002f);
        other[0] = position[0] + func_002A78D8(0, 0.01f);
        other[1] = position[1] + func_002A78D8(0, 0.01f);
        other[2] = position[2] + func_002A78D8(0, 0.01f);
        func_002C65A0_layer(other, velocity, ((s32)kind * 5 + 2) / 6, 0x7F7F7F, -count, 127, 127, energy, 2100, D_001B0798 * 0.00040000002f, 1);
        particle = func_002C65A0(position, velocity, ((s32)kind * 5 + 2) / 6, 0x202080, -(count << 1), 48, 48, 1, size * 1260000, 4200, D_001B0798 * 0.00040000002f);
        if (particle) particle[2] = **(char **)(definitions + 0xD4);
    }
    func_00282CF0(position, D_001B5200.position, center);
    func_00282F20(position, position, 1);
    func_00282CC0(center, center, position);
    {
        int i;
        for (i = 0; i < 20; i++) {
            float energy;
            int kind, count;
            char *particle, *sub;

            func_00282D30(velocity, D_0018A0E0, -(func_002A7878(D_001B07F0, D_001B07F4) * 0.020000001f));
            kind = ((s32)func_002A7820(D_001B07FC, D_001B0800) * 5 + 2) / 6;
            count = func_00283CF0(func_002A78D8(1, 2));
            energy = func_002A7878(D_001B07E4, D_001B07E8) * 210000;
            other[0] = center[0] + func_002A78D8(0, D_001B07EC);
            other[1] = center[1] + func_002A78D8(0, D_001B07EC);
            other[2] = center[2] + func_002A78D8(0, D_001B07EC);
            particle = func_PAL_002BE9A8_smoke(other, 0, 1, 1.01f, count, energy, velocity, 0x7F202020, 1);
            if (particle) {
                *(short *)(particle + 0xA) = kind;
                particle[3] = 0x44;
                particle[9] = func_00283CF0(4) + 64;
                sub = particle + 0x20;
                *(float *)(sub + 0x1C) = func_00283CE0(((s32)func_002A7820(7, 15) * 5 + 2) / 6);
                *(int *)(sub + 4) = 3;
                sub[0xA] = D_001B07F8;
                sub[0xB] = particle[0xA];
            }
        }
    }
}
