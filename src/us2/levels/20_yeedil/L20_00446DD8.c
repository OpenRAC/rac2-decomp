#include "include_asm.h"


#include "common.h"
extern void func_002A7750(int, int, int);
extern int func_002B3868(char *);
extern int func_002B38B8(char *);
extern void func_002AA548(char *, char *, float, float, float, float);
extern unsigned char D_0019B2E8[];
extern void *jtbl_002B5980[];
extern int func_002B3868(char *);
extern int func_002B38B8(char *);
extern void func_002AA548(char *, char *, float, float, float, float);
extern unsigned char D_0019B2E8[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
void func_US2_L20_004483B8(char *arg0) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(arg0 + 0x20);
    state = *(char **)(arg0 + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5980[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(arg0 + 0x10);
    func_002A7750(arg0, 1, -1);
    goto out;
c1:
    if ((D_0019B2E8[((unsigned char *)arg0)[0xB0] + *(int *)0x1A79F8 * 16] & 0x80) == 0) {
        goto end;
    }
    func_002A7750(arg0, 2, -1);
    goto out;
c2:
    if (func_002B3868(arg0) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    func_002AA548(arg0 + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (func_002B38B8(arg0) == 0) {
        goto end;
    }
    func_002A7750(arg0, 4, -1);
    goto out;
c4:
    if (func_002B3868(arg0) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    func_002AA548(arg0 + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

