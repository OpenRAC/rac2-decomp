#include "include_asm.h"


#include "common.h"
typedef int MovingEffectWord128 __attribute__((mode(TI)));
typedef union { MovingEffectWord128 word; float values[4]; } MovingEffectVector;
extern int save_is_record_value(int, int);
extern void moby_mark_spawned(void *);
extern void vec_transform_or_copy(void *, void *);
extern void vaporizer_update_passes(char *);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void lerp_vector(void *, void *, void *, float);
extern void vaporizer_add_chain_joint_pal(char *, void *);
extern void func_PAL_L00_003FAD60(char *, void *);
extern int vaporizer_bolt_test_hit_pal(char *, void *);
extern int math_fast_float_d(void *);

void vaporizer_bolt_update_pal(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    MovingEffectVector previous, point;
    int i;
    float *position;
    if (!save_is_record_value(0xC04, *(short *)(state + 0x1A))) {
        moby_mark_spawned(object);
        return;
    }
    switch ((unsigned char)object[0x20]) {
    case 2:
        vec_transform_or_copy(object + 0x10, object + 0x10);
        vaporizer_update_passes(object);
        break;
    default:
    if (*(int *)(state + 0x28) == 1)
        qcopy(&previous,state + 0x40);
    else
        qcopy(&previous,object + 0x10);
    position = (float *)(object + 0x10);
    FastVecAdd(position, position, state);
    if (*(int *)(state + 0x28) == 1)
        FastVecAdd(state + 0x40, state + 0x40, state + 0x30);
    if ((unsigned char)object[0x20] == 0)
        object[0x20] = 1;
    for (i = 0; i < 4; i++) {
        lerp_vector(&point, &previous, position, IntToFloat(i) * 0.25f);
        vaporizer_add_chain_joint_pal(object, &point);
    }
    func_PAL_L00_003FAD60(object, position);
    lerp_vector(&point, &previous, position, 0.5f);
    func_PAL_L00_003FAD60(object, &point);
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        if (*(float *)(object + 0x10) < 5.0f) *(float *)(object + 0x10) = 5.0f;
        if (*(float *)(object + 0x14) < 5.0f) *(float *)(object + 0x14) = 5.0f;
        if (*(float *)(object + 0x18) < 5.0f) *(float *)(object + 0x18) = 5.0f;
        {
            float hi = 1016.0f;
            if (*(float *)(object + 0x10) > hi) *(float *)(object + 0x10) = hi;
            if (*(float *)(object + 0x14) > hi) *(float *)(object + 0x14) = hi;
            if (*(float *)(object + 0x18) > hi) *(float *)(object + 0x18) = hi;
        }
        object[0x20] = 2;
    } else if (vaporizer_bolt_test_hit_pal(object, &previous) || math_fast_float_d(state + 0x10)) {
        object[0x20] = 2;
    } else {
        vaporizer_update_passes(object);
    }
    break;
    }
}

