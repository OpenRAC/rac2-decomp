#include "common.h"

/* Bodies of L11_004465F8.c whose globals the compiler reaches through $gp (-G8). */

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern s32 func_00282978(void *);
extern float *func_L11_004417E8(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L11_0045FDB0(void *, void *, void *, float, float, float, float);
extern TI128 D_00189EA0;
extern u16 D_L11_001B19A8 __attribute__((sda));
extern s32 D_L11_001B19AC __attribute__((sda));
extern float D_L11_001B19B0 __attribute__((sda));
extern float D_L11_001B19B4 __attribute__((sda));

extern s32 D_L11_005A0000 __attribute__((sda));

extern float func_32CB48(float f12, float f13);
extern s32 func_32CAB0(s32 a0);
extern s32 func_301700(float f12);
extern s32 func_3006B8(char *a0, s32 a1);
extern void func_32ED70(char *a0);
extern float func_3015A8(float f12, float f13);
extern void func_44F978(char *a0, char *a1, s32 a2, s32 a3);
extern void func_44FA58(char *a0, char *a1, s32 a2, s32 a3, float f12);
extern void func_44FBA8(char *a0, char *a1);
extern char *func_32F000(char *a0, s32 a1, s32 a2);
extern s32 func_338F10(char *a0, char *a1, s32 a2);
extern void func_301020(char *a0, char *a1);
extern void func_337410(char *a0, char *a1, s32 a2);
extern s32 func_4461C0(s32 a0, char *a1);
extern void func_32C9E0(char *a0, s32 a1, s32 a2);
extern void func_44C268(char *a0);
extern void func_44C4F0(char *a0);

/* turret entry of the 0x4A0 rig: arms the sub-object, seeds its parameter block and the
   0.4/0.6/0.8 constant set, then runs the per-frame aim and fire path */
extern s32 func_448CE0(char *a0);
extern void func_4493F8(char *a0, s32 a1);
extern void func_449970(char *a0, s32 a1, s32 a2);
extern void func_448DF8(char *a0);
extern void func_449878(char *a0);

/* The id-list walk of the 0x7FFF family (worker 02's matched skeleton): the entry's
   two-byte ids are addresses divided by 256 into the resident object bank, and bit 15
   of the last id ends the walk.  Returns 1 only from the third live 0xD98 object. */
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((sda));

s32 func_L11_00448D28(u8 *a0)
{
    u8 *base;
    u8 *p;
    u16 *q;
    u8 *e;
    s32 n;

    if (a0[0x21] == 0xFF)
        return 0;
    p = D_L11_001FC420[a0[0x21]];
    if (p == 0)
        return 0;
    q = (u16 *)p;
    base = D_L11_001B359C;
    n = 0;
    for (;;) {
        e = base + (*q & 0x7FFF) * 256;
        if (e != 0 && e[0x20] != 0xFE && e[0x20] != 0xFD && *(s16 *)(e + 0xAA) == 0xD98
            && e[0x95] == 6 && *(s16 *)(*(char **)(e + 0x68) + 0x366) == 1) {
            n++;
            if (n >= 3)
                return 1;
        }
        if ((s16)*q < 0)
            break;
        q++;
    }
    return 0;
}

extern void func_2FD7E8(void *a0, int a1, void *a2, void *a3, int a4, int a5,
                        int a6, int a7, float f12);

extern s32 D_L11_001B1C50 __attribute__((sda));

extern u8 D_L11_001B1C10 __attribute__((sda));

extern s32 D_L11_001B1C54;

/* hands the object's 0x270 and 0x370 tables, its 0x4B0/0x4B4/0x4B8 words and the level's
   own 0x1B1C50/0x1B1C54 state to the scene manager */
void func_L11_0044C220(char *a0)
{
    char *v0 = *(char **)(a0 + 0x68);

    func_2FD7E8(&D_L11_001B1C10, 4, v0 + 0x270, v0 + 0x370,
                *(s32 *)(v0 + 0x4B4), *(s32 *)(v0 + 0x4B0),
                D_L11_001B1C50, D_L11_001B1C54,
                *(f32 *)(v0 + 0x4B8));
}

typedef struct JobObject JobObject;

/* The record behind an object's +0x68 pointer for the kind handled by the two functions below. */
typedef struct {
    u8 pad00[0x18];
    float *params;          /* +0x18, points at paramBlock */
    u8 pad1C[4];
    float health;           /* +0x20 */
    u8 pad24[4];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 f34;
    u8 pad35[0x48 - 0x35];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    u8 hitInfo[0x10];       /* +0x50 */
    u8 f60;
    u8 pad61[8];
    u8 f69;
    u8 pad6A[0x80 - 0x6A];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xFC - 0x9C];
    float fFC;
    float paramBlock[5];    /* +0x100 */
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x1D4 - 0x138];
    float f1D4;
    u8 pad1D8[0x1E6 - 0x1D8];
    u8 f1E6;
    u8 pad1E7;
    u8 f1E8;
    u8 f1E9;
    u8 pad1EA[0x1FC - 0x1EA];
    u16 spawnTimer;         /* +0x1FC */
    u8 pad1FE[0x2F0 - 0x1FE];
    float basis[12];        /* +0x2F0 */
    float anchor[4];        /* +0x320 */
    u8 pad330[0x354 - 0x330];
    JobObject *turret;      /* +0x354 */
    float turnRate;         /* +0x358 */
    u8 pad35C[0x364 - 0x35C];
    s16 fireTimer;          /* +0x364 */
    u8 pad366[0x36E - 0x366];
    s16 f36E;
} JobState;

