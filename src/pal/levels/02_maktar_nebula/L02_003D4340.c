#include "include_asm.h"

#include "common.h"
extern char g_camera_l02_position;
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void moby_update_ground_check(char *);
extern void *part_find_owned_effect_slot(char *, int, int);
extern int moby_apply_damage_to_object_pal(char *, char *, int);
extern void armed_enemy_find_partner(char *);
extern int armed_enemy_is_holding_in_attack(char *, void *);
extern void part_spawn_dust_pairs_pal(char *, int);
extern void enemy_release_effect_record(char *);
extern void armed_enemy_drop_held_and_reset_pal(char *, int, int);

/* State 0 of the actor: fills its state record (a random heading of 10 to 30 degrees, either
   sign, then about twenty constants), queues func_L02_003D2390; then, while it is drawn, the
   per-frame part (the pulse test against D_L02_001BA500, the 0x15/0x10 animation switch,
   func_PAL_L02_003D64F8 and func_L02_003D1998).
   Spelling: the signed heading is a variable of its own, set after the coin flip and stored
   first. Its pseudo then crosses no call, so sched1 ties its store to that call by an
   anti-dependence (priority 3) and the zero store at 0x2F4 goes first, as in retail; stored
   from `ang` itself, the two stores tie at priority 4 and the dying `ang` wins. The constant
   stores come out in an order of the scheduler's own (the statement order below is the
   measured one), and 0.017453294f, 1.5707965f and 0.52359885f are retail's bits. */

void armed_enemy_update_pal(char *self) {
    char *state = *(char **)(self + 0x68);
    float ang;
    float dir;
    char *part;

    if (*(unsigned char *)(self + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        *(unsigned char *)(state + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(state + 0x4A) = FloatToInt(16.0f);
        ang = math_random_float_range(10.0f, 30.0f) * 0.017453294f;
        if (math_random_int_below(2) != 0)
            dir = -ang;
        else
            dir = ang;
        *(float *)(state + 0x2E8) = dir;
        *(unsigned char *)(state + 0x60) = 0x14;
        *(int *)(state + 0x98) = 7;
        *(float *)(state + 0x80) = 1.3f;
        *(float *)(state + 0x84) = 1.3f;
        *(unsigned char *)(state + 0x69) = 2;
        *(unsigned char *)(state + 0x1E9) = 3;
        *(float *)(state + 0x8C) = 0.4f;
        *(unsigned char *)(state + 0x1E6) = 5;
        *(float *)(state + 0x108) = 0.3f;
        *(unsigned char *)(state + 0x1E8) = 2;
        *(float *)(state + 0x1D4) = 0.5f;
        *(float *)(state + 0x100) = 1.0f;
        *(float *)(state + 0x104) = 0.2f;
        *(float *)(state + 0x10C) = 0.3f;
        *(float *)(state + 0x110) = 1.5707965f;
        *(float *)(state + 0x130) = 0.52359885f;
        *(short *)(state + 0x2F4) = 0;
        *(float *)(state + 0x134) = 0.01f;
        *(float *)(state + 0x12C) = 0.008f;
        *(unsigned char *)(state + 0x28) = 3;
        *(unsigned char *)(state + 0x29) = 1;
        *(float *)(state + 0x30) = 0.75f;
        if (math_random_int_below(2) == 0)
            *(unsigned short *)(self + 0x34) |= 0x8000;
        *(int *)(state + 0x2E4) = 0;
        enemy_release_effect_record(self);
    }
    if (*(unsigned char *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, &g_camera_l02_position) < 24.0f) {
            moby_update_ground_check(self);
            *(unsigned char *)(self + 0x6F) = 0x16;
        }
        if (*(unsigned char *)(self + 0x31) != 0 && *(unsigned char *)(self + 0x20) >= 3) {
            *(float *)(state + 0xFC) = 1.0f;
            part = part_find_owned_effect_slot(self, 0x10000, 1);
            if (part != 0) {
                *(float *)(state + 0xFC) = 1.0f;
                if (armed_enemy_is_holding_in_attack(self, part) != 0) {
                    *(unsigned char *)(state + 0x60) = 0x13;
                    moby_apply_damage_to_object_pal(self, state + 0x50, 1);
                    *(unsigned char *)(state + 0x60) = 0x14;
                    if (*(int *)(state + 0x2E4) != 0 && *(short *)(state + 0x2F4) == 0 &&
                        *(unsigned char *)(self + 0x31) != 0) {
                        part_spawn_dust_pairs_pal(*(char **)(state + 0x2E4) + 0x10, 2);
                        *(short *)(state + 0x2F4) = 0x32;
                    }
                } else {
                    moby_apply_damage_to_object_pal(self, state + 0x50, 0);
                }
            } else {
                moby_apply_damage_to_object_pal(self, state + 0x50, 0);
            }
            if (*(float *)(state + 0x20) <= 0.0f && *(unsigned char *)(self + 0x20) != 0x15) {
                moby_set_state(self, 0x15, 7);
                if (*(unsigned char *)(self + 0x43) != 0x10)
                    anim_start_blended_pal(self, 0x10, 0, 0);
            }
            if (*(unsigned char *)(self + 0x20) >= 2 && *(unsigned char *)(state + 0x2E) == 2)
                armed_enemy_drop_held_and_reset_pal(self, 1, 1);
            armed_enemy_find_partner(self);
        }
    }
}

