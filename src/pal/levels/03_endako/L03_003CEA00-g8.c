#include "include_asm.h"

#include "common.h"
extern f32  D_L03_001B0340 __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  math_random_int_range(s32 a0, s32 a1);
extern s32  math_random_int_below(s32 a0);
extern f32  FastAddRotations(f32 a0, f32 a1);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 D_L03_001B0350[] SDATA(D_L03_001B0350);
extern f32 D_L03_001B0648 __attribute__((sda));
extern u32 D_L03_001B3458;
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern u8  *D_L03_001B2A1C;
extern u8   g_sound_state[];
extern s32  D_L03_001B0438 __attribute__((sda));
extern f32  D_L03_001B043C __attribute__((sda));
extern s32  D_L03_001B0674 __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  point_in_path_xy(char *a0, void *a1, u32 a2);
extern f32  FastVecLength(f32 *a0);
extern f32 math_approach_target_with_direction_mode(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);

void func_PAL_L03_003CEA00(char *a0)
{
    if (*(u8 *)(a0 + 0x31) == 0) {
        return;
    }
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(u8 *)(a0 + 0xBC) = (u8)math_random_int_range(5, 10);
        if (math_random_int_below(2) != 0) {
            *(u8 *)(a0 + 0xBC) += 15;
        }
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        *(f32 *)(a0 + 0xF8) = FastAddRotations(*(f32 *)(a0 + 0xF8),
            D_L03_001B0340 * 0.0003490659f * (f32)(*(u8 *)(a0 + 0xBC) - 15));
        break;
    }
}
