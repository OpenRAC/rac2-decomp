#include "include_asm.h"

#include "common.h"
typedef struct {
    float v[10];
} L02_Table10;
typedef struct {
    u8 pad00[0x34];
    s32 time;
} L02_Clock;
extern int g_current_map_index;
extern void DrawQuadWithRotatedUVs(void *, int, int, unsigned int, int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern L02_Table10 g_intro_frame_table;
extern float g_intro_overlay_value;
extern L02_Clock g_mob_list;
extern char g_intro_overlay_quad[8] __attribute__((sda));

/* The callback func_L02_00300CE8 queues while the game state is 2. It reads the frame counter at +0x34
   of D_L02_001BE200 (read afresh in every test, as retail does) and
   - for frames 0x10B-0x114, sets D_L02_001B2FE4 to that frame's entry of the ten-float table;
   - picks the overlay ids and the alpha for the frame's window: 1-0x136 id 0x46, cross-fading into id 0x47
     (alpha = (frame - 0x10E) / 40 * 127 of the new one, the rest for the old one) from frame 0x10F on;
     0x137-0x17C id 0x47; 0x17D-0x18F id 0x49 with a random extra in 0-2; 0x191-0x1B4 id 0x48, fading out
     (alpha 127 - (frame - 0x1A1) / 15 * 127, at least 0) after frame 0x1A1;
   - draws the ids (the second one with the complementary alpha) through func_L01_002E2608 with the colour
     (alpha << 24) | 0x808080.
   The window limits sit in variables: retail compares them through registers (`slt` with the limit in
   a2/a3) and keeps every test of the ladder separate, where constants would fold into range tests.
   The unit is built with -g: the line label that then precedes the first div.s (the scheduler moves the
   next line's `li` above it) makes the assembler pad it with the two nops retail has, and the second
   div.s, which has no label in front of it, stays unpadded. */
void cutscene_draw_intro_overlays_pal(void *unused) {
    L02_Table10 tab;
    int k, n, alpha, id, id2, extra;
    float frac;

    if (g_current_map_index == 2) {
        int first_end = 0x102, second_end = 0x13D, third_end = 0x14D;

        tab = g_intro_frame_table;
        if (g_mob_list.time >= 0xDE) {
            if (g_mob_list.time < 0xE8) {
                k = g_mob_list.time - 0xDE;
                if (k < 10)
                    g_intro_overlay_value = tab.v[k];
            }
        }
        id = -1;
        id2 = -1;
        alpha = 0x80;
        extra = 0;
        if (g_mob_list.time > 0 && g_mob_list.time <= first_end) {
            n = g_mob_list.time - 0xE1;
            id = 0x46;
            if (n > 0) {
                id = 0x47;
                frac = IntToFloat(n);
                frac = frac / IntToFloat(0x21);
                id2 = 0x46;
                alpha = FloatToInt(frac * 127.0f);
            }
        } else if (g_mob_list.time > first_end && g_mob_list.time <= second_end) {
            id = 0x47;
        } else if (g_mob_list.time > second_end && g_mob_list.time < third_end) {
            extra = math_random_int_range(0, 3);
            id = 0x49;
        } else if (g_mob_list.time > third_end && g_mob_list.time < 0x16C) {
            n = g_mob_list.time - 0x15C;
            id = 0x48;
            if (n > 0) {
                frac = IntToFloat(n);
                frac = frac / IntToFloat(0xC);
                alpha = 0x7F - FloatToInt(frac * 127.0f);
            }
            if (alpha < 0)
                alpha = 0;
        }
        if (id != -1) {
            if (id2 == -1 || id == id2) {
                DrawQuadWithRotatedUVs(g_intro_overlay_quad, id, 0, (alpha << 24) | 0x808080, extra);
            } else {
                DrawQuadWithRotatedUVs(g_intro_overlay_quad, id, 0, (alpha << 24) | 0x808080, extra);
                DrawQuadWithRotatedUVs(g_intro_overlay_quad, id2, 0, ((0x7F - alpha) << 24) | 0x808080, extra);
            }
        }
    }
}
