#include "include_asm.h"

extern int D_L02_001B359C;
extern int D_L02_001B03F0 __attribute__((sda));
typedef struct { char pad[0x160]; float amount; int pad2; int time; int phase; } Shake;
extern Shake D_L02_001BA3C0;
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_0029F530(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_PAL_002B5E30(char *, float);
extern float func_L02_00321C30(void *, void *, float);
extern void *func_L02_003FC0B8(void *);
extern float *func_L02_003FC098(void *);
extern int func_L00_003206B8(void *, void *);
extern void func_PAL_L01_00323068(char *, void *);
extern void *func_0029FCC0(char *, int, void *);
extern void func_002833F0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L01_00322288(char *, float);
extern float func_00283C28(float);
extern void func_L02_003DAB68(char *);
extern float func_002AA2E8(float *, float, float);

void func_PAL_L02_003DD890(char *self) {
    float before[4];
    float after[4];
    float delta[4];
    char *state = *(char **)(self + 0x68);
    float *target = (float *)(state + 0x230);
    float distance = func_00282E80(self + 0x10, target);
    float heading = func_00283248(target[0] - *(float *)(self + 0x10), target[1] - *(float *)(self + 0x14));
    float frame = func_0029F530(self);
    char *part = (char *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + D_L02_001B359C);
    int saved = *(int *)(part + 0x98);
    unsigned int mode;
    float speed;
    *(int *)(part + 0x98) = 0;
    func_002B60B0(self, 0.0024f, 0.062000003f, 0.005026549f, 0.12566373f);
    mode = *(unsigned char *)(self + 0x42);
    switch (mode) {
    case 0:
    if (*(unsigned char *)(self + 0x20) != 4)
        func_PAL_002B5E30(self, *(float *)(self + 0xF8));
    else
        func_L02_00321C30(self + 0x10, &D_L02_001B03F0, 0.20000002f);
    break;
    case 1:
    if (func_L00_003206B8(self + 0x10, func_L02_003FC0B8(*(void **)(self + 0xB8))))
        func_PAL_L01_00323068(self, target);
    else
        func_PAL_L01_00323068(self, func_L02_003FC098(*(void **)(self + 0xB8)));
    if ((frame > 0.0f && frame < 2.0f) || (frame > 15.0f && frame < 17.0f) ||
        (frame > 30.0f && frame < 32.0f) || (frame > 45.0f && frame < 47.0f)) {
        D_L02_001BA3C0.amount = 0.05f;
        D_L02_001BA3C0.time = 12;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 2:
    if (frame > 12.0f && frame < 25.0f) {
        func_0029FCC0(self, 4, before);
        func_PAL_002B5E30(self, heading);
        func_002833F0(self + 0xC0, self + 0xF0);
        func_0029FCC0(self, 4, after);
        func_00282CF0(delta, before, after);
        func_00282CC0(self + 0x10, self + 0x10, delta);
    } else if (frame > 42.0f && frame < 55.0f) {
        func_0029FCC0(self, 8, before);
        func_PAL_002B5E30(self, heading);
        func_002833F0(self + 0xC0, self + 0xF0);
        func_0029FCC0(self, 8, after);
        func_00282CF0(delta, before, after);
        func_00282CC0(self + 0x10, self + 0x10, delta);
    }
    if ((frame > 0.0f && frame < 2.0f) || (frame > 29.0f && frame < 31.0f)) {
        D_L02_001BA3C0.amount = 0.1f;
        D_L02_001BA3C0.time = 12;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 3:
        if (frame < 23.0f)
            break;
    case 4:
    func_L01_00322288(self, func_00283248(*(float *)(state + 0xF0), *(float *)(state + 0xF4)));
    *(float *)(state + 0xF8) -= *(float *)(state + 0x7C);
    func_00282CC0(self + 0x10, self + 0x10, state + 0xF0);
    break;
    case 5:
    if (frame > 3.0f && frame < 5.0f) {
        D_L02_001BA3C0.amount = 0.4f;
        D_L02_001BA3C0.time = 21;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 6:
    if (frame > 20.0f && frame < 22.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 21;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 7:
    if ((unsigned int)(*(unsigned char *)(self + 0x20) - 10) >= 2) {
        *(float *)(self + 0xF8) += ((*(float *)(state + 0x20) / (float)*(short *)(state + 0x24)) * -90.0f + 160.0f) * 0.0003490659f;
        *(float *)(self + 0xF8) = func_00283C28(*(float *)(self + 0xF8));
        func_002833F0(self + 0xC0, self + 0xF0);
        func_L02_003DAB68(self);
        if (distance > 12.0f && *(unsigned char *)(self + 0x20) != 10) {
            if (func_L00_003206B8(self + 0x10, func_L02_003FC0B8(*(void **)(self + 0xB8)))) {
                speed = ((*(float *)(state + 0x20) / (float)*(short *)(state + 0x24)) * -2.2f + 3.0f) * 0.020000001f;
                func_002AA2E8((float *)(self + 0x10), target[0], speed);
                func_002AA2E8((float *)(self + 0x14), target[1], speed);
            } else {
                func_002AA2E8((float *)(self + 0x10), func_L02_003FC098(*(void **)(self + 0xB8))[0], 0.40000004f);
                func_002AA2E8((float *)(self + 0x14), func_L02_003FC098(*(void **)(self + 0xB8))[1], 0.40000004f);
            }
        }
    }
    break;
    case 8:
    if (frame > 30.0f && frame < 32.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 21;
        D_L02_001BA3C0.phase = 0;
    }
    case 9:
        break;
    }
    if (*(float *)(self + 0x18) < func_L02_003FC098(*(void **)(self + 0xB8))[2])
        *(float *)(self + 0x18) = func_L02_003FC098(*(void **)(self + 0xB8))[2];
    *(int *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + D_L02_001B359C + 0x98) = saved;
}
