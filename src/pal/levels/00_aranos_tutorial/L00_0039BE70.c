#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_0039BE70, level 00's copy of func_PAL_0030FB38: the same C. */
extern char *part_find_owned_effect_slot(char *, int, int);
extern int math_fast_float_d(int *);
extern int PlayMobySound(int, int, char *);
extern void func_PAL_002AC290(char *, char *);
extern void vec_add_random_offset(float *, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_PAL_002AC3C0(char *, char *);

void func_PAL_L00_0039BE70(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit = part_find_owned_effect_slot(object, 0x30001, 0);
    float direction[4];

    math_fast_float_d((int *)(state + 0x28));
    math_fast_float_d((int *)(state + 0x2C));
    if (hit != 0 && (*(int *)(hit + 0x20) != *(int *)(state + 0x34) ||
                     *(int *)(state + 0x28) == 0)) {
        *(int *)(state + 0x34) = *(int *)(hit + 0x20);
        *(int *)(state + 0x28) = 25;
        if (*(int *)(state + 0x2C) == 0) {
            if (*(unsigned short *)(hit + 0x28) == 0x101 && *(int *)(state + 0x30) == 0) {
                *(int *)(state + 0x2C) = 83;
                *(int *)(state + 0x30) = 1;
            } else {
                *(int *)(state + 0x30) = 0;
            }
        }
        PlayMobySound(0, 0, object);
        *(float *)(state + 0x24) -= *(float *)(hit + 0x2C);
        func_PAL_002AC290(object, state);
        if (*(float *)(state + 0x24) < 0.0f) {
            vec_add_random_offset(direction, 0.6f);
            func_PAL_002AC718(object, direction, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            object[0x20] = 6;
        }
    }
    ((unsigned char *)object)[0xA8] = 0xFF;
    func_PAL_002AC3C0(object, state);
}

/* func_PAL_L00_0039C018, level 00's copy of func_PAL_0030FCE8. */


extern char g_hero_state[];
extern char ref_PAL_L00_0039C018_00[];

extern void moby_get_facing_direction(char *, float *);
extern void FastVecSub(float *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(float *, float *, float);
extern float FastVecDot(float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int CollLine(float *, float *, int, int, int);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern int moby_move_and_collide(char *, float *, float, float, float, int);

void func_PAL_L00_0039C018(char *obj)
{
    char *e = *(char **)(obj + 0x68);
    char *d = g_hero_state;
    short flag = *(short *)(d + 0x202);
    float v0[4] __attribute__((aligned(16)));
    float v1[4] __attribute__((aligned(16)));
    float v2[4] __attribute__((aligned(16)));
    float v3[4] __attribute__((aligned(16)));
    float v4[4] __attribute__((aligned(16)));
    float v5[4] __attribute__((aligned(16)));
    float v6[4] __attribute__((aligned(16)));
    float v7[4] __attribute__((aligned(16)));
    float v8[4] __attribute__((aligned(16)));
    float v9[4] __attribute__((aligned(16)));
    float f;
    float projection;
    int mode;
    float l3, l2, step, acc, x;

    if (*(int *)(e + 0x44) == 0 && flag == 0)
        return;
    moby_get_facing_direction(obj + 0x10, v0);
    acc = 0.0f;
    FastVecSub(v1, obj + 0x10, d + 0x80);
    projection = FastVecDot(v1, v0);
    FastVecScale(v3, v0, projection);
    FastVecSub(v2, v1, v3);
    l3 = FastVecLength(v3);
    l2 = FastVecLength(v2);
    FastVecScale(v4, v0, -2.5f);
    FastVecAdd(v4, obj + 0x10, v4);
    FastVecScale(v5, v0, 0.5f);
    FastVecAdd(v5, obj + 0x10, v5);
    if (CollLine(v5, v4, 2, 0, 0)) {
        qcopy(v6, ref_PAL_L00_0039C018_00);
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        FastVecSub(v8, v6, obj + 0x10);
        projection = FastVecDot(v8, v0);
        FastVecScale(v7, v0, projection);
        acc = FastVecLength(v7);
    }
    if (*(int *)(e + 0x44) == 0) {
        if (!(l2 < 1.0f))
            return;
        if (!(l3 < 1.3f))
            return;
        *(int *)(e + 0x44) = 1;
    }
    qcopy(v8, v2);
    f = l2 - 1.4f;
    if (f > 0.0f)
        f = 0.0f;
    if (flag == 0)
        f = 0.0f;
    math_spring_float_to_goal(&f, 0.0f, (float *)(e + 0x48), 0.0288000014f, 0.432000041f, 0.080000006f);
    if (f == 0.0f && *(float *)(e + 0x48) == 0.0f && acc < 0.02f)
        *(int *)(e + 0x44) = 0;
    if (l2 < *(float *)(e + 0x48))
        *(float *)(e + 0x48) = l2;
    if (*(float *)(e + 0x48) < l2)
        vec_scale_to_length(v8, v8, *(float *)(e + 0x48));
    moby_move_and_collide(obj, v8, 0.5f, 0.4f, 0.0f, 0);
    if (mode == 0) {
        if (FastVecDot(v7, v0) > 0.0f) {
            qcopy(obj + 0x10, v6);
            *(float *)(e + 0x4C) = 0.0f;
        } else {
            x = *(float *)(e + 0x4C) - 0.0096000005f;
            *(float *)(e + 0x4C) = x;
            FastVecScale(v8, v0, x);
            FastVecAdd(obj + 0x10, v8, obj + 0x10);
            FastVecSub(v9, v6, obj + 0x10);
            if (FastVecDot(v9, v0) > 0.0f) {
                qcopy(obj + 0x10, v6);
                *(float *)(e + 0x4C) = 0.0f;
            }
        }
    } else {
        *(float *)(e + 0x4C) -= 0.0096000005f;
        FastVecScale(v8, v0, *(float *)(e + 0x4C));
        FastVecAdd(obj + 0x10, v8, obj + 0x10);
    }
}

