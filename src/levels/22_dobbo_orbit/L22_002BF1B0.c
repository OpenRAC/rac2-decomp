/* func_L22_002BF1B0 (Dobbo Orbit): the hero's per-frame state handler, a switch on the
   state at 0x2294 through one 147-entry jump table over 63 bodies (37268 bytes, level 22
   only; twin of func_L23_002C38B0).  One function: one prologue, one return.

   The unit's flags (config/cflags.txt) are each needed by retail's code:
   -ffast-math      retail's one max.s;
   -g               the line labels that put retail's nop pairs before the div.s
                    instructions;
   -frac2-zero-ti-por           the por+sq clears of 0($sp);
   -frac2-keep-block-order and  no Cygnus block counting before cse, so case 0x7C's spawn
   -frac2-no-null-pointer-checks  block keeps no stray no-op after its last call;
   (the quadword clears' zeros in $a0/$v0 are the compiler's one-GPR TImode reload);
   -frac2-hazard-labels         the branch target on the mtc1 hazard nop.
   See docs/build/compiler-notes.md for each option.

   The common 0xF0 tail is GCC's cross-jumping of the inline func_L00_002D34C0 calls, not a
   source label.  Call argument orders follow retail's register setup (same ABI).

   Function-scope shared_rate and shared_limit: one variable each serves two cases, as
   retail's register choices show.  shared_rate is case 0x00's frame count (state 3) and 0x57's
   turn rate: a pseudo with a second, live set is kept through gcse's constant propagation
   (cse2 substitutes it back), so 0x57 loads 0.3f into $f13 at the join as retail does.
   shared_limit is case 0x82's turn rate g and 0x57's turn limit: the wider conflicts put the
   limit in $f22.  Case 0x57's do { } while (0) ends between the rate and the 0x1454
   test; its loop notes are a scheduling barrier, so the rate load stays first and the
   two 0x40F branches keep empty delay slots. */

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));

extern unsigned char D_00189E20[];
extern unsigned char D_00189F10[];
#define FLD(base, type, offset) (((struct { u8 pad[offset]; type v; } *)(base))->v)
#define H(type, offset) FLD(D_00189E20, type, offset)
#define HP(offset) ((void *)&H(u8, offset))

extern unsigned char D_00188660[];
extern unsigned char D_L22_0025DE90[];
extern unsigned char D_L22_001B9B40[];
typedef struct { u16 count; u16 pad; u32 time; u32 levels; } StatRecord;
typedef struct { StatRecord records[32]; } StatTable;
extern StatTable D_0018C750;
extern unsigned int D_001A7390 __attribute__((sda));
extern unsigned int D_001A79F0 __attribute__((sda));
extern unsigned char D_00138180[];
extern u32 D_00138320;  /* the pad-buttons word inside D_00138180 */
extern u16 D_0018CF10;
static __inline__ void stat_bump(StatTable *table, int index)
{
    u32 clock;
    if (table->records[index].count < 0xFFFF) table->records[index].count++;
    clock = D_001A7390;
    if (table->records[index].time < clock) table->records[index].time = clock;
    table->records[index].levels = (table->records[index].levels | (1 << gCurrentMapIndex)) | 0x80000000;
}
extern u8 D_001A7B08[0x40] __attribute__((sda));
extern unsigned char D_001A7B2A __attribute__((sda));
typedef struct { int f[11]; } Rec44;
extern Rec44 D_L22_0025FA10[];
extern float D_L22_001ACE68[];
extern int D_L22_001A8FF0 __attribute__((sda));
extern void *D_L22_001B28B0 __attribute__((sda));
extern void *D_L22_001B28B8 __attribute__((sda));
extern void *D_L22_001C4140[];

extern void func_L00_002AA478(int, int);
extern void func_L00_002AA570(int, int);
extern void func_L00_002AA750(int, int);
extern void func_L00_002AA938(int, int, int);
extern void func_L00_002AABE0(int, int, int);
extern void func_L00_002AAE00(void);
extern void func_L00_002A9E30(float, float, float, float);
extern void func_L00_002AA0F0(float, float, float);
extern int func_L00_002ADEA0(int);
extern int func_L00_002ACF88(void *, void *, void *);
extern void func_L00_002AC578(void);
extern void func_L00_002B35A0(void);
extern int func_L00_002B3998(float);
extern void func_L00_002B39F0(float, int);
extern void func_L00_002B3D10(void);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L00_002B3F68(void);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B4208(float);
extern void func_L00_002B42D8(void *);
extern void func_L00_002B54F8(float, float);
extern float func_L00_002B5590(void *);
extern void func_L00_002B6560(void);
extern void func_L00_002B6BC8(void);
extern void func_L00_002B75A0(float, float, float);
extern void func_L00_002B7B80(void);
extern void func_L00_002B8930(void);
extern void func_L00_002B8CB8(void);
extern void func_L00_002B94D8(float);
extern void func_L00_002B9598(void);
extern float func_L00_002B9B38(void *, int);
extern int func_L00_002B9B88(int index, int flags);
extern void func_L00_002B9BB0(int, void *, int);
extern void func_L00_002B9F00(float, float, float);
extern void func_L00_002BA508(void);
extern int func_L00_002CAF20(void);
extern void func_L00_002D2168(int, int, float);
extern void func_L00_002D34C0(void *, void *, float);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_002D3798(void *, void *, float);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_L00_002D3960(void *, void *);
extern float func_L00_002D3A58(void *);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3BD8(void *, void *, float);
extern int func_L00_002D6900(unsigned int index);
extern void func_L00_00322BE0(void *, int);
extern float func_L00_0032F038(int);
extern void func_L00_0041E958(float, float, float);
extern void func_L22_002B8E10(int);

extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277F48(void *, int, float, void *, void *);
extern float func_00282C48(float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282F70(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern int func_00283CF0(float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern float func_002AA2E8(void *, float, float);
extern float func_002AA3A8(void *, void *, float, float, float, float);
extern float func_002AA738(float, int, float);
extern void func_002AA800(void *, int, float, float);
extern float func_002AA898(float *position, float target, float *velocity, float acceleration,
                           float damping, float limit, int direction);
extern int func_002ABB78(void *);
extern void func_002AC9F8(void *, float);
extern void func_002E59F8(int);
extern void func_002FD1B8(void *, void *, int, float, float, float, float);

extern int func_00282948(void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern void func_00290010(int, int, int, float);
extern void *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern void func_002BE278(void *, void *, int, float);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002A9D38(void *, void *, float);
extern void func_L00_002AB0A8(float, float);
extern void func_L00_002AB0D8(float, float);
extern void func_L00_002AB0F0(float, float);
extern void func_L00_002ADCF8(void *);
extern void func_L00_002B3DC0(float, float, float);
extern void func_L00_002B4308(void);
extern void func_L00_002B6198(float);
extern void func_L00_002BA220(void);
extern void func_L00_002C9228(void);
extern void func_L00_002D3638(void *, int, float, float, float);
extern void func_L00_002D3B58(void *, void *, float);
extern s32 func_L00_002EE4D8(void *, void *, float);
extern int func_L00_0031D620(int, int, float);
extern int func_L00_003417B8(void *, int, int, int);
extern u8 D_00139568[];
extern u32 D_L22_001B1C48 __attribute__((sda));
extern float D_L22_0025FD90[], D_L22_0028F5F0[];
extern u8 D_L22_002645F0[];
extern int func_00282978(void *);
extern float func_00282C10(float);
extern void func_002830C0(void *,void *,void *);
extern void func_00283410(void *,void *);
extern void func_00283698(void *,void *);
extern int func_002A77E0(int);
extern int func_002A88A0(float *,float *,float,float,float);
extern void func_002AF000(void *,float,float,float);
extern float func_L00_002A9F30(float *,int);
extern void func_L00_002AB0C0(float,float);
extern void func_L00_002BA138(void *,int);
extern void func_L00_00322A98(void *,void *);
extern void func_L00_00322AC0(void *,int,int,float);
extern void func_L00_00323F28(void *,void *,float,float,float);
extern void *func_L00_00338D28(void *,void *,float);
extern int func_L22_002A8CE0(int);
extern float D_L22_001A7DAC[][4] __attribute__((sda));
extern s32 func_002A8C28(u8 *object, const Vec4 *position, s32 mask,
                        float radius, float strength, float direction_scale, s32 type, s32 kind, s32 last);
extern void func_L22_003B9128(u8 *object, const Vec4 *position, s32 alternate);
extern void func_0029FCC0(u8 *object, s32 joint_index, Vec4 *out);
extern void func_002AFD88(u8 *object, Vec4 *out, float x, float y, float z);
extern s32 func_L00_00325FC8(float *angle, s32 first_color, s32 second_color, float step);
extern s32 func_L00_00341820(void *path, Vec4 *out, s32 *index, float *fraction, float step, s32 wrap);
extern s32 func_L00_00341FA8(void *path, Vec4 *position, Vec4 *state, s32 *index, float *fraction,
                            s32 wrap, float max_distance, float first, float second);
extern void func_L00_002B8F00(const Vec4 *input, Vec4 output_matrix[4], s32 mode,
                            float first, float second, float third);
extern u8 *func_002BF728(const Vec4 *from, const Vec4 *to, float radius, float floor);

typedef struct Probe48 {
    Vec4 vector;            /* +00..0f; w is the strength */
    u32 unused10;
    u32 unused14;
    u8 type;                /* +18 */
    u8 kind;                /* +19 */
    u16 id;                 /* +1a */
    u32 unused1c[5];
} Probe48;

typedef union Vec { U128 q; f32 f[4]; } Vec;
typedef struct Moby {
    u8 pad0[0x10];
    /* 0x10 */ Vec pos;
    u8 pad20[0x3];
    /* 0x23 */ u8 f23;
    u8 pad24[0xC];
    /* 0x30 */ u8 f30;
    /* 0x31 */ u8 f31;
    /* 0x32 */ u16 f32;
    /* 0x34 */ u16 f34;
    u8 pad36[0xB];
    /* 0x41 */ u8 f41;
    /* 0x42 */ u8 f42;
    /* 0x43 */ u8 f43;
    u8 pad44[0x1C];
    /* 0x60 */ u8 f60;
    u8 pad61[0x7];
    /* 0x68 */ u8* f68;
    u8 pad6C[0x3E];
    /* 0xAA */ s16 fAA;
    u8 padAC[0x14];
    /* 0xC0 */ Vec fC0[3];
    /* 0xF0 */ Vec rot;
} Moby;

/* Runs the hero's movement and actions every frame: it looks at the hero's current state and does what that state needs. */
void func_L22_002BF1B0(void)
{
    u8 *entry_object = H(u8 *, 0x2290);
    int entry_substate = H(int, 0x2298);
    u8 entry_animation = entry_object[0x43];
    float shared_scale, shared_speed;
    float shared_rate;
    float shared_limit;
    int shared_mode, shared_index;
    float *shared_table;
    u8 *hp32;
    u8 *shared_object;

    /* Only one state arm runs per invocation. Its temporary vectors and probe
     * records share storage; every pointer passed to a common tail is resident. */
    union {
        struct {
            Vec4 forward;
        } state_00;
        struct {
            Vec4 position;
            Vec4 velocity;
            Vec4 lateral;
        } state_32;
        struct {
            Vec4 joint_position;
            Vec4 projected_position;
            Vec4 offset;
        } state_67;
        struct {
            Vec4 local;
            Vec4 impulse;
            Vec4 output_matrix[4];
        } state_86;
        struct {
            Vec4 targetPosition;
            Vec4 desired;
            Vec4 offset;
        } state_24;
        struct {
            Vec4 targetPosition;
            Vec4 relative;
            Vec4 scaled;
            Vec4 delta;
        } state_25;
        struct {
            Vec4 direction;
            Vec4 angles;
            Vec4 matrices[4];
            Vec4 rotation;
            Vec4 inverse[4];
            Vec4 lateral;
            Vec4 relative;
            Vec4 point;
        } state_2b;
        struct {
            Vec4 delta;             /* also the contact origin */
            union {
                Vec4 movement;
                unsigned char contact[48] __attribute__((aligned(16)));
            } u;
            Vec4 force;
        } state_14;
        struct {
            unsigned char query[48] __attribute__((aligned(16)));
            Vec4 impulse;
            Vec4 point;
        } state_1f;
        struct {
            Vec4 impulse;
        } state_02;
        struct {
            Vec4 local;
            Vec4 target_position;
            Vec4 impulse;
        } state_7b;
        struct {
            Vec4 position;
            Vec4 velocity;
        } state_30;
        struct {
            Vec4 first;             /* path sample, or the spawned debris origin */
            Vec4 second;            /* second path sample, or the debris velocity */
            union {
                struct { Vec4 displacement; Vec4 previousStep; } d;
                struct { Vec4 probeA; Vec4 probeB; } p;
                unsigned char query[48] __attribute__((aligned(16)));
            } u;
            Vec4 direction;
            Vec4 position;
        } state_27;
        struct {
            Vec4 reference_position;
            Vec4 particle_position; /* later the path position */
            Vec4 particle_velocity; /* later the path difference */
        } state_71;
        struct {
            Vec4 contact;           /* first vector of a 64-byte contact record */
            Vec4 contact_rest[3];
            Vec4 side;
            Vec4 candidate;
            Vec4 direction;
        } state_19;
        struct {
            Vec4 rotation;
        } state_06;
        struct {
            Vec4 origin;
            Vec4 endpoint;          /* also the push force */
        } state_07;
        struct {
            Vec4 difference;
        } state_62;
        struct {
            Vec4 difference;
        } state_63;
        struct {
            Vec4 middle;
            Vec4 first;
            Vec4 second;
        } state_4d;
        struct {
            Vec4 hitPosition;       /* first vector of a 64-byte contact record */
            Vec4 hit_rest[3];
            Vec4 side;
            Vec4 candidate;
            Vec4 line;
        } state_49;
        struct {
            Vec4 effect_position;
            Probe48 probe;
            Vec4 local_offset;
            Vec4 midpoint;
        } state_5d;
        struct {
            Vec4 effect_position;
        } state_5e;
        struct {
            Vec4 effect_position;
        } state_58;
        struct {
            Vec4 effect_position;
        } state_57;
        struct {
            Vec4 effect_position;
        } state_59;
        struct { Vec s00, s10, s20, s30, s40, s50, s60; } mine;
        struct { Vec a, b, m1[4], e, m2[4], vB0, vC0, vD0; } mine2b;
    } workspace;

    switch (H(u32, 0x2294)) {
/* Hand reconstruction of the first state groups; offsets are in D_00189E20. */
case 0: case 1: case 3: case 4: case 28: case 29: case 30:
case 57: case 109: case 111: case 125:
{
    float step;
    if (H(u8, 0x22B9)) SpawnJitteredParticleAfterDelay(15, 30);
    if (H(u8, 0x1492)) BuildHeroMoveImpulse(0.7f, 0.0f);
    else BuildHeroMoveImpulse(0.5f, 0.033333335f);
    TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
    ResolveStickInputToDirection(1.0f, 0);
    if ((H(u32, 0x2294) == 1 || H(u32, 0x2294) == 29) && H(u8, 0x22B5)) {

        *(U128 *)&workspace.state_00.forward = 0; workspace.state_00.forward.x = 1.0f;
        matrix_mul_vec3(HP(0x190), &workspace.state_00.forward, &FLD(D_L22_001B9B40, u8, 0x370));
        H(float, 0x1A0) = FLD(D_L22_001B9B40, float, 0x158);
        SteerHeroHeading(0, 1.0f, 0.0f, 2.9088826f);
        if (H(u8, 0x22BB) && H(int, 0x1B8) == 120) {
            stat_bump(&gProgressStatistics, 18);
        }
    }
    if (H(u32, 0x2294) == 3 && TryStartHeroGrab()) goto finish;
    if (H(u32, 0x2294) == 4 &&
        (H(float, 0x24B8) > 0.2f || H(u8 *, 0x2290)[0x43] == 14 || H(u8 *, 0x2290)[0x43] == 15)) {
        if (H(u32, 0x2294) == 4) SteerHeroHeading(0, 0.002f, 0.07f, 0.1163553f);
        if (FloatAbs(H(float, 0x1A4)) > 0.0058177654f) {
            int anim = H(float, 0x1A4) < 0.0f;
            anim += 14;
            if (H(u8 *, 0x2290)[0x43] != anim)
                set_hero_animation(anim, 0, 5.0f);
            H(float, 0xC20) = FloatAbs(H(float, 0x1A4)) * 18.093401f;
            if (H(float, 0xC20) < 0.55f) H(float, 0xC20) = 0.55f;
            if (H(float, 0xC20) > 2.5f) H(float, 0xC20) = 2.5f;
        } else if (H(float, 0x1A4) == 0.0f && H(u8 *, 0x2290)[0x43] != 13) {
            set_hero_animation(13, 0, 7.0f);
        }
    }
    H(float, 0x1B0) = 0.0f;
    if (H(u32, 0x2294) == 3) {
        float rate = H(float, 0x17C) + 1.0f;
        if (rate > 1.0f) rate = 1.0f;
        step = rate * 0.0075000003f;
        H(float, 0x24AC) = step;
        if (H(u8 *, 0x2290)[0x42] == H(u8 *, 0x2290)[0x43]) {
            shared_rate = H(float, 0x174) / step;
            if (shared_rate > 5.0f && (float)H(u8 *, 0x2290)[0x41] < 5.5f) {
                AdjustHeroAnimationSpeedForTargetFrame(13.0f, shared_rate, 0.5f, -1.0f);
                if (H(float, 0xC20) > 1.1f) H(float, 0xC20) = 1.1f;
            } else if ((float)H(u8 *, 0x2290)[0x41] > 6.5f) H(float, 0xC20) = 1.0f;
        }
    } else if (H(u32, 0x2294) == 4) {
        step = H(u8, 0x1492) ? 0.00047222225f : 0.0075000003f;
    } else step = 0.004916667f;
    ApproachHeroSpeed(0.0f, step);
    ClearVector128(HP(0xF0));
    ShrinkHeroVectorByAmount(step);
    if (H(u8, 0x1497) && D_001A7B08[3]) {
        if (H(float, 0x31C) > 0.2f) { ApplyHeroModeTransform(HP(0xF0),HP(0x120),0.0061111115f); goto finish; }
        ApplyHeroModeTransform(HP(0xF0), HP(0xF0), 0.015000001f);
        if (H(int, 0x33C)) {
            qcopy(&H(U128, 0x80), &H(U128, 0x2D0));
            H(s16, 0x34E) = 0;
            H(float, 0x31C) = 0.0f;
        }
        goto finish;
    }
    SlideHeroAlongWalls(0);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); CancelHeroVelocityIntoWall(); }
    else ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}


    case 0x7C:
    {
        u8 *hero = gHeroState;
        if (FLD(hero, Moby *, 0x7A4) == 0) {
            Moby *m = CreateMoby(0x52A);
            FLD(hero, Moby *, 0x7A4) = m;
            if (FLD(hero, Moby *, 0x7A4) != 0) {
                qcopy(&m->pos, &FLD(hero, Vec, 0x80));
                qcopy(&m->rot, &FLD(hero, Vec, 0x90));
                m->f32 = 0x40;
                FLD(hero, Moby *, 0x7A4)->f31 = 1;
                FLD(hero, Moby *, 0x7A4)->f30 = 0;
                FLD(hero, Moby *, 0x7A4)->f23 = 0;
                FLD(hero, Moby *, 0x7A4)->f34 |= 0x800;
                func_002A0F48(FLD(hero, Moby *, 0x7A4));
                PlayMobySound(0, 0, FLD(hero, Moby *, 0x7A4));
            }
        }
        if (FLD(hero, Moby *, 0x7A4)) {
            Moby *source, *effect;
            FLD(hero, Moby *, 0x7A4)->f23 += FloatToInt(5.0f);
            if (FLD(hero, Moby *, 0x7A4)->f23 > 0x80) FLD(hero, Moby *, 0x7A4)->f23 = 0x80;
            effect = FLD(hero, Moby *, 0x7A4);
            source = FLD(hero, Moby *, 0x2290);
            qcopy(&effect->pos, &source->pos);
            qcopy(&effect->rot, &source->rot);
            func_002A0F48(effect);
        }
        H(float, 0xF8) = 0.0f;
        func_L00_002EE4D8(&H(Vec, 0xF0), &H(Vec, 0xF0), vec_length_xy(&H(Vec, 0xF0)) * 0.92f);
        UpdateHeroHeightOffset();
        goto finish;
    }

case 0x32: case 0x33: case 0x34:
{
    float oldPitch,steer,minimumSteer,pitchChange,controllerScale,rate,maximumInput,steeringLimit;
    if (H(u32,0x2294)==0x34) {
        if (H(s32,0x1B8)>70) D_0018CF10=65535;
        UpdateSoundSlotObject(5,H(void*,0x2290),15);QueueRecordsByIndex(22);
    } else {
        int slot=H(s32,0x2440);
        if (slot!=-1 && FLD(gSoundState+slot*0x70, void *, 0x88)==H(void*,0x2290) &&
            FLD(gSoundState+slot*0x70, u8, 0x74)) StopSoundVoice(slot);
        H(s32,0x2440)=-1;
    }
    if (H(s16,0xA4A)) {
        int count;
        FastDecTimer(HP(0xA4A));count=(s16)H(u16,0xA4A)>>2;
        if (count>8) count=8;
        EmitHeroRandomizedMotionEffects(count,0,0);
    }
    if (H(u32,0x2294)==0x32 && !H(s32,0xC2C) && H(float,0xC38)>0.0f && H(float,0xC38)<10.0f)
        EmitHeroRandomizedMotionEffects(4,1,0);
    if (H(u32,0x2294)==0x33 && H(s32,0x22A0)==0x34 && H(s32,0x1B8)<15)
        EmitHeroRandomizedMotionEffects((20-H(s32,0x1B8))/3+1,1,0);
    if (H(s32,0x2298)==1) {
        if (H(s32,0x1B8)==1) {
            EmitHeroDustAndDebris(3,16,0);
            if (D_L22_001B28B0)
                RippleDisturb(D_L22_001B28B0,D_L22_001B28B8,0,H(float,0x80),H(float,0x84),0.4f,-0.3f);
            H(u16,0xA4A)=70;
        }
        ++H(s32,0xA20);
        if (H(s32,0xA20)>40) H(s32,0x2298)=0;
    }
    {
        float horizontal=FLD(gPadState, float, 0x128), vertical=FLD(gPadState, float, 0x12C);
        maximumInput=horizontal<vertical?vertical:horizontal;
    }
    steeringLimit=0.011635531f;steeringLimit+=maximumInput*0.008726647f; /* retail max.s, not float-to-int/OR */
    steer=0.0f;
    minimumSteer=0.2f;
    if ((FLD(gPadState, u64, 0x1A0)&0xC0)==0x80 || H(s32,0x2298)==1) {
        steer=FLD(gPadState, float, 0x12C)*1.5f;
        if (steer>1.0f) steer=1.0f;
        if (steer<minimumSteer) steer=minimumSteer;
        if (FLD(gPadState, s32, 0x1DC)!=0x79) {
            ++H(s16,0xA42);H(s16,0xA40)=0;
            steer=(float)H(s16,0xA42)*0.025f+0.5f;
            if (steer>1.0f) steer=1.0f;
        }
        if (H(s32,0x2298)==1 && steer<0.35f) steer=0.35f;
        steer*=1.361357f;
    } else if (FLD(gPadState, u32, 0x1A0)&0x40) {
        steer=FLD(gPadState, float, 0x128)*1.5f;
        if (steer>1.0f) steer=1.0f;
        if (steer<minimumSteer) steer=minimumSteer;
        if (FLD(gPadState, s32, 0x1DC)!=0x79) {
            H(s16,0xA42)=0;++H(s16,0xA40);
            steer=(float)H(s16,0xA40)*0.025f+0.5f;
            if (steer>1.0f) steer=1.0f;
        }
        if ((float)H(s32,0x24C0)<1500.0f) steer=1.0f;
        steer*= -1.361357f;
    } else {
        H(s16,0xA40)=0;H(s16,0xA42)=0;
    }
    if (FLD(gPadState, u32, 0x1A0)&0x40) {
        ++H(s16,0xA4E);
        if (FLD(gPadState, float, 0x128)>0.75f) {
            if (++H(s16,0xA4C)>90) {
                if (gProgressStatistics.records[11].count < 0xFFFF) gProgressStatistics.records[11].count++;
            }
            {
                u32 clock = D_001A7390;
                if (gProgressStatistics.records[11].time < clock) gProgressStatistics.records[11].time = clock;
                gProgressStatistics.records[11].levels = (gProgressStatistics.records[11].levels | (1 << gCurrentMapIndex)) | 0x80000000;
            }
        } else H(s16,0xA4C)=0;
    } else {H(s16,0xA4E)=0;H(s16,0xA4C)=0;}

    if (FLD(gPadState, u32, 0x1A4)&0x40) {
        hp32=(u8 *)gHeroState;
        if ((s32)(D_L22_001B1C48-FLD(hp32,u32,0xA54))<70) ++FLD(hp32,s32,0xA50);
        FLD(hp32,u32,0xA54)=D_L22_001B1C48;
    }
    if (H(s16,0xA4E)>70) H(s32,0xA50)=0;
    if (FLD(gPadState, u32, 0x1A0)&0x80) H(s32,0xA50)=0;
    if (H(u32,0x2294)==0x33) steer=0.0f;
    oldPitch=H(float,0x94);
    ApproachWithVelocity(HP(0x94),steer,HP(0xA28),0.015f,0.2f,steeringLimit, 0);
    pitchChange=fast_subtract_rotations(H(float,0x94),oldPitch);
    ResolveStickInputToDirection(1.0f, 0);SteerHeroHeading(0,0.007f,0.08f,0.087266475f);
    H(float,0xA2C)=H(float,0x1A4);FastFloatHelperD(HP(0xA34));
    if (H(s32,0x2298)==1) H(float,0x1B0)=0.10000001f;
    else if (H(u32,0x2294)==0x34) {
        if (FLD(gPadState, u32, 0x1A0)&10) H(float,0x1B0)=0.116666675f;
        else H(float,0x1B0)=0.04666667f;
    }
    else H(float,0x1B0)=0.050000004f;
    controllerScale=H(float,0x24B8);
    if (((FLD(gPadState, u32, 0x1A0)&0xC0) || H(s32,0x2298)==1) && H(float,0x24B8)<1.0f) controllerScale=1.0f;
    if (H(float,0x24B8)>0.15f) {
        float minimum=H(u32,0x2294)==0x34?0.4f:0.35f;
        if (controllerScale<minimum) controllerScale=minimum;
    }
    if (H(u32,0x2294)!=0x34 || !(FLD(gPadState, u32, 0x1A0)&10)) H(float,0x1B0)*=controllerScale;
    if (FastFloatHelperD(HP(0xA30))) {

        int low,high,choice;
        TransformMobyJointToWorld(H(void*,0x2290),4,&workspace.state_32.position);
        *(U128 *)&workspace.state_32.lateral = 0; workspace.state_32.lateral.x = 0.4f;
        matrix_mul_vec3(&workspace.state_32.lateral,&workspace.state_32.lateral,H(u8*,0x2290)+0xC0);
        FastVecAdd(&workspace.state_32.position,&workspace.state_32.position,&workspace.state_32.lateral);
        qcopy(&workspace.state_32.velocity, &H(Vec4,0x110));
        vec_scale_to_length(&workspace.state_32.lateral,&workspace.state_32.lateral,0.025000002f);
        FastVecAdd(&workspace.state_32.velocity,&workspace.state_32.velocity,&workspace.state_32.lateral);workspace.state_32.velocity.z+=0.033333335f;
        SpawnBubbleParticle(&workspace.state_32.position,&workspace.state_32.velocity,25200.0f,-1.0f);
        choice=RandomIntBelow(100);
        if ((float)choice<40.0f) H(s32,0xA30)=RandomIntRange(4,11);
        else H(s32,0xA30)=RandomIntRange(40,90);
    }
    if (H(u32,0x2294)==0x34) {
        u8 *attachment;
        if (FastDecTimer(HP(0xA38)) && (attachment=H(u8*,0x1310)) && *(s16*)(attachment+0xAA)==0x261 /* moby class 609 */) {
            int i;
            for(i=0;i<4;++i) {

                float energy;
                TransformMobyJointToWorld(attachment,i%2,&workspace.state_32.position);
                *(U128 *)&workspace.state_32.lateral = 0; workspace.state_32.lateral.x = -0.15f;
                matrix_mul_vec3(&workspace.state_32.lateral,&workspace.state_32.lateral,H(u8*,0x2290)+0xC0);
                FastVecAdd(&workspace.state_32.position,&workspace.state_32.position,&workspace.state_32.lateral);
                workspace.state_32.position.x+=RandomFloatRange(0.0f,0.03f);
                workspace.state_32.position.y+=RandomFloatRange(0.0f,0.03f);
                workspace.state_32.position.z+=RandomFloatRange(0.0f,0.03f);
                qcopy(&workspace.state_32.velocity, &H(Vec4,0x110));
                AddOffsetVector(&workspace.state_32.velocity,&workspace.state_32.velocity,-0.012500001f,H(float,0x98),H(float,0x94));
                H(s16,0xA38)=FloatToInt((0.116666675f-H(float,0x1B4))*42.85714f);
                energy=RandomFloatRange(6300.0f,9450.0f);
                SpawnBubbleParticle(&workspace.state_32.position,&workspace.state_32.velocity,energy,-1.0f);
            }
        }
    }
    if (H(u32,0x2294)==0x34) ApproachHeroSpeed(0.003611111f,0.0022222223f);
    else ApproachHeroSpeed(0.0019444445f,0.0011111111f);
    {
        float angle=FastAddRotations(-H(float,0x94),0.0f);
        if (H(u32,0x2294)==0x34) BuildSphericalOffset(HP(0xF0),H(float,0x1B4),H(float,0x98),angle);
        else if (H(u32,0x2294)==0x32) {
            float speed=H(float,0x1B4)*BlendTableEntriesByClock(D_L22_0025FD90,30)*5.0f;
            if (H(s32,0x22A0)==0x34 && H(s32,0x1B8)<15 && speed<0.075f) speed=0.075f;
            BuildSphericalOffset(HP(0xF0),speed,H(float,0x98),angle);
        } else if (H(u32,0x2294)==0x33) {
            float speed=FastVecLength(HP(0x160));
            if (H(s32,0x22A0)==0x34) ApproachValue(&speed,0.0f,0.0022222223f);
            else ApproachValue(&speed,0.0f,0.0011111111f);
            vec_scale_to_length(HP(0x160),HP(0x160),speed);qcopy(&H(Vec4,0xF0), &H(Vec4,0x160));
        }
        SlideHeroAlongWalls(0);
        rate=H(float,0xA2C)*FastSinOrCosA(angle)*-7.0f;
    }
    ApproachWithVelocity(HP(0x90),rate,HP(0xA24),0.007f,0.17f,0.020362178f, 0);
    SetCameraLimitsSlot1(0.009f,0.22f);SetCameraLimitsSlot2(0.04f,0.2f);SetCameraLimitsSlot3(0.02f,0.2f);
    FLD(D_L22_0025DE90, float, 0x114)=pitchChange*47.0f;FLD(D_L22_0025DE90, float, 0x118)=rate*1.5f;FLD(D_L22_0025DE90, float, 0x110)=rate*1.4f;
    if (FLD(D_L22_0025DE90, float, 0x114)>0.8726647f) FLD(D_L22_0025DE90, float, 0x114)=0.8726647f;
    else if (FLD(D_L22_0025DE90, float, 0x114)< -0.8726647f) FLD(D_L22_0025DE90, float, 0x114)=-0.8726647f;
    FLD(D_L22_0025DE90, float, 0x364)=0.03f;FLD(D_L22_0025DE90, float, 0x368)=0.22f;
    FLD(D_L22_0025DE90, float, 0x324)=pitchChange*40.0f;FLD(D_L22_0025DE90, float, 0x328)=rate*1.1f;
    FLD(D_L22_0025DE90, float, 0x3D8)=rate*1.1f;FLD(D_L22_0025DE90, float, 0x3D4)=pitchChange*40.0f;
    FLD(D_L22_0025DE90, float, 0x414)=0.03f;FLD(D_L22_0025DE90, float, 0x418)=0.22f;
    goto finish;
}


case 0x73:
{
    s32 amount = 10 - H(s32, 0x1b8) / 3;
    float speed;
    if (8 < amount) amount = 8;
    EmitHeroRandomizedMotionEffects(amount, 0, 0);
    H(float, 0xf8) = 0.0f;
    speed = vec_length_xy(&H(Vec4, 0xf0));
    func_L00_002EE4D8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), speed * 0.920000017f);
    SlideHeroAlongWalls(0);
    goto finish;
}



case 0x72:
{
    float speed;
    SpawnJitteredParticleAfterDelay(15, 30);
    H(float, 0xf8) = 0.0f;
    speed = vec_length_xy(&H(Vec4, 0xf0));
    func_L00_002EE4D8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), speed * 0.920000017f);
    SlideHeroAlongWalls(0);
    UpdateHeroHeightOffset();
    goto finish;
}



case 0x67:
case 0x7f:
{

    float speed = FastVecLength(&H(Vec4, 0x160));
    ApproachValue(&speed, 0.0f, 0.00111111114f);
    vec_scale_to_length(&H(Vec4, 0x160), &H(Vec4, 0x160), speed);
    qcopy(&H(Vec4, 0xf0), &H(Vec4, 0x160));
    if (FastFloatHelperD(&H(s32, 0xa30)) == 2) {
        TransformMobyJointToWorld(H(u8 *, 0x2290), 4, &workspace.state_67.joint_position);
        *(U128 *)&workspace.state_67.offset = 0;
        workspace.state_67.offset.x = 0.400000006f;
        matrix_mul_vec3(&workspace.state_67.offset, &workspace.state_67.offset, H(u8 *, 0x2290) + 0xc0);
        FastVecAdd(&workspace.state_67.joint_position, &workspace.state_67.joint_position, &workspace.state_67.offset);
        qcopy(&workspace.state_67.projected_position, &H(Vec4, 0x110));
        vec_scale_to_length(&workspace.state_67.offset, &workspace.state_67.offset, 0.0250000022f);
        FastVecAdd(&workspace.state_67.projected_position, &workspace.state_67.projected_position, &workspace.state_67.offset);
        workspace.state_67.projected_position.z = workspace.state_67.projected_position.z + 0.0333333351f;
        SpawnBubbleParticle(&workspace.state_67.joint_position, &workspace.state_67.projected_position, 25200.0f, -1.0f);
        if (H(s32, 0x1b8) < 40) {
            H(s32, 0xa30) = RandomIntRange(2, 5);
            H(s32, 0xa30) = H(s32, 0xa30) + H(s32, 0x1b8) / 5;
        } else if (70 < H(s32, 0x1b8)) {
            H(s32, 0xa30) = RandomIntRange(10, 20);
        }
    }
    if (0.0f < H(float, 0xa3c)) H(float, 0xa3c) = 0.0f;
    ApproachValue(&H(float, 0xa3c), -0.0250000022f, 0.000416666677f);
    H(float, 0xf8) = H(float, 0xa3c);
    goto finish;
}



