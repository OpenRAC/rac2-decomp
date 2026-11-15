/* func_PAL_L22_003AF154, the PAL copy of func_L09_003A01D8: the same C, where the literals
   0.10471977f, 0.016666668f and 1.6666667f become 0.12566373f, 0.020000001f and 2.0000002f, the
   arguments 7 and 13 become 6 and 11, and func_002C16C0 and func_002ABBB8 become
   func_PAL_002C23B8 and func_PAL_002AC718. */
#include "common.h"

/* func_PAL_L22_003AF154: a 16-byte vector with a whole-quadword view, and the 0x28-byte impact
   request func_002A8C00 fills (attacker 0x10, flags 0x14, damage 0x1C, enabled 0x20 and the
   direction copied from its last argument). */
typedef int Quad_L09_003A01D8 __attribute__((mode(TI)));
typedef union {
    Quad_L09_003A01D8 q;
    float f[4];
} Vector_L09_003A01D8;

typedef struct {
    float direction[4];
    void *attacker;
    int flags;
    u8 kind;
    u8 mode;
    u16 object_class;
    float damage;
    int enabled;
    float unused24;
} Impact_L09_003A01D8;

typedef char Impact_L09_003A01D8_extent[sizeof(Impact_L09_003A01D8) == 0x28 ? 1 : -1];

#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

extern float D_L09_001B2390 MACRO_ADDR;
extern float D_L09_001B238C MACRO_ADDR;
extern int D_L09_001B2388 MACRO_ADDR;
extern u8 *D_L09_001BFE58 NOT_SDA;
extern float D_L09_001A8F20[] MACRO_ADDR;
extern float math_random_float_range(float lo, float hi);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern float FastAddRotations(float angle, float step);
extern float FastVecLength(void *v);
extern float math_random_angle(void);
extern int func_001163B0(void);
extern int math_fast_float_d(void *a0);
extern void FastVecAdd(void *dst, void *a, void *b);
extern void FastVecSub(void *dst, void *a, void *b);
extern void matrix_mul_vec3(void *dst, void *src, void *matrix);
extern void FastVecScale(void *dst, void *src, float scale);
extern void math_apply_axis_rotation_to_quat(void *dst, void *src, void *matrix, float angle);
extern void *func_PAL_002C23B8(void *position, void *velocity, int a2, int a3, int color, int t1,
                           float f12, float f13, float f14, float f15, float f16);
extern void *part_spawn_trailing_spark(void *a0, void *a1, int a2, int a3, int a4, int a5, float f12);
extern void make_hit_descriptor(void *impact, int attacker, int flags, float damage, void *direction);
extern int CollLine(void *from, void *to, int a2, void *object, Impact_L09_003A01D8 *impact);
extern int coll_test_point(void *position, int a1, void *object, float radius);
extern int coll_process_hit(void *position, int a1, void *target, Impact_L09_003A01D8 *impact,
                         float scale);
extern void func_PAL_002AC718(void *owner, void *direction, void *position, float radius, float damage,
                          int sparks, int flashes, int smoke, float glow, float white, float cutoff,
                          float scale, int sound, float blast, int shake, int debris, int quality,
                          int channels, int flags);
extern int PlayMobySound(int a0, int a1, void *object);
extern void moby_mark_spawned(void *object);

/* Moves a projectile along its velocity (state = object +0x68, velocity at state +0x00),
   spinning +0xF0. Unless the level is busy on an odd frame it leaves a drifting trail particle
   and, on odd random draws, a spark. It then asks for an impact towards the owner
   (state +0x3C); on a hit against anything but the owner it explodes and deletes itself,
   otherwise it commits the predicted position. The trail vectors and the impact request share
   one stack area. */