struct JobObject {
    u8 pad00[0x10];
    float position[4];      /* +0x10 */
    u8 stage;               /* +0x20 */
    u8 pad21[0x31 - 0x21];
    u8 f31;
    u8 pad32[2];
    u16 flags;              /* +0x34 */
    u8 pad36[0x68 - 0x36];
    JobState *state;        /* +0x68 */
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0x95 - 0x70];
    u8 f95;
    u8 pad96[0xB8 - 0x96];
    s32 fB8;
    u8 padBC[4];
    float rotation[12];     /* +0xC0 */
};

/* Spawns the effect at a random point around the object's anchor when its timer runs out. */
void func_L11_004471A8(JobObject *object)
{
    float position[4], velocity[4], acceleration[4];
    JobState *state = object->state;
    float angle;
    float *base;
    int chance;
    u16 timer;

    if (func_00282978(&state->spawnTimer)) {
        timer = D_L11_001B19A8;
        chance = D_L11_001B19AC;
        state->spawnTimer = timer;
        if (!func_002A77E0(chance)) {
            qcopy(position, &D_00189EA0);
            func_00282CF0(velocity, position, func_L11_004417E8(object));
            velocity[2] = 0;
            func_00282F20(velocity, velocity, D_L11_001B19B4);
            func_00282CC0(position, velocity, func_L11_004417E8(object));
            position[2] += 5.0f;
        } else {
            angle = func_002A7878(-3.1415927410125732f, 3.1415927410125732f);
            base = func_L11_004417E8(object);
            position[0] = base[0] + D_L11_001B19B4 * func_00283180(angle);
            base = func_L11_004417E8(object);
            position[1] = base[1] + D_L11_001B19B4 * func_00283198(angle);
            position[2] = func_L11_004417E8(object)[2] + 5.0f;
        }
        *(TI128 *)acceleration = 0;
        acceleration[2] = D_L11_001B19B0 * (1.0f / 60.0f);
        *(TI128 *)velocity = *(TI128 *)acceleration;
        func_L11_0045FDB0(object, velocity, position, state->health, (float)state->f34, 1.0f,
                          550.0f);
    }
}

extern s32 func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void *func_002A9640(void *, s32, s32);
extern s32 func_002B0ED8(void *, void *, s32);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(void *, void *, s32);
extern s32 func_L11_004461C0(s32, void *);
extern void func_002A7750(void *, s32, s32);
extern char D_L11_001BA8C0[];
extern s32 D_001A8FF4;
extern void func_L11_00449878(void *);
extern void func_L11_00448DF8(void *);
/* Two arguments: retail sets $a1 to the object func_002A9640 returned just before the call;
   the callee reads only $a0. */
