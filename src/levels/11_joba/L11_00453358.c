#include "common.h"

/* The actor object: position, stage and flags at fixed offsets, its state block behind `state`. */
typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 stage;
    u8 pad21[0x10];
    u8 active;
    u8 pad32[0x68 - 0x32];
    void *state;
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0xAA - 0x70];
    s16 id;
} JobaObject;

/* What func_002A9640 finds: the object that was hit, and a field cleared on it. */
typedef struct {
    u8 pad00[0x20];
    JobaObject *object;
    u8 pad24[8];
    s32 f2C;
} HitRecord;

/* State block of the main actor (offsets as the retail code reads them). */
typedef struct {
    u8 pad00[0x28];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 pad34[0x48 - 0x34];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    char contact[0x10];
    u8 f60;
    u8 pad61[0x80 - 0x61];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xE0 - 0x9C];
    s32 fE0;
    float fE4;
    u8 padE8[0x100 - 0xE8];
    float f100;
    float f104;
    float f108;
    float f10C;
    float f110;
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x256 - 0x138];
    s16 f256;
} JobaActorState;

/* State block of the point-ring effect: up to eight 16-byte points, then its tuning values. */
typedef struct {
    float points[8][4];
    s32 count;
    float minRadius;
    float maxRadius;
    float maxElevation;
    float minElevation;
    float f94;
    float f98;
    float f9C;
    float fA0;
    float fA4;
} JobaRingState;

/* The resident player block: its position and the player object. */
typedef struct {
    u8 pad00[0x80];
    float position[4];
    u8 pad90[0x2290 - 0x90];
    JobaObject *player;
} PlayerBlock;

