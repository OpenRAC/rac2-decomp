/* func_US2_L08_003C7F00, the USA v2.00 copy of func_L08_003C6AB0: the same C, where rename func_L08_002D2ED8 becomes func_US2_L08_002D31F8. */
/* func_US2_L08_003C7F00: the update of a rideable moby (levels 8, 19 and 30): a pvars block at moby+0x68, a seven-entry
 * state switch on moby+0x20, then a byte state on pvars+0x8A when the level flag is 8.
 *
 * What fixes the bytes:
 * - moby and pvars are real structures: a fixed scalar load cannot alias a varying structure member, so the tuning
 *   floats issue ahead of the stores between them without being const.
 * - The six inputs are scalars with their address taken, so they get their slots after the arrays. fire stays a
 *   pseudo that reload spills to the slot after them.
 * - The 64-byte inverse and the two vectors have their own blocks, which share one stack slot.
 * - ground + blend is an expression at each use: PRE makes the copy that retail keeps in $f21.
 * - The products are separate statements because fold rebalances four or more factors.
 * - `else t = 0` is a dead store that keeps the arm from if-conversion (retail has no movn); flow deletes it.
 * - scale holds pvars+0x78 before speed is loaded and frame holds 1/60 before its uses. Each shifts a live length in
 *   sched1's order, which decides local-alloc's FP registers in this long block (calls do not end it).
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } RideVector __attribute__((aligned(16)));
/* The initializer writes through +0x20; consumers also transport +0x24.
 * Its unknown final word remains opaque, with no invented initialization. */
typedef struct {
    RideVector direction;
    s32 owner, flags;
    u8 first, second;
    u16 objectId;
    f32 distance;
    s32 enabled;
    f32 opaque;
} RideQuery;
typedef struct { u8 b[0x400]; } Block400;
typedef struct { u8 pad[0xA]; u16 index; u8 tail[4]; } Row16;
typedef union { u8 b[0x400]; u32 w[0x100]; } Pad;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0x14];
    f32 x20;
    f32 x24;
    f32 x28;
    u8 pad2C[0x4];
    TI128 x30;
    u8 pad40[0x8];
    f32 x48;
    f32 x4C;
    u8 pad50[0x8];
    f32 x58;
    f32 x5C;
    f32 x60;
    s32 x64;
    f32 x68;
    u8 *x6C;
    u8 pad70[0x4];
    u8 *x74;
    f32 x78;
    s16 x7C;
    u16 x7E;
    u8 pad80[0x8];
    s16 x88;
    u8 x8A;
    u8 x8B;
    s16 x8C;
    u8 pad8E[0x9];
    u8 x97;
    u8 x98;
    u8 x99;
    u8 pad9A[0x6];
    u8 *xA0;
    s32 xA4;
    s32 xA8;
    s32 xAC;
} RideVars;
typedef struct {
    u8 pad0[0x10];
    RideVector pos;
    u8 x20;
    u8 pad21[0x3];
    u8 *x24;
    u8 pad28[0x4];
    f32 x2C;
    u8 pad30[0x1];
    u8 x31;
    u8 pad32[0x16];
    f32 x48;
    u8 pad4C[0x1C];
    u8 *x68;
    u8 pad6C[0x3];
    u8 x6F;
    u8 pad70[0x28];
    s32 x98;
    u8 pad9C[0xC];
    u8 xA8;
    u8 padA9[0x47];
    RideVector rot;
} RideMoby;

