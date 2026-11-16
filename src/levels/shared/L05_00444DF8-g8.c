#include "common.h"

extern s32 g_current_map_index;
extern float g_ship_reticle_size_scale __attribute__((sda));

extern unsigned long GetEffectTextureDescriptor(s32);
extern float FastAddRotations(float, float);
extern void gfx_draw_rotated_screen_sprite(float, float, float, float, float, s32, s32, long, s32, s32, s32, s32, s32);

/* Draws the four quarter-turn copies of a sprite ring around the point, the same size each time. */
void DrawSpriteRing(u8 red, u8 green, u8 blue, u8 alpha, float x, float y, float scale, float angle)
{
    unsigned long sprite;
    float size;

    if (g_current_map_index == 0x14)
        sprite = GetEffectTextureDescriptor(0x41);
    else
        sprite = GetEffectTextureDescriptor(0x3F);
    size = g_ship_reticle_size_scale * scale;
    gfx_draw_rotated_screen_sprite(x, y, size, size, angle, 0x3F, 0x3F, sprite, 0xFFFFF3, red, green, blue, alpha);
    angle = FastAddRotations(angle, 1.5707964f);
    gfx_draw_rotated_screen_sprite(x, y, size, size, angle, 0x3F, 0x3F, sprite, 0xFFFFF3, red, green, blue, alpha);
    angle = FastAddRotations(angle, 1.5707964f);
    gfx_draw_rotated_screen_sprite(x, y, size, size, angle, 0x3F, 0x3F, sprite, 0xFFFFF3, red, green, blue, alpha);
    gfx_draw_rotated_screen_sprite(x, y, size, size, FastAddRotations(angle, 1.5707964f), 0x3F, 0x3F, sprite, 0xFFFFF3, red, green, blue, alpha);
}
