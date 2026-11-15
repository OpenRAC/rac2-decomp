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

extern char *D_L00_001B1B00[] __attribute__((sda));
extern char *D_L00_001B1B00_sda __attribute__((sda));
extern char *D_001FDA80[];

extern int func_L00_002EE340(void *a, void *b);
extern int func_002ACBC8(void *a, int b);
extern int func_002ACCA8(void *a, int b);
extern int func_L00_003206B8(void *a, int b);
extern int func_002A8AF0(void *a, void *b, int c);

/* Tells whether a point is inside the region with the given index, by testing its bounds and then each of its shapes. */
int func_L00_00329520(void *pos, int index)
{
    char *base;
    Rec_00329520 *rec;
    int off;
    int i;
    int *shape;

    if (index < 0)
        return 0;
    base = D_L00_001B1B00[0];
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
        if (IsPointInsideUnitSphereOfRecord(pos, rec->list24[i]) != 0)
            return 1;
    }
    for (i = 0; i < rec->n16; i++) {
        if (IsPointInsideRecordVolume(pos, rec->list28[i]) != 0)
            return 1;
    }
    for (i = 0; i < rec->n10; i++) {
        shape = (int *)D_001FDA80[rec->list1C[i]];
        if (point_in_path_xy(pos, shape + 4, *shape) != 0)
            return 1;
    }
    return 0;
}
