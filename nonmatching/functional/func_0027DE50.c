/* functional: high. Appends a GIF/DMA packet at the cursor D_001B22A8: a 16-byte DMA tag header, two A+D quads, then four 64-bit GS words built from the shifted coordinates and the screen offsets; the fifth argument ($t0, 64 bits) is stored as the data of the second quad. The cursor is advanced in the same steps as retail and left 0x60 bytes on. */
extern int D_001B22A8;
extern int D_001A7350;
extern int D_001A7354;
extern long long D_001AC7E0[2];
extern long long D_001AC7F0[2];

void func_0027DE50(int a0, int a1, int a2, int a3, long long t0)
{
    int c0 = D_001B22A8;
    int c;
    long long k;
    long long v;

    *(int *)(c0 + 0x0) = 0x10000005;
    *(int *)(c0 + 0x4) = 0;
    *(int *)(c0 + 0x8) = 0;
    *(int *)(c0 + 0xC) = 0x50000005;
    c = c0 + 0x10;
    D_001B22A8 = c;
    ((long long *)c)[0] = D_001AC7E0[0];
    ((long long *)c)[1] = D_001AC7E0[1];
    *(short *)c = (short)0x8001;

    c = D_001B22A8 + 0x10;
    D_001B22A8 = c;
    *(long long *)c = 0x144;
    *(long long *)(c + 8) = t0;

    c = D_001B22A8 + 0x10;
    D_001B22A8 = c;
    ((long long *)c)[0] = D_001AC7F0[0];
    ((long long *)c)[1] = D_001AC7F0[1];
    *(short *)c = (short)0x8004;

    a0 <<= 4;
    a1 <<= 4;
    a2 <<= 4;
    a3 <<= 4;
    k = (long long)0xFFFFF000 << 24;

    c = D_001B22A8 + 0x10;
    D_001B22A8 = c;
    *(long long *)c = (long long)(a2 + D_001A7350 - 8) | ((long long)(a0 + D_001A7354 - 8) << 16) | k;
    *(long long *)(c + 8) = (long long)(a3 + D_001A7350 - 8) | ((long long)(a0 + D_001A7354 - 8) << 16) | k;
    *(long long *)(c + 0x10) = (long long)(a2 + D_001A7350 - 8) | ((long long)(a1 + D_001A7354 - 8) << 16) | k;
    *(long long *)(c + 0x18) = (long long)(a3 + D_001A7350 - 8) | ((long long)(a1 + D_001A7354 - 8) << 16) | k;
    D_001B22A8 = D_001B22A8 + 0x20;
}
