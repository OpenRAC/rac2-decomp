/* func_PAL_L00_00418250, the PAL copy of func_L00_00413358: the same C. */
#include "common.h"

/* func_PAL_L00_00418250 and func_L00_00413918 read their tuning values through $gp, hence -G8; they
 * are built with -g like the original, whose line notes give the two nops before a division. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

/* A textured quad as func_00280B90 draws it. */
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float length);
extern float IntToFloat(int value);
/* Draws a two-layer ribbon through count points, one quad per segment. */
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
void func_PAL_L00_00418250(char *object)
{
    BoltHit scratch;
    BoltState *state = *(BoltState **)(object + 0x68);
    float distance = fast_vec_dist(object + 0x10, &state->pos);
    float burst, ratio, spacing, step, t, a, b;
    float point10, amp10, point19, phase19, wave19, amp19, rate19;
    int i, sign, i10, i19;

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
    point10 = point10 / IntToFloat(5);
    ratio = distance + (0.01f - distance) * point10;
    spacing = ratio / IntToFloat(10);
    state->phase1 = FastAddRotations(state->phase1, D_L00_001B13A0 * step);
    state->phase2 = fast_subtract_rotations(state->phase2, D_L00_001B13A8);
    state->phase3 = FastAddRotations(state->phase3, D_L00_001B13B4);
    step = (360 / IntToFloat(10)) * step;

    for (i10 = 0; i10 < 10; i10++) {
        point10 = IntToFloat(i10);
        IntToFloat(10);
        amp10 = D_L00_001B1398;
        if (i10 == 0 || i10 == 9) {
            amp10 = 0;
        } else {
            amp10 *= math_fast_sin_or_cos_b(math_wrap_angle_to_pi(state->phase1 + point10 * step));
            amp10 += math_random_signed_float_range(0, D_L00_001B1394);
        }
        state->line[i10].f[2] = amp10;
        state->line[i10].f[1] = 0.0f;
        state->line[i10].f[0] = spacing * point10;
        state->line[i10].f[3] = 1;
    }

    for (i19 = 0; i19 < 19; i19++) {
        point19 = IntToFloat(i19);
        rate19 = point19 * D_L00_001B13AC;
        state->wave[i19].f[2] = 0.0f;
        phase19 = math_wrap_angle_to_pi(state->phase2 + rate19);
        wave19 = D_L00_001B13BC * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(state->phase3 + point19 * D_L00_001B13B8));
        amp19 = wave19 * math_fast_sin_or_cos_b(phase19) + math_random_signed_float_range(D_L00_001B1390, D_L00_001B1394);
        state->wave[i19].f[2] += amp19;
        state->wave[i19].f[1] = D_L00_001B13C0 * math_fast_sin_or_cos_a(phase19);
        state->wave[i19].f[0] = spacing * point19;
        state->wave[i19].f[3] = 1;
    }

    ref_L00_00413358_01(ref_L00_00413358_00, object);

    if (state->timer <= 0) {
        for (i = 0; i < 5; i++) {
            float third = 0.0f;
            float frame = 0.020000001f;
            float size = 0.0f;
            t = math_random_float_range(1, 6) * frame;
            a = math_random_angle();
            b = math_random_angle();
            vec_build_spherical_offset(&scratch, t, a, b);
            sign = math_random_int_range(1, 4);
            if (math_random_int_below(2)) {
                sign = -sign;
            }
            size = math_random_float_range(0.4f, 0.8f);
            part_spawn_ground_effect(&state->pos, 12, state->color | 0x7F000000, 0, size * 0.3f, size, sign, &scratch, third, 0);
            part_spawn_ground_effect(&state->pos, 12, 0x307F7F7F, 0, size * 0.15f, size * 0.5f, -sign, &scratch, third, 0);
        }
        sign = math_random_int_range(1, 8);
        if (math_random_int_below(2)) {
            sign = -sign;
        }
        burst = math_random_float_range(0.15f, 3);
        part_spawn_ground_effect(&state->pos, 10, state->color | 0x7F000000, 0, burst * 0.1f, burst, sign, D_L00_001A8F20, 0, 0);
    }
}