case 0x35: case 0x36:
{
    if (H(u32,0x2294)==0x36) SpawnJitteredParticleAfterDelay(15,30);
    if (H(float,0x174)>0.025000002f) EmitHeroTrailSpark(4,12);
    if (H(u32,0x2294)==0x35 && H(float,0x174)>0.016666668f) EmitHeroSideParticles(0,1);
    if (H(s16,0xA4A)) {
        int count;
        --H(u16,0xA4A);count=(s16)H(u16,0xA4A)>>3;
        if (count>6) count=6;
        EmitHeroRandomizedMotionEffects(count,0,0);
    }
    H(float,0xC20)=0.6f;ResolveStickInputToDirection(0.050000004f, 0);
    if (!FLD(gPadState, int, 0x1D4) && H(float,0x1B0)<0.025000002f) H(float,0x1B0)=0.025000002f;
    SteerHeroHeading(0,0.007f,0.08f,0.087266475f);FastFloatHelperD(HP(0x798));
    if (H(u32,0x2294)==0x35) {
        float speed;
        if (FLD(gPadState, int, 0x1D4) && H(s32,0x798)) H(float,0x1B0)=0.050000004f;
        if (FloatAbs(H(float,0x1A8))>0.78539824f) H(float,0x1B0)=0.0f;
        ApproachHeroSpeed(0.0011111111f,0.0013888889f);
        speed=H(float,0x1B4)*BlendTableEntriesByClock(D_L22_0025FD90,30)*5.5f;
        H(float,0xF0)=FastSinOrCosA(H(float,0x98))*speed;
        H(float,0xF4)=FastSinOrCosB(H(float,0x98))*speed;H(float,0xF8)=0.0f;
    } else {H(float,0x1B4)=0.0f;ClearVector128(HP(0xF0));}
    if (H(u32,0x2294)==0x35 && !H(s32,0xC2C) && H(float,0xC38)>0.0f && H(float,0xC38)<10.0f)
        EmitHeroRandomizedMotionEffects(4,1,0);
    ShrinkHeroVectorByAmount(0.0011666666f);
    SlideHeroAlongWalls(0);UpdateHeroHeightOffset();
    goto finish;
}


