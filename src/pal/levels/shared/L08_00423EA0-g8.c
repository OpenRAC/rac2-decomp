#include "common.h"

/* func_PAL_L08_00423EA0, the PAL copy of func_L08_0041EBF8: the same hover-vehicle update, where
   the per-frame float steps and timers are scaled for 50 Hz. D_L08_001B1B64 is read as a word here,
   since the scale needs its whole value. Same profile as the template's unit (config/cflags.txt). */

typedef struct VehicleVars VehicleVars;

/* The vehicle moby: only the fields this update touches. */
typedef struct VehicleMoby {
    u8 pad00[0x10];
    float pos[4];             /* 0x10 */
    u8 state;                 /* 0x20 */
    u8 pad21[3];
    u8 *class_ptr;               /* 0x24 */
    u8 pad28[4];
    float f2c;                /* 0x2c */
    u8 pad30;
    u8 drawn;                 /* 0x31 */
    u8 pad32[2];
    u16 mode_bits;             /* 0x34 */
    u8 pad36[0x0c];
    u8 seq_a;                  /* 0x42 */
    u8 seq_b;                  /* 0x43 */
    u8 pad44[0x1c];
    u8 f60;                   /* 0x60 */
    u8 pad61[7];
    VehicleVars *vars_ptr;       /* 0x68 */
    u8 pad6c[3];
    u8 f6f;                   /* 0x6f */
    u8 pad70[0x28];
    s32 coll_data;             /* 0x98 */
    s32 f9c;                  /* 0x9c */
    u8 padA0[8];
    u8 impact;                /* 0xa8 */
    u8 padA9[0x17];
    float mtx[3][4];          /* 0xc0 */
    float rot[4];             /* 0xf0 */
} VehicleMoby;

/* Its instance data (moby + 0x68). */
struct VehicleVars {
    float vel[4];             /* 0x00 */
    u8 pad10[0x10];
    float roll;               /* 0x20 */
    float pitch;              /* 0x24 */
    float yaw;                /* 0x28 */
    u8 pad2c[4];
    float home[4];            /* 0x30 */
    u8 pad40[8];
    float bob_phase;           /* 0x48 */
    float bob_offset;          /* 0x4c */
    float sway[2];            /* 0x50 */
    float last_z;              /* 0x58 */
    float throttle;           /* 0x5c */
    float health;             /* 0x60 */
    u8 pad64[4];
    float f68;                /* 0x68 */
    u8 *f6c;                  /* 0x6c */
    u8 pad70[4];
    void *f74;                /* 0x74 */
    float power;              /* 0x78 */
    s16 timer7c;              /* 0x7c */
    u8 pad7e[0x0a];
    s16 timer88;              /* 0x88 */
    u8 mode8a;                /* 0x8a */
    u8 hit_cooldown;           /* 0x8b */
    s16 f8c;                  /* 0x8c */
    u8 pad8e[2];
    u8 flash[7];              /* 0x90 */
    u8 flash_rgb[3];           /* 0x97 */
    u8 pad9a[6];
    u8 *last_hit;              /* 0xa0 */
    s32 fa4;                  /* 0xa4 */
    s32 fa8;                  /* 0xa8 */
    u8 padac[4];
    struct {
        u8 hdr[0x10];
        float mtx[3][4];
    } rotor[3];               /* 0xb0 */
    float angle[3];           /* 0x170 */
    float f17c;               /* 0x17c */
    float rate[3];            /* 0x180 */
    s32 sound;                /* 0x18c */
    s32 f190;                 /* 0x190 */
    s32 f194;                 /* 0x194 */
    u8 pad198[4];
    s32 f19c;                 /* 0x19c */
    u8 pad1a0[4];
    s32 fx1a4;                /* 0x1a4 */
    s32 fx1a8;                /* 0x1a8 */
    s32 fx1ac;                /* 0x1ac */
    s32 fx1b0;                /* 0x1b0 */
    s32 fx1b4;                /* 0x1b4 */
    u8 pad1b8[8];
    float trail[4];           /* 0x1c0 */
};

typedef struct {
    u8 pad00[0x80];
    float position[4];
    float rotation[4];
    u8 padA0[0x2d0 - 0xa0];
    float camera_position[4];
    u8 pad2E0[0x33c - 0x2e0];
    u8 *attachment;
    s32 available;
    u8 pad344[0x1830 - 0x344];
    VehicleMoby *vehicle;
    u8 pad1834[8];
    float health;
    float max_health;
    u8 pad1844[4];
    s32 health_bar;
    u8 pad184C[0x2290 - 0x184c];
    VehicleMoby *moby;
    s32 animation_state;
    u8 pad2298[4];
    s32 movement_state;
    u8 pad22A0[0x22b5 - 0x22a0];
    u8 vehicle_control;
    u8 pad22B6[0x24cc - 0x22b6];
    s32 health_available;
} VehiclePlayerState;
extern VehiclePlayerState D_00189E20_14;
extern s32 g_cutscene_l08_active_flag;
extern float g_mining_vehicle_class_scale __attribute__((sda));
extern s32 g_mining_hit_cooldown __attribute__((sda));
extern s32 vec_fast_helper_a(u8 *);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void gfx_start_color_fade_pal(u8 *, u8 *);
extern void gfx_update_color_fade_pal(u8 *, u8 *);
extern void moby_set_group_flags(s32, s32, s32, s32);

