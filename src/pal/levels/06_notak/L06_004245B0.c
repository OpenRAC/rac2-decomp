#include "include_asm.h"





#include "common.h"
extern void func_002A8598(int, int);
extern int func_00282948(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void *D_L06_002E1F00[];

/* func_L06_00420080 is defined in L06_00420080.c. */


/* func_L06_00420548 is defined in L06_00420548-g.c. */

/* func_L06_00420740 is defined in L06_00420740.c. */

/* func_L06_00420AE8 is defined in L06_00420AE8-g8.c. */

/* The object runs through five states. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1F00); `cases` only keeps the labels alive. */
void func_PAL_L06_0042FC88(char *a0)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&c3, &&c4};
    char *s0 = a0;
    char *s1;
    unsigned int sel;

    sel = *(unsigned char *)(s0 + 0x20);
    s1 = *(char **)(s0 + 0x68);
    if (sel < 5)
        goto *D_L06_002E1F00[sel];
    goto done;
c0:
    *(unsigned char *)(s0 + 0x20) = 1;
    *(int *)s1 = 0x4E2;
    goto done;
c1:
    if (*(unsigned char *)(s0 + 0xBC) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 2;
    if (*(unsigned char *)(s0 + 0x43) != 1)
        func_PAL_002A7E68(s0, 1, 0, 0);
    *(int *)(s0 + 0x98) = 0;
    goto done;
c2:
    if ((*(unsigned char *)(s0 + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 3;
    if (*(unsigned char *)(s0 + 0x43) == 2)
        goto done;
    func_PAL_002A7E68(s0, 2, 0, 0);
    goto done;
c3:
    if (func_00282948(s1) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 4;
    if (*(unsigned char *)(s0 + 0x43) == 3)
        goto done;
    func_PAL_002A7E68(s0, 3, 0, 0);
    goto done;
c4:
    if ((*(unsigned char *)(s0 + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 1;
    if (*(unsigned char *)(s0 + 0x43) == 0)
        goto tail;
    func_PAL_002A7E68(s0, 0, 0, 0);
tail:
    *(int *)(s0 + 0x98) = *(int *)(*(int *)(s0 + 0x24) + 0x10);
    *(int *)s1 = 0x4E2;
    func_002A8598(*(unsigned char *)(s0 + 0x21), 0);
    goto done;
done:
    return;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L06_004347BC);

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_004351A8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_00447DC8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_004485C0);

extern void func_36C158();
extern void func_36C1B0(float);

void func_PAL_L06_00448968(char *a0, int a1, int a2)
{
    char *p = *(char **)(a0 + 0x68);

    if (a2 == 0) {
        func_36C158();
    } else {
        func_36C1B0(*(float *)(p + 0x31C));
    }
}

