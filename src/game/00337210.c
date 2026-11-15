#include "common.h"

/* Adapted from the public RAC1 pause-menu grid renderer (GPL-3.0). */

extern void meter_set_max(unsigned char *, int);
extern void meter_set_value(char *, int);
extern int *object_get_fourth_field(void *);
extern void object_set_flag_value(void *, int);
extern int object_is_flag_positive(void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(void *, int, int);
extern int hud_get_widget_value_int(void *);
extern void hud_set_widget_field_b(int, unsigned int);
extern void object_set_first_pair(void *, int, int);
extern void shop_choose_item_colors(int, unsigned int *, unsigned int *, unsigned int *);
extern char *GetLocalizedString(int);
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern unsigned char D_001395B8[];
typedef struct {
    int exists, unknown4, textId;
    char pad0C[48];
    unsigned short icon;
    char pad3E[46];
    int maxExperience;
    char pad70[112];
} GridWeapon;
extern GridWeapon g_weapon_table[];
typedef struct { char pad[0x40]; int item[4]; } GridEquipped;
extern GridEquipped g_pause_menu_state;
extern int D_00139868[];
extern int D_001ADB18[4], D_001ADB28[2];

typedef struct { int value[4]; } GridLabels;
typedef struct { int x, y; } GridOffset;

typedef struct {
    unsigned short icon;
    short frame, type, item, unused;
} GridCell;
typedef struct {
    GridCell *cells;
    int columns, rows, selectedColumn, selectedRow;
    float *iconStep, *iconOrigin, *cellStep, *cellOrigin, *labelOrigin;
    void *background, *cellBackground, *selection, *meter;
    int equippedSet;
    void *sprite;
    int unknown40;
    void *label;
    float *origin;
    int selectedItem;
    int *hidden;
    int showSelection, highlightEquipped;
} Grid;

#define POSITION(node, step, base, col, row) \
    func_00335E38(node, ((step)[0] * (float)(col) + (base)[0]) + grid->origin[0], \
                        ((step)[1] * (float)(row) + (base)[1]) + grid->origin[1], 0.0f, 0.0f)
typedef struct {
    int reserved[2];
    short adjustment, pad;
    void (*draw)(void *);
} GridVTable;
#define DRAW(node) { \
    char *drawObject = (char *)(node); \
    GridVTable *vtable = *(GridVTable **)(drawObject + 0x30); \
    drawObject += vtable->adjustment; \
    vtable->draw(drawObject); \
}
#define WEAPON(item) (&D_00239BA0[D_00139568[item]])
#define WEAPON_AT(item) ((GridWeapon *)((char *)D_00239BA0 + D_00139568[item] * size))

