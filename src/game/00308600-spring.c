/* Rests on the redundant-insn rule of docs/COMPILER-NOTES.md (volatile asm): the last jump of the
   mode == 0 arm lands on the restore of $s0, across a qcopy. */

#include "common.h"

extern char D_00189E20[];
extern char ref_0030E8A8_00[];

extern void func_002FE8D8(char *, float *);
extern void func_00282CF0(float *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(float *, float *, float);
extern float func_00282DB0(float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern int func_002761F8(float *, float *, int, int, int);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern void func_002A8240(char *, float *, float, float, float, int);

void func_0030E8A8(char *obj)
{
    char *e = *(char **)(obj + 0x68);
    char *d = D_00189E20;
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
    func_002FE8D8(obj + 0x10, v0);
    acc = 0.0f;
    func_00282CF0(v1, obj + 0x10, d + 0x80);
    projection = func_00282DB0(v1, v0);
    func_00282D30(v3, v0, projection);
    func_00282CF0(v2, v1, v3);
    l3 = func_00282DF0(v3);
    l2 = func_00282DF0(v2);
    func_00282D30(v4, v0, -2.5f);
    func_00282CC0(v4, obj + 0x10, v4);
    func_00282D30(v5, v0, 0.5f);
    func_00282CC0(v5, obj + 0x10, v5);
    if (func_002761F8(v5, v4, 2, 0, 0)) {
        qcopy(v6, ref_0030E8A8_00);
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        func_00282CF0(v8, v6, obj + 0x10);
        projection = func_00282DB0(v8, v0);
        func_00282D30(v7, v0, projection);
        acc = func_00282DF0(v7);
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
    step = 0.02f;
    func_002AA3A8(&f, 0.0f, (float *)(e + 0x48), step, 0.3f, 0.06666667f);
    if (f == 0.0f && *(float *)(e + 0x48) == 0.0f && acc < step)
        *(int *)(e + 0x44) = 0;
    if (l2 < *(float *)(e + 0x48))
        *(float *)(e + 0x48) = l2;
    if (*(float *)(e + 0x48) < l2)
        func_00282F20(v8, v8, *(float *)(e + 0x48));
    func_002A8240(obj, v8, 0.5f, 0.4f, 0.0f, 0);
    if (mode == 0) {
        if (func_00282DB0(v7, v0) > 0.0f) {
            qcopy(obj + 0x10, v6);
            *(float *)(e + 0x4C) = 0.0f;
        } else {
            x = *(float *)(e + 0x4C) - 0.0066666668f;
            *(float *)(e + 0x4C) = x;
            func_00282D30(v8, v0, x);
            func_00282CC0(obj + 0x10, v8, obj + 0x10);
            func_00282CF0(v9, v6, obj + 0x10);
            if (func_00282DB0(v9, v0) > 0.0f) {
                qcopy(obj + 0x10, v6);
                *(float *)(e + 0x4C) = 0.0f;
            }
        }
    } else {
        *(float *)(e + 0x4C) -= 0.0066666668f;
        func_00282D30(v8, v0, *(float *)(e + 0x4C));
        func_00282CC0(obj + 0x10, v8, obj + 0x10);
    }
}
