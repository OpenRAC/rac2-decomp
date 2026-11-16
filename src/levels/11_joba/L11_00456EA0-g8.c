#include "common.h"

extern int g_ring_effect_sprite SDATA(D_L11_001B1DB4);
extern int g_ring_l11_effect_color SDATA(D_L11_001B1DB8);
extern float g_ring_effect_size SDATA(D_L11_001B1DBC);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);

/* Draws a pair of glowing sprites at each point of the ring effect, one large and one smaller. */
void joba_ring_effect_draw_sprites(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float *point;
    int i;
    float size, heading;
    for (i = 0; i < *(int *)(state + 0x80); i++) {
        point = (float *)(state + i * 16);
        heading = math_random_angle();
        gfx_draw_billboard_quad(point, g_ring_effect_sprite, g_ring_l11_effect_color, 1,
                       g_ring_effect_size, 0.08f, heading);
        size = g_ring_effect_size * 0.4f;
        heading = math_random_angle();
        gfx_draw_billboard_quad(point, g_ring_effect_sprite, 0x80808080, 1, size, 0.08f, heading);
    }
}
