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
    u8 *pClass;               /* 0x24 */
    u8 pad28[4];
    float f2c;                /* 0x2c */
    u8 pad30;
    u8 drawn;                 /* 0x31 */
    u8 pad32[2];
    u16 modeBits;             /* 0x34 */
    u8 pad36[0x0c];
    u8 seqA;                  /* 0x42 */
    u8 seqB;                  /* 0x43 */
    u8 pad44[0x1c];
    u8 f60;                   /* 0x60 */
    u8 pad61[7];
    VehicleVars *pVars;       /* 0x68 */
    u8 pad6c[3];
    u8 f6f;                   /* 0x6f */
    u8 pad70[0x28];
    s32 collData;             /* 0x98 */
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
    float bobPhase;           /* 0x48 */
    float bobOffset;          /* 0x4c */
    float sway[2];            /* 0x50 */
    float lastZ;              /* 0x58 */
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
    u8 hitCooldown;           /* 0x8b */
    s16 f8c;                  /* 0x8c */
    u8 pad8e[2];
    u8 flash[7];              /* 0x90 */
    u8 flashRGB[3];           /* 0x97 */
    u8 pad9a[6];
    u8 *lastHit;              /* 0xa0 */
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
    float cameraPosition[4];
    u8 pad2E0[0x33c - 0x2e0];
    u8 *attachment;
    s32 available;
    u8 pad344[0x1830 - 0x344];
    VehicleMoby *vehicle;
    u8 pad1834[8];
    float health;
    float maxHealth;
    u8 pad1844[4];
    s32 healthBar;
    u8 pad184C[0x2290 - 0x184c];
    VehicleMoby *moby;
    s32 animationState;
    u8 pad2298[4];
    s32 movementState;
    u8 pad22A0[0x22b5 - 0x22a0];
    u8 vehicleControl;
    u8 pad22B6[0x24cc - 0x22b6];
    s32 healthAvailable;
} VehiclePlayerState;
extern VehiclePlayerState D_00189E20_14;
extern s32 D_L08_001A8F00;
extern float D_L08_001B19B4 __attribute__((sda));
extern s32 D_L08_001B1B64 __attribute__((sda));
extern s32 vec_fast_helper_a(u8 *);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void func_PAL_002AC290(u8 *, u8 *);
extern void func_PAL_002AC3C0(u8 *, u8 *);
extern void moby_set_group_flags(s32, s32, s32, s32);