extern float g_mining_vehicle_spin_rate __attribute__((sda));
extern float g_mining_vehicle_sway_strength __attribute__((sda));
extern float g_mining_vehicle_player_range __attribute__((sda));
extern float g_mining_vehicle_bob_amplitude __attribute__((sda));
extern float g_mining_vehicle_bob_speed __attribute__((sda));
extern float g_mining_vehicle_sway_angle __attribute__((sda));
extern float g_mining_vehicle_sway_scale_x __attribute__((sda));
extern float g_mining_vehicle_sway_scale_y __attribute__((sda));
extern float g_mining_vehicle_turn_rate __attribute__((sda));
extern float g_mining_vehicle_drag_a __attribute__((sda));
extern float g_mining_vehicle_vertical_damping __attribute__((sda));
extern float g_mining_vehicle_push_scale __attribute__((sda));
extern float g_mining_vehicle_max_speed __attribute__((sda));
extern float g_mining_vehicle_hover_height_high __attribute__((sda));
extern float g_mining_vehicle_hover_spring __attribute__((sda));
extern float g_mining_vehicle_collision_radius __attribute__((sda));
extern s32 g_mining_vehicle_hero_animation __attribute__((sda));
extern s32 g_mining_vehicle_current_animation __attribute__((sda));
extern float g_mining_vehicle_gravity __attribute__((sda));
extern float g_mining_vehicle_drag_b __attribute__((sda));
extern float g_mining_vehicle_drag_c __attribute__((sda));
extern float g_mining_vehicle_bank_damping __attribute__((sda));
extern float g_mining_vehicle_bank_scale __attribute__((sda));
extern float g_mining_vehicle_throttle_scale __attribute__((sda));
extern float g_mining_vehicle_turn_push __attribute__((sda));
extern float g_mining_vehicle_bank_throttle_mix __attribute__((sda));
extern float g_mining_vehicle_pitch_scale __attribute__((sda));
extern float g_mining_vehicle_input_pitch_scale __attribute__((sda));
extern float g_mining_vehicle_steer_blend __attribute__((sda));
extern float g_mining_vehicle_accel_rate __attribute__((sda));
extern float g_mining_vehicle_brake_strength __attribute__((sda));
extern float g_mining_vehicle_hit_radius_a __attribute__((sda));
extern float g_mining_vehicle_reach_a __attribute__((sda));
extern float g_mining_vehicle_reach_b __attribute__((sda));
extern float g_mining_vehicle_reach_c __attribute__((sda));
extern float g_mining_vehicle_hit_radius_b __attribute__((sda));
extern float g_mining_vehicle_ground_offset __attribute__((sda));
extern float g_mining_vehicle_speed_limit __attribute__((sda));
extern float g_mining_vehicle_max_health_a __attribute__((sda));
extern float g_mining_vehicle_max_health_b __attribute__((sda));
extern float g_mining_vehicle_max_health_c __attribute__((sda));
extern float g_mining_vehicle_time_scale __attribute__((sda));
extern float g_mining_vehicle_power_decrease __attribute__((sda));
extern float g_mining_vehicle_power_increase __attribute__((sda));
extern float g_mining_vehicle_hover_height_low __attribute__((sda));
extern float g_mining_vehicle_hover_height_mid __attribute__((sda));
extern float g_mining_vehicle_hover_extra __attribute__((sda));
extern float g_mining_vehicle_tilt_scale __attribute__((sda));
extern float g_mining_vehicle_side_scale __attribute__((sda));
extern s32 g_mining_vehicle_trail_fade_near __attribute__((sda));
extern s32 g_mining_vehicle_trail_fade_far __attribute__((sda));
extern s32 g_mining_vehicle_timer_max __attribute__((sda));
extern float g_mining_vehicle_ring_param_c __attribute__((sda));
extern float g_mining_vehicle_ring_param_a __attribute__((sda));
extern float g_mining_vehicle_ring_param_b __attribute__((sda));
extern s32 g_mining_vehicle_ring_color __attribute__((sda));
extern float g_mining_vehicle_ring_speed __attribute__((sda));
extern float g_mining_vehicle_ring_rise __attribute__((sda));
extern float g_mining_vehicle_dust_param_c __attribute__((sda));
extern float g_mining_vehicle_dust_param_a __attribute__((sda));
extern float g_mining_vehicle_dust_param_b __attribute__((sda));
extern s32 g_mining_hit_ring_param_a __attribute__((sda));
extern float g_mining_hit_vec_y __attribute__((sda));
extern float g_mining_hit_vec_z __attribute__((sda));
extern float g_mining_hit_float_c __attribute__((sda));
extern float g_mining_hit_float_d __attribute__((sda));
extern float g_mining_hit_float_e __attribute__((sda));
extern s32 g_mining_hit_ring_param_b __attribute__((sda));
extern float g_mining_hit_float_f __attribute__((sda));
extern float g_mining_hit_float_g __attribute__((sda));
extern float g_mining_trail_param_a __attribute__((sda));
extern float g_mining_trail_param_b __attribute__((sda));
extern s32 g_current_map_index;
extern s32 g_pad_state[];
extern u8 g_sound_state[];
typedef struct {
    u8 pad00[0x74];
    u8 active;
    u8 pad75[0x13];
    struct VehicleMoby *owner;
} EffectSlot;
typedef struct {
    u8 pad00[0x18];
    struct VehicleMoby *moby;
    u8 pad1C[4];
    float lowest[4];
    float point[4];
    float normal[4];
} CollisionResult;
extern CollisionResult g_collision_l08_result;
typedef struct {
    u8 pad000[0x160];
    float amount;
    u8 pad164[4];
    s32 timer;
    s32 phase;
} ShakeState;
extern ShakeState g_hero_l08_extra_state;
extern u8 g_hero_position_vec[];
extern float g_hud_l08_bar_threshold[] __attribute__((sda));
extern void ref_L08_0041EBF8_00(void);
extern void anim_start_blended_pal(void *, s32, s32, s32);
extern void AttachManipulator(void *, s32, void *);
extern float func_002A0558(void *, void *);
extern s32 TryClaimNotice(s32, s32, s32);
extern s32 level_set_game_state_pair_pal(s32, void *, s32);
extern void script_queue_keyed_request(s32, s32);
extern s32 hero_l08_set_move_state_pal(s32, s32);
extern void set_hero_animation_pal(s32, s32, float);
extern void snd_stop_voice(s32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern s32 FastDecTimer(void *);
extern void moby_mark_in_range(void *);
extern s32 math_random_int_below(s32);
extern void vehicle_read_controls(float *, float *, float *, float *, float *);
extern float FastVecLength(void *);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fabs(float);
extern float IntegerPower(s32, float);
extern void build_axis_rotation_quaternion(void *, s32, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float coll_probe_ground_height_below(void *, s32, float);
extern s32 GetCollHitMaterial(void);
extern void mat_get_euler_angles(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern s32 coll_process_triangles(void *, float);
extern s32 coll_test_point(void *, s32, void *, float);
extern float FastVecDot(void *, void *);
extern void part_spawn_ring_pal(void *, void *, s32, float, float, float, float, float, float);
extern void make_hit_descriptor(void *, void *, s32, void *, float);
extern int coll_process_hit(void *, s32, void *, void *, float);
extern void vehicle_end_ride_pal(void *);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, s32, s32, s32, float, float, float, float,
                          s32, float, s32, s32, s32, s32, s32);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float IntToFloat(s32);
extern s32 FloatToInt(float);
extern void *part_spawn_attached_effect(void *, void *);
extern void moby_store_position_private(void *, void *);
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern s32 part_fill_effect_record_pal(void *, s32, s32, void *, float, float);
extern int snd_fade_looping_by_distance(void *, void *, s32, s32, float);
extern int math_fast_float_d(void *);
/* An effect record (0x70 bytes) still owned by this moby and active. */
#define EFFECT(i) ((EffectSlot *)(D_00188660 + (i) * 0x70))
#define EFFECT_LIVE(i) (EFFECT(i)->owner == moby && EFFECT(i)->active)

/* Update the rideable hovering vehicle and its player-control state. */
/* Updates the Mining Vehicle (moby class 3823): it lets the hero board and drive it, handles steering, boost, effects and sounds, and drops the hero off when the ride ends (PAL: 50 Hz timings). */
void mining_vehicle_update_pal(VehicleMoby *moby)
{
    VehicleVars *vars = moby->vars_ptr;
    s32 fresh;
    float input_turn, input_throttle, input_pitch, input_brake, input_strafe;
    /* basis: the ground-aligned matrix (rows x, y, normal, zero translation); its rows
     * are reused below as the probe point, its offset and the contact normal. */
    float forward[4], thrust[4], next_pos[4], basis[4][4], angles[4], scratch[16];

    if (g_cutscene_l08_active_flag == 2 || D_00189E20_14.animation_state == 97) {
        moby->drawn = 0;
        moby->mode_bits |= 1;
        return;
    }
    moby->drawn = 1;
    moby->mode_bits &= 0xfffe;
    if (vec_fast_helper_a(&vars->hit_cooldown))
        vars->last_hit = 0;
    if (moby->state) {
        u8 *hit, *target;
        moby->pos[2] = vars->last_z;
        hit = part_find_owned_effect_slot(moby, 1, 0);
        if (hit && (target = *(u8 **)(hit + 0x20))) {
            s32 kind = *(s16 *)(target + 0xaa);
            if (kind != MOBY_CLASS_MINING_VEHICLE && kind != 0x942 && kind != MOBY_CLASS_MUTANT_SANDFLY &&
                (target != vars->last_hit || !vars->hit_cooldown)) {
                vars->flash_rgb[0] = 0xd2;
                vars->flash_rgb[1] = 0xd2;
                vars->flash_rgb[2] = 0xd2;
                gfx_start_color_fade_pal(moby, vars->flash);
                vars->health -= *(float *)(hit + 0x2c);
                D_00189E20_14.health = vars->health;
                if (vars->health <= 0.0f)
                    moby->state = 5;
                vars->last_hit = *(u8 **)(hit + 0x20);
                vars->hit_cooldown = (g_mining_hit_cooldown * 5 + 2) / 6;
            }
        }
        moby->impact = 0xff;
    } else {
        vars->last_z = moby->pos[2];
    }
    gfx_update_color_fade_pal(moby, vars->flash);
    moby->f2c = *(float *)(moby->class_ptr + 0x24) * g_mining_vehicle_class_scale;
    if (D_00189E20_14.vehicle == moby && moby->state)
        D_00189E20_14.health_bar = (s32)(D_00189E20_14.health / D_00189E20_14.max_health * 200.0f);
    else
        D_00189E20_14.health_bar = 200;
    fresh = 0;
    if (vars->sound != -1)
        moby_set_group_flags(vars->sound, -1, -1, 1);
    switch (moby->state) {
    case 0:
        if (moby->seq_b)
            anim_start_blended_pal(moby, 0, 0, 10);
        if (!vars->rotor[0].hdr[1]) {
            s32 j;
            for (j = 0; j < 3; j++)
                AttachManipulator(moby, j + 2, &vars->rotor[j]);
        }
        vars->fa4 = 0;
        vars->fa8 = 255;
        qcopy(vars->home, moby->pos);
        qzero(vars->vel);
        switch (g_current_map_index) {
        case 8:
            D_00189E20_14.max_health = g_mining_vehicle_max_health_b;
            break;
        case 19:
            D_00189E20_14.max_health = g_mining_vehicle_max_health_c;
            break;
        default:
            D_00189E20_14.max_health = g_mining_vehicle_max_health_a;
            break;
        }
        vars->health = D_00189E20_14.max_health;
        D_00189E20_14.health = vars->health;
        vars->f74 = 0;
        moby->state = 1;
        vars->fx1a4 = -1;
        vars->power = 0.0f;
        vars->fx1ac = 0;
        vars->fx1b0 = 0;
        break;
    case 1:
        if (D_00189E20_14.animation_state != 28 && D_00189E20_14.animation_state != 22 &&
            D_00189E20_14.animation_state != 57 && D_00189E20_14.animation_state != 111 &&
            D_00189E20_14.movement_state != 2 && D_00189E20_14.movement_state != 4 &&
            D_00189E20_14.movement_state != 3 && D_00189E20_14.movement_state < 13 &&
            D_00189E20_14.movement_state != 7 && D_00189E20_14.movement_state != 10 &&
            D_00189E20_14.movement_state != 16 && D_00189E20_14.movement_state != 5 &&
            D_00189E20_14.animation_state != 98 && D_00189E20_14.health_available > 0 &&
            g_cutscene_l08_active_flag == 0 && D_00189E20_14.available &&
            (!D_00189E20_14.attachment || (*(s16 *)(D_00189E20_14.attachment + 0xaa) != 0x13e &&
                                    *(s16 *)(D_00189E20_14.attachment + 0xaa) != 0x46f)) &&
            func_002A0558(moby, D_00189E20_14.moby) < g_mining_vehicle_player_range &&
            D_00189E20_14.animation_state != 49) {
            s32 ready = TryClaimNotice(7, 0x12ea, 1) != 0;
            if ((g_pad_state[0x69] & 16) && ready) {
                vars->f190 = 0;
                fresh = 1;
                level_set_game_state_pair_pal(0, ref_L08_0041EBF8_00, 1);
                script_queue_keyed_request(vars->f194, vars->f19c);
                hero_l08_set_move_state_pal(49, 0);
                set_hero_animation_pal(g_mining_vehicle_hero_animation, 0, 15.0f);
                qcopy(D_00189E20_14.rotation, moby->rot);
                qcopy(D_00189E20_14.position, moby->pos);
                D_00189E20_14.vehicle = moby;
                moby->state = 3;
                if (vars->fx1b4 != -1 && EFFECT_LIVE(vars->fx1b4))
                    snd_stop_voice(vars->fx1b4);
                vars->fx1b4 = -1;
                D_00189E20_14.moby->f9c = -1;
                D_00189E20_14.vehicle_control = 1;
            }
        }
        if (!EFFECT_LIVE(vars->fx1b4))
            vars->fx1b4 = snd_play_from_class_bank(9, 4, moby, 0x85c);
        /* Activation continues through the control/movement path this frame. */
    case 3:
        moby->coll_data = 0;
        FastDecTimer(&vars->timer7c);
        input_strafe = input_brake = input_pitch = input_throttle = input_turn = 0.0f;
        if (moby->state == 3) {
            D_00189E20_14.vehicle_control = 1;
            if (g_pad_state[0x68] & 0x80) {
                if ((moby->seq_a < 1 || moby->seq_a > 3) && moby->seq_b != 1 && moby->seq_b != 2 &&
                    moby->seq_b != 3) {
                    if (moby->seq_b != 1)
                        anim_start_blended_pal(moby, 1, 0, 10);
                } else if (moby->f60 & 2) {
                    if (moby->seq_a == 1) {
                        if (moby->seq_b != 2)
                            anim_start_blended_pal(moby, 2, 0, 10);
                    } else if (moby->seq_b == 3 || moby->seq_b == 0) {
                        if (moby->seq_b != 1)
                            anim_start_blended_pal(moby, 1, 0, 10);
                    }
                }
                vars->power -= g_mining_vehicle_power_decrease * 1.2f;
                if (!math_random_int_below(9) || (g_pad_state[0x69] & 0x80))
                    moby_mark_in_range(moby);
            } else {
                if (moby->f60 & 2) {
                    if ((moby->seq_a >= 1 && moby->seq_a <= 2) ||
                        moby->seq_b == 1 || moby->seq_b == 2) {
                        if (moby->seq_b != 3)
                            anim_start_blended_pal(moby, 3, 0, 10);
                    } else if (moby->seq_b) {
                        anim_start_blended_pal(moby, 0, 0, 10);
                    }
                }
                vars->power += g_mining_vehicle_power_increase * 1.2f;
            }
            if (g_mining_vehicle_current_animation != g_mining_vehicle_hero_animation && g_mining_vehicle_hero_animation != -1)
                set_hero_animation_pal(g_mining_vehicle_hero_animation, 0, 15.0f);
            vehicle_read_controls(&input_turn, &input_throttle, &input_pitch, &input_brake, &input_strafe);
            input_turn *= vars->power;
        } else {
            vars->power -= g_mining_vehicle_power_decrease * 1.2f;
            if (moby->f60 & 2) {
                if ((moby->seq_a >= 1 && moby->seq_a <= 2) ||
                    moby->seq_b == 1 || moby->seq_b == 2) {
                    if (moby->seq_b != 3)
                        anim_start_blended_pal(moby, 3, 0, 2);
                } else if (moby->seq_b) {
                    anim_start_blended_pal(moby, 0, 0, 2);
                }
            }
        }
        if (vars->power > 1.0f)
            vars->power = 1.0f;
        else if (vars->power < 0.0f)
            vars->power = 0.0f;
        {
            float sign = 1.0f;
            float hover_height, rate, speed, speed_max, steer, turn, turn_rad, bank;
            float turn_factor, damping, push, acceleration, spin, strength, height;
            float *angle, *rates;
            s32 special, grounded, collision;

            input_throttle *= vars->power;
            input_brake += 1.0f - vars->power;
            input_strafe *= vars->power;
            hover_height = g_mining_vehicle_hover_height_high * vars->power + g_mining_vehicle_hover_height_low * (1.0f - vars->power);
            if (moby->state == 3)
                hover_height = g_mining_vehicle_hover_height_high * vars->power + g_mining_vehicle_hover_height_mid * (1.0f - vars->power);
            vars->throttle = input_throttle;
            input_pitch *= 0.017453294f;
            input_pitch *= g_mining_vehicle_input_pitch_scale;
            speed = FastVecLength(vars) * vars->power;
            speed_max = g_mining_vehicle_max_speed * 0.020000001f;
            rate = g_mining_vehicle_accel_rate * 0.020000001f;
            steer = (speed < rate ? speed : rate) / rate * g_mining_vehicle_steer_blend + (1.0f - g_mining_vehicle_steer_blend) +
                    g_mining_vehicle_hover_extra * (1.0f - vars->power);
            turn = input_turn * steer * 0.0003490659f;
            vars->yaw = FastAddRotations(vars->yaw, g_mining_vehicle_turn_rate * turn);
            turn_rad = input_turn * 0.017453294f;
            bank = g_mining_vehicle_bank_scale * turn_rad;
            bank *= vars->power;
            bank *= g_mining_vehicle_bank_throttle_mix * input_throttle + (1.0f - g_mining_vehicle_bank_throttle_mix);
            bank -= moby->rot[0];
            bank *= g_mining_vehicle_bank_damping;
            vars->roll += bank;
            forward[0] = math_fast_sin_or_cos_a(vars->yaw);
            forward[1] = math_fast_sin_or_cos_b(vars->yaw);
            forward[2] = 0.0f;
            if (input_throttle < 0.0f)
                input_throttle *= g_mining_vehicle_throttle_scale;
            if (input_throttle < 0.0f)
                sign = -1.0f;
            turn_factor = math_fabs(input_turn), damping = IntegerPower(2, (speed_max - speed) / speed_max);
            push = input_throttle + g_mining_vehicle_turn_push * turn_factor * sign;
            push *= 0.00040000002f;
            push *= g_mining_vehicle_push_scale;
            acceleration = push * damping;
            spin = vars->power * 0.0003490659f;
            vars->rate[0] = spin * g_mining_vehicle_spin_rate;
            strength = g_mining_vehicle_sway_strength * 0.0003490659f;
            rates = vars->rate;
            angle = vars->angle;
            {
                s32 k;
                for (k = 1; k < 3; k++) {
                    float t = speed / speed_max + input_throttle;
                    float x;
                    if (!(k & 1))
                        x = t - input_turn;
                    else
                        x = t + input_turn;
                    x = x * strength * 0.5f;
                    if (k & 1)
                        x = -x;
                    vars->rate[k] = x;
                }
            }
            {
                s32 k;
                for (k = 0; k < 3; k++) {
                    angle[k] = FastAddRotations(angle[k], rates[k]);
                    build_axis_rotation_quaternion(vars->rotor[k].mtx, k == 0 ? 2 : 0, angle[k]);
                }
            }
            FastVecAdd(next_pos, moby->pos, vars->vel);
            height = coll_probe_ground_height_below(next_pos, 0, 0.5f);
            special = 0;
            if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 11)
                special = 1;
            if (moby->pos[2] < height + hover_height + 0.3f && special)
                moby->state = 5;
            grounded = 1;
            vars->vel[2] -= g_mining_vehicle_gravity * 0.00040000002f;
            if (height != 0.0f) {
                vec_scale_to_length(basis[2], g_collision_l08_result.normal, 1.0f);
                FastVecCross(basis[1], moby->mtx, basis[2]);
                FastVecCross(basis[0], basis[1], basis[2]);
                qzero_nc(basis[3]);
                mat_get_euler_angles(basis, angles);
                {
                    float tilt = input_pitch * 0.5f;
                    vars->pitch = FastAddRotations(vars->pitch,
                        fast_subtract_rotations(FastAddRotations(-angles[1], tilt * (g_mining_vehicle_tilt_scale * (vars->power + 1.0f))),
                                      vars->pitch) * g_mining_vehicle_pitch_scale);
                }
                if (next_pos[2] < height + hover_height + 0.2f) {
                    grounded = 0;
                    if (next_pos[2] + 0.1f < height || special) {
                        next_pos[2] = height;
                        FastVecScale(vars, vars, g_mining_vehicle_drag_c);
                    }
                    vars->vel[2] += ((height + hover_height - next_pos[2]) * g_mining_vehicle_hover_spring - vars->vel[2]) *
                                 g_mining_vehicle_hover_spring;
                    if (input_brake > 0.0f) {
                        float brake = 1.0f - g_mining_vehicle_brake_strength * input_brake;
                        vars->vel[0] *= brake;
                        vars->vel[1] *= brake;
                    }
                    FastVecScale(vars, vars, g_mining_vehicle_drag_a);
                    matrix_from_basis_rows(scratch, moby->mtx);
                    transform_vector(vars, vars, scratch);
                    vars->vel[1] *= g_mining_vehicle_vertical_damping;
                    matrix_mul_vec3(vars, vars, moby->mtx);
                }
                vec_scale_to_length(thrust, moby->mtx, acceleration);
                if (vars->pitch < -0.78539824f) {
                    if (thrust[2] > 0.0f)
                        thrust[2] = 0.0f;
                    vec_scale_to_length(thrust, thrust, acceleration);
                } else {
                    float climb = g_mining_vehicle_gravity * 0.000100000005f;
                    if (thrust[2] > climb)
                        thrust[2] = climb;
                    vec_scale_to_length(thrust, thrust, acceleration);
                }
                {
                    float side = input_strafe * 0.00040000002f;
                    vec_scale_to_length(scratch, moby->mtx[1], g_mining_vehicle_side_scale * side * vars->power);
                }
                FastVecAdd(thrust, thrust, scratch);
                FastVecAdd(vars, vars, thrust);
            }
            qcopy(moby->pos, next_pos);
            moby_transform_joint_to_world(moby, 0, basis[0]);
            basis[0][2] += g_mining_vehicle_collision_radius - g_mining_vehicle_hover_height_low;
            FastVecSub(basis[1], moby->pos, basis[0]);
            moby->coll_data = 0;
            collision = coll_process_triangles(basis[0], g_mining_vehicle_collision_radius);
            if (!collision) {
                if (g_current_map_index == 19) {
                    s32 saved = D_00189E20_14.moby->coll_data;
                    D_00189E20_14.moby->coll_data = 0;
                    collision = coll_test_point(basis[0], 0, moby, g_mining_vehicle_collision_radius);
                    D_00189E20_14.moby->coll_data = saved;
                } else {
                    collision = coll_test_point(basis[0], 2, moby, g_mining_vehicle_collision_radius);
                }
            }
            moby->coll_data = *(s32 *)(moby->class_ptr + 0x10);
            if (collision) {
                if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 11)
                    moby->state = 5;
                if (g_collision_l08_result.moby != D_00189E20_14.moby) {
                    float give = 1.0f;
                    if (grounded) {
                        g_collision_l08_result.point[0] -= basis[0][0];
                        g_collision_l08_result.point[1] -= basis[0][1];
                        if (g_collision_l08_result.point[0] < 0.060000002f)
                            g_collision_l08_result.point[0] *= vars->power;
                        if (g_collision_l08_result.point[1] < 0.060000002f)
                            g_collision_l08_result.point[1] *= vars->power;
                        g_collision_l08_result.point[0] += basis[0][0];
                        g_collision_l08_result.point[1] += basis[0][1];
                    } else {
                        give = vars->power;
                    }
                    FastVecAdd(moby->pos, g_collision_l08_result.point, basis[1]);
                    FastVecCross(basis[3], g_collision_l08_result.normal, vars);
                    FastVecCross(basis[2], basis[3], g_collision_l08_result.normal);
                    vec_scale_to_length(basis[2], basis[2], 1.0f);
                    vec_scale_to_length(vars, basis[2], FastVecDot(vars, basis[2]) * give);
                    FastVecScale(vars, vars, g_mining_vehicle_drag_b);
                    if (moby->pos[2] < vars->f17c)
                        moby->state = 5;
                }
            }
        }
        if (moby->state == 3) {
            if (moby->pos[2] < g_collision_l08_result.lowest[2])
                g_collision_l08_result.lowest[2] = moby->pos[2];
            if (vars->power < 0.98f && (g_pad_state[0x68] & 0x80)) {
                if (vars->fx1a8 == 0) {
                    if (!vars->fx1ac)
                        snd_play_from_class_bank(1, 0, moby, 0x85c);
                    vars->fx1a8 = 2;
                    vars->fx1ac = 12;
                } else if (vars->fx1a8 == 2) {
                    if (!EFFECT_LIVE(vars->fx1a4)) {
                        vars->fx1a4 = snd_play_from_class_bank(2, 4, moby, 0x85c);
                        if (vars->fx1b4 != -1 && EFFECT_LIVE(vars->fx1b4))
                            snd_stop_voice(vars->fx1b4);
                        vars->fx1b4 = -1;
                    }
                }
                if (vars->f68 < g_hud_l08_bar_threshold[0]) {
                    part_spawn_ring_pal(moby, g_collision_l08_result.lowest, g_mining_hit_ring_param_a,
                        g_mining_vehicle_dust_param_a, g_mining_vehicle_dust_param_b, g_mining_vehicle_dust_param_c,
                        g_mining_vehicle_dust_param_c, g_mining_hit_vec_y, g_mining_hit_vec_z);
                    if (!math_random_int_below(11)) {
                        g_hero_l08_extra_state.amount = (1.0f - vars->power) * 0.05f;
                        g_hero_l08_extra_state.timer = 12;
                        g_hero_l08_extra_state.phase = 0;
                    }
                } else {
                    part_spawn_ring_pal(moby, g_collision_l08_result.lowest, g_mining_hit_ring_param_b,
                        g_mining_hit_float_d, g_mining_hit_float_e, g_mining_hit_float_c,
                        g_mining_hit_float_c, g_mining_hit_float_f, g_mining_hit_float_g);
                }
                if (vars->fx1b4 != -1 && EFFECT_LIVE(vars->fx1b4))
                    snd_stop_voice(vars->fx1b4);
                vars->fx1b4 = -1;
            } else if (vars->fx1a8 == 2) {
                if (vars->fx1a4 != -1 && EFFECT_LIVE(vars->fx1a4))
                    snd_stop_voice(vars->fx1a4);
                vars->fx1a4 = -1;
                if (vars->fx1ac == 0)
                    snd_play_from_class_bank(4, 0, moby, 0x85c);
                vars->fx1a8 = 0;
                vars->fx1ac = 12;
            } else if (!EFFECT_LIVE(vars->fx1b4)) {
                vars->fx1b4 = snd_play_from_class_bank(9, 4, moby, 0x85c);
            }
            part_spawn_ring_pal(moby, g_collision_l08_result.lowest, g_mining_vehicle_ring_color,
                g_mining_vehicle_ring_param_a, g_mining_vehicle_ring_param_b, g_mining_vehicle_ring_param_c,
                g_mining_vehicle_ring_speed, g_mining_vehicle_ring_rise, 1.0f);
        }
        moby_transform_joint_to_world(moby, 0, basis[0]);
        basis[0][2] += g_mining_vehicle_ground_offset;
        {
            float reach = g_mining_vehicle_reach_a;
            switch (g_current_map_index) {
            case 8:
                reach = g_mining_vehicle_reach_b;
                break;
            case 19:
                reach = g_mining_vehicle_reach_c;
                break;
            }
            make_hit_descriptor(basis[2], moby, 0x10000, vars, reach);
        }
        coll_process_hit(basis[0], 0, moby, basis[2], g_mining_vehicle_hit_radius_a);
        if (FastVecLength(vars) > g_mining_vehicle_speed_limit * 0.020000001f) {
            moby_transform_joint_to_world(moby, 1, scratch);
            coll_process_hit(scratch, 0, moby, basis[2], g_mining_vehicle_hit_radius_b);
        }
        if (!fresh && D_00189E20_14.vehicle == moby && (g_pad_state[0x69] & 16)) {
            vehicle_end_ride_pal(moby);
            moby->state = 1;
            if (!EFFECT_LIVE(vars->fx1b4))
                vars->fx1b4 = snd_play_from_class_bank(9, 4, moby, 0x85c);
        }
        break;
    case 2:
    case 4:
    case 6:
        break;
    case 5:
        vehicle_end_ride_pal(moby);
        moby_transform_joint_to_world(moby, 0, forward);
        SpawnExplosionEffects_pal(moby, vars, forward, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f,
                      1, 1, -1, 0, 0x810001);
        qcopy(moby->pos, vars->home);
        moby->state = 0;
        break;
    }
    vars->last_z = moby->pos[2];
    {
        float step = vars->power * 0.0003490659f;
        vars->bob_phase = FastAddRotations(vars->bob_phase, g_mining_vehicle_bob_speed * step);
    }
    vars->bob_offset = math_fast_sin_or_cos_b(vars->bob_phase) * g_mining_vehicle_bob_amplitude * vars->power;
    moby->pos[2] += vars->bob_offset * vars->power;
    {
        float k = vars->power * 0.0003490659f;
        moby_scale_owner_words_by_angles(moby, &vars->sway[0], &vars->sway[1], g_mining_vehicle_sway_angle * 0.017453294f,
                      g_mining_vehicle_sway_scale_x * k, g_mining_vehicle_sway_scale_y * k);
    }
    moby->rot[2] = vars->yaw;
    moby->rot[0] = FastAddRotations(moby->rot[0], vars->roll);
    moby->rot[1] = FastAddRotations(moby->rot[1], vars->pitch);
    if (moby->state == 3) {
        if (g_current_map_index == 8 || g_current_map_index == 19) {
            switch (vars->mode8a) {
            case 0:
                if (vars->f68 < g_hud_l08_bar_threshold[0]) {
                    vars->mode8a = 1;
                    vars->timer88 = 0;
                }
                break;
            case 1:
                (vars->timer88)++;
                if (vars->timer88 > (g_mining_vehicle_timer_max * 5 + 2) / 6)
                    vars->timer88 = (g_mining_vehicle_timer_max * 5 + 2) / 6;
                if (vars->f68 > g_hud_l08_bar_threshold[0])
                    vars->mode8a = 3;
                else if (vars->timer88 >= (g_mining_vehicle_timer_max * 5 + 2) / 6)
                    vars->mode8a = 2;
                break;
            case 2:
                if (vars->f68 > g_hud_l08_bar_threshold[0])
                    vars->mode8a = 3;
                break;
            case 3:
                FastDecTimer(&vars->timer88);
                if (vars->f68 < g_hud_l08_bar_threshold[0])
                    vars->mode8a = 1;
                else if (vars->timer88 == 0)
                    vars->mode8a = 0;
                break;
            }
            if (vars->mode8a && vars->f6c) {
                u8 *other = *(u8 **)(vars->f6c + 0x68);
                float num = IntToFloat(*(s32 *)(other + 4));
                vars->f8c =
                    FloatToInt(g_mining_vehicle_time_scale * num / ((IntToFloat(*(s32 *)other) * 60.0f * 5 + 2) / 6));
            } else {
                vars->f8c = 0x200;
            }
            if (vars->f6c) {
                if (!vars->f74)
                    vars->f74 = part_spawn_attached_effect(moby, vars->f6c + 0x10);
                else
                    moby_store_position_private(vars->f74, vars->f6c + 0x10);
            } else if (vars->f74) {
                moby_mark_spawned(vars->f74);
                vars->f74 = 0;
            }
        }
        vec_scale_to_length(forward, moby->mtx, -0.5f);
        if (forward[2] < 0.0f)
            forward[2] = 0.0f;
        forward[2] += 1.5f;
        FastVecAdd(D_00189E20_14.position, forward, moby->pos);
        qcopy(D_00189E20_14.camera_position, D_00189E20_14.position);
        D_00189E20_14.camera_position[2] = moby->pos[2];
        qcopy(D_00189E20_14.rotation, moby->rot);
    }
    moby->coll_data = *(s32 *)(moby->class_ptr + 0x10);
    if (moby->drawn && fast_vec_dist(moby->pos, g_hero_position_vec) < 64.0f) {
        moby_update_ground_check(moby);
        moby->f6f = 60;
    }
    if (vars->sound != -1)
        moby_set_group_flags(vars->sound, -1, 0, 0);
    if (vars->throttle != 0.0f) {
        if (!EFFECT_LIVE(vars->fx1a4)) {
            vars->fx1a4 = snd_play_from_class_bank(0, 4, moby, 0x85c);
            part_fill_effect_record_pal(moby, vars->fx1a4, 0, vars->trail, g_mining_trail_param_a, g_mining_trail_param_b);
        } else {
            FastVecSub(forward, moby->pos, vars->trail);
            forward[2] = 0.0f;
            snd_fade_looping_by_distance(moby, vars->trail, g_mining_vehicle_trail_fade_near, g_mining_vehicle_trail_fade_far, FastVecLength(forward));
            if (vars->fx1b4 != -1 && EFFECT_LIVE(vars->fx1b4))
                snd_stop_voice(vars->fx1b4);
            vars->fx1b4 = -1;
        }
    } else if (vars->fx1a8 != 2) {
        if (vars->fx1a4 != -1 && EFFECT_LIVE(vars->fx1a4))
            snd_stop_voice(vars->fx1a4);
        vars->fx1a4 = -1;
    }
    math_fast_float_d(&vars->fx1ac);
}
