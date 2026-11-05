/* 6 November 2026, round 6: 8,440/8,440, 0/27, first diff now +0x9C0. Dropping the `hitMoby` local (read
 * D_L00_001BF200.hit directly) lets jump threading send the null-hit test straight to the count test, as retail.
 * Left: +0x9C0 bc1f lands on retail's hazard nop (reorg's new label follows the line note; if/else and
 * default-then-override phase forms do not move it); retail `high` is non-equivalent in $fp while loop 3's
 * high<<16 is a rematerialized REG_EQUIV and r2 is a folded, spilled 0x30: needs cse2 to know low/high in
 * loop 3's preheader; reassigning them before loop 3 folds everything, `low = 0x60` at loop 2's end breaks
 * loop 2, literal 0x7F in loop 2 makes high rematerialized. defs: inline array read shrinks; moving the
 * assignment does not swap v1/a0.
 */
/* 5 November 2026: own -g8 unit, `-O2 -G8 -ffunction-sections -g`; 8,440/8,440, 0/27. Retail's $fp=0x7F is
 * hoisted `high` (`high = 0x7F` set in loop 2's body plus alpha `high` in loop 3 reproduces it), but loop 3's
 * uses then stay sll, not REG_EQUIV constants. Also left: r2 = 0x30 spill, $fp/$s7 picks, defs-load regs.
 * Per-frame update of the hero-steered bot (class 0x81E): flight, collision,
 * attachment, idle effects and self-destruct burst. Not functional-gated.
 * USA v1.01/v2.00: 8,432/8,440 bytes, 0/27 placements in each, 2026-11-01.
 * Compile separately as L00_003AE900-g8.c: -O2 -G8 -ffunction-sections.
 * Earlier retained source: 8,412 bytes. Normal assignments of the aligned
 * 0x50-byte templates use the current compiler's quadword block moves; both copy
 * loops now reproduce retail. Keep the full templates and real matrix buffers.
 * The collision test and following state-4 test are separate: the call may change
 * the state. The old nested-if/else form incorrectly skipped the reload on failure.
 * Sound slots have a 0x70-byte stride after the runtime's 0x70-byte header.
 * Remaining: one FPR save/frame size, held-pose matrix pointer allocation, colour
 * constant folding in the spray loops, and sound-index register allocation.
 * Byte-sized colour locals do not resolve the constants. Diagnostic regalloc
 * dumps reproduce the normal object; none of this qualifies the complete body.
 * Earlier trials with flat matrix arrays, pointer locals and one/two-level inline
 * helpers did not settle the held-pose registers; do not repeat them unchanged.
 */
#include "common.h"

typedef int TI128_AE900 __attribute__((mode(TI)));
typedef union { TI128_AE900 q; float f[4]; int i[4]; } VecAE900;

/* One frame at 60 Hz, and degrees to radians, as the retail constants fold. */
#define FRAME_AE900 0.016666668f
#define DEG_AE900 0.017453294f
#define PI_AE900 3.1415927f

struct VarsAE900;

typedef struct MobyAE900 {
    char pad00[0x10];
    VecAE900 pos;                 /* 0x10 */
    unsigned char state;          /* 0x20 */
    char pad21[3];
    char *pClass;                 /* 0x24 */
    char pad28[0xC];
    unsigned short flags;         /* 0x34 */
    char pad36[0xC];
    unsigned char b42;            /* 0x42 */
    unsigned char b43;            /* 0x43 */
    char pad44[0x1C];
    unsigned char b60;            /* 0x60 */
    char pad61[7];
    struct VarsAE900 *vars;       /* 0x68 */
    char pad6C[0x2C];
    int collData;                 /* 0x98 */
    char pad9C[0xC];
    unsigned char bA8;            /* 0xA8 */
    char padA9;
    short oClass;                 /* 0xAA */
    char padAC[0x10];
    unsigned char bBC;            /* 0xBC */
    char padBD[3];
    char matrix[0x30];            /* 0xC0 */
    float rot[4];                 /* 0xF0 */
} MobyAE900;

typedef struct VarsAE900 {
    VecAE900 vel;                 /* 0x00: vel.f[2] is the vertical speed */
    char pad10[0x20];
    MobyAE900 *owner;             /* 0x30 */
    short timer34;                /* 0x34 */
    short s36;                    /* 0x36 */
    char pad38[8];
    float pull;                   /* 0x40 */
    char pad44[4];
    short timer48;                /* 0x48 */
    char pad4A[2];
    MobyAE900 *ground;            /* 0x4C */
    short inWater;                /* 0x50 */
    short bob;                    /* 0x52 */
    MobyAE900 *target;            /* 0x54 */
    int timer58;                  /* 0x58 */
    int i5C;                      /* 0x5C */
    float f60;                    /* 0x60 */
    float f64;                    /* 0x64 */
    int sound;                    /* 0x68 */
    float amp;                    /* 0x6C */
    float phase;                  /* 0x70 */
    int frame;                    /* 0x74 */
    int i78;                      /* 0x78 */
} VarsAE900;

