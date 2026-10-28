/* functional: high. Starts a new 2D batch: remembers the DMA cursor in D_001B15F4 and reserves a qword, resets the VRAM cursor to the dynamic base, clears the UI texture slot table (16 bytes per entry) and a few scratch words, and, when arg is 0, zeroes HUD texture/clut slot halfwords at +4 that point past the VRAM frame buffer B limit (or all clut slots); same reads and writes as retail, only codegen differs. */
extern int D_001B22A8 __attribute__((sda));
extern int D_001B15F4 __attribute__((sda));
extern int D_001B15FC __attribute__((sda));
extern int D_001B1600 __attribute__((sda));
extern int D_001A72D0 __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern int D_001A72DC __attribute__((sda));
extern int D_001B1888 __attribute__((sda));
extern int D_001B1894 __attribute__((sda));
extern int D_001B1898 __attribute__((sda));
extern long D_001B9740[];
extern long D_001A8780 __attribute__((sda));
extern long D_001A8788 __attribute__((sda));
extern int D_001A8790 __attribute__((sda));

void func_0027C540(int arg) {
    int cursor = D_001B22A8;
    int base = D_001A72D4;
    int n;
    int i;
    D_001B15F4 = cursor;
    D_001B22A8 = cursor + 0x10;
    n = D_001B1600;
    D_001A72D0 = base;
    D_001B15FC = 0;
    for (i = 0; i < n; i++) {
        D_001B9740[i * 2] = 0;
    }
    D_001A8780 = 0;
    D_001A8788 = 0;
    D_001A8790 = 0;
    if (arg == 0) {
        for (i = 0; i < *(int *)(D_001B1888 + 0x44); i++) {
            unsigned short *p = (unsigned short *)(D_001B1894 + i * 8 + 4);
            if (!(*p < (D_001A72DC >> 8))) {
                *p = 0;
            }
        }
        for (i = 0; i < *(int *)(D_001B1888 + 0x24); i++) {
            *(unsigned short *)(D_001B1898 + i * 8 + 4) = 0;
        }
    }
}
