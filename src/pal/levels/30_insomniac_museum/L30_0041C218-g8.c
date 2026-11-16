#include "include_asm.h"

#include "common.h"
extern char *CreateMoby(int);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float vec_length_xy(void *);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float, float);
extern void *part_spawn_ground_effect(void *, int, int, float, float, int, int, void *, float, int);
extern float g_projectile_spawn_scale __attribute__((sda));
extern int g_spark_particle_texture_a __attribute__((sda)), g_spark_particle_texture_b __attribute__((sda));
extern char g_particle_spawn_template[] __attribute__((sda)) NOT_SDA;

char *museum_projectile_spawn_pal(char *owner, float *velocity, void *position, int type, float scale) {
    char *obj = CreateMoby(0x11EA);
    char *st;
    float angle, size;
    if (obj) {
        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned char *)(obj + 0xBC) = type;
        *(unsigned char *)(obj + 0x20) = 0;
        *(unsigned long long *)(obj + 0x38) = *(unsigned long long *)(owner + 0x38);
        qcopy(obj + 0x10, position);
        st = *(char **)(obj + 0x68);
        qcopy(st, velocity);
        *(char **)(st + 0x10) = owner;
        *(float *)(st + 0x14) = scale;
        *(float *)(st + 0x20) = 0.15f;
        *(unsigned short *)(obj + 0x34) |= 0x208;
        *(float *)(obj + 0xF8) = FastAddRotations(mat_fast_helper_a(velocity[0], velocity[1]), 1.5707964897155762f);
        *(float *)(obj + 0xF0) = -mat_fast_helper_a(vec_length_xy(velocity), velocity[2]);
        angle = math_random_angle();
        math_apply_axis_rotation_to_quat(obj + 0xE0, obj + 0xE0, obj + 0xD0, angle);
        math_apply_axis_rotation_to_quat(obj + 0xC0, obj + 0xC0, obj + 0xD0, angle);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        *(unsigned char *)(obj + 0x23) = 0x80;
        *(float *)(obj + 0x2C) = g_projectile_spawn_scale;
        *(unsigned short *)(obj + 0x34) |= 0x100;
        *(int *)(st + 0x24) = 0;
        size = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(obj + 0x10, 12, g_spark_particle_texture_a, size * 0.3f, size, 0, 10, g_particle_spawn_template, 0.0f, 0);
        part_spawn_ground_effect(obj + 0x10, 12, g_spark_particle_texture_b, size * 0.04f, size * 0.4f, 1, -10, g_particle_spawn_template, 0.0f, 0);
    }
    return obj;
}
