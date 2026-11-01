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

/* Emits paired particles with opposite spin and randomized velocities. */
void func_L04_003E5830(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L04_001B9680, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.0166666675f;
        func_00282CC0(origin, pos, offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 60, size * 0.1f, size, 0x80CA00CB, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


void *func_L04_003E5E40(unsigned char *a0, void *a1, float f12) {
    unsigned char *obj = func_0029EFD0(a1);

    if (obj != 0) {
        obj[0x30] = 0xFF;
        obj[0x31] = 1;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        obj[0x20] = 0;
        *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24) * f12;
        *(Q16_B0e5d8f83 *)(obj + 0x10) = *(Q16_B0e5d8f83 *)(a0 + 0x10);
        *(Q16_B0e5d8f83 *)(obj + 0xF0) = *(Q16_B0e5d8f83 *)(a0 + 0xF0);
        obj[0x62] = 1;
        func_002A0F48(obj);
    }
    return obj;
}

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

/* Takes the first moby of the parent's group as a new child: places it at position with
   its class defaults, links it to the parent and counts it. Returns the child, or 0 when
   there is no parent or no moby to take (which is reported with the parent's uid). */
Moby *func_L04_003EDD40(Moby *parent, Vec *position)
{
    Moby *child;
    Moby *result;
    SpawnerVars *vars;
    ChildInfo *info;
    Q16_B0e5d8f83 startCopy;
    float *start = (float *)&startCopy;

    *(Q16_B0e5d8f83 *)start = position->q;
    if (!parent)
        return 0;
    result = 0;
    vars = parent->vars;
    child = 0;
    if (!ref_L04_003EDD40_00(&child, vars->group, 1, 1)) {
        vars->childCount++;
        {
            Moby *copy = child;
            qcopy(&copy->position, start);
            copy->position.f[3] = 0;
        }
        child->state = 0;
        child->fBC = 0;
        child->modeBits = child->mclass->modeBits;
        child->scale = child->mclass->scale;
        child->f30 = 255;
        child->f32 = 255;
        child->f31 = 1;
        child->f40[0] = 0;
        child->f40[1] = 0;
        child->f40[2] = 0;
        child->f40[3] = 0;
        ref_L04_003EDD40_01(child);
        if (child->mclass->f40)
            child->modeBits |= 0x10;
        if (child->mclass->f0F)
            child->modeBits |= 0x400;
        child->f36 = 0x7F80;
        child->f61 = 255;
        child->f62 = 255;
        child->impactSlot = 255;
        if (vars->smallChildren)
            child->scale = child->mclass->scale * 0.1f;
        {
            ChildState *childState = ref_L04_003EDD40_02(child);
            if (childState) {
                childState->f94 = 0;
                childState->f68 = 0;
                childState->f6C = 0;
            }
        }
        child->parent = parent;
        child->f98 = child->mclass->f10;
        ref_L04_003EDD40_03(child);
        ref_L04_003EDD40_04(child);
        result = child;
        info = ref_L04_003EDD40_05(result);
        if (info) {
            info->f24 = 0;
            info->f20 = 0;
            info->f00 = (float)info->f04;
        }
        child->f7F = 0;
    } else {
        ref_L04_003EDD40_06(ref_L04_003EDD40_07, parent->uid, ref_L04_003EDD40_08[0]);
    }
    return result;
}

void func_L04_003EDF80(unsigned char *a0, unsigned char *a1) {
    if (func_002A9640(a0, 0x10000, 0) != 0) {
        a0[0x20] = 2;
        a1[0x57] = 0x78;
        func_002AB800(a0, a1 + 0x50);
    }
    a0[0xA8] = 0xFF;
    func_002AB8C0(a0, a1 + 0x50);
}

/* Stamps byte 0x81 from the per-record lookup, then walks the twenty slots: a slot whose
   object is live (not in either harness state) without the 0xB66 mark raises the count,
   every other slot is remembered in the returned index (-1 when all twenty pass). */
int func_L04_003EDFF0(unsigned char *a0, char *a1)
{
    char *s0 = a1;
    int i;
    int last = -1;

    *(unsigned char *)(s0 + 0x81) = func_002A8508(*(void **)(s0 + 0x84), -1);
    for (i = 0; i < 20; i++) {
        char *e = *(char **)(s0 + 0xA0 + i * 4);

        if (e != 0 && *(short *)(e + 0xAA) == 0xB66
            && *(unsigned char *)(e + 0x20) != 0xFE
            && *(unsigned char *)(e + 0x20) != 0xFD) {
            *(unsigned char *)(s0 + 0x81) = *(unsigned char *)(s0 + 0x81) + 1;
        } else {
            last = i;
        }
    }
    return last;
}

INCLUDE_ASM("asm/levels", func_L04_003EE090);



void func_L04_003F5F30(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    unsigned int *q;
    unsigned int v;
    int i;
    int j;

    p = (float *)(obj + 0x14);
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x24) = -1.0f;
    *(float *)(obj + 0x28) = -2.25f;
    *(float *)(obj + 0x2C) = 1.25f;
    *(float *)(obj + 0x30) = 2.5f;
    j = 3;
    q = (unsigned int *)(obj + 0x40);
    v = 0xFF;
    for (; j >= 0; j--) {
        *q = v;
        q--;
        v -= 0x40;
    }
    *(float *)(obj + 0x44) = 2.0f;
    *(float *)(obj + 0x48) = 2.5f;
    *(float *)(obj + 0x4C) = 2.5f;
    *(float *)(obj + 0x50) = 2.0f;
}


