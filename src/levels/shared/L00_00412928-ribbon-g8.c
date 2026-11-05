#include "common.h"

/* func_L00_00413358 and func_L00_00413918 read their tuning values through $gp, hence -G8; they
 * are built with -g like the original, whose line notes give the two nops before a division. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

/* A textured quad as func_00280B90 draws it. */
typedef struct {
    Vec v[4];
    unsigned color[4];
    float uv[4][2];
    long tag0, texture, tag2, tag3;
} QuadPacket;

typedef struct { Vec row[3], pos; } Frame;

extern unsigned D_L00_001B1380 __attribute__((sda));
extern float D_L00_001B1384 __attribute__((sda));
extern float D_L00_001B1388 __attribute__((sda));
extern float D_L00_001B138C __attribute__((sda));
extern int D_L00_001B13D0 __attribute__((sda));
extern char D_L00_001B8C80[];

extern long func_0027C878(int id);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, float length);
extern void func_00282DD8(void *dst, void *a, void *b);
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_002830C0(void *dst, void *src, void *frame);
extern void func_00280B90(void *packet, int a, int b);
extern float func_00283CE0(int value);
extern float func_002A7AA8(float a, float b, float c, float d, float t);

/* Draws a two-layer ribbon through count points, one quad per segment. */
void func_L00_00413918(char *object, Vec *points, int alpha, int alpha2, int count)
{
    QuadPacket outer, inner;
    Vec size, size2, dir;
    Frame frame;
    Vec first, second;
    Frame segment;
    char *state = *(char **)(object + 0x68);
    int i;
    float t, width;

    outer.texture = func_0027C878(0x17);
    outer.tag3 = 0x8000000048ULL;
    outer.tag2 = 0xff9000000260ULL;
    outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] =
        (D_L00_001B1380 & 0xffffff) | ((unsigned)alpha << 24);
    outer.tag0 = 0;
    inner.texture = func_0027C878(0xe);
    inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] =
        (*(unsigned *)(state + 0x24) & 0xffffff) | ((unsigned)alpha2 << 24);
    inner.tag3 = outer.tag3;
    inner.tag2 = outer.tag2;
    inner.tag0 = outer.tag0;
    inner.uv[0][0] = 1;
    inner.uv[0][1] = 0;
    inner.uv[1][0] = 1;
    inner.uv[1][1] = 1;
    inner.uv[2][0] = 0;
    inner.uv[2][1] = 0;
    inner.uv[3][0] = 0;
    inner.uv[3][1] = 1;
    outer.uv[0][0] = *(float *)(state + 0x14);
    outer.uv[0][1] = 0;
    outer.uv[1][0] = *(float *)(state + 0x14);
    outer.uv[1][1] = 1;
    outer.uv[2][0] = *(float *)(state + 0x14) + 1;
    outer.uv[2][1] = 0;
    outer.uv[3][0] = *(float *)(state + 0x14) + 1;
    outer.uv[3][1] = 1;
    size.q = 0;
    size.f[3] = 1;
    size.f[2] = D_L00_001B1388;
    size2.q = 0;
    size2.f[3] = 1;
    size2.f[2] = D_L00_001B1388 * D_L00_001B138C;

    func_00282CF0(&dir, state + 0x30, object + 0x10);
    func_00282F20(&dir, &dir, 1);
    qcopy(&frame.row[0], &dir);
    func_00282DD8(&frame.row[1], &frame.row[0], object + 0xe0);
    func_00282F20(&frame.row[1], &frame.row[1], 1);
    func_00282DD8(&frame.row[2], &frame.row[1], &frame.row[0]);
    qcopy(&frame.pos, object + 0x10);

    qcopy(&outer.v[0], &size);
    func_00282D30(&outer.v[1], &outer.v[0], -1);
    qcopy(&inner.v[0], &size2);
    func_00282D30(&inner.v[1], &inner.v[0], -1);
    func_002830C0(&first, &points[0], &frame);
    func_002830C0(&second, &points[1], &frame);
    func_00282CF0(&segment.row[0], &second, &first);
    func_00282F20(&segment.row[0], &segment.row[0], 1);
    func_00282CF0(&segment.row[1], D_L00_001B8C80 + 0x140, &first);
    func_00282DD8(&segment.row[2], &segment.row[1], &segment.row[0]);
    func_00282F20(&segment.row[2], &segment.row[2], 1);
    func_00282DD8(&segment.row[1], &segment.row[0], &segment.row[2]);
    qcopy(&segment.pos, &first);
    func_002830C0(&outer.v[0], &outer.v[0], &segment);
    func_002830C0(&outer.v[1], &outer.v[1], &segment);
    func_002830C0(&inner.v[0], &inner.v[0], &segment);
    func_002830C0(&inner.v[1], &inner.v[1], &segment);

    for (i = 1; i < count; i++) {
        qcopy(&outer.v[2], &size);
        func_00282D30(&outer.v[3], &outer.v[2], -1);
        qcopy(&inner.v[2], &size2);
        func_00282D30(&inner.v[3], &inner.v[2], -1);
        if (i == count - 1) {
            func_002830C0(&segment.pos, &points[i], &frame);
        } else {
            func_002830C0(&first, &points[i], &frame);
            func_002830C0(&second, &points[i + 1], &frame);
            func_00282CF0(&segment.row[0], &second, &first);
            func_00282F20(&segment.row[0], &segment.row[0], 1);
            func_00282CF0(&segment.row[1], D_L00_001B8C80 + 0x140, &first);
            func_00282DD8(&segment.row[2], &segment.row[1], &segment.row[0]);
            func_00282F20(&segment.row[2], &segment.row[2], 1);
            func_00282DD8(&segment.row[1], &segment.row[0], &segment.row[2]);
            qcopy(&segment.pos, &first);
        }
        func_002830C0(&outer.v[2], &outer.v[2], &segment);
        func_002830C0(&outer.v[3], &outer.v[3], &segment);
        func_002830C0(&inner.v[2], &inner.v[2], &segment);
        func_002830C0(&inner.v[3], &inner.v[3], &segment);

        if (i == 1 && D_L00_001B13D0 == alpha2) {
            /* Fade the ribbon's first edge out (alpha 0) for this draw only. */
            unsigned color, color2;

            color = outer.color[0];
            outer.color[0] = outer.color[1] = 0xffffff;
            color2 = inner.color[0];
            inner.color[0] = inner.color[1] = *(unsigned *)(state + 0x24) & 0xffffff;
            func_00280B90(&outer, 0, 0);
            func_00280B90(&inner, 0, 0);
            outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] = color;
            inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] = color2;
        } else if (i == count - 2 && D_L00_001B13D0 == alpha2) {
            /* Likewise its last edge. */
            unsigned color, color2;

            color = outer.color[2];
            outer.color[2] = outer.color[3] = 0xffffff;
            color2 = inner.color[2];
            inner.color[2] = inner.color[3] = *(unsigned *)(state + 0x24) & 0xffffff;
            func_00280B90(&outer, 0, 0);
            func_00280B90(&inner, 0, 0);
            outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] = color;
            inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] = color2;
        } else {
            func_00280B90(&outer, 0, 0);
            func_00280B90(&inner, 0, 0);
        }
        qcopy(&outer.v[0], &outer.v[2]);
        qcopy(&outer.v[1], &outer.v[3]);
        qcopy(&inner.v[0], &inner.v[2]);
        qcopy(&inner.v[1], &inner.v[3]);

        t = func_00283CE0(i);
        t /= func_00283CE0(count);
        width = func_002A7AA8(-1, 0, 1, 0, t);
        size.f[2] = D_L00_001B1388 + (D_L00_001B1384 - D_L00_001B1388) * width;
        size2.f[2] = size.f[2] * D_L00_001B138C;
        outer.uv[0][0] = *(float *)(state + 0x14);
        outer.uv[0][1] = 0;
        outer.uv[1][0] = *(float *)(state + 0x14);
        outer.uv[1][1] = 1;
        outer.uv[2][0] = *(float *)(state + 0x14) + 1;
        outer.uv[2][1] = 0;
        outer.uv[3][0] = *(float *)(state + 0x14) + 1;
        outer.uv[3][1] = 1;
    }
}

