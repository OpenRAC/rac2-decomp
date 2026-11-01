#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x80]; Vec position; } LiftHero;
extern LiftHero D_00189E20;
typedef struct { char head[0x10]; Vec position; char tail[0xD0]; Vec rotation; } LiftMoby;
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; char *owner; } LiftSound;
extern unsigned char D_00188660[];
typedef struct { char pad[0x140]; Vec from, to; char gap[0x30]; char *camera; } LiftCamera;
extern LiftCamera D_L00_001B8C80;
extern const int D_001A7908;
extern float func_00283B98(float, float), func_00283198(float), func_00282C48(float), func_002A7940(void);
extern float func_00282E80(void *, void *), func_00282E48(void *, void *);
extern int func_00283CF0(float), func_L00_00324120(int), func_002E59B0(void *, int), func_002E5CF8(int, int, void *);
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int), func_002E59F8(int), func_0029F338(void *), func_002A0F48(void *);
extern char *func_0029EFD0(int), *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(void *), func_00335438(void *, void *, int, int, int), func_003353C8(void *);
extern void func_00335370(void *), func_003355A8(int);
extern void func_00282CF0(void *, void *, void *), func_002AD6F0(void *, void *, void *, void *);
extern float func_002AA3A8(void *, void *, float, float, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern int func_002E5DA0(int, int, void *, int);
typedef struct {
    char head[0x20], transform[0x3C];
    int flags;
    Vec home;
    char gap[0x10];
    int direction, counter, sound;
    float endpoint;
    int initialDirection;
    float target, otherTarget;
    char *camera, *child;
    int release;
    float phase, velocity;
    int trigger;
} LiftContext;
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))
#define STOP_SOUND() {                                                                  \
        handle = ctx->sound;                                                            \
        if (handle != -1) {                                                             \
            LiftSound *sound = (LiftSound *)(handle * 0x70 + (int)D_00188660);          \
            if (sound->owner == obj && sound->active)                                   \
                func_002E59F8(handle);                                                  \
        }                                                                               \
        ctx->sound = -1;                                                                \
    }
#define RELEASE()                                                                       \
    if (ctx->release) {                                                                 \
        func_L00_002D7140(ctx->camera);                                                 \
        ctx->release = 0;                                                               \
    }
#define START_SOUND(s)                                                                  \
    if (!func_002E59B0(obj, ctx->sound))                                                \
        ctx->sound = func_002E5CF8(s, 4, obj)
#define RESET_CHILD()                                                                   \
    func_002A7750(obj, 1, -1);                                                          \
    I(ctx->child, 0x78) = 0x808C8C8C;                                                   \
    I(ctx->child, 0x98) = I(P(ctx->child, 0x24), 0x10)

