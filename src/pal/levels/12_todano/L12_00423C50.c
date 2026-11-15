#include "include_asm.h"

#include "common.h"
extern int g_current_map_index __attribute__((sda));
extern char D_0019B4A8[];
extern char g_hero_position[];
extern void FastVecSub(f32 *, const f32 *, const f32 *);
extern void vec_transform_and_set_height(char *, char *, char *, char *, f32);
extern void vec_scale_to_length(f32 *, f32 *, f32);
extern void func_PAL_002B15D8(void *, s32, void *, f32, f32, f32, f32, s32);
extern s32 *D_L12_001FEAC0[];
extern s32 *D_L12_001FEAC0[];
extern s32 CollLine(void *from, void *to, s32 mode, void *self, s32 flags);
extern s32 *D_L12_001FEAC0[];
extern char g_hero_position[];
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern s32 math_random_int_range(s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));
extern u8 D_001395DB;
extern s32 math_random_int_below(s32);
extern s32 FloatToInt(f32);
extern u8 *SpawnSpinningSparkParticle(void *, f32, f32, f32, s32, void *, f32, u32, s32);

void func_PAL_L12_00423C50(u8 *a0) {
    u8 *self = a0;
    f32 buf[4];
    u16 f;

    FastVecSub(buf, (f32 *)(self + 0x10), (f32 *)g_hero_position);
    vec_transform_and_set_height((char *)self, (char *)buf, (char *)buf, 0, 0.0f);
    vec_scale_to_length(buf, buf, 0.120000005f);
    func_PAL_002B15D8(self, 31, buf, 6.0f, 12.0f, 6.0f, 12.0f, 255);

    f = *(u16 *)(self + 0xB2);
    if (f & 1) {
        u8 *p = (u8 *)(((s16)f >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
        u8 c = *p;

        if (((c >> 4) & 7) != 7)
            *p = c + 0x10;
    } else {
        u8 *p = (u8 *)(((s16)f >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
        u8 c = *p;

        if ((c & 7) != 7)
            *p = c + 1;
    }
    PlayMobySound(1, 0, self);
}





