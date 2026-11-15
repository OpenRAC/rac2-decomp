#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_U32_FE8672EA5
#define RAC2_T_U32_FE8672EA5
typedef unsigned int u32_Fe8672ea5;
#endif

extern u32_Fe8672ea5 D_L04_001B2AF0[];

extern u32_Fe8672ea5 D_L04_001AC18C __attribute__((sda));

extern float D_L04_001AC190 __attribute__((sda));

extern void func_00282C88(void *target);

/* Clears the table of effect particles so every slot is free. */
void func_002ED260(u32_Fe8672ea5 tableBase)
{
    u32_Fe8672ea5 cursor = tableBase + 40952;
    int i;

    gEffectRecordTable = tableBase;
    for (i = 511; i >= 0; i--) {
        *(u32_Fe8672ea5 *)cursor = 0;
        cursor -= 80;
    }
    D_L04_001AC190 = 1.0f;
    ClearVector128(D_L04_001B2AF0);
}

/* func_002ED2B8 is matched in 002ED2B8-g8.c (built with -frac2-qcopy). */

extern float func_00283CE0(int value);
extern int func_00283CF0(float value);
extern int func_00283D38(int a, int b, float c);
extern float func_00283B98(float a, float b);
extern float func_002A7878(float a, float b);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_00282D30(void *a0, void *a1, float scale);
extern int func_00282948(void *a0);

/* Updates every particle that belongs to this owner: fades it, spins it and moves it along. */
void func_002ED368(u32_Fe8672ea5 owner)
{
    int i;
    u32_Fe8672ea5 offset;
    u32_Fe8672ea5 rec;
    float lifeRatio;

    if (gEffectRecordTable == 0) {
        return;
    }
    i = 0;
    offset = 0;
    while (1) {
        rec = offset + gEffectRecordTable;
        if (*(u32_Fe8672ea5 *)(rec + 0x48) == owner) {
            float ratio = IntToFloat(*(int *)(rec + 0x40));
            float delta;
            lifeRatio = ratio / IntToFloat(*(int *)(rec + 0x44));
            *(int *)(rec + 0x38) = FloatToInt((float)*(int *)(rec + 0x34) * lifeRatio);
            *(u32_Fe8672ea5 *)(rec + 0x30) = *(u32_Fe8672ea5 *)(rec + 0x2C);
            *(int *)(rec + 0x30) = FastTweenColor(0x003F3F3F, *(int *)(rec + 0x2C), (lifeRatio * lifeRatio) * lifeRatio);
            *(float *)(rec + 0x24) = FastAddRotations(*(float *)(rec + 0x24), *(float *)(rec + 0x20));
            if (*(int *)(rec + 0x3C) != 0) {
                delta = RandomFloatRange(0.001f, 0.003f);
                *(float *)(rec + 0x28) = *(float *)(rec + 0x28) + delta;
            }
            FastVecAdd((void *)rec, (void *)rec, (void *)(rec + 0x10));
            FastVecScale((void *)(rec + 0x10), (void *)(rec + 0x10), 0.99f);
            if (FastFloatHelperD((void *)(rec + 0x40)) != 0) {
                *(u32_Fe8672ea5 *)(rec + 0x48) = 0;
            }
        }
        i++;
        offset += 80;
        if (i >= 512)
            break;
    }
}

#include "include_asm.h"

#ifndef RAC2_T_U32_FE8672EA5
#define RAC2_T_U32_FE8672EA5
typedef unsigned int u32_Fe8672ea5;
#endif

extern u32_Fe8672ea5 D_L04_001AC18C __attribute__((sda));
extern float D_L04_001AC190 __attribute__((sda));

extern void func_00281EB8(void *a0, u32_Fe8672ea5 a1, u32_Fe8672ea5 a2, int a3, float f12, float f13, float f14);

/* Draws every particle that is in use. */
void func_002ED4B8(void)
{
    u32_Fe8672ea5 offset;
    u32_Fe8672ea5 cursor;
    int i;

    if (gEffectRecordTable == 0) {
        return;
    }
    offset = 0;
    for (i = 511; i >= 0; i--) {
        cursor = gEffectRecordTable + offset;
        if (*(u32_Fe8672ea5 *)(cursor + 0x48) != 0) {
            float scaled;
            int flag;
            int typeBits;
            flag = 1;
            typeBits = *(int *)(cursor + 0x3C) >> 1;
            if (typeBits != 0) {
                flag = typeBits != 1;
            }
            scaled = (float)*(int *)(cursor + 0x38) * D_L04_001AC190;
            DrawBillboardQuad_00281EB8((void *)cursor, *(u32_Fe8672ea5 *)(cursor + 0x4C),
                          *(u32_Fe8672ea5 *)(cursor + 0x30) | ((u32_Fe8672ea5)(int)scaled << 24),
                          flag,
                          *(float *)(cursor + 0x28), 0.001f, *(float *)(cursor + 0x24));
        }
        offset += 80;
    }
}
