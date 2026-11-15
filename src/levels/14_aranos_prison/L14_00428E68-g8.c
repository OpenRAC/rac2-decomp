#include "common.h"

#define W(p, o) (*(int *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))

typedef struct {
    char pad[0x80];
    float position[4];
} Hero;

extern int enemy_update_common(void *);
extern int flag_set_second_pending(void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern int moby_l01_turn_toward_target(void *, void *);
extern int coll_point_inside_region(void *, int);
extern int moby_start_effect_from_entry(void *, float);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
/* Integer and FP arguments retain their respective EE register-bank order. */
extern int coll_sweep_from_object(void *, void *, float, float, int, float, int, int, int);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float moby_get_anim_value(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void part_fire_burst_sound(void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_step_at_own_position(void *);
extern void moby_l14_set_state_value(void *, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void actor_update_walk_motion(void *);

extern float D_L14_001B1924 __attribute__((sda));
extern float D_L14_001B1928 __attribute__((sda));
extern float D_L14_001B192C __attribute__((sda));
extern float D_L14_001B1930 __attribute__((sda));
extern int D_L14_001B20C8;
extern u8 g_hero_state[];
extern u8 *g_moby_l14_pool;
extern int D_L14_001B1938[4];
extern char *D_L14_001C39C0[];

#define HERO ((Hero *)D_00189E20)
#define D_00189EA0 (HERO->position)

/* Updates the prison enemy that walks, climbs up and down to ledges and attacks the player, and is removed when destroyed. */
void climbing_enemy_update(char *self)
{
    char *vars = *(char **)(self + 0x68);
    int result, i;
    float angle, animTime;
    union {
        int choices[4];
        float pos[4];
    } scratch;

    if (enemy_update_common(self)) {
        moby_mark_spawned(self);
        return;
    }
    {
        switch (B(self, 0x95)) {
        case 0:
            if (W(vars, 0x2F0) == 1 && B(self, 0x20) == 1)
                moby_set_state(self, 5, 1);
            break;
        case 1:
            if (flag_set_second_pending(self))
                moby_set_controller_speed_limits(self,
                    D_L14_001B1924 * 0.0002777777845f,
                    D_L14_001B1928 * 0.0166666675359f,
                    D_L14_001B192C * 4.848137450608192e-06f,
                    D_L14_001B1930 * 0.0002908882452175021f);
            if (W(vars, 0x2F0) != 1) {
                moby_set_state(self, 1, 0);
                W(vars, 0x30C) = math_random_int_range(580, 600);
            }
            break;
        case 2:
            result = moby_dispatch_action_by_kind(self, vars + 0x140);
            if (result & 1) {
                part_fire_burst_sound(self);
                moby_mark_spawned(self);
                return;
            }
            if (result & 2) {
                if (W(vars, 0x2F0) == 1)
                    moby_set_state(self, 5, 1);
                else {
                    moby_set_state(self, 1, 0);
                    W(vars, 0x30C) = math_random_int_range(580, 600);
                }
            }
            break;
        }
    }

    switch (B(self, 0x20)) {
    case 1:
        if (flag_set_first_pending(self) && B(self, 0x43) != 6)
            anim_start_blended(self, 6, 0, 20);
        if (B(self, 0x60) & 2) {
            __builtin_memcpy(scratch.choices, D_L14_001B1938, 16);
            if (B(self, 0x43) != scratch.choices[math_random_int_below(4)])
                anim_start_blended(self, scratch.choices[math_random_int_below(4)], 0, 20);
        }
        if (W(vars, 0x2B8) != -1)
            moby_step_at_own_position(self);
        if ((D_L14_001B20C8 & 15) == (((int)self >> 8) & 15)) {
            if (W(vars, 0x2B8) == -1)
                break;
            if (W(vars, 0x31C) && HERO->position[2] + 2.0f < F(self, 0x18) &&
                vec_distance_xy(self + 0x10, g_hero_position) < 16.0f) {
                moby_set_state(self, 2, -1);
                break;
            }
            if (!W(vars, 0x31C) && F(self, 0x18) < HERO->position[2] - 2.0f &&
                vec_distance_xy(self + 0x10, g_hero_position) < 8.0f)
                moby_set_state(self, 3, -1);
        } else {
            angle = mat_fast_helper_a(HERO->position[0] - F(self, 0x10),
                                 HERO->position[1] - F(self, 0x14));
            if (FastDiffRots(F(self, 0xF8), angle) > 0.7853982449f)
                moby_set_state(self, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(self) && B(self, 0x43) != 8)
            anim_start_blended(self, 8, 0, 20);
        angle = mat_fast_helper_a(HERO->position[0] - F(self, 0x10),
                             HERO->position[1] - F(self, 0x14));
        moby_start_effect_from_entry(self, angle);
        if (FastDiffRots(F(self, 0xF8), angle) < 0.05235988274f)
            moby_set_state(self, 1, -1);
        break;
    case 2:
        if (flag_set_first_pending(self)) {
            if (B(self, 0x43) != 8)
                anim_start_blended(self, 8, 0, 20);
            moby_l14_set_state_value(g_moby_l14_pool + W(vars, 0x2B8) * 256, 0);
        }
        if (moby_l01_turn_toward_target(self, g_moby_l14_pool + W(vars, 0x2B8) * 256 + 0x10) & 128) {
            moby_l14_set_state_value(g_moby_l14_pool + W(vars, 0x2B8) * 256, 1);
            W(vars, 0x31C) = 0;
            moby_set_state(self, 1, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            if (B(self, 0x43) != 8)
                anim_start_blended(self, 8, 0, 20);
            moby_l14_set_state_value(g_moby_l14_pool + W(vars, 0x2B8) * 256, 0);
        }
        if (moby_l01_turn_toward_target(self, vars + 0x2E0) & 128) {
            W(vars, 0x31C) = 1;
            moby_set_state(self, 1, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(self) && B(self, 0x43) != 16)
            anim_start_blended(self, 16, 7, 7);
        animTime = moby_get_anim_value(self);
        if (animTime < 19.0f) {
            angle = mat_fast_helper_a(F(vars, 0x210) - F(self, 0x10),
                                 F(vars, 0x214) - F(self, 0x14));
            moby_start_effect_from_entry(self, angle);
            W(vars, 0x320) = 1;
        } else if (animTime <= 22.0f && W(vars, 0x320)) {
            coll_sweep_from_object(self, *(char **)(vars + 0x300) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            coll_sweep_from_object(self, *(char **)(vars + 0x304) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            moby_transform_joint_to_world(self, 6, scratch.pos);
            result = coll_sweep_from_object(self, scratch.pos, 0.57f, 2.0f, 1, 2.0f, 0, 1, 0);
            for (i = 0; i < result; i++)
                if (*(short *)(D_L14_001C39C0[i] + 0xAA) == 2404 /* Gadgebot */)
                    W(vars, 0x320) = 0;
        }
        break;
    case 7:
        if (coll_point_inside_region(g_hero_position, W(vars, 0x2BC)))
            moby_set_state(self, 8, -1);
        break;
    case 8:
        if (flag_set_first_pending(self) && B(self, 0x43) != 1)
            anim_start_blended(self, 1, 0, 2);
        if (B(self, 0x60) & 2)
            moby_set_state(self, 1, 0);
        break;
    }
    actor_update_walk_motion(self);
}
