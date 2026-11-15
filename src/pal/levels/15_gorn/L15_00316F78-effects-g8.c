/*
 * func_PAL_L15_00316F78, the PAL copy of func_L15_00315428: the same C at 50 Hz (frame counts and
 * rates scaled by 5/6 or 6/5), with a level test on the 0xFA0 objects. Holding 0xFA0 in a local
 * lengthens its pseudo's life, so the first loop pass hoists it ahead of the pointer giv's init.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union Vec {
    Quad q;
    float f[4];
} Vec;
#define FIELD(t, p, o) (*(t *)((char *)(p) + (o)))

typedef struct Stage {
    char pad[0x30];
    int busy, frame;
    char pad38[12];
    short count;
    char pad46[0x146];
    char *objects[4];
} Stage;

extern Stage D_L15_001BD4C0;
extern int g_current_map_index;
extern float D_L15_00293010[][8];
extern char D_L15_001A9420[16] SDATA(D_L15_001A9420);
extern char D_L15_001A9430[16] SDATA(D_L15_001A9430);
extern char D_L15_001A9440[16] SDATA(D_L15_001A9440);
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
extern void vec_fast_to_int_helper(void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void part_spawn_shockwave_burst(void *, int, int, int, int, int, int, int, int, int, int, float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_spawn_shot_effect(void *, void *, void *, int, int, int, int, int, float);
extern void moby_transform_joint_point(void *, int, void *);
extern void copy_matrix3x4(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void part_spawn_object_relative_particle(void *, void *, void *, void *, int);

/* Updates the stage objects and emits effects at the scripted frame counts. */
void func_PAL_L15_00316F78(void)
{
    /* The joint transform reuses the earlier effect vectors and writes 64 bytes. */
    union {
        struct { Vec a, b, c; } effect;
        Vec joint[4];
    } scratch;
    Vec matrix[3], offset, velocity, first, second, third, fourth;
    char *p;
    int n;
    float sign;
    float *row;

    anim_start_startup_animations();
    for (n = 0; n < D_L15_001BD4C0.count; n++) {
        char *p = D_L15_001BD4C0.objects[n];
        if (p && FIELD(short, p, 0xAA) == 0xE29) {
            FIELD(unsigned short, p, 0x34) |= 0x800;
        }
        if (FIELD(short, p, 0xAA) == 0xD54) {
            UpdateEquipmentPieces(p);
        }
        if (p) {
            int type = 0xFA0;
            if (FIELD(short, p, 0xAA) == type && g_current_map_index != 51) {
                if (FIELD(char *, p, 0x68)) {
                    math_store_angle_update_result(p, FIELD(char *, p, 0x68) + 0xC,
                                     0x80AAAAD2, 0x80396464, 0.073303841f);
                }
            }
        }
    }
    if (g_current_map_index != 15 || D_L15_001BD4C0.busy) {
        return;
    }

    p = D_L15_001BD4C0.objects[2];
    if (D_L15_001BD4C0.frame == 11) {
        vec_fast_to_int_helper(FIELD(char *, p, 0x58) + 0x10, &scratch.effect.b);
        quaternion_to_rotation_basis(&scratch.effect.b, p + 0xC0);
        moby_compute_local_point(p, &scratch.effect.a, 4, 3, 5);
        part_spawn_shockwave_burst(&scratch.effect.a, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
    }
    if ((unsigned)(D_L15_001BD4C0.frame - 17) >= 26 && !math_random_int_below(3)) {
        sign = 1;
        if (math_random_int_below(2)) {
            sign = -1;
        }
        row = D_L15_00293010[math_random_int_below(3)];
        moby_compute_local_point(p, &scratch.effect.a, row[0], row[1], row[2]);
        moby_compute_local_point(p, &scratch.effect.b, row[4], row[5], row[6]);
        scratch.effect.b.f[0] += math_random_signed_float_range(.5f, 1.5f);
        scratch.effect.b.f[1] += math_random_signed_float_range(.5f, 1.5f);
        scratch.effect.b.f[2] += math_random_signed_float_range(.5f, 1.5f);
        FastVecSub(&scratch.effect.c, &scratch.effect.b, &scratch.effect.a);
        vec_scale_to_length(&scratch.effect.c, &scratch.effect.c, 1.4000001f);
        moby_spawn_shot_effect(p, &scratch.effect.a, &scratch.effect.c, 0xbe4620, 0x783214, 1, 0, 1, sign);
    }
    if (D_L15_001BD4C0.frame < 117) {
        char *p = D_L15_001BD4C0.objects[3];
        float strength = .4f;
        moby_transform_joint_point(p, 0, scratch.joint);
        /* Only the three rotation rows are needed by the following transforms. */
        copy_matrix3x4(matrix, scratch.joint);
        offset.q = 0;
        offset.f[0] = -.3f;
        offset.f[3] = 1;
        velocity.q = 0;
        matrix_mul_vec3(&first, &offset, matrix);
        FastVecAdd(&first, &first, p + 0x10);
        first.f[3] = 0;
        second.q = first.q;
        third.q = first.q;
        fourth.q = first.q;
        vec_add_random_offset(&first, .3f);
        vec_add_random_offset(&second, .3f);
        vec_add_random_offset(&third, .3f);
        vec_add_random_offset(&fourth, .3f);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.020000001f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(p, &first, &velocity, D_L15_001A9420, 1);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.020000001f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(p, &second, &velocity, D_L15_001A9420, 1);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.020000001f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(p, &third, &velocity, D_L15_001A9430, 1);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.020000001f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(p, &fourth, &velocity, D_L15_001A9440, 1);
    }
}
