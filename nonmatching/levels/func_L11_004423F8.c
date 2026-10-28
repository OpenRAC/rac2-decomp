/* func_L11_004423F8 - 464 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Draft needs own file, cflags: -O2 -G64 -Wa,-G64 -ffunction-sections. Vec3
   tables must be `f32 D[3] __attribute__((sda))` (struct copy gives ldl/ldr;
   component copy via macro matches retail pattern).
   480 vs 464 bytes. Retail: object=s2, state=s1, D_00189E20 base in s0; first
   guide store reuses the pointer loaded for the null test (a0), later stores
   reload.
   Mine puts state in s0 and object in s1 and loads the pointer twice. Not
   tuned further. */

#include "common.h"

#define GUIDE(i) (*(f32 **)(state + 0x170))[i]
#define SET_GUIDE(v) (GUIDE(0) = (v)[0], GUIDE(1) = (v)[1], GUIDE(2) = (v)[2])

extern f32 D_L11_001B15BC[3] __attribute__((sda));
extern f32 D_L11_001B15C8[3] __attribute__((sda));
extern f32 D_L11_001B15D4[3] __attribute__((sda));
extern f32 D_L11_001B15E0[3] __attribute__((sda));
extern f32 D_L11_001B15EC[3] __attribute__((sda));
extern u8 D_00189E20[];
extern char *func_L00_002D70A0(int);
extern void func_L00_002D7140(void *);
extern u8 *func_L11_004417E8(u8 *);
extern void func_L00_00424F58(u8 *, f32, f32);

/* Keeps the object's guide vector (state +0x170) on the table entry its target selects. */
void func_L11_004423F8(u8 *object)
{
    u8 *state;
    u8 *e;
    s32 kind;

    kind = object[0x20];
    state = *(u8 **)(object + 0x68);
    if (kind != 8 && kind != 9) {
        func_L00_002D7140(*(void **)(state + 0x170));
        *(void **)(state + 0x170) = 0;
        return;
    }
    if (*(void **)(state + 0x170) == 0) {
        *(void **)(state + 0x170) = func_L00_002D70A0(5);
        return;
    }
    if (*(s32 *)(state + 0x180) != 0) {
        e = *(u8 **)(state + 0x184);
        if (e == 0) {
            SET_GUIDE(D_L11_001B15BC);
            return;
        }
        if (*(s16 *)(e + 0xAA) == 0xD4A)
            SET_GUIDE(D_L11_001B15D4);
        e = *(u8 **)(state + 0x184);
        if (*(s16 *)(e + 0xAA) == 0xD4B)
            SET_GUIDE(D_L11_001B15EC);
        else if (*(s16 *)(e + 0xAA) == 0xB3A)
            SET_GUIDE(D_L11_001B15E0);
    } else if (kind == 9) {
        SET_GUIDE(D_L11_001B15C8);
        if (((f32 *)func_L11_004417E8(object))[2] + 16.0f < *(f32 *)(D_00189E20 + 0x88)) {
            if (*(u16 *)(object + 0x96) < 500)
                func_L00_00424F58(func_L11_004417E8(object), 0.17333333f, 0.0f);
            else
                func_L00_00424F58(func_L11_004417E8(object), 0.0087f, 0.0f);
        }
    } else {
        SET_GUIDE(D_L11_001B15BC);
    }
}
