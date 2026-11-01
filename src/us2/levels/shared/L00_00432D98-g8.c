#include "include_asm.h"

extern void func_US2_0033C0F0(void *, float);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_US2_0033BC20(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_US2_0033C098(void *, int, int, int);
extern void func_US2_0033C078(void *, float, float, float, float, float, float);
extern void func_US2_L00_004348C8(void *, int);
extern int D_001ADDE0[2] __attribute__((sda));

extern int D_US2_001AE1A0[2] __attribute__((sda));

void func_US2_L00_004347A0(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001AE1A0);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_L00_004348C8(object, 0);
}



extern void func_US2_L00_00434F48(void *, int);

extern int D_US2_001AE1C0[2] __attribute__((sda));

void func_US2_L00_00434E20(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001AE1C0);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_L00_00434F48(object, 0);
}



extern void func_US2_L00_00435140(void *, int);

extern int D_US2_001AE1D0[2] __attribute__((sda));

void func_US2_L00_00435018(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001AE1D0);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_L00_00435140(object, 0);
}


