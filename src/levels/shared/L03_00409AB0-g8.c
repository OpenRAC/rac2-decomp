#include "common.h"

extern void moby_set_state(u8 *, s32, s32);
extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern s32 math_fast_float_d(void *);
extern f32 D_L03_001B1650 __attribute__((sda));
extern f32 D_L03_001B1654 __attribute__((sda));
extern f32 D_L03_001B1658 __attribute__((sda));

/* Moves the Slim Cognito ship up and down: it rises to a set height, then slowly settles back down. */
void slim_cognito_ship_update(u8 *object)
{
    u8 *vars = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        qcopy(vars, object + 0x10);
        moby_set_state(object, 1, -1);
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
        break;
    case 2:
        math_step_value_toward_target(object + 0x18, vars + 0x10, *(f32 *)(vars + 8), 0.0f,
                     D_L03_001B1654 * 0.00027777778450399637f,
                     D_L03_001B1658 * 0.01666666753590107f);
        if (*(f32 *)(object + 0x18) <= *(f32 *)(vars + 8)) {
            *(f32 *)(vars + 0x10) = 0.0f;
            if (math_fast_float_d(vars + 0x14) != 0)
                moby_set_state(object, 3, -1);
        }
        break;
    case 3:
        ApproachValue((f32 *)(vars + 0x10),
                     D_L03_001B1658 * 0.01666666753590107f,
                     D_L03_001B1650 * 0.00027777778450399637f);
        *(f32 *)(object + 0x18) += *(f32 *)(vars + 0x10);
        if (object[0x31] == 0) {
            *(s32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
            moby_set_state(object, 1, -1);
        }
        break;
    }
}
