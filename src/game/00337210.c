#include "common.h"

/* Adapted from the public RAC1 pause-menu grid renderer (GPL-3.0). */

extern void func_00336B90(unsigned char *, int);
extern void func_00336B98(char *, int);
extern int func_00335E20(void *);
extern void func_00335E68(void *, int);
extern int func_00335E88(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00336920(void *, int, int);
extern int func_00336950(void *);
extern void func_00336A38(int, unsigned int);
extern void func_00336498(void *, int, int);
extern void func_00336F20(int, unsigned int *, unsigned int *, unsigned int *);
extern int func_00288FB8(int);
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern unsigned char D_001395B8[];
typedef struct {
    int exists, unknown4, textId;
    char pad0C[48];
    unsigned short icon;
    char pad3E[46];
    int maxExperience;
    char pad70[112];
} GridWeapon;
extern GridWeapon D_00239BA0[];
typedef struct { char pad[0x40]; int item[4]; } GridEquipped;
extern GridEquipped D_001F2840;
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

void func_00337210(Grid *grid)
{
    int row, col;
    int size = 0xE0;
    if (grid->background) *(int *)func_00335E20(grid->background) = 0x30F0C070;
    func_00335E68(grid->label, 0);
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
            if (grid->meter) func_00335E68(grid->meter, 0);
            if (grid->background) *(int *)func_00335E20(grid->background) = 0x30F0C070;
            func_00335E68(grid->sprite, 0);
            if (grid->cellBackground) {
                POSITION(grid->cellBackground, grid->cellStep, grid->cellOrigin, col, row);
                DRAW(grid->cellBackground);
            }
            if (grid->cells[index].type == 2) {
                func_00336920(grid->sprite, grid->cells[index].icon, grid->cells[index].frame);
                func_00335E68(grid->sprite, 1);
                POSITION(grid->sprite, grid->iconStep, grid->iconOrigin, col, row);
            } else if (D_001A7AF8[grid->cells[index].item] || grid->cells[index].item == 7 ||
                       (grid->cells[index].item == 55 &&
                        (D_001395B8[0x84] || D_001395B8[0x86] || D_001395B8[0x89]))) {
                POSITION(grid->sprite, grid->iconStep, grid->iconOrigin, col, row);
                func_00335E68(grid->sprite, 1);
                *(int *)func_00335E20(grid->sprite) = 0x60F0F0B0;
                if (grid->cells[index].icon == 0xEA85) {
                    func_00336920(grid->sprite, 0xEA85, 0);
                } else {
                    int item = grid->cells[index].item;
                    if (item == 55) {
                        func_00336920(grid->sprite, WEAPON_AT(item)->icon, 0);
                        if (!D_001A7AF8[55]) *(int *)func_00335E20(grid->sprite) = disabledColor;
                    } else if (item == 7) {
                        int icon = 0xEA9A;
                        if (!D_001A7AF8[7]) {
                            if (D_001A7AF8[49]) icon = WEAPON_AT(49)->icon;
                            else func_00335E68(grid->sprite, 0);
                        }
                        func_00336920(grid->sprite, icon, 0);
                    } else {
                        func_00336920(grid->sprite, WEAPON_AT(item)->icon, 0);
                    }
                }
                if (grid->equippedSet != 2 &&
                    D_001F2840.item[grid->equippedSet] == grid->cells[index].item &&
                    grid->highlightEquipped && grid->background)
                    *(int *)func_00335E20(grid->background) = 0x80FFDE8D;
                if (grid->cells[index].item && grid->cells[index].item == grid->selectedItem &&
                    func_00335E88(grid->sprite)) {
                    int count;
                    func_00336A38((int)grid->label, func_00288FB8(WEAPON(grid->cells[index].item)->textId));
                    if (func_00336950(grid->sprite) == WEAPON(49)->icon)
                        func_00336A38((int)grid->label, func_00288FB8(WEAPON(49)->textId));
                    if (func_00336950(grid->sprite) == WEAPON(55)->icon && !D_001A7AF8[55]) {
                        count = !!D_001395B8[0x84] + !!D_001395B8[0x86] + !!D_001395B8[0x89];
                        if (count > 0) {
                            GridLabels labels = *(GridLabels *)D_001ADB18;
                            func_00336A38((int)grid->label, func_00288FB8(labels.value[count]));
                        }
                    }
                    func_00335E38(grid->label, grid->labelOrigin[0] + grid->origin[0],
                                 grid->labelOrigin[1] + grid->origin[1], 0.0f, 0.0f);
                    func_00335E68(grid->label, 1);
                    DRAW(grid->label);
                }
                if (grid->meter && WEAPON(grid->cells[index].item)->exists) {
                    if (WEAPON(grid->cells[index].item)->icon == 0xEA7E) {
                        *(int *)func_00335E20(grid->sprite) = disabledColor;
                    } else {
                        GridOffset offset = *(GridOffset *)D_001ADB28;
                        unsigned int a, b, color;
                        func_00336B90(grid->meter, WEAPON(grid->cells[index].item)->maxExperience);
                        func_00336B98(grid->meter, D_00139868[grid->cells[index].item] >> 5);
                        func_00335E38(grid->meter,
                            ((grid->iconStep[0] * (float)col + grid->iconOrigin[0]) + (float)offset.x) + grid->origin[0],
                            ((grid->iconStep[1] * (float)row + grid->iconOrigin[1]) + (float)offset.y) + grid->origin[1], 0.0f, 0.0f);
                        func_00335E68(grid->meter, 1);
                        a = 0; b = 0; color = 0;
                        func_00336F20(grid->cells[index].item, &a, &b, &color);
                        func_00336498(grid->meter, a, b);
                        *(int *)func_00335E20(grid->sprite) = color;
                        if (WEAPON(grid->cells[index].item)->maxExperience <= 0) {
                            func_00336B90(grid->meter, 100);
                            func_00336B98(grid->meter, 100);
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
        func_00335E68(grid->selection, 1);
        POSITION(grid->selection, grid->cellStep, grid->cellOrigin, grid->selectedColumn, grid->selectedRow);
    }
}
#undef POSITION
#undef DRAW
#undef WEAPON
#undef WEAPON_AT
