#include "include_asm.h"
#include "names.h"

extern void *F449e2f67_FUN_003361A8(char *p);

extern char *F449e2f67_FUN_00336968(char *p);

extern void *F449e2f67_FUN_003366D0(char *p);

/* Update the observed two-axis selection fields and their combined index. */
typedef struct {
    unsigned char gap0[0x43c];
    int column, row, index, mode;
} DobboGridState312;

extern int snd_play_from_global_bank(int, unsigned int, void *);

/* Sets up the fourteen parts of the grid menu before they are filled in. */
char *grid_menu_init_widgets(char *menu)
{
    F449e2f67_FUN_003361A8(menu);
    F449e2f67_FUN_003361A8(menu + 76);
    F449e2f67_FUN_003361A8(menu + 152);
    F449e2f67_FUN_003361A8(menu + 228);
    F449e2f67_FUN_003361A8(menu + 304);
    F449e2f67_FUN_003361A8(menu + 380);
    F449e2f67_FUN_00336968(menu + 456);
    F449e2f67_FUN_00336968(menu + 528);
    F449e2f67_FUN_003366D0(menu + 600);
    F449e2f67_FUN_00336968(menu + 664);
    F449e2f67_FUN_00336968(menu + 736);
    F449e2f67_FUN_00336968(menu + 808);
    F449e2f67_FUN_00336968(menu + 880);
    F449e2f67_FUN_00336968(menu + 952);
    return menu;
}

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void hud_set_widget_field_a(void *, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void object_set_helper_result(void *, void *, int);
extern void object_init_derived_c(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, int);
extern int grid_menu_update();
extern char g_menu_widget_desc_first[], g_menu_widget_desc_second[], g_menu_widget_desc_third[], g_menu_widget_desc_fourth[], g_menu_frame_desc[], g_menu_panel_desc[];
extern char g_info_panel_count_desc_first[], g_info_panel_count_desc_second[], g_info_panel_count_desc_third[], g_menu_hud_desc_body[], g_grid_menu_widget_defaults[];
extern char g_menu_hud_desc_title[], g_menu_hud_label_desc_alt[], g_menu_icon_desc[];
extern char *g_resident_data_base[] __attribute__((sda));

/* Builds the grid menu: allocates its position, creates all labels and icons, and sets their colours and texts. */
void grid_menu_construct(char *self, void *owner)
{
    int *allocation;
    float zero;

    *(void **)(self + 0x434) = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(self + 0x430) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    zero = 0.0f;
    *(int *)(self + 0x438) = 1;
    (*(float **)(self + 0x430))[0] = 250.0f;
    (*(float **)(self + 0x430))[1] = 207.0f;
    object_init_derived_arrays(self, g_menu_widget_desc_first, owner);
    object_init_derived_arrays(self + 0x4C, g_menu_widget_desc_second, owner);
    object_init_derived_arrays(self + 0x98, g_menu_widget_desc_third, owner);
    object_init_derived_arrays(self + 0xE4, g_menu_widget_desc_fourth, owner);
    object_init_derived_arrays(self + 0x130, g_menu_frame_desc, owner);
    object_init_derived_arrays(self + 0x17C, g_menu_panel_desc, owner);
    hud_init_widget_defaults(self + 0x328, g_info_panel_count_desc_first, owner);
    hud_init_widget_defaults(self + 0x370, g_info_panel_count_desc_second, owner);
    hud_init_widget_defaults(self + 0x3B8, g_info_panel_count_desc_third, owner);
    hud_init_widget_defaults(self + 0x298, g_menu_hud_desc_body, owner);
    hud_init_widget_defaults(self + 0x2E0, g_grid_menu_widget_defaults, owner);
    hud_init_widget_defaults(self + 0x1C8, g_menu_hud_desc_title, owner);
    hud_init_widget_defaults(self + 0x210, g_menu_hud_label_desc_alt, owner);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(self + 0x4C) = 0x60241700;
    *object_get_fourth_field(self + 0x98) = 0x55F0C070;
    *object_get_fourth_field(self + 0xE4) = 0x55F0C070;
    *object_get_fourth_field(self + 0x17C) = 0x70FFFEED;
    *object_get_fourth_field(self + 0x130) = 0x55F0C070;
    *object_get_fourth_field(self + 0x298) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x2E0) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x1C8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x210) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x328) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x370) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x3B8) = 0x80F0F0F0;
    hud_set_widget_field_a(self + 0x298, 1);
    hud_set_widget_field_a(self + 0x2E0, 1);
    object_set_second_float4(self + 0x2E0, 0.9f, 0.9f, zero, zero);
    object_set_helper_result(self, g_resident_data_base[0] + 0x8710, 0x9E);
    object_set_helper_result(self + 0x4C, g_resident_data_base[0] + 0x8710, 0x9F);
    object_set_helper_result(self + 0x98, g_resident_data_base[0] + 0x8710, 0xA0);
    object_set_helper_result(self + 0xE4, g_resident_data_base[0] + 0x8710, 0xA1);
    object_set_helper_result(self + 0x130, g_resident_data_base[0] + 0x8710, 0x5D);
    object_set_helper_result(self + 0x17C, g_resident_data_base[0] + 0x8710, 0x5E);
    *(int *)(self + 0x43C) = 0;
    *(int *)(self + 0x440) = 0;
    *(int *)(self + 0x448) = 3;
    object_init_derived_c(self + 0x258, g_menu_icon_desc, owner);
    *object_get_fourth_field(self + 0x258) = 0x60F0F0B0;
    object_set_second_float4(self + 0x258, 32.0f, 32.0f, zero, zero);
    *object_get_fourth_field(self + 0x1C8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x210) = 0x80F0F0F0;
    hud_set_widget_field_b(self + 0x1C8, GetLocalizedString(0x2D54));
    hud_set_widget_field_b(self + 0x210, GetLocalizedString(0x2D59));
    hud_set_widget_field_b(self + 0x328, (int)(self + 0x400));
    hud_set_widget_field_b(self + 0x370, (int)(self + 0x410));
    hud_set_widget_field_b(self + 0x3B8, (int)(self + 0x420));
    hud_set_widget_field_a(self + 0x328, 0);
    hud_set_widget_field_a(self + 0x370, 0);
    hud_set_widget_field_a(self + 0x3B8, 0);
    *(int *)(self + 0x444) = 0;
    hud_set_widget_field_b(self + 0x298, GetLocalizedString(0x2D4F));
    grid_menu_update(self, 0);
}

