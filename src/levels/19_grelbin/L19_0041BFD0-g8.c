#include "common.h"

extern void moby_set_state(void *, int, int);
extern int g_active_yeti_count __attribute__((sda));
extern int g_frame_l19_counter;
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_random_signed_float_range(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void anim_start_blended(void *, int, int, int);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void group_mark_entities(void *);
extern int weapon_select_aim_target(void *, int, float, float, void *, int);

/* Sets up a Y.E.T.I. on its first frame (speed, turning and size). Returns 1 when the Y.E.T.I. is done and should be removed. */
int yeti_init_stats(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    if (*(u8 *)(moby + 0x20) == 0) {
        g_active_yeti_count = 0;
        *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(14.4f);
        *(u8 *)(vars + 0x29) = 1;
        if (math_random_int_below(2)) *(u16 *)(moby + 0x34)|=0x8000;
        *(float *)(moby + 0x2C)*=1.45f;
        *(float *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34)|1)&0xEFFF;
        *(u8 *)(moby + 0x31) = 0;
        *(int *)(moby + 0x98) = 0;
        *(int *)(vars + 0x268) = 0;
        *(float *)(vars + 0x270) = math_random_signed_float_range(5.0f, 25.0f)*0.0174532942474f;
        qcopy(vars + 0x210, moby + 0x10);
        *(u8 *)(vars + 0x150) = 25;
        *(int *)(vars + 0x188) = 3;
        *(u8 *)(vars + 0x156) = 9;
        *(u8 *)(vars + 0x151) = 14;
        *(float *)(vars + 0x17C) = 0.15f;
        *(float *)(vars + 0x30) = 1.5f;
        *(float *)(vars + 0x170) = 0.5f;
        *(float *)(vars + 0x174) = 0.5f;
        *(u8 *)(vars + 0x1B7) = 1;
        *(u8 *)(vars + 0x2E) = 1;
        if (*(short *)(vars + 0x24) == 0) {
            *(short *)(vars + 0x24) = 1;
            *(float *)(vars + 0x20) = 1.0f;
        }
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x54) = 0.8f;
        *(float *)(vars + 0x50) = 1.0f;
        *(float *)(vars + 0x58) = 0.75f;
        *(float *)(vars + 0x5C) = 0.75f;
        *(float *)(vars + 0x60) = 1.57079648972f;
        *(float *)(vars + 0x80) = 0.52359885f;
        moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.00698131788522f, 0.8377582f);
        moby_set_state(moby, 1, 0);
        if (*(u8 *)(moby + 0x43) != 12) anim_start_blended(moby, 12, 0, 0);
    }
    if (*(u8 *)(vars + 0x2E) == 2) {
        g_active_yeti_count--;
        return 1;
    }
    if (moby_apply_damage_to_object(moby, vars + 0x140, 0)) group_mark_entities(moby);
    if (g_frame_l19_counter >= 6) {
        *(int *)(vars + 0x278) = weapon_select_aim_target(moby, *(int *)(vars + 0x228), *(float *)(vars + 0x22C), 10.0f, vars + 0x210, 0);
        *(int *)(vars + 0x27C) = weapon_select_aim_target(moby, *(int *)(vars + 0x220), *(float *)(vars + 0x224), 10.0f, vars + 0x210, 0);
    }
    return 0;
}
