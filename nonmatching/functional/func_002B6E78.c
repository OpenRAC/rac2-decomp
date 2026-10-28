/* functional: high. Same table reads, state stores, and 12-argument call (sign-extended sectors, user data = state+0x44 as 64-bit) as retail; register allocation and instruction order differ. */
typedef unsigned char u8;
extern u8 D_001A63A8[];
extern int D_0014B540[];
extern void func_00133340(long, long, int, int, int, int, int, int, int, int, int, long);
extern void func_002B7FB0(int, long);

void func_002B6E78(int index, int a, int b) {
    char *st = (char *)D_001A63A8;
    int *t = D_0014B540;

    if (index >= 0 && *(int *)(st + 0x44) == 0) {
        int lbn = t[0x14C0 + index * 2];
        if (lbn != 0) {
            int base = t[0x14BF];
            *(short *)(st + 0x4E) = 1;
            *(int *)(st + 0x58) = 10;
            *(int *)(st + 0x5C) = 0xBB80;
            *(short *)(st + 0x48) = index;
            *(int *)(st + 0x44) = -1;
            *(short *)(st + 0x4C) = a;
            *(short *)(st + 0x4A) = b;
            *(short *)(st + 0x54) = 0;
            func_00133340(lbn + base, t[0x14C0 + (index + 1) * 2] + base, 0, 0, (short)b, 0, 1, 0,
                          0, 0, (int)func_002B7FB0, (unsigned long)(unsigned int)(st + 0x44));
        }
    }
}
