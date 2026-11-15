/* func_L08_003CDF98: the hero-NPC state machine shared by Tabora, Dobbo and Grelbin
 * (levels 08, 09, 19), dispatched on moby byte 0x20 over the NPC block at moby+0x68.
 * Own unit: -G8 for the $gp tuning constants, -g for the nop pairs before div.s,
 * -frac2-qcopy for the 16-byte copies, -ffast-math for case 10's min.s.
 * Nothing reads the clamped ratio in case 7: retail still has its div.s and c.lt.s.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;

/* $gp-relative tuning constants (retail reads them as one-instruction gp loads). */
extern float D_L08_001AFFD0 __attribute__((sda));
extern float D_L08_001AFFD4 __attribute__((sda));
extern float D_L08_001AFFD8 __attribute__((sda));
extern s32 D_L08_001AFFDC __attribute__((sda));
extern s32 D_L08_001AFFE0 __attribute__((sda));
extern s32 D_L08_001AFFE4 __attribute__((sda));
extern float D_L08_001AFFE8 __attribute__((sda));
extern float D_L08_001AFFF8 __attribute__((sda));
extern float D_L08_001AFFFC __attribute__((sda));
extern float D_L08_001B0000 __attribute__((sda));
extern float D_L08_001B000C __attribute__((sda));
extern float D_L08_001B0010 __attribute__((sda));
extern float D_L08_001B0014 __attribute__((sda));
extern float D_L08_001B0018 __attribute__((sda));
extern float D_L08_001B0070 __attribute__((sda));
extern float D_L08_001B007C __attribute__((sda));
extern s32 D_L08_001B0084 __attribute__((sda));
extern float D_L08_001B0088 __attribute__((sda));
extern float D_L08_001B008C __attribute__((sda));
extern s32 D_L08_001B0090 __attribute__((sda));
extern float D_L08_001B0094 __attribute__((sda));
extern float D_L08_001B0098 __attribute__((sda));
extern float D_L08_001B009C __attribute__((sda));
extern float D_L08_001B00A0 __attribute__((sda));
extern float D_L08_001B00A4 __attribute__((sda));
extern float D_L08_001B00A8 __attribute__((sda));
extern float D_L08_001B00FC __attribute__((sda));
extern float D_L08_001B0100 __attribute__((sda));
extern float D_L08_001B0104 __attribute__((sda));
extern s32 D_L08_001B0108 __attribute__((sda));
extern float D_L08_001B010C __attribute__((sda));
extern float D_L08_001B0124 __attribute__((sda));
extern float D_L08_001B0128 __attribute__((sda));
extern s32 D_L08_001B0130 __attribute__((sda));
extern float D_L08_001B0134 __attribute__((sda));
extern float D_L08_001B0138 __attribute__((sda));
extern float D_L08_001B013C __attribute__((sda));
extern s32 D_L08_001B0140 __attribute__((sda));
extern float D_L08_001B3410;
typedef struct { u8 bytes[0x100]; } HeroCDF98;
extern HeroCDF98 *D_L08_001B29DC;
extern float D_L08_001B2094;
extern float D_L08_001B2098;
extern float D_L08_001B3414;
extern s32 D_00138324[];
typedef struct { float f[0x100]; } StateCDF98;
extern StateCDF98 D_L08_001B99C0;
extern char D_L08_001B9B00[];
extern char D_L08_001A8F20[] MACRO_ADDR;
extern char D_L08_001B0148[];
extern char D_L08_001B0168[];
extern char D_L08_001B0180[];
extern u8 D_001A7B0D;
extern s32 D_0018B650[];
typedef struct { u8 bytes[0x80]; } TargetCDF98;
extern TargetCDF98 *D_L08_001B2ACC;
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
extern void *D_0018A15C[];

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
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern void moby_update_ground_check(void *);
extern void StepAngleTowardTarget(void *, int, float, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int IsPointInCuboid(void *, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int TryClaimNotice(int, int, int);
extern int flag_set_first_pending(void *);
/* Interleaved: each register bank keeps the order of the definition in 002BDCE8.c. */
extern void *SpawnSpinningSparkParticle(void *, int, void *, float, float, int, int, float, float);
extern void snd_stop_voice(int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void hero_reset_speeds_and_vectors(void);
extern void hero_record_play_counters(void);
extern void set_hero_animation(int, int, float);
extern void script_queue_keyed_request(int, int);
extern int hero_l08_enter_state(int, int);
extern void cam_update_aim_values(void *, void *);
extern void hero_move_with_mount_to_transform(void *, void *);
extern void hero_save_transform_snap_object(void *, void *);
extern void vehicle_update_steering(void *, void *, float);
extern void moby_place_at_stored_transform(void *);
extern int vehicle_handle_collision(void *, void *);

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
#define OH(o) (((u16 *)obj)[(o) / 2])

/* Updates a Glider (moby class 2309): it waits at its pad, lets the hero hop on, launches, then
   steers and glides with the stick, leaves a smoke trail, and lands or lets go at a target. */
void UpdateHeroNpc(u8 *obj)
{
    Vec previousPos;
    union {
        Vec inverse[4];
        struct { Vec velocity, point, joint; } v;
    } scratch;
    u8 *d, *particle;
    int i, jointIndex, checkpointIndex;
    float amount;

    d = *(u8 **)(obj + 0x68);
    qcopy(&previousPos, d);
    if (OH(0x96) < 0x7FFD)
        OH(0x96) = OH(0x96) + 1;
    switch (OB(0x20)) {
    case 0:
        checkpointIndex = DI(0x6C);
        if (checkpointIndex > 0) {
            HeroCDF98 *table = D_L08_001B29DC;
            qcopy(d, table[checkpointIndex].bytes + 0x10);
            qcopy(d + 0x10, table[checkpointIndex].bytes + 0xF0);
            moby_place_at_stored_transform(obj);
        } else {
            STUB_printf(D_L08_001B0148, *(s16 *)(obj + 0xB2));
        }
        DF(8) = DF(8) + D_L08_001AFFD0;
        moby_transform_joint_to_world(obj, 8, d + 0x30);
        FastVecSub(d + 0x30, obj + 0x10, d + 0x30);
        matrix_from_basis_rows(scratch.inverse, obj + 0xC0);
        transform_vector(d + 0x30, d + 0x30, scratch.inverse);
        DF(0x3C) = 1.0f;
        if (OB(0x43) != 0)
            anim_start_blended(obj, 0, 0, 0xA);
        OB(0x30) = 0xFF;
        OB(0x31) = 0;
        *(s16 *)(obj + 0x32) = 0x3FF;
        OH(0x34) = OH(0x34) | 1;
        moby_set_state(obj, 1, -1);
        DI(0x98) = 0;
        DI(0xB0) = 0;
        break;
    case 1:
        if (D_001A7B0D == 0)
            return;
        {
            if (DI(0x6C) < 0) {
                if (fast_vec_dist(d, g_hero_state.pos) < D_L08_001AFFD4 && g_hero_state.unk2294 != 0x31) {
                    if (OB(0x43) != 0)
                        anim_start_blended(obj, 0, 0, 0xA);
                    moby_set_state(obj, 2, -1);
                }
            } else {
                u8 *q = (u8 *)D_0018A15C[0];
                if (q != 0 && *(s16 *)(q + 0xAA) == 0x988 /* Glider Pad */ && q == D_L08_001B29DC[DI(0x6C)].bytes) {
                    if (OB(0x43) != 0)
                        anim_start_blended(obj, 0, 0, 0xA);
                    moby_set_state(obj, 2, -1);
                }
            }
        }
        break;
    case 2: {
        int canGrab;
        hero_save_transform_snap_object(obj, d);
        if (g_hero_state.target == 0 || *(s16 *)(g_hero_state.target + 0xAA) != 0x988 /* Glider Pad */) {
            if (OB(0x43) != 0)
                anim_start_blended(obj, 0, 0, 0xA);
            qcopy(d, D_L08_001B29DC[DI(0x6C)].bytes + 0x10);
            DF(8) = DF(8) + D_L08_001AFFD0;
            moby_set_state(obj, 1, -1);
        }
        canGrab = TryClaimNotice(7, 0x279E, 1) != 0;
        if (OB(0x20) == 2 && (D_00138324[0] & 0x40)) {
            if (canGrab && g_hero_state.target == D_L08_001B29DC[DI(0x6C)].bytes && g_hero_state.unk340 != 0
                && g_hero_state.unk34E == 0) {
                u8 *q;
                hero_l08_enter_state(0x31, 0);
                set_hero_animation(0x87, 0, 3.0f);
                ((s32 *)g_hero_state.unk2290)[0x9C / 4] = -1;
                q = D_L08_001B29DC[DI(0x6C)].bytes;
                vec_scale_to_length(d + 0x20, q + 0xC0, D_L08_001B00FC * 0.016666668f);
                DI(0x50) = D_L08_001B0108;
                DF(0x28) = D_L08_001B0100 * 0.016666668f;
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
                STUB_printf(D_L08_001B0168);
                script_queue_keyed_request(DI(0xBC), DI(0xB8));
            }
            DI(0xB0) = 0x1E;
        } else if (math_fast_float_d(d + 0xB0) != 0) {
            snd_play_from_class_bank(6, 0, obj, 0x988);
            DI(0xB0) = 0xD2;
        }
        if (DI(0x9C) != 0 || g_hero_state.unkC38 > 10.0f) {
            DI(0x9C) = DI(0x9C) | 4;
            StepAngleTowardTarget(d + 0x14, 0, D_L08_001AFFE8 * 0.017453294f, D_L08_001B0134 * 0.00029088825f);
            if (D_L08_001B0140 != 0)
                FastVecAdd(d, d, d + 0x20);
            DF(0x28) = DF(0x28) - D_L08_001B010C * 0.00027777778f;
            if (DF(0x28) < -(D_L08_001B0104 * 0.016666668f))
                DI(0x9C) = DI(0x9C) | 1;
            if (g_hero_state.unkC28 & 2) {
                DI(0x9C) = DI(0x9C) | 2;
                set_hero_animation(0x81, 0, 15.0f);
            }
            if (math_fast_float_d(d + 0x50) != 0) {
                if (DI(0x9C) == 7) {
                    if (OH(0x34) & 1) {
                        OH(0x34) = OH(0x34) & 0xFFFE;
                        OB(0x31) = 1;
                        if (OB(0x43) != 1)
                            anim_start_blended(obj, 1, 0, 5);
                        snd_play_from_class_bank(0, 0, obj, 0x988);
                    }
                    DI(0x50) = D_L08_001AFFDC;
                    hero_l08_enter_state(0x31, 0);
                    set_hero_animation(0x81, 0, 15.0f);
                    ((s32 *)g_hero_state.unk2290)[0x9C / 4] = -1;
                    if (D_L08_001B0140 != 0)
                        DF(0x14) = D_L08_001AFFE8 * 0.017453294f;
                    DF(0x54) = 0.060000002f;
                    qzero_nc(d + 0x20);
                    DI(0xA8) = 0;
                    DF(0x58) = DF(8);
                    cam_update_aim_values(d + 0xA8, obj);
                    DF(0x64) = 0.0f;
                    D_L08_001B3410 = D_L08_001B2094;
                    D_L08_001B3414 = D_L08_001B2098;
                    D_L08_001B2094 = D_L08_001B00A4;
                    D_L08_001B2098 = D_L08_001B00A8;
                    g_hero_state.unk1830 = obj;
                    moby_set_state(obj, 5, -1);
                }
            }
            hero_move_with_mount_to_transform(obj, d);
            DI(0xB4) = 0;
        } else {
            DI(0xB4) = 0;
        }
        break;
    }
    case 4:
        if (D_L08_001AFFD8 < vec_distance_xy(obj + 0x10, g_hero_state.pos)) {
            if (OB(0x43) != 0)
                anim_start_blended(obj, 0, 0, 0xA);
            moby_set_state(obj, 1, -1);
        }
        break;
    case 5: {
        {
            VoiceSlotCDF98 *slot = (VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70);
            if (slot->voice.owner != obj || slot->voice.active == 0)
                DI(0xAC) = snd_play_from_class_bank(1, 4, obj, 0x988);
        }
        cam_update_aim_values(d + 0xA8, obj);
        DF(0x28) = -math_fast_sin_or_cos_b(DF(0x14)) * DF(0x54);
        {
            float c = DF(0x54) * math_fast_sin_or_cos_a(DF(0x14));
            DF(0x20) = c * math_fast_sin_or_cos_a(DF(0x18));
            DF(0x24) = c * math_fast_sin_or_cos_b(DF(0x18));
        }
        if (D_L08_001AFFE0 >= DI(0x50)) {
            if (OH(0x34) & 1) {
                OH(0x34) = OH(0x34) & 0xFFFE;
                OB(0x31) = 1;
                if (OB(0x43) != 1)
                    anim_start_blended(obj, 1, 0, 0xA);
            }
            {
                float r = IntToFloat(D_L08_001AFFE0 - DI(0x50)) / IntToFloat(D_L08_001AFFE0);
                DF(0x64) = r;
                if (r > 1.0f)
                    DF(0x64) = 1.0f;
                else if (r < 0.0f)
                    DF(0x64) = 0.0f;
            }
            vehicle_update_steering(obj, d, DF(0x64));
            FastVecScale(d + 0x20, d + 0x20, 1.0f - DF(0x64));
            vec_build_spherical_offset(&scratch.v.velocity, DF(0x54), DF(0x18), -DF(0x14));
            FastVecScale(&scratch.v.velocity, &scratch.v.velocity, DF(0x64));
            FastVecAdd(d + 0x20, d + 0x20, &scratch.v.velocity);
        }
        if (D_L08_001B0140 != 0)
            FastVecAdd(d, d, d + 0x20);
        if (vehicle_handle_collision(obj, &previousPos) == 0) {
            float newSpeed = DF(0x54) + D_L08_001AFFFC * 0.00027777778f;
            float maxSpeed = D_L08_001AFFF8 * 0.016666668f;
            float turnRate;
            DF(0x54) = newSpeed;
            if (maxSpeed < newSpeed)
                DF(0x54) = maxSpeed;
            turnRate = D_L08_001B0000 * 0.00029088825f;
            if (DI(0x50) < D_L08_001AFFDC - D_L08_001AFFE4 && D_L08_001B0140 != 0)
                DF(0x14) = fast_subtract_rotations(DF(0x14), turnRate);
            if (DF(0x14) < 0.0f)
                DF(0x14) = 0.0f;
            if (math_fast_float_d(d + 0x50) != 0) {
                if (OB(0x43) != 2)
                    anim_start_blended(obj, 2, 0, 0xA);
                set_hero_animation(0x82, 0, 15.0f);
                DF(0x40) = 0.0f;
                DF(0x48) = 0.0f;
                DF(0x44) = -(D_L08_001B0000 * 0.00029088825f);
                moby_set_state(obj, 6, -1);
            }
        }
        if ((OB(0x60) & 2) && OB(0x43) != 2)
            anim_start_blended(obj, 2, 0, 0xA);
        hero_move_with_mount_to_transform(obj, d);
        break;
    }
    case 6: {
        float amount;
        cam_update_aim_values(d + 0xA8, obj);
        {
            VoiceSlotCDF98 *slot = (VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70);
            if (slot->voice.owner != obj || slot->voice.active == 0)
                DI(0xAC) = snd_play_from_class_bank(1, 4, obj, 0x988);
        }
        vehicle_update_steering(obj, d, 1.0f);
        amount = DF(0x5C);
        if (amount < -0.4f) {
            if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x85 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x85) {
                set_hero_animation(0x85, 0, 15.0f);
                snd_play_from_class_bank(2, 0, obj, 0x988);
            }
        } else if (amount > 0.4f) {
            if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x86 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x86) {
                set_hero_animation(0x86, 0, 15.0f);
                snd_play_from_class_bank(2, 0, obj, 0x988);
            }
        } else {
            if (D_L08_001B0070 * 0.000041555468f < DF(0x44)) {
                if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x83 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x83)
                    set_hero_animation(0x83, 0, 25.0f);
            } else if (DF(0x44) < -D_L08_001B0070 * 0.000041555468f) {
                if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x81 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x81) {
                    set_hero_animation(0x81, 0, 25.0f);
                    if (DI(0xB0) == 0) {
                        snd_play_from_class_bank(3, 0, obj, 0x988);
                        DI(0xB0) = 0x2D;
                    }
                }
            } else if (*(u8 *)(g_hero_state.unk2290 + 0x42) != 0x82 && *(u8 *)(g_hero_state.unk2290 + 0x43) != 0x82) {
                set_hero_animation(0x82, 0, 20.0f);
            }
        }
        {
            float a = DF(8), b = DF(0x58), c = D_L08_001B0014;
            if (a - b <= c) {
                if (DI(0x98) == 0) {
                    float s = DF(0x54);
                    DF(0x54) = s + (((D_L08_001B0018 * 0.016666668f) - s) * 0.1f);
                }
            } else {
                float e = D_L08_001B000C;
                float k = b - a;
                float lo, newSpeed, maxSpeed;
                k += e;
                k /= e - c;
                if (k > 1.0f)
                    k = 1.0f;
                else if (k < 0.0f)
                    k = 0.0f;
                lo = D_L08_001B0018 * 0.016666668f;
                k = 1.0f - k;
                newSpeed = lo + (k * ((D_L08_001B0010 * 0.016666668f) - lo));
                if (DI(0x98) == 0 || newSpeed < DF(0x54))
                    DF(0x54) = DF(0x54) + ((newSpeed - DF(0x54)) * 0.1f);
                maxSpeed = D_L08_001B0018 * 0.016666668f;
                if (maxSpeed < DF(0x54))
                    DF(0x54) = maxSpeed;
            }
        }
        if (DF(0x64) < 1.0f) {
            float w = DF(0x64) + D_L08_001B00A0;
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
        if (D_L08_001B0140 != 0)
            FastVecAdd(d, d, d + 0x20);
        D_L08_001B99C0.f[0x3C8 / 4] = D_L08_001B99C0.f[0x3C8 / 4]
            + (((DF(0x28) * D_L08_001B007C) - D_L08_001B99C0.f[0x3C8 / 4]) * 0.5f);
        if (D_L08_001B000C < DF(8) - DF(0x58)) {
            float ang, lim;
            if (OB(0x43) != 2)
                anim_start_blended(obj, 2, 0, 3);
            set_hero_animation(0x84, 0, 15.0f);
            ang = DF(0x14);
            lim = D_L08_001B008C * 0.017453294f;
            DI(0x60) = 0;
            DI(0x50) = D_L08_001B0084;
            if (lim < ang)
                DF(0x68) = fast_subtract_rotations(lim, ang) / IntToFloat(D_L08_001B0084);
            else
                DF(0x68) = 0.0f;
            moby_set_state(obj, 7, -1);
        }
        hero_move_with_mount_to_transform(obj, d);
        vehicle_handle_collision(obj, &previousPos);
        if (g_hero_state.unk2294 != 0x31)
            moby_set_state(obj, 1, -1);
        break;
    }
    case 7: {
        cam_update_aim_values(d + 0xA8, obj);
        if (math_fast_float_d(d + 0x50) != 0) {
            DI(0x50) = D_L08_001B0090;
            moby_set_state(obj, 8, -1);
        }
        DF(0x28) = DF(0x28) + (-D_L08_001B0088 * 0.00027777778f);
        FastVecAdd(d, d, d + 0x20);
        DF(0x54) = FastVecLength(d + 0x20);
        amount = IntToFloat(DI(0x50)) / IntToFloat(D_L08_001B0084);
        if (amount > 1.0f)
            amount = 1.0f;
        else if (amount < 0.0f)
            amount = 0.0f;
        if (D_L08_001B0140 != 0)
            DF(0x14) = FastAddRotations(DF(0x14), DF(0x68));
        vehicle_update_steering(obj, d, 1.0f);
        vehicle_handle_collision(obj, &previousPos);
        hero_move_with_mount_to_transform(obj, d);
        break;
    }
    case 8: {
        cam_update_aim_values(d + 0xA8, obj);
        if (D_L08_001B0094 * 0.017453294f < DF(0x14) && DF(8) - DF(0x58) < D_L08_001B000C) {
            set_hero_animation(0x82, 0, 15.0f);
            if (OB(0x43) != 2)
                anim_start_blended(obj, 2, 0, 0xA);
            DF(0x64) = 0.0f;
            moby_set_state(obj, 6, -1);
        } else {
            math_fast_float_d(d + 0x50);
        }
        DF(0x28) = DF(0x28) + (-D_L08_001B0088 * 0.00027777778f);
        if (D_L08_001B0140 != 0)
            FastVecAdd(d, d, d + 0x20);
        DF(0x54) = FastVecLength(d + 0x20);
        vehicle_update_steering(obj, d, 1.0f);
        hero_move_with_mount_to_transform(obj, d);
        vehicle_handle_collision(obj, &previousPos);
        break;
    }
    case 9: {
        cam_update_aim_values(d + 0xA8, obj);
        if (flag_set_first_pending(obj) != 0) {
            if (DI(0xAC) != -1) {
                if (((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.owner == obj
                    && ((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.active != 0)
                    snd_stop_voice(DI(0xAC));
            }
            DI(0xAC) = -1;
            snd_play_from_class_bank(4, 0, obj, 0x988);
            DI(0xB0) = 0xF;
        }
        if (D_L08_001B0140 != 0)
            DF(0x18) = FastAddRotations(DF(0x18), D_L08_001B0098 * 0.00029088825f);
        DF(0x28) = DF(0x28) + (-D_L08_001B009C * 0.00027777778f);
        if (D_L08_001B0140 != 0)
            FastVecAdd(d, d, d + 0x20);
        hero_move_with_mount_to_transform(obj, d);
        vehicle_handle_collision(obj, &previousPos);
        if (DF(0x28) > 0.0f || DF(8) < 12.0f || FastVecLength(d + 0x20) < 0.016666668f
            || D_L08_001B0130 < (s32)OH(0x96)) {
            SpawnExplosionEffects(obj, D_L08_001A8F20, 0, 0.0f, 0.0f, 0xA, 3, 0x10, 4.0f, 2.0f, 9.0f, 1.0f,
                          -1, 15.0f, 1, 1, -1, 0, 0x810001);
            D_0018B650[0] = 0;
            hero_record_play_counters();
        }
        break;
    }
    case 10: {
        float distToTarget, lim;
        if (DI(0xAC) != -1) {
            if (((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.owner == obj
                    && ((VoiceSlotCDF98 *)(g_sound_state + DI(0xAC) * 0x70))->voice.active != 0)
                snd_stop_voice(DI(0xAC));
        }
        DI(0xAC) = -1;
        distToTarget = fast_vec_dist(d, d + 0x80);
        lim = DF(0x94) < distToTarget ? DF(0x94) : distToTarget;
        if (D_L08_001B0140 != 0) {
            StepAngleTowardTarget(d + 0x14, 0, 0.0f, D_L08_001B0138 * 0.00029088825f);
            StepAngleTowardTarget(d + 0x10, 0, 0.0f, D_L08_001B0138 * 0.00029088825f);
        }
        if ((OB(0x60) & 2) && OB(0x42) == 3) {
            if (OB(0x43) != 0)
                anim_start_blended(obj, 0, 0, 0xA);
            OB(0x31) = 0;
            OH(0x34) = OH(0x34) | 1;
        }
        if (lim < distToTarget) {
            FastVecSub(&scratch.v.velocity, d + 0x80, d);
            vec_scale_to_length(&scratch.v.velocity, &scratch.v.velocity, lim * D_L08_001B0128);
            FastVecScale(d + 0x20, d + 0x20, D_L08_001B0124);
            FastVecAdd(d + 0x20, d + 0x20, &scratch.v.velocity);
            if (D_L08_001B0140 != 0)
                FastVecAdd(d, d, d + 0x20);
            hero_move_with_mount_to_transform(obj, d);
            break;
        }
        qcopy(d, d + 0x80);
        DF(0x94) = 0.0f;
        if (g_hero_state.unkC28 & 2) {
            g_hero_state.unk1830 = 0;
            D_L08_001B2094 = D_L08_001B3410;
            D_L08_001B2098 = D_L08_001B3414;
            DI(0x50) = 0;
            hero_l08_enter_state(0, 1);
            hero_reset_speeds_and_vectors();
            if (OB(0x43) != 0)
                anim_start_blended(obj, 0, 0, 0xA);
            if (DI(0x6C) > 0) {
                qcopy(d, D_L08_001B29DC[DI(0x6C)].bytes + 0x10);
                moby_place_at_stored_transform(obj);
            }
            if (DI(0xC4) != -1) {
                STUB_printf(D_L08_001B0180);
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
                if (fast_vec_dist(obj + 0x10, D_L08_001B9B00) < 80.0f) {
                    moby_update_ground_check(obj);
                    OB(0x6F) = 0x4B;
                }
            }
            FastVecScale(&scratch.v.velocity, d + 0x20, 0.25f);
            for (jointIndex = 0; jointIndex < 7; jointIndex++) {
                moby_transform_joint_to_world(obj, jointIndex, &scratch.v.joint);
                for (f = 0.0f; f < 1.0f; f += 0.2f) {
                    FastVecScale(&scratch.v.point, d + 0x20, -f);
                    FastVecAdd(&scratch.v.point, &scratch.v.point, &scratch.v.joint);
                    amount = 0.0f;
                    if (OB(0x20) >= 7)
                        amount = 0.07f;
                    particle = SpawnSpinningSparkParticle(&scratch.v.point, 2, &scratch.v.velocity, amount, 0.5f, 0x0E7F7F7F, 0, 1.01f,
                                      math_random_float_range(24000.0f, 35000.0f));
                    if (particle != 0)
                        particle[8] = func_001163B0();
                }
            }
            slot = (s32 *)(d + 0x70);
            for (i = 0; i < 4; i++) {
                if (slot[i] != 0xFF && IsPointInCuboid(d, slot[i]) != 0
                    && *(float *)(D_L08_001B2ACC[slot[i]].bytes + 0x38) < g_hero_state.pos[2]) {
                    if (OB(0x43) != 3)
                        anim_start_blended(obj, 3, 0, 3);
                    set_hero_animation(0x88, 0, 15.0f);
                    qcopy(d + 0x80, D_L08_001B2ACC[slot[i]].bytes + 0x30);
                    DF(0x90) = fast_vec_dist(g_hero_state.pos, d + 0x80);
                    {
                        float m = FastVecLength(d + 0x20) > 0.06666667f ? FastVecLength(d + 0x20) : 0.06666667f;
                        DF(0x94) = m;
                    }
                    g_hero_state.unkC20 = D_L08_001B013C / (DF(0x90) / DF(0x94));
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
