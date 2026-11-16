#include "names.h"
extern char g_purchase_menu_model[];
extern int g_player_bolts;
extern float g_menu_slide_scale[] __attribute__((sda));
extern int g_buy_back_label_x __attribute__((sda));
extern int g_buy_back_label_x_step __attribute__((sda));
extern int g_buy_back_label_y;
extern unsigned char *func_L00_002F4668(int);
extern void func_L00_002E9B40(int, int, unsigned long long, unsigned char *, int);

/* Draws the buy and back labels for the selected item, showing buy only if the player has enough bolts. */
void shop_draw_buy_back_labels(void)
{
    char *model = g_purchase_menu_model;

    if (*(int *)(model + 0x84) != 0) {
        int index = *(int *)(model + 0x80);

        if (g_player_bolts >= *(int *)(g_purchase_menu_model + index * 16 + 0x148)) {
            func_L00_002E9B40(g_buy_back_label_x, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                              0x80F0F0F0ULL, func_L00_002F4668(0x113B), -1);
            func_L00_002E9B40(g_buy_back_label_x + g_buy_back_label_x_step, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                              0x80F0F0F0ULL, func_L00_002F4668(0x1138), -1);
        } else {
            func_L00_002E9B40(g_buy_back_label_x + g_buy_back_label_x_step, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                              0x80F0F0F0ULL, func_L00_002F4668(0x1124), -1);
        }
    } else {
        func_L00_002E9B40(g_buy_back_label_x, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                          0x80F0F0F0ULL, func_L00_002F4668(0x1125), -1);
        func_L00_002E9B40(g_buy_back_label_x + g_buy_back_label_x_step, (int)((float)g_buy_back_label_y * g_menu_slide_scale[0] + 0.5f),
                          0x80F0F0F0ULL, func_L00_002F4668(0x2D4F), -1);
    }
}
