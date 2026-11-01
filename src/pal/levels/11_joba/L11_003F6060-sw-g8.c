#include "include_asm.h"

#include "common.h"
extern f32 D_L11_001B0540 __attribute__((sda));
extern f32 D_L11_001B0544 __attribute__((sda));
extern f32 D_L11_001B0550 __attribute__((sda));
extern f32 D_L11_001B0554 __attribute__((sda));
extern f32 D_L11_001B0558 __attribute__((sda));
extern f32 func_00283B98(f32,f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 *func_L11_004417E8(s32);
extern void func_002833F0(void *,void *);

void func_PAL_L11_003F6DC8(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    f32 limit, speed, trig;
    switch (*(u8 *)(s0 + 0x42)) {
    case 1:
        speed = *(f32 *)(s1 + 0x254) - D_L11_001B0550 * 6.981318e-06f;
        limit = D_L11_001B0554 * 0.0003490659f;
        *(f32 *)(s1 + 0x254) = speed;
        if (speed > limit) *(f32 *)(s1 + 0x254) = limit;
        else if (speed < -limit) *(f32 *)(s1 + 0x254) = -limit;
        *(f32 *)(s1 + 0x250) = func_00283B98(*(f32 *)(s1 + 0x250), *(f32 *)(s1 + 0x254));
        break;
    case 2:
        speed = *(f32 *)(s1 + 0x254) + D_L11_001B0550 * 6.981318e-06f;
        limit = D_L11_001B0554 * 0.0003490659f;
        *(f32 *)(s1 + 0x254) = speed;
        if (speed > limit) *(f32 *)(s1 + 0x254) = limit;
        else if (speed < -limit) *(f32 *)(s1 + 0x254) = -limit;
        *(f32 *)(s1 + 0x250) = func_00283B98(*(f32 *)(s1 + 0x250), *(f32 *)(s1 + 0x254));
        break;
    case 0: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: break;
    }
    if (*(u8 *)(s0 + 0x20) == 5 || *(u8 *)(s0 + 0x20) == 9) return;
    if (*(s32 *)(s0 + 0xB8)) {
        trig = func_00283180(*(f32 *)(s1 + 0x250));
        *(f32 *)(s0 + 0x10) = D_L11_001B0558 * trig + func_L11_004417E8(*(s32 *)(s0 + 0xB8))[0];
        trig = func_00283198(*(f32 *)(s1 + 0x250));
        *(f32 *)(s0 + 0x14) = D_L11_001B0558 * trig + func_L11_004417E8(*(s32 *)(s0 + 0xB8))[1];
    }
    if (*(u8 *)(s0 + 0x95) == 2) {
        *(f32 *)(s0 + 0x18) = D_L11_001B0540;
        *(f32 *)(s0 + 0xF4) = -1.5707964897155762f;
        *(s32 *)(s0 + 0xF0) = 0;
        *(f32 *)(s0 + 0xF8) = *(f32 *)(s1 + 0x250);
        func_002833F0(s0 + 0xC0, s0 + 0xF0);
    } else if (*(u8 *)(s0 + 0x95) == 1) {
        *(f32 *)(s0 + 0x18) = D_L11_001B0544;
        *(f32 *)(s0 + 0xF4) = 1.5707964897155762f;
        *(s32 *)(s0 + 0xF0) = 0;
        *(f32 *)(s0 + 0xF8) = func_00283B98(3.1415927410125732f, *(f32 *)(s1 + 0x250));
        func_002833F0(s0 + 0xC0, s0 + 0xF0);
    }
}
