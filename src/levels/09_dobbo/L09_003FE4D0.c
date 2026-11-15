#include "common.h"

extern int func_00283DB8(void *, float);
extern int D_L09_00257110[];
extern float func_00283CE0(int);
extern void func_L09_003FD460(void *);
extern void func_L09_003FD128(void *);
extern void *func_L09_003FE3B0(int index, int *table);
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4_L09;

/* Unit of its own for -fno-gcse: with gcse, PRE keeps the table's high half in a saved
   register across the clear loop (324 bytes).

   Resets the 20-entry screen table to -1, then for each of the sub-object's 0x424 entries
   takes the next candidate from func_L09_003FE3B0, records its 0xB2 id in the table and,
   when its sphere passes the test, runs its draws: func_L09_003FD460 for flag 8 of its
   sub-object's 0x42C word, func_L09_003FD128 for flag 2. */
void func_L09_003FE4D0(unsigned char *a0)
{
    unsigned char *s5 = a0;
    unsigned char *s4 = *(unsigned char **)(s5 + 0x68);
    int fill = -1;
    int i;
    Vec4_L09 buf;

    for (i = 19; i >= 0; i--) {
        D_L09_00257110[i] = fill;
    }
    i = 0;
    if (*(short *)(s4 + 0x424) > 0) {
        int *tbl = D_L09_00257110;
        int none = -1;
        int *p = tbl;
        do {
            char *s0 = (char *)func_L09_003FE3B0(s5[0x21], tbl);
            unsigned char *s1;
            *p = *(short *)(s0 + 0xB2);
            p++;
            qcopy(&buf, s0 + 0x10);
            buf.f[3] = 4.0f;
            if (func_00283DB8(&buf, IntToFloat(*(short *)(s0 + 0x32))) != none) {
                s1 = *(unsigned char **)(s0 + 0x68);
                if (*(int *)(s1 + 0x42C) & 8)
                    func_L09_003FD460(s0);
                if (*(int *)(s1 + 0x42C) & 2)
                    func_L09_003FD128(s0);
            }
            i++;
        } while (i < *(short *)(s4 + 0x424));
    }
}
