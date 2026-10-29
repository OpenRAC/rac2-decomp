/* Truthful retained projectile reconstruction, 2026-10-28.
 * Retail 616 bytes; best ordinary C 604 bytes, 0/5 US placements.
 * Three trials: default qcopy, independently bounded qcopy_nc, and narrow
 * -fno-regmove all tie. Retail retains an additional position address across
 * the query call (S0 -> S4); the resulting save/copy schedule is not reproduced.
 * Default transfer helpers restored; no synthetic reads or register constraints.
 * No RAC1 implementation reused: smoke_puff_projectiles.c was inspected only
 * as a query-layout witness; RAC2 fields/bytes and canonical helpers were read.
 * Queries include +0x24 (40 logical bytes, 48 with vector alignment), two
 * aligned 16-byte vectors; frame 128 bytes plus outgoing/save slots matches D0.
 * 0032C700 returns allocated object at +0x300; 002A8C28 returns hit count.
 */
#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef struct {
    Vector direction;
    int owner, flags;
    u8 first, second;
    u16 object_class;
    float radius;
    int enabled;
    float extra;
} CollisionQuery;
typedef struct {
    Vector next;
    CollisionQuery line;
    Vector push;
    CollisionQuery sphere;
} ProjectileFrame;
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A8C00(char *, int, int, float, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277F48(void *, float, int, void *, void *);
extern void func_002A7750(void *, int, int);
extern void func_0029F338(void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L12_004081F8(void *);
extern void *D_L12_001C0258;

/* Requests include the +0x24 field read by the collision consumer. Retail's
 * initializer writes only the observed fields; no extra initialization is added.
 * All copied vectors have complete, aligned 16-byte storage. */
void func_L12_00407DE8(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    ProjectileFrame frame;
    void *position;
    int timer = *(int *)(vars + 0x24) + 1;
    *(int *)(vars + 0x24) = timer;
    if (timer > 240) {
        func_002A8C28(self, self + 0x10, 0x10001, 0, 1, 0, 0.6f, *(float *)(vars + 0x14), 0.0f);
        func_002A7750(self, 1, -1);
    }
    switch (self[0x20]) {
    case 0:
        position = self + 0x10;
        func_00282CC0(frame.next, position, vars);
        func_002A8C00((char *)&frame.line, (int)self, 1, *(float *)(vars + 0x14), vars);
        frame.line.object_class = *(u16 *)(self + 0xAA);
        if (func_002761F8(position, frame.next, 0, self, &frame.line)) {
            if (D_L12_001C0258 != 0) {
                if (D_L12_001C0258 == *(void **)(vars + 0x10))
                    goto move;
                qcopy(frame.push, vars);
                func_00282D30(frame.push, frame.push, 1.5f);
            } else {
                qcopy(frame.push, vars);
                func_00282D30(frame.push, frame.push, 3.0f);
            }
            frame.push[2] = 1.0f;
            frame.push[3] = 5627.9248046875f;
            func_002A8C00((char *)&frame.sphere, (int)self, 0x10001, *(float *)(vars + 0x14), frame.push);
            frame.sphere.second = 1;
            frame.sphere.object_class = *(u16 *)(self + 0xAA);
            frame.sphere.first = 0;
            func_00277F48(position, 0.6f, 0, self, &frame.sphere);
            func_002A7750(self, 1, -1);
            return;
        }
move:
        qcopy(position, frame.next);
        func_00282D30(frame.push, vars, -0.5f);
        break;
    case 1:
        func_0032C700(self + 0x10, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0.75f, 20.0f);
        func_0029F338(self);
        return;
    }
    func_L00_002E6EF8(func_L12_004081F8, self);
}
