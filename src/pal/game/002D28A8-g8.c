#include "include_asm.h"

#include "common.h"
extern char *g_resident_data_base;
extern int g_screen_width;
extern int g_extras_menu_title_y __attribute__((sda));
extern int g_extras_menu_cursor __attribute__((sda));
extern int g_extras_menu_enabled_flags[] SDATA(D_001ABA40);
extern int g_extras_menu_text_ids[] MACRO_ADDR;
extern float g_menu_alpha_scale;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);

/* Draws the five-entry Extras page: a title, a framed list and the entries, highlighting the cursor row. (PAL) */
int extras_menu_draw_pal(void)
{
    int i, y = 125;
    int *keys = g_extras_menu_text_ids;
    int *enabled = g_extras_menu_enabled_flags;
    float depth;

    SetupGifPaging(0);
    depth = 0.775f;
    gfx_draw_scaled_object_two_axes((char *)table_find_by_id(g_resident_data_base + 0x8710, 0x8B), 0x60442D00,
                 (float)(g_screen_width / 2), (float)g_extras_menu_title_y, 1.0f, g_menu_alpha_scale, depth);
    gfx_draw_scaled_object_two_axes((char *)table_find_by_id(g_resident_data_base + 0x8710, 0x8C), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)g_extras_menu_title_y, 1.0f, g_menu_alpha_scale, depth);
    gfx_draw_scaled_object_two_axes((char *)table_find_by_id(g_resident_data_base + 0x8710, 0x8D), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)g_extras_menu_title_y, 1.0f, g_menu_alpha_scale, depth);
    text_draw_centered_small(g_screen_width / 2, 65, 0x80F0F0F0UL, GetLocalizedString(0x111E), -1);
    text_draw_centered_small(g_screen_width / 2, 321, 0x80F0F0F0UL, GetLocalizedString(0xB86), -1);
    text_draw_centered_small(g_screen_width / 2, 346, 0x80F0F0F0UL, GetLocalizedString(0xB60), -1);
    AppendScreenRectPacket(312, 128, 449, 130, 0x55F0C070, 0);
    AppendScreenRectPacket(312, 265, 451, 267, 0x55F0C070, 0);
    AppendScreenRectPacket(312, 128, 314, 265, 0x55F0C070, 0);
    AppendScreenRectPacket(449, 128, 451, 265, 0x55F0C070, 0);
    for (i = 0; i < 5; i++, y += 31, keys++, enabled++) {
        unsigned long color = i == g_extras_menu_cursor ? 0x7000FFFFUL : 0x80F0F0F0UL;
        int key = *enabled ? *keys : 0xBD1;
        text_draw_centered_small(165, y, color, GetLocalizedString(key), -1);
    }
    DoGifPaging();
    return 0;
}
