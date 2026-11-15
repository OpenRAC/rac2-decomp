#include "common.h"

/* Adapted from rac1-decomp src/game/draw.c (GPL-3.0). */
extern int D_001A7350[] __attribute__((sda));
extern int D_001A7354[] __attribute__((sda));
extern int D_001A7358[] __attribute__((sda));
extern int D_001A735C[] __attribute__((sda));
extern int D_001B15A8, D_001B15AC;
extern unsigned char D_001A7BB0[] __attribute__((sda));
typedef union { int *words; char *bytes; int address; } PacketCursor;
extern PacketCursor ref_0027D900_01;
extern char ref_0027D900_02[], ref_0027D900_03[];
/* Draws the top and bottom letterbox bars, growing them to 52 lines while the flag is set and shrinking them otherwise. */
void func_0027D900(void) {
    int h;

    if (D_001B15A8 != 0) {
        if (D_001B15AC < 52) {
            D_001B15AC++;
        }
    } else {
        if (D_001B15AC == 0) {
            return;
        }
        D_001B15AC--;
    }
    h = D_001B15AC;
    if (h == 0 || D_001A7BB0[1]) {
        return;
    }
    h <<= 4;
    ref_0027D900_01.words[0] = 0x10000007;
    ref_0027D900_01.words[1] = 0;
    ref_0027D900_01.words[2] = 0;
    ref_0027D900_01.words[3] = 0x50000007;
    {
        int *base = ref_0027D900_01.words;
        ref_0027D900_01.words = base + 4;
        qcopy(ref_0027D900_01.words, ref_0027D900_02);
        *(short *)(base + 4) = 0x8001;
    }
    {
        int *base = ref_0027D900_01.words;
        long *p;
        ref_0027D900_01.words = base + 4;
        p = (long *)ref_0027D900_01.words;
        p[0] = 0x104;
        p[1] = 0x80000000;
    }
    {
        int *base = ref_0027D900_01.words;
        ref_0027D900_01.words = base + 4;
        qcopy(ref_0027D900_01.words, ref_0027D900_03);
        *(short *)(base + 4) = 0x8008;
    }
    {
        int *base = ref_0027D900_01.words;
        long *p;
        ref_0027D900_01.words = base + 4;
        p = (long *)ref_0027D900_01.words;
        p[0] = D_001A7350[0] | ((long)D_001A7354[0] << 16) | ((long)0xFFFFF3 << 32);
        p[1] = D_001A7350[0] | ((long)(D_001A7354[0] + h) << 16) | ((long)0xFFFFF3 << 32);
        p[2] = D_001A7358[0] | ((long)D_001A7354[0] << 16) | ((long)0xFFFFF3 << 32);
        p[3] = D_001A7358[0] | ((long)(D_001A7354[0] + h) << 16) | ((long)0xFFFFF3 << 32);
        p[4] = D_001A7358[0] | ((long)D_001A735C[0] << 16) | ((long)0xFFFFF3 << 32);
        p[5] = D_001A7358[0] | ((long)(D_001A735C[0] - h) << 16) | ((long)0xFFFFF3 << 32);
        p[6] = D_001A7350[0] | ((long)D_001A735C[0] << 16) | ((long)0xFFFFF3 << 32);
        p[7] = D_001A7350[0] | ((long)(D_001A735C[0] - h) << 16) | ((long)0xFFFFF3 << 32);
    }
    ref_0027D900_01.words = (int *)((char *)ref_0027D900_01.words + 0x40);
}
