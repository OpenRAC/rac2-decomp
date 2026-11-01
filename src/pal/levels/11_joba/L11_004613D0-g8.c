#include "include_asm.h"

#include "common.h"
extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, char *, float);
extern void func_002A7750(char *, int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282C88(void *);
extern float func_002A7878(float, float);
extern void func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *func_002A9640(char *, int, int);
extern void func_002A8C28(void *, void *, float, int, float, float, int, int, int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_0029F338(char *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L11_0045FEF8(void);
extern float D_L11_001B22C8 __attribute__((sda));
extern int D_L11_001B22C0 __attribute__((sda));
extern char *D_L11_001C0D18 NOT_SDA;
extern int D_0018C0B4 NOT_SDA;

void func_PAL_L11_004657E0(char *p)
{
    float next[4], velocity[4], zero[4];
    char *q = *(char **)(p + 0x68);
    char *hit;
    float a, b;
    switch (*(unsigned char *)(p + 0x20)) {
    case 0:
        *(float *)(p + 0xF0) = func_00283B98(*(float *)(p + 0xF0), *(float *)(q + 0x20) * 0.7f);
        *(float *)(p + 0xF4) = func_00283B98(*(float *)(p + 0xF4), *(float *)(q + 0x20) * 0.5f);
        *(float *)(p + 0xF8) = func_00283B98(*(float *)(p + 0xF8), *(float *)(q + 0x20));
        func_00282CC0(next, p + 0x10, q);
        if (func_00277258(next, 0, p, D_L11_001B22C8) &&
            D_L11_001C0D18 && D_L11_001C0D18 != *(char **)(q + 0x10)) {
            func_002A7750(p, 1, -1);
            return;
        }
        qcopy(p + 0x10, next);
        func_00282D30(velocity, q, -0.5f);
        func_00282C88(zero);
        a = func_002A7878(2.5f, 3.0f) * 210000.0f;
        b = func_002A7878(0.2f, 0.4f) * 210000.0f;
        func_002C65A0(p + 0x10, velocity, 15, D_L11_001B22C0, 3, 80, 0, a, b, 0.0f, 0);
        if (*(float *)(q + 0x24) < *(float *)(p + 0x18) && *(float *)(q + 0x24) > 0.0f)
            func_002A7750(p, 2, -1);
        hit = func_002A9640(p, 0x10000, 0);
        if (hit) {
            *(float *)(q + 0x14) -= *(float *)(hit + 0x2C);
            if (*(float *)(q + 0x14) <= 0.0f) func_002A7750(p, 1, -1);
        }
        if (D_0018C0B4 == 111) func_002A7750(p, 2, -1);
        break;
    case 1:
        func_002A8C28(p, p + 0x10, 3.0f, 0x10001, *(float *)(q + 0x18), 1.0f, 0, 1, 0);
        func_PAL_L00_003FB330(p + 0x10, 1, 2, 2, 5, 10, 2, 1, 3.0f, 0.0f, 0, 1, 0, 0);
        func_0029F338(p);
        return;
    case 2:
        func_PAL_L00_003FB330(p + 0x10, 0, 10, 2, 10, 5, 2, 1, 2.0f, 0.0f, 0, 1, 0, 0);
        func_0029F338(p);
        return;
    }
    func_L00_002E6EF8(func_L11_0045FEF8, p);
}

extern char *func_0029EFD0(int);
extern float func_002A7940(void);
extern void func_PAL_L11_00465FD0(void *, int);
extern void func_002E5DA0(int, int, char *, int);
extern float D_L11_001B22C4 __attribute__((sda));
extern int D_L11_001B22CC __attribute__((sda));
typedef struct {
    float velocity[4];
    char *owner;
    float parameterA;
    float parameterB;
    float heading;
    float turn;
    float parameterD;
} SpawnState;
typedef struct {
    char pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[2];
    u8 kind;
    char pad24[8];
    float scale;
    u8 opacity;
    u8 enabled;
    u16 alpha;
    u16 flags;
    u16 pad36;
    u64 ownerFlags;
    char pad40[0x28];
    SpawnState *data;
} SpawnObject;

/* Creates the object-type 0xE7B effect for an owner: copies the start velocity and position,
   picks a random heading and turn rate, and registers it. Returns the new object or NULL. */
char *func_PAL_L11_00465B28(char *owner, void *velocity, void *position, float paramA, float paramB,
                        float scale, float paramD)
{
    SpawnObject *obj = (SpawnObject *)func_0029EFD0(0xE7B);

    if (obj) {
        SpawnState *state;
        int arg;

        obj->opacity = 255;
        obj->alpha = 255;
        obj->enabled = 1;
        obj->state = 0;
        obj->ownerFlags = *(long long *)(owner + 0x38);
        qcopy(obj->position, position);

        state = obj->data;
        qcopy(state, velocity);
        state->owner = owner;
        state->parameterA = paramA;
        state->parameterB = paramB;
        state->heading = func_002A7940();
        state->turn = func_002A7878(0.062831864f, 0.12566373f);
        state->parameterD = paramD;

        obj->kind = 255;
        obj->flags = 8;
        arg = D_L11_001B22CC;
        obj->scale = D_L11_001B22C4 * scale;
        obj->flags = 0x1008;
        func_PAL_L11_00465FD0(obj->position, arg);
        func_002E5DA0(0, 0, (char *)obj, 0xE7B);
    }
    return (char *)obj;
}
