/* func_0028CC98: -G8 unit. The table whose address is taken and the word cleared last
 * are sized sda objects ($gp), the two words at 0x1B18D0 an incomplete sda array (the
 * assembler's macro stores through $at); the stores are in the order whose schedule
 * gives retail's constant registers. */
extern int D_001A8DD8[2] __attribute__((sda));
extern int D_001A8D48 __attribute__((sda));
extern int D_001B18D0[] __attribute__((sda));

/* Initialises the element at a0 with default sizes and values. */
void func_0028CC98(void *a0)
{
    D_001B18D0[0] = 8;
    D_001B18D0[1] = (int)D_001A8DD8;
    *(short *)((char *)a0 + 0x48) = 0;
    *(short *)((char *)a0 + 0x4A) = 0;
    *(int *)((char *)a0 + 0x58) = 0xD2;
    *(int *)((char *)a0 + 0x5C) = 0xC8;
    *(int *)((char *)a0 + 0x74) = -2;
    *(int *)((char *)a0 + 0x78) = 0x1E;
    D_001A8D48 = 0;
}
