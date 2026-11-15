#include "include_asm.h"
#include "names.h"

extern float D_L04_001AE440 __attribute__((sda));

extern float D_L04_001AE444;

extern float D_L04_001AE448 __attribute__((sda));

extern void func_00335E38_5(void *, float, float, float, float);

extern void func_00336920(void *, int, int);

extern void func_00336828_1(void *);

/* Draws the rows of a menu list one under the other, giving the fourth row a different label. */
void func_00342668(int *menu)
{
    int row;

    for (row = 0; row < menu[95]; row++) {
        float *origin = (float *)menu[96];
        int labelId;

        func_00335E38_5(menu + 76, origin[0] + D_L04_001AE440,
                (origin[1] + D_L04_001AE444) + D_L04_001AE448 * (float)row, 0.0f, 0.0f);
        if (row == 3)
            labelId = 0xEA9E;
        else
            labelId = 0xEAA6;
        menu[93] = labelId;
        SetWidgetValuePair(menu + 76, labelId, ((int *)menu[94])[row]);
        func_00336828_1(menu + 76);
    }
}

extern void func_00336320(int *);
extern void func_003425B8(int *);
extern void func_00342648(int);

/* Draws the menu, but only when it is switched on. */
void func_00342758(int *menu)
{
    if (menu[92] != 0) {
        DrawScreenElementAtStoredPosition(menu);
        DrawScreenElementAtStoredPosition(menu + 19);
        DrawListMenuCursor(menu);
        DrawListMenuScroller((int)menu);
        DrawMenuListRows(menu);
    }
}
