#include "include_asm.h"

#include "common.h"
typedef int EffectVector __attribute__((mode(TI)));
typedef struct { char pad[0x10]; EffectVector position; } EffectObject;
typedef struct { char pad[0x24]; int kind; char *object; char pad2[0x3C]; int active; } EffectWorld;
extern EffectWorld D_001A63A8;
extern float D_001B0228 SDATA(D_001B0228);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(float *, float *, float);
extern float func_00283B98(float, float);
extern float func_002A90F8(void *, void *);
extern void func_00282C88(void *);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_PAL_002C84A8(void *, void *, int);
extern float func_00282E48(void *, void *);
extern int func_00329DC0(void *, void *);
extern void func_PAL_0032B730(void *);
extern void func_002B0668(void *);
extern int func_002FD828(void *, void *, float, float, float);
extern void func_PAL_0032B650(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002C0428(void *, void *, float, float);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_0027CFD0(void *, void *);
extern void func_PAL_0032B920(void);

void func_PAL_0032AF58(char *self)
{
    float old[4] __attribute__((aligned(16)));
    float hit[4], zero[4], random[4];
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    int i;
    float height;
    switch ((unsigned char)self[0x20]) {
    case 0:
        self[0x20]=1;
        *(unsigned short *)(self + 0x34)|=8;
        *(int *)(state + 0x40)=0;
        *(int *)(state + 0x38)=0;
        *(int *)(state + 0x48)=0;
        if (!D_001A63A8.active && D_001A63A8.kind==-1) {
            D_001A63A8.object=self;
            D_001A63A8.kind=0xDB8;
        }
    case 1:
        qcopy(old, self + 0x10);
        func_00282CC0(self + 0x10, self + 0x10, state);
        *(float *)(state + 8)-=0.0044f;
        *(float *)(self + 0xF4)=func_00283B98(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8)=func_00283B98(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        func_002A90F8(self + 0x10, hit);
        func_00282C88(zero);
        for (i=7;i>=0;i--) {
            random[0]=func_002A78D8(0, D_001B0228);
            random[1]=func_002A78D8(0, D_001B0228);
            random[2]=func_002A78D8(0, D_001B0228);
            func_00282CC0(random, random, self + 0x10);
            func_PAL_002C84A8(random, state, func_002A7820(20, 40));
        }
        func_00282E48(old, self + 0x10);
        if (func_00329DC0(self, old)) {
            func_PAL_0032B730(self);
            if (*(int *)(state + 0x38)==2) self[0x20]=2;
            else {
                if (*(int *)(state + 0x38)) {
                    *(float *)(self + 0x18)+=1;
                    *(EffectVector *)velocity = ((EffectObject *)self)->position;
                    func_002B0668(velocity);
                    *(float *)(self + 0x18)-=1;
                    func_002FD828(self + 0x18, velocity, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
                    if (!*(int *)(state + 0x44)) func_PAL_0032B650(self);
                }
                self[0x20]=3;
                *(int *)(state + 0x34)=67;
            }
        }
        break;
    case 2:
        qcopy(old, self + 0x10);
        func_00282CC0(self + 0x10, self + 0x10, state);
        *(float *)(state + 8)-=0.0044f;
        *(float *)(self + 0xF4)=func_00283B98(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8)=func_00283B98(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        func_PAL_0032B730(self);
        if (*(int *)(state + 0x38)==1) {
            func_002E5CF8(0, 0, self);
            self[0x20]=3;
            *(int *)(state + 0x34)=67;
            *(float *)(self + 0x18)+=1;
            *(EffectVector *)position = ((EffectObject *)self)->position;
            func_002B0668(position);
            *(float *)(self + 0x18)-=1;
            func_002FD828(self + 0x18, velocity, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
            if (!*(int *)(state + 0x44)) func_PAL_0032B650(self);
        }
        break;
    case 3: {
        float one, low, high, scale;
        qcopy(old, self + 0x10);
        func_00282CC0(self + 0x10, self + 0x10, state);
        func_00282D30(state, state, 0.8f);
        *(float *)(state + 8)-=0.00352f;
        *(float *)(self + 0xF4)=func_00283B98(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8)=func_00283B98(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        func_00282E48(old, self + 0x10);
        *(float *)(state + 0x14)*=0.8f;
        *(float *)(state + 0x18)*=0.8f;
        if ((unsigned char)self[0x23] >= 3)
            self[0x23] -= 2;
        else
            self[0x23] = 0;
        one = 1.0f;
        low = -0.5f;
        high = 0.5f;
        scale = 0.2f;
        *(float *)(self + 0x18)+=one;
        height=func_002A90F8(self + 0x10, hit);
        *(float *)(self + 0x18)-=one;
        velocity[0]=func_002A7878(low, high);
        velocity[1]=func_002A7878(low, high);
        velocity[2]=func_002A7878(low, 2);
        velocity[3]=0;
        func_00282F20(velocity, velocity, func_002A7878(0.080000006f, 0.16000001f)*scale);
        func_PAL_002C0428(self + 0x10, velocity, func_002A7878(0.05f, 0.1f)*210000.0f, height);
        if (func_00282948(state + 0x34)) self[0x20]=4;
        break;
    }
    case 4:
        if (!*(int *)(state + 0x40)) {
            func_0029F338(self);
            return;
        }
        break;
    }
    /* The catalogue extent includes eight bytes before this return callback. */
    func_0027CFD0((char *)func_PAL_0032B920 + 8, self);
}
