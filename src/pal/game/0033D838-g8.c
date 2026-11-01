#include "include_asm.h"

extern void func_PAL_0033CFD0(void *, float);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_PAL_0033CB00(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_PAL_0033CF78(void *, int, int, int);
extern void func_PAL_0033CF58(void *, float, float, float, float, float, float);
extern void func_PAL_0033E160(void *, int);
extern int D_001ADDE0[2] __attribute__((sda));

void func_PAL_0033E038(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_001ADDE0);
    text = func_00288FB8(0x10FC);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.65f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033E160(object, 0);
}

extern void func_PAL_0033E460(void *, int);

extern int D_PAL_001ADE68[2] __attribute__((sda));

void func_PAL_0033E338(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADE68);
    text = func_00288FB8(0xBA9);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.65f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033E460(object, 0);
}



extern void func_PAL_0033E9E8(void *, int);

extern int D_PAL_001ADEB0[2] __attribute__((sda));

void func_PAL_0033E8C0(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADEB0);
    text = func_00288FB8(0xBA4);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.2f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033E9E8(object, 0);
}



extern void func_PAL_0033F470(void *, int);

extern int D_PAL_001ADEF0[2] __attribute__((sda));

void func_PAL_0033F348(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADEF0);
    text = func_00288FB8(0xBAA);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033F470(object, 0);
}



extern void func_PAL_0033F738(void *, int);

extern int D_PAL_001ADF00[2] __attribute__((sda));

void func_PAL_0033F610(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADF00);
    text = func_00288FB8(0xB72);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033F738(object, 0);
}



extern void func_PAL_0033FB00(void *, int);

extern int D_PAL_001ADF10[2] __attribute__((sda));

void func_PAL_0033F9D8(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADF10);
    text = func_00288FB8(0xB72);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033FB00(object, 0);
}



extern void func_PAL_0033FDF8(void *, int);

extern int D_PAL_001ADF20[2] __attribute__((sda));

void func_PAL_0033FCD0(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADF20);
    text = func_00288FB8(0xB72);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033FDF8(object, 0);
}



extern void func_PAL_00340038(void *, int);

extern int D_PAL_001ADF30[2] __attribute__((sda));

void func_PAL_0033FF10(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    func_PAL_0033CB00(child, argument, D_PAL_001ADF30);
    text = func_00288FB8(0xB72);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_00340038(object, 0);
}


