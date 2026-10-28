/* functional: high. Clears the 0x16C0-byte record table at 0x188660 (header qwords, two words at +0x40/+0x44, then the first word and flag byte of each 0x70-byte record), then configures the same engine-side slots in the same call order; retail clears with sq, codegen only. */
typedef unsigned char u8;
extern u8 D_00188660[];
extern int D_001A7B98 __attribute__((sda));
extern void func_00131DE8(int);
extern void func_00132938(int);
extern void func_00132968(int, int);
extern void func_001329B0(int, int, int);
extern void func_00132888(int, int);
extern void func_002E4860(void);
extern void func_001328C0(int, int *);
void func_002E48E8(void) {
    int cfg[5];
    u8 *p;
    int i;
    for (i = 3; i >= 0; i--) {
        ((long long *)D_00188660)[i * 2] = 0;
        ((long long *)D_00188660)[i * 2 + 1] = 0;
    }
    *(int *)(D_00188660 + 0x40) = 0;
    *(int *)(D_00188660 + 0x44) = 0;
    p = D_00188660;
    do {
        *(int *)(p + 0x70) = 0;
        p[0x74] = 0;
        p += 0x70;
    } while (p < D_00188660 + 0x16C0);
    func_00131DE8(2);
    func_00132938(D_001A7B98 == 0);
    func_00132968(0, 1);
    func_001329B0(1, 0x18, 0x2F);
    func_001329B0(2, 0x18, 0x2F);
    func_001329B0(4, 0x18, 0x2F);
    func_001329B0(5, 0x18, 0x2F);
    func_001329B0(6, 0x18, 0x2F);
    func_002E4860();
    func_00132888(0, *(int *)(D_00188660 + 0x48));
    func_00132888(1, *(int *)(D_00188660 + 0x4C));
    func_00132888(2, *(int *)(D_00188660 + 0x50));
    func_00132888(3, *(int *)(D_00188660 + 0x54));
    func_00132888(4, *(int *)(D_00188660 + 0x58));
    func_00132888(5, *(int *)(D_00188660 + 0x5C));
    func_00132888(6, *(int *)(D_00188660 + 0x50));
    cfg[0] = 6; cfg[1] = 0x3B; cfg[2] = 0x6666; cfg[3] = 0x8000; cfg[4] = 0x8000;
    func_001328C0(0, cfg);
}
