#include "common.h"

/* Fade sequence follows rac1-decomp src/game/draw.c (GPL-3.0). */
typedef union { int *words; char *bytes; int address; } PacketCursor;

extern void func_002FC3C0(int);
extern void func_002FC1D8(void);
extern void func_002FC280(void);
extern void func_002FC220(void);
extern int func_001261F0(int);
extern void func_00284EA8(void);
extern void func_00284F40(int);
extern void func_00284FC0(void);
extern void func_002FC560(unsigned int, unsigned long);
extern int D_001B1598;
extern int D_001B1598_GP SDATA(D_001B1598);
extern PacketCursor ref_0027D330_00;
extern char D_00138990[];

/* Fades the screen to black over the given number of frames, drawing one frame per step. */
void func_0027D330(int frames)
{
    int i;

    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598_GP = D_001B1598 + 1;
    func_002FC1D8();
    i = frames - 1;
    if (i >= 0) {
        do {
            int q;

            func_00284EA8();
            func_00284F40(1);
            PutDrawBufferSmall();
            VU1_addGSregister(0x42, 0x8000000044UL);
            q = (i << 7) / (i + 1);
            i--;
            VU1_addGSregister(1, (unsigned long)(128 - q) << 24);
            ref_0027D330_00.words[0] = 0x30000014;
            ref_0027D330_00.words[1] = (int)D_00138990;
            ref_0027D330_00.words[2] = 0;
            ref_0027D330_00.words[3] = 0x50000014;
            ref_0027D330_00.words += 4;
            func_002FC3C0(1);
            func_001261F0(0);
            D_001B1598_GP = D_001B1598 + 1;
            SubmitBufferedDmaChain();
            func_002FC220();
        } while (i >= 0);
    }
    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598_GP = D_001B1598 + 1;
    func_002FC1D8();
    func_00284EA8();
    func_00284F40(1);
}
