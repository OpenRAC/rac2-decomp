#include "include_asm.h"
#include "names.h"

typedef unsigned short u16;

typedef int s32;

extern s32 g_cam_follow_index __attribute__((sda));

extern s32 g_cam_prev_follow_index __attribute__((sda));

extern s32 g_cam_boost_timer __attribute__((sda));

extern float g_cam_offset_x __attribute__((sda));

extern float g_cam_offset_y __attribute__((sda));

extern float g_cam_offset_z __attribute__((sda));

extern float g_cam_offset_w __attribute__((sda));

extern s32 g_cam_side_flip __attribute__((sda));

extern float func_30EEF8(char *);

extern void cam_update_follow_placement(char *);


/* Arm one queue entry: seed its timers, scale them when it repeats, and start it. */
void cam_reset_follow_state(char *camera)
{
    char *cameraCopy = camera;

    cam_init_follow_offset(cameraCopy, 0);
    *(u16 *)(cameraCopy + 0x7E) = 0;
    g_cam_follow_index = -1;
    g_cam_prev_follow_index = -1;
    g_cam_boost_timer = -1;
}
