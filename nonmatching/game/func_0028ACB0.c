/* func_0028ACB0 - 468 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_0028ACB0: draft 460 B vs 468; 54 diff lines but most are relocation
   operands. Needs `#include "common.h"` (MACRO_ADDR) in 00288D88.c and the
   duplicate typedefs s32/u8/u32 removed there.
   Real differences: only the last block. Retail tests (a-1)<2 with `beql ...
   ; ld $s0,0($sp)` (epilogue copied into the delay slot) and then reloads
   D_001B1888 with lui/lw after the branch; mine moves the D_001B1888 load
   into the branch delay slot (where it becomes a $gp load) and has no
   epilogue copy. Tried: nested ifs vs combined condition, D_001B1888 as sda
   array vs MACRO_ADDR, per-block count variables (needed for s1/s2
   assignment), struct for D_001F2840. */

extern char *D_001B1888 MACRO_ADDR;
extern int D_001B18B0[];
extern int D_001B18B8[];
extern int D_001B18BC[];
extern int D_001B18C0[];
typedef struct { char pad00[0x20]; int obj; char pad24[0xF0]; int pos; } GameCtx;
extern GameCtx D_001F2840;
extern void func_002EEED0(int, int, int, int, int);
extern void func_0029D4D0(int, int);
extern void func_0028AE88(int, int);

void func_0028ACB0(int a)
{
    int n0 = *(int *)(D_001B1888 + 0x54);
    int n1;
    int n2;
    int obj = D_001F2840.obj;
    int pos = D_001F2840.pos;

    if (n0 != 0) {
        func_002EEED0(obj, *(int *)(D_001B1888 + 0x94), 0, D_001B18B0[0] / 16, 0);
        func_0029D4D0(obj, pos);
        func_0028AE88(0, pos);
        pos += n0;
    }
    n1 = *(int *)(D_001B1888 + 0x5C);
    if (n1 != 0) {
        func_002EEED0(obj, *(int *)(D_001B1888 + 0x9C), 0, D_001B18B8[0] / 16, 0);
        func_0029D4D0(obj, pos);
        func_0028AE88(2, pos);
        pos += n1;
    }
    if (a == 0 || a == 2) {
        n2 = *(int *)(D_001B1888 + 0x60);
        if (n2 != 0) {
            func_002EEED0(obj, *(int *)(D_001B1888 + 0xA0), 0, D_001B18BC[0] / 16, 0);
            func_0029D4D0(obj, pos);
            func_0028AE88(3, pos);
            pos += n2;
        }
    }
    if (a >= 1 && a <= 2 && *(int *)(D_001B1888 + 0x64) != 0) {
        func_002EEED0(obj, *(int *)(D_001B1888 + 0xA4), 0, D_001B18C0[0] / 16, 0);
        func_0029D4D0(obj, pos);
        func_0028AE88(4, pos);
    }
}
