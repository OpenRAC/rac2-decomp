#include "include_asm.h"
#include "names.h"

extern unsigned char D_001A7A0A;

extern int D_001A79F0 __attribute__((sda));

extern int func_L00_002E3A90(int, int);

/* Works out a level from the current difficulty and the given value, giving 3 when the mode flag is set. */
int func_L00_002E3B38(int amount)
{
    int mode = D_001A7A0A;
    int steps;
    int v;

    if (mode == 0) {
        steps = SumWeightedTableTaps(gCurrentMapIndex, amount) / 100;
        v = 3 - steps;
        return mode < v ? v : 1;
    }
    return 3;
}

extern int D_001A79F0_1;
extern float ref_L00_002E3BA0_00[][3];

extern char *func_L00_0031E7A8(char *);

/* Scales the health and glow of a spawned object by a per-level factor, except for crates. */
void func_L00_002E3BA0(char *object)
{
    char *glow;

    if (D_001A7A0A == 0)
        return;
    {
        short classId = *(short *)(object + 0xAA);

        if (classId == 0x1F4 /* Crate */ || classId == 0x1F6 /* moby class 502 */ || classId == 0x1F9 /* Explosive Crate */ || classId == 0x200 /* Purple Nanotech Crate */)
            return;
    }
    if (gCurrentMapIndex >= 0x1C)
        return;
    *(short *)(object + 0xB6) = (int)(*(short *)(object + 0xB6) * ref_L00_002E3BA0_00[gCurrentMapIndex][0]);
    if (*(short *)(object + 0xB6) < 0)
        *(short *)(object + 0xB6) = 0x7FFF;
    glow = func_L00_0031E7A8(object);
    if (glow != 0) {
        int i = gCurrentMapIndex;
        float size = *(short *)(glow + 4);
        float red = (unsigned char)glow[0x14];
        float green = (unsigned char)glow[0x15];
        float blue = (unsigned char)glow[0x16];
        int v;

        *(short *)(glow + 4) = (int)(ref_L00_002E3BA0_00[i][0] * size);
        *(float *)glow = *(short *)(glow + 4);
        v = (int)(ref_L00_002E3BA0_00[i][2] * red);
        if (v > 0xFF)
            v = 0xFF;
        glow[0x14] = v;
        v = (int)(ref_L00_002E3BA0_00[D_001A79F0_1][2] * green);
        if (v > 0xFF)
            v = 0xFF;
        glow[0x15] = v;
        v = (int)(ref_L00_002E3BA0_00[D_001A79F0_1][2] * blue);
        if (v > 0xFF)
            v = 0xFF;
        glow[0x16] = v;
    }
}



/* func_L00_002E54E0 is matched in its own unit, src/levels/shared/L00_002E54E0-g8.c (-O2 -G8 -ffunction-sections). */
