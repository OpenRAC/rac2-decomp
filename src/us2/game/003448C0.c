#include "include_asm.h"
#include "names.h"

extern void *F449e2f67_FUN_003361A8(char *menu);
extern char *F449e2f67_FUN_00336968(char *menu);
extern void *F449e2f67_FUN_003366D0(char *menu);

/* Sets up the fourteen parts of the grid menu before they are filled in (USA v2.00 copy). */
char *grid_menu_init_widgets_us2(char *menu)
{
    F449e2f67_FUN_003361A8(menu);
    F449e2f67_FUN_003361A8(menu + 76);
    F449e2f67_FUN_003361A8(menu + 152);
    F449e2f67_FUN_003361A8(menu + 228);
    F449e2f67_FUN_003361A8(menu + 304);
    F449e2f67_FUN_003361A8(menu + 380);
    F449e2f67_FUN_00336968(menu + 456);
    F449e2f67_FUN_00336968(menu + 544);
    F449e2f67_FUN_003366D0(menu + 632);
    F449e2f67_FUN_00336968(menu + 696);
    F449e2f67_FUN_00336968(menu + 784);
    F449e2f67_FUN_00336968(menu + 872);
    F449e2f67_FUN_00336968(menu + 960);
    F449e2f67_FUN_00336968(menu + 1048);
    return menu;
}


extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults_us2(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void hud_set_widget_field_a(void *, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void object_set_helper_result(void *, void *, int);
extern void object_init_derived_c(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, int);
extern int grid_menu_update_us2();
extern char g_menu_widget_desc_first[], g_menu_widget_desc_second[], g_menu_widget_desc_third[], g_menu_widget_desc_fourth[], g_menu_frame_desc[], g_menu_panel_desc[];
extern char g_info_panel_count_desc_first[], g_info_panel_count_desc_second[], g_info_panel_count_desc_third[], g_menu_hud_desc_body[], g_grid_menu_widget_defaults[];
extern char g_menu_hud_desc_title[], g_menu_hud_label_desc_alt[], g_menu_icon_desc[];
extern char *g_resident_data_base[] __attribute__((sda));

/* Builds the grid menu: allocates its position, creates and colors the widgets, sets their texts and
   picks the first cell (USA v2.00 copy). */
void grid_menu_construct_us2(char *self, void *owner)
{
    int *buf;
    float zero;

    *(void **)(self + 0x4A4) = owner;
    if (owner) {
        buf = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(self + 0x4A0) = buf;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;
        buf[0] = 0;
    }
    zero = 0.0f;
    *(int *)(self + 0x4A8) = 1;
    (*(float **)(self + 0x4A0))[0] = 250.0f;
    (*(float **)(self + 0x4A0))[1] = 207.0f;
    object_init_derived_arrays(self, g_menu_widget_desc_first, owner);
    object_init_derived_arrays(self + 0x4C, g_menu_widget_desc_second, owner);
    object_init_derived_arrays(self + 0x98, g_menu_widget_desc_third, owner);
    object_init_derived_arrays(self + 0xE4, g_menu_widget_desc_fourth, owner);
    object_init_derived_arrays(self + 0x130, g_menu_frame_desc, owner);
    object_init_derived_arrays(self + 0x17C, g_menu_panel_desc, owner);
    hud_init_widget_defaults_us2(self + 0x368, g_info_panel_count_desc_first, owner);
    hud_init_widget_defaults_us2(self + 0x3C0, g_info_panel_count_desc_second, owner);
    hud_init_widget_defaults_us2(self + 0x418, g_info_panel_count_desc_third, owner);
    hud_init_widget_defaults_us2(self + 0x2B8, g_menu_hud_desc_body, owner);
    hud_init_widget_defaults_us2(self + 0x310, g_grid_menu_widget_defaults, owner);
    hud_init_widget_defaults_us2(self + 0x1C8, g_menu_hud_desc_title, owner);
    hud_init_widget_defaults_us2(self + 0x220, g_menu_hud_label_desc_alt, owner);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(self + 0x4C) = 0x60241700;
    *object_get_fourth_field(self + 0x98) = 0x55F0C070;
    *object_get_fourth_field(self + 0xE4) = 0x55F0C070;
    *object_get_fourth_field(self + 0x17C) = 0x70FFFEED;
    *object_get_fourth_field(self + 0x130) = 0x55F0C070;
    *object_get_fourth_field(self + 0x2B8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x310) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x1C8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x220) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x368) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x3C0) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x418) = 0x80F0F0F0;
    hud_set_widget_field_a(self + 0x2B8, 0);
    hud_set_widget_field_a(self + 0x310, 1);
    object_set_second_float4(self + 0x310, 0.9f, 0.9f, zero, zero);
    object_set_helper_result(self, g_resident_data_base[0] + 0x8710, 0x9E);
    object_set_helper_result(self + 0x4C, g_resident_data_base[0] + 0x8710, 0x9F);
    object_set_helper_result(self + 0x98, g_resident_data_base[0] + 0x8710, 0xA0);
    object_set_helper_result(self + 0xE4, g_resident_data_base[0] + 0x8710, 0xA1);
    object_set_helper_result(self + 0x130, g_resident_data_base[0] + 0x8710, 0x5D);
    object_set_helper_result(self + 0x17C, g_resident_data_base[0] + 0x8710, 0x5E);
    *(int *)(self + 0x4AC) = 0;
    *(int *)(self + 0x4B0) = 0;
    *(int *)(self + 0x4B8) = 3;
    object_init_derived_c(self + 0x278, g_menu_icon_desc, owner);
    *object_get_fourth_field(self + 0x278) = 0x60F0F0B0;
    object_set_second_float4(self + 0x278, 32.0f, 32.0f, zero, zero);
    *object_get_fourth_field(self + 0x1C8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x220) = 0x80F0F0F0;
    hud_set_widget_field_b(self + 0x1C8, GetLocalizedString(0x2BEA));
    hud_set_widget_field_b(self + 0x220, GetLocalizedString(0x2BEF));
    hud_set_widget_field_b(self + 0x368, (int)(self + 0x470));
    hud_set_widget_field_b(self + 0x3C0, (int)(self + 0x480));
    hud_set_widget_field_b(self + 0x418, (int)(self + 0x490));
    hud_set_widget_field_a(self + 0x368, 0);
    hud_set_widget_field_a(self + 0x3C0, 0);
    hud_set_widget_field_a(self + 0x418, 0);
    *(int *)(self + 0x4B4) = 0;
    hud_set_widget_field_b(self + 0x2B8, GetLocalizedString(0x2BE5));
    grid_menu_update_us2(self, 0);
}


