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

extern void gfx_set_gs_register_constant(void);

extern s32 gfx_draw_billboard_quad_with_uv(f32 *, f32, s32, f32, f32, s32);

extern void matrix_mul_vec3(f32 *, f32 *, u8 *);

extern void FastVecAdd(u8 *, u8 *, u8 *);

extern f32 math_lerp_float(f32, f32, f32);

extern s32 FloatToInt(f32);

/* Walk the four controller entries, transform a cleared local vector with its Z
 * component scaled by the two controller lanes, then submit a weighted placement. */
void spark_lane_draw(u8 *moby) {
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
    gfx_set_gs_register_constant();
    lane = ctl + 0x20;
    for (; i >= 0; i--) {
        *(TI128 *)w = 0;
        w[2] = *(f32 *)(lane) * *(f32 *)(lane - 0x10);
        *(TI128 *)v = *(TI128 *)w;
        matrix_mul_vec3(v, v, obj + 0xC0);
        FastVecAdd(v, v, obj + 0x10);
        weight = math_lerp_float(D_L22_001AFF58, D_L22_001AFF5C, *(f32 *)(lane));
        phase = *(f32 *)(lane);
        if (phase < 0.1f)
            count = FloatToInt((f32)D_L22_001AFF60 * phase * 10.0f);
        else
            count = FloatToInt((f32)D_L22_001AFF60 * (1.0f - phase));
        gfx_draw_billboard_quad_with_uv(v, weight, count, D_L22_001AFF64, 0.08f, 0);
        lane += 4;
    }
}
