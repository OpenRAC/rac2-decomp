/* func_L00_003B1270: 604 bytes, nearly all instructions match (about 6 differ, 0/27 places).
 * Compiled with -O2 -G8 -ffunction-sections (the L00_003A8E28-g8.c profile).
 * Remaining difference: retail materializes the boot-global pointer G (D_00189E20) in a1
 * (lui v1; lui a0; addiu a1,v1,lo; lw v0,hi(D_00138320); lw v1,0x1230(a1); and; s3=a1+0x80);
 * our compiler folds G+0x1230 into the lo relocations and shares G+0x1230 as base for s3
 * (lw a0,0x1230(v0); addiu a1,v0,0x1230; addiu s3,a1,-0x11B0).
 * Tried: G as a local pointer (inside/outside the case, at function top: worse), operand order
 * of the mask, loading D_00138320 into a temporary first. Argument-inline expressions fixed the
 * s0/s1 allocation of the two call sites. Needs a way to stop the address folding.
 */
#include "include_asm.h"
#include "common.h"

extern char D_L00_0023BB78[];
extern unsigned char D_L00_001AF810 __attribute__((sda));
extern unsigned char D_L00_001AF811 __attribute__((sda));

extern unsigned short D_L00_001AF82C __attribute__((sda));
extern unsigned char D_L00_001AF830 __attribute__((sda));
extern int D_L00_001B19C8;
extern char D_L00_001AF838[];
extern char D_L00_001AF848[];
extern int D_00138320;
extern char D_00189E20[];
extern void func_L00_003B0CE8(int);
extern char *func_L00_003B0DA0(char *);
extern void func_L00_003B1A08(int, int, int, int, ...);
extern int func_001163B0(void);
extern char *func_002C56B0(void *, int, int, int, int, int, int, float, float);

void func_L00_003B1270(char *a0)
{
    int found = 0;
    int i;
    char *g;
    int m;

    if (D_L00_001AF811 != D_L00_001AF810) {
        do {
            i = D_L00_001AF811;
            if (D_L00_001B19C8 - *(int *)(D_L00_0023BB78 + i * 0x1C + 0xC) < 0x1E0) {
                found = 1;
            } else {
                func_L00_003B0CE8(i);
            }
        } while (!found && D_L00_001AF811 != D_L00_001AF810);
    }
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x20) = 1;
        break;
    case 1:
        *(unsigned char *)(a0 + 0x20) = 2;
        break;
    case 2:
        m = D_00138320;
        g = D_00189E20;
        if (m & *(int *)(g + 0x1230)) {
            char *s3 = g + 0x80;
            char *s4 = func_L00_003B0DA0(s3);

            if (s4 != 0) {
                *(char **)(s4 + 0x10) = func_002C56B0(
                    s3, (unsigned char)(D_L00_001AF810 - 1), 0,
                    (short)(D_L00_001AF82C + (func_001163B0() & 7)), 1,
                    (unsigned char)(D_L00_001AF830 + (func_001163B0() & 3)), (int)a0, 1.0f, 1.0f);
            } else {
                func_002C56B0(s3, 0, 1,
                              (short)(D_L00_001AF82C + (func_001163B0() & 7)), 1,
                              (unsigned char)(D_L00_001AF830 + (func_001163B0() & 3)), (int)a0, 1.0f, 1.0f);
            }
        }
        break;
    }
    func_L00_003B1A08(0x41, 0x41, 0x80000000, (int)D_L00_001AF838, D_L00_001AF810);
    func_L00_003B1A08(0x40, 0x40, 0x80F0F0F0, (int)D_L00_001AF838, D_L00_001AF810);
    func_L00_003B1A08(0x41, 0x51, 0x80000000, (int)D_L00_001AF848, D_L00_001AF811);
    func_L00_003B1A08(0x40, 0x50, 0x80F0F0F0, (int)D_L00_001AF848, D_L00_001AF811);
}
