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


void func_L00_00413128(char *object)
{
    char *state = *(char **)(object + 0x68);
    char local[32];
    char *child;
    int code, index;
    float *value;
    if (func_00282978(state + 0x1E) != 0) {
        func_0029F338(object);
        return;
    }
    func_00282D30(local, ((EffectHero *)D_00189E20)->ptr[2212] + 0xE0, 0.75f);
    func_00282CC0(object + 0x10, &((EffectHero *)D_00189E20)->f[32], local);
    if (*(char **)(state + 0x20) != 0) {
        code = *(unsigned char *)(*(char **)(state + 0x20) + 0x20);
        if (code == 254)
            *(char **)(state + 0x20) = 0;
        else if (code == 253)
            *(char **)(state + 0x20) = 0;
        child = *(char **)(state + 0x20);
        if (child != 0) {
            qcopy(state + 0x30, child + 0x10);
            value = func_002AB1F0(child);
            if (value != 0) {
                func_00282D30(local + 16, *(char **)(state + 0x20) + 0xE0, value[4]);
                func_00282CC0(state + 0x30, state + 0x30, local + 16);
            }
        }
    }
    if (*(unsigned char *)(object + 0x20) == 1) {
        func_L00_00414018_1(object);
        func_L00_00413358(object);
    } else {
        index = *(int *)(state + 0x18);
        if (index >= 0) {
            if (index != -1) {
                EffectReleaseSlot *entry = &((EffectReleaseSlot *)D_00188660)[index];
                if (*(char **)((char *)entry + 0x88) == object &&
                    *(unsigned char *)((char *)entry + 0x74) != 0)
                    func_002E59F8(index);
            }
            *(int *)(state + 0x18) = -1;
        }
    }
}

/* Clear both entry tables and reset the record state. */
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

INCLUDE_ASM("asm/levels", func_L00_00413358);



INCLUDE_ASM("asm/levels", func_L00_00413918);

void func_L00_00414018(void)
{
}

