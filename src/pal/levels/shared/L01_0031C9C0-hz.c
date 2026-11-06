/* func_PAL_L01_0031C9C0, the PAL copy of func_L01_0031AB20: the same C, where 0.5333333611f
   becomes 0.64000005f; 0.01388888899f becomes 0.020000001f; 0.2666666806f becomes 0.32000002f;
   0.06666667014f becomes 0.080000006f; 0.00555555569f becomes 0.008f; 0.1333333403f becomes
   0.16000001f; 0.002777777845f becomes 0.004f. */
#include "common.h"

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

extern void func_00283098(void *, void *, void *);

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

extern char D_00188660[];
extern int D_L01_001B2088[] __attribute__((sda));
extern MotionPath *D_L01_001B264C[] __attribute__((sda));
extern float D_L01_001BF928;
extern void func_00282D08(void *, void *, void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F70(void *, void *, float);
extern void func_002833F0(void *, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_002AC9F8(void *, float);
extern int func_002ACBC8(void *, int);
extern int func_002C9218(int, void *, void *, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern int func_L00_002E0200(void *, float, float, int, void *);
extern int func_L01_0031B300(void *, void *, void *, void *);

extern float func_00282E20(void *);

extern void func_00282D30(void *, void *, float);

extern int func_002761F8(void *, void *, int, void *, int);

#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
#undef FL
#undef IN

typedef int HeroQuad __attribute__((mode(TI)));
extern void func_002AA2E8(void *, float, float);

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
        float dist = func_00282E48(&motionHero.position, m + 0x10);

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
        if (func_002761F8(&start, &motionHero.probeEnd, 2, m, 0)) {
            motionHero.held = 0;
        }
        func_00282CF0(&delta, m + 0x10, &motionHero.position);
        if (state->frame != -1 && func_002ACBC8(m + 0x10, state->frame)) {
            func_00283098(&delta, &delta, D_L01_001B264C[0][state->frame].inverse);
            delta.v[1] = 0;
            func_00283098(&delta, &delta, D_L01_001B264C[0][state->frame].forward);
        }
        gain = 4.0f;
        if (state->gain != 0) {
            gain = state->gain;
        }
        func_00282F70(&delta, &delta, gain);
        func_00282CC0(&delta, &delta, &motionHero.position);
        func_00282F20(&turn, &motionHero.motion, gain);
        func_00282CC0(&turn, &turn, &motionHero.position);
        turn.v[2] = delta.v[2];
        func_00282D08(&delta, &delta, &turn, 0.5f);
        func_00282CF0(&delta, &delta, &motionHero.position);
        func_00282F20(&delta, &delta, gain);
        func_00282CC0(&delta, &delta, &motionHero.position);
        if (state->flags & 4) {
            gain = func_00282E80(m + 0x10, &delta) * 0.64000005f;
            accel = 0.020000001f;
            limit = 0.32000002f;
        } else {
            gain = func_00282E80(m + 0x10, &delta) * 0.080000006f;
            accel = 0.008f;
            limit = 0.16000001f;
        }
        if (limit < gain) {
            gain = limit;
        }
        func_00282CF0(&target, &delta, m + 0x10);
        target.v[2] = 0;
        func_00282F20(&target, &target, gain);
        func_00282CF0(&change, &target, state);
        func_002AC9F8(&change, accel);
        state->velocity.v[0] += change.v[0];
        state->velocity.v[1] += change.v[1];
    } else {
        speed = func_00282DF0(state);
        func_002AA2E8(&speed, 0, 0.004f);
        func_00282F20(state, state, speed);
    }
    if (0.001f < func_00282DF0(state)) {
        if (!(state->flags & 2)) {
            qcopy(&start, m + 0x10);
            qcopy(&delta, m + 0x10);
            start.v[2] += 0.25f;
            delta.v[2] -= 1;
            ground = 0;
            if (func_002761F8(&start, &delta, 16, m, 0)) {
                ground = D_L01_001BF928;
            }
            if (*(float *)(m + 0x18) < ground) {
                *(float *)(m + 0x18) = ground;
                MotionLandingSpeed(&state->velocity.v[2], 0, 0);
            } else {
                state->velocity.v[2] -= 0.008f;
            }
        }
        if (!(state->flags & 4) && func_00282E80(m + 0x10, &motionHero.position) < radius + 2.5f) {
            float toward;

            func_00282CF0(&start, &motionHero.position, m + 0x10);
            start.v[2] = 0;
            func_00282F20(&start, &start, 1);
            toward = func_00282DB0(&start, state);
            if (0 < toward) {
                func_00282F20(&delta, &start, -toward);
                func_00282CC0(state, state, &delta);
            }
        }
        turn.q = 0;
        turn.v[2] = 0.7853982449f;
        func_00282CC0(m + 0x10, m + 0x10, state);
        qcopy(&delta, m + 0x10);
        delta.v[2] += 0.25f;
        func_002833F0(matrix, &turn);
        func_00282F70(&start, state, radius);
        for (i = 0; i < 8; i++) {
            func_00283098(&start, &start, matrix);
            func_00282CC0(&samples[i], m + 0x10, &start);
            samples[i].v[2] += 0.25f;
            func_L01_0031B300(m, state, &delta, &samples[i]);
        }
        func_00282D30(&target, state, 5);
        func_00282CC0(&target, &target, m + 0x10);
        target.v[2] += radius;
        func_002A8C28(m, &target, 0x4000000, 0, 1, 0, radius + 0.2f, 1, 1);
        qcopy(&change, m + 0x10);
        change.v[2] += height;
        if (func_L00_002E0200(&change, radius, extent, 0, m)) {
            *(float *)(m + 0x10) = motionCollision.hitX;
            *(float *)(m + 0x14) = motionCollision.hitY;
        }
        if (path != -1) {
            func_002C9218(path, m + 0x10, m + 0x10, radius);
        }
        func_00282CF0(&actual, m + 0x10, &old);
        gain = func_00282E20(&actual);
        if (gain < func_00282E20(state)) {
            state->velocity.v[0] = actual.v[0];
            state->velocity.v[1] = actual.v[1];
        }
        if (func_00282E20(state) != 0) {
            char *sound = D_00188660 + state->sound * 0x70;

            if (*(char **)(sound + 0x88) != m || !((unsigned char *)sound)[0x74]) {
                state->sound = func_002E5CF8(0, 4, m);
            }
        } else {
            handle = state->sound;
            if (handle != -1) {
                unsigned char *sound = (unsigned char *)D_00188660 + handle * 0x70;

                if (*(char **)(sound + 0x88) == m && sound[0x74]) {
                    func_002E59F8(handle);
                }
            }
            state->sound = -1;
        }
    } else {
        handle = state->sound;
        if (handle != -1) {
            char *sound = D_00188660 + handle * 0x70;

            if (*(char **)(sound + 0x88) == m && ((unsigned char *)sound)[0x74]) {
                func_002E59F8(handle);
            }
        }
        state->sound = -1;
    }
}
