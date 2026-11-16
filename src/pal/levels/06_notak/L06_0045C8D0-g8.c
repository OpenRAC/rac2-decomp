#include "include_asm.h"

#include "common.h"
extern u8 *g_group_l06_id_lists[];
extern float g_ring_spin_speed_x __attribute__((sda));
extern float g_ring_spin_speed_y;
extern float g_ring_spin_speed_z;
extern float FastAddRotations(float, float);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void moby_init_between_points(u8 *, void *, void *);

/* Turns the owner's three angles by the level's step, then walks the owner's eight records:
   each gets a fresh object, scaled and blended against the owner's own axes. `axes` is the
   scratch area func_002833F0 fills; its first vector is the one the objects are given. */
void object_ring_spin_update_pal(char *a0)
{
    float axes[12];
    float v0[4];
    float v1[4];
    char *s0 = *(char **)(a0 + 0x68);
    char *s3 = s0 + 0xA0;
    char *s2 = s0 + 0x80;
    char *s4 = a0 + 0x10;
    float step = 0.0003490659f;
    float one = 1.0f;
    float two = 2.0f;
    int i;

    *(float *)(s0 + 0x120) = FastAddRotations(*(float *)(s0 + 0x120), g_ring_spin_speed_x * step);
    *(float *)(s0 + 0x124) = FastAddRotations(*(float *)(s0 + 0x124), g_ring_spin_speed_y * step);
    *(float *)(s0 + 0x128) = FastAddRotations(*(float *)(s0 + 0x128), g_ring_spin_speed_z * step);
    euler_rotation_basis(axes, s0 + 0x120);
    for (i = 7; i >= 0; i--) {
        matrix_mul_vec3(v0, s3, axes);
        s3 += 0x10;
        FastVecScale((char *)v0, (char *)v0, 3.0f);
        FastVecScale((char *)v1, (char *)v0, 3.3333335f);
        FastVecAdd((char *)v0, (char *)v0, s4);
        FastVecAdd((char *)v1, (char *)v1, s4);
        v0[3] = one;
        v1[3] = two;
        moby_init_between_points(*(u8 **)s2, v0, v1);
        s2 += 4;
    }
}
