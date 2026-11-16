#include "include_asm.h"
#include "names.h"

extern void func_00336320_1(char *a);
extern void func_00336A78_1(char *a);

/* early-returns when a 32-bit field is zero, otherwise calls one helper four times and another three times with fixed byte offsets off the argument pointer. */
void mission_screen_draw_parts_us2(char *a0)
{
    if (*(int *)(a0 + 728) == 0)
        return;
    func_00336320_1(a0 + 8);
    func_00336320_1(a0 + 84);
    func_00336320_1(a0 + 160);
    func_00336320_1(a0 + 236);
    func_00336A78_1(a0 + 312);
    func_00336A78_1(a0 + 400);
    func_00336A78_1(a0 + 488);
}

char *mission_screen_shutdown_us2(char *object)
{
    extern int prompt_bar_destroy(void *);
    extern void *object_construct_derived_a(void *);
    prompt_bar_destroy(object + 8);
    object_construct_derived_a(object + 0x2D8);
    return object;
}

typedef int s32;
typedef unsigned char u8;

void popup_set_flag_on_us2(u8 *a0) {s32 v=1;*(s32 *)(a0+0x330)=v;}

extern void prompt_bar_set_texts_enabled(unsigned char *owner, int value);

void popup_set_box_value_us2(unsigned char *owner, int value)
{
    prompt_bar_set_texts_enabled(owner + 8, value);
}

/* Measured target: byte-identical across all 27 levels. */
void popup_set_row_us2(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x328) = a1; }

extern char *func_00288FB8_3(int);
extern void prompt_bar_set_texts(char *, int, int, int);
extern void prompt_bar_set_spacing(char *, float);

/* Calls a one-argument helper three times with three fixed small integers, passes the three results and a pointer plus 8 to a four-argument helper, calls a two-argument helper with the same address and 0.0f, then clears the word at offset 764. */
void popup_init_texts_hidden_us2(char *p)
{
    int first = func_00288FB8_3(11316);
    int second = func_00288FB8_3(11314);

    prompt_bar_set_texts(p + 8, first, second, func_00288FB8_3(11237));
    prompt_bar_set_spacing(p + 8, 0.0f);
    *(int *)(p + 812) = 0;
}

extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_us2(void *, void *, void *, void *);
extern void prompt_bar_set_spacing_us2(void *, float);

/* looks up three objects by numeric id, runs a four-argument routine and a (pointer,float) routine on a sub-object at self+8, then stores 1 at self+764 */
void popup_init_texts_shown_us2(int *self)
{
    void *a;
    void *b;
    void *c;
    void *sub = (void *)(self + 2);

    a = GetLocalizedString(11315);
    b = GetLocalizedString(11314);
    c = GetLocalizedString(11237);

    prompt_bar_set_texts_us2(sub, a, b, c);
    prompt_bar_set_spacing_us2(sub, 0.0f);

    self[203] = 1;
}


extern int g_menu_prompt_flag_a __attribute__((sda));
extern int g_menu_prompt_flag_b __attribute__((sda));
extern void prompt_bar_set_extras_enabled_us2(int *p, int flag);
extern void prompt_bar_draw_us2(int *p);
extern void gfx_draw_screen_element_stored(int *p);

/* Lazily initialises a sub-object of the argument behind two global flags and a field, runs one guarded setup step on it, then hands it to two callees. */
void menu_draw_with_prompts_us2(int *obj)
{
    if (g_menu_prompt_flag_a != 0 || g_menu_prompt_flag_b != 0 || obj[204] != 0)
        prompt_bar_set_extras_enabled_us2(obj + 2, 0);
    if (obj[203] == 1)
        prompt_bar_set_extras_enabled_us2(obj + 2, 1);
    prompt_bar_draw_us2(obj + 2);
    gfx_draw_screen_element_stored(obj + 182);
}


extern char *func_L00_0042BAD0_1(char *object);
extern char *func_L00_0042C290_1(char *object);

/* calls two one-argument functions on a sequence of sub-objects of the argument (four at 8..236 stride 76, nine at 312..888 stride 72) and returns the argument */
char *list_screen_destroy_us2(char *object)
{
    func_L00_0042BAD0_1(object + 8);
    func_L00_0042BAD0_1(object + 84);
    func_L00_0042BAD0_1(object + 160);
    func_L00_0042BAD0_1(object + 236);
    func_L00_0042C290_1(object + 312);
    func_L00_0042C290_1(object + 400);
    func_L00_0042C290_1(object + 488);
    func_L00_0042C290_1(object + 576);
    func_L00_0042C290_1(object + 664);
    func_L00_0042C290_1(object + 752);
    func_L00_0042C290_1(object + 840);
    func_L00_0042C290_1(object + 928);
    func_L00_0042C290_1(object + 1016);
    return object;
}

/* func_US2_0033AF70, the USA v2.00 copy of func_00339F28: the same C, where the widgets moved
   and the scale is read from its global at each call instead of a local copy. */

typedef struct {
    float x, y;
} Point2_0033AF70;