typedef struct { char pad[112]; float scale; char rest[108]; } HitRecord;

/* What func_002A8E20 takes: a direction with a range in its last word, then the hit itself. */
typedef union {
    Vec vector;
    struct {
        char pad[16];
        char *owner;
        int flags;
        unsigned char kind, mode;
        unsigned short id;
        float scale;
        int enabled;
    } packet;
} BoltHit;

typedef struct {
    Vec *line;
    Vec *wave;
    float phase1;
    float phase2;
    float phase3;
    char pad14[8];
    short timer;
    void *target;
    int color;
    char pad28[8];
    Vec pos;
} BoltState;

extern unsigned char D_00139595[];
extern HitRecord D_L00_00262570[];
extern char D_L00_001A8F20[] MACRO_ADDR;
extern char ref_L00_00413358_00[];
extern float D_L00_001B1390 __attribute__((sda));
extern float D_L00_001B1394 __attribute__((sda));
extern float D_L00_001B1398 __attribute__((sda));
extern float D_L00_001B13A0 __attribute__((sda));
extern float D_L00_001B13A8 __attribute__((sda));
extern float D_L00_001B13AC __attribute__((sda));
extern float D_L00_001B13B4 __attribute__((sda));
extern float D_L00_001B13B8 __attribute__((sda));
extern float D_L00_001B13BC __attribute__((sda));
extern float D_L00_001B13C0 __attribute__((sda));

