#include "include_asm.h"
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139574;
extern char *D_0018C0B0 NOT_SDA;
extern int D_L06_001AC790 __attribute__((sda));
extern Collision D_L06_001BFC80;
extern Material D_L06_0026C7F0[];
extern void func_00282CC0(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_L00_0038F3D8(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);
extern void func_L00_0038E880(void *, void *, void *);

typedef float Vector[4] __attribute__((aligned(16)));

typedef struct MobyClass {
    unsigned char pad00[0xF];
    unsigned char f0F;
    int f10;
    unsigned char pad14[0x10];
    float scale;
    unsigned char pad28[0x18];
    int f40;
    unsigned short flags;
} MobyClass;

typedef struct Moby {
    unsigned char pad00[0x10];
    float position[3];
    int f1C;
    unsigned char mode;
    unsigned char pad21[3];
    MobyClass *class;
    unsigned char pad28[4];
    float scale;
    unsigned char f30;
    unsigned char f31;
    unsigned short f32;
    unsigned short flags;
    unsigned short f36;
    unsigned char pad38[0x29];
    unsigned char f61;
    unsigned char f62;
    unsigned char pad63[5];
    void *state;
    unsigned char pad6C[0x2C];
    int f98;
    unsigned char pad9C[0xC];
    unsigned char fA8;
    unsigned char padA9[9];
    short fB2;
    short health;
    struct Moby *parent;
    unsigned char fBC;
    unsigned char padBD[0x33];
    Vector rotation;
} Moby;

typedef struct {
    unsigned char pad00[0x20];
    unsigned char tracker[0x3C];
    int flags;
    Vector home;
    unsigned char pad70[0x10];
    int level;
    int step;
    int sound;
    int zone;
} PlatformState;

typedef struct {
    unsigned char pad00[0x74];
    unsigned char active;
    unsigned char pad75[0x13];
    Moby *owner;
} SoundSlot;

extern char D_00188660[];
typedef struct { char prefix[0x80]; Vector position; } PlatformPlayer;
extern PlatformPlayer D_00189E20;
extern int func_L00_00324120(Moby *);
extern void func_002A7750(Moby *, int, int);
extern int func_002E59B0(Moby *, int);
extern int func_002E5CF8(int, int, Moby *);
extern void func_002E59F8(int);
extern int func_002ACBC8(void *, int);
extern float func_00282E48(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);


/* func_L06_0033BDC0 is matched in L06_0033BDC0-scene-g8.c. */


/* Implemented in L06_00361728-helpers.c. */

/* func_L06_003660F0 is matched in L06_003660F0.c (built with -mno-split-addresses). */


INCLUDE_ASM("asm/levels", func_L06_00396268);

/* func_L06_003C5ED8 is in L06_003C5ED8.c. */

/* func_L06_003D0AC8 is defined in L06_003D0AC8.c. */

void func_L06_003D0EE0(char *obj) {
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
    frame.packet.material = (D_00139574 + D_L06_0026C7F0)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L06_001BFC80;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L06_001BFC80;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L06_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &D_L06_001BFC80;
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


typedef struct {
    unsigned char pad00[0x68];
    short f68;
    unsigned char pad6A[2];
    int f6C;
    unsigned char pad70[0x24];
    int f94;
} MobyPart;

typedef struct {
    float value;
    short limit;
    unsigned char pad06[0x1A];
    int f20;
    int f24;
} MobyRecord;

typedef struct {
    unsigned char pad00[0x81];
    unsigned char count;
    unsigned char pad82;
    unsigned char small;
    int group;
} SpawnerState;

extern int func_002A8600(Moby **, int, int, int);
extern MobyPart *func_L00_00345AF0(Moby *);
extern void func_002AB650(Moby *);
extern void func_002A0F48(Moby *);
extern MobyRecord *func_002AB1F0(Moby *);
extern void func_0026FEB8(const char *, ...);
extern char D_L06_001AF990[];
extern int D_L06_001B2348[] __attribute__((sda));

/* Allocate a child and initialize its rendering, health and parent linkage. */
Moby *func_L06_003F3448(Moby *parent, Quad *position)
{
    Quad spawnPoint;
    Quad *savedPoint = &spawnPoint;
    SpawnerState *state;
    Moby *child, *result;
    MobyPart *part;
    MobyRecord *record;

    *savedPoint = *position;
    if (!parent)
        return 0;

    state = parent->state;
    result = 0;
    child = 0;
    if (func_002A8600(&child, state->group, 1, 1) == 0) {
        state->count++;
        {
            Moby *spawned = child;

            qcopy(spawned->position, savedPoint);
            spawned->f1C = 0;
        }
        child->mode = 0;
        child->fBC = 0;
        child->flags = child->class->flags;
        child->scale = child->class->scale;
        child->f30 = 0xFF;
        child->f32 = 0xFF;
        child->f31 = 1;
        if (child->class->f40)
            child->flags |= 0x10;
        if (child->class->f0F)
            child->flags |= 0x400;
        child->f36 = 0x7F80;
        child->f61 = 0xFF;
        child->f62 = 0xFF;
        child->fA8 = 0xFF;
        if (state->small)
            child->scale = child->class->scale * 0.1f;

        part = func_L00_00345AF0(child);
        if (part) {
            part->f94 = 0;
            part->f68 = 0;
            part->f6C = 0;
        }

        if (parent->health < child->health)
            child->health = parent->health;
        parent->health -= child->health;
        if (parent->health < 0)
            parent->health = 0;
        child->parent = parent;
        child->f98 = child->class->f10;
        func_002AB650(child);
        func_002A0F48(child);
        result = child;

        record = func_002AB1F0(result);
        if (record) {
            record->f24 = 0;
            record->f20 = 0;
            record->value = (float)record->limit;
        }
    } else {
        func_0026FEB8(D_L06_001AF990, parent->fB2, D_L06_001B2348[0]);
    }
    return result;
}

extern int func_002A9640(char *a0, int a1, int a2);

extern float func_002A96A0(char *a0, int a1);

extern void func_002AB800(char *a0, char *a1);

extern void func_002A6C58(char *a0, int a1, int a2);

extern void func_002AB8C0(char *a0, char *a1);

/* runs a moby's timer down and picks the dying or the revived path from what is left */
void func_L06_003F3690(char *a0, char *a1)
{
    float t = func_002A96A0(a0, func_002A9640(a0, 0xC30000, 0));

    if (t > 0.0f) {
        float left = *(float *)(a1 + 0x20) - t;

        *(float *)(a1 + 0x20) = left;
        if (left > 0.0f) {
            *(unsigned char *)(a1 + 0x57) = 0x5A;
            func_002AB800(a0, a1 + 0x50);
        } else {
            func_002A6C58(a0, 0, 3);
            *(unsigned char *)(a0 + 0x20) = 2;
            *(unsigned char *)(a1 + 0x57) = 0x78;
            func_002AB800(a0, a1 + 0x50);
        }
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
    func_002AB8C0(a0, a1 + 0x50);
}

extern int func_002A8508(int a0, int a1);

/* counts the 0x75E-slot entries that are live and returns the last free one */
int func_L06_003F3760(int a0, char *a1)
{
    char *s0 = a1;
    int free_slot = -1;
    int i;

    *(unsigned char *)(s0 + 0x81) = func_002A8508(*(int *)(s0 + 0x84), -1);
    for (i = 0; i < 20; i++) {
        char *m = ((char **)(s0 + 0xA0))[i];

        if (m != 0 && *(short *)(m + 0xAA) == 0x75E
            && *(unsigned char *)(m + 0x20) != 0xFE && *(unsigned char *)(m + 0x20) != 0xFD)
            (*(unsigned char *)(s0 + 0x81))++;
        else
            free_slot = i;
    }
    return free_slot;
}

INCLUDE_ASM("asm/levels", func_L06_003F3800);

/* func_L06_003F3EF0 is defined in L06_003F3EF0-helpers.c. */

extern void func_0029F338(char *a0);

/* clears one word of a 0x75D moby's state block when it is neither dying nor gone */
void func_L06_003F4020(char *a0, char *a1)
{
    char *m = *(char **)(a1 + 0x10);

    if (m != 0 && *(short *)(m + 0xAA) == 0x75D
        && *(unsigned char *)(m + 0x20) != 0xFE && *(unsigned char *)(m + 0x20) != 0xFD) {
        int *p = *(int **)(m + 0x68);

        p += *(unsigned char *)(a1 + 0x1C);
        p[40] = 0;
    }
    func_0029F338(a0);
}


extern int D_L06_001B3760[];

/* zeroes the six words a finished moby left behind */
void func_L06_003F4908(char *a0)
{
    if (*(unsigned char *)(a0 + 0x20) == 0) {
        int i;

        for (i = 5; i >= 0; i--)
            D_L06_001B3760[i] = 0;
        func_0029F338(a0);
    }
}


/* func_L06_003FDA08 is matched in L06_0033BDC0-g8.c (it takes the $gp addresses of small-data objects). */

/* func_L06_003FDEB8 is in L06_003FE178-g8.c. */

/* func_L06_003FE178 is in L06_003FE178-g8.c. */

/* func_L06_00400498 is in L06_00400498-g8.c. */

INCLUDE_ASM("asm/levels", func_L06_004012B0);

/* Move a platform between its two paths according to the player's height. */
void func_L06_00401820(Moby *moby)
{
    Vector oldPosition, oldRotation, movement;
    PlatformState *state = moby->state;
    SoundSlot *sound;
    int handle;

    qcopy(oldPosition, moby->position);
    qcopy(oldRotation, moby->rotation);
    switch (moby->mode) {
    case 0:
        state->flags |= 1;
        qcopy(state->home, moby->position);
        moby->mode = 1;
        state->sound = -1;
        state->level = 0;
        state->step = 0;
        break;
    case 1:
        if (func_L00_00324120(moby)) {
            if (state->level == 0) {
                func_002A7750(moby, 3, -1);
                if (!func_002E59B0(moby, state->sound))
                    state->sound = func_002E5CF8(0, 4, moby);
            } else {
                func_002A7750(moby, 2, -1);
                if (!func_002E59B0(moby, state->sound))
                    state->sound = func_002E5CF8(1, 4, moby);
            }
        }
        if (D_00189E20.position[2] < 55.0f && state->level == 0) {
            if (!func_002E59B0(moby, state->sound))
                state->sound = func_002E5CF8(0, 4, moby);
            func_002A7750(moby, 3, -1);
        } else if (D_00189E20.position[2] > 57.0f && state->level == 1 &&
                   func_002ACBC8(D_00189E20.position, state->zone)) {
            if (!func_002E59B0(moby, state->sound))
                state->sound = func_002E5CF8(1, 4, moby);
            func_002A7750(moby, 2, -1);
        }
        break;
    case 2:
        if (func_00282E48(moby->position, state->home) > 0.04f) {
            movement[0] = func_00283180(moby->rotation[2] + 1.57079649f) * 0.05f;
            movement[1] = func_00283198(moby->rotation[2] + 1.57079649f) * 0.05f;
            movement[2] = 0.0f;
            func_00282CC0(moby->position, moby->position, movement);
            if (state->step < 104)
                moby->position[2] += 0.07f;
            state->step++;
        } else if (!func_L00_00324120(moby)) {
            state->level = 0;
            handle = state->sound;
            if (handle != -1) {
                sound = (SoundSlot *)(D_00188660 + handle * 0x70);
                if (sound->owner == moby && sound->active)
                    func_002E59F8(handle);
            }
            state->sound = -1;
            func_002A7750(moby, 1, -1);
            qcopy(moby->position, state->home);
            state->step = 0;
        } else {
            goto stop;
        }
        break;
    case 3:
        if (moby->position[2] >= 50.75f) {
            if (moby->position[2] < 53.0f &&
                func_002ACBC8(D_00189E20.position, state->zone) &&
                D_00189E20.position[2] < moby->position[2])
                break;
            movement[0] = func_00283180(moby->rotation[2] - 1.57079649f) * 0.05f;
            movement[1] = func_00283198(moby->rotation[2] - 1.57079649f) * 0.05f;
            movement[2] = 0.0f;
            func_00282CC0(moby->position, moby->position, movement);
            if (state->step >= 61)
                moby->position[2] -= 0.07f;
            state->step++;
        } else if (!func_L00_00324120(moby) && moby->position[2] < 50.75f) {
            state->level = 1;
            handle = state->sound;
            if (handle != -1) {
                sound = (SoundSlot *)(D_00188660 + handle * 0x70);
                if (sound->owner == moby && sound->active)
                    func_002E59F8(handle);
            }
            state->sound = -1;
            func_002A7750(moby, 1, -1);
            state->step = 0;
        } else {
            goto stop;
        }
        break;
    }
    goto done;
stop:
    handle = state->sound;
    if (handle != -1) {
        sound = (SoundSlot *)(D_00188660 + handle * 0x70);
        if (sound->owner == moby && sound->active)
            func_002E59F8(handle);
    }
    state->sound = -1;
done:
    func_00282CF0(movement, moby->position, oldPosition);
    func_002AD6F0(state->tracker, movement, oldRotation, moby->rotation);
}


INCLUDE_ASM("asm/levels", func_L06_00402230);

/* func_L06_00403F60 is matched in L06_0033BDC0-g8.c (it reaches a global through $gp). */


/* func_L06_00419CA8 is defined in L06_00419CA8-g8.c. */

/* clears one word of a 0xA58 moby's state block when it is neither dying nor gone */
void func_L06_0041CAB0(char *a0, char *a1)
{
    char *m = *(char **)(a1 + 0x10);

    if (m != 0 && *(short *)(m + 0xAA) == 0xA58
        && *(unsigned char *)(m + 0x20) != 0xFE && *(unsigned char *)(m + 0x20) != 0xFD) {
        int *p = *(int **)(m + 0x68);

        p += *(unsigned char *)(a1 + 0x1C);
        p[40] = 0;
    }
    func_0029F338(a0);
}

