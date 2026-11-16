#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern unsigned char g_subtitles_option __attribute__((sda));
extern unsigned char g_toggle_option_a __attribute__((sda));
extern void prompt_bar_draw_us2(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

void two_toggle_a_draw_us2(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    prompt_bar_draw_us2(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x2C75);
    second = GetLocalizedString(pair.ids[g_toggle_option_a != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x2C74);
    second = GetLocalizedString(pair.ids[g_subtitles_option != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
}

extern unsigned char g_weapon_wheel_enabled __attribute__((sda));
extern unsigned char g_option_toggle_b __attribute__((sda));
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

    prompt_bar_draw_us2(object + 8);
    gfx_disable_screen_flag();
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x2C30);
    second = GetLocalizedString(pair.ids[g_option_toggle_b != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x3079);
    second = GetLocalizedString(pair.ids[g_weapon_wheel_enabled != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
    gfx_enable_screen_flag();
}

extern void prompt_bar_draw_us2();
extern int DrawMenuPreviewImage();
extern void func_US2_003378A0();
extern void hud_draw_colored_quad_widget();
extern void gfx_draw_screen_element_stored();
extern void func_US2_0033FDD8();

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
void func_US2_0033FEF8(char *p)
{
    prompt_bar_draw_us2(p + 8);
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
