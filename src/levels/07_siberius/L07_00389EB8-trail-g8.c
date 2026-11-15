#include "common.h"

/* func_L07_003F3E80 needs -frac2-hazard-labels with -G8: retail keeps the case-1 join label on the
   mtc1 -> mul.s hazard nop. The two phase-step arms write one local; jump2 then cross-jumps their
   commutative-equal multiplies. */
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern void vec_copy_helper_a(void *), FastVecCross(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *), vec_set_direction_with_complement(void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *), multiply_matrix3x3(void *, void *, void *);
extern f32 FastVecLength(void *), math_random_signed_float_range(f32, f32), math_random_float_range(f32, f32);
extern s32 math_random_int_range(s32, s32), FloatToInt(f32), CollLine(void *, void *, s32, void *, void *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void vec_scale_to_length(void *, void *, f32), lerp_vector(void *, void *, void *, f32);
extern void *part_spawn_burst(void *, void *, s32, s32, s32, s32, f32, f32, f32, f32, f32);
extern void moby_set_state(void *, s32, s32), moby_mark_spawned(int);
extern s32 flag_set_first_pending(void *), moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern int snd_play_from_class_bank(s32, s32, void *, s32);
extern s32 math_random_int_below(s32);
extern void UpdateCollisionRing(u8 *);
extern void gfx_add_draw_callback_first(void (*)(u8 *), u8 *);
extern u8 D_L07_001BF660[];
extern f32 D_L07_001B0E3C __attribute__((sda)), D_L07_001B0E40 __attribute__((sda));
extern f32 D_L07_001B0E44 __attribute__((sda)), D_L07_001B0E48 __attribute__((sda));
extern f32 D_L07_001B0E4C __attribute__((sda));
extern s32 D_L07_001B0E50 __attribute__((sda));
extern u32 D_L07_001B0E58 __attribute__((sda));
extern s32 D_L07_001B0E70[] MACRO_ADDR;
extern s32 D_L07_001B0E70_gp SDATA(D_L07_001B0E70);
extern f32 D_L07_001B0E78[] MACRO_ADDR;
extern f32 D_L07_001B0E78_gp SDATA(D_L07_001B0E78);

/* The state block at object + 0x68; only the fields this function touches are named. */
typedef struct {
    f32 position[4];
    f32 direction[4];
    u8 *attachment;
    f32 growth, strength, phase, phase_step;
} SiberiusTrailState;

/* Moves a shot with a trail of sparks and, when it hits something, turns it into a fading
   impact effect. */
void spark_trail_shot_update(u8 *object)
{
    Vector axis, up, direction;
    f32 rotation[12];
    Vector previous, displacement, origin, point, velocity, speed;
    f32 magnitude, life, step;
    SiberiusTrailState *trail = *(SiberiusTrailState **)(object + 0x68);
    s32 i, size, count;
    u32 color;
    switch (object[0x20]) {
    case 0:
        vec_copy_helper_a(&up);
        if (trail->attachment) matrix_mul_vec3(&direction, trail->direction, trail->attachment + 0xC0);
        else qcopy(&direction, trail->direction);
        FastVecCross(&axis, &up, &direction);
        vec_set_direction_with_complement(&axis, &axis, D_L07_001B0E3C * 0.00029088825f);
        quaternion_to_rotation_basis(&axis, rotation);
        multiply_matrix3x3(object + 0xC0, rotation, object + 0xC0);
        qcopy(&previous, object + 0x10);
        trail->direction[2] -= trail->direction[3];
        if (trail->attachment) {
            FastVecAdd(trail->position, trail->position, trail->direction);
            matrix_mul_vec3(object + 0x10, trail->position, trail->attachment + 0xC0);
            FastVecAdd(object + 0x10, object + 0x10, trail->attachment + 0x10);
            matrix_mul_vec3(&displacement, trail->direction, trail->attachment + 0xC0);
            FastVecSub(&origin, object + 0x10, &displacement);
        } else {
            FastVecAdd(object + 0x10, object + 0x10, trail->direction);
            qcopy(&displacement, trail->direction);
            qcopy(&origin, &previous);
        }
        magnitude = FastVecLength(&displacement);
        for (i = 0; i < D_L07_001B0E50; i++) {
            size = math_random_int_range(D_L07_001B0E70_gp, D_L07_001B0E70[1]);
            count = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            life = math_random_float_range(D_L07_001B0E78_gp, D_L07_001B0E78[1]) * 210000.0f;
            speed.f[0] = magnitude;
            ApproachValue(speed.f, 0.0f, math_random_float_range(2.0f, 6.0f) * (1.0f / 60.0f));
            vec_scale_to_length(&velocity, &displacement, speed.f[0]);
            lerp_vector(&point, object + 0x10, &origin, math_random_float_range(0.0f, 1.0f));
            color = D_L07_001B0E58;
            part_spawn_burst(&point, &velocity, size, (s32)color >> 24, color & 0xFFFFFF, count,
                         life, 500.0f, 1.0f, 0.0f, 1.0f);
        }
        if (CollLine(&previous, object + 0x10, 2, object, 0)) {
            qcopy(object + 0x10, D_L07_001BF660);
            moby_set_state(object, 1, -1);
        } else {
            unsigned int timer = *(u16 *)(object + 0x96);
            unsigned int old = timer++;
            *(u16 *)(object + 0x96) = timer;
            if (old >= 301) moby_mark_spawned((int)object);
        }
        break;
    case 1:
        if (flag_set_first_pending(object)) {
            snd_play_from_class_bank(4, 0, object, 0xE5F);
            *(u32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
            *(f32 *)(object + 0x18) += 0.333f;
            trail->growth = 0.1f;
            trail->strength = 1.0f;
            if (math_random_int_below(2)) step = -D_L07_001B0E4C * (1.0f / 60.0f);
            else step = D_L07_001B0E4C * (1.0f / 60.0f);
            trail->phase_step = step;
            trail->phase = math_random_float_range(0.0f, 1.0f);
        }
        if (trail->attachment)
            moby_transform_point_and_rotation_by_parent(object, trail->attachment, object + 0x10, object + 0xF0, object + 0x10, object + 0xF0);
        trail->growth += D_L07_001B0E40 * (1.0f / 60.0f);
        if (trail->growth >= D_L07_001B0E44) {
            ApproachValue(&trail->strength, 0.0f, D_L07_001B0E48 * (1.0f / 60.0f));
            if (trail->strength <= 0.0f) { moby_mark_spawned((int)object); return; }
        }
        trail->phase += trail->phase_step;
        if (trail->phase > 1.0f) trail->phase -= 1.0f;
        else if (trail->phase < 0.0f) trail->phase += 1.0f;
        gfx_add_draw_callback_first(UpdateCollisionRing, object);
        break;
    }
}
