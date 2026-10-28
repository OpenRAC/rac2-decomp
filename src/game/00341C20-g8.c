#include "include_asm.h"

extern float D_001AE180 __attribute__((sda));
extern float D_001AE17C;
extern float D_001AE178 __attribute__((sda));
extern void func_00335E38(void *, float, float, float, float);
void func_003423C8(char *self)
{
    int index = *(int *)(self + 0x16C);
    float *v = *(float **)(self + 0x180);
    func_00335E38(self + 0xE4, D_001AE178 + v[0],
            (D_001AE17C + D_001AE180 * (float)index) + v[1],
            0.0f, 0.0f);
}

extern float D_001AE188 __attribute__((sda));
extern float D_001AE18C;
extern float D_001AE190 __attribute__((sda));
extern float D_001AE194 __attribute__((sda));
extern void func_003480F0(void *, float, float);
extern void func_003480D8(void *, int, int);
extern void *func_00347F80(void *, int);
extern int func_00348128(void *);
void func_00342428(char *self, int arg)
{
    char *child = self + 0x188;
    float *position = *(float **)(self + 0x180);
    func_003480F0(child, position[0] + D_001AE188, position[1] + D_001AE18C);
    func_003480D8(child, (int)D_001AE190, (int)D_001AE194);
    func_00347F80(child, arg);
    *(int *)(self + 0x16C) = func_00348128(child);
}
extern float D_001AE198 __attribute__((sda));
extern float D_001AE19C;
extern float D_001AE1A0 __attribute__((sda));
extern float D_001AE1A4;
extern float D_001AE1A8[2] __attribute__((sda));
extern int func_00348130(void *);
extern void func_003363C0(void *, float);
extern void func_00342420(void *);
int func_003424C0(char *self, int arg)
{
    char *child = self + 0x4C;
    float *position = *(float **)(self + 0x180);
    float *scale;
    unsigned int index;
    func_00335E38(self, D_001AE198 + position[0], D_001AE19C + position[1], 0.0f, 0.0f);
    position = *(float **)(self + 0x180);
    func_00335E38(child, D_001AE1A0 + position[0], D_001AE1A4 + position[1], 0.0f, 0.0f);
    index = func_00348130(self + 0x188) - 1;
    scale = (float *)((char *)D_001AE1A8 + (index << 2));
    func_003363C0(self, *scale);
    func_003363C0(child, *scale);
    func_00342428(self, arg);
    func_003423C8(self);
    func_00342420(self);
    return *(int *)(self + 0x16C);
}
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern char D_001ADC10[], D_001ADC18[];
extern char *D_001A8CFC[] __attribute__((sda));
extern float D_001AE12C __attribute__((sda));
extern void func_003361E0(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00347EC8(void *, void *);
extern void func_00341EE8(void *, int);
void func_00341CE0(char *object, void *argument)
{
    int *allocation;
    char *first, *second, *widget;
    *(void **)(object + 4) = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)object = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)object = 250.0f;
    (*(float **)object)[1] = 120.0f;
    first = object + 0xDC;
    second = object + 0x128;
    widget = object + 0x10;
    func_003361E0(first, D_001ADC10, argument);
    func_003361E0(second, D_001ADC18, argument);
    *func_00335E20(first) = 0x60442D00;
    *func_00335E20(second) = 0x55F0C070;
    func_00336390(first, D_001A8CFC[0] + 0x8710, 0x73);
    func_00336390(second, D_001A8CFC[0] + 0x8710, 0x74);
    func_003363C0(first, D_001AE12C);
    func_003363C0(second, D_001AE12C);
    func_00347EC8(widget, argument);
    func_003480D8(widget, 11, 60);
    func_00341EE8(object, 0);
}
extern char D_001ADC20[], D_001ADFC0[], D_001AE0C0[];
extern int D_001AE138 __attribute__((sda));
extern void func_00336710(void *, void *, void *);
extern void func_00336920(void *, int, int);
extern void func_00115484(void *, int, int);
extern void func_00348118(void *, int);
extern void func_00335F88(void *, float, float, float, float);
/* Sets up a level object: it allocates the pair of positions at +0x180 and puts
   253.0 and 200.0 in it, names the four children at +0x00, +0x4C, +0xE4 and
   +0x130, gives each of them its colour and its metric, and ends with the
   object's own fields at +0x170, +0x174, +0x178 and +0x17C. */
void func_00342118(char *object, void *arg)
{
    int *allocation;
    *(void **)(object + 0x184) = arg;
    if (arg != 0) {
        allocation = func_00336DA8(16, func_00336E40(arg));
        *(int **)(object + 0x180) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(object + 0x170) = 1;
    (*(float **)(object + 0x180))[0] = 253.0f;
    (*(float **)(object + 0x180))[1] = 200.0f;
    func_003361E0(object, D_001ADC10, arg);
    func_003361E0(object + 0x4C, D_001ADC20, arg);
    func_003361E0(object + 0xE4, D_001ADFC0, arg);
    func_00336710(object + 0x130, D_001AE0C0, arg);
    func_00347EC8(object + 0x188, arg);
    *func_00335E20(object) = 0x60442D00;
    *func_00335E20(object + 0x4C) = 0x55F0C070;
    *func_00335E20(object + 0xE4) = 0x70FFFEED;
    *func_00335E20(object + 0x130) = 0x60F0F0B0;
    func_003363C0(object, 1.0f);
    func_003363C0(object + 0x4C, 1.0f);
    func_00336390(object, D_001A8CFC[0] + 0x8710, 0xCD);
    func_00336390(object + 0x4C, D_001A8CFC[0] + 0x8710, 0xCE);
    func_00336390(object + 0xE4, D_001A8CFC[0] + 0x8710, 0x95);
    func_00335F88(object + 0xE4, 1.0f, 1.05f, 0.0f, 0.0f);
    func_00336920(object + 0x130, 0xEA9D, 0);
    func_00115484(object + 0x16C, 0, 4);
    func_00335F88(object + 0x130, 32.0f, 32.0f, 0.0f, 0.0f);
    *(int *)(object + 0x174) = 0xEAA6;
    *(void **)(object + 0x178) = &D_001AE138;
    *(int *)(object + 0x17C) = 4;
    func_00348118(object + 0x188, *(int *)(object + 0x16C));
}

extern float D_001AE130 __attribute__((sda));
extern float D_001AE134 __attribute__((sda));
extern int D_00138344[];
extern int func_00341E90(void *);
extern int *func_00335E20(void *);
extern void func_00336320(void *);
extern void func_00348138(void *);
extern int func_002A9588(int, int, int, int, int);

void func_00341F38(char *self)
{
    int count = func_00348130(self + 0x10);
    int i;
    int *slot;

    if (D_00138344[0] & 0x5000)
        func_002A9588(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        func_00335E38(self + 0xDC, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        func_00335E38(self + 0x128, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        slot = func_00335E20(self + 0x128);
        *slot = func_00341E90(self) == i ? func_002A9588(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        func_00336320(self + 0xDC);
        func_00336320(self + 0x128);
    }
    func_00348138(self + 0x10);
}
