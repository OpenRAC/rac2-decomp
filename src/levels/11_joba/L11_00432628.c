#include "common.h"
extern void func_00283098(float *, float *, float *);
extern void func_338398(char *, char *, float, int, int);
extern void func_32E480(char *, char *, int, float, float, float, int, int, int);
/* A path stores its point count in a 16-byte header, followed by vectors. */
struct RotorPath {
    int count;
    char pad04[12];
    float points[0][4];
};

/* The rotor's state (the object's field 0x68): a 13-point chain, the ten records it drives
   and the path it follows. Only the fields these functions use are named. */
struct RotorState {
    /* 0x000 */ char pad00[0x35];
    /* 0x035 */ u8 f35;
    /* 0x036 */ char pad36[0x1A];
    /* 0x050 */ float aim[4];
    /* 0x060 */ int f60;
    /* 0x064 */ char pad64[0x9C];
    /* 0x100 */ float points[13][4];
    /* 0x1D0 */ float oldPoints[13][4];
    /* 0x2A0 */ char pad2A0[0x10];
    /* 0x2B0 */ int choices[4][4];
    /* 0x2F0 */ char pad2F0[0x30];
    /* 0x320 */ int pathIndex;
    /* 0x324 */ struct RotorPath *path;
    /* 0x328 */ char pad328[8];
    /* 0x330 */ int records[10];
    /* 0x358 */ int linked;
    /* 0x35C */ char pad35C[0xC];
    /* 0x368 */ int projectileClass;
    /* 0x36C */ char pad36C[4];
    /* 0x370 */ s16 pathPoint;
    /* 0x372 */ char pad372[2];
    /* 0x374 */ s16 projectileIndex;
    /* 0x376 */ s16 projectileDelay;
    /* 0x378 */ s16 ropeCount;
    /* 0x37A */ u16 toggle;
    /* 0x37C */ char pad37C[4];
    /* 0x380 */ u8 disabled[10];
};

/* A basis vector whose fourth word is cleared as an integer. */
struct RotorAxis {
    float x, y, z;
    int w;
};

/* A rotor moby, and each 256-byte record of the level's table has the same layout. */
struct RotorObject {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float pos[4];
    /* 0x20 */ u8 mode;
    /* 0x21 */ char pad21[0x13];
    /* 0x34 */ u16 flags;
    /* 0x36 */ char pad36[0x32];
    /* 0x68 */ struct RotorState *state;
    /* 0x6C */ char pad6C[0x4C];
    /* 0xB8 */ int fB8;
    /* 0xBC */ char padBC[4];
    /* 0xC0 */ struct RotorAxis basis[3];
};

extern struct RotorPath *D_L11_001FF580[];
extern char D_00188660[];
extern void func_3739C0(int);
extern int func_002E5CF8(int, int, char *);
extern float func_00283CE0(int);
extern float func_002AA140(float, float, float);
extern void func_002AA2E8(float *, float, float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);

extern int D_L11_001B359C __attribute__((sda));

extern void func_32C700();

/* func_L11_00432628 is defined in L11_00432628-dust.c. */

INCLUDE_ASM("asm/levels", func_L11_00434580);

INCLUDE_ASM("asm/levels", func_L11_004349F8);

typedef int TI128 __attribute__((mode(TI)));

extern void func_L11_00434AF8(char *p, void *q);

extern void func_L11_00434D00(char *p, void *q);

/* Hands two reads of the state's quadword to the two measured stage helpers. */
void func_L11_00434AA8(char *p)
{
    char *state = *(char **)(p + 0x68);
    TI128 v = *(TI128 *)state;

    func_L11_00434AF8(p, &v);
    v = *(TI128 *)state;
    func_L11_00434D00(p, &v);
}

