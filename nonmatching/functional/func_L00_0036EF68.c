/* functional: high. Same loads, stores and order of side effects as retail; locals and register use differ. The 64-bit `dli 0xffff` compare is of a zero-extended halfword, so an unsigned short compare is the same. */
/*
 * func_L00_0036EF68 (248 bytes): writes three 6-bit fields (the arguments
 * shifted right by 2) into the low bits of the block's first three words, sets
 * bit 1 of byte 0x1E, then, when the block's row index (halfword 0x14) is not
 * 0xFFFF, writes the packed value (fields at bits 2, 10, 18, plus bit 31) into
 * every slot of the slot list the class record names, relative to the block's
 * row of the table at D_L00_001B2524 ($gp+0x3534).
 * Draft fixes: the table is the word at 0x1B2524 itself (not read through it),
 * and the flag is 0x80000000 (lui 0x8000), not 0x8000.
 */
extern unsigned int D_L00_001B2524;
extern unsigned int D_L00_00226700[];

void func_L00_0036EF68(int *a, unsigned int a1, unsigned int a2, unsigned int a3)
{
    unsigned int value;
    unsigned int base;
    unsigned int record;
    unsigned short *q;
    unsigned int off;
    unsigned int index;
    unsigned int n;
    int count;

    a1 >>= 2;
    a2 >>= 2;
    a3 >>= 2;
    *(unsigned char *)((char *)a + 0x1E) |= 2;
    a[0] = (a[0] & -64) | a1;
    a[1] = (a[1] & -64) | a2;
    a[2] = (a[2] & -64) | a3;
    index = *(unsigned short *)((char *)a + 0x14);
    if (index == 0xFFFF)
        return;

    base = D_L00_001B2524 + index * 16;
    record = D_L00_00226700[*(unsigned char *)((char *)a + 0x1D)];
    value = (a1 << 2) | (a2 << 10) | (a3 << 18) | 0x80000000u;

    n = *(unsigned short *)(record + *(unsigned char *)((char *)a + 0x1F) * 2 + 0x78);
    if (n != 0) {
        q = (unsigned short *)(*(unsigned int *)(record + 0x34) + n);
        count = q[0];
        off = q[1];
        q += 2;
        do {
            count--;
            *(unsigned int *)(base + off) = value;
            off = *q++;
        } while (count > 0);
    }
}
