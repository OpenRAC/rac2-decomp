#include "include_asm.h"
#include "names.h"

extern void func_0033AE28(void *);
extern void func_0033B018(void *, float, float);
extern void func_00335E38(void *, float, float, float, float);
extern int func_002E5E58(int, int, void *);
extern void func_00132938(int);
extern void func_00336B98(void *, int);
extern void func_002E4860(void);

/* Four option bytes precede the audio toggle and two volume words.
 * Offset accesses preserve the absolute loads and stores of these settings. */
extern unsigned char D_001A7B94[] __attribute__((sda));
extern struct { int w0, w1, w2; } D_00138340;
extern float D_L00_001AE198 __attribute__((sda));
extern float D_L00_001AE1A0 __attribute__((sda));
extern float D_L00_001AE19C, D_L00_001AE1A4;

/* Handles input for the audio options menu: moves the cursor, changes the two volume levels, and flips the sound mode. */
int func_0033D028(char *object, int flags)
{
    char *p = object + 8;
    float *vec;

    UpdateButtonPromptBar(p);
    vec = *(float **)(object + 0x33C);
    SetMenuAnchorPosition(p, vec[0], vec[1]);
    vec = *(float **)(object + 0x33C);
    SetFirstFloat4(object + 0x2AC, vec[0] + D_L00_001AE198,
                 vec[1] + D_L00_001AE19C, 0.0f, 0.0f);
    vec = *(float **)(object + 0x33C);
    SetFirstFloat4(object + 0x2F4, vec[0] + D_L00_001AE1A0,
                 vec[1] + D_L00_001AE1A4, 0.0f, 0.0f);
    if (flags & 0x1000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        *(int *)(object + 0x2A8) = (*(int *)(object + 0x2A8) + 2) % 3;
    } else if (flags & 0x4000) {
        PlaySoundFromGlobalBank(3, 0, 0);
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
            PlaySoundFromGlobalBank(4, 0, 0);
            value = *(int *)(D_001A7B94 + 4) == 0;
            *(int *)(D_001A7B94 + 4) = value;
            SendSoundCommand11_00132938(!value);
        } else {
            PlaySoundFromGlobalBank(5, 0, 0);
        }
    }
    SetMeterValue(object + 0x2F4, *(int *)(D_001A7B94 + 8));
    SetMeterValue(object + 0x2AC, *(int *)(D_001A7B94 + 12));
    SetDefaultSoundGroupVolumes();
    return (flags >> 6) & 1;
}
