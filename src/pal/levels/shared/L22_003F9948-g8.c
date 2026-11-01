#include "include_asm.h"

typedef unsigned char u8;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));
extern f32 func_00282C48(f32 f);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern void func_00283098(f32 *, const f32 *, const f32 *);
extern void func_00282CC0(char *, char *, char *);
extern f32 func_00283B98(f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern float ref_L22_003F5580_00 __attribute__((sda));
extern f32 func_00282DB0(void *, void *);
extern f32 func_00283CE0(int);
extern f32 func_002AA140(f32, f32, f32);
extern u8 D_L22_001B9C80[];
extern f32 D_L22_001B0A08 __attribute__((sda));
extern f32 D_L22_001B0A04 __attribute__((sda));
extern f32 D_L22_001B0A00 __attribute__((sda));
extern f32 D_L22_001B09FC __attribute__((sda));
extern u8 *D_L22_001B2794;
extern u8 *D_L22_001B2678;

/* Scales the controller of the object: when the controller is idle its position is copied to
 * the object, otherwise the controller's values are scaled and written back.
 */
void func_PAL_L22_003F9A10(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    f32 buf[4];
    f32 a, b, c, d, g, r;

    if (*(f32 *)(ctl + 0xBC) == 0.0f) {
        if (*(f32 *)(ctl + 0xC0) == 0.0f)
            return;
        *(TI128 *)(obj + 0xE0) = *(TI128 *)ctl;
        *(f32 *)(ctl + 0xC0) = 0.0f;
        return;
    }
    a = func_00283198(*(f32 *)(ctl + 0xC4));
    b = *(f32 *)(ctl + 0xBC);
    c = func_00283180(*(f32 *)(ctl + 0xB0));
    b = b * a;
    c = c * b;
    buf[0] = c;
    d = func_00283198(*(f32 *)(ctl + 0xB0));
    d = d * b;
    buf[1] = d;
    buf[2] = 0.0f;
    func_00283098(buf, buf, obj + 0xC0);
    buf[3] = 0.0f;
    func_00282CC0(obj + 0xE0, buf, ctl);
    r = func_00283B98(*(f32 *)(ctl + 0xC4), *(f32 *)(ctl + 0xC0));
    g = ref_L22_003F5580_00;
    *(f32 *)(ctl + 0xC4) = r;
    func_002AA2E8((f32 *)(ctl + 0xBC), 0.0f, g * (0.020000001f));
}