/* Draws the grid of weapons and items on the pause menu, with icons, the current choice, its name and a progress bar for each weapon. */
void DrawItemGrid(Grid *grid)
{
    int row, col;
    int size = 0xE0;
    if (grid->background) *(int *)object_get_fourth_field(grid->background) = 0x30F0C070;
    object_set_flag_value(grid->label, 0);
    for (row = 0; row < grid->rows; row++) {
        unsigned int grey = 0x80808080;
        unsigned int disabledColor = grey;
        for (col = 0; col < grid->columns; col++) {
            int index = row * grid->columns + col;
            int hide = 0;
            int i;
            if (grid->hidden) {
                for (i = 0; grid->hidden[i] >= 0 && i < 10; i++) {
                    if (index == grid->hidden[i]) { hide = 1; break; }
                }
            }
            if (hide) continue;
            if (grid->meter) object_set_flag_value(grid->meter, 0);
            if (grid->background) *(int *)object_get_fourth_field(grid->background) = 0x30F0C070;
            object_set_flag_value(grid->sprite, 0);
            if (grid->cellBackground) {
                POSITION(grid->cellBackground, grid->cellStep, grid->cellOrigin, col, row);
                DRAW(grid->cellBackground);
            }
            if (grid->cells[index].type == 2) {
                hud_set_widget_value_pair(grid->sprite, grid->cells[index].icon, grid->cells[index].frame);
                object_set_flag_value(grid->sprite, 1);
                POSITION(grid->sprite, grid->iconStep, grid->iconOrigin, col, row);
            } else if (g_item_owned_flags[grid->cells[index].item] || grid->cells[index].item == 7 ||
                       (grid->cells[index].item == 55 &&
                        (D_001395B8[0x84] || D_001395B8[0x86] || D_001395B8[0x89]))) {
                POSITION(grid->sprite, grid->iconStep, grid->iconOrigin, col, row);
                object_set_flag_value(grid->sprite, 1);
                *(int *)object_get_fourth_field(grid->sprite) = 0x60F0F0B0;
                if (grid->cells[index].icon == 0xEA85) {
                    hud_set_widget_value_pair(grid->sprite, 0xEA85, 0);
                } else {
                    int item = grid->cells[index].item;
                    if (item == 55) {
                        hud_set_widget_value_pair(grid->sprite, WEAPON_AT(item)->icon, 0);
                        if (!g_item_owned_flags[55]) *(int *)object_get_fourth_field(grid->sprite) = disabledColor;
                    } else if (item == 7) {
                        int icon = 0xEA9A;
                        if (!g_item_owned_flags[7]) {
                            if (g_item_owned_flags[49]) icon = WEAPON_AT(49)->icon;
                            else object_set_flag_value(grid->sprite, 0);
                        }
                        hud_set_widget_value_pair(grid->sprite, icon, 0);
                    } else {
                        hud_set_widget_value_pair(grid->sprite, WEAPON_AT(item)->icon, 0);
                    }
                }
                if (grid->equippedSet != 2 &&
                    g_pause_menu_state.item[grid->equippedSet] == grid->cells[index].item &&
                    grid->highlightEquipped && grid->background)
                    *(int *)object_get_fourth_field(grid->background) = 0x80FFDE8D;
                if (grid->cells[index].item && grid->cells[index].item == grid->selectedItem &&
                    object_is_flag_positive(grid->sprite)) {
                    int count;
                    hud_set_widget_field_b((int)grid->label, GetLocalizedString(WEAPON(grid->cells[index].item)->textId));
                    if (hud_get_widget_value_int(grid->sprite) == WEAPON(49)->icon)
                        hud_set_widget_field_b((int)grid->label, GetLocalizedString(WEAPON(49)->textId));
                    if (hud_get_widget_value_int(grid->sprite) == WEAPON(55)->icon && !g_item_owned_flags[55]) {
                        count = !!D_001395B8[0x84] + !!D_001395B8[0x86] + !!D_001395B8[0x89];
                        if (count > 0) {
                            GridLabels labels = *(GridLabels *)D_001ADB18;
                            hud_set_widget_field_b((int)grid->label, GetLocalizedString(labels.value[count]));
                        }
                    }
                    object_set_first_float4(grid->label, grid->labelOrigin[0] + grid->origin[0],
                                 grid->labelOrigin[1] + grid->origin[1], 0.0f, 0.0f);
                    object_set_flag_value(grid->label, 1);
                    DRAW(grid->label);
                }
                if (grid->meter && WEAPON(grid->cells[index].item)->exists) {
                    if (WEAPON(grid->cells[index].item)->icon == 0xEA7E) {
                        *(int *)object_get_fourth_field(grid->sprite) = disabledColor;
                    } else {
                        GridOffset offset = *(GridOffset *)D_001ADB28;
                        unsigned int a, b, color;
                        meter_set_max(grid->meter, WEAPON(grid->cells[index].item)->maxExperience);
                        meter_set_value(grid->meter, D_00139868[grid->cells[index].item] >> 5);
                        object_set_first_float4(grid->meter,
                            ((grid->iconStep[0] * (float)col + grid->iconOrigin[0]) + (float)offset.x) + grid->origin[0],
                            ((grid->iconStep[1] * (float)row + grid->iconOrigin[1]) + (float)offset.y) + grid->origin[1], 0.0f, 0.0f);
                        object_set_flag_value(grid->meter, 1);
                        a = 0; b = 0; color = 0;
                        shop_choose_item_colors(grid->cells[index].item, &a, &b, &color);
                        object_set_first_pair(grid->meter, a, b);
                        *(int *)object_get_fourth_field(grid->sprite) = color;
                        if (WEAPON(grid->cells[index].item)->maxExperience <= 0) {
                            meter_set_max(grid->meter, 100);
                            meter_set_value(grid->meter, 100);
                        }
                        DRAW(grid->meter);
                    }
                }
            }
            if (grid->background) POSITION(grid->background, grid->cellStep, grid->cellOrigin, col, row);
            DRAW(grid->sprite);
            if (grid->background) DRAW(grid->background);
        }
    }
    if (grid->showSelection) {
        object_set_flag_value(grid->selection, 1);
        POSITION(grid->selection, grid->cellStep, grid->cellOrigin, grid->selectedColumn, grid->selectedRow);
    }
}
#undef POSITION
#undef DRAW
#undef WEAPON
#undef WEAPON_AT
