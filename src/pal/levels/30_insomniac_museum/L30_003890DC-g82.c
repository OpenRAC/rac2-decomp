#include "include_asm.h"

#include "common.h"
extern float D_L30_001AEE90 __attribute__((sda));
extern float D_L30_001AEE94 __attribute__((sda));
extern char D_L30_001AEE98[];
extern void STUB_printf(const char *, ...);
extern void func_001163A0(unsigned int);
extern int math_random_int_below(int);
extern void moby_set_state(u8 *, int, int);
extern void math_update_wrapped_angle_offset(u8 *, u8 *, u8 *, float, float, float);
extern float FastAddRotations(float, float);

/* Steps one record: with the state byte clear it copies the record's own angle into the
   state block, and once the state index reaches thirteen it redraws the record with a fresh
   random duration, a timer sample and the state block's new bit mask. With the state byte
   set it folds the shared angle words into the record and the state block instead, and
   counts the frame in the record's halfword at 0x96. */
void func_PAL_L30_003890DC(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 v;

    if (*(u8 *)(object + 0x20) == 0) {
        float f = *(float *)(object + 0x18);
        unsigned int w = *(unsigned int *)state;

        *(float *)(state + 0xC) = f;
        if (w >= 13) {
            short a1 = *(short *)(object + 0xAA);
            short a2 = *(short *)(object + 0xB2);
            unsigned int ticks = T1_COUNT;

            STUB_printf(D_L30_001AEE98, a1, a2);
            func_001163A0(ticks);
            *(int *)state = math_random_int_below(13);
        }
        *(u16 *)(object + 0x7C) = 1 << *(int *)state;
        moby_set_state(object, 1, -1);
    } else {
        float f0 = D_L30_001AEE94;

        math_update_wrapped_angle_offset(object, state + 4, state + 8, D_L30_001AEE90,
                      f0 * 0.0003490659f, *(float *)(state + 0xC));
        *(float *)(object + 0xF8) =
            FastAddRotations(*(float *)(object + 0xF8), 0.01745329424738884f);
        *(u16 *)(object + 0x96) = 0;
    }
    v = *(u16 *)(object + 0x96);
    *(u16 *)(object + 0x96) = v + 1;
}