case 0x85:
{
    u8 *attached = H(u8 *, 0x1830);
    qcopy(&H(Vec4, 0x80), (Vec4 *)(attached + 0x10));
    qcopy(&H(Vec4, 0x90), (Vec4 *)(attached + 0xf0));
    goto finish;
}



    case 0x86: {
        f32 t;
        FastVecScale(&workspace.mine.s00, &H(Vec, 0x2C0), -1.0f);
        t = 0.0f;
        if (H(float, 0x24B8) > 0.2f) t = -H(float, 0x1FB4) * 0.75f;
        SpringFloatToGoal(&H(float, 0x7C0), &H(float, 0x7C4), t, 0.007f, 0.3f, 0.03f);
        FastVecScale(&workspace.mine.s10, &H(Vec, 0x0), H(float, 0x7C0));
        FastVecAdd(&workspace.mine.s00, &workspace.mine.s00, &workspace.mine.s10);
        vec_scale_to_length(&workspace.mine.s00, &workspace.mine.s00, 1.0f);
        ApplyHeroReferenceTiltRotation(&workspace.mine.s00, &workspace.mine.s30, 0, 0.025f, 0.4f, 0.0f);
        H(float, 0x1B4) = 0.21666668f;
        vec_scale_to_length(&H(Vec, 0xF0), &H(Vec, 0x0), H(float, 0x1B4));
        SetViewSpaceHeight(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.0f);
        ClearVector128(&workspace.mine.s00);
        workspace.mine.s00.f[1] = -H(float, 0x1FB0);
        matrix_mul_vec3(&H(Vec, 0x190), &workspace.mine.s00, &FLD(D_L22_001B9B40, u8, 0x370));
        SteerHeroHeading(0, 0.02f, 0.3f, 0.034906592f);
        goto finish;
    }

    case 0x2F: {
        s32 r = -1;
        s32 z = 0;
        if (H(u8, 0x1492)) BuildHeroMoveImpulse(0.7f, 0.0f);
        else BuildHeroMoveImpulse(0.5f, 0.033333335f);
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ResolveStickInputToDirection(1.0f, 0);
        ApproachHeroSpeed(0.004916667f, 0.004916667f);
        ClearVector128(&H(Vec, 0xF0));
        ShrinkHeroVectorByAmount(0.004916667f);
        if (H(s16, 0x34E)) {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0x110), 0.0069444445f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.015000001f);
        }
        if (r != -1 && H(Moby *, 0x2290)->f42 != 0x36) {
            set_hero_animation(r, 0, (f32)z);
        } else if (H(Moby *, 0x2290)->f60 & 2) {
            if (H(Moby *, 0x2290)->f42 == 0x36) set_hero_animation(GetShopEntryForState(0), 0, 5.0f);
        }
        goto finish;
    }

    case 0x8A: case 0x8B:
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        H(float, 0x1B0) = 0.0f;
        ApproachHeroSpeed(0.004916667f, 0.004916667f);
        ClearVector128(&H(Vec, 0xF0));
        ShrinkHeroVectorByAmount(0.004916667f);
        if (H(s16, 0x34E)) {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0x120), 0.0061111115f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.015000001f);
        }
        if (H(Moby *, 0xB10)) {
            H(float, 0x1A0) = FastMatrixHelperA(H(Moby *, 0xB10)->pos.f[0] - *(float *)(entry_object + 0x10), H(Moby *, 0xB10)->pos.f[1] - *(float *)(entry_object + 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        goto finish;

case 0x23:
{
    TryHeroSurfacePushResponse(3.7f,0.0f,0.35f);
    H(float,0x1B0)=0.0f;
    ApproachHeroSpeed(0.004916667f,0.004916667f);
    ClearVector128(HP(0xF0));
    ShrinkHeroVectorByAmount(0.004916667f);
    if (H(s16,0x34E)) {
        ApplyHeroModeTransform(HP(0xF0),HP(0x120),0.0061111115f);
        CancelHeroVelocityIntoWall();
    } else ApplyHeroModeTransform(HP(0xF0),HP(0xF0),0.015000001f);
    shared_object=H(u8*,0xAA4);
    { if (shared_object != 0) {
        H(float, 0x1a0) = FastMatrixHelperA(*(float *)(shared_object + 0x10) - *(float *)(entry_object + 0x10),
                                     *(float *)(shared_object + 0x14) - *(float *)(entry_object + 0x14));
        SteerHeroHeading(0, 0.0199999996f, 0.150000006f, 0.104719773f);
    } goto finish; }
}


case 0x24:
{

    float bearing,firstRoot,secondRoot;
    qcopy(&workspace.state_24.targetPosition, H(u8*,0xAA4)+0x10);
    H(float,0xAB0)=fast_vec_dist(HP(0x80),&workspace.state_24.targetPosition);
    H(float,0xAAC)=60.0f;
    if (H(float,0xAA0)>0.0f) H(float,0xAAC)=H(float,0xAB0)/H(float,0x170);
    if (H(s32,0x2298)==0) {
        ApproachValue(HP(0xAA0),0.45000002f,0.022222223f);
        bearing=FastMatrixHelperA(*(float*)(H(u8*,0xAA4)+0x10)-*(float*)(entry_object+0x10),
                              *(float*)(H(u8*,0xAA4)+0x14)-*(float*)(entry_object+0x14));
        if (H(s32,0x3A0) && FastDiffRots(H(float,0x98),bearing)>1.5707964f)
            bearing=FastAddRotations(bearing,3.1415927f);
        H(float,0x1A0)=bearing;
        SteerHeroHeading(0,0.03f,0.15f,0.12217307f);
    } else if (H(s32,0x2298)==1) ApproachValue(HP(0xAA0),0.0f,0.011666667f);
    if (SolveQuadratic(&firstRoot,&secondRoot,-0.0058333334f,H(float,0xAA0),1.9f-H(float,0xAB0))>0 && firstRoot>0.0f) {
        H(s32,0x2298)=1;
        H(float,0xAAC)=firstRoot;
    }
    H(u16,0x226)=3;
    if (H(float,0xAAC)<20.0f) H(s32,0xAB4)=1;
    if (H(s32,0xAB4)) StepAngleTowardTarget(HP(0x94),0,0.0f,0.063995413f);
    else {
        float horizontal=vec_distance_xy(HP(0x80),&workspace.state_24.targetPosition);
        bearing=FastMatrixHelperA(horizontal,workspace.state_24.targetPosition.z-H(float,0x88));
        bearing=FastAddRotations(-bearing,1.5707965f);
        StepAngleTowardTarget(HP(0x94),0,bearing,0.10762865f);
    }
    bearing=FastAddRotations(H(float,0x98),-1.5707965f);
    workspace.state_24.offset.x=FastSinOrCosA(bearing)*-0.57f;
    bearing=FastAddRotations(H(float,0x98),-1.5707965f);
    workspace.state_24.offset.y=FastSinOrCosB(bearing)*-0.57f;
    workspace.state_24.offset.z=0.0f;
    FastVecAdd(&workspace.state_24.offset,&workspace.state_24.offset,HP(0x80));
    FastVecSub(&workspace.state_24.desired,H(u8*,0xAA4)+0x10,&workspace.state_24.offset);
    vec_scale_to_length(HP(0xF0),&workspace.state_24.desired,H(float,0xAA0));
    if (H(float,0xAAC)<30.0f) H(float,0xF8)-=(30.0f-H(float,0xAAC))*0.008055556f;
    goto finish;
}


    case 0x25:
        ApproachValue(&H(float, 0xABC), H(float, 0xAC0), 0.16666667f);
        qcopy(&H(Vec, 0xF0), &H(Vec, 0x110));
        FastVecScale(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.9f);
        H(float, 0xF8) -= 0.004166667f;
        qcopy(&workspace.mine.s00, &H(Moby *, 0xAA4)->pos);
        H(float, 0xAB0) = fast_vec_dist(&H(Vec, 0x80), &workspace.mine.s00);
        FastVecAdd(&workspace.mine.s10, &H(Vec, 0x80), &H(Vec, 0xF0));
        FastVecSub(&workspace.mine.s30, &workspace.mine.s10, &workspace.mine.s00);
        vec_scale_to_length(&workspace.mine.s30, &workspace.mine.s30, H(float, 0xABC));
        FastVecAdd(&workspace.mine.s20, &workspace.mine.s00, &workspace.mine.s30);
        FastVecSub(&H(Vec, 0xF0), &workspace.mine.s20, &H(Vec, 0x80));
        goto finish;

    case 0x2B: {
        s32 above;
        f32 vz, yaw;

        if ((H(s32, 0xC28) & 2) && entry_object[0x43] == 0x34) {
            set_hero_animation(0x35, 0xA, 12.0f);
            H(float, 0xC20) = 0.3f;
        }
        vz = H(float, 0xF8);
        if (H(Moby *, 0xAD4) && H(Moby *, 0xAD4)->f68 && *(s32 *)(H(Moby *, 0xAD4)->f68 + 0x34)) {
            yaw = H(Moby *, 0xAD4)->rot.f[2];
            if (FastDiffRots(yaw, H(float, 0x98)) > 90.0f) yaw = FastAddRotations(yaw, 3.1415927f);
            ApproachWithVelocity(&H(float, 0xAEC), yaw, &H(float, 0xAF8), 0.02f, 0.3f, 0.0f, 0);
        }
        H(float, 0x1A0) = H(float, 0xAEC);
        SteerHeroHeading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub(&workspace.mine2b.a, &H(Moby *, 0xAD4)->pos, &H(Vec, 0x80));
        vec_scale_to_length(&workspace.mine2b.a, &workspace.mine2b.a, 1.0f);
        if (workspace.mine2b.a.f[2] < 0.23f) workspace.mine2b.a.f[2] = 0.23f;
        ClearVector128(&workspace.mine2b.e);
        workspace.mine2b.e.f[2] = H(float, 0x98);
        euler_to_matrix(workspace.mine2b.m1, &workspace.mine2b.e);
        matrix_from_basis_rows(workspace.mine2b.m2, workspace.mine2b.m1);
        transform_vector(&workspace.mine2b.a, &workspace.mine2b.a, workspace.mine2b.m2);
        workspace.mine2b.b.f[0] = -FastMatrixHelperA(square_root(workspace.mine2b.a.f[0] * workspace.mine2b.a.f[0] + workspace.mine2b.a.f[2] * workspace.mine2b.a.f[2]), workspace.mine2b.a.f[1]);
        workspace.mine2b.b.f[1] = FastMatrixHelperA(workspace.mine2b.a.f[2], workspace.mine2b.a.f[0]);
        ApproachWithVelocity(&H(float, 0x94), workspace.mine2b.b.f[1], &H(float, 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        ApproachWithVelocity(&H(float, 0x90), workspace.mine2b.b.f[0], &H(float, 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        above = H(float, 0x88) < H(Moby *, 0xAD4)->pos.f[2];

        if (H(s16, 0xADC)) {
            if (above && H(s32, 0x1B8) > 0x28 && H(float, 0x24B8) > 0.25f) {
                f32 push;
                ResolveStickInputToDirection(1.0f, 0);
                push = H(float, 0x24B8) * 0.0035f;
                if (push > 0.083333336f) push = 0.083333336f;
                workspace.mine2b.vB0.f[0] = FastSinOrCosA(H(float, 0x1A0)) * push;
                workspace.mine2b.vB0.f[1] = FastSinOrCosB(H(float, 0x1A0)) * push;
                workspace.mine2b.vB0.f[2] = 0.0f;
                FastVecAdd(&H(Vec, 0xF0), &H(Vec, 0xF0), &workspace.mine2b.vB0);
            }
            if (H(s16, 0xADC)) {
                if (vec_distance_xy(&H(Vec, 0x80), &H(Moby *, 0xAD4)->pos) < H(float, 0xAE0) * 1.57f || H(float, 0x31C) > 1.5f) {
                    ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0x110), 0.011111111f);
                    if (H(s16, 0xAFE) && GetViewSpaceHeight(&H(Vec, 0xF0)) > 0.0f) {
                        FastVecSub(&workspace.mine2b.vB0, &H(Vec, 0x80), &H(Moby *, 0xAD4)->pos);
                        ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.015833333f);
                    }
                }
                {
                f32 drag = FastVecLength(&H(Vec, 0xF0)) * 0.00025f;
                FastVecScale(&workspace.mine2b.vB0, &H(Vec, 0xF0), -1.0f);
                vec_scale_to_length(&workspace.mine2b.vB0, &workspace.mine2b.vB0, drag);
                }
                FastVecAdd(&H(Vec, 0xF0), &H(Vec, 0xF0), &workspace.mine2b.vB0);
            }
        }
        if (H(Moby *, 0xAD4) && H(Moby *, 0xAD4)->f68) {
            f32 *limits = (f32 *)H(Moby *, 0xAD4)->f68;
            f32 sp = FastVecLength(&H(Vec, 0xF0));
            if (limits[3] < sp) {
                ApproachValue(&sp, limits[3], 0.004166667f);

                vec_scale_to_length(&H(Vec, 0xF0), &H(Vec, 0xF0), sp);
            }
        }
        {
        f32 side = FastAddRotations(H(float, 0x98), -1.5707965f);
        workspace.mine2b.vD0.f[0] = FastSinOrCosA(side) * 0.15f;
        workspace.mine2b.vD0.f[1] = FastSinOrCosB(side) * 0.15f;
        }
        workspace.mine2b.vD0.f[2] = 0.0f;
        FastVecAdd(&workspace.mine2b.vD0, &workspace.mine2b.vD0, &H(Vec, 0x80));
        FastVecAdd(&workspace.mine2b.vB0, &workspace.mine2b.vD0, &H(Vec, 0xF0));
        FastVecSub(&workspace.mine2b.vC0, &workspace.mine2b.vB0, &H(Moby *, 0xAD4)->pos);
        vec_scale_to_length(&workspace.mine2b.vC0, &workspace.mine2b.vC0, H(float, 0xAE4));
        FastVecAdd(&workspace.mine2b.vB0, &H(Moby *, 0xAD4)->pos, &workspace.mine2b.vC0);
        FastVecSub(&H(Vec, 0xF0), &workspace.mine2b.vB0, &workspace.mine2b.vD0);
        {
        f32 previous = H(float, 0xAE4), change;
        SpringFloatToGoal(&H(float, 0xAE4), &H(float, 0xAE8), H(float, 0xAE0), H(float, 0xB04), H(float, 0xB08), H(float, 0xB0C));
        change = H(float, 0xAE4) - previous;
        if (H(float, 0xAE4) < FastVecLength(&workspace.mine2b.vC0)) {
            vec_scale_to_length(&workspace.mine2b.vC0, &workspace.mine2b.vC0, change);
            FastVecAdd(&H(Vec, 0x80), &H(Vec, 0x80), &workspace.mine2b.vC0);
        }
        }
        if (H(s16, 0xAFE) && above) {
            f32 target = 0.23333335f;
            f32 sp = vec_length_xy(&H(Vec, 0xF0));
            if (sp < target) {
                SpringFloatToGoal(&sp, &H(float, 0xAF4), target, 0.047f, 0.3f, 0.0f);

                workspace.mine2b.vB0.f[0] = FastSinOrCosA(H(float, 0xAEC)) * H(float, 0xAF4);
                workspace.mine2b.vB0.f[1] = FastSinOrCosB(H(float, 0xAEC)) * H(float, 0xAF4);
                workspace.mine2b.vB0.f[2] = 0.0f;
                FastVecAdd(&H(Vec, 0xF0), &H(Vec, 0xF0), &workspace.mine2b.vB0);
            }
        }
        if (H(s16, 0xADC) && H(s16, 0x34E)) {
            if ((vz < 0.0f && H(float, 0xF8) > 0.0f) || H(s16, 0xAFC)) {
                s32 c;
                f32 s;
                H(s16, 0xAFE) = 0;
                s = square_root(H(float, 0xAE0) / H(float, 0xAF0)) * 3.1415927f;
                if (H(s16, 0xAFC)) {
                    c = H(s16, 0xAFC) == 1;
                } else {
                    workspace.mine2b.vB0.q = H(U128, 0x110);

                    c = GetSpeedAlongHeroForward(&workspace.mine2b.vB0) > 0.0f;
                }
                if (c) {
                    if (entry_object[0x43] != 0x35) {
                        set_hero_animation(0x35, 6, 17.0f);
                        H(s16, 0xAFC) = 1;
                        goto finish;
                    }
                    if (H(Moby *, 0x2290)->f42 == H(Moby *, 0x2290)->f43) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, s, 0.5f, -1.0f);
                        H(s16, 0xAFC) = 0;
                    }
                } else {
                    if (entry_object[0x43] != 0x35) {
                        set_hero_animation(0x35, 0x15, 9.0f);
                        H(s16, 0xAFC) = 2;
                        goto finish;
                    }
                    if (H(Moby *, 0x2290)->f42 == H(Moby *, 0x2290)->f43) {
                        AdjustHeroAnimationSpeedForTargetFrame(12.0f, s, 0.5f, -1.0f);
                        H(s16, 0xAFC) = 0;
                    }
                }
            }
        }
        goto finish;
    }

case 20:
{
    float distance, limit, magnitude;
    int accelerate, settle;
    if (H(int, 0xC2C) || H(float, 0xC38) < (float)D_L22_0025FA10[H(s16, 0xBFC)].f[6]) H(u8, 0x1239) = 2;
    H(float, 0x1B0) = 0.0f;
    if (H(u8, 0x1492)) {
        if (H(void *, 0xBE4)) {
            float range = vec_distance_xy(HP(0x80), H(u8 *, 0xBE4) + 16);
            int boost = H(u8, 0x1496) || H(u8, 0x149B) || H(u8, 0x1495);
            if ((range > 2.0f && range < 5.0f) || boost) H(float, 0x1B0) = 0.075f;
            ApproachHeroSpeed(0.0011111111f, 0.0011111111f);
            H(float, 0xF0) = FastSinOrCosA(H(float, 0x98)) * H(float, 0x1B4);
            H(float, 0xF4) = FastSinOrCosB(H(float, 0x98)) * H(float, 0x1B4);
        } else {
            ApproachHeroSpeed(0.00055555557f, 0.00055555557f);
            SetViewSpaceVectorLength(HP(0xF0), HP(0xF0), H(float, 0x1B4));
        }
    } else {
        accelerate = (H(u64, 0x1490) & 0x00FFFF0000000000ULL) || H(u8, 0x149B) || H(float, 0x31C) > 4.0f;
        if (H(void *, 0xBE4)) {
            FastVecSub(&workspace.state_14.delta, H(u8 *, 0xBE4) + 16, HP(0x80));
            distance = GetViewSpaceVectorLength(&workspace.state_14.delta);
            if ((distance > 2.0f && distance < 5.0f) || accelerate) H(float, 0x1B0) = 0.075f;
            ApproachHeroSpeed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length(&workspace.state_14.u.movement, HP(0x0), H(float, 0x1B4));
            SetViewSpaceVectorLength(HP(0xF0), HP(0xF0), 0.0f);
            FastVecAdd(HP(0xF0), HP(0xF0), &workspace.state_14.u.movement);
        } else {
            if (accelerate && H(int, 0x1B8) < 70) H(float, 0x1B0) = 0.075f;
            ApproachHeroSpeed(0.004166667f, 0.004166667f);
            SetViewSpaceVectorLength(HP(0xF0), HP(0xF0), H(float, 0x1B4));
        }
    }
    if (H(int, 0xBE8) || H(void *, 0xBE4)) {
        H(float, 0x1A0) = H(float, 0xBEC);
        qcopy(&H(Vec4, 0x190), &H(Vec4, 0xBC0));
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
    } else if (H(float, 0xC38) < 25.0f) SelectHeroAimTarget(8.0f, 1.0471977f, 1.0471977f);
    limit = 0.12833333f;
    if (H(float, 0x31C) > 2.25f) limit = 0.064166665f;
    else if (H(float, 0x31C) > 1.8f) limit = 0.0898333266f;
    if (!H(int, 0xC2C) && H(float, 0xC38) > 23.5f && H(float, 0x118) < 0.0f && H(s16, 0x34E)) {


        qcopy(&workspace.state_14.delta, &H(Vec4, 0x80));
        ApplyHeroModeTransformReversed(&workspace.state_14.delta, &workspace.state_14.delta, -0.5f);
        vec_scale_to_length(&workspace.state_14.force, HP(0x0), 2.0f);
        make_hit_descriptor(workspace.state_14.u.contact, H(void *, 0x2290), 0x10000, 2.0f, &workspace.state_14.force);
        *(float *)(workspace.state_14.u.contact + 12) = 5627.9248f;
        workspace.state_14.u.contact[24] = 0;
        workspace.state_14.u.contact[25] = 1;
        *(u16 *)(workspace.state_14.u.contact + 26) = 71;
        ProcessCollisionHit(&workspace.state_14.delta, 0x10, 0.4f, H(void *, 0x2290), workspace.state_14.u.contact);
    }
    if (IsBelowPlaneWithinDepth(25.7f)) {
        QueueRecordsByIndex(25);
        H(u16, 0x1FA) = 50;
        if (D_001A7B2A) {
            FLD(D_L22_001B9B40, float, 0x180) = 0.1f;
            FLD(D_L22_001B9B40, int, 0x188) = 30;
            H(u16, 0x224) = 35;
            FLD(D_L22_001B9B40, int, 0x16C) = 0;
        }
    }
    settle = 14;
    if (H(int, 0x1B8) < 9) {
        magnitude = GetViewSpaceHeight(HP(0xF0));
        ApproachValue(&magnitude, limit, 0.041666668f);
        SetViewSpaceHeight(HP(0xF0), HP(0xF0), magnitude);
    } else if (H(int, 0x1B8) > settle) {
        float speed;
        ApplyHeroModeTransform(HP(0xF0), HP(0xF0), 0.036111113f);
        if (GetViewSpaceHeight(HP(0xF0)) < 0.0f) H(float, 0xC00) = 1.0f;
        shared_speed = -0.6166667f;
        if (D_L22_001A8FF0) shared_speed = -1.1666667f;
        if (GetViewSpaceHeight(HP(0xF0)) < shared_speed) SetViewSpaceHeight(HP(0xF0), HP(0xF0), shared_speed);
    }
    goto finish;

}


case 21: case 131:
{
    float angle, correction, speed, heading;
    int steer, locked;
    H(float, 0x1B0) = 0.0f;
    if (H(int, 0xC2C) || H(float, 0xC38) < (float)D_L22_0025FA10[H(s16, 0xBFC)].f[6]) H(u8, 0x1239) = 2;
    locked = H(int, 0x22A0) == 1 && H(int, 0x22A8) >= 21;
    if (!locked) {
        if (H(int, 0xBE8) || H(void *, 0xBE4)) {
            int sharp = 0;
            if (H(u8, 0x22C3)) {
                angle = GetDirectionAngleDelta(HP(0xBC0), 0);
                correction = GetDirectionAngleDelta(HP(0xBC0), 1);
            } else {
                angle = fast_subtract_rotations(H(float, 0xBEC), H(float, 0x98));
                correction = GetShortestAngleDelta(H(float, 0xBEC), 1, H(float, 0x98));
            }
            if (correction < 4.3633237f) sharp = 1;

            if (angle > 0.0f) H(float, 0xC20) = 1.0f / (correction + 1.0f);
            H(float, 0x1A0) = H(float, 0xBEC);
            qcopy(&H(Vec4, 0x190), &H(Vec4, 0xBC0));
            if (sharp) SteerHeroHeading(1, 0.057f, 0.2f, 0.2821616f);
            else SteerHeroHeading(0, 0.057f, 0.2f, 0.2821616f);

        } else {
            steer = 1;
            if (H(u32, 0x2294) == 131 && H(int, 0x1B8) > 11) steer = 0;
            else if (!H(int, 0xC2C) && H(float, 0xC38) > 6.0f) steer = 0;
            if (steer) {
                if (H(u32, 0x2294) == 21) SelectHeroAimTarget(14.0f, 0.52359885f, 0.78539824f);
                else UpdateHeroAimTarget(64.0f, 0.17453295f, 0.3490659f);
            }
        }
    }
    if (!H(int, 0xC2C) && H(u8 *, 0x2290)[0x43] == 26 && IsBelowPlaneWithinDepth(33.0f)) {
        if (H(u8, 0x1492) && H(float, 0x170) < 0.033333335f) {
            H(float, 0xF0) += FastSinOrCosA(H(float, 0x98)) * 0.021666666f;
            H(float, 0xF4) += FastSinOrCosB(H(float, 0x98)) * 0.021666666f;
            qcopy(&H(Vec4, 0x140), &H(Vec4, 0xF0));
        }
        if (H(u32, 0x2294) == 21) SetupHeroAttachedObjectTransform();
    }
    if (H(u8, 0x1492)) {
        if (IsBelowPlaneWithinDepth(84.0f)) {
            speed = 0.041666668f;
            heading = FastAddRotations(H(float, 0x98), 3.1415927f);
            if (D_00138320 & 8) speed = 0.050000004f;
            H(float, 0xF0) += FastSinOrCosA(heading) * speed;
            H(float, 0xF4) += FastSinOrCosB(heading) * speed;
            qcopy(&H(Vec4, 0x140), &H(Vec4, 0xF0));
        }
        { SteerHeroReferencePoint(); goto finish; }
    }
    ApproachHeroSpeed(0.010277778f, 0.007777778f);
    ComputeHeroPushDirection(99999.0f);
    if (H(s16, 0x34E)) {
        ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f);
    } else ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}


case 19:
{
    unsigned char *animation;
    int steer;
    float distance, excess, scaled, radius, limit, angle, magnitude, rate, offset;
    if (H(int, 0xC2C) || H(float, 0xC38) < (float)D_L22_0025FA10[H(s16, 0xBFC)].f[8]) H(u8, 0x1239) = 2;
    if (H(u8, 0x1492)) { SteerHeroReferencePoint(); goto finish; }
    animation = (unsigned char *)&D_L22_0025FA10[H(s16, 0xBFC)];
    H(float, 0x1B0) = 0.0f;
    if (H(void *, 0xBE4) && H(int, 0x1B8) < 4) {
        distance = vec_distance_xy(H(u8 *, 0xBE4) + 16, HP(0x80));
        if (D_L22_001A8FF0) distance = fast_vec_dist(H(u8 *, 0xBE4) + 16, HP(0x80));
        distance -= 0.5f;
        if (distance < 0.0f) distance = 0.0f;
        if (*(int *)(animation + 4) == 0) { offset = 0.75f; radius = 0.8f; limit = 4.0f; }
        else if (*(int *)(animation + 4) == 1) { offset = 0.6f; radius = 1.7f; limit = 4.0f; }
        else { offset = 1.3f; radius = 1.7f; limit = 1.9f; }
        excess = distance - offset;
        if (FloatAbs(excess) < radius + 3.0f) {
            scaled = excess * 1.1111112f;
            if (scaled > limit) scaled = limit;
            if (scaled > 1.0f) H(float, 0xBF4) = scaled;
        }
    }
    switch (*(int *)(animation + 4)) {
    case 0:
        if (H(float, 0xC38) < 18.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.07333334f;
        break;
    case 1:
        if (H(int, 0xC2C) || H(float, 0xC38) < 9.0f) {
            if (H(float, 0xC38) > 8.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.050000004f;
            else if (H(float, 0xC38) > 7.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.075f;
            else H(float, 0x1B0) = H(float, 0xBF4) * 0.095f;
        }
        break;
    case 2:
        if (H(int, 0xC2C) || H(float, 0xC38) < 12.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.06166667f;
        break;
    }
    ApproachValue(HP(0xC20), 1.0f, 0.2f);
    if (H(int, 0xBE8) || H(void *, 0xBE4)) {
        if (H(u8, 0x22C3)) angle = GetDirectionAngleDelta(HP(0xBC0), 0);
        else angle = fast_subtract_rotations(H(float, 0xBEC), H(float, 0x98));
        magnitude = FloatAbs(angle);
        if (*(int *)(animation + 4) == 1 && angle > 0.0f) H(float, 0xC20) = 1.0f / (magnitude + 1.0f);
        H(float, 0x1A0) = H(float, 0xBEC);
        qcopy(&H(Vec4, 0x190), &H(Vec4, 0xBC0));
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        steer = 1;
        if (*(int *)(animation + 4) == 1 && !H(int, 0xC2C) && H(float, 0xC38) > 7.0f) steer = 0;
        if (steer) SelectHeroAimTarget(5.0f, 0.78539824f, 0.78539824f);
    }
    ApproachHeroSpeed(0.010277778f, 0.007777778f);
    if (H(int, 0xBE8)) {
        if (H(u8, 0x22C3)) SetHeroPushDirection(HP(0xBC0));
        else ComputeHeroPushDirection(H(float, 0xBEC));
    } else ComputeHeroPushDirection(99999.0f);
    if (H(s16, 0x34E)) ApplyHeroModeTransform(HP(0xF0), HP(0x130), 0.0069444445f);
    else ApplyHeroModeTransform(HP(0xF0), HP(0xF0), 0.015000001f);
    TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
    goto finish;
}


case 0x77:
    ApproachValue(&H(float, 0x1b4), 0.0f, 0.00666666683f);
    if (D_L22_001A8FF0) {
        vec_scale_to_length(&H(Vec4, 0xf0), &H(Vec4, 0xbd0), H(float, 0x1b4));
        if (0.0f < H(float, 0x31c))
            ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f);
        else SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0f);
        FastVecScale(&H(Vec4, 0x190), &H(Vec4, 0xbd0), -1.0f);
    } else {
        H(float, 0xf0) = FastSinOrCosA(H(float, 0xbf0)) * H(float, 0x1b4);
        H(float, 0xf4) = FastSinOrCosB(H(float, 0xbf0)) * H(float, 0x1b4);
        if (0.0f < H(float, 0x31c)) H(float, 0xf8) = H(float, 0x128) - 0.0069444445f;
        else H(float, 0xf8) = 0.0f;
        H(float, 0x1a0) = FastAddRotations(H(float, 0xbf0), 3.14159274f);
    }
    SteerHeroHeading(0, 0.0500000007f, 0.200000003f, 0.282161593f);
    goto finish;



case 0x1F:
{
    s32 start, fade, mode;
    if (H(s32,0xBE8) || H(s32,0xBE4)) {
        H(float,0x1A0)=H(float,0xBEC);
        SteerHeroHeading(0,0.05f,0.2f,0.28216159f);
    } else if (H(s32,0x1B8)<4) SelectHeroAimTarget(11.0f,0.87266469f,-1.0f);
    H(float,0x1B0)=0.0f;
    start = 10;
    fade = 18;
    if (H(s32,0x1B8)>start && H(s32,0x1B8)<18) H(float,0x1B0)=0.3f;
    if (H(s32,0x1B8)==8 && H(float,0x184)<0.33333334f) {
        InitPendingSlot(H(void*,0x2290),HP(0x18E0));
        AppendRecordToFourEntryTable(HP(0x18E0),48,2,0.0f);
        AppendRecordToFourEntryTable(HP(0x18E0),23,4,0.0f);
        AppendRecordToFourEntryTable(HP(0x18E0),12,6,0.0f);
    }
    mode = H(s32,0x1B8)>fade?5:0;
    UpdateTransformHistoryFollowers(HP(0x18E0),mode);
    if (H(u8,0x1492)) {
        if (H(s32,0x1B8)>start && H(s32,0x1B8)<17 && H(float,0x178)<0.14166668f) {
            H(float,0xF0)+=FastSinOrCosA(H(float,0x98))*0.020000001f;
            H(float,0xF4)+=FastSinOrCosB(H(float,0x98))*0.020000001f;
            qcopy(&H(Vec4,0x140), &H(Vec4,0xF0));
        }
        SteerHeroReferencePoint();
    } else {
        if (H(s32,0x1B8)>start) ApproachHeroSpeed(0.052777778f,0.025f);
        if (H(s32,0xBE8)) ComputeHeroPushDirection(H(float,0xBEC));
        else ComputeHeroPushDirection(99999.0f);
    }
    {
        u8 *target;
        if (H(u32,0x2294)==0x1F && H(s32,0x1B8)>start && H(s32,0x1B8)<22 && (target=H(u8*,0x1220))) {


            float angle;
            int hit;
            workspace.state_1f.impulse.x=FastSinOrCosA(H(float,0x98))*2.0f;
            workspace.state_1f.impulse.y=FastSinOrCosB(H(float,0x98))*2.0f;
            workspace.state_1f.impulse.z=1.3f;
            make_hit_descriptor(workspace.state_1f.query,H(void*,0x2290),0x30000,3.0f,&workspace.state_1f.impulse);
            *(float*)(workspace.state_1f.query+12)=5627.9248f;
            workspace.state_1f.query[25]=3;
            workspace.state_1f.query[24]=0;
            angle=H(float,0x98);
            *(u16*)(workspace.state_1f.query+26)=*(u16*)(target+0xAA);
            workspace.state_1f.point.x=FastSinOrCosA(angle)*0.8f;
            workspace.state_1f.point.y=FastSinOrCosB(angle)*0.8f;
            workspace.state_1f.point.z=0.55f;
            FastVecAdd(&workspace.state_1f.point,&workspace.state_1f.point,HP(0x80));
            hit=ProcessCollisionHit(&workspace.state_1f.point,0,0.8f,target,workspace.state_1f.query);
            EmitEffectsAtNearbyObjects(target,hit);
            angle=FastAddRotations(H(float,0x98),-0.87266469f);
            workspace.state_1f.point.x=FastSinOrCosA(angle)*0.8f;
            workspace.state_1f.point.y=FastSinOrCosB(angle)*0.8f;
            workspace.state_1f.point.z=0.55f;
            FastVecAdd(&workspace.state_1f.point,&workspace.state_1f.point,HP(0x80));
            hit=ProcessCollisionHit(&workspace.state_1f.point,0,0.8f,H(void*,0x2290),workspace.state_1f.query);
            EmitEffectsAtNearbyObjects(target,hit);
            angle=FastAddRotations(H(float,0x98),0.87266469f);
            workspace.state_1f.point.x=FastSinOrCosA(angle)*0.8f;
            workspace.state_1f.point.y=FastSinOrCosB(angle)*0.8f;
            workspace.state_1f.point.z=0.55f;
            FastVecAdd(&workspace.state_1f.point,&workspace.state_1f.point,HP(0x80));
            hit=ProcessCollisionHit(&workspace.state_1f.point,0,0.8f,target,workspace.state_1f.query);
            EmitEffectsAtNearbyObjects(target,hit);
        }
    }
    if (H(s32,0x1B8)>10) TryHeroSurfacePushResponse(3.7f,0.0f,0.35f);
    SlideHeroAlongWalls(1);
    if (H(s16,0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), HP(0x120), 0.0061111115f); CancelHeroVelocityIntoWall(); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;
}


case 0x22:
{
    H(float,0x1B0)=0.0f;
    if (H(s32,0xBE8)) {
        H(float,0x1A0)=H(float,0xBEC);
        qcopy(&H(Vec4,0x190), &H(Vec4,0xBC0));
        SteerHeroHeading(0,0.04f,0.2f,0.28216159f);
    } else SelectHeroAimTarget(11.0f,0.87266469f,-1.0f);
    ApproachHeroSpeed(0.008333334f,0.009722223f);
    ComputeHeroPushDirection(99999.0f);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x110), 0.015000001f); CancelHeroVelocityIntoWall(); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;
}


    case 2: case 0x70: {
        s32 c = 0;
        f32 k, lim, m, heading;
        if (H(u8, 0x1494) && H(float, 0x24C4) < 0.25f) c = 1;
        if (H(u8, 0x22B9) || c) {
            if (H(float, 0x174) > 0.016666668f) EmitHeroSideParticles(0, 2);
            if (H(float, 0x174) > 0.008333334f) EmitHeroTrailSpark(2, 4);
            EmitHeroRandomizedMotionEffects(5, 2, 0);
        }
        if (H(s16, 0x1454) == 0) {
            if (H(float, 0x174) < 0.028333336f) {
                H(u8, 0x40C) = 1;
                if (FloatAbs(H(float, 0x1A8)) > 2.0943954f && H(float, 0x24B8) == 1.0f) H(u8, 0x40F) = 1;
            }
            heading = ReadPadFloatHistory(1);
            if (FastDiffRots(heading, ReadPadFloatHistory(7)) > 1.9198624f && FloatAbs(H(float, 0x1A8)) > 1.2217306f && H(float, 0x24B8) == 1.0f) {
                H(u8, 0x40F) = 1;
                H(u8, 0x40C) = 1;
            }
            if (FloatAbs(H(float, 0x1A8)) < 0.087266475f) H(u8, 0x40C) = 0;
        }
        if (H(u8, 0x40F) && FloatAbs(H(float, 0x1A8)) < 0.06981318f) H(u8, 0x40F) = 0;
        if (H(float, 0x24B8) < 0.2f) {
            if (H(s32, 0x410)) H(u8, 0x40F) = 1;
            H(float, 0x1B0) = 0.0f;
            qcopy(&H(Vec, 0x190), &H(Vec, 0x3F0));
            H(float, 0x1A0) = H(float, 0x408);
        } else {
            UpdateHeroTargetSpeed();
            if (hero_slot_item_id(0) == 10 && (H(float, 0x24BC) == 1.0f || H(s32, 0x410)) && !H(u8, 0x22BA)) {
                qcopy(&H(Vec, 0x3F0), &H(Vec, 0x190));
                H(s32, 0x410) = 1;
                H(float, 0x408) = H(float, 0x1A0);
            } else {
                qcopy(&H(Vec, 0x3F0), &H(Vec, 0x0));
                H(float, 0x408) = H(float, 0x98);
            }
        }
        if (H(float, 0xA70) > 0.0f) {
            Vec *impulse = &H(Vec, 0xA60);
            BuildHeroMoveImpulse(0.7f, 0.0f);
            workspace.mine.s00.q = impulse->q;
            H(float, 0x1B0) += GetSpeedAlongHeroForward(&workspace.mine.s00);
            if (H(float, 0x1B0) < 0.011666667f) H(float, 0x1B0) = 0.011666667f;
            ClearVector128(impulse);

        }
        k = 1.0f;
        if (H(s16, 0x1454)) {
            UpdateHeroTurnFromAnimation();
        } else {
            H(float, 0x1458) = H(float, 0x98);
            qcopy(&H(Vec, 0x1440), &H(Vec, 0x0));
            if (H(s32, 0x2298) == 1 && !H(u8, 0x40F) && !H(u8, 0x22BA)) {
                SteerHeroHeading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                f32 turn = FloatAbs(H(float, 0x1A8));
                if ((H(float, 0x24B8) < 0.9f || (H(u8, 0x22BA) && !H(u8, 0x40F))) && turn > 0.78539824f) k = 0.0f;
                SetHeroTurnRates();
            }
        }
        ApplyHeroModePoseOffsets();
        UpdateHeroLeanAndSwayParameters();
        if (H(u8, 0x40F)) {
            f32 cap = 0.09916667f - FloatAbs(H(float, 0x1A8)) * 0.029178405f;
            if (cap < 0.0f) cap = 0.0f;
            if (cap < H(float, 0x1B0)) H(float, 0x1B0) = cap;
        }
        m = k * 0.005f;
        lim = 0.0055555557f;
        if (H(u8, 0x40F)) {
            f32 scale = 2.617994f - H(float, 0x1A8);
            if (scale > 1.0f) scale = 1.0f;
            if (scale < 0.2f) scale = 0.2f;
            H(float, 0x1B0) *= scale;
            lim = 0.004722222f;
        }
        {
        f32 angle = FloatAbs(H(float, 0x1A8));
        if (H(float, 0x24B8) < 0.75f && angle > 0.6108653f) {
            f32 slow = 1.0f - angle * 0.4f;
            if (slow < 0.0f) slow = 0.0f;
            H(float, 0x1B0) *= slow;
        }
        }
        ApproachHeroSpeed(m, lim);
        if (H(u8, 0x40C) || H(s16, 0x1454)) {
            if (!H(u8, 0x22C3)) {
                if (H(s16, 0x1454)) ComputeHeroPushDirection(H(float, 0x1458));
                else ComputeHeroPushDirection(H(float, 0x1A0));
            } else {
                if (H(s16, 0x1454)) SetHeroPushDirection(&H(Vec, 0x1440));
                else SetHeroPushDirection(&H(Vec, 0x190));
            }
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        SlideHeroAlongWalls(1);
        if (H(s16, 0x214)) TryHeroSurfacePushResponse(5.0f, 0.2f, 0.35f);
        if (H(s16, 0x34E)) {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0x130), 0.0069444445f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.015000001f);
        }
        goto finish;
    }

