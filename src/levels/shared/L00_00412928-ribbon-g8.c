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

extern long GetEffectTextureDescriptor(int id);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float length);
extern void FastVecCross(void *dst, void *a, void *b);
extern void FastVecScale(void *dst, void *src, float scale);
extern void transform_vector(void *dst, void *src, void *frame);
extern void draw_world_quad(void *packet, int a, int b);
extern float IntToFloat(int value);
extern float cubic_hermite_scalar(float a, float b, float c, float d, float t);

/* Draws a two-layer ribbon through count points, one quad per segment. */
void wave_line_draw_ribbon(char *object, Vec *points, int alpha, int alpha2, int count)
{
    QuadPacket outer, inner;
    Vec size, size2, dir;
    Frame frame;
    Vec first, second;
    Frame segment;
    char *state = *(char **)(object + 0x68);
    int i;
    float progress, width;

    outer.texture = GetEffectTextureDescriptor(0x17);
    outer.tag3 = 0x8000000048ULL;
    outer.tag2 = 0xff9000000260ULL;
    outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] =
        (D_L00_001B1380 & 0xffffff) | ((unsigned)alpha << 24);
    outer.tag0 = 0;
    inner.texture = GetEffectTextureDescriptor(0xe);
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

    FastVecSub(&dir, state + 0x30, object + 0x10);
    vec_scale_to_length(&dir, &dir, 1);
    qcopy(&frame.row[0], &dir);
    FastVecCross(&frame.row[1], &frame.row[0], object + 0xe0);
    vec_scale_to_length(&frame.row[1], &frame.row[1], 1);
    FastVecCross(&frame.row[2], &frame.row[1], &frame.row[0]);
    qcopy(&frame.pos, object + 0x10);

    qcopy(&outer.v[0], &size);
    FastVecScale(&outer.v[1], &outer.v[0], -1);
    qcopy(&inner.v[0], &size2);
    FastVecScale(&inner.v[1], &inner.v[0], -1);
    transform_vector(&first, &points[0], &frame);
    transform_vector(&second, &points[1], &frame);
    FastVecSub(&segment.row[0], &second, &first);
    vec_scale_to_length(&segment.row[0], &segment.row[0], 1);
    FastVecSub(&segment.row[1], D_L00_001B8C80 + 0x140, &first);
    FastVecCross(&segment.row[2], &segment.row[1], &segment.row[0]);
    vec_scale_to_length(&segment.row[2], &segment.row[2], 1);
    FastVecCross(&segment.row[1], &segment.row[0], &segment.row[2]);
    qcopy(&segment.pos, &first);
    transform_vector(&outer.v[0], &outer.v[0], &segment);
    transform_vector(&outer.v[1], &outer.v[1], &segment);
    transform_vector(&inner.v[0], &inner.v[0], &segment);
    transform_vector(&inner.v[1], &inner.v[1], &segment);

    for (i = 1; i < count; i++) {
        qcopy(&outer.v[2], &size);
        FastVecScale(&outer.v[3], &outer.v[2], -1);
        qcopy(&inner.v[2], &size2);
        FastVecScale(&inner.v[3], &inner.v[2], -1);
        if (i == count - 1) {
            transform_vector(&segment.pos, &points[i], &frame);
        } else {
            transform_vector(&first, &points[i], &frame);
            transform_vector(&second, &points[i + 1], &frame);
            FastVecSub(&segment.row[0], &second, &first);
            vec_scale_to_length(&segment.row[0], &segment.row[0], 1);
            FastVecSub(&segment.row[1], D_L00_001B8C80 + 0x140, &first);
            FastVecCross(&segment.row[2], &segment.row[1], &segment.row[0]);
            vec_scale_to_length(&segment.row[2], &segment.row[2], 1);
            FastVecCross(&segment.row[1], &segment.row[0], &segment.row[2]);
            qcopy(&segment.pos, &first);
        }
        transform_vector(&outer.v[2], &outer.v[2], &segment);
        transform_vector(&outer.v[3], &outer.v[3], &segment);
        transform_vector(&inner.v[2], &inner.v[2], &segment);
        transform_vector(&inner.v[3], &inner.v[3], &segment);

        if (i == 1 && D_L00_001B13D0 == alpha2) {
            /* Fade the ribbon's first edge out (alpha 0) for this draw only. */
            unsigned color, color2;

            color = outer.color[0];
            outer.color[0] = outer.color[1] = 0xffffff;
            color2 = inner.color[0];
            inner.color[0] = inner.color[1] = *(unsigned *)(state + 0x24) & 0xffffff;
            draw_world_quad(&outer, 0, 0);
            draw_world_quad(&inner, 0, 0);
            outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] = color;
            inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] = color2;
        } else if (i == count - 2 && D_L00_001B13D0 == alpha2) {
            /* Likewise its last edge. */
            unsigned color, color2;

            color = outer.color[2];
            outer.color[2] = outer.color[3] = 0xffffff;
            color2 = inner.color[2];
            inner.color[2] = inner.color[3] = *(unsigned *)(state + 0x24) & 0xffffff;
            draw_world_quad(&outer, 0, 0);
            draw_world_quad(&inner, 0, 0);
            outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] = color;
            inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] = color2;
        } else {
            draw_world_quad(&outer, 0, 0);
            draw_world_quad(&inner, 0, 0);
        }
        qcopy(&outer.v[0], &outer.v[2]);
        qcopy(&outer.v[1], &outer.v[3]);
        qcopy(&inner.v[0], &inner.v[2]);
        qcopy(&inner.v[1], &inner.v[3]);

        progress = IntToFloat(i);
        progress /= IntToFloat(count);
        width = cubic_hermite_scalar(-1, 0, 1, 0, progress);
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
extern HitRecord g_weapon_l00_table[];
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

