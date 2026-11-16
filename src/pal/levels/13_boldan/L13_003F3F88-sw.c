#include "include_asm.h"

#include "common.h"
extern f32 FastAddRotations(f32, f32);
extern s32 flag_set_first_pending(u8 *);
extern int PlayMobySound(s32, s32, u8 *);
extern f32 math_approach_target_with_direction_mode(f32 *, f32, u8 *, f32, f32, f32, s32);
extern void moby_set_state(u8 *, s32, s32);

/* Swings the object between two angles, pausing 120 frames at each end, with a sound at each swing (PAL: counts the same frames). */
void swinging_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 frame_count;
    s32 next_frame_count;
    u32 state = moby[0x20];

    switch (state) {
    case 0:
        moby[0x30] = 0xFF;
        *(f32 *)(vars + 8) = *(f32 *)(moby + 0xF0);
        *(f32 *)vars = FastAddRotations(*(f32 *)(moby + 0xF0), 0.78539824f);
        moby[0x20] = 1;
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 1:
        if (flag_set_first_pending(moby))
            PlayMobySound(0, 0, moby);
        math_approach_target_with_direction_mode((f32 *)(moby + 0xF0), *(f32 *)vars, vars + 4, 0.0012566373f, 0.0012566373f,
                      0.12566373f, 0);
        frame_count = *(u16 *)(moby + 0x96);
        if (frame_count < 0x79) {
            next_frame_count = frame_count + 1;
            break;
        }
        moby_set_state(moby, 3, -1);
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 3:
        if (flag_set_first_pending(moby))
            PlayMobySound(0, 0, moby);
        math_approach_target_with_direction_mode((f32 *)(moby + 0xF0), *(f32 *)(vars + 8), vars + 4, 0.0012566373f,
                      0.0012566373f, 0.12566373f, 0);
        frame_count = *(u16 *)(moby + 0x96);
        if (frame_count < 0x79) {
            next_frame_count = frame_count + 1;
            break;
        }
        moby_set_state(moby, 1, -1);
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 2:
    case 4:
        return;
    default:
        return;
    }
    *(u16 *)(moby + 0x96) = next_frame_count;
}
