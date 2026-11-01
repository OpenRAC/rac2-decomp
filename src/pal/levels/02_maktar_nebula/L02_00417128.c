#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern void func_002A7750();
extern float func_00283198(float);
extern char D_L02_00188660[];
extern int func_002E59F8(int);
extern int func_002A77E0(int);
extern float func_00282E48(void *, void *);
extern void *func_002A9640(void *, int, int);
extern char D_L02_001BA500[];
extern u8 D_001A7BCB __attribute__((sda));
extern u8 D_L02_001395B8[];
extern u8 D_L02_001C0700[];
extern s32 func_00288AA0(u8 *, s32);
extern s32 func_00288BE8(u8 *);
extern void func_0029F338(u8 *);
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern u16 D_0018CFDC;
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002AA2E8(float *, float, float);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283B98(float, float);
extern void *func_002A9640(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_PAL_L02_00417490(u8 *);
extern void func_PAL_L02_004176A8(u8 *);
extern int func_002A77E0(int);
extern s32 D_L02_001AEC78 __attribute__((sda));
extern void func_L00_002E6CF0(void *, void *);
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
extern int func_002E5CF8(int, int, void *);

/* Steps the actor by its kind byte (+0x20). Kind 0 releases it (func_0029F338) when the table byte
   of its owner (D_0019B2E8, indexed by the byte at +0xB0 and D_001A79F0) has bit 7 set; otherwise
   it takes twice the size at +0x24 of its type record, sets or clears bit 15 of its flags at +0x34
   by func_002A77E0(2), starts state 1 and draws the block's two phases (+4 and +0x14) with
   func_002A7940. Kind 1 keeps its slot record (the index at +0x18 of the block) alive, eases the
   block's float at +0xC to 0 or 1 by whether func_00282E80 puts the actor farther than 64.0 from
   D_L02_001BA500, registers func_PAL_L02_004176A8 while it is nonzero, and when the entity found by
   func_002A9640 (a record whose halfword at +0xAA is 0x9C8) is within 5.0 starts state 2 and gives
   the slot up. Kind 2 only runs the common tail, which steps the two phases (func_00283B98), puts
   0.5 * sin(phase) + the base at +8 into the actor's float at +0x18 and runs the counter at +0x10
   down by 1/15, wrapping it into [-1, 1]. The first slot lookup is a separate block-local pointer
   from the one in the state-2 arm (retail keeps them in different registers). */
void func_PAL_L02_00417128(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u8 *p;
    u8 *q;
    s32 slot;
    float f;

    switch (a0[0x20]) {
    case 0:
        if (D_0019B2E8[a0[0xB0] + D_001A79F0 * 16] & 0x80) {
            func_0029F338(a0);
            return;
        }
        *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 2.0f;
        if (func_002A77E0(2))
            *(u16 *)(a0 + 0x34) |= 0x8000;
        else
            *(u16 *)(a0 + 0x34) &= 0x7FFF;
        func_002A7750(a0, 1, -1);
        *(float *)(s1 + 8) = *(float *)(a0 + 0x18);
        *(float *)(s1 + 4) = func_002A7940();
        *(float *)(s1 + 0x14) = func_002A7940();
        break;
    case 1:
        if (a0[0x31] != 0)
            func_PAL_L02_00417490(a0);
        {
            u8 *r = (u8 *)D_L02_00188660 + *(s32 *)(s1 + 0x18) * 0x70;

            if (*(u8 **)(r + 0x88) != a0 || r[0x74] == 0)
                *(s32 *)(s1 + 0x18) = func_002E5CF8(0, 4, a0);
        }
        f = func_00282E80(a0 + 0x10, D_L02_001BA500);
        if (f > 64.0f)
            func_002AA2E8((float *)(s1 + 0xC), 0.0f, 0.020000001f);
        else
            func_002AA2E8((float *)(s1 + 0xC), 1.0f, 0.020000001f);
        if (*(float *)(s1 + 0xC) != 0.0f)
            func_L00_002E6CF0((void *)func_PAL_L02_004176A8, a0);
        p = func_002A9640(a0, 0x10000, 0);
        if (p != 0) {
            q = *(u8 **)(p + 0x20);
            if (q != 0 && *(s16 *)(q + 0xAA) == 0x9C8 &&
                func_00282E48(a0 + 0x10, q + 0x10) < 5.0f) {
                D_0018CFDC = 0xFFFF;
                func_002A7750(a0, 2, -1);
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
                *(u32 *)(a0 + 0x98) = 0;
                slot = *(s32 *)(s1 + 0x18);
                if (slot != -1) {
                    u8 *rec = (u8 *)D_L02_00188660 + slot * 0x70;

                    if (*(u8 **)(rec + 0x88) == a0 && rec[0x74] != 0)
                        func_002E59F8(slot);
                }
                *(s32 *)(s1 + 0x18) = -1;
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        break;
    }
    *(float *)(s1 + 4) = func_00283B98(*(float *)(s1 + 4), 0.06981318f);
    *(float *)(s1 + 0x14) = func_00283B98(*(float *)(s1 + 0x14), -0.12566373f);
    *(float *)(a0 + 0x18) = func_00283198(*(float *)(s1 + 4)) * 0.5f + *(float *)(s1 + 8);
    f = *(float *)(s1 + 0x10) + -0.080000006f;
    *(float *)(s1 + 0x10) = f;
    if (f > 1.0f)
        *(float *)(s1 + 0x10) = f - 1.0f;
    else if (f < -1.0f)
        *(float *)(s1 + 0x10) = f + 1.0f;
}

