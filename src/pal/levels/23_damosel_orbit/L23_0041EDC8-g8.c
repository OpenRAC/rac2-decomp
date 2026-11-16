#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int g_shield_fade_state __attribute__((sda));
extern int g_shield_fade_frames __attribute__((sda));
extern float g_shield_fade_time_scale __attribute__((sda));
extern float g_shield_fade_extra_scale __attribute__((sda));
extern float g_boss_turn_speed_default __attribute__((sda));
extern float g_boss_turn_speed_mode_sixteen __attribute__((sda));
extern float g_boss_turn_speed_mode_thirteen __attribute__((sda));
extern float g_boss_turn_speed_negative __attribute__((sda));
extern int g_boss_half_time_frames __attribute__((sda));
extern int g_boss_part_mode_flag __attribute__((sda));
extern int g_enemy_relocate_count;
extern Quad g_mothership_shot_origin MACRO_ADDR;
extern Quad g_mothership_aim_direction MACRO_ADDR;
extern float g_mothership_aim_dot;
extern int g_mothership_line_clear;
extern char g_boss_joint_world_pos[] MACRO_ADDR;
extern char g_player_target_point[] MACRO_ADDR;
extern char *g_hero_moby __attribute__((nosda));
extern void vec_clear_128(Quad *);
extern void moby_transform_joint_point(char *, int, char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern float FastVecDot(char *, char *);
extern int CollLine(void *, void *, int, void *, int);
extern void FastVecCross(char *, char *, char *);
extern float math_fast_angle_helper(float);
extern float math_fast_float_g(float);
extern float FastAddRotations(float, float);
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);
extern void build_axis_rotation_quaternion(void *, int, float);
extern float fast_subtract_rotations(float, float);
extern void mothership_turn_joints_pal(char *, float, float);

/* Update the aiming aim_direction and its signed turn rate. */
int UpdateAimTurn_pal(char *object, char *target) {
    struct { Quad zero, matrix[4], axis, aim_direction, cross; } local;
    char *state = *(char **)(object + 0x68);
    char *aim_direction;
    float speed, dot, angle;
    unsigned int mode;
    vec_clear_128(&local.zero);
    ((float *)&local.zero)[3] = 1.0f;
    ((unsigned char *)state)[0x473] = 1;
    *(Quad *)(state + 0x480) = local.zero;
    moby_transform_joint_point(object, 39, (char *)local.matrix);
    qcopy(&g_mothership_shot_origin, &local.matrix[3]);
    qcopy(&g_mothership_aim_direction, &local.matrix[0]);
    if (g_shield_fade_state) return 0;
    local.axis = 0;
    ((float *)&local.axis)[2] = 1.0f;
    ((float *)&local.axis)[3] = 1.0f;
    FastVecScale(state + 0x4A0, (char *)&local.axis,
        (float)g_shield_fade_frames * g_shield_fade_time_scale * g_shield_fade_extra_scale);
    moby_transform_joint_to_world(object, 42, (char *)&local.axis);
    FastVecSub((char *)&local.aim_direction, target, (char *)&local.axis);
    vec_scale_to_length((char *)&local.aim_direction, (char *)&local.aim_direction, 1.0f);
    g_mothership_aim_dot = FastVecDot((char *)&local.aim_direction, (char *)&g_mothership_aim_direction);
    g_mothership_line_clear = CollLine(g_boss_joint_world_pos, g_player_target_point, 16, g_hero_moby, 0) == 0;
    aim_direction = (char *)&local.aim_direction;
    speed = g_boss_turn_speed_default * 0.0003490659f;
    if (((unsigned char *)state)[0x404] && ((unsigned char *)state)[0x405]) {
        mode = ((unsigned char *)object)[0x20];
        if ((unsigned char)mode != 7 || g_boss_half_time_frames / 2 < g_enemy_relocate_count) {
            if ((unsigned char)mode == 16) speed = g_boss_turn_speed_mode_sixteen * 0.0003490659f;
            else if ((unsigned)(mode - 13) < 3) speed = g_boss_turn_speed_mode_thirteen * 0.0003490659f;
        }
        FastVecCross((char *)&local.cross, aim_direction, (char *)&g_mothership_aim_direction);
        dot = FastVecDot((char *)&local.cross, object + 0xD0);
        angle = math_fast_angle_helper(dot);
        math_fast_float_g(angle + 1.5707964f);
        if (dot < 0.0f) *(float *)(state + 0x57C) = -speed;
        else *(float *)(state + 0x57C) = speed;
        *(float *)(state + 0x578) = FastAddRotations(*(float *)(state + 0x578), *(float *)(state + 0x57C));
        if (((unsigned char *)state)[0x4B1] == 0) AttachManipulator((unsigned char *)object, 39, (unsigned char *)state + 0x4B0);
        build_axis_rotation_quaternion(state + 0x4C0, 1, *(float *)(state + 0x578));
        *(float *)(state + 0x578) = fast_subtract_rotations(*(float *)(state + 0x578), *(float *)(state + 0x57C) * 0.0003490659f);
        mothership_turn_joints_pal(object, 1.0f, 1.0f);
        return 1;
    }
    if ((unsigned)((unsigned char)object[0x20] - 13) < 2) g_boss_part_mode_flag = 1;
    if (!((unsigned char *)state)[0x404]) {
        *(float *)(state + 0x57C) = -(g_boss_turn_speed_negative * 0.0003490659f);
        if (*(float *)(state + 0x578) > 0.0f) {
            *(float *)(state + 0x578) += *(float *)(state + 0x57C);
            if (((unsigned char *)state)[0x4B1] == 0) AttachManipulator((unsigned char *)object, 39, (unsigned char *)state + 0x4B0);
            build_axis_rotation_quaternion(state + 0x4C0, 1, *(float *)(state + 0x578));
            *(float *)(state + 0x578) = fast_subtract_rotations(*(float *)(state + 0x578), *(float *)(state + 0x57C) * 0.0003490659f);
            mothership_turn_joints_pal(object, -1.0f, -1.0f);
        }
    }
    return 0;
}
