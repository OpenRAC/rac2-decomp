#include "common.h"

extern int D_L09_001B3620[] MACRO_ADDR;
extern int D_L09_001B3660[] MACRO_ADDR;
extern int D_L09_001B36A0[] MACRO_ADDR;
extern int D_L09_001B36E0[] MACRO_ADDR;
extern int D_L09_001B3720[] MACRO_ADDR;
extern int D_L09_001B3760[] MACRO_ADDR;
extern int D_L09_001B37A0[] MACRO_ADDR;

extern void func_002FC560(int, unsigned long long);
extern void func_L08_00389B68(int, int, unsigned long, int, unsigned long);
extern void func_00282D48(void *, void *, float);
extern float func_00282E48(void *, void *);
extern int func_00283DB8(void *, float);
extern int func_L02_002F1658(void);
extern float D_L09_001B37E0[16] MACRO_ADDR;
extern char D_L09_00256510[][0x60];
extern int D_L09_001B35E0[16] MACRO_ADDR;
extern unsigned char *D_L09_00255E90[16][2];
extern unsigned char *func_0029EFD0(int);
extern float func_00283CE0(int);
extern void func_L08_002F2D10(void *, void *);


extern void func_L09_003FCA58(void *, int, int);
extern void func_L09_003FC1E8(int, int, void *, int, int, int, int, int);


extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L09_001AC810 __attribute__((sda));
extern int D_L09_001B2FF0 __attribute__((sda)), D_L09_001B2FF8 __attribute__((sda));
extern Collision D_L09_001BFE40;
extern Material D_L09_002651F0[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0038F178(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern void func_00282CC0(char *, char *, char *);


/* Resident (boot) bodies that are placed in every level program: their addresses differ
   from level to level, so they are named by their boot catalogue name. */
extern int func_00282978(unsigned short *);
extern void func_002829A8(unsigned short *);

/* same resident body, called here with three arguments */
extern void func_002A7750_3(unsigned char *, int, int);

extern void func_002A7470(unsigned char *, int, int, int);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern void func_002AEE70(unsigned char *, unsigned char *, unsigned char *, float, float, float);
extern void func_002AEF28(unsigned char *, unsigned char *, unsigned char *, float, float, float);
extern float func_002AA3A8(unsigned char *, unsigned char *, float, float, float, float);

/* Shared level-runtime bodies this file reaches: the eight-argument record
   starter and the two-argument record stepper. */
extern void func_L00_00323448();
extern void func_L00_00323958(unsigned char *, unsigned char *);
/* the sixteen-float record starter, called here for its live-record flag */
extern int func_L00_00341820(char *, char *, char *, char *, int, float);

extern unsigned int D_L09_001FE6C0[];

/* Level 09 table of track pointers, indexed by a record byte. */
extern short *D_L09_001FB560[];

extern float func_002A7940(void);
extern void func_L09_003FB860(int);
extern void func_L09_003FB9F8(void *, int);
extern void func_L09_003FBF98(char *);

/* func_L09_002F8BA0 is defined in L09_002F8BA0-draw-g8.c. */

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L09_002F8FD8;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L09_002F8FD8 *mobs[1];
} MobList_L09_002F8FD8;

extern MobList_L09_002F8FD8 ref_L09_002F8FD8_00;
extern int D_001A79F0 __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L09_002F8BA0(void *);

/* Walks the level's list of mobs like func_L02_00300CE8; when the game state is 9 and the
   list's word at +0x30 is 1 it queues a callback. */
void func_L09_002F8FD8(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < ref_L09_002F8FD8_00.count; i++) {
        Mob_L09_002F8FD8 *mob = ref_L09_002F8FD8_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_002E64A0(mob);
        if (mob != 0 && mob->type == 0xFA0 && mob->p68 != 0)
            func_L00_00326048(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.0610865355f);
    }
    if (D_001A79F0 == 9 && ref_L09_002F8FD8_00.mode == 1)
        func_L00_002E6CF0(func_L09_002F8BA0, *(void **)((char *)&ref_L09_002F8FD8_00 + 0x194));
}



INCLUDE_ASM("asm/levels", func_L09_00352150);

