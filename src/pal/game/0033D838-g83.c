#include "include_asm.h"

extern void func_PAL_0033CFD0(void *, float);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_PAL_0033CB00(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_PAL_0033CF78(void *, int, int, int);
extern void func_PAL_0033CF58(void *, float, float, float, float, float, float);
extern void func_PAL_0033EEF8(void *, int);
extern int D_001ADE48[2] __attribute__((sda));
extern char D_001ADC88[];
extern void func_00336408(void *, int, int, void *, void *);
extern void func_00336CC8(void *, int);
extern void func_PAL_003388E8(void *, int);
extern void func_00336B98(void *, int);
extern void func_00336498(void *, int, int);
extern void func_003364B0(void *, int, int);
extern void func_00336CE0(void *, int);
extern void func_00336CC0(void *, int);

void func_PAL_0033EC98(char *object, void *argument)
{
    int *allocation;
    char *child, *widget, *secondWidget;
    void *table;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = func_00336DA8(16, func_00336E40(argument));
        *(int **)(object + 0x36C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x36C) = 255.0f;
    (*(float **)(object + 0x36C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2DC;
    secondWidget = object + 0x324;
    func_PAL_0033CB00(child, argument, D_001ADE48);
    text = func_00288FB8(0xBA8);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.67f);
    table = D_001ADC88;
    func_00336408(widget, 150, 1, table, argument);
    func_00336CC8(widget, 16);
    func_PAL_003388E8(widget, 0x400);
    func_00336B98(widget, 0);
    func_00336498(widget, 0x55F0C070, 0x55F0C070);
    func_003364B0(widget, 0x60442D00, 0x60442D00);
    func_00336CE0(widget, 0x20FFFFFF);
    func_00336CC0(widget, 0);
    func_00336408(secondWidget, 150, 1, table, argument);
    func_00336CC8(secondWidget, 16);
    func_PAL_003388E8(secondWidget, 0x400);
    func_00336B98(secondWidget, 0);
    func_00336498(secondWidget, 0x55F0C070, 0x55F0C070);
    func_003364B0(secondWidget, 0x60442D00, 0x60442D00);
    func_00336CE0(secondWidget, 0x20FFFFFF);
    func_00336CC0(secondWidget, 0);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0033EEF8(object, 0);
}

extern void func_PAL_00340348(void *, int);
extern int D_001ADEC8[2] __attribute__((sda));
extern void func_PAL_0034A090(void *, void *);
extern void func_PAL_0034A2A0(void *, int, int);
extern void func_PAL_0034A2B0(void *, int);

void func_PAL_00340158(char *object, void *argument)
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
    func_PAL_0033CB00(child, argument, D_001ADEC8);
    text = func_00288FB8(0xBB1);
    second = func_00288FB8(0xB86);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_PAL_0033CFD0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_0034A090(widget, argument);
    func_PAL_0034A2A0(widget, -83, 32);
    func_PAL_0034A2B0(widget, 1);
    func_PAL_00340348(object, 0);
}

extern void func_PAL_0033CE70(char *);
extern void func_PAL_0034A2E8(char *, int);
extern void func_PAL_0034A300(char *);
extern unsigned char D_001A7BB4;
extern int D_001ADED8[2] __attribute__((sda));

void func_PAL_00340418(char *object)
{
    char *p;
    func_PAL_0033CE70(object + 8);
    p = object + 0x2E0;
    func_PAL_0034A2E8(p, D_001ADED8[D_001A7BB4]);
    func_PAL_0034A300(p);
}

extern void func_PAL_003405B0(void *, int);
extern int D_001ADEF0[2] __attribute__((sda));

void func_PAL_003404B0(char *object, void *argument)
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
    func_PAL_0033CB00(child, argument, D_001ADEF0);
    text = func_00288FB8(0xC31);
    func_PAL_0033CF78(child, text, 0, func_00288FB8(0xB60));
    func_PAL_0033CF58(child, -128.0f, -183.0f, 112.0f, 110.0f, 102.0f, 110.0f);
    func_PAL_003405B0(object, 0);
}

extern void func_00335E38(char *p, float x, float y, float zero, float zero2);
extern float D_L04_001AE1E0 __attribute__((sda));
extern float D_L04_001AE1E8 __attribute__((sda));
extern float D_L04_001AE1F0 __attribute__((sda));
extern float D_L04_001AE1F8 __attribute__((sda));
extern float D_L04_001AE1E4;
extern float D_L04_001AE1EC;
extern float D_L04_001AE1F4;
extern float D_L04_001AE1FC;
struct pos {
    float x;
    float y;
};

void func_PAL_00340C88(char *self)
{
    float zero = 0.0f;

    func_00335E38(self + 1400, D_L04_001AE1F8 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1FC + (*(struct pos **)(self + 728))->y, zero, zero);
    func_00335E38(self + 1136, D_L04_001AE1E0 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1E4 + (*(struct pos **)(self + 728))->y, zero, zero);
    func_00335E38(self + 1224, D_L04_001AE1E8 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1EC + (*(struct pos **)(self + 728))->y, zero, zero);
    func_00335E38(self + 1312, D_L04_001AE1F0 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1F4 + (*(struct pos **)(self + 728))->y, zero, zero);
}
