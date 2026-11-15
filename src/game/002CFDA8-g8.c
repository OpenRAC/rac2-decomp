#include "common.h"

extern void func_0027C540(long);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, u64, char *, int);
extern int func_0027FB40(int, int, u64, char *, int);
extern int func_001157AC(char *);
extern int func_0027F198(char *, int);
extern void func_002CF0A0(int, int);
extern void func_002CEBD0(void);
extern char *D_001A8CFC;
extern int D_001A7340;
extern float D_001B23A8;

extern void func_0027F120(void);
extern void func_0027F110(void);
extern int func_002B0E90(void);
extern int func_00115DA8(char *, char *, ...);
extern void func_0028FC48(int, int, int, int, u64, int);
extern int D_001AB9FC __attribute__((sda));
extern int D_001ABA00 __attribute__((sda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern short D_0026CF18[][3];

/* Draws the skill points list with the player's count out of 30 and five rows around the cursor. */
int func_002CFDA8(void) {
    char buf[64];
    int r, i, y, entryIndex, color;
    char *formatText;
    float z;
    SetupGifPaging(0);
    z = 0.0f;
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xD7);
    DrawScaledObjectTwoAxes(r, 0x60442D00, (float)(gScreenWidth / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xD8);
    DrawScaledObjectTwoAxes(r, 0x60241700, (float)(gScreenWidth / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xD9);
    DrawScaledObjectTwoAxes(r, 0x55F0C070, (float)(gScreenWidth / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0xDA);
    DrawScaledObjectTwoAxes(r, 0x55F0C070, (float)(gScreenWidth / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    DisableScreenFlag();
    DrawTextCenteredSmallFont(0xB9, 0x1B, 0x80F0F0F0ULL, GetLocalizedString(0x2E10), -1);
    formatText = GetLocalizedString(0x2F2F);
    Sprintf(buf, formatText, CountNonZeroFlags(), 30);
    DrawTextCenteredSmallFont(0x92, 0x177, 0x80F0F0F0ULL, buf, -1);
    EnableScreenFlag();
    DrawTextCenteredSmallFont(0x1AD, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0x2D4F), -1);
    AppendScreenRectPacket(0x15E, 0xDA, 0x1E6, 0xDC, 0x55F0C070ULL, 0);
    if (D_0026CF18[D_001AB9FC][2] != -1)
        DrawTextCenteredSmallFont(0x1A0, 0xE0, 0x80F0F0F0ULL, GetLocalizedString(D_0026CF18[D_001AB9FC][2]), -1);
    DrawMenuScrollArrowsAndFrame();
    for (y = 0x112, i = 0; i < 5; i++, y += 20) {
        char *rowText;
        entryIndex = i + D_001AB9FC - 2;
        if (entryIndex < 0) entryIndex += 30;
        if (entryIndex >= 30) entryIndex -= 30;
        color = 0x80F0F0F0;
        rowText = GetLocalizedString(D_0026CF18[entryIndex][0]);
        if (D_001A7A60[entryIndex]) color = 0x7029A1FF;
        color &= 0xFFFFFF;
        if (i == 0 || i == 4) color |= 0x10000000;
        else if (i == 1 || i == 3) color |= 0x50000000;
        else {
            color |= 0x70000000;
            DrawMenuTextHighlightFrame(MeasureTextWidthMediumFont(rowText, strlen_001157AC(rowText)), color);
        }
        DrawTextCenteredMediumFont(gScreenWidth / 2, y, color, rowText, -1);
    }
    DoGifPaging();
    return 0;
}
