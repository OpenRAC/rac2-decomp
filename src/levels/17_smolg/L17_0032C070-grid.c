#include "common.h"

/* The screen rectangle is one array: an element read with an offset is two instructions and
   never fills a slot. The scroll word's pointer is set outside the inner loop: loop hoists it, it
   gets no register, and reload builds the address beside the load. */

extern int g_screen_width[] MACRO_ADDR;
extern int g_tile_grid_scroll[];
extern float IntToFloat(int);
extern int FloatToInt(float);
extern unsigned long GetEffectTextureDescriptor(int);
extern int math_random_int_below(int);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws a grid of small square tiles over the whole screen. Each tile fades according to the
   object's timer and shows a random part of the texture. */
void gfx_draw_fading_tile_grid(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float screen_size[2];
    unsigned long packet;
    int columns, rows, i, j;
    float cell_pos[2];
    float scroll, alpha_num, alpha_den;
    int color;
    int tex_u, tex_v;

    screen_size[0] = IntToFloat(g_screen_width[2]);
    screen_size[1] = IntToFloat(g_screen_width[3]);
    packet = GetEffectTextureDescriptor(0x1E);
    columns = g_screen_width[0] / 32 + 1;
    rows = g_screen_width[1] / 32 + 1;

    for (i = 0; i < columns; i++) {
        int *scroll_ptr = g_tile_grid_scroll;
        for (j = 0; j < rows; j++) {
            cell_pos[0] = (float)(i * 32);
            cell_pos[1] = (float)(j * 32);
            scroll = (float)*scroll_ptr;
            alpha_num = IntToFloat(*(int *)(vars + 0x140));
            alpha_den = IntToFloat(0x5A);
            color = (FloatToInt(alpha_num * 127.5f / alpha_den) << 24) + 0xFF7F7F;
            tex_u = math_random_int_below(0x20);
            tex_v = math_random_int_below(0x20);
            DrawTexturedQuad(FloatToInt(cell_pos[0] - scroll), FloatToInt(cell_pos[1] - scroll), 0x20, 0x20, tex_u, tex_v, 0x20, 0x20, color, packet);
        }
    }
}
