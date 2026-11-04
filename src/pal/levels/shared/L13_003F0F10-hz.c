/* func_PAL_L13_003F0F10, the PAL copy of func_L13_003ECD48: the same C with the callees are PAL's
   func_PAL_002B1A50 and func_PAL_L00_003FB330. */
#include "include_asm.h"

#ifndef RAC2_T_OBJ_389848
typedef struct {
    char pad[0xAA];
    short key;          /* +0xAA */
} Obj_389848;
#endif

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

extern int func_PAL_002B1A50(void *, void *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_0029F338(void *);

typedef struct {
    unsigned char pad0[0x20];
    float f20;
    unsigned char pad24[0x50 - 0x24];
    unsigned char sub50[0x11];
    unsigned char b61;
    unsigned char b62;
    unsigned char pad63[0x6A - 0x63];
    unsigned char b6A;
    unsigned char pad6B[0xA8 - 0x6B];
    float fA8;
} L13_CD48Vars;

extern void func_L13_00389848(Obj_389848 *object);
void func_PAL_L13_003F0F10(unsigned char *m)
{
    L13_CD48Vars *v = *(L13_CD48Vars **)(m + 0x68);
    float p[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));

    if (m[0x20] == 0) {
        func_L13_00389848((Obj_389848 *)m);
        m[0x20] = 1;
    }
    v->b6A = 2;
    v->fA8 = 0.01f;
    v->b61 = 0xFF;
    v->b62 = 0xFF;
    if (func_PAL_002B1A50(m, v->sub50, 0) != 0) {
        func_002E5CF8(0, 0, (char *)m);
    }
    if (v->f20 <= 0.0f) {
        qcopy(p, m + 0x10);
        func_00282F20(a, m + 0xD0, -2.0f);
        func_00282CC0(p, a, p);
        func_00282F20(b, m + 0xC0, 1.5f);
        func_00282CC0(p, b, p);
        func_PAL_L00_003FB330(p, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.75f, 20.0f, 1, 0, 0, 0);
        func_0029F338(m);
    }
}
