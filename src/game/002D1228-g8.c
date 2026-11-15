#include "common.h"
extern void func_0027C540(int);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int,int,u64,char *,int);
extern int func_0027FB40(int,int,u64,char *,int);
extern int func_001157AC(char *);
extern int func_0027F198(char *,int);
extern void func_002CF0A0(int,int);
extern void func_002CEBD0(void);
extern char *D_001A8CFC;
extern int D_001A7340;
extern float D_001B23A8;
extern int D_001ABA28 __attribute__((sda));
extern int D_001ABA38 __attribute__((sda));
extern unsigned char D_001ABA30[8] __attribute__((sda));
extern short D_001ABD18[] MACRO_ADDR;

/* Draws the list of eight entries with five rows around the cursor; locked ones show a placeholder. */
int func_002D1228(void) {
    int i, y, entryIndex, color;
    int r;
    char *rowText;
    float z;
    SetupGifPaging(0);
    z = 0.0f;
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xD7);
    DrawScaledObjectTwoAxes(r, 0x60442D00, (float)(gScreenWidth / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xD8);
    DrawScaledObjectTwoAxes(r, 0x60241700, (float)(gScreenWidth / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xD9);
    DrawScaledObjectTwoAxes(r, 0x55F0C070, (float)(gScreenWidth / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xDD);
    DrawScaledObjectTwoAxes(r, 0x55F0C070, (float)(gScreenWidth / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    DrawTextCenteredSmallFont(0xB3, 0x1B, 0x80F0F0F0ULL, GetLocalizedString(0x3202), -1);
    DrawTextCenteredSmallFont(0x161, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0x2D4F), -1);
    DrawTextCenteredSmallFont(0xB5, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0x2D75), -1);
    DrawMenuScrollArrowsAndFrame();
    for (i = 0, y = 0x112; i < 5; i++, y += 20) {
        entryIndex = i + D_001ABA28 - 2;
        if (entryIndex < 0) entryIndex += 8;
        if (entryIndex >= 8) entryIndex -= 8;
        rowText = GetLocalizedString(D_001ABA30[entryIndex] ? D_001ABD18[entryIndex] : 0x2DC0);
        if (i == 0 || i == 4) color = 0x10F0F0F0;
        else if (i == 1 || i == 3) color = 0x50F0F0F0;
        else {
            color = 0x70F0F0F0;
            DrawMenuTextHighlightFrame(MeasureTextWidthMediumFont(rowText, strlen_001157AC(rowText)), 0x70F0F0F0);
        }
        DrawTextCenteredMediumFont(gScreenWidth / 2, y, color, rowText, -1);
    }
    DoGifPaging();
    return 0;
}
