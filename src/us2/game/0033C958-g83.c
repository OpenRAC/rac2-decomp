#include "include_asm.h"

extern void func_US2_0033BF90(char *);
extern void func_US2_00348E58(char *, int);
extern void func_US2_00348E70(char *);
extern unsigned char D_001A7BB4;
extern int D_001ADED8[2] __attribute__((sda));

void func_US2_0033F478(char *object)
{
    char *p;
    func_US2_0033BF90(object + 8);
    p = object + 0x2E0;
    func_US2_00348E58(p, D_001ADED8[D_001A7BB4]);
    func_US2_00348E70(p);
}

extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_US2_0033BC20(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_US2_0033C098(void *, int, int, int);
extern void func_US2_0033C078(void *, float, float, float, float, float, float);
extern void func_US2_0033F610(void *, int);
extern int D_001ADEF0[2] __attribute__((sda));

void func_US2_0033F510(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x2D8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2D8) = 255.0f;
    (*(float **)(object + 0x2D8))[1] = 208.0f;
    child = object + 8;
    func_US2_0033BC20(child, argument, D_001ADEF0);
    text = func_00288FB8(0x2CB7);
    func_US2_0033C098(child, text, 0, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, -128.0f, -183.0f, 112.0f, 110.0f, 102.0f, 110.0f);
    func_US2_0033F610(object, 0);
}

extern void func_US2_0033C0F0(void *, float);
extern void func_US2_0033F3F0(void *, int);
extern int D_001ADEC8[2] __attribute__((sda));
extern void func_US2_00348BF8(void *, void *);
extern void func_US2_00348E10(void *, int, int);
extern void func_US2_00348E20(void *, int);

void func_US2_0033F200(char *object, void *argument)
{
    int *allocation;
    char *child, *widget;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x3BC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x3BC) = 255.0f;
    (*(float **)(object + 0x3BC))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2E0;
    func_US2_0033BC20(child, argument, D_001ADEC8);
    text = func_00288FB8(0x2C36);
    second = func_00288FB8(0x2C0B);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_00348BF8(widget, argument);
    func_US2_00348E10(widget, -83, 32);
    func_US2_00348E20(widget, 1);
    func_US2_0033F3F0(object, 0);
}
