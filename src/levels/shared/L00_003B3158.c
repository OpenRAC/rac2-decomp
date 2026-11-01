#include "include_asm.h"
#include "common.h"

/* The moby fields func_L00_003B8E58 reads. */
typedef struct {
    u8 pad00[0x10];
    float position[4];          /* 0x10 */
    u8 state;                   /* 0x20: 0xFE (free) and 0xFD are not live */
    u8 pad21[0x68 - 0x21];
    void *vars;                 /* 0x68 */
    u8 pad6C[0xAA - 0x6C];
    short oClass;               /* 0xAA */
} Moby;

/* The instance data of a class 0xEE1 moby, as far as func_L00_003B8E58 reads it. */
typedef struct {
    u8 pad000[0x20];
    float f20;                  /* 0x20: positive for a target */
    u8 pad024[0x3B1 - 0x24];
    u8 flags3B1;                /* 0x3B1: bit 0x80 for a target */
    u8 pad3B2[0x3E4 - 0x3B2];
    float maxDistance;          /* 0x3E4: 0 for no limit */
} TargetVars;

/* The hero fields func_L00_003B8E58 reads. */
typedef struct {
    u8 pad0000[0x340];
    int f340;                   /* 0x340 */
    u8 pad0344[0x34E - 0x344];
    short f34E;                 /* 0x34E */
    u8 pad0350[0x1230 - 0x350];
    u32 buttonMask;             /* 0x1230: tested against controller 1's held buttons */
    u8 pad1234[0x1450 - 0x1234];
    Moby *target;               /* 0x1450: the current target */
} Hero;

extern Hero D_00189E20;
extern u32 D_00138320[];        /* controller 1's held buttons (D_00138180 + 0x1A0) */
extern float *func_002AB1F0(Moby *moby);
extern int func_002AF580(void *origin, void *direction, int *count, Moby **candidates, int capacity,
                         int, int, void *config,
                         float angle0, float angle1, float range, float angle2, float angle3);
extern float func_00282E80(void *from, void *to);

typedef struct OBJ {
    char pad0[32];
    unsigned char f20;
    char pad1[0x64 - 33];
    void (*f64)(struct OBJ *);
    char pad2[0xAA - 0x68];
    short fAA;
} OBJ;

extern OBJ *D_L06_001B2820_1 __attribute__((sda));

extern OBJ *D_L06_001B2824_1 __attribute__((sda));

extern OBJ *D_L06_001AC000 __attribute__((sda));

typedef struct NODE {
    char pad0[0x8];
    int f08;
    int f0C;
    char pad1[0x24 - 0x10];
    int f24;
    int f28;
    int f2C;
    unsigned char f30;
    char pad2[0x40 - 0x31];
    int f40;
    char pad3[0x68 - 0x44];
    void *f68;
    char pad4[0xB8 - 0x6C];
    int fB8;
    unsigned char fBC;
} NODE;

typedef struct V2 {
    float x;
    float y;
} V2;

extern V2 D_L00_001AFBC8;

extern void func_37CB80(void *, void *, float, void *);

extern float func_2EE048(float);

extern float ref_L00_003B7190_00 __attribute__((sda));

extern float ref_L00_003B7190_01 __attribute__((sda));

extern NODE *func_3100D8();

extern void func_31A658();

extern void func_310440();





INCLUDE_ASM("asm/levels", func_L00_003B39D0);





/* func_L00_003B4198 is defined in L00_003B3158-rings.c. */

INCLUDE_ASM("asm/levels", func_L00_003B4560);

/* func_L00_003B4EF8 is defined in L00_003B4EF8-g8.c. */



INCLUDE_ASM("asm/levels", func_L00_003B5BF8);



INCLUDE_ASM("asm/levels", func_L00_003B63D8);


extern void func_L00_003B6B70();
extern void func_L00_003B6F88();
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_002A0F48(void *);
extern char D_L00_001B8FF0[];

void func_L00_003B69D8(NODE *a0)
{
    void **slots;
    void **p;
    char *q;
    char *v;
    int i;

    slots = a0->f68;
    func_L00_003B6B70();
    v = (char *)slots;
    func_L00_003B6F88(a0);
    q = v + 0x10;
    p = slots;
    for (i = 1; i >= 0; i--) {
        func_00283098((char *)*p + 0x10, q, D_L00_001B8FF0);
        q += 0x10;
        func_00282CC0((char *)*p + 0x10, (char *)*p + 0x10, D_L00_001B8FF0 - 0x230);
        v = (char *)*p + 0xF0;
        func_002833F0((char *)*p + 0xC0, v);
        func_002A0F48(*p);
        p++;
    }
}