typedef struct {
    unsigned char gap0[0x4AC];
    int column, row, index, mode;
} DobboGridState312;
typedef struct { unsigned char pad[6]; short id; short tail; } SelectionRow;
extern SelectionRow g_grid_menu_selection_rows[];
extern SelectionRow ref_L00_00286D68_00[];

/* Moves the first-group cursor from the pad buttons; may hand the cursor over to another group. */
void grid_menu_handle_input_first_group_us2(DobboGridState312 *state, unsigned int buttons)
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


/* The cursor's up/down/left/right move: the button mask picks the direction, the state keeps
   the column (0x43C), the row (0x440), the chosen index (0x444) and the mode (0x448). */
void grid_menu_handle_input_main_grid_us2(DobboGridState312 *state, unsigned int buttons)
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
void grid_menu_handle_input_small_group_us2(DobboGridState312 *state, unsigned int buttons)
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


extern int snd_play_from_global_bank(int, unsigned int, void *);
extern short g_grid_menu_choice_value;

/* Moves the cursor between the four groups from the pad buttons and stores the chosen value. */
void grid_menu_handle_input_single_choice_us2(char *menu, unsigned int buttons)
{
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x4B8) = 2;
        *(int *)(menu + 0x4B0) = 1;
        *(int *)(menu + 0x4AC) = 3;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x4B8) = 2;
        *(int *)(menu + 0x4AC) = 3;
        *(int *)(menu + 0x4B0) = 0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x4B8) = 0;
        *(int *)(menu + 0x4AC) = 1;
        *(int *)(menu + 0x4B0) = 0;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x4B0) = 0;
        *(int *)(menu + 0x4B8) = 3;
        *(int *)(menu + 0x4AC) = 0;
    }
    *(int *)(menu + 0x4B4) = g_grid_menu_choice_value;
}


/* func_US2_00345298, the v2.00 copy of func_00344378: the same lookup, where mode 2 has its own
   case: at index 7, with flag 0x31 set and flag 7 clear, it reads entry 0x31. The shared body is
   reached by goto, and the one `return 0` follows that case, because retail keeps both there. */
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_weapon_table[];
typedef struct { unsigned char pad[0x42]; short field42; unsigned char rest[0xE0 - 0x44]; } Entry224;
typedef struct { int v[4]; } Ids_00344378;
extern Ids_00344378 g_grid_menu_text_ids;

/* Returns the text id of the selected grid menu entry, or 0 when it is not owned. */
int grid_menu_get_selected_text_id_us2(DobboGridState312 *state)
{
    Ids_00344378 table = g_grid_menu_text_ids;
    int value;
    int index;

    switch (state->mode) {
    case 0:
        index = state->index;
common:
        if (g_item_owned_flags[index] != 0) {
            value = ((Entry224 *)g_weapon_table)[g_item_slot_to_record[index]].field42;
            break;
        }
        goto none;
    case 1:
        if (g_item_owned_flags[6] != 0) {
            value = ((Entry224 *)g_weapon_table)[g_item_slot_to_record[6]].field42;
            break;
        }
        goto none;
    case 2:
        index = state->index;
        if (index == 7 && g_item_owned_flags[0x31] != 0 && g_item_owned_flags[7] == 0) {
            value = ((Entry224 *)g_weapon_table)[g_item_slot_to_record[0x31]].field42;
            break;
        }
        goto common;
none:
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
