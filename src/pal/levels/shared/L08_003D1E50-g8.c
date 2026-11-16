#include "names.h"
/* func_PAL_L08_003D1E50: the hero-NPC state machine shared by Tabora, Dobbo and Grelbin
 * (levels 08, 09, 19), dispatched on moby byte 0x20 over the NPC block at moby+0x68.
 * Own unit: -G8 for the $gp tuning constants, -g for the nop pairs before div.s,
 * -frac2-qcopy for the 16-byte copies, -ffast-math for case 10's min.s.
 * Nothing reads the clamped ratio in case 7: retail still has its div.s and c.lt.s.
 * The PAL copy of func_L08_003CDF98: the same C with PAL's 50 Hz scales and values, the
 * animation changes going through SetAnimation (its one-insn compare sets gcse's table
 * size, which orders the spill slots at sp+0x70..0x7C).
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;

/* $gp-relative tuning constants (retail reads them as one-instruction gp loads). */
extern float g_vehicle_df8_step __attribute__((sda));
extern float g_vehicle_hero_near_distance __attribute__((sda));
extern float g_vehicle_hero_far_distance __attribute__((sda));
extern s32 g_vehicle_timer_start __attribute__((sda));
extern s32 g_vehicle_timer_length __attribute__((sda));
extern s32 g_vehicle_timer_margin __attribute__((sda));
extern float g_vehicle_target_angle_degrees __attribute__((sda));
extern float g_vehicle_l08_max_speed __attribute__((sda));
extern float g_vehicle_speed_accel __attribute__((sda));
extern float g_vehicle_l08_turn_rate __attribute__((sda));
extern float g_vehicle_slope_threshold __attribute__((sda));
extern float g_vehicle_slow_speed __attribute__((sda));
extern float g_vehicle_slope_limit __attribute__((sda));
extern float g_vehicle_cruise_speed __attribute__((sda));
extern float g_vehicle_bank_limit_degrees __attribute__((sda));
extern float g_vehicle_df28_blend_scale __attribute__((sda));
extern s32 g_vehicle_df50_frames __attribute__((sda));
extern float g_vehicle_decel_a __attribute__((sda));
extern float g_vehicle_angle_limit_degrees __attribute__((sda));
extern s32 g_vehicle_df50_reset __attribute__((sda));
extern float g_vehicle_angle_threshold_degrees __attribute__((sda));
extern float g_vehicle_yaw_step __attribute__((sda));
extern float g_vehicle_decel_b __attribute__((sda));
extern float g_vehicle_df64_offset __attribute__((sda));
extern float g_vehicle_param_copy_a __attribute__((sda));
extern float g_vehicle_param_copy_b __attribute__((sda));
extern float g_vehicle_push_speed __attribute__((sda));
extern float g_vehicle_max_reverse_speed __attribute__((sda));
extern float g_vehicle_reverse_limit __attribute__((sda));
extern s32 g_vehicle_df50_alt_frames __attribute__((sda));
extern float g_vehicle_decel_c __attribute__((sda));
extern float g_vehicle_l08_velocity_damping __attribute__((sda));
extern float g_vehicle_velocity_length_scale __attribute__((sda));
extern s32 g_vehicle_threshold_frames __attribute__((sda));
extern float g_vehicle_target_angle_step __attribute__((sda));
extern float g_vehicle_angle_step_zero __attribute__((sda));
extern float g_vehicle_unk_ratio_scale __attribute__((sda));
extern s32 g_vehicle_active_flag __attribute__((sda));
extern float g_vehicle_saved_x;
typedef struct { u8 bytes[0x100]; } HeroCDF98;
extern HeroCDF98 *g_moby_array;
extern float g_vehicle_collision_x;
extern float g_vehicle_collision_y;
extern float g_vehicle_saved_y;
extern s32 g_pad_held_flags[];
typedef struct { float f[0x100]; } StateCDF98;
extern StateCDF98 g_hero_l08_extra_state;
extern char g_hero_position_vec[];
extern char g_str_effect_name[] MACRO_ADDR;
extern char g_str_vehicle_debug_printf[];
extern char g_str_vehicle_debug_message_a[];
extern char g_str_vehicle_debug_message_b[];
extern u8 g_level_flag_byte_2;
extern s32 g_held_object_ptr[];
typedef struct { u8 bytes[0x80]; } TargetCDF98;
extern TargetCDF98 *g_collision_box_table;
typedef struct {
    u32 handle;
    u8 active;
    u8 unknown05[0x13];
    void *owner;
    u8 unknown1C[0x54];
} VoiceCDF98;
typedef struct {
    u8 header[0x70];
    VoiceCDF98 voice;
} VoiceSlotCDF98;
extern u8 g_sound_state[];
extern void *g_platform_actor_ref[];

