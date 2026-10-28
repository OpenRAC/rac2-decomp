/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L01_003907B8.c
 * Game profile: -O2 -G0 -ffunction-sections
 * Compiled/retail bytes: 524/552. US: 0/13; US2: 0/13; PAL: 0/13.
 * Residual and reopening condition: Signed-byte reloads, sign-extension temporaries and return-tail sharing remain different. Default G0, G8-equivalent source and disabling the null-pointer pass did not recover the missing seven instructions. Reopen with the original inline-helper and byte-view contracts.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

extern char *D_L01_001B255C ;

void func_L01_003907B8(int index, unsigned char *state, int enabled)
{
    char *object = D_L01_001B255C + index * 256;
    char *info;
    if (object != 0) {
        if (enabled) {
            if ((signed char)state[0x7C] > 0)
                *(unsigned short *)(object + 0x34) &= ~2;
            else if ((signed char)state[0x7C] < 0)
                *(unsigned short *)(object + 0x34) |= 2;
            if ((signed char)state[0x7D] > 0) {
                if (object == 0 || *(char **)(object + 0x24) == 0 ||
                    *(short *)(*(char **)(object + 0x24) + 0x46) != 18) {
                    object[0x31] = 1;
                    *(unsigned short *)(object + 0x34) &= ~1;
                }
            } else if ((signed char)state[0x7D] < 0) {
                if (object == 0 || *(char **)(object + 0x24) == 0 ||
                    *(short *)(*(char **)(object + 0x24) + 0x46) != 18) {
                    object[0x31] = 0;
                    *(unsigned short *)(object + 0x34) |= 1;
                }
            }
            if ((signed char)state[0x7F] > 0) {
                info = *(char **)(object + 0x24);
                if (info != 0)
                    *(int *)(object + 0x98) = *(int *)(info + 0x10);
            } else if ((signed char)state[0x7F] < 0) {
                if (*(char **)(object + 0x24) != 0)
                    *(int *)(object + 0x98) = 0;
            }
        } else {
            if ((signed char)state[0x7C] > 0) {
                if (*(char **)(object + 0x24) == 0 ||
                    *(short *)(*(char **)(object + 0x24) + 0x46) != 18)
                    *(unsigned short *)(object + 0x34) |= 2;
            } else if ((signed char)state[0x7C] < 0) {
                if (object == 0 || *(char **)(object + 0x24) == 0 ||
                    *(short *)(*(char **)(object + 0x24) + 0x46) != 18)
                    *(unsigned short *)(object + 0x34) &= ~2;
            }
            if ((signed char)state[0x7D] > 0) {
                if (object == 0 || *(char **)(object + 0x24) == 0 ||
                    *(short *)(*(char **)(object + 0x24) + 0x46) != 18) {
                    object[0x31] = 0;
                    *(unsigned short *)(object + 0x34) |= 1;
                }
            } else if ((signed char)state[0x7D] < 0) {
                if (object == 0 || *(char **)(object + 0x24) == 0 ||
                    *(short *)(*(char **)(object + 0x24) + 0x46) != 18) {
                    object[0x31] = 1;
                    *(unsigned short *)(object + 0x34) &= ~1;
                }
            }
            if ((signed char)state[0x7F] > 0) {
                if (*(char **)(object + 0x24) != 0)
                    *(int *)(object + 0x98) = 0;
            } else if ((signed char)state[0x7F] < 0) {
                info = *(char **)(object + 0x24);
                *(int *)(object + 0x98) = *(int *)(info + 0x10);
            }
        }
    }
}