extern int func_00277F48(int, int, void *, int, float);
extern void func_002A8F70(void *, void *, int, float, float *, float *);
extern PlayerBlock D_00189E20;
extern JobaObject *D_L11_001C4D80[];
extern int func_00283CF0(float);
extern HitRecord *func_002A9640(void *, int, int);
extern int func_002B0ED8(void *, void *, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern char D_L11_001BA8C0[];
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283BE0(float, float);
extern float func_002A78D8(float, float);
extern void func_L00_002E6EF8(void *, char *);

typedef int TI128 __attribute__((mode(TI)));


extern void func_00282D30_2(char *dst, char *src, float scale);
extern void func_002A7750(void *a0, int a1, int a2);
extern void func_002AB8C0(void *a0, void *a1);
extern void func_002A0488(void *a0, int a1, int a2, int a3);
extern void func_002A8C28(void *a0, void *a1, int a2, float f12, float f13, float f14,
                          int a3, int t0, int t1);
extern void func_L11_00459F30();
extern void func_L11_0045A3C8();
extern void func_L11_0045A578();
extern float func_00283248(float a, float b);
extern float func_002A7878(float a, float b);
extern float func_00283180(float x);
extern float func_00283198(float x);

extern void func_002A7470(void *a0, int a1, int a2, int a3);

extern void func_002A05A8(void *a0);

extern void func_L11_00441978(char *p, int id);

extern int func_L11_00441868(char *p, int id);

extern int func_002B3BA8(void *a0, int a1, int a2, int a3, float f12, float f13);

extern void func_002B60B0(void *a0, float f12, float f13, float f14, float f15);

extern float func_002A7820(int a0, int a1);

extern float func_002A7940(void);

extern void func_00281EB8(void *a0, void *a1, void *a2, float f12, float f13,
                          float f14, int a3);

extern void func_002B3380(void *a0, void *a1, void *a2, int a3);

extern void func_002A0F48(void *a0);

extern void func_L00_002E6CF0(void *a0, void *a1);

extern void func_L11_0045B6C8(char *p);

extern int D_L11_001CAE40;

extern int D_L11_001B46D4;

extern int D_L11_001B30C8;

extern void func_L11_00458DF0(char *a0, void *a1, void *a2, int a3, int t0, float f12,
                              float f13);

/* The vector the aim helpers read, at 0x001BA780 in joba. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L11AimVector;

extern L11AimVector D_L11_001BA780;

extern void func_L11_0045FFB0(char *pkt);

extern long long func_0027C878(char *p);

extern float func_00282E80(void *p, float *v);

extern void func_00283410(float *matrix, float *quat);

extern void func_00282CF0(float *out, float *a, float *b);

extern void func_00282F20(float *dst, float *src, float scale);

extern void func_00280B90(char *pkt, float *matrix, int mode);
extern void func_002E59F8(int index);

extern void func_002E5DA0(int index, int value, char *object, int kind);

extern void func_0032C700(char *, int, int, int, int, int, int, int, float, float, int,
                         int, int, int);

extern void func_00282C88(void *);

extern void func_L11_003973F8(char *, int, float, float);

extern char D_00188660[];

extern void func_L11_00456540(char *);
extern void func_L11_00456378(char *);
extern void func_L11_00456EA0(void);

INCLUDE_ASM("asm/levels", func_L11_00453358);

/* func_L11_00454508 lives in the sibling small-data unit (L11_00453358-g8.c). */

void func_L11_00454AE0(char *p)
{
    char *q = *(char **)(p + 0x68);
    unsigned short c;

    func_002AB8C0(p, q + 0x50);
    if (*(short *)(q + 0x50) == 0) {
        if (*(short *)(q + 0x1FE) == 0) {
            func_002A0488(p, *(int *)(q + 0x1F0), *(int *)(q + 0x1F4), *(int *)(q + 0x1F8));
            *(short *)(q + 0x1FE) = 1;
        }
    } else {
        *(short *)(q + 0x1FE) = 0;
    }
    c = *(unsigned short *)(p + 0x96);
    if (c <= 0xFFFE)
        *(unsigned short *)(p + 0x96) = c + 1;
}

extern void func_002A7750_4b60();
extern int func_002B3BA8_4b60(void *, u32, float, float, int, int);

/* Same body as func_L02_0040CF68, with this function's own callees. */
void func_L11_00454B60(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);

    if (a0[0x20] < 4) {
        *(u16 *)(s1 + 0x1EC) = 0;
        *(s32 *)(s1 + 0x1C4) = 0;
    } else {
        if (*(s16 *)(s1 + 0x1EC) == 1) {
            *(s16 *)(s1 + 0x1EA) = func_002B3BA8_4b60(a0, *(u32 *)(s1 + 0x1E4), 100.0f, 100.0f, 0, 0);
            *(s32 *)(s1 + 0x1C4) = *(s32 *)(s1 + 0x160);
        } else {
            if (a0[0x31] != 0 && func_L11_00441868(*(void **)(a0 + 0xB8), *(s16 *)(a0 + 0xAA)) != 0) {
                *(u16 *)(s1 + 0x1EC) = 1;
                *(s16 *)(s1 + 0x1EA) = func_002B3BA8_4b60(a0, *(u32 *)(s1 + 0x1E4), 100.0f, 100.0f, 0, 0);
                *(s32 *)(s1 + 0x1C4) = *(s32 *)(s1 + 0x160);
            } else {
                *(u16 *)(s1 + 0x1EC) = 0;
                if (a0[0x20] == 0xB || a0[0x20] == 8) {
                    if (*(s32 *)(s1 + 0x1C0) != -1)
                        func_002A7750_4b60(a0, 7, 3);
                    else
                        func_002A7750_4b60(a0, 5, 2);
                }
            }
        }
    }
}


/* Aims the object's stage, re-arms its effect and stores the new heading. */
void func_L11_00454C78(char *p, int a1, int a2)
{
    char *q = *(char **)(p + 0x68);
    char *definition;
    unsigned short flags;
    int cache;
    float f;

    f = (float)*(short *)(q + 0x24);
    *(short *)(q + 0x1FC) = a2;
    *(short *)(q + 0x1EC) = 0;
    *(unsigned char *)(q + 0x2E) = 1;
    *(float *)(q + 0x20) = f;
    if (*(unsigned char *)(p + 0x43) != 0)
        func_002A7470(p, 0, 0, 10);
    flags = *(unsigned short *)(p + 0x34);
    *(unsigned char *)(p + 0x7F) = 0;
    *(unsigned short *)(p + 0x34) = (flags | 0x1000) & 0xFFB9;
    definition = *(char **)(p + 0x24);
    cache = *(int *)(definition + 0x10);
    *(int *)(p + 0x98) = cache;
    if (*(short *)(q + 0x1FC) != 0) {
        func_002A7750(p, 7, 3);
        *(unsigned short *)(p + 0x34) |= 0x100;
        func_L11_003973F8(p, 0, 2.0f, 2.0f);
    } else {
        func_002A7750(p, 3, 1);
        *(unsigned char *)(p + 0x31) = 1;
        *(unsigned short *)(p + 0x34) &= 0xFEFE;
    }
    func_00282C88(q + 0x1B0);
    f = func_002A7878(20.0f, 30.0f) * 0.017453294f;
    *(short *)(q + 0x1EE) = a1;
    *(float *)(q + 0x1CC) = f;
    if (*(short *)(q + 0x50) != 0) {
        *(short *)(q + 0x50) = 0;
        func_002A0488(p, *(int *)(q + 0x1F0), *(int *)(q + 0x1F4), *(int *)(q + 0x1F8));
        *(short *)(q + 0x52) = 1;
    }
}

