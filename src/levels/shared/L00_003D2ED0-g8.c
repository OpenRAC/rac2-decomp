#include "common.h"
typedef struct { float x, y, z, w; } EffectVector;
extern short D_L00_001B2AF0[] MACRO_ADDR;
extern char D_L00_00247310[], D_L00_00247450[];
extern short D_L00_001B2AF8, D_L00_001B2AFA;
extern char D_L00_001B8DC0[];
extern char D_0018A580[];
extern short D_001A6480[];
extern float D_L00_001B01BC __attribute__((sda)), D_L00_001B01C0 __attribute__((sda)), D_L00_001B01C4 __attribute__((sda)), D_L00_001B01C8 __attribute__((sda));
extern int D_L00_001B021C __attribute__((sda)), D_L00_001B020C __attribute__((sda));
extern float D_L00_001B0208 __attribute__((sda)), D_L00_001B0210 __attribute__((sda));
extern void func_L00_003D37E8(void *, int, int, int, float, float, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282CF0(void *, void *,void *);
extern void func_00282CC0(void *, void *,void *);
extern void func_00282DD8(void *, void *,void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *,void *);
extern void func_002ACB48(void *, float);
extern void func_00281DE8(void *, int, int,int);
extern void func_00280B90(void *, void *, int);
extern void func_002FC560(int, int);
extern void func_0027DE50(int, int,int, int, unsigned int);
/* Update four effect strips, then draw the active radial ring and fading quad. */
void func_L00_003D2ED0(char *object)
{
    char render[0x90];
    EffectVector position, axis, direction;
    struct { EffectVector points[20], offset, center, radial, rotated; int color; } effect;
    int color;
    int i, remaining;
    short *indices = D_L00_001B2AF0;
    char *records = D_L00_00247310;
    char *context = *(char **)(object + 0x68);
    float fade;
    float radius, spread;
    for (remaining = 3; remaining >= 0; indices++, records += 0x50, remaining--)
        DrawScrollingRibbonWithFadedEnds(records, *indices, *indices, 5, D_L00_001B01BC, D_L00_001B01C0, 0.2f);
    DrawScrollingRibbonWithFadedEnds(D_L00_00247450, D_L00_001B2AF8, D_L00_001B2AF8, 5, D_L00_001B01C4, D_L00_001B01C8, 0.2f);
    DrawScrollingRibbonWithFadedEnds(D_L00_00247450 + 0x50, D_L00_001B2AFA, D_L00_001B2AFA, 5, D_L00_001B01C4, D_L00_001B01C8, 0.2f);
    qcopy(&position, context + 0x10);
    func_002AFFD8(&position, &axis, 1);
    FastVecSub(&direction, D_L00_001B8DC0, &position);
    fade = 1.0f;
    vec_scale_to_length(&direction, &direction, fade);
    if (*(int *)(context + 0x44)) {
        if (*(int *)(context + 0x44) < D_L00_001B021C)
            fade = IntToFloat(*(int *)(context + 0x44)) * *(float *)(context + 0x48);
        effect.color = FloatToInt(fade * 64.0f);
        radius = (1.0f - fade) * 10.0f + 0.05f;
        spread = (1.0f - fade) * 0.5f;
        FastVecScale(&effect.offset, D_0018A580, (1.0f - fade)* 32.0f);
        FastVecAdd(&effect.center, &position, &effect.offset);
        for (i = 0; i < 20; i++) {
            func_002AB668(&effect.rotated, &direction, IntToFloat(i)* 0.3141593f);
            func_002ACDE8(&effect.radial, &axis, &effect.rotated);
            FastVecScale(&effect.radial, &effect.radial, radius);
            func_002ACB48(&effect.radial, spread);
            FastVecAdd(&effect.points[i], &effect.center, &effect.radial);
        }
        DrawScrollingRibbonWithFadedEnds(effect.points, effect.color, effect.color, 20, 0.3f, 1.2f, 0.2f);
    }
    if (*(int *)(context + 0x28)) {
        if (*(int *)(context + 0x28) < D_L00_001B020C)
            fade = IntToFloat(*(int *)(context + 0x28)) * *(float *)(context + 0x2C);
        else fade = 1.0f;
        func_00281DE8(render, 11, 1, 128);
        color = (FloatToInt(fade * 255.0f) << 24) | 0x808080;
        *(int *)(render+0x4C)=color;
        *(int *)(render+0x48)=color;
        *(int *)(render+0x44)=color;
        *(int *)(render+0x40)=color;
        *(int *)(render+0x50)=0;
        *(int *)(render+0x54)=0;
        *(int *)(render+0x58)=0;
        *(float *)(render+0x5C)=1.0f;
        *(float *)(render+0x60)=1.0f;
        *(int *)(render+0x64)=0;
        *(float *)(render+0x68)=1.0f;
        *(float *)(render+0x6C)=1.0f;
        FastVecScale(&effect.points[0], &direction, -0.1f);
        FastVecAdd(&effect.points[1], D_L00_001B8DC0, &effect.points[0]);
        FastVecCross(&effect.points[2], &direction, &axis);
        vec_scale_to_length(&effect.points[2], &effect.points[2], D_L00_001B0208);
        FastVecCross(&effect.points[3], &effect.points[2], &direction);
        vec_scale_to_length(&effect.points[3], &effect.points[3], D_L00_001B0208);
        FastVecAdd(&effect.points[4], &effect.points[1], &effect.points[3]);
        FastVecAdd(render, &effect.points[4], &effect.points[2]);
        FastVecSub(render+0x10, &effect.points[4], &effect.points[2]);
        FastVecSub(&effect.points[4], &effect.points[1], &effect.points[3]);
        FastVecAdd(render+0x20, &effect.points[4], &effect.points[2]);
        FastVecSub(render+0x30, &effect.points[4], &effect.points[2]);
        draw_world_quad(render, 0, 0);
        color = (FloatToInt(D_L00_001B0210 * fade) << 24) | 0x808080;
        *(int *)(render+0x4C)=color;
        *(int *)(render+0x48)=color;
        *(int *)(render+0x44)=color;
        *(int *)(render+0x40)=color;
        VU1_addGSregister(66, 72);
        func_0027DE50(0, D_001A6480[0xA9],0,D_001A6480[0xA8],*(unsigned int *)(render+0x40));
    }
}
