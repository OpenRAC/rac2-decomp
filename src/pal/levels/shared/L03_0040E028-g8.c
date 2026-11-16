#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *, s32, s32);
extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern s32 math_fast_float_d(void *);
extern f32 g_slim_ship_speed __attribute__((sda));
extern f32 g_slim_ship_turn_rate __attribute__((sda));
extern f32 g_slim_ship_accel __attribute__((sda));

/* Moves the Slim Cognito ship up and down: it rises to a set height, then slowly settles back down (PAL: 50 Hz rates). */
void slim_cognito_ship_update_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        qcopy(vars, moby + 0x10);
        moby_set_state(moby, 1, -1);
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        break;
    case 2:
        math_step_value_toward_target(moby + 0x18, vars + 0x10, *(f32 *)(vars + 8), 0.0f,
                     g_slim_ship_turn_rate * 0.00040000002f,
                     g_slim_ship_accel * 0.020000001f);
        if (*(f32 *)(moby + 0x18) <= *(f32 *)(vars + 8)) {
            *(f32 *)(vars + 0x10) = 0.0f;
            if (math_fast_float_d(vars + 0x14) != 0)
                moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        ApproachValue((f32 *)(vars + 0x10),
                     g_slim_ship_accel * 0.020000001f,
                     g_slim_ship_speed * 0.00040000002f);
        *(f32 *)(moby + 0x18) += *(f32 *)(vars + 0x10);
        if (moby[0x31] == 0) {
            *(s32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
            moby_set_state(moby, 1, -1);
        }
        break;
    }
}
