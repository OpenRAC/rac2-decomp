#include "include_asm.h"

#include "common.h"
extern int vec_fast_helper_b(void *);
extern int g_frame_l00_counter __attribute__((sda));
extern float g_homing_param __attribute__((sda));
extern float g_homing_yaw_degrees __attribute__((sda));
extern float g_homing_pitch_degrees __attribute__((sda));
extern float g_homing_speed __attribute__((sda));
extern float g_homing_target_height_offset __attribute__((sda));
extern int g_game_l00_mode[] MACRO_ADDR;
extern char g_cam_follow_matrix[];
extern char g_hero_position[];
extern char g_weapon_l00_table[][224];
typedef struct { char pad[0x1F]; unsigned char selected; } Selection3EB8E8;
extern Selection3EB8E8 g_item_slot_to_record;
extern unsigned char *g_effect_param_pointer_b NOT_SDA;
extern char g_default_vector[] __attribute__((sda));
extern void moby_transform_joint_to_world(char *, int, void *);
extern char *moby_get_or_find_target(void *, void *, int, float, float, float, float, float);
extern void anim_start_blended_pal(char *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern char *moby_get_private_value_0(char *);
extern int math_random_int_below(int);
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *homing_l00_shot_spawn_pal(void *, char *, char *);
extern int PlayMobySound(int, int, char *);
extern float math_random_float_range(float, float);
typedef struct {
    char pad[0x24];
    unsigned char phase;
    unsigned char shots;
    char pad26[2];
    char *target;
    char pad2C[12];
    int slot;
    float cooldown;
} State3EB8E8;

/* Lets a Synthenoid pick a target in front of it and, when ready, fire a homing shot at it (PAL: 50 Hz cooldown). */
void synthenoid_fire_homing_shot_pal(char *self, State3EB8E8 *state)
{
    float pos[4], v[4], target[4], dir[4];
    char *obj, *part, *bone;
    int angle;
    float dot;
    char *entry;

    if (!vec_fast_helper_b(&state->cooldown) || g_frame_l00_counter % 4 != state->slot)
        return;
    moby_transform_joint_to_world(self, 1, pos);
    state->phase ^= 1;
    obj = moby_get_or_find_target(pos, g_cam_follow_matrix, 0, g_homing_yaw_degrees * 0.01745329424738884f,
                            g_homing_pitch_degrees * 0.01745329424738884f, g_homing_param,
                            g_homing_yaw_degrees * 0.01745329424738884f, g_homing_pitch_degrees * 0.01745329424738884f);
    if (obj) {
        if ((*(short *)(obj + 0xAA) == 0xEE1 || *(short *)(obj + 0xAA) == 0xEC0 || *(short *)(obj + 0xAA) == 0xED4) &&
            *(unsigned char *)(*(char **)(obj + 0x68) + 0x3B1) == 255) {
            state->target = 0;
            return;
        }
        if (*(short *)(obj + 0xAA) == 0xEF4) {
            state->target = 0;
            return;
        }
        state->target = obj;
        if (*(unsigned char *)(self + 0x43) != 2)
            anim_start_blended_pal(self, 2, 0, 4);
        FastVecSub(v, self + 0x10, g_hero_position);
        dot = FastVecDot(v, self + 0xE0);
        if (g_game_l00_mode[0] != 2 && *(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
            *(unsigned char *)(self + 0x42) == 2 && dot > 1.1f) {
            qcopy_nc(target, obj + 0x10);
            bone = moby_get_private_value_0(obj);
            if (bone)
                target[2] += *(float *)(bone + 0x10);
            else
                target[2] += g_homing_target_height_offset;
            angle = math_random_int_below(255);
            part = part_spawn_gravity_fade(pos, g_default_vector, 2, 0x202080, angle, 127, 16, 420000.0f, 420000.0f, 0.0f, 0);
            if (part)
                part[2] = *g_effect_param_pointer_b;
            part = part_spawn_gravity_fade(pos, g_default_vector, 2, 0x601080, (angle + 128) % 255, 127, 16,
                                 420000.0f, 420000.0f, 0.0f, 0);
            if (part)
                part[2] = *g_effect_param_pointer_b;
            FastVecSub(dir, target, pos);
            vec_scale_to_length(dir, dir, g_homing_speed);
            FastVecAdd(pos, pos, dir);
            homing_l00_shot_spawn_pal(pos, self, obj);
            PlayMobySound(0, 0, self);
            {
                int selected = g_item_slot_to_record.selected;
                entry = g_weapon_l00_table[selected];
            }
            dot = math_random_float_range(0.0f, 0.17f);
            state->cooldown = 1.0f / *(float *)(entry + 0x54) + dot;
            state->shots++;
        }
    } else {
        state->target = 0;
    }
}
