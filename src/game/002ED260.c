#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_U32_FE8672EA5
#define RAC2_T_U32_FE8672EA5
typedef unsigned int u32_Fe8672ea5;
#endif

extern u32_Fe8672ea5 D_L04_001B2AF0[];

extern u32_Fe8672ea5 g_effect_record_table __attribute__((sda));

extern float D_L04_001AC190 __attribute__((sda));

extern void vec_clear_128(void *target);

/* Clears the table of effect particles so every slot is free. */
void part_init_effect_table(u32_Fe8672ea5 tableBase)
{
    u32_Fe8672ea5 cursor = tableBase + 40952;
    int i;

    g_effect_record_table = tableBase;
    for (i = 511; i >= 0; i--) {
        *(u32_Fe8672ea5 *)cursor = 0;
        cursor -= 80;
    }
    D_L04_001AC190 = 1.0f;
    vec_clear_128(D_L04_001B2AF0);
}

/* func_002ED2B8 is matched in 002ED2B8-g8.c (built with -frac2-qcopy). */

extern float IntToFloat(int value);
extern int FloatToInt(float value);
extern int FastTweenColor(int a, int b, float c);
extern float FastAddRotations(float a, float b);
extern float math_random_float_range(float a, float b);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern void FastVecScale(void *a0, void *a1, float scale);
extern int math_fast_float_d(void *a0);

/* Updates every particle that belongs to this owner: fades it, spins it and moves it along. */
void part_update_effect_records(u32_Fe8672ea5 owner)
{
    int i;
    u32_Fe8672ea5 offset;
    u32_Fe8672ea5 rec;
    float lifeRatio;

    if (g_effect_record_table == 0) {
        return;
    }
    i = 0;
    offset = 0;
    while (1) {
        rec = offset + g_effect_record_table;
        if (*(u32_Fe8672ea5 *)(rec + 0x48) == owner) {
            float ratio = IntToFloat(*(int *)(rec + 0x40));
            float delta;
            lifeRatio = ratio / IntToFloat(*(int *)(rec + 0x44));
            *(int *)(rec + 0x38) = FloatToInt((float)*(int *)(rec + 0x34) * lifeRatio);
            *(u32_Fe8672ea5 *)(rec + 0x30) = *(u32_Fe8672ea5 *)(rec + 0x2C);
            *(int *)(rec + 0x30) = FastTweenColor(0x003F3F3F, *(int *)(rec + 0x2C), (lifeRatio * lifeRatio) * lifeRatio);
            *(float *)(rec + 0x24) = FastAddRotations(*(float *)(rec + 0x24), *(float *)(rec + 0x20));
            if (*(int *)(rec + 0x3C) != 0) {
                delta = math_random_float_range(0.001f, 0.003f);
                *(float *)(rec + 0x28) = *(float *)(rec + 0x28) + delta;
            }
            FastVecAdd((void *)rec, (void *)rec, (void *)(rec + 0x10));
            FastVecScale((void *)(rec + 0x10), (void *)(rec + 0x10), 0.99f);
            if (math_fast_float_d((void *)(rec + 0x40)) != 0) {
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

extern u32_Fe8672ea5 g_effect_record_table __attribute__((sda));
extern float D_L04_001AC190 __attribute__((sda));

extern void gfx_draw_billboard_quad(void *a0, u32_Fe8672ea5 a1, u32_Fe8672ea5 a2, int a3, float f12, float f13, float f14);

/* Draws every particle that is in use. */
void part_draw_effect_records(void)
{
    u32_Fe8672ea5 offset;
    u32_Fe8672ea5 cursor;
    int i;

    if (g_effect_record_table == 0) {
        return;
    }
    offset = 0;
    for (i = 511; i >= 0; i--) {
        cursor = g_effect_record_table + offset;
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
            gfx_draw_billboard_quad((void *)cursor, *(u32_Fe8672ea5 *)(cursor + 0x4C),
                          *(u32_Fe8672ea5 *)(cursor + 0x30) | ((u32_Fe8672ea5)(int)scaled << 24),
                          flag,
                          *(float *)(cursor + 0x28), 0.001f, *(float *)(cursor + 0x24));
        }
        offset += 80;
    }
}