extern s32 vec_fast_helper_a(void *);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern void gfx_start_color_fade(void *, void *);
extern void gfx_update_color_fade(void *, void *);
extern f32 func_002A0558(void *, void *);
extern s32 TryClaimNotice(s32, s32, s32);
extern s32 func_US2_L08_002D31F8(s32, s32);
extern void set_hero_animation(int, int, f32);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern void moby_mark_nearby_creatures_active(char *);
extern void hero_read_aim_input_values(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern f32 FastVecLength(void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fabs(f32);
extern f32 IntegerPower(s32, f32);
extern void FastVecAdd(void *, void *, void *);
extern f32 coll_probe_ground_height_below(void *, int, f32);
extern int GetCollHitMaterial(void);
extern f32 fast_subtract_rotations(f32, f32);
extern void FastVecScale(void *, void *, f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecCross(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void make_hit_descriptor(f32, void *, void *, s32, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern s32 coll_process_triangles(void *, f32);
extern s32 coll_test_point(void *, s32, void *, f32);
extern f32 FastVecDot(void *, void *);
extern void part_emit_disk_particles(void *, void *, s32, f32, f32, f32, f32, f32, f32);
extern s32 coll_process_hit(f32, void *, s32, void *, void *);
extern void moby_mark_spawned(void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern void *part_spawn_attached_effect(void *, void *);
extern void moby_store_position_private(void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void UpdateAttachedChildObjects(void *);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, f32, f32, f32);

extern u8 g_pad_state[];
extern u8 g_hero_state[];
extern s32 g_current_map_index MACRO_ADDR;
extern s32 g_cutscene_l08_active_flag __attribute__((sda));
extern f32 g_hover_speed_gain __attribute__((sda));
extern s32 g_hover_timer_limit __attribute__((sda));
extern s32 g_hover_timer_margin __attribute__((sda));
extern f32 g_hover_hero_distance_limit __attribute__((sda));
extern f32 g_hover_sway_scale __attribute__((sda));
extern f32 g_hover_sway_rate __attribute__((sda));
extern f32 g_hover_tilt_degrees __attribute__((sda));
extern f32 g_hover_tilt_rate_x __attribute__((sda));
extern f32 g_hover_tilt_rate_y __attribute__((sda));
extern f32 g_hover_slew_rate __attribute__((sda));
extern f32 g_hover_velocity_damp __attribute__((sda));
extern f32 g_hover_drag_scale __attribute__((sda));
extern f32 g_hover_time_scale __attribute__((sda));
extern f32 g_hover_cruise_speed __attribute__((sda));
extern f32 g_hover_ground_height_high __attribute__((sda));
extern f32 g_hover_height_spring __attribute__((sda));
extern f32 g_hover_probe_depth __attribute__((sda));
extern s32 g_hover_anim_next __attribute__((sda));
extern s32 g_hover_anim_current __attribute__((sda));
extern f32 g_hover_gravity __attribute__((sda));
extern f32 g_hover_air_damp __attribute__((sda));
extern f32 g_hover_ground_damp __attribute__((sda));
extern f32 g_hover_roll_gain __attribute__((sda));
extern f32 g_hover_roll_target_scale __attribute__((sda));
extern f32 g_hover_speed_scale __attribute__((sda));
extern f32 g_hover_steer_gain __attribute__((sda));
extern f32 g_hover_gain_blend __attribute__((sda));
extern f32 g_hover_pitch_follow_a __attribute__((sda));
extern f32 g_hover_pitch_follow_b __attribute__((sda));
extern f32 g_hover_pitch_damp __attribute__((sda));
extern f32 g_hover_turn_blend __attribute__((sda));
extern f32 g_hover_top_speed_scale __attribute__((sda));
extern f32 g_hover_bank_damp __attribute__((sda));
extern f32 g_hover_hit_radius __attribute__((sda));
extern s32 g_gauge_tex_base_h __attribute__((sda));
extern f32 g_hover_height_scale __attribute__((sda));
extern f32 g_hover_hit_damage __attribute__((sda));
extern f32 g_hover_wall_hit_radius __attribute__((sda));
extern f32 g_hover_probe_lift __attribute__((sda));
extern f32 g_hover_min_move_speed __attribute__((sda));
extern f32 g_hover_max_health __attribute__((sda));
extern s32 g_hover_joint_index __attribute__((sda));
extern f32 g_hover_hero_z_offset __attribute__((sda));
extern f32 g_hover_speed_to_tilt __attribute__((sda));
extern f32 g_hover_blend_step_down __attribute__((sda));
extern f32 g_hover_blend_step_up __attribute__((sda));
extern f32 g_hover_ground_height_low __attribute__((sda));
extern f32 g_hover_blend_offset __attribute__((sda));
extern f32 g_hover_rise_scale __attribute__((sda));
extern u16 g_hover_wait_frames __attribute__((sda));
extern f32 g_hover_climb_scale __attribute__((sda));
extern u8 *g_color_row_ptr __attribute__((sda));
extern s32 g_hover_init_done __attribute__((sda));
extern s32 g_hover_frame_limit __attribute__((sda));
extern s32 g_hover_step_count __attribute__((sda));
extern f32 g_hover_emit_a_color_r __attribute__((sda));
extern f32 g_hover_emit_a_param_x __attribute__((sda));
extern f32 g_hover_emit_a_param_y __attribute__((sda));
extern s32 g_hover_emit_a_count __attribute__((sda));
extern f32 g_hover_emit_a_color_g __attribute__((sda));
extern f32 g_hover_emit_a_color_b __attribute__((sda));
extern f32 g_hover_emit_b_color_rg __attribute__((sda));
extern f32 g_hover_emit_b_param_x __attribute__((sda));
extern f32 g_hover_emit_b_param_y __attribute__((sda));
extern s32 g_hover_emit_b_count __attribute__((sda));
extern f32 g_hover_emit_b_color_b __attribute__((sda));
extern f32 g_hover_emit_b_color_a __attribute__((sda));
extern f32 g_hover_emit_c_color_rg __attribute__((sda));
extern f32 g_hover_emit_c_param_x __attribute__((sda));
extern f32 g_hover_emit_c_param_y __attribute__((sda));
extern s32 g_hover_emit_c_count __attribute__((sda));
extern f32 g_hover_emit_c_color_b __attribute__((sda));
extern f32 g_hover_emit_c_color_a __attribute__((sda));
extern u8 g_hover_byte_param __attribute__((sda));
extern f32 g_hud_l08_bar_threshold MACRO_ADDR;
extern u8 *g_effect_row_buffer MACRO_ADDR;
extern u8 g_hero_l08_extra_state[];
extern u8 g_hero_position_vec[];
extern u8 g_row_index_table[];
extern u8 g_collision_l08_result[];
extern u8 g_collision_l08_hit_point[];
extern u8 g_collision_aim_vector[];
extern Block400 g_hud_gauge_values;
extern void hud_draw_health_gauge(void);

void RideableMobyUpdate_us2(RideMoby *moby)
{
    f32 dir[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    union {
        f32 basis[4][4];
        struct { RideQuery request; RideVector position; } query;
    } work;
    f32 v90[4] __attribute__((aligned(16)));
    f32 turn;
    f32 speed;
    f32 pitch;
    f32 bank;
    f32 lift;
    f32 thrust;
    s32 fire;
    RideVars *vars;
    u8 *hit;
    u8 *other;

    vars = (RideVars *)moby->x68;
    if (vec_fast_helper_a((u8 *)vars + 0x8B) != 0) {
        vars->xA0 = 0;
    }
    if (moby->x20 != 0) {
        moby->pos.f[2] = vars->x58;
        hit = part_find_owned_effect_slot(moby, 1, 0);
        if (hit != 0 && (other = *(u8 **)(hit + 0x20)) != 0) {
            s16 kind = *(s16 *)(other + 0xAA);
            if (kind != 0x85C && kind != 0x942 && kind != 0xFFF) {
                if (other != vars->xA0 || vars->x8B == 0) {
                    vars->x97 = 0xD2;
                    vars->x98 = 0xD2;
                    vars->x99 = 0xD2;
                    gfx_start_color_fade(moby, (u8 *)vars + 0x90);
                    vars->x60 -= *(f32 *)(hit + 0x2C);
                    ((Hero *)g_hero_state)->f[0x183C / 4] = vars->x60;
                    if (vars->x60 <= 0.0f) {
                        moby->x20 = 5;
                    }
                    vars->xA0 = *(u8 **)(hit + 0x20);
                    vars->x8B = g_hover_byte_param;
                }
            }
        }
        moby->xA8 = 0xFF;
    } else {
        vars->x58 = moby->pos.f[2];
    }
    gfx_update_color_fade(moby, (u8 *)vars + 0x90);
    moby->x2C = *(f32 *)(moby->x24 + 0x24) * g_hover_height_scale;
    if (((Hero *)g_hero_state)->ptr[0x1830 / 4] == (u8 *)moby) {
        ((Hero *)g_hero_state)->i[0x1848 / 4] = ((Hero *)g_hero_state)->f[0x183C / 4] / g_hover_max_health * 200.0f;
    }
    fire = 0;
    switch (moby->x20) {
    case 0: {
        u8 *src = g_effect_row_buffer + ((Row16 *)g_row_index_table)[vars->x64 + g_gauge_tex_base_h].index * 16;
        s32 done = g_hover_init_done;
        g_color_row_ptr = src;
        vars->xA8 = 0xFF;
        vars->xA4 = 0;
        if (done == 0) {
            g_hud_gauge_values = *(Block400 *)src;
        }
        g_hover_init_done = 1;
        vars->x30 = moby->pos.q;
        qzero_nc(vars);
        {
            f32 health = g_hover_max_health;
            vars->x60 = health;
            ((Hero *)g_hero_state)->f[0x183C / 4] = health;
            ((Hero *)g_hero_state)->f[0x1840 / 4] = health;
        }
        vars->x74 = 0;
        moby->x20 = 1;
        vars->x78 = 0.0f;
        vars->xAC = 0;
        break;
    }
    case 1:
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1C || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x16
            || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x39 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x6F) {
            break;
        }
        if (((Hero *)g_hero_state)->i[0x229C / 4] == 2 || ((Hero *)g_hero_state)->i[0x229C / 4] == 4
            || ((Hero *)g_hero_state)->i[0x229C / 4] == 3 || ((Hero *)g_hero_state)->i[0x229C / 4] >= 0xD
            || ((Hero *)g_hero_state)->i[0x229C / 4] == 7 || ((Hero *)g_hero_state)->i[0x229C / 4] == 0xA
            || ((Hero *)g_hero_state)->i[0x229C / 4] == 0x10 || ((Hero *)g_hero_state)->i[0x229C / 4] == 5) {
            break;
        }
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x62) {
            break;
        }
        if (((Hero *)g_hero_state)->i[0x24CC / 4] <= 0) {
            break;
        }
        if (g_cutscene_l08_active_flag != 0) {
            break;
        }
        if (((Hero *)g_hero_state)->i[0x340 / 4] == 0) {
            break;
        }
        if (((Hero *)g_hero_state)->ptr[0x33C / 4] != 0) {
            s16 kind = *(s16 *)(((Hero *)g_hero_state)->ptr[0x33C / 4] + 0xAA);
            if (kind == 0x13E || kind == 0x46F) {
                break;
            }
        }
        if (func_002A0558(moby, ((Hero *)g_hero_state)->ptr[0x2290 / 4]) < g_hover_hero_distance_limit
            && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x31) {
            s32 t = TryClaimNotice(7, 0x12ea, 1) != 0;
            if (((Pad *)g_pad_state)->w[0x1A4 / 4] & 0x10) {
                fire = t;
            } else {
                t = 0;
            }
        }
        if (fire != 0) {
            func_US2_L08_002D31F8(0x31, 0);
            set_hero_animation(g_hover_anim_next, 0, 15.0f);
            *(TI128 *)(g_hero_state + 0x90) = moby->rot.q;
            *(TI128 *)(g_hero_state + 0x80) = moby->pos.q;
            ((Hero *)g_hero_state)->ptr[0x1830 / 4] = (u8 *)moby;
            moby->x20 = 3;
            *(s32 *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x9C) = -1;
        }
        /* fallthrough */
    case 3: {
        f32 sign;
        f32 blend;
        f32 cruise;
        f32 ground;
        s32 landed;
        s32 steer;
        f32 roll;
        f32 scale;

        moby->x98 = 0;
        FastDecTimer((u8 *)vars + 0x7C);
        math_fast_float_d((u8 *)vars + 0xAC);
        {
            f32 zero = 0.0f;
            turn = zero;
            speed = zero;
            pitch = zero;
            bank = zero;
            lift = zero;
            thrust = zero;
        }
        if (moby->x20 == 3) {
            if ((((Pad *)g_pad_state)->w[0x1A0 / 4] & 8) && vars->x7C == 0) {
                u8 **list = (u8 **)((u8 *)vars + 0x80);
                u16 wait;
                list += vars->x7E & 1;
                *(*list + 0xBC) = 1;
                wait = g_hover_wait_frames;
                vars->x7E ^= 1;
                vars->x7C = wait;
            }
            if (((Pad *)g_pad_state)->w[0x1A0 / 4] & 4) {
                vars->x78 -= g_hover_blend_step_down;
                if (math_random_int_below(9) == 0 || (((Pad *)g_pad_state)->w[0x1A4 / 4] & 4)) {
                    moby_mark_nearby_creatures_active((char *)moby);
                }
            } else {
                vars->x78 += g_hover_blend_step_up;
            }
            if (g_hover_anim_current != g_hover_anim_next && g_hover_anim_next != -1) {
                set_hero_animation(g_hover_anim_next, 0, 15.0f);
            }
            hero_read_aim_input_values(&turn, &speed, &pitch, &bank, &lift, &thrust);
        } else {
            vars->x78 -= g_hover_blend_step_down;
        }
        if (vars->x78 > 1.0f) {
            vars->x78 = 1.0f;
        } else if (vars->x78 < 0.0f) {
            vars->x78 = 0.0f;
        }
        scale = vars->x78;
        sign = 1.0f;
        speed *= scale;
        bank += 1.0f - vars->x78;
        lift *= vars->x78;
        thrust *= vars->x78;
        vars->x5C = speed;
        blend = g_hover_ground_height_high * vars->x78 + g_hover_ground_height_low * (1.0f - vars->x78);
        pitch = pitch * 0.017453294f;
        pitch *= g_hover_pitch_damp;
        {
            f32 raw = FastVecLength(vars);
            f32 frame = 0.016666668f;
            f32 cur = raw * vars->x78;
            f32 top = g_hover_top_speed_scale * frame;
            f32 lim = cur < top ? cur : top;
            f32 rate, slew, target, gain, rad;

            rate = turn * (lim / top * g_hover_turn_blend + (1.0f - g_hover_turn_blend)
                + g_hover_blend_offset * (1.0f - vars->x78));
            slew = rate * 0.000290888245f;
            cruise = g_hover_cruise_speed * frame;
            vars->x28 = FastAddRotations(vars->x28, g_hover_slew_rate * slew);
            gain = g_hover_gain_blend * speed + (1.0f - g_hover_gain_blend);
            rad = turn * 0.017453294f;
            target = g_hover_roll_target_scale * rad * vars->x78;
            vars->x20 += (target * gain - moby->rot.f[0]) * g_hover_roll_gain;
            dir[0] = math_fast_sin_or_cos_a(vars->x28);
            dir[1] = math_fast_sin_or_cos_b(vars->x28);
            dir[2] = 0.0f;
            {
                f32 zero = dir[2];
                if (speed < zero) {
                    speed *= g_hover_speed_scale;
                }
                if (speed < zero) {
                    sign = -1.0f;
                }
            }
            landed = 0;
            {
                f32 s = math_fabs(turn), k = IntegerPower(2, (cruise - cur) / cruise);
                {
                    f32 t = speed + g_hover_steer_gain * s * sign;
                    t *= 0.00027777778f;
                    moby->x48 += (speed * g_hover_speed_to_tilt - moby->x48) * 0.02f;
                    t *= g_hover_time_scale;
                    roll = t * k;
                }
            }
        }
        FastVecAdd(v40, (u8 *)moby + 0x10, vars);
        ground = coll_probe_ground_height_below(v40, 0, 0.5f);
        if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 0xB) {
            landed = 1;
        }
        if (moby->pos.f[2] < ground + blend + 0.3f) {
            if (landed) {
                moby->x20 = 5;
            }
        }
        if (g_hover_timer_limit - g_hover_timer_margin < vars->xAC) {
            vars->x8 += g_hover_speed_gain * 0.00027777778f;
        } else {
            vars->x8 -= g_hover_gravity * 0.00027777778f;
        }
        if (ground != 0.0f) {
            steer = 1;
            if (ground + blend < v40[2]) {
                vars->x24 = FastAddRotations(vars->x24,
                    fast_subtract_rotations(pitch, vars->x24) * g_hover_pitch_follow_b);
                if (g_current_map_index == 8) {
                    steer = 0;
                }
            } else {
                if (vars->xAC == 0 && thrust > 0.2f) {
                    vars->xAC = g_hover_timer_limit;
                }
                if (v40[2] + 0.1f < ground || landed) {
                    v40[2] = ground;
                    FastVecScale(vars, vars, g_hover_ground_damp);
                }
                vars->x8 += ((ground + blend - v40[2]) * g_hover_height_spring - vars->x8) * g_hover_height_spring;
                if (bank > 0.0f) {
                    f32 damp = 1.0f - g_hover_bank_damp * bank;
                    vars->x0 *= damp;
                    vars->x4 *= damp;
                }
                vec_scale_to_length(work.basis[2], g_collision_aim_vector, 1.0f);
                FastVecCross(work.basis[1], (u8 *)moby + 0xC0, work.basis[2]);
                FastVecCross(work.basis[0], work.basis[1], work.basis[2]);
                qzero_nc(work.basis[3]);
                mat_get_euler_angles(work.basis, v90);
                {
                    f32 half = pitch * 0.5f;
                    f32 rise = g_hover_rise_scale * (vars->x78 + 1.0f);
                    vars->x24 = FastAddRotations(vars->x24,
                        fast_subtract_rotations(FastAddRotations(-v90[1], half * rise),
                            vars->x24) * g_hover_pitch_follow_a);
                }
                FastVecScale(vars, vars, g_hover_velocity_damp);
                {
                    f32 inverse[4][4] __attribute__((aligned(16)));

                    matrix_from_basis_rows(inverse, (u8 *)moby + 0xC0);
                    transform_vector(vars, vars, inverse);
                }
                vars->x4 *= g_hover_drag_scale;
                matrix_mul_vec3(vars, vars, (u8 *)moby + 0xC0);
            }
            if (steer) {
                vec_scale_to_length(v30, (u8 *)moby + 0xC0, roll);
                {
                    f32 climb = lift * 0.00027777778f;
                    vec_scale_to_length(work.basis[0], (u8 *)moby + 0xD0, g_hover_climb_scale * climb * vars->x78);
                }
                FastVecAdd(v30, v30, work.basis[0]);
                FastVecAdd(vars, vars, v30);
            }
        }
        make_hit_descriptor(g_hover_hit_damage, &work.query.request, moby, 0x10000, vars);
        moby->pos.q = *(TI128 *)v40;
        moby_transform_joint_to_world(moby, 0, work.query.position.f);
        work.query.position.f[2] += g_hover_probe_depth - g_hover_ground_height_low;
        FastVecSub(v90, (u8 *)moby + 0x10, work.query.position.f);
        moby->x98 = 0;
        {
            s32 found = coll_process_triangles(work.query.position.f, g_hover_probe_depth);
            if (found == 0) {
                found = coll_test_point(work.query.position.f, 2, moby, g_hover_probe_depth);
            }
            moby->x98 = *(s32 *)(moby->x24 + 0x10);
            if (found != 0) {
                u8 *col;
                if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 0xB) {
                    moby->x20 = 5;
                }
                col = g_collision_l08_result;
                if (*(u8 **)(col + 0x18) != ((Hero *)g_hero_state)->ptr[0x2290 / 4]) {
                    f32 vA0[4] __attribute__((aligned(16)));
                    f32 vB0[4] __attribute__((aligned(16)));

                    *(f32 *)(col + 0x30) -= work.query.position.f[0];
                    *(f32 *)(col + 0x34) -= work.query.position.f[1];
                    *(f32 *)(col + 0x30) *= vars->x78;
                    *(f32 *)(col + 0x34) *= vars->x78;
                    *(f32 *)(col + 0x30) += work.query.position.f[0];
                    *(f32 *)(col + 0x34) += work.query.position.f[1];
                    FastVecAdd((u8 *)moby + 0x10, col + 0x30, v90);
                    FastVecCross(vB0, col + 0x40, vars);
                    FastVecCross(vA0, vB0, col + 0x40);
                    vec_scale_to_length(vA0, vA0, 1.0f);
                    vec_scale_to_length(vars, vA0, FastVecDot(vars, vA0) * vars->x78);
                    FastVecScale(vars, vars, g_hover_air_damp);
                }
            }
        }
        if (moby->x20 == 3) {
            if (vars->x78 < 0.98f && (((Pad *)g_pad_state)->w[0x1A0 / 4] & 4)) {
                if (vars->x68 < g_hud_l08_bar_threshold) {
                    part_emit_disk_particles(moby, g_collision_l08_hit_point, g_hover_emit_b_count, g_hover_emit_b_param_x, g_hover_emit_b_param_y,
                        g_hover_emit_b_color_rg, g_hover_emit_b_color_rg, g_hover_emit_b_color_b, g_hover_emit_b_color_a);
                    if (math_random_int_below(9) == 0) {
                        f32 amount = (1.0f - vars->x78) * 0.1f;
                        u8 *shake = g_hero_l08_extra_state;
                        *(s32 *)(shake + 0x168) = 0x14;
                        *(s32 *)(shake + 0x16C) = 0;
                        *(f32 *)(shake + 0x160) = amount;
                    }
                } else {
                    part_emit_disk_particles(moby, g_collision_l08_hit_point, g_hover_emit_c_count, g_hover_emit_c_param_x, g_hover_emit_c_param_y,
                        g_hover_emit_c_color_rg, g_hover_emit_c_color_rg, g_hover_emit_c_color_b, g_hover_emit_c_color_a);
                }
            }
            part_emit_disk_particles(moby, g_collision_l08_hit_point, g_hover_emit_a_count, g_hover_emit_a_param_x, g_hover_emit_a_param_y,
                g_hover_emit_a_color_r, g_hover_emit_a_color_g, g_hover_emit_a_color_b, 1.0f);
        }
        moby_transform_joint_to_world(moby, 0, work.query.position.f);
        work.query.position.f[2] += g_hover_probe_lift;
        coll_process_hit(g_hover_hit_radius, work.query.position.f, 0, moby, &work.query.request);
        if (FastVecLength(vars) > g_hover_min_move_speed * 0.016666668f) {
            f32 vA0[4] __attribute__((aligned(16)));

            moby_transform_joint_to_world(moby, 3, vA0);
            coll_process_hit(g_hover_wall_hit_radius, vA0, 0, moby, &work.query.request);
        }
        if (fire == 0 && ((Hero *)g_hero_state)->ptr[0x1830 / 4] == (u8 *)moby && (((Pad *)g_pad_state)->w[0x1A4 / 4] & 0x10)) {
            moby->x20 = 4;
        }
        break;
    }
    case 4:
        moby->x98 = *(s32 *)(moby->x24 + 0x10);
        *(s32 *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x9C) = 0;
        func_US2_L08_002D31F8(0, 1);
        ((Hero *)g_hero_state)->h[0x1834 / 2] = -1;
        ((Hero *)g_hero_state)->f[0x108 / 4] = 0.16666667f;
        ((Hero *)g_hero_state)->ptr[0x1830 / 4] = 0;
        ((Hero *)g_hero_state)->f[0x88 / 4] += 1.0f;
        if (vars->x74 != 0) {
            moby_mark_spawned(vars->x74);
        }
        vars->x74 = 0;
        vars->x88 = 0;
        vars->x8A = 0;
        moby->x20 = 1;
        break;
    case 5:
        moby->x98 = *(s32 *)(moby->x24 + 0x10);
        *(s32 *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x9C) = 0;
        func_US2_L08_002D31F8(0, 1);
        moby_transform_joint_to_world(moby, 0, dir);
        SpawnExplosionEffects(moby, vars, dir, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        moby->pos.q = vars->x30;
        ((Hero *)g_hero_state)->h[0x1834 / 2] = -1;
        ((Hero *)g_hero_state)->ptr[0x1830 / 4] = 0;
        if (vars->x74 != 0) {
            moby_mark_spawned(vars->x74);
        }
        vars->x74 = 0;
        vars->x88 = 0;
        vars->x8A = 0;
        moby->x20 = 0;
        break;
    case 6:
        break;
    }
    vars->x58 = moby->pos.f[2];
    {
        f32 t = vars->x78 * 0.000290888245f;
        vars->x48 = FastAddRotations(vars->x48, g_hover_sway_rate * t);
    }
    {
        f32 t;
        vars->x4C = math_fast_sin_or_cos_b(vars->x48) * g_hover_sway_scale * vars->x78;
        moby->pos.f[2] += vars->x4C * vars->x78;
        t = vars->x78 * 0.000290888245f;
        moby_scale_owner_words_by_angles(moby, (u8 *)vars + 0x50, (u8 *)vars + 0x54, g_hover_tilt_degrees * 0.017453294f,
            g_hover_tilt_rate_x * t, g_hover_tilt_rate_y * t);
    }
    moby->rot.f[2] = vars->x28;
    moby->rot.f[0] = FastAddRotations(moby->rot.f[0], vars->x20);
    moby->rot.f[1] = FastAddRotations(moby->rot.f[1], vars->x24);
    if (moby->x20 == 3) {
        if (g_current_map_index == 8) {
            switch (vars->x8A) {
            case 0:
                if (vars->x68 < g_hud_l08_bar_threshold) {
                    vars->x8A = 1;
                    vars->x88 = 0;
                }
                break;
            case 1: {
                s32 limit = g_hover_frame_limit;
                vars->x88 += 1;
                if (limit < vars->x88) {
                    vars->x88 = g_hover_frame_limit;
                }
                if (vars->x68 > g_hud_l08_bar_threshold) {
                    vars->x8A = 3;
                } else if (vars->x88 >= g_hover_frame_limit) {
                    vars->x8A = 2;
                }
                break;
            }
            case 2:
                if (vars->x68 > g_hud_l08_bar_threshold) {
                    vars->x8A = 3;
                }
                break;
            case 3:
                FastDecTimer((u8 *)vars + 0x88);
                if (vars->x68 < g_hud_l08_bar_threshold) {
                    vars->x8A = 1;
                } else if (vars->x88 == 0) {
                    vars->x8A = 0;
                }
                break;
            }
            if (vars->x8A != 0 && vars->x6C != 0) {
                u8 *anim = *(u8 **)(vars->x6C + 0x68);
                vars->x8C = FloatToInt(IntToFloat((g_hover_step_count - 1) << 5)
                    * IntToFloat(*(s32 *)(anim + 0x4)) / (IntToFloat(*(s32 *)(anim + 0x0)) * 60.0f));
            } else {
                vars->x8C = 0x200;
            }
            if (vars->x6C != 0) {
                if (vars->x74 == 0) {
                    vars->x74 = part_spawn_attached_effect(moby, vars->x6C + 0x10);
                } else {
                    moby_store_position_private(vars->x74, vars->x6C + 0x10);
                }
            } else if (vars->x74 != 0) {
                moby_mark_spawned(vars->x74);
                vars->x74 = 0;
            }
        }
        moby_transform_joint_to_world(moby, g_hover_joint_index, g_hero_state + 0x80);
        ((Hero *)g_hero_state)->f[0x88 / 4] += g_hover_hero_z_offset;
        *(TI128 *)(g_hero_state + 0x90) = moby->rot.q;
        gfx_add_draw_callback_third(hud_draw_health_gauge, moby);
    }
    moby->x98 = *(s32 *)(moby->x24 + 0x10);
    if (moby->x31 != 0 && fast_vec_dist((u8 *)moby + 0x10, g_hero_position_vec) < 64.0f) {
        moby_update_ground_check(moby);
        moby->x6F = 0x3C;
    }
    vars->x6C = 0;
    vars->x68 = 1000000.0f;
    UpdateAttachedChildObjects(moby);
}
