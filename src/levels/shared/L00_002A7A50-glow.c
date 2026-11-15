/* Source-shape reference: OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/hero_idle_and_animation.c. */
/* Draws the hero glow and the queued effects for the current mode. */
#include "common.h"

typedef struct {
    unsigned char pad0[0x21C];
    short f21C;                       /* 0x21C */
    unsigned char pad21E[0x186C - 0x21E];
    float f186C;                      /* 0x186C */
    unsigned char pad1870[0x1FE0 - 0x1870];
    float glow[3][4];                 /* 0x1FE0 */
    float v2010[4];                   /* 0x2010 */
    float v2020[4];                   /* 0x2020 */
    unsigned char pad2030[0x2080 - 0x2030];
    float queue[8][4];                /* 0x2080 */
    unsigned int queueColor[8];       /* 0x2100 */
    float queueSize[8];               /* 0x2120 */
    float queueFade[8];               /* 0x2140 */
    short queueCount;                 /* 0x2160 */
    unsigned char pad2162[0x22B4 - 0x2162];
    unsigned char mode;               /* 0x22B4 */
    unsigned char pad22B5[0x24FC - 0x22B5];
    short f24FC;                      /* 0x24FC */
    short pad24FE;
    short f2500;                      /* 0x2500 */
    unsigned char pad2502[0x2508 - 0x2502];
    unsigned int f2508;               /* 0x2508 */
    unsigned char pad250C[0x2520 - 0x250C];
    short f2520;                      /* 0x2520 */
    short pad2522;
    unsigned int f2524;               /* 0x2524 */
} Hero_L00_002A7A50;
extern Hero_L00_002A7A50 D_00189E20;
extern int D_L00_001A8F00 MACRO_ADDR;
extern unsigned char D_001A7A40[] __attribute__((sda));
extern void func_L00_00325AE8(void *, unsigned int, float, float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_0027DDC0(int, int, int, int);
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_L00_002ADEA0(int);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_002AA2E8(float *, float, float);

void func_L00_002A7A50(void)
{
    int index, alpha;
    float value, divisor, size, step, peak;
    unsigned int color;

    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        for (index = 0; index < gHeroState.queueCount; index++)
            DrawBillboardQuad_L00(gHeroState.queue[index], gHeroState.queueColor[index],
                              gHeroState.queueSize[index], gHeroState.queueFade[index]);
        return;
    }
    if (gHeroState.f21C) {
        value = IntToFloat(gHeroState.f21C);
        divisor = IntToFloat(18);
        value = value * 3.1415927f;
        value = FastSinOrCosB(value / divisor);
        alpha = FloatToInt((value * 0.5f + 0.5f) * 80.0f);
        SetClearColorPacket(0xAA, 0, 0, alpha);
        VU1_addGSregister(0x47, 0x5360B);
    }
    if (gHeroState.mode == 3) {
        unsigned int tint = gHeroState.f2508;
        float (*glow)[4] = gHeroState.glow;
        int remaining = 2;
        while (remaining >= 0) {
            DrawBillboardQuad_L00(*glow, tint, 0.2f, 0.08f);
            glow++;
            remaining--;
        }
    } else if (gHeroState.mode == 0) {
        if ((hero_slot_item_id(3) == 3 || hero_slot_item_id(3) == 2) && !gHeroState.f24FC) {
            if (gHeroState.f2500) {
                peak = 1.0f;
                if (peak < gHeroState.v2020[0]) peak = gHeroState.v2020[0];
                if (peak < gHeroState.v2020[1]) peak = gHeroState.v2020[1];
                if (peak < gHeroState.v2020[2]) peak = gHeroState.v2020[2];
                FastTweenColor(0xC0000028U, 0x28, peak);
            }
            DrawBillboardQuad_L00(gHeroState.v2010, 0xC0000028U, 0.05700000002980232f, 0.08f);
        }
        for (index = 0; index < gHeroState.queueCount; index++)
            DrawBillboardQuad_L00(gHeroState.queue[index], gHeroState.queueColor[index],
                              gHeroState.queueSize[index], gHeroState.queueFade[index]);
    } else if (gHeroState.mode == 2) {
        DrawBillboardQuad_L00(gHeroState.v2010, 0x300000C0U, 0.25f, 0.08f);
    } else if (gHeroState.mode == 1) {
        size = gHeroState.f2520 ? 0.101500004529953f : 0.07f;
        if (D_001A7A40[3]) {
            gHeroState.v2010[2] -= 0.01f;
            size *= 1.7f;
        } else {
            gHeroState.v2010[2] -= 0.02f;
        }
        ApproachValue(&gHeroState.f186C, size, 0.003f);
        DrawBillboardQuad_L00(gHeroState.v2010, gHeroState.f2524, gHeroState.f186C, 0.08f);
    }
}
