#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef unsigned char u8;
typedef float f32;

/* The four words the two passes hand to func_L16_003E7248, all read through $gp. */
extern int g_effect_texture_a __attribute__((sda));

extern int g_effect_texture_b __attribute__((sda));

extern int g_ground_effect_texture_a __attribute__((sda));

extern int g_ground_effect_texture_b __attribute__((sda));

extern s32 math_random_int_range(s32, s32);

extern f32 math_random_angle(void);

extern void DrawLayeredBeam(u8 *, int, f32, int, int, f32, f32, int, u8 *);

/* Draws the object's two sprites: each pass rolls a fresh value for its frame range and hands
   the object's position, the rolled value, the two $gp words and the drawer's depth/size
   arguments on. */
/* Draws the two layered sprites of a moving effect object, each with a random frame. */
void gfx_draw_two_layered_sprites(u8 *object) {
    DrawLayeredBeam(object + 0x10, g_ground_effect_texture_a, *(f32 *)(object + 0x2C),
                      math_random_int_range(0x5F, 0x6F), g_effect_texture_a, math_random_angle(),
                      1.0f, 2, object);
    {
        f32 half = *(f32 *)(object + 0x2C) * 0.5f;

        DrawLayeredBeam(object + 0x10, g_ground_effect_texture_b, half,
                          math_random_int_range(0x6F, 0x7F), g_effect_texture_b,
                          math_random_angle(), 1.0f, 2, object);
    }
}
