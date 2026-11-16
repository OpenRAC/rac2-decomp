#include "include_asm.h"
#include "names.h"

/* The 23-word descriptor func_00337210 takes, filled from the object: the defaults
   first, then the object's own fields. The same shape as func_00344F98, in the -G8
   unit where the small data comes out $gp-relative. */
extern void DrawItemGrid(int *);

extern char g_item_grid_second_mode_rows[];

extern int g_item_grid_build_second_desc_a __attribute__((sda));

extern int g_item_grid_build_second_desc_b __attribute__((sda));

extern int g_item_grid_build_second_desc_c __attribute__((sda));

extern int g_item_grid_build_second_desc_d __attribute__((sda));

extern int g_item_grid_build_second_desc_e __attribute__((sda));

extern int g_item_grid_build_second_desc_f __attribute__((sda));

extern int g_item_grid_build_second_desc_g __attribute__((sda));

/* Fills in the draw descriptor for the item grid, in mode 1, and hands it to the grid drawer. */
void item_grid_build_descriptor_second_mode(char *menu)
{
    int desc[23];

    desc[20] = 0;
    desc[14] = 1;
    desc[11] = 0;
    desc[13] = 0;
    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x494);
    desc[21] = ((*(int *)(menu + 0x498) ^ 1) == 0);
    desc[3] = *(int *)(menu + 0x48C);
    desc[4] = *(int *)(menu + 0x490);
    desc[16] = (int)(menu + 0x448);
    desc[9] = (int)&g_item_grid_build_second_desc_g;
    desc[1] = g_item_grid_build_second_desc_a;
    desc[2] = g_item_grid_build_second_desc_b;
    desc[0] = (int)g_item_grid_second_mode_rows;
    desc[17] = (int)(menu + 0x210);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x258);
    desc[18] = *(int *)(menu + 0x400);
    desc[8] = (int)&g_item_grid_build_second_desc_f;
    desc[7] = (int)&g_item_grid_build_second_desc_e;
    desc[6] = (int)&g_item_grid_build_second_desc_d;
    desc[5] = (int)&g_item_grid_build_second_desc_c;
    desc[22] = 1;
    DrawItemGrid(desc);
}

extern char g_selection_menu_rows[];

extern int g_item_grid_build_fourth_desc_a __attribute__((sda));

extern int g_item_grid_build_fourth_desc_b __attribute__((sda));

extern int g_item_grid_build_fourth_desc_c __attribute__((sda));

extern int g_item_grid_build_fourth_desc_d __attribute__((sda));

extern int g_item_grid_build_fourth_desc_e __attribute__((sda));

extern int g_item_grid_build_fourth_desc_f __attribute__((sda));

extern int g_item_grid_build_fourth_desc_g __attribute__((sda));

/* Fills in the draw descriptor for the item grid, in mode 3, and hands it to the grid drawer. */
void item_grid_build_descriptor_fourth_mode(char *menu)
{
    int desc[23];

    desc[20] = 0;
    desc[11] = 0;
    desc[13] = 0;
    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x494);
    desc[21] = ((*(int *)(menu + 0x498) ^ 3) == 0);
    desc[3] = *(int *)(menu + 0x48C);
    desc[4] = *(int *)(menu + 0x490);
    desc[16] = (int)(menu + 0x448);
    desc[9] = (int)&g_item_grid_build_fourth_desc_g;
    desc[14] = 3;
    desc[1] = g_item_grid_build_fourth_desc_a;
    desc[2] = g_item_grid_build_fourth_desc_b;
    desc[0] = (int)g_selection_menu_rows;
    desc[17] = (int)(menu + 0x210);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x258);
    desc[18] = *(int *)(menu + 0x400);
    desc[8] = (int)&g_item_grid_build_fourth_desc_f;
    desc[7] = (int)&g_item_grid_build_fourth_desc_e;
    desc[6] = (int)&g_item_grid_build_fourth_desc_d;
    desc[5] = (int)&g_item_grid_build_fourth_desc_c;
    desc[22] = 1;
    DrawItemGrid(desc);
}

/* Pad input on the 3 x 2 selection grid: up/down/left/right move the cursor (sound 3) and
   cross confirms an available entry (sound 4, else 5); the entry under the cursor is kept
   at +0x494 and, when available, its table value in D_001ADB10. */
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x48C]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[0xD8]; } SelectionMaterial;

extern int snd_play_from_global_bank(int, int, void *);
extern unsigned char g_item_owned_flags[] __attribute__((section(".sdata")));
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_table[];
extern int g_selection_grid_cursor[];
extern int g_selected_item_material __attribute__((sda));
extern SelectionEntry g_menu_item_table_second[];

