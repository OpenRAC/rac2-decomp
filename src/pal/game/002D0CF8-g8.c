#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, u64, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern int func_001157AC(char *);
extern int text_measure_width_medium(char *, int);
extern void menu_draw_text_highlight_frame(int, int);
extern void menu_draw_scroll_arrows_and_frame(void);
extern char *D_001A8CFC;
extern int g_screen_width;
extern float D_001B23A8;
extern void gfx_disable_screen_flag(void);
extern void gfx_enable_screen_flag(void);
extern int save_count_nonzero_flags(void);
extern int sprintf(char *, char *, ...);
extern void AppendScreenRectPacket(int, int, int, int, u64, int);
extern int D_001AB9FC __attribute__((sda));
extern int D_001ABA00 __attribute__((sda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern short D_0026CF18[][3];
extern void text_draw_small(int, int, u64, char *, int);

int func_PAL_002D0CF8(void) {
    char buf[64];
    int r, i, y, k, color;
    char *text;
    float z;
    SetupGifPaging(0);
    z = 0.0f;
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xD7);
    gfx_draw_scaled_object_two_axes(r, 0x60442D00, (float)(g_screen_width / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xD8);
    gfx_draw_scaled_object_two_axes(r, 0x60241700, (float)(g_screen_width / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xD9);
    gfx_draw_scaled_object_two_axes(r, 0x55F0C070, (float)(g_screen_width / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xDA);
    gfx_draw_scaled_object_two_axes(r, 0x55F0C070, (float)(g_screen_width / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    gfx_disable_screen_flag();
    text_draw_centered_small(0xB9, 0x1B, 0x80F0F0F0ULL, GetLocalizedString(0xC20), -1);
    text = GetLocalizedString(0xE54);
    sprintf(buf, text, save_count_nonzero_flags(), 30);
    text_draw_small(0x46, 0x175, 0x80F0F0F0ULL, buf, -1);
    gfx_enable_screen_flag();
    text_draw_centered_small(0x1AD, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    AppendScreenRectPacket(0x15E, 0xDA, 0x1E6, 0xDC, 0x55F0C070ULL, 0);
    if (D_0026CF18[D_001AB9FC][2] != -1)
        text_draw_centered_medium(0x1A0, 0xE0, 0x80F0F0F0ULL, GetLocalizedString(D_0026CF18[D_001AB9FC][2]), -1);
    menu_draw_scroll_arrows_and_frame();
    for (y = 0x112, i = 0; i < 5; i++, y += 20) {
        char *label;
        k = i + D_001AB9FC - 2;
        if (k < 0) k += 30;
        if (k >= 30) k -= 30;
        color = 0x80F0F0F0;
        label = GetLocalizedString(D_0026CF18[k][0]);
        if (D_001A7A60[k]) color = 0x7029A1FF;
        color &= 0xFFFFFF;
        if (i == 0 || i == 4) color |= 0x10000000;
        else if (i == 1 || i == 3) color |= 0x50000000;
        else {
            color |= 0x70000000;
            menu_draw_text_highlight_frame(text_measure_width_medium(label, func_001157AC(label)), color);
        }
        text_draw_centered_medium(g_screen_width / 2, y, color, label, -1);
    }
    DoGifPaging();
    return 0;
}
