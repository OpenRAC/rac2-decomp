#include "include_asm.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B23E8 __attribute__((sda));

extern float D_L20_001B23EC __attribute__((sda));

extern float D_L20_001B23F0 __attribute__((sda));

extern float D_L20_001B23F8 __attribute__((sda));

extern float D_L20_001B2410 __attribute__((sda));

extern float D_L20_001B2414 __attribute__((sda));

extern float D_L20_001B241C __attribute__((sda));

extern float D_L20_001B2450 __attribute__((sda));

extern float D_L20_001B2454 __attribute__((sda));

extern int D_L20_001B2AC8 __attribute__((sda));

extern void func_002A7750(char *, int, int);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *dst, void *src, float x);

extern float func_00282E20(void *vec);

extern void func_00282F70(char *a, char *b);

extern void func_002C9218(char *a, char *b, char *c, float f);

extern void func_0032DA58(char *, char *, void *, float);

/* func_002A8C28 returns a value here: retail keeps $v0 live after the call,
   and only a non-void prototype gives the flag word $v1 instead of $v0. */
extern int func_002A8C28(char *, char *, int, int, float, float, float, int, int);

extern float func_00283B98(float, float);

extern float func_00283198(float);

extern void func_002A9288(char *, float);

extern float func_00283248(float, float);

extern float func_002AAA00(char *a, char *b, int c, float d, float e, float f,
                            float g);

extern float func_002AA2E8(float *, float, float);

extern void *func_0029EFD0(int);

extern void func_002B37E8(u8 *, u8 *);

extern float func_002A7940(void);

extern void func_002833F0(void *, void *);

extern float func_002A7878(float a, float b);

extern int func_00277F48(float f, char *a, int b, char *c, int d);

extern void func_L20_00444C18(char *arg0, char *arg1);

extern char D_L20_001B9FC0[] __attribute__((nosda));

void func_L20_0044AA88(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *p = arg0 + 0xF8;
    float a = *(float *)(state + 0x140) - *(float *)(arg0 + 0x10);
    float b = *(float *)(state + 0x144) - *(float *)(arg0 + 0x14);
    float c = D_L20_001B2450 * 4.84813745e-06f;
    float d = D_L20_001B2454 * 0.000290888245f;
    float r;

    r = func_00283248(a, b);
    func_002AAA00(p, state + 0x1A4, 0, r, c, c, d);
    d = d * 4.0f;
    func_002AA2E8(arg0 + 0x0F0, *(float *)(state + 0x1A8), d);
    *(float *)(state + 0x1A8) = 0.0f;
    func_002AA2E8(arg0 + 0x0F4, *(float *)(state + 0x1AC), d);
    *(float *)(state + 0x1AC) = 0.0f;
}

void func_L20_00449AE8(char *arg0) {
    TI128 v;

    func_00282CF0(&v, D_L20_001B9FC0, arg0 + 0x10);
    func_00282F20(&v, &v, 1.0f);
    func_0032DA58(arg0, arg0 + 0x10, &v, *(float *)(arg0 + 0x18) - 0.5f);
    func_002A8C28(arg0, arg0 + 0x10, 0x10000, 0, 6.0f, D_L20_001B23EC, 2.0f,
                  1, 0);
    *(int *)(arg0 + 0x98) = 0;
    *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    func_002A7750(arg0, 1, -1);
}

/* func_L20_0044A838 is defined in L20_0044A838-g8.c. */

/* func_L20_00449BB0 is defined in L20_00449BB0-g8.c. */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* The moby fields func_L20_00449FD0 sets.  Written as casts of byte offsets, these four
   accesses let the scheduler put the $gp scale load after the pVars load; as struct
   members they give retail's order.  The float/int/float parameter order follows the
   0x14/0x18/0x1C fields it fills (a0-a3 and $f12/$f13 are assigned as before). */
typedef struct {
    u8 pad00[0x20];
    u8 state;        /* 0x20 */
    u8 pad21[3];
    char *pClass;    /* 0x24 */
    u8 pad28[4];
    float scale;     /* 0x2C */
    u8 pad30[4];
    u16 flags;       /* 0x34 */
    u8 pad36[0x68 - 0x36];
    char *pVars;     /* 0x68 */
} Moby449FD0;

char *func_L20_00449FD0(char *arg0, char *arg1, char *arg2, float arg3, int arg4,
                        float arg5) {
    char *obj;
    char *state;

    obj = func_0029EFD0(0x12EE);
    if (obj != 0) {
        func_002B37E8((u8 *)obj, (u8 *)arg0);
        qcopy(obj + 0x10, arg1);
        *(float *)(obj + 0xF0) = func_002A7940();
        *(float *)(obj + 0xF4) = func_002A7940();
        func_002833F0(obj + 0xC0, obj + 0xF0);
        ((Moby449FD0 *)obj)->state = 1;
        ((Moby449FD0 *)obj)->flags |= 0x100;
        ((Moby449FD0 *)obj)->scale =
            *(float *)(((Moby449FD0 *)obj)->pClass + 0x24) * D_L20_001B23F8;
        state = ((Moby449FD0 *)obj)->pVars;
        qcopy(state, arg2);
        *(float *)(state + 0x14) = arg3 * 0.016666668f;
        *(int *)(state + 0x18) = arg4;
        *(float *)(state + 0x1C) = arg5;
        *(int *)(state + 0x20) = 0x3C;
        *(float *)(state + 0x10) = func_002A7878(10.0f, 20.0f) * 0.00027777778f;
    }
    return obj;
}

/* func_L20_0044B100 is defined in L20_0044B100-g8.c. */

/* func_L20_0044A658 is defined in L20_0044A658-g8.c. */

/* func_L20_0044A8F0 is defined in L20_0044A8F0-g8.c. */

/* func_L20_00449338 is defined in L20_00449338-g8.c. */
