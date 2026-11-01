#include "include_asm.h"

#include "common.h"
extern u32 D_L03_001B0C48 __attribute__((sda));
extern u32 D_L03_001B0C4C NOT_SDA;
extern u32 D_L03_001B0C50 NOT_SDA;
extern u32 D_L03_001B0C54 NOT_SDA;
extern u32 D_L03_001B0C58 NOT_SDA;
extern u32 D_L03_001B0C5C NOT_SDA;
extern f32 D_L03_001B0C60 __attribute__((sda));
extern f32 D_L03_001B0C64 NOT_SDA;
extern f32 func_00283B98(f32, f32);
extern int ref_L01_0031BC68_00(int, int, f32);

/* Eases the record's own rate by the shared factor and hands the state the
   shared lookup asks for. */
void func_PAL_L03_003E8B88(u8 *a0) {
    u8 *rec = *(u8 **)(a0 + 0x68);
    u32 c[2];
    f32 f13;
    f32 r;

    if (a0[0x20] == 5 || *(short *)(rec + 0x6A) == 0) {
        c[0] = D_L03_001B0C48;
        c[1] = D_L03_001B0C4C;
        f13 = D_L03_001B0C60 * 0.0003490659f;
    } else if (*(short *)(rec + 0x68) != 0) {
        c[0] = D_L03_001B0C50;
        c[1] = D_L03_001B0C54;
        f13 = D_L03_001B0C64 * 0.0003490659f;
    } else {
        c[0] = D_L03_001B0C58;
        c[1] = D_L03_001B0C5C;
        f13 = D_L03_001B0C64 * 0.0003490659f;
    }
    r = func_00283B98(*(f32 *)(rec + 0x78), f13);
    *(f32 *)(rec + 0x78) = r;
    *(u32 *)(a0 + 0x78) = ref_L01_0031BC68_00(c[0], c[1], r);
}
