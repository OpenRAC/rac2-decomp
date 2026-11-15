#include "names.h"
/* func_PAL_L00_00428C98, the PAL copy of func_L00_004237C8: the same C, where wrap D_L00_001B14B4 (({e}) * 1.2f). */
#include "common.h"

extern char g_hero_state[];
typedef union { unsigned char b[0x2600]; int i[0x980]; } Hero;
extern float D_00138280 NOT_SDA;
extern float D_L00_001B14B4 __attribute__((sda));
extern float D_L00_001B14C8 __attribute__((sda));
extern float FastVecLength(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fabs(float);
extern void FastVecScale(void *, void *, float);

int func_PAL_L00_00428C98(char *object, void *input, int constrained, int preserve)
{
    char *state = *(char **)(object + 0x70);
    char *vector = state + 0x160;
    char *controller = state + 0x1F0;
    char *transform = state + 0x60;
    float old_length = FastVecLength(vector);
    float length;
    float limit;
    FastVecSub(vector, input, state + 0xB0);
    if (*(short *)(controller + 0x38)) {
        vec_scale_to_length(vector, vector, *(float *)(vector + 0x2C) - *(float *)(controller + 0x30));
        return preserve;
    }
    length = FastVecLength(vector);
    if (((Hero *)g_hero_state)->b[0x22B4] != 2) {
        if (math_fabs(D_00138280) > 0.05f && preserve) {
            length -= ((D_L00_001B14B4) * 1.2f);
            *(short *)(controller + 0x34) = 0x719;
        }
    }
    if (!constrained && ((Hero *)g_hero_state)->i[0x229C / 4] != 2) {
        if (old_length < length) {
            FastVecScale(vector, vector, old_length / length);
            *(float *)(controller + 0x30) = *(float *)(vector + 0x2C) - old_length;
            return preserve;
        }
    }
    limit = D_L00_001B14C8;
    if (length < limit) {
        if (length <= 0.0001f) {
            vec_scale_to_length(vector, *(char **)(transform + 0xC0) + 0xC0, -limit);
            length = D_L00_001B14C8;
        } else {
            FastVecScale(vector, vector, limit / length);
            length = D_L00_001B14C8;
        }
    }
    *(float *)(controller + 0x30) = *(float *)(vector + 0x2C) - length;
    return 1;
}