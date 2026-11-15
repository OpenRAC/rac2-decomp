#include "include_asm.h"
#include "names.h"

extern void func_002E37B0(void);
extern void func_002E3548(void);
extern void func_002E3820(void);
extern void func_002FC560(unsigned int reg, unsigned long value);

/* per level: the pointer handed to the first setter and the $gp slot it lands in */
extern int ref_L01_002F1F70_00 __attribute__((sda));
extern char ref_L01_002F1F70_01[];

extern int D_001A72E0 __attribute__((sda));

/* Sets up the drawing state for effects by running three setup routines and writing two graphics chip registers. */
void func_L01_002F1F70(void)
{
    ResetResidentTable();
    ref_L01_002F1F70_00 = (int)ref_L01_002F1F70_01;
    UpdateAllViewTransforms();
    LinkRenderPacketChain();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x01000000 | (D_001A72E0 >> 13));
}
