#include "names.h"
typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern int D_L03_001B2548;
extern int func_00282978(short *);
extern int func_L01_0031BC68(int, int, float);
extern float func_00283B98(float, float);
extern int func_00283D38(int, int, float);
extern void *func_L00_0033E220(float *, u8 *, int, int, int, int, int, int, float, float);
extern void func_002B0990(void *, float *, float, int, int);

/* Advance the warning light and emit its attached effect while it is visible. */
void func_L03_0041CEB0(u8 *entity)
{
    u8 *state = *(u8 **)(entity + 0x68);
    unsigned int timer;
    int colour;
    EffectVector effect;

    FastDecTimer((short *)(state + 0x2D0));
    FastDecTimer((short *)(state + 0x2D2));
    timer = *(unsigned short *)(entity + 0x96);
    if (timer <= 0xFFFE) *(unsigned short *)(entity + 0x96) = timer + 1;
    if (!entity[0x31] && gFrameCounter_L03 >= 2) return;

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
    if (gFrameCounter_L03 < 2) *(int *)(entity + 0x78) = colour;
    else *(int *)(entity + 0x78) = FastTweenColor(*(int *)(entity + 0x78), colour, 0.2f);

    if (entity && entity[0x20] != 0xFE && entity[0x20] != 0xFD) {
        effect.bits = 0;
        effect.value[0] = 0.33f;
        effect.value[2] = 0.075f;
        SpawnObjectFollowingEffect(effect.value, entity, *(int *)(entity + 0x78),
                         0, 1, 2, 0, -1, 94500.0f, 0.1f);
    }
    SetValueAndStartSmoothChange(entity, (float *)(state + 0x210), 1.8f, 0, 1);
}
