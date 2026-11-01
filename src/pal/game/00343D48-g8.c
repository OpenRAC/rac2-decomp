#include "include_asm.h"
extern void func_003480D8(void *, int, int);
extern void func_003363C0(void *, float);
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

void func_PAL_00343D48(char *object, void *argument)
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
    first = object + 0xEC;
    second = object + 0x138;
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

extern void func_00335E38(void *, float, float, float, float);
extern int func_PAL_0034A2F8(void *);
extern float D_001AE130 __attribute__((sda));
extern float D_001AE134 __attribute__((sda));
extern int D_00138344[];
extern int func_PAL_00343EF8(void *);
extern void func_00336320(void *);
extern void func_PAL_0034A300(void *);
extern int func_PAL_002A9FA0(int, int, int, int, int);

void func_PAL_00343FA0(char *self)
{
    int count = func_PAL_0034A2F8(self + 0x10);
    int i;
    int *slot;

    if (D_00138344[0] & 0x5000)
        func_PAL_002A9FA0(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        func_00335E38(self + 0xEC, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        func_00335E38(self + 0x138, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        slot = func_00335E20(self + 0x138);
        *slot = func_PAL_00343EF8(self) == i ? func_PAL_002A9FA0(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        func_00336320(self + 0xEC);
        func_00336320(self + 0x138);
    }
    func_PAL_0034A300(self + 0x10);
}