extern float fast_vec_dist(void *a, void *b);
extern float math_fast_sin_or_cos_b(float angle);
extern float math_fast_sin_or_cos_a(float angle);
extern float FastAddRotations(float angle, float delta);
extern float fast_subtract_rotations(float angle, float delta);
extern float math_wrap_angle_to_pi(float angle);
extern float math_random_signed_float_range(float centre, float range);
extern float math_random_float_range(float low, float high);
extern float math_random_angle(void);
extern int FastDecTimer(void *timer);
extern int math_random_int_range(int low, int high);
extern int math_random_int_below(int range);
extern void vec_build_spherical_offset(void *dst, float length, float a, float b);
extern void QueueMobyImpact(void *target, void *hit);
extern void ref_L00_00413358_01(void *callback, void *object);
/* The float arguments sit among the others so that the bank order stays that of the callee. */
extern char *part_spawn_ground_effect(void *position, int size, int color, int mode, float life, float secondLife,
                           int flag, void *vector, float third, int counter);

/* Each frame: sends the hit once the timer runs out, rebuilds the 10-point line and the 19-point
 * wave from their phases, registers the draw callback, and bursts into particles at the end.
 * third and frame stay locals of the burst loop, and size starts at zero there, for the sake of
 * loop.c: frame leaves the loop after third and the colour stays inside it. */
