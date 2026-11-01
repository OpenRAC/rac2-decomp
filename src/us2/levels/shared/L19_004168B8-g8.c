#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern u8 *D_L19_001B2B0C;
extern int D_001A79F0[] MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 D_0019B2E8[], D_0019B4A8[];
typedef struct { u8 pad[0x464]; u8 slot[0]; } SlotTable;
extern SlotTable D_L19_0021EA30;
#define D_L19_0021EE94 D_L19_0021EA30.slot
extern int D_L19_001B9D00 NOT_SDA;
typedef struct {
    u8 pad00[0x80]; Vector position, rotation;
    u8 padA0[0x60]; Vector relative;
    u8 pad110[0x22c]; u8 *platform;
    u8 pad340[0xe]; short platformMode;
    u8 pad350[0x228]; int alternateActive;
    u8 pad57C[0xc]; u8 *alternatePlatform;
    u8 pad58C[0x68c]; u8 *actor;
    u8 padC1C[0x1674]; u8 *currentActor;
    u8 pad2294[0x20]; u8 cameraMode;
} PlatformPlayer;
extern PlatformPlayer D_00189E20;
#define D_0018C0B0 D_00189E20.currentActor
#define D_0018C0D4 D_00189E20.cameraMode
#define D_0018AA38 D_00189E20.actor
#define D_0018A16E D_00189E20.platformMode
#define D_0018A15C D_00189E20.platform
#define D_0018A398 D_00189E20.alternateActive
#define D_0018A3A8 D_00189E20.alternatePlatform
#define D_00189EA0 D_00189E20.position
#define D_00189EB0 D_00189E20.rotation
#define D_00189F20 D_00189E20.relative
#define D_00189F28 D_00189E20.relative.f[2]
extern float D_L19_001B1BD0 __attribute__((sda));
extern float D_L19_001B1BE0 __attribute__((sda));
extern float D_L19_001B1BE4 __attribute__((sda));
extern float D_L19_001B1BE8 __attribute__((sda));
extern float D_L19_001B1BEC __attribute__((sda));
extern float D_L19_001B1BF0 __attribute__((sda));
extern float D_L19_001B1BF4 __attribute__((sda));
extern float func_002A7940(void);
extern void func_002A7750(void *, u8, int);
extern int func_002B38B8(void *);
extern void func_002A0430(unsigned int);
extern void *func_002A9640(void *, u32, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern float func_002AA150(float, float, float);
extern float func_002AA898(float *, float *, int, float, float, float, float);
extern void func_002AEF28(float *, float *, float *, float, float, float);
extern void func_L01_00316C48(void *, void *, void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_US2_L18_002D0050(int);
extern void func_002DF3F8(void *, void *);
extern void func_002B0A68(char *, int, void *, float, float, float, float, u8);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
    float, float, float, float, int, float, int, int, int, u8, int);
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define ADVANCE_GATE() { \
    unsigned int gate_id = actor->packedGate; \
    if (gate_id & 1) { \
        u8 *gate = D_0019B4A8 + (((int)(gate_id << 16) >> 17) + D_001A79F0_gp * 0x400); \
        if (((*gate >> 4) & 7) != 7) *gate += 0x10; \
    } else { \
        u8 *gate = D_0019B4A8 + (((int)(gate_id << 16) >> 17) + D_001A79F0_gp * 0x400); \
        if ((*gate & 7) != 7) ++*gate; \
    } \
}
typedef struct {
    u8 pad00[0x20], transformDelta[0x3c];
    int flags;
    Vector startPosition, startRotation, tilt, tiltVelocity;
    int destination;
    float duration, progress;
    int trigger;
    u8 playerOnly, noExplosion, carryingPlayer, gate;
    int linkedActor;
    float velocity, height, yaw, yawVelocity, phase;
    u8 padCC[4];
    int notify;
} PlatformState;
typedef struct {
    u8 pad00[0x10]; Vector position;
    u8 state, pad21[0x10], draw, pad32[2];
    unsigned short flags;
    u8 pad36[0x32]; PlatformState *vars;
    u8 pad6C[0x2c]; int attached;
    u8 pad9C[0xc], distance, padA9[7], gateId, padB1;
    unsigned short packedGate;
    u8 padB4[8], triggered, padBD[3];
    Vector forward, right, up, rotation;
} PlatformActor;

void func_US2_L19_004168B8(PlatformActor *actor)
{
    PlatformState *state = actor->vars;
    Vector old_position, old_rotation, temp, origin, point, camera_out;
    u8 *saved_player;
    unsigned int saved_mode;
    unsigned int id;
    int index;
    float progress, blend, height, forward_dot, target_x, old_z, gain, right_dot, target_y;
    qcopy(&old_position, &actor->position);
    qcopy(&old_rotation, &actor->rotation);
    switch (actor->state) {
    case 0:
        qcopy(&state->tilt, &actor->rotation);
        qzero_nc(&state->tiltVelocity);
        state->phase = func_002A7940();
        if (state->destination == -1) {
            actor->flags |= 2;
            return;
        }
        state->progress = 0.0f;
        state->flags |= 1;
        qcopy(&state->startPosition, &actor->position);
        qcopy(&state->startRotation, &actor->rotation);
        if (state->notify && actor->gateId != 0xff &&
                (D_0019B2E8[actor->gateId + D_001A79F0_gp * 16] & 0x80))
            goto active;
        if (D_L19_0021EE94[state->trigger])
            goto active;
        if (!state->gate) goto inactive_actor;
        id = actor->packedGate;
        if (D_L19_0021EE94[(short)id]) goto active;
        index = D_0019B4A8[((int)(id << 16) >> 17) + D_001A79F0[0] * 0x400];
        if (id & 1) {
            if ((index >> 4) & 7) goto active;
            goto inactive_actor;
        } else if (!(index & 7)) goto inactive_actor;
active:
        if (actor->gateId != 0xff && state->gate)
            ADVANCE_GATE();
        qcopy_nc(&actor->position, D_L19_001B2B0C + state->destination * 0x80 + 0x30);
        qcopy_nc(&actor->rotation, D_L19_001B2B0C + state->destination * 0x80 + 0x70);
        func_002A7750(actor, 4, -1);
        goto initialized;
inactive_actor:
        func_002A7750(actor, 1, -1);
initialized:
        {
            float initial_height = actor->position.f[2];
            state->velocity = 0.0f;
            state->height = initial_height;
        }
        break;
    case 1:
        if (actor->triggered || func_002B38B8(actor) || state->trigger == -1 ||
                (D_L19_001B2A1C[state->trigger * 0x100 + 0x20] == 0xfe) ||
                (D_L19_001B2A1C[state->trigger * 0x100 + 0x20] == 0xfd)) {
            if (state->linkedActor != -1)
                D_L19_001B2A1C[state->linkedActor * 0x100 + 0xbc] = 1;
            if (actor->gateId != 0xff && state->gate) {
                ADVANCE_GATE();
                if (state->notify) func_002A0430(actor->gateId);
            }
            func_002A7750(actor, 2, -1);
        }
        if (!state->noExplosion && func_002A9640(actor, 0x40000, 0)) {
            if (state->linkedActor != -1)
                D_L19_001B2A1C[state->linkedActor * 0x100 + 0xbc] = 1;
            func_00282CC0(&temp, &actor->right, &actor->up);
            func_00282F20(&temp, &temp, 1.0f / 12.0f);
            func_00282CC0(&origin, &actor->position, &actor->up);
            func_002ABBB8(actor, &temp, &origin, 0.0f, 0.0f, 10, 3, 16,
                4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            func_002B0A68((char *)actor, 31, &temp, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            {
                unsigned int event_id = actor->gateId;
                actor->draw = 0;
                actor->flags |= 1;
                actor->attached = 0;
                if (event_id != 0xff && state->gate) {
                    ADVANCE_GATE();
                    if (state->notify) func_002A0430(actor->gateId);
                }
            }
            func_002A7750(actor, 2, -1);
        }
        actor->distance = 0xff;
        break;
    case 2:
        progress = state->progress + 1.0f / state->duration;
        state->progress = progress;
        if (progress > 1.0f)
            state->progress = 1.0f;
        blend = (1.0f - func_00283180(state->progress * 3.1415927f)) * 0.5f;
        func_00282CF0(&temp, D_L19_001B2B0C + state->destination * 0x80 + 0x30, &state->startPosition);
        func_00282D30(&temp, &temp, blend);
        old_z = actor->position.f[2];
        func_00282CC0(&actor->position, &state->startPosition, &temp);
        state->height = actor->position.f[2];
        actor->position.f[2] = old_z;
        actor->rotation.f[2] = func_002AA150(state->startRotation.f[2], F(D_L19_001B2B0C + state->destination * 0x80, 0x78), blend);
        actor->rotation.f[1] = func_002AA150(state->startRotation.f[1], F(D_L19_001B2B0C + state->destination * 0x80, 0x74), blend);
        actor->rotation.f[0] = func_002AA150(state->startRotation.f[0], F(D_L19_001B2B0C + state->destination * 0x80, 0x70), blend);
        if (state->progress >= 1.0f) {
            func_002A7750(actor, 3, -1);
            goto finish_transition;
        }
        break;
    case 3:
finish_transition:
        if (state->linkedActor == -1 || !D_L19_001B2A1C[state->linkedActor * 0x100 + 0xbc]) {
            if (state->playerOnly) {
                D_L19_001B9D00 = 0;
                func_US2_L18_002D0050(0);
            }
            if (state->notify) {
                if (D_0018C0D4) {
                    saved_mode = D_0018C0D4;
                    saved_player = D_0018C0B0;
                    D_0018C0D4 = 0;
                    D_0018C0B0 = D_0018AA38;
                    func_002DF3F8(D_0018AA38 + 0x10, D_0018AA38 + 0xf0);
                    D_0018C0D4 = saved_mode;
                    D_0018C0B0 = saved_player;
                } else
                    func_002DF3F8(&D_00189EA0, &D_00189EB0);
            }
            func_002A7750(actor, 4, -1);
        }
        break;
    }
    height = state->height;
    if (actor->state != 2) {
        height += func_00283198(state->phase) * 0.1f;
        state->phase = func_00283B98(state->phase, 0.01745329611003399f);
    }
    if (state->carryingPlayer)
        height -= 0.2f;
    state->velocity = (state->velocity + (height - actor->position.f[2]) * 0.005f) * 0.98f;
    actor->position.f[2] += state->velocity;
    if (actor->state) {
        if ((!D_0018A16E && D_0018A15C == (u8 *)actor) || (D_0018A398 && D_0018A3A8 == (u8 *)actor)) {
            if (!state->carryingPlayer)
                state->velocity -= 1.0f / 60.0f;
            state->carryingPlayer = 1;
            func_00282CF0(&temp, &D_00189EA0, &actor->position);
            forward_dot = func_00282DB0(&temp, &actor->forward);
            right_dot = func_00282DB0(&temp, &actor->right);
            gain = D_L19_001B1BD0;
            origin.q = state->tilt.q;
            point.q = actor->position.q;
            target_y = gain * forward_dot;
            target_x = -gain;
            target_x *= right_dot;
            func_002AA898((float *)(&state->tilt), (float *)(&state->tiltVelocity), 0, target_x,
                D_L19_001B1BE0, D_L19_001B1BE4, D_L19_001B1BE8);
            func_002AA898((float *)(&state->tilt.f[1]), (float *)(&state->tiltVelocity.f[1]), 0, target_y,
                D_L19_001B1BE0, D_L19_001B1BE4, D_L19_001B1BE8);
            func_L01_00316C48(&D_00189EA0, &camera_out, &actor->position, &origin, &state->tilt);
            func_00282CF0(&D_00189F20, &camera_out, &D_00189EA0);
            D_00189F28 += actor->position.f[2] - point.f[2];
        } else {
            state->carryingPlayer = 0;
            func_002AA898((float *)(&state->tilt), (float *)(&state->tiltVelocity), 0, 0.0f,
                D_L19_001B1BEC, D_L19_001B1BF0, D_L19_001B1BF4);
            func_002AA898((float *)(&state->tilt.f[1]), (float *)(&state->tiltVelocity.f[1]), 0, 0.0f,
                D_L19_001B1BEC, D_L19_001B1BF0, D_L19_001B1BF4);
        }
        func_002AEF28((float *)actor, (float *)(&state->yaw), (float *)(&state->yawVelocity),
            0.02007128857076168f, 0.007272206246852875f, 0.009017535485327244f);
        actor->rotation.f[0] = func_00283B98(state->tilt.f[0], actor->rotation.f[0]);
        actor->rotation.f[1] = func_00283B98(state->tilt.f[1], actor->rotation.f[1]);
    }
    func_00282CF0(&temp, &actor->position, &old_position);
    func_002AD6F0(&state->transformDelta, &temp, &old_rotation, &actor->rotation);
}
