#include "include_asm.h"

#include "common.h"
extern float g_hit_damage_b __attribute__((sda));
extern float g_hit_damage_a __attribute__((sda));
extern char g_collision_l05_result[];
extern void vec_scale_to_length(void *, void *, float);
extern void QueueMobyImpact(void *, void *);
extern char *func_L05_003D1E60(void *, int, int);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_range(int, int);
extern char *part_spawn_spinning_spark_pal(void *, int, float, float, float, void *, int, int, float);
extern int math_random_int_below(int);
struct HitRecord {
    float pos[4];
    void *obj;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float damage;
    int one;
    char pad[12];
};

/* Applies damage to the thing a shot hit and makes a small spray of sparks when the target is a special one (PAL). */
void feltzin_shot_hit_pal(char *obj, char *input, float *output)
{
    struct HitRecord hit __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    int i;
    char *table;
    hit.flags = 0x810000;
    hit.obj = obj;
    if (*(int *)(input + 0x24))
        hit.damage = g_hit_damage_b;
    else
        hit.damage = g_hit_damage_a;
    hit.one = 1;
    qcopy(hit.pos, input);
    vec_scale_to_length(&hit, &hit, 1.0f);
    table = g_collision_l05_result;
    hit.pos[3] = 5627.9248046875f;
    hit.type = 3;
    hit.subtype = 2;
    hit.id = *(unsigned short *)(obj + 0xAA);
    if (*(char **)(table + 0x18))
        QueueMobyImpact(*(char **)(table + 0x18), &hit);
    func_L05_003D1E60(obj + 0x10, 0, 0);
    if (*(char **)(table + 0x18) && *(short *)(*(char **)(table + 0x18) + 0xAA) == 0x956) {
        float count = 20.0f, scale = 3.0f, spread = 2.0f;
        qcopy(pos, obj + 0x10);
        for (i = 0; (float)i < count; i++) {
            float yaw, pitch;
            char *particle;
            output[0] = pos[0] + math_random_signed_float_range(0.0f, spread);
            output[1] = pos[1] + math_random_signed_float_range(0.0f, spread);
            output[2] = pos[2] + math_random_signed_float_range(0.0f, spread);
            yaw = math_random_angle();
            pitch = math_random_angle();
            vec_build_spherical_offset(vel, 0.060000002f, yaw, pitch);
            particle = part_spawn_spinning_spark_pal(output, math_random_int_range(-3, 3), 0.0f, 1.0f, 1.0f, vel, 0x7FFFFFFF, 0, scale * 210000.0f);
            if (particle) {
                char *particle_data = particle + 0x20;
                *(short *)(particle + 0xA) = 100;
                *(unsigned char *)(particle + 8) = math_random_int_below(255);
                particle[3] = 0x44;
                *(int *)(particle_data + 4) = 2;
                particle_data[0xA] = 127;
                particle_data[0xB] = *(unsigned char *)(particle + 0xA);
            }
        }
    }
}

typedef int TI128 __attribute__((mode(TI)));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);
extern float g_particle_params_first[] SDATA(D_L05_001AFC60);
extern float g_particle_params_second[] SDATA(D_L05_001AFC70);
extern float g_particle_params_third[] SDATA(D_L05_001AFC80);

/* For each of two points in the object's frame, either side of it in Y, makes three copies of the
   point and passes each to func_L00_0033C0D0 with a random speed. */
void feltzin_enemy_spawn_exhaust_pal(char *obj)
{
    float left_offset[4] __attribute__((aligned(16)));
    float speed[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float p1[4] __attribute__((aligned(16)));
    float p2[4] __attribute__((aligned(16)));
    float p3[4] __attribute__((aligned(16)));
    float right_offset[4] __attribute__((aligned(16)));
    float factor;
    float y;

    *(TI128 *)left_offset = 0;
    left_offset[0] = -0.21f;
    left_offset[1] = 0.061f;
    *(TI128 *)speed = 0;
    left_offset[2] = 0.045f;
    left_offset[3] = 1.0f;
    matrix_mul_vec3(point, left_offset, obj + 0xC0);
    factor = 0.4f;
    FastVecAdd(point, point, obj + 0x10);
    point[3] = 0;
    qcopy(p1, point);
    qcopy(p2, point);
    qcopy(p3, point);
    vec_add_random_offset(point, 0.1f);
    vec_add_random_offset(p1, 0.1f);
    vec_add_random_offset(p2, 0.1f);
    vec_add_random_offset(p3, 0.1f);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p1, speed, g_particle_params_first, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p2, speed, g_particle_params_second, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p3, speed, g_particle_params_third, 1);
    y = -0.061f;
    *(TI128 *)right_offset = 0;
    right_offset[0] = -0.21f;
    right_offset[1] = y;
    right_offset[2] = 0.045f;
    right_offset[3] = 1.0f;
    matrix_mul_vec3(point, right_offset, obj + 0xC0);
    FastVecAdd(point, point, obj + 0x10);
    point[3] = 0;
    qcopy(p1, point);
    qcopy(p2, point);
    qcopy(p3, point);
    vec_add_random_offset(point, 0.1f);
    vec_add_random_offset(p1, 0.1f);
    vec_add_random_offset(p2, 0.1f);
    vec_add_random_offset(p3, 0.1f);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p1, speed, g_particle_params_first, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p2, speed, g_particle_params_second, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p3, speed, g_particle_params_third, 1);
}
