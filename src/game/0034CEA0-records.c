#include "common.h"

extern char *g_resident_data_base __attribute__((sda));
extern char g_records_widget_data_a[];
extern char g_records_widget_data_b[];

extern void *table_find_by_id(int, int);
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void meter_set_max(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, int, int);
extern void object_set_second_pair(void *, int, int);
extern void text_set_alignment(void *, unsigned int);
extern void widget_store_field(void *, int);
extern void hud_ammo_bolt_init(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void *object_get_field_b(void *);
extern void text_panel_init(void *, void *);

typedef struct {
    char records[0x798];
    void *f798;
    char pad79C[4];
    char f7A0[0x1590];
    char f1D30[0x3C];
    char f1D6C[0x250];
    char f1FBC[0x250];
    int f220C;
    int f2210;
} RecordSet;

/* Sets up the records screen: the record row texts, the ammo and bolt HUD, and the other panels. */
void records_screen_init(void *object, void *font_data, void *context)
{
    RecordSet *set = object;
    char *record = (char *)0x8710;
    char *end = set->records + 0x750;
    void *colour;

    set->f220C = table_find_by_id((int)g_resident_data_base + (int)record, 0x57);
    set->f2210 = table_find_by_id((int)g_resident_data_base + (int)record, 0x58);
    record = set->records;
    do {
        object_init_derived_b(record, 0x20, 1, g_records_widget_data_a, context);
        widget_set_pos_y(record, 5);
        meter_set_max(record, 0x64);
        meter_set_value(record, 0);
        object_set_first_pair(record, 0x8049C1FF, 0x80001EFF);
        object_set_second_pair(record, 0x50F0C070, 0x50F0C070);
        text_set_alignment(record, 0x80000000);
        widget_store_field(record, 1);
        record += 0x48;
    } while (record < end);
    record = set->f1D30;
    hud_ammo_bolt_init(set->f7A0, font_data, context);
    object_init_derived_c(record, g_records_widget_data_b, context);
    colour = object_get_fourth_field(record);
    *(float *)colour = 2155905152.0f;
    colour = object_get_field_b(record);
    *(float *)colour = 60008.0f;
    colour = object_get_field_b(record);
    *(int *)((char *)colour + 4) = 0;
    set->f798 = context;
    text_panel_init(set->f1D6C, context);
    text_panel_init(set->f1FBC, context);
}
