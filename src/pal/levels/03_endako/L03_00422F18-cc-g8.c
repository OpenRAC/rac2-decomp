/* func_PAL_L03_00422F18, the PAL copy of func_L03_0041DAD0: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_L03_0041E240 becomes func_PAL_L03_00423688. */
#include "common.h"
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern float D_L03_001B1BC0 __attribute__((sda));
extern float D_L03_001B1BC4 __attribute__((sda));
extern float D_L03_001B1BC8 __attribute__((sda));
extern u8 D_L03_001B9980[];
extern void func_0029F338(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A93B0(void *);
extern float func_00282E48(void *, void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern int func_002B3BA8(void *, int, int, int, float, float);
extern void func_PAL_L03_00423688(u8 *);

typedef struct { u8 pad[0x120]; f32 rate[3]; } RateView;

void func_PAL_L03_00422F18(u8 *self) {
    u8 *st = *(u8 **)(self + 0x68);

    if (self[0x20] == 0) {
        st[0x48] = func_00283CF0(20.0f);
        st[0x4A] = func_00283CF0(14.399999618530273f);
        st[0x60] = 7;
        *(f32 *)(st + 0x8C) = 0.4000000059604645f;
        *(s32 *)(st + 0x98) = 3;
        *(f32 *)(st + 0x80) = 0.5f;
        *(f32 *)(st + 0x84) = 0.5f;
        *(f32 *)(st + 0x90) = *(f32 *)(self + 0x18) - 2.0f;
        *(s32 *)(st + 0x138) |= 0x15;
        *(f32 *)(st + 0x134) = 0.05000000074505806f;
        *(f32 *)(st + 0x104) = 0.25f;
        *(f32 *)(st + 0x100) = 0.5f;
        *(f32 *)(st + 0x108) = 0.75f;
        *(f32 *)(st + 0x10C) = 0.75f;
        *(f32 *)(st + 0x110) = 0.7853982448577881f;
        *(f32 *)(st + 0x130) = 0.523598849773407f;
        st[0x28] = 3;
        *(s32 *)(st + 0x1D8) = -1;
        *(s32 *)(st + 0x350) = -1;
        if (*(s32 *)(st + 0x210) == -1) {
            func_0029F338(self);
            return;
        }
        func_002A7750(self, 1, 0);
        if (self[0x43] != 0)
            func_PAL_002A7E68(self, 0, 0, 0);
    }
    if (self[0x31] != 0) {
        if (func_00282E48(self + 0x10, D_L03_001B9980) < 48.0f) {
            func_002A93B0(self);
            self[0x6F] = 0x2D;
        }
    }
    ((RateView *)st)->rate[2] = D_L03_001B1BC0 * 0.020000001f;
    ((RateView *)st)->rate[0] = D_L03_001B1BC4 * 0.00040000002f;
    ((RateView *)st)->rate[1] = D_L03_001B1BC8 * 0.00040000002f;
    if (func_PAL_002B1A50(self, st + 0x50, 0))
        func_PAL_L03_00423688(self);
    func_002B3BA8(self, *(s32 *)(st + 0x214), 0, 0, 16.0f, 0.0f);
}
