#include "include_asm.h"

#include "common.h"
extern float g_museum_look_angle_rate __attribute__((sda));
extern float g_museum_look_param __attribute__((sda));
extern char g_str_museum_look_debug[];
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
void museum_look_state_update_pal(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 frame_count;

    if (*(u8 *)(object + 0x20) == 0) {
        float angle = *(float *)(object + 0x18);
        unsigned int state_index = *(unsigned int *)state;

        *(float *)(state + 0xC) = angle;
        if (state_index >= 13) {
            short value_a = *(short *)(object + 0xAA);
            short value_b = *(short *)(object + 0xB2);
            unsigned int ticks = T1_COUNT;

            STUB_printf(g_str_museum_look_debug, value_a, value_b);
            func_001163A0(ticks);
            *(int *)state = math_random_int_below(13);
        }
        *(u16 *)(object + 0x7C) = 1 << *(int *)state;
        moby_set_state(object, 1, -1);
    } else {
        float look_param = g_museum_look_param;

        math_update_wrapped_angle_offset(object, state + 4, state + 8, g_museum_look_angle_rate,
                      look_param * 0.0003490659f, *(float *)(state + 0xC));
        *(float *)(object + 0xF8) =
            FastAddRotations(*(float *)(object + 0xF8), 0.01745329424738884f);
        *(u16 *)(object + 0x96) = 0;
    }
    frame_count = *(u16 *)(object + 0x96);
    *(u16 *)(object + 0x96) = frame_count + 1;
}
