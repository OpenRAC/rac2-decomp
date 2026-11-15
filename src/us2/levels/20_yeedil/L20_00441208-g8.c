#include "common.h"

/* func_US2_L20_00441208, the USA v2.00 copy of func_L20_0043FC70: the same C, where the arm
   for reaching zero clears st + 0x280 and calls func_US2_002A7AA8 and func_L01_003E9CF8
   instead of moving the object, and also sets obj + 0xA8 only there. */
extern float D_L20_001B1FE4 __attribute__((sda));
extern float D_L20_001B1FE8 __attribute__((sda));
extern float D_L20_001B2BE8;
extern char g_hero_state[];
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength(char *, char *);
extern float ApproachValue(float *, float, float);
extern void func_US2_002A7AA8(char *, int, int), part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void moby_enter_state_six(char *);
extern int moby_apply_damage_to_object(char *, char *, int);
extern int weapon_select_aim_target(char *, int, void *, int, float, float);

void func_US2_L20_00441208(char *arg0) {
    char *st = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) == 0) {
        *(float *)(st + 0x170) = 0.5f;
        *(unsigned char *)(st + 0x150) = 5;
        *(int *)(st + 0x188) = 2;
        *(float *)(st + 0x174) = 0.6f;
        *(float *)(st + 0x17C) = 0.15f;
        *(float *)(st + 0x84) = 0.05f;
        *(float *)(st + 0x54) = 0.3f;
        *(float *)(st + 0x50) = 0.5f;
        *(float *)(st + 0x58) = 0.4f;
        *(float *)(st + 0x5C) = 2.0f;
        *(float *)(st + 0x60) = 1.57079649f;
        *(float *)(st + 0x80) = 0.785398245f;
        {
            float angle = math_random_signed_float_range(18.0f, 22.0f) * 0.0174532942f;
            float speed = D_L20_001B1FE4 * 0.0166666675f;
            float accel = D_L20_001B1FE8 * 0.00027777778f;

            *(short *)(st + 0x132) = 0x78;
            *(short *)(st + 0x134) = 0xB4;
            *(float *)(st + 0x12C) = angle;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            *(float *)(st + 0x74) = accel;
        }
        *(int *)(st + 0x88) |= 0x200;
        *(unsigned char *)(st + 0x48) = FloatToInt(8.0f);
        *(unsigned char *)(st + 0x4A) = FloatToInt(12.0f);
        *(unsigned char *)(st + 0x29) = 1;
        if (*(short *)(st + 0x24) == 0) {
            *(short *)(st + 0x24) = 3;
            *(float *)(st + 0x20) = 3.0f;
        }
        *(int *)(arg0 + 0x98) = 0;
        *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(arg0, 6, 3);
        if (*(unsigned char *)(arg0 + 0x43) != 0) {
            anim_start_blended(arg0, 0, 0, 0);
        }
    }

    *(float *)(st + 0x180) = D_L20_001B2BE8;
    if (*(unsigned char *)(arg0 + 0x20) == 6) {
        return;
    }
    if (*(unsigned char *)(st + 0x2E) == 2) {
        *(int *)(arg0 + 0x98) = 0;
        *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(arg0, 6, 3);
    }
    *(unsigned char *)(st + 0x2E) = 1;

    if (*(unsigned char *)(arg0 + 0x20) == 7 && *(float *)(st + 0x20) > 0.0f) {
        char *hit = part_find_owned_effect_slot(arg0, 0x10000, 0);
        float damage = moby_update_aim_target_strength(arg0, hit);

        ApproachValue((float *)(st + 0x20), 0.0f, damage);
        if (*(float *)(st + 0x20) <= 0.0f) {
            *(int *)(st + 0x280) = 0;
            func_US2_002A7AA8(arg0, 0, 3);
            part_queue_moby_for_glow(arg0, 0, moby_enter_state_six);
            *(unsigned char *)(arg0 + 0xA8) = 0xFF;
        }
    } else {
        moby_apply_damage_to_object(arg0, st + 0x140, 0);
    }
    weapon_select_aim_target(arg0, *(int *)(st + 0x270), 0, 0, 64.0f, 0.0f);

    if (*(int *)(st + 0x204) == 0) {
        char *g = g_hero_state;

        *(char **)(st + 0x200) = *(char **)(g + 0x2290);
        qcopy(st + 0x1F0, *(char **)(g + 0x2290) + 0x10);
        *(int *)(st + 0x204) = 1;
    }
}
