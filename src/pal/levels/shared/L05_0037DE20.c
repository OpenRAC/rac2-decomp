#include "include_asm.h"

#include "common.h"
extern int func_002ED688(char *);
extern void func_002EE678(char *, int);
extern int func_002A7820(int, int);
extern int func_001163B0(void);
extern int D_L05_00221D10[];
extern int D_L05_00221D10[];

/* looks up an object, then sets flags, arms a stored value and calls one of two helper pairs before building a timer */
void func_PAL_L05_0037DE20(char *obj)
{
    char *s;

    s = (char *)func_002ED688(obj);
    if (s == 0)
        return;
    if (*(int *)(s + 288) == 0)
        return;
    if (*(int *)(s + 284) != 0) {
        int *p = D_L05_00221D10;
        int one = 1;

        *(int *)(s + 280) = one;
        p[3] += one;
        if (func_L05_0037CEB8(obj) != 5) {
            func_002EE678(obj, 4);
            *(float *)(s + 120) = (func_001163B0() & 1) ? -1.0f : 1.0f;
            if (func_001163B0() & 1)
                *(float *)(s + 116) = -1.0f;
            else
                *(float *)(s + 116) = 1.0f;
            *(int *)(s + 252) = one;
            *(int *)(s + 112) = 0;
            *(int *)(s + 124) = 0;
        } else {
            func_002EE678(obj, 7);
        }
        *(int *)(s + 304) = ((s32)(func_002A7820(120, 500)) * 5 + 2) / 6;
    } else {
        int *p = D_L05_00221D10;

        *(int *)(s + 280) = 1;
        p[3] += 1;
        if (func_L05_0037CEB8(obj) != 5)
            func_002EE678(obj, 4);
        else
            func_002EE678(obj, 7);
        *(int *)(s + 304) = ((s32)(func_002A7820(120, 500)) * 5 + 2) / 6;
        *(int *)(s + 252) = 0;
    }
}

