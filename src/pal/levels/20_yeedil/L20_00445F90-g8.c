#include "include_asm.h"
#include "names.h"

extern float g_motion_limit_speed __attribute__((sda));
extern float g_motion_limit_accel __attribute__((sda));
extern float g_motion_limit_small_angle __attribute__((sda));
extern float g_motion_limit_angle __attribute__((sda));
extern void moby_set_controller_speed_limits(char *, float, float, float, float);

/* Sets the motion limits of a moby from four stored settings, converting them to game units. (PAL: 50 Hz scale) */
void moby_set_motion_limits_pal(char *moby) {
    moby_set_controller_speed_limits(moby, g_motion_limit_accel * 0.00040000002f,
                  g_motion_limit_speed * 0.020000001f,
                  g_motion_limit_small_angle * 6.981318e-06f,
                  g_motion_limit_angle * 0.0003490659f);
}

extern float g_motion_range_speed __attribute__((sda));
extern float g_motion_range_accel __attribute__((sda));
extern float g_motion_range_angle __attribute__((sda));
extern float g_motion_range_small_angle __attribute__((sda));

/* Sets the motion limits of a moby like the function above, and also stores an extra range value. (PAL) */
void moby_set_motion_limits_range_pal(char *moby, float chase_range) {
    char *state = *(char **)(moby + 0x68);

    moby_set_controller_speed_limits(moby, g_motion_range_accel * 0.00040000002f,
                  g_motion_range_speed * 0.020000001f,
                  g_motion_range_small_angle * 6.981318e-06f,
                  g_motion_range_angle * 0.0003490659f);
    *(float *)(state + 0x84) = chase_range;
}
