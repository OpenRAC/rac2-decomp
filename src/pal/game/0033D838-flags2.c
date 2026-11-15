#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 D_L00_001AE110;
extern char D_L00_001AE118[];
extern unsigned char D_001A7B94 __attribute__((sda));
extern unsigned char D_001A7B95 __attribute__((sda));
extern void func_PAL_0033CE70(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

void func_PAL_0033EAF0(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    func_PAL_0033CE70(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0xBF0);
    second = GetLocalizedString(pair.ids[D_001A7B95 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0xBEF);
    second = GetLocalizedString(pair.ids[D_001A7B94 != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
}

extern void func_PAL_0033CE70();
extern void DrawMenuPreviewImage();
extern void func_PAL_00338770();
extern void hud_draw_colored_quad_widget();
extern void gfx_draw_screen_element_stored();
extern void func_PAL_00340D78();

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
void func_PAL_00341020(char *p)
{
    func_PAL_0033CE70(p + 8);
    DrawMenuPreviewImage(0);
    func_PAL_00338770(p + 792);
    func_PAL_00338770(p + 880);
    func_PAL_00338770(p + 968);
    hud_draw_colored_quad_widget(p + 732);
    gfx_draw_screen_element_stored(p + 1056);
    func_PAL_00338770(p + 1576);
    func_PAL_00338770(p + 1488);
    func_PAL_00340D78(p);
}

extern unsigned char D_PAL_001A7C3A __attribute__((sda));
extern unsigned char D_PAL_001A7C3B __attribute__((sda));

void func_PAL_0033F840(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    func_PAL_0033CE70(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0xBAB);
    second = GetLocalizedString(pair.ids[D_PAL_001A7C3A != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x10FB);
    second = GetLocalizedString(pair.ids[D_PAL_001A7C3B != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
}
