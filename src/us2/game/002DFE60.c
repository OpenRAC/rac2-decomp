#include "include_asm.h"

#include "common.h"
typedef struct {
    short f0;
    short f2;
    char pad4[8];
} Slot;
extern Slot D_0025EBD0[];
extern int D_001AB29C[4] MACRO_ADDR;
extern int D_001A7318 MACRO_ADDR;
extern int func_002B0E90(void);
extern int func_002B0E28(void);

/* Unlock levels for the counts the player has collected. */
void func_US2_002DFE60(void)
{
    int a = func_002B0E90() >= 15;
    int b = func_002B0E90() >= 30;
    int c = func_002B0E28() >= 10;
    D_0025EBD0[5].f2 = a ? 3 : 2;
    D_0025EBD0[6].f2 = b ? 3 : 2;
    D_0025EBD0[7].f2 = c ? 10 : 2;
    D_0025EBD0[8].f2 = c ? 3 : 2;
    D_001AB29C[0] = a ? 0x2CB5 : 0x2CBB;
    D_001AB29C[1] = b ? 0x2CB6 : 0x2CBC;
    D_001AB29C[2] = c ? 0x2CB9 : 0x2CBD;
    D_001AB29C[3] = c ? 0x2CBA : 0x2CBD;
    if (D_001A7318) D_0025EBD0[8].f0 = 0;
}

