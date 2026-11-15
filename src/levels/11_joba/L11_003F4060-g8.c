#include "common.h"

extern void func_00282C88(void *a0);

extern void func_00282F20(f32 *dst, f32 *a, f32 len);

extern f32 func_00283180(f32 a0);

extern f32 func_00283198(f32 a0);

extern f32 func_00283B98(f32 a0, f32 a1);

extern f32 D_L11_001B05DC __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

void func_L11_003F4060(u8 *arg0) {
    u8 *s4 = arg0;
    u8 *s3 = *(u8 **)(s4 + 0x68);
    f32 vec[4];
    u8 *rec;
    u8 *p;
    s32 i, next;

    for (i = 0; i < 2; i = next) {
        s32 j;

        rec = s3 + 0xA0 + i * 0xA0;
        func_00282C88((TI128 *)vec);
        {
            u8 *flagRecord = s3 + i * 2;
            if (*(s16 *)(flagRecord + 0x278) != 1) {
                vec_scale_to_length(vec, (f32 *)(s4 + 0xE0), D_L11_001B05DC);
            }
        }
        next = i + 1;
        i = (s32)rec;
        p = (u8 *)i;
        for (j = 1; j >= 0; j--) {
            *(f32 *)(p + 0x40) = FastAddRotations(*(f32 *)(p + 0x40), *(f32 *)(p + 0x60));
            *(f32 *)(p + 0x44) = FastAddRotations(*(f32 *)(p + 0x44), *(f32 *)(p + 0x64));
            *(f32 *)(p + 0x48) = FastAddRotations(*(f32 *)(p + 0x48), *(f32 *)(p + 0x68));
            *(f32 *)(p + 0x20) = vec[0] + func_00283180(*(f32 *)(p + 0x40)) * *(f32 *)(p + 0x80);
            *(f32 *)(p + 0x24) = vec[1] + func_00283198(*(f32 *)(p + 0x44)) * *(f32 *)(p + 0x84);
            *(f32 *)(p + 0x28) = vec[2] - func_00283198(*(f32 *)(p + 0x48)) * *(f32 *)(p + 0x88);
            p += 0x10;
        }
    }
}
