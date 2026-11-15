#include "include_asm.h"

#include "common.h"
extern f32  D_L03_001B0340 __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 D_L03_001B0350[] SDATA(D_L03_001B0350);
extern f32 D_L03_001B0648 __attribute__((sda));
extern u32 D_L03_001B3458;
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern u8  *D_L03_001B2A1C;
extern u8   g_sound_state[];
extern s32  D_L03_001B0438 __attribute__((sda));
extern f32  D_L03_001B043C __attribute__((sda));
extern s32  D_L03_001B0674 __attribute__((sda));
extern char g_hero_position[];
extern char D_L03_001B9980[];
typedef struct {
    s32 index;
    u8 pad04[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
} L03_22C8State;
typedef struct {
    u32 field00;
    u8 pad04[0xC];
} L03_22C8Entry;
extern L03_22C8Entry *D_L03_001FE700[];
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_mark_spawned(char *a0);
extern s32  point_in_path_xy(char *a0, void *a1, u32 a2);
extern void SetCamera5Pose(char *a0, char *a1, s32 a2, s32 a3, s32 a4);
extern void cam_compute_aim_and_angles(char *a0, f32 *a1, f32 *a2);
extern void FastVecSub(void *, void *, void *);
extern f32  FastVecLength(f32 *a0);
extern void math_approach_target_with_braking(f32 *a0, f32 a1, f32 a2, f32 a3, f32 a4);
extern void vec_scale_to_length(f32 *a0, f32 *a1, f32 a2);
extern void FastVecAdd(void *, void *, void *);
extern void object_copy_vector_to_selected(char *a0);
extern f32 math_approach_target_with_direction_mode(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);
extern void cam_set_state_rotation(char *a0);
extern void cam_set_mode_state(s32 a0);

void func_PAL_L03_003D6468(char *a0)
{
    L03_22C8State *s2 = *(L03_22C8State **)(a0 + 0x68);
    f32 v0[4] __attribute__((aligned(16)));
    f32 v1[4] __attribute__((aligned(16)));
    f32 v2[4] __attribute__((aligned(16)));
    f32 k;
    f32 len;
    f32 one;
    f32 k2;

    if (D_L03_001B0674 != 0) {
        return;
    }
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        moby_set_state(a0, 1, -1);
        if (s2->index == -1) {
            moby_mark_spawned(a0);
        }
        break;
    case 1:
        if (point_in_path_xy(g_hero_position, ((u8 *)D_L03_001FE700[s2->index] + 0x10), D_L03_001FE700[s2->index]->field00) != 0) {
            SetCamera5Pose(D_L03_001B9980, D_L03_001B9980 + 0x10, 1, 0, 0);
            moby_set_state(a0, 2, -1);
        }
        break;
    case 2:
        k = 0.004f;
        cam_compute_aim_and_angles(a0, v0, v1);
        one = 1.0f;
        FastVecSub(v2, v0, D_L03_001B9980);
        k2 = 0.0012566373f;
        len = FastVecLength(v2);
        math_approach_target_with_braking(&s2->f18, len, k, k, one);
        vec_scale_to_length(v2, v2, s2->f18);
        FastVecAdd(D_L03_001B9980, v2, D_L03_001B9980);
        object_copy_vector_to_selected(D_L03_001B9980);
        math_approach_target_with_direction_mode(D_L03_001B9980 + 0x14, &s2->f1C, v1[1], k2, k2, one, 0);
        math_approach_target_with_direction_mode(D_L03_001B9980 + 0x18, &s2->f20, v1[2], k2, k2, one, 0);
        cam_set_state_rotation(D_L03_001B9980 + 0x10);
        if (point_in_path_xy(g_hero_position, ((u8 *)D_L03_001FE700[s2->index] + 0x10), D_L03_001FE700[s2->index]->field00) == 0) {
            cam_set_mode_state(1);
            moby_set_state(a0, 1, -1);
        }
        break;
    }
}
