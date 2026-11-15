#include "common.h"

typedef struct CrateMoby CrateMoby;

/* A crate's instance data. */
typedef struct {
    char pad00[0xA0];
    CrateMoby *above;           /* 0xA0: the crate stacked on this one */
    CrateMoby *below;           /* 0xA4: the crate this one stands on */
    char padA8[4];
    int flags;                  /* 0xAC */
    char padB0[0xCA - 0xB0];
    unsigned char burstFrame;   /* 0xCA */
    char padCB[0xF0 - 0xCB];
    void *attachment;           /* 0xF0: what the crate rides on, 0 for none */
} CrateVars;

struct CrateMoby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x34 - 0x21];
    unsigned short flags;       /* 0x34 */
    char pad36[0x68 - 0x36];
    CrateVars *vars;            /* 0x68 */
    char pad6C[0x98 - 0x6C];
    int collision;              /* 0x98 */
    char pad9C[0xAA - 0x9C];
    short oClass;               /* 0xAA */
    char padAC[0xBC - 0xAC];
    unsigned char command;      /* 0xBC */
    char padBD[0xE0 - 0xBD];
    float up[4];                /* 0xE0 */
};

/* The hit message that destroyed the crate. */
typedef struct {
    char pad00[0x10];
    float position[4];          /* 0x10 */
} CrateHit;

extern int D_001B1688;          /* the frame counter */
extern int D_001B24AC, D_001B24B0;
extern int D_001B1A80;
extern int D_001AF0F8 __attribute__((sda)), D_001AF0FC __attribute__((sda));
extern char *D_0018C0B0 NOT_SDA; /* the hero */
extern char *D_001AD7EC;

extern int func_00282C30(int);
extern int func_002E5DA0(int index, int value, char *object, int kind);
extern int func_002E5CF8(int index, int a1, char *a2);
extern int func_002ABB78(void *);
extern void func_00282A28(void);
extern char *func_002BC768(char *pos, int spin, int color, float spread, float low, float high,
                           float accel, float size);
extern void func_00282CF0(void *out, void *a, void *b);
extern float func_002AA340(int *, int, int);
extern int func_002AD330(char *, char *, char *, char *);
extern void func_002B0A68(char *self, int mask, float *arg2, float, float, float, float, unsigned char);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *out, void *a, void *b);
extern char *func_0032C700(void *position, int flash, int n0, int n1, int n2, int n3, int n4,
                           int orient, float size, float distance, int mode, int extra, int flags,
                           char *owner);

/* Destroys a crate: sounds, unlinks it from its stack, spawns debris and the bolts it drops. */
void func_003120C8(CrateMoby *self, int explode, CrateHit *hit)
{
    float position[4], direction[4], velocity[4];
    CrateVars *vars = self->vars;
    CrateMoby *p;
    int i, amount, kind;

    if (subtract_integer_with_clamp(gGameTime - D_001B24AC) >= 2) {
        switch (self->oClass) {
        case 0x1FA /* moby class 506 */: PlaySoundFromClassBank(0, 0, (char *)self, 0x1F4); break;
        case 0x1FF /* Ammo Crate */: PlaySoundFromClassBank(1, 0, (char *)self, 0x1FF); break;
        default: PlayMobySound(0, 0, (char *)self); break;
        }
        D_001B24AC = gGameTime;
    }
    if (subtract_integer_with_clamp(gGameTime - D_001B24B0) >= 2)
        D_001B24B0 = gGameTime;
    if (vars->above) {
        vars->above->vars->below = vars->below;
        vars->above->vars->flags |= 0x24;
    }
    if (vars->below) {
        if (!IsMobyInSpecialClassRange(vars->below->vars->above))
            TrapAlways();
        vars->below->vars->above = vars->above;
        vars->below->vars->flags |= 0x24;
    }
    p = self;
    do {
        CrateVars *v = p->vars;
        v->flags |= 0x20;
        p = v->above;
    } while (p);
    qcopy(position, self->position);
    position[2] += 0.3f;
    SpawnFlashParticle_002BC768((char *)position, 1, 0x40808080, 0.3f, 1.01f, 1.075f, 0.05f, 50000.0f);
    i = 4;
    do {
        SpawnFlashParticle_002BC768((char *)position, 1, 0x40808080, 0.3f, 1.01f, 1.07f, 0.05f, 50000.0f);
        --i;
    } while (i >= 0);
    if (hit)
        qcopy(direction, hit->position);
    else
        FastVecSub(direction, self->position, gHeroMoby_0018C0B0 + 0x10);
    if (subtract_integer_with_clamp(gGameTime - D_001AF0F8) >= 241) {
        D_001AF0FC = 0;
        D_001AF0F8 = gGameTime;
    } else if (gGameTime != D_001AF0F8) {
        StepIntTowardTarget(&D_001AF0FC, 0, subtract_integer_with_clamp(gGameTime - D_001AF0F8) >> 2);
        D_001AF0F8 = gGameTime;
    }
    if (D_001B1A80 >= 251 && D_001AF0FC < 5)
        amount = 4;
    else if (D_001B1A80 >= 201 && D_001AF0FC < 10)
        amount = 3;
    else if (D_001B1A80 >= 151 && D_001AF0FC < 15)
        amount = 2;
    else
        amount = D_001B1A80 >= 101 && D_001AF0FC < 20;
    if (amount) {
        int type;
        kind = 0;
        type = self->oClass;
        D_001AF0FC += amount;
        switch (type) {
        case 0x1F4 /* Crate */: case 0x1FF /* Ammo Crate */:
            switch (amount) {
            case 1: kind = 1; break;
            case 2: kind = 5; break;
            case 3: default: kind = 37; break;
            }
            break;
        case 0x1F5 /* Nanotech Crate */: case 0x200 /* Purple Nanotech Crate */:
            kind = (1 << (amount - 1)) - 1;
            if (kind > 15)
                kind = 15;
            break;
        }
        if (kind) {
            qzero_nc(velocity);
            if (vars->attachment && !D_001AD7EC)
                TransformPointByMobyAttachment((char *)self, vars->attachment, (char *)self->position, (char *)velocity);
            SpawnDebrisForMaskedParts((char *)self, kind, velocity, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        }
    }
    self->state = 3;
    self->flags |= 1;
    self->command = 15;
    self->collision = 0;
    if (explode) {
        vars->burstFrame = 1;
        vec_scale_to_length(velocity, self->up, 0.5f);
        FastVecAdd(velocity, velocity, self->position);
        SpawnExplosion(velocity, 0, 10, 10, 10, 10, 15, 0, 1.0f, 0.0f, 0, 0, 0, 0);
    }
}
