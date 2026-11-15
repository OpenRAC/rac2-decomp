#include "include_asm.h"
#include "common.h"

/* In its own unit: level 00's copy calls func_L00_003BAAD0 where the boot calls
   func_003181E0, so that callee must stay an external here. */

#ifndef RAC2_T_STATE_001B5200
#define RAC2_T_STATE_001B5200
typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;
#endif

extern State_001b5200 g_active_camera;
extern short *D_001EE5A0[];
extern u8 *D_001B1B5C MACRO_ADDR;
extern int D_001B1B78 MACRO_ADDR;
extern int FloatToInt(float);
extern float math_random_signed_float_range(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int math_random_int_below(int);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern int moby_count_group_not_in_state(int, int);
extern int weapon_select_aim_target(void *, int, void *, float, float, int);
extern void flyer_alert_group_on_death(void *);
extern void flyer_alert_group(void *);

/* Sets up the enemy on its first frame, then checks its health each frame. Returns 1 when it has died. */
int flyer_init_check_death(char *self)
{
    char *data = *(char **)(self + 0x68);
    int result, dead;
    short *p;
    u8 *other;
    if (*(u8 *)(self + 0x20) == 0) {
        self[0x7E] |= 1;
        *(char **)(data + 0x18) = data + 0x110;
        *(float *)(data + 0x28C) = *(float *)(self + 0x18);
        *(float *)(self + 0x2C) *= 0.75f;
        *(int *)(data + 0x2A8) = -1;
        data[0x48] = FloatToInt(10.0f);
        data[0x4A] = FloatToInt(8.0f);
        if (*(float *)(data + 0x290) == -1.0f)
            *(float *)(data + 0x290) = 0.01745329424738884f * math_random_signed_float_range(25.0f, 100.0f);
        else
            *(float *)(data + 0x290) *= 0.01745329424738884f;
        self[0x30] = 48;
        *(float *)(data + 0x1C0) = *(float *)(data + 0x29C) * 0.01666666753590107f;
        /* The -1 bytes between 0x9C and 0x110 keep the 0.85..25.13 constants live one
           insn longer than 0.4 before local-alloc, which gives retail's $f3..$f7. */
        data[0x70] = 11;
        *(float *)(data + 0x7C) = 0.10000000894069672f;
        *(float *)(data + 0x80) = 0.06666667014360428f;
        *(float *)(data + 0x84) = 0.004166666883975267f;
        *(float *)(data + 0x88) = 0.008333333767950535f;
        *(float *)(data + 0x8C) = 0.004166666883975267f;
        *(float *)(data + 0x9C) = 0.4f;
        data[0xCC] = -1; data[0xCD] = -1; data[0xCE] = -1; data[0xCF] = -1; data[0xD2] = -1; data[0xD3] = -1;
        *(float *)(data + 0x110) = 0.85f;
        *(float *)(data + 0x118) = 0.75f;
        *(float *)(data + 0x120) = 1.134464144706726f;
        *(float *)(data + 0x140) = 25.13274383544922f;
        *(int *)(data + 0x298) = 1;
        *(int *)(data + 0xA8) = 3;
        data[0x71] = 0; data[0x72] = 0; data[0x76] = 0; data[0x77] = 0;
        *(float *)(data + 0x90) = 0.5f; *(float *)(data + 0x94) = 0.5f;
        data[0xD6] = 1;
        *(int *)(data + 0x114) = 0;
        *(float *)(data + 0x11C) = 0.5f;
        *(int *)(data + 0x13C) = 0;
        *(int *)(data + 0x148) |= 0x10;
        moby_set_controller_speed_limits(self, 0.006666666828095913f, 0.06666667014360428f, 0.8377581834793091f, 0.8377581834793091f);
        qcopy(data + 0x200, self + 0x10);
        data[0x28] = 3; data[0x2E] = 1;
        *(float *)(data + 0x210) = 1.0f;
        *(float *)(data + 0x21C) = 5.0f;
        *(float *)(data + 0x220) = 10.0f;
        *(float *)(data + 0x2B0) = (unsigned char)data[0x34];
        *(float *)(data + 0x30) -= 0.5f;
        *(short *)(data + 0x272) = math_random_int_below(10);
        moby_set_state(self, 2, 0);
        if (*(u8 *)(self + 0x43)) anim_start_blended(self, 0, 0, 0);
    }
    if (*(u8 *)(self + 0x31) && fast_vec_dist(self + 0x10, g_active_camera.pos) < 48.0f) {
        moby_update_ground_check(self); self[0x6F] = 45;
    }
    dead = (unsigned char)data[0x2E] == 2;
    result = moby_apply_damage_to_object(self, data + 0x60, 0);
    if (result || dead) {
        flyer_alert_group(self);
        if (result == 4 || result == 5 || dead) {
            if ((unsigned char)self[0x21] <= D_001B1B78 && moby_count_group_not_in_state((unsigned char)self[0x21], -1) >= 2) {
                p = D_001EE5A0[(unsigned char)self[0x21]];
                do {
                    other = D_001B1B5C + ((*p & 0x7FFF) << 8);
                    if (*(short *)(other + 0xAA) == 0x99C /* moby class 2460 */) {
                        char *otherData = *(char **)(other + 0x68);
                        if (!*(int *)(otherData + 0x2AC)) {
                            *(int *)(otherData + 0x2AC) = 1;
                            break;
                        }
                    }
                } while (*p++ >= 0);
            }
        }
    }
    if (dead) { flyer_alert_group_on_death(self); return 1; }
    *(int *)(data + 0x258) = weapon_select_aim_target(self, *(int *)(data + 0x250), 0, *(float *)(data + 0x268), 10.0f, 0);
    *(int *)(data + 0x25C) = weapon_select_aim_target(self, *(int *)(data + 0x254), 0, *(float *)(data + 0x26C), 10.0f, 0);
    return 0;
}
