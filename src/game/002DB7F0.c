#include "names.h"
/* Adapted from RAC1 src/game/pause.c, draw_menu_choice_list. */
extern void VU1_addGSregister(int, long);
extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern void text_draw_small(int,int,long,signed char *,int);
typedef struct { int text; unsigned char *value; int names[4]; } OptionB7;
typedef struct { char pad[0x20]; int width, height; char pad28[12]; OptionB7 *items; int selected; } MenuB7;
extern char *GetLocalizedString(int);
extern void text_draw_right_aligned_small(int,int,unsigned long,char *,int);
/* Draws a list of options with the current choice of each shown on the right. */
int DrawMenuChoiceList(MenuB7 *m) {
    OptionB7 *p, *it;
    int n, i, step, y, color;
    VU1_addGSregister(0x47,0x2004B);
    SetupGifPaging(0);
    n = 0;
    for (p = m->items; p->text; p++)
        n++;
    step = m->height / (n + 1);
    p = m->items;
    y = step - 8;
    for (i = 0; m->items[i].text; i++) {
        it = &m->items[i];
        if (i == m->selected)
            color = 0x8020FFFF;
        else
            color = 0x80FFA888;
        text_draw_small(12,y,color,(signed char *)GetLocalizedString(it->text),-1);
        text_draw_right_aligned_small(m->width-12,y,0x80FFA888,GetLocalizedString(it->names[*it->value]),-1);
        y += step;
    }
    DoGifPaging();
    return 2;
}
