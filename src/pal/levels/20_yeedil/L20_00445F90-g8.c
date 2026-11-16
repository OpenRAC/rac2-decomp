#include "include_asm.h"
#include "names.h"

extern float g_motion_limit_speed __attribute__((sda));
extern float g_motion_limit_accel __attribute__((sda));
extern float g_motion_limit_small_angle __attribute__((sda));
extern float g_motion_limit_angle __attribute__((sda));
extern void moby_set_controller_speed_limits(char *, float, float, float, float);

void moby_set_motion_limits_pal(char *arg0) {
    moby_set_controller_speed_limits(arg0, g_motion_limit_accel * 0.00040000002f,
                  g_motion_limit_speed * 0.020000001f,
                  g_motion_limit_small_angle * 6.981318e-06f,
                  g_motion_limit_angle * 0.0003490659f);
}

extern float g_motion_range_speed __attribute__((sda));
extern float g_motion_range_accel __attribute__((sda));
extern float g_motion_range_angle __attribute__((sda));
extern float g_motion_range_small_angle __attribute__((sda));

void moby_set_motion_limits_range_pal(char *arg0, float f) {
    char *state = *(char **)(arg0 + 0x68);

    moby_set_controller_speed_limits(arg0, g_motion_range_accel * 0.00040000002f,
                  g_motion_range_speed * 0.020000001f,
                  g_motion_range_small_angle * 6.981318e-06f,
                  g_motion_range_angle * 0.0003490659f);
    *(float *)(state + 0x84) = f;
}
