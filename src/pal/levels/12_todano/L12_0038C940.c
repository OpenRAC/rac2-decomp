#include "include_asm.h"



#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision D_L00_001BF200;
extern Material D_L00_00262570[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_PAL_L00_00392250(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_PAL_002C0838(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(void *);
extern void func_002FEE50(int);
extern void func_PAL_L00_00390F48(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

void func_PAL_L12_00396400(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, ctx, position);
    func_002FEE70(*(int *)(ctx + 0x1C), ctx, 0);
    func_00300190(position, position);
    func_00300248(ctx, ctx);
    func_002FE880(position, ctx, 0.0044f);
    func_PAL_L00_00392250(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L00_00262570 + D_00139568[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!func_00278E78() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            func_002FD1B8(D_L00_001B2630, D_L00_001B2638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.030000001f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L00_001BF200.point.f[2];
            effect = func_00312D58(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = func_002A7940();
                speed = func_002A7878(0.0f, 0.060000002f);
                frame.spread.f[0] = func_00283180(angle) * speed;
                frame.spread.f[1] = func_00283198(angle) * speed;
                frame.spread.f[2] = func_002A7878(0.060000002f, 0.13000001f);
                lifetime = func_002A7820(90, 120);
                func_PAL_002C0838(&frame.position, spread, func_002A77E0(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L00_001BF200;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0xF1)
                    goto finish;
                reread = &D_L00_001BF200;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
                func_00282F20(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
                func_00282F20(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
    }
}


extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_PAL_L00_00391958(void *, void *, void *);
extern void func_PAL_L00_00392500(void *);

void func_PAL_L12_00396818(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.00044f);
    func_PAL_L00_00392500(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L00_00262570)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L00_001BF200;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0xF2)
                goto finish;
            reread = &D_L00_001BF200;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L00_001BF200;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 17)
            func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
        else
            func_PAL_L00_00391958(obj, &frame.velocity, &frame.normal);
    }
}



/* func_PAL_L12_003A44BC: per-frame update of a crate, after RAC1's crate_update
 * (OpenRAC/rac1-decomp, src/overlays/shared/morphoray_chicken_and_drones.c, GPL-3.0).
 * States: 0 initialize, 1 process hits, 2 class-change cooldown, 3 broken, 4 reactivation delay,
 * 5 detonation countdown, 6 wait to respawn. */
typedef struct CrateMoby CrateMoby;

typedef struct {
    char pad00[0x10];
    int collision;              /* 0x10 */
} CrateClass;

/* The hit message func_002A9640 returns. */
typedef struct {
    char pad00[0x24];
    int flags;                  /* 0x24: 0x1000000 a touch, 0x20000 detonates at once */
    char pad28[4];
    float f2C;                  /* 0x2C */
} CrateHit;

typedef struct {
    char pad00[0x1E];
    unsigned short flags;       /* 0x1E */
} CrateColl;

/* A crate's instance data. */
typedef struct {
    char pad00[0x20];
    CrateColl coll;             /* 0x20 */
    char pad40[0x90 - 0x40];
    float f90[4];               /* 0x90 */
    CrateMoby *above;           /* 0xA0: the crate stacked on this one */
    CrateMoby *below;           /* 0xA4: the crate this one stands on */
    int fA8;                    /* 0xA8 */
    int flags;                  /* 0xAC: 0xC runs the stack motion, clear bit 0 attaches to the ground */
    char padB0[4];
    int frame;                  /* 0xB4: D_001B1688 when last updated */
    long long savedColor;       /* 0xB8 */
    char padC0[6];
    short fC6;                  /* 0xC6 */
    unsigned char respawns;     /* 0xC8 */
    unsigned char respawnTimer; /* 0xC9: 255 for never */
    unsigned char burstFrame;   /* 0xCA */
    char padCB;
    int fCC;                    /* 0xCC */
    char padD0[0xFC - 0xD0];
    void *linked;               /* 0xFC */
    int f100;                   /* 0x100 */
} CrateVars;

struct CrateMoby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    unsigned char group;        /* 0x21 */
    char pad22[2];
    CrateClass *pclass;         /* 0x24 */
    char pad28[0x31 - 0x28];
    unsigned char visible;      /* 0x31 */
    short drawDistance;         /* 0x32 */
    unsigned short flags;       /* 0x34 */
    char pad36[2];
    long long color;            /* 0x38 */
    char pad40[0x68 - 0x40];
    CrateVars *vars;            /* 0x68 */
    char pad6C[0x98 - 0x6C];
    int collision;              /* 0x98 */
    char pad9C[0xA8 - 0x9C];
    unsigned char hitSlot;      /* 0xA8 */
    char padA9;
    short oClass;               /* 0xAA */
    char padAC[0xB4 - 0xAC];
    short fB4;                  /* 0xB4 */
    char padB6[0xBC - 0xB6];
    unsigned char command;      /* 0xBC: the countdown of states 2, 4 and 5 */
    char padBD[0xC0 - 0xBD];
    float forward[4];           /* 0xC0 */
    char padD0[0x10];
    float up[4];                /* 0xE0 */
};

/* Prefix of the hero. */
typedef struct {
    char pad000[0x26C];
    CrateMoby *collHitMoby;     /* 0x26C */
    CrateMoby *f270;            /* 0x270 */
    char pad274[0x33C - 0x274];
    CrateMoby *groundMoby;      /* 0x33C */
    char pad340[0x34E - 0x340];
    short airFrames;            /* 0x34E */
    char pad350[0x588 - 0x350];
    CrateMoby *ledgeMoby;       /* 0x588 */
    char pad58C[0x2290 - 0x58C];
    CrateMoby *moby;            /* 0x2290 */
    char pad2294[0x229C - 0x2294];
    int f229C;                  /* 0x229C */
} CrateHero;

typedef struct {
    float position[4];          /* 0x00 */
    CrateMoby *moby;            /* 0x10 */
    int f14;                    /* 0x14 */
    char pad18[4];
    float f1C;                  /* 0x1C */
    int f20;                    /* 0x20 */
    char pad24[0xC];
} __attribute__((aligned(16))) CrateBurst;

extern int D_001B1688 MACRO_ADDR;   /* the frame counter */
extern char D_00189E20[];
extern char D_001BF000[];
extern int D_0018C0BC;

#define HERO ((CrateHero *)D_00189E20)

extern void func_PAL_00313A70(CrateMoby *);
extern CrateHit *func_002A9640(CrateMoby *, int, int);
extern int func_002ABB78(CrateMoby *);
extern void func_00282C88(void *);
extern void func_003116E8(CrateMoby *);
extern void *func_00312E20(CrateMoby *, int);
extern int func_002B3868(CrateMoby *);
extern void func_PAL_00313538(CrateMoby *, int, CrateHit *);
extern void func_PAL_003133E0(CrateMoby *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00277F48(void *, int, CrateMoby *, void *, float);
extern void func_002A9850(CrateMoby *, void *, void *, int, CrateMoby *, int, int, int, float, float, float);
extern int func_002A7820(int, int);
extern void func_0029F338(CrateMoby *);
extern int func_00283DB8(void *, float);
extern int func_002829A8(unsigned char *);
extern void func_002A7750(CrateMoby *, int, int);
extern int func_002A8600(CrateMoby **, int, int, int);
extern int func_002A86E8(CrateMoby **, CrateMoby *, int, int);
extern float func_00282E80(void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_002E5CF8(int, int, CrateMoby *);
extern void func_002A0488(CrateMoby *, int, int, int);

void func_PAL_L12_003A44BC(CrateMoby *moby)
{
    CrateBurst burst;
    float position[4] __attribute__((aligned(16)));
    CrateMoby *found;
    CrateVars *vars = moby->vars;
    CrateHit *hit;
    int touched;
    CrateColl *coll = &vars->coll;

    if (vars->flags & 0xC) {
        if (vars->frame != D_001B1688) {
            func_PAL_00313A70(moby);
        }
    }
    if (vars->above == 0) {
        coll->flags |= 1;
    }
    hit = func_002A9640(moby, 0x5830001, 0);
    touched = 0;
    if (hit != 0 && hit->flags == 0x1000000) {
        hit = 0;
        touched = 1;
    }
    switch (moby->state) {
    case 0:
        if (vars->above != 0 && !func_002ABB78(vars->above)) {
            vars->above = 0;
        }
        if (vars->below != 0 && !func_002ABB78(vars->below)) {
            vars->below = 0;
        }
        func_00282C88(vars->f90);
        moby->state = 1;
        vars->fA8 = 0;
        if (moby->oClass == 0x1FF) {
            vars->frame++;
        }
        if (vars->fCC == 0) {
            vars->flags |= 0x14;
            if ((vars->flags ^ 1) & 1) {
                func_003116E8(moby);
            }
        }
        vars->linked = 0;
        if (moby->oClass == 0x1FF) {
            vars->fC6 = 100;
        } else if (moby->oClass == 0x1F5) {
            vars->linked = func_00312E20(moby, 0);
        } else if (moby->oClass == 0x200) {
            vars->linked = func_00312E20(moby, 1);
        }
        break;
    case 1:
        if (func_002B3868(moby)) {
            vars->f100 = 0;
        }
        if (moby->oClass == 0x1F9 &&
            (HERO->f270 == moby || HERO->collHitMoby == moby ||
             (HERO->groundMoby == moby && HERO->airFrames == 0) ||
             HERO->ledgeMoby == moby || touched)) {
            if (HERO->f229C == 15) {
                func_PAL_00313538(moby, 1, 0);
                func_PAL_003133E0(moby);
                break;
            }
            moby->command = 0;
            moby->state = 5;
            break;
        }
        if (hit != 0 && hit->f2C > 0.0f) {
            int doHit = 1;

            if (moby->oClass == 0x1F6 && !(hit->flags & 0x20000)) {
                doHit = 0;
            }
            if (moby->oClass == 0x1F9) {
                moby->state = 5;
                if (hit->flags & 0x20000) {
                    moby->command = 1;
                } else {
                    moby->command = func_00283CF0(((func_002A7878(5.0f, 15.0f)) * 5.0f + 2.0f) * 0.16666667f);
                }
                vars->savedColor = moby->color;
                doHit = 0;
            }
            if (doHit) {
                func_PAL_00313538(moby, moby->oClass == 0x1F9, hit);
                func_PAL_003133E0(moby);
            }
            moby->hitSlot = 255;
        }
        break;
    case 2:
        if (--moby->command == 255) {
            moby->hitSlot = 255;
            moby->state = 1;
        }
        break;
    case 3:
        if (moby->oClass == 0x1F9 && vars->burstFrame < 18) {
            float radius;
            int target;

            burst.moby = moby;
            burst.f1C = 2.0f;
            qcopy(&burst, moby->forward);
            burst.f20 = 0;
            func_00282F20(position, moby->up, 0.5f);
            func_00282CC0(position, position, moby->position);
            radius = func_00283CE0(vars->burstFrame) * 0.05882353f;
            burst.f14 = 1;
            func_00277F48(position, 16, moby, &burst, radius + radius);
            burst.f14 = 0x30000;
            target = func_00277F48(position, 16, HERO->moby, 0, radius * 3.0f);
            if (target != 0) {
                func_002A9850(moby, position, D_001BF000, target, HERO->moby, 0x10000, 0, 0x30000, 4.0f, 1.0f, 1.0f);
            }
            vars->burstFrame++;
        } else if (vars->respawns != 0) {
            moby->flags = (moby->flags | 0x41) & 0xEFFF;
            moby->collision = 0;
            if (moby->fB4 >= 2) {
                moby->fB4 = 1;
            }
            moby->state = 6;
            if (vars->respawnTimer != 255) {
                vars->respawnTimer = func_002A7820(30, 60);
            }
        } else {
            func_0029F338(moby);
            break;
        }
        moby->hitSlot = 255;
        break;
    case 6:
        vars->f100++;
        if (vars->respawnTimer == 255) {
            break;
        }
        qcopy(&burst, moby->position);
        burst.position[2] += 0.5f;
        burst.position[3] = 1.0f;
        if (func_00283DB8(&burst, (float)moby->drawDistance) != -1 || !func_002829A8(&vars->respawnTimer)) {
            goto done;
        }
        if (moby->group == 255) {
            func_002A7750(moby, 1, -1);
            moby->flags = (moby->flags & 0xFFBE) | 0x1000;
            moby->collision = moby->pclass->collision;
            break;
        }
        func_002A8600(&found, moby->group, 0, 0);
        while (found != 0) {
            if (moby != found && !(func_00282E80(moby->position, found->position) > 0.1f) && found->state == 1) {
                CrateVars *other = found->vars;

                if (other->above == 0) {
                    qcopy(moby->position, found->position);
                    moby->position[2] += 1.0f;
                    other->above = moby;
                    vars->below = found;
                    vars->above = 0;
                    moby->state = 1;
                    moby->visible = 1;
                    moby->flags &= 0xFFFE;
                    moby->collision = moby->pclass->collision;
                    moby->flags |= 0x1000;
                    break;
                }
            }
            func_002A86E8(&found, found, 0, 0);
        }
        if (moby->state != 1) {
            moby->position[2] = func_002A89A8(moby->position, 0, 0.5f);
            moby->state = 1;
            vars->above = 0;
            vars->below = 0;
            moby->visible = 1;
            moby->flags &= 0xFFFE;
            moby->collision = moby->pclass->collision;
        }
        goto done;
    case 5:
        if (moby->command == 0) {
            moby->command = 149;
            vars->savedColor = moby->color;
        } else if (moby->command >= 13 && hit != 0) {
            moby->command = func_00283CF0(((func_002A7878(5.0f, 15.0f)) * 5.0f + 2.0f) * 0.16666667f);
        }
        if (moby->command % 50 == 47 || moby->command == 11) {
            func_002E5CF8(1, 32, moby);
        }
        if (moby->command % 50 > 33 || moby->command < 12) {
            func_002A0488(moby, 200, 64, 64);
        } else {
            moby->color = vars->savedColor;
        }
        if (moby->command == 1 || D_0018C0BC == 22) {
            moby->color = vars->savedColor;
            func_PAL_00313538(moby, 1, 0);
            func_PAL_003133E0(moby);
        }
        moby->hitSlot = 255;
        moby->command--;
        break;
    case 4:
        if (func_002829A8(&moby->command)) {
            moby->state = 1;
            moby->flags &= 0xFFFE;
        }
done:
        moby->hitSlot = 255;
        break;
    }
}
