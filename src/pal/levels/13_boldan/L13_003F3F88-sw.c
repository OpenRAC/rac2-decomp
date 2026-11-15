#include "include_asm.h"

#include "common.h"
extern f32 FastAddRotations(f32, f32);
extern s32 flag_set_first_pending(u8 *);
extern void PlayMobySound(s32, s32, u8 *);
extern void math_approach_target_with_direction_mode(f32 *, f32, u8 *, f32, f32, f32, s32);
extern void moby_set_state(u8 *, s32, s32);

void func_PAL_L13_003F3F88(u8 *a0) {
    u8 *vars = *(u8 **)(a0 + 0x68);
    u16 counter;
    s32 next_counter;
    u32 sel = a0[0x20];

    switch (sel) {
    case 0:
        a0[0x30] = 0xFF;
        *(f32 *)(vars + 8) = *(f32 *)(a0 + 0xF0);
        *(f32 *)vars = FastAddRotations(*(f32 *)(a0 + 0xF0), 0.78539824f);
        a0[0x20] = 1;
        *(u16 *)(a0 + 0x96) = 0;
        return;
    case 1:
        if (flag_set_first_pending(a0))
            PlayMobySound(0, 0, a0);
        math_approach_target_with_direction_mode((f32 *)(a0 + 0xF0), *(f32 *)vars, vars + 4, 0.0012566373f, 0.0012566373f,
                      0.12566373f, 0);
        counter = *(u16 *)(a0 + 0x96);
        if (counter < 0x79) {
            next_counter = counter + 1;
            break;
        }
        moby_set_state(a0, 3, -1);
        *(u16 *)(a0 + 0x96) = 0;
        return;
    case 3:
        if (flag_set_first_pending(a0))
            PlayMobySound(0, 0, a0);
        math_approach_target_with_direction_mode((f32 *)(a0 + 0xF0), *(f32 *)(vars + 8), vars + 4, 0.0012566373f,
                      0.0012566373f, 0.12566373f, 0);
        counter = *(u16 *)(a0 + 0x96);
        if (counter < 0x79) {
            next_counter = counter + 1;
            break;
        }
        moby_set_state(a0, 1, -1);
        *(u16 *)(a0 + 0x96) = 0;
        return;
    case 2:
    case 4:
        return;
    default:
        return;
    }
    *(u16 *)(a0 + 0x96) = next_counter;
}
