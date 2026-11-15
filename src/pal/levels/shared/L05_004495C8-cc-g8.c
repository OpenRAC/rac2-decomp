/* func_PAL_L05_004495C8, the PAL copy of func_L05_004432E0: the same C. */
#include "common.h"

/* func_PAL_L05_004495C8 needs -g -frac2-qcopy -frac2-qcopy-barrier besides -G8, so it has a unit
   of its own (config/cflags.txt). */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector_L05_004432E0;

extern char *D_001B1EC4, *D_L05_001B251C;
extern int g_current_map_index;
/* Retail splits this address: its lui fills a branch delay slot on its own. */
extern char *D_L05_00221D88 __attribute__((nosda));
extern char *D_L05_001B2614 __attribute__((sda));
/* The output vector. As an incomplete sda array its address stays one `la` (an adjacent
   lui/addiu pair), which reorg does not copy into the early exits' delay slots. */
extern char D_L05_001B3600[] __attribute__((sda));
extern float D_L05_001B1AC0 __attribute__((sda));
extern float D_L05_001B1AC4 __attribute__((sda)), D_L05_001B1AC8 __attribute__((sda));
extern float D_L05_001B1BF0 __attribute__((sda)), D_L05_001B1BF4 __attribute__((sda));
extern float D_L05_001B1BD0 __attribute__((sda)), D_L05_001B1BD4 __attribute__((sda));
extern float D_L05_001B1BD8 __attribute__((sda)), D_L05_001B1BDC __attribute__((sda));
extern float D_L05_001B1BE0 __attribute__((sda)), D_L05_001B1BE4 __attribute__((sda));
extern float D_L05_001B1BE8 __attribute__((sda)), D_L05_001B1BEC __attribute__((sda));
extern float D_L05_001B1A7C __attribute__((sda));
extern int hero_get_state_value_b(void);
extern float math_step_spring_damper_clamped(float *velocity, float current, float goal, float a, float b, float c);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

#define FRAME_TIME 0.020000001f /* 1/60 s */
#define DEG_TO_RAD 0.017453294f

static inline float Lerp_L05_004432E0(float from, float to, float t)
{
    return from + (to - from) * t;
}

/* Moves the camera position at camera+0x30 along its moby's +0xC0 direction by the moby
   state's speed, which outside level 20 first approaches a goal (func_002702C8). Level 20 adds
   a height and a side step interpolated from the record's +0x50 block; level 15 adds an
   interpolated climb (written per arm, so jump2 cross-jumps the common tail) and clamps the
   height to 400..650. A sway along camera+0x10 driven by the record's +0xD4 block follows, then
   the [5, 1000] box clamp and a pull back towards entry `index` of D_L05_001B2614. The frame's
   motion is accumulated at record+0x30; the position is copied to D_L05_001B3600. */
