/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), 29 October 2026; retained near miss.
 * Profile: -O2 -G8 -ffunction-sections -frac2-keep-block-order
 *          -fno-schedule-insns; needs a dedicated -G8 unit.
 * USA v1.01: 176/176 bytes, 0/3 places (18, 19, 20), first reported
 * non-relocation mismatch at +0x7C. No linked build or other-release checks.
 * NOT_SDA on the absolute mode global fixes entry load allocation/scheduling.
 * A captured first-component pointer plus keep-block-order recovers the retail
 * size and comparison layout. Disabling initial scheduling gives the numbered
 * cases and shared final stores the retail FP registers.
 * The default path still loads its third component in the dispatch branch's
 * delay slot and its second component before the first store. Retail loads the
 * second component early, stores the first, then loads the third. Moving the
 * default assignments or using a restricted inner pointer does not close both
 * ordering and allocation. Three ordinary declaration/assignment variants tie.
 * Reopen with a source or aliasing witness for the default triple's lifetimes.
 */
#include "common.h"

extern s32 D_L18_001C9D40 NOT_SDA;
extern float D_L18_001B0430 __attribute__((sda));
extern float D_L18_001B0434 __attribute__((sda));
extern float D_L18_001B0438 __attribute__((sda));
extern float D_L18_001B043C __attribute__((sda));
extern float D_L18_001B0440 __attribute__((sda));
extern float D_L18_001B0444 __attribute__((sda));
extern float D_L18_001B0448 __attribute__((sda));
extern float D_L18_001B044C __attribute__((sda));
extern float D_L18_001B0450 __attribute__((sda));
extern void *func_L00_002D70A0(s32);
extern void func_L00_002D7140(void *);

void func_L18_003F9DA0(char *a0, s32 a1)
{
    char *s0 = *(char **)(a0 + 0x68);
    float f0, f1, f2;
    float *p;

    if (D_L18_001C9D40 == 0) {
        if (*(void **)(s0 + 0x80) == 0) {
            *(void **)(s0 + 0x80) = func_L00_002D70A0(5);
        } else {
            p = *(float **)(s0 + 0x80);
            switch (a1) {
            case 1:
                f0 = D_L18_001B043C;
                f1 = D_L18_001B0440;
                p[0] = f0;
                f2 = D_L18_001B0444;
                break;
            case 2:
                f0 = D_L18_001B0448;
                f1 = D_L18_001B044C;
                p[0] = f0;
                f2 = D_L18_001B0450;
                break;
            default:
                f2 = D_L18_001B0438;
                f0 = D_L18_001B0430;
                f1 = D_L18_001B0434;
                p[0] = f0;
                break;
            }
            *(float *)(*(char **)(s0 + 0x80) + 0x4) = f1;
            *(float *)(*(char **)(s0 + 0x80) + 0x8) = f2;
        }
    } else {
        func_L00_002D7140(*(void **)(s0 + 0x80));
        *(int *)(s0 + 0x80) = 0;
    }
}
