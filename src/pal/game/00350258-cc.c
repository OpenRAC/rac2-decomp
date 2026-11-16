#include "names.h"
/* func_PAL_00350258, the PAL copy of func_0034E070: the same C, where rename func_00336B90 becomes func_PAL_003388E8; rename func_0034B2C8 becomes func_PAL_0034D490; rename func_00337C10 becomes func_PAL_00339968; pad 0x1590 becomes 5552. */
#include "common.h"

extern char *g_resident_data_base __attribute__((sda));
extern char g_records_widget_data_a[];
extern char g_records_widget_data_b[];

extern void *table_find_by_id(int, int);
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void func_PAL_003388E8(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, int, int);
extern void object_set_second_pair(void *, int, int);
extern void text_set_alignment(void *, unsigned int);
extern void widget_store_field(void *, int);
extern void hud_ammo_bolt_init_pal(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void *object_get_field_b(void *);
extern void text_panel_init_pal(void *, void *);

typedef struct {
    char records[0x798];
    void *f798;
    char pad79C[4];
    char f7A0[0x15b0];
    char f1D30[0x3C];
    char f1D6C[0x250];
    char f1FBC[0x250];
    int f220C;
    int f2210;
} RecordSet;

/* Sets up the records screen: the row_ptr row texts, the ammo and bolt HUD, and the other panels (PAL layout). */
void records_screen_init_pal(void *screen, void *font_data, void *context)
{
    RecordSet *set = screen;
    char *row_ptr = (char *)0x8710;
    char *end = set->records + 0x750;
    void *color;

    set->f220C = table_find_by_id((int)g_resident_data_base + (int)row_ptr, 0x57);
    set->f2210 = table_find_by_id((int)g_resident_data_base + (int)row_ptr, 0x58);
    row_ptr = set->records;
    do {
        object_init_derived_b(row_ptr, 0x20, 1, g_records_widget_data_a, context);
        widget_set_pos_y(row_ptr, 5);
        func_PAL_003388E8(row_ptr, 0x64);
        meter_set_value(row_ptr, 0);
        object_set_first_pair(row_ptr, 0x8049C1FF, 0x80001EFF);
        object_set_second_pair(row_ptr, 0x50F0C070, 0x50F0C070);
        text_set_alignment(row_ptr, 0x80000000);
        widget_store_field(row_ptr, 1);
        row_ptr += 0x48;
    } while (row_ptr < end);
    row_ptr = set->f1D30;
    hud_ammo_bolt_init_pal(set->f7A0, font_data, context);
    object_init_derived_c(row_ptr, g_records_widget_data_b, context);
    color = object_get_fourth_field(row_ptr);
    *(float *)color = 2155905152.0f;
    color = object_get_field_b(row_ptr);
    *(float *)color = 60008.0f;
    color = object_get_field_b(row_ptr);
    *(int *)((char *)color + 4) = 0;
    set->f798 = context;
    text_panel_init_pal(set->f1D6C, context);
    text_panel_init_pal(set->f1FBC, context);
}
