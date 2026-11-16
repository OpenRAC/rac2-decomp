#include "include_asm.h"
#include "names.h"
typedef short s16;
typedef int s32;

extern s32 g_camera_pose_table __attribute__((sda));
extern s32 g_camera_pose_target_table __attribute__((sda));
extern s32 g_selected_object_vec_table __attribute__((sda));
extern s32 g_camera_rotation_table __attribute__((sda));
extern s32 g_camera_mode_table __attribute__((sda));

extern void SetCamera5Pose(char *moby, char *a1, s32 a2, s32 a3, s32 t0);
extern void SetCamera5Mode(s32 moby, s32 a1);
extern void object_copy_vector_to_selected(char *moby);
extern void cam_set_state_rotation(char *moby);
extern s32 hero_l18_set_action(s32 moby, s32 a1);

/* Starts a timed effect sequence for the chosen entry and sets its frame counter to 1. */
void part_start_timed_sequence(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    SetCamera5Pose((char *)&g_camera_pose_table + (*(s16 *)(vars + 0xAE) << 4),
                (char *)&g_camera_pose_target_table + (*(s16 *)(vars + 0xAE) << 4), 1, 0, 0);
    SetCamera5Mode(2, *(s32 *)((char *)&g_camera_mode_table + (*(s16 *)(vars + 0xAE) << 2)));
    object_copy_vector_to_selected((char *)&g_selected_object_vec_table + (*(s16 *)(vars + 0xAE) << 4));
    cam_set_state_rotation((char *)&g_camera_rotation_table + (*(s16 *)(vars + 0xAE) << 4));
    hero_l18_set_action(0x6F, 1);
    *(s16 *)(vars + 0xAC) = 1;
}
