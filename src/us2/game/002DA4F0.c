#include "include_asm.h"
#include "names.h"

extern void F70997ba9_FUN_002FC560(int a, int b);
extern void F70997ba9_FUN_0027C540(int a);
extern char *F70997ba9_FUN_00288FB8(int id);
extern int F70997ba9_FUN_0027F198(void *p, int i);
extern void F70997ba9_FUN_0027F120(void);
extern void F70997ba9_FUN_0027F5B8(int a, int b, long c, void *d, int e);
extern void F70997ba9_FUN_0027F110(void);
extern void F70997ba9_FUN_0027C660(void);

/* Draws five text labels in a column, sized to the widest one (a sixth when the extra flag is set). */
int menu_label_column_draw_us2(int *menu)
{
    int max_width;
    int width;
    int x;
    int row_height;
    int y;

    F70997ba9_FUN_002FC560(66, 68);
    F70997ba9_FUN_002FC560(71, 11);
    F70997ba9_FUN_0027C540(0);
    max_width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11251), -1);
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11263), -1);
    if (width >= max_width)
        max_width = width;
    if (*(int *)0x1A79F8 != 0) {
        width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11252), -1);
        if (width >= max_width)
            max_width = width;
    }
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11264), -1);
    if (width >= max_width)
        max_width = width;
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11265), -1);
    if (width >= max_width)
        max_width = width;
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11237), -1);
    if (width >= max_width)
        max_width = width;
    x = (menu[8] - max_width) >> 1;
    if (x <= 1)
        x = 2;
    row_height = menu[9] / (*(int *)0x1A79F8 != 0 ? 7 : 6);
    F70997ba9_FUN_0027F120();
    y = row_height - 6;
    F70997ba9_FUN_0027F5B8(x, y, 0x80FFA888L, F70997ba9_FUN_00288FB8(11251), -1);
    y += row_height;
    F70997ba9_FUN_0027F5B8(x, y, 0x80FFA888L, F70997ba9_FUN_00288FB8(11263), -1);
    y += row_height;
    F70997ba9_FUN_0027F5B8(x, y, 0x80FFA888L, F70997ba9_FUN_00288FB8(11264), -1);
    y += row_height;
    F70997ba9_FUN_0027F5B8(x, y, 0x80FFA888L, F70997ba9_FUN_00288FB8(11265), -1);
    y += row_height;
    F70997ba9_FUN_0027F5B8(x, y, 0x80FFA888L, F70997ba9_FUN_00288FB8(11237), -1);
    F70997ba9_FUN_0027F110();
    F70997ba9_FUN_0027C660();
    return 2;
}


