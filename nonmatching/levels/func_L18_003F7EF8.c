/* func_L18_003F7EF8 - 424 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L18_003F7EF8-zero.c, flags `-O2 -G0 -ffunction-sections -g
   -frac2-zero-ti-por` (Quad union as in L04_0046D6A8.c; D_L18_003F9018 is
   func_L18_003F9018's address passed as a0 of func_L00_002E6EF8).
   Same size (424 B); 3 masked diff lines, registers only: last test `lbu
   v0,0x20(s0); sltiu v0,v0,2; bnel v0` in draft, retail uses $v1 for it.
   Tried `>1`, `!=0 && !=1`, returning func_002A8C28's result (adds a move). */

#include "include_asm.h"
#include "common.h"

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

extern u8 D_L18_003F9018[];
extern u8 *func_002A9640(u8 *a0, s32 a1, s32 a2);
extern void func_002B0ED8(u8 *a0, u8 *a1, s32 a2);
extern void func_002A6C58(u8 *a0, s32 a1, s32 a2);
extern void func_0029F338(u8 *a0);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_002A8C28(u8 *a0, void *a1, f32 f12, f32 f13, s32 a2, f32 f14, s32 a3, s32 t0, s32 t1);
extern void func_L00_002E6EF8(u8 *a0, u8 *a1);

void func_L18_003F7EF8(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    u8 *r = func_002A9640(self, 0x10000, 1);
    u8 saved;
    Quad v0, v10, v20;

    if (r != 0 && *(u8 **)(r + 0x20) != 0) {
        s32 cls = *(s16 *)(*(u8 **)(r + 0x20) + 0xAA);

        if (cls == 0xB69) {
            if (self[0x31] != 0)
                *(f32 *)(r + 0x2C) = 4.0f;
            else
                *(s32 *)(r + 0x2C) = 0;
        } else if (cls == 0xF0A || cls == 0xF9E) {
            *(s32 *)(r + 0x2C) = 0;
        }
    }
    saved = self[0x94];
    func_002B0ED8(self, state + 0x60, 0);
    if (self[0x20] == 9) {
        u8 mode = self[0x94];

        if (mode == 9 || mode == 4 || mode == 3)
            self[0x94] = saved;
    }
    if (*(f32 *)(self + 0x18) < 90.0f) {
        func_002A6C58(self, 0, 3);
        func_0029F338(self);
        return;
    }
    v20.q = 0;
    v20.f[2] = *(f32 *)(state + 0x114) + *(f32 *)(state + 0x110);
    v10.q = v20.q;
    func_00282CC0(&v0, self + 0x10, &v10);
    func_002A8C28(self, &v0, *(f32 *)(state + 0x110) + 0.2f, 10.0f, 0x4000000, 1.0f, 0, 1, 0);
    if (self[0x20] >= 2)
        func_L00_002E6EF8(D_L18_003F9018, self);
}
