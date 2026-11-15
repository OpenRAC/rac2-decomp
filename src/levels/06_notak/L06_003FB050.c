#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
extern char g_sound_state[];
typedef struct { unsigned char prefix[0x80]; Vector position; } PlayerPosition;
extern PlayerPosition g_hero_state;
extern char *D_L06_001BFC98;
extern int D_L06_001B2348 MACRO_ADDR;
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern int hero_is_current_selected_id(void *);
extern void moby_set_state(void *, int, int);
extern int coll_test_point(void *, int, void *, float);
extern void math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Raise and lower a platform while maintaining its motion sound. */
void rising_l06_platform_update(char *moby)
{
    Vector oldPosition, oldRotation, delta;
    char *state = *(char **)(moby + 0x68);
    int handle, phase, brightness;
    float time, wave;
    unsigned int selection;
    qcopy(oldPosition, (moby + 0x10));
    qcopy(oldRotation, (moby + 0xF0));
    selection = *(unsigned char *)(moby + 0x20);
    switch (selection) {
    case 0:
    *(int *)(state + 0x7C) = *(int *)(state + 0x78);
    *(int *)(state + 0x5C) |= 1;
    qcopy((state + 0x90), (moby + 0x10));
    qcopy((state + 0x80), (state + 0x90));
    *(float *)(state + 0x88) = *(float *)(state + 0x98) - *(float *)(state + 0x68);
    *(int *)(state + 0x60) = *(int *)(state + 0x74);
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
        (!D_L06_001BFC98 || *(short *)(D_L06_001BFC98 + 0xAA) != 0xEA3 /* moby class 3747 */))
        goto stop;
    {
        char *sound = g_sound_state + *(int *)(state + 0xB0) * 0x70;
    if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74))
        *(int *)(state + 0xB0) = PlayMobySound(0, 4, moby);
    }
    math_step_value_toward_target(moby + 0x18, state + 0x64, *(float *)(state + 0x88),
                  0.001944444492f, 0.001666666707f, 0.1000000089f);
    goto done;
    case 3:
    math_step_value_toward_target(moby + 0x18, state + 0x64, *(float *)(state + 0x98),
                  0.001944444492f, 0.001666666707f, 0.1000000089f);
    if (*(float *)(moby + 0x18) >= *(float *)(state + 0x98)) {
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = g_sound_state + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            snd_stop_voice(handle);
    }
    *(int *)(state + 0xB0) = -1;
        if (!hero_is_current_selected_id(moby)) {
            *(int *)(state + 0x60) = *(int *)(state + 0x74);
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
    time = (float)D_L06_001B2348 * (1.0f / 60.0f);
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
    FastVecSub(delta, moby + 0x10, oldPosition);
    mat_combine_and_store(state + 0x20, delta, oldRotation, moby + 0xF0);
}