typedef struct {
    char pad00[0x88];
    float z;                      /* 0x88 */
    char pad8C[0x33C - 0x8C];
    MobyAE900 *standing;          /* 0x33C */
    char pad340[0x1220 - 0x340];
    MobyAE900 *held;              /* 0x1220 */
    char pad1224[0x2290 - 0x1224];
    MobyAE900 *moby;              /* 0x2290 */
    char pad2294[0x22B4 - 0x2294];
    unsigned char b22B4;
    unsigned char b22B5;
    char pad22B6[9];
    unsigned char b22BF;
} HeroAE900;

typedef struct {
    char pad00[0x18];
    MobyAE900 *hit;               /* 0x18 */
    int count;                    /* 0x1C */
    VecAE900 point;               /* 0x20 */
    VecAE900 p30;                 /* 0x30 */
    VecAE900 normal;              /* 0x40 */
} CollAE900;

/* The record handed to the collision test (its fifth argument). */
typedef struct {
    VecAE900 dir;                 /* 0x00 */
    MobyAE900 *owner;             /* 0x10 */
    int flags;                    /* 0x14 */
    unsigned char b18;
    unsigned char b19;
    unsigned short oClass;        /* 0x1A */
    float damage;                 /* 0x1C */
    int i20;                      /* 0x20 */
} HitAE900;

/* 0xE0-byte weapon record: +4 upgraded flag, +0x70 a rate. */
typedef struct { char pad00[4]; unsigned char upgraded; char pad05[0x6B]; float rate; char pad74[0x6C]; } WeaponAE900 __attribute__((aligned(16)));

/* Sound state has a 0x70-byte header followed by 52 0x70-byte voices. */
typedef struct {
    unsigned int handle;
    unsigned char active;
    char unknown05[0x13];
    MobyAE900 *owner;
    char unknown1C[0x54];
} SlotAE900 __attribute__((aligned(16)));
typedef struct { char header[0x70]; SlotAE900 slots[52]; } SoundAE900;
#define SLOT_AE900(i) (D_00188660.slots[(i)])

/* 0x50-byte effect template copied to the stack for func_00312B70. */
typedef struct { VecAE900 v; char rest[0x40]; } TemplateAE900;

/* Four per-kind rates, 4-byte aligned: copied with unaligned doubleword moves. */
typedef struct { float v[4]; } RatesAE900;

/* Camera shake record: +0x160 amount, +0x168 frames, +0x16C counter. */
typedef struct { char pad000[0x160]; float amount; char pad164[4]; int frames; int counter; } ShakeAE900;

#define WEAPON_AE900 (D_00262570[D_00139568[0x22]])

extern HeroAE900 D_00189E20;
extern unsigned char D_00139568[];
extern WeaponAE900 D_00262570[];
extern SoundAE900 D_00188660;
extern CollAE900 D_L00_001BF200;
extern TemplateAE900 D_L00_002A2870;
extern TemplateAE900 D_L00_002A28C0;
extern RatesAE900 D_L00_001AF7E0;
extern int D_L00_001B19C8 MACRO_ADDR;
extern float D_L00_001AF7B4 __attribute__((sda));
extern int D_L00_001AF7B0 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda));
extern int D_L00_001B2638 __attribute__((sda));
extern VecAE900 D_L00_001B8DC0;
extern ShakeAE900 D_L00_001B8C80;
extern char D_L00_001C3280[];
extern MobyAE900 *D_L00_001FACE0[];
extern char D_L00_001FDEF8[];
extern char D_L00_001FE940[];

