#include "common.h"

extern void vec_clear_128(void *a0);

extern void vec_scale_to_length(f32 *dst, f32 *a, f32 len);

extern f32 math_fast_sin_or_cos_a(f32 a0);

extern f32 math_fast_sin_or_cos_b(f32 a0);

extern f32 FastAddRotations(f32 a0, f32 a1);

extern f32 D_L11_001B05DC __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

/* Swings the points of each of the two beam arms around toward their target angles, around the object. */
void UpdateTwinRecordAnglesAndPositions(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 center[4];
    u8 *arm;
    u8 *joint;
    s32 i, nextIndex;

    for (i = 0; i < 2; i = nextIndex) {
        s32 j;

        arm = vars + 0xA0 + i * 0xA0;
        vec_clear_128((TI128 *)center);
        {
            u8 *flagRecord = vars + i * 2;
            if (*(s16 *)(flagRecord + 0x278) != 1) {
                vec_scale_to_length(center, (f32 *)(moby + 0xE0), D_L11_001B05DC);
            }
        }
        nextIndex = i + 1;
        i = (s32)arm;
        joint = (u8 *)i;
        for (j = 1; j >= 0; j--) {
            *(f32 *)(joint + 0x40) = FastAddRotations(*(f32 *)(joint + 0x40), *(f32 *)(joint + 0x60));
            *(f32 *)(joint + 0x44) = FastAddRotations(*(f32 *)(joint + 0x44), *(f32 *)(joint + 0x64));
            *(f32 *)(joint + 0x48) = FastAddRotations(*(f32 *)(joint + 0x48), *(f32 *)(joint + 0x68));
            *(f32 *)(joint + 0x20) = center[0] + math_fast_sin_or_cos_a(*(f32 *)(joint + 0x40)) * *(f32 *)(joint + 0x80);
            *(f32 *)(joint + 0x24) = center[1] + math_fast_sin_or_cos_b(*(f32 *)(joint + 0x44)) * *(f32 *)(joint + 0x84);
            *(f32 *)(joint + 0x28) = center[2] - math_fast_sin_or_cos_b(*(f32 *)(joint + 0x48)) * *(f32 *)(joint + 0x88);
            joint += 0x10;
        }
    }
}
