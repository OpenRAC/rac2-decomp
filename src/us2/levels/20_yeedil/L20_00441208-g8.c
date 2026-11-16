#include "common.h"

/* func_US2_L20_00441208, the USA v2.00 copy of func_L20_0043FC70: the same C, where the arm
   for reaching zero clears st + 0x280 and calls func_US2_002A7AA8 and func_L01_003E9CF8
   instead of moving the object, and also sets obj + 0xA8 only there. */
extern float g_yeedil_small_speed_b __attribute__((sda));
extern float g_yeedil_small_accel_a __attribute__((sda));
extern float g_level_shared_float;
extern char g_hero_state[];
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength(char *, char *);
extern float ApproachValue(float *, float, float);
extern void SetDeathBits_us2(char *, int, int), part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void moby_enter_state_six(char *);
extern int moby_apply_damage_to_object(char *, char *, int);
extern int weapon_select_aim_target(char *, int, void *, int, float, float);

/* Sets up the small Yeedil enemy on its first frame, then handles its hits, damage and death each frame (USA v2.00). */
void yeedil_small_enemy_init_damage_us2(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(float *)(vars + 0x170) = 0.5f;
        *(unsigned char *)(vars + 0x150) = 5;
        *(int *)(vars + 0x188) = 2;
        *(float *)(vars + 0x174) = 0.6f;
        *(float *)(vars + 0x17C) = 0.15f;
        *(float *)(vars + 0x84) = 0.05f;
        *(float *)(vars + 0x54) = 0.3f;
        *(float *)(vars + 0x50) = 0.5f;
        *(float *)(vars + 0x58) = 0.4f;
        *(float *)(vars + 0x5C) = 2.0f;
        *(float *)(vars + 0x60) = 1.57079649f;
        *(float *)(vars + 0x80) = 0.785398245f;
        {
            float angle = math_random_signed_float_range(18.0f, 22.0f) * 0.0174532942f;
            float speed = g_yeedil_small_speed_b * 0.0166666675f;
            float accel = g_yeedil_small_accel_a * 0.00027777778f;

            *(short *)(vars + 0x132) = 0x78;
            *(short *)(vars + 0x134) = 0xB4;
            *(float *)(vars + 0x12C) = angle;
            *(float *)(vars + 0x78) = speed;
            *(float *)(vars + 0x70) = accel;
            *(float *)(vars + 0x74) = accel;
        }
        *(int *)(vars + 0x88) |= 0x200;
        *(unsigned char *)(vars + 0x48) = FloatToInt(8.0f);
        *(unsigned char *)(vars + 0x4A) = FloatToInt(12.0f);
        *(unsigned char *)(vars + 0x29) = 1;
        if (*(short *)(vars + 0x24) == 0) {
            *(short *)(vars + 0x24) = 3;
            *(float *)(vars + 0x20) = 3.0f;
        }
        *(int *)(moby + 0x98) = 0;
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 6, 3);
        if (*(unsigned char *)(moby + 0x43) != 0) {
            anim_start_blended(moby, 0, 0, 0);
        }
    }

    *(float *)(vars + 0x180) = g_level_shared_float;
    if (*(unsigned char *)(moby + 0x20) == 6) {
        return;
    }
    if (*(unsigned char *)(vars + 0x2E) == 2) {
        *(int *)(moby + 0x98) = 0;
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 6, 3);
    }
    *(unsigned char *)(vars + 0x2E) = 1;

    if (*(unsigned char *)(moby + 0x20) == 7 && *(float *)(vars + 0x20) > 0.0f) {
        char *hit = part_find_owned_effect_slot(moby, 0x10000, 0);
        float damage = moby_update_aim_target_strength(moby, hit);

        ApproachValue((float *)(vars + 0x20), 0.0f, damage);
        if (*(float *)(vars + 0x20) <= 0.0f) {
            *(int *)(vars + 0x280) = 0;
            SetDeathBits_us2(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, moby_enter_state_six);
            *(unsigned char *)(moby + 0xA8) = 0xFF;
        }
    } else {
        moby_apply_damage_to_object(moby, vars + 0x140, 0);
    }
    weapon_select_aim_target(moby, *(int *)(vars + 0x270), 0, 0, 64.0f, 0.0f);

    if (*(int *)(vars + 0x204) == 0) {
        char *hero = g_hero_state;

        *(char **)(vars + 0x200) = *(char **)(hero + 0x2290);
        qcopy(vars + 0x1F0, *(char **)(hero + 0x2290) + 0x10);
        *(int *)(vars + 0x204) = 1;
    }
}
