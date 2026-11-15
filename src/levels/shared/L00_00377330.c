/* func_L00_00377330: draw the selected item's price and description lines. */
#include "include_asm.h"
#include "names.h"

extern char D_L00_0022F7C0[];
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79F8 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int func_00288FB8(int);
extern void func_0027FA10(int, int, unsigned long long, unsigned char *, int);
extern int func_0028E588(int, int);
extern int func_0028EA58(int, int, int, int, int, unsigned int *);
extern void func_002F9BC0(char *, int);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);
extern unsigned int func_L00_002F3DD0(int);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);

/* Draws the selected item's price and its description text, with the price in red when it costs too much. */
void func_L00_00377330(void) {
    unsigned int colors[4];
    char text[256];
    char *model = gPurchaseMenuModel;
    int price = *(int *)(model + 0x144 + *(int *)(model + 0x80) * 12);
    int y;
    unsigned long long color;
    if (price > 0) {
        DrawTextRightAlignedMediumFont(140, (int)(D_L00_001B25E0 * 290.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x114E), -1);
        colors[0] = 0x60F0F0B0;
        colors[1] = 0x60F0F0B0;
        colors[2] = 0x60F0F0B0;
        colors[3] = 0x60F0F0B0;
        DrawHudSpriteGradient(GetIconFrame(0x7567, 0), 156,
                      (int)(D_L00_001B25E0 * 290.0f + 0.5f), 16,
                      (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
        FormatNumberWithSeparators_002F9BC0(text, price);
        color = 0x80F0F0F0ULL;
        if (price > gPlayerBolts) color = 0x802020F0ULL;
        DrawTextMediumFont(176, (int)(D_L00_001B25E0 * 290.0f + 0.5f), color, (unsigned char *)text, -1);
        y = (int)(D_L00_001B25E0 * 363.0f + 0.5f) + 7;
        if (!gIsPalVideo) y -= 7;
        DrawTextCenteredMediumFont(256, y, 0x80F0F0F0ULL,
            (unsigned char *)GetLocalizedString(GetNativeTableEntry(*(int *)(model + 0x148 + *(int *)(model + 0x80) * 12))), -1);
    } else {
        y = (int)(D_L00_001B25E0 * 363.0f + 0.5f) + 7;
        if (!gIsPalVideo) y -= 7;
        DrawTextCenteredMediumFont(256, y, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x3188), -1);
    }
}
