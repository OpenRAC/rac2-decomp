#include "include_asm.h"

#include "common.h"
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
typedef struct {
    u8 pad[0x60];
    s32 node;
    s32 destination;
    f32 angularSpeed;
    f32 speed;
    f32 origin[4];
    s32 sound;
    f32 targetHeight;
    f32 targetAngle;
    s32 timer;
} LiftVars;
extern u8 *D_L12_001B2F8C MACRO_ADDR;
typedef struct {
    u8 pad0[0x80];
    f32 position[4];
    u8 pad90[0x33C - 0x90];
    u8 *lift;
    s32 active;
} LiftHero;
extern LiftHero D_00189E20;
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    u8 *owner;
} LiftSound;
extern u8 D_00188660[];
extern u8 *D_0018C0B0 NOT_SDA;
extern s32 D_00138324 NOT_SDA;
extern f32 func_00283B98(f32, f32);
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);
extern void func_002A7750(void *, s32, s32);
extern s32 func_002B0C28(s32, s32, s32);
extern s32 func_002B3868(void *);
extern s32 func_L00_002D40F0(void);
extern s32 func_002ACBC8(void *, s32);
extern void func_L00_002D40A0(void *, s32, f32);
extern void func_L01_002C98B8(void);
extern void func_002E59F8(s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern f32 func_002AA548(void *, void *, f32, f32, f32, f32);
extern f32 func_002AAA00(void *, void *, f32, f32, f32, f32, s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

void func_US2_L12_0041EC70(u8 *self)
{
    f32 oldpos[4] __attribute__((aligned(16)));
    f32 oldrot[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    LiftVars *p = *(LiftVars **)(self + 0x68);
    f32 target, speed, y;

    qcopy(oldpos, self + 0x10);
    qcopy(oldrot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        F(self, 0xF8) = func_00283B98(F(self, 0xF8), 1.5707964897155762f);
        qcopy_nc(p->origin, self + 0x10);
        p->origin[3] = F(self, 0xF8);
        func_002A7750(self, 2, -1);
        break;
    case 2:
        p->targetHeight = p->destination ?
            F((u8 *)(p->node * 128 + (u32)D_L12_001B2F8C), 0x38) : p->origin[2];
        p->targetAngle = p->destination ?
            func_00283B98(F((u8 *)(p->node * 128 + (u32)D_L12_001B2F8C), 0x78),
                          4.7123894691467285f) : p->origin[3];
        y = F((u8 *)(p->node * 128 + (u32)D_L12_001B2F8C), 0x38);
        if (D_00189E20.lift == self && D_00189E20.active) {
            func_002B0C28(8, 0x12EC, 1);
            if (D_00138324 & 16) {
                p->destination = (p->destination + 1) & 1;
                func_002A7750(self, 3, -1);
            }
        } else if (p->destination) {
            if (func_00282C48(D_00189E20.position[2] - p->origin[2]) < 4.0f &&
                func_00282E80(D_00189E20.position, self + 0x10) < 32.0f) {
                p->destination = 0;
                func_002A7750(self, 1, -1);
            }
        } else if (func_00282C48(D_00189E20.position[2] - y) < 4.0f &&
                   func_00282E80(D_00189E20.position, self + 0x10) < 32.0f) {
            p->destination = 1;
            func_002A7750(self, 1, -1);
        }
        break;
    case 3:
        if (func_002B3868(self)) {
            func_L00_002D40A0(self + 0x10, 0, F(D_0018C0B0, 0xF8));
            p->timer = 0;
        }
        if (++p->timer >= 361) {
            func_L01_002C98B8();
            func_002A7750(self, 2, -1);
        } else if (func_L00_002D40F0() != 1) {
            func_002A7750(self, 1, -1);
        }
        break;
    case 1:
        if (func_002B3868(self)) {
            p->angularSpeed = 0;
            p->speed = 0;
        }
        p->targetHeight = p->destination ?
            F((u8 *)(p->node * 128 + (u32)D_L12_001B2F8C), 0x38) : p->origin[2];
        p->targetAngle = p->destination ?
            func_00283B98(F((u8 *)(p->node * 128 + (u32)D_L12_001B2F8C), 0x78),
                          4.7123894691467285f) : p->origin[3];
        target = p->targetHeight;
        speed = 0.003888889f;
        if (p->destination) {
            if (D_00189E20.position[2] < F(self, 0x18) - 1.0f &&
                func_002ACBC8(D_00189E20.position, p->node)) {
                target += 3.0f;
                speed = 0.007777778f;
            } else {
                target += 0.5f;
            }
        }
        func_002AA548(self + 0x18, &p->speed, target, 0.0019444445f, speed, 0.5f);
        if (func_00282C48(p->targetHeight - F(self, 0x18)) < 0.6f &&
            func_00282C48(p->speed) < 0.01f) {
            {
                s32 index = p->sound;

                if (index != -1) {
                    LiftSound *entry = (LiftSound *)(index * 0x70 + (s32)D_00188660);

                    if (entry->owner == self && entry->active)
                        func_002E59F8(index);
                }
            }
            p->sound = -1;
            func_002A7750(self, 2, -1);
        } else {
            LiftSound *entry = (LiftSound *)(p->sound * 0x70 + (s32)D_00188660);

            if (entry->owner != self || !entry->active)
                p->sound = func_002E5CF8(0, 4, self);
        }
        func_002AAA00(self + 0xF8, &p->angularSpeed, p->targetAngle,
                      0.00014544412260875106f, 0.00014544412260875106f, 0.10471977f, 0);
        break;
    }
    func_00282CF0(delta, self + 0x10, oldpos);
    func_002AD6F0((u8 *)p + 0x20, delta, oldrot, self + 0xF0);
}
