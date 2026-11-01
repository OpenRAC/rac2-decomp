#include "include_asm.h"

typedef int V4_L00_004170A8 __attribute__((mode(TI)));
extern char D_L00_0025A920[];
extern V4_L00_004170A8 D_L00_001BF220;
extern int func_00282948(void *);
extern void func_PAL_L00_0041C528(char *);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_PAL_L00_0041CBB8(char *, void *, int);
extern void func_L00_00417D70(char *);
extern void func_PAL_L00_0041C390(char *);
extern void func_PAL_L00_0041C878(char *);
extern void func_0029F338(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);

void func_PAL_L00_0041C220(char *object)
{
    char *state = *(char **)(object + 0x68);
    V4_L00_004170A8 local;
    float a, b;
    int i;
    char *p;
    if (func_00282948(state) == 0) {
        if (*(int *)(state + 4) == 0)
            func_PAL_L00_0041C528(object);
        if (*(int *)(state + 4) == 0) {
            a = func_002A7940();
            b = func_002A7940();
            func_002AF000(&local, 7.0f, a, b);
        } else {
            a = func_002A7940();
            b = func_002A7940();
            func_002AF000(&local, 5.0f, a, b);
        }
        func_00282CC0(&local, &local, object + 0x10);
        if (func_002761F8(object + 0x10, &local, 0, object, 0) != 0)
            local = D_L00_001BF220;
        func_PAL_L00_0041CBB8(object, &local, 17);
        func_L00_00417D70(object);
        ref_L00_004170A8_00(func_PAL_L00_0041C878, object);
    } else {
        p = D_L00_0025A920;
        p += 0x106C;
        for (i = 23; i >= 0; --i, p -= 0xB0)
            *(int *)p = 0;
        if (*(int *)(state + 4) == 0)
            func_PAL_L00_0041C390(object);
        func_0029F338(object);
    }
}

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern void ref_L00_00417868_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_00417868_01(void *, int, void *, int);

void func_PAL_L00_0041C9E0(char *object, char *state) {
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
        ref_L00_00417868_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = func_002A7878(-1.0f, 1.0f);
        jitter.values[1] = func_002A7878(-1.0f, 1.0f);
        jitter.values[2] = func_002A7878(-1.0f, 1.0f);
        func_00282F20(&jitter, &jitter, 0.075f);
        func_00282CC0(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 8)
        ref_L00_00417868_01(object, func_002A7820(0x40, 0x80), points, 25);
    else
        ref_L00_00417868_01(object, func_002A7820(0, 0x40), points, 25);
}
