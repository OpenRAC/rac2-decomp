#include "include_asm.h"
#include "names.h"

extern void func_002E37B0(void);
extern void func_00291158(void);
extern void func_002E3548(void);
extern void func_002E3820(void);
extern void func_002FC560(unsigned int, unsigned long);
extern float D_00255B40[];
extern float *D_001B1990 __attribute__((sda));
extern int D_001A79F0;
extern int D_001A72E0;

/* Sets up level drawing: picks one of two set-up paths by level number and writes two graphics settings. */
void func_00291268(void)
{
    ResetResidentTable();
    D_001B1990 = D_00255B40;
    if (gCurrentMapIndex == 0)
        UpdateSkyShellHeights();
    else
        UpdateAllViewTransforms();
    LinkRenderPacketChain();
    VU1_addGSregister(0x47, 0x5360BUL);
    VU1_addGSregister(0x4E, (D_001A72E0 >> 13) | 0x1000000);
}
