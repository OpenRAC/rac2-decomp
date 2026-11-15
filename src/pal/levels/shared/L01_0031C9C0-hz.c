#include "names.h"
/* func_PAL_L01_0031C9C0, the PAL copy of func_L01_0031AB20: the same C, where 0.5333333611f
   becomes 0.64000005f; 0.01388888899f becomes 0.020000001f; 0.2666666806f becomes 0.32000002f;
   0.06666667014f becomes 0.080000006f; 0.00555555569f becomes 0.008f; 0.1333333403f becomes
   0.16000001f; 0.002777777845f becomes 0.004f. */
#include "common.h"

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

extern void matrix_mul_vec3(void *, void *, void *);

typedef int MotionQuad __attribute__((mode(TI)));
typedef union { float v[4]; MotionQuad q; } MotionVec;

typedef struct {
    MotionVec motion;
    char pad10[0x70];
    MotionVec position;
    char pad90[0x50];
    MotionVec probeEnd;
    char padF0[0x4D0];
    char *held;
} MotionHero;
typedef struct {
    MotionVec velocity;
    char pad10[0x10];
    int flags;
    char pad24[0xC];
    int frame;
    float gain;
    float distance;
    int pad3C;
    int sound;
} MotionState;
typedef struct { MotionVec forward[4]; MotionVec inverse[4]; } MotionPath;

extern MotionHero motionHero __asm__("D_00189E20");
typedef struct {
    char pad00[0x30];
    float hitX;
    float hitY;
} MotionCollision;
extern MotionCollision motionCollision __asm__("D_L01_001BF900");

