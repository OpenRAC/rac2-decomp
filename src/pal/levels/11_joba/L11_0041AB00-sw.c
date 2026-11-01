#include "include_asm.h"

#include "common.h"
extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *func_002A9640(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002E59B0(u8 *arg0, s32 arg1);
extern s32 func_002E5CF8(s32 arg0, s32 arg1, u8 *arg2);
extern s32 func_00283CF0(f32 arg0);
extern f32 func_00282E48(u8 *arg0, u8 *arg1);
extern s32 func_L11_003F2E00(u8 *arg0);
extern u8 D_L11_00188660[];
extern u8 D_L11_001BA8C0[];
extern s32 D_L11_001A8FF0 __attribute__((sda));
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern f32 func_002B04E0(u8 *a0, f32 *a1, s32 a2);
extern f32 func_00282E80(u8 *a0, u8 *a1);
extern u8 D_L11_00189EA0[];
extern u8 *D_L11_001B359C[] __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[][16];
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002B38B8(u8 *);
extern f32 func_00283BE0(f32, f32);
extern f32 func_002AA548(void *, void *, f32, f32, f32, f32);

/* Defined in L11_003F4F30-g8.c. */

/* func_L11_003F7B70 is in L11_003F7B70-g8.c. */

/* Defined in L11_003F7F58.c. */

/* Defined in L11_003F8150.c. */

/* Defined in L11_003F8510-g8.c. */

/* Defined in L11_00411D40-g8.c. */

/* Defined in L11_00412B20-g8.c. */

/* Defined in L11_00415E70.c. */


/* Steps a seven-state swing, easing the angle at 0xF0 between -90 and -75/-85 degrees, then
   places the linked table entity at this one's position, offset along two of its axes. */
void func_PAL_L11_0041B670(u8 *arg0) {
    f32 tmp[4], tmp2[4];
    u8 *s2 = arg0;
    u8 *s1 = *(u8 **)(s2 + 0x68);
    u8 *s0 = D_L11_001B359C[0] + *(s32 *)s1 * 256;
    u8 *pos;

    switch (*(u8 *)(s2 + 0x20)) {
    case 0:
        func_002A7750(s2, 1, -1);
        break;
    case 1:
        if (func_002B38B8(s0)) {
            func_002E5CF8(0, 0, s2);
            func_002A7750(s2, 2, -1);
        }
        if (D_0019B2E8[D_001A79F0[0]][*(u8 *)(s2 + 0xB0)] & 0x80) {
            *(f32 *)(s2 + 0xF0) = func_00283BE0(*(f32 *)(s2 + 0xF0), 1.5707965f);
            func_002A7750(s2, 6, -1);
        }
        break;
    case 2:
        func_002AA548(s2 + 0xF0, s1 + 4, -1.5707965f, 0.000767945f,
                      251.32744f, 349.06592f);
        if (*(f32 *)(s2 + 0xF0) <= -1.5707965f) {
            *(s32 *)(s1 + 4) = 0;
            func_002A7750(s2, 3, -1);
            func_002E5CF8(1, 0, s2);
        }
        break;
    case 3:
        func_002AA548(s2 + 0xF0, s1 + 4, -1.308997f, 0.025132746f,
                      0.00062831864f, 1.0471977f);
        if (*(f32 *)(s2 + 0xF0) >= -1.308997f) {
            *(s32 *)(s1 + 4) = 0;
            func_002A7750(s2, 4, -1);
        }
        break;
    case 4:
        func_002AA548(s2 + 0xF0, s1 + 4, -1.5707965f, 0.00062831864f,
                      0.25132746f, 3.4906592f);
        if (*(f32 *)(s2 + 0xF0) <= -1.5707965f) {
            *(s32 *)(s1 + 4) = 0;
            func_002A7750(s2, 5, -1);
            func_002E5CF8(1, 0, s2);
        }
        break;
    case 5:
        func_002AA548(s2 + 0xF0, s1 + 4, -1.48353f, 0.025132746f,
                      0.00062831864f, 1.0471977f);
        if (*(f32 *)(s2 + 0xF0) >= -1.48353f) {
            *(s32 *)(s1 + 4) = 0;
            func_002A7750(s2, 6, -1);
        }
        break;
    case 6:
        func_002AA548(s2 + 0xF0, s1 + 4, -1.5707965f, 0.00062831864f,
                      0.25132746f, 3.4906592f);
        if (*(f32 *)(s2 + 0xF0) <= -1.5707965f) {
            *(s32 *)(s1 + 4) = 0;
            func_002A7750(s2, 7, -1);
            func_002E5CF8(1, 0, s2);
        }
        break;
    }
    pos = s0 + 0x10;
    qcopy(pos, s2 + 0x10);
    func_00282F20(tmp, s2 + 0xE0, 5.7f);
    func_00282CC0(pos, pos, tmp);
    func_00282F20(tmp2, s2 + 0xD0, 0.35f);
    func_00282CC0(pos, pos, tmp2);
}
