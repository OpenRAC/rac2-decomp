/* func_PAL_L00_003D21C0, the PAL copy of func_L00_003CE278: the same C, where rename func_002A7470 becomes func_PAL_002A7E68. */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

typedef struct LiftContext LiftContext;
typedef struct { char pad[0x10]; int animation; } LiftModel;
typedef struct LiftObject {
    char pad00[0x10];
    Vec position;
    unsigned char state, pad21[3];
    LiftModel *model;
    char pad28[8];
    unsigned char group, childMode;
    unsigned short identifier;
    char pad34[4];
    long long parameter;
    char pad40[3];
    unsigned char animation;
    char pad44[0x24];
    LiftContext *context;
    char pad6C[0xC];
    unsigned int color;
    char pad7C[0x1C];
    int animationData;
    char pad9C[0x54];
    Vec rotation;
} LiftObject;
struct LiftContext {
    char pad00[0x5C];
    int flags;
    Vec home;
    char pad70[0x10];
    int active, frames, sound;
    float otherHeight;
    int direction;
    float upperHeight, lowerHeight;
    LiftObject *child;
    float phase, rate;
    unsigned int blockFlag;
};

typedef struct { unsigned char pad[0x80]; Vec position; } LiftHero;
extern LiftHero D_00189E20;
extern unsigned char D_00188660[];
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern float func_002A7940(void);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern int func_L00_00324120(int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern LiftObject *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern float func_002AA3A8(void *, void *, float, float, float, float);
extern int func_002E5DA0(int, int, void *, int);

typedef struct {
    unsigned char pad00[0x74];
    unsigned char active;
    unsigned char pad75[0x13];
    LiftObject *owner;
} LiftSound;

#define STOP_SOUND() { \
    handle = ctx->sound; \
    if (handle != -1) { \
        LiftSound *sound = (LiftSound *)(handle * 0x70 + (int)D_00188660); \
        if (sound->owner == obj && sound->active) func_002E59F8(handle); \
    } \
    ctx->sound = -1; \
}
#define START_SOUND() \
    if (!func_002E59B0(obj, ctx->sound)) ctx->sound = func_002E5CF8(0, 4, obj)
#define SET_ACTIVE(s) \
    func_002A7750(obj, s, -1); \
    if (obj->animation != 2) func_PAL_002A7E68(obj, 2, 0, 5); \
    ctx->child->color = 0x8000DF2A; \
    func_002E5DA0(0, 0, obj, 0x8A1); \
    ctx->child->animationData = 0

