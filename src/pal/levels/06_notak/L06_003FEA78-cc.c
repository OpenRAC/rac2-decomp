#include "names.h"
/* func_PAL_L06_003FEA78, the PAL copy of func_L06_003FB050: the same C, where expr 0.016666668f becomes 0.02f; scale *(int *)(state + 0x74); scale *(int *)(state + 0x78). */
#include "common.h"
typedef float Vector[4] __attribute__((aligned(16)));
extern char g_sound_state[];
typedef struct { unsigned char prefix[0x80]; Vector position; } PlayerPosition;
extern PlayerPosition g_hero_state;
extern char *g_hit_l06_result;
extern int g_game_l06_frame_counter MACRO_ADDR;
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern int hero_is_current_selected_id(void *);
extern void moby_set_state(void *, int, int);
extern int coll_test_point(void *, int, void *, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Raise and lower a platform while maintaining its motion sound. */
void rising_l06_platform_update_pal(char *moby)
{
    Vector old_position, old_rotation, delta;
    char *state = *(char **)(moby + 0x68);
    int handle, phase, brightness;
    float time, wave;
    unsigned int selection;
    qcopy(old_position, (moby + 0x10));
    qcopy(old_rotation, (moby + 0xF0));
    selection = *(unsigned char *)(moby + 0x20);
    switch (selection) {
    case 0:
    *(int *)(state + 0x7C) = *(int *)(state + 0x78);
    *(int *)(state + 0x5C) |= 1;
    qcopy((state + 0x90), (moby + 0x10));
    qcopy((state + 0x80), (state + 0x90));
    *(float *)(state + 0x88) = *(float *)(state + 0x98) - *(float *)(state + 0x68);
    *(int *)(state + 0x60) = (((int)(*(int *)(state + 0x74)) * 5 + 2) / 6);
    *(unsigned char *)(moby + 0x20) = 1;
    *(int *)(state + 0xB0) = -1;
    *(int *)(state + 0x64) = 0;
    goto done;
    case 1:
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = g_sound_state + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            snd_stop_voice(handle);
    }
    *(int *)(state + 0xB0) = -1;
    if (hero_is_current_selected_id(moby)) {
        if (*(float *)(moby + 0x18) == *(float *)(state + 0x98))
            moby_set_state(moby, 2, -1);
        else
            moby_set_state(moby, 3, -1);
    }
    if (*(float *)(moby + 0x18) - g_hero_state.position[2] > 3.0f &&
        *(float *)(moby + 0x18) == *(float *)(state + 0x98))
        moby_set_state(moby, 2, -1);
    else if (*(float *)(moby + 0x18) - g_hero_state.position[2] < -3.0f &&
             *(float *)(moby + 0x18) == *(float *)(state + 0x88))
        moby_set_state(moby, 3, -1);
    goto done;
    case 2:
    if (*(float *)(moby + 0x18) <= *(float *)(state + 0x88)) {
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = g_sound_state + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            snd_stop_voice(handle);
    }
    *(int *)(state + 0xB0) = -1;
        if (!hero_is_current_selected_id(moby))
            *(unsigned char *)(moby + 0x20) = 1;
        goto done;
    }
    if (coll_test_point(moby + 0x10, 1, moby, 2.1f) &&
        !(*(float *)(moby + 0x18) <= g_hero_state.position[2]) &&
        (!g_hit_l06_result || *(short *)(g_hit_l06_result + 0xAA) != 0xEA3))
        goto stop;
    {
        char *sound = g_sound_state + *(int *)(state + 0xB0) * 0x70;
    if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74))
        *(int *)(state + 0xB0) = PlayMobySound(0, 4, moby);
    }
    math_step_value_toward_target(moby + 0x18, state + 0x64, *(float *)(state + 0x88),
                  0.0028000001f, 0.0024f, 0.120000005f);
    goto done;
    case 3:
    math_step_value_toward_target(moby + 0x18, state + 0x64, *(float *)(state + 0x98),
                  0.0028000001f, 0.0024f, 0.120000005f);
    if (*(float *)(moby + 0x18) >= *(float *)(state + 0x98)) {
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = g_sound_state + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            snd_stop_voice(handle);
    }
    *(int *)(state + 0xB0) = -1;
        if (!hero_is_current_selected_id(moby)) {
            *(int *)(state + 0x60) = (((int)(*(int *)(state + 0x74)) * 5 + 2) / 6);
            (*(int *)(state + 0x78))--;
            *(unsigned char *)(moby + 0x20) = 1;
        }
    } else {
        char *sound = g_sound_state + *(int *)(state + 0xB0) * 0x70;
        if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74))
            *(int *)(state + 0xB0) = PlayMobySound(0, 4, moby);
    }
    goto done;
stop:
    case 4:
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = g_sound_state + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            snd_stop_voice(handle);
    }
    *(int *)(state + 0xB0) = -1;
    }
done:
    time = (float)g_game_l06_frame_counter * (0.02f);
    phase = (int)time;
    wave = time - (float)phase;
    if (!(phase & 1))
        wave = 1.0f - wave;
    brightness = (int)(wave * 255.0f);
    {
        int hi = (brightness << 8) | 0x7F000000;
        int mid = (brightness << 16) | hi;
        *(int *)(moby + 0x78) = mid | brightness;
    }
    FastVecSub(delta, moby + 0x10, old_position);
    mat_combine_and_store(state + 0x20, delta, old_rotation, moby + 0xF0);
}
