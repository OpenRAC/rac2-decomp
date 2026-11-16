#include "include_asm.h"

#include "common.h"
extern void FastVecSub(float *off, float *v, char *p);
extern void vec_scale_to_length(float *dst, float *src, float angle);
typedef unsigned int JointEffectQuad __attribute__((mode(TI)));
extern void moby_transform_joint_point(char *, int, float *);
extern void FastVecAdd(float *, float *, float *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_add_random_offset(float *, float);
extern int coll_sweep_from_object(char *, float *, float, int, float, float, int, int, int);
extern void *part_spawn_gravity_fade(float *, float *, float, float, float, int, int, int, int, int, int);
extern unsigned char *part_spawn_burst_pal(float *, float *, int, int, int, int,
                                    float, float, float, float, float);
extern unsigned char *g_particle_texture_table[];

/* Effect at an object's joint: func_002A8C28 at the joint and at two points along its axis,
   three grey func_002C65A0 particles at the joint and one func_PAL_002C23B8 particle at the near
   point, which at random takes flags 0x48 and the 0x707070 tint. */
void part_spawn_joint_hit_effects_pal(char *object, float *position, int joint, float intensity)
{
    float matrix[16] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float base[4] __attribute__((aligned(16)));
    float near[4] __attribute__((aligned(16)));
    float far[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    int i, j;
    float start, end, gravity;
    unsigned char *particle;

    moby_transform_joint_point(object, joint, matrix);
    qcopy(axis, matrix + 4);
    FastVecSub(base, matrix + 12, (char *)position);
    vec_scale_to_length(near, axis, 0.85f);
    vec_scale_to_length(far, axis, 1.6f);
    FastVecAdd(near, near, base);
    FastVecAdd(far, far, base);
    near[2] -= 0.1f;
    far[2] -= 0.1f;
    vec_scale_to_length(velocity, matrix + 4, 0.3f);
    FastVecAdd(velocity, velocity, position);
    coll_sweep_from_object(object, base, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    coll_sweep_from_object(object, near, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    coll_sweep_from_object(object, far, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    for (i = 0; i < 3; i++) {
        vec_add_random_offset(base, 0.1f);
        start = math_random_float_range(0.2f, 0.4f) * 2.1e+05f;
        end = math_random_float_range(1.0f, 1.5f) * 2.1e+05f;
        gravity = math_random_signed_float_range(0.0f, 0.01f);
        part_spawn_gravity_fade(base, velocity, start, end, gravity, 6, 0x808080, 30, 127, 32, 0);
    }
    *(JointEffectQuad *)drift = 0;
    drift[2] = 0.1f;
    drift[3] = 1.0f;
    FastVecAdd(drift, drift, position);
    for (j = 0; j < 1; j++) {
        particle = part_spawn_burst_pal(near, drift, 12, 60, 0x606060, 3,
                                 1.05e+05f, 2.1e+04f, 1.0f, -0.0002f, 0.0f);
        if (particle) {
            particle[2] = *g_particle_texture_table[23];
            particle[3] = 0x44;
            if (math_random_int_range(0, 1)) {
                unsigned char *payload;
                unsigned short alpha;
                particle[3] = 0x48;
                alpha = 127;
                *(unsigned int *)(particle + 4) = 0x70707F;
                payload = particle + 0x20;
                payload[0x11] = 0x70;
                payload[0x12] = 0x70;
                payload[0x13] = 0x70;
                *(unsigned short *)(payload + 0x1E) = alpha;
            }
        }
    }
}



extern void moby_mark_spawned(void *);
extern int cam_moby_update_pal(char *);
extern void moby_set_state(unsigned char *, unsigned char, int);

/* Updates one piece of robot debris: it flies, then fades out and goes away. */
void part_update_fading_debris_pal(char *object)
{
    char *data = *(char **)(object + 0x68);
    *(float *)(data + 4) -= 0.012f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (cam_moby_update_pal(object)) {
            moby_set_state((unsigned char *)object, 1, -1);
            *(unsigned short *)(object + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update_pal(object);
        if (*(unsigned char *)(object + 0x23) < 2)
            moby_mark_spawned(object);
        else
            *(unsigned char *)(object + 0x23) -= 2;
        break;
    }
}
