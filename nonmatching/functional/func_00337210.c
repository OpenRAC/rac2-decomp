/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* func_00337210 - 2500 bytes, 28 places. Tier opus-1 (Claude Opus 5.5 xhigh),
 * task v2028. USA v1.01, game -O2 -G0 -ffunction-sections, in src/game/00336A78.c
 * where the INCLUDE_ASM marker stands (func_00335E20 is already declared there
 * as returning int *). All declarations it needs are below.
 *
 * Best check.py: 2508/2500 bytes, 0 of 28 places. No linked build was run.
 *
 * What differs on the build's compiler: two extra instructions, which account
 * for all 8 bytes. At the row preheader retail has lui v0,0x8080 / ori v0,0x8080 /
 * sw v0,0x1C(sp); this has lui / sw v0,0x1C(sp) / ori / sw. The extra store then
 * brings one alignment nop after lw a0,4(s0). The other aligned rows read, up to
 * +0x2A0, are the 8-byte shift showing through branch displacements and
 * relocation masking.
 *
 * Cause, tested: the split constant 0x80808080 has no hard register. Reload gives
 * the first half an output reload, but the ior's combined in-out RELOAD_OTHER
 * reload loses inheritance, so delete_output_reload cannot remove the first store.
 * The refusal comes from tools/compiler/transformers/reload_reg_used_guard.py: its
 * test reads reload_reg_used, which holds the non-spill registers and also this
 * insn's own RELOAD_OTHER marks. func_002E7338, func_L11_004465F8 and func_00316E08
 * show the same store. Why retail behaves like the narrow test below is unexplained.
 *
 * Private diagnostic, nothing in the repo: a binary-patched copy of cc1 whose guard
 * tests a snapshot of reload_reg_used taken right after
 * IOR_COMPL_HARD_REG_SET (reload_reg_used, chain->used_spill_regs).
 * Differing instructions, relocated fields ignored:
 *                          stock        no guard     narrow guard
 *   func_L00_003C5B88      0            78           0  (the guard's witness)
 *   func_002E7338          4            0            0
 *   func_L11_004465F8      7            0            0
 *   func_00316E08          147          2            2
 *   func_00337210 (this)   2508 bytes   not re-run   2500 bytes, 0
 * Only these five functions were tried. Relocated values were not compared. Not
 * run: tools/build.py all --strict, tests/test_reload_reg_used_guard.py,
 * func_L15_00437B68.
 *
 * Wordings that reach retail's code (each checked with the narrow compiler):
 * - DRAW is a plain block. do/while(0) emits NOTE_INSN_LOOP_BEG, which changed the
 *   virtual-call registers, added the label/meter nop and extra reload rows.
 * - size = 0xE0 at function level, used for the 55, 49 and final-else lookups
 *   (43 differences -> 7). Without it the dump shows the three arms' 0xE0 rejected
 *   by loop.c ("savings 3 not desirable"); as one local it is rematerialized before
 *   each madd, after mtlo. Row- and column-level declarations tie with this one;
 *   inside the else block it stays in a register (2492 bytes). The other WEAPON
 *   sites must stay in plain array form.
 * - D_001F2840.item[set] (7 -> 0). An array reference expands as (plus base offset),
 *   so the sum ties to the base; the earlier cast of a char pointer gave
 *   (plus offset base) and moved the equippedSet register from v1 to a0. That the
 *   operand order is the reason is inferred from the expander and the listing; the
 *   result itself is tested.
 * - grey -> disabledColor is a local holding a value before its use. Constant
 *   wordings of it (column-level, arm-local, function-level, int, inline function,
 *   struct initializer, adjacent to the use) all kept two stores or took $fp.
 *
 * Next: decide the guard's narrowing in the transformer, run the full strict build
 * on it, then this body should only need installing and check.py.
 */
extern void func_00336B90(unsigned char *, int);
extern void func_00336B98(char *, int);
extern int *func_00335E20(void *);
extern void func_00335E68(void *, int);
extern int func_00335E88(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00336920(void *, int, int);
extern int func_00336950(void *);
extern void func_00336A38(void *, char *);
extern void func_00336498(void *, int, int);
extern void func_00336F20(int, int *, int *, int *);
extern char *func_00288FB8(int);
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
typedef struct { char pad[0x40]; int item[2]; } GridEquipped;
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
    if (grid->background) *func_00335E20(grid->background) = 0x30F0C070;
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
            if (grid->background) *func_00335E20(grid->background) = 0x30F0C070;
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
                *func_00335E20(grid->sprite) = 0x60F0F0B0;
                if (grid->cells[index].icon == 0xEA85) {
                    func_00336920(grid->sprite, 0xEA85, 0);
                } else {
                    int item = grid->cells[index].item;
                    if (item == 55) {
                        func_00336920(grid->sprite, WEAPON_AT(item)->icon, 0);
                        if (!D_001A7AF8[55]) *func_00335E20(grid->sprite) = disabledColor;
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
                    *func_00335E20(grid->background) = 0x80FFDE8D;
                if (grid->cells[index].item && grid->cells[index].item == grid->selectedItem &&
                    func_00335E88(grid->sprite)) {
                    int count;
                    func_00336A38(grid->label, func_00288FB8(WEAPON(grid->cells[index].item)->textId));
                    if (func_00336950(grid->sprite) == WEAPON(49)->icon)
                        func_00336A38(grid->label, func_00288FB8(WEAPON(49)->textId));
                    if (func_00336950(grid->sprite) == WEAPON(55)->icon && !D_001A7AF8[55]) {
                        count = !!D_001395B8[0x84] + !!D_001395B8[0x86] + !!D_001395B8[0x89];
                        if (count > 0) {
                            GridLabels labels = *(GridLabels *)D_001ADB18;
                            func_00336A38(grid->label, func_00288FB8(labels.value[count]));
                        }
                    }
                    func_00335E38(grid->label, grid->labelOrigin[0] + grid->origin[0],
                                 grid->labelOrigin[1] + grid->origin[1], 0.0f, 0.0f);
                    func_00335E68(grid->label, 1);
                    DRAW(grid->label);
                }
                if (grid->meter && WEAPON(grid->cells[index].item)->exists) {
                    if (WEAPON(grid->cells[index].item)->icon == 0xEA7E) {
                        *func_00335E20(grid->sprite) = disabledColor;
                    } else {
                        GridOffset offset = *(GridOffset *)D_001ADB28;
                        int a, b, color;
                        func_00336B90(grid->meter, WEAPON(grid->cells[index].item)->maxExperience);
                        func_00336B98(grid->meter, D_00139868[grid->cells[index].item] >> 5);
                        func_00335E38(grid->meter,
                            ((grid->iconStep[0] * (float)col + grid->iconOrigin[0]) + (float)offset.x) + grid->origin[0],
                            ((grid->iconStep[1] * (float)row + grid->iconOrigin[1]) + (float)offset.y) + grid->origin[1], 0.0f, 0.0f);
                        func_00335E68(grid->meter, 1);
                        a = 0; b = 0; color = 0;
                        func_00336F20(grid->cells[index].item, &a, &b, &color);
                        func_00336498(grid->meter, a, b);
                        *func_00335E20(grid->sprite) = color;
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
