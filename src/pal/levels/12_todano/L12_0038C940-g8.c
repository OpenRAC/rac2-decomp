#include "include_asm.h"
#include "names.h"

typedef int Quadword89F80 __attribute__((mode(TI)));
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_set_state(void *, int, int);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern int moby_is_state_two(char *);
extern char *ref_L12_00389F80_00 __attribute__((sda));
extern char *ref_L12_00389F80_01;
extern float ref_L12_00389F80_02 __attribute__((sda));
extern float ref_L12_00389F80_03 __attribute__((sda));

/* Per-state step of a homing object: state 0 starts it, state 1 steers it by the thing it
   follows (or just turns it) and then spins a short delay loop. */
void func_PAL_L12_0038CD10(char *object) {
    char *state = *(char **)(object + 0x68);
    float a[4];
    float b[4];
    float c[4];
    float dot;
    int i;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned int *)(state + 0x5C) |= 4;
        *(short *)(object + 0x7C) = 3;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (*(int *)(state + 0xE0) == -1 ||
            moby_is_state_two(ref_L12_00389F80_00 + (*(int *)(state + 0xE0) << 8)) == 0) {
            vec_scale_to_length(state + 0x30, object + 0xD0, -(ref_L12_00389F80_02 * 0.020000001f));
            *(float *)(object + 0x48) = ref_L12_00389F80_03;
        } else {
            moby_transform_point_and_rotation_by_parent(object, ref_L12_00389F80_01 + (*(int *)(state + 0xE0) << 8), object + 0x10,
                          object + 0xF0, a, b);
            a[2] = 0.0f;
            FastVecSub(c, a, object + 0x10);
            *(Quadword89F80 *)a = *(Quadword89F80 *)c;
            a[2] = 0.0f;
            b[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8) + 4.7123895f);
            b[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8) + 4.7123895f);
            b[2] = 0.0f;
            dot = FastVecDot(a, b);
            c[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8)) * dot * 0.1f;
            c[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8)) * dot * 0.1f;
            c[2] = 0.0f;
            mat_combine_and_store(state + 0x20, c, object + 0xF0, object + 0xF0);
            *(float *)(object + 0x48) = dot * 49.999996f;
        }
        i = 6;
        while (--i >= 0)
            ;
        break;
    }
}
