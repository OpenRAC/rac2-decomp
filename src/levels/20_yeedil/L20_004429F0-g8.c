#include "common.h"

extern int D_L20_001B20EC __attribute__((sda));
extern char *D_L20_001FEC80[];
extern int func_L20_0039E0A0(int);
extern int func_00282948(char *);
extern float func_L20_00444B48(int, int, float, float);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_00282D08(float *, const void *, const void *, float);
extern float func_002A89A8(char *, int, float);
extern int func_00277258(void *, int, void *, float);
extern u8 *func_L20_0039DBC8(void *, int, const float *);

void func_L20_004429F0(char *object)
{
    /* Interpolation, ground probing and collision use the complete quadword,
     * including the fourth lane even though this controller edits only XYZ. */
    float point[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *polygon;
    float rate, interval;
    int requested, attempts, spawned;
    int sides;
    int first, next;

    if (*(int *)(state + 0x182C) <= 0 && D_L20_001B20EC == 0)
        return;
    if (*(u8 *)(object + 0x95) == 5)
        return;
    if (func_L20_0039E0A0(*(int *)(state + 0x23C)) != 0)
        return;
    if (func_00282948(state + 0x1848) == 0 && D_L20_001B20EC == 0)
        return;
    rate = 60.0f;
    requested = 4;
    interval = func_L20_00444B48(5, 20, 0.0f, rate);
    attempts = 0;
    spawned = 0;
    *(int *)(state + 0x1848) = func_00283CF0((float)(int)(interval * rate)) + 1200;
    if (*(int *)(state + 0x182C) == 2)
        requested = 6;
    polygon = D_L20_001FEC80[*(int *)(state + 0x234)];
    for (; attempts < 30 && spawned < requested; ++attempts) {
        float height = 1.0f;
        float blend;
        sides = 6;
        first = func_002A77E0(6);
        next = (first + 1) % sides;
        blend = func_002A7878(0.2f, 0.8f);
        func_00282D08(point, polygon + (first * 16 + 16),
                     polygon + (next * 16 + 16), blend);
        point[2] = func_002A89A8((char *)point, 0, 0.5f) + height;
        if (func_00277258(point, 0, 0, 0.9f) == 0) {
            point[2] -= height;
            if (func_L20_0039DBC8(object, *(int *)(state + 0x23C), point) == 0)
                break;
            ++spawned;
        }
    }
}
