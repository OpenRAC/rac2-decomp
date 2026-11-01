#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0040B520);

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0040B8B8);

#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern int func_00283CF0(float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00282978(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283028(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern void func_002833F0(void *, void *);
extern void func_PAL_L00_00322198(void *, void *, float, float, int);
extern void func_PAL_L00_003FB330(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern int func_00277258(void *, int, float, void *);
extern void func_002AB668(void *, void *, float);
extern void func_002839D0(void *, void *);
extern void func_002AB6D8(void *, void *);
extern float D_L04_001BFB00[];
extern void func_PAL_L04_0040B8B8(void *);
extern void func_00282CC0(void *, void *, void *);

void func_PAL_L04_0040BC70(unsigned char *m)
{
    float oldpoint[4];
    float rot[12];
    float point[4];
    float delta[4];
    float probe[4];
    float matrix[13];
    float bounce[4];
    float axis[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    float speed, dot;
    float radius;
    *(unsigned short *)(p + 0x32) += 1;
    switch (m[0x20]) {
    case 1:
        if (func_00282978(p + 0x30)) {
            m[0x20] = (*(int *)(p + 0x34) & 1) ? 3 : 2;
            *(short *)(p + 0x30) = func_00283CF0(8.666667f);
            return;
        }
        if (*(int *)(p + 0x34) & 4) func_L00_002E6EF8(func_PAL_L04_0040B8B8, m);
        break;
    case 2:
        func_00283098(oldpoint, p + 0x20, m + 0xc0);
        func_00282CC0(oldpoint, oldpoint, m + 0x10);
        if (*(int *)(p + 0x34) & 2) func_PAL_L00_00322198(m, oldpoint, 0.3f, 10.0f, -1);
        else func_PAL_L00_003FB330(m + 0x10, 0.5f, 0.0f, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0);
        goto destroy;
    case 3:
        if (func_00282978(p + 0x30)) {
        case 0:
        destroy:
            func_0029F338(m);
            return;
        }
        m[0x23] = func_00283CF0((float)*(short *)(p + 0x30) * 14.76923f);
        break;
    }
    func_002833F0(rot, p + 0x10);
    func_00283098(oldpoint, p + 0x20, m + 0xc0);
    func_00283738(m + 0xc0, rot, m + 0xc0);
    func_00283098(point, p + 0x20, m + 0xc0);
    func_00282CF0(delta, point, oldpoint);
    func_00282CF0(m + 0x10, m + 0x10, delta);
    func_00282CC0(m + 0x10, m + 0x10, p);
    *(float *)(p + 8) -= *(float *)(p + 0x38);
    radius = *(float *)(p + 0x2c);
    func_00283098(probe, p + 0x20, m + 0xc0);
    func_00282CC0(probe, probe, m + 0x10);
    if (func_00277258(probe, 0, radius, m)) {
        func_00282F20(D_L04_001BFB00, D_L04_001BFB00, 1.0f);
        speed = func_00282DF0(p);
        dot = func_00282DB0(p, D_L04_001BFB00);
        if (dot < 0.0f) {
            func_00283028(p, p, D_L04_001BFB00);
            func_00282F20(bounce, D_L04_001BFB00, dot * 0.5f);
            func_00282CC0(p, p, bounce);
            func_00282F20(p, p, speed);
            func_00282DD8(axis, D_L04_001BFB00, p);
            func_00282F20(axis, axis, 1.0f);
            func_002AB668(axis, axis, func_00282DF0(p + 0x10));
            func_002839D0(axis, matrix);
            func_002AB6D8(matrix, p + 0x10);
            if (*(short *)(p + 0x32) >= 13) *(short *)(p + 0x30) = 0;
        }
    }
}

