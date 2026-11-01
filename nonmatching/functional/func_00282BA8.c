/* functional: high. The memory barrier (sync) between the engine writes and the status read-back is not emitted; the read is kept and its value discarded, as in retail. */
typedef unsigned int u32;

/* Engine draw setup: three registers and the command 0x100 go to the engine, the status word is read back, 0x100 is returned. */
u32 func_00282BA8(u32 a0, u32 a1, u32 a2) {
    volatile u32 *p = (volatile u32 *)0x1000D000;
    p[0x20] = a1;
    p[0x04] = a0;
    p[0x08] = a2;
    p[0x00] = 0x100;
    (void)*(volatile u32 *)0x20100000;
    return 0x100;
}
