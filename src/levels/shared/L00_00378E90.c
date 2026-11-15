#include "names.h"
typedef struct { short field[12]; } TextLayout;
extern char D_L00_0022F7C0[];
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
extern void func_002FC620(int, int, int, int);
extern void *func_00115484(void *, int, unsigned int);
extern unsigned char *func_00288FB8(int);
/* Retail consumes a 24-byte layout and the complete 64-bit color word. */
extern void func_00280200(TextLayout *, unsigned long long, unsigned char *, int);

/* Draws a text box telling the player whether the selected item is at its limit. */
void func_L00_00378E90(void) {
    TextLayout copy;
    TextLayout layout;
    char *model;
    int index;
    float scale;
    SetGsScissorClamped(192, 488, 59, 195);
    model = gPurchaseMenuModel;
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
        DrawTextWindowMediumFont(&copy, 0x80F0F0F0ULL, GetLocalizedString(0x1129), -1);
    } else {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 60) * scale + 0.5f);
        DrawTextWindowMediumFont(&copy, 0x80F0F0F0ULL, GetLocalizedString(0x1128), -1);
    }
}
