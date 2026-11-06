#include "common.h"

/* func_PAL_L12_00418E80, the PAL copy of func_L12_00413F68: the same C, with the three
   timer values scaled to 50 Hz. */

extern s32 D_L12_001B1838 __attribute__((sda));

extern s32 D_L12_001B183C __attribute__((sda));

extern s32 D_L12_001B1840 __attribute__((sda));

extern s32 D_L12_001B1834 __attribute__((sda));

extern f32 D_L12_001B1858 __attribute__((sda));

extern s32 func_2F15C8(void *arg0);

extern s32 func_31E2E0(s32 arg0, s32 arg1);

extern void func_3296A8(void *arg0, void *arg1, s32 arg2, f32 x, s32 arg3);

/* Steps the measured slot timer and restarts the tracked sub-object. */
void func_PAL_L12_00418E80(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    if (*(u8 *)(state + 0x2EA) != 0) {
        *(u8 *)(state + 0x2EA) = 0;
        if (*(s16 *)(state + 0x2E0) < (D_L12_001B1838 * 5 + 2) / 6)
            *(u16 *)(state + 0x2E0) = ((s32)(func_31E2E0(D_L12_001B183C, D_L12_001B1840)) * 5 + 2) / 6;
    }
    if (func_2F15C8(state + 0x2E0) == 0)
        *(u16 *)(state + 0x2E8) = (D_L12_001B1834 * 5 + 2) / 6;
    func_2F15C8(state + 0x2E2);
    func_2F15C8(state + 0x2E6);
    func_2F15C8(state + 0x2E8);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
    func_3296A8(*(void **)(state + 0x2F8), state + 0x420, 3, D_L12_001B1858, 1);
}
