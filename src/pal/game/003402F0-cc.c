#include "names.h"
/* func_PAL_003402F0, the PAL copy of func_0033E348: the same C, where rename func_00348128 becomes func_PAL_0034A2F0. */

extern int func_PAL_003402F0(int);

extern int menu_get_selected_index_pal(unsigned char *);

/* Qwen draft (branch qwen/autonomy, 4419d477), checked by tools/check.py */
int func_PAL_003402F0(int owner)
{
    return menu_get_selected_index_pal((unsigned char *)(owner + 0x2e0));
}

extern void prompt_bar_update(char *);
extern void menu_set_anchor_pos(char *, float, float);
extern void prompt_bar_update(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