case 0x7b:
{

    float turn, shape;
    s32 hits, i;
    UpdateSoundSlotObject(4, H(u8 *, 0x2290), 13);
    ResolveStickInputToDirection(1.0f, 0);
    H(float, 0x1b0) = 0.191666678f;
    ClampStickToUnitRange(&workspace.state_7b.local, &H(Vec4, 0x9f0), 0.170000002f);
    { float t = workspace.state_7b.local.x * 0.0203621779f; turn = H(float, 0x24b8) * t; }
    if (D_L22_001A8FF0 == 0 && H(s32, 0x1b8) < 60) {
        turn = turn * 0.100000001f;
        H(float, 0x1b0) = 0.5f;
    }
    if (0.200000003f < H(float, 0x24b8)) RotateHeroMatrix(0.0f, 0.0f, turn);
    ApproachHeroSpeed(0.027777778f, 0.00416666688f);
    ComputeHeroPushDirection(99999.0f);
    if (D_L22_001A8FF0) {
        qcopy(&workspace.state_7b.target_position, &H(Vec4, 0x2d0));
        ApplyHeroModeTransformReversed(&workspace.state_7b.target_position, &workspace.state_7b.target_position, 0.170000002f);
        SpringVectorToTarget(&H(Vec4, 0x80), &workspace.state_7b.target_position, &H(float, 0xa00),
                     0.0399999991f, 0.300000012f, 0.125f);
    } else {
        SpringFloatToGoal(&H(float, 0x88), &H(float, 0xa00), H(float, 0x318) + 0.170000002f,
                     0.0399999991f, 0.300000012f, 0.125f);
    }
    FastVecScale(&workspace.state_7b.target_position, &H(Vec4, 0x110), 3.0f);
    FastVecAdd(&workspace.state_7b.target_position, &workspace.state_7b.target_position, &H(Vec4, 0xe0));
    hits = ProcessCollisionHit(&workspace.state_7b.target_position, 0, 0.569999993f, H(u8 *, 0x2290), 0);
    if (hits != 0) {
        FastVecScale(&workspace.state_7b.impulse, &H(Vec4, 0x110), 7.0f);
        for (i = 0; i < hits; ++i) {
            if (IsMobyInSpecialClassRange(D_L22_001C4140[i]) != 0)
                QueueImpactEffect(D_L22_001C4140[i], H(u8 *, 0x2290), 0x10000,
                             &H(Vec4, 0x80), &workspace.state_7b.impulse, 1.0f);
        }
    }
    SetCameraLimitsSlot0(0.0170000009f, 0.300000012f);
    SetCameraLimitsSlot2(0.0250000004f, 0.300000012f);
    SetCameraLimitsSlot3(0.0299999993f, 0.270000011f);
    shape = turn * 27.0f;
    if (1.70000005f < shape) shape = 1.70000005f;
    else if (shape < -1.70000005f) shape = -1.70000005f;
    FLD(D_L22_0025DE90, float, 0x60) = -shape;
    FLD(D_L22_0025DE90, float, 0x278) = shape * 0.5f;
    FLD(D_L22_0025DE90, float, 0x1C8) = shape * 0.5f;
    goto finish;
}



    case 0x2E:
        SteerHeroReferencePoint();
        SetCameraLimitsSlot0(0.04f, 0.2f);
        SetCameraLimitsSlot1(0.04f, 0.2f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        if (entry_object[0x43] == 0x37) {
            f32 t = H(float, 0x1A8);
            if (t > 1.4f) t = 1.4f;
            else if (t < -1.4f) t = -1.4f;
            FLD(D_L22_0025DE90, float, 0x60) = t * -0.14f;
            FLD(D_L22_0025DE90, float, 0x118) = t * 0.3f;
            FLD(D_L22_0025DE90, float, 0x1C0) = t * -0.22f;
            FLD(D_L22_0025DE90, float, 0x278) = t * 0.4f;
            FLD(D_L22_0025DE90, float, 0x274) = FloatAbs(t) * -0.09f;
            FLD(D_L22_0025DE90, float, 0x270) = FloatAbs(t) * 0.08f;
        } else if (entry_object[0x43] == 0x66) {
            f32 dir = FastAddRotations(fast_subtract_rotations(FastMatrixHelperA(H(float, 0x110), H(float, 0x114)), H(float, 0x98)), 3.1415927f);
            f32 k = H(float, 0x174) * 6.9813175f;
            if (k > 0.43633235f) k = 0.43633235f;
            {
            f32 forward = FastSinOrCosA(dir) * k;
            f32 side = -FastSinOrCosB(dir) * k;
            FLD(D_L22_0025DE90, float, 0x114) = forward;
            FLD(D_L22_0025DE90, float, 0x110) = side;
            }
        }
        if (H(s16, 0x34E)) {
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0x110), 0.0069444445f);
        } else {
            H(float, 0xF8) = 0.0f;
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.041666668f);
        }
        goto finish;

    case 0x30: {
        f32 prev, d, t;
        if (gCurrentMapIndex == 0) UpdateSoundSlotObject(2, H(Moby *, 0x2290), 0x13);
        else if (gCurrentMapIndex != 1) UpdateSoundSlotObject(2, H(Moby *, 0x2290), 6);
        if ((u32)gCurrentMapIndex < 2) {
            EmitHeroRandomizedMotionEffects(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects(4, 2, 0);
            workspace.mine.s00.f[0] = H(float, 0x80) + RandomFloatRange(-0.25f, 0.25f);
            workspace.mine.s00.f[1] = H(float, 0x84) + RandomFloatRange(-0.25f, 0.25f);
            workspace.mine.s00.f[2] = H(float, 0x88) + RandomFloatRange(-0.1f, 0.4f);
            FastVecScale(&workspace.mine.s10, &H(Vec, 0x110), 0.9f);
            workspace.mine.s10.f[0] += RandomFloatRange(-0.011666667f, 0.011666667f);
            workspace.mine.s10.f[1] += RandomFloatRange(-0.011666667f, 0.011666667f);
            workspace.mine.s10.f[2] += RandomFloatRange(0.016666668f, 0.033333335f);
            SpawnTwoPointEffect(&workspace.mine.s00, &workspace.mine.s10, RandomFloatRange(37800.0f, 75600.0f));
        }
        H(float, 0x1A0) = H(float, 0xB40);
        prev = H(float, 0x98);
        SteerHeroHeading(0, 0.033f, 0.3f, 0.069813184f);
        d = FastDiffRots(H(float, 0x98), prev);
        ClearVector128(&H(Vec, 0xF0));
        ShrinkHeroVectorByAmount(0.0019444445f);
        H(float, 0xF8) = H(float, 0x118) - 0.013888889f;
        if (H(float, 0xF8) > -0.011111111f) H(float, 0xF8) = -0.011111111f;
        if (d > 0.023271061f) d = 0.023271061f;
        t = d * 9.0f;
        ApproachWithVelocity(&H(float, 0x90), t * 0.5f, &H(float, 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        ApproachWithVelocity(&H(float, 0x94), -H(float, 0xB44), &H(float, 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        SetCameraLimitsSlot1(0.009f, 0.22f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        FLD(D_L22_0025DE90, float, 0x118) = t * 2.1f;
        FLD(D_L22_0025DE90, float, 0x110) = t * 3.5f;
        goto finish;
    }

case 0x27: case 0x28: case 0x29: case 0x2A: case 0x3E:
{

    int typeAllowsPose,poseAvailable,heightJump,configuration;
    if ((u32)(H(u32,0x2294)-0x28)>=2U && H(u32,0x2294)!=0x3E) UpdateSoundSlotObject(0,H(void*,0x2290),0);
    else {
        int slot=H(s32,0x242C);
        if (slot!=-1 && FLD(gSoundState+slot*0x70, void *, 0x88)==H(void*,0x2290) &&
            FLD(gSoundState+slot*0x70, u8, 0x74)) StopSoundVoice(slot);
        H(s32,0x242C)=-1;
    }
    if (H(u32,0x2294)==0x27 || H(u32,0x2294)==0x2A) {

        float angle;
        float magnitude;
        qcopy(&workspace.state_27.first, &H(Vec4,0x80));
        angle=RandomSignedFloatRange(0.0f,0.52359885f);
        angle=FastAddRotations(H(float,0x64C),angle);
        magnitude=RandomFloatRange(0.06666667f,0.116666675f);
        workspace.state_27.second.x=FastSinOrCosA(angle)*magnitude;
        workspace.state_27.second.y=FastSinOrCosB(angle)*magnitude;
        workspace.state_27.second.z=0.0f;
        workspace.state_27.second.z=RandomFloatRange(0.050000004f,0.083333336f);
        workspace.state_27.second.w=-0.008333334f;
        SpawnWhiteFlashParticle(&workspace.state_27.first,&workspace.state_27.second,0,-1.0f);
    }
    configuration=FLD(D_L22_002645F0+gItemSlotToRecord[H(s32,0x1248)]*0xE0, s32, 0x1C);
    typeAllowsPose=configuration!=0;
    if (H(s32,0x1248)==13) typeAllowsPose=0;
    poseAvailable=0;
    if (typeAllowsPose) poseAvailable=H(u8,0x22BA)!=0;
    find_nearest_path_point(H(void*,0x630),HP(0x80),HP(0x5D0),HP(0x634),HP(0x638),H(s32,0x654),999.0f,2.0f,2.5f);
    if (H(s32,0x660))
        find_nearest_path_point(H(void*,0x664),HP(0x80),HP(0x610),HP(0x668),HP(0x66C),H(s32,0x670),999.0f,2.0f,2.5f);
    heightJump=0;
    if (H(float,0x31C)>1.0699999f && H(u32,0x2294)!=0x28 && H(u32,0x2294)!=0x3E && !H(s32,0x660))
        heightJump=H(s32,0x1BC)>30;
    if (heightJump) ++H(s32,0x6C8); else H(s32,0x6C8)=0;
    if ((H(s32,0x640) && ++H(s32,0x640)) || heightJump) {
        qcopy(&H(Vec4,0xF0), &H(Vec4,0x120));
        if ((u32)(H(u32,0x2294)-0x28)<2U) { ApplyHeroGravityAndJumpMotion();goto finish; }
        H(float,0xF8)-=0.0061111115f;

        goto finish;
    } else {
        float pathStep=(float)H(s32,0x648);
        float pathSpeed=H(float,0x644)*pathStep;
        if (H(u32,0x2294)==0x3E) pathSpeed=H(float,0x69C)*pathStep;
        Spline_AdvanceByDistance(H(void*,0x630),&workspace.state_27.first,HP(0x634),HP(0x638),pathSpeed,H(s32,0x654));
        if (H(s32,0x660))
            Spline_AdvanceByDistance(H(void*,0x664),&workspace.state_27.second,HP(0x668),HP(0x66C),pathSpeed,H(s32,0x670));
        if (H(s32,0x1BC)>90) {
            int segment,hitA,hitB;
            float weight,heading;
            pathSpeed=H(float,0x170);pathSpeed*=30.0f;
            qcopy(&workspace.state_27.u.p.probeA, &H(Vec4,0x80));
            segment=H(s32,0x634);weight=H(float,0x638);
            hitA=Spline_AdvanceByDistance(H(void*,0x630),&workspace.state_27.u.p.probeA,&segment,&weight,pathSpeed,H(s32,0x654));
            qcopy(&workspace.state_27.u.p.probeB, &H(Vec4,0x80));
            segment=H(s32,0x634);weight=H(float,0x638);
            hitB=Spline_AdvanceByDistance(H(void*,0x630),&workspace.state_27.u.p.probeB,&segment,&weight,pathSpeed+0.1f,H(s32,0x654));
            if ((!(hitA | hitB) || H(s32,0x654)) && H(u32,0x2294)==0x27) {
                heading=FastMatrixHelperA(workspace.state_27.u.p.probeB.x-workspace.state_27.u.p.probeA.x,workspace.state_27.u.p.probeB.y-workspace.state_27.u.p.probeA.y);
                heading=fast_subtract_rotations(H(float,0x64C),heading)*0.47f;
                if (heading>0.78539824f) heading=0.78539824f;
                if (heading< -0.78539824f) heading=-0.78539824f;
                SetCameraLimitsSlot0(0.03f,0.2f);
                if (H(s32,0x65C)) FLD(D_L22_0025DE90, float, 0x64)=-heading;
                else FLD(D_L22_0025DE90, float, 0x64)=heading;
            }
        }
        if (H(u32,0x2294)!=0x28 && H(u32,0x2294)!=0x3E && H(u32,0x2294)!=0x29) {
            float horizontal=vec_length_xy(HP(0x110));
            FLD(D_L22_0025DE90, float, 0x60)=FastMatrixHelperA(horizontal,H(float,0x118));
        }
        if (typeAllowsPose) {
            u8 *pose_hero=gHeroState;
            float poseScale=0.3f;
            SetCameraLimitsSlot3(0.017f,0.3f);
            SetCameraLimitsSlot1(0.027f,poseScale);
            SetCameraLimitsSlot2(0.027f,poseScale);
            if (FLD(pose_hero,void*,0x6A8)) {
                float angle,sideScale;
                FastVecSub(&workspace.state_27.u.d.displacement,FLD(pose_hero,u8*,0x6A8)+0x10,&FLD(pose_hero,u8,0x80));
                matrix_mul_vec3(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.displacement,&FLD(pose_hero,u8,0x40));
                angle=FastMatrixHelperA(workspace.state_27.u.d.displacement.x,workspace.state_27.u.d.displacement.y);
                if (FLD(pose_hero,u8*,0x2290)[0x42]==0x31) {
                    angle=fast_subtract_rotations(angle,1.5707965f);sideScale=0.2f;
                } else {
                    angle=fast_subtract_rotations(angle,-1.5707965f);sideScale=0.5f;
                }
                FLD(D_L22_0025DE90, float, 0x1C8)=angle*sideScale;
                FLD(D_L22_0025DE90, float, 0x278)=angle*poseScale;
            } else {
                u8 action=FLD(pose_hero,u8*,0x2290)[0x43];
                float angularBase,pose;
                if (action!=0x31 && FLD(pose_hero,u8*,0x2290)[0x43]==0x48) {

                    poseScale=0.5f;
                    pose=FastAddRotations(0.13962635f,FLD(pose_hero,float,0x6A0));
                    angularBase=-0.06981318f;
                    FLD(D_L22_0025DE90, float, 0x278)=pose;
                    FLD(D_L22_0025DE90, float, 0x118)=FastAddRotations(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                    FLD(D_L22_0025DE90, float, 0x1C8)=FastAddRotations(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                } else if (action==0x31 || action==0x47) {
                    poseScale=0.58823526f;
                    pose=FastAddRotations(-0.8203048f,FLD(pose_hero,float,0x6A0));
                    angularBase=0.73303837f;
                    FLD(D_L22_0025DE90, float, 0x278)=pose;
                    FLD(D_L22_0025DE90, float, 0x118)=FastAddRotations(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                    FLD(D_L22_0025DE90, float, 0x1C8)=FastAddRotations(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                }
            }
        }
        {
            int nextIndex=AdvancePathIndex(H(void*,0x630),H(s32,0x634),H(s32,0x648),H(s32,0x654));
            float distance;
            FastVecSub(&workspace.state_27.u.d.displacement,(u8*)H(void*,0x630)+(nextIndex*16+16),&workspace.state_27.first);
            distance=FastVecLength(&workspace.state_27.u.d.displacement);
            if (distance<0.001f) {
                if (H(s32,0x634)==nextIndex) { H(s32,0x640)=1;goto finish; }
            } else {
                H(float,0x64C)=FastMatrixHelperA(workspace.state_27.u.d.displacement.x,workspace.state_27.u.d.displacement.y);
                H(float,0x650)=FastMatrixHelperA(vec_length_xy(&workspace.state_27.u.d.displacement),workspace.state_27.u.d.displacement.z);
            }
        }
        H(float,0x1A0)=FastAddRotations(H(float,0x64C),H(float,0x658));
        SteerHeroHeading(0,0.015f,0.15f,0.10471977f);
        if (((u32)(H(u32,0x2294)-0x28)<2U && !H(u8,0x49C)) || H(u32,0x2294)==0x3E) {
            if (H(s32,0x694)) {
                float desired=FastMatrixHelperA(H(float,0x620)-H(float,0x80),H(float,0x624)-H(float,0x84));
                if (FastDiffRots(H(float,0x98),desired)<1.5707965f) {
                    H(float,0x1A0)=desired;
                    SteerHeroHeading(0,0.04f,0.2f,0.10471977f);
                }
            }
            if (H(s32,0x660) && H(s32,0x678)<49) {
                float fraction;
                FastVecSub(&workspace.state_27.u.d.displacement,&workspace.state_27.first,&workspace.state_27.second);
                ++H(s32,0x678);
                fraction=(float)H(s32,0x678)*0.020833334f;
                FastVecScale(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.displacement,fraction);
                fraction=(float)(H(s32,0x678)-1)*0.020833334f;
                FastVecSub(&workspace.state_27.u.d.previousStep,&workspace.state_27.first,&workspace.state_27.second);
                FastVecScale(&workspace.state_27.u.d.previousStep,&workspace.state_27.u.d.previousStep,fraction);
                H(float,0x88)+=workspace.state_27.u.d.displacement.z-workspace.state_27.u.d.previousStep.z;
                FastVecAdd(&workspace.state_27.u.d.previousStep,&workspace.state_27.second,&workspace.state_27.u.d.displacement);
                FastVecSub(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.previousStep,HP(0x80));
                H(float,0xF0)=workspace.state_27.u.d.displacement.x;H(float,0xF4)=workspace.state_27.u.d.displacement.y;
                FastVecSub(&workspace.state_27.u.d.displacement,&workspace.state_27.first,HP(0x5D0));
                H(float,0x88)+=workspace.state_27.u.d.displacement.z;
                if (H(float,0x88)<H(float,0x5D8) && H(s32,0x678)<49 && H(float,0x88)<H(float,0x5D8)) H(float,0x88)=H(float,0x5D8);
            } else {
                FastVecSub(&workspace.state_27.u.d.displacement,&workspace.state_27.first,HP(0x5D0));
                H(float,0xF0)=workspace.state_27.u.d.displacement.x;
                H(float,0x88)+=workspace.state_27.u.d.displacement.z;
                H(float,0xF4)=workspace.state_27.u.d.displacement.y;
                FastVecSub(&workspace.state_27.u.d.previousStep,HP(0x5D0),HP(0x80));
                workspace.state_27.u.d.previousStep.z=0.0f;
                if (FastVecLength(&workspace.state_27.u.d.previousStep)>0.016666668f)
                    vec_scale_to_length(&workspace.state_27.u.d.previousStep,&workspace.state_27.u.d.previousStep,0.016666668f);
                H(float,0x80)+=workspace.state_27.u.d.previousStep.x;
                H(float,0x84)+=workspace.state_27.u.d.previousStep.y;
            }
            if (H(u32,0x2294)==0x3E) H(float,0xF8)-=0.006388889f;
            else ApplyHeroGravityAndJumpMotion();
        } else {
            float steering,slope,speedAdjustment,negativeDistance,distance;
            int segment;float weight;
            H(s32,0x660)=0;
            steering=0.0f;
            if (H(float,0x24B8)>0.2f && poseAvailable) {
                ResolveStickInputToDirection(1.0f, 0);
                steering=fast_subtract_rotations(H(float,0x1A0),H(float,0x64C));
                if (steering>0.78539824f) steering=0.78539824f;
                else if (steering< -0.78539824f) steering=-0.78539824f;
            }

            ApproachWithVelocity(HP(0x6A0),steering,HP(0x6A4),0.015f,0.3f,0.0f, 0);
            ApproachValue(HP(0x680),0.20000002f,0.004166667f);
            segment=H(s32,0x634);weight=H(float,0x638);
            qcopy(&workspace.state_27.u.p.probeA, &H(Vec4,0x80));
            Spline_AdvanceByDistance(H(void*,0x630),&workspace.state_27.u.p.probeA,&segment,&weight,0.3f,H(s32,0x654));
            slope=FastMatrixHelperA(vec_distance_xy(HP(0x5D0),&workspace.state_27.u.p.probeA),workspace.state_27.u.p.probeA.z-H(float,0x5D8));
            if (slope>0.0f) {
                speedAdjustment=slope*-0.07957746f;
                if (slope>0.26179942f) H(s32,0x67C)=0;
                else if (slope<0.13962635f && H(s32,0x67C)==0) H(s32,0x67C)=-1;
            } else {
                speedAdjustment=-slope*0.38197184f;
                if (slope< -0.19198623f) H(s32,0x67C)=1;
                else if (slope> -0.122173056f && H(s32,0x67C)==1) H(s32,0x67C)=-1;
            }
            if (H(float,0x674)<speedAdjustment) ApproachValue(HP(0x674),speedAdjustment,0.0022222223f);
            else ApproachValue(HP(0x674),speedAdjustment,0.00055555557f);
            if (H(float,0x674)>0.20000002f) H(float,0x674)=0.20000002f;
            if (H(float,0x674)< -0.041666668f) H(float,0x674)=-0.041666668f;
            H(float,0x644)=H(float,0x680)+H(float,0x674);
            if (H(float,0x644)<0.0f) H(float,0x644)=0.0f;
            FastVecSub(HP(0xF0),&workspace.state_27.first,HP(0x5D0));
            FastVecSub(&workspace.state_27.u.d.displacement,HP(0x5D0),HP(0x80));
            negativeDistance=-FastVecLength(&workspace.state_27.u.d.displacement);
            SpringFloatToGoal(&negativeDistance,HP(0x6AC),0.0f,0.03f,0.3f,0.116666675f);
            distance=FastVecLength(&workspace.state_27.u.d.displacement);
            if (distance<H(float,0x6AC)) H(float,0x6AC)=distance;
            if (H(float,0x6AC)<distance) vec_scale_to_length(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.displacement,H(float,0x6AC));
            FastVecAdd(HP(0x80),HP(0x80),&workspace.state_27.u.d.displacement);
            if (H(float,0x88)<H(float,0x5D8) && H(float,0x31C)<1.0f && H(float,0x88)<H(float,0x5D8))
                H(float,0x88)=H(float,0x5D8);
        }
        if (H(u32,0x2294)==0x2A && H(s32,0x1B8)<20) {


            float angle=RandomSignedFloatRange(0.3490659f,0.6108653f);
            angle=FastAddRotations(H(float,0x64C),angle);
            workspace.state_27.direction.x=FastSinOrCosA(angle);workspace.state_27.direction.y=FastSinOrCosB(angle);workspace.state_27.direction.z=0.0f;
            make_hit_descriptor(workspace.state_27.u.query,H(void*,0x2290),0x10000,1.0f,&workspace.state_27.direction);
            qcopy(&workspace.state_27.position, &H(Vec4,0x80));workspace.state_27.position.z+=0.6f;
            ProcessCollisionHit(&workspace.state_27.position,0x10,1.0f,H(void*,0x2290),workspace.state_27.u.query);
        }
        goto finish;
    }
}


case 0x71:
{

    float angle, radius, distance, vertical_error;
    s32 next_index;
    GetHeroOffsetVector(&workspace.state_71.reference_position);
    if (*(u8 *)(H(u8 *, 0x2290) + 0x43) == 0x5f) {
        UpdateSoundSlotObject(0, H(u8 *, 0x2290), 0);
        if ((D_L22_001B1C48 & 1) != 0) {
            qcopy(&workspace.state_71.particle_position, &workspace.state_71.reference_position); /* lq/sq at 002C524C */
            FastVecScale(&workspace.state_71.particle_velocity, &H(Vec4, 0x110), 0.400000006f);
            angle = RandomSignedFloatRange(0.0f, 0.52359885f);
            angle = FastAddRotations(H(float, 0x700), angle);
            radius = RandomFloatRange(0.0f, 0.0666666701f);
            workspace.state_71.particle_velocity.x = workspace.state_71.particle_velocity.x + FastSinOrCosA(angle) * radius;
            workspace.state_71.particle_velocity.y = workspace.state_71.particle_velocity.y + FastSinOrCosB(angle) * radius;
            workspace.state_71.particle_velocity.z = RandomFloatRange(0.0500000045f, 0.0833333358f);
            workspace.state_71.particle_velocity.w = -0.00972222257f;
            SpawnWhiteFlashParticle(&workspace.state_71.particle_position, &workspace.state_71.particle_velocity, 0, -1.0f);
        }
    }
    find_nearest_path_point(H(void *, 0x6e0), &workspace.state_71.reference_position, &H(Vec4, 0x6d0),
                       &H(s32, 0x6e4), &H(float, 0x6e8), H(s32, 0x6fc),
                       999.0f, 8.0f, 2.5f);
    if (H(s32, 0x6f0) != 0) {
        qcopy_nc(&H(Vec4, 0xf0), &H(Vec4, 0x120));
        H(s32, 0x6f0) = H(s32, 0x6f0) + 1;
        H(float, 0xf8) = H(float, 0xf8) - 0.00611111149f;
        goto finish;
    }
    Spline_AdvanceByDistance(H(void *, 0x6e0), &workspace.state_71.particle_position, &H(s32, 0x6e4),
                       &H(float, 0x6e8), H(float, 0x6f4), H(s32, 0x6fc));
    next_index = AdvancePathIndex(H(void *, 0x6e0), H(s32, 0x6e4), 1, H(s32, 0x6fc));
    FastVecSub(&workspace.state_71.particle_velocity, H(u8 *, 0x6e0) + 0x10 + next_index * 0x10, &workspace.state_71.particle_position);
    if (FastVecLength(&workspace.state_71.particle_velocity) < 0.00100000005f) {
        if (H(s32, 0x6e4) == next_index) {
            H(s32, 0x6f0) = 1;
            goto finish;
        }
    } else {
        H(float, 0x700) = FastMatrixHelperA(workspace.state_71.particle_velocity.x, workspace.state_71.particle_velocity.y);
        distance = vec_length_xy(&workspace.state_71.particle_velocity);
        H(float, 0x704) = FastMatrixHelperA(distance, workspace.state_71.particle_velocity.z);
    }
    H(float, 0x1a0) = H(float, 0x700);
    SteerHeroHeading(0, 0.0179999992f, 0.200000003f, 0.107628651f);
    ApproachValue(&H(float, 0x6f4), 0.233333349f, 0.00249999994f);
    FastVecSub(&H(Vec4, 0xf0), &workspace.state_71.particle_position, &H(Vec4, 0x6d0));
    FastVecSub(&workspace.state_71.particle_velocity, &H(Vec4, 0x6d0), &workspace.state_71.reference_position);
    vertical_error = -FastVecLength(&workspace.state_71.particle_velocity);
    SpringFloatToGoal(&vertical_error, &H(float, 0x708), 0.0f,
                 0.0500000007f, 0.300000012f, 0.166666672f);
    distance = FastVecLength(&workspace.state_71.particle_velocity);
    if (distance < H(float, 0x708)) H(float, 0x708) = distance;
    if (H(float, 0x708) < distance)
        vec_scale_to_length(&workspace.state_71.particle_velocity, &workspace.state_71.particle_velocity, H(float, 0x708));
    FastVecAdd(&H(Vec4, 0x80), &H(Vec4, 0x80), &workspace.state_71.particle_velocity);
    goto finish;
}



case 23: case 24:
    FastVecSub(HP(0x190), HP(0x560), HP(0x550));
    H(float, 0x1A0) = FastMatrixHelperA(H(float, 0x190), H(float, 0x194));
    SteerHeroHeading(0, 0.04f, 0.2f, 0.10471977f);
    if (H(u8, 0x22C3) != 2) StepAngleTowardTarget(HP(0x94), 0, 0.0f, 0.078539826f);
    FastVecSub(HP(0xF0), HP(0x550), HP(0x80));
    ClampVectorLength(HP(0xF0), 0.06666667f);
    ApproachValue(HP(0x580),H(float,0x88),0.050000004f);
    goto finish;


case 0x46: case 0x47:
    FastVecSub(HP(0x190),HP(0x560),HP(0x550));
    H(float,0x1A0)=FastMatrixHelperA(H(float,0x190),H(float,0x194));
    SteerHeroHeading(0,0.02f,0.2f,0.078539826f);
    FastVecSub(HP(0xF0),HP(0x550),HP(0x80));ClampVectorLength(HP(0xF0),0.028333336f);
    ApproachValue(HP(0x580),H(float,0x88),0.050000004f);
    goto finish;


    case 0x19: case 0x1A:
        FastVecSub(&H(Vec, 0x190), &H(Vec, 0x560), &H(Vec, 0x550));
        H(float, 0x1A0) = FastMatrixHelperA(H(float, 0x190), H(float, 0x194));
        SteerHeroHeading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub(&workspace.mine.s60, &H(Vec, 0x560), &H(Vec, 0x550));
        ClearVector128(&H(Vec, 0xF0));
        if (H(s32, 0x2294) == 0x19) FastVecCross(&workspace.mine.s40, &H(Vec, 0x2C0), &workspace.mine.s60);
        else FastVecCross(&workspace.mine.s40, &workspace.mine.s60, &H(Vec, 0x2C0));
        vec_scale_to_length(&workspace.mine.s40, &workspace.mine.s40, 0.2f);
        FastVecAdd(&workspace.mine.s50, &H(Vec, 0x80), &workspace.mine.s40);
        if (!FindHeroLedgeGrab(&H(Vec, 0x80), &H(Vec, 0x90), 0)) goto finish;
        if (!FindHeroLedgeGrab(&workspace.mine.s50, &H(Vec, 0x90), &workspace.mine.s00)) goto finish;
        FastVecSub(&H(Vec, 0xF0), &workspace.mine.s00, &H(Vec, 0x80));
        vec_scale_to_length(&H(Vec, 0xF0), &H(Vec, 0xF0), D_L22_001ACE68[FloatToInt(H(float, 0xC38))] * 0.5f);
        goto finish;

case 0x76:
    H(float, 0x1a0) = H(float, 0x32c);
    H(float, 0x1b0) = 0.0916666687f;
    ApproachHeroVelocity(0.0069444445f);
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.00499999989f);
    goto finish;



case 6: case 44:
{
    if (H(u32, 0x2294) == 44) {

        float target = H(float, 0x31C) > 4.0f ? 0.43633235f : 0.0f;
        qcopy(&workspace.state_06.rotation, &H(Vec4, 0x90));
        ApproachWithVelocity(&workspace.state_06.rotation.y, target, HP(0xA4), 0.02f, 0.3f, 0.043633237f, 0);
        ApproachWithVelocity(&workspace.state_06.rotation.x, 0.0f, HP(0xA0), 0.02f, 0.3f, 0.043633237f, 0);
        StartHeroPoseOffset(H(float, 0xA0), H(float, 0xA4), 0);
        if (H(float, 0x31C) > 1.0f) H(int, 0x2298) = 1;
    }
    UpdateHeroTargetSpeed();
    if (!H(s16, 0x1E0)) UpdateHeroAirborneSteering();
    ApplyHeroModePoseOffsets();
    BuildHeroMoveImpulse(0.7f, 0.0f);
    ApplyHeroModeTransform(HP(0xF0), HP(0xF0), H(float, 0xA80));
    if (GetViewSpaceHeight(HP(0xF0)) < -0.833333373f) {
        shared_speed = -0.833333373f;
        { SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_speed); goto finish; }
    }
    goto finish;
}


case 0x74:
{
    float speed;
    H(u8, 0x22bc) = 1;
    ApproachValue(&H(float, 0xa88), H(float, 0xa90), 0.00242406875f);
    ApproachValue(&H(float, 0xa8c), H(float, 0xa94), 0.00242406875f);
    StartHeroPoseOffset(H(float, 0xa88), H(float, 0xa8c), 0.0f);
    speed = vec_length_xy(&H(Vec4, 0xf0));
    func_L00_002EE4D8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), speed * 0.899999976f);
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), H(float, 0xa80));
    speed = GetViewSpaceHeight(&H(Vec4, 0xf0));
    if (speed < -0.833333373f) {
        shared_speed = -0.833333373f;
        { SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_speed); goto finish; }
    }
    goto finish;
}



case 0x82:
{
    s32 phase, color;
    u32 held;
    float elevation, factor, step;
    UpdateSoundSlotObject(4, H(u8 *, 0x2290), 13);
    phase = LerpInt(720, 180, H(float, 0x5b0) * 0.0199999996f);
    color = UpdateAngleAndBlend(&H(float, 0x5a0), 0x60ffffff, 0x40ffc0a0,
                             (float)phase * 0.000290888245f);
    ShowGaugePopup(2, color, 0, 1.0f - H(float, 0x5b0) * 0.0199999996f);
    held = FLD(gPadState, u32, 0x1A0) & 0x40;
    if (H(float, 0x5b0) == 0.0f) held = 0;
    if (held != 0) {
        ApproachValue(&H(float, 0x5b0), 0.0f, 0.100000001f);
        OffsetPointInViewSpace(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0250000004f);
    } else ApproachValue(&H(float, 0x5b0), 0.0f, 0.0199999996f);
    if ((FLD(gPadState, u32, 0x1A4) & 0x40) != 0) ApproachValue(&H(float, 0x5b0), 0.0f, 0.5f);
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0075000003f);
    elevation = GetViewSpaceHeight(&H(Vec4, 0xf0));
    if (0.100000009f < elevation)
        SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.100000009f);
    elevation = GetViewSpaceHeight(&H(Vec4, 0xf0));
    if (elevation < -0.200000018f)
        SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), -0.200000018f);
    elevation = GetViewSpaceHeight(&H(Vec4, 0xf0));
    if (25.0f < H(float, 0x5b0) && H(short, 0x5be) < 90 && elevation < 0.0f && H(float, 0x31c) < 1.20000005f) {
        factor = (H(float, 0x31c) - 0.25f) * 1.0526315f;
        H(u16, 0x5be) = H(u16, 0x5be) + 1;
        if (factor < 0.0f) factor = 0.0f;
        SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), elevation * factor);
        if (H(float, 0x31c) < 0.25f)
            SpringFloatToGoal(&H(float, 0x88), &H(float, 0x5b4), H(float, 0x318) + 0.25f,
                         0.0270000007f, 0.300000012f, 0.0833333358f);
    } else if (0.0f < elevation) H(short, 0x5be) = 0;
    FLD(D_L22_001B9B40, float, 0x3C8) = GetViewSpaceHeight(&H(Vec4, 0xf0));
    ApplyHeroModePoseOffsets();
    ResolveStickInputToDirection(H(float, 0x24b8) * 0.200000018f, 0);
    if (H(float, 0x24b8) < 0.200000003f) H(float, 0x1a0) = H(float, 0x98);
    SteerHeroHeading(0, 0.0270000007f, 0.300000012f, H(float, 0x24b8) * 0.087266475f);
    step = 0.00138888892f;
    if (H(float, 0x24b8) < 0.200000003f) step = 0.000555555569f;
    ApproachHeroVelocity(step);
    goto finish;
}



    case 8: {
        f32 k;
        if (hero_slot_item_id(3) == 2) {
            s32 idx = H(s32, 0x243C);
            if (idx != -1) {
                char *e = gSoundState + idx * 0x70;
                if (*(Moby **)(e + 0x88) == H(Moby *, 0x2290) && *(u8 *)(e + 0x74)) StopSoundVoice(idx);
            }
            H(s32, 0x243C) = -1;
            UpdateSoundSlotObject(3, H(Moby *, 0x2290), 2);
        } else {
            s32 idx = H(s32, 0x2438);
            if (idx != -1) {
                char *e = gSoundState + idx * 0x70;
                if (*(Moby **)(e + 0x88) == H(Moby *, 0x2290) && *(u8 *)(e + 0x74)) StopSoundVoice(idx);
            }
            H(s32, 0x2438) = -1;
            UpdateSoundSlotObject(4, H(Moby *, 0x2290), 0xD);
        }
        shared_limit = 0.050000004f;
        if (H(s32, 0x1338) == 3) shared_limit = 0.083333336f;
        k = 0.72f;
        if (H(u8, 0x24EF)) {
            shared_limit = 0.12833333f;
            k = 0.98640007f;
        }
        if (H(float, 0x24C8) != 0.0f) k = H(float, 0x24C8);
        {
            f32 v = GetViewSpaceHeight(&H(Vec, 0xF0));
            ResolveStickInputToDirection(shared_limit, 0);
            SteerHeroHeading(0, 0.025f, 0.3f, 0.20943955f);
            ApproachHeroSpeed(0.004166667f, 0.0019444445f);
            ComputeHeroPushDirection(99999.0f);
            ApplyHeroModePoseOffsets();
            ProjectVectorOntoViewPlane(&H(Vec, 0xF0), &H(Vec, 0xF0));
            SpringFloatToGoal(&v, &H(float, 0xA98), -shared_limit * k, 0.025f, 0.3f, 0.28333336f);
            ApplyHeroModeTransform(&H(Vec, 0xF0), &H(Vec, 0xF0), -v);
        }
        if (H(float, 0x88) < H(float, 0x490)) ApproachValue(&H(float, 0x490), H(float, 0x88), 0.06666667f);
        ProbeHeroAirborneWallContact();
        goto finish;
    }

