#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern int moby_step_at_own_position_factor_pal(void *, float);
extern char *part_spawn_spinning_spark_pal(void *, int, float, float, void *, float, int, int, float);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern float g_object_anim_sparks_table[];

/* Moves the object along its animation-driven speed curve toward dest, and throws sparks at two points of the animation (PAL). */
void object_move_along_anim_sparks_pal(char *moby, float *dest)
{
    float step_vec[4], spark_pos[4], offset_vel[4], random_dir[4], spawn_pos[4];
    float frame, frame_floor, particle_life;
    int index, i, particle_kind;
    unsigned short lifetime;
    char *particle, *particle_data;

    if ((unsigned char)moby[0x42] != (unsigned char)moby[0x43]) {
        moby_l01_turn_toward_target_pal(moby, dest);
        return;
    }
    frame = moby_get_anim_value(moby);
    index = FloatToInt(frame);
    {
        int next_index = index + 1;
        frame_floor = IntToFloat(index);
        frame -= frame_floor;
        FastVecScale(step_vec, moby + 0xc0,
                      g_object_anim_sparks_table[index] + (g_object_anim_sparks_table[next_index] - g_object_anim_sparks_table[index]) * frame);
    }
    FastVecAdd(moby + 0x10, step_vec, moby + 0x10);
    moby_step_at_own_position_factor_pal(moby, mat_fast_helper_a(dest[0] - *(float *)(moby + 0x10), dest[1] - *(float *)(moby + 0x14)));
    *(float *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
    if (index != 5 && index != 15) {
        return;
    }
    if (index == 5) {
        moby_transform_joint_to_world(moby, 3, spark_pos);
    } else {
        moby_transform_joint_to_world(moby, 2, spark_pos);
    }
    FastVecScale(offset_vel, moby + 0xc0, 0.5f);
    FastVecAdd(spark_pos, spark_pos, offset_vel);
    spark_pos[2] -= 0.2f;
    lifetime = 50;
    for (i = 9; i >= 0; i--) {
        vec_random_direction(random_dir, 0.0060000005f, 0.060000002f);
        particle_kind = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
        particle_life = math_random_float_range(0.3f, 1.0f) * 210000.0f;
        spawn_pos[0] = spark_pos[0] + math_random_signed_float_range(0.0f, 0.3f);
        spawn_pos[1] = spark_pos[1] + math_random_signed_float_range(0.0f, 0.3f);
        spawn_pos[2] = spark_pos[2] + math_random_signed_float_range(0.0f, 0.3f);
        particle = part_spawn_spinning_spark_pal(spawn_pos, particle_kind, 0.0f, 1.0f, random_dir, 1.01f, 0x406080, 0, particle_life);
        if (particle) {
            *(unsigned short *)(particle + 0xa) = lifetime;
            particle_data = particle + 0x20;
            particle[3] = 0x44;
            particle[9] = FloatToInt(4.0f) + 0x40;
            *(float *)(particle_data + 0x1c) = IntToFloat(4);
            *(int *)(particle_data + 4) = 3;
            particle_data[0xa] = 0x20;
            particle_data[0xb] = particle[0xa];
        }
    }
}