void func_PAL_L05_004495C8(char *camera)
{
    Vector_L05_004432E0 motion;
    Vector_L05_004432E0 delta;
    char *record = *(char **)(camera + 0x70);
    char *moby = D_L05_001B251C
        + (*(int *)(*(char **)(D_001B1EC4 + *(short *)(camera + 0x84) * 32 + 0x1C) + 0x20) << 8);
    char *state = *(char **)(moby + 0x68);

    if (g_current_map_index != 20) {
        float goal;
        if (*(int *)(state + 0x34)) {
            goal = (hero_get_state_value_b() ? D_L05_001B1AC8 : D_L05_001B1AC4) * FRAME_TIME;
            *(float *)(state + 0x38) = math_step_spring_damper_clamped((float *)(state + 0x3C),
                *(float *)(state + 0x38), goal, D_L05_001B1BF0, 0.2f, 0.0f);
        } else {
            goal = D_L05_001B1AC0 * FRAME_TIME;
            *(float *)(state + 0x38) = math_step_spring_damper_clamped((float *)(state + 0x3C),
                *(float *)(state + 0x38), goal, D_L05_001B1BF4, 0.2f, 0.0f);
        }
    }
    FastVecScale(&motion, moby + 0xC0, *(float *)(state + 0x38));
    FastVecAdd(camera + 0x30, camera + 0x30, &motion);
    qzero_nc(record + 0x30);

    if (g_current_map_index == 20) {
        char *input = *(char **)(camera + 0x70) + 0x50;
        float t = -*(float *)(input + 0x64) / (*(float *)(input + 0x74) * DEG_TO_RAD);
        float rise = (D_L05_001B1BD4 + (D_L05_001B1BD0 - D_L05_001B1BD4) * t) * FRAME_TIME;
        float sideLow = D_L05_001B1BDC, sideHigh = D_L05_001B1BD8;
        float side;
        *(float *)(camera + 0x38) += rise;
        *(float *)(record + 0x38) = rise;
        t = *(float *)(input + 0x68) / (*(float *)(input + 0x78) * DEG_TO_RAD);
        side = (sideLow + (sideHigh - sideLow) * t) * FRAME_TIME;
        FastVecScale(&delta, camera + 0x10, side);
        FastVecAdd(camera + 0x30, camera + 0x30, &delta);
        FastVecAdd(record + 0x30, record + 0x30, &delta);
    }

    if (g_current_map_index == 15) {
        float oldHeight = *(float *)(camera + 0x38);
        float t = *(float *)(record + 0x40);
        float climb;
        if (hero_get_state_value_b())
            climb = Lerp_L05_004432E0(D_L05_001B1BEC, D_L05_001B1BE8, t) * FRAME_TIME;
        else
            climb = Lerp_L05_004432E0(D_L05_001B1BEC, D_L05_001B1BE4, t) * FRAME_TIME;
        *(float *)(camera + 0x38) += climb;
        if (*(float *)(camera + 0x38) < 400.0f)
            *(float *)(camera + 0x38) = 400.0f;
        else if (*(float *)(camera + 0x38) > 650.0f)
            *(float *)(camera + 0x38) = 650.0f;
        *(float *)(record + 0x38) = *(float *)(camera + 0x38) - oldHeight;
    }

    {
        char *roll = *(char **)(camera + 0x70) + 0xD4;
        if (*(short *)(roll + 4)) {
            float amount = IntToFloat(*(short *)(roll + 6));
            amount = D_L05_001B1BE0 * math_fast_sin_or_cos_b(amount * *(float *)(roll + 8) * 3.1415927f);
            if (*(short *)(roll + 4) == 1)
                amount = -amount;
            FastVecScale(&delta, camera + 0x10, amount);
            FastVecAdd(camera + 0x30, camera + 0x30, &delta);
            FastVecAdd(record + 0x30, record + 0x30, &delta);
        }
    }

    if (*(float *)(camera + 0x30) < 5.0f) *(float *)(camera + 0x30) = 5.0f;
    if (*(float *)(camera + 0x34) < 5.0f) *(float *)(camera + 0x34) = 5.0f;
    if (*(float *)(camera + 0x38) < 5.0f) *(float *)(camera + 0x38) = 5.0f;
    if (*(float *)(camera + 0x30) > 1000.0f) *(float *)(camera + 0x30) = 1000.0f;
    if (*(float *)(camera + 0x34) > 1000.0f) *(float *)(camera + 0x34) = 1000.0f;
    if (*(float *)(camera + 0x38) > 1000.0f) *(float *)(camera + 0x38) = 1000.0f;

    if (!hero_get_state_value_b() && D_L05_00221D88) {
        int index = **(int **)(D_L05_00221D88 + 0x68);
        if (index >= 0) {
            char *sphere = D_L05_001B2614 + index * 128;
            float radius = FastVecLength(sphere) - D_L05_001B1A7C;
            float distance;
            FastVecSub(&delta, sphere + 0x30, camera + 0x30);
            distance = FastVecLength(&delta);
            if (radius < distance) {
                vec_scale_to_length(&delta, &delta, distance - radius);
                FastVecAdd(camera + 0x30, camera + 0x30, &delta);
            }
        }
    }
    *(Quad *)D_L05_001B3600 = *(Quad *)(camera + 0x30);
}
