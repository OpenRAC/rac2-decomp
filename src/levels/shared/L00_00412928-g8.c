#include "include_asm.h"
#include "common.h"

/* func_L00_00412FF8 reads its spawn counters through $gp, and func_L00_004173B0 its
 * spawn configurations, hence -G8. */

extern int D_L00_001B1378 __attribute__((sda));
extern int D_L00_001B137C __attribute__((sda));
extern unsigned short D_L00_001B13DC __attribute__((sda));
extern char D_00189EB0[];
extern char D_L00_0025A1A0[];
extern char D_L00_0025A420[];
extern char *CreateMoby(int id);
extern void euler_rotation_basis(char *dst, char *src);
extern void FastVecScale(float *dst, char *src, float scale);
extern void FastVecAdd(char *dst, char *src, float *local);
extern void wave_line_reset_effect(char *object);

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void cam_compute_view_direction(void *, void *, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void *part_spawn_spinning_particle(float, void *, void *, int, int, int, int, float, int, int, int);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);
extern char D_L00_001B1418 __attribute__((sda));
extern char D_L00_001B13F8 __attribute__((sda));
extern char D_L00_001B1408 __attribute__((sda));
extern char D_L00_001B1428 __attribute__((sda));

/* Creates a lightning arc object for an owner and gives it one of four reusable sets of points. */
char *lightning_arc_spawn(char *owner)
{
    char *moby = CreateMoby(0x1195 /* moby class 4501 */);
    char *vars;
    int counter;
    float offset[4];

    if (moby != 0) {
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        vars = *(char **)(moby + 0x68);
        *(unsigned short *)(vars + 0x1E) = D_L00_001B13DC;
        *(int *)(vars + 0x18) = -1;
        euler_rotation_basis(moby + 0xC0, D_00189EB0);
        counter = D_L00_001B1378;
        *(char **)(vars + 0) = D_L00_0025A1A0 + counter * 0xA0;
        *(char **)(vars + 4) = D_L00_0025A420 + counter * 0x140;
        if ((unsigned int)counter >= 4)
            D_L00_001B1378 = 0;
        D_L00_001B1378 = (D_L00_001B1378 + 1) % 4;
        *(int *)(vars + 0x24) = D_L00_001B137C;
        *(char **)(vars + 0x20) = owner;
        FastVecScale(offset, *(char **)(D_00189EB0 + 0x2200) + 0xE0, 0.75f);
        FastVecAdd(moby + 0x10, D_00189EB0 - 0x10, offset);
        wave_line_reset_effect(moby);
    }
    return moby;
}

/* Emits three effect particles at the object, then four spawns along its velocity at rising heights. */
void part_emit_spark_burst_at_moby(char *moby)
{
    Vec up, velocity, pos, pos2, pos3, pos4;
    char *vars = *(char **)(moby + 0x68);
    int i;
    float angle, random, life, speed, spread, frame;

    cam_compute_view_direction(moby + 0x10, &up, 1);
    if (*(int *)(vars + 4) != 0)
        return;
    frame = 0.016666668f;
    for (i = 0; i < 3; i++) {
        angle = math_random_float_range(-0.9599311948f, -1.3962635994f);
        random = math_random_angle();
        speed = math_random_float_range(0.0f, 0.5f);
        spread = 0.3f;
        frame = 0.016666668f;
        speed *= frame;
        vec_build_spherical_offset(&velocity, speed, random, angle);
        life = math_random_float_range(0.65f, 0.85f) * 210000.0f;
        pos.f[0] = *(float *)(moby + 0x10) + math_random_signed_float_range(0.0f, spread);
        pos.f[1] = *(float *)(moby + 0x14) + math_random_signed_float_range(0.0f, spread);
        pos.f[2] = *(float *)(moby + 0x18) + math_random_signed_float_range(0.0f, spread);
        part_spawn_spinning_particle(life, &pos, &velocity, 0x4F808080, 0x08101010, math_random_int_range(35, 50), 1, 0.5f, 1, -1, 1);
    }
    cam_compute_view_direction(moby + 0x10, &velocity, 1);
    vec_scale_to_length(&velocity, &velocity, 0.2f);
    qcopy_nc(&pos, moby + 0x10);
    pos.f[2] += math_random_float_range(0.1f, 0.4f);
    part_spawn_object_relative_particle(moby, &pos, &velocity, &D_L00_001B1418, math_random_int_below(2));
    qcopy_nc(&pos2, moby + 0x10);
    pos2.f[2] += math_random_float_range(0.9f, 1.2f);
    part_spawn_object_relative_particle(moby, &pos2, &velocity, &D_L00_001B13F8, math_random_int_below(2));
    qcopy_nc(&pos3, moby + 0x10);
    pos3.f[2] += math_random_float_range(0.8f, 1.5f);
    part_spawn_object_relative_particle(moby, &pos3, &velocity, &D_L00_001B1408, math_random_int_below(2));
    qcopy_nc(&pos4, moby + 0x10);
    part_spawn_object_relative_particle(moby, &pos4, &velocity, &D_L00_001B1428, math_random_int_below(2));
}