extern float D_L08_001B18D0 __attribute__((sda));
extern float D_L08_001B18D8 __attribute__((sda));
extern float D_L08_001B18E0 __attribute__((sda));
extern float D_L08_001B18E4 __attribute__((sda));
extern float D_L08_001B18E8 __attribute__((sda));
extern float D_L08_001B18EC __attribute__((sda));
extern float D_L08_001B18F0 __attribute__((sda));
extern float D_L08_001B18F4 __attribute__((sda));
extern float D_L08_001B18F8 __attribute__((sda));
extern float D_L08_001B18FC __attribute__((sda));
extern float D_L08_001B1900 __attribute__((sda));
extern float D_L08_001B1904 __attribute__((sda));
extern float D_L08_001B1908 __attribute__((sda));
extern float D_L08_001B190C __attribute__((sda));
extern float D_L08_001B1910 __attribute__((sda));
extern float D_L08_001B1914 __attribute__((sda));
extern s32 D_L08_001B1918 __attribute__((sda));
extern s32 D_L08_001B191C __attribute__((sda));
extern float D_L08_001B1920 __attribute__((sda));
extern float D_L08_001B1924 __attribute__((sda));
extern float D_L08_001B1928 __attribute__((sda));
extern float D_L08_001B192C __attribute__((sda));
extern float D_L08_001B1930 __attribute__((sda));
extern float D_L08_001B1934 __attribute__((sda));
extern float D_L08_001B1938 __attribute__((sda));
extern float D_L08_001B193C __attribute__((sda));
extern float D_L08_001B1940 __attribute__((sda));
extern float D_L08_001B1948 __attribute__((sda));
extern float D_L08_001B194C __attribute__((sda));
extern float D_L08_001B1950 __attribute__((sda));
extern float D_L08_001B1954 __attribute__((sda));
extern float D_L08_001B1958 __attribute__((sda));
extern float D_L08_001B19B8 __attribute__((sda));
extern float D_L08_001B19BC __attribute__((sda));
extern float D_L08_001B19C0 __attribute__((sda));
extern float D_L08_001B19C4 __attribute__((sda));
extern float D_L08_001B19C8 __attribute__((sda));
extern float D_L08_001B19CC __attribute__((sda));
extern float D_L08_001B19D0 __attribute__((sda));
extern float D_L08_001B19D4 __attribute__((sda));
extern float D_L08_001B19D8 __attribute__((sda));
extern float D_L08_001B19E4 __attribute__((sda));
extern float D_L08_001B1A14 __attribute__((sda));
extern float D_L08_001B1A18 __attribute__((sda));
extern float D_L08_001B1A1C __attribute__((sda));
extern float D_L08_001B1A20 __attribute__((sda));
extern float D_L08_001B1A24 __attribute__((sda));
extern float D_L08_001B1A28 __attribute__((sda));
extern float D_L08_001B1A30 __attribute__((sda));
extern s32 D_L08_001B1A44 __attribute__((sda));
extern s32 D_L08_001B1A48 __attribute__((sda));
extern s32 D_L08_001B1A78 __attribute__((sda));
extern float D_L08_001B1B1C __attribute__((sda));
extern float D_L08_001B1B20 __attribute__((sda));
extern float D_L08_001B1B24 __attribute__((sda));
extern s32 D_L08_001B1B28 __attribute__((sda));
extern float D_L08_001B1B2C __attribute__((sda));
extern float D_L08_001B1B30 __attribute__((sda));
extern float D_L08_001B1B34 __attribute__((sda));
extern float D_L08_001B1B38 __attribute__((sda));
extern float D_L08_001B1B3C __attribute__((sda));
extern s32 D_L08_001B1B40 __attribute__((sda));
extern float D_L08_001B1B44 __attribute__((sda));
extern float D_L08_001B1B48 __attribute__((sda));
extern float D_L08_001B1B4C __attribute__((sda));
extern float D_L08_001B1B50 __attribute__((sda));
extern float D_L08_001B1B54 __attribute__((sda));
extern s32 D_L08_001B1B58 __attribute__((sda));
extern float D_L08_001B1B5C __attribute__((sda));
extern float D_L08_001B1B60 __attribute__((sda));
extern float D_L08_001B1B7C __attribute__((sda));
extern float D_L08_001B1B80 __attribute__((sda));
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
extern CollisionResult D_L08_001BFF40;
typedef struct {
    u8 pad000[0x160];
    float amount;
    u8 pad164[4];
    s32 timer;
    s32 phase;
} ShakeState;
extern ShakeState D_L08_001B99C0;
extern u8 D_L08_001B9B00[];
extern float D_L08_001B031C[] __attribute__((sda));
extern void ref_L08_0041EBF8_00(void);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void AttachManipulator(void *, s32, void *);
extern float func_002A0558(void *, void *);
extern s32 TryClaimNotice(s32, s32, s32);
extern s32 func_PAL_L08_0031ACF8(s32, void *, s32);
extern void script_queue_keyed_request(s32, s32);
extern s32 func_PAL_L08_002D3078(s32, s32);
extern void func_PAL_L00_002D2668(s32, s32, float);
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
extern void func_PAL_L08_004239F0(void *, void *, s32, float, float, float, float, float, float);
extern void make_hit_descriptor(void *, void *, s32, void *, float);
extern int coll_process_hit(void *, s32, void *, void *, float);
extern void func_PAL_L08_00423D30(void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, s32, s32, s32, float, float, float, float,
                          s32, float, s32, s32, s32, s32, s32);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float IntToFloat(s32);
extern s32 FloatToInt(float);
extern void *part_spawn_attached_effect(void *, void *);
extern void moby_store_position_private(void *, void *);
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern s32 func_PAL_L08_0033B2D0(void *, s32, s32, void *, float, float);
extern int snd_fade_looping_by_distance(void *, void *, s32, s32, float);
extern int math_fast_float_d(void *);
/* An effect record (0x70 bytes) still owned by this moby and active. */
#define EFFECT(i) ((EffectSlot *)(D_00188660 + (i) * 0x70))
#define EFFECT_LIVE(i) (EFFECT(i)->owner == moby && EFFECT(i)->active)

