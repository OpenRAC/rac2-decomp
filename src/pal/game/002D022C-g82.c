#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, u64, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern int func_001157AC(char *);
extern char *g_resident_data_base;
extern int g_screen_width;
extern float g_menu_alpha_scale;
extern void gfx_disable_screen_flag(void);
extern void gfx_enable_screen_flag(void);
extern int save_count_nonzero_flags(void);
extern int sprintf(char *, char *, ...);
extern void text_draw_medium(int, int, u64, char *, int);
extern int g_unlockable_options_cursor __attribute__((sda));
extern int g_menu_title_y_b __attribute__((sda));
extern unsigned char g_item_enabled_flags[] MACRO_ADDR;
extern unsigned char g_unlocked_item_flags[] MACRO_ADDR;
extern char g_str_localized_text_fmt[];
extern char g_str_count_fmt[];
typedef struct {
    short text;
    unsigned char index;
    unsigned char limit;
} MenuOption;
extern MenuOption g_unlockable_shop_table[] MACRO_ADDR;

/* Draws the unlockable options menu: twelve options with on or off, or the skill points still needed to unlock them. (PAL) */
int DrawUnlockableOptionsMenu_pal(void)
{
    char buf[64];
    int r, i, y, color, limit, available;
    u64 style;
    float depth;

    available = save_count_nonzero_flags();
    depth = 0.84f;
    SetupGifPaging(0);
    r = table_find_by_id(g_resident_data_base + 0x8710, 0x8B);
    gfx_draw_scaled_object_two_axes((char *)r, 0x60442D00, (float)(g_screen_width / 2), (float)g_menu_title_y_b, 1.0f, g_menu_alpha_scale, depth);
    r = table_find_by_id(g_resident_data_base + 0x8710, 0x8C);
    gfx_draw_scaled_object_two_axes((char *)r, 0x55F0C070, (float)(g_screen_width / 2), (float)g_menu_title_y_b, 1.0f, g_menu_alpha_scale, depth);
    r = table_find_by_id(g_resident_data_base + 0x8710, 0x8D);
    gfx_draw_scaled_object_two_axes((char *)r, 0x55F0C070, (float)(g_screen_width / 2), (float)g_menu_title_y_b, 1.0f, g_menu_alpha_scale, depth);
    text_draw_centered_small(g_screen_width / 2, 0x41, 0x80F0F0F0ULL, GetLocalizedString(0xC22), -1);
    text_draw_centered_small(g_screen_width / 2, 0x141, 0x80F0F0F0ULL, GetLocalizedString(0xB5F), -1);
    text_draw_centered_small(g_screen_width / 2, 0x15A, 0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    for (i = 0, y = 0x70; i < 12; i++) {
        limit = g_unlockable_shop_table[i].limit;
        if (limit == 100) continue;
        if (limit != 90) {
            if (available < limit) goto locked;
            goto enabled;
        }
        if (g_item_enabled_flags[0]) goto enabled;
locked:
        {
            color = 0x80808080;
            if (i == g_unlockable_options_cursor) color = 0x7029A1FF;
            text_draw_medium(0x2B, y, color, GetLocalizedString(0xBD1), -1);
            if (limit == 90)
                sprintf(buf, g_str_localized_text_fmt, GetLocalizedString(0xC38));
            else
                sprintf(buf, g_str_count_fmt, limit, GetLocalizedString(0xC20));
            style = color;
            gfx_disable_screen_flag();
            r = func_001157AC(buf);
            text_draw_centered_medium(0x195, y, style, buf, r);
            gfx_enable_screen_flag();
        }
        goto next;
enabled:
        {
            color = 0x80F0F0F0;
            if (i == g_unlockable_options_cursor) color = 0x7029A1FF;
            text_draw_medium(0x2B, y, color, GetLocalizedString(g_unlockable_shop_table[i].text), -1);
            text_draw_centered_medium(0x195, y, color, GetLocalizedString(g_unlocked_item_flags[g_unlockable_shop_table[i].index] ? 0xBD7 : 0xBD8), -1);
        }
next:
        y += 19;
    }
    DoGifPaging();
    return 0;
}
