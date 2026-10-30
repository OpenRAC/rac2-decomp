/* func_002D6230 - 1700 bytes, boot and all 27 levels. Draws a text list (the ListMenu
   of func_002D5EC0): each entry's label centred, a shadow pass at
   (D_001AA444, D_001AA448) and a colour pass; the control-binding lists print the
   bound button with the label through D_001ABAC8. Returns 1 when the list switches to
   the small font to fit, else 2.

   Attempt, 30 October 2026: 1696/1700 bytes, 0/28 USA places (tools/check.py), in
   src/game/002D5E98-list-g8.c after func_002D5EC0 (which still passes 28/28) with
   ListMenu given width at 0x20 and height at 0x24.
   What differs is register allocation (MATCHING-BLOCKERS 1): retail keeps menu in
   s3, the entry index in s4, the text in s2, the colour in s7, `below` in s6 and y in
   fp, and spills i + 1 to 0x18($sp); cc1 puts menu in s2, the index in s3, the text
   in s4, the colour in s6, i + 1 in s7, `below` in fp and spills y to 0x18($sp).
   Measured steps: an unsigned colour (zero-extended for the u64 argument) cost a
   register and a frame of 0x80 (1692 bytes); a signed colour gives retail's 0x70
   frame (1668); dropping an explicit next gives 1688; one entry pointer for the colour
   choice stops cc1 hoisting the constant 12 into fp (1696).
   Tried without change at 1696: an explicit next assigned after the text, after the
   colour, before or after `below`; y declared first; y advanced after the second
   label. `y += spacing` instead of `below` is 1712. */

extern unsigned char D_00263B50[], D_00264290[], D_00263EF0[];
extern char D_00258EE8[], D_00259018[];
extern char D_00259148[], D_00259198[], D_002591E8[], D_00259238[], D_00259288[], D_002592D8[];
extern int D_00258D70[];
extern char D_00210C40[];
extern char D_001ABAC8[];
extern int D_001AA444 __attribute__((sda));
extern int D_001AA448 __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C540(long);
extern void func_0027C660(void);
extern char *func_00288FB8(int);
extern int func_0027F128(char *text, int length, unsigned char *charset);
extern void func_0027F110(void);
extern void func_0027F120(void);
extern unsigned long long func_0027C878(int);
extern void func_0027F2A8(int, int, unsigned long long, char *, int, unsigned long long, unsigned char *);
extern int func_002D68D8(int, int, int);
extern void func_00282A60(void *, unsigned int, int);
extern int func_00115DA8(char *, const char *, ...);

/* Text list drawing: each entry's label, centred, in a shadow pass and a colour pass;
 * the control-binding lists print the bound button with the label. */
int func_002D6230(ListMenu *menu)
{
    int focused = D_001F2840.current->focus == menu;
    unsigned char *font = D_00263B50;
    int size = 1;
    int lineHeight = 12;
    int count;
    int spacing;
    int centre;
    int widest;
    int y;
    int flags;
    int i;

    flags = menu->flags;
    if (flags & 4) {
        size = 3;
        font = D_00264290;
        lineHeight = 14;
    }
    if (flags & 8) {
        size = 2;
        font = D_00263EF0;
        lineHeight = 10;
    }
    func_002FC560(0x42, 0x44);
    func_002FC560(0x47, 0x2004B);
    func_0027C540(0);
    count = 0;
    while (menu->entries[count].text != 0)
        count++;
    if (menu->flags & 0x10)
        spacing = lineHeight + 3;
    else
        spacing = menu->height / (count + 1);
    centre = menu->width >> 1;
    widest = 0;
    y = spacing - lineHeight / 2 - 1;
    if (menu->flags & 0x4000) {
        for (i = 0; menu->entries[i].text != 0; i++) {
            int width = func_0027F128(func_00288FB8(menu->entries[i].text), -1, font);
            if (widest < width)
                widest = width;
        }
    }
    flags = menu->flags;
    if ((flags & 0x20000) && menu->width < widest + 6 && !(flags & 8)) {
        menu->flags = flags | 8;
        return 1;
    }
    if (menu->width < widest)
        widest = menu->width;

    for (i = 0; menu->entries[i].text != 0; i++) {
        int selected = 0;
        ListEntry *entry;
        int active;
        int color;
        char *text;
        int x;
        int below;
        int binding;

        if (focused)
            selected = menu->selected == i;
        entry = &menu->entries[i];
        active = entry->action != 0;
        if (menu->flags & 2) {
            color = (int)0x80FFA888;
        } else if (selected) {
            if (active)
                color = func_002D68D8((short)entry->fadeTimer, -1, -1);
            else
                color = (int)0x80006060;
        } else if (active) {
            color = func_002D68D8((short)entry->fadeTimer, -1, -1);
        } else {
            color = (int)0x80303030;
        }
        text = func_00288FB8(menu->entries[i].text);
        below = y + spacing;
        if ((D_001F2840.current == (MenuPage *)D_00258EE8 || D_001F2840.current == (MenuPage *)D_00259018)
            && ((char *)menu == D_00259148 || (char *)menu == D_00259198 || (char *)menu == D_002591E8
                || (char *)menu == D_00259238 || (char *)menu == D_00259288 || (char *)menu == D_002592D8)) {
            int k;

            binding = -1;
            for (k = 0; k < 14; k += 2) {
                if (D_00258D70[k] == menu->entries[i].text) {
                    binding = k + 1;
                    break;
                }
            }
            if (binding >= 0) {
                char *label;

                func_00282A60(D_00210C40, 0, 0x100);
                label = func_00288FB8(menu->entries[i].text);
                func_00115DA8(D_00210C40, D_001ABAC8, func_00288FB8(D_00258D70[binding]), label);
                text = D_00210C40;
            }
        }
        if (menu->entries[i].action == 2)
            text = func_00288FB8(0x2DC0);
        x = centre - (func_0027F128(text, -1, font) >> 1);
        if (menu->flags & 0x40)
            x = 4;
        else if (menu->flags & 0x4000)
            x = centre - (widest >> 1);
        func_0027F120();
        func_0027F2A8(x + D_001AA444, y + D_001AA448, 0x80000000u, text, -1, func_0027C878(size), font);
        func_0027F110();
        if (menu->flags & 0x80)
            func_0027F120();
        func_0027F2A8(x, y, color, text, -1, func_0027C878(size), font);
        y = below;
        if (menu->entries[i].text2 != 0) {
            func_0027F120();
            text = func_00288FB8(menu->entries[i].text2);
            func_0027F2A8(x + D_001AA444, y + D_001AA448, 0x80000000u, text, -1, func_0027C878(size), font);
            if (!(menu->flags & 0x80))
                func_0027F110();
            text = func_00288FB8(menu->entries[i].text2);
            y = below + spacing;
            func_0027F2A8(x, below, color, text, -1, func_0027C878(size), font);
        }
        if (menu->flags & 0x80)
            func_0027F110();
    }
    func_0027C660();
    return 2;
}
