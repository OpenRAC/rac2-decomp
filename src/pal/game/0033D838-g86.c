#include "include_asm.h"
#include "names.h"

extern int func_PAL_00340A50(char *, int);
extern char D_001ADC88[];
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, void *);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void func_PAL_0033CB00(void *, void *, void *);
extern void func_PAL_00338688(void *, void *, void *);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_field_a(void *, int);
extern unsigned int *object_get_fourth_field(void *);
extern void object_init_derived_c(void *, void *, void *);
extern void hud_set_widget_value_pair(void *, int, int);
extern void object_set_helper_result(void *, void *, int);
extern int D_001ADF00[2] __attribute__((sda));
extern char *D_001A8CFC;
extern char D_001ADF08[], D_001ADF10[], D_001ADF18[], D_001ADF20[];

void func_PAL_003406C0(char *object, void *owner)
{
    int *allocation;
    char *a;
    char *b;
    char *c;
    char *d;
    char *e;
    char *f;
    char *g;
    char *h;
    char *i;
    char *j;
    char *k;
    char *table;
    unsigned int color;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2D8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    (*(float **)(object + 0x2D8))[0] = 255.0f;
    (*(float **)(object + 0x2D8))[1] = 200.0f;
    a = object + 0x318;
    b = object + 0x370;
    c = object + 0x3C8;
    d = object + 0x628;
    e = object + 0x5D0;
    f = object + 0x420;
    g = object + 0x578;
    h = object + 0x2DC;
    color = 0x80F0F0F0;
    func_PAL_0033CB00(object + 8, owner, D_001ADF00);
    table = D_001ADC88;
    func_PAL_00338688(a, table, owner);
    func_PAL_00338688(b, table, owner);
    i = object + 0x470;
    j = object + 0x4C8;
    func_PAL_00338688(c, table, owner);
    k = object + 0x520;
    func_PAL_00338688(d, table, owner);
    func_PAL_00338688(e, table, owner);
    object_init_derived_arrays(f, table, owner);
    func_PAL_00338688(g, table, owner);
    hud_set_widget_field_b(e, object + 0x680);
    hud_set_widget_field_b(g, GetLocalizedString(0xAD2));
    object_set_second_float4(g, 0.9f, 0.9f, 0.0f, 0.0f);
    hud_set_widget_field_b(a, GetLocalizedString(0xB60));
    hud_set_widget_field_b(b, GetLocalizedString(0x1B61));
    hud_set_widget_field_b(c, GetLocalizedString(0xBE2));
    hud_set_widget_field_a(a, 0);
    hud_set_widget_field_a(b, 0);
    hud_set_widget_field_a(c, 0);
    *object_get_fourth_field(a) = color;
    *object_get_fourth_field(b) = color;
    *object_get_fourth_field(c) = color;
    *object_get_fourth_field(d) = color;
    *object_get_fourth_field(e) = color;
    *object_get_fourth_field(g) = color;
    *object_get_fourth_field(f) = 0x55F0C070;
    object_init_derived_c(h, table, owner);
    hud_set_widget_value_pair(h, 0xEAA2, 0);
    object_set_second_float4(h, 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(h) = 0x60F0F0B0;
    object_set_helper_result(f, D_001A8CFC + 0x8710, 0x5D);
    func_PAL_00338688(i, D_001ADF10, *(void **)object);
    func_PAL_00338688(j, D_001ADF18, *(void **)object);
    func_PAL_00338688(k, D_001ADF20, *(void **)object);
    *object_get_fourth_field(i) = color;
    *object_get_fourth_field(j) = color;
    *object_get_fourth_field(k) = color;
    hud_set_widget_field_b(i, object + 0x6C0);
    hud_set_widget_field_b(j, object + 0x6D8);
    hud_set_widget_field_b(k, object + 0x6F0);
    func_PAL_00340A50(object, 0);
}

extern void func_PAL_0033CD50(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(char *, int);
extern void func_PAL_00340C88(void *);
extern int func_PAL_002D7B68(int);
extern char g_map_overlay_state[], D_001ADC88[];
extern int D_00258D70[];
extern float D_001ADF28 __attribute__((sda));
extern float D_001ADF2C[] __attribute__((sda));
extern float D_001ADF30 __attribute__((sda));
extern float D_001ADF34[] __attribute__((sda));
extern float D_001ADF38 __attribute__((sda));
extern float D_001ADF3C[] __attribute__((sda));
extern float D_001ADF40 __attribute__((sda));
extern float D_001ADF44[] __attribute__((sda));
extern float D_001ADF48 __attribute__((sda));
extern float D_001ADF4C[] __attribute__((sda));
extern float D_001ADF50 __attribute__((sda));
extern float D_001ADF54[] __attribute__((sda));
extern float D_001ADF58 __attribute__((sda));
extern float D_001ADF5C[] __attribute__((sda));

int func_PAL_00340A50(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x628;
    char *state;
    int text;
    float x, y;

    func_PAL_0033CD50(child);
    menu_set_anchor_pos(child, (*(float **)(object + 0x2D8))[0], (*(float **)(object + 0x2D8))[1]);
    x = D_001ADF28 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF2C[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x318, x, y, 0.0f, 0.0f);
    x = D_001ADF30 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF34[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x370, x, y, 0.0f, 0.0f);
    x = D_001ADF38 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF3C[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x3C8, x, y, 0.0f, 0.0f);
    x = D_001ADF50 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF54[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x2DC, x, y, 0.0f, 0.0f);
    x = D_001ADF58 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF5C[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x420, x, y, 0.0f, 0.0f);
    x = D_001ADF48 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF4C[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(label, x, y, 0.0f, 0.0f);
    x = D_001ADF40 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF44[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x5D0, x, y, 0.0f, 0.0f);
    state = g_map_overlay_state;
    text_format_location_name(object + 0x680, *(int *)(state + 0x230));
    text = D_00258D70[*(int *)(state + 0x230) * 2 + 1];
    if (text >= 0)
        hud_set_widget_field_b(label, GetLocalizedString(text));
    else
        hud_set_widget_field_b(label, D_001ADC88);
    func_PAL_00340C88(object);
    func_PAL_002D7B68(0);
    return (flags >> 6) & 1;
}