typedef struct { unsigned char pad[6]; short id; short tail; } SelectionRow;
extern SelectionRow g_grid_menu_selection_rows[];

/* Handles the direction buttons while the cursor is in the first group of the grid menu. */
void grid_menu_handle_input_first_group(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        state->row = 1;
        state->mode = 2;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        state->row = 0;
        state->mode = 2;
    } else if (buttons & 0x8000) {
        --state->column;
        snd_play_from_global_bank(3, 0, 0);
        if (state->column < 0) {
            state->column = 0;
            state->mode = 1;
        }
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        ++state->column;
        if (state->column >= 2) {
            state->column = 0;
            state->mode = 1;
            state->row = 0;
        }
    }
    state->index = g_grid_menu_selection_rows[state->column].id;
}

/* The cursor's cell table: the same ten-byte record shape as the selection rows above, but the
   table's address is the level's own, so it is a ref_ name. */
extern SelectionRow ref_L00_00286D68_00[];

/* The cursor's up/down/left/right move: the button mask picks the direction, the state keeps
   the column (0x43C), the row (0x440), the chosen index (0x444) and the mode (0x448). */
/* Handles the direction buttons while the cursor is in the main grid of the menu. */
void grid_menu_handle_input_main_grid(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        if (--state->row < 0) {
            if (state->column < 2) {
                state->row = 0;
                state->mode = 0;
            } else if (state->column == 2) {
                state->row = 1;
            } else {
                state->row = 0;
                state->mode = 1;
                state->column = 0;
            }
        }
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        if (++state->row >= 2) {
            if (state->column < 2) {
                state->row = 0;
                state->mode = 0;
            } else if (state->column == 2) {
                state->row = 0;
            } else {
                state->row = 0;
                state->mode = 3;
                state->column = 0;
            }
        }
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        if (--state->column < 0) {
            state->column = 3;
        }
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        if (++state->column >= 4) {
            state->column = 0;
            state->mode = 3;
            state->row = 0;
        }
    }
    state->index = ref_L00_00286D68_00[state->column + state->row * 4].id;
}

