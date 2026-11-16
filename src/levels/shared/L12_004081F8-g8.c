#include "include_asm.h"
#include "common.h"

extern int g_blast_ground_effect_type_a __attribute__((sda));
extern int g_blast_ground_effect_type_b __attribute__((sda));
extern int g_blast_glow_param_a __attribute__((sda));
extern int g_blast_glow_param_b __attribute__((sda));
extern f32 g_blast_glow_size_scale __attribute__((sda));
extern f32 g_blast_glow_size_factor __attribute__((sda));
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_angle(void);
extern void ref_L12_004081F8_00(u8 *, int, f32, int, int, f32, f32, int, u8 *);

/* The func_L16_003E70E0 pair of glow layers with the sizes scaled by the level's factors. */
/* Draws the two glow layers around a blast projectile. */
void blast_projectile_draw_glow(u8 *moby) {
    ref_L12_004081F8_00(moby + 0x10, g_blast_ground_effect_type_a, g_blast_glow_size_scale * *(f32 *)(moby + 0x2C),
                        math_random_int_range(0x5F, 0x6F), g_blast_glow_param_a, math_random_angle(),
                        1.0f, 2, moby);
    {
        f32 size = g_blast_glow_size_scale * *(f32 *)(moby + 0x2C) * g_blast_glow_size_factor;

        ref_L12_004081F8_00(moby + 0x10, g_blast_ground_effect_type_b, size,
                            math_random_int_range(0x6F, 0x7F), g_blast_glow_param_b,
                            math_random_angle(), 1.0f, 2, moby);
    }
}