/* Moves the cursor on a small selection grid with the pad and lets the player pick an item they own. */
void selection_grid_handle_input(SelectionOwner *owner, int buttons)
{
    if (buttons & 0x1000) {
        int row;
        snd_play_from_global_bank(3, 0, 0);
        row = owner->row - 1;
        owner->row = row;
        if (row < 0) {
            owner->row = 0;
            owner->state = 1;
        }
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        if (owner->row == 0) {
            if (owner->column == 0) {
                owner->column = 1;
                owner->row = 1;
            } else
                owner->row = 1;
        } else if (owner->row == 1) {
            owner->state = 3;
            owner->row = 0;
            owner->column--;
        }
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        --owner->column;
        if (owner->row == 0)
            owner->column = owner->column < 0 ? 2 : owner->column;
        else
            owner->column = owner->column < 1 ? 2 : owner->column;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        ++owner->column;
        if (owner->row == 0)
            owner->column = owner->column > 2 ? 0 : owner->column;
        else
            owner->column = owner->column > 2 ? 1 : owner->column;
    } else if (buttons & 0x40) {
        int id = g_menu_item_table_second[owner->column + owner->row * 3].v[3];
        if (id && g_item_owned_flags[id]) {
            snd_play_from_global_bank(4, 0, 0);
            g_selection_grid_cursor[0] = id;
            owner->selected = id;
        } else
            snd_play_from_global_bank(5, 0, 0);
    }
    {
        int id = g_menu_item_table_second[owner->column + owner->row * 3].v[3];
        owner->selected = id;
        if (id && g_item_owned_flags[id])
            g_selected_item_material = ((SelectionMaterial *)(g_weapon_table + g_item_slot_to_record[id] * 0xE0))->material;
    }
}

/* func_00348EC0: draws the list menu's rows centred on the screen. The row spacing is rounded with
   label_y after the row count is read; that block end is what gives retail's count, spacing and
   0.5 registers. Standalone declarations, the boot's addresses. */
#include "common.h"

extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void gfx_draw_screen_element_stored(char *);
extern float *object_get_first_field(char *);
extern int *object_get_fourth_field(char *);
extern float g_list_menu_label_y __attribute__((sda));
extern float g_hud_scale[] MACRO_ADDR;
extern int g_screen_height[] MACRO_ADDR;
extern float g_centered_rows_rect_x_offset __attribute__((sda));
extern float g_centered_rows_rect_y_base[] MACRO_ADDR;
extern float g_centered_rows_rect_y_step __attribute__((sda));
extern float g_centered_rows_alt_x_offset __attribute__((sda));
extern float g_centered_rows_alt_y_base[] MACRO_ADDR;
extern float g_centered_rows_alt_y_step __attribute__((sda));

typedef struct { float x, y, w, h; } ListRect;
typedef struct {
    char pad[0x434];
    ListRect *origin;
    int unknown438;
    int selected;
    int enabled;
    int count;
    int showSpecial;
} ListMenu;
typedef struct { short pad[4]; short offset; short pad2; void (*call)(char *); } ListVtable;
typedef struct {
    ListRect *position;
    ListRect *scale;
    void *parameter08;
    unsigned int *colors;
    float *visibility;
    char lifetime[0x1C];
    ListVtable *table;
    void *metrics;
    unsigned long style;
    char *text;
    int alignment;
} ListSlot;

extern int g_hud_mode;

/* label_y, the HUD label idiom (the shared definition in src/levels/15_gorn/L15_00431590-g8.c, its
   mode word the boot's D_001B23A0). Its tests do not change the result: flow deletes their stores
   and jump2 their jumps, but only after allocation and both scheduling passes, which see the block
   they end. Here it rounds the list row spacing. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the list menu rows centred on the screen and highlights the selected row. */
void list_menu_draw_centered_rows(char *rawMenu)
{
    int color = math_ping_pong_blend_values(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int startY, i, spacing, halfHeight, rowCount;
    float half, spacingF;
    ListMenu *menu = (ListMenu *)rawMenu;

    if (menu->enabled) {
        gfx_draw_screen_element_stored(rawMenu);
        gfx_draw_screen_element_stored(rawMenu + 0x130);
        gfx_draw_screen_element_stored(rawMenu + 0x4C);
        gfx_draw_screen_element_stored(rawMenu + 0x98);
        gfx_draw_screen_element_stored(rawMenu + 0xE4);
        rowCount = menu->count;
        half = (float)rowCount * 0.5f;
        spacing = label_y(rawMenu, g_list_menu_label_y, g_hud_scale[0], 0.5f, 1);
        spacingF = (float)spacing;
        halfHeight = g_screen_height[0] >> 1;
        startY = (int)((float)halfHeight - spacingF * half);
        for (i = 0; i < menu->count; i++) {
            ListRect *rect;
            char *slot;
            ListVtable *vtable;
            int rowColor;

            if (i == 7 && !menu->showSpecial)
                continue;
            rect = (ListRect *)((float *)object_get_first_field(rawMenu + 0x17C));
            rect->x = g_centered_rows_rect_x_offset + menu->origin->x;
            rect->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)startY;
            rowColor = i == menu->selected ? color : 0x55F0C070;
            *((int *)object_get_fourth_field(rawMenu + 0x1C8)) = rowColor;
            gfx_draw_screen_element_stored(rawMenu + 0x17C);
            rect = (ListRect *)((float *)object_get_first_field(rawMenu + 0x1C8));
            rect->x = g_centered_rows_rect_x_offset + menu->origin->x;
            rect->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)startY;
            gfx_draw_screen_element_stored(rawMenu + 0x1C8);
            slot = (char *)&((ListSlot *)(rawMenu + 0x218))[i];
            rect = (ListRect *)((float *)object_get_first_field(slot));
            rect->x = g_centered_rows_alt_x_offset + menu->origin->x;
            rect->y = (g_centered_rows_alt_y_base[0] + (float)i * g_centered_rows_alt_y_step) + (float)startY;
            vtable = *(ListVtable **)(rawMenu + i * 72 + 0x248);
            spacing = vtable->offset;
            vtable->call(slot + spacing);
        }
    }
}
