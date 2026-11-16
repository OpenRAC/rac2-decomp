#include "include_asm.h"
#include "names.h"

typedef struct Rec_00329520 {
    unsigned char prefix_00[0x10];
    short n10;
    short n12;
    short n14;
    short n16;
    unsigned char pad_18[4];
    int *list1C;
    int *list20;
    int *list24;
    int *list28;
} Rec_00329520;

extern char *g_region_group_table[] __attribute__((sda));
extern char *D_L00_001B1B00_sda __attribute__((sda));
extern char *g_object_pointer_table[];

extern int func_L00_002EE340(void *a, void *b);
extern int IsPointInCuboid(void *a, int b);
extern int coll_is_point_inside_unit_sphere(void *a, int b);
extern int coll_point_inside_record_volume(void *a, int b);
extern int point_in_path_xy(void *a, void *b, int c);

/* Tells whether a point is inside the region with the given index, by testing its bounds and then each of its shapes. */
int coll_point_inside_region(void *pos, int index)
{
    char *base;
    Rec_00329520 *rec;
    int off;
    int i;
    int *shape;

    if (index < 0)
        return 0;
    base = g_region_group_table[0];
    if (index >= *(int *)base)
        return 0;
    off = index * 0x30 + 0x20;
    if (func_L00_002EE340(pos, base + off) == 0)
        return 0;
    rec = (Rec_00329520 *)(D_L00_001B1B00_sda + off);
    for (i = 0; i < rec->n12; i++) {
        if (IsPointInCuboid(pos, rec->list20[i]) != 0)
            return 1;
    }
    for (i = 0; i < rec->n14; i++) {
        if (coll_is_point_inside_unit_sphere(pos, rec->list24[i]) != 0)
            return 1;
    }
    for (i = 0; i < rec->n16; i++) {
        if (coll_point_inside_record_volume(pos, rec->list28[i]) != 0)
            return 1;
    }
    for (i = 0; i < rec->n10; i++) {
        shape = (int *)g_object_pointer_table[rec->list1C[i]];
        if (point_in_path_xy(pos, shape + 4, *shape) != 0)
            return 1;
    }
    return 0;
}
