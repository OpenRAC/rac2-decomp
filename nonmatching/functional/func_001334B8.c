/* functional: high. Same reads, writes and calls as retail (CdStartRead); only instruction scheduling differs from retail. */
extern int D_001A748C __attribute__((sda));
extern int D_001A7494 __attribute__((sda));
extern int D_001A7498 __attribute__((sda));
extern void func_0011B3D0(void *, void *);
extern int func_001253A8(void);
extern int func_00133580(int);
extern void func_00132DF0(int, int, void *, int, int);

int func_001334B8(int arg0, int arg1, int arg2) {
    int payload[4];

    if (D_001A748C == 0) {
        return func_001253A8();
    }
    if (func_00133580(1) == 1) {
        return 0;
    }
    *(int *)0x1A7100 = 1;
    *(int *)0x1A7110 = 0;
    func_0011B3D0((void *)0x1A7100, (void *)0x1A713F);
    payload[0] = arg0;
    payload[1] = arg1;
    payload[2] = arg2;
    D_001A7494 = 1;
    D_001A7498 = 0;
    func_00132DF0(0x38, 0xC, payload, 0, 0);
    return 1;
}
