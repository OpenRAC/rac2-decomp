/* func_L12_00402DF8 - 516 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c goes in L12_00402DF8-g8.c (-G8, gp floats and D_001A79F0 sda). 484
   vs 516 bytes. Logic fully decoded.
   Diffs: retail loads the byte once into an int (sra by 4 -> use `int val =
   *slot`), tests odd/even nibble with the three
   `func_0029F338(obj); return` exits merged into ONE shared block (retail has
   a single jal at +0x... for tbl!=0, nibble!=0), and
   the float prologue schedules differently (stores 0xF0/0xF4/0xF8 order). `st
   = obj->0x68` must be loaded before the state test (delay slot). */

#include "common.h"

extern void func_002AEE70(u8 *, u8 *, u8 *, float, float, float);
extern void func_0029F338(void *);
extern void func_L12_00402B48(void *);
extern float func_00282E80(void *, void *);
extern void func_002B0A18(int, int);
extern void func_00288308(int);
extern void func_L00_003294F0(void *, int);
extern void func_002AD860(int);
extern float D_L12_001B12B0 __attribute__((sda));
extern float D_L12_001B12B4 __attribute__((sda));
extern float D_L12_001B12B8 __attribute__((sda));
extern float D_L12_001B12BC __attribute__((sda));
extern float D_L12_001B12C0 __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_L12_001B3C1C[];
extern u8 D_L12_001B3C20[];
extern u8 D_L12_0021EDF0[];
extern u8 D_0019B4A8[];
extern u8 D_00189EA0[];
extern s32 D_L12_001B2E9C_2;

void func_L12_00402DF8(u8 *obj) {
    u8 *st;
    s16 idx;
    u8 *slot;
    f32 rx, ry, rz, pitch, yaw;

    st = *(u8 **)(obj + 0x68);
    if (obj[0x20] != 0) {
        return;
    }
    rx = D_L12_001B12B8 * 0.0174532942f;
    ry = D_L12_001B12BC * 0.0174532942f;
    rz = D_L12_001B12C0 * 0.0174532942f;
    pitch = D_L12_001B12B4 * 0.00029088825f;
    yaw = D_L12_001B12B0;

    *(f32 *)(obj + 0xF0) = rx;
    *(f32 *)(obj + 0xF4) = ry;
    *(f32 *)(obj + 0xF8) = rz;
    func_002AEE70(obj, D_L12_001B3C1C, D_L12_001B3C20, yaw, pitch, 0.0f);
    idx = *(u16 *)(obj + 0xB2);
    if (D_L12_0021EDF0[idx + 0x464] != 0) {
        func_0029F338(obj);
        return;
    }
    slot = D_0019B4A8 + (idx >> 1) + (D_001A79F0 << 10);
    if (*(u16 *)(obj + 0xB2) & 1) {
        if (((*slot >> 4) & 7) != 0) {
            func_0029F338(obj);
            return;
        }
    } else {
        if ((*slot & 7) != 0) {
            func_0029F338(obj);
            return;
        }
    }
    func_L12_00402B48(obj);
    if (func_00282E80(obj + 0x10, D_00189EA0) < 1.5f) {
        func_002B0A18(0x1246, 0x1F4);
        func_00288308(0x10);
        func_L00_003294F0((u8 *)D_L12_001B2E9C_2 + (*(s32 *)st << 8), 1);
        func_002AD860(0x10);
        idx = *(u16 *)(obj + 0xB2);
        slot = D_0019B4A8 + (idx >> 1) + (D_001A79F0 << 10);
        if (*(u16 *)(obj + 0xB2) & 1) {
            if (((*slot >> 4) & 7) != 7) {
                *slot += 0x10;
            }
        } else {
            if ((*slot & 7) != 7) {
                *slot += 1;
            }
        }
        func_0029F338(obj);
    }
}
