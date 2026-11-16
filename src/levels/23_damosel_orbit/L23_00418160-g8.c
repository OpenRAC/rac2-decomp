#include "names.h"
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

/* Fires a shot from the gun joint at the next target in the ring, starts the beam effect and plays its sound. */
void mothership_fire_gun_at_target(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *obj = g_mothership_crowd_mobys[g_boss_part_index];
    char *p16;
    float backOffset[4];
    float jointPos[4];
    float jointMatrix[16];
    float dirVec[4];
    float flatPos[4];
    int mode;

    mode = *(unsigned char *)(moby + 0x20);
    if (mode == 0xC || mode == 0x10)
        *(int *)(state + 0x598) = g_gun_state_value_b;
    else
        *(int *)(state + 0x598) = g_gun_state_value_a;
    *(int *)(state + 0x59C) = (int)obj;
    *(int *)(state + 0x590) = *(int *)(state + 0x590) - 1;
    moby_transform_joint_to_world(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointPos);
    g_gun_joint_position = *(TI128 *)jointPos;
    moby_transform_joint_point(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointMatrix);
    FastVecScale((char *)backOffset, (char *)(jointMatrix + 8), -16.0f);
    *(TI128 *)flatPos = *(TI128 *)jointPos;
    mothership_project_point_onto_surface((char *)flatPos, 0.0f);
    p16 = obj + 0x10;
    FastVecSub((char *)dirVec, (char *)flatPos, state + 0x3E0);
    FastVecScale((char *)dirVec, (char *)dirVec, 2.2f);
    FastVecAdd((char *)backOffset, (char *)backOffset, (char *)dirVec);
    FastVecAdd((char *)jointPos, (char *)jointPos, (char *)backOffset);
    if (*(unsigned char *)(obj + 0x20) != 2) {
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(moby + 0xC0);
        *(TI128 *)(obj + 0xD0) = *(TI128 *)(moby + 0xD0);
        *(TI128 *)(obj + 0xE0) = *(TI128 *)(moby + 0xE0);
        *(TI128 *)p16 = *(TI128 *)jointPos;
    }
    FastVecScale(g_gun_aim_offset, moby + 0xE0, g_gun_direction_scale);
    FastVecAdd(g_gun_aim_offset, g_gun_aim_offset, p16);
    if (g_gun_trail_effect_a == 0)
        g_gun_trail_effect_a = (int)ribbon_trail_create((char *)&g_gun_joint_position, 1.7f, moby, 1.9f, g_gun_aim_offset, 0.5f, 0x32,
                                                g_gun_shot_param_float, 0x46, g_gun_shot_param_short_a, g_gun_shot_param_short_b,
                                                0xF7F0F, 0x2F00, 1, -1, 1);
    moby_set_state(obj, 1, 0);
    PlayMobySound(4, 0, moby);
    g_boss_part_index = (g_boss_part_index + 1) % 25;
}
