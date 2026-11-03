/* functional: high. Same hardware stores in the same order (volatile). Retail keeps $s registers untouched and so does this. */

/* DMA controller reset: D_PCR |= 0x200, D_CTRL = 1 (DMA enable), then QWC = 0 on the VIF0, VIF1, GIF, fromIPU, toIPU, fromSPR and toSPR channels. */
void func_0029D050(void)
{
    volatile unsigned int *pcr = (volatile unsigned int *)0x1000E020;

    *pcr = *pcr | 0x200;
    *(volatile unsigned int *)0x1000E000 = 1;
    *(volatile unsigned int *)0x10008020 = 0;
    *(volatile unsigned int *)0x10009020 = 0;
    *(volatile unsigned int *)0x1000A020 = 0;
    *(volatile unsigned int *)0x1000B020 = 0;
    *(volatile unsigned int *)0x1000B420 = 0;
    *(volatile unsigned int *)0x1000D020 = 0;
    *(volatile unsigned int *)0x1000D420 = 0;
}
