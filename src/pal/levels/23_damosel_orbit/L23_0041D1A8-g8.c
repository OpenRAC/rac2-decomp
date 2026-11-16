#include "names.h"
/* func_PAL_L23_0041D1A8, the PAL copy of func_L23_00418160: the same C, where both
 * arms of the timer store are scaled to 50 Hz; cross-jumping shares their tail.
 */
/* The quadword profile preserves the six aligned transfers. The effect-call
 * declaration interleaves typed integer/FP arguments while preserving each EE
 * register bank's order and the four stack words of func_L23_004256F0.
 */
typedef int TI128 __attribute__((mode(TI)));

extern float g_gun_direction_scale __attribute__((sda));

extern TI128 g_gun_joint_position __attribute__((sda));

extern char g_gun_aim_offset[16] __attribute__((sda));

extern int g_gun_trail_effect_a;

extern char *g_mothership_crowd_mobys[];

extern void moby_transform_joint_to_world(char *, int, char *);

extern void moby_transform_joint_point(char *, int, char *);

extern void FastVecScale(char *, char *, float);

extern void FastVecAdd(char *, char *, char *);

extern void FastVecSub(char *, char *, char *);

extern int g_boss_part_index __attribute__((sda));

extern int g_gun_state_value_a __attribute__((sda));

extern int g_gun_state_value_b __attribute__((sda));

extern float g_gun_shot_param_float __attribute__((sda));

extern short g_gun_shot_param_short_a __attribute__((sda));

extern short g_gun_shot_param_short_b __attribute__((sda));

extern void mothership_project_point_onto_surface(char *, float);

extern void moby_set_state(char *, int, int);

extern int PlayMobySound(int, int, char *);

extern void *ribbon_trail_create(char *, float, char *, float, char *, float, unsigned char, float,
                               unsigned char, short, short, int, int, int, int, int);

void func_PAL_L23_0041D1A8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *obj = g_mothership_crowd_mobys[g_boss_part_index];
    char *p16;
    float B[4];
    float A[4];
    float M[16];
    float D[4];
    float C[4];
    int type;

    type = *(unsigned char *)(arg0 + 0x20);
    if (type == 0xC || type == 0x10)
        *(int *)(state + 0x598) = (((int)(g_gun_state_value_b) * 5 + 2) / 6);
    else
        *(int *)(state + 0x598) = (((int)(g_gun_state_value_a) * 5 + 2) / 6);
    *(int *)(state + 0x59C) = (int)obj;
    *(int *)(state + 0x590) = *(int *)(state + 0x590) - 1;
    moby_transform_joint_to_world(arg0, *(int *)(state + 0x594) + 0x1E, (char *)A);
    g_gun_joint_position = *(TI128 *)A;
    moby_transform_joint_point(arg0, *(int *)(state + 0x594) + 0x1E, (char *)M);
    FastVecScale((char *)B, (char *)(M + 8), -16.0f);
    *(TI128 *)C = *(TI128 *)A;
    mothership_project_point_onto_surface((char *)C, 0.0f);
    p16 = obj + 0x10;
    FastVecSub((char *)D, (char *)C, state + 0x3E0);
    FastVecScale((char *)D, (char *)D, 2.2f);
    FastVecAdd((char *)B, (char *)B, (char *)D);
    FastVecAdd((char *)A, (char *)A, (char *)B);
    if (*(unsigned char *)(obj + 0x20) != 2) {
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(arg0 + 0xC0);
        *(TI128 *)(obj + 0xD0) = *(TI128 *)(arg0 + 0xD0);
        *(TI128 *)(obj + 0xE0) = *(TI128 *)(arg0 + 0xE0);
        *(TI128 *)p16 = *(TI128 *)A;
    }
    FastVecScale(g_gun_aim_offset, arg0 + 0xE0, g_gun_direction_scale);
    FastVecAdd(g_gun_aim_offset, g_gun_aim_offset, p16);
    if (g_gun_trail_effect_a == 0)
        g_gun_trail_effect_a = (int)ribbon_trail_create((char *)&g_gun_joint_position, 1.7f, arg0, 1.9f, g_gun_aim_offset, 0.5f, 0x32,
                                                g_gun_shot_param_float, 0x46, g_gun_shot_param_short_a, g_gun_shot_param_short_b,
                                                0xF7F0F, 0x2F00, 1, -1, 1);
    moby_set_state(obj, 1, 0);
    PlayMobySound(4, 0, arg0);
    g_boss_part_index = (g_boss_part_index + 1) % 25;
}
