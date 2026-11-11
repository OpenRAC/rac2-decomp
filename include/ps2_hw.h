#ifndef PS2_HW_H
#define PS2_HW_H

/* EE hardware registers, named once here. Hardware, so volatile (AGENTS.md); matched C uses
 * the name, never a cast on the address. A register is an integer address, not a linked
 * symbol: an extern symbol at that address lets the compiler keep the address in a register
 * across a loop, where retail rebuilds the constant at each access (func_L00_002A3B88).
 * Names follow the public PS2 hardware documentation (EE User's Manual register names as
 * used by the open PS2SDK), grouped by hardware block. */

#if defined(__mips__) || defined(__mips64)
typedef unsigned int ps2_u128 __attribute__((mode(TI), aligned(16)));
#else
typedef struct { unsigned int words[4]; } ps2_u128;
#endif

/* EE timers (10000000 timer 0, 10000800 timer 1, 10001800 timer 3) */
#define T0_COUNT (*(volatile unsigned int *)0x10000000)
#define T0_MODE  (*(volatile unsigned int *)0x10000010)
#define T1_COUNT (*(volatile unsigned int *)0x10000800)
#define T1_MODE  (*(volatile unsigned int *)0x10000810)
#define T3_MODE  (*(volatile unsigned int *)0x10001810)

/* IPU */
#define IPU_CMD      (*(volatile unsigned int *)0x10002000)
#define IPU_CMD64    (*(volatile unsigned long *)0x10002000) /* the same register read as 64 bits */
#define IPU_CTRL     (*(volatile unsigned int *)0x10002010)
#define IPU_TOP      (*(unsigned long *)0x10002030) /* not volatile: retail reads it once */
#define IPU_BP       (*(volatile unsigned int *)0x10002020)
#define IPU_IN_FIFO  (*(volatile ps2_u128 *)0x10007010)

/* GIF */
#define GIF_CTRL (*(volatile unsigned int *)0x10003000)

/* VIF1 */
#define VIF1_STAT  (*(volatile unsigned int *)0x10003C00)
#define VIF1_FBRST (*(volatile unsigned int *)0x10003C10)
#define VIF1_FIFO  (*(volatile ps2_u128 *)0x10005000)

/* DMA channel 0 (VIF0) */
#define D0_CHCR (*(volatile unsigned int *)0x10008000)
#define D0_QWC  (*(volatile unsigned int *)0x10008020)
#define D0_TADR (*(volatile unsigned int *)0x10008030)
/* DMA channel 1 (VIF1) */
#define D1_CHCR (*(volatile unsigned int *)0x10009000)
#define D1_MADR (*(volatile unsigned int *)0x10009010)
#define D1_QWC  (*(volatile unsigned int *)0x10009020)
#define D1_TADR (*(volatile unsigned int *)0x10009030)
/* DMA channel 2 (GIF) */
#define D2_CHCR (*(volatile unsigned int *)0x1000A000)
#define D2_MADR (*(volatile unsigned int *)0x1000A010)
#define D2_QWC  (*(volatile unsigned int *)0x1000A020)
/* DMA channel 3 (fromIPU) */
#define D3_CHCR (*(volatile unsigned int *)0x1000B000)
#define D3_MADR (*(volatile unsigned int *)0x1000B010)
#define D3_QWC  (*(volatile unsigned int *)0x1000B020)
/* DMA channel 4 (toIPU) */
#define D4_CHCR (*(volatile unsigned int *)0x1000B400)
#define D4_MADR (*(volatile unsigned int *)0x1000B410)
#define D4_QWC  (*(volatile unsigned int *)0x1000B420)
#define D4_TADR (*(volatile unsigned int *)0x1000B430)
/* DMA channel 5 (SIF0) */
#define D5_CHCR (*(volatile unsigned int *)0x1000C000)
/* DMA channel 8 (fromSPR) */
#define D8_CHCR (*(volatile unsigned int *)0x1000D000)
#define D8_MADR (*(volatile unsigned int *)0x1000D010)
#define D8_QWC  (*(volatile unsigned int *)0x1000D020)
#define D8_SADR (*(volatile unsigned int *)0x1000D080)
/* DMA channel 9 (toSPR) */
#define D9_CHCR (*(volatile unsigned int *)0x1000D400)
#define D9_MADR (*(volatile unsigned int *)0x1000D410)
#define D9_QWC  (*(volatile unsigned int *)0x1000D420)
#define D9_SADR (*(volatile unsigned int *)0x1000D480)
/* DMA controller */
#define D_CTRL    (*(volatile unsigned int *)0x1000E000)
#define D_STAT    (*(volatile unsigned int *)0x1000E010)
#define D_PCR     (*(volatile unsigned int *)0x1000E020)
#define D_SQWC    (*(volatile unsigned int *)0x1000E030)
#define D_RBSR    (*(volatile unsigned int *)0x1000E040)
#define D_RBOR    (*(volatile unsigned int *)0x1000E050)
#define D_ENABLER (*(volatile unsigned int *)0x1000F520)
#define D_ENABLEW (*(volatile unsigned int *)0x1000F590)

/* INTC */
#define I_STAT (*(volatile unsigned int *)0x1000F000)

/* EE SIO */
#define SIO_ISR    (*(volatile unsigned int *)0x1000F130)
#define SIO_TXFIFO (*(volatile unsigned char *)0x1000F180)

/* GS privileged registers */
#define GS_PMODE    (*(volatile unsigned long *)0x12000000)
#define GS_SMODE2   (*(volatile unsigned long *)0x12000020)
#define GS_DISPFB1  (*(volatile unsigned long *)0x12000070)
#define GS_DISPLAY1 (*(volatile unsigned long *)0x12000080)
#define GS_DISPFB2  (*(volatile unsigned long *)0x12000090)
#define GS_DISPLAY2 (*(volatile unsigned long *)0x120000A0)
#define GS_EXTDATA  (*(volatile unsigned long *)0x120000C0)
#define GS_EXTWRITE (*(volatile unsigned long *)0x120000D0)
#define GS_BGCOLOR  (*(volatile unsigned long *)0x120000E0)
#define GS_CSR      (*(volatile unsigned long *)0x12001000)
#define GS_BUSDIR   (*(volatile unsigned long *)0x12001040)

#endif
