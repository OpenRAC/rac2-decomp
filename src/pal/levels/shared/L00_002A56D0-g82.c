#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char type, attached, pad2, absolute;
    unsigned char pad4[8];
    float blend;
    Vector quat, scale, translation;
} Manip5840;
typedef struct {
    unsigned char pad[0x1080];
    Manip5840 effects[4];
    unsigned char pad1180[0xC];
    short delay, timer;
    unsigned char pad1190[0x24FC - 0x1190];
    short disabled;
} Hero5840;
extern Hero5840 D_00189E20;
extern unsigned char D_001A7A43;
extern float D_L00_001A7CF8 SDATA(D_L00_001A7CF8);
extern int D_L00_001B19C8;
extern Vector D_L00_001A7E60[4] SDATA(D_L00_001A7E60);
extern Vector D_L00_001A7EA0[4] SDATA(D_L00_001A7EA0);
extern Vector D_L00_001A7EE0[4] SDATA(D_L00_001A7EE0);
extern int D_L00_001A7F20[4] SDATA(D_L00_001A7F20);
extern float D_L00_0025DEE0[22];
extern float func_002AA2E8(float *, float, float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_00282978(short *);
extern int func_002A7820(int, int);
extern void func_0029F9F0(char *, char *);
extern void func_0029F978(unsigned char *, unsigned int, unsigned char *);
extern void func_00282D30(void *, void *, float);

/* Update the hero glow and initialize, fade or detach four extra manipulators.
 * Adapted from RAC1's update_hero_glow_and_extra_manipulators
 * (src/overlays/shared/hero_idle_and_animation.c, GPL-3.0).
 */
void func_PAL_L00_002A56D0(void) {
    unsigned char *h0, *g, *g2;
    unsigned char *object;
    int alpha, k, t3, red, blue, green, g_wave, r_wave, b_wave, period;
    float normalized, wave, amplitude;
    if (D_001A7A43)
        func_002AA2E8(&D_L00_001A7CF8, 1.8f, 0.05f);
    else
        func_002AA2E8(&D_L00_001A7CF8, 1.0f, 0.05f);
    h0 = (unsigned char *)&D_00189E20;
    if ((unsigned int)(h0[0x22B4] - 1) < 2)
        object = *(unsigned char **)(h0 + 0x2290);
    else {
        if (*(short *)(h0 + 0x24FC)) return;
        object = *(unsigned char **)(h0 + 0x1314);
    }
    if (object == 0) return;
    g = (unsigned char *)&D_00189E20;
    *(unsigned short *)(object + 0x34) |= 0x10;
    alpha = 128;
    green = 136;
    blue = 56;
    if (*(int *)(g + 0x24CC) == 1) blue = green;
    period = 92;
    normalized = func_00283CE0(period);
    normalized = (float)(D_L00_001B19C8 % period) / normalized;
    normalized = normalized + normalized;
    normalized = normalized * 3.1415927f;
    wave = func_00283198(normalized + -3.1415927f);
    amplitude = wave * 24.0f;
    b_wave = func_00283CF0(amplitude) + 12;
    blue += b_wave;
    k = func_00283CF0(wave * 48.0f);
    g_wave = k + 24;
    t3 = func_00283CF0(amplitude);
    green = k + 160;
    r_wave = t3 + 12;
    red = t3 + 76;
    if (*(short *)(g + 0x20E) != 0) {
        float blend = 1.0f;
        int max = 33;
        int age = *(short *)(g + 0x20E);
        if (max < age)
            blend = func_00283CE0(37 - *(short *)(g + 0x20E)) / func_00283CE0(4);
        if (*(short *)(g + 0x20E) < 17)
            blend = func_00283CE0(*(short *)(g + 0x20E)) / func_00283CE0(17);
        blue -= func_00283CF0((float)b_wave * blend);
        green -= func_00283CF0((float)g_wave * blend);
        red -= func_00283CF0((float)r_wave * blend);
        blue += func_00283CF0(blend * 112.0f);
        green -= func_00283CF0(blend * 72.0f);
    }
    {
        int color = (alpha << 24) | (red << 16);
        color |= green << 8;
        color |= blue;
        *(int *)(object + 0x78) = color;
    }
    g2 = (unsigned char *)&D_00189E20;
    if (g2[0x22B4] != 0 || *(int *)(g2 + 0x2294) == 124) return;
    if (func_00282978((short *)(g2 + 0x118C)) && object[0x43] == 1) {
        *(short *)(g2 + 0x118C) = func_002A7820(42, 167);
        *(short *)(g2 + 0x118E) = 1;
    }
    if (D_00189E20.timer == 0) return;
    D_00189E20.timer++;
    if (D_00189E20.timer > 21) D_00189E20.timer = 0;
    if (D_00189E20.timer == 0) {
        int i;
        for (i = 0; i < 4; i++)
            if (D_00189E20.effects[i].attached)
                func_0029F9F0((char *)object, (char *)&D_00189E20.effects[i]);
    } else {
        int i, j;
        const Vector *scale = D_L00_001A7EA0;
        for (i = 0; i < 4; scale++, i++) {
            if (!D_00189E20.effects[i].attached) {
                func_0029F978(object, D_L00_001A7F20[i], (unsigned char *)&D_00189E20.effects[i]);
                D_00189E20.effects[i].absolute = 1;
                qcopy(&D_00189E20.effects[i].quat, &D_L00_001A7E60[i]);
                qcopy(&D_00189E20.effects[i].scale, scale);
                qcopy(&D_00189E20.effects[i].translation, &D_L00_001A7EE0[i]);
                func_00282D30(&D_00189E20.effects[i].translation, &D_00189E20.effects[i].translation, *(float *)(object + 0x2C));
            }
        }
        for (j = 0; j < 4; j++)
            D_00189E20.effects[j].blend = D_L00_0025DEE0[D_00189E20.timer];
    }
}
