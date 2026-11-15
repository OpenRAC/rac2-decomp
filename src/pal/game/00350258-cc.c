#include "names.h"
/* func_PAL_00350258, the PAL copy of func_0034E070: the same C, where rename func_00336B90 becomes func_PAL_003388E8; rename func_0034B2C8 becomes func_PAL_0034D490; rename func_00337C10 becomes func_PAL_00339968; pad 0x1590 becomes 5552. */
#include "common.h"

extern char *D_001A8CFC __attribute__((sda));
extern char D_001AE710[];
extern char D_001AE720[];

extern void *table_find_by_id(int, int);
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void func_PAL_003388E8(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, int, int);
extern void object_set_second_pair(void *, int, int);
extern void text_set_alignment(void *, unsigned int);
extern void widget_store_field(void *, int);
extern void func_PAL_0034D490(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void *object_get_field_b(void *);
extern void func_PAL_00339968(void *, void *);

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

void func_PAL_00350258(void *object, void *a1, void *a2)
{
    RecordSet *set = object;
    char *record = (char *)0x8710;
    char *end = set->records + 0x750;
    void *colour;

    set->f220C = table_find_by_id((int)D_001A8CFC + (int)record, 0x57);
    set->f2210 = table_find_by_id((int)D_001A8CFC + (int)record, 0x58);
    record = set->records;
    do {
        object_init_derived_b(record, 0x20, 1, D_001AE710, a2);
        widget_set_pos_y(record, 5);
        func_PAL_003388E8(record, 0x64);
        meter_set_value(record, 0);
        object_set_first_pair(record, 0x8049C1FF, 0x80001EFF);
        object_set_second_pair(record, 0x50F0C070, 0x50F0C070);
        text_set_alignment(record, 0x80000000);
        widget_store_field(record, 1);
        record += 0x48;
    } while (record < end);
    record = set->f1D30;
    func_PAL_0034D490(set->f7A0, a1, a2);
    object_init_derived_c(record, D_001AE720, a2);
    colour = object_get_fourth_field(record);
    *(float *)colour = 2155905152.0f;
    colour = object_get_field_b(record);
    *(float *)colour = 60008.0f;
    colour = object_get_field_b(record);
    *(int *)((char *)colour + 4) = 0;
    set->f798 = a2;
    func_PAL_00339968(set->f1D6C, a2);
    func_PAL_00339968(set->f1FBC, a2);
}
