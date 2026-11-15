#include "common.h"

extern void func_0027C540(long);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, u64, char *, int);
extern int func_0027FB40(int, int, u64, char *, int);
extern int func_001157AC(char *);
extern char *D_001A8CFC;
extern int D_001A7340;
extern float D_001B23A8;

extern void func_0027F120(void);
extern void func_0027F110(void);
extern int func_002B0E90(void);
extern int func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(int, int, u64, char *, int);
extern int D_001AB9EC __attribute__((sda));
extern int D_001AB9F0 __attribute__((sda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
extern char D_001AB9F8[];
extern char D_001AB9D8[];
typedef struct {
    short text;
    unsigned char index;
    unsigned char limit;
} MenuOption;
extern MenuOption D_001ABCD0[] MACRO_ADDR;

/* Draws the unlockable options menu: twelve options with on or off, or the skill points still needed to unlock them. */
int func_002CF7F0(void)
{
    char buf[64];
    int r, i, y, color, limit, available;
    u64 style;
    float z;

    available = CountNonZeroFlags();
    z = 0.84f;
    SetupGifPaging(0);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0x8B);
    DrawScaledObjectTwoAxes((char *)r, 0x60442D00, (float)(gScreenWidth / 2), (float)D_001AB9F0, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0x8C);
    DrawScaledObjectTwoAxes((char *)r, 0x55F0C070, (float)(gScreenWidth / 2), (float)D_001AB9F0, 1.0f, D_001B23A8, z);
    r = FindTableEntryById(D_001A8CFC + 0x8710, 0x8D);
    DrawScaledObjectTwoAxes((char *)r, 0x55F0C070, (float)(gScreenWidth / 2), (float)D_001AB9F0, 1.0f, D_001B23A8, z);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 0x41, 0x80F0F0F0ULL, GetLocalizedString(0x2E12), -1);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 0x141, 0x80F0F0F0ULL, GetLocalizedString(0x2D4E), -1);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 0x15A, 0x80F0F0F0ULL, GetLocalizedString(0x2D4F), -1);
    for (i = 0, y = 0x70; i < 12; i++) {
        limit = D_001ABCD0[i].limit;
        if (limit == 100) continue;
        if (limit != 90) {
            if (available < limit) goto locked;
            goto enabled;
        }
        if (D_001A7A60[0]) goto enabled;
locked:
        {
            color = 0x80808080;
            if (i == D_001AB9EC) color = 0x7029A1FF;
            DrawTextMediumFont(0x2B, y, color, GetLocalizedString(0x2DC0), -1);
            if (limit == 90)
                Sprintf(buf, D_001AB9F8, GetLocalizedString(0x2E28));
            else
                Sprintf(buf, D_001AB9D8, limit, GetLocalizedString(0x2E10));
            style = color;
            DisableScreenFlag();
            r = strlen_001157AC(buf);
            DrawTextCenteredMediumFont(0x195, y, style, buf, r);
            EnableScreenFlag();
        }
        goto next;
enabled:
        {
            color = 0x80F0F0F0;
            if (i == D_001AB9EC) color = 0x7029A1FF;
            DrawTextMediumFont(0x2B, y, color, GetLocalizedString(D_001ABCD0[i].text), -1);
            DrawTextCenteredMediumFont(0x195, y, color, GetLocalizedString(D_001A7A40[D_001ABCD0[i].index] ? 0x2DC6 : 0x2DC7), -1);
        }
next:
        y += 19;
    }
    DoGifPaging();
    return 0;
}
