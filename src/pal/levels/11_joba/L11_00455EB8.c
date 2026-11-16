#include "include_asm.h"

#include "common.h"
extern char *CreateMoby(int id);
extern float math_random_float_range(float a, float b);
extern float math_random_angle(void);
extern void *part_spawn_ground_effect(void *, unsigned int, int, unsigned int, int, char *, float, float, float, int);
extern char g_identity_l11_matrix[] __attribute__((sda));
typedef int TI128 __attribute__((mode(TI)));

/* func_L11_0044C850 is defined in L11_004465F8-aim-0044C850-g8.c. */

/* Spawns a spinning debris moby from a robot at a position, with a ground dust effect; returns it. */
char *robot_spawn_debris_pal(char *robot, TI128 *velocity, TI128 *position, float scale)
{
    char *debris = CreateMoby(0xDD9);

    if (debris != 0) {
        char *vars;
        float size;

        *(unsigned char *)(debris + 0x30) = 0xFF;
        *(short *)(debris + 0x32) = 0xFF;
        debris[0x31] = 1;
        debris[0x20] = 0;
        *(long long *)(debris + 0x38) = *(long long *)(robot + 0x38);
        qcopy(debris + 0x10, position);
        vars = *(char **)(debris + 0x68);
        qcopy(vars, velocity);
        *(float *)(vars + 0x14) = scale;
        *(char **)(vars + 0x10) = robot;
        *(float *)(vars + 0x18) = math_random_angle();
        *(float *)(vars + 0x1C) = math_random_float_range(0.25132746f, 0.75398237f);
        *(float *)(vars + 0x20) = 0.15f;
        *(unsigned char *)(debris + 0x23) = 0x80;
        *(unsigned short *)(debris + 0x34) |= 0x100;
        *(float *)(debris + 0x2C) = math_random_float_range(0.005f, 0.00625f);
        *(int *)(vars + 0x24) = 0;
        *(unsigned short *)(debris + 0x34) |= 0x200;
        size = math_random_float_range(2.0f, 4.0f);
        *(unsigned short *)(debris + 0x34) |= 0x41;
        part_spawn_ground_effect(debris + 0x10, 3, 0x801060E0, 0, 10, g_identity_l11_matrix, size * 0.3f, size, 0.0f, 0);
        part_spawn_ground_effect(debris + 0x10, 3, -1, 1, -10, g_identity_l11_matrix, size * 0.04f, size * 0.4f, 0.0f, 0);
    }
    return debris;
}

