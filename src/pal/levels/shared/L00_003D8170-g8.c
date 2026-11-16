#include "include_asm.h"

#include "common.h"
extern int ref_L00_003D40D8_00(float *);
extern int g_frame_l00_counter __attribute__((sda));
extern float g_kilonoid_shot_float_param __attribute__((sda));
extern float g_kilonoid_aim_yaw_degrees __attribute__((sda));
extern float g_kilonoid_aim_pitch_degrees __attribute__((sda));
extern float g_kilonoid_shot_velocity_scale __attribute__((sda));
extern float g_kilonoid_target_height_offset __attribute__((sda));
extern int g_kilonoid_shot_sound_id __attribute__((sda));
extern float g_kilonoid_shot_speed __attribute__((sda));
extern float g_kilonoid_projectile_speed __attribute__((sda));
extern float g_kilonoid_projectile_param __attribute__((sda));
extern char g_cam_follow_matrix[];
extern char g_hero_position[];
extern char g_default_vector[] __attribute__((sda));
extern char g_weapon_l00_table[];
extern int g_game_l00_mode MACRO_ADDR;
extern unsigned char g_kilonoid_weapon_index __attribute__((nosda));
extern unsigned char *g_effect_param_pointer_b __attribute__((nosda));
extern void ref_L00_003D40D8_01(char *,int,float *);
extern char *ref_L00_003D40D8_02(float *,char *,int,float,float,float,float,float);
extern void ref_L00_003D40D8_03(char *,int,int,int);
extern void ref_L00_003D40D8_04(float *,void *,void *);
extern float ref_L00_003D40D8_05(float *,void *);
extern char *ref_L00_003D40D8_06(char *);
extern int ref_L00_003D40D8_07(int);
extern char *ref_L00_003D40D8_08(float *,char *,int,int,int,int,int,float,float,float,int);
extern void ref_L00_003D40D8_09(float *,float *,float);
extern void ref_L00_003D40D8_10(float *,float *,float *);
extern float ref_L00_003D40D8_11(float *,float *,int,float,float);
extern char *ref_L00_003D40D8_12(char *,float *,float *,int,float);
extern int ref_L00_003D40D8_13(int,int,char *);
extern void ref_L00_003D40D8_14(float *,char *,char *);
extern float ref_L00_003D40D8_15(float,float);
typedef struct {
    char reserved[0x24];
    unsigned char alternate, shots;
    char reserved26[2];
    char *target;
    char reserved2c[0xc];
    int frame;
    float cooldown;
    int reserved40;
    short charges;
} EffectLauncherState;

/* Per-frame fire step: on its cooldown and frame slot, looks for a target (skipping some
 * classes), aims, spawns two particles, fires one of two shot kinds (the first while charges
 * remain) and restarts the cooldown from the weapon table'state rate at +0x54. */
void kilonoid_fire_shot_pal(unsigned char *moby, EffectLauncherState *state)
{
    float pos[4], delta[4], target[4], step[4], velocity[4];
    char *target_moby;
    int sound_seed;
    float angle;

    if (!ref_L00_003D40D8_00(&state->cooldown))
        return;
    if (g_frame_l00_counter % 4 != state->frame)
        return;
    ref_L00_003D40D8_01(moby, 1, pos);
    state->alternate ^= 1;
    target_moby = ref_L00_003D40D8_02(pos, g_cam_follow_matrix, 0,
                              g_kilonoid_aim_yaw_degrees * 0.017453294f, g_kilonoid_aim_pitch_degrees * 0.017453294f,
                              g_kilonoid_shot_float_param,
                              g_kilonoid_aim_yaw_degrees * 0.017453294f, g_kilonoid_aim_pitch_degrees * 0.017453294f);
    if (target_moby) {
        if ((*(short *)(target_moby + 0xaa) == 0xee1 || *(short *)(target_moby + 0xaa) == 0xec0
             || *(short *)(target_moby + 0xaa) == 0xed4)
            && *(unsigned char *)(*(char **)(target_moby + 0x68) + 0x3b1) == 255) {
            state->target = 0;
            return;
        }
        if (*(short *)(target_moby + 0xaa) == 0xef4) {
            state->target = 0;
            return;
        }
        state->target = target_moby;
        if ((unsigned char)moby[0x43] != 2)
            ref_L00_003D40D8_03(moby, 2, 0, 4);
        ref_L00_003D40D8_04(delta, moby + 0x10, g_hero_position);
        angle = ref_L00_003D40D8_05(delta, moby + 0xe0);
        if (g_game_l00_mode == 2 || moby[0x42] != moby[0x43] || (unsigned char)moby[0x42] != 2
            || !(angle > 1.1f))
            return;
        qcopy(target, target_moby + 0x10);
        {
            char *v = ref_L00_003D40D8_06(target_moby);

            if (v)
                target[2] += *(float *)(v + 0x10);
            else
                target[2] += g_kilonoid_target_height_offset;
        }
        sound_seed = ref_L00_003D40D8_07(255);
        {
            char *result = ref_L00_003D40D8_08(pos, g_default_vector, 2, 0x202080, sound_seed, 127, 16,
                                               420000.0f, 420000.0f, 0.0f, 0);

            if (result)
                result[2] = *g_effect_param_pointer_b;
        }
        {
            char *result = ref_L00_003D40D8_08(pos, g_default_vector, 2, 0x601080, (sound_seed + 128) % 255,
                                               127, 16, 420000.0f, 420000.0f, 0.0f, 0);

            if (result)
                result[2] = *g_effect_param_pointer_b;
        }
        ref_L00_003D40D8_04(step, target, pos);
        ref_L00_003D40D8_09(step, step, g_kilonoid_shot_velocity_scale);
        ref_L00_003D40D8_10(pos, pos, step);
        if (state->charges && !ref_L00_003D40D8_07(g_kilonoid_shot_sound_id)) {
            float f;
            char *result;

            if (--state->charges < 0)
                state->charges = 0;
            f = ref_L00_003D40D8_11(pos, target, 0, g_kilonoid_shot_speed * 0.020000001f,
                                    -(g_kilonoid_projectile_speed * 0.00040000002f));
            ref_L00_003D40D8_04(velocity, target, pos);
            velocity[2] = 0;
            ref_L00_003D40D8_09(velocity, velocity, g_kilonoid_shot_speed * 0.020000001f);
            velocity[2] = f;
            result = ref_L00_003D40D8_12(moby, pos, velocity, 150, g_kilonoid_projectile_speed * 0.00040000002f);
            ref_L00_003D40D8_13(3, 0, moby);
            *(float *)(result + 0x2c) = g_kilonoid_projectile_param;
        } else {
            ref_L00_003D40D8_14(pos, moby, target_moby);
            ref_L00_003D40D8_13(0, 0, moby);
        }
        {
            char *v = g_weapon_l00_table + g_kilonoid_weapon_index * 0xe0;
            float f = ref_L00_003D40D8_15(0.0f, 0.17f);
            float delay = 1.0f / *(float *)(v + 0x54);

            ++state->shots;
            state->cooldown = delay + f;
        }
        return;
    }
    state->target = 0;
}
