/* func_PAL_L07_003FD168, the PAL copy of func_L07_003F8908: the same C, where the two delays
 * each arm stores take PAL's 50 Hz scale. Those stores use struct members: as a fixed scalar
 * cannot alias a member, the scheduler moves each arm's second load above its first store. */
#include "common.h"

extern s32 ref_L07_003F8908_00(s32 a0);
extern s32 ref_L07_003F8908_01(s32 a0, s32 a1);
extern void ref_L07_003F8908_02(void *a0, s32 a1, s32 a2);
extern s32 ref_L07_003F8908_03(s32 a0);
extern s32 ref_L07_003F8908_04 __attribute__((sda));
extern s32 ref_L07_003F8908_05 __attribute__((sda));
extern s32 ref_L07_003F8908_06 __attribute__((sda));
extern s32 ref_L07_003F8908_07 __attribute__((sda));
extern s32 ref_L07_003F8908_08 __attribute__((sda));
extern s32 ref_L07_003F8908_09 __attribute__((sda));

typedef struct {
    u8 pad0[0x180];
    s32 x180;
    u8 pad184[0x41C - 0x184];
    s32 x41C;
    s32 x420;
    u8 pad424[0x438 - 0x424];
    s32 x438;
    u8 pad43C[0x444 - 0x43C];
    s32 x444;
    s32 x448;
    u8 pad44C[0x458 - 0x44C];
    s32 x458;
} Vars;

/* Picks the enemy's next action from its current phase and a random roll, and sets up the timer and handlers for it. Returns the chosen action number (PAL: 50 Hz timings). */
s32 enemy_choose_action_pal(void *moby) {
    s32 one = 1;
    Vars *vars;
    s32 action;
    s32 value;
    s32 roll;

    vars = *(Vars **)((u8 *)moby + 0x68);
    value = vars->x420;
    action = 7;
    if (value != one) {
        action = 7;
        if (value < 2) {
            if (value != 0) {
                goto state_default;
            }
        } else {
            goto state_default;
        }
        goto dispatch;
    }

    one = ref_L07_003F8908_00(0xFF) & 1;
    value = 6;
    if (one != 0) {
        action = value;
    }
    goto dispatch;

state_default:
    roll = ref_L07_003F8908_00(vars->x420 + 1);
    switch (roll) {
    case 0:
        action = 7;
        break;
    case 1:
        action = 6;
        break;
    case 2:
        if (vars->x458 != 0) {
            action = 8;
            ref_L07_003F8908_02(&vars->x458, 0, 1);
        } else {
            s32 roll_arg = 2;

            action = 6;
            roll = ref_L07_003F8908_00(roll_arg);
            value = 7;
            if (roll != 0) {
                action = value;
            }
        }
        break;
    case 3:
        action = 9;
        break;
    }

dispatch:
    switch (action) {
    case 7:
        vars->x444 = (ref_L07_003F8908_05 * 5 + 2) / 6;
        vars->x448 = (ref_L07_003F8908_08 * 5 + 2) / 6;
        vars->x438 = ref_L07_003F8908_01(3, 5);
        break;
    case 6:
        vars->x444 = (ref_L07_003F8908_04 * 5 + 2) / 6;
        vars->x448 = (ref_L07_003F8908_07 * 5 + 2) / 6;
        vars->x438 = ref_L07_003F8908_01(2, 3);
        break;
    case 8:
        vars->x438 = 1;
        vars->x41C = ref_L07_003F8908_03(vars->x180);
        break;
    case 9:
        vars->x444 = (ref_L07_003F8908_06 * 5 + 2) / 6;
        vars->x448 = (ref_L07_003F8908_09 * 5 + 2) / 6;
        vars->x438 = ref_L07_003F8908_01(1, 3);
        break;
    }
    return action;
}
