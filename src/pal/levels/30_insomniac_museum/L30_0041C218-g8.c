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

/* Creates a museum projectile with the given velocity, owner and scale, turned to face its direction, with two spark effects at its start (PAL version). */
char *museum_projectile_spawn_pal(char *owner, float *velocity, void *position, int type, float scale) {
    char *projectile = CreateMoby(0x11EA);
    char *vars;
    float angle, size;
    if (projectile) {
        *(unsigned char *)(projectile + 0x30) = 0xFF;
        *(unsigned short *)(projectile + 0x32) = 0xFF;
        *(unsigned char *)(projectile + 0x31) = 1;
        *(unsigned char *)(projectile + 0xBC) = type;
        *(unsigned char *)(projectile + 0x20) = 0;
        *(unsigned long long *)(projectile + 0x38) = *(unsigned long long *)(owner + 0x38);
        qcopy(projectile + 0x10, position);
        vars = *(char **)(projectile + 0x68);
        qcopy(vars, velocity);
        *(char **)(vars + 0x10) = owner;
        *(float *)(vars + 0x14) = scale;
        *(float *)(vars + 0x20) = 0.15f;
        *(unsigned short *)(projectile + 0x34) |= 0x208;
        *(float *)(projectile + 0xF8) = FastAddRotations(mat_fast_helper_a(velocity[0], velocity[1]), 1.5707964897155762f);
        *(float *)(projectile + 0xF0) = -mat_fast_helper_a(vec_length_xy(velocity), velocity[2]);
        angle = math_random_angle();
        math_apply_axis_rotation_to_quat(projectile + 0xE0, projectile + 0xE0, projectile + 0xD0, angle);
        math_apply_axis_rotation_to_quat(projectile + 0xC0, projectile + 0xC0, projectile + 0xD0, angle);
        euler_rotation_basis(projectile + 0xC0, projectile + 0xF0);
        *(unsigned char *)(projectile + 0x23) = 0x80;
        *(float *)(projectile + 0x2C) = g_projectile_spawn_scale;
        *(unsigned short *)(projectile + 0x34) |= 0x100;
        *(int *)(vars + 0x24) = 0;
        size = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(projectile + 0x10, 12, g_spark_particle_texture_a, size * 0.3f, size, 0, 10, g_particle_spawn_template, 0.0f, 0);
        part_spawn_ground_effect(projectile + 0x10, 12, g_spark_particle_texture_b, size * 0.04f, size * 0.4f, 1, -10, g_particle_spawn_template, 0.0f, 0);
    }
    return projectile;
}
