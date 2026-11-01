#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002B1A50);


typedef unsigned char u8;
extern u8 D_00139648;
extern int F9a90bcc4_FUN_002A77E0(int count);
extern u8 D_001A7A47 __attribute__((sda));
extern u8 D_00139568[];
extern u8 D_00239BA0[];
extern u8 D_001A7A60[] __attribute__((sda));

/* func_002B1350 is defined in 002B00B0-reaction-g8.c. */

int func_PAL_002B2618(u8 *owner, int b, int *outIndex,
                                       float *o0, float *o1, float *o2, float *o3,
                                       float *o4, float *o5, float *o6)
{
    int n;
    int count;
    int i;
    int k;
    int left;
    u8 *p;

    n = 0;
    count = *(u8 *)(*(int *)(owner + 36) + 12);
    if (count != 0) {
        int *t = (int *)(*(int *)(owner + 36) + 72);
        u8 *q;
        left = count;
        do {
            q = *(u8 **)(*t + 20);
            if (q != 0 && *q == b)
                n++;
            t++;
            left--;
        } while (left != 0);
    }

    if (n != 0)
        goto second;

    return 0;

found:
    *o0 = *(float *)(p + 8) * 0.020000001f;
    *o1 = *(float *)(p + 12) * 0.020000001f;
    *o2 = *(float *)(p + 16) * 0.00040000002f;
    *o3 = *(float *)(p + 20) * 0.00040000002f;
    *o6 = *(float *)(p + 4) * 0.00040000002f;
    *o4 = *(float *)(p + 24);
    *o5 = *(float *)(p + 28);
    *outIndex = i;
    return 1;

second:
    k = F9a90bcc4_FUN_002A77E0(n);
    for (i = 0; i < *(u8 *)(*(int *)(owner + 36) + 12); i++) {
        char *tbl = (char *)(*(int *)(owner + 36) + 72);
        char *e = *(char **)(tbl + i * 4);
        p = *(u8 **)(e + 20);
        if (p == 0 || *p != b)
            continue;
        if (k == 0)
            goto found;
        k--;
    }
    return 0;
}


