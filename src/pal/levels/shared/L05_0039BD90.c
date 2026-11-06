#include "include_asm.h"

#include "common.h"

/* func_PAL_L05_0039C0D8, the PAL copy of func_L05_00399268: the same C, with the five random
 * lifetimes scaled for 50 Hz and four rates raised to match. */

extern float func_332BB0(float, float);
extern int func_307778(float);
extern int func_332AF8(int, int);
extern void func_332C60(void *, float, float);
extern char *func_352B28(void *, void *, int, int, int, int, int, int, float, float, float);
extern float func_306CD0(float, float);
extern float func_307620(float, float);
extern char *func_347040(void *, int, void *, int, float, float, float, float, int);
extern float func_307768(int);
extern float func_332B50(float, float);
extern void func_33B330(void *, float, float, float);
extern int func_001163B0(void);
typedef struct {
    char pad[0x140];
    float pos[4];
} ParticleCamera99268;
extern ParticleCamera99268 D_L05_001B9580;
extern unsigned char *D_L05_001FF240[];
typedef struct {
    int v[2];
} __attribute__((packed)) ParticleColors99268;
extern ParticleColors99268 D_L05_001AEC00;

void func_PAL_L05_0039C0D8(char *obj)
{
    float pos[4];
    float vel[4];
    ParticleColors99268 colors;
    char *s = *(char **)(obj + 0x68);
    int i, j, k, sign;
    float angle;
    char *p, *d;

    for (i = 0; i < *(int *)(s + 0x20); i++) {
        int type, life;
        float scale;

        type = func_307778(func_332BB0(2.0f, 5.0f));
        life = func_332AF8(30, 50);
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        scale = func_332B50(0.6f, 1.0f) * *(float *)(s + 0x14);
        func_332C60(vel, 0.06f, 0.1f);
        func_352B28(pos, vel, (life * 5 + 2) / 6, 0x102FFF, type, 255, 0, 1, scale * 210000.0f, scale * 105000.0f, 0.0028000001f);
    }

    for (j = 0; j < *(int *)(s + 0x24); j++) {
        int type, life;
        float scale;

        type = func_307778(func_332BB0(2.0f, 5.0f));
        life = func_332AF8(30, 50);
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        scale = func_332B50(0.75f, 1.5f) * *(float *)(s + 0x14);
        func_332C60(vel, 0.5f, 0.8f);
        func_352B28(pos, vel, (life * 5 + 2) / 6, 0x8FFF, type, 127, 127, 5, scale * 210000.0f, *(float *)(s + 0x14) * 2100.0f, 0.00584f);
    }

    angle = func_306CD0(D_L05_001B9580.pos[0] - *(float *)(obj + 0x10), D_L05_001B9580.pos[1] - *(float *)(obj + 0x14));
    sign = 1;
    for (k = 0; (float)k < (float)*(int *)(s + 0x2C) * 3.0f + (float)(*(int *)(s + 0x3C) * 10); k++) {
        float scale, a, b;

        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        sign = -sign;
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        scale = func_332B50(0.020000001f, 0.030000001f) * *(float *)(s + 0x14);
        a = func_332BB0(0.0f, 1.396263599395752f);
        b = func_332BB0(0.0f, 1.5707964897155762f);
        func_33B330(vel, scale, func_307620(angle, b), a);
        p = func_347040(pos, sign, vel, *(int *)(s + 0x3C) ? 0xD10572 : 0x5A182, 0.0f, 1.0f, 1.01f, *(float *)(s + 0x14) * 31500.001953125f, 0);
        colors = D_L05_001AEC00;
        if (p) {
            d = p + 0x20;
            {
                int index = func_001163B0() % 2;
                p[3] = colors.v[index];
            }
            if (*(int *)(s + 0x3C))
                *(short *)(p + 0xA) = (func_332AF8(120, 150) * 5 + 2) / 6;
            else
                *(short *)(p + 0xA) = (func_332AF8(90, 120) * 5 + 2) / 6;
            p[9] = func_307778(4.0f) + 64;
            *(int *)(d + 4) = 3;
            *(float *)(d + 0x1C) = func_307768((func_332AF8(1, 10) * 5 + 2) / 6);
            d[0xA] = func_332AF8(64, 128);
            d[0xB] = p[0xA];
            if (func_332AB8(4) != 0)
                p[2] = D_L05_001FF240[34][0];
            else
                p[2] = D_L05_001FF240[105][0];
        }
    }
}
