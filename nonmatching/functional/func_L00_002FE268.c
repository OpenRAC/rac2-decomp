/* functional: high. Same stores in retail's order (the latch, block[0], block[2], then block[1] in the call's delay slot). Retail leaves the block's address in $a3 at the call; func_002933D0 takes three arguments and overwrites $a3 before reading it, so the C passes three. */
/*
 * func_L00_002FE268 (108 bytes): latches its argument in D_001A72C0, fills
 * the three-doubleword GIF block at D_L00_001C91C0 (the resident word at
 * D_001A72C8, then the tag words 0xFFA0000000E0 and 0x40000400004000, as
 * func_00292328 does for the boot's blocks) and hands the level's header word
 * D_L00_001BF1B4 and the map at D_L00_001A9510 ($gp-0x5AE0) to func_002933D0.
 */
extern unsigned long D_001A72C8;
extern unsigned int D_001A72C0;
extern unsigned int D_L00_001BF1B4;
extern unsigned long D_L00_001C91C0[3];
extern unsigned char D_L00_001A9510[];

extern void func_002933D0(void *, int, void *);

void func_L00_002FE268(unsigned int value)
{
    unsigned long previous = D_001A72C8;

    D_001A72C0 = value;
    D_L00_001C91C0[0] = previous;
    D_L00_001C91C0[2] = 0x40000400004000UL;
    D_L00_001C91C0[1] = 0xFFA0000000E0UL;
    func_002933D0((void *)D_L00_001BF1B4, 0, D_L00_001A9510);
}
