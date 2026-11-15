/* snd_SendCommandSync; adapted from rac1-decomp src/core/989snd.c
 * snd_SendIOPCommandAndWait (GPL-3.0). RPC buffers use absolute macro
 * addresses; the default split profile keeps the diagnostic base in s1. */
#include "common.h"
extern unsigned char D_001A70C0[] MACRO_ADDR;
extern int D_001A7080[] MACRO_ADDR;
extern char D_001A7040[] MACRO_ADDR;
extern char D_001A7578[];
extern int D_001A7480 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74C0 __attribute__((sda));
extern int D_001A74C4 __attribute__((sda));
extern int *D_001A74A0[2] __attribute__((sda));
extern int func_00132028(void);
extern void func_0011AEA0(int);
extern void func_001322B8(void *, int);
extern int func_0011D810(void *);
extern void func_00115D48(char *, ...);
extern int func_0011D620(void *, int, int, void *, int, void *, int, int, int);
extern int func_00132220(void);
extern void func_00133108(void);
int func_00132C48(int cmd, int size, void *arg) {
    unsigned char *data = arg;
    int i;
    int result;
    for (i = 0; i < size; i++) D_001A70C0[i] = data[i];
    goto check;
    do {
        snd_Pump();
        func_0011AEA0(0);
check:;
    } while (D_001A7480 != 0);
    func_001322B8(D_001A7080, 1);
    while (func_0011D810(D_001A7040) != 0) {
        if (D_001A74F8 == 0) func_00115D48(D_001A7578);
        snd_Pump();
        func_0011AEA0(0);
    }
    if (size != 0)
        func_0011D620(D_001A7040, cmd, 1, D_001A70C0, size, D_001A7080, 12, 0, 0);
    else
        func_0011D620(D_001A7040, cmd, 1, 0, 0, D_001A7080, 12, 0, 0);
    while (func_00132220() == 0) {}
    result = D_001A7080[1];
    if (*D_001A74A0[D_001A74C0] != 0 && D_001A74C4 == 0) func_00133108();
    return result;
}
