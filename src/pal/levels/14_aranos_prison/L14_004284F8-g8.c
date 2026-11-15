#include "include_asm.h"
#include "common.h"

extern float D_L14_001B16B0 __attribute__((sda));
extern int part_find_owned_effect_slot(char *a0, int a1, int a2);
extern void moby_apply_damage_to_object(char *a0, char *a1, int a2);
extern void part_spawn_explosion_with_sparks(char *a0, char *a1, float f12, float f13, int a2);
extern void SetDeathBits(char *a0, int a1, int a2);
extern void moby_mark_spawned(char *a0);

/* Resets the moby's scale when its model says so, then lets it fall or die. */
void func_PAL_L14_00428798(char *a0)
{
    char *s0 = a0;
    char *s1;
    char *m;
    char *v;

    s1 = *(char **)(s0 + 0x68);
    v = (char *)part_find_owned_effect_slot(a0, 0x10000, 1);
    if (v != 0) {
        m = *(char **)(v + 0x20);
        if (m != 0 && *(short *)(m + 0xAA) == 0xB69) {
            if (*(unsigned char *)(s0 + 0x31) == 0)
                *(float *)(v + 0x2C) = 0.0f;
            else
                *(float *)(v + 0x2C) = 1.0f;
        }
    }
    moby_apply_damage_to_object(s0, s1 + 0x60, 0);
    if (*(float *)(s1 + 0x20) <= 0.0f) {
        part_spawn_explosion_with_sparks(s0, s0 + 0x10, 1.0f, 13.0f, -1);
        SetDeathBits(s0, 0, 3);
        moby_mark_spawned(s0);
    } else if (*(float *)(s0 + 0x18) < D_L14_001B16B0) {
        SetDeathBits(s0, 0, 3);
        moby_mark_spawned(s0);
    }
}

