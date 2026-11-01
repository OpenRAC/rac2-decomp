#include "include_asm.h"


typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;
extern u32 *func_0037BA88(u8 *arg0);
extern s32 func_003351C0(s32 mode);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern void func_0037BD88(u8 *arg0, u32 flags, s32 a, s32 b, s32 c, s32 d, s32 e,
                          f32 f0, f32 f1, f32 f2, f32 f3);
extern f32 func_00335320(void);
extern u8 *func_0037B670(u8 *arg0);
extern s32 func_003062A0(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_00335200(s32 a0, s32 a1);
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern void func_L10_00418AD8(u8 *arg0);
extern s32 func_L05_0037B538(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_002E5DA0(s32 index, s32 value, u8 *object, s32 kind);
extern s32 func_0037D6E0(u8 *a0);
extern u8 *D_L10_0020B1E0[];
extern u8 *D_001B251C;
extern u8 D_L10_00265BA0[];
extern u8 D_L10_00188660[];
extern u8 D_L10_00221CD0[];
extern u8 D_00188660[];
extern s32 D_001B0F44 __attribute__((sda));
extern s32 D_001B0F48 __attribute__((sda));

/* arms one timed effect slot and records it in the state word, skipping out while the
   object is inactive */
void func_PAL_L10_0041D888(u8 *arg0) {
    u8 *state = *(u8 **)(arg0 + 0x68);
    u8 *p = (u8 *)func_0037BA88(arg0);
    if (p == 0) return;
    if (*(s32 *)(p + 0x120) == 0) return;
    if (*(s32 *)(state + 0x268) != 0) return;
    func_0037BD88(arg0, 0x60000080, 1, 0, 0, -1, 0, 0.8f, 2.0f, 1.0f, 1.3f);
    if (func_003351C0(3) != 0) {
        func_003737B8(1, 0, arg0, 0xF8E);
    }
    *(s32 *)(state + 0x268) = 0x19;
}

