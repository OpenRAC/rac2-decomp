#include "include_asm.h"

typedef unsigned char u8;
typedef int s32;
extern u8 *D_L23_001B1484 __attribute__((sda));
extern u8 *D_L23_001B1484_2;
extern s32 D_L23_001B1958 __attribute__((sda));
extern s32 D_L23_001B1954 __attribute__((sda));
extern s32 D_0018C0B0 __attribute__((nosda));
extern s32 D_L23_001B1430 __attribute__((sda));
extern s32 func_L23_0041B948(void);
extern s32 func_L23_0041C0C0(void);
extern s32 func_L23_0041C0B0(void);
extern s32 D_L23_001B194C __attribute__((sda));
extern s32 D_L23_001B1950 __attribute__((sda));
extern s32 D_L23_001A8AB0[4] __attribute__((sda));
extern s32 D_L23_001A8AC0[4] __attribute__((sda));
extern s32 D_L23_001B3714;
extern s32 D_L23_001B13E8 __attribute__((sda));
extern void func_002E5CF8(int, int, u8 *);
extern s32 func_002A77E0(s32);
extern s32 D_L23_001A8AB4[3] __attribute__((sda));
extern s32 D_L23_001A8AC4[3] __attribute__((sda));
extern s32 D_L23_001A8FF0;
extern u8 *func_0029EFD0(s32);
extern s32 func_L00_0035F5A0(s32, s32, s32);
extern s32 D_L23_001B19C4 __attribute__((sda));
extern s32 D_L23_001B19C8 __attribute__((sda));
extern s32 D_L23_001B19D8 __attribute__((sda));

/* publishes the boot stamp once, seeding the shared state first */
void func_PAL_L23_00423838(void) {
    if (D_L23_001B3714 == 0) {
        u8 *state = D_L23_001B1484;

        if (state != 0) {
            func_002E5CF8(0x10, 0, state);
        }
    }
    D_L23_001B3714 = ((s32)(D_L23_001B13E8) * 5 + 2) / 6;
}
