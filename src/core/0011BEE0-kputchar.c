#include "ps2_hw.h"
/* kputchar (libkernl.a:kprintf.o; config/datamine/ntsc-u-sdk-matches.tsv): wait until the SIO
   status register's busy bit (0x8000) is clear, write the character to the SIO data register
   and return it. Both accesses are real hardware registers. The store reaches the return's
   delay slot through the SDK assembler's slot swap, not through reorg, so this unit needs
   -Wa,--r5900-swap-branch-slots like the rest of kprintf.o (src/core/0011BF18.c); see
   docs/build/compiler-notes.md, "SDK objects". */
int func_0011BEE0(int c) {
    while (SIO_ISR & 0x8000)
        ;
    SIO_TXFIFO = c;
    return c;
}
