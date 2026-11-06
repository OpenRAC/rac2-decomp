/* func_PAL_L09_00408090, the PAL copy of func_L09_004031D8: the same C, where D_L09_001B13C0 is read as
   a word and scaled to 50 Hz, both in the test and in the store to 0x26C. */
#include "common.h"

extern s32 D_L09_001B13C0 __attribute__((sda));
extern void func_2EA110(char *p);

void func_PAL_L09_00408090(char *a0) {
    char *s1 = a0;
    char *s0 = *(char **)(s1 + 0x68);
    u16 n;
    if (*(s16 *)(s0 + 0x270) != 0
        || (*(s32 *)(s0 + 0x234) == 1
            && *(s16 *)(s0 + 0x26C) < ((s32)(D_L09_001B13C0 / 2) * 5 + 2) / 6)) {
        *(u16 *)(s0 + 0x26C) = ((s32)(D_L09_001B13C0) * 5 + 2) / 6;
        *(s16 *)(s0 + 0x270) = 0;
    }
    func_2EA110(s0 + 0x26C);
    func_2EA110(s0 + 0x26E);
    n = *(u16 *)(s1 + 0x96);
    if (n < 0xFFFF) {
        *(u16 *)(s1 + 0x96) = n + 1;
    }
}
