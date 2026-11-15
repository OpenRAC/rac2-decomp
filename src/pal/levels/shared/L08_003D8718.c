#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void *func_PAL_L08_003B6448(void *, void *, void *, int);
extern float math_random_float_range(float, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_range(int, int);
extern u8 *part_spawn_velocity_particle(void *, void *, int, int, float);
typedef int TI128 __attribute__((mode(TI)));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L08_001B22E0[] __attribute__((sda));
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_L08_001A7C80[] __attribute__((sda));
extern u8 D_001395B8[];
extern u8 D_L08_001BFD00[];

void func_PAL_L08_003D8718(u8 *self)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float random[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(self + 0x68);
    int i;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        moby_mark_spawned(self);
        return;
    }
    if ((self[0x60] & 2) && self[0x43])
        func_PAL_002A7E68(self, 0, 0, 0);
    if (self[0xBC]) {
        self[0xBC] = 0;
        if (self[0x43] != 1) func_PAL_002A7E68(self, 1, 0, 0);
        vec_build_spherical_offset(direction, 1.2f, *(float *)(self+0xF8), -*(float *)(self+0xF4));
        moby_transform_joint_to_world(self, 0, position);
        func_PAL_L08_003B6448(self, position, direction, 0x4B);
        i = 4;
        do {
            *(TI128 *)random = 0;
            random[0] = math_random_float_range(-1.0f, 1.0f);
            random[1] = math_random_float_range(-1.0f, 1.0f);
            random[2] = math_random_float_range(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)random;
            vec_scale_to_length(velocity, velocity, FastVecLength(direction)*0.5799999f);
            FastVecAdd(velocity, direction, velocity);
            vec_scale_to_length(velocity, velocity, math_random_float_range(0.060000002f, 0.120000005f));
            part_spawn_velocity_particle(position, velocity, 0x5F2F4F6F, math_random_int_range(4,8), 50000.0f);
        } while (--i >= 0);
        vec_scale_to_length(direction, direction, 0.010000001f);
        part_spawn_velocity_particle(position, direction, 0x2F4F7F7F, math_random_int_range(3,6), 500000.0f);
    }
}

