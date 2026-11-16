#include "include_asm.h"
#include "names.h"

extern char g_purchase_menu_model[];
extern float g_menu_slide_scale __attribute__((sda));
extern int g_player_bolts __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern char *GetLocalizedString(int);
extern void text_draw_right_aligned_medium(int, int, unsigned long long, unsigned char *, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);
extern void text_format_number_with_separators(char *, int);
extern void text_draw_medium(int, int, unsigned long long, unsigned char *, int);
extern unsigned int level_get_native_table_entry(int);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);

void func_US2_L00_00378678(void) {
    unsigned int colors[4];
    char text[256];
    char *model = g_purchase_menu_model;
    int price = *(int *)(model + 0x144 + *(int *)(model + 0x80) * 12);
    int y;
    unsigned long long color;
    if (price > 0) {
        text_draw_right_aligned_medium(140, (int)(g_menu_slide_scale * 290.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x31DA), -1);
        colors[0] = 0x60F0F0B0;
        colors[1] = 0x60F0F0B0;
        colors[2] = 0x60F0F0B0;
        colors[3] = 0x60F0F0B0;
        hud_draw_sprite_gradient(GetIconFrame(0x7567, 0), 156,
                      (int)(g_menu_slide_scale * 290.0f + 0.5f), 16,
                      (int)(g_menu_slide_scale * 16.0f + 0.5f), colors);
        text_format_number_with_separators(text, price);
        color = 0x80F0F0F0ULL;
        if (price > g_player_bolts) color = 0x802020F0ULL;
        text_draw_medium(176, (int)(g_menu_slide_scale * 290.0f + 0.5f), color, (unsigned char *)text, -1);
        y = (int)(g_menu_slide_scale * 363.0f + 0.5f) + 7;
        if (!g_is_pal_video) y -= 7;
        text_draw_centered_medium(256, y, 0x80F0F0F0ULL,
            (unsigned char *)GetLocalizedString(level_get_native_table_entry(*(int *)(model + 0x148 + *(int *)(model + 0x80) * 12))), -1);
    } else {
        y = (int)(g_menu_slide_scale * 363.0f + 0.5f) + 7;
        if (!g_is_pal_video) y -= 7;
        text_draw_centered_medium(256, y, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x301E), -1);
    }
}
