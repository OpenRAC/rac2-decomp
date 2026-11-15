#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L16_001B18A0 __attribute__((sda));
extern float D_L16_001B18A4;
extern u32 D_L16_001B18A8 __attribute__((sda));
extern u32 D_L16_001B18AC;
extern u32 D_L16_001B18B0;
extern u32 D_L16_001B18B4;
extern u32 D_L16_001B18B8;
extern u32 D_L16_001B18BC;
extern u32 D_L16_001B18C0 __attribute__((sda));
extern u32 D_L16_001B18C4;
extern u32 D_L16_001B18C8;
extern s32 D_L16_001B2648;

extern void moby_transform_joint_to_world(char *, int, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern char *part_spawn_scaling(void *, void *, u32, s32, s32, s32, s32, s32);

/* The burst of func_L02_00401D38, from the object's two attachment points (func_0029FCC0)
   instead of a fixed pair of vectors. */
/* Emits a small burst of fire particles from the object's two attach points. */
void snivelak_emit_fire_burst(char *moby) {
    float position[4];
    float velocity[4];
    float fall[4];
    s32 i;
    float speed;
    float rate = 0.016666668f;

    for (i = 0; i < 2; i++) {
        *(TI128 *)fall = 0;
        speed = math_random_float_range(D_L16_001B18A0, D_L16_001B18A4);
        fall[2] = -(speed * rate);
        *(TI128 *)velocity = *(TI128 *)fall;
        moby_transform_joint_to_world(moby, i, position);
        if (D_L16_001B2648 & 1) {
            part_spawn_scaling(position, velocity, D_L16_001B18A8, D_L16_001B18AC, math_random_int_range(0x12, 0x16), D_L16_001B18C0, -10, 1);
        } else {
            part_spawn_scaling(position, velocity, D_L16_001B18B0, D_L16_001B18B4, math_random_int_range(0x14, 0x18), D_L16_001B18C4, -10, 1);
        }
        part_spawn_scaling(position, velocity, D_L16_001B18B8, D_L16_001B18BC, math_random_int_range(0xA, 0xF), D_L16_001B18C8, -10, 1);
    }
}
