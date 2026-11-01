#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *a0, int a1, int a2);
extern void func_002A0488(void *a0, int a1, int a2, int a3);
extern float func_002A7878(float a, float b);
extern void func_002A7470(void *a0, int a1, int a2, int a3);
extern void func_00282C88(void *);
extern void func_L11_003973F8(char *, int, float, float);

/* Aims the object's stage, re-arms its effect and stores the new heading. */
void func_PAL_L11_0045A848(char *p, int a1, int a2)
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
        func_002A7470(p, 0, 0, 8);
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

extern void func_002A05A8(void *a0);
extern void func_L11_00441978(char *p, int id);
extern void func_002E59F8(int index);
extern void func_002E5DA0(int index, int value, char *object, int kind);
extern void func_0032C700(char *, int, int, int, int, int, int, int, float, float, int,
                         int, int, int);
extern char D_00188660[];

/* Releases the object's slot in the shared table and drops it to the idle flag block. */
void func_PAL_L11_0045A9A8(char *p)
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
typedef struct {
    u8 pad00[0x20];
    JobaObject *object;
    u8 pad24[8];
    s32 f2C;
} HitRecord;
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
extern JobaObject *D_L11_001C4D80[];
extern int func_00283CF0(float);
extern HitRecord *func_002A9640(void *, int, int);
extern int func_PAL_002B1A50(void *, void *, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern char D_L11_001BA8C0[];
extern void func_L11_00456540(char *);
extern void func_L11_00456378(char *);

/* func_L11_00454F18 lives in L11_00454F18-g8.c. */

/* Sets up the actor's tuning on its first stage, handles contacts while active, and runs the
   attack-state update. */
void func_PAL_L11_0045B9E8(JobaObject *obj)
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
        state->f12C = 0.008f;
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
            if (func_PAL_002B1A50(obj, state->contact, 0) == 5) {
                state->fE0 = 0;
                state->fE4 = 1.0053098f;
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

