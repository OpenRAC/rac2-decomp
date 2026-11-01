#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, s32, s32);
extern u8 *func_002A9640(void *, s32, s32);
extern f32 func_00282E48(void *, void *);
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern void func_002E5CF8(s32, s32, void *);
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L07_00408338(void *);
extern void func_002E5E58(s32, s32, s32);
extern void func_US2_002B1880(s32, s32);
extern s32 func_00282948(void *);
extern void func_0029F338(void *);
extern u8 D_L07_001B1540[16] __attribute__((sda));
extern u8 D_L07_001B1538[8] __attribute__((sda));
extern u8 D_L07_001B1530[8] __attribute__((sda));
extern s32 D_L07_001B1560 __attribute__((sda));
extern u8 D_001A7A70 __attribute__((nosda));
extern u8 D_001A7A70_read[] __asm__("D_001A7A70") __attribute__((sda));
extern s32 D_L07_001A903C[] __attribute__((sda));
extern f32 D_L07_001B3198 __attribute__((sda));
extern f32 D_L07_001AA698 __attribute__((sda));

void func_US2_L07_00409480(u8 *obj)
{
    f32 a[4], b[4];
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *hit;
    s32 blocked;
    switch (obj[0x20]) {
    case 0:
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (!*(s32 *)state) {
            hit = func_002A9640(obj, 0x4010000, 0);
            if (hit) {
                qcopy(a, obj + 0x10);
                a[2] += 0.5f;
                blocked = 1;
                if (*(u8 **)(hit + 0x20)) {
                    qcopy(b, *(u8 **)(hit + 0x20) + 0x10);
                    b[2] += 0.5f;
                    if (func_00282E48(b, a) < 64.0f) {
                        blocked = 0;
                        if (!func_002761F8(b, a, 2, obj, 0)) blocked = 1;
                    }
                }
                if (blocked) func_002A7750(obj, 2, -1);
            }
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        func_002E5CF8(0, 0, obj);
        func_L00_0032A258(obj, D_L07_001B1540, D_L07_001B1538, D_L07_001B1530, 0xFFF, -1, D_L07_001B1560, 16, 0xFFFF, 0xFF, 0);
        func_L07_00408338(obj);
        *(s32 *)(state + 4) = 480;
        if (!D_001A7A70_read[0]) {
            D_001A7A70 = 1;
            func_002E5E58(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L07_001A903C[0] = 1;
        }
        if (D_L07_001B1560 >= 0) *(u16 *)(obj + 0x7C) = (1 << D_L07_001B1560) | 0x8000;
        else *(u16 *)(obj + 0x34) |= 0x41;
        func_002A7750(obj, 3, -1);
        break;
    case 3:
        if (func_00282948(state + 4)) {
            D_L07_001AA698 = D_L07_001B3198;
            func_0029F338(obj);
        }
        break;
    }
}
