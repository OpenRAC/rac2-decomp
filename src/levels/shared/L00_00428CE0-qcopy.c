#include "include_asm.h"
#include "common.h"

extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern float func_002703B0(char *, float, float, float, float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern char ref_L00_00428CE0_00[];

void func_L00_00428CE0(char *obj) {
    char *aux = *(char **)(obj + 0x70);
    char *a30 = aux + 0x30;
    char *a40 = aux + 0x40;
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float t[4] __attribute__((aligned(16)));
    float scale, ang;

    qcopy(v, D_00189EA0);
    v[2] += *(float *)(a40 + 0x4C);
    func_00282CF0(w, v, obj + 0x30);
    func_00282F20(w, w, 1.0f);
    ang = 1.5707964f - func_002831B0(func_00282DB0(w, obj));
    if (*(int *)(D_00189EA0 + 0x2214) == 0x24) {
        *(float *)a30 = *(float *)a30 + 0.017f;
        if (1.0f < *(float *)a30)
            *(float *)a30 = 1.0f;
        scale = ang * *(float *)a30;
    } else {
        scale = func_002703B0(a30, 0.0f, ang, 0.02f, 0.175f, 0.0f);
    }
    func_00282DD8(t, w, obj + 0x40);
    func_002ACEC0(obj, obj + 0x40, t, scale);
    func_00282F20(obj + 0x40, obj, 1.0f);
    qcopy(obj, obj + 0x40);
    func_00282DD8(obj + 0x10, obj, ref_L00_00428CE0_00);
    func_00282F20(obj + 0x10, obj + 0x10, 1.0f);
    func_00282DD8(obj + 0x20, obj + 0x10, obj);
}
