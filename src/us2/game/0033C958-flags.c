#include "include_asm.h"
#include "names.h"
extern void Fe524d931_FUN_0033AE28(char *p);
extern void Fe524d931_FUN_0033B018(char *p, float x, float y);
extern int Fe524d931_FUN_002E5E58(int a, int b, int c);
extern void UpdateViewContext(void);
extern unsigned char D_001A7BB1;

int func_US2_0033D320(char *object, int mask)
{
    float *v;

    Fe524d931_FUN_0033AE28(object + 8);
    v = *(float **)(object + 0x2DC);
    Fe524d931_FUN_0033B018(object + 8, v[0], v[1]);
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0) {
        D_001A7BB1 = D_001A7BB1 == 0;
        Fe524d931_FUN_002E5E58(4, 0, 0);
        UpdateViewContext();
    }
    return (mask >> 6) & 1;
}
