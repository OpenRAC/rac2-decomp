/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Retained C, 30 October 2026; not matching and no exact-C credit.
 * Profile: game -O2 -G8 -ffunction-sections. US: 864/872 bytes, 0/1.
 * Uses the reviewed qcopy/qzero with a height snapshot across the copy;
 * every local vector retains its full 16 bytes. Corrects the old numbered
 * object-table alias and distinguishes the absolute table/hero loads from
 * the GP-relative group count and thresholds. The first subtract now has
 * retail's FP registers. Position/state GPR allocation, saved addresses,
 * clear/list setup and loop scheduling still differ. The TI copy/barrier
 * probe was 868/872 but emitted a por-based clear, unlike retail's sq zero.
 * Next: a measured pointer lifetime/source-shape witness; no blind copy
 * or flag permutations. No strict-build claim for this candidate.
 */
#include "common.h"

extern s32 D_L09_001B2878 __attribute__((sda));
extern u8 *D_L09_001B285C NOT_SDA;
extern u16 *D_L09_001FB560[];

typedef int TI128 __attribute__((mode(TI)));

extern f32 D_L09_001B13B8 __attribute__((sda));
extern f32 D_L09_001B13BC __attribute__((sda));
extern f32 D_L09_001B13C4 __attribute__((sda));
extern f32 D_L09_001B13C8 __attribute__((sda));
extern f32 D_L09_001B13CC __attribute__((sda));
extern f32 D_L09_001B13D0 __attribute__((sda));
extern u8 *D_0018C0B0 NOT_SDA;

extern void func_00282CF0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_002A7790(f32);
extern void func_002AEE70(u8 *, void *, void *, f32, f32, f32);
extern void func_002AEF28(u8 *, void *, void *, f32, f32, f32);

void func_L09_00403398(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    f32 P[4] __attribute__((aligned(16)));
    f32 B[4] __attribute__((aligned(16)));
    f32 C[4] __attribute__((aligned(16)));
    u8 *pos;
    u8 *t;
    u16 *p;
    u8 *e;
    f32 f0, f2, len, w;
    f32 height;
    f32 *r0, *r1, *r2, *r3;

    *(f32 *)(state + 0x288) = *(f32 *)(a0 + 0x18);
    if (a0[0x20] != 9 && a0[0x20] != 4) {
        height = *(f32 *)(state + 0x294) - 0.033333335f;
        *(f32 *)(state + 0x294) = height;
        qcopy(P, a0 + 0x10);
        pos = a0 + 0x10;
        P[2] = height + (D_L09_001B13C4 - D_L09_001B13BC);
        t = *(u8 **)(state + 0x188);
        if (t == 0 || (t != D_0018C0B0 && *(s16 *)(t + 0xAA) != 0xD57 &&
                       *(s16 *)(*(u8 **)(t + 0x24) + 0x46) >= 11)) {
            f0 = *(f32 *)(state + 0x288) + D_L09_001B13BC;
            f2 = *(f32 *)(state + 0x294);
            if (f2 < f0)
                *(f32 *)(state + 0x294) = f2 + (f0 - f2) * D_L09_001B13C8;
        }
        f0 = *(f32 *)(state + 0x264) + D_L09_001B13BC;
        f2 = *(f32 *)(state + 0x294);
        if (f2 < f0)
            *(f32 *)(state + 0x294) = f2 + (f0 - f2) * D_L09_001B13C8;
        if (a0[0x20] >= 6 && a0[0x20] <= 8) {
            f0 = *(f32 *)(*(u8 **)(state + 0x230) + 0x18) + D_L09_001B13B8;
            f2 = *(f32 *)(state + 0x294);
            if (f2 < f0)
                *(f32 *)(state + 0x294) = f2 + (f0 - f2) * D_L09_001B13CC;
        }
        *(f32 *)(a0 + 0x18) = *(f32 *)(state + 0x294);
        qzero(B);
        r0 = (f32 *)(state + 0x278);
        r1 = (f32 *)(state + 0x27C);
        r2 = (f32 *)(state + 0x280);
        r3 = (f32 *)(state + 0x284);
        for (p = D_L09_001FB560[a0[0x21]];
             a0[0x21] != 0xFF && a0[0x21] <= D_L09_001B2878 && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L09_001FB560[a0[0x21]]);
             p++) {
            e = D_L09_001B285C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            func_00282CF0(C, pos, e + 0x10);
            len = func_00282DF0(C);
            if (len > D_L09_001B13D0)
                len = D_L09_001B13D0;
            else if (len < 0.0f)
                len = 0.0f;
            w = 1.0f - len / D_L09_001B13D0;
            func_002A7790(w);
            func_00282F20(C, C, len * w);
            func_00282CC0(B, B, C);
        }
        func_00282CC0(pos, pos, B);
        func_002AEE70(a0, r0, r1, 0.1f, 0.087266475f, *(f32 *)(a0 + 0x18));
        func_002AEF28(a0, r2, r3, 0.13962635f, 0.026179943f, 0.026179943f);
    } else {
        *(f32 *)(state + 0x294) = *(f32 *)(a0 + 0x18);
    }
}