extern char D_L11_001BA8C0[];
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);
void func_L11_00434F48(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L11_001BA8C0, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878(1.0f, 5.0f) * 0.0166666675f;
        func_00282CC0((char *)origin, (char *)pos, (char *)offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 60, size * 0.1f, size, 0x8020FF20, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00282E80(void *, void *);
extern char D_00189EA0[];

/* Stops the object's sound if its slot still belongs to it, then forgets the slot. */
static inline void stop_owned_sound(char *state, char *p)
{
    int slot = *(int *)(state + 0x14);

    if (slot != -1) {
        char *e = D_00188660 + slot * 0x70;

        if (*(char **)(e + 0x88) == p && *(unsigned char *)(e + 0x74))
            func_3739C0(slot);
    }
    *(int *)(state + 0x14) = -1;
}

/* Five-stage mover driven by the parent's state byte: when the parent reaches 2 it starts its
   sound and moves out along its +0xE0 direction over half a turn (pi/120 a frame); when the
   parent leaves 2 it does the same back, only while D_00189EA0 is more than 6 away, and at a
   full turn returns to its saved position and waits again. */
void func_L11_00435228(char *p)
{
    char *state = *(char **)(p + 0x68);
    char *parent = (char *)(D_L11_001B359C + (*(int *)(state + 8) << 8));
    float offset[4];

    switch (*(unsigned char *)(p + 0x20)) {
    case 0:
        *(unsigned char *)(p + 0x20) = 1;
        *(float *)(state + 0xC) = 3.1415927f;
        *(float *)(state + 0x10) = 0;
        qcopy(state + 0x20, p + 0x10);
        *(unsigned short *)(p + 0x34) |= 0x800;
    case 1:
        if (*(unsigned char *)(parent + 0x20) == 2) {
            char *e = D_00188660 + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != p || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = func_002E5CF8(0, 4, p);
            *(unsigned char *)(p + 0x20) = 2;
            *(float *)(state + 0xC) = 3.1415927f;
            *(float *)(state + 0x10) = 0;
        } else {
            stop_owned_sound(state, p);
        }
        break;
    case 2:
        *(float *)(state + 0x10) += 0.026179943f;
        *(float *)(state + 0xC) = func_00283B98(*(float *)(state + 0xC), 0.026179943f);
        if (*(float *)(state + 0x10) >= 3.1415927f) {
            stop_owned_sound(state, p);
            *(unsigned char *)(p + 0x20) = 3;
        } else {
            func_00282F20((char *)offset, p + 0xE0, (func_00283180(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
            func_00282CC0(p + 0x10, (char *)offset, state + 0x20);
        }
        break;
    case 3:
        if (*(unsigned char *)(parent + 0x20) != 2) {
            char *e = D_00188660 + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != p || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = func_002E5CF8(0, 4, p);
            *(unsigned char *)(p + 0x20) = 4;
        } else {
            stop_owned_sound(state, p);
        }
        break;
    case 4:
        if (func_00282E80(p + 0x10, D_00189EA0) > 6.0f) {
            *(float *)(state + 0x10) += 0.026179943f;
            *(float *)(state + 0xC) = func_00283B98(*(float *)(state + 0xC), 0.026179943f);
            if (*(float *)(state + 0x10) >= 6.2831855f) {
                stop_owned_sound(state, p);
                *(unsigned char *)(p + 0x20) = 1;
                *(float *)(state + 0xC) = 3.1415927f;
                *(float *)(state + 0x10) = 0;
                qcopy(p + 0x10, state + 0x20);
            } else {
                func_00282F20((char *)offset, p + 0xE0, (func_00283180(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
                func_00282CC0(p + 0x10, (char *)offset, state + 0x20);
            }
        }
        break;
    }
}

/* func_L11_00435600 is defined in L11_00435600-g8.c. */

/* func_L11_00436350 is defined in L11_00436350-g8.c. */

void func_L11_00436768(char *obj)
{
    float tmp[3];
    TI128 tmp2[2];
    char *state;
    float f0, f1;

    tmp2[1] = 0;
    state = *(char **)(obj + 0x68);
    f1 = *(float *)(state + 0x100);
    f0 = *(float *)(state + 0x104);
    *(float *)((char *)&tmp2[1] + 8) = f0 + f1;
    tmp2[0] = tmp2[1];
    func_00283098((float *)&tmp2[0], (float *)&tmp2[0], (float *)((char *)obj + 0xC0));
    func_00282CC0((char *)tmp, (char *)obj + 0x10, (char *)&tmp2[0]);
    if (*(unsigned short *)(obj + 0x96) <= 0xFFFE)
        *(unsigned short *)(obj + 0x96) = *(unsigned short *)(obj + 0x96) + 1;
    func_338398(obj, state + 0x290, 2.5f, 1, 1);
    func_32E480(obj, obj + 0x10, 0x4000000, 1.0f, 1.0f, 1.0f, 0, 1, 0);
}


/* Re-arms the measured stage guard, then clears it. */
extern int func_002B3BA8_6850(char *, int, float, float, int, int);

/* Same body as func_L02_003F16F0, with this function's own callees. */
void func_L11_00436850(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) < 4) {
        *(int *)(state + 0x270) = 0;
        goto done;
    }

    if (*(short *)(state + 0x282) == 1) {
        *(short *)(state + 0x280) =
            func_002B3BA8_6850(arg0, *(int *)(state + 0x27C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x270) = *(int *)(state + 0x200);
    } else {
        if (func_L11_00441868(*(int *)(arg0 + 0xB8), *(short *)(arg0 + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x282) = 1;
        *(short *)(state + 0x280) =
            func_002B3BA8_6850(arg0, *(int *)(state + 0x27C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x270) = *(int *)(state + 0x200);
    }
    return;

done:
    *(short *)(state + 0x282) = 0;
}

extern void func_002B60B0(char *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002A05A8(char *);
extern void func_002A0488(char *, int, int, int);
extern void func_L11_003973F8(char *, int, float, float);

void func_L11_00436910(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    unsigned short flags;
    char *definition;
    int cache;

    *(short *)(state + 0x282) = 0;
    *(short *)(state + 0x88) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x286) = active;
    func_002B60B0(object, 0.004444444552063942f, 0.13333334028720856f,
                  0.006981317885220051f, 0.20943954586982727f);
    flags = *(unsigned short *)(object + 0x34);
    definition = *(char **)(object + 0x24);
    cache = *(int *)(definition + 0x10);
    *(unsigned short *)(object + 0x34) = (flags | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = cache;
    *(unsigned char *)(object + 0x7F) = 0;
    if (*(short *)(state + 0x286) != 0) {
        func_002A7750(object, 7, 3);
        *(unsigned short *)(object + 0x34) |= 0x100;
        func_002A7470(object, 1, 0, 0);
        func_002A05A8(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        func_002A7750(object, 3, 0);
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) &= 0xFEFE;
    }
    *(unsigned char *)(state + 0x2E) = 1;
    *(short *)(state + 0x284) = mode;
    *(unsigned char *)(state + 0x6A) = 0;
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(unsigned char *)(state + 0x54),
                      *(unsigned char *)(state + 0x55), *(unsigned char *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

extern void func_L11_00441978(unsigned char *object, int class_id);

extern void func_0032C700(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);

extern void func_002E5DA0(int, int, void *, int);

extern void func_002A7470(void *, int, int, int);

extern void func_002A05A8(char *);

extern void func_002A7750(void *, int, int);

/* Retires the measured stage-46 record: clears the guard, drops the effect and re-tags the object. */
void func_L11_00436A78(char *obj)
{
    char *state = *(char **)(obj + 0x68);

    if (*(short *)(state + 0x282) == 1) {
        func_L11_00441978(*(unsigned char **)(obj + 0xB8), 0xD37);
        *(int *)(state + 0x270) = 0;
    } else {
        *(int *)(state + 0x270) = 0;
    }
    *(short *)(state + 0x282) = 0;
    if (*(unsigned char *)(obj + 0x31)) {
        func_0032C700(obj + 0x10, 0, 0, 0x1E, 5, 0, 0x32, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        func_002E5DA0(0, 0, obj, 0xDF7);
    }
    func_002A7470(obj, 0, 0, 3);
    func_002A05A8(obj);
    func_002A7750(obj, 1, 0);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) & 0xEFFF) | 0x47;
}

/* func_L11_00436B78 is defined in L11_00436B78-flags.c. */


/* func_L11_00436F80 is defined in L11_00436F80.c. */

/* func_L11_004375B8 is defined in L11_004375B8.c. */

extern unsigned char D_L11_00438880[];

extern void func_802F8AD0(void *a0, void *a1);
extern void func_80338398(void *a0, void *a1, int a2, int a3, float f12);
extern void func_L11_004395C8(char *p);
extern void func_L11_00437EA8(void *obj);
extern void func_L11_00437FD0(char *p);
extern void func_L11_00438460(void *obj);
extern void func_L11_004386B8(void *obj);

/* Runs the ten rotors' update, one frame each, and restarts the entry timer. */
void func_L11_00437CF0(char *p)
{
    char *q = *(char **)(p + 0x68);
    int i;

    func_802F8AD0((void *)D_L11_00438880, p);

    for (i = 12; i >= 0; i--)
        ;

    if (*(unsigned char *)(p + 0x20) >= 2) {
        func_L11_004395C8(p);
        func_L11_00437EA8(p);
        func_L11_00437FD0(p);
        func_L11_00438460(p);
        func_L11_004386B8(p);
    }
    if (*(unsigned short *)(p + 0x96) <= 0xFFFE) {
        (*(unsigned short *)(p + 0x96))++;
    }
    func_80338398(p, q + 0x80, 1, 1, 2.5f);
}

/* Walks the ten measured indices, clearing each record selected through 0x330. */
void func_L11_00437DC0(char *p, int a1, int a2, int a3)
{
    int i;

    for (i = 0; i < 10; i++) {
        int offset = i * 4;
        int index = *(int *)(*(char **)(p + 0x68) + offset + 0x330);
        char *record = (char *)(D_L11_001B359C + (index << 8));

        if (*(unsigned char *)(record + 0x43) != a1)
            func_32C700(record, a1, a2, a3);
    }
}

/* Invalidates the measured slot at 0x43 of the 256-byte record indexed by 0x358. */
void func_L11_00437E68(char *p, int a1, int a2, int a3)
{
    int record = (*(int *)(*(char **)(p + 0x68) + 0x358) << 8) + D_L11_001B359C;

    if (*(unsigned char *)(record + 0x43) != a1)
        func_002A7470((char *)record, a1, a2, a3);
}

extern void func_00282C88(void *);
extern void func_00282D30(void *, void *, float);

/* A 16-byte aligned vector, copied as one quadword. */
typedef union Quad {
    TI128 q;
    float f[4];
} Quad;

/* Advances the thirteen chain points one Verlet step: each moves by its damped displacement
   from its old position plus a small downward pull, and the old position takes the point's
   previous value. The damping blends 0.97 to 0.98 with the count at 0x378. */
void func_L11_00437EA8(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;
    float (*pos)[4];
    float (*old)[4];
    Quad saved;
    Quad delta;
    Quad gravity;
    float t;
    float damping;
    int i;

    func_00282C88(&gravity);
    pos = state->points;
    old = state->oldPoints;
    gravity.f[2] = -1.0f / 720.0f;

    t = func_00283CE0(state->ropeCount);
    damping = func_002AA140(0.97f, 0.98f, (t -= 2.0f) / func_00283CE0(8));

    for (i = 12; i >= 0; i--, pos++, old++) {
        qcopy(&saved, pos);
        func_00282CF0(delta.f, *pos, *old);
        func_00282D30(&delta, &delta, damping);
        func_00282CC0(pos, pos, &delta);
        func_00282CC0(pos, pos, &gravity);
        qcopy(old, &saved);
    }
}

INCLUDE_ASM("asm/levels", func_L11_00437FD0);

extern void func_002833F0(char *, char *);

INCLUDE_ASM("asm/levels", func_L11_00438248);

extern void func_00282DD8(void *a, void *b, void *c);

extern void func_002AB6D8(char *a, char *b);

extern void func_002AAA00(char *a, char *b, int c, float d, float e, float f, float g);

/* Builds the measured three-axis basis of the object and hands it to the three slots. */
void func_L11_00438320(char *obj, char *direction, float a, float b, float c)
{
    char *state = *(char **)(obj + 0x68);
    float m[4][4];
    float out[4];

    func_00282F20((char *)m[0], direction, 1.0f);
    func_00282C88((TI128 *)m[2]);
    m[2][2] = 1.0f;
    func_00282DD8((char *)m[1], (char *)m[0], (char *)m[2]);
    func_00282F20((char *)m[1], (char *)m[1], 1.0f);
    func_00282DD8((char *)m[2], (char *)m[1], (char *)m[0]);
    func_00282F20((char *)m[2], (char *)m[2], 1.0f);
    func_002AB6D8((char *)m[0], (char *)out);
    func_002AAA00(obj + 0xF0, state + 0x2A0, 0, out[0], a, b, c);
    func_002AAA00(obj + 0xF4, state + 0x2A4, 0, out[1], a, b, c);
    func_002AAA00(obj + 0xF8, state + 0x2A8, 0, out[2], a, b, c);
}

/* Record `index` of the level's 256-byte record table. */
#define ROTOR_RECORD(index) ((struct RotorObject *)(D_L11_001B359C + ((index) << 8)))
/* The record the object's state lists at `i`, and the one it links to. */
#define LISTED_RECORD(obj, i) ROTOR_RECORD((obj)->state->records[i])
#define LINKED_RECORD(obj) ROTOR_RECORD((obj)->state->linked)
/* The same records for stores, with the addition ordered as retail orders it there. */
#define STORED_RECORD(index) \
    ((struct RotorObject *)(((index) << 8) + D_L11_001B359C))
#define LISTED_STORE(obj, i) STORED_RECORD((obj)->state->records[i])
#define LINKED_STORE(obj) STORED_RECORD((obj)->state->linked)

/* Updates the positions and orthonormal bases of the ten enabled records. */
void func_L11_00438460(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;
    int i;

    for (i = 0; i < 10; i++) {
        if (state->disabled[i])
            continue;

        qcopy_nc(LISTED_STORE(obj, i)->pos, state->points[i + 1]);
        func_00282CF0(&LISTED_RECORD(obj, i)->basis[0], state->points[i], state->points[i + 1]);
        LISTED_STORE(obj, i)->basis[0].w = 0;
        func_00282F20(&LISTED_RECORD(obj, i)->basis[0], &LISTED_RECORD(obj, i)->basis[0], 1.0f);
        func_00282C88(&LISTED_RECORD(obj, i)->basis[2]);
        LISTED_STORE(obj, i)->basis[2].z = 1.0f;
        func_00282DD8(&LISTED_RECORD(obj, i)->basis[1], &LISTED_RECORD(obj, i)->basis[0],
                      &LISTED_RECORD(obj, i)->basis[2]);
        LISTED_STORE(obj, i)->basis[1].w = 0;
        func_00282F20(&LISTED_RECORD(obj, i)->basis[1], &LISTED_RECORD(obj, i)->basis[1], 1.0f);
        func_00282DD8(&LISTED_RECORD(obj, i)->basis[2], &LISTED_RECORD(obj, i)->basis[1],
                      &LISTED_RECORD(obj, i)->basis[0]);
        LISTED_STORE(obj, i)->basis[2].w = 0;
        func_00282F20(&LISTED_RECORD(obj, i)->basis[2], &LISTED_RECORD(obj, i)->basis[2], 1.0f);
        LISTED_STORE(obj, i)->flags |= 0x100;
    }
}

/* Updates the single record selected by the state index at 0x358. */
void func_L11_004386B8(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;

    qcopy_nc(LINKED_STORE(obj)->pos, state->points[11]);
    func_00282CF0(&LINKED_RECORD(obj)->basis[0], state->points[10], state->points[11]);
    LINKED_STORE(obj)->basis[0].w = 0;
    func_00282F20(&LINKED_RECORD(obj)->basis[0], &LINKED_RECORD(obj)->basis[0], 1.0f);
    func_00282C88(&LINKED_RECORD(obj)->basis[2]);
    LINKED_STORE(obj)->basis[2].z = 1.0f;
    func_00282DD8(&LINKED_RECORD(obj)->basis[1], &LINKED_RECORD(obj)->basis[0],
                  &LINKED_RECORD(obj)->basis[2]);
    LINKED_STORE(obj)->basis[1].w = 0;
    func_00282F20(&LINKED_RECORD(obj)->basis[1], &LINKED_RECORD(obj)->basis[1], 1.0f);
    func_00282DD8(&LINKED_RECORD(obj)->basis[2], &LINKED_RECORD(obj)->basis[1],
                  &LINKED_RECORD(obj)->basis[0]);
    LINKED_STORE(obj)->basis[2].w = 0;
    func_00282F20(&LINKED_RECORD(obj)->basis[2], &LINKED_RECORD(obj)->basis[2], 1.0f);
    LINKED_STORE(obj)->flags |= 0x100;
}

INCLUDE_ASM("asm/levels", func_L11_00438880);

/* Clears the two 16-bit flags at 0x374/0x376 of the object held at 0x68. */
void func_L11_00438CD8(char *p)
{
    char *q = *(char **)(p + 0x68);
    *(short *)(q + 0x374) = 0;
    *(short *)(q + 0x376) = 0;
}

extern int func_00282978(short *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern char *func_L07_003F6B88(int);
extern void func_L11_00458A98(char *, void *, int, int, void *, void *, int, float, float);
extern void func_002A7A00(float *, float, float);

/* Emits a projectile from the next enabled record, with a fifteen-frame delay. */
void func_L11_00438CE8(struct RotorObject *obj)
{
    float pos[4];
    float matrix[4][4];
    float offset[4];
    float velocity[4];
    float jitter[4];
    float toTarget[4];
    struct RotorState *state = obj->state;
    char *projectile;

    if (state->projectileIndex == -1)
        return;

    while (state->disabled[state->projectileIndex])
        ++state->projectileIndex;
    if (state->projectileIndex >= 10) {
        state->projectileIndex = -1;
        return;
    }
    if (!func_00282978(&state->projectileDelay))
        return;

    func_0029FCC0(LISTED_RECORD(obj, state->projectileIndex), 0, pos);
    func_0029FC20(LISTED_RECORD(obj, state->projectileIndex), 0, matrix);
    func_00282F20(offset, matrix[2], -0.3f);
    func_00282CC0(pos, pos, offset);

    func_002A7A00(jitter, 0.0166666675f, 0.0500000045f);
    jitter[2] = -0.0833333358f;
    qcopy_nc(velocity, jitter);
    func_00282CF0(toTarget, state->aim, pos);
    func_00282F20(toTarget, toTarget, 0.333333343f);
    func_00282CC0(velocity, velocity, toTarget);

    projectile = func_L07_003F6B88(state->projectileClass);
    if (projectile)
        func_L11_00458A98(projectile, LISTED_RECORD(obj, state->projectileIndex), obj->fB8,
                          state->f60, pos, velocity, 120, 0.00277777785f, state->f35);
    ++state->projectileIndex;
    state->projectileDelay = 15;
}

/* Chooses the state-dependent path, then finds its nearest point. */
void func_L11_00438F18(struct RotorObject *obj)
{
    struct RotorState *state = obj->state;
    struct RotorPath *path;
    float best;
    float d;
    int pick;
    int i;
    int toggled;

    toggled = state->toggle ^ 1;
    state->toggle = toggled;
    switch (obj->mode) {
    case 2:
        state->path = D_L11_001FF580[state->pathIndex];
        break;
    case 3:
        if (toggled != 0)
            path = D_L11_001FF580[state->choices[0][func_002A77E0(4)]];
        else
            path = D_L11_001FF580[state->choices[1][func_002A77E0(4)]];
        state->path = path;
        break;
    case 4:
        if (toggled != 0)
            path = D_L11_001FF580[state->choices[2][func_002A77E0(4)]];
        else
            path = D_L11_001FF580[state->choices[3][func_002A77E0(4)]];
        state->path = path;
        break;
    }
    pick = 0;
    best = func_00282E80(obj->pos, state->path->points[0]);
    for (i = 0; i < state->path->count - 1; i++) {
        d = func_00282E80(obj->pos, state->path->points[i]);
        if (d < best) {
            best = d;
            pick = i;
        }
    }
    state->pathPoint = pick;
}

/* Follows the current path, steers toward its next point and releases the sound at the end. */
int func_L11_004390D0(char *object)
{
    char *state = *(char **)(object + 0x68);
    float target[4], direction[4], aim[4], old[4];
    float speed, duration;

    if (!*(int *)(state + 0x324)) {
        if (*(int *)(state + 0x38C) != -1) {
            char *entry = D_00188660 + *(int *)(state + 0x38C) * 0x70;
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74))
                func_3739C0(*(int *)(state + 0x38C));
        }
        *(int *)(state + 0x38C) = -1;
        return 1;
    }
    {
        char *entry = D_00188660 + *(int *)(state + 0x38C) * 0x70;
        if (*(char **)(entry + 0x88) != object || !*(unsigned char *)(entry + 0x74))
            *(int *)(state + 0x38C) = func_002E5CF8(0, 4, object);
    }
    qcopy(target, *(char **)(state + 0x324) + *(short *)(state + 0x370) * 16 + 16);
    speed = func_00283CE0(*(short *)(state + 0x378));
    duration = func_00283CE0(8);
    speed = func_002AA140(15.0f, 20.0f, (speed - 2.0f) / duration);
    func_002AA2E8((float *)(state + 0x32C), speed * (1.0f / 60.0f), 1.0f / 180.0f);
    func_00282CF0(direction, target, (float *)(object + 0x10));
    func_00282F20((char *)direction, (char *)direction, *(float *)(state + 0x32C));
    func_00282CC0(object + 0x10, object + 0x10, (char *)direction);
    func_00282CF0(old, (float *)(state + 0x50), (float *)(object + 0x10));
    func_00282F20((char *)old, (char *)old, 1.0f);
    func_00282F20((char *)direction, (char *)direction, 1.0f);
    if (func_00282DB0(direction, old) > 0.707f) {
        qcopy(aim, old);
        func_L11_00438320(object, (char *)aim, 0.006981317885220051f,
                         0.006981317885220051f, 0.41887909173965454f);
    } else {
        qcopy(aim, direction);
        func_L11_00438320(object, (char *)aim, 0.006981317885220051f,
                         0.006981317885220051f, 0.41887909173965454f);
    }
    if (func_00282E48(object + 0x10, target) < 4.0f)
        (*(short *)(state + 0x370))++;
    if (*(short *)(state + 0x370) < **(int **)(state + 0x324) - 1)
        return 0;
    *(int *)(state + 0x324) = 0;
    if (*(int *)(state + 0x38C) != -1) {
        char *entry = D_00188660 + *(int *)(state + 0x38C) * 0x70;
        if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74))
            func_3739C0(*(int *)(state + 0x38C));
    }
    *(int *)(state + 0x38C) = -1;
    return 1;
}

/* func_L11_004393D8 is defined in L11_00432628-g8.c (it reaches D_L11_001B12C4
   through $gp). */

/* func_L11_004395C8: attempt kept in drafts (112 bytes, expected 116). */
/* func_L11_004395C8 is defined in L11_00432628-g8.c (this unit has no $gp access for it). */

/* func_L11_00439640 is defined in L11_00432628-burst-g8.c. */

/* func_L11_00439950 is defined in L11_00432628-reset-g64.c. */

extern int func_373978(char *obj, int a);

extern void func_3739C0(int a);

extern struct RotorPath *D_L11_001FF580[];
extern char D_00188660[];

#define REC_L11_359C(o, t) ((*(int *)(*(char **)((o) + 0x68) + 0x358) << 8) + (int)(t))

/* Releases the object's measured slot and clears the six flags of its record. */
void func_L11_00439BF0(char *obj)
{
    char *state;
    char *records;

    func_002A7750(obj, 1, 0);
    state = *(char **)(obj + 0x68);
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) & 0xEFFF) | 0x47;
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    if (func_373978(obj, *(int *)(state + 0x38C)) != 0) {
        if (*(int *)(state + 0x38C) != -1) {
            char *entry = D_00188660 + *(int *)(state + 0x38C) * 0x70;

            if (*(char **)(entry + 0x88) == obj && *(unsigned char *)(entry + 0x74) != 0)
                func_3739C0(*(int *)(state + 0x38C));
        }
        *(int *)(state + 0x38C) = -1;
    }
    records = (char *)D_L11_001B359C;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x2;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x4;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x40;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) &= 0xEFFF;
    *(unsigned short *)(REC_L11_359C(obj, records) + 0x34) |= 0x1;
    *(unsigned char *)(REC_L11_359C(obj, records) + 0x31) = 0;
    *(int *)(REC_L11_359C(obj, (char *)D_L11_001B359C) + 0x98) = 0;
}


/* Picks the measured 3/4 code from the counter at 0x364 of the object at 0x68. */
int func_L11_00439D60(char *p)
{
        if (*(int *)(*(char **)(p + 0x68) + 0x364))
        return 3;
    return 4;
}

/* func_L11_00439DD0 is defined in L11_00439DD0-g8.c. */

extern int func_00283CF0(float);
extern void func_L11_0043AB28(char *);
extern void func_002B0ED8(char *, char *, int);
extern int func_002B3BA8(char *, int, int, int, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern char D_L11_001BA8C0[];

void func_L11_0043A3F8(char *object) {
    char *state = *(char **)(object + 0x68);

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(state + 0x48) = func_00283CF0(15.0f);
        *(unsigned char *)(state + 0x4A) = func_00283CF0(12.0f);
        *(float *)(state + 0x1A0) = 1.0f;
        *(unsigned char *)(state + 0x180) = 6;
        *(int *)(state + 0x1B8) = 2;
        *(float *)(state + 0x1AC) = 0.15f;
        *(float *)(state + 0x80) = 1.0f;
        *(float *)(state + 0x84) = 0.4f;
        *(float *)(state + 0x88) = 0.3f;
        *(float *)(state + 0x8C) = 0.3f;
        *(float *)(state + 0x90) = 1.5707964897155762f;
        *(float *)(state + 0xB0) = 0.523598849773407f;
        *(float *)(state + 0xB4) = 2.0f;
        *(float *)(state + 0xAC) = 0.0027777778450399637f;
        *(int *)(state + 0x1A4) = 0;
        func_002B60B0(object, 0.2777777910232544f, 0.3333333432674408f,
                      0.0017453294713050127f, 0.05235988646745682f);
        if (*(short *)(state + 0x24) == 0) {
            *(short *)(state + 0x24) = 10;
            *(float *)(state + 0x20) = 10;
        }
        if (*(unsigned char *)(object + 0x43) != 1)
            func_002A7470(object, 1, 0, 0);
        func_002A7750(object, 1, -1);
        func_L11_0043AB28(object);
    }
    if (*(unsigned char *)(object + 0x20) >= 4)
        func_002B0ED8(object, state + 0x170, 0);
    if (*(unsigned char *)(object + 0x20) >= 3 &&
        *(unsigned char *)(state + 0x2E) == 2)
        func_L11_0043AB28(object);
    *(int *)(state + 0x2D8) = func_002B3BA8(object, *(int *)(state + 0x2E8),
                                         0, 0, 255.0f, 255.0f);
    if (*(unsigned char *)(object + 0x31) != 0) {
        if (func_00282E48(object + 0x10, D_L11_001BA8C0) < 48.0f) {
            func_002A93B0(object);
            *(unsigned char *)(object + 0x6F) = 45;
        }
    }
}

extern void func_32E480(char *p, char *q, int a, float b, float c, float d, int e, int f, int g);

/* Bumps the 16-bit counter at 0x96 while it is under the measured ceiling, then re-arms. */
void func_L11_0043A620(char *p)
{
    unsigned short count = *(unsigned short *)(p + 0x96);

    if (count <= 0xFFFE)
        *(unsigned short *)(p + 0x96) = count + 1;
    func_32E480(p, p + 0x10, 0x4000000, 1.2f, 1.0f, 1.0f, 0, 1, 0);
}

/* func_L11_0043A680 is defined in L11_0043A680-g8.c. */

/* True when the byte at 0x20 is above the measured small-id range. */
int func_L11_0043A800(char *p)
{
    return *(unsigned char *)(p + 0x20) >= 4;
}


extern void func_002A7A00(float *out, float a, float b);
extern float func_002A7878(float a, float b);
extern void func_002B0A68(char *self, int mask, float *arg2, unsigned char arg3,
                           float f0, float f1, float f2, float f3);
extern int func_002E5CF8(int index, int a1, char *a2);
extern void func_0029F9F0(char *list, char *node);

/* Spawns the object's jitter effect while its flag byte is set, then retires the state. */
void func_L11_0043AB28(char *obj)
{
    char *state;
    unsigned short flags;
    float v[3];

    if (*(unsigned char *)(obj + 0x20) == 0)
        return;

    if (*(unsigned char *)(obj + 0x31) != 0) {
        float s = 1.0f / 6.0f;

        func_002A7A00(v, s, 1.0f / 3.0f);
        v[2] = func_002A7878(1.0f / 12.0f, s);
        func_002B0A68(obj, 3, v, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(1, 0, obj);
        func_0032C700(obj + 0x10, 1, 0x19, 0xA, 0xA, 5, 0, 1, 1.0f, 20.0f, 0, 0, 0, 0);
        func_002E5DA0(0, 0, obj, 0xDF7);
    }

    func_002A7750(obj, 1, 0);
    func_002A7470(obj, 0, 0, 3);
    func_002A05A8(obj);

    state = *(char **)(obj + 0x68);
    flags = *(unsigned short *)(obj + 0x34);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (flags & 0xEFFF) | 0x47;

    if (*(unsigned char *)(state + 0x221))
        func_0029F9F0(obj, state + 0x220);
    if (*(unsigned char *)(state + 0x261))
        func_0029F9F0(obj, state + 0x260);
}

INCLUDE_ASM("asm/levels", func_L11_0043ACB0);

/* Maps the measured selector onto its small index. */
/* func_L11_0043E090 is defined in L11_0043E090.c. */

/* Maps the measured selector onto its large index. */
/* func_L11_0043E108 is defined in L11_0043E108.c. */
