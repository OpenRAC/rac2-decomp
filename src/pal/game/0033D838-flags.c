#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern void prompt_bar_draw_pal(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

void func_PAL_0033E248(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    prompt_bar_draw_pal(object + 8);
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x10FC);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7C39 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

void func_PAL_0033FBE0(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    prompt_bar_draw_pal(object + 8);
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0xBAB);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7C3A != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

extern void *prompt_bar_destroy_pal(void *);
extern unsigned long long menu_pass_through_handle(void *);

void *func_PAL_00340118(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    menu_pass_through_handle(object + 0x2E0);
    return object;
}

extern void *hud_construct_widget_base(void *);

void *func_PAL_00340470(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    hud_construct_widget_base(object + 0x2E0);
    return object;
}

void func_PAL_00340310(unsigned char *owner, float *records)
{
    extern void menu_set_entry_table_pal(unsigned char *, float *);
    menu_set_entry_table_pal(owner + 0x2E0, records);
    *(float **)(owner + 0x3B8) = records;
}

extern void prompt_bar_update_pal(char *);
extern void menu_set_anchor_pos(char *, float, float);
extern void prompt_bar_update_pal(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);

int func_PAL_003405B0(char *object, int flags)
{
    char *p = object + 8;
    float *v;
    prompt_bar_update_pal(p);
    v = *(float **)(object + 0x2D8);
    menu_set_anchor_pos(p, v[0], v[1]);
    return (flags >> 6) & 1;
}

#include "common.h"
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;
typedef struct {
    int x;
    int y;
    int text;
    float scale;
} Row_0033B910;
extern void gfx_draw_screen_element_stored(char *);
extern void func_PAL_00338770(char *);
extern void hud_draw_colored_quad_widget(char *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(char *, int, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern int *object_get_fourth_field(char *);
extern float *object_get_first_field(char *);
extern void gfx_draw_screen_line(int, int, int, int, unsigned long long, int);
extern Row_0033B910 g_map_spot_table[];
extern unsigned char g_map_visited_flags[] MACRO_ADDR;
extern unsigned char g_map_unlocked_flags[] MACRO_ADDR;
extern char g_map_overlay_state[];
static __inline__ void SetColor_0033B910(char *w, int c)
{
    *object_get_fourth_field(w) = c;
}

void map_screen_draw_pal(char *obj)
{
    int i;
    char *base;

    gfx_draw_screen_element_stored(obj);
    gfx_draw_screen_element_stored(obj + 0x4C);
    gfx_draw_screen_element_stored(obj + 0x98);
    func_PAL_00338770(obj + 0x1D8);
    func_PAL_00338770(obj + 0x230);
    func_PAL_00338770(obj + 0x288);
    hud_draw_colored_quad_widget(obj + 0x2E0);
    for (i = 0; i < 21; i++) {
        object_set_first_float4(obj + 0x31C, (float)g_map_spot_table[i].x + (*(float **)(obj + 0x1C8))[0],
                      (float)g_map_spot_table[i].y + (*(float **)(obj + 0x1C8))[1], 0.0f, 0.0f);
        hud_set_widget_value_pair(obj + 0x31C, 0xE99E, g_map_spot_table[i].text);
        object_set_second_float4(obj + 0x31C, g_map_spot_table[i].scale, g_map_spot_table[i].scale, 0.0f, 0.0f);
        if (g_map_unlocked_flags[i] == 0)
            SetColor_0033B910(obj + 0x31C, 0x70A0C0C0);
        else
            SetColor_0033B910(obj + 0x31C, 0x7029A1FF);
        if (g_map_visited_flags[i] != 0)
            hud_draw_colored_quad_widget(obj + 0x31C);
    }
    base = g_map_overlay_state;
    if (*(int *)(base + 0x230) < 21) {
        char *first = obj + 0xE4;
        char *mid = obj + 0x130;
        char *bar = obj + 0x17C;
        char *q = obj + 0x114;
        char *r = first;
        int k;

        for (k = 2; k >= 0; k--) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
            r += 76;
            q += 76;
        }
        gfx_draw_screen_line((int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(mid)[1] + 6.0f),
                      (int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(first)[1] - 4.0f), 0x180000FF, 0);
        gfx_draw_screen_line((int)(object_get_first_field(bar)[0] + 8.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f),
                      (int)(object_get_first_field(bar)[0] + 304.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f), 0x180000FF, 0);
        gfx_draw_screen_line((int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(mid)[1] + 6.0f),
                      (int)(object_get_first_field(first)[0] + 1.0f),
                      (int)(object_get_first_field(first)[1] - 4.0f), 0x180000FF, 0);
        gfx_draw_screen_line((int)(object_get_first_field(bar)[0] + 8.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f),
                      (int)(object_get_first_field(bar)[0] + 304.0f),
                      (int)(object_get_first_field(bar)[1] + 2.0f), 0x180000FF, 0);
    }
}
