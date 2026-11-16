#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern void prompt_bar_draw_pal(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the on/off option page: the prompt bar and a centred line with the option's current state. */
void onoff_menu_draw_pal(char *object)
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

/* Draws a single-toggle option page: the prompt bar and a centred line with the option's current state. */
void single_toggle_c_draw_pal(char *object)
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

/* Destroys the list page's prompt bar and menu, and returns the page. */
void *list_page_destroy_pal(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    menu_pass_through_handle(object + 0x2E0);
    return object;
}

extern void *hud_construct_widget_base(void *);

/* Destroys the list page's prompt bar and base widget, and returns the page. */
void *simple_list_page_destroy_pal(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    hud_construct_widget_base(object + 0x2E0);
    return object;
}

/* Hands the record table to the list menu and keeps a pointer to it in the page. */
void list_page_set_records_pal(unsigned char *owner, float *records)
{
    extern void menu_set_entry_table_pal(unsigned char *, float *);
    menu_set_entry_table_pal(owner + 0x2E0, records);
    *(float **)(owner + 0x3B8) = records;
}

extern void prompt_bar_update_pal(char *);
extern void menu_set_anchor_pos(char *, float, float);
extern void prompt_bar_update_pal(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);

/* Updates the page's prompt bar at the stored anchor and returns whether the flags have bit 6 set. */
int simple_page_update_pal(char *object, int flags)
{
    char *prompt_bar = object + 8;
    float *anchor;
    prompt_bar_update_pal(prompt_bar);
    anchor = *(float **)(object + 0x2D8);
    menu_set_anchor_pos(prompt_bar, anchor[0], anchor[1]);
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
extern void text_label_draw_pal(char *);
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

/* Draws the map screen: its panels, the 21 spot markers (coloured by unlocked, drawn when visited) and, while a spot is selected, its highlight and frame lines. */
void map_screen_draw_pal(char *screen)
{
    int i;
    char *overlay;

    gfx_draw_screen_element_stored(screen);
    gfx_draw_screen_element_stored(screen + 0x4C);
    gfx_draw_screen_element_stored(screen + 0x98);
    text_label_draw_pal(screen + 0x1D8);
    text_label_draw_pal(screen + 0x230);
    text_label_draw_pal(screen + 0x288);
    hud_draw_colored_quad_widget(screen + 0x2E0);
    for (i = 0; i < 21; i++) {
        object_set_first_float4(screen + 0x31C, (float)g_map_spot_table[i].x + (*(float **)(screen + 0x1C8))[0],
                      (float)g_map_spot_table[i].y + (*(float **)(screen + 0x1C8))[1], 0.0f, 0.0f);
        hud_set_widget_value_pair(screen + 0x31C, 0xE99E, g_map_spot_table[i].text);
        object_set_second_float4(screen + 0x31C, g_map_spot_table[i].scale, g_map_spot_table[i].scale, 0.0f, 0.0f);
        if (g_map_unlocked_flags[i] == 0)
            SetColor_0033B910(screen + 0x31C, 0x70A0C0C0);
        else
            SetColor_0033B910(screen + 0x31C, 0x7029A1FF);
        if (g_map_visited_flags[i] != 0)
            hud_draw_colored_quad_widget(screen + 0x31C);
    }
    overlay = g_map_overlay_state;
    if (*(int *)(overlay + 0x230) < 21) {
        char *first = screen + 0xE4;
        char *mid = screen + 0x130;
        char *bar = screen + 0x17C;
        char *vtables = screen + 0x114;
        char *sprite = first;
        int k;

        for (k = 2; k >= 0; k--) {
            ENTRY_F624a0727 *vtable = *(ENTRY_F624a0727 **)vtables;
            vtable->fn(sprite + vtable->n);
            sprite += 76;
            vtables += 76;
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
