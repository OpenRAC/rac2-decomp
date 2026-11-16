#include "include_asm.h"

#include "common.h"
#define NULL ((void *)0)
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; Quad q[0x260]; } Hero;
typedef struct { Vector pos, v30, v40, v50; void *obj; int kind; } Hit;
extern char g_hero_state[];
extern char g_hero_position[];
extern u8 *g_hero_moby __attribute__((nosda));
extern s16 g_ray_hit_flag __attribute__((nosda));
extern int g_game_l06_frame_counter[] __attribute__((sda));
extern int g_ripple_l06_disturb_y[] __attribute__((sda));
extern u8 g_trace_start_pos[];
extern char g_str_actor_debug_a[], g_str_actor_debug_b[];
extern u8 *g_moby_l06_table __attribute__((sda));
extern int g_ripple_l06_disturb_x __attribute__((sda));
extern u8 g_next_state_table[9] __attribute__((sda));
extern u8 g_next_anim_table[9] __attribute__((sda));
extern void STUB_printf(const char *, ...);
extern int coll_test_point(void *, int, void *, float);
extern int GetCollHitMaterial(void);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern int FloatToInt(float);
extern void moby_mark_spawned(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float MobySpringTurn(void *, float, void *, float, float, float);
extern int moby_move_over_ground(void *, void *, void *, float, float, float, float, int);
extern int point_in_path_xy(void *, void *, int);
extern float coll_get_ground_height_at_position(void *, void *);
extern void gfx_update_color_fade_pal(void *, void *);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int IsPointInCuboid(void *, int);
extern void *part_spawn_drifting(void *, void *, int, float, float);
extern int PlayMobySound(int, int, void *);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern s32 hero_l00_set_action_pal(int, int);
extern void moby_update_empty_alt(void *, void *, void *);
extern float math_turn_angle_toward_target(void *, float, float, float, float, float);
extern int math_blend_scaled_count(void *, void *, int, int, float, float);
extern int func_001163B0(void);
extern int mine_fall_pal(void *, void *);
extern int moby_find_nearest_target(void *, void *, float);
extern void part_update_attached_scale(void *, int, void *, float);
extern int actor_classify_headroom(void *, void *);
extern void actor_start_size_anim(void *, void *);
extern int spawn_record_resolve_links(void *, void *);
extern void actor_choose_free_heading(void *, void *);
extern void actor_apply_fall_move_pal(void *, void *, float, float, float);
extern int actor_adjust_speed_facing(void *, void *, float, float, float, float, float, float, float);
extern void actor_try_pickup_transition_pal(void *, void *, int, int, float, float, float, float, float, int, int, int, void *);
extern int actor_probe_hits_target(void *, void *, float);
extern int group_is_member_in_state_range(void *, int, int);
#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define UH(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(int *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))

void UpdateMoby4070_pal(u8 *self) {
    Hit hit;
    Vector vec_head, vec_delta, vec_tmp1, vec_tmp2, vec_prev_pos, vec_target;
    u8 *vars;
    u8 *path_data;
    float *unused_ptr;
    u8 *self_pos_a, *self_pos_b, *self_pos_c, *vel_a, *vel_b, *vel_c, *vel_d, *vel_e;
    int ray_hit, timer_expired, close_enough, table_idx;
    u8 next_anim, next_state;
    u8 old_mode;
    int cur_index;
    int new_mode;
    float float_a, float_b, float_c;

    if (self != NULL && (vars = *(u8 **)(self + 0x68)) != NULL) {
        part_update_attached_scale(self, 0, vars + 0x140, 2.20000005f);
        if (B(self, 0x20) == 0) {
            if (spawn_record_resolve_links(self, vars) != 0) {
                STUB_printf(g_str_actor_debug_a, H(self, 0xB2));
                moby_mark_spawned(self);
                return;
            }
            goto check;
        }
        moby_find_nearest_target(self, &hit, 30.0f);
        moby_update_empty_alt(self, vars, vars + 0x20);
        gfx_update_color_fade_pal(self, vars + 0x50);
        timer_expired = math_fast_float_d(vars + 0x124) != 0;
        if (W(vars, 0x100) != 0 && B(self, 0x20) >= 7) {
            path_data = *(u8 **)(vars + 0x138);
            ray_hit = point_in_path_xy(&hit, path_data + 0x10, *(int *)path_data) != 0;
        } else {
            path_data = *(u8 **)(vars + 0x138);
            ray_hit = point_in_path_xy(g_hero_position, path_data + 0x10, *(int *)path_data) != 0;
            if (vec_distance_xy(self + 0x10, g_hero_position) < 30.0f) {
                hit.obj = *(void **)(g_hero_position + 0x2210);
                qcopy(&hit.pos, g_hero_position);
                qcopy(&hit.v30, g_hero_position + 0x10);
                qcopy(&hit.v40, g_hero_position + 0x50);
                qcopy(&hit.v50, g_hero_position + 0x60);
                hit.kind = 0;
            } else {
                hit.obj = NULL;
                qzero(&hit.pos);
                qzero(&hit.v30);
                qzero(&hit.v50);
                qzero(&hit.v40);
                hit.kind = 2;
            }
        }
        if (W(vars, 0x100) != 0) {
            path_data = *(u8 **)(vars + 0x118);
            point_in_path_xy(self + 0x10, path_data + 0x10, *(int *)path_data);
        }
        old_mode = B(self, 0xBC);
        next_state = 0xFF;
        new_mode = actor_classify_headroom(self, vars);
        next_anim = 0xFF;
        B(self, 0xBC) = new_mode;
        if (old_mode != (u8)new_mode) {
            table_idx = (u8)new_mode + old_mode * 3;
            next_state = g_next_state_table[table_idx];
            next_anim = g_next_anim_table[table_idx];
        }
        moby_transform_joint_to_world(self, 0, vec_head.f);
        if (coll_test_point(vec_head.f, 1, self, 0.800000012f) != 0 && GetCollHitMaterial() == 0) {
            float_a = **(float **)(vars + 0x11C);
            float_a -= F(vars, 0x120);
            float_a *= 0.5f;
            if (float_a < math_fabs(F(self, 0x18) - vec_head.f[2])) {
                float_a = (**(float **)(vars + 0x11C) - F(vars, 0x120)) * 0.5f;
            } else {
                float_a = math_fabs(F(self, 0x18) - vec_head.f[2]);
            }
            if (F(vars, 0xC8) < 0.0f) {
                float_a = -float_a;
            }
            if (B(self, 0x20) == 0xE || B(self, 0x20) == 0xC) {
                float_a *= 2.0f;
            }
            self_pos_a = self + 0x10;
            if (vec_distance_xy(self_pos_a, g_trace_start_pos) > 0.5f) {
                float_b = vec_distance_xy(self_pos_a, g_trace_start_pos) * 2.0f;
            } else {
                float_b = 1.0f;
            }
            if (g_game_l06_frame_counter[0] % 45 == H(self, 0xB2) && math_random_int_below(2) == 0) {
                RippleDisturb(g_ripple_l06_disturb_x, g_ripple_l06_disturb_y[0], 1, F(self, 0x10), F(self, 0x14), float_b, float_a);
            }
            if (g_game_l06_frame_counter[0] % ((func_001163B0() & 7) + 0x14) == 0) {
                float_c = math_random_float_range(1.5f, 2.4000001f);
                vec_head.f[0] += math_random_float_range(-0.150000006f, 0.150000006f);
                vec_head.f[1] += math_random_float_range(-0.150000006f, 0.150000006f);
                vec_head.f[2] = coll_get_ground_height_at_position(g_trace_start_pos, NULL);
                part_spawn_drifting(vec_head.f, NULL, -1, float_c, 5250.0f);
            }
        }
        if (F(vars, 0x13C) >= 1.0f) {
            *(Quad *)g_hero_position = *(Quad *)(self + 0x10);
        }
        cur_index = W(vars, 0x108);
        if (cur_index != -1 && B(*(u8 **)(g_moby_l06_table + (cur_index << 8) + 0x68), 0x14) != 0) {
            if (B(self, 0x43) != 0xD) {
                anim_start_blended_pal(self, 0xD, 0, 0xA);
            }
            B(self, 0x20) = 0x14;
        }
        switch (B(self, 0x20)) {
        case 0:
            STUB_printf(g_str_actor_debug_b);
            break;
        case 20:
            cur_index = W(vars, 0x108);
            if (cur_index != -1 && B(*(u8 **)(g_moby_l06_table + (cur_index << 8) + 0x68), 0x14) == 0) {
                B(self, 0x20) = 0x15;
            }
            break;
        case 21:
            if (UH(self, 0x96) >= 0x168) {
                if (B(self, 0x43) != 0) {
                    anim_start_blended_pal(self, 0, 0, 0xA);
                }
                UH(self, 0x96) = 0;
                B(self, 0x20) = 1;
            } else {
                actor_apply_fall_move_pal(self, vars, 0.006f, 0.020000001f, 0.16000001f);
                UH(self, 0x96) = UH(self, 0x96) + 1;
            }
            break;
        case 1:
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 0) {
                anim_start_blended_pal(self, 0, 0, 0xA);
            }
            if (ray_hit != 0 && hit.obj != NULL && hit.obj == g_hero_moby && group_is_member_in_state_range(self, 4, 6) == 0) {
                if (B(self, 0x43) != 1) {
                    anim_start_blended_pal(self, 1, 0, 0xA);
                }
                B(self, 0x20) = 4;
            }
            if (hit.obj != NULL && hit.obj == g_hero_moby && actor_probe_hits_target(self, hit.obj, 1.5f) != 0) {
                if (B(self, 0x43) != 2) {
                    anim_start_blended_pal(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                B(self, 0x20) = 5;
            } else if (timer_expired != 0) {
                if (B(self, 0x43) != 1) {
                    anim_start_blended_pal(self, 1, 0, 0xA);
                }
                W(vars, 0x124) = func_001163B0() % 200 + 0x12C;
                F(vars, 0x12C) = math_random_angle();
                B(self, 0x20) = 2;
            }
            FastVecScale(vars + 0xC0, vars + 0xC0, 0.94f);
            actor_apply_fall_move_pal(self, vars, 0.006f, 0.020000001f, 0.16000001f);
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 2:
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 1) {
                anim_start_blended_pal(self, 1, 0, 0xA);
            }
            if (ray_hit != 0 && hit.obj != NULL && hit.obj == g_hero_moby) {
                if (group_is_member_in_state_range(self, 4, 6) == 0) {
                    if (B(self, 0x43) != 1) {
                        anim_start_blended_pal(self, 1, 0, 0xA);
                    }
                    B(self, 0x20) = 4;
                }
            } else {
                MobySpringTurn(self, F(vars, 0x12C), vars + 0x110, 0.0006981318f, 0.0018151427f, 0.03490659f);
                F(self, 0xF4) = math_turn_angle_toward_target(vars + 0x114, F(self, 0xF4), 0.0f, 0.0006981318f, 0.0018151427f, 0.03490659f);
                if (timer_expired != 0 && IsPointInCuboid(self + 0x10, W(vars, 0x104)) != 0) {
                    if (B(self, 0x43) != 0) {
                        anim_start_blended_pal(self, 0, 0, 0xA);
                    }
                    W(vars, 0x124) = func_001163B0() % 120 + 0x3C;
                    B(self, 0x20) = 1;
                }
            }
            actor_choose_free_heading(self, vars);
            if (actor_adjust_speed_facing(self, vars, F(vars, 0x12C), 0.209439531f, 0.0024f, 0.52359885f, 0.0016000001f, 0.14000002f, 0.060000002f) != 0 && timer_expired != 0) {
                if (B(self, 0x43) != 0) {
                    anim_start_blended_pal(self, 0, 0, 0xA);
                }
                W(vars, 0x124) = func_001163B0() % 120 + 0x3C;
                B(self, 0x20) = 1;
            }
            if (hit.obj != NULL && hit.obj == g_hero_moby && actor_probe_hits_target(self, hit.obj, 1.5f) != 0) {
                if (B(self, 0x43) != 2) {
                    anim_start_blended_pal(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                B(self, 0x20) = 5;
            }
            actor_apply_fall_move_pal(self, vars, 0.006f, 0.020000001f, 0.16000001f);
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 4:
            self_pos_b = self + 0x10;
            close_enough = 1;
            float_c = mat_fast_helper_a(hit.pos.f[0] - F(self, 0x10), hit.pos.f[1] - F(self, 0x14));
            MobySpringTurn(self, float_c, vars + 0x110, 0.005026549f, 0.0f, 0.25132746f);
            { float t = -mat_fast_helper_a(vec_distance_xy(self_pos_b, &hit), hit.pos.f[2] - F(self, 0x18));
            F(self, 0xF4) = math_turn_angle_toward_target(vars + 0x114, F(self, 0xF4), t, 0.005026549f, 0.0f, 0.25132746f); }
            if (vec_distance_xy(self_pos_b, g_hero_position) < 3.0f) {
            } else {
                close_enough = 0;
            }
            if (close_enough != 0) {
                FastVecScale(vars + 0xC0, vars + 0xC0, 0.88f);
            }
            if (actor_adjust_speed_facing(self, vars, float_c, 0.209439531f, 0.008f, 0.52359885f, 0.0012f, 0.40000004f, 0.10000001f) != 0 && close_enough != 0 && (u32)(W(g_hero_position, 0x221C) - 0x11) < 2) {
                if (B(self, 0x43) != 2) {
                    anim_start_blended_pal(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                W(self, 0x98) = 0;
                B(self, 0x20) = 5;
                F(vars, 0x13C) = 0.0f;
                qcopy(vars + 0xF0, self_pos_b);
            }
            F(vars, 0x128) = hit.pos.f[2] - 0.25f;
            actor_apply_fall_move_pal(self, vars, 0.0152f, 0.0f, 0.76000005f);
            if (ray_hit == 0 || g_ray_hit_flag == 0) {
                if (B(self, 0x43) != 1) {
                    anim_start_blended_pal(self, 1, 0, 0xA);
                }
                B(self, 0x20) = 2;
            }
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 5:
            self_pos_c = self + 0x10;
            moby_transform_joint_to_world(self, 0, vec_head.f);
            FastVecSub(&vec_delta, vec_head.f, self_pos_c);
            float_b = mat_fast_helper_a(hit.pos.f[0] - vec_head.f[0], hit.pos.f[1] - vec_head.f[1]);
            MobySpringTurn(self, float_b, vars + 0x110, 0.005026549f, 0.0f, 0.25132746f);
            F(self, 0xF4) = F(self, 0xF4) * 0.84000003f;
            F(vars, 0x13C) = F(vars, 0x13C) + 0.0280000009f;
            qcopy(&vec_prev_pos, self_pos_c);
            FastVecSub(&vec_tmp1, &hit, &vec_delta);
            FastVecSub(&vec_tmp2, &vec_tmp1, vars + 0xF0);
            FastVecScale(&vec_tmp2, &vec_tmp2, F(vars, 0x13C) < 1.0f ? F(vars, 0x13C) : 1.0f);
            FastVecAdd(&vec_target, &vec_tmp2, vars + 0xF0);
            moby_move_over_ground(self, self_pos_c, &vec_target, 0.75f, 0.75f, 40.0f, 6.28318596f, 3);
            FastVecSub(vars + 0xC0, self_pos_c, &vec_prev_pos);
            if (F(vars, 0x13C) >= 1.0f) {
                ((Hero *)g_hero_state)->i[0x24CC / 4] = 0;
                hero_l00_set_action_pal(0x39, 1);
                W(((Hero *)g_hero_state)->ptr[0x2290 / 4], 0x9C) = -1;
                ((Hero *)g_hero_state)->b[0x22B5] = 1;
                B(self, 0x20) = 6;
            } else {
                F(vars, 0x12C) = float_b;
            }
            break;
        case 6:
            actor_choose_free_heading(self, vars);
            actor_adjust_speed_facing(self, vars, F(vars, 0x12C), 0.209439531f, 0.0024f, 0.52359885f, 0.0016000001f, 0.14000002f, 0.060000002f);
            actor_apply_fall_move_pal(self, vars, 0.0048f, 0.020000001f, 0.14000002f);
            MobySpringTurn(self, F(vars, 0x12C), vars + 0x110, 0.00062831864f, 0.0012566373f, 0.062831864f);
            F(self, 0xF4) = math_turn_angle_toward_target(vars + 0x114, F(self, 0xF4), 0.0f, 0.00062831864f, 0.0012566373f, 0.062831864f);
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 1) {
                anim_start_blended_pal(self, 1, 0, 0xA);
            }
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 7:
            if (ray_hit != 0) {
                if (B(self, 0x43) != 4) {
                    anim_start_blended_pal(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 9;
            } else if (timer_expired != 0) {
                if (B(self, 0x43) != 4) {
                    anim_start_blended_pal(self, 4, 0, 0xA);
                }
                W(vars, 0x124) = func_001163B0() % 200 + 0x12C;
                F(vars, 0x12C) = math_random_angle();
                B(self, 0x20) = 8;
            }
            vel_a = vars + 0xC0;
            FastVecScale(vel_a, vel_a, 0.94f);
            F(vars, 0xC8) = F(vars, 0xC8) - 0.19600002f;
            if (math_blend_scaled_count(self, vel_a, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(vel_a, vel_a, 0.5f);
            }
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 8:
            if (ray_hit != 0) {
                if (B(self, 0x43) != 4) {
                    anim_start_blended_pal(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 9;
            } else {
                MobySpringTurn(self, F(vars, 0x12C), vars + 0x110, 0.00031415932f, 0.00062831864f, 0.015707966f);
                F(self, 0xF4) = math_turn_angle_toward_target(vars + 0x114, F(self, 0xF4), 0.0f, 0.00031415932f, 0.00062831864f, 0.015707966f);
                if (timer_expired != 0 && IsPointInCuboid(self + 0x10, W(vars, 0x104)) != 0) {
                    if (B(self, 0x43) != 3) {
                        anim_start_blended_pal(self, 3, 0, 0xA);
                    }
                    W(vars, 0x124) = func_001163B0() % 120 + 0x3C;
                    B(self, 0x20) = 7;
                }
            }
            actor_choose_free_heading(self, vars);
            if (actor_adjust_speed_facing(self, vars, F(vars, 0x12C), 0.3490659f, 0.0012f, 1.0471977f, 0.0036000002f, 0.020000001f, 0.020000001f) != 0 && timer_expired != 0) {
                if (B(self, 0x43) != 3) {
                    anim_start_blended_pal(self, 3, 0, 0xA);
                }
                W(vars, 0x124) = func_001163B0() % 120 + 0x3C;
                B(self, 0x20) = 7;
            }
            vel_b = vars + 0xC0;
            F(vars, 0xC8) = F(vars, 0xC8) - 0.19600002f;
            if (math_blend_scaled_count(self, vel_b, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(vel_b, vel_b, 0.5f);
            }
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 9:
        case 10:
            float_a = mat_fast_helper_a(hit.pos.f[0] - F(self, 0x10), hit.pos.f[1] - F(self, 0x14));
            MobySpringTurn(self, float_a, vars + 0x110, 0.00031415932f, 0.00062831864f, 0.015707966f);
            if (actor_adjust_speed_facing(self, vars, float_a, 0.52359885f, 0.0016000001f, 1.57079649f, 0.0036000002f, 0.030000001f, 0.020000001f) != 0 && vec_distance_xy(self + 0x10, &hit) < 1.89999998f && B(self, 0x20) != 0xA) {
                if (B(self, 0x43) != 5) {
                    anim_start_blended_pal(self, 5, 0, 2);
                }
                B(self, 0x20) = 0xA;
            }
            vel_c = vars + 0xC0;
            F(vars, 0xC8) = F(vars, 0xC8) - 0.19600002f;
            if (math_blend_scaled_count(self, vel_c, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(vel_c, vel_c, 0.5f);
            }
            B(vars, 0x48) = FloatToInt(8.0f);
            B(vars, 0x4A) = FloatToInt(9.60000038f);
            if (ray_hit == 0) {
                if (B(self, 0x43) != 4) {
                    anim_start_blended_pal(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 8;
            }
            actor_try_pickup_transition_pal(self, vars, 0xA, 5, 17.0f, 20.0f, 1.0f, 1.0f, 1.0f, 4, 4, 0xB, hit.obj);
            if (B(self, 0x60) & 2) {
                if (B(self, 0x43) != 4) {
                    anim_start_blended_pal(self, 4, 0, 0xA);
                }
                W(vars, 0x124) = func_001163B0() % 200 + 0x12C;
                B(self, 0x20) = 8;
            }
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 11:
            if (B(self, 0x60) & 2) {
                B(self, 0x20) = 7;
            }
            break;
        case 12:
            if (mine_fall_pal(self, vars + 0x60) & 1) {
                actor_start_size_anim(self, vars);
            }
            break;
        case 13:
            if (B(self, 0x60) & 2) {
                actor_start_size_anim(self, vars);
            }
            break;
        case 14:
            if (mine_fall_pal(self, vars + 0x60) & (B(self, 0x60) & 2)) {
                SpawnExplosionEffects_pal(self, vars + 0xC0, NULL, 0.0f, 0.0f, 3, 3, 5, 2.0f, 1.0f, 4.0f, 1.0f, -1, 7.0f, 0, 1, -1, 0, 0x810001);
                moby_mark_spawned(self);
                return;
            }
            break;
        case 16:
            vel_d = vars + 0xC0;
            FastVecScale(vel_d, vel_d, 0.94f);
            F(vars, 0xC8) = F(vars, 0xC8) - 0.19600002f;
            math_blend_scaled_count(self, vel_d, 0x400, 0x10, 1.0f, 0.0f);
            if (B(self, 0x60) & 2) {
                actor_start_size_anim(self, vars);
            }
            break;
        case 15:
            vel_e = vars + 0xC0;
            FastVecScale(vel_e, vel_e, 0.94f);
            F(vars, 0xC8) = F(vars, 0xC8) - 0.19600002f;
            math_blend_scaled_count(self, vel_e, 0x400, 0x10, 1.0f, 0.0f);
            if (next_state != 0xFF) {
                if (B(self, 0x43) != next_anim) {
                    anim_start_blended_pal(self, next_anim, 0, 6);
                }
                B(self, 0x20) = next_state;
            }
            break;
        case 17:
            FastVecScale(vars + 0xC0, vars + 0xC0, 0.94f);
            if (B(self, 0x60) & 2) {
                actor_start_size_anim(self, vars);
            }
            break;
        }
    check:
        if (F(self, 0x10) < 2.0f || F(self, 0x10) > 1021.0f || F(self, 0x14) < 2.0f || F(self, 0x14) > 1021.0f || F(self, 0x18) < 2.0f || F(self, 0x18) > 1021.0f) {
            moby_mark_spawned(self);
        }
    }
}
