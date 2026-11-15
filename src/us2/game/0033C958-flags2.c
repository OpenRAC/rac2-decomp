#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair D_L00_001AE110;
extern char D_L00_001AE118[];
extern void func_US2_0033BF90(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern void text_draw_centered_small(int, int, unsigned long, char *, int);

void func_US2_0033D3C0(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    func_US2_0033BF90(object + 8);
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x307A);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7BB9 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

void func_US2_0033ED18(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    func_US2_0033BF90(object + 8);
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x2C30);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7BBA != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

extern void *func_US2_0033BB98(void *);
extern void *menu_pass_through_handle(void *);

void *func_US2_0033F1C0(char *object) {
    func_US2_0033BB98(object + 0x8);
    menu_pass_through_handle(object + 0x2E0);
    return object;
}

extern void *hud_construct_widget_base(void *);

void *func_US2_0033F4D0(char *object) {
    func_US2_0033BB98(object + 0x8);
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
extern void func_US2_003378A0(char *);
extern void hud_draw_colored_quad_widget(char *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(char *, int, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern int *object_get_fourth_field(char *);
extern float *object_get_first_field(char *);
extern void gfx_draw_screen_line(int, int, int, int, unsigned long long, int);
extern Row_0033B910 g_map_spot_table[];
extern unsigned char D_001A7BC8[] MACRO_ADDR;
extern unsigned char D_001A7BE8[] MACRO_ADDR;
extern char g_map_overlay_state[];
static __inline__ void SetColor_0033B910(char *w, int c)
{
    *object_get_fourth_field(w) = c;
}

void func_US2_0033C958(char *obj)
{
    int i;
    char *base;

    gfx_draw_screen_element_stored(obj);
    gfx_draw_screen_element_stored(obj + 0x4C);
    gfx_draw_screen_element_stored(obj + 0x98);
    func_US2_003378A0(obj + 0x1D8);
    func_US2_003378A0(obj + 0x230);
    func_US2_003378A0(obj + 0x288);
    hud_draw_colored_quad_widget(obj + 0x2E0);
    for (i = 0; i < 21; i++) {
        object_set_first_float4(obj + 0x31C, (float)g_map_spot_table[i].x + (*(float **)(obj + 0x1C8))[0],
                      (float)g_map_spot_table[i].y + (*(float **)(obj + 0x1C8))[1], 0.0f, 0.0f);
        hud_set_widget_value_pair(obj + 0x31C, 0xE99E, g_map_spot_table[i].text);
        object_set_second_float4(obj + 0x31C, g_map_spot_table[i].scale, g_map_spot_table[i].scale, 0.0f, 0.0f);
        if (D_001A7BE8[i] == 0)
            SetColor_0033B910(obj + 0x31C, 0x70A0C0C0);
        else
            SetColor_0033B910(obj + 0x31C, 0x7029A1FF);
        if (D_001A7BC8[i] != 0)
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
