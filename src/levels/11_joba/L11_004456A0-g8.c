#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

extern void joba_menu_draw_help_prompts(char *, int);
extern char *GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern int arena_get_challenge_flag_index(int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);

extern float D_L11_001B1808 __attribute__((sda));
extern int D_L11_001B180C __attribute__((sda));
extern int D_L11_001B1810 __attribute__((sda));
extern int D_L11_001B1814 __attribute__((sda));
extern int D_L11_001B1818 __attribute__((sda));
extern int D_L11_001B181C __attribute__((sda));
extern int D_L11_001B1820 __attribute__((sda));
extern int D_L11_001B1824 __attribute__((sda));
extern int D_L11_001B1828 __attribute__((sda));
extern int D_L11_001B182C __attribute__((sda));
extern int D_L11_001B1830 __attribute__((sda));
extern int D_L11_001B1834;
extern int D_L11_001B1838;
extern int D_L11_001B183C;
extern int D_L11_001B1840 __attribute__((sda));
extern float D_L11_001B3E04;
extern char D_L11_001B15A0[];
extern char D_L11_002A3AD0[];
extern u8 D_001395B8[0x100];

extern int D_L11_001B3E00;

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* Draws the Joba menu header and the count box with its message. */
void joba_menu_draw_header_count_box(char *moby) {
    char boxBuf[0x20];
    char lineBuf[0x70];
    char *state;
    char *text;
    char *unitText;
    float titleX, scale, half;
    int titleY, boxX, boxY, boxH, one;

    joba_menu_draw_help_prompts(moby, 0);
    half = 0.5f;
    state = *(char **)(moby + 0x68);
    text = (char *)GetLocalizedString(0x2F45);
    one = 1;
    scale = D_L11_001B3E04;
    titleX = (float)D_L11_001B1810;
    titleY = scaled_coord(D_L11_001B1814, scale, half, one);
    FontPrintScaled(titleX, (float)titleY, D_L11_001B180C, text, D_L11_001B1808, -1,
                  GetEffectTextureDescriptor(1), D_L11_002A3AD0);
    scale = D_L11_001B3E04;
    boxX = scaled_coord(D_L11_001B1830, scale, half, one);
    boxY = scaled_coord(D_L11_001B1834, scale, half, one);
    boxH = scaled_coord(D_L11_001B1820, scale, half, one);
    FontSetWindow(boxBuf, boxX, boxY, D_L11_001B1838, D_L11_001B183C, D_L11_001B181C, boxH,
                  D_L11_001B1840, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && D_001395B8[arena_get_challenge_flag_index(0)] < 2) {
        text = (char *)GetLocalizedString(0x2F96);
        text_draw_window_large(boxBuf, D_L11_001B1818, text, func_001157AC(text));
    } else if (*(s16 *)(state + 0x1E8) == 1 && D_001395B8[arena_get_challenge_flag_index(1)] < 2) {
        text = (char *)GetLocalizedString(0x2F97);
        text_draw_window_large(boxBuf, D_L11_001B1818, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0x2F62);
        unitText = (char *)GetLocalizedString(0x2F5E);
        sprintf(lineBuf, D_L11_001B15A0, text, *(int *)(state + 0x1E0), unitText);
        text_draw_window_large(boxBuf, D_L11_001B1818, lineBuf, func_001157AC(lineBuf));
    }
    text = (char *)GetLocalizedString(0x2F47);
    {
        float half = 0.5f;
        int one = 1;

        scale = D_L11_001B3E04;
        boxX = scaled_coord(D_L11_001B1830, scale, half, one);
        boxY = scaled_coord(D_L11_001B1834, scale, half, one);
        boxH = scaled_coord(D_L11_001B182C, scale, half, one);
        FontSetWindow(boxBuf, boxX, boxY, D_L11_001B1838, D_L11_001B183C, D_L11_001B1828, boxH,
                      D_L11_001B1840, 3);
    }
    text_draw_window_small(boxBuf, D_L11_001B1824, text, func_001157AC(text));
}
