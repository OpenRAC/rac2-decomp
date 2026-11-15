#include "common.h"
extern float D_L18_001B1270 __attribute__((sda));
extern u16 D_L18_001B1240 __attribute__((sda)), D_L18_001B1244 __attribute__((sda));
extern u16 D_L18_001B1268 __attribute__((sda));
extern u8 D_L18_001B1248 __attribute__((sda));
extern int D_L18_001B124C __attribute__((sda)), D_L18_001B1250 __attribute__((sda));
extern u32 D_00138320[];
extern char D_L18_001B1360[];
extern float vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern void moby_step_at_own_position(void *), moby_step_at_own_position_factor(void *, float);
extern int moby_l01_turn_toward_target(void *, void *), enemy_aim_at_target(void *);
extern int FastDecTimer(short *), vec_fast_helper_a(u8 *);
extern void SetDeathBits(void *, int, int), moby_set_state(void *, int, int);
extern void moby_start_or_forward_anim(void *, int, int, float), moby_rebuild_scale_matrix(void *);
extern u8 *shooter_fire_shot(void *, int);
extern int math_random_int_range(int, int), func_001163B0(void);
extern void STUB_printf(const char *, ...);

/* Advance the shared enemy's ranged attack and its two muzzle timers. */
int shooter_update_ranged_attack(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int changed = 0;
    switch (*(short *)(object + 0xAA)) {
    case 0xEC0 /* moby class 3776 */:
        if (object[0xBC] != 1) {
            if (vec_distance_xy(object + 0x10, state + 0x220) < D_L18_001B1270)
                moby_step_at_own_position(object);
            else moby_l01_turn_toward_target(object, state + 0x220);
        } else {
            if (D_00138320[1] & 0x80) *(u16 *)(state + 0x392) = D_L18_001B1240;
            FastDecTimer((short *)(state + 0x392));
        }
        if (*(float *)(object + 0x18) < *(float *)(state + 0x90)) {
            SetDeathBits(object, 0, 3);
            changed = 1;
            moby_set_state(object, 12, -1);
        }
        enemy_aim_at_target(object);
        if (*(short *)(state + 0x392) == 0) {
            if (object[0xBC] != 1) {
                moby_rebuild_scale_matrix(object);
                changed = 1;
                *(u16 *)(state + 0x396) = D_L18_001B1244;
                moby_start_or_forward_anim(object, 2, 0, 10.0f);
                moby_set_state(object, 4, 6);
            } else changed = 1;
        }
        break;
    case 0xED4 /* moby class 3796 */:
    case MOBY_CLASS_RECEIVER_BOT:
        if (object[0xBC] != 1) {
            u8 *target = *(u8 **)(state + 0x230);
            moby_step_at_own_position_factor(object, mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(object + 0x10),
                                             *(float *)(target + 0x14) - *(float *)(object + 0x14)));
        }
        switch (object[0x42]) {
        case 10:
            if (object[0x60] & 2) {
                moby_start_or_forward_anim(object, 11, 0, 10.0f);
                *(float *)(object + 0x48) = 3.0f;
                {
                    u8 bursts = D_L18_001B1248;
                    *(short *)(state + 0x394) = 0;
                    state[0x39D] = bursts;
                }
            }
            break;
        case 11:
            if (*(short *)(object + 0xAA) == MOBY_CLASS_RECEIVER_BOT) {
                if (*(short *)(state + 0x394) % 6 == 0) {
                    shooter_fire_shot(object, 0);
                    vec_fast_helper_a(state + 0x39D);
                }
                if ((*(short *)(state + 0x394) + 3) % 6 == 0) shooter_fire_shot(object, 1);
            } else if (*(short *)(object + 0xAA) == 0xED4 /* moby class 3796 */ && *(short *)(state + 0x394) % 6 != 0) {
                shooter_fire_shot(object, 0);
                vec_fast_helper_a(state + 0x39D);
            }
            {
                int controlled = object[0xBC];
                if (controlled == 1) {
                    changed = (D_00138320[0] & 0x80) ? changed : controlled;
                } else if (state[0x39D] == 0) moby_start_or_forward_anim(object, 12, 0, 10.0f);
            }
            break;
        case 12:
            if (object[0x60] & 2) {
                changed = 1;
                {
                    int delay = math_random_int_range(D_L18_001B124C, D_L18_001B1250);
                    u16 cooldown = D_L18_001B1268;
                    *(short *)(state + 0x396) = delay;
                    *(u16 *)(state + 0x392) = cooldown;
                }
                moby_start_or_forward_anim(object, (func_001163B0() & 1) | 4, 0, 10.0f);
                moby_set_state(object, 2, 6);
            }
            break;
        }
        break;
    default:
        STUB_printf(D_L18_001B1360);
        break;
    }
    return changed;
}
