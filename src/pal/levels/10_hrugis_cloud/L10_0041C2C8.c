#include "include_asm.h"

#include "common.h"
extern u8 *func_002ED688(u8 *);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern f32 func_00282E48(void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_002831B0(f32);
extern f32 func_00282DF0(void *);
extern u8 D_L10_001B9680[];
extern f32 func_00335320(void);
extern u8 *func_0037B670();
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern u8 *D_L10_0020B1E0[];
extern u8 *D_001B251C;
extern u8 D_L10_00265BA0[];
extern u8 D_L10_00188660[];
extern u8 D_L10_00221CD0[];
extern u8 D_00188660[];
extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern u8 *D_001B2614 __attribute__((sda));
extern u8 *func_002ED688(u8 *arg0);
extern f32 func_002A7940(void);
extern f32 func_00283180(f32 f12);
extern f32 func_00309B38(f32 f12, f32 f13);
extern u8 func_L10_00423780(void);

/* func_L10_004170F8 is in L10_003170D0-path-g8.c. */

/* func_L10_004174C8 is in L10_003170D0-g8.c: it only comes out right with -G8. */

void func_PAL_L10_0041C2C8(u8 *arg0) {
    u8 *s = *(u8 **)(arg0 + 0x68);

    switch (arg0[0x20]) {
    case 1:
        *(f32 *)(s + 0x2CC) = *(f32 *)(s + 0x2CC) + 5.5850545e-05f;
        *(f32 *)(s + 0x2D0) = *(f32 *)(s + 0x2D0) + 5.5850545e-05f;
        if (*(f32 *)(s + 0x2CC) > 0.027925273f)
            *(f32 *)(s + 0x2CC) = 0.027925273f;
        if (*(f32 *)(s + 0x2D0) > 0.013962637f)
            *(f32 *)(s + 0x2D0) = 0.013962637f;
        break;
    case 2:
        *(f32 *)(s + 0x2CC) = *(f32 *)(s + 0x2CC) - 8.377582e-05f;
        *(f32 *)(s + 0x2D0) = *(f32 *)(s + 0x2D0) - 8.377582e-05f;
        if (*(f32 *)(s + 0x2CC) < 0.0f)
            *(f32 *)(s + 0x2CC) = 0.0f;
        if (*(f32 *)(s + 0x2D0) < 0.0f)
            *(f32 *)(s + 0x2D0) = 0.0f;
        break;
    }
}

