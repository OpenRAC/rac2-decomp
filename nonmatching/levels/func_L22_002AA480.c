/* func_L22_002AA480 - 504 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs `#include "common.h"` in L22_002A8B98.c and removal of that file's
   later `typedef u8/u16/f32` lines (they clash). Draft is 496 B vs 504 B,
   logic fully decoded.
   Open: retail keeps the object in s1 and the table pointer (D_L22_001B8EC0,
   lui/addiu) in s0 computed inside the first branch; mine hoists the table
   into s1 and the object into s0 (register naming), and is 8 bytes short
   around the table address build. */

extern void func_00316A90(char *a0, int a1, float *a2);
extern void func_002F4568(char *a0, float *a1);
extern void func_00324260(float *a0, char *a1);
extern char *func_002A8C48(char *a0, int a1, int a2, char *a3);
extern char D_L22_001B8EC0[];
extern void func_002F3858(char *dst, char *src, int n);
extern void func_003180D8(char *a0);

void func_L22_002AA480(void)
{
    float m[16];
    char *base = D_00189E20;
    char *s1 = *(char **)(base + 0xC18);
    char *a0;
    char *s0;

    *(u8 *)(s1 + 0x6F) = 0;
    a0 = *(char **)(base + 0x2290);
    if ((*(u16 *)(a0 + 0x34) ^ 1) & 1) {
        func_00316A90(a0, 5, m);
        qcopy(s1 + 0x10, &m[12]);
        func_002F4568(s1 + 0xC0, m);
        func_00324260(m, s1 + 0xF0);
        *(u16 *)(s1 + 0x34) &= 0xFFBE;
        if (*(u8 *)(s1 + 0x43) != 0x7A) {
            s0 = D_L22_001B8EC0;
            *(u8 *)(s1 + 0x43) = 0x7A;
            *(u8 *)(s1 + 0x42) = 0x7A;
            *(u8 *)(s1 + 0x40) = 1;
            *(char **)(s1 + 0x58) = func_002A8C48(s1, 0x7A, 1, s0);
            *(char **)(s1 + 0x5C) = func_002A8C48(s1, *(u8 *)(s1 + 0x43), *(u8 *)(s1 + 0x41), s0 + 0x600);
        } else {
            if (*(u8 *)(s1 + 0x42) == *(u8 *)(s1 + 0x43))
                *(float *)(s1 + 0x44) += *(float *)(s1 + 0x48) * *(float *)(s1 + 0x4C);
            else
                *(float *)(s1 + 0x44) += *(float *)(s1 + 0x4C);
        }
        if (1.0f <= *(float *)(s1 + 0x44)) {
            s0 = D_L22_001B8EC0 + 0x600;
            *(u8 *)(s1 + 0x40) = *(u8 *)(s1 + 0x41);
            *(char **)(s1 + 0x58) = D_L22_001B8EC0;
            func_002F3858(D_L22_001B8EC0, s0, 0x600);
            *(u8 *)(s1 + 0x41) += 1;
            if (*(u8 *)(s1 + 0x41) >= *(u8 *)(*(char **)(*(char **)(s1 + 0x24) + *(u8 *)(s1 + 0x43) * 4 + 0x48) + 0x10))
                *(u8 *)(s1 + 0x41) = 0;
            *(char **)(s1 + 0x5C) = func_002A8C48(s1, *(u8 *)(s1 + 0x43), *(u8 *)(s1 + 0x41), s0);
            *(float *)(s1 + 0x44) = (*(float *)(s1 + 0x44) - 1.0f) / *(float *)(s1 + 0x4C);
            *(float *)(s1 + 0x4C) = **(float **)(s1 + 0x58);
            *(float *)(s1 + 0x44) *= *(float *)(s1 + 0x4C);
            func_003180D8(s1);
        }
    } else {
        *(u16 *)(s1 + 0x34) |= 0x41;
    }
}
