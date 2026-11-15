#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC;
extern int D_001A7340, D_001A7908;
extern int D_001ABA70 __attribute__((sda));
extern float D_001B23A8;
extern char D_001AB9C0[], D_001AB9F8[];

extern void func_0027C540(long);
extern void func_0027C660(void);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern void func_0027F538(int, int, unsigned long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);

/* Draws an options menu screen with its title, a heading line and a line showing whether the setting is on or off, plus the button hints. */
int func_002D2918(void)
{
    char text[64];
    char *heading_format;
    char *option_format;
    float depth;

    SetupGifPaging(0);
    depth = 0.56f;
    DrawScaledObjectTwoAxes(FindTableEntryById(D_001A8CFC + 0x8710, 0x8B), 0x60442D00,
                 (float)(gScreenWidth / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    DrawScaledObjectTwoAxes(FindTableEntryById(D_001A8CFC + 0x8710, 0x8C), 0x55F0C070,
                 (float)(gScreenWidth / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    DrawScaledObjectTwoAxes(FindTableEntryById(D_001A8CFC + 0x8710, 0x8D), 0x55F0C070,
                 (float)(gScreenWidth / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 65, 0x80F0F0F0UL, GetLocalizedString(0x323F), -1);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 321, 0x80F0F0F0UL, GetLocalizedString(0x2D4E), -1);
    DrawTextCenteredSmallFont(gScreenWidth / 2, 346, 0x80F0F0F0UL, GetLocalizedString(0x2D4F), -1);

    heading_format = D_001AB9C0;
    Sprintf(text, heading_format, GetLocalizedString(0x323F));
    DrawTextSmallFont(134, 186, 0x80F0F0F0UL, text, strlen_001157AC(text));
    option_format = D_001AB9F8;
    Sprintf(text, option_format, GetLocalizedString(D_001A7908 ? 0x2DC6 : 0x2DC7));
    DrawTextCenteredSmallFont(349, 186, 0x80F0F0F0UL, text, strlen_001157AC(text));
    DoGifPaging();
    return 0;
}
