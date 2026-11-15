#include "include_asm.h"


#include "common.h"
typedef int Quad_Dobbo __attribute__((mode(TI)));
extern float math_random_float_range(float, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern float IntToFloat(int);
extern char *part_spawn_scaling(void *, void *, int, int, int, int, int, int);

void func_PAL_L09_0040E1C0(char *obj)
{
    float pos[3];
    float vel[3];
    float initial[3];
    int i;
    *(Quad_Dobbo *)initial = 0;
    initial[2] = -(math_random_float_range(3.5f, 4.5f) * 0.020000001f);
    *(Quad_Dobbo *)vel = *(Quad_Dobbo *)initial;
    for (i = 0; i < 2; i++) {
        moby_transform_joint_to_world(obj, 2, pos);
        pos[2] += IntToFloat(i) * 0.015f;
        if (i & 1)
            part_spawn_scaling(pos, vel, 0x77FF0000, 0xFF0060, 14, 150, -100, 1);
        else
            part_spawn_scaling(pos, vel, 0x77FF0060, 0xFF0000, 16, 220, -100, 1);
        part_spawn_scaling(pos, vel, 0x77FFFFFF, 0xFF0000, 8, 80, -80, 1);
    }
}



/* func_PAL_L09_0040FD68 lives in L09_0040FD68-g8.c. */
