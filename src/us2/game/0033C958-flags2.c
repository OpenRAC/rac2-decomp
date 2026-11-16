#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern void prompt_bar_draw_us2(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the on/off option menu: the prompt bar and the current setting. */
void onoff_menu_draw_us2(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    prompt_bar_draw_us2(object + 8);
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x307A);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7BB9 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

/* Draws a one-option menu: the prompt bar and the current setting. */
void single_toggle_c_draw_us2(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    prompt_bar_draw_us2(object + 8);
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x2C30);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7BBA != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

extern void *prompt_bar_destroy_us2(void *);
extern unsigned long long menu_pass_through_handle(void *);

/* Destroys a list page: its prompt bar and list widgets. */
void *list_page_destroy_us2(char *object) {
    prompt_bar_destroy_us2(object + 0x8);
    menu_pass_through_handle(object + 0x2E0);
    return object;
}

extern void *hud_construct_widget_base(void *);

/* Destroys a simple list page: its prompt bar and list widget. */
void *simple_list_page_destroy_us2(char *object) {
    prompt_bar_destroy_us2(object + 0x8);
    hud_construct_widget_base(object + 0x2E0);
    return object;
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
extern void text_label_draw_us2(char *);
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

/* Draws the map screen: its sprites, the level spots and the cursor lines. */
void map_screen_draw_us2(char *obj)
{
    int i;
    char *base;

    gfx_draw_screen_element_stored(obj);
    gfx_draw_screen_element_stored(obj + 0x4C);
    gfx_draw_screen_element_stored(obj + 0x98);
    text_label_draw_us2(obj + 0x1D8);
    text_label_draw_us2(obj + 0x230);
    text_label_draw_us2(obj + 0x288);
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
