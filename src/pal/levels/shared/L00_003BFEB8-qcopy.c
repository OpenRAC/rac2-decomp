#include "include_asm.h"

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern void ref_L00_003BC228_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_003BC228_01(void *, int, void *, int);

void func_PAL_L00_003BFEB8(char *object, char *state) {
    CurveVector points[17];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 16; i++) {
        t = func_00283CE0(i) / func_00283CE0(15);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        func_00282CC0(&start, &start, state + 0x20);
        func_00282CC0(&end, &end, state + 0x30);
        ref_L00_003BC228_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = func_002A7878(-0.5f, 0.5f);
        jitter.values[1] = func_002A7878(-0.5f, 0.5f);
        jitter.values[2] = func_002A7878(-0.5f, 0.5f);
        func_00282F20(&jitter, &jitter, 0.075f);
        func_00282CC0(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x88) >= 8)
        ref_L00_003BC228_01(object, func_002A7820(0x40, 0x80), points, 17);
    else
        ref_L00_003BC228_01(object, func_002A7820(0, 0x40), points, 17);
}