extern s32 func_L11_00448CE0(void *, void *);
extern void func_L11_004493F8(void *, s32);
extern void func_L11_00449970(void *, s32, s32);

/* Per-frame update of a turret-like enemy: on its first frame it seeds its parameter block
   (including a random-sign turn rate of 10 to 30 degrees), then handles hits, firing, damage
   and the death sequence. The turn rate's sign is chosen in the store's own expression so the
   stored value does not cross the coin-flip call. */
void func_L11_004484A8(JobObject *object)
{
    JobState *state = object->state;
    void *hit;
    float speed;

    if (object->stage == 0) {
        state->params = state->paramBlock;
        state->f48 = func_00283CF0(15.0f);
        state->f4A = func_00283CF0(16.0f);
        speed = func_002A7878(10.0f, 30.0f) * 0.01745329424738884f;
        state->turnRate = func_002A77E0(2) ? -speed : speed;
        state->f80 = 1.3f;
        state->f84 = 1.3f;
        state->f69 = 2;
        state->f1E9 = 3;
        state->f1D4 = 0.5f;
        state->paramBlock[1] = 0.5f;
        state->paramBlock[2] = 0.5f;
        state->f60 = 16;
        state->f98 = 7;
        state->f8C = 0.4f;
        state->f1E6 = 5;
        state->f1E8 = 2;
        state->paramBlock[0] = 1.3f;
        state->paramBlock[3] = 0.5f;
        state->paramBlock[4] = 1.5707964897155762f;
        state->f130 = 0.523598849773407f;
        state->f134 = 0.01f;
        state->f12C = 0.0055555556900799274f;
        state->f28 = 3;
        state->f29 = 1;
        state->f30 = 0.75f;
        state->fireTimer = 0;
        if (!func_002A77E0(2))
            object->flags |= 0x8000;
        state->turret = 0;
        func_L11_00449878(object);
    }
    if (state->f36E == 0 && object->stage != 18 && !D_001A8FF4) {
        object->flags |= 0x400;
        if (object->f31 && func_00282E48(object->position, D_L11_001BA8C0) < 24.0f) {
            func_002A93B0(object);
            object->f6F = 22;
        }
    } else {
        object->flags &= 0xFBFF;
    }
    if (object->stage >= 3) {
        state->fFC = 1.0f;
        hit = func_002A9640(object, 0x10000, 1);
        if (hit) {
            state->fFC = 1.0f;
            if (func_L11_00448CE0(object, hit)) {
                state->f60 = 15;
                func_002B0ED8(object, state->hitInfo, 1);
                state->f60 = 16;
                if (state->turret && state->fireTimer == 0 && object->f31) {
                    func_L11_004493F8(state->turret->position, 2);
                    state->fireTimer = 60;
                }
            } else {
                func_002B0ED8(object, state->hitInfo, 0);
            }
        } else {
            func_002B0ED8(object, state->hitInfo, 0);
        }
        if (state->health <= 0.0f && object->f95 != 7 && object->f95 != 8)
            func_L11_00449970(object, 1, 0);
        if (state->f36E) {
            func_00283698(state->basis, object->rotation);
            func_002AFFD8(object->position, state->anchor, 0);
            if (!func_L11_004461C0(object->fB8, object->position) && object->f95 != 8) {
                state->health = 0;
                func_002A7750(object, 18, 8);
            }
        }
        if (object->stage >= 2 && state->f2E == 2)
            func_L11_00449970(object, 1, 1);
        func_L11_00448DF8(object);
    }
}

