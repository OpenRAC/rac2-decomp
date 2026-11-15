#include "include_asm.h"
/* func_00278EB0 (204 bytes, boot + 27 levels): fills the D_001B7F80 block. The 0x60000
 * reset of D_001B22B0 is written before the coordinate stores; its constant then dies at the
 * second coordinate's addition, which gives retail's order of the two additions. */
extern void func_002FC3C0(unsigned long);
extern int func_001261F0(int);
extern void func_002FC1D8(void);
extern void func_002E5FE0(void);
extern int D_001BAEC0[8];
typedef struct { int x, y, z, pad0C, f10, f14, f18; char pad1C[0x26 - 0x1C]; short f26; } CamState;
extern CamState D_001B7F80;
extern int D_001B1598 __attribute__((sda));
extern int D_001B22B0 __attribute__((sda));
extern int D_001A8BC0 __attribute__((sda));
extern float D_001B15A0 __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));

/* Prepares the screen for the next state: sets up the display, adjusts buffer offsets and initialises the state block. */
void func_00278EB0(void)
{
    CamState *state;
    int x, y, z;
    func_002FC3C0(1UL);
    func_001261F0(0);
    D_001B1598++;
    y = D_001BAEC0[4];
    x = D_001BAEC0[3];
    z = D_001B22B0;
    state = &D_001B7F80;
    state->f14 = z - 0x60000;
    D_001B22B0 = 0x60000;
    state->x = x + 0x60000;
    state->y = y + 0x60000;
    state->z = state->x + 0xD0800;
    D_001A8BC0 = 0x2000;
    func_002FC1D8();
    func_002E5FE0();
    state->f18 = D_001A72D4;
    state->f26 = 0;
    D_001B15A0 = 1.0f;
}