/* Releases the object's slot in the shared table and drops it to the idle flag block. */
void func_L11_00454DD8(char *p)
{
    char *q = *(char **)(p + 0x68);
    int i = *(int *)(q + 0x1DC);
    char *entry;

    if (i != -1) {
        entry = D_00188660 + i * 0x70;
        if (*(char **)(entry + 0x88) == p && *(unsigned char *)(entry + 0x74) != 0)
            func_002E59F8(i);
    }
    *(int *)(q + 0x1DC) = -1;
    if (*(short *)(q + 0x1EC) == 1) {
        *(short *)(q + 0x1EC) = 0;
        func_L11_00441978(*(char **)(p + 0xB8), *(short *)(p + 0xAA));
    }
    if (*(unsigned char *)(p + 0x31) != 0) {
        func_0032C700(p + 0x10, 0, 10, 30, 0, 10, 45, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        func_002E5DA0(0, 0, p, 0xDF7);
    }
    func_002A7470(p, 0, 0, 3);
    func_002A05A8(p);
    func_002A7750(p, 1, 0);
    *(unsigned short *)(p + 0x34) = (*(unsigned short *)(p + 0x34) & 0xEFFF) | 0x47;
    *(int *)(p + 0x98) = 0;
    *(unsigned char *)(p + 0x31) = 0;
    *(short *)(q + 0x1EC) = 0;
    *(int *)(q + 0x1C4) = 0;
}

/* func_L11_00454F18 lives in L11_00454F18-g8.c. */

/* Sets up the actor's tuning on its first stage, handles contacts while active, and runs the
   attack-state update. */
void func_L11_00455DF8(JobaObject *obj)
{
    JobaActorState *state = obj->state;
    HitRecord *hit;
    JobaObject *other;

    if (obj->stage == 0) {
        state->f48 = func_00283CF0(15.0f);
        state->f4A = func_00283CF0(12.0f);
        state->f80 = 0.5f;
        state->f84 = 0.5f;
        state->f108 = 0.5f;
        state->f256 = 0;
        state->f60 = 13;
        state->f98 = 4;
        state->f8C = 0.4f;
        state->f100 = 1.0f;
        state->f104 = 0.25f;
        state->f10C = 0.5f;
        state->f110 = 1.57079649f;
        state->f130 = 0.52359885f;
        state->f134 = 0.01f;
        state->f12C = 0.00555555569f;
        state->f28 = 3;
        state->f30 = 0.75f;
        state->f29 = 1;
        func_L11_00456540((char *)obj);
    }

    if (obj->active) {
        if (obj->stage >= 3) {
            hit = func_002A9640(obj, 0x10000, 1);
            if (hit && (other = hit->object) && !obj->active) {
                if (other->id == 0xDF9 || other->id == 0xB89)
                    hit->f2C = 0;
            }
            if (func_002B0ED8(obj, state->contact, 0) == 5) {
                state->fE0 = 0;
                state->fE4 = 0.837758183f;
            }
        }
        if (obj->active && func_00282E48(obj->position, D_L11_001BA8C0) < 24.0f) {
            func_002A93B0(obj);
            obj->f6F = 22;
        }
    }

    if (obj->stage >= 2 && state->f2E == 2)
        func_L11_00456540((char *)obj);
    func_L11_00456378((char *)obj);
}

void func_L11_00456010(char *p)
{
    unsigned short c = *(unsigned short *)(p + 0x96);

    if (c < 0xFFFF)
        *(unsigned short *)(p + 0x96) = c + 1;
    func_002A8C28(p, p + 0x10, 0x4000000, 1.6f, 1.0f, 1.0f, 0, 1, 0);
}

extern int func_002B3BA8_6378(char *, int, float, float, int, int);

/* Same body as func_L02_003F16F0, with this function's own callees. */
void func_L11_00456378(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) < 4) {
        *(int *)(state + 0x240) = 0;
        goto done;
    }

    if (*(short *)(state + 0x256) == 1) {
        *(short *)(state + 0x254) =
            func_002B3BA8_6378(arg0, *(int *)(state + 0x24C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x240) = *(int *)(state + 0x220);
    } else {
        if (func_L11_00441868(*(int *)(arg0 + 0xB8), *(short *)(arg0 + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x256) = 1;
        *(short *)(state + 0x254) =
            func_002B3BA8_6378(arg0, *(int *)(state + 0x24C), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x240) = *(int *)(state + 0x220);
    }
    return;

done:
    *(short *)(state + 0x256) = 0;
}


/* Retires the state's counter and drops the object to its idle flag block. */
void func_L11_00456540(char *p)
{
    char *q = *(char **)(p + 0x68);

    if (*(short *)(q + 0x256) == 1) {
        func_L11_00441978(*(char **)(p + 0xB8), 0xDF9);
    }
    *(short *)(q + 0x256) = 0;
    *(int *)(q + 0x240) = 0;
    func_002A7470(p, 0, 0, 3);
    func_002A05A8(p);
    func_002A7750(p, 1, 0);
    *(int *)(p + 0x98) = 0;
    *(unsigned short *)(p + 0x34) = (*(unsigned short *)(p + 0x34) & 0xEFFF) | 0x47;
    *(char *)(p + 0x31) = 0;
}

/* Same body as func_L02_003F1A88, with this function's own callees. */
void func_L11_004565D8(char *arg0, char *arg1) {
    char *state;
    float angle;
    float radius;

    angle = func_00283248(*(float *)(arg0 + 0x10) - *(float *)arg1,
                          *(float *)(arg0 + 0x14) - *(float *)(arg1 + 4));
    angle += func_002A7878(-0.78539824f, 0.78539824f);
    radius = func_002A7878(-2.0f, 2.0f) + 8.0f;
    state = *(char **)(arg0 + 0x68);
    qcopy(state + 0x230, arg1);
    *(float *)(state + 0x230) += radius * func_00283180(angle);
    *(float *)(state + 0x234) += radius * func_00283198(angle);
}

/* func_L11_004566C0 lives in L11_00453358-aim-g8.c. */

/* Defined in L11_00453358-retreat-g8.c. */

/* Damages and knocks back every object within radius of the source, with separate damage,
   scale and lift for the player and for everything else. */
void func_L11_00456A48(JobaObject *source, int kind, float radius, float playerDamage,
                       float otherDamage, float playerScale, float otherScale, float playerZ,
                       float otherZ)
{
    float pos[4];           /* receives a copy of the target position that is not read again */
    float impulseStorage[4];
    float *impulse;
    int count = func_00277F48(kind, 0, source, 0, radius);
    JobaObject **entry;
    PlayerBlock *resident;
    int remaining;
    JobaObject *target;
    float *point;
    float scale, z, damage;

    if (count != 0) {
        if (count > 0) {
            impulse = impulseStorage;
            resident = &D_00189E20;
            entry = D_L11_001C4D80;
            remaining = count;
            do {
                target = *entry;
                if (target == resident->player) {
                    if (playerDamage <= 0.0f)
                        goto next;
                    qcopy(pos, resident->position);
                    scale = playerScale;
                    z = playerZ;
                    damage = playerDamage;
                    point = target->position;
                } else {
                    if (target->id == 0xDF9)
                        goto next;
                    qcopy_nc(pos, target->position);
                    point = target->position;
                    scale = otherScale;
                    z = otherZ;
                    damage = otherDamage;
                }
                func_00282CF0(impulse, point, source->position);
                impulseStorage[2] = 0.0f;
                func_00282F20(impulse, impulse, scale);
                impulseStorage[2] = z;
                impulseStorage[3] = 5627.925f;
                func_002A8F70(target, source, 0x10001, damage, point, impulse);
            next:
                remaining--;
                entry++;
            } while (remaining != 0);
        }
    }
}

/* Keeps the ring's points inside the configured radial and angular limits. */
void func_L11_00456C20(JobaObject *obj)
{
    JobaRingState *state = obj->state;
    float *point;
    int i, j;
    float scratch[4];
    float radius, azimuth, elevation, step;

    if (obj->stage == 0) {
        if (state->count > 8)
            state->count = 8;
        obj->stage = 1;
        for (i = 0; i < state->count; i++) {
            float newRadius, newAzimuth;

            newRadius = func_002A7878(state->minRadius, state->maxRadius);
            newAzimuth = func_002A7940();
            func_002AF000(state->points[i], newRadius, newAzimuth, func_002A7940());
            func_00282CC0(state->points[i], obj->position, state->points[i]);
        }
    }

    if (obj->stage == 1) {
        func_L00_002E6EF8(func_L11_00456EA0, (char *)obj);
        for (j = 0; j < state->count; j++) {
            point = state->points[j];
            func_00282CF0(scratch, obj->position, point);
            azimuth = func_00283248(point[0] - obj->position[0], point[1] - obj->position[1]);
            elevation = func_00283248(func_00282E80(obj->position, point),
                                      point[2] - obj->position[2]);
            azimuth = func_00283BE0(azimuth, state->f9C * 0.017453294f);
            elevation = func_00283BE0(elevation,
                                      func_002A78D8(state->fA4, state->fA0) * 0.017453294f);
            if (state->maxElevation < elevation)
                elevation = state->maxElevation;
            if (elevation < state->minElevation)
                elevation = state->minElevation;

            radius = func_00282E48(obj->position, point);
            step = func_002A78D8(state->f98 * 0.0166666675f, state->f94 * 0.0166666675f);
            radius += step;
            if (state->maxRadius < radius)
                radius = state->maxRadius;
            if (radius < state->minRadius)
                radius = state->minRadius;

            func_002AF000(point, radius, azimuth, elevation);
            func_00282CC0(point, obj->position, point);
        }
    }
}

/* func_L11_00456EA0 lives in L11_00456EA0-g8.c. */

extern void func_L04_0040A090(int, void *, void *, void *, void *, void *);
extern char D_L11_001B1E50[] __attribute__((sda));
extern char D_L11_001B1E70[] __attribute__((sda));
extern char D_L11_001B1E80[] __attribute__((sda));
extern char D_L11_001B1EA0[] __attribute__((sda));
extern char D_L11_001B1EB0[] __attribute__((sda));
extern char D_L11_001B1EE0[] __attribute__((sda));
extern char D_L11_001B1F20[] __attribute__((sda));
extern char D_L11_001B1F30[] __attribute__((sda));
extern char D_L11_001B1F50[] __attribute__((sda));
extern char D_L11_001B1F70[] __attribute__((sda));
extern char D_L11_001B43F0[] __attribute__((sda));
extern char D_L11_001B4430[] __attribute__((sda));
extern char D_L11_001B4450[] __attribute__((sda));
extern char D_L11_001B4490[] __attribute__((sda));
extern char D_L11_001B44B0[] __attribute__((sda));
extern char D_L11_001B44D0[] __attribute__((sda));
extern char D_L11_001B4510[] __attribute__((sda));
extern char D_L11_001B4550[] __attribute__((sda));
extern char D_L11_001B4570[] __attribute__((sda));
extern char D_L11_001B4580[] __attribute__((sda));
extern char D_L11_001B4588[] __attribute__((sda));
extern char D_L11_001B4598[] __attribute__((sda));
extern char D_L11_001B45A0[] __attribute__((sda));
extern char D_L11_001B45B8[] __attribute__((sda));
extern char D_L11_001B45D8[] __attribute__((sda));
extern char D_L11_001B45E0[] __attribute__((sda));
extern char D_L11_001B45F0[] __attribute__((sda));
extern char D_L11_001B4600[] __attribute__((sda));
extern char D_L11_001B4608[] __attribute__((sda));
extern char D_L11_001B4618[] __attribute__((sda));
extern char D_L11_001B4620[] __attribute__((sda));
extern char D_L11_001B4630[] __attribute__((sda));
extern char D_L11_001B4638[] __attribute__((sda));
extern char D_L11_001B4650[] __attribute__((sda));
extern char D_L11_001B4670[] __attribute__((sda));
extern char D_L11_001B4678[] __attribute__((sda));
extern char D_L11_001B4688[] __attribute__((sda));
extern char D_L11_001B4698[] __attribute__((sda));
extern char D_L11_001B46A0[] __attribute__((sda));
extern char D_L11_001B46A4[] __attribute__((sda));
extern char D_L11_001B46A8[] __attribute__((sda));
extern char D_L11_001B46AC[] __attribute__((sda));
extern char D_L11_001B46B0[] __attribute__((sda));
extern char D_L11_001B46B4[] __attribute__((sda));
extern char D_L11_001B46B8[] __attribute__((sda));
extern char D_L11_001B46BC[] __attribute__((sda));
extern char D_L11_001B46C0[] __attribute__((sda));
extern char D_L11_001B46C4[] __attribute__((sda));
extern char D_L11_002626B0[];
extern char D_L11_00262710[];

void func_L11_00457600(void) {
    func_L04_0040A090(4, D_L11_001B1E50, D_L11_001B43F0, D_L11_001B4570, D_L11_001B4608, D_L11_001B46A0);
    func_L04_0040A090(2, D_L11_001B1E70, D_L11_001B4430, D_L11_001B4580, D_L11_001B4618, D_L11_001B46A4);
    func_L04_0040A090(4, D_L11_001B1E80, D_L11_001B4450, D_L11_001B4588, D_L11_001B4620, D_L11_001B46A8);
    {
        char *data = D_L11_001B4490;
        func_L04_0040A090(2, D_L11_001B1EA0, data, D_L11_001B4598, D_L11_001B4630, D_L11_001B46AC);
    }
    func_L04_0040A090(6, D_L11_001B1EB0, D_L11_002626B0, D_L11_001B45A0, D_L11_001B4638, D_L11_001B46B0);
    func_L04_0040A090(8, D_L11_001B1EE0, D_L11_00262710, D_L11_001B45B8, D_L11_001B4650, D_L11_001B46B4);
    func_L04_0040A090(2, D_L11_001B1F20, D_L11_001B44B0, D_L11_001B45D8, D_L11_001B4670, D_L11_001B46B8);
    func_L04_0040A090(4, D_L11_001B1F30, D_L11_001B44D0, D_L11_001B45E0, D_L11_001B4678, D_L11_001B46BC);
    func_L04_0040A090(4, D_L11_001B1F50, D_L11_001B4510, D_L11_001B45F0, D_L11_001B4688, D_L11_001B46C0);
    func_L04_0040A090(2, D_L11_001B1F70, D_L11_001B4550, D_L11_001B4600, D_L11_001B4698, D_L11_001B46C4);
}


/* func_L11_004577F8 is defined in L11_00453358-curve.c. */

INCLUDE_ASM("asm/levels", func_L11_004580E8);

/* func_L11_00458A98 is defined in L11_00453358-g8.c. */

/* func_L11_00458C38 lives in L11_00458C38-g8.c. */

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L11_00458D88(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

void func_L11_00458F58(char *p)
{
    *(int *)(p + 0x98) = 0;
    *(unsigned short *)(p + 0x34) = (*(unsigned short *)(p + 0x34) | 0x41) & 0xEFFF;
    func_002A7750(p, 1, -1);
}

/* func_L11_00458F90 is defined in L11_00458F90-qcopy-barrier-g8.c. */


/* func_L11_00459640 and func_L11_00459D48 live in the sibling small-data unit (L11_00453358-g8.c). */

void func_L11_00459E48(char *p)
{
    int i;

    func_L11_00459F30(p);
    func_L11_0045A3C8(p);
    for (i = 4; i >= 0; i--)
        func_L11_0045A578(p);
}

/* shared native body of family a04928c6 */
void func_L11_00459EA0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Defined in L11_00459F30-g8.c. */

/* func_L11_0045A3C8 is defined in L11_0045A3C8-flags-g8.c. */

/* func_L11_0045A578 lives in the sibling small-data unit (L11_00453358-g8.c). */


/* Defined in L11_00453358-pulse.c. */

/* func_L11_0045B6C8 is defined in L11_0045B6C8-g64.c. */

/* func_L11_0045FA68 is in L11_0045FA68-g8.c. */

/* func_L11_0045FDB0 is defined in L11_00453358-spawn-g8.c. */

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L11_00460038(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, aims a quaternion at the level's vector from pos through three
   float helpers, derives an offset basis by a fourth, writes the last matrix row from pos
   plus that offset, then dispatches the packet. */
void func_L11_004600A0(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L11_0045FFB0(pkt);
    r = func_0027C878(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_00283248(D_L11_001BA780.x_140 - *(float *)(pos + 0),
                           D_L11_001BA780.y_144 - *(float *)(pos + 4));
    quat[1] = -func_00283248(func_00282E80(pos, &D_L11_001BA780.x_140),
                             D_L11_001BA780.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_00283410(m, quat);
    func_00282CF0(off, &D_L11_001BA780.x_140, pos);
    func_00282F20(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L11_00460038(pkt, fA);
    func_00280B90(pkt, m, 0);
}

INCLUDE_ASM("asm/levels", func_L11_00461308);
