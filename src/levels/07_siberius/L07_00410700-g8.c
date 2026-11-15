#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(u8 *a, s32 b, s32 c);
extern f32 D_L07_001B17E0 __attribute__((sda));
extern f32 D_L07_001B17F0 __attribute__((sda));
extern f32 D_L07_001B1800 __attribute__((sda));
extern f32 D_L07_001B1810 __attribute__((sda));
extern f32 D_L07_001B1814;
extern f32 D_L07_001B1818;
extern f32 D_L07_001B1744 __attribute__((sda));
extern f32 D_L07_001B1748 __attribute__((sda));
extern u16 **D_L07_001A9014;
extern u8 *D_L07_001B2954;
extern s32 D_L07_001B1E90;
extern s32 g_music_state[];
extern char g_hero_position[];
extern f32 g_hero_state[];
extern void func_002A0F48(u8 *a);
extern void math_approach_target_with_braking(void *a, f32 b, f32 c, f32 d, f32 e);
extern void hero_reset_position_and_direction(void *obj, void *pos, s32 a2, s32 a3);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 vec_distance_xy(void *a, void *b);
extern void SetCamera5Pose(void *a, void *b, s32 c, s32 d, s32 e);
extern void moby_build_matrix(u8 *a);

/* Starts the second phase of the object: its two position vectors, the shared timer record, the
   effect call and the camera-facing vector, then raises bit 2 of every record of the group. */
void ship_start_second_phase(u8 *moby, s32 group)
{
    f32 lookAngles[4];
    f32 eyePos[4];
    u8 *vars;
    u16 *entry;
    u8 *record;
    f32 flatDist;
    f32 *cameraOrigin;

    moby_set_state(moby, 5, -1);
    qcopy(moby + 0x10, &D_L07_001B17E0);
    qcopy(moby + 0xF0, &D_L07_001B17F0);
    *(u16 *)(moby + 0x34) &= 0xFFFD;
    func_002A0F48(moby);
    vars = *(u8 **)(moby + 0x68);
    g_music_state[9] = (*(s32 *)(vars + 0xD4) & 0x3FFF) + 3000;
    g_music_state[10] = 0;
    math_approach_target_with_braking(vars + 0x11C, 400.0f - D_L07_001B17E0, 5.0f,
                  D_L07_001B1748 * 0.00027777778f, D_L07_001B1744 * 0.016666668f);
    *(s32 *)(vars + 0x16B0) = 0;
    *(s32 *)(vars + 0xD0) = group;
    *(f32 *)(vars + 0x16B8) = 1.0f;
    *(s32 *)(vars + 0x16BC) = 0;
    hero_reset_position_and_direction(&D_L07_001B1800, &D_L07_001B17F0, 0x6F, 1);
    *(TI128 *)eyePos = *(TI128 *)g_hero_position;
    eyePos[2] = eyePos[2] + 1.0f;
    qzero_nc(lookAngles);
    cameraOrigin = &D_L07_001B1810;
    lookAngles[2] = mat_fast_helper_a(g_hero_state[0x20] - D_L07_001B1810, g_hero_state[0x21] - D_L07_001B1814);
    flatDist = vec_distance_xy(eyePos, cameraOrigin);
    lookAngles[1] = mat_fast_helper_a(flatDist, D_L07_001B1818 - eyePos[2]);
    SetCamera5Pose(cameraOrigin, lookAngles, 1, 0, 0);
    moby_build_matrix(moby);
    for (entry = D_L07_001A9014[group];
         entry != 0 && ((s16)entry[-1] >= 0 || entry == D_L07_001A9014[group]) &&
         (record = D_L07_001B2954 + ((*entry & 0x7FFF) << 5)) != 0;
         entry++) {
        record[0x1E] |= 4;
    }
    D_L07_001B1E90 = 0;
}