void func_L04_003F8FA0(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    unsigned int *q;
    unsigned int v;
    int i;
    int j;

    p = (float *)(obj + 0x10);
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x20) = -1.0f;
    *(float *)(obj + 0x24) = -2.25f;
    *(float *)(obj + 0x28) = 1.25f;
    *(float *)(obj + 0x2C) = 2.5f;
    j = 3;
    q = (unsigned int *)(obj + 0x3C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *q = v;
        q--;
        v -= 0x40;
    }
    *(float *)(obj + 0x40) = 2.0f;
    *(float *)(obj + 0x44) = 2.5f;
    *(float *)(obj + 0x48) = 2.5f;
    *(float *)(obj + 0x4C) = 2.0f;
}


INCLUDE_ASM("asm/levels", func_L04_003F9320);

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
extern void func_L04_0040C0C0(void *, void *, int, int);
extern Collision D_L04_001BFAC0;
extern CollisionHit D_L04_001BFAE0;

/* Sweeps a projectile from *position by direction (a line probe over the whole move and,
   when that is clear, a 0.5 sphere probe every 0.49 units) and works out its response.
   Hitting a moby other than the ignored one sets fBC to 2, moves onto that moby (or
   stays, for class 0xA1F) and returns the projectile. A surface whose normal lies 45 to
   90 degrees from direction bends direction by the normal, re-aims the projectile and
   marks the hit point; any other surface hit sets fBC to 1 and moves to the hit point.
   Moby and stopping surface hits fill response, hitNormal and hitDelta. The final
   position is written back to *position; the result is 0 unless a moby was hit. */
