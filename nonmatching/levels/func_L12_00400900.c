/* Nonmatching reconstruction. Profile: -O2 -G0 -ffunction-sections -frac2-no-null-pointer-checks.
 * Compiled 524 bytes; retail 552 bytes.
 * USA v1.01, PAL and USA v2.00: 0/3 places per release; no carrying absence.
 * No strict linked qualification. The compiler folds signed and unsigned byte lifetimes that retail keeps separate. The null-pointer pass opt-out and explicit real unsigned captures tied at 524 bytes; no extra reads or volatile steering are introduced. Reopen with a documented optimization-pass explanation.
 */
#include "common.h"
extern char *D_L12_001B2E9C[] __attribute__((sda));

void func_L12_00400900(int index, unsigned char *control, int apply)
{
    char *object = D_L12_001B2E9C[0] + (index << 8);
    char *state;
    unsigned char saved;
    if (object) {
        if (apply) {
            if (*(signed char *)(control + 0x7C) > 0)
                *(unsigned short *)(object + 0x34) &= 0xFFFD;
            else if (*(signed char *)(control + 0x7C) < 0)
                *(unsigned short *)(object + 0x34) |= 2;
            saved = control[0x7D];
            if (*(signed char *)(control + 0x7D) > 0) {
                if (!object || !(state = *(char **)(object + 0x24)) || *(short *)(state + 0x46) != 0x12) {
                    object[0x31] = 1;
                    *(unsigned short *)(object + 0x34) &= 0xFFFE;
                }
            } else if ((signed char)saved < 0) {
                if (!object || !(state = *(char **)(object + 0x24)) || *(short *)(state + 0x46) != 0x12) {
                    object[0x31] = 0;
                    *(unsigned short *)(object + 0x34) |= 1;
                }
            }
            saved = control[0x7F];
            if (*(signed char *)(control + 0x7F) > 0) {
                state = *(char **)(object + 0x24);
                if (state)
                    *(int *)(object + 0x98) = *(int *)(state + 0x10);
            } else if ((signed char)saved < 0) {
                if (*(char **)(object + 0x24))
                    *(int *)(object + 0x98) = 0;
            }
        } else {
            saved = control[0x7C];
            if (*(signed char *)(control + 0x7C) > 0) {
                state = *(char **)(object + 0x24);
                if (!state || *(short *)(state + 0x46) != 0x12)
                    *(unsigned short *)(object + 0x34) |= 2;
            } else if ((signed char)saved < 0) {
                if (!object || !(state = *(char **)(object + 0x24)) || *(short *)(state + 0x46) != 0x12)
                    *(unsigned short *)(object + 0x34) &= 0xFFFD;
            }
            saved = control[0x7D];
            if (*(signed char *)(control + 0x7D) > 0) {
                if (!object || !(state = *(char **)(object + 0x24)) || *(short *)(state + 0x46) != 0x12) {
                    object[0x31] = 0;
                    *(unsigned short *)(object + 0x34) |= 1;
                }
            } else if ((signed char)saved < 0) {
                if (!object || !(state = *(char **)(object + 0x24)) || *(short *)(state + 0x46) != 0x12) {
                    object[0x31] = 1;
                    *(unsigned short *)(object + 0x34) &= 0xFFFE;
                }
            }
            if (*(signed char *)(control + 0x7F) > 0) {
                if (*(char **)(object + 0x24))
                    *(int *)(object + 0x98) = 0;
            } else if (*(signed char *)(control + 0x7F) < 0) {
                state = *(char **)(object + 0x24);
                *(int *)(object + 0x98) = *(int *)(state + 0x10);
            }
        }
    }
}