extern float func_00282E48(void *a, void *b);
extern float func_00283198(float angle);
extern float func_00283180(float angle);
extern float func_00283B98(float angle, float delta);
extern float func_00283BE0(float angle, float delta);
extern float func_002ABB18(float angle);
extern float func_002A78D8(float centre, float range);
extern float func_002A7878(float low, float high);
extern float func_002A7940(void);
extern int func_00282978(void *timer);
extern int func_002A7820(int low, int high);
extern int func_002A77E0(int range);
extern void func_002AF000(void *dst, float length, float a, float b);
extern void func_002A8E20(void *target, void *hit);
extern void ref_L00_00413358_01(void *callback, void *object);
/* The float arguments sit among the others so that the bank order stays that of the callee. */
extern char *func_002C2210(void *position, int size, int color, int mode, float life, float secondLife,
                           int flag, void *vector, float third, int counter);

/* Each frame: sends the hit once the timer runs out, rebuilds the 10-point line and the 19-point
 * wave from their phases, registers the draw callback, and bursts into particles at the end.
 * third and frame stay locals of the burst loop, and size starts at zero there, for the sake of
 * loop.c: frame leaves the loop after third and the colour stays inside it. */
void func_L00_00413358(char *object)
{
    BoltHit scratch;
    BoltState *state = *(BoltState **)(object + 0x68);
    float distance = func_00282E48(object + 0x10, &state->pos);
    float burst, ratio, spacing, step, t, a, b;
    float point10, amp10, point19, phase19, wave19, amp19, rate19;
    int i, sign, i10, i19;

    if (state->timer != 0) {
        if (func_00282978(&state->timer) && state->target != 0) {
            scratch.packet.flags = 0x810000;
            scratch.packet.enabled = 1;
            scratch.packet.owner = object;
            scratch.packet.scale = ((HitRecord *)(D_00139595[0] * sizeof(HitRecord) + (int)D_L00_00262570))->scale;
            func_00282CF0(&scratch, &state->pos, object + 0x10);
            func_00282F20(&scratch, &scratch, 1);
            scratch.vector.f[3] = 5627.925f;
            scratch.packet.kind = 3;
            scratch.packet.mode = 2;
            scratch.packet.id = *(unsigned short *)(object + 0xAA);
            func_002A8E20(state->target, &scratch);
        }
    }

    step = 0.017453294f;
    point10 = func_00283CE0(state->timer);
    point10 = point10 / func_00283CE0(6);
    ratio = distance + (0.01f - distance) * point10;
    spacing = ratio / func_00283CE0(10);
    state->phase1 = func_00283B98(state->phase1, D_L00_001B13A0 * step);
    state->phase2 = func_00283BE0(state->phase2, D_L00_001B13A8);
    state->phase3 = func_00283B98(state->phase3, D_L00_001B13B4);
    step = (360 / func_00283CE0(10)) * step;

    for (i10 = 0; i10 < 10; i10++) {
        point10 = func_00283CE0(i10);
        func_00283CE0(10);
        amp10 = D_L00_001B1398;
        if (i10 == 0 || i10 == 9) {
            amp10 = 0;
        } else {
            amp10 *= func_00283198(func_002ABB18(state->phase1 + point10 * step));
            amp10 += func_002A78D8(0, D_L00_001B1394);
        }
        state->line[i10].f[2] = amp10;
        state->line[i10].f[1] = 0.0f;
        state->line[i10].f[0] = spacing * point10;
        state->line[i10].f[3] = 1;
    }

    for (i19 = 0; i19 < 19; i19++) {
        point19 = func_00283CE0(i19);
        rate19 = point19 * D_L00_001B13AC;
        state->wave[i19].f[2] = 0.0f;
        phase19 = func_002ABB18(state->phase2 + rate19);
        wave19 = D_L00_001B13BC * func_00283198(func_002ABB18(state->phase3 + point19 * D_L00_001B13B8));
        amp19 = wave19 * func_00283198(phase19) + func_002A78D8(D_L00_001B1390, D_L00_001B1394);
        state->wave[i19].f[2] += amp19;
        state->wave[i19].f[1] = D_L00_001B13C0 * func_00283180(phase19);
        state->wave[i19].f[0] = spacing * point19;
        state->wave[i19].f[3] = 1;
    }

    ref_L00_00413358_01(ref_L00_00413358_00, object);

    if (state->timer <= 0) {
        for (i = 0; i < 5; i++) {
            float third = 0.0f;
            float frame = 0.016666668f;
            float size = 0.0f;
            t = func_002A7878(1, 6) * frame;
            a = func_002A7940();
            b = func_002A7940();
            func_002AF000(&scratch, t, a, b);
            sign = func_002A7820(1, 4);
            if (func_002A77E0(2)) {
                sign = -sign;
            }
            size = func_002A7878(0.4f, 0.8f);
            func_002C2210(&state->pos, 15, state->color | 0x7F000000, 0, size * 0.3f, size, sign, &scratch, third, 0);
            func_002C2210(&state->pos, 15, 0x307F7F7F, 0, size * 0.15f, size * 0.5f, -sign, &scratch, third, 0);
        }
        sign = func_002A7820(1, 8);
        if (func_002A77E0(2)) {
            sign = -sign;
        }
        burst = func_002A7878(0.15f, 3);
        func_002C2210(&state->pos, 12, state->color | 0x7F000000, 0, burst * 0.1f, burst, sign, D_L00_001A8F20, 0, 0);
    }
}