void func_L09_0038B700(unsigned char *obj) {
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
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, ctx, position);
    func_002FEE70(*(int *)(ctx + 0x1C), ctx, 0);
    func_00300190(position, position);
    func_00300248(ctx, ctx);
    func_002FE880(position, ctx, 0.0030555557f);
    func_L00_0038F178(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L09_002651F0 + D_00139568[12] * sizeof(Material)))->material;
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
            func_002FD1B8(D_L09_001B2FF0, D_L09_001B2FF8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L09_001BFE40.point.f[2];
            effect = func_00312D58(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = func_002A7940();
                speed = func_002A7878(0.0f, 0.050000004f);
                frame.spread.f[0] = func_00283180(angle) * speed;
                frame.spread.f[1] = func_00283198(angle) * speed;
                frame.spread.f[2] = func_002A7878(0.050000004f, 0.10833334f);
                lifetime = func_002A7820(90, 120);
                func_002BFB38(&frame.position, spread, func_002A77E0(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L09_001BFE40;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L09_001BFE40;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L09_001AC810 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
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
        func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
    }
}

void func_L09_0038BB18(char *obj) {
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
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.0003055556f);
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L09_002651F0)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L09_001BFE40;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L09_001BFE40;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L09_001AC810 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L09_001BFE40;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
        else
            func_L00_0038E880(obj, &frame.velocity, &frame.normal);
    }
}



INCLUDE_ASM("asm/levels", func_L09_0039BA18);

/* func_L09_003C0DF8 is defined in L09_002F8BA0-mover.c (its own MACRO_ADDR declarations). */

/* Two-state gate on the record's byte 0x20. In state 0, as long as the live
   word the sub-object opens with is not -1, the record is stamped 0xFF, the
   shared eight-argument starter is run on the sub-object's track block and the
   record flips to state 1. In state 1 the sub-object's first float is scaled by
   2*pi/21600 (a per-frame 1/100 s turn rate) and folded into the record's own
   angle before its track block is stepped again. */
void func_L09_003C8CD8(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned char *s1 = *(unsigned char **)(s0 + 0x68);
    switch (s0[0x20]) {
    case 0:
        if (*(long long *)s1 == -1) {
            break;
        }
        {
            unsigned char stamp = 0xFF;
            *(unsigned char *)(s0 + 0x30) = stamp;
        }
        func_L00_00323448(s0, s1 + 0x30, 0x64, *(int *)(s1 + 4), *(int *)s1,
                          -1, 7, 0);
        s1[0xC5A] = 1;
        s0[0x20] = 1;
        break;
    case 1:
        *(float *)(s0 + 0xF0) = func_00283B98(
            *(float *)(s0 + 0xF0), *(float *)(s1 + 8) * 0.000290888245f);
        func_L00_00323958(s0, s1 + 0x30);
        break;
    }
}


/* Two-state step of a scripted record: while the state byte is clear a random
   duration in 150..200 is drawn and the record is marked active; in the active
   state the stored duration becomes a signed angle (0.000290888245f is
   2*pi/21600) which the resident step body folds into the record's angle. */
void func_L09_003DDAA0(unsigned char *a0) {
    int v1;
    unsigned char *a2;
    if (a0[0x20] != 0)
        return;
    v1 = *(int *)(a0 + 0x24);
    a2 = *(unsigned char **)(v1 + 0x48);
    func_002A7470(a0, 0,
                  (int)((float)a2[0x10] * ((float)((int)a0 % 3) * 0.333f)), 1);
    func_002A7750_3(a0, 1, -1);
}

/* Same measured body as func_L09_003DDAA0, at its own place in the level. */
void func_L09_003DDB40(unsigned char *a0) {
    int v1;
    unsigned char *a2;
    if (a0[0x20] != 0)
        return;
    v1 = *(int *)(a0 + 0x24);
    a2 = *(unsigned char **)(v1 + 0x48);
    func_002A7470(a0, 0,
                  (int)((float)a2[0x10] * ((float)((int)a0 % 3) * 0.333f)), 1);
    func_002A7750_3(a0, 1, -1);
}

/* The record's state byte is a small switch, not an if/else chain: the retail
   compares it against 0 and 1 in turn and falls straight out for anything else.
   State 0 draws a random duration in 150..200 and marks the record active;
   state 1 converts the drawn duration to a signed angle and folds it into the
   record's angle through the resident step body. */
