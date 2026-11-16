#include "names.h"
/* func_PAL_L02_00401EC8, the PAL copy of func_L02_003FD770: the same C, where the wait is scaled to 50 Hz. */

#include "common.h"

extern char g_cutscene_camera_position[8] __attribute__((sda));
extern char g_cutscene_l02_camera_rotation[8] __attribute__((sda));
extern char g_cutscene_camera_pose_start[8] __attribute__((sda));
extern char g_cutscene_camera_pose_end[8] __attribute__((sda));
extern int g_cutscene_camera_mode_arg __attribute__((sda));

extern void vec_clear_128(void *);
extern void SetCamera5Pose(char *, char *, int, int, int);
extern void SetCamera5Mode(int, int);
extern void object_copy_vector_to_selected(char *);
extern void cam_set_state_rotation(char *);

void func_PAL_L02_00401EC8(char *a0) {
    char buf[16];
    vec_clear_128(buf);
    SetCamera5Pose(g_cutscene_camera_pose_start, g_cutscene_camera_pose_end, 1, 0, 0);
    SetCamera5Mode(2, ((s32)(g_cutscene_camera_mode_arg) * 5 + 2) / 6);
    object_copy_vector_to_selected(g_cutscene_camera_position);
    cam_set_state_rotation(g_cutscene_l02_camera_rotation);
}
