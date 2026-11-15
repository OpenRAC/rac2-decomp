#include "include_asm.h"
#include "names.h"
extern int D_L00_001A904C;
extern void UpdateBoltCounter(int);
extern int D_L00_001A904C;

void func_PAL_L00_0030FA80(int argument)
{
    if (D_L00_001A904C != 0) {
        UpdateBoltCounter(argument);
    }
}

extern void DrawBoltCounterDeltas(int);

void func_PAL_L00_0030FAA8(int argument)
{
    if (D_L00_001A904C != 0) {
        DrawBoltCounterDeltas(argument);
    }
}
