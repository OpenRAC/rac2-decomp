#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern int g_frame_l03_counter;
extern int FastDecTimer(short *);
extern int PulseColor(int, int, float);
extern float FastAddRotations(float, float);
extern int FastTweenColor(int, int, float);
extern void *part_spawn_object_following_effect(float *, u8 *, int, int, int, int, int, int, float, float);
extern void value_set_and_smooth_pal(void *, float *, float, int, int);

/* Advance the warning light and emit its attached effect while it is visible. */
void sweeper_bot_update_warning_light_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    unsigned int timer;
    int color;
    EffectVector effect;

    FastDecTimer((short *)(state + 0x2D0));
    FastDecTimer((short *)(state + 0x2D2));
    timer = *(unsigned short *)(moby + 0x96);
    if (timer <= 0xFFFE) *(unsigned short *)(moby + 0x96) = timer + 1;
    if (!moby[0x31] && g_frame_l03_counter >= 2) return;

    switch (moby[0x95]) {
    case 2:
        color = PulseColor(0x502020D0, 0x50202070, *(float *)(state + 0x2E8));
        *(float *)(state + 0x2E8) = FastAddRotations(*(float *)(state + 0x2E8), 0.17802362f);
        break;
    case 1:
        color = PulseColor(0x5020D0D0, 0x50207070, *(float *)(state + 0x2E8));
        *(float *)(state + 0x2E8) = FastAddRotations(*(float *)(state + 0x2E8), 0.17802362f);
        break;
    default:
        color = PulseColor(0x5020D020, 0x50207020, *(float *)(state + 0x2E8));
        *(float *)(state + 0x2E8) = FastAddRotations(*(float *)(state + 0x2E8), 0.08028516f);
        break;
    }
    if (g_frame_l03_counter < 2) *(int *)(moby + 0x78) = color;
    else *(int *)(moby + 0x78) = FastTweenColor(*(int *)(moby + 0x78), color, 0.2f);

    if (moby && moby[0x20] != 0xFE && moby[0x20] != 0xFD) {
        effect.bits = 0;
        effect.value[0] = 0.33f;
        effect.value[2] = 0.075f;
        part_spawn_object_following_effect(effect.value, moby, *(int *)(moby + 0x78),
                         0, 1, 2, 0, -1, 94500.0f, 0.1f);
    }
    value_set_and_smooth_pal(moby, (float *)(state + 0x210), 1.8f, 0, 1);
}
