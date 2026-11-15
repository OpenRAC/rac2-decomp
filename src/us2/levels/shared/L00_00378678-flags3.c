#include "include_asm.h"
#include "names.h"

typedef struct { short field[12]; } TextLayout;
extern char g_purchase_menu_model[];
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
extern void gfx_set_scissor_clamped(int, int, int, int);
extern void *memset(void *, int, unsigned int);
extern unsigned char *GetLocalizedString(int);
extern void text_draw_window_medium(TextLayout *, unsigned long long, unsigned char *, int);

void func_US2_L00_0037A2C8(void) {
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
    scale = D_L00_001B25E0;
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
    if (D_001A79FC >= *(int *)(model + 0x144 + index * 28)) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, GetLocalizedString(0x31B5), -1);
    } else {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 60) * scale + 0.5f);
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, GetLocalizedString(0x31B4), -1);
    }
}
