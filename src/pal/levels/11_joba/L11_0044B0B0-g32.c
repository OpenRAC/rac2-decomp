#include "common.h"
#include "include_asm.h"

/* func_PAL_L11_0044B0B0, the PAL copy of func_L11_004456A0: the same C, where the text ids and
 * func_0027F640 change and the x coordinate D_L11_001B1810 becomes a table of six ints indexed by
 * the byte D_PAL_001A7C3C. The table is reached through $gp, so this unit's threshold has to cover
 * its true 24 bytes: -G32 rather than the template's -G8. */

extern void joba_menu_draw_help_prompts(char *, int);
extern int GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void func_PAL_0027FB48(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern int arena_get_challenge_flag_index(int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);

extern float D_L11_001B1808 __attribute__((sda));
extern int D_L11_001B180C __attribute__((sda));
extern int D_L11_001B1810[6] __attribute__((sda));
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
extern unsigned char D_PAL_001A7C3C MACRO_ADDR;

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

void func_PAL_L11_0044B0B0(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    joba_menu_draw_help_prompts(a0, 0);
    half = 0.5f;
    state = *(char **)(a0 + 0x68);
    text = (char *)GetLocalizedString(0xe6a);
    one = 1;
    s = D_L11_001B3E04;
    x = (float)D_L11_001B1810[D_PAL_001A7C3C];
    r0 = scaled_coord(D_L11_001B1814, s, half, one);
    func_PAL_0027FB48(x, (float)r0, D_L11_001B180C, text, D_L11_001B1808, -1,
                  GetEffectTextureDescriptor(1), D_L11_002A3AD0);
    s = D_L11_001B3E04;
    r1 = scaled_coord(D_L11_001B1830, s, half, one);
    r2 = scaled_coord(D_L11_001B1834, s, half, one);
    r3 = scaled_coord(D_L11_001B1820, s, half, one);
    FontSetWindow(buf1, r1, r2, D_L11_001B1838, D_L11_001B183C, D_L11_001B181C, r3,
                  D_L11_001B1840, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && D_001395B8[arena_get_challenge_flag_index(0)] < 2) {
        text = (char *)GetLocalizedString(0xebb);
        text_draw_window_large(buf1, D_L11_001B1818, text, func_001157AC(text));
    } else if (*(s16 *)(state + 0x1E8) == 1 && D_001395B8[arena_get_challenge_flag_index(1)] < 2) {
        text = (char *)GetLocalizedString(0xebc);
        text_draw_window_large(buf1, D_L11_001B1818, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0xe87);
        msg = (char *)GetLocalizedString(0xe83);
        sprintf(buf2, D_L11_001B15A0, text, *(int *)(state + 0x1E0), msg);
        text_draw_window_large(buf1, D_L11_001B1818, buf2, func_001157AC(buf2));
    }
    text = (char *)GetLocalizedString(0xe6c);
    {
        float half = 0.5f;
        int one = 1;

        s = D_L11_001B3E04;
        r1 = scaled_coord(D_L11_001B1830, s, half, one);
        r2 = scaled_coord(D_L11_001B1834, s, half, one);
        r3 = scaled_coord(D_L11_001B182C, s, half, one);
        FontSetWindow(buf1, r1, r2, D_L11_001B1838, D_L11_001B183C, D_L11_001B1828, r3,
                      D_L11_001B1840, 3);
    }
    text_draw_window_small(buf1, D_L11_001B1824, text, func_001157AC(text));
}
