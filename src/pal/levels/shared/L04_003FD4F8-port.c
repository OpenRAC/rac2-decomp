#include "common.h"

extern float func_00283CE0(int);
extern char *D_L04_001FE340[];
extern void func_002C96F8(void *, void *, void *, void *, float, float);
extern void func_002A05A8(void *);

#include "include_asm.h"

extern int func_002A9640(unsigned char *a0, int a1, int a2);

extern void func_002AB800(unsigned char *a0, unsigned char *a1);

extern void func_002AB8C0(unsigned char *a0, unsigned char *a1);

extern void *func_0029EFD0(void *a0);

extern void func_002A0F48(void *a0);

extern int func_002A8508(void *a0, int a1);

extern int func_002A77E0(int a0);

extern void func_L04_003F9078(unsigned char *a0);

#ifndef RAC2_T_Q16_B0E5D8F83
#define RAC2_T_Q16_B0E5D8F83
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
#endif

/* func_L04_003C8380 is in L04_003C8380-stream.c. */

extern char D_L04_001B9680[];
extern void func_00282F20(char *, char *, float);
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);

typedef union {
    Q16_B0e5d8f83 q;
    float f[4];
} Vec;

/* A moby class, as far as these functions read it. */
typedef struct {
    u8 pad00[0x0F];
    u8 f0F;                     /* 0x0F */
    int f10;                    /* 0x10: copied to the moby's +0x98 */
    u8 pad14[0x24 - 0x14];
    float scale;                /* 0x24 */
    u8 pad28[0x40 - 0x28];
    int f40;                    /* 0x40 */
    u16 modeBits;               /* 0x44: the moby's initial mode bits */
} MobyClass;

/* The moby, as far as func_L04_003EDD40 and func_L04_003F9ED0 read it. */
typedef struct Moby {
    u8 pad00[0x10];
    Vec position;               /* 0x10 */
    u8 state;                   /* 0x20 */
    u8 pad21[0x24 - 0x21];
    MobyClass *mclass;          /* 0x24 */
    u8 pad28[0x2C - 0x28];
    float scale;                /* 0x2C */
    u8 f30;                     /* 0x30 */
    u8 f31;                     /* 0x31 */
    s16 f32;                    /* 0x32 */
    u16 modeBits;               /* 0x34 */
    s16 f36;                    /* 0x36 */
    u8 pad38[0x40 - 0x38];
    u8 f40[4];                  /* 0x40 */
    u8 pad44[0x61 - 0x44];
    u8 f61;                     /* 0x61 */
    u8 f62;                     /* 0x62 */
    u8 pad63[0x68 - 0x63];
    void *vars;                 /* 0x68: the instance data */
    u8 pad6C[0x7F - 0x6C];
    u8 f7F;                     /* 0x7F */
    u8 pad80[0x98 - 0x80];
    int f98;                    /* 0x98 */
    u8 pad9C[0xA8 - 0x9C];
    u8 impactSlot;              /* 0xA8 */
    u8 padA9;
    s16 oClass;                 /* 0xAA */
    u8 padAC[0xB2 - 0xAC];
    s16 uid;                    /* 0xB2 */
    u8 padB4[0xB8 - 0xB4];
    struct Moby *parent;        /* 0xB8 */
    u8 fBC;                     /* 0xBC: func_L04_003F9ED0's hit: 1 surface, 2 moby */
    u8 padBD[0xF0 - 0xBD];
    Vec rotation;               /* 0xF0 */
} Moby;

/* The instance data of a moby that hands out children. */
typedef struct {
    u8 pad00[0x81];
    u8 childCount;              /* 0x81 */
    u8 pad82;
    u8 smallChildren;           /* 0x83: children start at a tenth of their class scale */
    int group;                  /* 0x84: the moby group the children come from */
} SpawnerVars;

/* What ref_L04_003EDD40_02 returns for a moby. */
typedef struct {
    u8 pad00[0x68];
    s16 f68;                    /* 0x68 */
    u8 pad6A[0x6C - 0x6A];
    int f6C;                    /* 0x6C */
    u8 pad70[0x94 - 0x70];
    int f94;                    /* 0x94 */
} ChildState;

/* What ref_L04_003EDD40_05 returns for a moby. */
typedef struct {
    float f00;                  /* 0x00 */
    s16 f04;                    /* 0x04 */
    u8 pad06[0x20 - 0x06];
    int f20;                    /* 0x20 */
    int f24;                    /* 0x24 */
} ChildInfo;

/* In level 04 these resolve to func_002A8600 (GetFirstMobyInGroup), func_0029F390,
   func_L00_00345AF0, func_002AB650, func_002A0F48, func_002AB1F0 and func_0026FEB8. */
