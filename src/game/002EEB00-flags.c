#include "include_asm.h"
#include "names.h"

extern int D_001A72D0 __attribute__((sda));
extern int D_001A72D4;
extern unsigned char *D_001B22A8 __attribute__((nosda));
extern char D_001ACA60[];

extern void func_002FC560(unsigned int reg, unsigned long long value);
extern int func_0011AEA0(int);
extern void func_002F1010(void);
extern void func_002F0E08(void);
extern void func_002F35B0(void);
extern void func_002F1E88(void);
extern void func_002F2A38(void);
extern void func_00282B50(void *, void *, int);

/* Starts the display list for the level, moves the resident chain cursor and
   appends the 0x20-byte packet at D_001ACA60. */
/* Draws one frame of the level: sets up the render state, runs each render pass in order, then adds the frame's final packet. */
void func_002F0EF8(void)
{
    VU1_addGSregister(0x47, 0x5180B);
    D_001A72D0 = D_001A72D4;
    FlushCache(0);
    func_002F1010();
    RunLevelRenderStep();
    FlushCache(0);
    func_002F35B0();
    func_002F1E88();
    func_002F2A38();
    FastMemoryHelperC(gDmaPacketCursor, D_001ACA60, 0x20);
    gDmaPacketCursor += 0x20;
}