/* Moves the lift between its two heights and updates its child and looping sound. */
void func_PAL_L00_003D21C0(LiftObject *obj) {
    struct { Vec old, rotation, delta; } frame;
    LiftContext *ctx = obj->context;
    LiftObject *child;
    int value, handle;
    unsigned int brightness, color;

    qcopy(&frame.old, &obj->position);
    qcopy(&frame.rotation, &obj->rotation);
    switch (obj->state) {
    case 0: {
        LiftObject *child;

        ctx->flags |= 1;
        qcopy(&ctx->home, &obj->position);
        obj->state = 1;
        if (!ctx->direction) {
            ctx->upperHeight = ctx->home.f[2];
            ctx->lowerHeight = ctx->otherHeight;
            ctx->active = 0;
        } else {
            ctx->active = 1;
            ctx->upperHeight = ctx->otherHeight;
            ctx->lowerHeight = ctx->home.f[2];
        }
        ctx->frames = 0;
        ctx->sound = -1;
        ctx->child = func_0029EFD0(0xC16);
        if (!ctx->child) {
            func_0029F338(obj);
            return;
        }
        ctx->child->group = obj->group;
        ctx->child->identifier = obj->identifier;
        ctx->child->childMode = 1;
        ctx->child->parameter = obj->parameter;
        child = ctx->child;
        qcopy(&child->position, &obj->position);
        child->position.f[2] += 0.15f;
        func_002A0F48(ctx->child);
        if (obj->animation != 2) func_PAL_002A7E68(obj, 2, 0, 0);
        ctx->phase = func_002A7940();
        break;
    }
    case 1:
        ctx->phase = func_00283B98(ctx->phase, 0.12566373f);
        value = func_00283CF0((func_00283198(ctx->phase) * 4.0f - 3.0f) * 208.0f);
        if (value > 208) value = 208;
        else if (value < 80) value = 80;
        brightness = (value << 8) | 0x80000000;
        color = (value << 16) | brightness;
        ctx->child->color = color | value;
        if (func_00282E80(&obj->position, &D_00189E20.position) < 6.0f && obj->animation == 2)
            func_PAL_002A7E68(obj, 1, 0, 5);
        if (func_L00_00324120((int)ctx->child)) {
            if (!ctx->active) {
                func_002A7750(obj, 3, -1);
                if (obj->animation != 2) func_PAL_002A7E68(obj, 2, 0, 5);
                ctx->child->animationData = 0;
                ctx->child->color = 0x8000DF2A;
                func_002E5DA0(0, 0, obj, 0x8A1);
                START_SOUND();
            } else {
                SET_ACTIVE(2);
                START_SOUND();
            }
        }
        if (func_00282C48(obj->position.f[2] - D_00189E20.position.f[2]) > 14.0f &&
            !ctx->active && D_00189E20.position.f[2] < obj->position.f[2]) {
            START_SOUND();
            SET_ACTIVE(3);
        } else if (func_00282C48(obj->position.f[2] - D_00189E20.position.f[2]) > 6.0f &&
                   ctx->active == 1 && obj->position.f[2] < D_00189E20.position.f[2]) {
            START_SOUND();
            SET_ACTIVE(2);
        }
        break;
    case 2:
        qcopy(&frame.delta, &obj->position);
        frame.delta.f[2] = ctx->upperHeight;
        if (func_00282E48(&obj->position, &frame.delta) > 0.14f) {
            func_002AA3A8(&obj->position.f[2], &ctx->rate, frame.delta.f[2],
                          0.02f, 0.3f, 0.120000005f);
            ++ctx->frames;
        } else {
            if (func_00282E80(&obj->position, &D_00189E20.position) > 1.2f) {
                ctx->active = 0;
                STOP_SOUND();
                func_002A7750(obj, 1, -1);
                if (obj->animation != 1) func_PAL_002A7E68(obj, 1, 0, 5);
                ctx->child->color = 0x808C8C8C;
                ctx->child->animationData = ctx->child->model->animation;
            } else {
                if (ctx->frames > 0) {
                    func_002E5CF8(1, 0, obj);
                    ctx->frames = 0;
                }
                STOP_SOUND();
                if (obj->animation != 1) func_PAL_002A7E68(obj, 1, 0, 5);
            }
        }
        break;
    case 3: {
        float height = obj->position.f[2];

        if (ctx->lowerHeight < height) {
            if (height - D_00189E20.position.f[2] < 1.8f && D_00189E20.position.f[2] < height) {
                if (func_002ACBC8(&D_00189E20.position, ctx->blockFlag)) break;
                func_002AA3A8(&obj->position.f[2], &ctx->rate, ctx->lowerHeight,
                              0.02f, 0.3f, 0.120000005f);
                ++ctx->frames;
            } else {
                func_002AA3A8(&obj->position.f[2], &ctx->rate, ctx->lowerHeight,
                              0.0024f, 0.0048f, 0.120000005f);
                ++ctx->frames;
            }
            break;
        }
        if (func_00282E80(&obj->position, &D_00189E20.position) > 1.2f) {
            ctx->active = 1;
            STOP_SOUND();
            func_002A7750(obj, 1, -1);
            if (obj->animation != 1) func_PAL_002A7E68(obj, 1, 0, 5);
            ctx->child->color = 0x808C8C8C;
            ctx->child->animationData = ctx->child->model->animation;
        } else {
            if (ctx->frames > 0) {
                func_002E5CF8(1, 0, obj);
                ctx->frames = 0;
            }
            STOP_SOUND();
            if (obj->animation != 1) func_PAL_002A7E68(obj, 1, 0, 5);
        }
        break;
    }
    }
    func_00282CF0(&frame.delta, &obj->position, &frame.old);
    func_002AD6F0((char *)ctx + 0x20, &frame.delta, &frame.rotation, &obj->rotation);
    child = ctx->child;
    qcopy(&child->position, &obj->position);
    child->position.f[2] += 0.2f;
}
