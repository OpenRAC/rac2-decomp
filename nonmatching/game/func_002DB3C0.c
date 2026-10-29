/* Nonmatching USA644/644 bytes, 0/28 placements. Six bounded checks:
 * initial donor adaptation644; count lifetime deferred644; indexed sentinel
 * count recovers all operations except the step/condition-offset allocation
 * (s7/fp instead of retail fp/s7). Repeated height division680; -g and a named
 * byte offset tie the indexed form. No flags retained. Reopen on actual source
 * lifetime/type evidence for that pair; no register pin or fake dependency.
 *
 * All 64-bit font style contracts are retained: signed 32-bit local highlight colors
 * sign-extend into the 64-bit style (as in the current donor), while the literal
 * right-column style is a positive 64-bit value. 288FB8 actually returns s32
 * address bits; callers cast explicitly. GS register value is unsigned64.
 * The aggregate font layout initializes all 12 halfwords and the compiler copies
 * the complete 24 bytes. FontPrint reads/mutates only its complete 24-byte layout.
 * Choices retain their full 20-byte stride; external menu prefix reaches 0x3B.
 * Actual C definitions verified for all callees; implicit memset retail returns
 * the original destination pointer. No packet/vector undersizing or volatile.
 */
/* Adapted from RAC1 draw_menu_choice_list, src/game/pause.c at8bbc6b38
 * (GPL-3.0), itself credited to Lombyte src/ui/menus/fun_00221460.c.
 * RAC2 uses20-byte choices and adds the empty-list prompt measured below. */
#include "common.h"

typedef struct {
    int text;
    unsigned char *value;
    int names[3];
} ChoiceItem;
typedef struct {
    char reserved00[0x20];
    int width, height;
    char reserved28[8];
    int flags;
    ChoiceItem *items;
    int selected;
} ChoiceMenuPrefix;
typedef struct { short s[12]; } ChoiceTextBox;
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C540(int);
extern int func_00288FB8(int);
extern void func_00280190(unsigned short *, unsigned long, unsigned char *, int);
extern void func_0027F538(int, int, unsigned long, unsigned char *, int);
extern void func_0027F980(int, int, unsigned long, unsigned char *, int);
extern void func_0027C660(void);

int func_002DB3C0(ChoiceMenuPrefix *menu)
{
    ChoiceItem *item;
    int count;
    int index, step, y, color;
    func_002FC560(0x47, 0x2004BULL);
    func_0027C540(0);
    if ((menu->flags & 1) && menu->items[0].text == 0) {
        /* A complete mutable font layout is initialized and copied by value. */
        ChoiceTextBox box = {{1, menu->height + 1, 1, menu->width + 1,
                              menu->width >> 1, menu->height / 3, 0, 0, 16, 1}};
        func_00280190((unsigned short *)&box, 0x80FFA888UL,
                     (unsigned char *)func_00288FB8(0x2E0C), -1);
    }
    for (count = 0; menu->items[count].text != 0; count++) {
    }
    step = menu->height / (count + 1);
    y = step - 8;
    for (index = 0; menu->items[index].text != 0; index++) {
        int value = 0;
        item = &menu->items[index];
        if (index == menu->selected)
            color = 0x8020FFFF;
        else
            color = 0x80FFA888;
        if (item->value)
            value = *item->value;
        func_0027F538(12, y, (unsigned long)color,
                     (unsigned char *)func_00288FB8(item->text), -1);
        func_0027F980(menu->width - 12, y, 0x80FFA888UL,
                     (unsigned char *)func_00288FB8(value ? item->names[0] : item->names[1]), -1);
        y += step;
    }
    func_0027C660();
    return 2;
}
