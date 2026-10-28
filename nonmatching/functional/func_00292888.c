/* functional: high. Hand-decoded from the assembly (match not attempted to the end): same reads, writes and calls in the same order with the same arguments; pointers are 32-bit game addresses held as int. */
extern int D_001A7288;
extern int D_001B18B0[5];
extern int D_001B1888;
extern int D_001B188C;
extern int D_001B1890;
extern int D_001B1894;
extern int D_001B1898;
extern int D_001BAEC0[];
extern int D_001A91F0[];
extern int D_001A9200[];
extern int D_001A9210[];
extern int D_001A9220[];
extern int D_001A9230[];
extern int func_0028B2B8(int, int, void *, int);
extern void func_00282B50(int, int, int);
extern void func_00292B20(int, int);
extern int func_002EED58(int, int, int, void *);
extern void func_0028B160(int, int, int);
extern void func_0011AEA0(int);
extern void func_0028AE88(int, int);

void func_00292888(void)
{
    int *hdr = (int *)D_001A7288;
    int base = D_001A7288;
    int i, size, mem, dst, n;
    int *m;

    for (i = 0; i < 5; i++)
        D_001B18B0[i] = (hdr[9 + i * 2] + 0x3F) & ~0x3F;
    size = (hdr[7] + 0x3F) & ~0x3F;
    mem = func_0028B2B8(size, 0, D_001A91F0, 0x2FF);
    func_00282B50(mem, hdr[6] + base, size);
    D_001B1888 = mem;
    m = (int *)mem;
    D_001B188C = mem + m[1];
    D_001B1890 = mem + m[2];
    D_001B1898 = mem + m[3];
    D_001B1894 = mem + m[4];
    dst = D_001BAEC0[4] + 0x60000;
    if (m[0x54 / 4] != 0) {
        n = (hdr[9] + 0x3F) & ~0x3F;
        func_00292B20(0, dst);
        n >>= 4;
        ((int *)D_001B1888)[0x94 / 4] = func_002EED58(base + hdr[8], n, n, D_001A9200);
        func_0028B160(0, dst, 1);
    }
    if (((int *)D_001B1888)[0x58 / 4] != 0) {
        mem = func_0028B2B8(((int *)D_001B1888)[0x58 / 4], 0, D_001A91F0, 0x327);
        func_00292B20(1, mem);
        func_0011AEA0(0);
        func_0028AE88(1, mem);
    }
    if (((int *)D_001B1888)[0x5C / 4] != 0) {
        n = ((hdr[13] + 0x3F) & ~0x3F) >> 4;
        ((int *)D_001B1888)[0x9C / 4] = func_002EED58(base + hdr[12], n, n, D_001A9210);
    }
    if (((int *)D_001B1888)[0x60 / 4] != 0) {
        n = ((hdr[15] + 0x3F) & ~0x3F) >> 4;
        ((int *)D_001B1888)[0xA0 / 4] = func_002EED58(base + hdr[14], n, n, D_001A9220);
    }
    if (((int *)D_001B1888)[0x64 / 4] != 0) {
        n = ((hdr[17] + 0x3F) & ~0x3F) >> 4;
        ((int *)D_001B1888)[0xA4 / 4] = func_002EED58(base + hdr[16], n, n, D_001A9230);
    }
}
