/* func_PAL_L02_00401EC8, the PAL copy of func_L02_003FD770: the same C, where the wait is scaled to 50 Hz. */

#include "common.h"

extern char D_L02_001B11D0[8] __attribute__((sda));
extern char D_L02_001B11E0[8] __attribute__((sda));
extern char D_L02_001B11F0[8] __attribute__((sda));
extern char D_L02_001B1200[8] __attribute__((sda));
extern int D_L02_001B1210 __attribute__((sda));

extern void func_00282C88(void *);
extern void func_00335438(char *, char *, int, int, int);
extern void func_L01_0042A6F0(int, int);
extern void func_00335370(char *);
extern void func_003353C8(char *);

void func_PAL_L02_00401EC8(char *a0) {
    char buf[16];
    func_00282C88(buf);
    func_00335438(D_L02_001B11F0, D_L02_001B1200, 1, 0, 0);
    func_L01_0042A6F0(2, ((s32)(D_L02_001B1210) * 5 + 2) / 6);
    func_00335370(D_L02_001B11D0);
    func_003353C8(D_L02_001B11E0);
}