case 7: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
case 16: case 17: case 18: case 27: case 56: case 69: case 72:
case 91: case 102: case 110: case 129: case 137: case 146:
{
    float magnitude, saved_speed;
    int frame, mark;
    if (H(u32, 0x2294) == 27 && !H(s16, 0x24FC) && H(int, 0x1338) == 3 && IsBelowPlaneWithinDepth(10.0f))
        PlayHeroSound(4, 0);
    if (H(s16, 0x528) && H(u8, 0x1492)) H(float, 0x1B0) = H(float, 0x1B4);
    else {
        if (H(u8, 0x49C)) ResolveStickInputToDirection(0.09916667f, 0);
        ResolveStickInputToDirection(H(float, 0x4A4), 0);
    }
    if (H(u32, 0x2294) == 18) {
        if (H(int, 0x1B8) == 20) {
            EmitHeroDustAndDebris(3, 16, 1);
            if (D_L22_001B28B0)
                RippleDisturb(D_L22_001B28B0, D_L22_001B28B8, 0,
                              H(float, 0x80), H(float, 0x84), 0.4f, 0.35f);
        }
        if (H(float, 0xC38) >= 4.0f && H(float, 0xC38) <= 7.0f) EmitHeroRandomizedMotionEffects(7, 0, 0);
    }
    mark = H(s16, 0x4AC); frame = H(int, 0x1B8);
    if (frame == mark) qcopy(&H(Vec4, 0x460), &H(Vec4, 0x80));
    if (H(u8, 0x49C) || (frame < mark &&
        H(u32, 0x2294) != 11 && H(u32, 0x2294) != 16 && H(u32, 0x2294) != 12 &&
        H(u32, 0x2294) != 17 && H(u32, 0x2294) != 27 && H(u32, 0x2294) != 137 && H(u32, 0x2294) != 72)) {
        if (H(s16, 0x528)) {
            SteerHeroReferencePoint();
            if (H(u32, 0x2294) == 10 && H(int, 0x1B8) < 10 && H(float, 0x178) < 0.116666675f) {
                H(float, 0xF0) += FastSinOrCosA(H(float, 0x98)) * 0.011666667f;
                H(float, 0xF4) += FastSinOrCosB(H(float, 0x98)) * 0.011666667f;
                qcopy(&H(Vec4, 0x140), &H(Vec4, 0xF0));
            }
        } else {
            SteerHeroHeading(0, 0.015f, 0.2f, 0.2501639f);
            saved_speed = H(float, 0x1B4);
            if (H(u8, 0x49C) > 1) H(float, 0x1B4) *= 0.4f;
            if (H(s16, 0x1454)) ComputeHeroPushDirection(H(float, 0x1458));
            else ComputeHeroPushDirection(99999.0f);
            H(float, 0x1B4) = saved_speed;
            if (H(u8, 0x49C) != 1) ApproachHeroSpeed(H(float, 0x500), H(float, 0x504));
            if (H(u8, 0x49C)) {
                if (FLD(gPadState, int, 0x1D4) && H(s16, 0x34A)) H(float, 0x1B4) = 0.0f;
                if (H(u8, 0x49C)) ShrinkHeroVectorByAmount(H(float, 0x504));
            }
            BuildHeroMoveImpulse(0.5f, 0.033333335f);
            if (H(u32, 0x2294) == 9 && H(int, 0x1B8) < H(s16, 0x4AC) + 4)
                OffsetPointBySideDirection(HP(0xF0), HP(0xF0), H(int, 0x1B8) * 0.0044444446f);
            if (H(u32, 0x2294) == 10 && H(int, 0x1B8) < 34)
                OffsetPointBySideDirection(HP(0xF0), HP(0xF0), H(int, 0x1B8) * 0.014722222f);
            if (H(int, 0x1B8) < 10 && H(float, 0x24B8) > 0.2f) {

                qcopy(&workspace.state_07.origin, &H(Vec4, 0x80));
                OffsetPointInViewSpace(&workspace.state_07.origin, &workspace.state_07.origin, 0.5f);
                OffsetPointBySideDirection(&workspace.state_07.endpoint, &workspace.state_07.origin, 0.95f);
                if (CollLine(&workspace.state_07.origin, &workspace.state_07.endpoint, 4, H(void *, 0x2290), 0)) H(s16, 0x524) = 1;
            }
        }
    } else {
        UpdateHeroAirborneSteering();
        if (H(u32, 0x2294) == 18) {
            magnitude = vec_length_xy(HP(0xF0));
            if (magnitude > 0.06166667f) magnitude = 0.06166667f;
            FastVectorNormalizeHelper(HP(0xF0), HP(0xF0), magnitude);
        }
    }
    if (H(float, 0x318) > H(float, 0x490)) {
        H(float, 0x490) += 0.10000001f;
        if (H(float, 0x490) > H(float, 0x318)) H(float, 0x490) = H(float, 0x318);
    }
    if (H(float, 0x490) > H(float, 0x88)) H(float, 0x490) = H(float, 0x88);
    if (H(int, 0x1B8) > H(s16, 0x4AC) && GetViewSpaceHeight(HP(0xF0)) < 0.001f &&
        (!H(u8, 0x49D) || H(int, 0x1B8) > H(int, 0x434)) &&
        (H(u32, 0x2294) != 14 || H(int, 0x1B8) > 17)) {
        H(u8, 0x49E) = 1;
        if (H(float, 0x458) != 0.0f) H(float, 0x520) = H(float, 0x458);
    }
    if (!H(u8, 0x22B4)) ApplyHeroModePoseOffsets();
    if (H(u8, 0x22B4) == 1) UpdateHeroMotionResponseParameters();
    if (H(u32, 0x2294) == 16 || H(u32, 0x2294) == 13)
        UpdateTransformHistoryFollowers(HP(0x18E0), H(int, 0x1B8) < 13 ? 0 : 2);
    if (H(u32, 0x2294) == 129)
        UpdateTransformHistoryFollowers(HP(0x18E0), H(int, 0x1B8) < 14 ? 0 : 2);
    if (H(u32, 0x2294) == 16 && H(int, 0x1B8) > 8 && H(float, 0xC38) < 28.0f) {

        int count, i;
        BuildHeroRelativePoint(&workspace.state_07.origin, 1, 0.8f, 0.0f, 0.3f);
        count = ProcessCollisionHit(&workspace.state_07.origin, 0, 0.9f, H(void *, 0x2290), 0);
        if (count) {
            FastVecScale(&workspace.state_07.endpoint, HP(0x110), 7.0f);
            for (i = 0; i < count; i++) {
                if (IsMobyInSpecialClassRange(D_L22_001C4140[i]))
                    QueueImpactEffect(D_L22_001C4140[i], H(void *, 0x2290), 0x10000, HP(0x80), &workspace.state_07.endpoint, 1.0f);
            }
        }
    }
    if (H(u32, 0x2294) == 56 && !H(u8, 0x49E) && H(float, 0xF8) > 0.025000002f)
        EmitHeroTimedEffects();
    ApplyHeroGravityAndJumpMotion();
    ProbeHeroAirborneWallContact();
    goto finish;
}


