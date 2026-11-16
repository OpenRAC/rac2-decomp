#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern int g_effect_init_flag __attribute__((sda));

/* func_PAL_L03_0038E5C8, the PAL copy of func_L03_0038B4E8: the same C, with the three
   timers at 0x18, 0x1C and 0x20 scaled to 50 Hz. */
void effect_init_moby_state_pal(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *origin = object;
    int value;

    value = *(int *)(state + 0x9C);
    *(int *)(state + 0x94) = 0;
    if (value < 0)
        *(int *)(state + 0x9C) = 0xE;
    value = *(int *)(state + 0x80);
    if (value < 0)
        *(int *)(state + 0x80) = 0x10;
    *(int *)(state + 0xBC) = 0x80402080;
    *(int *)(state + 0xC0) = 0x80004880;
    *(float *)(state + 0xA4) = 1.0f;
    *(float *)(state + 0xA0) = 0.25f;
    *(int *)(state + 0xA8) = 0;
    *(int *)(state + 0x60) = 0x807F0000;
    *(int *)(state + 0x64) = 0x8000007F;
    *(int *)(state + 0x68) = 0x807F0000;
    *(int *)(state + 0x6C) = 0x8000007F;
    origin += 0x10;
    *(TI128 *)(state + 0xE0) = *(TI128 *)origin;
    *(float *)(state + 0xE8) = *(float *)(state + 0xE8) + 1.1f;
    *(int *)(state + 0x18) = (*(int *)(state + 0x18) * 5 + 2) / 6;
    *(int *)(state + 0x1C) = (*(int *)(state + 0x1C) * 5 + 2) / 6;
    *(int *)(state + 0x20) = (*(int *)(state + 0x20) * 5 + 2) / 6;
    *(int *)(state + 0xD8) = -1;
    *(int *)(state + 0xDC) = *(int *)(state + 0xDC) << 3;
    g_effect_init_flag = 0;
}
