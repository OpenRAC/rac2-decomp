#include "include_asm.h"
#include "common.h"

/* A body whose retail bytes address its global through $gp in ordinary flow: the assembler
   only selects that form when the back end emits the .extern size directive, which the
   pinned profile does at -G8 (see docs/COMPILER-NOTES.md). */
extern unsigned char *func_0029EFD0(int size);

extern unsigned char *D_L00_001B0A20 __attribute__((sda));

unsigned char *func_L00_003F8DC8(int unused)
{
    unsigned char *p = func_0029EFD0(0xD04);

    if (p != 0) {
        unsigned int v = 0xFF;

        D_L00_001B0A20 = p;
        *(unsigned short *)(p + 0x32) = v;
        p[0x20] = 1;
        p[0x30] = v;
    }
    return p;
}

/* Per-frame update of the player's gadget table: it walks the records of one table
   entry, scales each record's pair of floats and asks the slot manager to refresh
   them, then folds the two level globals into the table's offset. */

extern float D_L00_001B096C __attribute__((sda));

extern float D_L00_001B0970 __attribute__((sda));

extern char *func_L00_0032A088(int a0, int a1);

extern float func_00283B98(float a0, float a1);

extern void func_L00_003F5870(char *rec, int index);

extern int func_00282978(char *a0);

int func_L00_003F59F0(char *a0)
{
    char *state;
    char *table;
    char *base;
    char *rec;
    int index;
    int count;
    int i = 0;
    float value;

    state = *(char **)(a0 + 0x68);
    table = func_L00_0032A088(0xC04, *(short *)(state + 0x1A));
    index = *(short *)(state + 0x18);
    base = *(char **)(table + index * 4);
    count = *(short *)(state + 0x20);
    if (count > 0) {
        rec = base;
        do {
            *(float *)(rec + 0x20) = func_00283B98(*(float *)(rec + 0x20), *(float *)(rec + 0x28));
            func_L00_003F5870(base, i);
            rec += 0x30;
            i++;
        } while (i < count);
    }
    value = D_L00_001B096C;
    if (value > 7.0f) {
        D_L00_001B096C = 0.0f;
    } else if (value < -7.0f) {
        D_L00_001B096C = 0.0f;
    }
    D_L00_001B096C = D_L00_001B096C - D_L00_001B0970;
    if (D_L00_001B096C <= -4.0f) {
        D_L00_001B096C = D_L00_001B096C + 4.0f;
    }
    return func_00282978(state + 0x22) == 0;
}

/* func_L00_003EFA98 and func_L00_003EFD00: two 64-face quad renderers. Each builds a textured
   packet from the level's $gp tuning words, scales a diagonal matrix by the object's size, and
   per face takes four corners and UVs from the face table, transforms them through the matrix,
   the object's basis (0xC0) and position (0x10) plus an offset, and draws the quad. */

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern int D_L00_001B0870 __attribute__((sda));
extern int D_L00_001B0874 __attribute__((sda));
extern int D_L00_001B0878 __attribute__((sda));
extern int D_L00_001B087C __attribute__((sda));
extern int D_L00_001B0880 __attribute__((sda));
extern int D_L00_001B0884 __attribute__((sda));
extern int D_L00_001B0888 __attribute__((sda));
extern float D_L00_001B088C __attribute__((sda));
extern Vector D_L00_0029AF40[];
extern short D_L00_0029B440[][4][2];
extern float D_L00_0029B840[][2];
extern long long func_0027C878(int id);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_002AFFD8(char *, char *, int);
extern void func_00280B90(void *packet, void *frame, int mode);

