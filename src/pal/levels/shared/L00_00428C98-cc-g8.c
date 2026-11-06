/* func_PAL_L00_00428C98, the PAL copy of func_L00_004237C8: the same C, where wrap D_L00_001B14B4 (({e}) * 1.2f). */
#include "common.h"

extern char D_00189E20[];
typedef union { unsigned char b[0x2600]; int i[0x980]; } Hero;
extern float D_00138280 NOT_SDA;
extern float D_L00_001B14B4 __attribute__((sda));
extern float D_L00_001B14C8 __attribute__((sda));
extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282C48(float);
extern void func_00282D30(void *, void *, float);

int func_PAL_L00_00428C98(char *object, void *input, int constrained, int preserve)
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
    if (((Hero *)D_00189E20)->b[0x22B4] != 2) {
        if (func_00282C48(D_00138280) > 0.05f && preserve) {
            length -= ((D_L00_001B14B4) * 1.2f);
            *(short *)(controller + 0x34) = 0x719;
        }
    }
    if (!constrained && ((Hero *)D_00189E20)->i[0x229C / 4] != 2) {
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
            length = D_L00_001B14C8;
        } else {
            func_00282D30(vector, vector, limit / length);
            length = D_L00_001B14C8;
        }
    }
    *(float *)(controller + 0x30) = *(float *)(vector + 0x2C) - length;
    return 1;
}