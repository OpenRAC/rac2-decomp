#include "common.h"

/* func_L20_0039D680 lives in a -G8 unit of its own: it reads D_L20_001B2FB8 through $gp,
   while func_L20_0039E890 in L20_0039C448-g8.c reads the same word absolutely. */

extern float func_00282E80(void *, void *);
extern char D_00189EA0[];
extern char *D_L20_001FBB20[];
extern char *D_L20_001B2F9C;
/* 0x1AEFF0 + 0x3FC8: read through $gp. */
extern int D_L20_001B2FB8 __attribute__((sda));

/* Counts the other objects of this object's group (the 0x7FFF-masked id list at
   D_L20_001FBB20[object[0x21]]) that are closer to D_00189EA0 than the object itself,
   skipping state 6; sets state+0x27C when fewer than two are.  The loop condition is
   the group-iteration form of func_00325DA0: its size keeps jump from duplicating the
   exit test, so the test stays at the bottom, entered by a branch, as in retail. */
void func_L20_0039D680(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    float limit = func_00282E80(object + 0x10, D_00189EA0);
    unsigned short *p;
    unsigned char *e;
    int count = 0;

    for (p = (unsigned short *)D_L20_001FBB20[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= D_L20_001B2FB8 && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)D_L20_001FBB20[object[0x21]]);
         p++) {
        e = (unsigned char *)D_L20_001B2F9C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e != object && e[0x20] != 6 && func_00282E80(e + 0x10, D_00189EA0) < limit)
            count++;
    }
    *(int *)(state + 0x27C) = count < 2;
}
