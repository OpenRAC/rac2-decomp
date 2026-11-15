#include "include_asm.h"
#include "common.h"

typedef int MovingEffectWord128 __attribute__((mode(TI)));
typedef union { MovingEffectWord128 word; float values[4]; } MovingEffectVector;
extern int func_002B4038(int, int);
extern void func_0029F338(void *);
extern void func_00300190(void *, void *);
extern void func_L00_003F5660(char *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern void func_L00_003F5750(char *, void *);
extern void func_L00_003F6900(char *, void *);
extern int func_L00_003F5238(char *, void *);
extern int func_00282948(void *);

void func_L00_003F4EC8(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    MovingEffectVector previous, point;
    int i;
    float *position;
    if (!func_002B4038(0xC04, *(short *)(state + 0x1A))) {
        func_0029F338(object);
        return;
    }
    switch ((unsigned char)object[0x20]) {
    case 2:
        func_00300190(object + 0x10, object + 0x10);
        func_L00_003F5660(object);
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
        func_L00_003F5750(object, &point);
    }
    func_L00_003F6900(object, position);
    lerp_vector(&point, &previous, position, 0.5f);
    func_L00_003F6900(object, &point);
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
    } else if (func_L00_003F5238(object, &previous) || func_00282948(state + 0x10)) {
        object[0x20] = 2;
    } else {
        func_L00_003F5660(object);
    }
    break;
    }
}
