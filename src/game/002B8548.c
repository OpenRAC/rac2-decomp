#include "names.h"
/* func_002B8548: the two-word request block at 0x1B1D70 is an sda array (assembler
 * macro stores through $at) whose address is held in a local, as retail keeps it in $s3;
 * the callees are func_001282A8, func_001288C0 and func_00128900(void *, char *), whose
 * result is stored, and the two clears of each state are in retail's store order. */
typedef struct {
    char reserved[0x194];
    int f194;
    int f198;
    int f19C;
} State_2B8548;

extern State_2B8548 D_00138180;
extern State_2B8548 D_00138500;
extern int D_001B1D70[2] __attribute__((sda));

extern int func_001282A8(void *);
extern int func_001288C0(int);
extern int func_00128900(void *, char *);

/* Sets up both controller ports at start-up. */
void func_002B8548(void *padInfo)
{
    int *requestBlock = D_001B1D70;
    int portMode = 2;

    SceDbcInit(padInfo);
    InitPad2SocketTable(0);
    D_001B1D70[0] = portMode;
    D_001B1D70[1] = 0;
    gPadState.f194 = ScePad2CreateSocket(requestBlock, (char *)&gPadState);
    gPadState.f198 = 0;
    gPadState.f19C = 0;
    D_001B1D70[0] = portMode;
    D_001B1D70[1] = 1;
    D_00138500.f194 = ScePad2CreateSocket(requestBlock, (char *)&D_00138500);
    D_00138500.f198 = 0;
    D_00138500.f19C = 0;
}