/* Update the rideable hovering vehicle and its player-control state. */
void func_PAL_L08_00423EA0(VehicleMoby *moby)
{
    VehicleVars *p = moby->pVars;
    s32 fresh;
    float inputTurn, inputThrottle, inputPitch, inputBrake, inputStrafe;
    /* basis: the ground-aligned matrix (rows x, y, normal, zero translation); its rows
     * are reused below as the probe point, its offset and the contact normal. */
    float forward[4], thrust[4], nextPos[4], basis[4][4], angles[4], scratch[16];

    if (D_L08_001A8F00 == 2 || D_00189E20_14.animationState == 97) {
        moby->drawn = 0;
        moby->modeBits |= 1;
        return;
    }
    moby->drawn = 1;
    moby->modeBits &= 0xfffe;
    if (vec_fast_helper_a(&p->hitCooldown))
        p->lastHit = 0;
    if (moby->state) {
        u8 *hit, *target;
        moby->pos[2] = p->lastZ;
        hit = part_find_owned_effect_slot(moby, 1, 0);
        if (hit && (target = *(u8 **)(hit + 0x20))) {
            s32 kind = *(s16 *)(target + 0xaa);
            if (kind != 0xeef && kind != 0x942 && kind != 0xfff &&
                (target != p->lastHit || !p->hitCooldown)) {
                p->flashRGB[0] = 0xd2;
                p->flashRGB[1] = 0xd2;
                p->flashRGB[2] = 0xd2;
                func_PAL_002AC290(moby, p->flash);
                p->health -= *(float *)(hit + 0x2c);
                D_00189E20_14.health = p->health;
                if (p->health <= 0.0f)
                    moby->state = 5;
                p->lastHit = *(u8 **)(hit + 0x20);
                p->hitCooldown = (D_L08_001B1B64 * 5 + 2) / 6;
            }
        }
        moby->impact = 0xff;
    } else {
        p->lastZ = moby->pos[2];
    }
    func_PAL_002AC3C0(moby, p->flash);
    moby->f2c = *(float *)(moby->pClass + 0x24) * D_L08_001B19B4;
    if (D_00189E20_14.vehicle == moby && moby->state)
        D_00189E20_14.healthBar = (s32)(D_00189E20_14.health / D_00189E20_14.maxHealth * 200.0f);
    else
        D_00189E20_14.healthBar = 200;
    fresh = 0;
    if (p->sound != -1)
        moby_set_group_flags(p->sound, -1, -1, 1);
    switch (moby->state) {
    case 0:
        if (moby->seqB)
            func_PAL_002A7E68(moby, 0, 0, 10);
        if (!p->rotor[0].hdr[1]) {
            s32 j;
            for (j = 0; j < 3; j++)
                AttachManipulator(moby, j + 2, &p->rotor[j]);
        }
        p->fa4 = 0;
        p->fa8 = 255;
        qcopy(p->home, moby->pos);
        qzero(p->vel);
        switch (g_current_map_index) {
        case 8:
            D_00189E20_14.maxHealth = D_L08_001B19D4;
            break;
        case 19:
            D_00189E20_14.maxHealth = D_L08_001B19D8;
            break;
        default:
            D_00189E20_14.maxHealth = D_L08_001B19D0;
            break;
        }
        p->health = D_00189E20_14.maxHealth;
        D_00189E20_14.health = p->health;
        p->f74 = 0;
        moby->state = 1;
        p->fx1a4 = -1;
        p->power = 0.0f;
        p->fx1ac = 0;
        p->fx1b0 = 0;
        break;
    case 1:
        if (D_00189E20_14.animationState != 28 && D_00189E20_14.animationState != 22 &&
            D_00189E20_14.animationState != 57 && D_00189E20_14.animationState != 111 &&
            D_00189E20_14.movementState != 2 && D_00189E20_14.movementState != 4 &&
            D_00189E20_14.movementState != 3 && D_00189E20_14.movementState < 13 &&
            D_00189E20_14.movementState != 7 && D_00189E20_14.movementState != 10 &&
            D_00189E20_14.movementState != 16 && D_00189E20_14.movementState != 5 &&
            D_00189E20_14.animationState != 98 && D_00189E20_14.healthAvailable > 0 &&
            D_L08_001A8F00 == 0 && D_00189E20_14.available &&
            (!D_00189E20_14.attachment || (*(s16 *)(D_00189E20_14.attachment + 0xaa) != 0x13e &&
                                    *(s16 *)(D_00189E20_14.attachment + 0xaa) != 0x46f)) &&
            func_002A0558(moby, D_00189E20_14.moby) < D_L08_001B18E0 &&
            D_00189E20_14.animationState != 49) {
            s32 ready = TryClaimNotice(7, 0x12ea, 1) != 0;
            if ((g_pad_state[0x69] & 16) && ready) {
                p->f190 = 0;
                fresh = 1;
                func_PAL_L08_0031ACF8(0, ref_L08_0041EBF8_00, 1);
                script_queue_keyed_request(p->f194, p->f19c);
                func_PAL_L08_002D3078(49, 0);
                func_PAL_L00_002D2668(D_L08_001B1918, 0, 15.0f);
                qcopy(D_00189E20_14.rotation, moby->rot);
                qcopy(D_00189E20_14.position, moby->pos);
                D_00189E20_14.vehicle = moby;
                moby->state = 3;
                if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                    snd_stop_voice(p->fx1b4);
                p->fx1b4 = -1;
                D_00189E20_14.moby->f9c = -1;
                D_00189E20_14.vehicleControl = 1;
            }
        }
        if (!EFFECT_LIVE(p->fx1b4))
            p->fx1b4 = snd_play_from_class_bank(9, 4, moby, 0x85c);
        /* Activation continues through the control/movement path this frame. */
    case 3:
        moby->collData = 0;
        FastDecTimer(&p->timer7c);
        inputStrafe = inputBrake = inputPitch = inputThrottle = inputTurn = 0.0f;
        if (moby->state == 3) {
            D_00189E20_14.vehicleControl = 1;
            if (g_pad_state[0x68] & 0x80) {
                if ((moby->seqA < 1 || moby->seqA > 3) && moby->seqB != 1 && moby->seqB != 2 &&
                    moby->seqB != 3) {
                    if (moby->seqB != 1)
                        func_PAL_002A7E68(moby, 1, 0, 10);
                } else if (moby->f60 & 2) {
                    if (moby->seqA == 1) {
                        if (moby->seqB != 2)
                            func_PAL_002A7E68(moby, 2, 0, 10);
                    } else if (moby->seqB == 3 || moby->seqB == 0) {
                        if (moby->seqB != 1)
                            func_PAL_002A7E68(moby, 1, 0, 10);
                    }
                }
                p->power -= D_L08_001B1A14 * 1.2f;
                if (!math_random_int_below(9) || (g_pad_state[0x69] & 0x80))
                    moby_mark_in_range(moby);
            } else {
                if (moby->f60 & 2) {
                    if ((moby->seqA >= 1 && moby->seqA <= 2) ||
                        moby->seqB == 1 || moby->seqB == 2) {
                        if (moby->seqB != 3)
                            func_PAL_002A7E68(moby, 3, 0, 10);
                    } else if (moby->seqB) {
                        func_PAL_002A7E68(moby, 0, 0, 10);
                    }
                }
                p->power += D_L08_001B1A18 * 1.2f;
            }
            if (D_L08_001B191C != D_L08_001B1918 && D_L08_001B1918 != -1)
                func_PAL_L00_002D2668(D_L08_001B1918, 0, 15.0f);
            vehicle_read_controls(&inputTurn, &inputThrottle, &inputPitch, &inputBrake, &inputStrafe);
            inputTurn *= p->power;
        } else {
            p->power -= D_L08_001B1A14 * 1.2f;
            if (moby->f60 & 2) {
                if ((moby->seqA >= 1 && moby->seqA <= 2) ||
                    moby->seqB == 1 || moby->seqB == 2) {
                    if (moby->seqB != 3)
                        func_PAL_002A7E68(moby, 3, 0, 2);
                } else if (moby->seqB) {
                    func_PAL_002A7E68(moby, 0, 0, 2);
                }
            }
        }
        if (p->power > 1.0f)
            p->power = 1.0f;
        else if (p->power < 0.0f)
            p->power = 0.0f;
        {
            float sign = 1.0f;
            float hoverHeight, rate, speed, speedMax, steer, turn, turnRad, bank;
            float turnFactor, damping, push, acceleration, spin, strength, height;
            float *angle, *rates;
            s32 special, grounded, collision;

            inputThrottle *= p->power;
            inputBrake += 1.0f - p->power;
            inputStrafe *= p->power;
            hoverHeight = D_L08_001B190C * p->power + D_L08_001B1A1C * (1.0f - p->power);
            if (moby->state == 3)
                hoverHeight = D_L08_001B190C * p->power + D_L08_001B1A20 * (1.0f - p->power);
            p->throttle = inputThrottle;
            inputPitch *= 0.017453294f;
            inputPitch *= D_L08_001B1948;
            speed = FastVecLength(p) * p->power;
            speedMax = D_L08_001B1908 * 0.020000001f;
            rate = D_L08_001B1950 * 0.020000001f;
            steer = (speed < rate ? speed : rate) / rate * D_L08_001B194C + (1.0f - D_L08_001B194C) +
                    D_L08_001B1A24 * (1.0f - p->power);
            turn = inputTurn * steer * 0.0003490659f;
            p->yaw = FastAddRotations(p->yaw, D_L08_001B18F8 * turn);
            turnRad = inputTurn * 0.017453294f;
            bank = D_L08_001B1930 * turnRad;
            bank *= p->power;
            bank *= D_L08_001B193C * inputThrottle + (1.0f - D_L08_001B193C);
            bank -= moby->rot[0];
            bank *= D_L08_001B192C;
            p->roll += bank;
            forward[0] = math_fast_sin_or_cos_a(p->yaw);
            forward[1] = math_fast_sin_or_cos_b(p->yaw);
            forward[2] = 0.0f;
            if (inputThrottle < 0.0f)
                inputThrottle *= D_L08_001B1934;
            if (inputThrottle < 0.0f)
                sign = -1.0f;
            turnFactor = math_fabs(inputTurn), damping = IntegerPower(2, (speedMax - speed) / speedMax);
            push = inputThrottle + D_L08_001B1938 * turnFactor * sign;
            push *= 0.00040000002f;
            push *= D_L08_001B1904;
            acceleration = push * damping;
            spin = p->power * 0.0003490659f;
            p->rate[0] = spin * D_L08_001B18D0;
            strength = D_L08_001B18D8 * 0.0003490659f;
            rates = p->rate;
            angle = p->angle;
            {
                s32 k;
                for (k = 1; k < 3; k++) {
                    float t = speed / speedMax + inputThrottle;
                    float x;
                    if (!(k & 1))
                        x = t - inputTurn;
                    else
                        x = t + inputTurn;
                    x = x * strength * 0.5f;
                    if (k & 1)
                        x = -x;
                    p->rate[k] = x;
                }
            }
            {
                s32 k;
                for (k = 0; k < 3; k++) {
                    angle[k] = FastAddRotations(angle[k], rates[k]);
                    build_axis_rotation_quaternion(p->rotor[k].mtx, k == 0 ? 2 : 0, angle[k]);
                }
            }
            FastVecAdd(nextPos, moby->pos, p->vel);
            height = coll_probe_ground_height_below(nextPos, 0, 0.5f);
            special = 0;
            if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 11)
                special = 1;
            if (moby->pos[2] < height + hoverHeight + 0.3f && special)
                moby->state = 5;
            grounded = 1;
            p->vel[2] -= D_L08_001B1920 * 0.00040000002f;
            if (height != 0.0f) {
                vec_scale_to_length(basis[2], D_L08_001BFF40.normal, 1.0f);
                FastVecCross(basis[1], moby->mtx, basis[2]);
                FastVecCross(basis[0], basis[1], basis[2]);
                qzero_nc(basis[3]);
                mat_get_euler_angles(basis, angles);
                {
                    float tilt = inputPitch * 0.5f;
                    p->pitch = FastAddRotations(p->pitch,
                        fast_subtract_rotations(FastAddRotations(-angles[1], tilt * (D_L08_001B1A28 * (p->power + 1.0f))),
                                      p->pitch) * D_L08_001B1940);
                }
                if (nextPos[2] < height + hoverHeight + 0.2f) {
                    grounded = 0;
                    if (nextPos[2] + 0.1f < height || special) {
                        nextPos[2] = height;
                        FastVecScale(p, p, D_L08_001B1928);
                    }
                    p->vel[2] += ((height + hoverHeight - nextPos[2]) * D_L08_001B1910 - p->vel[2]) *
                                 D_L08_001B1910;
                    if (inputBrake > 0.0f) {
                        float brake = 1.0f - D_L08_001B1954 * inputBrake;
                        p->vel[0] *= brake;
                        p->vel[1] *= brake;
                    }
                    FastVecScale(p, p, D_L08_001B18FC);
                    matrix_from_basis_rows(scratch, moby->mtx);
                    transform_vector(p, p, scratch);
                    p->vel[1] *= D_L08_001B1900;
                    matrix_mul_vec3(p, p, moby->mtx);
                }
                vec_scale_to_length(thrust, moby->mtx, acceleration);
                if (p->pitch < -0.78539824f) {
                    if (thrust[2] > 0.0f)
                        thrust[2] = 0.0f;
                    vec_scale_to_length(thrust, thrust, acceleration);
                } else {
                    float climb = D_L08_001B1920 * 0.000100000005f;
                    if (thrust[2] > climb)
                        thrust[2] = climb;
                    vec_scale_to_length(thrust, thrust, acceleration);
                }
                {
                    float side = inputStrafe * 0.00040000002f;
                    vec_scale_to_length(scratch, moby->mtx[1], D_L08_001B1A30 * side * p->power);
                }
                FastVecAdd(thrust, thrust, scratch);
                FastVecAdd(p, p, thrust);
            }
            qcopy(moby->pos, nextPos);
            moby_transform_joint_to_world(moby, 0, basis[0]);
            basis[0][2] += D_L08_001B1914 - D_L08_001B1A1C;
            FastVecSub(basis[1], moby->pos, basis[0]);
            moby->collData = 0;
            collision = coll_process_triangles(basis[0], D_L08_001B1914);
            if (!collision) {
                if (g_current_map_index == 19) {
                    s32 saved = D_00189E20_14.moby->collData;
                    D_00189E20_14.moby->collData = 0;
                    collision = coll_test_point(basis[0], 0, moby, D_L08_001B1914);
                    D_00189E20_14.moby->collData = saved;
                } else {
                    collision = coll_test_point(basis[0], 2, moby, D_L08_001B1914);
                }
            }
            moby->collData = *(s32 *)(moby->pClass + 0x10);
            if (collision) {
                if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 11)
                    moby->state = 5;
                if (D_L08_001BFF40.moby != D_00189E20_14.moby) {
                    float give = 1.0f;
                    if (grounded) {
                        D_L08_001BFF40.point[0] -= basis[0][0];
                        D_L08_001BFF40.point[1] -= basis[0][1];
                        if (D_L08_001BFF40.point[0] < 0.060000002f)
                            D_L08_001BFF40.point[0] *= p->power;
                        if (D_L08_001BFF40.point[1] < 0.060000002f)
                            D_L08_001BFF40.point[1] *= p->power;
                        D_L08_001BFF40.point[0] += basis[0][0];
                        D_L08_001BFF40.point[1] += basis[0][1];
                    } else {
                        give = p->power;
                    }
                    FastVecAdd(moby->pos, D_L08_001BFF40.point, basis[1]);
                    FastVecCross(basis[3], D_L08_001BFF40.normal, p);
                    FastVecCross(basis[2], basis[3], D_L08_001BFF40.normal);
                    vec_scale_to_length(basis[2], basis[2], 1.0f);
                    vec_scale_to_length(p, basis[2], FastVecDot(p, basis[2]) * give);
                    FastVecScale(p, p, D_L08_001B1924);
                    if (moby->pos[2] < p->f17c)
                        moby->state = 5;
                }
            }
        }
        if (moby->state == 3) {
            if (moby->pos[2] < D_L08_001BFF40.lowest[2])
                D_L08_001BFF40.lowest[2] = moby->pos[2];
            if (p->power < 0.98f && (g_pad_state[0x68] & 0x80)) {
                if (p->fx1a8 == 0) {
                    if (!p->fx1ac)
                        snd_play_from_class_bank(1, 0, moby, 0x85c);
                    p->fx1a8 = 2;
                    p->fx1ac = 12;
                } else if (p->fx1a8 == 2) {
                    if (!EFFECT_LIVE(p->fx1a4)) {
                        p->fx1a4 = snd_play_from_class_bank(2, 4, moby, 0x85c);
                        if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                            snd_stop_voice(p->fx1b4);
                        p->fx1b4 = -1;
                    }
                }
                if (p->f68 < D_L08_001B031C[0]) {
                    func_PAL_L08_004239F0(moby, D_L08_001BFF40.lowest, D_L08_001B1B40,
                        D_L08_001B1B38, D_L08_001B1B3C, D_L08_001B1B34,
                        D_L08_001B1B34, D_L08_001B1B44, D_L08_001B1B48);
                    if (!math_random_int_below(11)) {
                        D_L08_001B99C0.amount = (1.0f - p->power) * 0.05f;
                        D_L08_001B99C0.timer = 12;
                        D_L08_001B99C0.phase = 0;
                    }
                } else {
                    func_PAL_L08_004239F0(moby, D_L08_001BFF40.lowest, D_L08_001B1B58,
                        D_L08_001B1B50, D_L08_001B1B54, D_L08_001B1B4C,
                        D_L08_001B1B4C, D_L08_001B1B5C, D_L08_001B1B60);
                }
                if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                    snd_stop_voice(p->fx1b4);
                p->fx1b4 = -1;
            } else if (p->fx1a8 == 2) {
                if (p->fx1a4 != -1 && EFFECT_LIVE(p->fx1a4))
                    snd_stop_voice(p->fx1a4);
                p->fx1a4 = -1;
                if (p->fx1ac == 0)
                    snd_play_from_class_bank(4, 0, moby, 0x85c);
                p->fx1a8 = 0;
                p->fx1ac = 12;
            } else if (!EFFECT_LIVE(p->fx1b4)) {
                p->fx1b4 = snd_play_from_class_bank(9, 4, moby, 0x85c);
            }
            func_PAL_L08_004239F0(moby, D_L08_001BFF40.lowest, D_L08_001B1B28,
                D_L08_001B1B20, D_L08_001B1B24, D_L08_001B1B1C,
                D_L08_001B1B2C, D_L08_001B1B30, 1.0f);
        }
        moby_transform_joint_to_world(moby, 0, basis[0]);
        basis[0][2] += D_L08_001B19C8;
        {
            float reach = D_L08_001B19B8;
            switch (g_current_map_index) {
            case 8:
                reach = D_L08_001B19BC;
                break;
            case 19:
                reach = D_L08_001B19C0;
                break;
            }
            make_hit_descriptor(basis[2], moby, 0x10000, p, reach);
        }
        coll_process_hit(basis[0], 0, moby, basis[2], D_L08_001B1958);
        if (FastVecLength(p) > D_L08_001B19CC * 0.020000001f) {
            moby_transform_joint_to_world(moby, 1, scratch);
            coll_process_hit(scratch, 0, moby, basis[2], D_L08_001B19C4);
        }
        if (!fresh && D_00189E20_14.vehicle == moby && (g_pad_state[0x69] & 16)) {
            func_PAL_L08_00423D30(moby);
            moby->state = 1;
            if (!EFFECT_LIVE(p->fx1b4))
                p->fx1b4 = snd_play_from_class_bank(9, 4, moby, 0x85c);
        }
        break;
    case 2:
    case 4:
    case 6:
        break;
    case 5:
        func_PAL_L08_00423D30(moby);
        moby_transform_joint_to_world(moby, 0, forward);
        func_PAL_002AC718(moby, p, forward, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f,
                      1, 1, -1, 0, 0x810001);
        qcopy(moby->pos, p->home);
        moby->state = 0;
        break;
    }
    p->lastZ = moby->pos[2];
    {
        float step = p->power * 0.0003490659f;
        p->bobPhase = FastAddRotations(p->bobPhase, D_L08_001B18E8 * step);
    }
    p->bobOffset = math_fast_sin_or_cos_b(p->bobPhase) * D_L08_001B18E4 * p->power;
    moby->pos[2] += p->bobOffset * p->power;
    {
        float k = p->power * 0.0003490659f;
        moby_scale_owner_words_by_angles(moby, &p->sway[0], &p->sway[1], D_L08_001B18EC * 0.017453294f,
                      D_L08_001B18F0 * k, D_L08_001B18F4 * k);
    }
    moby->rot[2] = p->yaw;
    moby->rot[0] = FastAddRotations(moby->rot[0], p->roll);
    moby->rot[1] = FastAddRotations(moby->rot[1], p->pitch);
    if (moby->state == 3) {
        if (g_current_map_index == 8 || g_current_map_index == 19) {
            switch (p->mode8a) {
            case 0:
                if (p->f68 < D_L08_001B031C[0]) {
                    p->mode8a = 1;
                    p->timer88 = 0;
                }
                break;
            case 1:
                (p->timer88)++;
                if (p->timer88 > (D_L08_001B1A78 * 5 + 2) / 6)
                    p->timer88 = (D_L08_001B1A78 * 5 + 2) / 6;
                if (p->f68 > D_L08_001B031C[0])
                    p->mode8a = 3;
                else if (p->timer88 >= (D_L08_001B1A78 * 5 + 2) / 6)
                    p->mode8a = 2;
                break;
            case 2:
                if (p->f68 > D_L08_001B031C[0])
                    p->mode8a = 3;
                break;
            case 3:
                FastDecTimer(&p->timer88);
                if (p->f68 < D_L08_001B031C[0])
                    p->mode8a = 1;
                else if (p->timer88 == 0)
                    p->mode8a = 0;
                break;
            }
            if (p->mode8a && p->f6c) {
                u8 *other = *(u8 **)(p->f6c + 0x68);
                float num = IntToFloat(*(s32 *)(other + 4));
                p->f8c =
                    FloatToInt(D_L08_001B19E4 * num / ((IntToFloat(*(s32 *)other) * 60.0f * 5 + 2) / 6));
            } else {
                p->f8c = 0x200;
            }
            if (p->f6c) {
                if (!p->f74)
                    p->f74 = part_spawn_attached_effect(moby, p->f6c + 0x10);
                else
                    moby_store_position_private(p->f74, p->f6c + 0x10);
            } else if (p->f74) {
                moby_mark_spawned(p->f74);
                p->f74 = 0;
            }
        }
        vec_scale_to_length(forward, moby->mtx, -0.5f);
        if (forward[2] < 0.0f)
            forward[2] = 0.0f;
        forward[2] += 1.5f;
        FastVecAdd(D_00189E20_14.position, forward, moby->pos);
        qcopy(D_00189E20_14.cameraPosition, D_00189E20_14.position);
        D_00189E20_14.cameraPosition[2] = moby->pos[2];
        qcopy(D_00189E20_14.rotation, moby->rot);
    }
    moby->collData = *(s32 *)(moby->pClass + 0x10);
    if (moby->drawn && fast_vec_dist(moby->pos, D_L08_001B9B00) < 64.0f) {
        moby_update_ground_check(moby);
        moby->f6f = 60;
    }
    if (p->sound != -1)
        moby_set_group_flags(p->sound, -1, 0, 0);
    if (p->throttle != 0.0f) {
        if (!EFFECT_LIVE(p->fx1a4)) {
            p->fx1a4 = snd_play_from_class_bank(0, 4, moby, 0x85c);
            func_PAL_L08_0033B2D0(moby, p->fx1a4, 0, p->trail, D_L08_001B1B7C, D_L08_001B1B80);
        } else {
            FastVecSub(forward, moby->pos, p->trail);
            forward[2] = 0.0f;
            snd_fade_looping_by_distance(moby, p->trail, D_L08_001B1A44, D_L08_001B1A48, FastVecLength(forward));
            if (p->fx1b4 != -1 && EFFECT_LIVE(p->fx1b4))
                snd_stop_voice(p->fx1b4);
            p->fx1b4 = -1;
        }
    } else if (p->fx1a8 != 2) {
        if (p->fx1a4 != -1 && EFFECT_LIVE(p->fx1a4))
            snd_stop_voice(p->fx1a4);
        p->fx1a4 = -1;
    }
    math_fast_float_d(&p->fx1ac);
}
