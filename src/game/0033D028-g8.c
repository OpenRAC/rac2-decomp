#include "include_asm.h"
#include "names.h"

extern void prompt_bar_update(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern int snd_play_from_global_bank(int, int, void *);
extern void snd_send_cmd11_one_value(int);
extern void meter_set_value(void *, int);
extern void snd_set_default_group_volumes(void);

/* Four option bytes precede the audio toggle and two volume words.
 * Offset accesses preserve the absolute loads and stores of these settings. */
extern unsigned char D_001A7B94[] __attribute__((sda));
extern struct { int w0, w1, w2; } D_00138340;
extern float D_L00_001AE198 __attribute__((sda));
extern float D_L00_001AE1A0 __attribute__((sda));
extern float D_L00_001AE19C, D_L00_001AE1A4;

/* Handles input for the audio options menu: moves the cursor, changes the two volume levels, and flips the sound mode. */
int audio_menu_update(char *object, int flags)
{
    char *p = object + 8;
    float *vec;

    prompt_bar_update(p);
    vec = *(float **)(object + 0x33C);
    menu_set_anchor_pos(p, vec[0], vec[1]);
    vec = *(float **)(object + 0x33C);
    object_set_first_float4(object + 0x2AC, vec[0] + D_L00_001AE198,
                 vec[1] + D_L00_001AE19C, 0.0f, 0.0f);
    vec = *(float **)(object + 0x33C);
    object_set_first_float4(object + 0x2F4, vec[0] + D_L00_001AE1A0,
                 vec[1] + D_L00_001AE1A4, 0.0f, 0.0f);
    if (flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(object + 0x2A8) = (*(int *)(object + 0x2A8) + 2) % 3;
    } else if (flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(object + 0x2A8) = (*(int *)(object + 0x2A8) + 1) % 3;
    } else if (D_00138340.w0 & 0x8000) {
        switch (*(int *)(object + 0x2A8)) {
        case 0: {
            int value = *(int *)(D_001A7B94 + 12) - 3;
            *(int *)(D_001A7B94 + 12) = value < 0 ? 0 : value;
            break;
        }
        case 1: {
            int value = *(int *)(D_001A7B94 + 8) - 3;
            *(int *)(D_001A7B94 + 8) = value < 0 ? 0 : value;
            break;
        }
        }
    } else if (D_00138340.w0 & 0x2000) {
        switch (*(int *)(object + 0x2A8)) {
        case 0: {
            int value = *(int *)(D_001A7B94 + 12) + 3;
            *(int *)(D_001A7B94 + 12) = value > 1024 ? 1024 : value;
            break;
        }
        case 1: {
            int value = *(int *)(D_001A7B94 + 8) + 3;
            *(int *)(D_001A7B94 + 8) = value > 1024 ? 1024 : value;
            break;
        }
        }
    } else if (flags & 0x40) {
        if (*(int *)(object + 0x2A8) == 2) {
            int value;
            snd_play_from_global_bank(4, 0, 0);
            value = *(int *)(D_001A7B94 + 4) == 0;
            *(int *)(D_001A7B94 + 4) = value;
            snd_send_cmd11_one_value(!value);
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    meter_set_value(object + 0x2F4, *(int *)(D_001A7B94 + 8));
    meter_set_value(object + 0x2AC, *(int *)(D_001A7B94 + 12));
    snd_set_default_group_volumes();
    return (flags >> 6) & 1;
}
