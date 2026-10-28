#include "include_asm.h"
#include "common.h"

#ifndef RAC2_T_V4_002AD6F0
#define RAC2_T_V4_002AD6F0
typedef int V4_002AD6F0 __attribute__((mode(TI)));
#endif

typedef struct { char pad[64]; } Matrix64_002AD6F0;

extern void func_00283410(char *dst, char *src);
extern void func_00283698(char *dst, char *src);
extern void func_00283788(char *a, char *b, char *c);
extern void func_002AB6D8(char *a, char *b);

extern void func_00283098(char *a, char *b, char *c);
extern void func_00282CC0(char *dst, char *a, char *b);
extern void func_00283658(char *dst, char *src);
extern void func_002AC9F8(char *vec, float x);
extern char *func_002AD0B0(char *a);
extern int func_002AD5F8(char *unused, char *obj, char *arg2, char *arg3, char *arg4, char *arg5);
extern char *D_0018C0B0;

int func_002AD470(char *a0, char *a1, char *a2, char *a3, char *a4, char *a5)
{
    char buf0[64];
    char buf2[64];
    char vec[16];
    char *p;

    p = func_002AD0B0(a1);
    if (p == 0)
        return 0;
    if (*(int *)(p + 60) & 0x40)
        func_00283410(buf0, a1 + 240);
    else
        func_00283658(buf0, a1 + 192);
    func_00283098(a4, a2, buf0);
    func_00282CC0(a4, a4, a1 + 16);
    func_00283410(buf2, a3);
    func_00283788(buf2, buf0, buf2);
    func_002AB6D8(buf2, a5);
    if (*(int *)(p + 60) & 4) {
        func_00282CC0(a4, a4, p + 16);
        func_002AD5F8(a0, a1, a4, a5, a2, a3);
        return 1;
    }
    if (a0 == D_0018C0B0)
        return 1;
    if ((unsigned char)a0[0x22] < (unsigned char)a1[0x22]) {
        qcopy(vec, p + 16);
        func_002AC9F8(vec, 1.0f);
        func_00282CC0(a4, a4, vec);
    }
    return 1;
}

void func_002AD6F0(void *obj, void *a1, void *a2, void *a3)
{
    Matrix64_002AD6F0 m0, m1, m2, m3;
    V4_002AD6F0 *p;

    func_00283410((char *)&m0, (char *)a2);
    func_00283698((char *)&m1, (char *)&m0);
    func_00283410((char *)&m2, (char *)a3);
    func_00283788((char *)&m3, (char *)&m1, (char *)&m2);
    func_002AB6D8((char *)&m3, (char *)obj);
    if (*(int *)((char *)obj + 0x3C) & 2) {
        p = (V4_002AD6F0 *)((char *)obj + 0x20);
        *p = *(V4_002AD6F0 *)a2;
    }
    p = (V4_002AD6F0 *)((char *)obj + 0x10);
    *p = *(V4_002AD6F0 *)a1;
}

extern void func_00282DD8(float *dst, float *a, float *b);
extern void func_00282F20(float *dst, float *src, float scale);
extern float func_00282DB0(float *a, float *b);
extern float func_00282DF0(float *a);
extern float func_002831B0(float x);
extern float func_00283198(float x);
extern float func_00283180(float x);
extern void func_00282D30(float *dst, float *src, float scale);
extern void func_002ACDE8(float *dst, float *a, float *b);

void func_002ACF68(float *dst, float *a, float *b, int normalized, float scale)
{
    float axis[4];
    float dot;
    float len;
    float angle;

    func_00282DD8(axis, b, a);
    func_00282F20(axis, axis, 1.0f);
    dot = func_00282DB0(a, b);
    if (normalized == 0) {
        len = func_00282DF0(a) * func_00282DF0(b);
        if (len == 0.0f) {
            qcopy(dst, a);
            return;
        }
        dot /= len;
    }
    angle = (1.5707964f - func_002831B0(dot)) * (scale * 0.5f);
    func_00282D30(axis, axis, func_00283198(angle));
    axis[3] = func_00283180(angle);
    func_002ACDE8(dst, a, axis);
}

