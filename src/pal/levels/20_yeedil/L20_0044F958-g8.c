#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
extern float D_L20_001B23F8 __attribute__((sda));
extern void *func_0029EFD0(int);
extern void func_002B37E8(u8 *, u8 *);
extern float func_002A7940(void);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float a, float b);
/* func_L20_0044A838 is defined in L20_0044A838-g8.c. */

/* func_L20_00449BB0 is defined in L20_00449BB0-g8.c. */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
typedef struct {
    u8 pad00[0x20];
    u8 state;         
    u8 pad21[3];
    char *pClass;     
    u8 pad28[4];
    float scale;      
    u8 pad30[4];
    u16 flags;        
    u8 pad36[0x68 - 0x36];
    char *pVars;      
} Moby449FD0;

char *func_PAL_L20_0044FC48(char *arg0, char *arg1, char *arg2, float arg3, int arg4,
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
        *(float *)(state + 0x14) = arg3 * 0.019867549f;
        *(int *)(state + 0x18) = arg4;
        *(float *)(state + 0x1C) = arg5;
        *(int *)(state + 0x20) = 0x32;
        *(float *)(state + 0x10) = func_002A7878(10.0f, 20.0f) * 0.00040000002f;
    }
    return obj;
}

extern float D_L20_001B2450 __attribute__((sda));
extern float D_L20_001B2454 __attribute__((sda));
extern float func_00283248(float, float);
extern float func_002AAA00(char *a, char *b, int c, float d, float e, float f,
                            float g);
extern float func_002AA2E8(float *, float, float);

void func_PAL_L20_00450700(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *p = arg0 + 0xF8;
    float a = *(float *)(state + 0x140) - *(float *)(arg0 + 0x10);
    float b = *(float *)(state + 0x144) - *(float *)(arg0 + 0x14);
    float c = D_L20_001B2450 * 6.981318e-06f;
    float d = D_L20_001B2454 * 0.0003490659f;
    float r;

    r = func_00283248(a, b);
    func_002AAA00(p, state + 0x1A4, 0, r, c, c, d);
    d = d * 4.0f;
    func_002AA2E8(arg0 + 0xF0, *(float *)(state + 0x1A8), d);
    *(float *)(state + 0x1A8) = 0.0f;
    func_002AA2E8(arg0 + 0x0F4, *(float *)(state + 0x1AC), d);
    *(float *)(state + 0x1AC) = 0.0f;
}
