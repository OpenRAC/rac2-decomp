#include "names.h"
/* func_PAL_L11_0043F9A8, the PAL copy of func_L11_0043A3F8: the same C, where the value at 0xAC and
   the four func_002B60B0 arguments take their 50 Hz values. */
#include "common.h"

extern int FloatToInt(float);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void drone_kill_with_effects_pal(char *);
extern int moby_apply_damage_to_object_pal(char *, char *, int);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
extern char g_hero_l11_position[];

/* Sets up the flying drone on its first frame, then each frame handles hits and checks whether the
   hero is very close (PAL: 50 Hz values). */
void drone_setup_and_hits_pal(char *object) {
    char *state = *(char **)(object + 0x68);

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(state + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(state + 0x4A) = FloatToInt(12.0f);
        *(float *)(state + 0x1A0) = 1.0f;
        *(unsigned char *)(state + 0x180) = 6;
        *(int *)(state + 0x1B8) = 2;
        *(float *)(state + 0x1AC) = 0.15f;
        *(float *)(state + 0x80) = 1.0f;
        *(float *)(state + 0x84) = 0.4f;
        *(float *)(state + 0x88) = 0.3f;
        *(float *)(state + 0x8C) = 0.3f;
        *(float *)(state + 0x90) = 1.5707965f;
        *(float *)(state + 0xB0) = 0.52359885f;
        *(float *)(state + 0xB4) = 2.0f;
        *(float *)(state + 0xAC) = 0.004f;
        *(int *)(state + 0x1A4) = 0;
        moby_set_controller_speed_limits(object, 0.4f, 0.40000004f,
                      0.0025132746f, 0.062831864f);
        if (*(short *)(state + 0x24) == 0) {
            *(short *)(state + 0x24) = 10;
            *(float *)(state + 0x20) = 10;
        }
        if (*(unsigned char *)(object + 0x43) != 1)
            anim_start_blended_pal(object, 1, 0, 0);
        moby_set_state(object, 1, -1);
        drone_kill_with_effects_pal(object);
    }
    if (*(unsigned char *)(object + 0x20) >= 4)
        moby_apply_damage_to_object_pal(object, state + 0x170, 0);
    if (*(unsigned char *)(object + 0x20) >= 3 &&
        *(unsigned char *)(state + 0x2E) == 2)
        drone_kill_with_effects_pal(object);
    *(int *)(state + 0x2D8) = weapon_select_aim_target(object, *(int *)(state + 0x2E8),
                                         0, 0, 255.0f, 255.0f);
    if (*(unsigned char *)(object + 0x31) != 0) {
        if (fast_vec_dist(object + 0x10, g_hero_l11_position) < 48.0f) {
            moby_update_ground_check(object);
            *(unsigned char *)(object + 0x6F) = 45;
        }
    }
}

