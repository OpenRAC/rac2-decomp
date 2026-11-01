#include "include_asm.h"

extern unsigned int D_001B22A8 __attribute__((sda));
extern char *D_001A742C __attribute__((section(".sdata")));
extern char D_001BAD40[];
extern void func_US2_0027DB38(void);
extern void func_0027D5C0(void);
extern char D_001A6AF0[];
extern int D_001B8840[];
extern void func_0011AED0(int);

/* Starts a DMA chain at packet: two ref tags sent through VIF DIRECT (9 quadwords from
   the screen context + 0xC0, 0x25 from D_001A6AF0), counts the frame at D_001B8840 + 0x34,
   lets one of two builders append, then ends the chain and hands it to func_0011AED0.
   The cursor is an integer address, so each word stored through it may alias it and it
   is read again before every store. */
void func_US2_002B73A0(unsigned int *packet)
{
    D_001B22A8 = (unsigned int)packet;
    *(unsigned int *)(D_001B22A8 + 0x00) = 0x30000009;
    *(unsigned int *)(D_001B22A8 + 0x04) = (unsigned int)(D_001A742C + 0xC0) & 0x0FFFFFFF;
    *(unsigned int *)(D_001B22A8 + 0x08) = 0;
    *(unsigned int *)(D_001B22A8 + 0x0C) = 0x50000009;
    *(unsigned int *)(D_001B22A8 + 0x10) = 0x30000025;
    *(unsigned int *)(D_001B22A8 + 0x14) = (unsigned int)D_001A6AF0;
    *(unsigned int *)(D_001B22A8 + 0x18) = 0;
    *(unsigned int *)(D_001B22A8 + 0x1C) = 0x50000025;
    D_001B22A8 += 0x20;
    D_001B8840[13]++;
    if (*(int *)D_001BAD40)
        func_US2_0027DB38();
    else
        func_0027D5C0();
    *(unsigned int *)(D_001B22A8 + 0x00) = 0x70000000;
    *(unsigned int *)(D_001B22A8 + 0x04) = 0;
    D_001B22A8 += 0x10;
    func_0011AED0(0);
}

