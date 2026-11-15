/* -mno-split-addresses keeps the absolute factor load inside the loop.
 * The interleaved placement-call prototype preserves both EE argument banks.
 */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* the level's two blend words and the scale the placement call takes, all through $gp,
 * and the absolute factor the blend call takes. */
extern f32 D_L22_001AFF58 __attribute__((sda));

extern s32 D_L22_001AFF60 __attribute__((sda));

extern f32 D_L22_001AFF64 __attribute__((sda));

extern f32 D_L22_001AFF5C NOT_SDA;

extern void func_002820A0(void);

extern s32 func_002820D0(f32 *, f32, s32, f32, f32, s32);

extern void func_00283098(f32 *, f32 *, u8 *);

extern void func_00282CC0(u8 *, u8 *, u8 *);

extern f32 func_002AA140(f32, f32, f32);

extern s32 func_00283CF0(f32);

/* Walk the four controller entries, transform a cleared local vector with its Z
 * component scaled by the two controller lanes, then submit a weighted placement. */
void func_L22_003C9D48(u8 *moby) {
    u8 *obj = moby;
    s32 i = 3;
    u8 *lane;
    u8 *ctl;
    f32 v[4];
    f32 w[4];
    f32 weight;
    f32 phase;
    s32 count;

    ctl = *(u8 **)(obj + 0x68);
    SetGsRegisterConstant();
    lane = ctl + 0x20;
    for (; i >= 0; i--) {
        *(TI128 *)w = 0;
        w[2] = *(f32 *)(lane) * *(f32 *)(lane - 0x10);
        *(TI128 *)v = *(TI128 *)w;
        matrix_mul_vec3(v, v, obj + 0xC0);
        FastVecAdd(v, v, obj + 0x10);
        weight = LerpFloat_002AA140(D_L22_001AFF58, D_L22_001AFF5C, *(f32 *)(lane));
        phase = *(f32 *)(lane);
        if (phase < 0.1f)
            count = FloatToInt((f32)D_L22_001AFF60 * phase * 10.0f);
        else
            count = FloatToInt((f32)D_L22_001AFF60 * (1.0f - phase));
        DrawBillboardQuadWithUv(v, weight, count, D_L22_001AFF64, 0.08f, 0);
        lane += 4;
    }
}
