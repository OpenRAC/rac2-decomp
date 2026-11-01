#include "include_asm.h"

#include "common.h"
typedef struct { u16 top, bottom, left, right, x, y, width, height, line, flags, extra0, extra1; } TextBox_002D99E8;
typedef struct {
    char pad0[0x18];
    int x, y, width, height;       
    char pad1[0x30 - 0x28];
    int selected[29];              
    int scroll;                    
} Menu_002D99E8;
extern int D_001AB910 __attribute__((sda));
extern int D_001ABB28 __attribute__((sda));
extern int D_001C4FA0[];
extern void func_0027C540(int);
extern int func_0029DB28(int *, int *, int *, int);
extern void func_002FC560(unsigned int, unsigned long);
extern int func_00288FB8(int);
extern void func_0027F538(int, int, long, signed char *, int);
extern void *func_00115484(void *, int, unsigned int);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0027F120(void);
extern void func_0027F110(void);
extern void func_0027C660(void);
extern void func_00280200(TextBox_002D99E8 *, int, signed char *, int);
extern void func_002D9CF8(int, int, int);

int func_PAL_002DA708(Menu_002D99E8 *menu)
{
    TextBox_002D99E8 draw, initial;
    int mask;
    int x, y, count, i, selected, color, rows, iconY;
    int iconX, iconTop, limit;
    int *list;
    int *base;

    mask = 0;
    y = 4;
    x = 4;
    func_0027C540(0);
    list = (int *)0x70000000;
    count = func_0029DB28(list, &mask, 0, 0);
    func_002FC560(0x42, 0x44);
    func_002FC560(0x47, 0x10B);
    if (!D_001AB910) {
        x = menu->x;
        y = menu->y;
    }
    func_0027F538(x, y, 0x80FFA888, (signed char *)func_00288FB8(0xBD6), -1);
    y += 20;
    func_00115484(&initial, 0, 24);
    initial.bottom = menu->height;
    initial.right = menu->width;
    initial.line = 16;
    initial.top = y;
    initial.left = x;
    draw = initial;
    if (D_001ABB28)
        func_0027EB88(y, menu->height, x, menu->width, 64, 0x202020);
    for (i = 0; i < count; i++) {
        iconX = x + 4;
        iconY = y + 10;
        base = D_001C4FA0;
        selected = menu->selected[base[0x230 / 4]] == i;
        color = selected ? 0x8020FFFF : 0x80FFA888;
        if (selected)
            func_0027F120();
        limit = x + 16;
        draw.x = limit;
        draw.y = y - menu->scroll;
        func_00280200(&draw, color, (signed char *)func_00288FB8(list[i]), -1);
        if (selected) {
            if ((s16)draw.y < (limit = (s16)draw.top + 4))
                menu->scroll -= 4;
            if ((s16)draw.bottom - (s16)draw.height - 4 < (s16)draw.y)
                menu->scroll += 4;
            func_0027F110();
        }
        rows = (s16)draw.height / (s16)draw.line;
        if (rows == 2)
            iconY += 6;
        iconTop = iconY - menu->scroll;
        if ((s16)draw.top + 4 <= iconTop && iconTop <= (s16)draw.bottom - 4)
            func_002D9CF8(iconX + 5, iconTop, (mask >> i) & 1);
        y += rows * 16;
    }
    func_0027C660();
    return 2;
}
