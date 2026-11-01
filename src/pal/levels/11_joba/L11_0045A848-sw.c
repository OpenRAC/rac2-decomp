#include "include_asm.h"

#include "common.h"
typedef int ActorQuadword __attribute__((mode(TI)));
typedef struct ActorObject ActorObject;
typedef struct {
    char pad00[0x34];
    u8 meleeDamage;
    u8 contactDamage;
    char pad36[0x50 - 0x36];
    char contact[0x10];
    char pad60[0x124 - 0x60];
    float step;
    char pad128[0x230 - 0x128];
    float goal[4];
    ActorObject *target;
    s32 group;
    float turnRate;
    s32 field24C;
    ActorObject *aimTarget;
    s16 field254;
    s16 attached;
    s16 idleDelay;
} ActorState;
struct ActorObject {
    char pad00[0x10];
    float pos[4];
    u8 state;
    char pad21[0x42 - 0x21];
    u8 animation;
    u8 nextAnimation;
    char pad44[4];
    float speed;
    char pad4C[0x60 - 0x4C];
    u8 animationFlags;
    char pad61[7];
    ActorState *data;
    char pad6C[0x95 - 0x6C];
    u8 secondaryState;
    u16 timer;
    char pad98[0xAA - 0x98];
    s16 classId;
    char padAC[0xB8 - 0xAC];
    char *controller;
    u8 idleStage;
    char padBD[0xF8 - 0xBD];
    float heading;
    char padFC[4];
};
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x249C - 0x90];
    ActorObject *attackTarget;
} ActorPlayerBlock;
extern ActorPlayerBlock D_00189E20;
extern s32 D_L11_001B30C8[] __attribute__((sda));
extern ActorObject *D_L11_001B359C[] __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern u16 *D_L11_001FC420[];
extern float D_L11_001B1D60 SDATA(D_L11_001B1D60);
extern s32 D_L11_001B1D64 SDATA(D_L11_001B1D64);
extern float D_L11_001B1D6C SDATA(D_L11_001B1D6C);
extern float D_L11_001B1D70 SDATA(D_L11_001B1D70);
extern float D_L11_001B1D74 SDATA(D_L11_001B1D74);
extern float D_L11_001B1D78 SDATA(D_L11_001B1D78);
extern float D_L11_001B1D7C SDATA(D_L11_001B1D7C);
extern float D_L11_001B1D80 SDATA(D_L11_001B1D80);
extern float D_L11_001B1D84 SDATA(D_L11_001B1D84);
extern float D_L11_001B1D88 SDATA(D_L11_001B1D88);
extern float D_L11_001B1D8C SDATA(D_L11_001B1D8C);
extern void func_002A7750(void *, int, int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_L02_002F21C0(void *, void *);
extern float func_002A7878(float, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_0029F530(void *);
extern float func_00283C80(float, float);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern char *func_L11_004417E8(void *);
extern int func_L11_00441808(void *, void *);
extern int func_L11_00441858(void *);
extern int func_002A77E0(int);
extern void func_L11_004565D8(void *, void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int func_002B1C20(void *, void *);
extern void func_PAL_L02_004009A0(void *, int, int);
extern void func_L01_003E9CF8(void *, int, void (*)(char *));
extern void func_L11_00456938(void *);
extern void func_L11_00456540(char *);
extern void func_PAL_L11_0045B9E8(void *);
extern void func_L11_00456010(void *);
extern int func_PAL_L11_0045C2B0(void *);
extern void func_PAL_L11_0045BC60(void *, void *);
extern void func_002A7CA0(void *, float, float, float, float *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_L11_00456A48(void *, int, float, float, float, float, float, float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A8D70(void *, float, float, int, int, float, int, int, int);

void func_PAL_L11_0045AAE4(ActorObject *p)
{
    ActorState *q = p->data;
    float target[4];
    float scratch[4];
    float hit[4];
    float distance, heading, delta, animationFrame;
    int flags, secondaryState;
    u16 *ids;
    ActorObject *entity;

    if (p->state == 1) return;
    func_PAL_L11_0045B9E8(p);
    if (p->state == 1) return;
    if (q->attached == 0) {
        q->target = 0;
        if (p->secondaryState == 3) func_002A7750(p, 4, 2);
    }
    animationFrame = func_0029F530(p);
    if (q->target) {
        *(ActorQuadword *)target = *(ActorQuadword *)(q->target->pos);
        heading = func_00283248(q->target->pos[0] - p->pos[0],
                                q->target->pos[1] - p->pos[1]);
    } else {
        *(ActorQuadword *)target = *(ActorQuadword *)D_00189E20.position;
        heading = func_00283248(D_00189E20.position[0] - p->pos[0],
                                D_00189E20.position[1] - p->pos[1]);
    }
    delta = func_00283C80(p->heading, heading);
    distance = func_00282E80(p->pos, target);
    /* The entry substate also selects the initial walking animation. */
    secondaryState = p->secondaryState;
    switch (secondaryState) {
    case 2:
        if (func_002B3890(p)) {
            p->speed = func_002A7878(0.5f, 1.25f);
            func_002B60B0(p, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (p->nextAnimation != secondaryState) func_PAL_002A7E68(p, 2, 0, 8);
            p->idleStage = 0;
            func_L11_004565D8(p, func_L11_004417E8(p->controller));
            p->timer = 10000;
        }
        if (p->idleStage == 1 && p->timer >= 251) {
            if (p->nextAnimation) func_PAL_002A7E68(p, 0, 0, 8);
            p->timer = func_002A77E0(83);
        }
        if (q->attached) {
            p->speed = 1.0f;
            func_002A7750(p, 5, 3);
        }
        if (p->idleStage == 0 && func_00282E80(p->pos, q->goal) < 0.5f)
            p->idleStage = 1;
        else func_PAL_L01_00323068(p, q->goal);
        break;
    case 3:
        break;
    case 4:
        flags = func_002B1C20(p, q->contact);
        if (flags & 1) {
            func_PAL_L02_004009A0(p, 0, -1);
            func_L01_003E9CF8(p, 0, func_L11_00456540);
        } else if (flags & 2) func_L11_00456938(p);
        break;
    }
    switch (p->state) {
    case 3:
        if (func_002B3868(p)) {
            p->idleStage = 0;
            if (p->nextAnimation != 0) func_PAL_002A7E68(p, 0, 0, 0);
            p->timer = 0;
        }
        if (p->idleStage == 0 && q->idleDelay < p->timer) {
            if (p->nextAnimation != 3) func_PAL_002A7E68(p, 3, 0, 8);
            p->idleStage = 1;
        } else if (p->idleStage == 1) {
            if (func_L11_00441808(p->controller, p->pos))
                func_002A7750(p, 4, 2);
            func_PAL_L01_00323068(p, func_L11_004417E8(p->controller));
        }
        break;
    case 5:
        if (func_002B3868(p)) {
            if (p->nextAnimation != func_002A77E0(2) + 1)
                func_PAL_002A7E68(p, func_002A77E0(2) + 1, 0, 8);
        }
        func_002A7CA0(p, heading, 0.001f, 0.01f, &q->turnRate, 0.1f);
        if (p->animationFlags & 2) func_L11_00456938(p);
        break;
    case 6:
        if (func_002B3868(p)) {
            func_002B60B0(p, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (p->nextAnimation != 2) func_PAL_002A7E68(p, 2, 0, 8);
        }
        func_PAL_L01_00323068(p, target);
        if (D_L11_001B1D60 < distance) func_L11_00456938(p);
        else if (distance < 2.7f) func_L11_00456938(p);
        break;
    case 7:
        if (func_002B3868(p)) {
            func_002B60B0(p, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            if (p->nextAnimation != 3) func_PAL_002A7E68(p, 3, 0, 8);
            p->timer = 0;
        }
        if (q->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)p >> 8) & 0x3F)) {
            for (ids = D_L11_001FC420[func_L11_00441858(p->controller)];
                 (func_L11_00441858(p->controller) & 0xFF) != 0xFF &&
                 func_L11_00441858(p->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == D_L11_001FC420[func_L11_00441858(p->controller)]); ids++) {
                entity = D_L11_001B359C[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (func_00283C80(p->heading, func_00283248(entity->pos[0] - p->pos[0],
                                                        entity->pos[1] - p->pos[1])) < 0.52359885f &&
                    func_L02_002F21C0(p->pos, entity->pos) < 20.0f) {
                    q->aimTarget = entity;
                    break;
                }
            }
        } else if (q->aimTarget == 0 || (q->aimTarget->state == 0xFE || (q->aimTarget->state == 0xFD || q->aimTarget->state < 2))) {
            q->aimTarget = 0;
        }
        if (!func_PAL_L11_0045C2B0(p)) {
            if (q->aimTarget) func_PAL_L11_0045BC60(p, q->aimTarget->pos);
            else func_PAL_L11_0045BC60(p, target);
        }
        func_0029FCC0(p, 1, scratch);
        func_L11_00456A48(p, (int)scratch, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (distance < 2.7f && delta < 0.3490659f) func_002A7750(p, 11, -1);
        if (p->timer > ((s32)(D_L11_001B1D64) * 5 + 2) / 6) func_002A7750(p, 6, -1);
        break;
    case 9:
        if (func_002B3868(p)) {
            if (p->nextAnimation != 4) func_PAL_002A7E68(p, 4, 0, 8);
            q->step = 0.010000001f;
            func_002B60B0(p, 0.0096f, 0.24000001f, 0.00031415932f, 0.00767945f);
        }
        if (q->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)p >> 8) & 0x3F)) {
            for (ids = D_L11_001FC420[func_L11_00441858(p->controller)];
                 (func_L11_00441858(p->controller) & 0xFF) != 0xFF &&
                 func_L11_00441858(p->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == D_L11_001FC420[func_L11_00441858(p->controller)]); ids++) {
                entity = D_L11_001B359C[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (func_00283C80(p->heading, func_00283248(entity->pos[0] - p->pos[0],
                                                        entity->pos[1] - p->pos[1])) < 0.52359885f &&
                    func_L02_002F21C0(p->pos, entity->pos) < 20.0f) {
                    q->aimTarget = entity;
                    break;
                }
            }
        } else if (q->aimTarget == 0 || (q->aimTarget->state == 0xFE || (q->aimTarget->state == 0xFD || q->aimTarget->state < 2))) {
            q->aimTarget = 0;
        }
        if (q->aimTarget) {
            func_PAL_L01_00323068(p, q->aimTarget->pos);
            func_002A7CA0(p,
                          func_00283248(q->aimTarget->pos[0] - p->pos[0],
                                        q->aimTarget->pos[1] - p->pos[1]),
                          0.001f, 0.01f, &q->turnRate, 0.1f);
        } else {
            func_PAL_L01_00323068(p, target);
            func_002A7CA0(p, heading, 0.001f, 0.01f, &q->turnRate, 0.1f);
        }
        func_0029FCC0(p, 1, scratch);
        func_L11_00456A48(p, (int)scratch, D_L11_001B1D6C, (float)q->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D80, D_L11_001B1D88);
        if (D_00189E20.attackTarget == p) func_002A7750(p, 10, -1);
        if (0.38397247f < delta) func_002A7750(p, 8, -1);
        break;
    case 10:
        if (func_002B3868(p)) {
            if (p->nextAnimation != 5) func_PAL_002A7E68(p, 5, 0, 2);
            func_002B60B0(p, 0.006f, 0.040000003f, 0.00062831864f, 0.015707966f);
        }
        scratch[0] = 4.0f * func_00283180(p->heading);
        scratch[1] = 4.0f * func_00283198(p->heading);
        scratch[2] = 0.0f;
        func_00282CC0(scratch, p->pos, scratch);
        func_PAL_L01_00323068(p, scratch);
        func_0029FCC0(p, 1, hit);
        func_L11_00456A48(p, (int)hit, D_L11_001B1D6C, (float)q->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D84, D_L11_001B1D8C);
        if (p->animationFlags & 2) func_002A7750(p, 8, -1);
        break;
    case 8:
        if (func_002B3868(p)) {
            if (p->nextAnimation != 4) func_PAL_002A7E68(p, 4, 0, 8);
        }
        scratch[0] = 4.0f * func_00283180(p->heading);
        scratch[1] = 4.0f * func_00283198(p->heading);
        scratch[2] = 0.0f;
        func_00282CC0(scratch, p->pos, scratch);
        func_PAL_L01_00323068(p, scratch);
        func_002A7CA0(p, heading, 0.001f, 0.01f, &q->turnRate, 0.1f);
        func_0029FCC0(p, 1, hit);
        func_L11_00456A48(p, (int)hit, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (p->animationFlags & 2) func_L11_00456938(p);
        break;
    case 11:
        if (func_002B3868(p)) {
            if (p->nextAnimation != 6) func_PAL_002A7E68(p, 6, 0, 4);
        }
        if (p->animation == 6 && animationFrame >= 10.0f && animationFrame <= 15.0f)
            func_002A8D70(p, 1.0f, (float)q->meleeDamage, 1, 1, 1.0f, 0, 1, 0);
        if (p->animationFlags & 2) {
            if (distance < 2.7f && delta < 0.3490659f) func_002A7750(p, 11, -1);
            else func_L11_00456938(p);
        }
        break;
    case 12:
        if (p->animationFlags & 2) func_L11_00456938(p);
        break;
    }
    func_L11_00456010(p);
}