Moby *func_L04_003F9ED0(Moby *projectile, ProjectileVars *vars, float *position,
    float *direction, float *response, float *hitNormal, float *hitDelta)
{
    float pos[4];
    float unit[4];
    float step[4];
    CollisionProbe probe;
    float forward[4];
    float hitPoint[4];
    float target[4];
    Collision *collision;
    Moby *hitMoby;
    Moby *result = 0;
    float remaining;
    float stride = 0;
    float dot;
    int lineHit;
    int collided = 0;

    *(Q16_B0e5d8f83 *)pos = *(Q16_B0e5d8f83 *)position;
    probe.flags = 0x30000;
    probe.radius = 2;
    probe.owner = projectile;
    probe.active = 1;
    qcopy(probe.v, direction);
    func_00282F70(&probe, &probe, 1);
    probe.enabled = 1;
    probe.v[3] = 5627.925f;
    probe.mode = 3;
    probe.oClass = projectile->oClass;
    probe.v[2] = 1;

    func_00282CC0(step, pos, direction);
    lineHit = func_002761F8(pos, step, 0, vars->ignored, &probe);
    if (lineHit) {
        collided = 1;
        remaining = 0;
    } else {
        stride = 0.49f;
        remaining = func_00282DF0(direction);
        if (remaining > 0)
            func_00282D30(unit, direction, 1.0f / remaining);
        else
            qzero(unit);
    }
    while (remaining > 0 && !collided) {
        if (stride < remaining) {
            func_00282D30(step, unit, stride);
            remaining -= stride;
        } else {
            func_00282D30(step, unit, remaining);
            remaining = 0;
        }
        func_00282CC0(pos, pos, step);
        if (func_00277F48(0.5f, pos, 0, vars->ignored, &probe))
            collided = 1;
    }

    if (collided) {
        collision = &D_L04_001BFAC0;
        if (collision->moby) {
            if (collision->moby == vars->ignored)
                goto done;
            projectile->fBC = 2;
            hitMoby = collision->moby;
            if (hitMoby->oClass == 0xA1F)
                qcopy(pos, &projectile->position);
            else
                qcopy(pos, &hitMoby->position);
            func_00282CF0(hitDelta, &D_L04_001BFAE0.f30, &D_L04_001BFAE0.f40);
            func_00282F20((char *)hitDelta, (char *)hitDelta, 1);
            result = projectile;
            func_00283028(response, direction, &D_L04_001BFAE0.normal);
            func_00282F20((char *)response, (char *)response, 0.033333335f);
            func_00282F20((char *)hitNormal, (char *)&D_L04_001BFAE0.normal, 1);
        } else if (collision->count > 0) {
            *(Q16_B0e5d8f83 *)forward = *(Q16_B0e5d8f83 *)direction;
            func_001290E0(&collision->hit.normal, &collision->hit.normal);
            func_001290E0(forward, forward);
            dot = func_00282DB0(forward, &collision->hit.normal);
            if (dot > 0 && dot < 0.707f) {
                func_00282D30(&collision->hit.normal, &collision->hit.normal, dot);
                func_00282CC0(direction, direction, &collision->hit.normal);
                func_00282CD8(target, pos, direction);
                projectile->rotation.f[2] = func_00283248(direction[0], direction[1]);
                projectile->rotation.f[1] = -func_00283248(func_00282E20(direction), direction[2]);
                *(Q16_B0e5d8f83 *)hitPoint = collision->hit.point.q;
                func_L04_0040C0C0(hitPoint, direction, 4, 0);
            } else {
                projectile->fBC = 1;
                qcopy(pos, &D_L04_001BFAE0.point);
                func_00282CF0(hitDelta, &D_L04_001BFAE0.f30, &D_L04_001BFAE0.f40);
                func_00282F20((char *)hitDelta, (char *)hitDelta, 1);
                func_00283028(response, direction, &D_L04_001BFAE0.normal);
                func_00282F20((char *)response, (char *)response, 0.033333335f);
                func_00282F20((char *)hitNormal, (char *)&D_L04_001BFAE0.normal, 1);
            }
        }
    }
done:
    *(Q16_B0e5d8f83 *)position = *(Q16_B0e5d8f83 *)pos;
    return result;
}

