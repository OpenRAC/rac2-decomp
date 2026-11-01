#include "include_asm.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern s32 D_L18_001B1254 __attribute__((sda));
extern s32 D_L18_001B1258 __attribute__((sda));
extern s32 D_L18_001B125C __attribute__((sda));
extern f32 D_L18_001B12FC __attribute__((sda));
extern f32 D_L18_001B12C0 __attribute__((sda));
extern f32 D_L18_001B1C4C __attribute__((sda));
extern f32 D_L18_001B1C48 __attribute__((sda));
extern f32 D_L18_001B1C44 __attribute__((sda));
extern f32 D_L18_001B1C40 __attribute__((sda));
extern s32 func_002A7820(s32, s32);
extern s32 func_00337AD8(s32, s32, f32);
extern s32 func_L01_003120A8(void *, void *, void *, s32, f32, f32, s32, s32, s32);
extern f32 D_L18_001B1C50 __attribute__((sda));
extern f32 D_L18_001B1C54[] __attribute__((sda));
extern s32 D_L18_001B1C58 __attribute__((sda));
extern f32 D_L18_001B1C5C __attribute__((sda));
extern f32 func_002AA140(f32, f32, f32);
extern s32 func_00283CF0(f32);
typedef float L18_EDE8f32;
static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
extern void func_002A7A00(void *, L18_EDE8f32, L18_EDE8f32);
extern int func_002A77E0(int);
extern void func_00283098(void *, const void *, const void *);
extern void func_00282CC0(void *, void *, void *);
extern unsigned char D_L18_002BD9B0[];
extern L18_EDE8f32 D_L18_001B1C68 __attribute__((sda));
extern L18_EDE8f32 D_L18_001B1C6C __attribute__((sda));
extern L18_EDE8f32 D_L18_001B1C70 __attribute__((sda));
extern L18_EDE8f32 D_L18_001B1C74 __attribute__((sda));

void func_PAL_L18_00444240(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    L18_EDE8f32 v[4] __attribute__((aligned(16)));
    s32 i;

    for (i = 0; i < 2; i++) {
        u8 *s = state + i * 0xA0;

        func_002A7A00(s + 0x60, D_L18_001B1C68 * 0.0003490659f, D_L18_001B1C6C * 0.0003490659f);
        func_002A7A00(s + 0x70, D_L18_001B1C68 * 0.0003490659f, D_L18_001B1C6C * 0.0003490659f);
        func_002A7A00(s + 0x80, D_L18_001B1C70, D_L18_001B1C74);
        func_002A7A00(s + 0x90, D_L18_001B1C70, D_L18_001B1C74);
        qcopy(state, state + 0x140);
        qcopy(state + 0xA0, state + 0x140);
        func_00283098(v, D_L18_002BD9B0 + func_002A77E0(6) * 16, obj + 0xC0);
        func_00282CC0(v, obj + 0x10, v);
        qcopy(state + 0x10, v);
    }
}