void func_PAL_L00_003D1828(LiftMoby *moby) {
    char *obj = (char *)moby;
    struct { Vec old, rotation, delta, camera; } frame;
    LiftContext *ctx = *(LiftContext **)(obj + 0x68);

    int value, handle;
    unsigned int brightness;
    qcopy(&frame.old, &moby->position);
    qcopy(&frame.rotation, &moby->rotation);
    switch ((unsigned char)obj[0x20]) {
    case 0: {
        char *created;
        *(unsigned short *)(obj + 0x34) |= 0x800;
        ctx->flags |= 1;
        qcopy(&ctx->home, &moby->position);
        ctx->velocity = 0.0f;
        obj[0x20] = 1;
        if (!ctx->initialDirection) {
            ctx->target = ctx->home.f[2];
            ctx->otherTarget = ctx->endpoint;
            ctx->direction = 0;
        } else {
            ctx->direction = 1;
            ctx->target = ctx->endpoint;
            ctx->otherTarget = ctx->home.f[2];
        }
        ctx->counter = 0;
        ctx->sound = -1;
        created = func_0029EFD0(0xC16);
        ctx->child = created;
        if (!created) {
            func_0029F338(obj);
            return;
        }
        created[0x30] = obj[0x30];
        *(short *)(ctx->child + 0x32) = *(short *)(obj + 0x32);
        ctx->child[0x31] = 1;
        {
            char *child = ctx->child;
            qcopy(&((LiftMoby *)child)->position, &moby->position);
            F(child, 0x18) += 0.25f;
        }
        func_002A0F48(ctx->child);
        ctx->phase = func_002A7940();
        break;
    }
    case 1:
        ctx->phase = func_00283B98(ctx->phase, 0.12566373f);
        value = func_00283CF0((func_00283198(ctx->phase) * 4.0f - 3.0f) * 208.0f);
        if (value > 208)
            value = 208;
        else if (value < 80)
            value = 80;
        brightness = value;
        {
            unsigned int low = brightness << 8 | 0x80000000;
            unsigned int color = brightness << 16 | low;
            I(ctx->child, 0x78) = color | brightness;
        }
        if (func_L00_00324120((int)ctx->child) && ctx->direction) {
            func_002A7750(obj, 2, -1);
            ctx->velocity = 0.0f;
            I(ctx->child, 0x78) = 0x8000DF2A;
            if (!D_001A7908) {
                func_00335438(&D_L00_001B8C80.from, &D_L00_001B8C80.to, 2, 100, 0);
                frame.camera.f[0] = 246.85f;
                frame.camera.f[1] = 198.19f;
                frame.camera.f[2] = D_00189E20.position.f[2] + 1.5f;
                frame.delta.f[2] = 1.5707965f;
                frame.delta.f[0] = 0;
                frame.delta.f[1] = 0;
                func_003353C8(&frame.delta);
                func_00335370(&frame.camera);
            }
            func_002E5DA0(0, 0, obj, 0x8A1);
            I(ctx->child, 0x98) = 0;
            START_SOUND(0);
            ctx->camera = func_PAL_L00_002D7850(5);
            F(ctx->camera, 0) = 2.0f;
            F(ctx->camera, 4) = 1.5f;
            ctx->release = 1;
        }
        if (func_00282C48(F(obj, 0x18) - D_00189E20.position.f[2]) > 12.0f && !ctx->direction) {
            START_SOUND(0);
            func_002A7750(obj, 3, -1);
            I(ctx->child, 0x78) = 0x8000DF2A;
            I(ctx->child, 0x98) = 0;
        } else if (func_00282C48(F(obj, 0x18) - D_00189E20.position.f[2]) > 12.0f && ctx->direction == 1) {
            START_SOUND(1);
            func_002A7750(obj, 2, -1);
            ctx->velocity = 0.0f;
            I(ctx->child, 0x78) = 0x8000DF2A;
            I(ctx->child, 0x98) = 0;
        }
        break;
    case 2:
        qcopy(&frame.delta, &moby->position);
        frame.delta.f[2] = ctx->target;
        if (func_00282E48(&moby->position, &frame.delta) > 0.14f) {
            func_002AA548(obj + 0x18, &ctx->velocity, frame.delta.f[2], 0.0028000001f, 0.0024f,
                          0.120000005f);
            ++ctx->counter;
        } else if (func_00282E80(&moby->position, &D_00189E20.position) > 1.2f) {
            RELEASE();
            ctx->direction = 0;
            STOP_SOUND();
            RESET_CHILD();
        } else {
            if (ctx->counter > 0) {
                func_002E5CF8(1, 0, obj);
                ctx->counter = 0;
            }
            RELEASE();
            STOP_SOUND();
        }
        if (func_00282C48(F(obj, 0x18) - D_00189E20.position.f[2]) > 3.0f
            && D_00189E20.position.f[2] < F(obj, 0x18))
            func_002A7750(obj, 3, -1);
        break;
    case 3:
        if (F(obj, 0x18) > ctx->otherTarget) {
            if (func_002ACBC8(&D_00189E20.position, ctx->trigger)) {
                if (F(obj, 0x18) - D_00189E20.position.f[2] < 1.8f && D_00189E20.position.f[2] < F(obj, 0x18))
                    break;
                func_002AA3A8(obj + 0x18, &ctx->velocity, ctx->otherTarget, 0.02f, 0.3f, 0.120000005f);
                ++ctx->counter;
            } else {
                F(obj, 0x18) -= 0.08f;
                ++ctx->counter;
            }
        } else if (func_00282E80(&moby->position, &D_00189E20.position) > 1.0f) {
            func_002E5CF8(1, 0, obj);
            RELEASE();
            ctx->direction = 1;
            STOP_SOUND();
            RESET_CHILD();
            ctx->counter = 0;
        } else {
            RELEASE();
            STOP_SOUND();
        }
        break;
    }
    func_00282CF0(&frame.delta, &moby->position, &frame.old);
    func_002AD6F0(ctx->transform, &frame.delta, &frame.rotation, obj + 0xF0);
    {
        char *child = ctx->child;
        qcopy(child + 0x10, &moby->position);
        F(child, 0x18) += 0.25f;
    }
    if (*(short *)(D_L00_001B8C80.camera + 0x86) == 5) {
        frame.camera.f[0] = 246.85f;
        frame.camera.f[1] = 198.19f;
        frame.camera.f[2] = D_00189E20.position.f[2] + 1.5f;
        func_00335370(&frame.camera);
        if (func_00282E80(D_L00_001B8C80.camera + 0x30, &frame.camera) < 0.5f)
            func_003355A8(1);
    }
}
