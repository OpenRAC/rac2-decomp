#include "common.h"

/* func_US2_L11_00399764, the v2.00 copy of func_L11_003983F0: the same two triggers, but the first
   no longer tests D_L11_001AED04 and D_L11_001AED00. The hero's fields 0x2294 and 0x24CC clear or set
   D_US2_001A9050, and while D_US2_001A904C is set each call scans 40 objects from the table for live
   ones of class 0xCF5, 0xCF6 or 0xD07, firing the trigger when a full pass finds none. Built without
   -mno-split-addresses: the hero's address is split, the MACRO_ADDR globals keep their macro loads. */

extern void func_002A7750(u8 *a0, u8 a1, s32 a2);

extern int func_002E5E58(int a0, unsigned int a1, void *a2);

extern void func_002B0A18(int a0, int a1);

typedef struct {
    char pad0[0x2294];
    int w2294;
    char pad2298[0x24CC - 0x2298];
    int w24CC;
} Hero_00399764;

extern Hero_00399764 D_00189E20;

extern u8 *D_L11_001B359C MACRO_ADDR;

extern u8 *D_L11_001B35A0 MACRO_ADDR;

extern s32 D_L11_001B30C8 MACRO_ADDR;

extern s32 D_L11_001AED04 __attribute__((sda));

extern s32 D_L11_001AED08 __attribute__((sda));

extern s32 D_US2_001A904C MACRO_ADDR;

extern s32 D_US2_001A9050 MACRO_ADDR;

extern s32 D_L11_001A903C MACRO_ADDR;

extern u8 D_001A7A60[] MACRO_ADDR;

void func_US2_L11_00399764(u8 *arg0) {
    u8 *v1 = arg0;
    int s0 = v1[0x20];
    int *vars = *(int **)(v1 + 0x68);
    int i;

    if (s0 != 1) {
        if (s0 < 2) {
            if (s0 == 0) {
                v1[0x30] = 0xFF;
                D_L11_001AED08 = 0;
                func_002A7750(v1, 1, -1);
            }
        }
        return;
    }
    if (D_00189E20.w2294 == 0x74 || D_00189E20.w24CC <= 0) {
        D_US2_001A9050 = 0;
        D_L11_001AED04 = 0;
    }
    if (D_L11_001B30C8 >= 6 && D_00189E20.w2294 == 0 && D_00189E20.w24CC <= 0) {
        D_US2_001A9050 = 1;
    }
    if (D_US2_001A904C != 0 && D_001A7A60[0x12] == 0) {
        int kind = 0xD07;

        for (i = 0; i < 40; i++) {
            u8 *e = D_L11_001B359C + (vars[1] << 8);
            u16 c = *(u16 *)(e + 0xAA);
            u8 *flags = D_001A7A60;

            if (c == 0xCF5 || c == 0xCF6 || (s16)c == kind) {
                if (((s8 *)e)[0x20] >= 0) {
                    vars[0]++;
                }
            }
            vars[1]++;
            if (D_L11_001B359C + (vars[1] << 8) >= D_L11_001B35A0) {
                if (vars[0] == 0 && flags[0x12] == 0) {
                    flags[0x12] = 1;
                    func_002E5E58(1, 0, 0);
                    func_002B0A18(0x1233, -1);
                    D_L11_001A903C = 1;
                }
                vars[1] = 0;
                vars[0] = 0;
            }
        }
    }
    if (D_L11_001AED08 < 12)
        return;
    if (D_001A7A60[0x14] != 0)
        return;
    D_001A7A60[0x14] = 1;
    func_002E5E58(1, 0, 0);
    func_002B0A18(0x1233, -1);
    D_L11_001A903C = 1;
}
