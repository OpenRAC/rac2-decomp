#include "include_asm.h"

extern int D_001A8A5C __attribute__((sda));
extern int D_PAL_001B1D7C __attribute__((sda));

int func_PAL_L00_0030BA48(void) {
    return D_PAL_001B1D7C;
}


/* func_PAL_L00_0030BA80, the PAL copy of func_00298BB8: the same C, unchanged. */
extern unsigned char D_001A7930[];
extern unsigned char D_001A7948[];
extern unsigned char D_001A7960[];
extern unsigned char D_001A7980[];
extern unsigned char D_001A79A0[];
extern unsigned char D_001A79D0[];
extern void func_00115AC0(void *, int, int);

void func_PAL_L00_0030BA80(unsigned char *source)
{
    int i;
    int value = source[0x12];
    if (value == 0x45)
        D_001A7930[2] = value;
    else if (value == 0x50)
        D_001A7930[2] = 0x49;
    for (i = 3; i < 7; i++)
        D_001A7930[i] = source[i + 0xd];
    for (i = 8; i < 11; i++)
        D_001A7930[i] = source[i + 0xd];
    for (i = 11; i < 13; i++)
        D_001A7930[i] = source[i + 0xe];
    func_00115AC0(D_001A7948, (int)D_001A7930, 13);
    func_00115AC0(D_001A7960, (int)D_001A7930, 13);
    func_00115AC0(D_001A7980, (int)D_001A7930, 13);
    func_00115AC0(D_001A79A0, (int)D_001A7930, 13);
    func_00115AC0(D_001A79A0 + 0x14, (int)D_001A7930, 13);
    func_00115AC0(D_001A79D0, (int)D_001A7930, 13);
}
