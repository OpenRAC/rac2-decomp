/* func_L05_0042C928 - 424 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Goes at the end of L05_00428350-g8.c (add `#include "common.h"` for
   u8/s32/qcopy; the file only has include_asm.h). Same size, ~40 masked
   lines.
   Open: (1) retail's early exit is `beqz a0,+3; nop; b exit; daddu v0,zero`
   (two separate return-0 blocks, unfilled slot), mine shares one block via
   `bnez a0,exit` with v0=0 in the delay slot. (2) retail loads the three gp
   floats (0x2758/0x275C/0x2760) together right after the 4th func_332C18
   call, before the mtc1 constant; mine loads each next to its multiply even
   with ax/ay/az locals.
   (3) D_001A79F0 as `int []` sda gives the tied lui/lw form as in retail. */

extern u8 D_0019B278[];
extern int D_001A79F0[] __attribute__((sda));
extern char *D_L05_0018C0B0 NOT_SDA;
extern float D_L05_001B1748 __attribute__((sda));
extern float D_L05_001B174C __attribute__((sda));
extern float D_L05_001B1750 __attribute__((sda));
extern char *D_L05_001B1780 __attribute__((sda));
extern char *D_L05_001B2528[] __attribute__((sda));
extern char *func_328508(s32 a0);
extern float func_332C18(void);
extern void func_42C290(char *a0);
extern void func_32A498(char *a0, s32 a1, s32 a2, s32 a3);

char *func_L05_0042C928(float *pos, u32 kind, s32 a2, s32 a3)
{
    char *s2;
    char *s0;
    char *p;
    char *r;
    float ax;
    float ay;
    float az;

    if (kind < 4) {
        if (D_0019B278[(D_001A79F0[0] << 2) + kind] != 0)
            return 0;
    }
    s2 = func_328508(0x126C);
    if (s2 == 0)
        return 0;
    s0 = *(char **)(s2 + 0x68);
    *(long *)(s2 + 0x38) = *(long *)(D_L05_0018C0B0 + 0x38);
    qcopy(s2 + 0x10, pos);
    *(u8 *)(s2 + 0x30) = 0x40;
    *(s16 *)(s2 + 0x32) = 0x40;
    *(u8 *)(s2 + 0x31) = 1;
    *(u32 *)s0 = kind;
    qcopy(s0 + 0x10, s2 + 0x10);
    *(float *)(s0 + 0x1C) = *(float *)(s2 + 0xF8);
    *(float *)(s2 + 0xF0) = func_332C18();
    *(float *)(s2 + 0xF4) = func_332C18();
    *(float *)(s2 + 0xF8) = func_332C18();
    *(float *)(s2 + 0xFC) = func_332C18();
    ax = D_L05_001B1748;
    ay = D_L05_001B174C;
    az = D_L05_001B1750;
    *(float *)(s0 + 0x60) = az * 0.00029088825f;
    *(s32 *)(s0 + 8) = a3;
    *(float *)(s0 + 0x68) = ax * 0.00029088825f;
    *(s32 *)(s0 + 4) = a2;
    *(float *)(s0 + 0x64) = ay * 0.00029088825f;
    *(u8 *)(s2 + 0x20) = 1;
    func_42C290(s2);
    func_32A498(s2, 0x82, 0x82, 0x82);
    if (D_L05_001B1780 == 0) {
        r = 0;
        for (p = D_L05_001B2528[0]; p != 0; p = *(char **)(p + 0x28)) {
            if (*(s16 *)(p + 0xAA) == 0xFBF)
                r = p;
        }
        D_L05_001B1780 = r;
    }
    return s2;
}