void func_L00_003EFA98(char *object)
{
    RenderPacket packet;
    Vector matrix[3];
    Vector offset;
    char *state = *(char **)(object + 0x68);
    Vector *origin;
    float *u_base, *v_base;
    int face, corner;
    unsigned int color;
    long flags;
    float quarter;

    packet.f78 = func_0027C878(D_L00_001B0884);
    flags = (long)D_L00_001B0870;
    flags |= (long)D_L00_001B0874 << 2;
    flags |= (long)D_L00_001B0878 << 4;
    flags |= (long)D_L00_001B087C << 6;
    flags |= (long)D_L00_001B0880 << 32;
    packet.f80 = 0xFF9000000260L;
    packet.flags = flags;
    packet.f70 = 0;
    quarter = 0.25f;
    func_00282C88(&matrix[0]);
    func_00282C88(&matrix[1]);
    func_00282C88(&matrix[2]);
    matrix[0].v[0] = *(float *)(state + 0x10) + *(float *)(state + 0x10);
    matrix[1].v[1] = *(float *)(state + 0x10) + *(float *)(state + 0x10);
    matrix[2].v[2] = *(float *)(state + 0x10) * quarter;
    color = D_L00_001B0888 + (*(unsigned int *)(state + 0x24) << 24);
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    func_002AFFD8(object + 0x10, (char *)&offset, 1);
    func_00282D30(&offset, &offset, quarter);
    u_base = &packet.uv[0][0];
    v_base = &packet.uv[0][1];
    for (face = 0; face < 64; face++) {
        origin = (Vector *)(object + 0x10);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029AF40[D_L00_0029B440[face][corner][0]];
            int uv = D_L00_0029B440[face][corner][1];

            func_00282D30(&packet.vertex[corner], position, D_L00_001B088C);
            u_base[corner * 2] = D_L00_0029B840[uv][0];
            v_base[corner * 2] = D_L00_0029B840[uv][1];
            func_00283098(&packet.vertex[corner], &packet.vertex[corner], matrix);
            func_00283098(&packet.vertex[corner], &packet.vertex[corner], object + 0xC0);
            func_00282CC0(&packet.vertex[corner], &packet.vertex[corner], origin);
            func_00282CC0(&packet.vertex[corner], &packet.vertex[corner], &offset);
        }
        func_00280B90(&packet, 0, 0);
    }
}

void func_L00_003EFD00(char *object)
{
    RenderPacket packet;
    Vector matrix[3];
    Vector offset;
    char *state = *(char **)(object + 0x68);
    Vector *origin;
    float *u_base, *v_base;
    int face, corner;
    unsigned int color;
    long flags;

    packet.f78 = func_0027C878(D_L00_001B0884);
    flags = (long)D_L00_001B0870;
    flags |= (long)D_L00_001B0874 << 2;
    flags |= (long)D_L00_001B0878 << 4;
    flags |= (long)D_L00_001B087C << 6;
    flags |= (long)D_L00_001B0880 << 32;
    packet.f80 = 0xFF9000000260L;
    packet.flags = flags;
    packet.f70 = 0;
    func_00282C88(&matrix[0]);
    func_00282C88(&matrix[1]);
    func_00282C88(&matrix[2]);
    matrix[0].v[0] = *(float *)(state + 0x10);
    matrix[1].v[1] = *(float *)(state + 0x10);
    matrix[2].v[2] = *(float *)(state + 0x10) * 0.125f;
    color = D_L00_001B0888 + (*(unsigned int *)(state + 0x24) << 24);
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    func_002AFFD8(object + 0x10, (char *)&offset, 1);
    func_00282D30(&offset, &offset, 0.25f);
    u_base = &packet.uv[0][0];
    v_base = &packet.uv[0][1];
    for (face = 0; face < 64; face++) {
        origin = (Vector *)(object + 0x10);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029AF40[D_L00_0029B440[face][corner][0]];
            int uv = D_L00_0029B440[face][corner][1];

            func_00282D30(&packet.vertex[corner], position, D_L00_001B088C);
            u_base[corner * 2] = D_L00_0029B840[uv][0];
            v_base[corner * 2] = D_L00_0029B840[uv][1];
            func_00283098(&packet.vertex[corner], &packet.vertex[corner], matrix);
            func_00283098(&packet.vertex[corner], &packet.vertex[corner], object + 0xC0);
            func_00282CC0(&packet.vertex[corner], &packet.vertex[corner], origin);
            func_00282CC0(&packet.vertex[corner], &packet.vertex[corner], &offset);
        }
        func_00280B90(&packet, 0, 0);
    }
}

extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern float D_L00_001B0940 __attribute__((sda));
extern float D_L00_001B0944 __attribute__((sda));
extern float D_L00_001B0948 __attribute__((sda));
extern float D_L00_001B094C __attribute__((sda));
extern float D_L00_001B0950 __attribute__((sda));
extern float D_L00_001B0954 __attribute__((sda));

/* One 0x30-byte joint of the chain func_L00_003F5870 lays out. */
typedef struct {
    float offset[4];
    float position[4];
    float angle;
    float length;
    float f28;
    float f2c;
} L00Joint;

/* Places one joint of a table entry's chain at `position`: its angle, length and two
   rates come from level tuning values, then func_L00_003F5870 lays out its offset and
   the entry's joint count advances. The record offset is computed once and added to the
   reloaded chain pointer at every store, as retail's addu order shows. */
