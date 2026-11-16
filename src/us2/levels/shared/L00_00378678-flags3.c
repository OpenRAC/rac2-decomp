#include "include_asm.h"
#include "names.h"

typedef struct { short field[12]; } TextLayout;
extern char g_purchase_menu_model[];
extern float g_menu_slide_scale __attribute__((sda));
extern int g_bolt_count __attribute__((sda));
extern void gfx_set_scissor_clamped(int, int, int, int);
extern void *memset(void *, int, unsigned int);
extern char *GetLocalizedString(int);
extern void text_draw_window_medium(TextLayout *, unsigned long long, unsigned char *, int);

/* Draws a text box telling the player whether the selected item is at its limit. */
void shop_draw_item_limit_text_box_us2(void) {
    TextLayout copy;
    TextLayout layout;
    char *model;
    int index;
    float scale;
    gfx_set_scissor_clamped(192, 488, 59, 195);
    model = g_purchase_menu_model;
    if (*(int *)(model + 0x84) == 0) return;
    index = *(int *)(model + 0x80);
    memset(&layout, 0, 24);
    scale = g_menu_slide_scale;
    layout.field[2] = 32;
    layout.field[3] = 386;
    layout.field[4] = 209;
    layout.field[0] = (short)(scale * 63.0f + 0.5f);
    layout.field[1] = (short)(scale * 231.0f + 0.5f);
    layout.field[5] = (short)(scale * 204.0f + 0.5f);
    layout.field[6] = 346;
    layout.field[7] = (short)(scale * 160.0f + 0.5f);
    layout.field[8] = 16;
    layout.field[9] = 3;
    copy = layout;
    if (g_bolt_count >= *(int *)(model + 0x144 + index * 28)) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, GetLocalizedString(0x31B5), -1);
    } else {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 60) * scale + 0.5f);
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, GetLocalizedString(0x31B4), -1);
    }
}
