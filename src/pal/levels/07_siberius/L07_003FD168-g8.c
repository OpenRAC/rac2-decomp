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

s32 func_PAL_L07_003FD168(void *arg0) {
    s32 one = 1;
    Vars *temp_s0;
    s32 var_s1;
    s32 temp_v1;
    s32 temp_v0;

    temp_s0 = *(Vars **)((u8 *)arg0 + 0x68);
    temp_v1 = temp_s0->x420;
    var_s1 = 7;
    if (temp_v1 != one) {
        var_s1 = 7;
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                goto state_default;
            }
        } else {
            goto state_default;
        }
        goto dispatch;
    }

    one = ref_L07_003F8908_00(0xFF) & 1;
    temp_v1 = 6;
    if (one != 0) {
        var_s1 = temp_v1;
    }
    goto dispatch;

state_default:
    temp_v0 = ref_L07_003F8908_00(temp_s0->x420 + 1);
    switch (temp_v0) {
    case 0:
        var_s1 = 7;
        break;
    case 1:
        var_s1 = 6;
        break;
    case 2:
        if (temp_s0->x458 != 0) {
            var_s1 = 8;
            ref_L07_003F8908_02(&temp_s0->x458, 0, 1);
        } else {
            s32 arg0 = 2;

            var_s1 = 6;
            temp_v0 = ref_L07_003F8908_00(arg0);
            temp_v1 = 7;
            if (temp_v0 != 0) {
                var_s1 = temp_v1;
            }
        }
        break;
    case 3:
        var_s1 = 9;
        break;
    }

dispatch:
    switch (var_s1) {
    case 7:
        temp_s0->x444 = (ref_L07_003F8908_05 * 5 + 2) / 6;
        temp_s0->x448 = (ref_L07_003F8908_08 * 5 + 2) / 6;
        temp_s0->x438 = ref_L07_003F8908_01(3, 5);
        break;
    case 6:
        temp_s0->x444 = (ref_L07_003F8908_04 * 5 + 2) / 6;
        temp_s0->x448 = (ref_L07_003F8908_07 * 5 + 2) / 6;
        temp_s0->x438 = ref_L07_003F8908_01(2, 3);
        break;
    case 8:
        temp_s0->x438 = 1;
        temp_s0->x41C = ref_L07_003F8908_03(temp_s0->x180);
        break;
    case 9:
        temp_s0->x444 = (ref_L07_003F8908_06 * 5 + 2) / 6;
        temp_s0->x448 = (ref_L07_003F8908_09 * 5 + 2) / 6;
        temp_s0->x438 = ref_L07_003F8908_01(1, 3);
        break;
    }
    return var_s1;
}
