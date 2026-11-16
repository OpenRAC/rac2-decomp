#include "names.h"
/* func_US2_0033F398, the USA v2.00 copy of func_0033E348: the same C, where rename func_00348128 becomes func_US2_00348E60. */

extern int list_menu_get_selected_index_us2(int);

extern int func_US2_00348E60(unsigned char *);

/* Qwen draft (branch qwen/autonomy, 4419d477), checked by tools/check.py */
/* Returns the selected index of the list widget in the page. (USA v2.00) */
int list_menu_get_selected_index_us2(int owner)
{
    return func_US2_00348E60((unsigned char *)(owner + 0x2e0));
}

extern void prompt_bar_update(char *);
extern void menu_set_anchor_pos(char *, float, float);
extern void prompt_bar_update(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