extern void func_L00_003ADEA0(void);
extern int func_L00_003AE550(VarsAE900 *, MobyAE900 *, int);
extern float func_L00_002EF548(float, float, float);
extern void *func_L00_0033AA40(void *, void *, unsigned int, float, float, int, float, int, int);
extern int func_L00_0031C998(int, int, float);
extern float func_00282DF0(void *);
extern char *func_002AD0B0(void *);
extern void func_00283410(void *, void *);
extern void func_00283658(void *, void *);
extern void func_00283788(void *, void *, void *);
extern void func_00283678(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_002A77E0(int);
extern float func_002A90F8(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void * func_002BF728(void *, void *, float, float);
extern void func_00282F70(void *, void *, float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern float func_00283180(float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern void * func_002BFB38(void *, void *, int, int);
extern int func_002ABB78(void *);
extern float func_002A89A8(void *, int, float);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002E59F8(int);
extern void func_002A7470(void *, int, int, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_00282978(void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern int func_00277258(void *, int, void *, float);
extern int func_00282948(void *);
extern void func_002AEF28(void *, void *, void *, float, float, float);
extern char *func_002A9640(void *, unsigned int, int);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_002ACAD0(void *, void *);
extern void func_0029F338(void *);
extern float func_00283B98(float, float);
extern void func_002A9850(void *, void *, void *, int, int, int, int, int, float, float, float);
extern float func_002A8A20(void *);
extern int func_002AAFA0(unsigned int, int);
extern char *func_002BCB00(float, void *, void *, int, int, int, int, int, int, int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_00283CF0(float);
extern char *func_002BCF18(void *, void *, int, int, float, int, int);
extern void func_002AF000(void *, float, float, float);
extern void * func_00312B70(void *, void *, int, int);
extern void func_002A9288(void *, float);

/* Leaves the current state: stops the owned sound and resets the fall. */
#define DETACH_AE900() \
    { \
        int sound; \
        moby->state = 0; \
        sound = vars->sound; \
        if (sound != -1) { \
            if (SLOT_AE900(sound).owner == moby && SLOT_AE900(sound).active) \
                func_002E59F8(sound); \
        } \
        vars->sound = -1; \
        vars->timer34 = 0x78; \
        vars->vel.f[2] = 0.0f; \
    }

/* Packs a particle colour (0xAABBGGRR); the components are not folded before the loops hoist them. */
static __inline__ int RgbaAE900(int r, int g, int b, int a)
{
    int c = (a << 24) | (g << 8) | (b << 16);

    return c | r;
}

/* Rotation matrix for half a turn about X. */
static __inline__ void HalfTurnAE900(VecAE900 *m)
{
    VecAE900 turn;

    turn.q = 0;
    turn.f[0] = PI_AE900;
    func_00283410(m, &turn);
}

/* Copies the owner's matrix into dst. */
static __inline__ void OwnerMatrixAE900(VecAE900 *dst, MobyAE900 *owner)
{
    func_00283658(dst, owner->matrix);
}

/* While held (state 1): the bot's matrix is its owner's, turned half a turn about X. */
static __inline__ void AlignToOwnerAE900(MobyAE900 *moby, VarsAE900 *vars)
{
    VecAE900 m1[4];
    VecAE900 m2[4];
    VecAE900 *rot = m1;
    VecAE900 *own;

    HalfTurnAE900(rot);
    own = m2;
    OwnerMatrixAE900(own, vars->owner);
    func_00283788(rot, own, rot);
    func_00283678(moby->matrix, rot);
}

void func_L00_003AE900(MobyAE900 *moby)
{
    TemplateAE900 small;
    TemplateAE900 big;
    VecAE900 impulse;
    VecAE900 prev;
    VecAE900 up;
    VarsAE900 *vars;
    char *landed;
    MobyAE900 *owner;

    small = D_L00_002A2870;
    big = D_L00_002A28C0;
    landed = 0;
    impulse.q = 0;
    impulse.f[2] = 2.0f * FRAME_AE900;
    up.q = 0;
    up.f[2] = 1.0f;
    vars = moby->vars;
    func_L00_003ADEA0();

    if ((D_00189E20.b22B5 != 0 || D_00189E20.b22BF != 0) && moby->state == 1)
        moby->flags |= 0x41;
    else
        moby->flags &= ~0x41;

    if (D_00189E20.held == 0 || D_00189E20.held->oClass != 0x81E) {
        if (moby->state == 1) {
            func_0029F338(moby);
            return;
        }
    }
    if (D_00189E20.b22B4 != 0) {
        if (moby->state == 1) {
            func_0029F338(moby);
            return;
        }
    }

    owner = vars->owner;
    if (owner != 0)
        if (owner->state != 0xFE)
            if (owner->state != 0xFD)
                if (owner->oClass == 0x81E && vars->s36 == 0 && func_00282DF0(vars) > 0.0f) {
                    if (D_00189E20.standing == 0 || func_002AD0B0(D_00189E20.standing) == 0) {
                        func_L00_003AE550(vars, moby, 1);
                    } else {
                        if (func_L00_003AE550(vars, moby, 0) == 0)
                            func_L00_003AE550(vars, moby, 2);
                    }
                }

    if (moby->state == 1) {
        if (D_00189E20.held == 0 || D_00189E20.held->oClass != 0x81E) {
            func_0029F338(moby);
            return;
        }
        AlignToOwnerAE900(moby, vars);
        moby->collData = 0;
        moby->flags |= 0x100;
        return;
    } else {
        HitAE900 hit;
        VecAE900 t120;
        VecAE900 t130;
        VecAE900 t140;
        VecAE900 t150;
        VecAE900 t160;
        VecAE900 t170;
        VecAE900 t180;
        float t;
        float dist;
        float water;
        MobyAE900 *target;

        moby->flags &= ~0x100;
        qcopy_nc(&prev, &moby->pos);
        if (!(moby->state & 4)) {
            func_00282CC0(&moby->pos, &moby->pos, &vars->vel);
            if (vars->inWater == 0) {
                vars->vel.f[2] -= 9.8f / 60.0f / 60.0f;
            } else {
                vars->vel.f[2] -= 0.98f / 60.0f / 60.0f;
                if (func_002A77E0(5) == 0) {
                    float height = func_002A90F8(&moby->pos, &hit.dir);
                    func_00282D30(&hit.dir, &vars->vel, 0.25f);
                    func_002BF728(&moby->pos, &hit.dir, func_002A7878(0.05f, 0.1f) * 210000.0f, height);
                }
            }
        }
        hit.owner = moby;
        hit.flags = 0x830000;
        hit.i20 = 1;
        hit.damage = WEAPON_AE900.rate;
        qcopy(&hit.dir, &vars->vel);
        func_00282F70(&hit.dir, &hit.dir, 1.0f);
        hit.b18 = 2;
        hit.dir.f[3] = 5627.925f;
        hit.b19 = 1;
        hit.oClass = moby->oClass;
        hit.dir.f[2] = 1.0f;
        moby->pos.f[2] -= 0.4f;
        t = func_00283CE0(D_L00_001B19C8 - vars->frame) / D_L00_001AF7B4;
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        moby->pos.f[2] -= vars->amp * func_00283198(vars->phase) * t;

        if (!(moby->state & 4) && func_002761F8(&prev, &moby->pos, 0x10, moby, &hit)) {
            if (vars->inWater == 0 && func_00278E78() == 0 && vars->vel.f[2] < 0.0f) {
                char *splash;
                int i;

                func_002FD1B8(D_L00_001B2630, D_L00_001B2638, 1, moby->pos.f[0], moby->pos.f[1], 0.5f, -0.35f);
                vars->inWater = 1;
                func_00282C88(vars);
                vars->vel.f[2] = -1.5f * FRAME_AE900;
                t120.f[0] = moby->pos.f[0];
                t120.f[1] = moby->pos.f[1];
                t120.f[2] = D_L00_001BF200.point.f[2];
                splash = func_00312D58(&t120, 2.0f);
                if (splash)
                    splash[0x23] = 0x70;
                for (i = 0; i < 16; i++) {
                    float a = func_002A7940();
                    float r = func_002A7878(0.0f, 3.0f * FRAME_AE900);
                    int life;

                    t130.f[0] = func_00283180(a) * r;
                    t130.f[1] = func_00283198(a) * r;
                    t130.f[2] = func_002A7878(3.0f * FRAME_AE900, 6.5f * FRAME_AE900);
                    life = func_002A7820(90, 120);
                    func_002BFB38(&t120, &t130, func_002A77E0(2), life);
                }
            } else if (vars->inWater != 0 || func_00278E78() != 0) {
                if (D_L00_001BF200.hit) {
                    if (func_002ABB78(D_L00_001BF200.hit) || (D_L00_001BF200.hit->flags & 0x1000)) {
                        if (D_L00_001BF200.hit->oClass != moby->oClass && D_L00_001BF200.hit != D_00189E20.moby
                            && D_L00_001BF200.hit != vars->owner) {
                            moby->bBC = 1;
                            if (moby->state != 1) {
                                qcopy(&moby->pos, &D_L00_001BF200.point);
                                moby->pos.f[2] = func_002A89A8(&moby->pos, 0, 0.5f);
                            }
                            goto settled;
                        }
                    }
                }
                if (D_L00_001BF200.hit && D_L00_001BF200.hit->oClass == moby->oClass) {
                    func_00282CF0(&D_L00_001BF200.normal, &moby->pos, &D_L00_001BF200.hit->pos);
                    if (vars->vel.f[2] < -9.8f * FRAME_AE900) {
                        moby->bBC = 1;
                        qcopy(&moby->pos, &D_L00_001BF200.point);
                        func_00283028(&impulse, &vars->vel, &D_L00_001BF200.normal);
                        func_00282F20(&impulse, &impulse, 2.0f * FRAME_AE900);
                        func_00282F20(&up, &D_L00_001BF200.normal, 1.0f);
                    } else {
                        qcopy(&moby->pos, &D_L00_001BF200.point);
                        func_00282F20(&t120, &D_L00_001BF200.normal, 9.7f / 3600.0f);
                        func_00282CC0(&moby->pos, &moby->pos, &t120);
                        func_00283028(&vars->vel, &vars->vel, &D_L00_001BF200.normal);
                        func_00282D30(&vars->vel, &vars->vel, 0.4f);
                        func_00282F20(&t120, &D_L00_001BF200.normal, 1.0f);
                        func_00282DB0(&t120, &up);
                        qcopy(&t130, &D_L00_001BF200.normal);
                        goto align;
                    }
                } else if ((D_L00_001BF200.hit && D_L00_001BF200.hit != D_00189E20.moby && D_L00_001BF200.hit != vars->owner) || D_L00_001BF200.count > 0) {
                    if (vars->inWater != 0 || func_00278E78() == 0 || vars->vel.f[2] < -9.8f * FRAME_AE900) {
                        moby->bBC = 1;
                        qcopy(&moby->pos, &D_L00_001BF200.point);
                        func_00283028(&impulse, &vars->vel, &D_L00_001BF200.normal);
                        func_00282F20(&impulse, &impulse, 2.0f * FRAME_AE900);
                        func_00282F20(&up, &D_L00_001BF200.normal, 1.0f);
                    } else {
                        MobyAE900 *under = D_L00_001BF200.hit;

                        if (under)
                            landed = func_002AD0B0(under);
                        qcopy(&moby->pos, &D_L00_001BF200.point);
                        func_00282F20(&t120, &D_L00_001BF200.normal, 9.7f / 3600.0f);
                        func_00282CC0(&moby->pos, &moby->pos, &t120);
                        t150.q = vars->vel.q;
                        func_00283028(&vars->vel, &vars->vel, &D_L00_001BF200.normal);
                        func_00282D30(&vars->vel, &vars->vel, 0.6f);
                        vars->vel.f[2] *= 0.5f;
                        if (vars->amp == 0.0f) {
                            vars->amp = func_00282C48(t150.f[2]) * 2.0f;
                            vars->phase = (t150.f[2] > 0.0f) ? 45.0f * DEG_AE900 : -135.0f * DEG_AE900;
                            vars->frame = D_L00_001B19C8;
                        }
                        func_00282F20(&t120, &D_L00_001BF200.normal, 1.0f);
                        if (func_00282DB0(&t120, &up) > 0.707f) {
                            if (t150.f[2] < 0.0f) {
                                float floor = func_002A89A8(&moby->pos, 0, 0.5f);

                                if (moby->pos.f[2] < floor)
                                    moby->pos.f[2] = floor;
                                vars->vel.f[2] = -vars->vel.f[2];
                                if (func_00282DF0(vars) < 0.5f * FRAME_AE900 || landed) {
                                    func_00282C88(vars);
                                    moby->state |= 4;
                                    moby->collData = *(int *)(moby->pClass + 0x10);
                                    if (D_L00_001BF200.hit && landed)
                                        vars->ground = D_L00_001BF200.hit;
                                }
                            }
                        }
                        qcopy(&t130, &D_L00_001BF200.normal);
                    align:
                        t140.f[0] = t130.f[0] * func_00283180(moby->rot[2]) + t130.f[1] * func_00283198(moby->rot[2]);
                        t140.f[1] = t130.f[1] * func_00283180(moby->rot[2]) - t130.f[0] * func_00283198(moby->rot[2]);
                        t140.f[2] = t130.f[2];
                        moby->rot[0] = func_L00_002EF548(moby->rot[0],
                            -func_00283248(func_00282C10(t140.f[0] * t140.f[0] + t140.f[2] * t140.f[2]), t140.f[1]),
                            PI_AE900 * FRAME_AE900);
                        moby->rot[1] = func_L00_002EF548(moby->rot[1], func_00283248(t140.f[2], t140.f[0]), PI_AE900 * FRAME_AE900);
                    }
                }
            }
        } else if (moby->state & 4) {
            float floor = func_002A89A8(&moby->pos, 0, 0.5f);

            if (vars->ground) {
                if (vars->ground->state != 0xFE)
                    if (vars->ground->state != 0xFD)
                        goto alive;
                moby->bBC = 1;
                vars->ground = 0;
                goto check;
            alive:
                if (D_L00_001BF200.hit) {
                    landed = func_002AD0B0(D_L00_001BF200.hit);
                    if (landed)
                        func_002AD0E0(moby, vars->ground, &moby->pos, moby->rot, &moby->pos, moby->rot);
                }
            check:
                if (!landed) {
                    DETACH_AE900();
                    vars->ground = 0;
                }
            } else if (!(moby->state & 8)) {
                if (moby->pos.f[2] - floor < 1.0f / 90.0f) {
                    moby->pos.f[2] = floor;
                    vars->timer34 = 0;
                    if (D_L00_001BF200.hit && func_002AD0B0(D_L00_001BF200.hit))
                        vars->ground = D_L00_001BF200.hit;
                } else {
                    DETACH_AE900();
                }
            }
            target = vars->target;
            if (target == 0)
                goto lost;
            if (target->state == 0xFE)
                goto lost;
            if (target->state == 0xFD)
                goto lost;
            if (target->flags & 0x1000)
                goto kept;
        lost:
            if (moby->state & 8) {
                DETACH_AE900();
                vars->target = 0;
                if (moby->b43)
                    func_002A7470(moby, 0, 0, 10);
            }
        kept:
            if (vars->target != 0 && (moby->state & 8)) {
                t130.q = moby->pos.q;
                if (moby->b60 & 2) {
                    if (moby->b42 == 1 && moby->b43 != 2)
                        func_002A7470(moby, 2, 0, 10);
                }
                if (!func_002E59B0(moby, vars->sound))
                    vars->sound = func_002E5CF8(1, 4, moby);
                vars->pull += 0.25f * FRAME_AE900;
                if (vars->pull > 16.0f * FRAME_AE900)
                    vars->pull = 16.0f * FRAME_AE900;
                if (vars->bob == 1) {
                    moby->pos.f[2] += 0.05f;
                    if (func_00282978(&vars->timer48)) {
                        vars->timer48 = 7;
                        vars->bob = 2;
                    }
                } else if (vars->bob == 2) {
                    moby->pos.f[2] -= 0.05f;
                    if (func_00282978(&vars->timer48))
                        vars->bob = 0;
                }
                func_00282CF0(&t120, &vars->target->pos, &moby->pos);
                func_00282F20(&t120, &t120, vars->pull);
                func_00282CC0(&moby->pos, &moby->pos, &t120);
                func_002A8C00(&t140, moby, 0x10000, &t120, WEAPON_AE900.rate);
                qcopy(&t170, &moby->pos);
                t170.f[2] += 0.35f;
                if (func_00277F48(&t170, 0x10, moby, &t140, 0.35f)) {
                    MobyAE900 *blocker = D_L00_001BF200.hit;

                    if (blocker && blocker->oClass != 0x363 && blocker->oClass != 0x81F && blocker->oClass != 0x458
                        && blocker->oClass != 0x365 && blocker->oClass != 0x367)
                        moby->bBC = 1;
                }
                qcopy(&t170, &moby->pos);
                t170.f[2] += 0.25f;
                if (func_00277258(&t170, 0, moby, 0.25f)) {
                    func_00282CF0(&t180, &D_L00_001BF200.p30, &t170);
                    func_00282CC0(&moby->pos, &moby->pos, &t180);
                }
                if (func_00282948(&vars->timer58))
                    moby->bBC = 1;
            }
            func_002AEF28(moby, &vars->f60, &vars->f64, 30.0f * DEG_AE900, 30.0f * DEG_AE900 * FRAME_AE900,
                          17.0f * DEG_AE900 * FRAME_AE900);
            if (moby->state & 4) {
                func_00282CF0(&t120, &moby->pos, &prev);
                vars->vel.q = t120.q;
            }
        }
    settled:
        if (!(moby->state & 2)) {
            if (func_00282978(&vars->timer34)) {
                moby->state |= 2;
                vars->target = 0;
            }
        }
        {
            char *link = func_002A9640(moby, 0x830000, 0);

            if (link && *(MobyAE900 **)(link + 0x20) && (*(MobyAE900 **)(link + 0x20))->oClass != moby->oClass)
                moby->bBC = 1;
        }
        moby->bA8 = 0xFF;
        if (moby->state & 2) {
            if (!(moby->state & 4)
                || (func_00282E80(&D_00189E20.moby->pos, &moby->pos) < 0.75f
                    && func_00282C48(moby->pos.f[2] - D_00189E20.z) < 0.25f && (moby->state & 8))) {
                moby->bBC = 1;
            } else if (func_00282E48(&D_00189E20.moby->pos, &moby->pos) < 0.75f) {
                func_00282CF0(&t140, &moby->pos, &D_00189E20.moby->pos);
                t120.q = t140.q;
                func_00282F20(&t120, &t120, 0.75f);
                func_00282CC0(&t140, &D_00189E20.moby->pos, &t120);
                t130.q = t140.q;
                func_002A7EA0(moby, &moby->pos, &t130, 0.4f, 0.25f, 0.25f, 30.0f * DEG_AE900, 0);
            } else {
                int i = 0;
                MobyAE900 *other = D_L00_001FACE0[0];

                while (other) {
                    if (!(func_00282E48(&moby->pos, &other->pos) > 30.0f)) {
                        if (func_00282E48(&moby->pos, &other->pos) < 0.75f) {
                            moby->bBC = 1;
                            break;
                        }
                    }
                    i++;
                    other = D_L00_001FACE0[i];
                }
            }
        }
        vars->i78 = 0;
        if (vars->i5C < 0 || D_L00_001AF7B0 != 0) {
            func_002AC728(moby, &moby->pos, -1, 0.33f, 13.0f);
            func_002ACAD0(moby, D_L00_001FDEF8);
            func_0029F338(moby);
        }
        if (vars->amp > 0.05f) {
            vars->amp *= 0.988f;
            if (vars->amp < 0.05f)
                vars->amp = 0.05f;
        }
        t = func_00283CE0(D_L00_001B19C8 - vars->frame) / D_L00_001AF7B4;
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        vars->phase = func_00283B98(vars->phase, 360.0f * DEG_AE900 * FRAME_AE900);
        moby->pos.f[2] = moby->pos.f[2] + vars->amp * func_00283198(vars->phase) * t + 0.4f;
        if (moby->bBC) {
            dist = func_00282E80(&moby->pos, &D_L00_001B8DC0);
            if (vars->inWater == 0) {
                float radius = 2.0f;
                int count;

                if (WEAPON_AE900.upgraded)
                    radius = 3.0f;
                count = func_00277F48(&moby->pos, 0x10, moby, 0, radius);
                t120.q = moby->pos.q;
                func_002A9850(moby, &t120, D_L00_001C3280, count, 0, 0x810000, 4, 1, WEAPON_AE900.rate, 0.25f, 1.5f);
            }
            water = func_002A8A20(&moby->pos);
            if (vars->inWater != 0) {
                float surface;
                int i;

                t120.q = moby->pos.q;
                t120.f[2] += 3.5f;
                surface = func_002A89A8(&t120, 0, 0.5f);
                for (i = 0; i < 150; i++) {
                    t140.q = 0;
                    t140.f[0] = func_002A7878(-1.0f, 1.0f);
                    t140.f[1] = func_002A7878(-1.0f, 1.0f);
                    t140.f[2] = func_002A7878(-0.5f, -2.0f);
                    t130.q = t140.q;
                    func_00282F20(&t130, &t130, func_002A7878(4.0f * FRAME_AE900, 8.0f * FRAME_AE900));
                    func_002BF728(&moby->pos, &t130, func_002A7878(0.05f, 0.1f) * 210000.0f, surface);
                }
                {
                int low = 0x60;
                int high = 0x7F;
                float half = 0.5f;

                for (i = 0; i < 150; i++) {
                    float r;
                    float a;

                    t140.q = 0;
                    t140.f[0] = func_002A7878(-0.75f * FRAME_AE900, 0.75f * FRAME_AE900);
                    t140.f[1] = func_002A7878(-0.75f * FRAME_AE900, 0.75f * FRAME_AE900);
                    t140.f[2] = func_002A7878(4.0f * FRAME_AE900, 16.0f * FRAME_AE900);
                    t130.q = t140.q;
                    r = func_002A7878(0.0f, 0.35f);
                    a = func_002A7940();
                    t140.f[0] = func_00283180(a) * r;
                    t140.f[1] = func_00283198(a) * r;
                    t140.f[2] = 0.0f;
                    func_00282CC0(&t140, &t140, &moby->pos);
                    t140.f[2] = surface + half;
                    t130.f[2] -= r * (8.0f * FRAME_AE900);
                    func_L00_0033AA40(&t140, &t130, 0, func_002A7878(0.35f, 1.25f), surface,
                                      RgbaAE900(low, low, high, 0x16), 1.0f / 180.0f, RgbaAE900(low, low, high, 0), 1);
                }
                for (i = 0; i < 20; i++) {
                    int c1;
                    int c2;
                    char **defs;

                    c1 = func_L00_0031C998(0x7F000000, RgbaAE900(0x60, 0x60, high, 0x7F), func_002A7878(0.25f, 1.0f));
                    c2 = func_L00_0031C998(0, RgbaAE900(low >> 1, 0x30, 0x3F, 0), func_002A7878(0.5f, 1.0f));
                    t140.f[0] = func_002A7878(-3.0f, 3.0f);
                    t140.f[1] = func_002A7878(-3.0f, 3.0f);
                    t140.f[2] = func_002A7878(4.0f * FRAME_AE900, 14.0f * FRAME_AE900);
                    func_00282F20(&t140, &t140, func_002A7878(1.5f, 3.0f) * FRAME_AE900);
                    t140.f[2] = func_002A7878(3.0f, 6.0f) * FRAME_AE900;
                    t130.q = moby->pos.q;
                    t130.f[2] = surface;
                    defs = (char **)D_L00_001FE940;
                    c1 = func_002AAFA0(c1, WEAPON_AE900.upgraded != 0);
                    c2 = func_002AAFA0(c2, WEAPON_AE900.upgraded != 0);
                    func_002BCB00(func_002A7878(0.15f * 210000.0f, 0.25f * 210000.0f), &t130, &t140, c1, c2,
                                  func_002A7820(90, 150), 1, *(unsigned char *)defs[11], -1, 0);
                }
                }
            } else if (water + 2.0f < moby->pos.f[2]) {
                func_00282C88(&t120);
                func_002ABBB8(moby, &t120, 0, 0.0f, 0.0f, 3, 3, 5, 2.0f, 1.0f, 4.0f, 1.0f, 2, 7.0f, 0, 1, -1,
                              WEAPON_AE900.upgraded != 0, 0x810001);
            } else {
                float scale = 1.0f;
                int count;
                int i;

                if (WEAPON_AE900.upgraded)
                    scale = 1.5f;
                count = func_00283CF0(dist * 15.0f);
                for (i = 0; i < count; i++) {
                    int kind = func_002A77E0(4);
                    RatesAE900 *rates = (RatesAE900 *)&t120;
                    float r;
                    float a;

                    *rates = D_L00_001AF7E0;
                    t140.q = 0;
                    t140.f[0] = func_002A7878(-0.5f * FRAME_AE900, 0.5f * FRAME_AE900) * scale;
                    t140.f[1] = func_002A7878(-0.5f * FRAME_AE900, 0.5f * FRAME_AE900) * scale;
                    t140.f[2] = func_002A7878(4.0f * FRAME_AE900, rates->v[kind]) * scale;
                    t130.q = t140.q;
                    r = func_002A7878(0.0f, kind == 1 ? 0.5f : 0.25f) * scale;
                    a = func_002A7940();
                    t140.f[0] = func_00283180(a) * r;
                    t140.f[1] = func_00283198(a) * r;
                    t140.i[2] = 0;
                    func_00282CC0(&t140, &t140, &moby->pos);
                    t140.f[2] -= r * func_00283180(0.785398f);
                    t130.f[2] -= r * (8.0f * FRAME_AE900);
                    switch (kind) {
                    case 0: {
                        int c = func_002AAFA0(0x1F101820, WEAPON_AE900.upgraded != 0);
                        float f = func_002A7878(200000.0f, 300000.0f) * scale;
                        func_002BCF18(&t140, &t130, c, 0x101010, f, func_002A7820(180, 240), 0);
                        break;
                    }
                    case 1: {
                        int c1 = func_002AAFA0(0x3F081020, WEAPON_AE900.upgraded != 0);
                        int c2 = func_002AAFA0(0x0F081020, WEAPON_AE900.upgraded != 0);
                        func_002BCF18(&t140, &t130, c1, c2, func_002A7878(50000.0f, 100000.0f) * scale, 180, 1);
                        break;
                    }
                    case 2: {
                        int color;
                        int c1;
                        int c2;
                        float f;
                        int roll = func_002A77E0(100);

                        color = 0x2F486078;
                        if (roll <= 39)
                            color = 0x5FF8F8F8;
                        c1 = func_002AAFA0(color, WEAPON_AE900.upgraded != 0);
                        c2 = func_002AAFA0(0x0F000020, WEAPON_AE900.upgraded != 0);
                        f = scale * 150000.0f;
                        func_002BCF18(&t140, &t130, c1, c2, f, func_002A7820(30, 45), 2);
                        break;
                    }
                    case 3: {
                        int c1 = func_L00_0031C998(0x7F000000, 0x7F182030, func_002A7878(0.25f, 1.0f));
                        int c2 = func_L00_0031C998(0, 0x5F5F5F, func_002A7878(0.5f, 1.0f));
                        float f;

                        c1 = func_002AAFA0(c1, WEAPON_AE900.upgraded != 0);
                        c2 = func_002AAFA0(c2, WEAPON_AE900.upgraded != 0);
                        func_002AF000(&t130, func_002A7878(0.0f, 1.0f) * FRAME_AE900, a, func_002A7940());
                        f = func_002A7878(200000.0f, 300000.0f) * scale;
                        func_002BCF18(&t140, &t130, c1, c2, f, func_002A7820(240, 300), 3);
                        break;
                    }
                    }
                }
            }
            moby->bBC = 0;
            if (WEAPON_AE900.upgraded)
                func_002E5CF8(3, 0, moby);
            else
                func_002E5CF8(2, 0, moby);
            {
                ShakeAE900 *shake = &D_L00_001B8C80;

                if (dist < 20.0f)
                    shake->amount = 0.4f - dist * 0.0175f;
                else
                    shake->amount = 0.4f - 20.0f * 0.0175f;
            }
            D_L00_001B8C80.counter = 0;
            D_L00_001B8C80.frames = 25;
            if (WEAPON_AE900.upgraded)
                func_00312B70(&big, &moby->pos, 0, 0);
            else
                func_00312B70(&small, &moby->pos, 0, 0);
            func_002ACAD0(moby, D_L00_001FDEF8);
            func_0029F338(moby);
        } else {
            func_002A9288(moby, 0.25f);
        }
    }
}
