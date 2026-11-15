#include "common.h"
extern char *D_001A8CFC;
extern int g_screen_width;
extern int D_001ABA54 __attribute__((sda));
extern int D_001ABA3C __attribute__((sda));
extern int D_001ABA40[] SDATA(D_001ABA40);
extern int D_001ABD28[] MACRO_ADDR;
extern float D_001B23A8;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);

/* Draws the five-entry Extras page: a title, a framed list and the entries, highlighting the cursor row. */
int extras_menu_draw(void)
{
    int i, y = 125;
    int *text_ids = D_001ABD28;
    int *enabled_flags = D_001ABA40;
    float z;

    SetupGifPaging(0);
    z = 0.775f;
    gfx_draw_scaled_object_two_axes((char *)table_find_by_id(D_001A8CFC + 0x8710, 0x8B), 0x60442D00,
                 (float)(g_screen_width / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    gfx_draw_scaled_object_two_axes((char *)table_find_by_id(D_001A8CFC + 0x8710, 0x8C), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    gfx_draw_scaled_object_two_axes((char *)table_find_by_id(D_001A8CFC + 0x8710, 0x8D), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    text_draw_centered_small(g_screen_width / 2, 65, 0x80F0F0F0UL, GetLocalizedString(0x320C), -1);
    text_draw_centered_small(g_screen_width / 2, 321, 0x80F0F0F0UL, GetLocalizedString(0x2D75), -1);
    text_draw_centered_small(g_screen_width / 2, 346, 0x80F0F0F0UL, GetLocalizedString(0x2D4F), -1);
    AppendScreenRectPacket(312, 128, 449, 130, 0x55F0C070, 0);
    AppendScreenRectPacket(312, 265, 451, 267, 0x55F0C070, 0);
    AppendScreenRectPacket(312, 128, 314, 265, 0x55F0C070, 0);
    AppendScreenRectPacket(449, 128, 451, 265, 0x55F0C070, 0);
    for (i = 0; i < 5; i++, y += 31, text_ids++, enabled_flags++) {
        unsigned long color = i == D_001ABA3C ? 0x7000FFFFUL : 0x80F0F0F0UL;
        int text_id = *enabled_flags ? *text_ids : 0x2DC0;
        text_draw_centered_small(165, y, color, GetLocalizedString(text_id), -1);
    }
    DoGifPaging();
    return 0;
}
