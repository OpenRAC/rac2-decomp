#include "common.h"
extern float g_lift_travel_height __attribute__((sda));
extern float g_lift_rise_frames __attribute__((sda));
extern float g_lift_lower_frames __attribute__((sda));
extern float g_lift_trigger_distance __attribute__((sda));
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float vec_distance_xy(void *, void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern int PlayMobySound(int, int, void *);
typedef struct { u8 *other; float angle, height, time; } LiftState;
/* func_PAL_L19_00423BC8, the PAL copy of func_L19_0041E5B0: the same C, where each timer's rate
   is scaled for 50 Hz. Lowers and rotates the lift, waits for the linked object to leave, then resets it. */
void grelbin_lift_update_pal(u8 *moby)
{
    LiftState *lift = *(LiftState **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0: {
        float angle, height;
        lift->other = 0;
        lift->angle = *(float *)(moby + 0xF8);
        lift->height = *(float *)(moby + 0x18);
        angle = FastAddRotations(*(float *)(moby + 0xF8), 3.1415927f);
        height = *(float *)(moby + 0x18) - g_lift_travel_height;
        *(float *)(moby + 0xF8) = angle;
        *(float *)(moby + 0x18) = height;
        moby_set_state(moby, 1, -1);
        break;
    }
    case 1:
        if (lift->other && lift->other[0x20] != 0xFE && lift->other[0x20] != 0xFD) {
            lift->time = 0;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) PlayMobySound(0, 0, moby);
        lift->time += 1.0f / ((g_lift_rise_frames * 5.0f + 2.0f) * 0.16666667f);
        if (lift->time > 1.0f) {
            lift->time = 0;
            *(float *)(moby + 0x18) = lift->height;
            moby[0xBC] = 1;
            moby_set_state(moby, 3, -1);
        } else {
            float ease = (math_fast_sin_or_cos_a(lift->time * 3.1415927f) + 1.0f) * 0.5f;
            if (ease > 1.0f) ease = 1.0f;
            else if (ease < 0.0f) ease = 0.0f;
            *(float *)(moby + 0x18) = lift->height - ease * g_lift_travel_height;
        }
        break;
    case 3:
        lift->time += 1.0f / ((g_lift_lower_frames * 5.0f + 2.0f) * 0.16666667f);
        if (lift->time > 1.0f) {
            lift->time = 0;
            *(float *)(moby + 0xF8) = lift->angle;
            moby[0xBC] = 2;
            moby_set_state(moby, 4, -1);
        } else {
            float ease = (math_fast_sin_or_cos_a(lift->time * 3.1415927f) + 1.0f) * 0.5f;
            *(float *)(moby + 0xF8) = FastAddRotations(lift->angle, ease * 3.1415927f);
        }
        break;
    case 4:
        if (!lift->other || lift->other[0x20] == 0xFE || lift->other[0x20] == 0xFD ||
            vec_distance_xy(moby + 0x10, lift->other + 0x10) > g_lift_trigger_distance) {
            moby[0xBC] = 3;
            lift->other = 0;
            lift->time = 1.0f;
            moby_set_state(moby, 5, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) PlayMobySound(1, 0, moby);
        lift->time -= 1.0f / ((g_lift_lower_frames * 5.0f + 2.0f) * 0.16666667f);
        if (lift->time <= 0.0f) {
            lift->time = 1.0f;
            *(float *)(moby + 0xF8) = FastAddRotations(lift->angle, 3.1415927f);
            moby_set_state(moby, 6, -1);
        } else {
            float ease = (math_fast_sin_or_cos_a(lift->time * 3.1415927f) + 1.0f) * 0.5f;
            *(float *)(moby + 0xF8) = FastAddRotations(lift->angle, ease * 3.1415927f);
        }
        break;
    case 6:
        lift->time -= 1.0f / ((g_lift_rise_frames * 5.0f + 2.0f) * 0.16666667f);
        if (lift->time <= 0.0f) {
            float height = lift->height - g_lift_travel_height;
            lift->time = 0;
            moby[0xBC] = 0;
            *(float *)(moby + 0x18) = height;
            moby_set_state(moby, 1, -1);
        } else {
            float ease = (math_fast_sin_or_cos_a(lift->time * 3.1415927f) + 1.0f) * 0.5f;
            if (ease > 1.0f) ease = 1.0f;
            else if (ease < 0.0f) ease = 0.0f;
            *(float *)(moby + 0x18) = lift->height - ease * g_lift_travel_height;
        }
        break;
    }
}
