#include "common.h"

extern char *moby_get_motion_data(unsigned char *);
extern int follower_get_state(unsigned char *);
extern float g_follower_height_scale __attribute__((sda));
extern float g_follower_pull_speed __attribute__((sda));
extern float g_follower_max_scale __attribute__((sda));

/* Loads the follow speed, pull and range settings that match the follower's current state. */
void follower_load_tuning_for_state(unsigned char *owner)
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
        g_follower_height_scale = 0.416666687f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 1) {
        g_follower_height_scale = 0.400000036f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 13) {
        g_follower_height_scale = 0.400000036f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 2) {
        g_follower_height_scale = 0.13333334f;
        g_follower_pull_speed = 0.005f;
        g_follower_max_scale = 0.025f;
    } else if (state == 5) {
        g_follower_height_scale = 0.416666687f;
        g_follower_pull_speed = 0.04f;
        g_follower_max_scale = 0.2f;
    } else if (state == 6) {
        g_follower_height_scale = 0.366666675f;
        g_follower_pull_speed = 0.03f;
        g_follower_max_scale = 0.15f;
    } else if (state == 4) {
        g_follower_height_scale = 0.5f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 8) {
        g_follower_height_scale = 0.416666687f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 7) {
        g_follower_height_scale = 0.166666672f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 11) {
        g_follower_height_scale = 0.5f;
        g_follower_pull_speed = 0.02f;
        g_follower_max_scale = 0.1f;
    } else if (state == 12) {
        float *duration = *(float **)(object + 0x154);
        g_follower_height_scale = duration ? *duration * (1.0f / 60.0f) : 0.166666672f;
        g_follower_pull_speed = 0.005f;
        g_follower_max_scale = 0.025f;
    }
    if (*(int *)(object + 0x108) && state != 11 && state != 2 && state != 12) {
        g_follower_pull_speed *= 0.7f;
        g_follower_max_scale *= 0.7f;
    }
}