extern void ref_L04_003FA5A8_00(void *, float, float, float);
extern unsigned char *ref_L04_003FA5A8_01(void *, void *, void *, float *, float *, float *, float, float);
extern void ref_L04_003FA5A8_02(void *, void *, void *);
extern void ref_L04_003FA5A8_03(void *, void *, void *, void *, void *, void *, void *);
unsigned char *func_L04_003FA5A8(unsigned char *owner, float *pos,
    unsigned char *target, float x, float y, float z, float angle, float tilt)
{
    float origin[4], matrix[16], position[4];
    unsigned char *m = func_0029EFD0((void *)0xABD);
    unsigned char *state;

    if (m != 0) {
        m[0x30] = 255;
        *(short *)(m + 0x32) = 255;
        m[0x31] = 1;
        m[0x20] = 0;
        *(float *)(m + 0xF8) = angle;
        *(float *)(m + 0xF4) = tilt;
        *(float *)(m + 0x2C) =
            *(float *)(*(unsigned char **)(m + 0x24) + 0x24) * 3.0f;
        state = *(unsigned char **)(m + 0x68);
        if (target == 0) {
            ref_L04_003FA5A8_00(matrix, 0.33333334f, angle, tilt);
            *(Q16_B0e5d8f83 *)position = *(Q16_B0e5d8f83 *)pos;
            target = ref_L04_003FA5A8_01(m, position, matrix, &x, &y, &z,
                0.349065899848938f, 30.0f);
        }
        *(void **)(state + 0x20) = owner;
        qcopy(m + 0x10, pos);
        *(int *)(state + 0x48) = 1;
        *(float *)(state + 0x44) = 0.8333333730697632f;
        *(int *)(state + 0x34) = 0;
        *(int *)(state + 0x38) = 0;
        *(int *)(state + 0x30) = 0;
        *(int *)(state + 0x54) = -1;
        *(int *)(state + 0x50) = -1;
        *(void **)(state + 0x28) = target;
        *(float *)(state + 0x3C) = x;
        *(float *)(state + 0x40) = y;
        *(int *)(state + 0x24) = 300;
        if (target != 0) {
            qcopy(state, target + 0x10);
            *(float *)(state + 8) += z;
            *(float *)(state + 0x2C) = z;
        }
        if (owner != 0 && *(short *)(owner + 0xAA) == 0xBBC) {
            *(short *)(state + 0x4E) = 60;
            *(short *)(state + 0x4C) = 60;
        } else {
            *(short *)(state + 0x4E) = 1;
            *(short *)(state + 0x4C) = 1;
        }
        *(Q16_B0e5d8f83 *)origin = *(Q16_B0e5d8f83 *)(owner + 0x10);
        origin[2] = pos[2];
        ref_L04_003FA5A8_02(matrix, pos, origin);
        if (target != 0 && *(short *)(target + 0xAA) != 0xBBC) {
            ref_L04_003FA5A8_03(m, state, origin, matrix,
                matrix + 12, matrix + 4, matrix + 8);
        }
        func_002A0F48(m);
        *(float *)(m + 0x2C) += *(float *)(m + 0x2C);
    }
    return m;
}

INCLUDE_ASM("asm/levels", func_L04_003FA7E0);

INCLUDE_ASM("asm/levels", func_L04_003FB990);

/* func_L04_003FBD80 is in the sibling file L04_003C8380-g8.c (it stores through $gp). */

INCLUDE_ASM("asm/levels", func_L04_003FBEF8);

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
extern void func_L04_003FB990(unsigned char *, L04_C678Vars *);
extern void func_L04_003FBEF8(void);
extern unsigned char D_00188660[];
extern int D_L04_001B0488 __attribute__((sda));

void func_L04_003FC678(unsigned char *m)
{
    L04_C678Vars *v = *(L04_C678Vars **)(m + 0x68);
    int s;
    L04_C678Slot *e;

    *(L04_C678Quad *)(m + 0x10) = *(L04_C678Quad *)(v->owner + 0x10);
    func_002AA800(m + 0xF8, 0, *(float *)(v->owner + 0xF8), 0.026179943f);
    v->age = v->age + 1.0f;
    if (v->timer != 0 && func_00282948(&v->timer) != 0) {
        s = D_L04_001B0488;
        if (s != -1) {
            e = (L04_C678Slot *)(D_00188660 + s * 0x70);
            if (e->owner == v->owner && e->active != 0) {
                func_002E59F8(s);
            }
        }
        D_L04_001B0488 = -1;
        func_0029F338(m);
        return;
    }
    if (30.0f < v->age && v->timer == 0) {
        v->timer = func_00283CF0(15.0f);
    } else {
        func_L04_003FB990(m, v);
    }
    func_L00_002E6DB8(func_L04_003FBEF8, m);
}

