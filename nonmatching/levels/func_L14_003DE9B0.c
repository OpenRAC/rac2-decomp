/* Nonmatching prison rotation/color controller, 2026-10-28. No C credit.
 * Five bounded US checks, 0/1. Retained812/812B and exact frame0x30 with
 * -O2 -G0 -ffunction-sections. Explicit component temporaries give808B and
 * worse register roles; regrouped unsigned packed-color expression restores
 * 812B. Narrow block/edge controls and broad -fno-gcse produce byte-identical
 * complete diff logs to that form, so stop after three equivalent results.
 * Remaining: packed-color/index temporary roles, one branch/call preparation
 * instruction, rotation predicate and common-tail scheduling. No option
 * retained. Reopen only with independent original expression/scope evidence.
 *
 * Actual definitions confirm int B3868/ACBC8, void A7750/B4090/3294F0 and
 * the three-FP/two-pointer pose helper contract. B4090 reads a complete16B
 * point; the local is whole-copied before Z modification, never shortened
 * to XYZ. Raw833F0 loads16B Euler input and writes three16B orientation
 * rows; its void interface remains a raw-only hypothesis, separate from
 * the proven memory extents. Globals remain incomplete; the object table
 * uses one canonical GP pointer. Unsigned shifts preserve packed color bits
 * without signed-shift overflow, and counter increment explicitly preserves
 * the observed low32 wrap before signed modulo150 and float conversion.
 * The default state path still runs the common pulse counter as retail does.
 */

#include "common.h"
extern unsigned char *D_L14_001B259C SDATA(D_L14_001B259C);
extern unsigned char D_00189EA0[], D_L14_001A8F20[];
extern void func_002A7750(void *, int, int);
extern float func_00282E48(const void *, const void *), func_00283198(float);
extern int func_002ACBC8(const void *, int), func_002B3868(void *);
extern void func_002B4090(void *, const void *, float, float, float);
extern void func_002833F0(void *, const void *), func_L00_003294F0(void *, int);

void func_L14_003DE9B0(unsigned char *object)
{
    float point[4] __attribute__((aligned(16)));
    unsigned char *state = *(unsigned char **)(object + 0x68);
    int base, shade, tick;
    switch (object[0x20]) {
    case 0:
        if (*(int *)state >= 0) {
            *(unsigned char **)(state + 0x10) = D_L14_001B259C + *(int *)state * 256;
            *(unsigned int *)(object + 0x78) = 0x80404040;
            *(unsigned short *)(object + 0x34) |= 0x10;
            *(int *)(state + 0x14) = 0;
        } else *(void **)(state + 0x10) = 0;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        base = *(int *)(state + 0x18);
        *(unsigned int *)(object + 0x78) = ((unsigned int)base << 16) | (((unsigned int)base << 8) | 0x80000000U) | (unsigned int)base;
        if (*(int *)(state + 0xC) == -1) {
            if (func_00282E48(D_00189EA0, object + 0x10) < 10.0f) func_002A7750(object, 2, -1);
        } else if (func_002ACBC8(D_00189EA0, *(int *)(state + 0xC))) func_002A7750(object, 2, -1);
        break;
    case 2:
        if (func_002B3868(object)) *(int *)(state + 0x1C) = 100;
        if (*(int *)(state + 0x1C)) --*(int *)(state + 0x1C);
        base = *(int *)(state + 0x18);
        shade = (int)((float)base * (float)*(int *)(state + 0x1C) * 0.01f);
        *(unsigned int *)(object + 0x78) = ((unsigned int)shade << 16) | (((unsigned int)shade << 8) | 0x80000000U) | (unsigned int)base;
        if ((*(float *)(object + 0xF8) >= 3.1415927410125732f && !*(int *)(state + 8)) ||
            (*(float *)(object + 0xF4) <= -3.1415927410125732f && *(int *)(state + 8))) {
            func_002A7750(object, 3, -1);
            break;
        }
        if (*(int *)(state + 8)) *(float *)(object + 0xF4) -= *(float *)(state + 4);
        else *(float *)(object + 0xF8) += *(float *)(state + 4);
        if (*(void **)(state + 0x10)) {
            qcopy(point, D_L14_001A8F20);
            point[2] -= 0.5f;
            func_002B4090(*(void **)(state + 0x10), point, *(float *)(state + 4), 0.0f, 0.0f);
            {
                unsigned char *bound = *(unsigned char **)(state + 0x10);
                func_002833F0(bound + 0xC0, bound + 0xF0);
            }
        }
        break;
    case 3:
        if (func_002B3868(object)) {
            *(float *)(object + 0xF8) = 3.1415927410125732f;
            if (*(void **)(state + 0x10)) func_L00_003294F0(*(void **)(state + 0x10), 1);
        }
        *(unsigned int *)(object + 0x78) = (unsigned int)*(int *)(state + 0x18) | 0x80000000U;
        break;
    }
    tick = (int)((unsigned int)*(int *)(state + 0x14) + 1U);
    *(int *)(state + 0x14) = tick;
    *(int *)(state + 0x18) = (int)(func_00283198((float)(tick % 150) * 0.041887905448675156f) * 48.0f) + 80;
}