void func_L09_003E31C0(unsigned char *a0) {
    switch (a0[0x20]) {
    case 0:
        a0[0xBC] = func_002A7820(0x96, 0xC8);
        if (func_002A77E0(2) != 0) {
            a0[0x95] = 1;
        }
        a0[0x20] = 1;
        break;
    case 1:
        if (a0[0x95] != 0) {
            *(float *)(a0 + 0xF4) = func_00283B98(
                *(float *)(a0 + 0xF4), -((float)a0[0xBC] * 0.000290888245f));
        } else {
            *(float *)(a0 + 0xF4) = func_00283B98(
                *(float *)(a0 + 0xF4), (float)a0[0xBC] * 0.000290888245f);
        }
        break;
    }
}

INCLUDE_ASM("asm/levels", func_L09_003E3288);

/* Arms the sub-object: the halfword 10 at 0x24, the angle 10.0f, the word
   at 0xA4 copied to 0x8C, the byte 3, the scale 1.0f and the live byte 0x2F,
   then the resident four-argument starter on the record. */
void func_L09_003F02D0(unsigned char *a0) {
    unsigned char *state = *(unsigned char **)(a0 + 0x68);

    *(float *)(state + 0x20) = 10.0f;
    *(short *)(state + 0x24) = 10;
    *(unsigned char *)(state + 0x28) = 3;
    *(float *)(state + 0x30) = 1.0f;
    *(unsigned char *)(state + 0x2F) = 1;
    *(int *)(state + 0x8C) = *(int *)(state + 0xA4);
    func_002A7750_3(a0, 0, 1);
}


/* Advances the object's saturation counter while it is below 0xFFFF and runs
   the resident two-call teardown on the sub-object; the counter's guard is an
   unsigned `x < 0xFFFFu`, which cc1 prints as `0xFFFE < x`. */
void func_L09_003F0330(unsigned char *a0) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    if (*(unsigned short *)(a0 + 0x96) < 0xFFFFu) {
        *(unsigned short *)(a0 + 0x96) = *(unsigned short *)(a0 + 0x96) + 1;
    }
    func_00282978((unsigned short *)(s0 + 0x92));
    func_002829A8((unsigned short *)(s0 + 0x90));
}


INCLUDE_ASM("asm/levels", func_L09_003F04D0);

typedef struct DobboMoby DobboMoby;

/* State block of a beam link (class 0xD09), at its +0x68. */
typedef struct {
    float direction[4];
    float velocity[4];
    DobboMoby *owner;
    DobboMoby *partner;
    float radius;
    float f2c;
    int timer;
    float max_distance;
    float duration_f;
    int hit_timer;
} DobboLinkState;

typedef struct {
    char pad00[0x24];
    float scale;
} DobboMobyClass;

/* Fields shared by the beam link and its owner. */
struct DobboMoby {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[2];
    unsigned char alpha;
    DobboMobyClass *cls;
    char pad28[4];
    float scale;
    unsigned char f30;
    unsigned char f31;
    unsigned short f32;
    unsigned short flags;
    char pad36[0x43 - 0x36];
    unsigned char f43;
    char pad44[4];
    float f48;
    char pad4C[0x60 - 0x4C];
    unsigned char f60;
    char pad61[0x68 - 0x61];
    DobboLinkState *data;
    char pad6C[0xAA - 0x6C];
    short type;
    char padAC[0xBC - 0xAC];
    unsigned char f_bc;
    char padBD[0xF0 - 0xBD];
    float rotation[3];
};

/* Spawns a beam-link moby (class 0xD09) at the given position with a random rotation, the
   class scale and the given direction, owner, partner link, radius, range and duration. A spawn
   without a partner also sets byte 0xBC. Returns the moby, or NULL if none was available. */
DobboMoby *func_L09_003F6820(void *position, void *direction, DobboMoby *owner, DobboMoby *partner,
                             int duration, float radius, float f2c, float max_distance)
{
    DobboMoby *moby = (DobboMoby *)func_0029EFD0(0xD09);
    DobboLinkState *state;

    if (moby) {
        moby->f30 = 255;
        moby->f32 = 255;
        moby->f31 = 1;
        state = moby->data;
        moby->rotation[2] = func_002A7940();
        moby->rotation[1] = func_002A7940();
        moby->rotation[0] = func_002A7940();
        moby->scale = moby->cls->scale;
        state->owner = owner;
        moby->flags |= 0x2200;
        qcopy(moby->position, position);
        qcopy(state->direction, direction);
        qzero(state->velocity);
        state->radius = radius;
        state->f2c = f2c;
        state->partner = partner;
        state->timer = duration;
        state->duration_f = func_00283CE0(duration);
        state->max_distance = max_distance;
        moby->alpha = 0;
        /* stored as !partner: a plain 1 here is not what retail emits */
        if (!partner)
            moby->f_bc = !partner;
        if (moby->f43)
            func_002A7470((unsigned char *)moby, 0, 0, 1);
        moby->f31 = 0;
        moby->f48 = 0.5f;
        moby->flags |= 1;
        func_002A7750_3((unsigned char *)moby, 0, -1);
    }
    return moby;
}

