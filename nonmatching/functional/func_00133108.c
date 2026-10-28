/* functional: high. snd_SendCurrentBatch: same reads, writes and calls in the same order; only the register allocation and the $gp-relative addressing differ (globals are addressed absolutely here). */
extern int D_001A74C0;
extern int *D_001A74A0[2];
extern int D_001A74A8[2];
extern int D_001A74B8[2];
extern int D_001A74F8;
extern int func_001322B8(int, int, int *);
extern int func_0011D810(void *);
extern int func_0011D620(void *, int, int, void *, int, void *, int, int, int);
extern void func_0011AEA0(int);
extern void func_00115D48(int, ...);
extern char D_001A7040[];

void func_00133108(void) {
    int idx = D_001A74C0;
    int nxt;

    func_001322B8(D_001A74B8[idx], *D_001A74A0[idx], D_001A74A0[idx]);
    while (func_0011D810(D_001A7040) != 0) {
        if (D_001A74F8 == 0)
            func_00115D48(0x1A7578);
        func_0011AEA0(0);
    }
    idx = D_001A74C0;
    func_0011D620(D_001A7040, 0x4D, 1, D_001A74A0[idx], 0x1000 - D_001A74A8[idx],
                  (void *)D_001A74B8[idx], (*D_001A74A0[idx] << 2) + 8, 0, 0);
    nxt = (D_001A74C0 != 1);
    D_001A74C0 = nxt;
    *D_001A74A0[nxt] = 0;
    D_001A74A8[nxt] = 0xFFC;
}