case 22:
{
    float speed = GetViewSpaceVectorLength(HP(0xF0));
    if (!H(s16, 0x34E) && H(int, 0x1B8) >= 11) speed -= 0.0027777778f;
    else speed -= 0.0011111111f;
    if (speed < 0.0f) speed = 0.0f;
    if (H(u8, 0x1497)) TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
    SetViewSpaceVectorLength(HP(0xF0), HP(0xF0), speed);
    shared_scale = 0.004f;
    { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_scale); goto finish; }
}


    case 0x8C:
        qzero(D_00189F10);
        H(float, 0xF8) = -0.38333336f;
        goto finish;

case 0x62:
{

    float distance;
    u8 mode;
    float weight;
    FastVecSub(&workspace.state_62.difference, &H(Vec4, 0x18a0), &H(Vec4, 0x80));
    H(float, 0x1a0) = FastMatrixHelperA(workspace.state_62.difference.x, workspace.state_62.difference.y);
    distance = vec_length_xy(&workspace.state_62.difference);
    if (0.200000003f < distance) {
        hp32 = (u8 *)gHeroState;
        FLD(hp32, float, 0x24b8) = 1.0f;
        H(float, 0x1a0) = FastMatrixHelperA(workspace.state_62.difference.x, workspace.state_62.difference.y);
        H(float, 0x1b0) = distance; /* store in ordinary branch delay slot */
        if (distance < D_L22_001A7DAC[0][2]) H(float, 0x1b0) = D_L22_001A7DAC[0][1] * 0.0166666675f;
        else H(float, 0x1b0) = D_L22_001A7DAC[1][1] * 0.0166666675f;
        if (H(u8, 0x22b4) == 1) H(float, 0x1b0) = 0.0150000006f;
    } else {
        H(float, 0x24b8) = 1.0f;
        H(float, 0x1a0) = H(float, 0x18ac);
        H(float, 0x1b0) = 0.0f;
    }
    weight = 1.0f;
    mode = H(u8, 0x22b4);
    if (mode == 3) SteerHeroHeading(0, 0.0299999993f, 0.300000012f, 0.0930842459f);
    else if (mode == 1) SteerHeroHeading(0, 0.0299999993f, 0.300000012f, 0.130899712f);
    else if (mode == 0) SteerHeroHeading(0, 0.0299999993f, 0.300000012f, 0.130899712f);
    else goto turn_done;
    if (H(u8, 0x22b4) == 0) ApplyHeroModePoseOffsets();
turn_done:
    ApproachHeroSpeed(weight * 0.00499999989f, 0.00555555569f);
    ComputeHeroPushDirection(99999.0f);
    if (H(u8, 0x22b4) == 0) SlideHeroAlongWalls(1);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x110), 0.0069444445f); CancelHeroVelocityIntoWall(); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;
}



case 0x63:
{

    FastVecSub(&workspace.state_63.difference, &H(Vec4, 0x18a0), &H(Vec4, 0x80));
    if (FastVecDot(&workspace.state_63.difference, &H(Vec4, 0x160)) < 0.0f)
        ClearVector128(&H(Vec4, 0x160));
    ClearVector128(&H(Vec4, 0xf0));
    ShrinkHeroVectorByAmount(0.0075000003f);
    SlideHeroAlongWalls(0);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x110), 0.0069444445f); CancelHeroVelocityIntoWall(); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;
}



case 0x3C: case 100:
    ClearVector128(HP(0xF0));goto finish;


case 0x65:
    ClearVector128(&H(Vec4, 0xf0));
    if ((float)H(s32, 0x18c0) * 0.5f < H(float, 0x334) - H(float, 0x88))
        H(float, 0xf8) = -0.00416666688f;
    else H(float, 0xf8) = -0.0166666675f;
    goto finish;



case 0x79:
    EmitHeroRadialParticles();
    /* fall through */


case 0x78:
    ClearVector128(&H(Vec4, 0xf0));
    H(float, 0xf8) = -0.0166666675f;
    goto finish;



case 0x7a:
    ClearVector128(&H(Vec4, 0xf0));
    H(float, 0xf8) = -0.00583333336f;
    goto finish;



