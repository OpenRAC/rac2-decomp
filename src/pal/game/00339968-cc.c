#include "names.h"
/* func_PAL_00339968, the PAL copy of func_00337C10: the same C, where template us2 func_US2_00338AB8. */

extern int *object_get_fourth_field(void *);
extern void object_set_flag_value(void *, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_helper_result(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *memset(void *, int, unsigned int);
extern char D_001ADB40[];
extern char D_001ADB50[];
extern char *D_001A8CFC[] __attribute__((sda));

/* Initialises a text panel: clears its state and, when a pool is given, takes four 16-byte
   cells from it with func_00336E40/func_00336DA8 (255,108 / colour 0x60442D00 / two cleared
   cells), then sets up the "aTxBrack" and "aTxTop" widgets at +0x10 and +0x5C with
   D_001A8CFC[0] + 0x8710 and colour 0x55F0C070. The cleared cells store word 0 last, as in
   func_00339078; the colour cell is cleared as floats before its integer colour is stored. */
void func_PAL_00339968(char *obj, void *pool)
{
    char *top;
    char *bracket;

    obj[0xA8] = 0;
    *(int *)(obj + 0x1AC) = 0;
    *(int *)(obj + 0x1A8) = 0;
    *(int *)(obj + 0x1C8) = 0;
    *(int *)(obj + 0x1CC) = 0;
    *(int *)(obj + 0x1C4) = 2;
    *(int *)(obj + 0x1D4) = 0x28;
    *(int *)(obj + 0x1B0) = 1;
    memset(obj + 0x1D8, 0, 0x78);
    if (pool != 0) {
        float *xy;
        float *colour;
        int *cell4;
        int *cellC;

        xy = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        xy[0] = 255.0f;
        xy[1] = 108.0f;
        ((int *)xy)[2] = 0;
        ((int *)xy)[3] = 0;
        *(float **)(obj + 0) = xy;
        colour = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        colour[0] = 0.0f;
        colour[1] = 0.0f;
        *(int *)colour = 0x60442D00;
        ((int *)colour)[2] = 0;
        ((int *)colour)[3] = 0;
        *(float **)(obj + 8) = colour;
        cell4 = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        *(int **)(obj + 4) = cell4;
        cell4[1] = 0;
        cell4[2] = 0;
        cell4[3] = 0;
        cell4[0] = 0;
        cellC = ui_return_second_arg((void *)16, pool_alloc_cell(pool));
        *(int **)(obj + 12) = cellC;
        cellC[1] = 0;
        cellC[2] = 0;
        cellC[3] = 0;
        cellC[0] = 0;
    }
    bracket = obj + 0x10;
    top = obj + 0x5C;
    object_init_derived_arrays(bracket, D_001ADB40, pool);
    object_set_helper_result(bracket, (int)(D_001A8CFC[0] + 0x8710), 0x57);
    object_set_value_float(bracket, 0.02f);
    object_set_flag_value(bracket, 1);
    *object_get_fourth_field(bracket) = 0x55F0C070;
    object_init_derived_arrays(top, D_001ADB50, pool);
    object_set_helper_result(top, (int)(D_001A8CFC[0] + 0x8710), 0x58);
    object_set_flag_value(top, 1);
    *object_get_fourth_field(top) = 0x55F0C070;
    **(int **)(obj + 12) = 0x80F0F0F0;
    *(int *)(obj + 0x1B8) = 0;
    **(int **)(obj + 4) = 0;
}

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
