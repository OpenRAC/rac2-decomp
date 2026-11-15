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
extern void value_set_and_smooth(void *, float *, float, int, int);

/* Advance the warning light and emit its attached effect while it is visible. */
void sweeper_bot_update_warning_light(u8 *entity)
{
    u8 *state = *(u8 **)(entity + 0x68);
    unsigned int timer;
    int colour;
    EffectVector effect;

    FastDecTimer((short *)(state + 0x2D0));
    FastDecTimer((short *)(state + 0x2D2));
    timer = *(unsigned short *)(entity + 0x96);
    if (timer <= 0xFFFE) *(unsigned short *)(entity + 0x96) = timer + 1;
    if (!entity[0x31] && g_frame_l03_counter >= 2) return;

    switch (entity[0x95]) {
    case 2:
        colour = PulseColor(0x502020D0, 0x50202070, *(float *)(state + 0x2E8));
        *(float *)(state + 0x2E8) = FastAddRotations(*(float *)(state + 0x2E8), 0.14835301041603088f);
        break;
    case 1:
        colour = PulseColor(0x5020D0D0, 0x50207070, *(float *)(state + 0x2E8));
        *(float *)(state + 0x2E8) = FastAddRotations(*(float *)(state + 0x2E8), 0.14835301041603088f);
        break;
    default:
        colour = PulseColor(0x5020D020, 0x50207020, *(float *)(state + 0x2E8));
        *(float *)(state + 0x2E8) = FastAddRotations(*(float *)(state + 0x2E8), 0.06690429896116257f);
        break;
    }
    if (g_frame_l03_counter < 2) *(int *)(entity + 0x78) = colour;
    else *(int *)(entity + 0x78) = FastTweenColor(*(int *)(entity + 0x78), colour, 0.2f);

    if (entity && entity[0x20] != 0xFE && entity[0x20] != 0xFD) {
        effect.bits = 0;
        effect.value[0] = 0.33f;
        effect.value[2] = 0.075f;
        part_spawn_object_following_effect(effect.value, entity, *(int *)(entity + 0x78),
                         0, 1, 2, 0, -1, 94500.0f, 0.1f);
    }
    value_set_and_smooth(entity, (float *)(state + 0x210), 1.8f, 0, 1);
}
