/* functional: high. Hand-written from the assembly (never matched); same stores and calls in order. func_002DFD88 is called with a0 still holding the queue pointer (D_001B1B80), passed explicitly. The result is whatever retail leaves in $v0 (the last queue pointer), returned explicitly. */
typedef unsigned int u32;

extern int D_001B1B7C;
extern u32 *D_001B1B80;
extern u32 *D_001B22A8;
extern void func_002DFD88(u32 *);
extern u32 D_001EF2E0[];
extern void func_002DFBB0(u32 *);

int func_002A0048(void)
{
    u32 *saved;

    if (D_001B1B7C == 0) {
        D_001B1B80[0] = 0x10000000;
        D_001B1B80[1] = 0;
        D_001B1B80[2] = 0;
        D_001B1B80[3] = 0;
        return (int)D_001B1B80;
    }
    saved = D_001B22A8;
    D_001B22A8 = saved + 4;
    D_001B1B80[0] = 0x20000000;
    D_001B1B80[1] = (u32)D_001B22A8;
    D_001B1B80[2] = 0;
    D_001B1B80[3] = 0;
    func_002DFD88(D_001B1B80);
    func_002DFBB0(D_001EF2E0);
    D_001B22A8[0] = 0x20000000;
    D_001B22A8[1] = (u32)(D_001B1B80 + 4);
    D_001B22A8[2] = 0;
    D_001B22A8[3] = 0;
    D_001B22A8 = D_001B22A8 + 4;
    saved[0] = 0x20000000;
    saved[3] = 0;
    saved[1] = (u32)D_001B22A8;
    saved[2] = 0;
    return (int)D_001B22A8;
}
