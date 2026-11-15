#include "include_asm.h"
#include "names.h"

typedef int V4_L00_004170A8 __attribute__((mode(TI)));
extern char g_spark_l00_records[];
extern V4_L00_004170A8 D_L00_001BF220;
extern int math_fast_float_d(void *);
extern void func_PAL_L00_0041C528(char *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void func_PAL_L00_0041CBB8(char *, void *, int);
extern void spark_records_update(char *);
extern void func_PAL_L00_0041C390(char *);
extern void func_PAL_L00_0041C878(char *);
extern void moby_mark_spawned(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);

void func_PAL_L00_0041C220(char *object)
{
    char *state = *(char **)(object + 0x68);
    V4_L00_004170A8 local;
    float a, b;
    int i;
    char *p;
    if (math_fast_float_d(state) == 0) {
        if (*(int *)(state + 4) == 0)
            func_PAL_L00_0041C528(object);
        if (*(int *)(state + 4) == 0) {
            a = math_random_angle();
            b = math_random_angle();
            vec_build_spherical_offset(&local, 7.0f, a, b);
        } else {
            a = math_random_angle();
            b = math_random_angle();
            vec_build_spherical_offset(&local, 5.0f, a, b);
        }
        FastVecAdd(&local, &local, object + 0x10);
        if (CollLine(object + 0x10, &local, 0, object, 0) != 0)
            local = D_L00_001BF220;
        func_PAL_L00_0041CBB8(object, &local, 17);
        spark_records_update(object);
        ref_L00_004170A8_00(func_PAL_L00_0041C878, object);
    } else {
        p = g_spark_l00_records;
        p += 0x106C;
        for (i = 23; i >= 0; --i, p -= 0xB0)
            *(int *)p = 0;
        if (*(int *)(state + 4) == 0)
            func_PAL_L00_0041C390(object);
        moby_mark_spawned(object);
    }
}

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_range(int, int);
extern void ref_L00_00417868_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_00417868_01(void *, int, void *, int);

void func_PAL_L00_0041C9E0(char *object, char *state) {
    CurveVector points[25];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 24; i++) {
        t = IntToFloat(i) / IntToFloat(23);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        FastVecAdd(&start, &start, state + 0x20);
        FastVecAdd(&end, &end, state + 0x30);
        ref_L00_00417868_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = math_random_float_range(-1.0f, 1.0f);
        jitter.values[1] = math_random_float_range(-1.0f, 1.0f);
        jitter.values[2] = math_random_float_range(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 8)
        ref_L00_00417868_01(object, math_random_int_range(0x40, 0x80), points, 25);
    else
        ref_L00_00417868_01(object, math_random_int_range(0, 0x40), points, 25);
}
