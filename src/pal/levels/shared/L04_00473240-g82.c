#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} CameraVector;
typedef struct {
    char pad[0x30];
    CameraVector position;
    char pad40[0x30];
    char *motion;
    char pad74[0x10];
    short index;
} CameraObject;
typedef struct {
    CameraVector basis[8];
    CameraVector position;
} CameraPlayer;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    CameraVector point, position;
} CameraCollision;
typedef struct {
    char pad[0x1C];
    char *definition;
} CameraEntry;
typedef struct {
    char bytes[0x100];
} CameraRecord;
extern CameraEntry *D_L04_001B1E84;
extern CameraRecord *D_L04_001B24DC;
extern float D_L04_001B1C8C __attribute__((sda));
extern float D_L04_001B1C90 __attribute__((sda));
extern float D_L04_001B1C94 __attribute__((sda));
extern float D_L04_001B1CAC __attribute__((sda));
extern int D_L04_001B1CC4 __attribute__((sda));
extern int D_L04_001B1CCC __attribute__((sda));
extern float D_L04_001B1CD0 __attribute__((sda));
extern CameraPlayer D_00189E20;
extern CameraCollision D_L04_001BFAC0;
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_002AA2E8(float *, float, float);
extern float func_00282E20(void *);
extern void func_00282948(int *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern int func_00277258(void *, int, int, float);

/* Smooth a player-relative camera offset, then resolve movement collisions.
 * Debug line labels preserve the horizontal scaling division's padding. */
void func_PAL_L04_004734D8(CameraObject *obj) {
    CameraVector old, offset, negative, projection, axis, center, velocity, rotated, delta;
    char *entry, *state, *hit;
    CameraVector *motion;
    float scale;
    float smoothing;
    old.q = obj->position.q;
    entry = (char *)&D_L04_001B24DC[*(int *)(D_L04_001B1E84[obj->index].definition + 0x60)];
    state = *(char **)(entry + 0x68);
    smoothing = D_L04_001B1CAC;
    motion = (CameraVector *)(obj->motion + 0x70);
    offset.f[0] = D_L04_001B1C8C;
    offset.f[1] = D_L04_001B1C90;
    offset.f[2] = D_L04_001B1C94;
    offset.f[3] = 1.0f;
    if (*(unsigned char *)(entry + 0x20) == 3) {
        offset.f[0] += offset.f[0];
        if (D_L04_001B1CC4) offset.f[0] = -offset.f[0];
        D_L04_001B1CCC = -1;
        offset.f[2] *= 1.5f;
    } else {
        if (D_L04_001B1CCC == -1 && (*(int *)(state + 0x278) > 0 || *(int *)(state + 0x338) > 0)) D_L04_001B1CCC = 75;
        if (*(int *)(state + 0x278) <= 0 && *(int *)(state + 0x338) <= 0) D_L04_001B1CCC = -1;
    }
    func_00282D30(&negative, &D_00189E20, -1.0f);
    qcopy(&center, &D_00189E20.position);
    velocity.q = 0;
    velocity.f[2] = 1.0f;
    velocity.f[3] = 1.0f;
    qcopy(&axis, &velocity);
    func_00282DD8(&projection, &negative, &velocity);
    func_00282F20(&projection, &projection, 1.0f);
    func_00282DD8(&negative, &axis, &projection);
    func_002830C0(&rotated, &offset, &negative);
    func_00282CF0(&delta, &rotated, &D_00189E20.position);
    func_00282D08(motion, motion, &delta, smoothing);
    velocity.q = motion->q;
    if (D_L04_001B1CCC > 0) {
        if (D_L04_001B1CCC >= 63) func_002AA2E8(&D_L04_001B1CD0, 1.0f, 0.050000004f);
        else func_002AA2E8(&D_L04_001B1CD0, 0.0f, 0.015000001f);
        if (D_L04_001B1CD0 > 0) {
            scale = func_00282E20(&velocity);
            scale = (scale + D_L04_001B1CD0) / scale;
            velocity.f[0] *= scale;
            velocity.f[1] *= scale;
        }
        func_00282948(&D_L04_001B1CCC);
    }
    func_00282CC0(&obj->position, &D_00189E20.position, &velocity);
    if (func_002761F8(&old, &obj->position, 4, 0, 0)) {
        hit = D_L04_001BFAC0.hit;
        if (!hit || (*(short *)(hit + 0xAA) != 0xB2D && *(short *)(hit + 0xAA) != 0xBBC && *(short *)(hit + 0xAA) != 0xA1F)) {
            func_00282CF0(&rotated, &D_L04_001BFAC0.point, &old);
            func_00282D30(&velocity, &rotated, 0.95f);
            func_00282CC0(&obj->position, &old, &velocity);
        }
    }
    if (func_002761F8(&D_00189E20.position, &obj->position, 2, 0, 0)) {
        hit = D_L04_001BFAC0.hit;
        if (!hit || (*(short *)(hit + 0xAA) != 0xB2D && *(short *)(hit + 0xAA) != 0xBBC && *(short *)(hit + 0xAA) != 0xA1F)) {
            func_00282CF0(&rotated, &D_L04_001BFAC0.point, &D_00189E20.position);
            func_00282D30(&velocity, &rotated, 0.95f);
            func_00282CC0(&obj->position, &D_00189E20.position, &velocity);
        }
    }
    if (func_00277258(&obj->position, 4, 0, 0.15f)) {
        hit = D_L04_001BFAC0.hit;
        if (!hit || (*(short *)(hit + 0xAA) != 0xB2D && *(short *)(hit + 0xAA) != 0xBBC)) obj->position.q = D_L04_001BFAC0.position.q;
    }
}
