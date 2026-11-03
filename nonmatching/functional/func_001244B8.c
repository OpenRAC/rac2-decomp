/* functional: medium. Same hardware reads in the same order each pass (volatile), returns 0 as retail. Retail also reads VU0 control register 29 (VPU-STAT) with cfc2 and waits while its bit 0x100 (VU1 running) is set; that register has no C spelling and no memory address, so this C does not wait on it. The arguments are not read by retail. */

/* Wait until the GS paths are idle (libgraph sceGsSyncPath's wait, mode 0): VIF1 and GIF DMA channels stopped (CHCR STR),
   VIF1_STAT VPS idle, VU1 not running, GIF_STAT APATH idle. Returns 0. */
int func_001244B8(int mode, int timeout)
{
    unsigned int busy;

    do {
        unsigned int vif1 = *(volatile unsigned int *)0x10009000;
        unsigned int gif = *(volatile unsigned int *)0x1000A000;
        unsigned int vstat = *(volatile unsigned int *)0x10003C00;
        unsigned int gstat;

        busy = (vif1 & 0x100) ? 1 : 0;
        if (gif & 0x100) {
            busy |= 2;
        }
        if (vstat & 3) {
            busy |= 4;
        }
        /* retail: cfc2 $a0, $vi29; bit 0x100 adds 8 */
        gstat = *(volatile unsigned int *)0x10003020;
        if (gstat & 0xC00) {
            busy |= 0x10;
        }
    } while (busy != 0);
    return 0;
}
