#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct {
    char pad00[0x10];
    int f10;
} LiftModel;
typedef struct LiftMoby {
    char pad00[0x10];
    Vec position;
    unsigned char state;
    char pad21[3];
    LiftModel *model;
    char pad28[8];
    char f30;
    char f31;
    short f32;
    char pad34[4];
    long long f38;
    char pad40[0x28];
    struct LiftContext *ctx;
    char pad6C[0xC];
    unsigned int colour;
    char pad7C[0x1C];
    int f98;
    char pad9C[0x54];
    Vec rotation;
} LiftMoby;
typedef struct LiftContext {
    char pad00[0x20];
    char mover[0x3C];
    int flags;
    Vec home;
    char pad70[0x10];
    int atBottom;
    int travelFrames;
    int soundHandle;
    float otherHeight;
    int startsAtBottom;
    float topHeight;
    float bottomHeight;
    LiftMoby *child;
    float blinkPhase;
    int fA4;
    char smoothing[8];
} LiftContext;
typedef struct {
    char pad00[0x80];
    Vec position;
} Player;
typedef struct {
    char pad00[0x74];
    unsigned char playing;
    char pad75[0x13];
    LiftMoby *owner;
} SoundSlot;
extern Player D_00189E20;
extern unsigned char D_00188660[];
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00282C48(float);
extern float func_002A7940(void);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern int func_L00_00324120(LiftMoby *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern LiftMoby *func_0029EFD0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002AA3A8(float *, void *, float, float, float, float);
extern int func_002E5DA0(int, int, void *, int);
#define PLAYER_POSITION D_00189E20.position
#define STOP_SOUND()                                                                  \
    {                                                                                 \
        SoundSlot *slot;                                                              \
        handle = ctx->soundHandle;                                                    \
        if (handle != -1 && (slot = (SoundSlot *)(handle * 0x70 + D_00188660))->owner == obj \
            && slot->playing)                                                         \
            func_002E59F8(handle);                                                    \
        ctx->soundHandle = -1;                                                        \
    }
#define START_SOUND()                                 \
    if (!func_002E59B0(obj, ctx->soundHandle))        \
        ctx->soundHandle = func_002E5CF8(0, 4, obj)
#define START_MOVING(state)                           \
    func_002A7750(obj, state, -1);                    \
    ctx->child->colour = 0x8000DF2A;                  \
    func_002E5DA0(0, 0, obj, 0x8A1);                  \
    ctx->child->f98 = 0

void func_PAL_L00_003D3F50(LiftMoby *obj) {
    struct {
        Vec old, rotation, delta, offset;
    } frame;
    LiftContext *ctx = obj->ctx;
    LiftMoby *child, *made;
    unsigned int colour;
    int value, handle;

    qcopy(&frame.old, &obj->position);
    qcopy(&frame.rotation, &obj->rotation);
    switch (obj->state) {
    case 0:
        ctx->flags |= 1;
        qcopy(&ctx->home, &obj->position);
        obj->state = 1;
        if (!ctx->startsAtBottom) {
            ctx->topHeight = ctx->home.f[2];
            ctx->bottomHeight = ctx->otherHeight;
            ctx->atBottom = 0;
        } else {
            ctx->atBottom = 1;
            ctx->topHeight = ctx->otherHeight;
            ctx->bottomHeight = ctx->home.f[2];
        }
        ctx->travelFrames = 0;
        ctx->soundHandle = -1;
        made = func_0029EFD0(0xC16);
        ctx->child = made;
        if (!made) {
            func_0029F338(obj);
            return;
        }
        made->f30 = obj->f30;
        ctx->child->f32 = obj->f32;
        ctx->child->f31 = 1;
        ctx->child->f38 = obj->f38;
        child = ctx->child;
        qcopy(&child->position, &obj->position);
        child->position.f[2] += 0.25f;
        frame.delta.f[0] = func_00283180(obj->rotation.f[2]);
        frame.delta.f[1] = func_00283198(obj->rotation.f[2]);
        frame.delta.f[2] = 0;
        func_00282CC0(&ctx->child->position, &ctx->child->position, &frame.delta);
        func_002A0F48(ctx->child);
        ctx->blinkPhase = func_002A7940();
        break;
    case 1:
        ctx->blinkPhase = func_00283B98(ctx->blinkPhase, 0.12566373f);
        value = func_00283CF0((func_00283198(ctx->blinkPhase) * 4.0f - 3.0f) * 208.0f);
        if (value > 208)
            value = 208;
        else if (value < 80)
            value = 80;
        colour = 0x80000000 | value << 16 | value << 8;
        ctx->child->colour = colour | value;
        if (func_L00_00324120(ctx->child)) {
            if (!ctx->atBottom) {
                START_MOVING(3);
                START_SOUND();
            } else {
                func_002A7750(obj, 2, -1);
                ctx->child->f98 = 0;
                ctx->child->colour = 0x8000DF2A;
                func_002E5DA0(0, 0, obj, 0x8A1);
                START_SOUND();
            }
        }
        if (func_00282C48(obj->position.f[2] - PLAYER_POSITION.f[2]) > 6.0f && !ctx->atBottom
            && func_00282E80(&obj->position, &PLAYER_POSITION) < 25.0f) {
            START_SOUND();
            START_MOVING(3);
        } else if (func_00282C48(obj->position.f[2] - PLAYER_POSITION.f[2]) > 6.0f && ctx->atBottom == 1) {
            START_SOUND();
            START_MOVING(2);
        }
        break;
    case 2:
        qcopy(&frame.delta, &obj->position);
        frame.delta.f[2] = ctx->topHeight;
        if (func_00282E48(&obj->position, &frame.delta) > 0.25f) {
            func_002AA3A8(&obj->position.f[2], ctx->smoothing, frame.delta.f[2], 0.02f, 0.3f, 0.120000005f);
            ++ctx->travelFrames;
            break;
        }
        if (!func_L00_00324120(ctx->child)
            && (func_00282E80(&obj->position, &PLAYER_POSITION) > 2.0f || obj->position.f[2] > PLAYER_POSITION.f[2])) {
            ctx->atBottom = 0;
            STOP_SOUND();
            func_002A7750(obj, 1, -1);
            ctx->child->colour = 0x808C8C8C;
            ctx->child->f98 = ctx->child->model->f10;
        } else {
            if (ctx->travelFrames > 0) {
                func_002E5CF8(1, 0, obj);
                ctx->travelFrames = 0;
            }
            STOP_SOUND();
        }
        break;
    case 3:
        if (obj->position.f[2] > ctx->bottomHeight) {
            if (obj->position.f[2] - PLAYER_POSITION.f[2] < 1.8f && PLAYER_POSITION.f[2] < obj->position.f[2]) {
                if (func_002ACBC8(&PLAYER_POSITION, ctx->fA4))
                    break;
                func_002AA3A8(&obj->position.f[2], ctx->smoothing, ctx->bottomHeight, 0.02f, 0.3f, 0.120000005f);
                ++ctx->travelFrames;
            } else {
                func_002AA3A8(&obj->position.f[2], ctx->smoothing, ctx->bottomHeight, 0.0024f, 0.0048f,
                              0.120000005f);
                ++ctx->travelFrames;
            }
            break;
        }
        if (!func_L00_00324120(ctx->child)
            && (func_00282E80(&obj->position, &PLAYER_POSITION) > 2.0f || obj->position.f[2] > PLAYER_POSITION.f[2])) {
            ctx->atBottom = 1;
            STOP_SOUND();
            func_002A7750(obj, 1, -1);
            ctx->child->colour = 0x808C8C8C;
            ctx->child->f98 = ctx->child->model->f10;
            ctx->travelFrames = 0;
        } else {
            if (ctx->travelFrames > 0) {
                func_002E5CF8(1, 0, obj);
                ctx->travelFrames = 0;
            }
            STOP_SOUND();
        }
        break;
    }
    func_00282CF0(&frame.delta, &obj->position, &frame.old);
    func_002AD6F0(ctx->mover, &frame.delta, &frame.rotation, &obj->rotation);
    qcopy(&ctx->child->position, &obj->position);
    frame.offset.f[0] = func_00283180(obj->rotation.f[2]);
    frame.offset.f[1] = func_00283198(obj->rotation.f[2]);
    frame.offset.f[2] = 0;
    func_00282CC0(&ctx->child->position, &ctx->child->position, &frame.offset);
    ctx->child->position.f[2] += 0.25f;
}
