#include "include_asm.h"
#include "names.h"

extern void Fe524d931_FUN_0033AE28(char *p);
extern void Fe524d931_FUN_0033B018(char *p, float x, float y);
extern void Fe524d931_FUN_002E5E58(int a, int b, int c);
extern void func_0027AB40(void);
extern unsigned char D_001A7BB1;

/* Updates the on/off option menu: when confirm is pressed it flips the setting and plays a sound. */
int func_0033C2D8(char *object, int mask)
{
    float *anchor;

    Fe524d931_FUN_0033AE28(object + 8);
    anchor = *(float **)(object + 0x2AC);
    Fe524d931_FUN_0033B018(object + 8, anchor[0], anchor[1]);
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2A8) == 0) {
        D_001A7BB1 = D_001A7BB1 == 0;
        Fe524d931_FUN_002E5E58(4, 0, 0);
        UpdateViewContext();
    }
    return (mask >> 6) & 1;
}
