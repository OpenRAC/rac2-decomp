#include "include_asm.h"

#include "common.h"
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_002A7750(unsigned char *, int, int);
extern void func_0029FCC0(char *, int, char *);
extern float func_00282E80(void *, void *);
extern void func_L00_003294F0(unsigned char *, int);
extern void func_002A0430(unsigned int);
extern void func_PAL_L20_002C59B0(int);
typedef struct {
    char reserved00[0xBC];
    unsigned char enabled;
    char reservedBD[0x100 - 0xBD];
} YeedilObject;
extern YeedilObject *D_L20_001B2F9C;
extern YeedilObject *yeedilObjectsGp SDATA(D_L20_001B2F9C);
extern struct {
    char reserved00[0x80];
    float position[4];
    char reserved90[0x33C - 0x90];
    unsigned char *owner;
    int active;
} D_00189E20;
typedef struct {
    int objects[4];
    int modes[4];
    float angle;
    int activated;
    unsigned int event;
    int callback;
} YeedilActivation;

void func_PAL_L20_0044B390(unsigned char *object)
{
    float point[4] __attribute__((aligned(16)));
    YeedilActivation *state = *(YeedilActivation **)(object + 0x68);
    int color;
    if (!state) return;
    state->angle = func_00283B98(state->angle, 0.12566373f);
    color = func_00283CF0((func_00283198(state->angle) * 4.0f - 3.0f) * 128.0f);
    if (color > 128) color = 128;
    else if (color < 32) color = 32;
    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x34) |= 0x10;
        func_002A7750(object, 1, -1);
    } else if (object[0x20] == 1) {
        float distance;
        func_0029FCC0((char *)object, 0, (char *)point);
        distance = func_00282E80(D_00189E20.position, point);
        state->activated = 0;
        if (D_00189E20.owner == object && D_00189E20.active &&
            distance < *(float *)(object + 0x2C) * 0.5f / *(float *)(*(char **)(object + 0x24) + 0x24)) {
            int missing = -1;
            int enabled;
            int *entry;
            int remaining;
            func_002A7750(object, 2, missing);
            enabled = 1;
            entry = state->objects;
            for (remaining = 3; remaining >= 0; entry++, remaining--) {
                int index = *entry;
                if (index != missing) {
                    if (entry[4]) {
                        func_L00_003294F0((unsigned char *)&yeedilObjectsGp[index], enabled);
                    } else {
                        D_L20_001B2F9C[index].enabled = enabled;
                    }
                }
            }
            func_002A0430(state->event);
            if (state->callback) func_PAL_L20_002C59B0(0);
        }
        *(unsigned int *)(object + 0x78) = color | (0x80 << 24);
    } else if (object[0x20] == 2) {
        if (!state->activated) state->activated = 1;
        {
            unsigned int green = (color << 8) | (0x80 << 24);
            unsigned int blue = color << 16;
            *(unsigned int *)(object + 0x78) = blue | green;
        }
    }
}
