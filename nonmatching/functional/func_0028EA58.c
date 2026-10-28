/* functional: high. Appends a 0x70-byte GIF packet (tag header, one A+D quad, then eight 64-bit GS words) at the cursor D_001B22A8 and advances it by 0x70. Sibling of func_0028E868 with six arguments; fifth/sixth are a delta and a pointer to four words. func_0028E640 gets a0 as in retail. */
extern int D_001B22A8;
extern int D_001B1890;
extern int D_001B1894;
extern int D_001B187C;
extern int D_001A7350;
extern int D_001A7354;
extern long long D_001AC830[2];
extern long long func_0028E640(int a0);

void func_0028EA58(int a0, int a1, int a2, int a3, int a4, int *a5)
{
    short *row = (short *)((a0 << 2) + D_001B1890);
    unsigned char *entry = (unsigned char *)(D_001B1894 + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int c0, s2;
    long long Z;
    int xs, ys, xe, ye;

    c0 = D_001B22A8;
    *(int *)(c0 + 0x0) = 0x10000008;
    *(int *)(c0 + 0x4) = 0;
    *(int *)(c0 + 0x8) = 0;
    *(int *)(c0 + 0xC) = 0x50000008;
    D_001B22A8 = c0 + 0x10;
    ((long long *)(c0 + 0x10))[0] = D_001AC830[0];
    ((long long *)(c0 + 0x10))[1] = D_001AC830[1];
    s2 = c0 + 0x20;
    D_001B22A8 = s2;
    *(long long *)(c0 + 0x20) = func_0028E640(a0);

    xs = a2 << 4;
    ys = a1 << 4;
    xe = (a1 + a3) << 4;
    ye = (a2 + a4) << 4;
    *(long long *)(s2 + 0x08) = 0x15C;
    *(long long *)(s2 + 0x10) = a5[0];
    *(long long *)(s2 + 0x18) = 0;
    Z = (long long)D_001B187C << 32;
    *(long long *)(s2 + 0x20) = (long long)(ys + D_001A7350 - 8) | ((long long)(xs + D_001A7354 - 8) << 16) | Z;
    *(long long *)(s2 + 0x28) = a5[1];
    *(long long *)(s2 + 0x30) = mask6 << 4;
    *(long long *)(s2 + 0x38) = (long long)(xe + D_001A7350 - 8) | ((long long)(xs + D_001A7354 - 8) << 16) | (long long)D_001B187C << 32;
    *(long long *)(s2 + 0x40) = a5[2];
    *(long long *)(s2 + 0x48) = mask7 << 20;
    *(long long *)(s2 + 0x50) = (long long)(ys + D_001A7350 - 8) | ((long long)(ye + D_001A7354 - 8) << 16) | (long long)D_001B187C << 32;
    *(long long *)(s2 + 0x58) = a5[3];
    *(long long *)(s2 + 0x60) = (long long)((mask7 << 20) + (mask6 << 4));
    *(long long *)(s2 + 0x68) = (long long)(xe + D_001A7350 - 8) | ((long long)(ye + D_001A7354 - 8) << 16) | (long long)D_001B187C << 32;
    D_001B22A8 = D_001B22A8 + 0x70;
}
