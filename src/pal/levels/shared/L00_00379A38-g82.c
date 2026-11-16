#include "include_asm.h"
#include "names.h"

extern char g_purchase_menu_model[];
extern int g_player_bolts;
extern float g_menu_slide_scale[] __attribute__((sda));
extern int g_buy_back_label_x __attribute__((sda));
extern int g_buy_back_label_x_step __attribute__((sda));
extern int g_buy_back_label_y;
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);

/* Draws the buy and back button labels of the selected item. */
void shop_draw_buy_back_labels_pal(void)
{
    char *model = g_purchase_menu_model;

    if (*(int *)(model + 0x84) != 0) {
        int index = *(int *)(model + 0x80);

        if (g_player_bolts >= *(int *)(g_purchase_menu_model + index * 16 + 0x148)) {
            text_draw_centered_medium(g_buy_back_label_x, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                              0x80F0F0F0ULL, GetLocalizedString(0x113B), -1);
            text_draw_centered_medium(g_buy_back_label_x + g_buy_back_label_x_step, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                              0x80F0F0F0ULL, GetLocalizedString(0x1138), -1);
        } else {
            text_draw_centered_medium(g_buy_back_label_x + g_buy_back_label_x_step, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                              0x80F0F0F0ULL, GetLocalizedString(0x1124), -1);
        }
    } else {
        text_draw_centered_medium(g_buy_back_label_x, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                          0x80F0F0F0ULL, GetLocalizedString(0x1125), -1);
        text_draw_centered_medium(g_buy_back_label_x + g_buy_back_label_x_step, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                          0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    }
}
