/* func_PAL_L01_003B5970, the PAL copy of func_L01_003B1F08: the same C, where rename func_L01_003208D0 becomes func_PAL_L01_00322798; scale state- becomes returnWait; scale state- becomes returnWait; wrap state- becomes nextWait (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 mode;
    u8 index;
    u8 pad22[2];
    u8 *info;
    u8 pad28[0xC];
    u16 flags;
    u8 pad36[0x32];
    struct MoverState *state;
    u8 pad6C[0x2C];
    int timer;
    u8 pad9C[0x20];
    u8 triggered;
    u8 padBD[0x33];
    float rot[4];
} MoverObject;

typedef struct MoverState {
    u8 pad00[0x20];
    float motion[0x10];
    float homePos[4];
    float homeRot[4];
    int target;
    int waitDuration;
    float moveTime;
    int nextWait;
    u8 pad90[4];
    int returnWait;
    int cycles;
    float t;
    int wait;
    int cycleWait;
    int sound;
    u8 tailAC[1];
} MoverState;

typedef struct {
    u8 pad00[0x30];
    float pos[4];
    u8 pad40[0x30];
    float rot[4];
} MoverTarget;

extern int func_00282948(void *);
extern float func_00283180(float);
extern void func_00282CC0(void *, void *, void *);
extern u8 D_00188660[];
extern MoverTarget *D_L01_001B264C __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern void func_002E59F8(int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_002A8598(int, int);
extern float func_002AA150(float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_PAL_L01_00322798(void *, void *, int);

#define CLEAR_SOUND() { \
    int id = state->sound; \
    if (id != -1) { \
        u8 *slot = D_00188660 + id * 0x70; \
        if (*(MoverObject **)(slot + 0x88) == object && slot[0x74]) \
            func_002E59F8(id); \
    } \
    state->sound = -1; \
}

#define KEEP_SOUND() { \
    u8 *slot = D_00188660 + state->sound * 0x70; \
    if (*(MoverObject **)(slot + 0x88) != object || !slot[0x74]) \
        state->sound = func_002E5DA0(0, 4, object, 0x9EA); \
}

#define INTERPOLATE() { \
    weight = 1.0f - func_00283180(state->t * 3.1415927f); \
    weight *= 0.5f; \
    func_00282CF0(delta, D_L01_001B264C[state->target].pos, state->homePos); \
    func_00282D30(delta, delta, weight); \
    func_00282CC0(object->pos, state->homePos, delta); \
    object->rot[2] = func_002AA150(state->homeRot[2], D_L01_001B264C[state->target].rot[2], weight); \
    object->rot[1] = func_002AA150(state->homeRot[1], D_L01_001B264C[state->target].rot[1], weight); \
    object->rot[0] = func_002AA150(state->homeRot[0], D_L01_001B264C[state->target].rot[0], weight); \
}

void func_PAL_L01_003B5970(MoverObject *object)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    MoverState *state = object->state;
    float weight;

    qcopy(oldpos, object->pos);
    qcopy(oldrot, object->rot);
    switch (object->mode) {
    case 0:
        object->flags |= 0x2000;
        state->sound = -1;
        qcopy(state->homePos, object->pos);
        qcopy(state->homeRot, object->rot);
        func_002A7750(object, 1, -1);
        object->timer = 0;
        break;
    case 1:
        CLEAR_SOUND()
        if (object->triggered) {
            state->cycleWait = state->cycles;
            state->wait = state->waitDuration;
            func_002A7750(object, 2, -1);
            object->timer = *(int *)(object->info + 0x10);
        }
        break;
    case 2:
        if (func_00282948(&state->wait)) {
            state->t = 0.0f;
            func_002A7750(object, 3, -1);
        }
        break;
    case 3:
        state->t += 1.0f / state->moveTime;
        if (state->t > 1.0f)
            state->t = 1.0f;
        INTERPOLATE()
        if (state->t >= 1.0f) {
            if (state->nextWait == -1) {
                func_002A7750(object, 5, -1);
            } else {
                state->wait = (((int)(state->nextWait) * 5 + 2) / 6);
                func_002A7750(object, 4, -1);
            }
        }
        KEEP_SOUND()
        break;
    case 4:
        CLEAR_SOUND()
        if (func_00282948(&state->wait)) {
            state->t = 1.0f;
            func_002A7750(object, 6, -1);
        }
        break;
    case 5:
        CLEAR_SOUND()
        if (object->triggered) {
            state->wait = state->waitDuration;
            object->triggered = 0;
            func_002A7750(object, 4, -1);
        }
        break;
    case 6:
        state->t -= 1.0f / state->moveTime;
        if (state->t < 0.0f)
            state->t = 0.0f;
        INTERPOLATE()
        if (state->t <= 0.0f) {
            if (state->cycles == -1) {
                state->wait = (((int)(state->returnWait) * 5 + 2) / 6);
                func_002A7750(object, 7, -1);
            } else if (func_00282948(&state->cycleWait)) {
                func_002A8598(object->index, 0);
                func_002A7750(object, 1, -1);
                object->timer = 0;
            } else {
                state->wait = (((int)(state->returnWait) * 5 + 2) / 6);
                func_002A7750(object, 7, -1);
            }
        }
        KEEP_SOUND()
        break;
    case 7:
        CLEAR_SOUND()
        if (func_00282948(&state->wait)) {
            state->t = 0.0f;
            func_002A7750(object, 3, -1);
        }
        break;
    }
    object->triggered = 0;
    if (object->mode < 8) {
        func_00282CF0(delta, object->pos, oldpos);
        func_002AD6F0(state->motion, delta, oldrot, object->rot);
    }
    func_PAL_L01_00322798(object, state->tailAC, object->mode >= 2);
}
