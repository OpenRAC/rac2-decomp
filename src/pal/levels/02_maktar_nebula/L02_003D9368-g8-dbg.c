#include "include_asm.h"

#include "common.h"
extern float D_L02_001B01B8;
typedef int Vector __attribute__((mode(TI)));
extern float func_00282E48(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002AAA00(void *, float, float, float, float, void *, int);

int func_PAL_L02_003D9368(char *self) {
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float *p = position;
    char *state = *(char **)(self + 0x68);
    float angle = 1.15f;
    float distance;
    float height;
    float sine;
    float cosine;
    *(Vector *)position = *(Vector *)(self + 0x10);
    distance = func_00282E48(position, *(char **)(state + 0x30C) + 0x10);
    sine = func_00283180(angle);
    cosine = func_00283198(angle);
    height = D_L02_001B01B8 + distance * sine / cosine;
    p[2] = height - 4.2f;
    if (D_L02_001B01B8 + 5.0f < p[2])
        return 0;
    if (p[2] < D_L02_001B01B8 + 0.5f) {
        float scale = 4.7f / (p[2] - D_L02_001B01B8 + 4.2f);
        func_00282CF0(delta, self + 0x10, *(char **)(state + 0x30C) + 0x10);
        delta[2] = 0.0f;
        func_00282D30(delta, delta, scale);
        func_00282CC0(&position, &position, delta);
        func_002AA548(self + 0x10, state + 0x1B0, p[0], 0.036000002f, 0.036000002f, 3.0000002f);
        func_002AA548(self + 0x14, state + 0x1B4, p[1], 0.036000002f, 0.036000002f, 3.0000002f);
        func_002AAA00(self + 0xF8, func_00283248(*(float *)(*(char **)(state + 0x30C) + 0x10) - *(float *)(self + 0x10),
                         *(float *)(*(char **)(state + 0x30C) + 0x14) - *(float *)(self + 0x14)), 0.005026549f, 0.005026549f, 0.26529008f, state + 0x1C4, 0);
    } else {
        func_002AA548(self + 0x18, state + 0x1B8, p[2], 0.036000002f, 0.036000002f, 3.0000002f);
        func_002AAA00(self + 0xF8, func_00283248(*(float *)(*(char **)(state + 0x30C) + 0x10) - *(float *)(self + 0x10),
                         *(float *)(*(char **)(state + 0x30C) + 0x14) - *(float *)(self + 0x14)), 0.005026549f, 0.005026549f, 0.26529008f, state + 0x1C4, 0);
    }
    if (func_00282E48(self + 0x10, &position) < 0.0001f) {
        *(int *)(state + 0x1B8) = 0;
        return 2;
    }
    return 1;
}
