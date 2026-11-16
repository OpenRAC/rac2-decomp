#include "include_asm.h"
#include "common.h"

extern int g_snivelak_glow_texture_a __attribute__((sda));
extern int g_snivelak_glow_texture_b __attribute__((sda));
extern int g_glow_layer_texture_a __attribute__((sda));
extern int g_glow_layer_texture_b __attribute__((sda));
extern f32 g_glow_size_scale __attribute__((sda));
extern f32 g_glow_size_factor __attribute__((sda));
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_angle(void);
extern void gfx_draw_beam_quads_glows(u8 *, int, f32, int, int, f32, f32, int, u8 *);

/* The level-16 copy of func_L12_004081F8: the func_L16_003E70E0 pair of glow layers with the sizes scaled by the level's factors. */
/* Draws two glow layers at the object's position with random brightness. */
void gfx_draw_two_glow_layers(u8 *object) {
    gfx_draw_beam_quads_glows(object + 0x10, g_snivelak_glow_texture_a, g_glow_size_scale * *(f32 *)(object + 0x2C),
                        math_random_int_range(0x5F, 0x6F), g_glow_layer_texture_a, math_random_angle(),
                        1.0f, 2, object);
    {
        f32 size = g_glow_size_scale * *(f32 *)(object + 0x2C) * g_glow_size_factor;

        gfx_draw_beam_quads_glows(object + 0x10, g_snivelak_glow_texture_b, size,
                            math_random_int_range(0x6F, 0x7F), g_glow_layer_texture_b,
                            math_random_angle(), 1.0f, 2, object);
    }
}
