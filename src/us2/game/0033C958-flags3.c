#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 D_L00_001AE110;
extern char D_L00_001AE118[];
extern unsigned char D_001A7B94 __attribute__((sda));
extern unsigned char D_001A7B95 __attribute__((sda));
extern void func_US2_0033BF90(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

void func_US2_0033DC68(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    func_US2_0033BF90(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x2C75);
    second = GetLocalizedString(pair.ids[D_001A7B95 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x2C74);
    second = GetLocalizedString(pair.ids[D_001A7B94 != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
}

extern unsigned char D_001A7BB3 __attribute__((sda));
extern unsigned char D_001A7BB2 __attribute__((sda));
extern void gfx_enable_screen_flag(void);
extern void gfx_disable_screen_flag(void);

/* func_US2_0033E9B8, the v2.00 copy of func_0033D970: the same C with func_0027F120 before the text and
 * func_0027F110 after it. func_0027FAA8 must be declared int here (as in this unit), not void: the ignored
 * call value is what leaves the second test in $v1, so this cannot live in 0033C958.c, which declares it void. */
void func_US2_0033E9B8(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    func_US2_0033BF90(object + 8);
    gfx_disable_screen_flag();
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x2C30);
    second = GetLocalizedString(pair.ids[D_001A7BB2 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x3079);
    second = GetLocalizedString(pair.ids[D_001A7BB3 != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
    gfx_enable_screen_flag();
}

extern void func_US2_0033BF90();
extern void DrawMenuPreviewImage();
extern void func_US2_003378A0();
extern void hud_draw_colored_quad_widget();
extern void gfx_draw_screen_element_stored();
extern void func_US2_0033FDD8();

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
void func_US2_0033FEF8(char *p)
{
    func_US2_0033BF90(p + 8);
    DrawMenuPreviewImage(0);
    func_US2_003378A0(p + 792);
    func_US2_003378A0(p + 880);
    func_US2_003378A0(p + 968);
    hud_draw_colored_quad_widget(p + 732);
    gfx_draw_screen_element_stored(p + 1056);
    func_US2_003378A0(p + 1576);
    func_US2_003378A0(p + 1488);
    func_US2_0033FDD8(p);
}