extern void func_002B60B0(char *, float, float, float, float);
extern void func_L11_00452DF8(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern s32 func_002B3BA8(void *, s32, s32, s32, float, float);

/* Per-frame update of an L11 object: on its first frame it seeds its state block (a random-sign
   turn rate of 15 to 40 degrees, the 0.5/0.4 constant set) and runs its setup; then it sets the
   proximity flag, rebuilds the frame at state + 0x290 and, from stage 3 on, runs its hit, death
   and tracking checks. */
void func_L11_00452450(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *aim;
    char *hit;
    char *source;
    float matrix[16];
    float turnRate;
    s16 kind;

    if (*(u8 *)(object + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        turnRate = func_002A7878(15.0f, 40.0f) * 0.017453294f;
        if (func_002A77E0(2) != 0)
            turnRate = -turnRate;
        *(f32 *)(state + 0x2C8) = turnRate;
        if (func_002A77E0(2) == 1)
            *(u16 *)(object + 0x34) |= 0x8000;
        *(u8 *)(state + 0x48) = func_00283CF0(15.0f);
        *(u8 *)(state + 0x4A) = func_00283CF0(12.0f);
        *(u8 *)(state + 0x60) = 0xB;
        *(s32 *)(state + 0x98) = 4;
        *(f32 *)(state + 0x100) = 0.8f;
        *(f32 *)(state + 0x104) = *(f32 *)(state + 0x84) = *(f32 *)(state + 0x80) = 0.5f;
        *(f32 *)(state + 0x10C) = *(f32 *)(state + 0x108) = *(f32 *)(state + 0x8C) = 0.4f;
        *(f32 *)(state + 0x110) = 1.5707965f;
        *(f32 *)(state + 0x130) = 0.52359885f;
        *(f32 *)(state + 0x12C) = 0.0055555557f;
        *(f32 *)(state + 0x134) = 2.8f;
        func_002B60B0(object, 0.004444444552063942f, 0.13333334028720856f,
                      0.0011635529808700085f, 0.10471977293491364f);
        *(u8 *)(state + 0x28) = 3;
        func_L11_00452DF8(object);
    }
    if (*(s16 *)(state + 0x2D8) == 0 && *(u8 *)(object + 0x20) != 0xC && D_001A8FF4 == 0) {
        *(u16 *)(object + 0x34) |= 0x400;
        if (*(u8 *)(object + 0x31) != 0 && func_00282E48(object + 0x10, D_L11_001BA8C0) < 24.0f) {
            func_002A93B0(object);
            *(u8 *)(object + 0x6F) = 0x16;
        }
    } else {
        *(u16 *)(object + 0x34) &= 0xFBFF;
    }
    aim = state + 0x290;
    func_0029FCC0(object, 1, state + 0x270);
    func_0029FCC0(object, 2, state + 0x280);
    func_0029FC20(object, 3, matrix);
    func_00282C88(aim);
    *(s32 *)(state + 0x298) = 0;
    *(f32 *)(state + 0x290) = 0.25f;
    func_002830C0(aim, aim, matrix);
    func_00282CC0(aim, aim, matrix + 12);
    if (*(u8 *)(object + 0x20) >= 3) {
        hit = (char *)func_002A9640(object, 0x10000, 1);
        if (hit != 0) {
            source = *(char **)(hit + 0x20);
            if (source != 0 && *(u8 *)(object + 0x31) == 0) {
                kind = *(s16 *)(source + 0xAA);
                if (kind == 0xA03 || kind == 0xB89)
                    *(s32 *)(hit + 0x2C) = 0;
            }
        }
        if (func_002B0ED8(object, state + 0x50, 0) == 5) {
            *(s32 *)(state + 0xE0) = 0;
            *(f32 *)(state + 0xE4) = 0.8377582f;
        }
        if (*(s16 *)(state + 0x2D8) != 0) {
            char *pos;
            func_00283698(state + 0x230, object + 0xC0);
            pos = object + 0x10;
            func_002AFFD8(pos, state + 0x260, 0);
            if (func_L11_004461C0(*(s32 *)(object + 0xB8), pos) == 0) {
                *(s32 *)(state + 0x20) = 0;
                func_002A7750(object, 0xC, 4);
            }
        }
        if (*(u8 *)(object + 0x20) >= 2 && *(u8 *)(state + 0x2E) == 2)
            func_L11_00452DF8(object);
        *(s16 *)(state + 0x2D0) = func_002B3BA8(object, *(s32 *)(state + 0x2CC), 0, 0, 100.0f, 100.0f);
        *(s32 *)(state + 0x2C4) = *(s32 *)(state + 0x220);
    }
}
