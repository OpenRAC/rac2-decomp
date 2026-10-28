/* functional: medium. Starts from the near-miss draft; same reads, writes and calls in retail order; byte differences are register allocation only. */
/* func_00341030 (380 bytes, boot; unit src/game/0033F030.c, -O2 -G0).
   26 October 2026 (M32): 368/380. Grid menu input; calls, fields and the movz wrap of
   the increments agree. Retail's decrements keep the new value in $v1 for the store and
   test a $v0 copy (daddu $v0,$v1,$zero; bgez) - one extra move each - which none of
   --x, x--, x = x - 1, a local or a ternary reproduces; with `if (++x >= n) x = 0`
   the size is 380 but the increments lose the movz. */
typedef struct {
    short unk0;
    short unk2;
    short unk4;
    short id;
    short unk8;
} MenuCell_00341030;

typedef struct {
    char pad000[0x1B0];
    float *origin;
    char pad1B4[0x50];
    int column;
    int row;
    int columns;
    int rows;
    int selected;
} Menu_00341030;

extern void func_00115484(void *, int, int);
extern void func_00335E38(void *, float, float, float, float);
extern void func_002E5E58(int, int, int);

/* Grid menu input: draws the menu at its origin, moves the cursor with the four
   direction bits (wrapping, with a click) and selects the cell's id. */
int func_00341030(Menu_00341030 *menu, int pad, MenuCell_00341030 *cells)
{
    float offset[2];

    func_00115484(offset, 0, 8);
    if (cells != 0) {
    menu->selected = 0;
    func_00335E38(menu, offset[0] + menu->origin[0], offset[1] + menu->origin[1], 0.0f, 0.0f);
    if (pad & 0x1000) {
        func_002E5E58(3, 0, 0);
        if (--menu->row < 0)
            menu->row = menu->rows - 1;
    } else if (pad & 0x4000) {
        func_002E5E58(3, 0, 0);
        menu->row = menu->row + 1 < menu->rows ? menu->row + 1 : 0;
    } else if (pad & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--menu->column < 0)
            menu->column = menu->columns - 1;
    } else if (pad & 0x2000) {
        func_002E5E58(3, 0, 0);
        menu->column = menu->column + 1 < menu->columns ? menu->column + 1 : 0;
    }
    menu->selected = cells[menu->row * menu->columns + menu->column].id;
    }
    return 0;
}
