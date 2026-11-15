#include "include_asm.h"
#include "common.h"

extern int D_001B2758 MACRO_ADDR;
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern void vec_clear_128(void *), gravity_get_dir_at_object(void *, void *, int);
extern char *moby_get_private_value_0(void *);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float), math_random_int_range(int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void moby_set_state(void *, int, int), anim_start_blended(void *, int, int, int);
extern float D_001BAFA8;

typedef int TI128_00318340 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128_00318340 q[0x260]; } Hero_00318340;
extern u8 g_hero_state[];
extern char g_hero_position[];
extern u8 g_sound_state[];

extern char D_001A8BD0[16] MACRO_ADDR;
extern char D_001AFA80[];
extern void STUB_printf(const char *, ...);
extern void gfx_register_overlay_draw_callback(void (*)(char *), char *);
extern int math_fast_float_d(void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(void *);
extern void SetDeathBits(void *, int, int);
extern int math_random_int_below(int);
extern float moby_turn_toward_position(void *, void *, void *, float, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern int IsPointInCuboid(void *, int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int math_is_value_within_step(void *, float);
extern int flag_set_first_pending(void *);
extern int flag_is_third_pending_set(void *);
extern void *part_spawn_gravity_fade(void *, void *, int, u32, int, int, int, int, float, float, float);
extern void path_sample_position(void *, int, void *, void *, int, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void hover_enemy_update_body_group(char *);
extern void hover_enemy_draw_effects(char *);
extern void hover_enemy_tick_timers(char *);
extern int group_claim_lead_token(char *);
extern int group_pass_lead_token(char *);
extern int group_is_moby_member(unsigned char *);
extern int moby_is_target_outside_turn_limit(char *, float);
extern void moby_turn_toward_target(char *);
extern void *part_spawn_spinning_effect_moby(char *, void *, void *, int, int, float);
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);

/* One of the twelve 0xA0-byte records at *D_001B2758 that func_0031DEE8 steps for their
   owner: the boot counterpart of the level records func_L00_003BBB68 updates. */
typedef struct {
    float out0[4];          /* 0x00: ang0 through the two angle helpers, times amp0 */
    float out1[4];          /* 0x10: the same for ang1 */
    float start[4];         /* 0x20: copied from the owner's position each frame */
    float pos[4];           /* 0x30: follows the target */
    float ang0[3];          /* 0x40 */
    float rate0[3];         /* 0x4C */
    float amp0[3];          /* 0x58 */
    float ang1[3];          /* 0x64 */
    float rate1[3];         /* 0x70 */
    float amp1[3];          /* 0x7C */
    int life;               /* 0x88: timer, frees the record when it expires */
    char *owner;            /* 0x8C */
    char *target;           /* 0x90 */
    int time;               /* 0x94: timer, also counts the approach */
    int duration;           /* 0x98 */
    int hit;                /* 0x9C */
} Slot31DEE8;

/* The 0xE0-byte class records; D_00139568 maps a class number to its record. */
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class31DEE8;

extern unsigned char g_item_slot_to_record[];
extern Class31DEE8 g_weapon_table[];
extern float FastAddRotations(float angle, float step);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern float IntToFloat(int ticks);
extern int math_fast_float_d(void *timer);
extern void lerp_vector(void *out, void *from, void *to, float t);
extern void make_hit_descriptor(void *packet, char *owner, int flags, void *direction, float amount);
extern void QueueMobyImpact(char *target, void *packet);
extern void part_spawn_hit_sparks(void *pos, int count, int mode);
extern int StartAttachedEffect(char *target, int kind, int value);

extern char F669d6320_D_001BAFC0[];

extern void F669d6320_FUN_00282F20(void *out, void *in, float scale);

extern void F669d6320_FUN_00282CC0(void *out, void *in1, void *in2);

extern int F669d6320_FUN_002761F8(void *a, void *b, int mode, void *self, int flag);

extern void F669d6320_FUN_00282D30(void *out, void *in, float scale);

extern void F2c74c194_FUN_00282D30(char *dst, char *src, float scale);

extern void F5a19df7a_FUN_002FC560(unsigned int a, unsigned long b);

extern void F5a19df7a_FUN_0031E2A0(char *p);

extern void F5a19df7a_FUN_0031E560(char *p);

extern s32 F5a19df7a_FUN_002A7820(int a, int b);

extern float F5a19df7a_FUN_002A7940(void);

extern void F5a19df7a_FUN_0031EB00(char *a, int b, float e, char *c, float f, int d, int g);

extern void Fc936841d_FUN_00282CF0(char *local, char *first, char *second);

extern void Fc936841d_FUN_00282CC0(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* The four 16-byte blocks the record carries and scales. */
#ifndef RAC2_T_BLOCK_0031A340
#define RAC2_T_BLOCK_0031A340
typedef struct {
    float q[4];
} Block_0031a340;
#endif

/* The 240-byte record func_0031A340 builds: a scaled matrix, a colour, the
   looked-up handle, the fixed fields and the two computed vectors. */
#ifndef RAC2_T_LOC_0031A340
#define RAC2_T_LOC_0031A340
typedef struct {
    Block_0031a340 b0;
    Block_0031a340 b1;
    Block_0031a340 b2;
    Block_0031a340 b3;
    int k0;
    int k1;
    int k2;
    int k3;
    int z80;
    int z84;
    int z88;
    float f92;
    float f96;
    int z100;
    float f104;
    float f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float v192;
    float v196;
    float v200;
    float v204;
    float v208;
    float f212;
    float f216;
    float v220;
    float e0;
    float e1;
    float e2;
    float e3;
} Loc_0031a340;
#endif

/* The state block whose +0x140 holds the position the record is built around. */
#ifndef RAC2_T_STATE_001B5200
#define RAC2_T_STATE_001B5200
typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;
#endif

extern State_001b5200 g_active_camera;

extern void mat_build_rotation_from_angles(void *, float *);

extern int flyer_init_check_death(char *);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void snd_stop_voice(int);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int PlayMobySound(int, int, void *);
extern void SetDeathBits(void *, int, int);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void func_002A677C(void *);
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);
extern void flyer_tick_timers(char *);
extern unsigned char g_sound_state[];
extern unsigned char g_hero_state[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *g_path_table[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");

#undef FI
#undef FF
#undef FH
#undef FU
#undef FB
#undef FP

extern void flyer_alert_group(void *);



extern void gfx_update_color_fade(char *, char *);
extern int FastDecTimer(void *);
extern void math_update_wrapped_angle_offset(char *, float, float, char *, float, char *);
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);

/* A moby's per-frame update: pvars at moby+0x68, a switch on moby+0x95, a switch on the state at
   moby+0x20, then the sound-slot keep-alive on pvars+0x2C4. The template vector is MACRO_ADDR: retail
   schedules its address as one `la`, not a split %hi/%lo pair. func_L00_003BD7E0 is the level twin. */
/* Updates one flying enemy each frame: picks its next action, moves it, aims and fires at the hero, and keeps its sound playing. */
void hover_enemy_update(char *obj)
{
    f32 muzzle_pos[4] __attribute__((aligned(16)));
    f32 target_pos[4] __attribute__((aligned(16)));
    f32 aim_dir[4] __attribute__((aligned(16)));
    f32 axis[4] __attribute__((aligned(16)));
    f32 to_target[4] __attribute__((aligned(16)));
    char *pv = *(char **)(obj + 0x68);
    char *tgt13, *tgt10, *tgt16;
    f32 *pos;
    s32 *path;
    int id;
    int mode0, mode2, flags, state_now;
    float h13, h12, floor12, y12, diff12, h5, diff5, dist10, dot, dist11, dist16, sx, sy, sz;

    if (((Hero_00318340 *)g_hero_state)->b[0x22B4] == 1)
        return;
    switch (*(u8 *)(obj + 0x95)) {
    case 0:
        if (*(s32 *)(pv + 0x2E0) != 0 && flag_is_third_pending_set(obj) == 0)
            break;
        if (flag_set_second_pending(obj) != 0)
            moby_set_controller_speed_limits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        mode0 = *(s32 *)(pv + 0x34);
        if (mode0 == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            if (math_fast_float_d(pv + 0x2D0) != 0) {
                moby_set_state(obj, 9, 3);
                if (*(u8 *)(obj + 0x43) != mode0)
                    anim_start_blended(obj, 1, 0, 4);
            }
        } else if (*(s16 *)(pv + 0x286) != 0) {
            moby_set_state(obj, 8, 2);
            *(s16 *)(pv + 0x286) = 0;
            if (*(s16 *)(pv + 0x280) < 300)
                *(s16 *)(pv + 0x280) = math_random_int_range(0x1E0, 0x258);
        }
        break;
    case 2:
        if (flag_set_second_pending(obj) != 0) {
            moby_set_controller_speed_limits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            *(f32 *)(obj + 0x48) = 1.0f;
        }
        mode2 = *(s32 *)(pv + 0x34);
        if (mode2 == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            moby_set_state(obj, 9, 3);
            if (*(u8 *)(obj + 0x43) != mode2)
                anim_start_blended(obj, 1, 0, 4);
        } else if (*(s16 *)(pv + 0x280) == 0) {
            moby_set_state(obj, 2, 0);
            if (*(u8 *)(obj + 0x43) != 2)
                anim_start_blended(obj, 2, 0, 10);
        }
        break;
    case 1:
        if (flag_set_second_pending(obj) != 0)
            moby_set_controller_speed_limits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(pv + 0x34) == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            if (math_fast_float_d(pv + 0x2D0) == 0)
                break;
        } else {
            if (*(s16 *)(pv + 0x286) == 0 || *(s32 *)(pv + 0x2A4) == 0)
                break;
            *(s16 *)(pv + 0x286) = 0;
        }
        moby_set_state(obj, 0xD, 3);
        if (*(u8 *)(obj + 0x43) != 0x19)
            anim_start_blended(obj, 0x19, 0, 4);
        break;
    case 3:
        if (flag_set_second_pending(obj) != 0) {
            moby_set_controller_speed_limits(obj, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(f32 *)(obj + 0x48) = 1.0f;
        }
        if (*(s32 *)(pv + 0x34) != 1 && *(u8 *)(obj + 0x20) != 0xD && *(u8 *)(obj + 0x20) != 0xC && *(u8 *)(obj + 0x20) != 0xF) {
            moby_set_state(obj, 8, 2);
            if (*(u8 *)(obj + 0x43) != 6)
                anim_start_blended(obj, 6, 0, 10);
            *(s16 *)(pv + 0x280) = math_random_int_range(0x244, 0x258);
            if (*(s32 *)(pv + 0x28C) != 0) {
                moby_set_state(obj, 3, 1);
                if (*(u8 *)(obj + 0x43) != 0xB)
                    anim_start_blended(obj, 0xB, 0, 0x14);
            }
        }
        break;
    case 4:
        if (flag_set_first_pending(obj) != 0)
            *(s16 *)(pv + 0x46) = 0x3C;
        flags = moby_dispatch_action_by_kind(obj, pv + 0x80);
        if ((flags & 1) || *(f32 *)(pv + 0x40) <= 0.0f) {
            part_spawn_explosion_with_sparks(obj, obj + 0x10, -1, 1.0f, 13.0f);
            SetDeathBits(obj, 0, 3);
            moby_mark_spawned(obj);
            return;
        }
        if (flags & 2) {
            if (*(s32 *)(pv + 0x34) == 1) {
                moby_set_state(obj, 7, 3);
                if (*(u8 *)(obj + 0x43) != 7)
                    anim_start_blended(obj, 7, 0, 6);
            } else {
                moby_set_state(obj, 8, 2);
                if (*(u8 *)(obj + 0x43) != 6)
                    anim_start_blended(obj, 6, 0, 10);
                *(s16 *)(pv + 0x280) = math_random_int_range(0x244, 0x258);
            }
            if (*(s32 *)(pv + 0x2A4) != 1)
                *(s32 *)(pv + 0x2A4) = 1;
        }
        break;
    }

    switch (*(u8 *)(obj + 0x20)) {
    case 2:
        break;
    case 7:
        if (moby_is_target_outside_turn_limit(obj, 10.0f) != 0) {
            moby_turn_toward_target(obj);
        } else {
            moby_set_state(obj, 0xA, -1);
            if (*(u8 *)(obj + 0x43) != 0x1E)
                anim_start_blended(obj, 0x1E, 0, 6);
        }
        break;
    case 3:
        moby_scale_owner_words_by_angles(0.06981318f, 0.052359886f, obj, pv + 0x2A8, 0.013089972f, pv + 0x2AC);
        break;
    case 13:
        tgt13 = *(char **)(pv + 0x30);
        *(s32 *)(pv + 0x2C0) += 1;
        if (tgt13 != 0) {
            moby_turn_toward_position(obj, tgt13, pv + 0x29C, 0.001f, 0.01f, 0.1f);
            math_spring_float_to_goal(obj + 0xF4, 0.0f, pv + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            math_spring_float_to_goal(obj + 0xF0, 0.0f, pv + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            h13 = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
            if (*(f32 *)(obj + 0x18) - h13 > 0.05f) {
                *(f32 *)(obj + 0x18) -= h13 * 0.00025f;
            } else {
                moby_set_state(obj, 6, -1);
                if (*(u8 *)(obj + 0x43) != 0xE)
                    anim_start_blended(obj, 0xE, 0, 3);
            }
            if (*(u8 *)(obj + 0x60) & 2) {
                moby_set_state(obj, 0xC, -1);
                if (*(u8 *)(obj + 0x43) != 0x1A)
                    anim_start_blended(obj, 0x1A, 0, 0xF);
            }
        }
        break;
    case 12:
        *(s32 *)(pv + 0x2C0) += 1;
        moby_turn_toward_target(obj);
        h12 = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
        y12 = *(f32 *)(obj + 0x18);
        floor12 = *(f32 *)(pv + 0x2DC);
        diff12 = y12 - h12;
        h12 -= 3.0f;
        if (floor12 != -1.0f && y12 <= floor12) {
            if (group_is_moby_member(obj) == 0) {
                moby_set_state(obj, 0x10, -1);
                if (*(u8 *)(obj + 0x43) != 0x1D)
                    anim_start_blended(obj, 0x1D, 0, 3);
            } else {
                *(s32 *)(pv + 0x354) = 0;
                group_claim_lead_token(obj);
                moby_set_state(obj, 0xE, -1);
            }
        } else if (diff12 > 0.05f) {
            math_step_value_toward_target(obj + 0x18, pv + 0x290, h12, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            STUB_printf(D_001AFA80, *(s32 *)(pv + 0x2C0));
            moby_set_state(obj, 6, -1);
            if (*(u8 *)(obj + 0x43) != 0xE)
                anim_start_blended(obj, 0xE, 0, 3);
        }
        break;
    case 14:
        if (flag_set_first_pending(obj) != 0) {
            *(TI128_00318340 *)(pv + 0x360) = *(TI128_00318340 *)(obj + 0x10);
            if (*(s32 *)(pv + 0x350) != 0)
                *(f32 *)(pv + 0x368) = *(f32 *)(pv + 0x2DC) + math_random_float_range(4.0f, 7.0f);
            else
                *(f32 *)(pv + 0x368) = *(f32 *)(pv + 0x2DC) + math_random_float_range(-3.0f, 3.0f);
        }
        if (fast_vec_dist(obj + 0x10, pv + 0x360) < 0.05f) {
            *(s32 *)(pv + 0x354) = 0;
            moby_set_state(obj, 0x10, -1);
        }
        *(s32 *)(pv + 0x2C0) += 1;
        moby_turn_toward_target(obj);
        math_step_value_toward_target(obj + 0x18, pv + 0x290, *(f32 *)(pv + 0x368), 0.004166667f, 0.004166667f, 0.16666667f);
        break;
    case 4:
        if (*(u8 *)(obj + 0x60) & 2) {
            moby_set_state(obj, 5, -1);
            if (*(u8 *)(obj + 0x43) != 0xD)
                anim_start_blended(obj, 0xD, 0, 0xF);
        }
        break;
    case 5:
        if (*(char **)(pv + 0x30) != 0) {
            math_spring_float_to_goal(obj + 0xF4, 0.0f, pv + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            euler_rotation_basis(obj + 0xC0, obj + 0xF0);
            moby_turn_toward_position(obj, *(char **)(pv + 0x30), pv + 0x29C, 0.001f, 0.01f, 0.1f);
            h5 = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
            diff5 = *(f32 *)(obj + 0x18) - h5;
            h5 -= 3.0f;
            if (diff5 > 0.05f) {
                math_step_value_toward_target(obj + 0x18, pv + 0x290, h5, 0.025000002f, 0.16333334f, 0.25f);
            } else {
                moby_set_state(obj, 6, -1);
                if (*(u8 *)(obj + 0x43) != 0xE)
                    anim_start_blended(obj, 0xE, 0, 3);
            }
        }
        break;
    case 6:
        if (*(u8 *)(obj + 0x60) & 2) {
            moby_set_state(obj, 0xA, 3);
            if (*(u8 *)(obj + 0x43) != 0x1E)
                anim_start_blended(obj, 0x1E, 0, 6);
            *(f32 *)(obj + 0x18) = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
        }
        break;
    case 9:
        if (*(u8 *)(obj + 0x60) & 2) {
            moby_set_controller_speed_limits(obj, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            moby_set_state(obj, 7, -1);
            if (*(u8 *)(obj + 0x43) != 7)
                anim_start_blended(obj, 7, 0, 6);
        }
        break;
    case 10:
        if (*(u8 *)(obj + 0x60) & 2) {
            if (moby_is_target_outside_turn_limit(obj, 10.0f) != 0) {
                moby_set_state(obj, 7, -1);
                if (*(u8 *)(obj + 0x43) != 7)
                    anim_start_blended(obj, 7, 0, 6);
            } else if (((Hero_00318340 *)g_hero_state)->ptr[0x249C / 4] == (u8 *)obj || math_random_int_below(6) == 1) {
                moby_set_state(obj, 0xB, -1);
                if (*(u8 *)(obj + 0x43) != 0x10)
                    anim_start_blended(obj, 0x10, 0, 7);
            }
        }
        dist10 = moby_get_anim_value(obj);
        if (math_is_value_within_step(obj, 17.0f) != 0) {
            moby_transform_joint_to_world(obj, 4, muzzle_pos);
            tgt10 = *(char **)(pv + 0x30);
            if (tgt10 == (char *)((Hero_00318340 *)g_hero_state)->ptr[0x2290 / 4]) {
                qcopy(target_pos, &((Hero_00318340 *)g_hero_state)->q[0xD0 / 16]);
                pos = target_pos;
            } else {
                if (tgt10 == 0)
                    break;
                qcopy(target_pos, tgt10 + 0x10);
                pos = target_pos;
                target_pos[2] += *(f32 *)(tgt10 + 0xC) * 0.0009765625f;
            }
            if (moby_is_target_outside_turn_limit(obj, 10.0f) != 0) {
                FastVecSub(to_target, pos, muzzle_pos);
                qcopy(aim_dir, D_001A8BD0);
                aim_dir[0] = 1.0f;
                matrix_mul_vec3(aim_dir, aim_dir, obj + 0xC0);
                FastVecCross(axis, aim_dir, to_target);
                dot = FastVecDot(aim_dir, to_target);
                if (dot > 0.0f)
                    math_apply_axis_rotation_to_quat(aim_dir, aim_dir, axis, -0.17453294f);
                else
                    math_apply_axis_rotation_to_quat(aim_dir, aim_dir, axis, 0.17453294f);
            } else {
                FastVecSub(aim_dir, pos, muzzle_pos);
            }
            vec_scale_to_length(aim_dir, aim_dir, 0.33333334f);
            part_spawn_spinning_effect_moby(obj, aim_dir, muzzle_pos, 0, 0, *(u8 *)(pv + 0x54));
        } else if (dist10 < 17.0f && *(u8 *)(obj + 0x43) == 0x1E) {
            moby_transform_joint_to_world(obj, 4, muzzle_pos);
        }
        break;
    case 11:
        if (*(u8 *)(obj + 0x60) & 2) {
            if (vec_distance_xy(obj + 0x10, g_hero_position) > 4.0f) {
                moby_set_controller_speed_limits(obj, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                moby_set_state(obj, 0xA, -1);
                if (*(u8 *)(obj + 0x43) != 0x1E)
                    anim_start_blended(obj, 0x1E, 0, 6);
            } else {
                moby_set_controller_speed_limits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                moby_set_state(obj, 0xA, -1);
                if (*(u8 *)(obj + 0x43) != 0x1E)
                    anim_start_blended(obj, 0x1E, 0, 6);
            }
        }
        dist11 = moby_get_anim_value(obj);
        if (*(u8 *)(obj + 0x42) == 0x10 && (dist11 <= 5.0f || (dist11 >= 12.0f && dist11 <= 15.0f)))
            *(s32 *)(pv + 0x2C8) = 1;
        else
            *(s32 *)(pv + 0x2C8) = 0;
        break;
    case 15:
        if (flag_set_first_pending(obj) != 0) {
            *(f32 *)(pv + 0x374) = 0.0f;
            *(f32 *)(pv + 0x378) = 0.0f;
        }
        if (*(s32 *)(pv + 0x37C) == 0) {
            if (IsPointInCuboid(g_hero_position, *(s32 *)(pv + 0x35C)) != 0)
                *(s32 *)(pv + 0x37C) = 1;
        } else {
            path = (s32 *)g_path_table[*(s32 *)(pv + 0x370)];
            math_step_value_toward_target(pv + 0x374, pv + 0x378, (f32)(*path - 1), 0.013888889f, 0.0013888889f, 0.33333334f);
            path_sample_position(path, 0, obj + 0x10, obj + 0xF0, 0, *(f32 *)(pv + 0x374));
            euler_rotation_basis(obj + 0xC0, obj + 0xF0);
            if ((f32)(*path - 1) <= *(f32 *)(pv + 0x374))
                moby_set_state(obj, 0xA, 3);
        }
        break;
    case 16:
        if ((*(u8 *)(obj + 0x60) & 2) && group_is_moby_member(obj) != 0) {
            *(s32 *)(pv + 0x354) += 1;
            if (*(s32 *)(pv + 0x350) != 0) {
                if (*(s32 *)(pv + 0x354) >= 3 && group_pass_lead_token(obj) != 0) {
                    moby_set_state(obj, 0xE, -1);
                    if (*(u8 *)(obj + 0x43) != 0x1A)
                        anim_start_blended(obj, 0x1A, 0, 0xF);
                }
            } else {
                moby_set_state(obj, 0xE, -1);
                if (*(u8 *)(obj + 0x43) != 0x1A)
                    anim_start_blended(obj, 0x1A, 0, 0xF);
            }
        }
        dist16 = moby_get_anim_value(obj);
        if (math_is_value_within_step(obj, 16.0f) != 0) {
            moby_transform_joint_to_world(obj, 4, muzzle_pos);
            tgt16 = *(char **)(pv + 0x30);
            if (tgt16 == (char *)((Hero_00318340 *)g_hero_state)->ptr[0x2290 / 4]) {
                qcopy(target_pos, &((Hero_00318340 *)g_hero_state)->q[0xD0 / 16]);
                pos = target_pos;
            } else {
                if (tgt16 == 0)
                    break;
                qcopy(target_pos, tgt16 + 0x10);
                pos = target_pos;
                target_pos[2] += *(f32 *)(tgt16 + 0xC) * 0.0009765625f;
            }
            FastVecSub(aim_dir, pos, muzzle_pos);
            vec_scale_to_length(aim_dir, aim_dir, 0.33333334f);
            PlayMobySound(0xB, 0, obj);
            part_spawn_spinning_effect_moby(obj, aim_dir, muzzle_pos, 0, 0, *(u8 *)(pv + 0x54));
        } else if (dist16 < 17.0f && *(u8 *)(obj + 0x43) == 0x1E) {
            moby_transform_joint_to_world(obj, 4, muzzle_pos);
            sx = math_random_float_range(1.0f, 1.5f) * 210000.0f;
            sy = math_random_float_range(0.2f, 0.4f) * 210000.0f;
            sz = math_random_signed_float_range(0.0f, 0.1f);
            part_spawn_gravity_fade(muzzle_pos, D_001A8BD0, 4, 0x808080, 9, 0x4F, 0, 0, sx, sy, sz);
        }
        break;
    }

    state_now = *(u8 *)(obj + 0x20);
    if (state_now == 12 || state_now == 13 || state_now == 14 || state_now == 16) {
        u8 *recA;
        recA = *(s32 *)(pv + 0x2C4) * 0x70 + g_sound_state;
        if (*(char **)(recA + 0x88) != obj || recA[0x74] == 0)
            *(s32 *)(pv + 0x2C4) = PlayMobySound(10, 4, obj);
    } else {
        u8 *recB;
        id = *(s32 *)(pv + 0x2C4);
        if (id != -1) {
            recB = id * 0x70 + g_sound_state;
            if (*(char **)(recB + 0x88) == obj && recB[0x74] != 0)
                snd_stop_voice(id);
        }
        *(s32 *)(pv + 0x2C4) = -1;
    }
    hover_enemy_update_body_group(obj);
    hover_enemy_tick_timers(obj);
    gfx_register_overlay_draw_callback(hover_enemy_draw_effects, obj);
}