char *func_L00_00414020(float size, char *position, int trigger, int kind, int red, int green,
                        int blue, int enabled, int flags, int extra, int control, int extra2,
                        char *parent)
{
    Vector128 direction[1], up[1], attachment[1], sphere[1], difference[1];
    char *object = func_0029EFD0(0x139c);
    ParentedSpawnState *state;
    SpawnObject *m;
    if (object != 0) {
        m = (SpawnObject *)object;
        *(unsigned char *)(object + 0x30) = 0xff;
        object[0x20] = 0;
        *(short *)(object + 0x32) = 0xff;
        state = (ParentedSpawnState *)m->state;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        func_00282CF0(direction, D_L00_001B8C80 + 0x140, object + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        func_00282DD8(object + 0xd0, object + 0xc0, up);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
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
            func_002AD330(object, parent, object + 0x10, (char *)attachment);
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (func_00282E48(position, D_L00_001B8C80 + 0x140) < 48.0f && trigger != 0) {
                char *manager = D_L00_001B8C80;
                *(int *)(manager + 0x16c) = 0;
                *(int *)(manager + 0x168) = 20;
                *(float *)(manager + 0x160) = 0.075f;
            }
            if (state->flags != 0) {
                func_00282CF0(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                func_00282F20(difference, difference, 1.0f);
                if (1.5707964f - func_002831B0(func_00282DB0(difference, D_L00_001B8C80 + 0x370)) < 0.45378566f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        func_L00_00414540(object, (char *)up, (char *)attachment);
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

    func_00281DE8(&packet, texture, 1, 0x80);
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
    func_00282CF0((char *)&frame.row[0], (char *)(D_L00_001B8C80 + 0x140), (char *)&frame.position);
    func_00282F20((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    func_00282DD8((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    func_00282F20((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    func_00282DD8((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        func_002833F0(scratch.u.rotation, &scratch.angles);
        func_00283738(frame.row, frame.row, scratch.u.rotation);
    }
    func_00282D30(&scratch.angles, &frame.row[0], offset);
    func_00282CC0(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = D_L00_001AA310;
        count = 3;
        do {
            func_00282D30(vertex, corner, size);
            ++corner;
            --count;
            func_002830C0(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    func_002FC560(0x47, 0x31001ULL);
    func_00280B90((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                func_00282CC0(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        func_00282D30(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            func_00282CF0((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            func_00282D30(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            func_00282CC0(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            func_0027C768((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            func_0027C768((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    func_00281DE8(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    func_002FC560(0x47, 0x33001ULL);
    func_00280B90((char *)&packet, 0, 0);
    func_002FC560(0x47, 0x5360bULL);
}


char *func_L00_00415740(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = func_0029EFD0(0x139d);
    SpawnState *state;
    SpawnObject *m;
    char *camera;
    float angle;
    if (object != 0) {
        m = (SpawnObject *)object;
        state = m->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = D_L00_001B8C80 + 0x140;
        func_00282CF0(direction, camera, object + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        func_00282DD8(object + 0xd0, object + 0xc0, up);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
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
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (func_00282E48(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                func_00282CF0(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                func_00282F20(difference, difference, 1.0f);
                angle = func_002831B0(func_00282DB0(difference, (char *)&D_L00_001B8C80 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        func_L00_00415DE8(object, (char *)up);
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

    func_00281DE8(&packet, texture, 1, 0x80);
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
    func_00282CF0((char *)&frame.row[0], (char *)(D_L00_001B8C80 + 0x140), (char *)&frame.position);
    func_00282F20((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    func_00282DD8((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    func_00282F20((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    func_00282DD8((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        func_002833F0(scratch.u.rotation, &scratch.angles);
        func_00283738(frame.row, frame.row, scratch.u.rotation);
    }
    func_00282D30(&scratch.angles, &frame.row[0], offset);
    func_00282CC0(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = D_L00_001AA310;
        count = 3;
        do {
            func_00282D30(vertex, corner, size);
            ++corner;
            --count;
            func_002830C0(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    func_002FC560(0x47, 0x31001ULL);
    func_00280B90((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                func_00282CC0(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        func_00282D30(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            func_00282CF0((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            func_00282D30(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            func_00282CC0(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            func_0027C768((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            func_0027C768((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    func_00281DE8(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    func_002FC560(0x47, 0x33001ULL);
    func_00280B90((char *)&packet, 0, 0);
    func_002FC560(0x47, 0x5360bULL);
}


char *func_L00_00416F68(Vector128 *position, int kind, char *parent)
{
    Vector128 direction[1], up[1];
    char *object = func_0029EFD0(0x139E);
    if (object != 0) {
        SpawnObject *m = (SpawnObject *)object;
        AttachedSpawnState *state = (AttachedSpawnState *)m->state;
        char *first = object + 0x10;
        char *second;
        char *third;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(first, position);
        *(float *)(object + 0x1c) = 1.0f;
        second = object + 0xc0;
        func_00282CF0(direction, D_L00_001B8C80 + 0x140, first);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(first, (char *)up, 1);
        qcopy(second, direction);
        third = object + 0xd0;
        func_00282DD8(third, second, up);
        func_00282F20(third, third, 1.0f);
        func_00282DD8(object + 0xe0, third, second);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
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
        heading = func_00283248(((CameraHead *)D_L00_001B8C80)->x - *(float *)(object + 0x10),
                                ((CameraHead *)D_L00_001B8C80)->y - *(float *)(object + 0x14));
        speed = func_002A78D8(1.0f, 2.0f);
        func_00283CF0(speed);
        spawn[0] = *(float *)(object + 0x10) + func_002A78D8(-0.25f, 0.25f);
        spawn[1] = *(float *)(object + 0x14) + func_002A78D8(-0.25f, 0.25f);
        spawn[2] = *(float *)(object + 0x18) + func_002A78D8(-0.25f, 0.25f);
        spread = 0.0f;
        angle = func_00283B98(heading, func_002A78D8(spread, -1.5707965f));
        speed = 4.0f;
        spawn[4] = func_00283180(angle) * 0.016666668f * speed;
        spawn[5] = func_00283198(angle) * 0.016666668f * speed;
        spawn[6] = 0.075f;
        func_L00_0033FFB8(spawn, D_L00_001A8F20, 300);
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
        EffectRecord *p;
        float ratio, blend;

        if (D_L00_0025A920[i].owner != object)
            continue;
        p = &D_L00_0025A920[i];
        p->start.v[0] += func_002A7878(-0.1f, 0.1f);
        p->start.v[1] += func_002A7878(-0.1f, 0.1f);
        p->start.v[2] += func_002A7878(-0.1f, 0.1f);
        func_00282CF0(&delta, &p->end, &p->start);
        if (*(int *)(state + 4) == 0) {
            qcopy(&p->start, object + 0x10);
        } else {
            offset.word = 0;
            offset.v[0] = -0.15f;
            offset.v[1] = -0.8f;
            offset.v[3] = 1.0f;
            func_00283098(&transformed, &offset, *(char **)(state + 8) + 0xC0);
            func_00282CC0(&transformed, &transformed, *(char **)(state + 8) + 0x10);
            qcopy(&p->start, &transformed);
        }
        func_00282CC0(&p->end, &p->start, &delta);
        if (p->time != 0) {
            p->ang0[0] = func_00283B98(p->ang0[0], p->rate0[0] * 100.0f);
            p->ang0[1] = func_00283B98(p->ang0[1], p->rate0[1] * 100.0f);
            p->ang0[2] = func_00283B98(p->ang0[2], p->rate0[2] * 100.0f);
            p->ang1[0] = func_00283B98(p->ang1[0], p->rate1[0] * 100.0f);
            p->ang1[1] = func_00283B98(p->ang1[1], p->rate1[1] * 100.0f);
            p->ang1[2] = func_00283B98(p->ang1[2], p->rate1[2] * 100.0f);
        } else {
            p->ang0[0] = func_00283B98(p->ang0[0], p->rate0[0] * 50.0f);
            p->ang0[1] = func_00283B98(p->ang0[1], p->rate0[1] * 50.0f);
            p->ang0[2] = func_00283B98(p->ang0[2], p->rate0[2] * 50.0f);
            p->ang1[0] = func_00283B98(p->ang1[0], p->rate1[0] * 50.0f);
            p->ang1[1] = func_00283B98(p->ang1[1], p->rate1[1] * 50.0f);
            p->ang1[2] = func_00283B98(p->ang1[2], p->rate1[2] * 50.0f);
        }
        p->out0.v[0] = func_00283180(p->ang0[0]) * p->amp0[0];
        p->out0.v[1] = func_00283198(p->ang0[1]) * p->amp0[1];
        p->out0.v[2] = -func_00283198(p->ang0[2]) * p->amp0[2];
        p->out1.v[0] = func_00283180(p->ang1[0]) * p->amp1[0];
        p->out1.v[1] = func_00283198(p->ang1[1]) * p->amp1[1];
        p->out1.v[2] = -func_00283198(p->ang1[2]) * p->amp1[2];
        ratio = func_00283CE0(p->time);
        ratio /= func_00283CE0(p->duration);
        blend = 1.0f - ratio;
        if (*(int *)(state + 4) == 0)
            func_00282D08(&p->point, &p->start, &p->end, blend);
        else
            func_00282D08(&p->point, &p->start, &p->end, 0.75f);
        if (func_00282948(&p->time)) {
            if (p->started == 0)
                p->started = 1;
            if (func_00282948(&p->release))
                p->owner = 0;
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
void func_L00_004181A8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

INCLUDE_ASM("asm/levels", func_L00_00418230);

char *func_L00_00418730(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = func_0029EFD0(0x139f);
    SpawnState *state;
    SpawnObject *m;
    char *camera;
    float angle;
    if (object != 0) {
        m = (SpawnObject *)object;
        state = m->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = D_L00_001B8C80 + 0x140;
        func_00282CF0(direction, camera, object + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        func_00282DD8(object + 0xd0, object + 0xc0, up);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
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
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (func_00282E48(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                func_00282CF0(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                func_00282F20(difference, difference, 1.0f);
                angle = func_002831B0(func_00282DB0(difference, (char *)&D_L00_001B8C80 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        func_L00_00418A80(object, (char *)up);
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
               func_00283DB8(handle + 0x30, (float)*(short *)(object + 0x32)) != 0) {
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

INCLUDE_ASM("asm/levels", func_L00_0041A5C0);
