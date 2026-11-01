#include "include_asm.h"

extern char *D_L02_001B359C __attribute__((sda));
extern char *D_L02_001FC060[];
extern int D_L02_001B35B8 __attribute__((sda));
typedef int L02Word;
extern L02Word D_L02_001B35B8 __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));

/* Sets every entity of the object's group to state 1 with a 0xB4 timer. */
void func_PAL_L02_003D1828(unsigned char *arg0) {
    unsigned short *q;
    char *e;

    if (arg0[0x21] == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        char *o;

        e = D_L02_001B359C + ((*q & 0x7FFF) << 8);
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        *(unsigned short *)(o + 0x382) = 1;
        *(unsigned short *)(o + 0x386) = 0x96;
        q++;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L02_003D18D8);


#include "common.h"
extern void func_L02_00333438(char *, char *);
extern int func_L01_00321178(char *, char *);
extern int func_002B4FF0(char *, float *, float);
extern int D_L02_001A8FF0 __attribute__((sda));

/* Runs the kind's entry hook: the first when the level flag is set, the second when the third
   argument is clear, the third with the object's own angle otherwise. */
void func_PAL_L02_003D2898(char *a0, char *a1, int a2) {
    char *p = *(char **)(a0 + 0x68);

    if (D_L02_001A8FF0)
        func_L02_00333438(a0, a1);
    else if (a2 == 0)
        func_L01_00321178(a0, a1);
    else
        func_002B4FF0(a0, (float *)a1, *(float *)(p + 0x31C));
}

