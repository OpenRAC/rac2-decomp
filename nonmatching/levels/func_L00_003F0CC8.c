/* func_L00_003F0CC8 (1592 B, 27 places). Opus closer g1, 1 November 2026: 3 rows off, profile
 * -O2 -G8 -ffunction-sections. Left: `addiu s0,sp,0x10` comes after the 0x500000000000 mask's
 * ori/dsll in the hit loop's preheader; retail has it first. A pointer local in the loop body and
 * before the loop did not move it. The body follows func_L00_003E4BF0's relatives: an indexed
 * angle loop, `remaining = count` before the do/while, `progress` from one divide statement.
 * The retail read of the request impulse before its first fill is kept. */
/* GPT-6.1 Sol (high effort), bounded retry, 29 October 2026; not linked.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * USA v1.01 and USA v2.00: 1592/1592 bytes, 0/27 placements each.
 * In level 00, 69 non-relocated words differ; relocations are not included in
 * that diagnostic count. Equal size is not a match and no link credit is claimed.
 * The earlier 1588-byte draft reproduced. Writing active before the remaining
 * request fields hoists its 1 as retail does. A TI impulse assignment and
 * explicit interpolation steps reach retail size, but also hoist enabled=5
 * instead of the mask. Count copy, loop constant selection/registers, request
 * copy scheduling and FP allocation remain different. The initial state switch
 * and angle-table loop have scheduling differences as well.
 * Indexed/guarded/separate countdown variants did not resolve the loop. A
 * separate tail phase variable ties; -fno-rerun-loop-opt regresses to 1556;
 * -fno-strength-reduce leaves the earlier variant at 1588. Stop without new
 * owner/live-range evidence or a qualified caller/callee contract.
 * The resident owner is outside small data and the light pool extent is unknown.
 * Preserve the observed owner argument to 0032A978 despite its current no-argument
 * C definition. Retail also normalizes the request impulse before its first fill;
 * no native-safety claim is made. All required declarations follow.
 */
#include "common.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
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
#define H ((Hero *)D_00189E20)
extern Vector D_L00_001B8DC0, D_L00_001BF220;
extern float D_L00_00252F60[137][2];
extern char *D_L00_001C3280[];
extern Light D_L00_001C6F40[];
extern int D_L00_001B08D0 __attribute__((sda));
extern float func_002A7940(void);
extern float func_00283CE0(int);
extern float func_002A7790(float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(Vector *, const Vector *, const Vector *);
extern void func_00282CF0(Vector *, const Vector *, const Vector *);
extern void func_00282F20(Vector *, const Vector *, float);
extern int func_002761F8(Vector *, Vector *, int, char *, int);
extern void func_0032B598(char *, Vector *, int);
extern void func_0032ABC0(char *);
extern int func_00282948(int *);
extern int func_00277F48(Vector *, int, char *, DamageRequest *, float);
extern void func_002A8C00(char *, int, int, float, Quad16 *);
extern void func_002A8E20(char *, DamageRequest *);
/* This caller supplies its owner in the first integer argument. The original
   formal signature is not qualified by the current C callee definition. */
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
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_0032B190(void *);

void func_L00_003F0CC8(char *object)
{
    Vector point;
    DamageRequest request;
    EffectState *state = *(EffectState **)(object + 0x68);
    char **hit;
    char *satellite;
    Light *light;
    int count, remaining, i;
    float progress, first_angle, second_angle;

    qcopy(object + 0x10, H->ptr[0x2290 / 4] + 0x10);
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
            func_00282CC0(&point, &point, (Vector *)&H->b[0xE0]);
            if (func_002761F8((Vector *)&H->b[0xE0], &point, 0, H->ptr[0x2290 / 4], 0) != 0)
                qcopy(&point, &D_L00_001BF220);
            func_0032B598(object, &point, 10);
        }
        if (state->timer < 10 && (state->timer & 7) == 0)
            func_0032ABC0(object);
        if (func_00282948(&state->timer) != 0) {
            state->timer = 120;
            *(unsigned char *)(object + 0x20) = 3;
            count = func_00277F48((Vector *)&H->b[0xE0], 0, object, 0, 15.0f);
            if (count > 0) {
            hit = D_L00_001C3280;
            remaining = count;
            do {
                if ((*(unsigned long long *)(*hit + 0x30) & 0x500000000000ULL) != 0 &&
                    *hit != H->ptr[0x2290 / 4] && *(short *)(*hit + 0xaa) != 0xce7 &&
                    *(short *)(*hit + 0xaa) != 0xbb8) {
                    func_00282CF0(&point, (Vector *)(*hit + 0x10), (Vector *)&H->b[0xE0]);
                    func_00282F20(&point, &point, 1.0f);
                    /* The incoming request impulse is not initialized in retail. */
                    func_00282F20(&request.impulse, &request.impulse, 1.0f);
                    func_002A8C00((char *)&request, (int)object, 0x830000, 30.0f, (Quad16 *)&point);
                    request.impulse.word = point.word;
                    request.active = 1;
                    request.impulse.v[3] = 5627.9248f;
                    request.enabled = 5;
                    request.kind = 3;
                    request.object_class = *(unsigned short *)(*hit + 0xaa);
                    func_002A8E20(*hit, &request);
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
        qcopy(state->first + 0x10, H->ptr[0x2290 / 4] + 0x10);
    }
    if (state->second != 0) {
        **(int **)(state->second + 0x68) = func_00283CF0(progress * 32.0f);
        *(float *)(state->second + 0xf8) = func_00283BE0(*(float *)(state->second + 0xf8), 0.052359887f);
        satellite = state->second;
        func_002833F0((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->second + 0xe8) = progress;
        qcopy(state->second + 0x10, H->ptr[0x2290 / 4] + 0x10);
    }
    if (state->light != -1) {
        light = &D_L00_001C6F40[state->light];
        func_00282F20(&point, (Vector *)&H->b[0x2A0], 0.5f);
        func_00282CC0(&light->position, (Vector *)(H->ptr[0x2290 / 4] + 0x10), &point);
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
    func_L00_002E6EF8(func_0032B190, object);
}
