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




/* func_L06_003C5ED8 is in L06_003C5ED8.c. */

/* func_L06_003D0AC8 is defined in L06_003D0AC8.c. */

/* Updates a falling object: it moves, checks what it touches, and bounces or breaks when it hits something. */
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
    FastVecAdd(position, position, ctx);
    ComputeViewDirection(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    SpawnSparkPuff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L06_0026C7F0)->material;
    qcopy(&frame.packet.vector, ctx);
    FastVectorNormalizeHelper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L06_001BFC80;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == gHeroMoby_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L06_001BFC80;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L06_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            FastVectorNormalize(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L06_001BFC80;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            FastVectorNormalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (FastFloatHelperD(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        ClearEntryFlag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            SpawnBigExplosionEffect(obj, &frame.velocity, &frame.normal);
        else
            SpawnImpactBurst(obj, &frame.velocity, &frame.normal);
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
    if (GetFirstMobyInGroup(&child, state->group, 1, 1) == 0) {
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

        part = ReturnZeroUnsigned(child);
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
        CopyHeroField38ToMoby(child);
        func_002A0F48(child);
        result = child;

        record = GetMobyPrivateValue0(result);
        if (record) {
            record->f24 = 0;
            record->f20 = 0;
            record->value = (float)record->limit;
        }
    } else {
        STUB_printf(D_L06_001AF990, parent->fB2, D_L06_001B2348[0]);
    }
    return result;
}

extern int func_002A9640(char *a0, int a1, int a2);

extern float func_002A96A0(char *a0, int a1);

extern void func_002AB800(char *a0, char *a1);

extern void func_002A6C58(char *a0, int a1, int a2);

extern void func_002AB8C0(char *a0, char *a1);

/* runs a moby's timer down and picks the dying or the revived path from what is left */
void func_L06_003F3690(char *moby, char *vars)
{
    float damageStep = UpdateAimTargetStrength(moby, FindOwnedEffectSlot(moby, 0xC30000, 0));

    if (damageStep > 0.0f) {
        float timeLeft = *(float *)(vars + 0x20) - damageStep;

        *(float *)(vars + 0x20) = timeLeft;
        if (timeLeft > 0.0f) {
            *(unsigned char *)(vars + 0x57) = 0x5A;
            StartColorFade(moby, vars + 0x50);
        } else {
            SetDeathBits(moby, 0, 3);
            *(unsigned char *)(moby + 0x20) = 2;
            *(unsigned char *)(vars + 0x57) = 0x78;
            StartColorFade(moby, vars + 0x50);
        }
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
    UpdateColorFade(moby, vars + 0x50);
}

extern int func_002A8508(int a0, int a1);

/* counts the 0x75E-slot entries that are live and returns the last free one */
int func_L06_003F3760(int spawnerMoby, char *varsIn)
{
    char *vars = varsIn;
    int freeSlot = -1;
    int i;

    *(unsigned char *)(vars + 0x81) = CountMobysInGroupNotInState(*(int *)(vars + 0x84), -1);
    for (i = 0; i < 20; i++) {
        char *member = ((char **)(vars + 0xA0))[i];

        if (member != 0 && *(short *)(member + 0xAA) == 0x75E /* moby class 1886 */
            && *(unsigned char *)(member + 0x20) != 0xFE && *(unsigned char *)(member + 0x20) != 0xFD)
            (*(unsigned char *)(vars + 0x81))++;
        else
            freeSlot = i;
    }
    return freeSlot;
}

/* func_L06_003F3800 is matched in L06_003F3800-g8.c. */

/* func_L06_003F3EF0 is defined in L06_003F3EF0-helpers.c. */

extern void func_0029F338(char *a0);

/* clears one word of a 0x75D moby's state block when it is neither dying nor gone */
void func_L06_003F4020(char *moby, char *vars)
{
    char *spawnerMoby = *(char **)(vars + 0x10);

    if (spawnerMoby != 0 && *(short *)(spawnerMoby + 0xAA) == 0x75D /* moby class 1885 */
        && *(unsigned char *)(spawnerMoby + 0x20) != 0xFE && *(unsigned char *)(spawnerMoby + 0x20) != 0xFD) {
        int *spawnerVars = *(int **)(spawnerMoby + 0x68);

        spawnerVars += *(unsigned char *)(vars + 0x1C);
        spawnerVars[40] = 0;
    }
    MarkMobySpawned(moby);
}


extern int D_L06_001B3760[];

/* zeroes the six words a finished moby left behind */
void func_L06_003F4908(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        int i;

        for (i = 5; i >= 0; i--)
            D_L06_001B3760[i] = 0;
        MarkMobySpawned(moby);
    }
}


/* func_L06_003FDA08 is matched in L06_0033BDC0-g8.c (it takes the $gp addresses of small-data objects). */

/* func_L06_003FDEB8 is in L06_003FE178-g8.c. */

/* func_L06_003FE178 is in L06_003FE178-g8.c. */

/* func_L06_00400498 is in L06_00400498-g8.c. */

/* func_L06_004012B0 is in L06_004012B0.c. */

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
        if (IsCurrentSelectedId(moby)) {
            if (state->level == 0) {
                SetMobyState(moby, 3, -1);
                if (!IsVoicePlayingForOwner(moby, state->sound))
                    state->sound = PlayMobySound(0, 4, moby);
            } else {
                SetMobyState(moby, 2, -1);
                if (!IsVoicePlayingForOwner(moby, state->sound))
                    state->sound = PlayMobySound(1, 4, moby);
            }
        }
        if (gHeroState.position[2] < 55.0f && state->level == 0) {
            if (!IsVoicePlayingForOwner(moby, state->sound))
                state->sound = PlayMobySound(0, 4, moby);
            SetMobyState(moby, 3, -1);
        } else if (gHeroState.position[2] > 57.0f && state->level == 1 &&
                   IsPointInCuboid(gHeroState.position, state->zone)) {
            if (!IsVoicePlayingForOwner(moby, state->sound))
                state->sound = PlayMobySound(1, 4, moby);
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (fast_vec_dist(moby->position, state->home) > 0.04f) {
            movement[0] = FastSinOrCosA(moby->rotation[2] + 1.57079649f) * 0.05f;
            movement[1] = FastSinOrCosB(moby->rotation[2] + 1.57079649f) * 0.05f;
            movement[2] = 0.0f;
            FastVecAdd(moby->position, moby->position, movement);
            if (state->step < 104)
                moby->position[2] += 0.07f;
            state->step++;
        } else if (!IsCurrentSelectedId(moby)) {
            state->level = 0;
            handle = state->sound;
            if (handle != -1) {
                sound = (SoundSlot *)(gSoundState + handle * 0x70);
                if (sound->owner == moby && sound->active)
                    StopSoundVoice(handle);
            }
            state->sound = -1;
            SetMobyState(moby, 1, -1);
            qcopy(moby->position, state->home);
            state->step = 0;
        } else {
            goto stop;
        }
        break;
    case 3:
        if (moby->position[2] >= 50.75f) {
            if (moby->position[2] < 53.0f &&
                IsPointInCuboid(gHeroState.position, state->zone) &&
                gHeroState.position[2] < moby->position[2])
                break;
            movement[0] = FastSinOrCosA(moby->rotation[2] - 1.57079649f) * 0.05f;
            movement[1] = FastSinOrCosB(moby->rotation[2] - 1.57079649f) * 0.05f;
            movement[2] = 0.0f;
            FastVecAdd(moby->position, moby->position, movement);
            if (state->step >= 61)
                moby->position[2] -= 0.07f;
            state->step++;
        } else if (!IsCurrentSelectedId(moby) && moby->position[2] < 50.75f) {
            state->level = 1;
            handle = state->sound;
            if (handle != -1) {
                sound = (SoundSlot *)(gSoundState + handle * 0x70);
                if (sound->owner == moby && sound->active)
                    StopSoundVoice(handle);
            }
            state->sound = -1;
            SetMobyState(moby, 1, -1);
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
        sound = (SoundSlot *)(gSoundState + handle * 0x70);
        if (sound->owner == moby && sound->active)
            StopSoundVoice(handle);
    }
    state->sound = -1;
done:
    FastVecSub(movement, moby->position, oldPosition);
    CombineTransformsAndStore(state->tracker, movement, oldRotation, moby->rotation);
}

/* func_L06_00402230 is matched in L06_00402230.c (built with -g). */

/* func_L06_00403F60 is matched in L06_0033BDC0-g8.c (it reaches a global through $gp). */


/* func_L06_00419CA8 is defined in L06_00419CA8-g8.c. */

/* clears one word of a 0xA58 moby's state block when it is neither dying nor gone */
void func_L06_0041CAB0(char *moby, char *vars)
{
    char *spawnerMoby = *(char **)(vars + 0x10);

    if (spawnerMoby != 0 && *(short *)(spawnerMoby + 0xAA) == 0xA58 /* moby class 2648 */
        && *(unsigned char *)(spawnerMoby + 0x20) != 0xFE && *(unsigned char *)(spawnerMoby + 0x20) != 0xFD) {
        int *spawnerVars = *(int **)(spawnerMoby + 0x68);

        spawnerVars += *(unsigned char *)(vars + 0x1C);
        spawnerVars[40] = 0;
    }
    MarkMobySpawned(moby);
}

