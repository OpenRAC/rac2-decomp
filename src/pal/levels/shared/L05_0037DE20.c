#include "include_asm.h"

#include "common.h"
extern int moby_get_motion_data(char *);
extern void follower_set_state(char *, int);
extern int math_random_int_range(int, int);
extern int func_001163B0(void);
extern int D_L05_00221D10[];
extern int D_L05_00221D10[];

/* looks up an object, then sets flags, arms a stored value and calls one of two helper pairs before building a timer */
void func_PAL_L05_0037DE20(char *obj)
{
    char *s;

    s = (char *)moby_get_motion_data(obj);
    if (s == 0)
        return;
    if (*(int *)(s + 288) == 0)
        return;
    if (*(int *)(s + 284) != 0) {
        int *p = D_L05_00221D10;
        int one = 1;

        *(int *)(s + 280) = one;
        p[3] += one;
        if (moby_get_state_value(obj) != 5) {
            follower_set_state(obj, 4);
            *(float *)(s + 120) = (func_001163B0() & 1) ? -1.0f : 1.0f;
            if (func_001163B0() & 1)
                *(float *)(s + 116) = -1.0f;
            else
                *(float *)(s + 116) = 1.0f;
            *(int *)(s + 252) = one;
            *(int *)(s + 112) = 0;
            *(int *)(s + 124) = 0;
        } else {
            follower_set_state(obj, 7);
        }
        *(int *)(s + 304) = ((s32)(math_random_int_range(120, 500)) * 5 + 2) / 6;
    } else {
        int *p = D_L05_00221D10;

        *(int *)(s + 280) = 1;
        p[3] += 1;
        if (moby_get_state_value(obj) != 5)
            follower_set_state(obj, 4);
        else
            follower_set_state(obj, 7);
        *(int *)(s + 304) = ((s32)(math_random_int_range(120, 500)) * 5 + 2) / 6;
        *(int *)(s + 252) = 0;
    }
}

