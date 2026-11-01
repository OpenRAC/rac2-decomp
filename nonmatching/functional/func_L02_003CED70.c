/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* Bounded manual reconstruction, 2026-10-25; not linked.
 * Profile: -O2 -G0 -ffunction-sections.
 * 208/208 bytes; us: 0/2 placements; us2: 0/2 placements; pal: 0/2 placements.
 * Two complete input vectors are copied before the guard, as in retail. The canonical state helper
 * has three arguments; metadata used for the +0x98 store is preserved as a real read. The two-FP-
 * input helper returns f0, and the later integer-return helper result is ignored. Size and prefix
 * through +0x9c agree; the final flags temporary uses a different GPR from +0xa0.
 * Reopen with evidence for the final flags field or pointer lifetime. A typed tail view grew to 212
 * bytes and did not resolve allocation.
 * Prior complete variants and allocator diagnostics are preserved privately.
 * No candidate or linked-build credit is claimed.
 */
#include "common.h"



typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(u8 *object, s32 mode, s32 flag);

extern int func_002B6318(unsigned char *object);

extern float func_00283248(float, float);

void func_L02_003CED70(char *a0, char *a1, char *a2)
{
    union { TI128 q; float f[4]; } vectors[2];
    TI128 *p0 = &vectors[0].q;
    TI128 *p1 = &vectors[1].q;
    TI128 *q;
    char *p;
    unsigned short h;
    int t;

    vectors[0].q = *(TI128 *)a1;
    vectors[1].q = *(TI128 *)a2;
    p = *(char **)(a0 + 0x68);
    if (*(unsigned char *)(a0 + 0x20) != 0xD)
        return;
    h = *(unsigned short *)(a0 + 0x34);
    h &= 0xFFBE;
    h |= 0x1000;
    *(unsigned short *)(a0 + 0x34) = h;
    *(int *)(a0 + 0x98) = *(int *)(*(char **)(a0 + 0x24) + 0x10);
    func_002A7750((u8 *)a0, 0xE, -1);
    q = (TI128 *)(a0 + 0x10);
    qcopy(q, p0);
    *(float *)(a0 + 0xF8) = func_00283248(vectors[1].f[0], ((float *)p1)[1]);
    func_002B6318((unsigned char *)a0);
    q = (TI128 *)(p + 0x1A0);
    qcopy(q, p1);
    t = *(int *)(p + 0x138);
    *(int *)(p + 0x124) = 0;
    t |= 0x11;
    *(int *)(p + 0x120) = 0;
    *(int *)(p + 0x138) = t;
}
