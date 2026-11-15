#include "names.h"
/* Samples a keyframe track at time t with keys every step: the key index (clamped to
   the track, with the fraction zeroed at either end) goes to *idx and the fraction past
   it to *frac, and *out gets the key or the blend toward the next one. Retail compiles
   this with -g (the nop pair before div.s). */
typedef int TI128_2C96F8 __attribute__((mode(TI)));
typedef struct {
    int count;
    int pad4[3];
    float keys[1][4];
} KeyTrack2C96F8;
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_002C96F8(float time, float step, KeyTrack2C96F8 *track, int *keyIndex, float *fraction, float *result)
{
    float delta[4];
    int i;

    i = FloatToInt(time / step);
    *keyIndex = i;
    if (i >= track->count - 1) {
        *keyIndex = track->count - 1;
        *fraction = 0.0f;
        *(TI128_2C96F8 *)result = *(TI128_2C96F8 *)track->keys[*keyIndex];
    } else if (i < 0) {
        *keyIndex = 0;
        *fraction = 0.0f;
        *(TI128_2C96F8 *)result = *(TI128_2C96F8 *)track->keys[*keyIndex];
    } else {
        *fraction = time - IntToFloat(i) * step;
        FastVecSub(delta, track->keys[*keyIndex + 1], track->keys[*keyIndex]);
        *(TI128_2C96F8 *)result = *(TI128_2C96F8 *)delta;
        vec_scale_to_length(result, result, *fraction);
        FastVecAdd(delta, result, track->keys[*keyIndex]);
        *(TI128_2C96F8 *)result = *(TI128_2C96F8 *)delta;
    }
}