extern char g_sound_state[];
extern int D_L01_001B2088[] __attribute__((sda));
extern MotionPath *D_L01_001B264C[] __attribute__((sda));
extern float D_L01_001BF928;
extern void lerp_vector(void *, void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern void vec_clamp_length(void *, float);
extern int IsPointInCuboid(void *, int);
extern int path_push_point_away(int, void *, void *, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern int func_L00_002E0200(void *, float, float, int, void *);
extern int moby_push_out_of_wall(void *, void *, void *, void *);

extern float vec_length_xy(void *);

extern void FastVecScale(void *, void *, float);

extern int CollLine(void *, void *, int, void *, int);

#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
#undef FL
#undef IN

typedef int HeroQuad __attribute__((mode(TI)));
extern f32 ApproachValue(void *, float, float);

typedef struct MobyModel {
    char pad00[0x10];
    int f10;
    char pad14[0x32];
    short kind;                 /* 0x46 */
} MobyModel;

typedef struct Moby {
    char pad00[5];
    unsigned char flags;
    char pad06[2];
    float fade;                 /* 0x08: 1.0 fully shown, 0.0 gone */
    char pad0C[0x17];
    unsigned char animation;    /* 0x23 */
    MobyModel *model;           /* 0x24 */
    int f28;
    char pad2C[5];
    unsigned char f31;
    char pad32[2];
    unsigned short state;       /* 0x34 */
    char pad36[2];
    char *buffer0;              /* 0x38 */
    char *buffer1;              /* 0x3C */
    char pad40[0x58];
    int f98;
    char pad9C[0x24];
    HeroQuad matrix[3];         /* 0xC0 */
    char padF0[0x10];
} Moby;

typedef struct WeaponInfo {
    char pad00[0x2C];
    int animation;              /* 0x2C */
    int altAnimation;           /* 0x30: used while the hero's state is 12 */
    char pad34[0xAC];
} WeaponInfo;

typedef struct HeroState {
    char pad00[0x90];
    HeroQuad position;          /* 0x90 */
    char padA0[0x730 - 0xA0];
    HeroQuad matrix[3];         /* 0x730 */
    float f760;
    char pad764[0xC];
    union {
        HeroQuad quad;
        float v[4];
    } f770;                     /* 0x770: copy of position, z eased to 0 */
    char pad780[0xE98 - 0x780];
    Moby *attached[2];          /* 0xE98 */
    char padEA0[4];
    int attachedMode;           /* 0xEA4: 0 shown, 1 fading out, 2 fading out fast */
    char padEA8[0x2290 - 0xEA8];
    Moby *moby;                 /* 0x2290 */
    char pad2294[8];
    int state;                  /* 0x229C */
    char pad22A0[0x22B8 - 0x22A0];
    unsigned char f22B8;
    char pad22B9;
    unsigned char f22BA;
    char pad22BB[8];
    unsigned char f22C3;
    char pad22C4[0x24B0 - 0x22C4];
    int animation;              /* 0x24B0 */
    int weaponId;               /* 0x24B4 */
} HeroState;

static inline void MotionLandingSpeed(float *speed, float rising, float falling)
{
    if (0 < *speed) {
        *speed = rising;
    } else {
        *speed = falling;
    }
}

void func_PAL_L01_0031C9C0(char *m, MotionState *state, int path, float height, float radius, float extent)
{
    MotionVec old, start, delta, turn, target, change, samples[8], matrix[3], actual;
    float speed, gain, limit, accel, ground;
    int i, handle;
    int phase = D_L01_001B2088[0];

    if ((phase & 15) == (((int)m >> 8) & 15)) {
        float dist = fast_vec_dist(&motionHero.position, m + 0x10);

        if (*(unsigned short *)(m + 0x34) & 0x1000) {
            if (state->distance < dist) {
                *(unsigned short *)(m + 0x34) &= 0xEFFF;
            }
        } else if (dist < state->distance) {
            *(unsigned short *)(m + 0x34) |= 0x1000;
        }
    }
    qcopy(&old, m + 0x10);
    if (motionHero.held == m) {
        qcopy(&start, m + 0x10);
        start.v[2] += 0.5f;
        if (CollLine(&start, &motionHero.probeEnd, 2, m, 0)) {
            motionHero.held = 0;
        }
        FastVecSub(&delta, m + 0x10, &motionHero.position);
        if (state->frame != -1 && IsPointInCuboid(m + 0x10, state->frame)) {
            matrix_mul_vec3(&delta, &delta, D_L01_001B264C[0][state->frame].inverse);
            delta.v[1] = 0;
            matrix_mul_vec3(&delta, &delta, D_L01_001B264C[0][state->frame].forward);
        }
        gain = 4.0f;
        if (state->gain != 0) {
            gain = state->gain;
        }
        vec_fast_normalize_helper(&delta, &delta, gain);
        FastVecAdd(&delta, &delta, &motionHero.position);
        vec_scale_to_length(&turn, &motionHero.motion, gain);
        FastVecAdd(&turn, &turn, &motionHero.position);
        turn.v[2] = delta.v[2];
        lerp_vector(&delta, &delta, &turn, 0.5f);
        FastVecSub(&delta, &delta, &motionHero.position);
        vec_scale_to_length(&delta, &delta, gain);
        FastVecAdd(&delta, &delta, &motionHero.position);
        if (state->flags & 4) {
            gain = vec_distance_xy(m + 0x10, &delta) * 0.64000005f;
            accel = 0.020000001f;
            limit = 0.32000002f;
        } else {
            gain = vec_distance_xy(m + 0x10, &delta) * 0.080000006f;
            accel = 0.008f;
            limit = 0.16000001f;
        }
        if (limit < gain) {
            gain = limit;
        }
        FastVecSub(&target, &delta, m + 0x10);
        target.v[2] = 0;
        vec_scale_to_length(&target, &target, gain);
        FastVecSub(&change, &target, state);
        vec_clamp_length(&change, accel);
        state->velocity.v[0] += change.v[0];
        state->velocity.v[1] += change.v[1];
    } else {
        speed = FastVecLength(state);
        ApproachValue(&speed, 0, 0.004f);
        vec_scale_to_length(state, state, speed);
    }
    if (0.001f < FastVecLength(state)) {
        if (!(state->flags & 2)) {
            qcopy(&start, m + 0x10);
            qcopy(&delta, m + 0x10);
            start.v[2] += 0.25f;
            delta.v[2] -= 1;
            ground = 0;
            if (CollLine(&start, &delta, 16, m, 0)) {
                ground = D_L01_001BF928;
            }
            if (*(float *)(m + 0x18) < ground) {
                *(float *)(m + 0x18) = ground;
                MotionLandingSpeed(&state->velocity.v[2], 0, 0);
            } else {
                state->velocity.v[2] -= 0.008f;
            }
        }
        if (!(state->flags & 4) && vec_distance_xy(m + 0x10, &motionHero.position) < radius + 2.5f) {
            float toward;

            FastVecSub(&start, &motionHero.position, m + 0x10);
            start.v[2] = 0;
            vec_scale_to_length(&start, &start, 1);
            toward = FastVecDot(&start, state);
            if (0 < toward) {
                vec_scale_to_length(&delta, &start, -toward);
                FastVecAdd(state, state, &delta);
            }
        }
        turn.q = 0;
        turn.v[2] = 0.7853982449f;
        FastVecAdd(m + 0x10, m + 0x10, state);
        qcopy(&delta, m + 0x10);
        delta.v[2] += 0.25f;
        euler_rotation_basis(matrix, &turn);
        vec_fast_normalize_helper(&start, state, radius);
        for (i = 0; i < 8; i++) {
            matrix_mul_vec3(&start, &start, matrix);
            FastVecAdd(&samples[i], m + 0x10, &start);
            samples[i].v[2] += 0.25f;
            moby_push_out_of_wall(m, state, &delta, &samples[i]);
        }
        FastVecScale(&target, state, 5);
        FastVecAdd(&target, &target, m + 0x10);
        target.v[2] += radius;
        coll_sweep_from_object(m, &target, 0x4000000, 0, 1, 0, radius + 0.2f, 1, 1);
        qcopy(&change, m + 0x10);
        change.v[2] += height;
        if (func_L00_002E0200(&change, radius, extent, 0, m)) {
            *(float *)(m + 0x10) = motionCollision.hitX;
            *(float *)(m + 0x14) = motionCollision.hitY;
        }
        if (path != -1) {
            path_push_point_away(path, m + 0x10, m + 0x10, radius);
        }
        FastVecSub(&actual, m + 0x10, &old);
        gain = vec_length_xy(&actual);
        if (gain < vec_length_xy(state)) {
            state->velocity.v[0] = actual.v[0];
            state->velocity.v[1] = actual.v[1];
        }
        if (vec_length_xy(state) != 0) {
            char *sound = g_sound_state + state->sound * 0x70;

            if (*(char **)(sound + 0x88) != m || !((unsigned char *)sound)[0x74]) {
                state->sound = PlayMobySound(0, 4, m);
            }
        } else {
            handle = state->sound;
            if (handle != -1) {
                unsigned char *sound = (unsigned char *)g_sound_state + handle * 0x70;

                if (*(char **)(sound + 0x88) == m && sound[0x74]) {
                    snd_stop_voice(handle);
                }
            }
            state->sound = -1;
        }
    } else {
        handle = state->sound;
        if (handle != -1) {
            char *sound = g_sound_state + handle * 0x70;

            if (*(char **)(sound + 0x88) == m && ((unsigned char *)sound)[0x74]) {
                snd_stop_voice(handle);
            }
        }
        state->sound = -1;
    }
}
