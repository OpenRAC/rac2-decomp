#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern u8 *g_moby_l02_pool;
extern int g_frame_l02_counter;
extern int D_L02_001B2AAC __attribute__((sda));
extern float D_L02_001B2AA0 __attribute__((sda));
extern float D_L02_001B2AA4 __attribute__((sda));
extern float D_L02_001B2AA8 __attribute__((sda));
extern float D_L02_001B2AB0 __attribute__((sda));
extern int moby_is_state_at_least_2(u8 *);
extern int math_fast_helper_a(float *, float);
extern void moby_start_idle_anim_variant(u8 *);
extern int flag_set_first_pending(u8 *);
extern int math_random_int_below(int);
extern void anim_start_blended(u8 *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);

/* Hand-adapted from func_L11_00474920. */
extern float ref_L02_0042E988_00 __attribute__((sda));
extern float ref_L02_0042E988_01 __attribute__((sda));
extern float ref_L02_0042E988_02 __attribute__((sda));
extern int ref_L02_0042E988_03 __attribute__((sda));
extern float ref_L02_0042E988_04 __attribute__((sda));
void wandering_l02_creature_update(u8 *object) {
    float bounds[4];
    float center[4];
    int *state = *(int **)(object + 0x68);
    u8 *target;
    float level, angle, heading, delta;
    int animation;
    if (!moby_is_state_at_least_2(g_moby_l02_pool + *state * 0x100)) return;
    *(Quadword *)center = 0;
    center[0] = *(float *)(object + 0x10);
    center[1] = *(float *)(object + 0x14);
    center[2] = *(float *)(object + 0x18);
    center[3] = 5.0f;
    *(Quadword *)bounds = *(Quadword *)center;
    if (math_fast_helper_a(bounds, 255.0f) <= 0) {
        *(unsigned short *)(object + 0x32) = 0;
        return;
    }
    *(unsigned short *)(object + 0x32) = 255;
    moby_start_idle_anim_variant(object);
    target = (u8 *)(*state * 0x100 + (int)g_moby_l02_pool);
    level = *(float *)(*(u8 **)(target + 0x68) + 0x6C);
    switch (object[0x20]) {
    case 1:
        if (flag_set_first_pending(object) && object[0x43] != math_random_int_below(2)) {
            animation = math_random_int_below(2);
            anim_start_blended(object, animation, 0, 10);
        }
        if (level > ref_L02_0042E988_00 && !math_random_int_below(60)) {
            moby_set_state(object, 2, -1);
        } else if (level < ref_L02_0042E988_01 && !math_random_int_below(60)) {
            moby_set_state(object, 3, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2) + 2) {
                animation = math_random_int_below(2);
                anim_start_blended(object, animation + 2, 0, 10);
            }
            return;
        }
        if (level < ref_L02_0042E988_02 && !math_random_int_below(60)) moby_set_state(object, 1, -1);
        break;
    case 3:
        angle = ((float)(g_frame_l02_counter % ref_L02_0042E988_03) * -6.2831855f) / (float)ref_L02_0042E988_03 + 3.1415927f;
        {
            center[1] = 600.0f;
            center[0] = 500.0f;
            center[2] = 500.0f;
            center[3] = 1.0f;
            delta = *(float *)(object + 0x10) - center[0];
            heading = mat_fast_helper_a(delta, *(float *)(object + 0x14) - center[1]);
        }
        if (FastDiffRots(heading, angle) < ref_L02_0042E988_04 ||
            FastDiffRots(heading, FastAddRotations(angle, 3.1415927f)) < ref_L02_0042E988_04) {
            if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
        } else if ((object[0x60] & 2) && object[0x43] != math_random_int_below(2)) {
            animation = math_random_int_below(2);
            anim_start_blended(object, animation, 0, 10);
        }
        if (level > ref_L02_0042E988_02 && !math_random_int_below(60)) moby_set_state(object, 1, -1);
        break;
    }
}