void UpdateWaveLineEffect(char *object)
{
    BoltHit scratch;
    BoltState *state = *(BoltState **)(object + 0x68);
    float distance = fast_vec_dist(object + 0x10, &state->pos);
    float burst, ratio, spacing, step, burst_speed, yaw, pitch;
    float point10, amp10, point19, phase19, wave19, amp19, rate19;
    int i, sign, line_idx, wave_idx;

    if (state->timer != 0) {
        if (FastDecTimer(&state->timer) && state->target != 0) {
            scratch.packet.flags = 0x810000;
            scratch.packet.enabled = 1;
            scratch.packet.owner = object;
            scratch.packet.scale = ((HitRecord *)(D_00139595[0] * sizeof(HitRecord) + (int)g_weapon_l00_table))->scale;
            FastVecSub(&scratch, &state->pos, object + 0x10);
            vec_scale_to_length(&scratch, &scratch, 1);
            scratch.vector.f[3] = 5627.925f;
            scratch.packet.kind = 3;
            scratch.packet.mode = 2;
            scratch.packet.id = *(unsigned short *)(object + 0xAA);
            QueueMobyImpact(state->target, &scratch);
        }
    }

    step = 0.017453294f;
    point10 = IntToFloat(state->timer);
    point10 = point10 / IntToFloat(6);
    ratio = distance + (0.01f - distance) * point10;
    spacing = ratio / IntToFloat(10);
    state->phase1 = FastAddRotations(state->phase1, D_L00_001B13A0 * step);
    state->phase2 = fast_subtract_rotations(state->phase2, D_L00_001B13A8);
    state->phase3 = FastAddRotations(state->phase3, D_L00_001B13B4);
    step = (360 / IntToFloat(10)) * step;

    for (line_idx = 0; line_idx < 10; line_idx++) {
        point10 = IntToFloat(line_idx);
        IntToFloat(10);
        amp10 = D_L00_001B1398;
        if (line_idx == 0 || line_idx == 9) {
            amp10 = 0;
        } else {
            amp10 *= math_fast_sin_or_cos_b(math_wrap_angle_to_pi(state->phase1 + point10 * step));
            amp10 += math_random_signed_float_range(0, D_L00_001B1394);
        }
        state->line[line_idx].f[2] = amp10;
        state->line[line_idx].f[1] = 0.0f;
        state->line[line_idx].f[0] = spacing * point10;
        state->line[line_idx].f[3] = 1;
    }

    for (wave_idx = 0; wave_idx < 19; wave_idx++) {
        point19 = IntToFloat(wave_idx);
        rate19 = point19 * D_L00_001B13AC;
        state->wave[wave_idx].f[2] = 0.0f;
        phase19 = math_wrap_angle_to_pi(state->phase2 + rate19);
        wave19 = D_L00_001B13BC * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(state->phase3 + point19 * D_L00_001B13B8));
        amp19 = wave19 * math_fast_sin_or_cos_b(phase19) + math_random_signed_float_range(D_L00_001B1390, D_L00_001B1394);
        state->wave[wave_idx].f[2] += amp19;
        state->wave[wave_idx].f[1] = D_L00_001B13C0 * math_fast_sin_or_cos_a(phase19);
        state->wave[wave_idx].f[0] = spacing * point19;
        state->wave[wave_idx].f[3] = 1;
    }

    ref_L00_00413358_01(ref_L00_00413358_00, object);

    if (state->timer <= 0) {
        for (i = 0; i < 5; i++) {
            float third = 0.0f;
            float frame = 0.016666668f;
            float size = 0.0f;
            burst_speed = math_random_float_range(1, 6) * frame;
            yaw = math_random_angle();
            pitch = math_random_angle();
            vec_build_spherical_offset(&scratch, burst_speed, yaw, pitch);
            sign = math_random_int_range(1, 4);
            if (math_random_int_below(2)) {
                sign = -sign;
            }
            size = math_random_float_range(0.4f, 0.8f);
            part_spawn_ground_effect(&state->pos, 15, state->color | 0x7F000000, 0, size * 0.3f, size, sign, &scratch, third, 0);
            part_spawn_ground_effect(&state->pos, 15, 0x307F7F7F, 0, size * 0.15f, size * 0.5f, -sign, &scratch, third, 0);
        }
        sign = math_random_int_range(1, 8);
        if (math_random_int_below(2)) {
            sign = -sign;
        }
        burst = math_random_float_range(0.15f, 3);
        part_spawn_ground_effect(&state->pos, 12, state->color | 0x7F000000, 0, burst * 0.1f, burst, sign, D_L00_001A8F20, 0, 0);
    }
}
