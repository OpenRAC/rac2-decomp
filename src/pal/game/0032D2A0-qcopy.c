#include "include_asm.h"

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7AE0(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern void func_0032BE30(void *, int, void *, int);

void func_PAL_0032D408(char *object, char *state) {
    CurveVector points[25];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 24; i++) {
        t = func_00283CE0(i) / func_00283CE0(23);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        func_00282CC0(&start, &start, state + 0x20);
        func_00282CC0(&end, &end, state + 0x30);
        func_002A7AE0(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = func_002A7878(-1.0f, 1.0f);
        jitter.values[1] = func_002A7878(-1.0f, 1.0f);
        jitter.values[2] = func_002A7878(-1.0f, 1.0f);
        func_00282F20(&jitter, &jitter, 0.075f);
        func_00282CC0(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 8)
        func_0032BE30(object, func_002A7820(0x40, 0x80), points, 25);
    else
        func_0032BE30(object, func_002A7820(0, 0x40), points, 25);
}