void *func_L04_00400A18(unsigned char *a0, void *a1, float f12) {
    unsigned char *obj = func_0029EFD0(a1);

    if (obj != 0) {
        obj[0x30] = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24) * f12;
        *(Q16_B0e5d8f83 *)(obj + 0x10) = *(Q16_B0e5d8f83 *)(a0 + 0x10);
        *(Q16_B0e5d8f83 *)(obj + 0xF0) = *(Q16_B0e5d8f83 *)(a0 + 0xF0);
        func_002A0F48(obj);
    }
    return obj;
}

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

/* Blend the nearby pressure-surface contact using a full64-byte inverse matrix. */
void func_L04_004027B0(unsigned char *object, unsigned char *state) {
    EffectVector delta;
    EffectMatrix4 inverse;
    unsigned char *nearby;
    unsigned char *contact;
    int kind;
    float distance;
    if (*(int *)(state + 0x80) == -1) return;
    func_002A8600(&nearby, *(int *)(state + 0x80), 0, 0);
    while (nearby) {
        kind = *(short *)(nearby + 0xAA);
        if (kind == 0x474 || kind == 0xCEF) {
            func_00282CF0(&delta, nearby + 0x10, object + 0x10);
            distance = func_00282DB0(&delta, &delta);
            if (!(20.0f < distance)) {
                func_00283388(&inverse);
                func_00283698(&inverse, nearby + 0xC0);
                func_002830C0(&delta, &delta, &inverse);
                if (func_00282C48(delta.f[0]) < 2.8f && func_00282C48(delta.f[1]) < 1.25f && func_00282C48(delta.f[2]) < 1.5f) {
                    contact = *(unsigned char **)(nearby + 0x68);
                    if (*(short *)(state + 0x140) == 0 && (*(unsigned char **)(state + 0x164))[0x20] != 3)
                        func_002E5CF8(0, 0, (char *)nearby);
                    *(unsigned short *)(state + 0x140) = *(unsigned short *)contact;
                }
            }
        }
        func_002A86E8(&nearby, nearby, 0, 0);
    }
    if (*(short *)(state + 0x140) != 0) {
        *(short *)(state + 0x142) = 1;
        func_002AA2E8((float *)(state + 0x13C), 0.10000000894069672f, 0.0055555556900799274f);
        if (*(short *)(state + 0x140)) func_00282978((short *)(state + 0x140));
    } else {
        *(short *)(state + 0x142) = 0;
        func_002AA2E8((float *)(state + 0x13C), 0.0f, 0.002777777845039964f);
    }
}