extern int flag_set_first_pending(void *);
extern int math_random_int_below(int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int path_advance(void *, void *, int, void *, int, float);
extern void actor_aim_at_target(void *, void *);
extern int actor_group_has_active_non_tourist(void *);
extern int path_measure_moby_against_entry(void *, int, float);
extern float vec_distance_xy(void *, void *);
extern int ComputeRegionRouteHeading(void *, void *, void *, void *, int, void *, void *, float, float);
extern unsigned long moby_dispatch_action_by_kind(void *, void *);

extern char *g_moby_l14_pool;
extern char *D_L14_001B268C;
extern int D_L14_001B16B4 __attribute__((sda));
extern int D_L14_001B16B8 __attribute__((sda));
extern int D_L14_001B16BC __attribute__((sda));
extern char g_hero_position[];

/*
 * Updates the actor's animation, movement phases and hit response.
 * func_PAL_L14_004288B0, the PAL copy of func_L14_00423358: the same C, where the animation blend
 * of 10 frames becomes 8, the four rates passed to func_002B60B0 are rescaled for 50 Hz, and the
 * idle timer's limit D_L14_001B16B4 is scaled by 5/6.
 */
void func_PAL_L14_004288B0(char *self)
{
    char *state = *(char **)(self + 0x68);
    float target[4];
    unsigned long flags;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        break;
    case 1:
        if (flag_set_first_pending(self)) {
            if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 1)
                anim_start_blended(self, math_random_int_below(2) + 1, 0, 8);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            float a = *(float *)(state + 0x720);
            float b = *(float *)(state + 0x724);
            moby_set_controller_speed_limits(self, (a + a) * 0.00040000002f,
                a * 0.020000001f, (b + b) * 6.981318e-06f,
                b * 0.0003490659f);
            if (*(unsigned char *)(self + 0x43) != math_random_int_below(4) + 6)
                anim_start_blended(self, math_random_int_below(4) + 6, 0, 8);
            *(short *)(state + 0x770) = 0;
        } else if (path_advance(self, state + 0x700, *(int *)(state + 0x730), state + 0x770, 0, 2.0f)) {
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(self)) {
            if (*(unsigned char *)(self + 0x43) != 1)
                anim_start_blended(self, 1, 0, 8);
            *(unsigned char *)(self + 0xBC) = 0;
            *(unsigned short *)(self + 0x96) = math_random_int_below(D_L14_001B16B4 >> 1);
        } else {
            qcopy_nc(target, (void *)((*(int *)(state + 0x748) << 8) + (unsigned int)g_moby_l14_pool + 0x10));
            target[2] += 0.3f;
            actor_aim_at_target(self, g_moby_l14_pool + (*(int *)(state + 0x748) << 8) + 0x10);
            if (*(unsigned char *)(self + 0xBC) == 0 && *(unsigned short *)(self + 0x96) > ((s32)(D_L14_001B16B4) * 5 + 2) / 6) {
                *(unsigned short *)(self + 0x96) = math_random_int_below(D_L14_001B16B4 >> 1);
                if (math_random_int_below(5) != 0 && *(unsigned char *)(self + 0x43) != 5)
                    anim_start_blended(self, 5, 0, 8);
            }
            if (*(unsigned char *)(self + 0xBC) == 1 && (*(unsigned char *)(self + 0x60) & 2))
                moby_set_state(self, 2, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(self)) {
            switch (*(unsigned char *)(self + 0xBC) = math_random_int_below(2)) {
            case 0:
                if (*(unsigned char *)(self + 0x43) != 4)
                    anim_start_blended(self, 4, 0, 8);
                break;
            case 1:
                if (*(unsigned char *)(self + 0x43) != 3)
                    anim_start_blended(self, 3, 0, 8);
                break;
            }
        }
        if (*(int *)(state + 0x764) != -1)
            actor_aim_at_target(self, D_L14_001B268C + (*(int *)(state + 0x764) << 7) + 0x30);
        if (*(unsigned char *)(self + 0x60) & 2)
            moby_set_state(self, 5, 2);
        break;
    case 5:
        if (flag_set_first_pending(self)) {
            *(unsigned char *)(self + 0xBC) = 0;
            if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 10)
                anim_start_blended(self, math_random_int_below(2) + 10, 0, 8);
        } else {
            if (*(unsigned char *)(self + 0xBC) == 0 && (*(unsigned char *)(self + 0x60) & 2)) {
                if (*(int *)(state + 0x734) != -1) {
                    float a, b;
                    *(unsigned char *)(self + 0xBC) = 1;
                    a = *(float *)(state + 0x728);
                    b = *(float *)(state + 0x72C);
                    moby_set_controller_speed_limits(self, (a + a) * 0.00040000002f,
                        a * 0.020000001f, (b + b) * 6.981318e-06f,
                        b * 0.0003490659f);
                    if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 14)
                        anim_start_blended(self, math_random_int_below(2) + 14, 0, 8);
                    *(short *)(state + 0x770) = path_measure_moby_against_entry(self + 0x10, *(int *)(state + 0x734), 0.0f);
                } else {
                    *(unsigned char *)(self + 0xBC) = 2;
                }
            } else if (*(unsigned char *)(self + 0xBC) == 1) {
                path_advance(self, state + 0x700, *(int *)(state + 0x734), state + 0x770, *(short *)(state + 0x77C), 1.0f);
                if (*(unsigned short *)(self + 0x96) % D_L14_001B16B8 == 0 && math_random_int_below(D_L14_001B16BC) == 0) {
                    *(unsigned char *)(self + 0xBC) = 2;
                    if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 12)
                        anim_start_blended(self, math_random_int_below(2) + 12, 0, 8);
                }
            } else if (*(unsigned char *)(self + 0xBC) == 2 && (*(unsigned char *)(self + 0x60) & 2)) {
                if (actor_group_has_active_non_tourist(self))
                    moby_set_state(self, 5, -1);
                else
                    moby_set_state(self, 1, -1);
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(self)) {
            *(unsigned char *)(self + 0xBC) = 0;
            if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 10)
                anim_start_blended(self, math_random_int_below(2) + 10, 0, 8);
        } else {
            if (*(unsigned char *)(self + 0xBC) == 0 && (*(unsigned char *)(self + 0x60) & 2)) {
                float a, b;
                *(unsigned char *)(self + 0xBC) = 1;
                a = *(float *)(state + 0x728);
                b = *(float *)(state + 0x72C);
                moby_set_controller_speed_limits(self, (a + a) * 0.00040000002f,
                    a * 0.020000001f, (b + b) * 6.981318e-06f,
                    b * 0.0003490659f);
                if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 14)
                    anim_start_blended(self, math_random_int_below(2) + 14, 0, 8);
            } else if (*(unsigned char *)(self + 0xBC) == 1) {
                qcopy(state + 0x700, g_hero_position);
                if (vec_distance_xy(self + 0x10, state + 0x700) < *(float *)(state + 0x74C) && *(unsigned char *)(self + 0x31)) {
                    *(unsigned char *)(self + 0xBC) = 2;
                    if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 12)
                        anim_start_blended(self, math_random_int_below(2) + 12, 0, 8);
                }
            } else if (*(unsigned char *)(self + 0xBC) == 2 && (*(unsigned char *)(self + 0x60) & 2)) {
                moby_set_state(self, 6, -1);
            }
        }
        break;
    case 7:
        if (flag_set_first_pending(self)) {
            if (*(unsigned char *)(self + 0x43) != math_random_int_below(2) + 14)
                anim_start_blended(self, math_random_int_below(2) + 14, 0, 8);
        }
        ComputeRegionRouteHeading(self + 0x10, state + 0x710, state + 0x768, state + 0x200,
            *(int *)(state + 0x750), state + 0x75C, state + 0x760, 0.0f, 0.4f);
        qcopy(state + 0x700, state + 0x710);
        *(short *)(state + 0x77A) = 1;
        if (vec_distance_xy(self + 0x10, state + 0x710) < 0.2f)
            moby_set_state(self, 1, 1);
        break;
    case 8:
        flags = moby_dispatch_action_by_kind(self, state + 0x60);
        if ((*(unsigned char *)(self + 0x42) == 0x12 && math_random_int_below(30) == 0) || ((flags & 1UL) == 1UL)) {
            SetDeathBits(self, 0, 3);
            moby_mark_spawned(self);
        } else if ((flags & 2UL) == 2UL) {
            moby_set_state(self, *(unsigned char *)(self + 0x94), 2);
        }
        break;
    }
}
