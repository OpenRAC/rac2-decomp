#include "common.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

extern float D_L17_001B032C __attribute__((sda));

extern float D_L17_001B0330 __attribute__((sda));

extern float D_L17_001B0334 __attribute__((sda));

extern float D_L17_001B0338 __attribute__((sda));

extern float D_L17_001B033C __attribute__((sda));

extern float D_L17_001B0360 __attribute__((sda));

extern float D_00189EA0[];

extern void func_002AEE70(char *, char *, char *, float, float, float);

extern void func_002AEF28(char *, char *, char *, float, float, float);

extern void func_00282CF0(float *, float *, float *);

extern void func_002836E8(float *, float *);

extern void func_00283098(float *, float *, float *);

extern float func_00282C48(float);

/* Re-aims one record's two angle pairs from the level's shared angle words: the 0x118/0x11C
   pair takes 0.000290888245f (arcseconds to radians) times the shared 0x1B0330 word, with the
   record's own 0x12C float as the third argument in the type-3 arm and -1.0f otherwise; the
   0x120/0x124 pair then takes the other two scaled words. */
void func_L17_003C7018(char *moby)
{
    char *state = *(char **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 3) {
        UpdateWrappedAngleOffset(moby, state + 0x11C, state + 0x118, D_L17_001B032C,
                      D_L17_001B0330 * 0.000290888245f,
                      *(f32 *)(state + 0x12C));
    } else {
        UpdateWrappedAngleOffset(moby, state + 0x11C, state + 0x118, D_L17_001B032C,
                      D_L17_001B0330 * 0.000290888245f, -1.0f);
    }
    ScaleOwnerWordsByAngles(moby, state + 0x120, state + 0x124, D_L17_001B0334,
                  D_L17_001B0338 * 0.000290888245f,
                  D_L17_001B033C * 0.000290888245f);
}

/* Transforms the level's fixed point through the object's own matrix, then through the
   object's second matrix, and keeps the result when both coordinates stay inside the
   shared bound and the object's own height is within two of the fixed point's. */
int func_L17_003C70E0(char *moby)
{
    float localPoint[4];
    float matrix[12];

    FastVecSub(localPoint, gHeroPosition, moby + 0x10);
    FastMatrixHelperC(matrix, moby + 0xC0);
    matrix_mul_vec3(localPoint, localPoint, matrix);
    if (!(FloatAbs(localPoint[0]) <= D_L17_001B0360))
        return 0;
    if (!(FloatAbs(localPoint[1]) <= D_L17_001B0360))
        return 0;
    if (FloatAbs(gHeroPosition[2] - *(float *)(moby + 0x18)) < 2.0f)
        return 1;
    return 0;
}

extern s32 D_001B2748;

/* Scales the level's shared word by the object's own signed halfword, takes it modulo
   sixty and paints the object with 0x80FFFFFF when the remainder is under fifteen and
   with 0x80404040 otherwise; then it sets the sub-object's two flag words. */
void func_L17_003BCBC8(s32 moby)
{
    s32 frame = D_001B2748;
    s32 period = 60;
    s32 value = *(short *)(moby + 0xB2);
    s32 dimColor = 0x80404040;
    s32 brightColor = 0x80FFFFFF;
    s32 color;
    s32 vars;

    frame = frame + value;
    value = frame % period;
    if (value >= 15)
        color = dimColor;
    else
        color = brightColor;
    *(s32 *)(moby + 0x78) = color;
    vars = *(s32 *)(moby + 0x68);
    *(u32 *)(vars + 0x8C) |= 1;
    *(u16 *)(vars + 0x3E) |= 8;
    *(u8 *)(moby + 0x30) = 0;
}
