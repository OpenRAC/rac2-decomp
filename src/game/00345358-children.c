#include "names.h"
/* Sets up the menu page's seven labels and its seven list rows. Its own unit: the labels' addresses
   are recomputed at each use and gcse numbers those pseudos in its hash table's order, which depends
   on the function's insn count. Retail's spill slots need the table of 93 buckets, which needs the
   string arguments unprecomputed (-fno-expensive-optimizations) and the row pointer walked. */
typedef unsigned char u8;
extern int object_get_fourth_field(u8 *);
extern void *ui_return_second_arg(int, int);
extern int pool_alloc_cell(void *);
extern void *hud_init_widget_defaults(void *, void *, void *);
extern void object_set_helper_result(char *, char *, int);
extern void menu_set_field_44c(u8 *, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_set_widget_field_b(void *, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void UpdateMenuChoiceListWidgets(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern char ref_003486A8_00[];
extern char ref_003486A8_01[];
extern char ref_003486A8_02[];
extern char ref_003486A8_03[];
extern char ref_003486A8_04[];
extern char ref_003486A8_05[];
extern char ref_003486A8_06[];
extern char ref_003486A8_07[];

void menu_page_construct_with_rows(char *menu, void *data)
{
    int *allocation;

    *(int *)(menu + 0x43C) = 0;
    menu_set_field_44c((u8 *)menu, 0);
    *(void **)(menu + 0x438) = data;
    if (data) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(data));
        *(int **)(menu + 0x434) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    {
        float *position = *(float **)(menu + 0x434);

        *(int *)(menu + 0x440) = 1;
        position[0] = 250.0f;
    }
    (*(float **)(menu + 0x434))[1] = 190.0f;
    object_init_derived_arrays(menu + 0x0, ref_003486A8_00, data);
    object_init_derived_arrays(menu + 0x130, ref_003486A8_01, data);
    object_init_derived_arrays(menu + 0x4C, ref_003486A8_02, data);
    object_init_derived_arrays(menu + 0x98, ref_003486A8_03, data);
    object_init_derived_arrays(menu + 0xE4, ref_003486A8_04, data);
    object_init_derived_arrays(menu + 0x17C, ref_003486A8_05, data);
    object_init_derived_arrays(menu + 0x1C8, ref_003486A8_06, data);
    *(int *)(menu + 0x410) = 0;
    *(int *)(menu + 0x444) = 0;
    {
        int i;
        char *row = menu + 0x218;

        for (i = 0; i < 7; i++) {
            hud_init_widget_defaults(row, ref_003486A8_07, data);
            hud_set_widget_field_b(row, 0);
            object_set_second_float4(row, 1.0f, 0.0f, 0.0f, 0.0f);
            *(int *)object_get_fourth_field((u8 *)row) = 0x80F0F0F0;
            *(int *)(menu + 0x418 + i * 4) = 1;
            row += 72;
        }
    }
    *(int *)object_get_fourth_field((u8 *)menu + 0x0) = 0x60442D00;
    *(int *)object_get_fourth_field((u8 *)menu + 0x130) = 0x55F0C070;
    *(int *)object_get_fourth_field((u8 *)menu + 0x4C) = 0x55F0C070;
    *(int *)object_get_fourth_field((u8 *)menu + 0x98) = 0x80FFDE8D;
    *(int *)object_get_fourth_field((u8 *)menu + 0xE4) = 0x70FFFEED;
    *(int *)object_get_fourth_field((u8 *)menu + 0x17C) = 0x60442D00;
    *(int *)object_get_fourth_field((u8 *)menu + 0x1C8) = 0x55F0C070;
    object_set_helper_result(menu + 0x0, D_001A8CFC[0] + 0x8710, 28);
    object_set_helper_result(menu + 0x130, D_001A8CFC[0] + 0x8710, 29);
    object_set_helper_result(menu + 0x4C, D_001A8CFC[0] + 0x8710, 30);
    object_set_helper_result(menu + 0x98, D_001A8CFC[0] + 0x8710, 31);
    object_set_helper_result(menu + 0xE4, D_001A8CFC[0] + 0x8710, 32);
    object_set_helper_result(menu + 0x17C, D_001A8CFC[0] + 0x8710, 115);
    object_set_helper_result(menu + 0x1C8, D_001A8CFC[0] + 0x8710, 116);
    UpdateMenuChoiceListWidgets(menu, 0);
}