/* func_L09_003F69A0 is defined in L09_002F8BA0-g8.c (it reads a global through $gp). */

/* func_L09_003F6AB8 lives in the -g8.c brother: it loads a global through $gp. */

/* func_L09_003F6B28 is defined in L09_002F8BA0-beam-g8.c. */

/* Steps the beam-link slot table once per frame. State 0 clears all sixteen slots. State 1 walks
   them: a slot whose first moby has been destroyed is released, a slot in state 4 is handed to
   func_L09_003FB860, and any other live slot is handed to func_L09_003FB9F8 and moves to state 4.
   If any slot was handed over, func_L09_003FBF98 is queued on the moby to draw the links. */
void func_L09_003FB4D0(DobboMoby *moby)
{
    int i, count;
    int clearIndex;

    switch (moby->state) {
    case 0:
        for (clearIndex = 0; clearIndex < 16; clearIndex++) {
            D_L09_001B35E0[clearIndex] = 0;
            D_L09_00255E90[clearIndex][0] = 0;
            D_L09_00255E90[clearIndex][1] = 0;
        }
        moby->state = 1;
        moby->f30 = 255;
        break;
    case 1:
        count = 0;
        for (i = 0; i < 16; i++) {
            if (D_L09_001B35E0[i] == 1) {
                if ((signed char)D_L09_00255E90[i][0][0x20] < 0) {
                    D_L09_00255E90[i][0] = 0;
                    D_L09_001B35E0[i] = 0;
                    D_L09_00255E90[i][1] = 0;
                }
            } else if (D_L09_001B35E0[i] == 4) {
                func_L09_003FB860(i);
            } else if (D_L09_001B35E0[i]) {
                count++;
                func_L09_003FB9F8(D_L09_00255E90[i][0], i);
                D_L09_001B35E0[i] = 4;
            }
        }
        if (count)
            func_L08_002F2D10(func_L09_003FBF98, moby);
        break;
    }
}


/* Starts a record slot: the first pass returns 1 when the id is already live
   in either half of a slot, the second takes the first free slot, fills its
   parallel tables and returns 1; 0 when every slot is taken. */
int func_L09_003FB650(unsigned char *object, unsigned char *partner, int third, int fourth)
{
    int i;
    int j;

    for (i = 0; i < 16; i++) {
        if (D_L09_00255E90[i][0] == object)
            return 1;
        if (D_L09_00255E90[i][1] == object)
            return 1;
    }
    for (j = 0; j < 16; j++) {
        if (D_L09_00255E90[j][0] == 0) {
            D_L09_00255E90[j][0] = object;
            D_L09_00255E90[j][1] = partner;
            D_L09_001B3620[j] = 0;
            D_L09_001B3660[j] = 0;
            D_L09_001B36A0[j] = 0;
            D_L09_001B36E0[j] = -1;
            D_L09_001B3720[j] = -1;
            D_L09_001B3760[j] = third;
            D_L09_001B37A0[j] = fourth;
            D_L09_001B37E0[j] = 0;
            D_L09_001B35E0[j] = 1;
            return 1;
        }
    }
    return 0;
}



/* Releases the first slot holding the id in either half: both halves and the
   slot's live word are cleared, and the two handles at 0x1B36E0 and 0x1B3720
   are given back to the shared release body. 1 when a slot was found. */



/* Same release at its own place in the level, on the id byte of a slot rather
   than a live id: both halves and the slot's live word are cleared and the two
   handles are given back. */


extern Quad D_L09_00255F10[][4];
extern Quad D_L09_00256310[];
extern void func_00282B50(void *, void *, int);

/* Stores a new record for the link that holds object, copies both end positions and moves its
   state on (1 to 2, 4 to 3). Returns 1, or 0 when no link holds object. */