void func_PAL_L22_003AF154(u8 *object)
{
    struct {
        float predicted[4];
        union {
            struct {
                Vector_L09_003A01D8 point, velocity, axis;
            } effects;
            Impact_L09_003A01D8 impact;
        } payload;
    } f;
    u8 *state = P(object, 0x68), *hit;
    float length;
    int collision;
    int busy;

    if (object[0x20])
        return;
    F(object, 0xF0) = FastAddRotations(F(object, 0xF0), 0.12566373f);
    FastVecAdd(f.predicted, object + 0x10, state);
    busy = D_L09_001B238C > 0.9f || D_L09_001B2390 > 0.9f;
    if (!busy || !(D_L09_001B2388 & 1)) {
        length = FastVecLength(state);
        f.payload.effects.axis.q = 0;
        f.payload.effects.axis.f[0] = math_random_float_range(-1.0f, 1.0f);
        f.payload.effects.axis.f[1] = math_random_float_range(-1.0f, 1.0f);
        f.payload.effects.axis.f[2] = math_random_float_range(-1.0f, 1.0f);
        f.payload.effects.velocity.q = f.payload.effects.axis.q;
        vec_scale_to_length(f.payload.effects.velocity.f, f.payload.effects.velocity.f,
                      math_random_float_range(0.04f, 0.08f) * 0.020000001f);
        FastVecScale(f.payload.effects.point.f, state, math_random_float_range(0.2f, 0.99f));
        FastVecAdd(f.payload.effects.velocity.f, f.payload.effects.velocity.f,
                      f.payload.effects.point.f);
        vec_scale_to_length(f.payload.effects.point.f, state, math_random_float_range(0.0f, 1.0f) * length);
        FastVecAdd(f.payload.effects.point.f, f.payload.effects.point.f, object + 0x10);
        func_PAL_002C23B8(object + 0x10, f.payload.effects.velocity.f, 6, 127, 0xB0B0B0, 3,
                      40000.0f, 1000.0f, 1.0f, -0.00039999998989515007f, 0.0f);
        f.payload.effects.axis.q = 0;
        f.payload.effects.axis.f[2] = 0.01f;
        matrix_mul_vec3(f.payload.effects.axis.f, f.payload.effects.axis.f, object + 0xC0);
        math_apply_axis_rotation_to_quat(f.payload.effects.axis.f, f.payload.effects.axis.f, object + 0xC0,
                      math_random_angle());
        if (func_001163B0() & 1)
            part_spawn_trailing_spark(f.payload.effects.point.f, f.payload.effects.axis.f, 0x4F007FFF,
                          0x1FFFFFFF, 11, 1, 25000.0f);
    }
    make_hit_descriptor(&f.payload.impact, I(state, 0x3C), 0x10001, F(state, 0x40), state);
    f.payload.impact.object_class = *(u16 *)(object + 0xAA);
    FastVecSub(f.payload.impact.direction, object + 0x10, P(state, 0x3C) + 0x10);
    f.payload.impact.direction[2] = 0.0f;
    vec_scale_to_length(f.payload.impact.direction, f.payload.impact.direction, 2.0000002f);
    f.payload.impact.direction[3] = 5627.9248046875f;
    f.payload.impact.enabled |= 1;
    f.payload.impact.kind = 4;
    collision = CollLine(object + 0x10, f.predicted, 0, object, &f.payload.impact);
    if (collision || coll_test_point(object + 0x10, 1, object, 0.3f)
        || math_fast_float_d(state + 0x38)) {
        hit = D_L09_001BFE58;
        if (hit) {
            if (hit == P(state, 0x3C)) {
                qcopy(object + 0x10, f.predicted);
                return;
            }
            if (*(short *)(hit + 0xAA) != 0x4E)
                coll_process_hit(object + 0x10, 0, P(state, 0x3C), &f.payload.impact, 0.5f);
            /* The calls are written out per arm: a call ending a block that falls into a label
               gets a (use 0) from flow, which stops jump2 from cross-jumping the tails. */
            func_PAL_002AC718(object, D_L09_001A8F20, 0, 0.0f, 0.0f, 0, 2, 10, 0.0f, 0.0f, 9.0f,
                          0.666f, -1, 0.0f, 0, 1, -1, 0, 0x810001);
            PlayMobySound(0, 0, object);
            moby_mark_spawned(object);
        } else {
            func_PAL_002AC718(object, D_L09_001A8F20, 0, 0.0f, 0.0f, 0, 2, 8, 0.0f, 0.0f, 9.0f,
                          0.5f, -1, 0.0f, 0, 1, -1, 0, 0x810001);
            PlayMobySound(0, 0, object);
            moby_mark_spawned(object);
        }
    } else
        qcopy(object + 0x10, f.predicted);
}

#undef I
#undef F
#undef P
