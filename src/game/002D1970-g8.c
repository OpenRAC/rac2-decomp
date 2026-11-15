#include "common.h"
extern char *D_001A8CFC;
extern int D_001A7340;
extern int D_001ABA54 __attribute__((sda));
extern int D_001ABA3C __attribute__((sda));
extern int D_001ABA40[] SDATA(D_001ABA40);
extern int D_001ABD28[] MACRO_ADDR;
extern float D_001B23A8;
extern void func_0027C540(long);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);

/* Draws the five-entry Extras page: a title, a framed list and the entries, highlighting the cursor row. */
int func_002D1970(void)
{
    int i, y = 125;
    int *textIds = D_001ABD28;
    int *enabledFlags = D_001ABA40;
    float z;

    SetupGifPaging(0);
    z = 0.775f;
    DrawScaledObjectTwoAxes((char *)FindTableEntryById(D_001A8CFC + 0x8710, 0x8B), 0x60442D00,
                 (float)(gScreenWidth / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    DrawScaledObjectTwoAxes((char *)FindTableEntryById(D_001A8CFC + 0x8710, 0x8C), 0x55F0C070,
                 (float)(gScreenWidth / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    DrawScaledObjectTwoAxes((char *)FindTableEntryById(D_001A8CFC + 0x8710, 0x8D), 0x55F0C070,
                 (float)(gScreenWidth / 2), (float)D_001ABA54, 1.0f, D_001B23A8, z);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 65, 0x80F0F0F0UL, GetLocalizedString(0x320C), -1);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 321, 0x80F0F0F0UL, GetLocalizedString(0x2D75), -1);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 346, 0x80F0F0F0UL, GetLocalizedString(0x2D4F), -1);
    AppendScreenRectPacket(312, 128, 449, 130, 0x55F0C070, 0);
    AppendScreenRectPacket(312, 265, 451, 267, 0x55F0C070, 0);
    AppendScreenRectPacket(312, 128, 314, 265, 0x55F0C070, 0);
    AppendScreenRectPacket(449, 128, 451, 265, 0x55F0C070, 0);
    for (i = 0; i < 5; i++, y += 31, textIds++, enabledFlags++) {
        unsigned long color = i == D_001ABA3C ? 0x7000FFFFUL : 0x80F0F0F0UL;
        int textId = *enabledFlags ? *textIds : 0x2DC0;
        DrawTextCenteredSmallFont(165, y, color, GetLocalizedString(textId), -1);
    }
    DoGifPaging();
    return 0;
}
