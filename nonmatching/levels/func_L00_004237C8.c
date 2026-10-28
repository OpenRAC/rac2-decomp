/* func_L00_004237C8 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * Measured in src/levels/shared/L00_004237C8-g8.c: 480/480 bytes.
 * US: 0/27 local places; PAL: ABSENT; US2: 0/27 local places.
 * No strict linked build was run because no local placement matched.
 * The hero base split, mixed global access forms and float branch/store scheduling differ. Reopen with a qualified partial hero view and actual lifetime evidence.
 */

#include "common.h"

extern char D_00189E20[];
extern float D_00138280 NOT_SDA;
extern float D_L00_001B14B4 __attribute__((sda));
extern float D_L00_001B14C8 __attribute__((sda));
extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282C48(float);
extern void func_00282D30(void *, void *, float);

int func_L00_004237C8(char *object, void *input, int constrained, int preserve)
{
    char *state = *(char **)(object + 0x70);
    char *vector = state + 0x160;
    char *controller = state + 0x1F0;
    char *transform = state + 0x60;
    float old_length = func_00282DF0(vector);
    float length;
    float limit;
    func_00282CF0(vector, input, state + 0xB0);
    if (*(short *)(controller + 0x38)) {
        func_00282F20(vector, vector, *(float *)(vector + 0x2C) - *(float *)(controller + 0x30));
        return preserve;
    }
    length = func_00282DF0(vector);
    if (*(unsigned char *)(D_00189E20 + 0x22B4) != 2) {
        if (func_00282C48(D_00138280) > 0.05f && preserve) {
            *(short *)(controller + 0x34) = 0x884;
            length -= D_L00_001B14B4;
        }
    }
    if (!constrained && *(int *)(D_00189E20 + 0x229C) != 2) {
        if (old_length < length) {
            func_00282D30(vector, vector, old_length / length);
            *(float *)(controller + 0x30) = *(float *)(vector + 0x2C) - old_length;
            return preserve;
        }
    }
    limit = D_L00_001B14C8;
    if (length < limit) {
        if (length <= 0.0001f) {
            func_00282F20(vector, *(char **)(transform + 0xC0) + 0xC0, -limit);
        } else {
            func_00282D30(vector, vector, limit / length);
        }
        length = D_L00_001B14C8;
        *(float *)(controller + 0x30) = *(float *)(vector + 0x2C) - length;
        return 1;
    }
    *(float *)(controller + 0x30) = *(float *)(vector + 0x2C) - length;
    return preserve;
}