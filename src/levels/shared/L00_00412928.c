#include "common.h"
#include "include_asm.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct { Vector row[3]; Vector position; } Frame;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern Vector D_0018A0E0;
extern Vector D_L00_001AA310[4];
extern void func_00281DE8(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C768(int, float *, float *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);


extern void func_00280B90(char *, int, int);

typedef int Vector128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(char *, char *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_L00_00415DE8(char *, char *);
extern void func_L00_00418A80(char *, char *);
extern void func_L00_00414540(char *, char *, char *);
extern int func_002AD330(char *, char *, char *, char *);
extern char ref_L00_004195C8_00[];
extern char D_L00_001B8C80[];
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
/* SpawnState with an attachment parent, as func_L00_00414020 fills it. */
typedef struct ParentedSpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra, extra2;
    char *parent;
} ParentedSpawnState;
/* The record func_L00_00416F68 fills; func_L00_00417D70 reads kind as a mode and parent. */
typedef struct AttachedSpawnState {
    int life;
    int kind;
    char *parent;
} AttachedSpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;



extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

extern int func_00282978_5(char *handle);

extern void func_0029F338_2(char *object);

extern int func_002EDD78(char *handle);

extern void func_002E6EF8(char *callback, char *object);

extern void func_00310440(char *object);

extern void func_00320DE0(char *object, int a, char *b, char *c, char *d, char *e);

extern char ref_L00_00415A38_00[];

extern char ref_L00_00414350_00[];

extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern unsigned char *func_L00_0033FFB8(void *, void *, int);
extern char D_L00_001A8F20[] __attribute__((sda));
typedef struct { char pad[0x140]; float x, y; } CameraHead;
extern float func_00283CE0(int);
extern int func_00282948(void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00283098(void *, void *, void *);

/* One of the twenty-four 0xB0-byte records at D_L00_0025A920 (claimed by func_L00_00417A40,
   updated by func_L00_00417D70). Measured layout; field roles are inferred from those two. */
typedef struct {
    Vector out0;            /* 0x00: ang0 through the two angle helpers, times amp0 */
    Vector out1;            /* 0x10: the same for ang1 */
    Vector start;           /* 0x20: follows the owner's position */
    Vector point;           /* 0x30: blended between start and end */
    Vector end;             /* 0x40: keeps its offset from start */
    float ang0[3];          /* 0x50 */
    float rate0[3];         /* 0x5C */
    float amp0[3];          /* 0x68 */
    float ang1[3];          /* 0x74 */
    float rate1[3];         /* 0x80 */
    float amp1[3];          /* 0x8C */
    int release;            /* 0x98: timer, frees the record when it expires */
    char *owner;            /* 0x9C */
    int time;               /* 0xA0: timer */
    int duration;           /* 0xA4 */
    int started;            /* 0xA8 */
    int pad;                /* 0xAC */
} EffectRecord;

extern EffectRecord D_L00_0025A920[24];

extern char D_00189E20[];
extern char D_00188660[];
typedef union { unsigned char b[0x2600]; int i[0x980]; float f[0x980]; char *ptr[0x980]; } EffectHero;
typedef struct { char bytes[0x70]; } EffectReleaseSlot;
extern int func_00282978(void *);
extern void func_0029F338(char *);
extern float *func_002AB1F0(char *);
extern void func_L00_00413358(char *);
/* Preserve the object argument passed to the empty callback in retail. */
extern void func_L00_00414018_1(char *);
extern void func_002E59F8(int);
extern Vector128 D_L00_001BF220;
extern void func_L00_004173B0(char *);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L00_00417A40(char *, void *, int);
extern void func_L00_00417218(char *);
extern void func_L00_00417700(char *);
extern void func_L00_00417D70(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);


/* Updates the wave line effect (moby class 4501). It follows the hero and its target, and lets go of its sound when it stops. */
void func_L00_00413128(char *object)
{
    char *state = *(char **)(object + 0x68);
    char local[32];
    char *child;
    int code, index;
    float *childData;
    if (FastDecTimer(state + 0x1E) != 0) {
        MarkMobySpawned(object);
        return;
    }
    FastVecScale(local, ((EffectHero *)gHeroState)->ptr[2212] + 0xE0, 0.75f);
    FastVecAdd(object + 0x10, &((EffectHero *)gHeroState)->f[32], local);
    if (*(char **)(state + 0x20) != 0) {
        code = *(unsigned char *)(*(char **)(state + 0x20) + 0x20);
        if (code == 254)
            *(char **)(state + 0x20) = 0;
        else if (code == 253)
            *(char **)(state + 0x20) = 0;
        child = *(char **)(state + 0x20);
        if (child != 0) {
            qcopy(state + 0x30, child + 0x10);
            childData = GetMobyPrivateValue0(child);
            if (childData != 0) {
                FastVecScale(local + 16, *(char **)(state + 0x20) + 0xE0, childData[4]);
                FastVecAdd(state + 0x30, state + 0x30, local + 16);
            }
        }
    }
    if (*(unsigned char *)(object + 0x20) == 1) {
        func_L00_00414018_1(object);
        UpdateWaveLineEffect(object);
    } else {
        index = *(int *)(state + 0x18);
        if (index >= 0) {
            if (index != -1) {
                EffectReleaseSlot *entry = &((EffectReleaseSlot *)gSoundState)[index];
                if (*(char **)((char *)entry + 0x88) == object &&
                    *(unsigned char *)((char *)entry + 0x74) != 0)
                    StopSoundVoice(index);
            }
            *(int *)(state + 0x18) = -1;
        }
    }
}

/* Clear both entry tables and reset the record state. */
/* Clears the two point lists of the wave line effect and resets its counters. */
void func_L00_00413298(char *object)
{
    char *state = *(char **)(object + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        *(int *)(*(char **)(state + 0) + i * 16 + 0) = 0;
        *(int *)(*(char **)(state + 0) + i * 16 + 4) = 0;
        *(int *)(*(char **)(state + 0) + i * 16 + 8) = 0;
        *(float *)(*(char **)(state + 0) + i * 16 + 12) = 1.0f;
    }

    for (i = 0; i < 20; i++) {
        *(int *)(*(char **)(state + 4) + i * 16 + 0) = 0;
        *(int *)(*(char **)(state + 4) + i * 16 + 4) = 0;
        *(int *)(*(char **)(state + 4) + i * 16 + 8) = 0;
        *(float *)(*(char **)(state + 4) + i * 16 + 12) = 1.0f;
    }

    *(int *)(state + 0xC) = 0;
    *(short *)(state + 0x1C) = 6;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x8) = 0;
}

/* Empty callback that does nothing. */
void func_L00_00414018(void)
{
}

/* Creates an explosion effect (moby class 5020) that can be attached to a parent. It sets up the sizes and timers and shakes the camera when close. */
char *func_L00_00414020(float size, char *position, int trigger, int kind, int red, int green,
                        int blue, int enabled, int flags, int extra, int control, int extra2,
                        char *parent)
{
    Vector128 direction[1], up[1], attachment[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139c /* moby class 5020 */);
    ParentedSpawnState *state;
    SpawnObject *self;
    if (object != 0) {
        self = (SpawnObject *)object;
        *(unsigned char *)(object + 0x30) = 0xff;
        object[0x20] = 0;
        *(short *)(object + 0x32) = 0xff;
        state = (ParentedSpawnState *)self->state;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        FastVecSub(direction, D_L00_001B8C80 + 0x140, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        ComputeViewDirection(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        state->size = size;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->extra2 = extra2;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->control = control;
        state->flags = flags;
        state->parent = parent;
        qzero_nc(attachment);
        if (parent)
            TransformPointByMobyAttachment(object, parent, object + 0x10, (char *)attachment);
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (FastMathHelperA(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, D_L00_001B8C80 + 0x140) < 48.0f && trigger != 0) {
                char *manager = D_L00_001B8C80;
                *(int *)(manager + 0x16c) = 0;
                *(int *)(manager + 0x168) = 20;
                *(float *)(manager + 0x160) = 0.075f;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                if (1.5707964f - FastAngleHelper(FastVecDot(difference, D_L00_001B8C80 + 0x370)) < 0.45378566f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        SpawnExplosionBurstWithDrift(object, (char *)up, (char *)attachment);
    }
    return object;
}

/* Forwards the cached sub-object into the pair update when it is present, then releases the handle pair or re-arms the module callback. */
void func_L00_00414350(char *object)
{
    char *handle = *(char **)(object + 0x68);

    if (*(int *)(handle + 0x3C) != 0)
        func_00320DE0(object, *(int *)(handle + 0x3C), object + 0x10, object + 0xF0,
                      object + 0x10, object + 0xF0);

    if (func_002EDD78(handle) == 0) {
        func_002EDD78(handle + 4);
        func_002E6EF8(ref_L00_00414350_00, object);
    } else {
        func_00310440(object);
    }
}



/* Draws a flat square sprite that faces the camera, with an optional roll and a random wobble in its texture. */
void func_L00_00415210(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    InitQuadPacketState(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub((char *)&frame.row[0], (char *)(D_L00_001B8C80 + 0x140), (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = D_L00_001AA310;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            ProjectWorldToScreen((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (RandomIntBelow(1) == 0) {
                packet.uv[i][0] += RandomFloatRange(-jitter, jitter);
                packet.uv[i][1] += RandomFloatRange(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            ProjectWorldToScreen((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (RandomIntBelow(1) == 0) {
                packet.uv[i][0] += RandomFloatRange(-jitter, jitter);
                packet.uv[i][1] += RandomFloatRange(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    InitQuadPacketState(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}


/* Creates an explosion effect (moby class 5021). It sets up the sizes and timers and shakes the camera when close. */
char *func_L00_00415740(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139d /* moby class 5021 */);
    SpawnState *state;
    SpawnObject *self;
    char *camera;
    float angle;
    if (object != 0) {
        self = (SpawnObject *)object;
        state = self->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = D_L00_001B8C80 + 0x140;
        FastVecSub(direction, camera, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        ComputeViewDirection(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (FastMathHelperA(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                angle = FastAngleHelper(FastVecDot(difference, (char *)&D_L00_001B8C80 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        SpawnExplosionBurst_L00_2(object, (char *)up);
    }
    return object;
}


/* Releases the object's cached handle pair when free and otherwise re-arms the module's tick callback. */
void func_L00_00415A38(char *object)
{
    char *handle = *(char **)(object + 0x68);

    if (func_002EDD78(handle) == 0) {
        func_002EDD78(handle + 4);
        func_002E6EF8(ref_L00_00415A38_00, object);
    } else {
        func_00310440(object);
    }
}



/* Draws a flat square sprite that faces the camera, with an optional roll and a random wobble in its texture. */
void func_L00_00416A38(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    InitQuadPacketState(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub((char *)&frame.row[0], (char *)(D_L00_001B8C80 + 0x140), (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = D_L00_001AA310;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            ProjectWorldToScreen((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (RandomIntBelow(1) == 0) {
                packet.uv[i][0] += RandomFloatRange(-jitter, jitter);
                packet.uv[i][1] += RandomFloatRange(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            ProjectWorldToScreen((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (RandomIntBelow(1) == 0) {
                packet.uv[i][0] += RandomFloatRange(-jitter, jitter);
                packet.uv[i][1] += RandomFloatRange(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    InitQuadPacketState(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}


/* Creates a spark effect object (moby class 5022) that can be attached to a parent. */
char *func_L00_00416F68(Vector128 *position, int kind, char *parent)
{
    Vector128 direction[1], up[1];
    char *object = CreateMoby(0x139E /* moby class 5022 */);
    if (object != 0) {
        SpawnObject *self = (SpawnObject *)object;
        AttachedSpawnState *state = (AttachedSpawnState *)self->state;
        char *first = object + 0x10;
        char *second;
        char *third;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(first, position);
        *(float *)(object + 0x1c) = 1.0f;
        second = object + 0xc0;
        FastVecSub(direction, D_L00_001B8C80 + 0x140, first);
        vec_scale_to_length(direction, direction, 1.0f);
        ComputeViewDirection(first, (char *)up, 1);
        qcopy(second, direction);
        third = object + 0xd0;
        FastVecCross(third, second, up);
        vec_scale_to_length(third, third, 1.0f);
        FastVecCross(object + 0xe0, third, second);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        state->life = 60;
        state->kind = kind;
        state->parent = parent;
    }
    return object;
}


/* Spawns 25 particles around the object, each drifting away from the camera at a random angle. */
void func_L00_00417218(char *object)
{
    float spawn[8];
    float heading, angle, speed;
    float spread = 0.0f;
    int i;

    for (i = 24; i >= 0; i--) {
        heading = FastMatrixHelperA(((CameraHead *)D_L00_001B8C80)->x - *(float *)(object + 0x10),
                                ((CameraHead *)D_L00_001B8C80)->y - *(float *)(object + 0x14));
        speed = RandomSignedFloatRange(1.0f, 2.0f);
        FloatToInt(speed);
        spawn[0] = *(float *)(object + 0x10) + RandomSignedFloatRange(-0.25f, 0.25f);
        spawn[1] = *(float *)(object + 0x14) + RandomSignedFloatRange(-0.25f, 0.25f);
        spawn[2] = *(float *)(object + 0x18) + RandomSignedFloatRange(-0.25f, 0.25f);
        spread = 0.0f;
        angle = FastAddRotations(heading, RandomSignedFloatRange(spread, -1.5707965f));
        speed = 4.0f;
        spawn[4] = FastSinOrCosA(angle) * 0.016666668f * speed;
        spawn[5] = FastSinOrCosB(angle) * 0.016666668f * speed;
        spawn[6] = 0.075f;
        SpawnSpinningParticle_L00_2(spawn, D_L00_001A8F20, 300);
    }
}




/* Steps every record the object owns: jitters its start, moves start (and end with it) to the
   object's position or to an offset from its parent, advances the two angle triples (faster
   while the timer runs), blends point between start and end, and releases the record when
   its release timer expires after the main timer. */
void func_L00_00417D70(char *object)
{
    Vector delta, transformed, offset;
    char *state = *(char **)(object + 0x68);
    int i;

    for (i = 0; i < 24; ++i) {
        EffectRecord *record;
        float ratio, blend;

        if (gSparkRecords_L00[i].owner != object)
            continue;
        record = &gSparkRecords_L00[i];
        record->start.v[0] += RandomFloatRange(-0.1f, 0.1f);
        record->start.v[1] += RandomFloatRange(-0.1f, 0.1f);
        record->start.v[2] += RandomFloatRange(-0.1f, 0.1f);
        FastVecSub(&delta, &record->end, &record->start);
        if (*(int *)(state + 4) == 0) {
            qcopy(&record->start, object + 0x10);
        } else {
            offset.word = 0;
            offset.v[0] = -0.15f;
            offset.v[1] = -0.8f;
            offset.v[3] = 1.0f;
            matrix_mul_vec3(&transformed, &offset, *(char **)(state + 8) + 0xC0);
            FastVecAdd(&transformed, &transformed, *(char **)(state + 8) + 0x10);
            qcopy(&record->start, &transformed);
        }
        FastVecAdd(&record->end, &record->start, &delta);
        if (record->time != 0) {
            record->ang0[0] = FastAddRotations(record->ang0[0], record->rate0[0] * 100.0f);
            record->ang0[1] = FastAddRotations(record->ang0[1], record->rate0[1] * 100.0f);
            record->ang0[2] = FastAddRotations(record->ang0[2], record->rate0[2] * 100.0f);
            record->ang1[0] = FastAddRotations(record->ang1[0], record->rate1[0] * 100.0f);
            record->ang1[1] = FastAddRotations(record->ang1[1], record->rate1[1] * 100.0f);
            record->ang1[2] = FastAddRotations(record->ang1[2], record->rate1[2] * 100.0f);
        } else {
            record->ang0[0] = FastAddRotations(record->ang0[0], record->rate0[0] * 50.0f);
            record->ang0[1] = FastAddRotations(record->ang0[1], record->rate0[1] * 50.0f);
            record->ang0[2] = FastAddRotations(record->ang0[2], record->rate0[2] * 50.0f);
            record->ang1[0] = FastAddRotations(record->ang1[0], record->rate1[0] * 50.0f);
            record->ang1[1] = FastAddRotations(record->ang1[1], record->rate1[1] * 50.0f);
            record->ang1[2] = FastAddRotations(record->ang1[2], record->rate1[2] * 50.0f);
        }
        record->out0.v[0] = FastSinOrCosA(record->ang0[0]) * record->amp0[0];
        record->out0.v[1] = FastSinOrCosB(record->ang0[1]) * record->amp0[1];
        record->out0.v[2] = -FastSinOrCosB(record->ang0[2]) * record->amp0[2];
        record->out1.v[0] = FastSinOrCosA(record->ang1[0]) * record->amp1[0];
        record->out1.v[1] = FastSinOrCosB(record->ang1[1]) * record->amp1[1];
        record->out1.v[2] = -FastSinOrCosB(record->ang1[2]) * record->amp1[2];
        ratio = IntToFloat(record->time);
        ratio /= IntToFloat(record->duration);
        blend = 1.0f - ratio;
        if (*(int *)(state + 4) == 0)
            lerp_vector(&record->point, &record->start, &record->end, blend);
        else
            lerp_vector(&record->point, &record->start, &record->end, 0.75f);
        if (FastFloatHelperD(&record->time)) {
            if (record->started == 0)
                record->started = 1;
            if (FastFloatHelperD(&record->release))
                record->owner = 0;
        }
    }
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_00418140(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_004181A8(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}


/* Creates a blue explosion effect (moby class 5023). It sets up the sizes and timers and shakes the camera when close. */
char *func_L00_00418730(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139f /* moby class 5023 */);
    SpawnState *state;
    SpawnObject *self;
    char *camera;
    float angle;
    if (object != 0) {
        self = (SpawnObject *)object;
        state = self->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = D_L00_001B8C80 + 0x140;
        FastVecSub(direction, camera, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        ComputeViewDirection(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (FastMathHelperA(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                angle = FastAngleHelper(FastVecDot(difference, (char *)&D_L00_001B8C80 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        SpawnBurstParticles(object, (char *)up);
    }
    return object;
}


/* Tests the handle cached in the object and, while the handle reports itself already released, drops the next sub-handle, otherwise runs the object's destroy helper. */
void func_L00_00418A28(char *object)
{
    char *handle = *(char **)(object + 104);

    if (func_00282978_5(handle) == 0)
        func_00282978_5(handle + 4);
    else
        func_0029F338_2(object);
}

/* func_L00_00418A80 is defined in L00_00418A80-g8.c. */

/* Runs the destroy helper once the child's status goes negative; otherwise re-arms the module callback
   when the timer at 0x3C is zero or the sphere test accepts the record at 0x30. */
void func_L00_004195C8(char *object)
{
    char *handle = *(char **)(object + 0x68);
    char *child = *(char **)(handle + 0x44);

    if (child != 0 && *(signed char *)(child + 0x20) < 0) {
        func_00310440(object);
    } else if (*(float *)(handle + 0x3C) == 0.0f ||
               FastMathHelperA(handle + 0x30, (float)*(short *)(object + 0x32)) != 0) {
        func_002E6EF8(ref_L00_004195C8_00, object);
    }
}

/* func_L00_00419668 is in L00_00419668-dbg.c. */


/* Marks the object as started and raises the high bit of its flag word, once. */
void func_L00_00419B58(char *object)
{
    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x20) = 1;
        *(unsigned short *)(object + 0x34) |= 0x800;
    }
}

/* func_L00_00419C98 is defined in L00_00419C98-g8.c. */

/* func_L00_0041A490 is defined in L00_0041A490-dbg.c. */