case 0x3F: case 0x43:
    TryHeroSurfacePushResponse(3.7f,0.0f,0.35f);ResolveStickInputToDirection(1.0f, 0);H(float,0x1B0)=0.0f;
    ApproachHeroSpeed(0.0f,0.0035f);ClearVector128(HP(0xF0));SlideHeroAlongWalls(0);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), HP(0x130), 0.0069444445f); CancelHeroVelocityIntoWall(); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;


    case 0x4D: {
        char *t = (char *)&D_L22_0025FA10[H(s16, 0xBFC)];
        H(float, 0x1B0) = 0.0f;
        if ((FLD(t, s32, 0x04) == 0 || FLD(t, s32, 0x04) == 1) && H(float, 0xC38) < 5.5f) H(float, 0x1B0) = 0.058333337f;
        if (H(s32, 0xC2C) == 0 && (f32)FLD(t, s32, 0x1C) <= H(float, 0xC38) && H(float, 0xC38) <= (f32)FLD(t, s32, 0x20)) {
            s32 side = 2;
            if (FLD(t, s32, 0x04) == 1) side = 0;
            TransformMobyJointToWorld(H(Moby *, 0x2290), side, &workspace.mine.s10);
            TransformMobyJointToWorld(H(Moby *, 0x2290), side | 1, &workspace.mine.s20);
            FastVecAdd(&workspace.mine.s00, &workspace.mine.s10, &workspace.mine.s20);
            FastVecScale(&workspace.mine.s00, &workspace.mine.s00, 0.5f);
            SweepCollisionFromObject(H(Moby *, 0x2290), &workspace.mine.s00, 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
        }
        ApproachValue(&H(float, 0xC20), 1.0f, 0.2f);
        if (H(s32, 0xBE8) || H(Moby *, 0xBE4)) {
            H(float, 0x1A0) = H(float, 0xBEC);
            SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        } else {
            SelectHeroAimTarget(5.0f, 0.78539824f, 0.78539824f);
        }
        ApproachHeroSpeed(0.010277778f, 0.007777778f);
        if (H(s32, 0xBE8)) {
            if (H(u8, 0x22C3) == 2) SetHeroPushDirection(&H(Vec, 0xBC0));
            else ComputeHeroPushDirection(H(float, 0xBEC));
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        if (H(s16, 0x34E)) {
            H(float, 0xF8) = H(float, 0x118) - 0.0069444445f;
            CancelHeroVelocityIntoWall();
        } else {
            H(float, 0xF8) -= 0.015000001f;
        }
        TryHeroSurfacePushResponse(0.7f, 0.0f, 0.3f);
        goto finish;
    }

case 0x4B:
    ResolveStickInputToDirection(0.033333335f, 0);SteerHeroHeading(0,0.04f,0.2f,0.14544412f);
    ApproachHeroSpeed(0.004166667f,0.0019444445f);ComputeHeroPushDirection(99999.0f);
    ProjectVectorOntoViewPlane(HP(0xF0),HP(0xF0));shared_scale=0.024000002f;{ ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_scale); goto finish; }


case 0x4E:
    H(float,0x1A0)=H(float,0x32C);H(float,0x1B0)=0.09166667f;
    ApproachHeroVelocity(0.0069444445f);
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.005f); goto finish;




case 0x41:
    ResolveStickInputToDirection(0.050000004f, 0);
    if (!H(s16,0x1E0)) UpdateHeroAirborneSteering();
    ApplyHeroModeTransform(HP(0xF0),HP(0xF0),0.0033333334f);
    if (H(float,0xF8)< -0.16666667f) H(float,0xF8)=-0.16666667f;
    goto finish;


case 0x44:
    if (H(float,0xF8)>0.0f) StartHeroPoseOffset(0.0f,0.20943955f,0.0f);
    shared_scale=0.0055555557f;{ ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_scale); goto finish; }


case 0x40: case 0x4C:
{
    float acceleration,maximum,turn;
    ResolveStickInputToDirection(0.050000004f, 0);
    maximum=0.16580631f;acceleration=0.033f;
    if (H(u8,0x40F)) {maximum=0.19489513f;acceleration=0.037f;}
    SteerHeroHeading(0,acceleration,0.15f,maximum);ApproachHeroSpeed(0.005f,0.0055555557f);
    if (H(float,0x174)<0.011666667f) {
        H(u8,0x40C)=1;
        if (FloatAbs(H(float,0x1A8))>1.7453294f && H(float,0x24B8)>0.8f) H(u8,0x40F)=1;
    }
    {
        float firstAngle=ReadPadFloatHistory(0),secondAngle=ReadPadFloatHistory(2);
        if (FastDiffRots(firstAngle,secondAngle)>2.617994f &&
            FloatAbs(H(float,0x1A8))>1.2217306f && H(float,0x24B8)>0.8f) {
            H(u8,0x40F)=1;H(u8,0x40C)=1;
        }
    }
    if (FloatAbs(H(float,0x1A8))<0.087266475f) H(u8,0x40C)=0;
    if (H(u8,0x40F)) {
        if (FloatAbs(H(float,0x1A8))<0.06981318f) H(u8,0x40F)=0;
        if (H(u8,0x40F)) {
            turn=0.050000004f-FloatAbs(H(float,0x1A8))*0.02122066f;
            if (turn<0.0f) turn=0.0f;
            if (turn<H(float,0x1B0)) H(float,0x1B0)=turn;
        }
    }
    if (H(u8,0x40C)) ComputeHeroPushDirection(H(float,0x1A0));
    else ComputeHeroPushDirection(99999.0f);
    shared_mode=1;
    { SlideHeroAlongWalls(shared_mode); if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); CancelHeroVelocityIntoWall(); } else ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish; }
}


case 0x42:
{
    float speed=vec_length_xy(HP(0xF0));
    if (H(s16,0x34E)) speed*=0.99f; else speed*=0.92f;
    func_L00_002EE4D8(HP(0xF0),HP(0xF0),speed);
    H(float,0xF8)=0.0f;

    if (H(s16,0x34E)) { ApplyHeroModeTransform(HP(0xF0),HP(0x120),0.0061111115f); goto finish; }
    shared_scale=0.004f;{ ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_scale); goto finish; }
}


case 0x49: case 0x4A:
{

    H(float,0xC20)=1.3f;
    FastVecSub(HP(0x190),HP(0x560),HP(0x550));
    H(float,0x1A0)=FastMatrixHelperA(H(float,0x190),H(float,0x194));
    SteerHeroHeading(0,0.02f,0.2f,0.078539826f);
    FastVecSub(&workspace.state_49.line,HP(0x560),HP(0x550));ClearVector128(HP(0xF0));
    if (H(u32,0x2294)==0x49) FastVecCross(&workspace.state_49.side,HP(0x2C0),&workspace.state_49.line);
    else FastVecCross(&workspace.state_49.side,&workspace.state_49.line,HP(0x2C0));
    vec_scale_to_length(&workspace.state_49.side,&workspace.state_49.side,0.2f);FastVecAdd(&workspace.state_49.candidate,HP(0x80),&workspace.state_49.side);
    if (FindHeroLedgeGrab(HP(0x80),HP(0x90),0) && FindHeroLedgeGrab(&workspace.state_49.candidate,HP(0x90),&workspace.state_49.hitPosition)) {
        FastVecSub(HP(0xF0),&workspace.state_49.hitPosition,HP(0x80));
        shared_index=FloatToInt(H(float,0xC38));shared_table=D_L22_0028F5F0;
        { vec_scale_to_length(HP(0xF0), HP(0xF0), shared_table[shared_index] * 0.5f); goto finish; }
    }
    goto finish;
}


case 0x56:
case 0x5f:
    TryHeroSurfacePushResponse(3.70000005f, 0.0f, 0.349999994f);
    ResolveStickInputToDirection(1.0f, 0);
    H(float, 0x1b0) = 0.0f;
    ApproachHeroSpeed(0.0f, 0.00491666701f);
    ClearVector128(&H(Vec4, 0xf0));
    ShrinkHeroVectorByAmount(0.00491666701f);
    SlideHeroAlongWalls(0);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); CancelHeroVelocityIntoWall(); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;



case 0x5d:
{


    s32 mode;
    int range = 50;
    ResolveStickInputToDirection(1.0f, 0);
    SteerHeroHeading(0, 0.0199999996f, 0.200000003f, 0.0319977067f);
    H(float, 0x1b0) = 0.0f;
    ClearVector128(&H(Vec4, 0xf0));
    ShrinkHeroVectorByAmount(0.00491666701f);
    if (H(s32, 0xc2c) == 0) {
        {
            float offset = 1.5f;
            if (H(short, 0xbfc) == 2) offset = 5.5f;
            BuildHeroRelativePoint(&workspace.state_5d.local_offset, 0, offset, 0.0f, 0.0f);
        }
        make_hit_descriptor(&workspace.state_5d.probe, H(u8 *, 0x2290), 0xb0000, range, &workspace.state_5d.local_offset);
        workspace.state_5d.probe.vector.w = 5627.9248f; /* exact bits 0x45afdf66 */
        workspace.state_5d.probe.type = 7;
        workspace.state_5d.probe.kind = 1;
        workspace.state_5d.probe.id = *(u16 *)(H(u8 *, 0x2290) + 0xaa);
        switch (H(short, 0xbfc)) {
        case 0:
            if (7.0f < H(float, 0xc38) && H(float, 0xc38) < 14.0f) {
                TransformMobyJointToWorld(H(u8 *, 0x2290), 3, &workspace.state_5d.effect_position);
                ProcessCollisionHit(&workspace.state_5d.effect_position, 0x10, 2.70000005f, H(u8 *, 0x2290), &workspace.state_5d.probe);
            }
            break;
        case 1:
            if (7.0f < H(float, 0xc38) && H(float, 0xc38) < 14.0f) {
                TransformMobyJointToWorld(H(u8 *, 0x2290), 4, &workspace.state_5d.effect_position);
                ProcessCollisionHit(&workspace.state_5d.effect_position, 0x10, 2.70000005f, H(u8 *, 0x2290), &workspace.state_5d.probe);
            }
            break;
        case 2:
            if (14.0f < H(float, 0xc38) && H(float, 0xc38) < 21.0f) {
                TransformMobyJointToWorld(H(u8 *, 0x2290), 3, &workspace.state_5d.effect_position);
                TransformMobyJointToWorld(H(u8 *, 0x2290), 4, &workspace.state_5d.midpoint);
                FastVecAdd(&workspace.state_5d.midpoint, &workspace.state_5d.effect_position, &workspace.state_5d.midpoint);
                FastVecScale(&workspace.state_5d.midpoint, &workspace.state_5d.midpoint, 0.5f);
                ProcessCollisionHit(&workspace.state_5d.midpoint, 0x10, 2.70000005f, H(u8 *, 0x2290), &workspace.state_5d.probe);
            }
            break;
        }
    }
    switch (H(short, 0xbfc)) {
    case 0: case 1:
        if (H(s32, 0xc2c) == 0 && 7.0f <= H(float, 0xc38) && H(float, 0xc38) < 15.6999998f)
            H(float, 0x1b0) = 0.400000036f;
        ApproachHeroSpeed(0.0500000007f, 0.0388888903f);
        ComputeHeroPushDirection(99999.0f);
        break;
    case 2:
        if (H(s32, 0xc2c) == 0 && 11.0f <= H(float, 0xc38) && H(float, 0xc38) < 20.0f)
            H(float, 0x1b0) = 0.5f;
        ApproachHeroSpeed(0.0416666679f, 0.0333333351f);
        ComputeHeroPushDirection(99999.0f);
        break;
    }
    SlideHeroAlongWalls(1);
    if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); goto finish; }
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;
}



case 0x5e:
{

    H(float, 0x1b0) = 0.0f;
    ApproachHeroSpeed(0.0f, 0.00491666701f);
    ClearVector128(&H(Vec4, 0xf0));
    ShrinkHeroVectorByAmount(0.00491666701f);
    if (H(s32, 0xc2c) == 0) {
        /* Ordered FP comparisons matter: retain the retail NaN fallthrough. */
        if (22.0f < H(float, 0xc38) && H(float, 0xc38) < 55.0f) {
            H(float, 0xc20) = 1.0f;
        } else if (H(s32, 0xc2c) == 0 && H(float, 0xc38) <= 22.0f) {
            TransformMobyJointToWorld(H(u8 *, 0x2290), 4, &workspace.state_5e.effect_position);
            PlaceKeyedObject(entry_object, &workspace.state_5e.effect_position, 1);
            H(float, 0xc20) = 1.0f;
        }
    }
    { if (H(s16, 0x34E)) { ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); CancelHeroVelocityIntoWall(); goto finish; } ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish; }
}



case 0x58:
{

    ResolveStickInputToDirection(0.216666684f, 0);
    BuildHeroRelativePoint(&workspace.state_58.effect_position, 1, 0.0f, 0.0f, -1.0f);
    SweepCollisionFromObject(H(u8 *, 0x2290), &workspace.state_58.effect_position, 0x30000,
                 3.5f, 2.0f, 1.0f, 0, 1, 0);
    if (H(short, 0x1e0) == 0) UpdateHeroAirborneSteering();
    ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0102777779f);
    if (GetViewSpaceHeight(&H(Vec4, 0xf0)) < -0.950000048f) {
        shared_speed = -0.950000048f;
        { SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_speed); goto finish; }
    }
    goto finish;
}



case 0x57:
{

    float first_angle, second_angle, turn;
    s32 i;
    FastDiffRots(H(float, 0x98), H(float, 0x1a0));
    for (i = 0; i < 3; ++i) {
        float angle = FastAddRotations(-0.785398245f, (float)i * 0.785398245f);
        BuildHeroRelativeOffset(&workspace.state_57.effect_position, 1, 1.79999995f, angle, 1.39999998f);
        SweepCollisionFromObject(H(u8 *, 0x2290), &workspace.state_57.effect_position, 0x04000000,
                     2.70000005f, 2.0f, 1.0f, 0, 1, 0);
    }
    shared_limit = 0.078539826f;
    ResolveStickInputToDirection(0.216666684f, 0);
    if (H(s32, 0x1b8) < 3) {
        H(u8, 0x40c) = 1;
        if (1.74532938f < FloatAbs(H(float, 0x1a8)) &&
            0.800000012f < H(float, 0x24b8)) H(u8, 0x40f) = 1;
    }
    first_angle = ReadPadFloatHistory(0);
    second_angle = ReadPadFloatHistory(2);
    if (2.61799407f < FastDiffRots(first_angle, second_angle) &&
        1.22173059f < FloatAbs(H(float, 0x1a8)) &&
        0.800000012f < H(float, 0x24b8)) {
        H(u8, 0x40f) = 1;
        H(u8, 0x40c) = 1;
    }
    if (FloatAbs(H(float, 0x1a8)) < 0.087266475f) H(u8, 0x40c) = 0;
    do {
    if (H(u8, 0x40f) != 0) {
        if (FloatAbs(H(float, 0x1a8)) < 0.069813177f) H(u8, 0x40f) = 0;
        if (H(u8, 0x40f) != 0) shared_limit = 0.107628651f;
    }
    shared_rate = 0.300000012f;
    } while (0);
    if (H(short, 0x1454) != 0) {
        UpdateHeroTurnFromAnimation();
    } else {
        H(float, 0x1458) = H(float, 0x98);
        qcopy(&H(Vec4, 0x1440), &H(Vec4, 0x0));
        SteerHeroHeading(0, 0.0274999999f, shared_rate, shared_limit);
    }
    ApproachHeroSpeed(0.0102777779f, 0.00555555569f);
    if (H(short, 0x1454) == 0) {
        turn = H(float, 0x1a4) * 17.0f;
        if (1.89999998f < turn) turn = 1.89999998f;
        else if (turn < -1.89999998f) turn = -1.89999998f;
        FLD(D_L22_0025DE90, float, 0x1494) = 0.0240000002f;
        FLD(D_L22_0025DE90, float, 0x1334) = 0.0270000007f;
        FLD(D_L22_0025DE90, float, 0x13E4) = 0.0199999996f;
        FLD(D_L22_0025DE90, float, 0x1498) = 0.300000012f;
        FLD(D_L22_0025DE90, float, 0x1338) = 0.300000012f;
        FLD(D_L22_0025DE90, float, 0x13E8) = 0.300000012f;
        FLD(D_L22_0025DE90, float, 0x12F0) = -turn * 0.200000003f;
        FLD(D_L22_0025DE90, float, 0x12F8) = turn * 0.370000005f;
        FLD(D_L22_0025DE90, float, 0x13A8) = turn * 0.569999993f;
    }
    if (H(u8, 0x40c) || H(short, 0x1454)) {
        if (H(short, 0x1454)) SetHeroPushDirection(&H(Vec4, 0x1440));
        else SetHeroPushDirection(&H(Vec4, 0x190));
    } else ComputeHeroPushDirection(99999.0f);
    SlideHeroAlongWalls(1);
    if (H(s16, 0x34E)) {
        ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); CancelHeroVelocityIntoWall();
    } else ApplyHeroModeTransform(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}



case 0x59:
case 0x5a:
{

    float length, elevation;
    vec_scale_to_length(&workspace.state_59.effect_position, &H(Vec4, 0xf0), 3.5f);
    AddTransformedPointToVector(H(u8 *, 0x2290), &workspace.state_59.effect_position, 0.0f, 0.0f, 2.0f);
    FastVecAdd(&workspace.state_59.effect_position, &workspace.state_59.effect_position, &H(Vec4, 0x80));
    SweepCollisionFromObject(H(u8 *, 0x2290), &workspace.state_59.effect_position, 0xb0000,
                 5.0f, 100.0f, 1.0f, 0, 1, 0);
    length = GetViewSpaceVectorLength(&H(Vec4, 0xf0));
    if (0.0833333358f < length) {
        FastVecScale(&H(Vec4, 0x190), &H(Vec4, 0xf0), -1.0f);
        SteerHeroHeading(0, 0.0500000007f, 0.200000003f, 12.833334f);
    }
    if (H(short, 0x34e)) ApproachValue(&length, 0.0f, 0.0194444451f);
    else length = length * 0.899999976f;
    elevation = GetViewSpaceHeight(&H(Vec4, 0xf0));
    SetViewSpaceVectorLength(&H(Vec4, 0xf0), &H(Vec4, 0xf0), length);
    shared_speed = elevation - 0.0152777778f;
    if (0.183333337f < shared_speed) shared_speed = 0.183333337f;
    { SetViewSpaceHeight(&H(Vec4, 0xf0), &H(Vec4, 0xf0), shared_speed); goto finish; }
}



case 0x37:
    if (H(u8*,0x2290)[0x43]==0x44) SteerHeroHeading(0,0.137f,0.25f,0.20362177f);
    else SteerHeroHeading(0,1.0f,0.1f,0.40724355f);
    goto finish;


case 0x60:
case 0x61:
    ClearVector128(&H(Vec4, 0xf0));
    goto finish;

    default: goto finish;
    }


finish:
    if (entry_substate != H(int, 0x2298)) H(int, 0x1C0) = 0;
    if (entry_animation != entry_object[0x43]) H(int, 0x1C4) = 0;
}
