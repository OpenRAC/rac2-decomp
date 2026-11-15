typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
/* Copies the position and orientation (three direction vectors) from one object to another. */
void func_L05_00432158(u8 *source, u8 *dest) {
    TI128 *srcVec;
    TI128 *dstVec;
    int i;
    *(TI128 *)(dest + 0x10) = *(TI128 *)(source + 0x10);
    srcVec = (TI128 *)(source + 0xC0);
    dstVec = (TI128 *)(dest + 0xC0);
    for (i = 0; i < 3; i++)
        *dstVec++ = *srcVec++;
}
