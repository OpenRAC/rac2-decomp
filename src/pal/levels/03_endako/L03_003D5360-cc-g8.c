/* func_PAL_L03_003D5360, the PAL copy of func_L03_003D11E0: the same C, where rename func_00273730 becomes func_PAL_002735D0; expr 0.016666668f becomes 0.020000001f; wrap func_002A7820(D_L03_001B0638, D_L03_001B0638_1[1]) (((i; rename func_002C16C0 becomes func_PAL_002C23B8. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L03_001B0610 __attribute__((sda)), D_L03_001B05F8 __attribute__((sda)), D_L03_001B05F0 __attribute__((sda)), D_L03_001B0600 __attribute__((sda)), D_L03_001B0608 __attribute__((sda));
extern float D_L03_001B0614 __attribute__((sda)), D_L03_001B0618 __attribute__((sda));
extern int D_L03_001B061C __attribute__((sda));
extern float D_L03_001B0628 __attribute__((sda)), D_L03_001B0620 __attribute__((sda));
extern int D_L03_001B0630 __attribute__((sda)), D_L03_001B0638 __attribute__((sda));
extern float D_L03_001B0640 __attribute__((sda));
/* Each upper bound is the second word of its measured min/max pair.
 * The scalar lower bounds use GP loads; these views keep the upper loads absolute. */
extern float D_L03_001B05F0_1[] MACRO_ADDR, D_L03_001B0600_1[] MACRO_ADDR, D_L03_001B0608_1[] MACRO_ADDR, D_L03_001B0628_1[] MACRO_ADDR, D_L03_001B0620_1[] MACRO_ADDR;
extern int D_L03_001B0630_1[] MACRO_ADDR, D_L03_001B0638_1[] MACRO_ADDR;
extern char D_L03_001FF5C0[];
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern char *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, int, float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern int math_random_int_range(int, int), math_random_int_below(int);
extern char *func_PAL_002C23B8(void *, void *, int, int, int, int, float, float, float, float, float);

/* Emits twelve objects followed by the configured randomized particle burst. */
void func_PAL_L03_003D5360(char *obj)
{
    float velocityOffset[4], vector[4], particleVector[4], verticalVelocity[4];
    float angle, radius, f, g;
    int color, alpha, count;
    char *spawn, *particle;

    vec_scale_to_length(velocityOffset, obj + 0xc0, -(D_L03_001B0610*(0.020000001f)));
    { int i = 0; float f, g;
    do {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, D_L03_001B05F8)*(0.020000001f);
        vector[0] = math_fast_sin_or_cos_a(angle)*radius;
        vector[1] = math_fast_sin_or_cos_b(angle)*radius;
        vector[2] = 0.0f;
        vector[2] = math_random_float_range(D_L03_001B05F0, D_L03_001B05F0_1[1])*(0.020000001f);
        FastVecAdd(vector, vector, velocityOffset);
        f = math_random_float_range(D_L03_001B0600, D_L03_001B0600_1[1]);
        g = math_random_float_range(D_L03_001B0608, D_L03_001B0608_1[1]);
        spawn = func_PAL_002735D0(obj, 2, *(short *)(obj + 0xaa), i, obj + 0x10, obj + 0xf0, vector, 255, f, g);
        { char *state = *(char **)(spawn + 0x68);
        float life = D_L03_001B0618*(0.020000001f);
        *(float *)(state + 0x38) = D_L03_001B0614;
        *(float *)(state + 0x3c) = life; }
        i++;
    } while (i < 12);
    }
    { int i;
    for (i = 0;i<D_L03_001B061C;i++) {
        char *context = D_L03_001FF5C0;
        *(TI128 *)particleVector = 0;
        particleVector[0] = math_random_signed_float_range(0.0f, 0.5f);
        particleVector[1] = math_random_signed_float_range(0.0f, 1.4f);
        particleVector[2] = math_random_float_range(0.3f, 1.5f);
        *(TI128 *)(vector) = *(TI128 *)(particleVector);
        matrix_mul_vec3(vector, vector, obj + 0xc0);
        FastVecAdd(vector, vector, obj + 0x10);
        f = math_random_float_range(D_L03_001B0628, D_L03_001B0628_1[1])*210000.0f;
        g = math_random_float_range(D_L03_001B0620, D_L03_001B0620_1[1])*0.00040000002f;
        angle = math_random_float_range(0.0f, 1.0f);
        color = FastTweenColor(D_L03_001B0630, D_L03_001B0630_1[1], angle);
        alpha = color>>24;
        count = (((int)(math_random_int_range(D_L03_001B0638, D_L03_001B0638_1[1])) * 5 + 2) / 6);
        *(TI128 *)verticalVelocity = 0;
        verticalVelocity[2] = math_random_float_range(0.0f, D_L03_001B0640*(0.020000001f));
        *(TI128 *)(particleVector) = *(TI128 *)(verticalVelocity);
        color&=0xffffff;
        particle = func_PAL_002C23B8(vector, particleVector, count, alpha, color, math_random_int_below(3)-1, f, 500.0f, 1.0f, g, 0.0f);
        if (particle) {
            u8 type = **(u8 **)(context + 0x5c);
            particle[3] = 0x44;
            particle[2] = type;
        }
    }
    }
}
