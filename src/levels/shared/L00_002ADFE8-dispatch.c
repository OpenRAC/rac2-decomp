#include "include_asm.h"
#include "names.h"
extern void *D_L00_0029FF70[76];
extern float g_item_aim_angle;
/* Uses the level's existing kind table to choose a vertical adjustment. */
/* Says whether an item kind needs an aim tweak, and gives the up or down angle for it. */
int hero_get_item_aim_adjustment(int kind, float *out)
{
    /* These legitimate arm addresses keep labels in discarded object data. */
    static void *arms[] = {&&constant, &&yes, &&threshold, &&no};
    *out = 0.0f;
    if ((unsigned int)(kind - 28) >= 76) goto no;
    goto *D_L00_0029FF70[kind - 28];
constant:
    *out = -0.9599311947822571f;
    return 1;
yes:
    return 1;
threshold:
    if (g_item_aim_angle > 25.0f) *out = -1.3089970350265503f;
    goto yes;
no:
    return 0;
}
