/* func_0033B910: draw the 21-row menu panel and its frame lines. */
#include "common.h"

#ifndef RAC2_T_ENTRY_F624A0727
#define RAC2_T_ENTRY_F624A0727
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;
#endif

typedef struct {
    int x;
    int y;
    int text;
    float scale;
} Row_0033B910;

extern void gfx_draw_screen_element_stored(char *);
extern void text_label_draw(char *);
extern void hud_draw_colored_quad_widget(char *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(char *, int, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern int *object_get_fourth_field(char *);
extern float *object_get_first_field(char *);
extern void gfx_draw_screen_line(int, int, int, int, unsigned long long, int);
extern Row_0033B910 g_map_spot_table[];
extern unsigned char g_map_visited_flags[] MACRO_ADDR;
extern unsigned char g_map_unlocked_flags[] MACRO_ADDR;
extern char g_map_overlay_state[];

static __inline__ void SetColor_0033B910(char *w, int c)
{
    *object_get_fourth_field(w) = c;
}

/* Draws the map screen: title, labels, each of the 21 map spots, and the frame lines. */
void map_screen_draw(char *screen)
{
    int i;
    char *game;

    gfx_draw_screen_element_stored(screen);
    gfx_draw_screen_element_stored(screen + 0x4C);
    gfx_draw_screen_element_stored(screen + 0x98);
    text_label_draw(screen + 0x1D8);
    text_label_draw(screen + 0x220);
    text_label_draw(screen + 0x268);
    hud_draw_colored_quad_widget(screen + 0x2B0);
    for (i = 0; i < 21; i++) {
        object_set_first_float4(screen + 0x2EC, (float)g_map_spot_table[i].x + (*(float **)(screen + 0x1C8))[0],
                      (float)g_map_spot_table[i].y + (*(float **)(screen + 0x1C8))[1], 0.0f, 0.0f);
        hud_set_widget_value_pair(screen + 0x2EC, 0xE99E, g_map_spot_table[i].text);
        object_set_second_float4(screen + 0x2EC, g_map_spot_table[i].scale, g_map_spot_table[i].scale, 0.0f, 0.0f);
        if (g_map_unlocked_flags[i] == 0)
            SetColor_0033B910(screen + 0x2EC, 0x70A0C0C0);
        else
            SetColor_0033B910(screen + 0x2EC, 0x7029A1FF);
        if (g_map_visited_flags[i] != 0)
            hud_draw_colored_quad_widget(screen + 0x2EC);
    }
    game = g_map_overlay_state;
    if (*(int *)(game + 0x230) < 21) {
        char *first = screen + 0xE4;
        char *mid = screen + 0x130;
        char *bar = screen + 0x17C;
        char *q = screen + 0x114;
        char *r = first;
        int k;

        for (k = 2; k >= 0; k--) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
            r += 76;
            q += 76;
        }
        gfx_draw_screen_line((int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(mid)[1] + 6.0f),
                      (int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(first)[1] - 4.0f), 0x180000FF, 0);
        gfx_draw_screen_line((int)(object_get_first_field(bar)[0] + 8.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f),
                      (int)(object_get_first_field(bar)[0] + 304.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f), 0x180000FF, 0);
        gfx_draw_screen_line((int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(mid)[1] + 6.0f),
                      (int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(first)[1] - 4.0f), 0x180000FF, 0);
        gfx_draw_screen_line((int)(object_get_first_field(bar)[0] + 8.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f),
                      (int)(object_get_first_field(bar)[0] + 304.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f), 0x180000FF, 0);
    }
}
