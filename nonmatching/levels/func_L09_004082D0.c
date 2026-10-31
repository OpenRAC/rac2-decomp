/* Retained C, 30 October 2026; not matching and no exact-C credit.
 * Profile: game -O2 -G0 -ffunction-sections -fno-thread-jumps.
 * US: 420/420 bytes, 0/1; first unbound mismatch +0x6C. The four-slot
 * scan advances once for either a missing slot or a queried slot; the
 * previous draft incorrectly reset/doubled the pointer. State transitions
 * preserve the shared object-state guard. Modern qcopy preserves the
 * complete 16-byte local position, and the query uses its canonical name.
 * Boolean if-conversion, loop likely slots, and tail setup still differ.
 * A byte snapshot/assignment ties the conversion; -fno-if-conversion is
 * not supported by this cc1. -mno-split-addresses makes the source select
 * a movn, so it was rejected. No strict-build claim for this candidate.
 * Next: a measured control-flow witness that retains the scalar branches.
 */
#include "common.h"

extern s32 D_L09_001B2388 __attribute__((sda));

extern char D_L09_00189EA0[];
extern char D_L09_001B9A00[];

extern s32 func_L00_00329520(char *a0, s32 a1);
extern void func_L09_00408250(char *a0, char *a1, s32 a2, s32 a3);
extern void func_L09_004081F0(char *a0, s32 a1, char *a2, s32 a3);

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TQ_L09_004082D0 __attribute__((mode(TI)));

void func_L09_004082D0(u8 *a0) {
    char *s3;
    TQ_L09_004082D0 *src;
    s32 *p;
    s32 *q;
    s32 i;
    s32 r;
    u8 mode;
    s32 flag;
    TQ_L09_004082D0 buf;

    if (D_L09_001B2388 >= 5) {
        s3 = *(char **)(a0 + 0x68);
        a0[0x30] = 0xFF;
        flag = 0;
        if (*(s8 *)(s3 + 0xBE) != 0) {
            src = (TQ_L09_004082D0 *)D_L09_001B9A00;
        } else {
            src = (TQ_L09_004082D0 *)D_L09_00189EA0;
        }
        qcopy(&buf, src);
        mode = a0[0x95];
        if (mode == 0) {
            for (i = 0, p = (s32 *)s3; i < 4; i++) {
                if (*p == -1) {
                    p++;
                    continue;
                }
                r = func_L00_00329520((char *)&buf, *p);
                p++;
                if (r != 0) {
                    flag = 1;
                    break;
                }
            }
        } else if (mode == 1) {
            flag = 1;
        }
        if (flag ? a0[0xBC] != 0 : a0[0xBC] == 0) {
            if (a0[0x20] != 0)
                return;
        }
        if (flag)
            a0[0xBC] = 1;
        else
            a0[0xBC] = 0;
        a0[0x20] = a0[0xBC] + 1;
        p = (s32 *)(s3 + 0x10);
        for (i = 28; i >= 0; i--) {
            s32 v = *p;
            if (v != -1) {
                func_L09_00408250(a0, s3, v, flag);
            }
            p++;
        }
        q = (s32 *)(s3 + 0x84);
        for (i = 13; i >= 0; i--) {
            s32 v = *q;
            if (v != -1) {
                func_L09_004081F0(a0, v, s3, flag);
            }
            q++;
        }
    }
}
