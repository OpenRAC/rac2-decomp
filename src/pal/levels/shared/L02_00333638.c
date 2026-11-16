#include "include_asm.h"
#include "names.h"

extern void *moby_get_vars_word_18(char *moby);
extern int moby_step_controller(void *moby, void *target, float step_param);
extern void *moby_get_vars_word_18(char *moby);
extern void *moby_get_vars_word_18(char *moby);

/* Set the record's fields for the call, then put the old ones back. */
int moby_move_to_target_temp_limits_pal(void *moby, void *target, int flag_mask, float step_param, float max_speed, float accel) {
    char *controller;
    int old_flags;
    float old_max_speed;
    float old_accel;
    int result;

    controller = (char *)moby_get_vars_word_18((char *)moby);
    if (controller == 0)
        return 8;
    old_flags = *(int *)(controller + 0x38);
    old_max_speed = *(float *)(controller + 0x28);
    *(int *)(controller + 0x38) = flag_mask;
    if (0.0f < max_speed)
        *(float *)(controller + 0x28) = max_speed;
    old_accel = *(float *)(controller + 0x20);
    if (0.0f < accel)
        *(float *)(controller + 0x20) = accel;
    result = moby_step_controller(moby, target, step_param);
    *(int *)(controller + 0x38) = old_flags;
    *(float *)(controller + 0x28) = old_max_speed;
    *(float *)(controller + 0x20) = old_accel;
    return result;
}

