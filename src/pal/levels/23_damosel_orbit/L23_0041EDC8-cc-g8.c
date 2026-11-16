#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int g_shield_fade_state __attribute__((sda));

extern int g_shield_fade_frames __attribute__((sda));

extern float g_shield_fade_time_scale __attribute__((sda));

extern int g_shield_fade_counter;

extern int g_shield_saved_value_a __attribute__((sda));

extern int g_shield_saved_value_b __attribute__((sda));

extern int g_shield_fade_param_a;

extern int g_shield_fade_param_b;

extern void AttachManipulator(char *, int, char *);

extern void FastVecScale(char *, char *, float);

extern void build_axis_rotation_quaternion(void *, int, float);

/* func_PAL_L23_0041EDC8, the PAL copy of func_L23_00419D60: the same C, with the two durations scaled for 50 Hz. */
/* Advances the three-phase transition and updates its state vectors. */
void mothership_update_shield_fade_pal(char *shield_moby) {
    char *state = *(char **)(shield_moby + 0x68);
    float scale;
    float active_fade, inactive_fade, active_duration, inactive_duration;
    union {
        TI128 q;
        float f[4];
    } axis;

    if ((unsigned char)(*(unsigned char *)(shield_moby + 0x20) - 8) < 3) {
        scale = 0.0f;
        if (g_shield_fade_state == 0) {
            g_shield_fade_state = 1;
            g_shield_fade_counter = g_shield_fade_frames;
        } else if (g_shield_fade_state != 2) {
            if (*(unsigned char *)(state + 0x471) == 0)
                AttachManipulator(shield_moby, 0x26, state + 0x470);
            axis.q = 0;
            axis.f[2] = 1.0f;
            axis.f[3] = 1.0f;
            scale = (float)(g_shield_fade_frames - g_shield_fade_counter) * g_shield_fade_time_scale;
            FastVecScale(state + 0x4A0, (char *)&axis, scale);
            g_shield_fade_counter = g_shield_fade_counter - 1;
            if (g_shield_fade_counter == -1)
                g_shield_fade_state = 2;
        } else {
            g_shield_fade_counter = g_shield_fade_frames;
            if (*(unsigned char *)(state + 0x471) == 0)
                AttachManipulator(shield_moby, 0x26, state + 0x470);
            axis.q = 0;
            axis.f[2] = 1.0f;
            axis.f[3] = 1.0f;
            scale = (float)g_shield_fade_frames * g_shield_fade_time_scale;
            FastVecScale(state + 0x4A0, (char *)&axis, scale);
            if (*(unsigned char *)(state + 0x4B1) == 0)
                AttachManipulator(shield_moby, 0x27, state + 0x4B0);
            *(float *)(state + 0x578) = 1.4726216f;
            build_axis_rotation_quaternion(state + 0x4C0, 1, 1.4726216f);
        }
        qzero_nc(state + 0x480);
        active_duration = g_shield_fade_time_scale * (float)g_shield_fade_frames * 4.0f;
        *(unsigned char *)(state + 0x473) = 1;
        *(float *)(state + 0x47C) = 1.0f;
        *(float *)(state + 0x48C) = 1.0f;
        *(float *)(state + 0x49C) = 1.0f;
        active_fade = 1.0f - scale / active_duration;
        *(float *)(state + 0x498) = active_fade;
        *(float *)(state + 0x494) = active_fade;
        *(float *)(state + 0x490) = active_fade;
    } else if (g_shield_fade_state != 0) {
        if (*(unsigned char *)(state + 0x471) == 0)
            AttachManipulator(shield_moby, 0x26, state + 0x470);
        axis.q = 0;
        axis.f[2] = 1.0f;
        axis.f[3] = 1.0f;
        scale = (float)g_shield_fade_counter * g_shield_fade_time_scale;
        FastVecScale(state + 0x4A0, (char *)&axis, scale);
        g_shield_fade_counter = g_shield_fade_counter - 1;
        if (g_shield_fade_counter == -1) {
            g_shield_fade_state = 0;
            g_shield_fade_param_a = ((s32)(g_shield_saved_value_a) * 5 + 2) / 6;
            g_shield_fade_param_b = ((s32)(g_shield_saved_value_b) * 5 + 2) / 6;
        }
        qzero_nc(state + 0x480);
        inactive_duration = g_shield_fade_time_scale * (float)g_shield_fade_frames;
        *(unsigned char *)(state + 0x473) = 1;
        *(float *)(state + 0x47C) = 1.0f;
        *(float *)(state + 0x48C) = 1.0f;
        *(float *)(state + 0x49C) = 1.0f;
        inactive_fade = 1.0f - scale / (inactive_duration * 2.0f);
        *(float *)(state + 0x498) = inactive_fade;
        *(float *)(state + 0x494) = inactive_fade;
        *(float *)(state + 0x490) = inactive_fade;
    }
}
