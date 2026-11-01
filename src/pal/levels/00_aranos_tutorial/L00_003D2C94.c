#include "include_asm.h"



#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct {
    char pad00[0x24];
    float f24;
} AranosModel;
typedef struct AranosMoby {
    char pad00[0x10];
    Vec position;
    unsigned char state;
    char pad21[2];
    unsigned char f23;
    AranosModel *model;
    char pad28[4];
    float f2C;
    char pad30;
    unsigned char f31;
    char pad32[2];
    unsigned short flags;
    char pad36[0x2E];
    void (*hook)(void *);
    void *ctx;
    char pad6C[0x10];
    unsigned short f7C;
    char pad7E[0x1A];
    int f98;
    char pad9C[0xC];
    unsigned char fA8;
    char padA9;
    short classId;
    char padAC[0x14];
    char matrix[0x30];
    Vec rotation;
} AranosMoby;
extern AranosMoby *func_00273730(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern char D_00189EA0[];
extern int func_002ACBC8(char *, unsigned int);
extern void func_0029F338(void *);
extern void func_002E5CF8(int, int, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern AranosMoby *D_L00_00220DA0[];
extern void func_0029F338(void *);
typedef struct {
    unsigned int flag;
    int frames;
} AranosDriftCtx;

/* Once its flag is set, drifts the object along its heading for 100 frames, then removes it. */
void func_PAL_L00_003D3478(AranosMoby *obj) {
    AranosDriftCtx *ctx;
    int result;
    float angle;
    float point[3];

    ctx = obj->ctx;
    if (obj->state == 0) {
        result = func_002ACBC8(D_00189EA0, ctx->flag);
        if (result != 0) {
            obj->state = 1;
            ctx->frames = 0;
            func_002E5CF8(0, 0, obj);
        }
    }
    if (obj->state != 1)
        return;
    angle = obj->rotation.f[2];
    point[0] = func_00283180(angle) * 0.50000006f;
    angle = obj->rotation.f[2];
    point[1] = func_00283198(angle) * 0.50000006f;
    point[2] = 0.0f;
    func_00282CC0(&obj->position, &obj->position, point);
    ctx->frames += 1;
    if (ctx->frames < 0x65)
        return;
    func_0029F338(obj);
}



extern void func_002833F0(void *, void *);
extern int func_002A7820(int, int);
extern int func_00282948(void *);
extern float func_002A78D8(float, float);
extern void func_002AA3A8(float *, float *, float, float, float, float);

void func_PAL_L00_003D38F8(char *obj) {
    char *ctx;
    float limit;
    ctx = *(char **)(obj + 0x68);
    if (*(unsigned char *)(obj + 0x20) == 0) {
        *(float *)(ctx + 8) = func_002A78D8(5.0f, 15.0f);
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(ctx + 0x0C) = func_002A7820(0x3C, 0x78);
        limit = *(float *)(ctx + 8) * 0.017453294f;
        if (*(float *)(obj + 0xF0) < limit) {
            func_002E5CF8(0, 0, obj);
        } else {
            func_002E5CF8(1, 0, obj);
        }
    }
    if (*(unsigned char *)(obj + 0x20) != 1) return;
    limit = *(float *)(ctx + 8) * 0.017453294f;
    func_002AA3A8((float *)(obj + 0xF0), (float *)ctx, limit,
        0.0010471977f, 0.0010471977f, 0.0052359886f);
    func_002833F0(obj + 0xC0, obj + 0xF0);
    if (func_00282948(ctx + 0x0C) != 0) {
        *(unsigned char *)(obj + 0x20) = 0;
    } else if (*(float *)(obj + 0xF0) == *(float *)(ctx + 8) * 0.017453294f) {
        *(unsigned char *)(obj + 0x20) = 0;
    }
}


typedef struct {
    char pad00[4];
    float f04;
    char pad08[0x48];
    int f50;
} AranosChildCtx;
extern float D_L00_001B19CC __attribute__((sda));
extern float D_L00_001B19D0 __attribute__((sda));
extern void *func_002A9640(void *, unsigned int, int);
extern int func_002B3868(void *);
extern void func_002A7750(void *, int, int);
extern void func_002A7A00(void *, float, float);
extern int func_002A99A0(void *, int, void *, int, float);
extern int func_002E5DA0(int, int, void *, int);
extern char *func_L00_00326620(void *, int, int);
extern AranosMoby *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_PAL_L00_0039E608(void *);
extern void func_002A0488(void *, unsigned char, unsigned char, unsigned char);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
typedef struct {
    AranosMoby *sparks[16];
    float decay[16];
    int hold;
    int timer;
} AranosSparkerCtx;

/* Spawns a burst of sparks around the object, then fades them until the timer runs out. */
void func_PAL_L00_003D3A48(AranosMoby *obj) {
    struct {
        Vec velocity, offset, position;
    } frame;
    AranosSparkerCtx *ctx = obj->ctx;
    AranosMoby *child;
    AranosChildCtx *childctx;
    int type, i;
    float life;

    switch (obj->state) {
    case 0:
        for (i = 15; i >= 0; i--)
            ctx->sparks[i] = 0;
        if (obj->classId == 0xAC9) {
            obj->rotation.f[1] += 0.78539824f;
            func_002833F0(obj->matrix, &obj->rotation);
        }
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (func_002A9640(obj, 0x10000, 0) && ctx->hold == 0)
            func_002A7750(obj, 2, -1);
        obj->fA8 = 0xFF;
        return;
    case 2: {
        unsigned char alpha;
        int count = 5, n;

        if (D_L00_001B19CC < 0.85f && D_L00_001B19D0 < 0.85f)
            count = 14;
        for (n = 0; n < count; n++) {
            func_002A7A00(&frame.offset, 0.85f, 1.95f);
            func_002A99A0(obj, 1, &frame.position, 0xFFFF, 1000.0f);
            func_00282CC0(&frame.offset, &frame.offset, &frame.position);
            frame.velocity.f[2] = func_002A7878(0.0f, 5.0f) * 0.020000001f;
            frame.velocity.f[1] = func_002A7878(-6.0f, 6.0f) * 0.020000001f;
            if (func_002A77E0(4)) {
                type = 1;
                ctx->decay[n] = func_002A7878(20.0f, 40.0f) * 0.00040000002f;
                frame.velocity.f[0] = func_002A7878(-8.0f, -4.0f) * 0.020000001f;
                life = func_002A7878(5.0f, 10.0f);
            } else {
                type = 2;
                ctx->decay[n] = 0.0f;
                frame.velocity.f[0] = func_002A7878(2.0f, 4.0f) * 0.020000001f;
                life = func_002A7878(15.0f, 20.0f);
            }
            child = func_PAL_002735D0(obj, type, 0x43E, func_002A77E0(4), &frame.offset, &obj->rotation, &frame.velocity,
                                  0xFF, 180.0f, life);
            ctx->sparks[n] = child;
            if (child) {
                child->hook = func_PAL_L00_0039E608;
                life = func_002A7878(0.75f, 5.0f);
                ctx->sparks[n]->f2C = ctx->sparks[n]->model->f24 * life;
                childctx = ctx->sparks[n]->ctx;
                alpha = 0x80;
                func_002A0488(ctx->sparks[n], 0x20, 0x60, alpha);
                ctx->sparks[n]->f23 = alpha;
                childctx->f50 = 0x1806020;
            }
        }
        func_002E5DA0(func_002A7820(0, 1), 0, obj, 0xC0A);
        switch (obj->classId) {
        case 0xC0A:
            func_L00_00326620(obj, 0xC10, 0);
            break;
        case 0xC0B:
            func_L00_00326620(obj, 0xC11, 0);
            break;
        case 0xC0C:
            func_L00_00326620(obj, 0xC12, 0);
            break;
        case 0xC0D:
            func_L00_00326620(obj, 0xC13, 0);
            break;
        case 0xE01:
            obj->f7C = 0x8001;
            break;
        case 0xE02:
            obj->f7C = 0x8001;
            break;
        case 0xAC9:
            obj->f7C = 0x8001;
            break;
        }
        func_002A7750(obj, 3, -1);
        break;
    }
    case 3:
        if (func_002B3868(obj)) {
            if (!(obj->f7C & 0x8000)) {
                obj->f31 = 0;
                obj->flags |= 1;
            }
            obj->f98 = 0;
            ctx->timer = 250;
        }
        if (!func_00282948(&ctx->timer)) {
            for (i = 0; i < 16; i++) {
                if (ctx->sparks[i])
                    ((AranosChildCtx *)ctx->sparks[i]->ctx)->f04 -= ctx->decay[i];
            }
        } else if (!(obj->f7C & 0x8000)) {
            func_0029F338(obj);
        }
        return;
    default:
        return;
    }
}



