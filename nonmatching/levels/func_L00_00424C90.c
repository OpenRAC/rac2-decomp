/* func_L00_00424C90 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G0 -ffunction-sections.
 * Measured in src/levels/shared/L00_00424C90.c: 540/544 bytes.
 * US: 0/27 local places; PAL: 0/27 local places; US2: 0/27 local places.
 * No strict linked build was run because no local placement matched.
 * The compiler folds the up-vector offset into its symbol relocation; retail constructs the base separately before adding 0x20. Plain, sda, MACRO_ADDR, mno-split-addresses and the coordinator partial-basis control did not close it. Reopen with independent base lifetime evidence.
 */

#include "common.h"

extern char D_L00_001B8E20[];
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_002831B0(float);
extern float func_00283BE0(float, float);
extern float func_00282C48(float);
extern float func_002A7AA8(float, float, float, float, float);

float func_L00_00424C90(char *object, float *vector, float threshold)
{
    float temporary[4] __attribute__((aligned(16)));
    float first[4] __attribute__((aligned(16)));
    float second[4] __attribute__((aligned(16)));
    float cross[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x70);
    char *output = state + 0x1C0;
    char *direction = state + 0x160;
    char *up = D_L00_001B8E20 + 0x20;
    float dot;
    float length;
    float angle;
    float signed_angle = 0.0f;
    float sign;
    float factor;
    func_00282D30(temporary, up, func_00282DB0(vector, up));
    func_00282CF0(first, vector, temporary);
    func_00282D30(temporary, up, func_00282DB0(direction, up));
    func_00282CF0(second, direction, temporary);
    dot = func_00282DB0(first, second);
    length = func_00282DF0(first);
    if (length == 0.0f) return 0.0f;
    length *= func_00282DF0(second);
    if (length == 0.0f) return 0.0f;
    angle = 1.57079632679f - func_002831B0(dot / length);
    sign = -1.0f;
    func_00282DD8(cross, first, up);
    if (func_00282DB0(cross, second) >= 0.0f) sign = 1.0f;
    signed_angle = func_00283BE0(3.14159265359f, angle);
    if (threshold != 0.0f && func_00282C48(signed_angle) > threshold) return signed_angle;
    factor = func_002A7AA8(-1.0f, 0.0f, 1.0f, 0.0f, signed_angle * 0.63661975f);
    if (factor > 1.0f) factor = 1.0f;
    *(float *)(output + 0x1C) = factor * sign;
    return signed_angle;
}