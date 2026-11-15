#include "common.h"

typedef struct {
    short ids[4];
    short name;
    short value;
    short description;
    short detail;
    short stats[4];
} Item;

extern char *D_001A8CFC;
extern int g_screen_width;
extern int D_001AB9B0 __attribute__((sda));
extern int D_001AB9B8 __attribute__((sda));
extern int D_001AB9BC __attribute__((sda));
extern unsigned short D_00188510[][2];
extern Item D_00264630[];
extern int D_00138340 NOT_SDA;
extern float D_001B23A8;
extern int D_001B23A0;
extern char D_001AB9C0[], D_001AB9C8[], D_001AB9D8[];
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void SetupGifPaging(long), DoGifPaging(void);
extern char *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern void text_draw_medium(int, int, u64, char *, int);
extern int text_draw_centered_small(int, int, u64, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);
extern void AppendScreenRectPacket(int, int, int, int, u64, int);
extern void gfx_disable_screen_flag(void), gfx_enable_screen_flag(void);

/* Draws the item details page: its name, description, four stat bars and the previous and next buttons. */
int DrawItemStatsMenu(void)
{
    char text[64];
    int dim_color, button_color, bar_width, center_x, count;
    char *line_format, *count_format;
    int active = 1;
    float alpha, zero = 0.0f;

    dim_color = math_ping_pong_blend_values(0x60442D00, 0x80FFDE8D, 25, 0, 0);
    SetupGifPaging(0);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xAE), 0x60442D00, (float)(g_screen_width / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xAF), 0x60241700, (float)(g_screen_width / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xB0), 0x55F0C070, (float)(g_screen_width / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xB1), 0x55F0C070, (float)(g_screen_width / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    text_draw_medium(31, 62, 0x80F0F0F0ULL, GetLocalizedString(0x31F3), -1);
    text_draw_medium(31, 92, 0x80F0F0F0ULL, GetLocalizedString(0x31F4), -1);
    text_draw_medium(31, 122, 0x80F0F0F0ULL, GetLocalizedString(0x31F2), -1);
    text_draw_medium(31, 152, 0x80F0F0F0ULL, GetLocalizedString(0x31F5), -1);

    line_format = D_001AB9C0;
    sprintf(text, line_format, GetLocalizedString(0x31F6));
    count = func_001157AC(text);
    text_draw_medium(31, 184, 0x80F0F0F0ULL, text, count);
    sprintf(text, line_format, GetLocalizedString(0x31F7));
    count = func_001157AC(text);
    text_draw_medium(31, 201, 0x80F0F0F0ULL, text, count);
    text_draw_medium(429, 373, 0x80F0F0F0ULL, GetLocalizedString(0x2F42), -1);
    text_draw_centered_small(154, 26, 0x80F0F0F0ULL, GetLocalizedString(0x31C6), -1);

    if (D_00188510[D_001AB9B0][0] != 0 || D_00188510[D_001AB9B0][1] != 0) {
        bar_width = (int)((float)D_00264630[D_001AB9B0].stats[0] * 2.44f);
        if (bar_width > 244)
            bar_width = 244;
        AppendScreenRectPacket(31, 78, bar_width + 31, 88, 0x55F0C070ULL, 0);
        bar_width = (int)((float)D_00264630[D_001AB9B0].stats[1] * 2.44f);
        if (bar_width > 244)
            bar_width = 244;
        AppendScreenRectPacket(31, 108, bar_width + 31, 118, 0x55F0C070ULL, 0);
        bar_width = (int)((float)D_00264630[D_001AB9B0].stats[2] * 2.44f);
        if (bar_width > 244)
            bar_width = 244;
        AppendScreenRectPacket(31, 139, bar_width + 31, 150, 0x55F0C070ULL, 0);
        bar_width = (int)((float)D_00264630[D_001AB9B0].stats[3] * 2.44f);
        if (bar_width > 244)
            bar_width = 244;
        AppendScreenRectPacket(31, 169, bar_width + 31, 180, 0x55F0C070ULL, 0);
        if (D_001AB9B0 < D_001AB9B8) {
            button_color = (D_00138340 & 0x2000) ? 0x80F0F0F0 : dim_color;
            {
                char *sprite = table_find_by_id(D_001A8CFC + 0x8710, 0x4A);
                {
                    float factor = 0.8f;
                    alpha = D_001B23A8 * factor;
                }
                if (D_001B23A0 == active)
                    alpha += -0.05f;
                gfx_draw_scaled_object_two_axes(sprite, button_color, 316.0f, 278.0f, 1.0f, alpha, zero);
            }
            text_draw_medium(432, 276, 0x80F0F0F0ULL, GetLocalizedString(0x2F41), -1);
        }
        if (D_001AB9B0 >= 2) {
            button_color = (D_00138340 & 0x8000) ? 0x80F0F0F0 : dim_color;
            {
                char *sprite = table_find_by_id(D_001A8CFC + 0x8710, 0x4B);
                {
                    float factor = 0.8f;
                    alpha = D_001B23A8 * factor;
                }
                if (D_001B23A0 == 1)
                    alpha += -0.05f;
                gfx_draw_scaled_object_two_axes(sprite, button_color, 207.0f, 278.0f, 1.0f, alpha, zero);
            }
            text_draw_medium(55, 276, 0x80F0F0F0ULL, GetLocalizedString(0x2F40), -1);
        }
        gfx_disable_screen_flag();
        center_x = g_screen_width / 2;
        text_draw_centered_medium(center_x, 276, 0x80F0F0F0ULL, GetLocalizedString(D_00264630[D_001AB9B0].name), -1);
        gfx_enable_screen_flag();
        text_draw_medium(156, 185, 0x80F0F0F0ULL, GetLocalizedString(D_00264630[D_001AB9B0].description), -1);
        if (D_00264630[D_001AB9B0].detail == -1) {
            sprintf(text, D_001AB9C8);
            count = func_001157AC(text);
            text_draw_medium(156, 202, 0x80F0F0F0ULL, text, count);
        } else {
            text_draw_medium(156, 202, 0x80F0F0F0ULL, GetLocalizedString(D_00264630[D_001AB9B0].detail), -1);
        }
        count = D_00188510[D_001AB9B0][0];
        count_format = D_001AB9D8;
        sprintf(text, count_format, count, GetLocalizedString(0x2F61));
        count = func_001157AC(text);
        text_draw_centered_medium(152, 228, 0x80F0F0F0ULL, text, count);
    }
    DoGifPaging();
    return 0;
}