void func_L04_004029D8(unsigned char *m) {
    unsigned char *s = *(unsigned char **)(m + 0x68);
    float f;
    unsigned char *o;
    s[0xA2] = s[0x9C];
    *(Q16_B0e5d8f83 *)(m+0x10) = *(Q16_B0e5d8f83 *)(s+0xB0);
    *(Q16_B0e5d8f83 *)(m+0xF0) = *(Q16_B0e5d8f83 *)(s+0xC0);
    s[0xA0] = 0;
    f = func_00283CE0(s[0xA2]-1);
    *(float *)(s+0x134) = 0.36916667222976685f - f * 0.011666666716337204f - (1.0f - (float)*(int *)(s+0x1A8)*0.1f)*0.03333333507180214f;
    *(int *)(s+0x138)=0;
    *(int *)(s+0x158)=0;
    *(int *)(s+0x13C)=0;
    *(short *)(s+0x142)=0;
    *(short *)(s+0x140)=0;
    *(int *)(s+0x160)=0;
    *(int *)(s+0x24C)=0;
    if (*(int *)(s+0x54)==-1) *(char **)(s+0x110)=D_L04_001FE340[*(int *)(s+0x50)];
    else *(char **)(s+0x110)=D_L04_001FE340[*(int *)(s+0x54)];
    *(float *)(s+0xA8)=5.0f;
    *(float *)(s+0x1F8)=1.0f;
    *(int *)(s+0xAC)=0;
    *(int *)(s+0x114)=0;
    *(int *)(s+0x118)=0;
    *(int *)(s+0x128)=0;
    *(int *)(s+0x12C)=0;
    *(int *)(s+0x130)=0;
    *(int *)(s+0x244)=0;
    *(int *)(s+0x1F4)=0;
    *(int *)(s+0x144)=0;
    s[0xA4]=0; s[0xA5]=0; *(short *)(s+0xA6)=0;
    *(int *)(s+0x154)=0;
    *(int *)(s+0x150)=0;
    *(int *)(s+0x148)=0;
    *(int *)(s+0x178)=0;
    *(int *)(s+0x248)=0;
    *(int *)(s+0x14C)=0;
    *(int *)(s+0x15C)=0;
    s[0xA1]=0;
    qzero(s+0xD0); qzero(s+0xE0); qzero(s+0x100);
    o=*(unsigned char **)(s+0x110);
    func_002C96F8(o,s+0x114,s+0x118,s+0xF0,*(float *)(s+0xA8),*(float *)(o+0x1C));
    *(float *)(s+0x16C)=func_002A7878_range(-1.5f,1.5f);
    *(int *)(s+0x174)=func_00283CF0(func_002A7878_range(3.0f,6.0f)*60.0f);
    *(int *)(s+0x170)=0;
    *(int *)(m+0x98)=*(int *)(*(unsigned char **)(m+0x24)+0x10);
    *(unsigned short *)(m+0x34)=(*(unsigned short *)(m+0x34)&0xFFBE)|0x1400;
    if (!*(void **)(s+0x8C)) {
        *(void **)(s+0x8C)=func_L04_003E5E40(m,(void *)0x8EF,0.25f);
        if (!*(void **)(s+0x8C)) goto done;
    }
    {
    unsigned char *child=*(unsigned char **)(s+0x8C);
    *(unsigned short *)(child+0x34)&=0xFFBE;
    }
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0x10)=*(Q16_B0e5d8f83 *)(m+0x10);
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0xF0)=*(Q16_B0e5d8f83 *)(m+0xF0);
    (*(unsigned char **)(s+0x8C))[0x30]=0;
    func_002A05A8(*(void **)(s+0x8C));
    func_002A0F48(*(void **)(s+0x8C));
done:
    *(short *)(s+0x17E)=0; *(short *)(s+0x17C)=-1;
    *(int *)(s+0x180)=0; m[0x20]=2;
    *(int *)(s+0x120)=-1;
    *(int *)(s+0x240)=*(int *)(s+0x1C0)=*(int *)(s+0x124)=
    *(int *)(s+0x11C)=*(int *)(s+0x1AC)=*(int *)(s+0x1A0)=*(int *)(s+0x19C)=0;
}

extern float func_00282E48(char *arg0, char *arg1);

extern char *D_001FE340[];

void func_L04_00402C88(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *obj;

    {
        int *slot;
        int i;

        slot = (int *)(state + 0x54);
        for (i = 5; i >= 0; i--, slot++) {
            if (*slot != -1) {
                obj = D_001FE340[*slot];
                *(float *)(obj + 0x1C) = func_00282E48(obj + 0x10, obj + 0x20);
            }
        }
    }
    {
        int none = -1;
        int *slot;
        int i;

        slot = (int *)(state + 0x6C);
        for (i = 3; i >= 0; i--, slot++) {
            if (*slot != none) {
                obj = D_001FE340[*slot];
                *(float *)(obj + 0x1C) = func_00282E48(obj + 0x10, obj + 0x20);
            }
        }
    }
    if (*(int *)(state + 0x7C) != -1) {
        obj = D_001FE340[*(int *)(state + 0x7C)];
        *(float *)(obj + 0x1C) = func_00282E48(obj + 0x10, obj + 0x20);
    }
}
