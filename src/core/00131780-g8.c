#include "common.h"

extern int r1_D_0015EDC4 __attribute__((sda));
extern void func_00132028(void);

void func_00133230(void) {
    r1_D_0015EDC4 = 0;
    func_00132028();
}

extern int D_001A74F8 __attribute__((sda));
extern char D_001A7578[];
extern void func_00115D48(const void *, ...);
extern void func_0011AEA0(int);
extern int func_0011D810(const void *);
extern int func_0011D620(const void *, int, int, int *, int, int *, int, int, int);
extern int *D_001A74A0[2] __attribute__((sda));
extern int D_001A74A8[2] __attribute__((sda));
extern int *D_001A74B8[2] __attribute__((sda));
extern int D_001A74C0 __attribute__((sda));
extern int D_001A7040;
extern void func_001322B8(void *, int, void *);
void func_00133108(void) {
    func_001322B8(D_001A74B8[D_001A74C0], *D_001A74A0[D_001A74C0], D_001A74A0[D_001A74C0]);
    while (func_0011D810(&D_001A7040)) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7578);
        func_0011AEA0(0);
    }
    func_0011D620(&D_001A7040, 0x4D, 1, D_001A74A0[D_001A74C0], 0x1000-D_001A74A8[D_001A74C0], D_001A74B8[D_001A74C0], (*D_001A74A0[D_001A74C0] << 2)+8, 0, 0);
    {
        int next = (D_001A74C0 ^ 1) != 0;
        D_001A74C0 = next;
        *D_001A74A0[next] = 0;
        D_001A74A8[next] = 0xFFC;
    }
}

extern int D_001A74C8 __attribute__((sda));
extern int D_001A7488 __attribute__((sda));
extern int D_001A74D0 __attribute__((sda));
extern int D_001A71C0 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
extern volatile long D_001A74D8 MACRO_ADDR;
extern int D_001A7140 MACRO_ADDR;
extern char D_001A76F8[];
void func_001325E0(int a, int c, long d) {
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0) return;
        func_00115D48(D_001A76F8);
        return;
    }
    do {
        D_001A71C0 = a;
        D_001A74D0 = c;
        D_001A7180 = -1u;
        D_001A74D8 = d;
    } while (0);
    while (func_0011D810(&D_001A7140)) {
        if (D_001A74F8 == 0) func_00115D48(D_001A7578);
        func_00132028();
        func_0011AEA0(0);
    }
    D_001A74C8 = 1;
    func_0011D620(&D_001A7140, 0x57, 1, &D_001A71C0, 4, (int *)&D_001A7180, 4, 0, 0);
}