void func_L00_003F5750(char *object, char *position)
{
    char *state = *(char **)(object + 0x68);
    char **table = (char **)func_L00_0032A088(0xc04, *(short *)(state + 0x1a));
    short index = *(short *)(state + 0x20);
    char **entry;
    int offset = index * 0x30;
    entry = (char **)((*(short *)(state + 0x18) << 2) + (int)table);
    qcopy(((L00Joint *)(offset + (int)*entry))->position, position);
    ((L00Joint *)(offset + (int)*entry))->angle = func_002ABB18(func_00283CE0(index) * 0.017453294f * D_L00_001B0948);
    ((L00Joint *)(offset + (int)*entry))->f28 = func_002A7878(D_L00_001B0940, D_L00_001B0944) * 0.017453294f;
    ((L00Joint *)(offset + (int)*entry))->length = D_L00_001B094C;
    ((L00Joint *)(offset + (int)*entry))->f2c = func_002A78D8(D_L00_001B0950, D_L00_001B0954) * 0.016666668f;
    func_L00_003F5870(*entry, index);
    (*(unsigned short *)(state + 0x20))++;
}

/* BEGIN v2340 func_L00_003F0CC8 */

typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Vector impulse;
    int owner, flags;
    unsigned char enabled, kind;
    unsigned short object_class;
    float damage;
    int active;
} DamageRequest;

