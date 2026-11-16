#include "common.h"
typedef union { u8 b[0x800]; s32 i[0x200]; u8 *ptr[0x200]; } HudModel;
extern char g_purchase_menu_model[];
extern float g_menu_slide_scale;
extern int g_is_pal_video MACRO_ADDR;
extern int g_shop_help_string_id __attribute__((sda));
extern int g_shop_help_string_ids[6] __attribute__((sda));
extern void gfx_set_scissor_clamped(int, int, int, int);
extern unsigned int func_001157AC(const char *);
extern int math_random_int_below(int);
extern char *GetLocalizedString(int);
extern void shop_set_message_text(void *);
extern void draw_large_text_edge_faded(float, float, unsigned long long, unsigned char *, int, float);

/* Draws the scrolling help text, advancing its scroll and starting a random voice line at the end. */
void text_draw_scrolling_help(void) {
    int baseline;
    float magnification;
    int choice;
    int y;
    if (((HudModel *)g_purchase_menu_model)->i[0x50 / 4] == 2) {
        baseline = 20;
        magnification = 1.0f;
        gfx_set_scissor_clamped(75, 355, (int)(g_menu_slide_scale * 19.0f + 0.5f), (int)(g_menu_slide_scale * 36.0f + 0.5f));
    } else {
        baseline = 60;
        magnification = 1.5f;
        gfx_set_scissor_clamped(80, 432, (int)(g_menu_slide_scale * 56.0f + 0.5f), (int)(g_menu_slide_scale * 100.0f + 0.5f));
    }
    if ((int)func_001157AC((char *)((HudModel *)g_purchase_menu_model)->ptr[0x3C / 4]) - ((HudModel *)g_purchase_menu_model)->i[0x64 / 4] / 20 > 0)
        ((HudModel *)g_purchase_menu_model)->i[0x64 / 4] = ((HudModel *)g_purchase_menu_model)->i[0x64 / 4] + 2;
    else if (((HudModel *)g_purchase_menu_model)->i[0x744 / 4] == 0 && (unsigned int)(((HudModel *)g_purchase_menu_model)->i[0x50 / 4] - 1) > 1) {
        choice = math_random_int_below(12);
        if (choice >= 6) shop_set_message_text((void *)GetLocalizedString(g_shop_help_string_id));
        else shop_set_message_text((void *)GetLocalizedString(g_shop_help_string_ids[choice]));
    }
    y = (int)((float)baseline * g_menu_slide_scale + 0.5f);
    draw_large_text_edge_faded((float)-((HudModel *)g_purchase_menu_model)->i[0x64 / 4], (float)(g_is_pal_video ? y - 4 : y), 0xF0C070ULL, ((HudModel *)g_purchase_menu_model)->ptr[0x3C / 4], -1, magnification);
}
