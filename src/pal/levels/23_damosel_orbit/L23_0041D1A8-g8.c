#include "names.h"
/* func_PAL_L23_0041D1A8, the PAL copy of func_L23_00418160: the same surface_point, where both
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

/* Fires a shot from the gun joint toward the next ring target part and starts its ribbon trail. (PAL: 50 Hz timings) */
void mothership_fire_gun_at_target_pal(char *gun_moby) {
    char *state = *(char **)(gun_moby + 0x68);
    char *part = g_mothership_crowd_mobys[g_boss_part_index];
    char *part_pos;
    float aim_offset[4];
    float joint_pos[4];
    float joint_matrix[16];
    float surface_delta[4];
    float surface_point[4];
    int part_type;

    part_type = *(unsigned char *)(gun_moby + 0x20);
    if (part_type == 0xC || part_type == 0x10)
        *(int *)(state + 0x598) = (((int)(g_gun_state_value_b) * 5 + 2) / 6);
    else
        *(int *)(state + 0x598) = (((int)(g_gun_state_value_a) * 5 + 2) / 6);
    *(int *)(state + 0x59C) = (int)part;
    *(int *)(state + 0x590) = *(int *)(state + 0x590) - 1;
    moby_transform_joint_to_world(gun_moby, *(int *)(state + 0x594) + 0x1E, (char *)joint_pos);
    g_gun_joint_position = *(TI128 *)joint_pos;
    moby_transform_joint_point(gun_moby, *(int *)(state + 0x594) + 0x1E, (char *)joint_matrix);
    FastVecScale((char *)aim_offset, (char *)(joint_matrix + 8), -16.0f);
    *(TI128 *)surface_point = *(TI128 *)joint_pos;
    mothership_project_point_onto_surface((char *)surface_point, 0.0f);
    part_pos = part + 0x10;
    FastVecSub((char *)surface_delta, (char *)surface_point, state + 0x3E0);
    FastVecScale((char *)surface_delta, (char *)surface_delta, 2.2f);
    FastVecAdd((char *)aim_offset, (char *)aim_offset, (char *)surface_delta);
    FastVecAdd((char *)joint_pos, (char *)joint_pos, (char *)aim_offset);
    if (*(unsigned char *)(part + 0x20) != 2) {
        *(TI128 *)(part + 0xC0) = *(TI128 *)(gun_moby + 0xC0);
        *(TI128 *)(part + 0xD0) = *(TI128 *)(gun_moby + 0xD0);
        *(TI128 *)(part + 0xE0) = *(TI128 *)(gun_moby + 0xE0);
        *(TI128 *)part_pos = *(TI128 *)joint_pos;
    }
    FastVecScale(g_gun_aim_offset, gun_moby + 0xE0, g_gun_direction_scale);
    FastVecAdd(g_gun_aim_offset, g_gun_aim_offset, part_pos);
    if (g_gun_trail_effect_a == 0)
        g_gun_trail_effect_a = (int)ribbon_trail_create((char *)&g_gun_joint_position, 1.7f, gun_moby, 1.9f, g_gun_aim_offset, 0.5f, 0x32,
                                                g_gun_shot_param_float, 0x46, g_gun_shot_param_short_a, g_gun_shot_param_short_b,
                                                0xF7F0F, 0x2F00, 1, -1, 1);
    moby_set_state(part, 1, 0);
    PlayMobySound(4, 0, gun_moby);
    g_boss_part_index = (g_boss_part_index + 1) % 25;
}
