#include "include_asm.h"
#include "names.h"

extern void func_002FC560(unsigned int reg, unsigned long long value);

extern int D_001A72E0;

extern short D_001A6480[];

extern void func_0027DE50(int a, int b, int c, int d, unsigned long e);

/* The argument is a structure: a word at +4 and a double word at +8. */
/* Draws a screen-sized fade or tint step using the values stored in the given packet. */
void func_0027DCE8(char *packet)
{
    if (*(unsigned long long *)(packet + 8) != 0) {
        VU1_addGSregister(0x42, *(unsigned long long *)(packet + 8) & 0xFF000000FFULL);
    }
    if (*(int *)(packet + 4) & 0xFF000000) {
        VU1_addGSregister(0x4E, (((long long)(D_001A72E0 >> 13) | 0x1000000) | (1LL << 32)));
        DrawColoredRectangle(0, gScreenAdjustOffsets[0xA9], 0, gScreenAdjustOffsets[0xA8], *(unsigned int *)(packet + 4));
        VU1_addGSregister(0x4E, (D_001A72E0 >> 13) | 0x1000000);
    }
    if (*(unsigned long long *)(packet + 8) != 0) {
        VU1_addGSregister(0x42, 0x8000000044ULL);
    }
}

extern char *ref_0027DDC0_00;

extern char D_00138850[];

/* Packs a colour into the GS register 1 and writes the matching packet. */
/* Sets the screen clear color and adds a matching draw packet. */
void func_0027DDC0(int r, int g, int b, int a)
{
    unsigned long packed;

    packed = (unsigned long)r | ((unsigned long)g << 8);
    packed |= ((unsigned long)b << 16);
    packed |= ((unsigned long)a << 24);
    VU1_addGSregister(1, packed);
    *(int *)(ref_0027DDC0_00 + 0) = 0x30000014;
    *(char **)(ref_0027DDC0_00 + 4) = D_00138850;
    *(int *)(ref_0027DDC0_00 + 8) = 0;
    *(int *)(ref_0027DDC0_00 + 12) = 0x50000014;
    ref_0027DDC0_00 = ref_0027DDC0_00 + 16;
}

extern int *D_001B22A8 __attribute__((section(".sdata")));
extern int *D_001B15F4 __attribute__((section(".sdata")));
extern int D_001A72D0 __attribute__((section(".sdata")));
extern int D_001A72D4 __attribute__((section(".sdata")));
extern int D_001A72DC __attribute__((section(".sdata")));
extern int D_001B15FC __attribute__((section(".sdata")));
extern int D_001B1600 __attribute__((section(".sdata")));
extern long D_001A8780 __attribute__((sda));
extern long D_001A8788 __attribute__((sda));
extern int D_001A8790 __attribute__((section(".sdata")));
extern long D_001B9740[];
extern char D_001B1870[] __attribute__((sda));

/* SetupGifPaging, after RAC1 draw.c (GPL-3.0): marks the packet cursor in
   D_001B15F4 and reserves 0x10 bytes, restarts the texture allocation cursor,
   clears the upload count and the first dword of the paging slots, then, when
   arg0 is 0, clears the +4 half of the arena's 8-byte list entries: the list
   at +0x24 (count at +0x44 of the record at +0x18) where it is at least
   D_001A72DC >> 8, and all of the list at +0x28 (count at +0x24).  The arena
   read at an offset is a two-word load, which keeps the second list's load out
   of the loop branch's delay slot. */
void func_0027C540(int keepEntries) {
    int *cursor = gDmaPacketCursor;
    int i;

    D_001B15F4 = cursor;
    cursor += 4;
    gDmaPacketCursor = cursor;
    D_001A72D0 = D_001A72D4;
    D_001B15FC = 0;
    {
        int k;

        for (k = 0; k < D_001B1600; k++) {
            D_001B9740[k * 2] = 0;
        }
    }
    D_001A8780 = 0;
    D_001A8788 = 0;
    D_001A8790 = 0;
    if (keepEntries == 0) {
        for (i = 0; i < *(int *)(*(char **)(gHudState + 0x18) + 0x44); i++) {
            unsigned short *el = (unsigned short *)(i * 8 + *(int *)(gHudState + 0x24) + 4);

            if (*el >= (D_001A72DC >> 8)) {
                *el = 0;
            }
        }
        {
            int j;

            for (j = 0; j < *(int *)(*(char **)(gHudState + 0x18) + 0x24); j++) {
                *(short *)(*(char **)(gHudState + 0x28) + j * 8 + 4) = 0;
            }
        }
    }
}
