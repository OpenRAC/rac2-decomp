#include "include_asm.h"

typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(s32 a0);
extern u8 **func_L05_00379EB8(void);
extern s32 func_L00_004272A0(void);
extern void func_L05_0037B280(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_US2_L05_00422530(u8 *a0, s32 a1);
extern s32 D_L05_001B1364 __attribute__((sda));
extern s32 D_L05_00221D10[];
extern s32 D_L05_001B2048;
extern u8 *D_L05_001B2614;

void func_US2_L05_00422D38(u8 *arg0) {
    s32 n;
    s32 count;
    u8 **p;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        p = func_L05_00379EB8();
        count = func_L00_004272A0();
        if (count > 0) {
            n = count;
            do {
                if (*(s16 *)(*p + 0xAA) == 0xF73) {
                    func_L05_0037B280(*p, 1);
                    func_L05_0037CEE0(*p, (u8 *)D_L05_001B2614 + (D_L05_00221D10[0] << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*p, (u8 *)D_L05_001B2614 + (D_L05_00221D10[0] << 7) + 0x30, 64.0f);
                }
                n--;
                p++;
            } while (n);
        }
    }
    if (D_L05_00221D10[4] == 0 && D_L05_001B2048 >= 6)
        func_US2_L05_00422530(arg0, 2);
}
