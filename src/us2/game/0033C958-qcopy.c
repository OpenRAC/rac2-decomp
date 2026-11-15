#include "include_asm.h"
#include "names.h"

struct SolIds {
    int ids[2];
};
extern struct SolIds D_001ADDD0;
extern char D_001ADDD8[];
extern int g_screen_width __attribute__((sda));
extern int g_widescreen_flag __attribute__((sda));
extern float D_001B23A4 __attribute__((sda));
extern void func_US2_0033BF90(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern void text_draw_centered_small(int, int, unsigned long, char *, int);
extern void FontSetWindow(void *, int, int, int, int, int, int, int, int);
extern void text_draw_window_small(void *, unsigned long, char *, int);

void func_US2_0033D070(char *object)
{
    char buffer[64];
    struct SolIds pair;
    char scratch[32];
    char *format;
    char *first;
    char *second;
    float x;
    int w, h;

    func_US2_0033BF90(object + 8);
    pair = D_001ADDD0;
    format = D_001ADDD8;
    first = GetLocalizedString(0x307B);
    second = GetLocalizedString(pair.ids[g_widescreen_flag != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(g_screen_width >> 1, 0x8C, 0x80F0F0F0UL, buffer, -1);
    x = D_001B23A4;
    w = (int)(x * 170.0f + 0.5f);
    if (w != 0)
        h = (int)(x * 379.0f + 0.5f);
    else
        h = (int)(x * 379.0f + 0.5f);
    FontSetWindow(scratch, w, h, 44, 468, 254, 222, 20, 3);
    text_draw_window_small(scratch, 0x80F0F0F0UL, GetLocalizedString(0x3136), -1);
}
