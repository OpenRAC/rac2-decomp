#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char *owner;
    float speed;
    int field08, field0c, lifetime;
    char *attachment;
    int field18, field1c;
    char *attachment20;
    void *matrix24, *matrix28;
    int field2c;
    char pad30[0x14];
    float field44, field48;
    int field4c;
} TetherState;
typedef struct {
    char pad00[0x110]; float velocity[4]; char pad120[0x21C]; u8 *supportObject;
    char pad340[0x420]; float axis[4]; char pad770[0x1A90]; float matrix[2][16];
    char *current; char pad2284[0xC]; char *object;
} TetherHero;
extern TetherHero D_00189E20;
/* The moby fields set at spawn (RAC1 struct Moby: state, update_dist, visible, draw_dist). */
typedef struct { char pad00[0x20]; u8 state; char pad21[0xF]; u8 updateDist; u8 visible; s16 drawDist; } TetherActor;
extern int D_L00_001B1BE8[] __attribute__((sda)), D_L00_001B1A4C[] __attribute__((sda));
extern int D_L00_001A8FF0;
extern float D_L00_001AF0E4 __attribute__((sda));
extern float D_L00_001BF220[4];
extern char *func_0029EFD0(int);
extern s32 func_002AD0B0(u8 *);
extern float func_00282DF0(void *);
extern void func_L00_00390E10(void *), func_002A0F48(void *);
extern char *func_L00_004282F0(void *);
extern int func_L00_002C42E0(int a0, int a1);
extern void func_00282A60(void *, int, int), func_0029F978(u8 *, u32, u8 *);
extern char *func_L00_00395240(char *);
extern void func_002AB650(u8 *);
extern int func_002E5CF8(int, int, char *), func_002761F8(void *, void *, int, void *, int), func_002B0CE0(int, int, int);
extern void func_002AFFD8(char *, char *, int), func_00282DD8(void *, void *, void *), func_00282F20(void *, void *, float);
extern int func_002FED90(void *, int, float, float, float);
/* Creates the active tether actor and its attachments, inheriting the hero's support frame. */
char *func_L00_00390FF8(char *owner, char *position, float yaw, float pitch) {
    char *actor = func_0029EFD0(0xAC);
    TetherState *state;
    float start[4] __attribute__((aligned(16)));
    float side[4];
    if (actor) {
        state = *(TetherState **)(actor + 0x68);
        D_L00_001B1BE8[0] = 1;
        D_00189E20.current = actor;
        ((TetherActor *)actor)->updateDist = 0xFF;
        ((TetherActor *)actor)->visible = 1;
        ((TetherActor *)actor)->state = 1;
        ((TetherActor *)actor)->drawDist = 0xFF;
        if (D_L00_001A8FF0) {
            *(float *)(actor + 0xF8) = 0;
            *(float *)(actor + 0xF4) = 0;
        } else {
            *(float *)(actor + 0xF8) = yaw;
            *(float *)(actor + 0xF4) = pitch;
        }
        *(float *)(actor + 0xF0) = 0;
        *(float *)(actor + 0xFC) = 0;
        state->matrix24 = D_00189E20.matrix[0];
        state->matrix28 = D_00189E20.matrix[1];
        state->owner = owner;
        qcopy(actor + 0x10, position);
        state->field08 = 0;
        state->field0c = 0;
        if (D_00189E20.supportObject && func_002AD0B0(D_00189E20.supportObject))
            state->speed = func_00282DF0(D_00189E20.velocity);
        else state->speed = 0;
        state->field18 = 0;
        state->field1c = 0;
        state->attachment = 0;
        state->field44 = 0.4f;
        state->lifetime = 3000;
        func_L00_00390E10(actor);
        func_002A0F48(actor);
        {
            char *attachment = func_L00_004282F0(actor);
            state->attachment = attachment;
            func_L00_002C42E0(28, 1);
        }
        func_00282A60(state->matrix24, 0, 64);
        func_00282A60(state->matrix28, 0, 64);
        func_0029F978((u8 *)actor, 0, state->matrix24);
        func_0029F978((u8 *)actor, 1, state->matrix28);
        {
            char *attachment = func_L00_00395240(actor);
            float dt = D_L00_001AF0E4;
            state->attachment20 = attachment;
            state->field48 = dt * 0.016666668f;
        }
        func_002AB650((u8 *)actor);
        state->field2c = func_002E5CF8(0, 4, actor);
        *(Quad *)(start) = *(Quad *)(owner + 0x10);
        start[2] = ((float *)position)[2];
        if (func_002761F8(start, position, 0, D_00189E20.object, 0)) {
            *(u8 *)(actor + 0xBC) = 1;
            qcopy(actor + 0x10, D_L00_001BF220);
        }
        D_L00_001B1A4C[0] = 1;
        func_002B0CE0(6, 0, 1);
        if (D_L00_001A8FF0) {
            *(u16 *)(actor + 0x34) |= 0x100;
            qcopy(actor + 0xC0, D_00189E20.axis);
            func_002AFFD8(actor + 0x10, actor + 0xE0, 1);
            func_00282DD8(side, actor + 0xC0, actor + 0xE0);
            func_00282F20(actor + 0xD0, side, 1.0f);
            func_00282DD8(actor + 0xE0, actor + 0xD0, actor + 0xC0);
            *(float *)(actor + 0xCC) = *(float *)(actor + 0xDC) = *(float *)(actor + 0xEC) = 0.0f;
        }
        state->field4c = func_002FED90(actor, 0, 1.0f, 1.0f, 1.0f);
    }
    return actor;
}
