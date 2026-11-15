#include "common.h"

typedef int Vector __attribute__((mode(TI)));
/* Four additional hero manipulators, each with a 0x40-byte record. */
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
void func_L00_002A5840(void) {
    unsigned char *hero0, *hero1, *hero2;
    unsigned char *object;
    int alpha, greenBase, redWave, red, blue, green, greenOffset, redOffset, blueOffset, period;
    float normalized, wave, amplitude;
    if (D_001A7A43)
        ApproachValue(&D_L00_001A7CF8, 1.8f, 0.05f);
    else
        ApproachValue(&D_L00_001A7CF8, 1.0f, 0.05f);
    hero0 = (unsigned char *)&gHeroState;
    if ((unsigned int)(hero0[0x22B4] - 1) < 2)
        object = *(unsigned char **)(hero0 + 0x2290);
    else {
        if (*(short *)(hero0 + 0x24FC)) return;
        object = *(unsigned char **)(hero0 + 0x1314);
    }
    if (object == 0) return;
    hero1 = (unsigned char *)&gHeroState;
    *(unsigned short *)(object + 0x34) |= 0x10;
    alpha = 128;
    green = 136;
    blue = 56;
    if (*(int *)(hero1 + 0x24CC) == 1) blue = green;
    period = 110;
    normalized = IntToFloat(period);
    normalized = (float)(gFrameCounter_L00 % period) / normalized;
    normalized = normalized + normalized;
    normalized = normalized * 3.1415927f;
    wave = FastSinOrCosB(normalized + -3.1415927f);
    amplitude = wave * 24.0f;
    blueOffset = FloatToInt(amplitude) + 12;
    blue += blueOffset;
    greenBase = FloatToInt(wave * 48.0f);
    greenOffset = greenBase + 24;
    redWave = FloatToInt(amplitude);
    green = greenBase + 160;
    redOffset = redWave + 12;
    red = redWave + 76;
    if (*(short *)(hero1 + 0x20E) != 0) {
        float blend = 1.0f;
        int max = 40;
        int age = *(short *)(hero1 + 0x20E);
        if (max < age)
            blend = IntToFloat(45 - *(short *)(hero1 + 0x20E)) / IntToFloat(5);
        if (*(short *)(hero1 + 0x20E) < 20)
            blend = IntToFloat(*(short *)(hero1 + 0x20E)) / IntToFloat(20);
        blue -= FloatToInt((float)blueOffset * blend);
        green -= FloatToInt((float)greenOffset * blend);
        red -= FloatToInt((float)redOffset * blend);
        blue += FloatToInt(blend * 112.0f);
        green -= FloatToInt(blend * 72.0f);
    }
    {
        int color = (alpha << 24) | (red << 16);
        color |= green << 8;
        color |= blue;
        *(int *)(object + 0x78) = color;
    }
    hero2 = (unsigned char *)&gHeroState;
    if (hero2[0x22B4] != 0 || *(int *)(hero2 + 0x2294) == 124) return;
    if (FastDecTimer((short *)(hero2 + 0x118C)) && object[0x43] == 1) {
        *(short *)(hero2 + 0x118C) = RandomIntRange(50, 200);
        *(short *)(hero2 + 0x118E) = 1;
    }
    if (gHeroState.timer == 0) return;
    gHeroState.timer++;
    if (gHeroState.timer > 21) gHeroState.timer = 0;
    if (gHeroState.timer == 0) {
        int i;
        for (i = 0; i < 4; i++)
            if (gHeroState.effects[i].attached)
                DetachManipulator((char *)object, (char *)&gHeroState.effects[i]);
    } else {
        int i, j;
        const Vector *scale = D_L00_001A7EA0;
        for (i = 0; i < 4; scale++, i++) {
            if (!gHeroState.effects[i].attached) {
                AttachManipulator(object, D_L00_001A7F20[i], (unsigned char *)&gHeroState.effects[i]);
                gHeroState.effects[i].absolute = 1;
                qcopy(&gHeroState.effects[i].quat, &D_L00_001A7E60[i]);
                qcopy(&gHeroState.effects[i].scale, scale);
                qcopy(&gHeroState.effects[i].translation, &D_L00_001A7EE0[i]);
                FastVecScale(&gHeroState.effects[i].translation, &gHeroState.effects[i].translation, *(float *)(object + 0x2C));
            }
        }
        for (j = 0; j < 4; j++)
            gHeroState.effects[j].blend = D_L00_0025DEE0[gHeroState.timer];
    }
}
