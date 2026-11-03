/* 2026-11-03 w02 source-contract review (USA v1.01 only).
 * Profile: -O2 -G0 -ffunction-sections -g -fno-gcse.
 * Current check.py: 696/696 bytes, 0/2 places, first mismatch +0x1D4.
 * Corrected func_L01_00355BA0 and func_002E5F40 to their actual integer returns, verified in matched definitions. Division scheduling and the amount/original FP copies still differ.
 * Reopen: Independent division expression and FP-lifetime evidence.
 * No linked match or cross-release qualification is claimed. Earlier notes follow.
 */
/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 profile: -O2 -G0 -ffunction-sections -g -fno-gcse.
 * 696/696 bytes; local check fails at +0x1d4. Branch-shaped effect selection fixed the original conditional moves. Remaining division scheduling and value-copy choices differ. -g and -fno-gcse do not close the remaining gap.
 * US object comparison only in this retry; no linked strict-build claim.
 * Reopen with a measured allocation, scheduling or source-interface witness.
 */
#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned char D_00188660[];
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern int func_002E5F40(int, int);

void func_L04_0040DF90(unsigned char *m, unsigned char *p)
{
    float elapsed, amount, original;
    if (*(int *)(p + 0x32c) && func_00282948(p + 0x324)) {
        int handle = *(int *)(p + 0x328);
        if (handle != -1) {
            unsigned char *record = D_00188660 + handle * 0x70;
            if (*(void **)(record + 0x88) == m && record[0x74])
                func_002E59F8(handle);
        }
        *(int *)(p + 0x32c) = 0;
        *(int *)(p + 0x328) = -1;
        *(int *)(p + 0x324) = 0;
    }
    elapsed = *(float *)(p + 0x30c) + *(float *)(p + 0x27c) - 0.050000004f;
    if (elapsed < 0.0f) elapsed = 0.0f;
    if (!func_002E59B0(m, *(int *)(p + 0x330))) {
        if (m[0x20] == 3)
            *(int *)(p + 0x330) = func_002E5CF8(20, 5, m);
        else
            *(int *)(p + 0x330) = func_002E5CF8(0, 5, m);
    }
    if (!func_002E59B0(m, *(int *)(p + 0x334))) {
        if (m[0x20] == 3)
            *(int *)(p + 0x334) = func_002E5CF8(21, 5, m);
        else
            *(int *)(p + 0x334) = func_002E5CF8(1, 5, m);
    }
    if (func_002E59B0(m, *(int *)(p + 0x330))) {
        amount = elapsed * 3.0f;
        if (amount > 1.0f) amount = 1.0f;
        amount = 1.0f - amount;
        func_L01_00355BA0(*(int *)(p + 0x330), func_00283CF0(func_00283CE0(1024) * amount));
        amount = elapsed * 3.0f;
        if (amount > 1.0f) amount = 1.0f;
        func_002E5F40(*(int *)(p + 0x330), func_00283CF0(amount * 2816.0f));
    }
    if (func_002E59B0(m, *(int *)(p + 0x334))) {
        amount = elapsed / 0.45f;
        if (amount < 0.85f) {
            original = amount;
            amount = amount * 0.9411764f + 0.2f;
        } else {
            original = amount;
            amount -= 0.85f;
            amount = (1.0f - amount) * 0.8f + 0.2f;
        }
        func_L01_00355BA0(*(int *)(p + 0x334), func_00283CF0(func_00283CE0(1024) * amount));
        func_002E5F40(*(int *)(p + 0x334), func_00283CF0((1.0f - original) * -2816.0f));
    }
}
