#include "include_asm.h"
#include "names.h"

extern char g_purchase_menu_model[];
extern int g_player_bolts;
extern float D_L00_001B25E0[] __attribute__((sda));
extern int D_001AD778 __attribute__((sda));
extern int D_001AD780 __attribute__((sda));
extern int D_001AD77C;
extern unsigned char *GetLocalizedString(int);
extern void text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);

void func_PAL_L00_0037AFB0(void)
{
    char *model = g_purchase_menu_model;

    if (*(int *)(model + 0x84) != 0) {
        int index = *(int *)(model + 0x80);

        if (g_player_bolts >= *(int *)(g_purchase_menu_model + index * 16 + 0x148)) {
            text_draw_centered_medium(D_001AD778, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                              0x80F0F0F0ULL, GetLocalizedString(0x113B), -1);
            text_draw_centered_medium(D_001AD778 + D_001AD780, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                              0x80F0F0F0ULL, GetLocalizedString(0x1138), -1);
        } else {
            text_draw_centered_medium(D_001AD778 + D_001AD780, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                              0x80F0F0F0ULL, GetLocalizedString(0x1124), -1);
        }
    } else {
        text_draw_centered_medium(D_001AD778, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                          0x80F0F0F0ULL, GetLocalizedString(0x1125), -1);
        text_draw_centered_medium(D_001AD778 + D_001AD780, (int)((float)D_001AD77C * D_L00_001B25E0[0] + 0.5f),
                          0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    }
}
