#include "names.h"
/* func_PAL_L18_003FDF30, the PAL copy of func_L18_003F9E50: the same C, where rename func_L18_002E0070 becomes func_PAL_L18_002E01E0; scale *(s32 *)((char *)&D_L18_001B04E0 + (*(s16 *)(s0 + 0xAE) << 2)). */
typedef short s16;
typedef int s32;

extern s32 g_camera_pose_table __attribute__((sda));
extern s32 g_camera_pose_target_table __attribute__((sda));
extern s32 g_selected_object_vec_table __attribute__((sda));
extern s32 g_camera_rotation_table __attribute__((sda));
extern s32 g_camera_mode_table __attribute__((sda));

extern void SetCamera5Pose(char *a0, char *a1, s32 a2, s32 a3, s32 t0);
extern void SetCamera5Mode(s32 a0, s32 a1);
extern void object_copy_vector_to_selected(char *a0);
extern void cam_set_state_rotation(char *a0);
extern s32 func_PAL_L18_002E01E0(s32 a0, s32 a1);

void func_PAL_L18_003FDF30(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);

    SetCamera5Pose((char *)&g_camera_pose_table + (*(s16 *)(s0 + 0xAE) << 4),
                (char *)&g_camera_pose_target_table + (*(s16 *)(s0 + 0xAE) << 4), 1, 0, 0);
    SetCamera5Mode(2, (((int)(*(s32 *)((char *)&g_camera_mode_table + (*(s16 *)(s0 + 0xAE) << 2))) * 5 + 2) / 6));
    object_copy_vector_to_selected((char *)&g_selected_object_vec_table + (*(s16 *)(s0 + 0xAE) << 4));
    cam_set_state_rotation((char *)&g_camera_rotation_table + (*(s16 *)(s0 + 0xAE) << 4));
    func_PAL_L18_002E01E0(0x6F, 1);
    *(s16 *)(s0 + 0xAC) = 1;
}
