#include "include_asm.h"

#include "common.h"
extern float D_L11_001B12C8 __attribute__((sda));

/* Bleeds the ten rotation timers the level keeps beside its state: each armed
   entry loses a sixtieth of the shared rate and clamps at zero, disarming. */
void func_PAL_L11_0043EB58(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        u8 *armed = (u8 *)(state + 0x380 + i);
        f32 *timer = (f32 *)(state + 0x2F0 + 4 * i);
        if (*armed == 1) {
            f32 left = *timer - D_L11_001B12C8 * 0.020000001f;
            *timer = left;
            if (left < 0.0f) {
                *timer = 0.0f;
                *armed = 2;
            }
        }
    }
}
