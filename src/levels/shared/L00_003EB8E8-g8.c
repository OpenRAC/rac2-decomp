#include "common.h"

/* func_L00_003EB8E8 has a unit of its own for -g (the nop pair before div.s, config/cflags.txt)
 * and its small-data tuning values (-G8). */
extern int vec_fast_helper_b(void *);
extern int g_frame_l00_counter __attribute__((sda));
extern float g_homing_param __attribute__((sda));
extern float g_homing_yaw_degrees __attribute__((sda));
extern float g_homing_pitch_degrees __attribute__((sda));
extern float g_homing_speed __attribute__((sda));
extern float g_homing_target_height_offset __attribute__((sda));
/* The unsized macro-address view keeps the absolute load tied to its address register. */
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
extern void anim_start_blended(char *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern char *moby_get_private_value_0(char *);
extern int math_random_int_below(int);
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *homing_l00_shot_spawn(void *, char *, char *);
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

void UpdateAutoTargetFire(char *self, State3EB8E8 *st)
{
    float pos[4], to_player[4], target[4], dir[4];
    char *candidate, *spark, *target_info;
    int spark_seed;
    float dot;
    char *entry;

    if (!vec_fast_helper_b(&st->cooldown) || g_frame_l00_counter % 4 != st->slot)
        return;
    moby_transform_joint_to_world(self, 1, pos);
    st->phase ^= 1;
    candidate = moby_get_or_find_target(pos, g_cam_follow_matrix, 0, g_homing_yaw_degrees * 0.01745329424738884f,
                            g_homing_pitch_degrees * 0.01745329424738884f, g_homing_param,
                            g_homing_yaw_degrees * 0.01745329424738884f, g_homing_pitch_degrees * 0.01745329424738884f);
    if (candidate) {
        if ((*(short *)(candidate + 0xAA) == MOBY_CLASS_RECEIVER_BOT || *(short *)(candidate + 0xAA) == 0xEC0 /* moby class 3776 */ || *(short *)(candidate + 0xAA) == 0xED4 /* moby class 3796 */) &&
            *(unsigned char *)(*(char **)(candidate + 0x68) + 0x3B1) == 255) {
            st->target = 0;
            return;
        }
        if (*(short *)(candidate + 0xAA) == 0xEF4 /* moby class 3828 */) {
            st->target = 0;
            return;
        }
        st->target = candidate;
        if (*(unsigned char *)(self + 0x43) != 2)
            anim_start_blended(self, 2, 0, 5);
        FastVecSub(to_player, self + 0x10, g_hero_position);
        dot = FastVecDot(to_player, self + 0xE0);
        if (g_game_l00_mode[0] != 2 && *(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
            *(unsigned char *)(self + 0x42) == 2 && dot > 1.1f) {
            qcopy_nc(target, candidate + 0x10);
            target_info = moby_get_private_value_0(candidate);
            if (target_info)
                target[2] += *(float *)(target_info + 0x10);
            else
                target[2] += g_homing_target_height_offset;
            spark_seed = math_random_int_below(255);
            spark = part_spawn_gravity_fade(pos, g_default_vector, 3, 0x202080, spark_seed, 127, 16, 420000.0f, 420000.0f, 0.0f, 0);
            if (spark)
                spark[2] = *g_effect_param_pointer_b;
            spark = part_spawn_gravity_fade(pos, g_default_vector, 3, 0x601080, (spark_seed + 128) % 255, 127, 16,
                                 420000.0f, 420000.0f, 0.0f, 0);
            if (spark)
                spark[2] = *g_effect_param_pointer_b;
            FastVecSub(dir, target, pos);
            vec_scale_to_length(dir, dir, g_homing_speed);
            FastVecAdd(pos, pos, dir);
            homing_l00_shot_spawn(pos, self, candidate);
            PlayMobySound(0, 0, self);
            {
                int selected = g_item_slot_to_record.selected;
                entry = g_weapon_l00_table[selected];
            }
            dot = math_random_float_range(0.0f, 0.17f);
            st->cooldown = 1.0f / *(float *)(entry + 0x54) + dot;
            st->shots++;
        }
    } else {
        st->target = 0;
    }
}
