#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC;
extern int g_screen_width, D_001A7908;
extern int D_001ABA70 __attribute__((sda));
extern float D_001B23A8;
extern char D_001AB9C0[], D_001AB9F8[];
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern char *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern void text_draw_small(int, int, unsigned long, char *, int);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);

int func_US2_002D38C8(void)
{
    char text[64];
    char *heading_format;
    char *option_format;
    float depth;

    SetupGifPaging(0);
    depth = 0.56f;
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x8B), 0x60442D00,
                 (float)(g_screen_width / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x8C), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x8D), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    text_draw_centered_small(g_screen_width / 2, 65, 0x80F0F0F0UL, GetLocalizedString(0x30D5), -1);
    text_draw_centered_small(g_screen_width / 2, 321, 0x80F0F0F0UL, GetLocalizedString(0x2BE4), -1);
    text_draw_centered_small(g_screen_width / 2, 346, 0x80F0F0F0UL, GetLocalizedString(0x2BE5), -1);

    heading_format = D_001AB9C0;
    sprintf(text, heading_format, GetLocalizedString(0x30D5));
    text_draw_small(134, 186, 0x80F0F0F0UL, text, func_001157AC(text));
    option_format = D_001AB9F8;
    sprintf(text, option_format, GetLocalizedString(D_001A7908 ? 0x2C5C : 0x2C5D));
    text_draw_centered_small(349, 186, 0x80F0F0F0UL, text, func_001157AC(text));
    DoGifPaging();
    return 0;
}