void func_L00_003B6A90(NODE *a0)
{
    void **b = (void **)a0->f68;
    OBJ *p;
    short key;

    if (b[0] != 0)
        func_310440(b[0]);
    if (b[1] != 0)
        func_310440(b[1]);

    key = D_L06_001AC000->fAA;
    for (p = D_L06_001B2820_1; p < D_L06_001B2824_1; p = (OBJ *)((char *)p + 256)) {
        if (p == 0)
            continue;
        if (p->fAA != key)
            continue;
        if (p->f20 == 254)
            continue;
        if (p->f20 == 253)
            continue;
        if (p == D_L06_001AC000)
            continue;
        func_310440(p);
    }
}


/* func_L00_003B6B70 is defined in L00_003B3158-pair.c. */



void func_L00_003B7190(float *a0, float *a1)
{
    if (func_2EE048(*a0) > ref_L00_003B7190_00) {
        if (*a0 < -ref_L00_003B7190_00)
            *a0 = ref_L00_003B7190_00;
        else if (*a0 > ref_L00_003B7190_00)
            *a0 = -ref_L00_003B7190_00;
    }

    if (func_2EE048(*a1) > ref_L00_003B7190_01) {
        if (*a1 < -ref_L00_003B7190_01)
            *a1 = ref_L00_003B7190_01;
        else if (*a1 > ref_L00_003B7190_01)
            *a1 = -ref_L00_003B7190_01;
    }
}


/* func_L00_003B7410 is defined in L00_003B7410-qcopy.c. */


/* shared native body of family 32969de2c02196ef */
void func_L00_003B75C8(void *object)
{
    OBJ *p;
    short key = D_L06_001AC000->fAA;

    for (p = D_L06_001B2820_1; p < D_L06_001B2824_1; p = (OBJ *)((char *)p + 256)) {
        if (p == 0)
            continue;
        if (p->fAA != key)
            continue;
        if (p->f20 == 254)
            continue;
        if (p->f20 == 253)
            continue;
        if (p == D_L06_001AC000)
            continue;
        p->f64(p);
    }
}


/* func_L00_003B79A0 is defined in L00_003B3158-collect-g8.c. */

void func_L00_003B8158(NODE *a0)
{
    NODE *o = a0->f68;

    if (o->f24 == 0)
        return;
    if (o->f2C == 0) {
        func_37CB80(o, (char *)o + 0x10, 1.0f, 0);
    } else {
        V2 v = D_L00_001AFBC8;

        func_37CB80(o, (char *)o + 0x10, 1.0f, &v);
    }
}




INCLUDE_ASM("asm/levels", func_L00_003B84F0);

/* Picks a target: the hero's current one while it is live; else, of the class 0xEE1 mobies
   func_002AF580 finds, the preferred one (while controller 1 holds a button of the hero's
   buttonMask) or the first one in range. */
Moby *func_L00_003B8E58(void *origin, void *direction, Moby *preferred,
                        float angle0, float angle1, float range, float angle2, float angle3)
{
    Moby *candidates[20];
    int count;
    Moby *current;
    float *info;
    Moby *candidate;
    TargetVars *vars;
    int i;
    Moby *fallback;
    TargetVars *fallbackVars;
    int j;

    current = D_00189E20.target;
    if (current && current->state != 0xFE && current->state != 0xFD) {
        info = func_002AB1F0(current);
        if (info && *info > 0.0f)
            return D_00189E20.target;
    }

    func_002AF580(origin, direction, &count, candidates, 20, 0, 0, 0,
                  angle0, angle1, range, angle2, angle3);

    /* The preferred moby first. */
    if (D_00189E20.f340 && !D_00189E20.f34E && (D_00138320[0] & D_00189E20.buttonMask)
        && preferred && preferred->state != 0xFE && preferred->state != 0xFD) {
        for (i = 0; i < count; ++i) {
            candidate = candidates[i];
            if (candidate && candidate->state != 0xFE && candidate->state != 0xFD
                && candidate == preferred && candidate->oClass == 0xEE1) {
                vars = candidate->vars;
                if ((vars->flags3B1 & 0x80) && vars->f20 > 0.0f) {
                    if (vars->maxDistance == 0.0f
                        || func_00282E80(origin, candidate->position) < vars->maxDistance)
                        return candidate;
                }
            }
        }
    }

    /* Then the first target in range. */
    for (j = 0; j < count; ++j) {
        fallback = candidates[j];
        if (fallback && fallback->state != 0xFE && fallback->state != 0xFD
            && fallback->oClass == 0xEE1) {
            fallbackVars = fallback->vars;
            if ((fallbackVars->flags3B1 & 0x80) && fallbackVars->f20 > 0.0f) {
                if (fallbackVars->maxDistance == 0.0f
                    || func_00282E80(origin, fallback->position) < fallbackVars->maxDistance)
                    return fallback;
            }
        }
    }
    return 0;
}

/* func_L00_003B9310 is defined in L00_003B3158-lock-g8.c. */