extern int func_001163B0(void);
extern void STUB_printf(void *, ...);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_fast_float_d(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_from_basis_rows(void *, void *);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float IntToFloat(int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern void moby_update_ground_check(void *);
extern void StepAngleTowardTarget(void *, int, float, float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int IsPointInCuboid(void *, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int TryClaimNotice(int, int, int);
extern int flag_set_first_pending(void *);
/* Interleaved: each register bank keeps the order of the definition in 002BDCE8.c. */
extern void *part_spawn_spinning_spark_pal(void *, int, void *, float, float, int, int, float, float);
extern void snd_stop_voice(int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void hero_reset_speeds_and_vectors(void);
extern void hero_record_play_counters_pal(void);
extern void set_hero_animation_pal(int, int, float);
extern void script_queue_keyed_request(int, int);
extern int hero_l08_enter_state_pal(int, int);
extern void cam_update_aim_values_pal(void *, void *);
extern void hero_move_with_mount_to_transform(void *, void *);
extern void hero_save_transform_snap_object(void *, void *);
extern void vehicle_update_steering_pal(void *, void *, float);
extern void moby_place_at_stored_transform(void *);
extern int vehicle_handle_collision_pal(void *, void *);

typedef struct {
    u8 unk0[0x80];
    float pos[4];        /* 0x80 */
    u8 unk90[0x33C - 0x90];
    u8 *target;          /* 0x33C */
    s32 unk340;
    u8 unk344[0x34E - 0x344];
    s16 unk34E;
    u8 unk350[0xC20 - 0x350];
    float unkC20;
    u8 unkC24[0xC28 - 0xC24];
    s32 unkC28;
    u8 unkC2C[0xC38 - 0xC2C];
    float unkC38;
    u8 unkC3C[0x1830 - 0xC3C];
    u8 *unk1830;
    u8 unk1834[0x2290 - 0x1834];
    u8 *unk2290;
    s32 unk2294;
} PlayerCDF98;
extern PlayerCDF98 g_hero_state;
#define DI(o) (((s32 *)d)[(o) / 4])
#define DF(o) (((float *)d)[(o) / 4])
#define OB(o) (*(u8 *)(obj + (o)))
static __inline__ void SetAnimation(u8 *p, s32 animation, s32 mode, s32 blend)
{
    if (p[0x43] != animation) anim_start_blended_pal(p, animation, mode, blend);
}
#define OH(o) (((u16 *)obj)[(o) / 2])

/* Updates a Glider (moby class 2309): it waits at its pad, lets the hero hop on, launches, then steers and glides with the stick, leaves a smoke trail, and lands or lets go at a target (PAL: 50 Hz values). */
void hero_npc_update_pal(u8 *obj)
{
    Vec saved;
    union {
        Vec inverse[4];
        struct { Vec velocity, point, joint; } v;
    } scratch;
    u8 *d, *p;
    int i, n, id;
    float t;

    d = *(u8 **)(obj + 0x68);
    qcopy(&saved, d);
    if (OH(0x96) < 0x7FFD)
        OH(0x96) = OH(0x96) + 1;
    switch (OB(0x20)) {
    case 0:
        id = DI(0x6C);
        if (id > 0) {
            HeroCDF98 *table = g_moby_array;
            qcopy(d, table[id].bytes + 0x10);
            qcopy(d + 0x10, table[id].bytes + 0xF0);
            moby_place_at_stored_transform(obj);
        } else {
            STUB_printf(g_str_vehicle_debug_printf, *(s16 *)(obj + 0xB2));
        }
        DF(8) = DF(8) + g_vehicle_df8_step;
        moby_transform_joint_to_world(obj, 8, d + 0x30);
        FastVecSub(d + 0x30, obj + 0x10, d + 0x30);
        matrix_from_basis_rows(scratch.inverse, obj + 0xC0);
        transform_vector(d + 0x30, d + 0x30, scratch.inverse);
        DF(0x3C) = 1.0f;
        SetAnimation(obj, 0, 0, 0xA);
        OB(0x30) = 0xFF;
        OB(0x31) = 0;
        *(s16 *)(obj + 0x32) = 0x3FF;
        OH(0x34) = OH(0x34) | 1;
        moby_set_state(obj, 1, -1);
        DI(0x98) = 0;
        DI(0xB0) = 0;
        break;
    case 1:
        if (g_level_flag_byte_2 == 0)
            return;
        {
            if (DI(0x6C) < 0) {
                if (fast_vec_dist(d, g_hero_state.pos) < g_vehicle_hero_near_distance && g_hero_state.unk2294 != 0x31) {
                    SetAnimation(obj, 0, 0, 0xA);
                    moby_set_state(obj, 2, -1);
                }
            } else {
                u8 *q = (u8 *)g_platform_actor_ref[0];
                if (q != 0 && *(s16 *)(q + 0xAA) == MOBY_CLASS_GLIDER_PAD && q == g_moby_array[DI(0x6C)].bytes) {
                    SetAnimation(obj, 0, 0, 0xA);
                    moby_set_state(obj, 2, -1);
                }
            }
        }
        break;
    case 2: {
        int ok;
        hero_save_transform_snap_object(obj, d);
        if (g_hero_state.target == 0 || *(s16 *)(g_hero_state.target + 0xAA) != MOBY_CLASS_GLIDER_PAD) {
            SetAnimation(obj, 0, 0, 0xA);
            qcopy(d, g_moby_array[DI(0x6C)].bytes + 0x10);
            DF(8) = DF(8) + g_vehicle_df8_step;
            moby_set_state(obj, 1, -1);
        }
        ok = TryClaimNotice(7, 0x12f0, 1) != 0;
        if (OB(0x20) == 2 && (g_pad_held_flags[0] & 0x40)) {
            if (ok && g_hero_state.target == g_moby_array[DI(0x6C)].bytes && g_hero_state.unk340 != 0
                && g_hero_state.unk34E == 0) {
                u8 *q;
                hero_l08_enter_state_pal(0x31, 0);
                set_hero_animation_pal(0x87, 0, 3.0f);
                ((s32 *)g_hero_state.unk2290)[0x9C / 4] = -1;
                q = g_moby_array[DI(0x6C)].bytes;
                vec_scale_to_length(d + 0x20, q + 0xC0, g_vehicle_push_speed * 0.020000001f);
                DF(0x28) = g_vehicle_max_reverse_speed * 0.020000001f;
                DI(0x50) = ((s32)(g_vehicle_df50_alt_frames) * 5 + 2) / 6;
                DF(0x18) = *(float *)(q + 0xF8);
                g_hero_state.unk1830 = obj;
                DI(0x9C) = 0;
                moby_set_state(obj, 3, -1);
            }
        }
        break;
    }
    case 3: {
        if (flag_set_first_pending(obj) != 0) {
            if (DI(0xBC) != -1) {
                STUB_printf(g_str_vehicle_debug_message_a);
                script_queue_keyed_request(DI(0xBC), DI(0xB8));
            }
            DI(0xB0) = 0x19;
        } else if (math_fast_float_d(d + 0xB0) != 0) {
            snd_play_from_class_bank(6, 0, obj, 0x988);
            DI(0xB0) = 0xaf;
        }
        if (DI(0x9C) != 0 || g_hero_state.unkC38 > 10.0f) {
            DI(0x9C) = DI(0x9C) | 4;
            StepAngleTowardTarget(d + 0x14, 0, g_vehicle_target_angle_degrees * 0.017453294f, g_vehicle_target_angle_step * 0.0003490659f);
            if (g_vehicle_active_flag != 0)
                FastVecAdd(d, d, d + 0x20);
            DF(0x28) = DF(0x28) - g_vehicle_decel_c * 0.00040000002f;
            if (DF(0x28) < -(g_vehicle_reverse_limit * 0.020000001f))
                DI(0x9C) = DI(0x9C) | 1;
            if (g_hero_state.unkC28 & 2) {
                DI(0x9C) = DI(0x9C) | 2;
                set_hero_animation_pal(0x81, 0, 12.0f);
            }
            if (math_fast_float_d(d + 0x50) != 0) {
                if (DI(0x9C) == 7) {
                    if (OH(0x34) & 1) {
                        OH(0x34) = OH(0x34) & 0xFFFE;
                        OB(0x31) = 1;
                        SetAnimation(obj, 1, 0, 5);
                        snd_play_from_class_bank(0, 0, obj, 0x988);
                    }
                    DI(0x50) = (((s32)(g_vehicle_timer_start) * 5 + 2) / 6);
                    hero_l08_enter_state_pal(0x31, 0);
                    set_hero_animation_pal(0x81, 0, 12.0f);
                    ((s32 *)g_hero_state.unk2290)[0x9C / 4] = -1;
                    if (g_vehicle_active_flag != 0)
                        DF(0x14) = g_vehicle_target_angle_degrees * 0.017453294f;
                    DF(0x54) = 0.07200001f;
                    qzero_nc(d + 0x20);
                    DI(0xA8) = 0;
                    DF(0x58) = DF(8);
                    cam_update_aim_values_pal(d + 0xA8, obj);
                    DF(0x64) = 0.0f;
                    g_vehicle_saved_x = g_vehicle_collision_x;
                    g_vehicle_saved_y = g_vehicle_collision_y;
                    g_vehicle_collision_x = g_vehicle_param_copy_a;
                    g_vehicle_collision_y = g_vehicle_param_copy_b;
                    g_hero_state.unk1830 = obj;
                    moby_set_state(obj, 5, -1);
                }
            }
            hero_move_with_mount_to_transform(obj, d);
        }
        DI(0xB4) = 0;
        break;
    }
    case 4:
        if (g_vehicle_hero_far_distance < vec_distance_xy(obj + 0x10, g_hero_state.pos)) {
            SetAnimation(obj, 0, 0, 0xA);
            moby_set_state(obj, 1, -1);
        }
        break;
    case 5: {
        {
            VoiceSlotCDF98 *slot = (VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70);
            if (slot->voice.owner != obj || slot->voice.active == 0)
                DI(0xAC) = snd_play_from_class_bank(1, 4, obj, 0x988);
        }
        cam_update_aim_values_pal(d + 0xA8, obj);
        DF(0x28) = -math_fast_sin_or_cos_b(DF(0x14)) * DF(0x54);
        {
            float c = DF(0x54) * math_fast_sin_or_cos_a(DF(0x14));
            DF(0x20) = c * math_fast_sin_or_cos_a(DF(0x18));
            DF(0x24) = c * math_fast_sin_or_cos_b(DF(0x18));
        }
        if ((((s32)(g_vehicle_timer_length) * 5 + 2) / 6) >= DI(0x50)) {
            if (OH(0x34) & 1) {
                OH(0x34) = OH(0x34) & 0xFFFE;
                OB(0x31) = 1;
                SetAnimation(obj, 1, 0, 0xA);
            }
            {
                float r = IntToFloat((((s32)(g_vehicle_timer_length) * 5 + 2) / 6) - DI(0x50)) / IntToFloat(g_vehicle_timer_length);
                DF(0x64) = r;
                if (r > 1.0f)
                    DF(0x64) = 1.0f;
                else if (r < 0.0f)
                    DF(0x64) = 0.0f;
            }
            vehicle_update_steering_pal(obj, d, DF(0x64));
            FastVecScale(d + 0x20, d + 0x20, 1.0f - DF(0x64));
            vec_build_spherical_offset(&scratch.v.velocity, DF(0x54), DF(0x18), -DF(0x14));
            FastVecScale(&scratch.v.velocity, &scratch.v.velocity, DF(0x64));
            FastVecAdd(d + 0x20, d + 0x20, &scratch.v.velocity);
        }
        if (g_vehicle_active_flag != 0)
            FastVecAdd(d, d, d + 0x20);
        if (vehicle_handle_collision_pal(obj, &saved) == 0) {
            float sp = DF(0x54) + g_vehicle_speed_accel * 0.00040000002f;
            float top = g_vehicle_l08_max_speed * 0.020000001f;
            float rate;
            DF(0x54) = sp;
            if (top < sp)
                DF(0x54) = top;
            rate = g_vehicle_l08_turn_rate * 0.0003490659f;
            if (DI(0x50) < ((s32)(g_vehicle_timer_start) * 5 + 2) / 6 - ((s32)(g_vehicle_timer_margin) * 5 + 2) / 6 && g_vehicle_active_flag != 0)
                DF(0x14) = fast_subtract_rotations(DF(0x14), rate);
            if (DF(0x14) < 0.0f)
                DF(0x14) = 0.0f;
            if (math_fast_float_d(d + 0x50) != 0) {
                SetAnimation(obj, 2, 0, 0xA);
                set_hero_animation_pal(0x82, 0, 12.0f);
                DF(0x40) = 0.0f;
                DF(0x48) = 0.0f;
                DF(0x44) = -(g_vehicle_l08_turn_rate * 0.0003490659f);
                moby_set_state(obj, 6, -1);
            }
        }
        if (OB(0x60) & 2)
            SetAnimation(obj, 2, 0, 0xA);
        hero_move_with_mount_to_transform(obj, d);
        break;
    }
    case 6: {
        float t;
        cam_update_aim_values_pal(d + 0xA8, obj);
        {
            VoiceSlotCDF98 *slot = (VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70);
            if (slot->voice.owner != obj || slot->voice.active == 0)
                DI(0xAC) = snd_play_from_class_bank(1, 4, obj, 0x988);
        }
        vehicle_update_steering_pal(obj, d, 1.0f);
        t = DF(0x5C);
        if (t < -0.4f) {
            if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x85 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x85) {
                set_hero_animation_pal(0x85, 0, 12.0f);
                snd_play_from_class_bank(2, 0, obj, 0x988);
            }
        } else if (t > 0.4f) {
            if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x86 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x86) {
                set_hero_animation_pal(0x86, 0, 12.0f);
                snd_play_from_class_bank(2, 0, obj, 0x988);
            }
        } else {
            if (g_vehicle_bank_limit_degrees * 4.986656e-05f < DF(0x44)) {
                if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x83 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x83)
                    set_hero_animation_pal(0x83, 0, 21.0f);
            } else if (DF(0x44) < -g_vehicle_bank_limit_degrees * 4.986656e-05f) {
                if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x81 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x81) {
                    set_hero_animation_pal(0x81, 0, 21.0f);
                    if (DI(0xB0) == 0) {
                        snd_play_from_class_bank(3, 0, obj, 0x988);
                        DI(0xB0) = 0x25;
                    }
                }
            } else if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x82 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x82) {
                set_hero_animation_pal(0x82, 0, 17.0f);
            }
        }
        {
            float a = DF(8), b = DF(0x58), c = g_vehicle_slope_limit;
            if (a - b <= c) {
                if (DI(0x98) == 0) {
                    float s = DF(0x54);
                    DF(0x54) = s + (((g_vehicle_cruise_speed * 0.020000001f) - s) * 0.14400001f);
                }
            } else {
                float e = g_vehicle_slope_threshold;
                float k = b - a;
                float lo, sp, top;
                k += e;
                k /= e - c;
                if (k > 1.0f)
                    k = 1.0f;
                else if (k < 0.0f)
                    k = 0.0f;
                lo = g_vehicle_cruise_speed * 0.020000001f;
                k = 1.0f - k;
                sp = lo + (k * ((g_vehicle_slow_speed * 0.020000001f) - lo));
                if (DI(0x98) == 0 || sp < DF(0x54))
                    DF(0x54) = DF(0x54) + ((sp - DF(0x54)) * 0.14400001f);
                top = g_vehicle_cruise_speed * 0.020000001f;
                if (top < DF(0x54))
                    DF(0x54) = top;
            }
        }
        if (DF(0x64) < 1.0f) {
            float w = DF(0x64) + g_vehicle_df64_offset * 1.2f;
            DF(0x64) = w;
            if (w > 1.0f)
                DF(0x64) = 1.0f;
            vec_build_spherical_offset(&scratch.v.velocity, DF(0x54), DF(0x18), -DF(0x14));
            FastVecScale(d + 0x20, d + 0x20, 1.0f - DF(0x64));
            FastVecScale(&scratch.v.velocity, &scratch.v.velocity, DF(0x64));
            FastVecAdd(d + 0x20, d + 0x20, &scratch.v.velocity);
        } else {
            vec_build_spherical_offset(d + 0x20, DF(0x54), DF(0x18), -DF(0x14));
        }
        if (g_vehicle_active_flag != 0)
            FastVecAdd(d, d, d + 0x20);
        g_hero_l08_extra_state.f[0x3C8 / 4] = g_hero_l08_extra_state.f[0x3C8 / 4]
            + (((DF(0x28) * g_vehicle_df28_blend_scale) - g_hero_l08_extra_state.f[0x3C8 / 4]) * 0.72f);
        if (g_vehicle_slope_threshold < DF(8) - DF(0x58)) {
            float ang, lim;
            SetAnimation(obj, 2, 0, 3);
            set_hero_animation_pal(0x84, 0, 12.0f);
            ang = DF(0x14);
            lim = g_vehicle_angle_limit_degrees * 0.017453294f;
            DI(0x60) = 0;
            DI(0x50) = g_vehicle_df50_frames;
            if (lim < ang)
                DF(0x68) = fast_subtract_rotations(lim, ang) / IntToFloat(g_vehicle_df50_frames);
            else
                DF(0x68) = 0.0f;
            moby_set_state(obj, 7, -1);
        }
        hero_move_with_mount_to_transform(obj, d);
        vehicle_handle_collision_pal(obj, &saved);
        if (g_hero_state.unk2294 != 0x31)
            moby_set_state(obj, 1, -1);
        break;
    }
    case 7: {
        cam_update_aim_values_pal(d + 0xA8, obj);
        if (math_fast_float_d(d + 0x50) != 0) {
            DI(0x50) = g_vehicle_df50_reset;
            moby_set_state(obj, 8, -1);
        }
        DF(0x28) = DF(0x28) + (-g_vehicle_decel_a * 0.00040000002f);
        FastVecAdd(d, d, d + 0x20);
        DF(0x54) = FastVecLength(d + 0x20);
        t = IntToFloat(DI(0x50)) / IntToFloat(g_vehicle_df50_frames);
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        if (g_vehicle_active_flag != 0)
            DF(0x14) = FastAddRotations(DF(0x14), DF(0x68));
        vehicle_update_steering_pal(obj, d, 1.0f);
        vehicle_handle_collision_pal(obj, &saved);
        hero_move_with_mount_to_transform(obj, d);
        break;
    }
    case 8: {
        cam_update_aim_values_pal(d + 0xA8, obj);
        if (g_vehicle_angle_threshold_degrees * 0.017453294f < DF(0x14) && DF(8) - DF(0x58) < g_vehicle_slope_threshold) {
            set_hero_animation_pal(0x82, 0, 12.0f);
            SetAnimation(obj, 2, 0, 0xA);
            DF(0x64) = 0.0f;
            moby_set_state(obj, 6, -1);
        } else {
            math_fast_float_d(d + 0x50);
        }
        DF(0x28) = DF(0x28) + (-g_vehicle_decel_a * 0.00040000002f);
        if (g_vehicle_active_flag != 0)
            FastVecAdd(d, d, d + 0x20);
        DF(0x54) = FastVecLength(d + 0x20);
        vehicle_update_steering_pal(obj, d, 1.0f);
        hero_move_with_mount_to_transform(obj, d);
        vehicle_handle_collision_pal(obj, &saved);
        break;
    }
    case 9: {
        cam_update_aim_values_pal(d + 0xA8, obj);
        if (flag_set_first_pending(obj) != 0) {
            if (DI(0xAC) != -1) {
                if (((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.owner == obj
                    && ((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.active != 0)
                    snd_stop_voice(DI(0xAC));
            }
            DI(0xAC) = -1;
            snd_play_from_class_bank(4, 0, obj, 0x988);
            DI(0xB0) = 0xc;
        }
        if (g_vehicle_active_flag != 0)
            DF(0x18) = FastAddRotations(DF(0x18), g_vehicle_yaw_step * 0.0003490659f);
        DF(0x28) = DF(0x28) + (-g_vehicle_decel_b * 0.00040000002f);
        if (g_vehicle_active_flag != 0)
            FastVecAdd(d, d, d + 0x20);
        hero_move_with_mount_to_transform(obj, d);
        vehicle_handle_collision_pal(obj, &saved);
        if (DF(0x28) > 0.0f || DF(8) < 12.0f || FastVecLength(d + 0x20) < 0.020000001f
            || (s32)OH(0x96) > ((s32)(g_vehicle_threshold_frames) * 5 + 2) / 6) {
            SpawnExplosionEffects_pal(obj, g_str_effect_name, 0, 0.0f, 0.0f, 0xA, 3, 0x10, 4.0f, 2.0f, 9.0f, 1.0f,
                          -1, 15.0f, 1, 1, -1, 0, 0x810001);
            g_held_object_ptr[0] = 0;
            hero_record_play_counters_pal();
        }
        break;
    }
    case 10: {
        float dist, lim;
        if (DI(0xAC) != -1) {
            if (((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.owner == obj
                    && ((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.active != 0)
                snd_stop_voice(DI(0xAC));
        }
        DI(0xAC) = -1;
        dist = fast_vec_dist(d, d + 0x80);
        lim = DF(0x94) < dist ? DF(0x94) : dist;
        if (g_vehicle_active_flag != 0) {
            StepAngleTowardTarget(d + 0x14, 0, 0.0f, g_vehicle_angle_step_zero * 0.0003490659f);
            StepAngleTowardTarget(d + 0x10, 0, 0.0f, g_vehicle_angle_step_zero * 0.0003490659f);
        }
        if ((OB(0x60) & 2) && OB(0x42) == 3) {
            SetAnimation(obj, 0, 0, 0xA);
            OB(0x31) = 0;
            OH(0x34) = OH(0x34) | 1;
        }
        if (lim < dist) {
            FastVecSub(&scratch.v.velocity, d + 0x80, d);
            vec_scale_to_length(&scratch.v.velocity, &scratch.v.velocity, lim * g_vehicle_velocity_length_scale);
            FastVecScale(d + 0x20, d + 0x20, g_vehicle_l08_velocity_damping);
            FastVecAdd(d + 0x20, d + 0x20, &scratch.v.velocity);
            if (g_vehicle_active_flag != 0)
                FastVecAdd(d, d, d + 0x20);
            hero_move_with_mount_to_transform(obj, d);
            break;
        }
        qcopy(d, d + 0x80);
        DF(0x94) = 0.0f;
        if (g_hero_state.unkC28 & 2) {
            g_hero_state.unk1830 = 0;
            g_vehicle_collision_x = g_vehicle_saved_x;
            g_vehicle_collision_y = g_vehicle_saved_y;
            DI(0x50) = 0;
            hero_l08_enter_state_pal(0, 1);
            hero_reset_speeds_and_vectors();
            SetAnimation(obj, 0, 0, 0xA);
            if (DI(0x6C) > 0) {
                qcopy(d, g_moby_array[DI(0x6C)].bytes + 0x10);
                moby_place_at_stored_transform(obj);
            }
            if (DI(0xC4) != -1) {
                STUB_printf(g_str_vehicle_debug_message_b);
                script_queue_keyed_request(DI(0xC4), DI(0xC0));
            }
            moby_set_state(obj, 1, -1);
        }
        break;
    }
    }
    {
        float f;
        s32 *slot;
        if (DF(0) < 10.0f) DF(0) = 10.0f;
        if (DF(0) > 1013.0f) DF(0) = 1013.0f;
        if (DF(4) < 10.0f) DF(4) = 10.0f;
        if (DF(4) > 1013.0f) DF(4) = 1013.0f;
        if (DF(8) < 10.0f) DF(8) = 10.0f;
        if (DF(8) > 1013.0f) DF(8) = 1013.0f;
        if ((u32)(OB(0x20) - 5) < 5) {
            if (OB(0x31) != 0) {
                if (fast_vec_dist(obj + 0x10, g_hero_position_vec) < 80.0f) {
                    moby_update_ground_check(obj);
                    OB(0x6F) = 0x4B;
                }
            }
            FastVecScale(&scratch.v.velocity, d + 0x20, 0.25f);
            for (n = 0; n < 7; n++) {
                moby_transform_joint_to_world(obj, n, &scratch.v.joint);
                for (f = 0.0f; f < 1.0f; f += 0.2f) {
                    FastVecScale(&scratch.v.point, d + 0x20, -f);
                    FastVecAdd(&scratch.v.point, &scratch.v.point, &scratch.v.joint);
                    t = 0.0f;
                    if (OB(0x20) >= 7)
                        t = 0.07f;
                    p = part_spawn_spinning_spark_pal(&scratch.v.point, 2, &scratch.v.velocity, t, 0.5f, 0x0E7F7F7F, 0, 1.01f,
                                      math_random_float_range(24000.0f, 35000.0f));
                    if (p != 0)
                        p[8] = func_001163B0();
                }
            }
            slot = (s32 *)(d + 0x70);
            for (i = 0; i < 4; i++) {
                if (slot[i] != 0xFF && IsPointInCuboid(d, slot[i]) != 0
                    && *(float *)(g_collision_box_table[slot[i]].bytes + 0x38) < g_hero_state.pos[2]) {
                    /* Written out: SetAnimation's int compare would keep 3 in a saved register across the loop. */
                    if (OB(0x43) != 3)
                        anim_start_blended_pal(obj, 3, 0, 2);
                    set_hero_animation_pal(0x88, 0, 12.0f);
                    qcopy(d + 0x80, g_collision_box_table[slot[i]].bytes + 0x30);
                    DF(0x90) = fast_vec_dist(g_hero_state.pos, d + 0x80);
                    {
                        float m = FastVecLength(d + 0x20) > 0.080000006f ? FastVecLength(d + 0x20) : 0.080000006f;
                        DF(0x94) = m;
                    }
                    g_hero_state.unkC20 = g_vehicle_unk_ratio_scale / (DF(0x90) / DF(0x94));
                    moby_set_state(obj, 0xA, -1);
                }
            }
        }
        {
            int j;
            slot = (s32 *)(d + 0xA0);
            for (j = 0; j < 2; j++) {
                if (slot[j] != 0 && slot[j] != 0xFF && (((DI(0xB4) >> j) ^ 1) & 1)
                    && IsPointInCuboid(d, slot[j]) != 0 && OB(0x20) != 9) {
                    snd_play_from_class_bank(5, 0, obj, 0x988);
                    DI(0xB4) = DI(0xB4) | (1 << j);
                }
            }
        }
        math_fast_float_d(d + 0x98);
        math_fast_float_d(d + 0xB0);
    }
}