extern void *memset(void *, int, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(void *, int);
extern void hud_set_widget_field_b(void *, int);
extern Point2_0033AF70 g_list_screen_title_pos, g_list_screen_list_pos, g_list_screen_prev_pos, g_list_screen_next_pos;
extern Point2_0033AF70 g_list_screen_scale __attribute__((sda));
/* Two views of one object: retail reads .x through $gp and .y through its absolute macro form. */
extern Point2_0033AF70 D_001ADD00_gp __asm__("D_001ADD00__gp") __attribute__((section(".sdata")));
extern char g_map_overlay_state[];
extern int g_menu_text_id_table[];
extern char g_circle_menu_icon_data[];

int list_screen_layout_us2(char *obj, int unused)
{
    Point2_0033AF70 z0, z1, z2, z3;
    Point2_0033AF70 title, list, prev, next;
    char *base;
    int index;

    memset(&z0, 0, 8);
    memset(&z1, 0, 8);
    memset(&z2, 0, 8);
    memset(&z3, 0, 8);
    title = g_list_screen_title_pos;
    list = g_list_screen_list_pos;
    prev = g_list_screen_prev_pos;
    next = g_list_screen_next_pos;
    object_set_second_float4(obj + 0x190, D_001ADD00_gp.x, g_list_screen_scale.y, 0.0f, 0.0f);
    object_set_second_float4(obj + 0x1E8, D_001ADD00_gp.x, g_list_screen_scale.y, 0.0f, 0.0f);
    object_set_second_float4(obj + 0x240, D_001ADD00_gp.x, g_list_screen_scale.y, 0.0f, 0.0f);
    object_set_second_float4(obj + 0x298, D_001ADD00_gp.x, g_list_screen_scale.y, 0.0f, 0.0f);
    object_set_second_float4(obj + 0x2F0, D_001ADD00_gp.x, g_list_screen_scale.y, 0.0f, 0.0f);
    object_set_second_float4(obj + 0x348, D_001ADD00_gp.x, g_list_screen_scale.y, 0.0f, 0.0f);
    object_set_first_float4(obj + 0x8, z0.x + (*(float **)(obj + 4))[0],
                  z0.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0x54, z3.x + (*(float **)(obj + 4))[0],
                  z3.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0xA0, z1.x + (*(float **)(obj + 4))[0],
                  z1.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0xEC, z2.x + (*(float **)(obj + 4))[0],
                  z2.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0x138, title.x + (*(float **)(obj + 4))[0],
                  title.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0x190, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0x1E8, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 18.0f, 0.0f, 0.0f);
    object_set_first_float4(obj + 0x240, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 36.0f, 0.0f, 0.0f);
    object_set_first_float4(obj + 0x298, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 54.0f, 0.0f, 0.0f);
    object_set_first_float4(obj + 0x2F0, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 72.0f, 0.0f, 0.0f);
    object_set_first_float4(obj + 0x348, list.x + 8.0f + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 90.0f, 0.0f, 0.0f);
    object_set_first_float4(obj + 0x3A0, prev.x + (*(float **)(obj + 4))[0],
                  prev.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(obj + 0x3F8, next.x + (*(float **)(obj + 4))[0],
                  next.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    base = g_map_overlay_state;
    text_format_location_name(obj + 0x450, *(int *)(base + 0x230));
    index = g_menu_text_id_table[*(int *)(base + 0x230) * 2 + 1];
    if (index >= 0)
        hud_set_widget_field_b(obj + 0x3F8, (int)GetLocalizedString(index));
    else
        hud_set_widget_field_b(obj + 0x3F8, (int)g_circle_menu_icon_data);
    return 0;
}

extern void F8ad956d6_FUN_00336320(char *target);
extern void F8ad956d6_FUN_002FC560(int marker, int code);
extern void F8ad956d6_FUN_00295F60(int first, int second);
extern int F8ad956d6_FUN_002DAF68(char *target);
extern void F8ad956d6_FUN_00336A78(char *target);

void list_screen_draw_us2(char *object)
{
    char *s0 = object;

    if (*(int *)(s0 + 1168) == 0)
        return;
    F8ad956d6_FUN_00336320(s0 + 8);
    F8ad956d6_FUN_00336320(s0 + 84);
    F8ad956d6_FUN_002FC560(66, 68);
    F8ad956d6_FUN_002FC560(71, 11);
    F8ad956d6_FUN_00295F60(0, 1);
    F8ad956d6_FUN_002DAF68(0);
    F8ad956d6_FUN_00336320(s0 + 160);
    F8ad956d6_FUN_00336320(s0 + 236);
    F8ad956d6_FUN_00336A78(s0 + 312);
    F8ad956d6_FUN_00336A78(s0 + 400);
    F8ad956d6_FUN_00336A78(s0 + 488);
    F8ad956d6_FUN_00336A78(s0 + 576);
    F8ad956d6_FUN_00336A78(s0 + 664);
    F8ad956d6_FUN_00336A78(s0 + 752);
    F8ad956d6_FUN_00336A78(s0 + 840);
    F8ad956d6_FUN_00336A78(s0 + 928);
    F8ad956d6_FUN_00336A78(s0 + 1016);
}

