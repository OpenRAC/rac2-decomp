#include "names.h"
/* func_PAL_L06_003E8240, the PAL copy of func_L06_003E4BE0: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 0.00027777778450399637f becomes 0.00040000002f; 0.000004848137291264255f becomes
   6.981318e - 06f; 0.20943954586982727f becomes 0.25132746f; 0.0002908882452175021f becomes
   0.0003490659f. */
#include "common.h"
typedef int L06Qword __attribute__((mode(TI)));
typedef union { L06Qword bits; float f[4]; } L06Vector;
extern char *g_path_list[];
extern u8 g_sound_flag_bytes[];
extern char g_sound_state[];
extern float g_path_wait_seconds __attribute__((sda));
extern float g_path_speed_scale __attribute__((sda));
extern float g_path_pitch_rate __attribute__((sda));
extern float g_path_yaw_rate __attribute__((sda));
extern float g_path_turn_rate __attribute__((sda));
extern float g_path_roll_rate __attribute__((sda));
extern float g_path_speed_factor __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern float vec_length_xy(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float math_approach_target_with_direction_mode(void *, void *, int, float, float, float, float);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void snd_stop_voice(int);

int moby_move_along_path_pal(char *moby, int path, int *sound)
{
    L06Vector target, delta;
    float height;
    char **route = &g_path_list[path];
    char *st = *(char **)(moby + 0x68);
    int done = 0;
    float limit, angle;
    int handle;
    u8 *slot;
    float *yaw;
    int point = *(int *)(st + 0x64);
    char *node = *route;
    height = 0;
    qcopy(&target, node + point * 16 + 0x10);
    *(float *)(st + 0x108) = target.f[2];
    *(float *)(st + 0xEC) = 0;
    *(float *)(st + 0xE8) = 0;
    FastVecSub(&delta, &target, moby + 0x10);
    if (FastVecLength(&delta) < g_path_wait_seconds * (0.020000001f) * 2.0f) {
        ++*(int *)(st + 0x64);
        done = *(int *)(st + 0x64) == *(int *)*route;
    }
    limit = fast_vec_dist(moby + 0x10, *route + *(int *)*route * 16);
    math_step_value_toward_target(&height, st + 0x60, limit,
        g_path_speed_scale * 0.00040000002f,
        g_path_speed_scale * 0.00040000002f,
        g_path_wait_seconds * (0.020000001f));
    vec_scale_to_length(&delta, &delta, *(float *)(st + 0x60));
    FastVecAdd(moby + 0x10, &delta, moby + 0x10);
    angle = -mat_fast_helper_a(vec_length_xy(&delta), delta.f[2]);
    if (angle > 0.2617994248867035f) angle = 0.2617994248867035f;
    else if (angle < -0.2617994248867035f) angle = -0.2617994248867035f;
    yaw = (float *)(moby + 0xF8);
    math_approach_target_with_direction_mode(moby + 0xF4, st + 0x6C, 0, angle,
        g_path_turn_rate * 6.981318e-06f,
        g_path_turn_rate * 6.981318e-06f, 0.25132746f);
    angle = mat_fast_helper_a(target.f[0] - *(float *)(moby + 0x10), target.f[1] - *(float *)(moby + 0x14));
    math_approach_target_with_direction_mode(yaw, st + 0x68, 0, angle,
        g_path_pitch_rate * 6.981318e-06f,
        g_path_pitch_rate * 6.981318e-06f,
        g_path_yaw_rate * 0.0003490659f);
    math_approach_target_with_direction_mode(moby + 0xF0, st + 0x70, 0,
        *(float *)(st + 0x68) * *(float *)(st + 0x60) * g_path_speed_factor,
        g_path_roll_rate * 6.981318e-06f,
        g_path_roll_rate * 6.981318e-06f, 0.25132746f);
    if (!done) {
        if (!snd_is_voice_playing_for_owner(moby, *sound) && g_sound_flag_bytes[0] != 0xFF)
            *sound = snd_play_from_class_bank(0, 4, moby, 0x330);
    } else {
        handle = *sound;
        if (handle != -1) {
            slot = (u8 *)g_sound_state + handle * 0x70;
            if (*(char **)(slot + 0x88) == moby && slot[0x74]) snd_stop_voice(handle);
        }
        *sound = -1;
    }
    return done;
}
