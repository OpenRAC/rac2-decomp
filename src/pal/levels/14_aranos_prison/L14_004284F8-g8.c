#include "include_asm.h"
#include "common.h"

extern float g_protopet_distance_threshold __attribute__((sda));
extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);
extern int moby_apply_damage_to_object(char *a0, char *a1, int a2);
extern void part_spawn_explosion_with_sparks(char *a0, char *a1, float f12, float f13, int a2);
extern void SetDeathBits(char *a0, int a1, int a2);
extern void moby_mark_spawned(char *a0);

/* Resets the moby's scale when its model says so, then lets it fall or die. */
void protopet_holder_update_pal(char *moby)
{
    char *self = moby;
    char *vars;
    char *target_moby;
    char *slot;

    vars = *(char **)(self + 0x68);
    slot = (char *)part_find_owned_effect_slot(moby, 0x10000, 1);
    if (slot != 0) {
        target_moby = *(char **)(slot + 0x20);
        if (target_moby != 0 && *(short *)(target_moby + 0xAA) == 0xB69) {
            if (*(unsigned char *)(self + 0x31) == 0)
                *(float *)(slot + 0x2C) = 0.0f;
            else
                *(float *)(slot + 0x2C) = 1.0f;
        }
    }
    moby_apply_damage_to_object(self, vars + 0x60, 0);
    if (*(float *)(vars + 0x20) <= 0.0f) {
        part_spawn_explosion_with_sparks(self, self + 0x10, 1.0f, 13.0f, -1);
        SetDeathBits(self, 0, 3);
        moby_mark_spawned(self);
    } else if (*(float *)(self + 0x18) < g_protopet_distance_threshold) {
        SetDeathBits(self, 0, 3);
        moby_mark_spawned(self);
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
extern char *g_platform_projection_table;
extern int g_enemy_random_timer_max __attribute__((sda));
extern int g_enemy_random_timer_period __attribute__((sda));
extern int g_enemy_random_chance_range __attribute__((sda));
extern char g_hero_position[];

/*
 * Updates the actor's animation, movement phases and hit response.
 * func_PAL_L14_004288B0, the PAL copy of func_L14_00423358: the same C, where the animation blend
 * of 10 frames becomes 8, the four rates passed to func_002B60B0 are rescaled for 50 Hz, and the
 * idle timer's limit D_L14_001B16B4 is scaled by 5/6.
 */
void prison_actor_state_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float target[4];
    unsigned long flags;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        break;
    case 1:
        if (flag_set_first_pending(moby)) {
            if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 1)
                anim_start_blended(moby, math_random_int_below(2) + 1, 0, 8);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            float turn_rate = *(float *)(vars + 0x720);
            float aim_rate = *(float *)(vars + 0x724);
            moby_set_controller_speed_limits(moby, (turn_rate + turn_rate) * 0.00040000002f,
                turn_rate * 0.020000001f, (aim_rate + aim_rate) * 6.981318e-06f,
                aim_rate * 0.0003490659f);
            if (*(unsigned char *)(moby + 0x43) != math_random_int_below(4) + 6)
                anim_start_blended(moby, math_random_int_below(4) + 6, 0, 8);
            *(short *)(vars + 0x770) = 0;
        } else if (path_advance(moby, vars + 0x700, *(int *)(vars + 0x730), vars + 0x770, 0, 2.0f)) {
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            if (*(unsigned char *)(moby + 0x43) != 1)
                anim_start_blended(moby, 1, 0, 8);
            *(unsigned char *)(moby + 0xBC) = 0;
            *(unsigned short *)(moby + 0x96) = math_random_int_below(g_enemy_random_timer_max >> 1);
        } else {
            qcopy_nc(target, (void *)((*(int *)(vars + 0x748) << 8) + (unsigned int)g_moby_l14_pool + 0x10));
            target[2] += 0.3f;
            actor_aim_at_target(moby, g_moby_l14_pool + (*(int *)(vars + 0x748) << 8) + 0x10);
            if (*(unsigned char *)(moby + 0xBC) == 0 && *(unsigned short *)(moby + 0x96) > ((s32)(g_enemy_random_timer_max) * 5 + 2) / 6) {
                *(unsigned short *)(moby + 0x96) = math_random_int_below(g_enemy_random_timer_max >> 1);
                if (math_random_int_below(5) != 0 && *(unsigned char *)(moby + 0x43) != 5)
                    anim_start_blended(moby, 5, 0, 8);
            }
            if (*(unsigned char *)(moby + 0xBC) == 1 && (*(unsigned char *)(moby + 0x60) & 2))
                moby_set_state(moby, 2, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            switch (*(unsigned char *)(moby + 0xBC) = math_random_int_below(2)) {
            case 0:
                if (*(unsigned char *)(moby + 0x43) != 4)
                    anim_start_blended(moby, 4, 0, 8);
                break;
            case 1:
                if (*(unsigned char *)(moby + 0x43) != 3)
                    anim_start_blended(moby, 3, 0, 8);
                break;
            }
        }
        if (*(int *)(vars + 0x764) != -1)
            actor_aim_at_target(moby, g_platform_projection_table + (*(int *)(vars + 0x764) << 7) + 0x30);
        if (*(unsigned char *)(moby + 0x60) & 2)
            moby_set_state(moby, 5, 2);
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            *(unsigned char *)(moby + 0xBC) = 0;
            if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 10)
                anim_start_blended(moby, math_random_int_below(2) + 10, 0, 8);
        } else {
            if (*(unsigned char *)(moby + 0xBC) == 0 && (*(unsigned char *)(moby + 0x60) & 2)) {
                if (*(int *)(vars + 0x734) != -1) {
                    float turn_rate, aim_rate;
                    *(unsigned char *)(moby + 0xBC) = 1;
                    turn_rate = *(float *)(vars + 0x728);
                    aim_rate = *(float *)(vars + 0x72C);
                    moby_set_controller_speed_limits(moby, (turn_rate + turn_rate) * 0.00040000002f,
                        turn_rate * 0.020000001f, (aim_rate + aim_rate) * 6.981318e-06f,
                        aim_rate * 0.0003490659f);
                    if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 14)
                        anim_start_blended(moby, math_random_int_below(2) + 14, 0, 8);
                    *(short *)(vars + 0x770) = path_measure_moby_against_entry(moby + 0x10, *(int *)(vars + 0x734), 0.0f);
                } else {
                    *(unsigned char *)(moby + 0xBC) = 2;
                }
            } else if (*(unsigned char *)(moby + 0xBC) == 1) {
                path_advance(moby, vars + 0x700, *(int *)(vars + 0x734), vars + 0x770, *(short *)(vars + 0x77C), 1.0f);
                if (*(unsigned short *)(moby + 0x96) % g_enemy_random_timer_period == 0 && math_random_int_below(g_enemy_random_chance_range) == 0) {
                    *(unsigned char *)(moby + 0xBC) = 2;
                    if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 12)
                        anim_start_blended(moby, math_random_int_below(2) + 12, 0, 8);
                }
            } else if (*(unsigned char *)(moby + 0xBC) == 2 && (*(unsigned char *)(moby + 0x60) & 2)) {
                if (actor_group_has_active_non_tourist(moby))
                    moby_set_state(moby, 5, -1);
                else
                    moby_set_state(moby, 1, -1);
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            *(unsigned char *)(moby + 0xBC) = 0;
            if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 10)
                anim_start_blended(moby, math_random_int_below(2) + 10, 0, 8);
        } else {
            if (*(unsigned char *)(moby + 0xBC) == 0 && (*(unsigned char *)(moby + 0x60) & 2)) {
                float turn_rate, aim_rate;
                *(unsigned char *)(moby + 0xBC) = 1;
                turn_rate = *(float *)(vars + 0x728);
                aim_rate = *(float *)(vars + 0x72C);
                moby_set_controller_speed_limits(moby, (turn_rate + turn_rate) * 0.00040000002f,
                    turn_rate * 0.020000001f, (aim_rate + aim_rate) * 6.981318e-06f,
                    aim_rate * 0.0003490659f);
                if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 14)
                    anim_start_blended(moby, math_random_int_below(2) + 14, 0, 8);
            } else if (*(unsigned char *)(moby + 0xBC) == 1) {
                qcopy(vars + 0x700, g_hero_position);
                if (vec_distance_xy(moby + 0x10, vars + 0x700) < *(float *)(vars + 0x74C) && *(unsigned char *)(moby + 0x31)) {
                    *(unsigned char *)(moby + 0xBC) = 2;
                    if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 12)
                        anim_start_blended(moby, math_random_int_below(2) + 12, 0, 8);
                }
            } else if (*(unsigned char *)(moby + 0xBC) == 2 && (*(unsigned char *)(moby + 0x60) & 2)) {
                moby_set_state(moby, 6, -1);
            }
        }
        break;
    case 7:
        if (flag_set_first_pending(moby)) {
            if (*(unsigned char *)(moby + 0x43) != math_random_int_below(2) + 14)
                anim_start_blended(moby, math_random_int_below(2) + 14, 0, 8);
        }
        ComputeRegionRouteHeading(moby + 0x10, vars + 0x710, vars + 0x768, vars + 0x200,
            *(int *)(vars + 0x750), vars + 0x75C, vars + 0x760, 0.0f, 0.4f);
        qcopy(vars + 0x700, vars + 0x710);
        *(short *)(vars + 0x77A) = 1;
        if (vec_distance_xy(moby + 0x10, vars + 0x710) < 0.2f)
            moby_set_state(moby, 1, 1);
        break;
    case 8:
        flags = moby_dispatch_action_by_kind(moby, vars + 0x60);
        if ((*(unsigned char *)(moby + 0x42) == 0x12 && math_random_int_below(30) == 0) || ((flags & 1UL) == 1UL)) {
            SetDeathBits(moby, 0, 3);
            moby_mark_spawned(moby);
        } else if ((flags & 2UL) == 2UL) {
            moby_set_state(moby, *(unsigned char *)(moby + 0x94), 2);
        }
        break;
    }
}
