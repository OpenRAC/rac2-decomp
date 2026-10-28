/* func_L09_003F6820 - 380 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L09_003F6820 (380 B, 1 place), needs `#include "common.h"` in
   L09_002F8BA0.c (qcopy/qzero), callee names are boot catalogue names
   (func_0029EFD0, func_002A7940, func_00283CE0, func_002A7470,
   func_002A7750_3).
   Draft h4 = best. Output is 384 B: only difference is that cse shares the
   constant 1:
     mine:   addiu $s7,$zero,1 hoisted, `sb $s7,0x31($s1)`, s7 saved in
   prologue
     retail: `addiu $a0,$zero,1; sb $a0,0x31($s1)` and a later separate `addiu
   $v0,$zero,1; sb $v0,0xBC($s1)`
   Everything else matches (with `m[0xBC] = 2` instead of 1 the whole function
   matches, 0 masked diff lines).
   Tried: `if (a3 != 0) {} else {...}`, `if (!a3)`, `m[0xBC] = (a3 == 0)`
   (different code); the order of `m[0x48]=0.5f` before `m[0x34] |= 1` is
   needed (fixes the tail swap).
   tried -fno-gcse on the file: no change to the shared constant 1 */

extern unsigned char *func_0029EFD0(int);
extern float func_002A7940(void);
extern float func_00283CE0(int);
extern void func_002A7470(unsigned char *, int, int, int);

unsigned char *func_L09_003F6820(unsigned char *pos, unsigned char *vel, int a2, int a3, int a4,
                                 float f0, float f1, float f2) {
    unsigned char *m = func_0029EFD0(0xD09);
    unsigned char *s0;

    if (m != 0) {
        m[0x30] = 0xFF;
        *(unsigned short *)(m + 0x32) = 0xFF;
        m[0x31] = 1;
        s0 = *(unsigned char **)(m + 0x68);
        *(float *)(m + 0xF8) = func_002A7940();
        *(float *)(m + 0xF4) = func_002A7940();
        *(float *)(m + 0xF0) = func_002A7940();
        *(float *)(m + 0x2C) = *(float *)(*(unsigned char **)(m + 0x24) + 0x24);
        *(int *)(s0 + 0x20) = a2;
        *(unsigned short *)(m + 0x34) |= 0x2200;
        qcopy(m + 0x10, pos);
        qcopy(s0, vel);
        qzero(s0 + 0x10);
        *(float *)(s0 + 0x28) = f0;
        *(float *)(s0 + 0x2C) = f1;
        *(int *)(s0 + 0x24) = a3;
        *(int *)(s0 + 0x30) = a4;
        *(float *)(s0 + 0x38) = func_00283CE0(a4);
        *(float *)(s0 + 0x34) = f2;
        m[0x23] = 0;
        if (a3 == 0) {
            m[0xBC] = 1;
        }
        if (m[0x43] != 0) {
            func_002A7470(m, 0, 0, 1);
        }
        m[0x31] = 0;
        *(float *)(m + 0x48) = 0.5f;
        *(unsigned short *)(m + 0x34) |= 1;
        func_002A7750_3(m, 0, -1);
    }
    return m;
}