int func_L09_003FB908(unsigned char *object, void *src)
{
    Quad (*blocks)[4] = D_L09_00255F10;
    int i;

    for (i = 0; i < 16; i++) {
        if (D_L09_00255E90[i][0] == object || D_L09_00255E90[i][1] == object) {
            unsigned char **row;
            Quad *position;
            if (D_L09_001B35E0[i] == 1)
                D_L09_001B35E0[i] = 2;
            else if (D_L09_001B35E0[i] == 4)
                D_L09_001B35E0[i] = 3;
            func_00282B50(blocks[i], src, 0x40);
            position = &blocks[i][3];
            row = D_L09_00255E90[i];
            qcopy(position, row[0] + 0x10);
            qcopy(&D_L09_00256310[i], row[1] + 0x10);
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/levels", func_L09_003FB9F8);

typedef struct {
    int x;
    int y;
} DobboLinkScreen;

/* Draws every active beam link whose bounding sphere is visible: a large and a small textured
   quad per link, with a per-link scroll offset that advances while func_L02_002F1658() is true. */
void func_L09_003FBF98(char *moby)
{
    Vec sphere, midpoint;
    int i, fade, x, y, big, small;
    char *small_tex;
    DobboLinkScreen *screen = *(DobboLinkScreen **)(moby + 0x68);

    func_002FC560(0x47, 0x51001);
    for (i = 0; i < 16; i++) {
        if (!D_L09_00255E90[i][0] || !D_L09_00255E90[i][1] || D_L09_001B35E0[i] < 2)
            continue;

        func_00282CC0((char *)&midpoint, D_L09_00255E90[i][0] + 0x10, D_L09_00255E90[i][1] + 0x10);
        sphere.q = midpoint.q;
        func_00282D48(&midpoint, &sphere, 0.5f);
        sphere.f[3] = func_00282E48(D_L09_00255E90[i][0] + 0x10, D_L09_00255E90[i][1] + 0x10) * 0.5263158f;
        if (func_00283DB8(&sphere, 64.0f) == -1)
            continue;

        big = i * 2;
        small = big + 1;
        fade = D_L09_00255E90[i][0][0x23];
        if (func_L02_002F1658()) {
            D_L09_001B37E0[i] -= 0.2f;
            if (D_L09_001B37E0[i] <= -8.0f)
                D_L09_001B37E0[i] += 8.0f;
        }
        small_tex = D_L09_00256510[small];
        func_L09_003FCA58(D_L09_00255E90[i][0], i, fade);
        y = screen->y + 63;
        x = screen->x + 63;
        func_L09_003FC1E8(y, x, D_L09_00256510[big], 128, 64, fade, i, -1);
        func_L09_003FC1E8(y, x, small_tex, 48, 16, fade, i, func_002A7820(1, 6));
    }
    func_L08_00389B68(2, 0x47, 0x5340BUL, 0x42, 0x8000000044UL);
}

/* func_L09_003FC1E8 is defined in L09_003FC1E8-g64.c. */

/* func_L09_003FCA58 is defined in L09_003FCA58-g64.c. */

/* func_L09_003FCF68 is defined in L09_002F8BA0-beam-g64.c. */

/* func_L09_003FD128 is in L09_003FD128-g8.c. */

/* func_L09_003FD128 is defined in L09_003FD128-g8.c. */

/* func_L09_003FD460 is defined in L09_002F8BA0-beam-g64.c (a 64-byte table read through $gp). */

/* func_L09_003FD7D0 lives in L09_003FD7D0-overlay.c. */


/* Samples the sub-object through the shared record starter and ramps the
   three floats it wrote into the object's 0x390/0x394/0x398 channels at 0.02
   per frame. When the sub-object's halfword 0x32A is clear and the starter
   reported no live record, the saved 0x324 word and 0x3EC float are put back
   and the 0x388 angle is negated. */
void func_L09_003FDC58(unsigned char *a0) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float buf[4];
    float step = 0.02f;
    float keep = *(float *)(s0 + 0x3EC);
    int save = *(int *)(s0 + 0x324);
    int live = func_L00_00341820(
        (char *)D_L09_001FE6C0[*(int *)(s0 + 0x318)], (char *)buf,
        (char *)(s0 + 0x324), (char *)(s0 + 0x3EC), *(short *)(s0 + 0x32A),
        *(float *)(s0 + 0x388));
    func_002AA3A8((char *)(s0 + 0x390), (char *)(s0 + 0x3A0), buf[0], step, 0.2f,
                  0.0f);
    func_002AA3A8((char *)(s0 + 0x394), (char *)(s0 + 0x3A4), buf[1], step, 0.2f,
                  0.0f);
    func_002AA3A8((char *)(s0 + 0x398), (char *)(s0 + 0x3A8), buf[2], step, 0.2f,
                  0.0f);
    if (*(short *)(s0 + 0x32A) == 0 && live != 0) {
        *(float *)(s0 + 0x3EC) = keep;
        *(int *)(s0 + 0x324) = save;
        *(float *)(s0 + 0x388) = -*(float *)(s0 + 0x388);
    }
}

/* Sums the floats of a sixteen-byte-strided sample block, scales the total by
   the object's 0x38C and 0x3B0, and hands it to the shared record starter
   together with a zero pair it fills in; the three floats it wrote then ramp
   the object's 0x10/0x14/0x18 channels at 0.02 per frame. */


/* Feeds the sub-object two measured channel ramps, then, only in state 1 and
   only while the sub-object's halfword 0x3D4 is live, stamps it 0x104 and
   folds a 2.0943954 radian turn into its 0xF8 angle -- sign drawn from the
   resident two-way draw -- before the shared four-float ramp body runs on the
   block at 0x3D8. */
void func_L09_003FDED8(unsigned char *a0) {
    unsigned char *s1 = a0;
    unsigned char *s0 = *(unsigned char **)(s1 + 0x68);
    func_002AEE70(a0, s0 + 0x3C0, s0 + 0x3C4, 0.25f, 0.06f, -1.0f);
    func_002AEF28(s1, s0 + 0x3C8, s0 + 0x3CC, 0.15f, 0.05f, 0.025f);
    if (s1[0x20] != 1)
        return;
    if (func_00282978((unsigned short *)(s0 + 0x3D4)) != 0) {
        float t = 2.0943954f;
        *(short *)(s0 + 0x3D4) = 0x104;
        if (func_002A77E0(2) != 0)
            t = -t;
        *(float *)(s0 + 0x3D0) = func_00283B98(*(float *)(s1 + 0xF8), t);
    }
    func_002AA3A8(s1 + 0xF8, s0 + 0x3D8, *(float *)(s0 + 0x3D0), 0.003f, 0.2f,
                  0.02f);
}

/* func_L09_003FDFF0 is defined in L09_003FDFF0-helpers.c. */

/* func_L09_003FE0C0 is defined in L09_003FE0C0.c. */

INCLUDE_ASM("asm/levels", func_L09_003FE2D8);

/* Walks the record's track while its signed halfwords stay non-negative and
   returns the entry whose measured value is largest, skipping the entries
   whose field 0xB2 is in the twenty-value screen table. */
INCLUDE_ASM("asm/levels", func_L09_003FE3B0);


/* func_L09_003FE4D0 is defined in L09_003FE4D0.c. */

/* Number of leading non-negative halfwords of the track the record's byte 0x21
   selects, counting the first negative one. The pointer has to walk itself
   (`v = *q; q++;`) inside a do/while: the indexed spelling rotates the two
   body instructions the other way and grows an induction-variable copy. */
int func_L09_003FE620(unsigned char *a0) {
    short *q = D_L09_001FB560[a0[0x21]];
    int i = 0;
    int v;
    if (q == 0)
        return 0;
    do {
        v = *q;
        q++;
        i++;
    } while (v >= 0);
    return i;
}

/* func_L09_003FE670 is defined in L09_003FE670-g8.c. */

/* Same counter step as func_L09_003F0330, followed by the sub-object's own
   two-track restart: track 0x412 only when its live word at 0x154 is clear,
   then tracks 0x428 and 0x426 unconditionally. */
void func_L09_003FE918(unsigned char *a0) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    if (*(unsigned short *)(a0 + 0x96) < 0xFFFFu) {
        *(unsigned short *)(a0 + 0x96) = *(unsigned short *)(a0 + 0x96) + 1;
    }
    if (*(int *)(s0 + 0x154) == 0) {
        func_00282978((unsigned short *)(s0 + 0x412));
    }
    func_002829A8((unsigned short *)(s0 + 0x428));
    func_00282978((unsigned short *)(s0 + 0x426));
}

/* func_L09_003FE978 is defined in L09_002F8BA0-g8.c (it reads the group count through $gp). */
