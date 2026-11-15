#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern unsigned int D_L16_001B2648 MACRO_ADDR;
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void *part_spawn_scaling(void *, void *, int, int, int, int, int, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Emits two particle layers from five bones, with velocity chosen by bone group. */
void EmitSnivelakBoneParticles(u8 *moby)
{
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float clear[4] __attribute__((aligned(16)));
    int bone, lifetime, size;
    for (bone = 5; bone < 8; bone++) {
        *(TI128 *)clear = 0;
        clear[2] = -(math_random_float_range(4.5f, 5.5f) * 0.016666668f);
        *(TI128 *)velocity = *(TI128 *)clear;
        moby_transform_joint_to_world(moby, bone, position);
        if (D_L16_001B2648 & 1) {
            size = math_random_int_range(18, 22);
            part_spawn_scaling(position, velocity, 0xcf0000ff, 0xcf, size, 180, -10, 1);
        } else {
            size = math_random_int_range(20, 24);
            part_spawn_scaling(position, velocity, 0x6000ffff, 0x80, size, 350, -10, 1);
        }
        lifetime = math_random_int_range(20, 90);
        size = math_random_int_range(10, 15);
        part_spawn_scaling(position, velocity, 0xefff7f4f, 0xff0000, size, lifetime, -lifetime, 1);
    }
    for (bone = 3; bone < 5; bone++) {
        vec_scale_to_length(velocity, moby + 0xc0, -(math_random_float_range(4.5f, 5.5f) * 0.016666668f));
        moby_transform_joint_to_world(moby, bone, position);
        if (D_L16_001B2648 & 1) {
            size = math_random_int_range(18, 22);
            part_spawn_scaling(position, velocity, 0xcf0000ff, 0xcf, size, 50, -10, 1);
        } else {
            size = math_random_int_range(20, 24);
            part_spawn_scaling(position, velocity, 0x6000ffff, 0x80, size, 100, -10, 1);
        }
        lifetime = math_random_int_range(10, 25);
        size = math_random_int_range(10, 15);
        part_spawn_scaling(position, velocity, 0xefff7f4f, 0xff0000, size, lifetime, -lifetime, 1);
    }
}
