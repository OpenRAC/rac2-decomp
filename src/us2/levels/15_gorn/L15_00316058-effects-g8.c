/* func_US2_L15_00316058, the USA v2.00 copy of func_L15_00315428: the same C, plus a level test (0x33) before the
 * 0xFA0 effect. */
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

extern Stage g_gorn_stage_state;
extern int g_current_map_index;
extern float g_effect_row_table[][8];
extern char g_cutscene_particle_vel_a[16] SDATA(D_L15_001A9420);
extern char g_cutscene_particle_vel_b[16] SDATA(D_L15_001A9430);
extern char g_cutscene_particle_vel_c[16] SDATA(D_L15_001A9440);
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces_us2(void *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
extern void vec_fast_to_int_helper(void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern char *part_spawn_shockwave_burst(void *, int, int, int, int, int, int, int, int, int, int, float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *moby_spawn_shot_effect(void *, void *, void *, int, int, int, int, int, float);
extern void moby_transform_joint_point(void *, int, void *);
extern void copy_matrix3x4(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);

/* Updates the Gorn stage objects and emits the scripted effects (USA v2.00: skips the 0xFA0 effect on map 0x33). */
void gorn_stage_effects_update_us2(void)
{
    /* The joint transform reuses the earlier effect vectors and writes 64 bytes. */
    union {
        struct { Vec a, b, c; } effect;
        Vec joint[4];
    } scratch;
    Vec matrix[3], offset, velocity, first, second, third, fourth;
    char *moby;
    int i;
    float sign;
    float *row;

    anim_start_startup_animations();
    for (i = 0; i < g_gorn_stage_state.count; i++) {
        /* Stage.objects[i], word 99 of the stage. */
        char **slot = (char **)&g_gorn_stage_state + i;
        char *moby = slot[99];
        if (moby && FIELD(short, moby, 0xAA) == 0xE29) {
            FIELD(unsigned short, moby, 0x34) |= 0x800;
        }
        if (FIELD(short, moby, 0xAA) == 0xD54) {
            UpdateEquipmentPieces_us2(moby);
        }
        if (moby && FIELD(short, moby, 0xAA) == MOBY_CLASS_TV_SCREENS && g_current_map_index != 0x33) {
            if (FIELD(char *, moby, 0x68)) {
                math_store_angle_update_result(moby, FIELD(char *, moby, 0x68) + 0xC,
                                 0x80AAAAD2, 0x80396464, 0.061086535f);
            }
        }
    }
    if (g_current_map_index != 15 || g_gorn_stage_state.busy) {
        return;
    }

    moby = g_gorn_stage_state.objects[2];
    if (g_gorn_stage_state.frame == 13) {
        vec_fast_to_int_helper(FIELD(char *, moby, 0x58) + 0x10, &scratch.effect.b);
        quaternion_to_rotation_basis(&scratch.effect.b, moby + 0xC0);
        moby_compute_local_point(moby, &scratch.effect.a, 4, 3, 5);
        part_spawn_shockwave_burst(&scratch.effect.a, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
    }
    if ((unsigned)(g_gorn_stage_state.frame - 20) >= 31 && !math_random_int_below(3)) {
        sign = 1;
        if (math_random_int_below(2)) {
            sign = -1;
        }
        row = g_effect_row_table[math_random_int_below(3)];
        moby_compute_local_point(moby, &scratch.effect.a, row[0], row[1], row[2]);
        moby_compute_local_point(moby, &scratch.effect.b, row[4], row[5], row[6]);
        scratch.effect.b.f[0] += math_random_signed_float_range(.5f, 1.5f);
        scratch.effect.b.f[1] += math_random_signed_float_range(.5f, 1.5f);
        scratch.effect.b.f[2] += math_random_signed_float_range(.5f, 1.5f);
        FastVecSub(&scratch.effect.c, &scratch.effect.b, &scratch.effect.a);
        vec_scale_to_length(&scratch.effect.c, &scratch.effect.c, 1.1666667f);
        moby_spawn_shot_effect(moby, &scratch.effect.a, &scratch.effect.c, 0xbe4620, 0x783214, 1, 0, 1, sign);
    }
    if (g_gorn_stage_state.frame < 140) {
        char *moby = g_gorn_stage_state.objects[3];
        float strength = .4f;
        moby_transform_joint_point(moby, 0, scratch.joint);
        /* Only the three rotation rows are needed by the following transforms. */
        copy_matrix3x4(matrix, scratch.joint);
        offset.q = 0;
        offset.f[0] = -.3f;
        offset.f[3] = 1;
        velocity.q = 0;
        matrix_mul_vec3(&first, &offset, matrix);
        FastVecAdd(&first, &first, moby + 0x10);
        first.f[3] = 0;
        second.q = first.q;
        third.q = first.q;
        fourth.q = first.q;
        vec_add_random_offset(&first, .3f);
        vec_add_random_offset(&second, .3f);
        vec_add_random_offset(&third, .3f);
        vec_add_random_offset(&fourth, .3f);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(moby, &first, &velocity, g_cutscene_particle_vel_a, 1);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(moby, &second, &velocity, g_cutscene_particle_vel_a, 1);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(moby, &third, &velocity, g_cutscene_particle_vel_b, 1);
        velocity.f[0] = -(math_random_float_range(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        part_spawn_object_relative_particle(moby, &fourth, &velocity, g_cutscene_particle_vel_c, 1);
    }
}
