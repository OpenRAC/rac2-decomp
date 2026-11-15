#include "include_asm.h"
#include "common.h"

extern int D_L16_001B1460 __attribute__((sda));
extern int D_L16_001B1464 __attribute__((sda));
extern int D_L16_001B1498 __attribute__((sda));
extern int D_L16_001B149C __attribute__((sda));
extern f32 D_L16_001B14A0 __attribute__((sda));
extern f32 D_L16_001B14A4 __attribute__((sda));
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_angle(void);
extern void gfx_draw_beam_quads_glows(u8 *, int, f32, int, int, f32, f32, int, u8 *);

/* The level-16 copy of func_L12_004081F8: the func_L16_003E70E0 pair of glow layers with the sizes scaled by the level's factors. */
/* Draws two glow layers at the object's position with random brightness. */
void gfx_draw_two_glow_layers(u8 *object) {
    gfx_draw_beam_quads_glows(object + 0x10, D_L16_001B1460, D_L16_001B14A0 * *(f32 *)(object + 0x2C),
                        math_random_int_range(0x5F, 0x6F), D_L16_001B1498, math_random_angle(),
                        1.0f, 2, object);
    {
        f32 size = D_L16_001B14A0 * *(f32 *)(object + 0x2C) * D_L16_001B14A4;

        gfx_draw_beam_quads_glows(object + 0x10, D_L16_001B1464, size,
                            math_random_int_range(0x6F, 0x7F), D_L16_001B149C,
                            math_random_angle(), 1.0f, 2, object);
    }
}
