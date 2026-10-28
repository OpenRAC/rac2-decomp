#include "include_asm.h"

extern unsigned char D_001A7A0A;

extern int D_001A79F0 __attribute__((sda));

extern int func_L00_002E3A90(int, int);

int func_L00_002E3B38(int x)
{
    int b = D_001A7A0A;
    int q;
    int v;

    if (b == 0) {
        q = func_L00_002E3A90(D_001A79F0, x) / 100;
        v = 3 - q;
        return b < v ? v : 1;
    }
    return 3;
}

extern int D_001A79F0_1;
extern float ref_L00_002E3BA0_00[][3];

extern char *func_L00_0031E7A8(char *);

void func_L00_002E3BA0(char *object)
{
    char *p;

    if (D_001A7A0A == 0)
        return;
    {
        short id = *(short *)(object + 0xAA);

        if (id == 0x1F4 || id == 0x1F6 || id == 0x1F9 || id == 0x200)
            return;
    }
    if (D_001A79F0 >= 0x1C)
        return;
    *(short *)(object + 0xB6) = (int)(*(short *)(object + 0xB6) * ref_L00_002E3BA0_00[D_001A79F0][0]);
    if (*(short *)(object + 0xB6) < 0)
        *(short *)(object + 0xB6) = 0x7FFF;
    p = func_L00_0031E7A8(object);
    if (p != 0) {
        int i = D_001A79F0;
        float size = *(short *)(p + 4);
        float red = (unsigned char)p[0x14];
        float green = (unsigned char)p[0x15];
        float blue = (unsigned char)p[0x16];
        int v;

        *(short *)(p + 4) = (int)(ref_L00_002E3BA0_00[i][0] * size);
        *(float *)p = *(short *)(p + 4);
        v = (int)(ref_L00_002E3BA0_00[i][2] * red);
        if (v > 0xFF)
            v = 0xFF;
        p[0x14] = v;
        v = (int)(ref_L00_002E3BA0_00[D_001A79F0_1][2] * green);
        if (v > 0xFF)
            v = 0xFF;
        p[0x15] = v;
        v = (int)(ref_L00_002E3BA0_00[D_001A79F0_1][2] * blue);
        if (v > 0xFF)
            v = 0xFF;
        p[0x16] = v;
    }
}



/* func_L00_002E54E0 is matched in its own unit, src/levels/shared/L00_002E54E0-g8.c (-O2 -G8 -ffunction-sections). */
