#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 D_L03_001B108C __attribute__((sda));
extern u8 *func_002BDCE8(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern s32 func_002B38B8();
extern u8 *D_L03_001FB5A0[];
typedef struct {
    u8 pad00[0x30];
    s32 field30;
    s32 field34;
    u8 pad38[0x158];
    u8 *field190;
    u8 *field194;
} L03Block;
extern L03Block D_L03_001BD680;
extern s32 D_L03_001A8F00 __attribute__((sda));
extern void func_002A0488(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L02_003272D8(u8 *a0);
extern void func_002AEC18(u8 *a0, s32 a1);

void func_PAL_L03_0041EAE8(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    s32 old, next, base, rem;
    s32 arg1, arg2, arg3;

    switch (entity[0x20]) {
    case 0:
        entity[0x30] = 0xFF;
        entity[0x20] = 1;
        return;
    case 1: {
        s32 mode = D_L03_001A8F00;

        if (mode == 2) {
            if (D_L03_001BD680.field30 == 5) {
                if (D_L03_001BD680.field34 < 10) {
                    *(u16 *)(D_L03_001BD680.field194 + 0x7C) = 0x3F;
                }
            }
            if (D_L03_001BD680.field30 == 7) {
                u8 *obj = D_L03_001BD680.field190;
                if (D_L03_001BD680.field34 < 0x376) goto other;
                if (D_L03_001BD680.field34 >= 0x3B3) goto other;
                old = *(s32 *)state;
                next = old + 1;
                *(s32 *)state = next;
                base = (next > -1) ? next : old + 4;
                base = (base >> 2) << 2;
                rem = next - base;
                if (rem < 3) {
                    arg1 = 0;
                    arg2 = 0;
                    arg3 = 0;
                } else {
                    arg1 = 0xB0;
                    arg2 = 0xB0;
                    arg3 = 0xF0;
                }
                func_002A0488(obj, arg1, arg2, arg3);
                return;
            other:
                if (D_L03_001BD680.field34 < 0x395) {
                    *(s32 *)(state + 4) = func_L02_003272D8(obj);
                } else {
                    func_002AEC18(obj, *(s32 *)(state + 4));
                }
            }
        }
        return;
    }
    }
}
