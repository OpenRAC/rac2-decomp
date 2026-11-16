#include "names.h"
/* func_PAL_002EF2D8, the PAL copy of func_002EE3B0: the same C, with the 60 Hz values scaled by 6/5
 * for 50 Hz and both rates multiplied by 1.2f at the end. */
#include "common.h"

extern char *moby_get_motion_data(unsigned char *);
extern int follower_get_state(unsigned char *);
extern float g_follower_height_scale __attribute__((sda));
extern float g_follower_pull_speed __attribute__((sda));
extern float g_follower_max_scale __attribute__((sda));

/* Loads the follow speed, pull and range settings that match the follower's current state (PAL: scaled for 50 Hz). */
void follower_load_tuning_for_state_pal(unsigned char *owner)
{
    char *object = moby_get_motion_data(owner);
    int state;

    if (!object)
        return;
    if (*(unsigned char **)(object + 0x10))
        state = follower_get_state(*(unsigned char **)(object + 0x10));
    else
        state = follower_get_state(owner);
    if (state == 3) {
        g_follower_height_scale = 0.50000006f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 1) {
        g_follower_height_scale = 0.48000002f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 13) {
        g_follower_height_scale = 0.48000002f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 2) {
        g_follower_height_scale = 0.16000001f;
        g_follower_pull_speed = 0.005f;
        g_follower_max_scale = 0.025f;
    } else if (state == 5) {
        g_follower_height_scale = 0.50000006f;
        g_follower_pull_speed = 0.04f;
        g_follower_max_scale = 0.2f;
    } else if (state == 6) {
        g_follower_height_scale = 0.44000003f;
        g_follower_pull_speed = 0.03f;
        g_follower_max_scale = 0.15f;
    } else if (state == 4) {
        g_follower_height_scale = 0.6f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 8) {
        g_follower_height_scale = 0.50000006f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 7) {
        g_follower_height_scale = 0.20000002f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 11) {
        g_follower_height_scale = 0.6f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 12) {
        float *duration = *(float **)(object + 0x154);
        g_follower_height_scale = duration ? *duration * 0.020000001f : 0.20000002f;
        g_follower_pull_speed = 0.005f;
        g_follower_max_scale = 0.025f;
    }
    if (*(int *)(object + 0x108) && state != 11 && state != 2 && state != 12) {
        g_follower_pull_speed *= 0.7f;
        g_follower_max_scale *= 0.7f;
    }
    g_follower_pull_speed *= 1.2f;
    g_follower_max_scale *= 1.2f;
}