extern int ref_L04_003EDD40_00(Moby **, int, int, int);
extern void ref_L04_003EDD40_01(Moby *);
extern ChildState *ref_L04_003EDD40_02(Moby *);
extern void ref_L04_003EDD40_03(Moby *);
extern void ref_L04_003EDD40_04(Moby *);
extern ChildInfo *ref_L04_003EDD40_05(Moby *);
extern void ref_L04_003EDD40_06(char *, int, int);
extern char ref_L04_003EDD40_07[];
extern int ref_L04_003EDD40_08[] __attribute__((sda));


/* func_L04_003F9320 is in L04_003C8380-shot.c. */

/* func_L04_003F9718 is in L04_003C8380-homing.c. */

/* func_L04_003F9C60 is in L04_003F9C60-zero.c. */

/* The probe func_002761F8 and func_00277F48 test with. */
typedef struct {
    float v[4];                 /* 0x00 */
    void *owner;                /* 0x10 */
    int flags;                  /* 0x14 */
    u8 mode;                    /* 0x18 */
    u8 enabled;                 /* 0x19 */
    u16 oClass;                 /* 0x1A: the class of owner */
    float radius;               /* 0x1C */
    int active;                 /* 0x20 */
} CollisionProbe;

/* The hit of the last collision probe: D_L04_001BFAC0's +0x20, which retail also
   addresses under its own symbol, D_L04_001BFAE0. */
typedef struct {
    Vec point;                  /* 0x00 */
    u8 pad10[0x20 - 0x10];
    Vec normal;                 /* 0x20 */
    Vec f30;                    /* 0x30 */
    Vec f40;                    /* 0x40 */
} CollisionHit;
/* func_L04_003FA350 is defined in L04_003FA350.c. */

/* The result of the last collision probe. */
typedef struct {
    u8 pad00[0x18];
    Moby *moby;                 /* 0x18: the moby hit, or 0 */
    int count;                  /* 0x1C: above 0 when a surface was hit */
    CollisionHit hit;           /* 0x20 */
} Collision;

/* The projectile's instance data. */
typedef struct {
    u8 pad00[0x20];
    Moby *ignored;              /* 0x20: the moby its probes pass through */
} ProjectileVars;

extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
/* The radius comes first: the EE ABI keeps the order within each register bank. */
extern int func_00277F48(float, void *, int, void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_001290E0(void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_PAL_L04_00410678(void *, void *, int, int);
extern Collision D_L04_001BFAC0;
extern CollisionHit D_L04_001BFAE0;

extern void ref_L04_003FA5A8_00(void *, float, float, float);
extern unsigned char *ref_L04_003FA5A8_01(void *, void *, void *, float *, float *, float *, float, float);
extern void ref_L04_003FA5A8_02(void *, void *, void *);
extern void ref_L04_003FA5A8_03(void *, void *, void *, void *, void *, void *, void *);

/* func_L04_003FA7E0 is defined in L04_003FA7E0.c. */


extern int func_002E5CF8(int, int, char *);

extern unsigned char *D_L04_001C3B40[];
extern float func_00283C80(float, float);
extern float func_00282E80(void *, void *);
extern float func_00282E48(char *, char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283C28(float);
extern float func_00283B98(float, float);
extern void func_002A8E20(void *, void *);
extern void func_002AF000(void *, float, float, float);

/* The impact record func_002A8E20 queues: the layout of Rac2Impact32 in engine.h,
   rounded up to whole quadwords as its stack slot is. */
typedef struct {
    float vector[4];
    void *source;
    int flags;
    unsigned char unk18, unk19;
    unsigned short objectClass;
    float strength;
    int unk20;
    int unk24;
    int pad[2];
} B990Impact;

/* Hits the mobys around m inside its firing cone, then traces the cone's edge rays and
   leaves an effect where one is blocked. gcse numbers the two spilled pointers in hash-bucket
   order, and retail's stack slots need at least 228 insns there: the argument locals, range
   and the initial values of angle, angle0, angle1, sign and i supply them, and leave no code. */
void func_PAL_L04_003FFB98(unsigned char *m, void *vars)
{
    unsigned char *v = vars;
    float radius = *(float *)(v + 0x70) * *(float *)(v + 0x7C);
    float angle = 0.0f, angle0 = 0.0f, angle1 = 0.0f, sign = 0.0f;
    int count, n, side, i = 0;
    int soundId = 10, soundArg = 0;
    int rayMask = 18;
    void *rayResult = 0;
    int sparkKind = 8, sparkArg = 0;
    if (radius < 0.75f) radius = 0.75f;
    n = func_00277F48(radius, m + 0x10, 16, *(void **)(v + 0x74), 0);
    for (count = 0; count < n; count++) {
        if (D_L04_001C3B40[count] == *(unsigned char **)(v + 0x74)) continue;
        if (*(float *)(v + 0x7C) > 0) {
            angle = func_00283248(*(float *)(D_L04_001C3B40[count] + 0x10) - *(float *)(m + 0x10),
                                  *(float *)(D_L04_001C3B40[count] + 0x14) - *(float *)(m + 0x14));
            if (func_00283C80(angle, *(float *)(m + 0xF8)) > 0.741765022277832f) continue;
            angle = func_00283248(func_00282E80(m + 0x10, D_L04_001C3B40[count] + 0x10),
                                  *(float *)(D_L04_001C3B40[count] + 0x18) - *(float *)(m + 0x18));
            if (func_00283C80(angle, -*(float *)(m + 0xF4)) > 0.523598849773407f) continue;
        }
        if (func_00282E48((char *)m + 0x10, (char *)D_L04_001C3B40[count] + 0x10) > radius * 0.75f) {
            B990Impact impact;
            impact.source = *(void **)(v + 0x74);
            impact.flags = 0x230000;
            impact.unk18 = 2;
            impact.unk19 = 3;
            impact.objectClass = *(unsigned short *)(m + 0xAA);
            impact.strength = 1.0f;
            impact.unk20 = 0x230000;
            angle = func_00283248(*(float *)(D_L04_001C3B40[count] + 0x10) - *(float *)(m + 0x10),
                                  *(float *)(D_L04_001C3B40[count] + 0x14) - *(float *)(m + 0x14));
            impact.vector[0] = func_00283180(angle);
            impact.vector[1] = func_00283198(angle);
            impact.vector[2] = 1.0f;
            impact.vector[3] = 5627.9248046875f;
            func_002A8E20(D_L04_001C3B40[count], &impact);
            func_002E5CF8(soundId, soundArg, *(void **)(v + 0x74));
        }
    }
    {
    float ray[3][4];
    float range = radius;
    for (side = 0; side < 2; side++) {
        sign = (side & 1) ? 1.0f : -1.0f;
        for (i = 0; i < 5; i++) {
            angle0 = func_00283C28(func_00283CE0(i) * sign * 0.1396263688802719f);
            angle1 = func_00283C28(func_00283CE0(i + 1) * sign * 0.1396263688802719f);
            func_002AF000(ray[0], range, func_00283B98(angle0, *(float *)(m + 0xF8)), -*(float *)(m + 0xF4));
            func_002AF000(ray[1], range, func_00283B98(angle1, *(float *)(m + 0xF8)), -*(float *)(m + 0xF4));
            func_00282CD8(ray[2], ray[0], m + 0x10);
            func_00282CD8(ray[2], ray[1], m + 0x10);
            if (func_002761F8(ray[0], ray[1], rayMask, *(void **)(v + 0x74), rayResult)) {
                func_002AF000(ray[2], 0.40000004f, *(float *)(m + 0xF8), -*(float *)(m + 0xF4));
                func_PAL_L04_00410678(&D_L04_001BFAE0, ray[2], sparkKind, sparkArg);
            }
        }
    }
    }
}

/* func_L04_003FBD80 is in the sibling file L04_003C8380-g8.c (it stores through $gp). */



typedef struct {
    unsigned char pad0[0x74];
    unsigned char active;
    unsigned char pad75[0x88 - 0x75];
    void *owner;
} L04_C678Slot;
typedef int L04_C678Quad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[0x74];
    unsigned char *owner;
    int timer;
    float age;
} L04_C678Vars;

extern int func_00282948(void *);
extern int func_00283CF0(float);
extern void func_0029F338(void *);
extern float func_002AA800(void *, int, float, float);
extern void func_002E59F8(int);
extern void func_L00_002E6DB8(void *, void *);
extern void func_PAL_L04_003FFB98(unsigned char *, void *);
extern void func_L04_003FBEF8(void);
extern unsigned char D_00188660[];
extern int D_L04_001B0488 __attribute__((sda));

/* func_L04_00400AB0 and func_L04_00400D48 are in L04_003C8380-path-g8.c. */

typedef union { Q16_B0e5d8f83 q; float f[4]; } EffectVector;
typedef struct { EffectVector row[4]; } EffectMatrix4;
extern int func_002A8600(unsigned char **, int, int, int);
extern int func_002A86E8(unsigned char **, unsigned char *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, char *);
extern float func_002AA2E8(float *, float, float);
extern int func_00282978(short *);

extern float func_00282E48(char *arg0, char *arg1);

extern char *D_001FE340[];