typedef struct {
    int pending, timer;
    char *first, *second;
    int light;
    float radius;
} EffectState;
typedef struct {
    int reserved[2];
    float intensity;
    int flags;
    Vector position;
} Light;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; QuadWord q[0x260]; } Hero;
extern u8 D_00189E20[];
extern Vector D_L00_001B8DC0, D_L00_001BF220;
extern float D_L00_00252F60[137][2];
extern char *D_L00_001C3280[];
extern Light D_L00_001C6F40[];
extern int D_L00_001B08D0 __attribute__((sda));
extern float func_002A7940(void);
extern float func_00283CE0(int);
extern float func_002A7790(float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CF0(Vector *, const Vector *, const Vector *);
extern void func_00282F20(Vector *, const Vector *, float);
extern int func_002761F8(Vector *, Vector *, int, char *, int);
extern void func_0032B598(char *, Vector *, int);
extern void func_0032ABC0(char *);
extern int func_00282948(int *);
extern int func_00277F48(Vector *, int, char *, DamageRequest *, float);
extern void func_002A8C00(char *, int, int, float, Quad16 *);
extern void func_002A8E20(char *, DamageRequest *);
/* Retail passes the object in $a0 although the matched definition in src/game/00327038.c
   takes no parameters, so this caller declares it without a prototype. */
extern void func_0032A978();
extern void func_0032AA30(void *);
extern void func_0029F338(void *);
extern void func_00291450(int);
extern float func_00283180(float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002833F0(Vector *, const Vector *);
extern void func_0032ACF0(int);
extern void func_0032AF50(s8 *);
extern void func_0032B7D0(char *);
/* The binder: func_L00_002E6EF8 in most programs, a per-level variant in levels 08, 09, 19 and 30. */
extern void ref_L00_003F0CC8_00(void (*)(void *), void *);
extern void func_0032B190(void *);

void func_L00_003F0CC8(char *object)
{
    Vector point;
    DamageRequest request;
    DamageRequest *req;
    EffectState *state = *(EffectState **)(object + 0x68);
    char **hit;
    char *satellite;
    Light *light;
    int count, remaining, i;
    float progress, first_angle, second_angle;

    qcopy(object + 0x10, ((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x10);
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 1;
        state->timer = 60;
        state->radius = 0.0f;
        for (i = 0; i < 137; i++) {
            D_L00_00252F60[i][0] = func_002A7940();
            D_L00_00252F60[i][1] = func_002A7940();
        }
    case 1:
        *(unsigned char *)(object + 0x20) = 2;
    case 2:
        progress = func_00283CE0(state->timer);
        progress /= func_00283CE0(60);
        state->radius = func_002A7790(1.0f - progress) * 15.0f;
        if (state->timer % 3 == 0) {
            first_angle = func_002A7940();
            second_angle = func_002A7940();
            func_002AF000(point.v, state->radius, first_angle, second_angle);
            func_00282CC0(&point, &point, (Vector *)&((Hero *)D_00189E20)->b[0xE0]);
            if (func_002761F8((Vector *)&((Hero *)D_00189E20)->b[0xE0], &point, 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], 0) != 0)
                qcopy(&point, &D_L00_001BF220);
            func_0032B598(object, &point, 10);
        }
        if (state->timer < 10 && (state->timer & 7) == 0)
            func_0032ABC0(object);
        if (func_00282948(&state->timer) != 0) {
            state->timer = 120;
            *(unsigned char *)(object + 0x20) = 3;
            count = func_00277F48((Vector *)&((Hero *)D_00189E20)->b[0xE0], 0, object, 0, 15.0f);
            if (count > 0) {
                hit = D_L00_001C3280;
                remaining = count;
                do {
                    req = &request;
                    if ((*(unsigned long long *)(*hit + 0x30) & 0x500000000000ULL) != 0 &&
                        *hit != ((Hero *)D_00189E20)->ptr[0x2290 / 4] && *(short *)(*hit + 0xaa) != 0xce7 &&
                        *(short *)(*hit + 0xaa) != 0xbb8) {
                        func_00282CF0(&point, (Vector *)(*hit + 0x10), (Vector *)&((Hero *)D_00189E20)->b[0xE0]);
                        func_00282F20(&point, &point, 1.0f);
                        /* The incoming request impulse is not initialized in retail. */
                        func_00282F20(&req->impulse, &req->impulse, 1.0f);
                        func_002A8C00((char *)req, (int)object, 0x830000, 30.0f, (Quad16 *)&point);
                        request.impulse.word = point.word;
                        request.active = 1;
                        request.impulse.v[3] = 5627.9248f;
                        request.enabled = 5;
                        request.kind = 3;
                        request.object_class = *(unsigned short *)(*hit + 0xaa);
                        func_002A8E20(*hit, req);
                    }
                    ++hit;
                } while (--remaining != 0);
            }
            func_0032A978(object);
        }
        break;
    case 3:
        if ((state->timer & 7) == 0) func_0032ABC0(object);
        func_00282948(&state->timer);
        func_0032AA30(object);
        if (state->timer == 40) *(unsigned char *)(object + 0x20) = 4;
        break;
    case 4:
        if (func_00282948(&state->timer) != 0 && state->pending == 0) {
            if (state->first != 0) func_0029F338(state->first);
            if (state->second != 0) func_0029F338(state->second);
            if (state->light != -1) func_00291450(state->light);
            D_L00_001B08D0 = 0;
            func_0029F338(object);
            return;
        }
        break;
    }
    progress = func_00283CE0(state->timer) / func_00283CE0(120);
    progress = 1.0f - progress;
    progress *= 6.2831855f;
    progress -= 3.1415927f;
    progress = func_00283180(progress);
    progress = (progress + 1.0f) * 0.5f;
    if (state->first != 0) {
        **(int **)(state->first + 0x68) = func_00283CF0(progress * 32.0f);
        *(float *)(state->first + 0xf8) = func_00283B98(*(float *)(state->first + 0xf8), 0.052359887f);
        satellite = state->first;
        func_002833F0((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->first + 0xc0) *= 0.5f;
        *(float *)(state->first + 0xd4) *= 0.5f;
        *(float *)(state->first + 0xe8) = progress * 1.5f;
        qcopy(state->first + 0x10, ((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x10);
    }
    if (state->second != 0) {
        **(int **)(state->second + 0x68) = func_00283CF0(progress * 32.0f);
        *(float *)(state->second + 0xf8) = func_00283BE0(*(float *)(state->second + 0xf8), 0.052359887f);
        satellite = state->second;
        func_002833F0((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->second + 0xe8) = progress;
        qcopy(state->second + 0x10, ((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x10);
    }
    if (state->light != -1) {
        light = &D_L00_001C6F40[state->light];
        func_00282F20(&point, (Vector *)&((Hero *)D_00189E20)->b[0x2A0], 0.5f);
        func_00282CC0(&light->position, (Vector *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x10), &point);
        func_00282CF0(&point, &D_L00_001B8DC0, &light->position);
        func_00282F20(&point, &point, 0.15f);
        func_00282CC0(&light->position, &light->position, &point);
        light->intensity = progress;
        light->position.v[3] = 5.0f;
        light->flags = 0;
    }
    func_0032ACF0((int)object);
    func_0032AF50((s8 *)object);
    func_0032B7D0(object);
    ref_L00_003F0CC8_00(func_0032B190, object);
}