/* prioritized masks1000/4000/8000/2000 update signedcolumns43C/rows440 and mode448 with originalevent3 flags0/entitynull; index444=column+2row */
/* Handles the direction buttons while the cursor is in the small two-by-two group of the grid menu. */
void grid_menu_handle_input_small_group(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        --state->row;
        if (state->row < 0) {
            if (state->column == 0) {
                state->mode = 2;
                state->row = 1;
                state->column = 3;
            } else if (state->column == 1) {
                state->row = state->column;
            }
        }
    } else if (buttons & 0x4000) {
        int row;
        snd_play_from_global_bank(3, 0, 0);
        row = state->row + 1;
        state->row = row > 1 ? 0 : row;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        --state->column;
        if (state->column < 0) {
            state->column = 3;
            state->row = 1;
            state->mode = 2;
        }
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        ++state->column;
        if (state->column >= 2)
            state->column = 0;
    }
    state->index = state->column + state->row * 2;
}

extern short g_grid_menu_choice_value;
/* Handles the direction buttons for the single-choice group, jumping the cursor to a fixed place. */
void grid_menu_handle_input_single_choice(char *menu, unsigned int buttons)
{
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x448) = 2;
        *(int *)(menu + 0x440) = 1;
        *(int *)(menu + 0x43C) = 3;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x448) = 2;
        *(int *)(menu + 0x43C) = 3;
        *(int *)(menu + 0x440) = 0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x448) = 0;
        *(int *)(menu + 0x43C) = 1;
        *(int *)(menu + 0x440) = 0;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x440) = 0;
        *(int *)(menu + 0x448) = 3;
        *(int *)(menu + 0x43C) = 0;
    }
    *(int *)(menu + 0x444) = g_grid_menu_choice_value;
}

/* Per-mode lookup of the selected entry's id (the short at +0x42 of a 0xE0-byte record).
   Retail reads the mode 1 flag byte through a bare small-data symbol, so it is declared sda
   under its own name (D_001A7AFE, the byte at +6 of the D_001A7AF8 flags) in this -G0 file. */
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_item_owned_flags[];
extern unsigned char g_starting_items_granted __attribute__((sda));
extern unsigned char g_weapon_table[];
typedef struct { unsigned char pad[0x42]; short field42; unsigned char rest[0xE0 - 0x44]; } Entry224;
/* The four text ids, copied from their retail data: the build keeps no compiler .rodata. */
typedef struct { int v[4]; } Ids_00344378;
extern Ids_00344378 g_grid_menu_text_ids;

/* Returns the text id of the entry the cursor is on, or 0 if it cannot be picked. */
int grid_menu_get_selected_text_id(DobboGridState312 *state)
{
    Ids_00344378 table = g_grid_menu_text_ids;
    int value;

    switch (state->mode) {
    case 0:
    case 2: {
        int index = state->index;
        if (g_item_owned_flags[index] != 0) {
            value = ((Entry224 *)g_weapon_table)[g_item_slot_to_record[index]].field42;
            break;
        }
        return 0;
    }
    case 1:
        if (g_starting_items_granted != 0) {
            value = ((Entry224 *)g_weapon_table)[g_item_slot_to_record[6]].field42;
            break;
        }
        return 0;
    case 3:
        value = table.v[state->index];
        break;
    default:
        value = 0;
        break;
    }
    return value;
}

