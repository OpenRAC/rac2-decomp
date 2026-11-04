#include "include_asm.h"
#include "common.h"

/* func_L05_004432E0 needs -g -frac2-qcopy -frac2-qcopy-barrier besides -G8, so it has a unit
   of its own (config/cflags.txt). */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector_L05_004432E0;

extern char *D_001B1EC4, *D_L05_001B251C;
extern int D_001A79F0;
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
extern int func_L05_00379F38(void);
extern float func_002702C8(float *velocity, float current, float goal, float a, float b, float c);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

#define FRAME_TIME 0.0166666675f /* 1/60 s */
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
void func_L05_004432E0(char *camera)
{
    Vector_L05_004432E0 motion;
    Vector_L05_004432E0 delta;
    char *record = *(char **)(camera + 0x70);
    char *moby = D_L05_001B251C
        + (*(int *)(*(char **)(D_001B1EC4 + *(short *)(camera + 0x84) * 32 + 0x1C) + 0x20) << 8);
    char *state = *(char **)(moby + 0x68);

    if (D_001A79F0 != 20) {
        float goal;
        if (*(int *)(state + 0x34)) {
            goal = (func_L05_00379F38() ? D_L05_001B1AC8 : D_L05_001B1AC4) * FRAME_TIME;
            *(float *)(state + 0x38) = func_002702C8((float *)(state + 0x3C),
                *(float *)(state + 0x38), goal, D_L05_001B1BF0, 0.2f, 0.0f);
        } else {
            goal = D_L05_001B1AC0 * FRAME_TIME;
            *(float *)(state + 0x38) = func_002702C8((float *)(state + 0x3C),
                *(float *)(state + 0x38), goal, D_L05_001B1BF4, 0.2f, 0.0f);
        }
    }
    func_00282D30(&motion, moby + 0xC0, *(float *)(state + 0x38));
    func_00282CC0(camera + 0x30, camera + 0x30, &motion);
    qzero_nc(record + 0x30);

    if (D_001A79F0 == 20) {
        char *input = *(char **)(camera + 0x70) + 0x50;
        float t = -*(float *)(input + 0x64) / (*(float *)(input + 0x74) * DEG_TO_RAD);
        float rise = (D_L05_001B1BD4 + (D_L05_001B1BD0 - D_L05_001B1BD4) * t) * FRAME_TIME;
        float sideLow = D_L05_001B1BDC, sideHigh = D_L05_001B1BD8;
        float side;
        *(float *)(camera + 0x38) += rise;
        *(float *)(record + 0x38) = rise;
        t = *(float *)(input + 0x68) / (*(float *)(input + 0x78) * DEG_TO_RAD);
        side = (sideLow + (sideHigh - sideLow) * t) * FRAME_TIME;
        func_00282D30(&delta, camera + 0x10, side);
        func_00282CC0(camera + 0x30, camera + 0x30, &delta);
        func_00282CC0(record + 0x30, record + 0x30, &delta);
    }

    if (D_001A79F0 == 15) {
        float oldHeight = *(float *)(camera + 0x38);
        float t = *(float *)(record + 0x40);
        float climb;
        if (func_L05_00379F38())
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
            float amount = func_00283CE0(*(short *)(roll + 6));
            amount = D_L05_001B1BE0 * func_00283198(amount * *(float *)(roll + 8) * 3.1415927f);
            if (*(short *)(roll + 4) == 1)
                amount = -amount;
            func_00282D30(&delta, camera + 0x10, amount);
            func_00282CC0(camera + 0x30, camera + 0x30, &delta);
            func_00282CC0(record + 0x30, record + 0x30, &delta);
        }
    }

    if (*(float *)(camera + 0x30) < 5.0f) *(float *)(camera + 0x30) = 5.0f;
    if (*(float *)(camera + 0x34) < 5.0f) *(float *)(camera + 0x34) = 5.0f;
    if (*(float *)(camera + 0x38) < 5.0f) *(float *)(camera + 0x38) = 5.0f;
    if (*(float *)(camera + 0x30) > 1000.0f) *(float *)(camera + 0x30) = 1000.0f;
    if (*(float *)(camera + 0x34) > 1000.0f) *(float *)(camera + 0x34) = 1000.0f;
    if (*(float *)(camera + 0x38) > 1000.0f) *(float *)(camera + 0x38) = 1000.0f;

    if (!func_L05_00379F38() && D_L05_00221D88) {
        int index = **(int **)(D_L05_00221D88 + 0x68);
        if (index >= 0) {
            char *sphere = D_L05_001B2614 + index * 128;
            float radius = func_00282DF0(sphere) - D_L05_001B1A7C;
            float distance;
            func_00282CF0(&delta, sphere + 0x30, camera + 0x30);
            distance = func_00282DF0(&delta);
            if (radius < distance) {
                func_00282F20(&delta, &delta, distance - radius);
                func_00282CC0(camera + 0x30, camera + 0x30, &delta);
            }
        }
    }
    *(Quad *)D_L05_001B3600 = *(Quad *)(camera + 0x30);
}
