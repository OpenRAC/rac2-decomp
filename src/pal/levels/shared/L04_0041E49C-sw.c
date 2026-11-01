#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_001B01E8 __attribute__((sda));
typedef struct { char pad[0x34]; int owner; char tail[8]; } ParticleRecord;
extern ParticleRecord D_0022B0A0[100];
typedef struct { char pad[0x24]; int kind; char *owner; char tail[0x3C]; int active; } OwnerContext;
extern OwnerContext D_001A63A8;
extern char D_001BAFA0[0x30];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float), func_00282E48(void *, void *);
extern void func_00328848(void *), func_PAL_0032A898(void *, void *, float);
extern int func_003286D0(void *, void *);
extern void func_00328758(void *), func_002E5CF8(int, int, void *);
extern float func_002A7940(void), func_002A7878(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_PAL_002BEF58(void *, void *, int, float);
extern int func_00282948(int *);
extern void func_0029F338(void *), func_PAL_0032A0E0(void *), func_00329328(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_PAL_0032A1E8(void);

void func_PAL_L04_0041F8A8(char *self)
{
    float previous[4], velocity[4];
    char *state = *(char **)(self + 0x68);
    float angle, elevation;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0: {
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(state + 0x48) = 0;
        {
            int initialized = D_001B01E8;
            *(int *)(state + 0x4C) = 0;
            *(int *)(state + 0x50) = 0;
            if (!initialized) {
                int i;
                for (i = 99; i >= 0; i--) D_0022B0A0[i].owner = 0;
                D_001B01E8 = 1;
            }
        }
        {
            OwnerContext *context = &D_001A63A8;
            if (!context->active && context->kind == -1) {
                context->owner = self;
                context->kind = 0xDB9;
            }
        }
    }
    /* Fall through to move the object on its first update. */
    case 1:
        *(Quad *)previous = *(Quad *)(self + 0x10);
        func_00282CC0(self + 0x10, self + 0x10, state);
        *(float *)(state + 8) -= 0.0044f;
        *(float *)(self + 0xF4) = func_00283B98(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8) = func_00283B98(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        func_00328848(self);
        func_PAL_0032A898(self, self + 0x10, func_00282E48(previous, self + 0x10) * 0.5f);
        if (func_003286D0(self, previous)) {
            *(unsigned char *)(self + 0x20) = 2;
            *(int *)(state + 0x44) = 17;
            *(int *)(state + 0x58) = 128;
            *(unsigned short *)(self + 0x34) |= 8;
            func_00282C88(state);
            func_00328758(self);
            func_002E5CF8(0, 0, self);
            func_00282D30(state + 0x20, D_001BAFA0 + 0x20, 0.0009765625f);
            func_00282F20(state + 0x20, state + 0x20, 1.0f);
            *(Quad *)(state + 0x30) = *(Quad *)D_001BAFA0;
            if (!*(int *)(state + 0x54)) {
                float *v = velocity;
                int i;
                for (i = 7; i >= 0; i--) {
                    angle = func_002A7940();
                    elevation = func_002A7878(0.392699093f, 3.14159274f);
                    func_002AF000(v, 0.16000001f, angle, elevation);
                    func_PAL_002BEF58(self + 0x10, v, 0, -1.0f);
                }
            }
        }
        break;
    case 2:
        func_PAL_0032A898(self, self + 0x10, 0.1f);
        func_00282CC0(self + 0x10, self + 0x10, state);
        *(float *)(state + 8) -= 0.0022f;
        *(unsigned char *)(self + 0x23) -= 4;
        func_00282948((int *)(state + 0x44));
        if (*(unsigned char *)(self + 0x23) > 4) *(unsigned char *)(self + 0x23) -= 4;
        if (!*(int *)(state + 0x44) && *(unsigned char *)(self + 0x23) < 4) *(unsigned char *)(self + 0x20) = 3;
        break;
    case 3:
        if (*(unsigned char *)(self + 0x23)) --*(unsigned char *)(self + 0x23);
        if (*(int *)(state + 0x58) >= 5) *(int *)(state + 0x58) -= 4;
        else if (*(int *)(state + 0x58) > 0) --*(int *)(state + 0x58);
        if (!*(long long *)(state + 0x48) && !*(int *)(state + 0x58)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(self + 0x98) = 0;
            *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 4:
        if (func_00282948((int *)(state + 0x5C))) {
            func_0029F338(self);
            return;
        }
        break;
    }
    func_PAL_0032A0E0(self);
    func_00329328(self);
    func_L00_002E6EF8(func_PAL_0032A1E8, self);
}
