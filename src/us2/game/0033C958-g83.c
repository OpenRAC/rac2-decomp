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

extern void func_US2_0033E8B0(void *, int);
extern int D_001ADDE0[2] __attribute__((sda));

extern int D_US2_001ADE60[2] __attribute__((sda));

void func_US2_0033E788(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001ADE60);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_0033E8B0(object, 0);
}



extern void func_US2_0033EC80(void *, int);

extern int D_US2_001ADE70[2] __attribute__((sda));

void func_US2_0033EB58(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001ADE70);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_0033EC80(object, 0);
}



extern void func_US2_0033EF30(void *, int);

extern int D_US2_001ADE80[2] __attribute__((sda));

void func_US2_0033EE08(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001ADE80);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_0033EF30(object, 0);
}



extern void func_US2_0033F128(void *, int);

extern int D_US2_001ADE90[2] __attribute__((sda));

void func_US2_0033F000(char *object, void *argument)
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
    func_US2_0033BC20(child, argument, D_US2_001ADE90);
    text = func_00288FB8(0x2BF7);
    second = func_00288FB8(0x2BE4);
    func_US2_0033C098(child, text, second, func_00288FB8(0x2BE5));
    func_US2_0033C078(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_US2_0033C0F0(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_0033F128(object, 0);
}



extern void func_US2_0033BE70(void *);
extern void func_0033B018(void *, float, float);
extern void func_00335E38(void *, float, float, float, float);
extern int func_002E5E58(int, int, void *);
extern void func_00132938(int);
extern void func_00336B98(void *, int);
extern void func_002E4860(void);
extern unsigned char D_001A7B94[] __attribute__((sda));
extern struct { int w0, w1, w2; } D_00138340;
extern float D_L00_001AE198 __attribute__((sda));
extern float D_L00_001AE1A0 __attribute__((sda));
extern float D_L00_001AE19C, D_L00_001AE1A4;

int func_US2_0033E070(char *object, int flags)
{
    char *p = object + 8;
    float *vec;

    func_US2_0033BE70(p);
    vec = *(float **)(object + 0x36C);
    func_0033B018(p, vec[0], vec[1]);
    vec = *(float **)(object + 0x36C);
    func_00335E38(object + 0x2DC, vec[0] + D_L00_001AE198,
                 vec[1] + D_L00_001AE19C, 0.0f, 0.0f);
    vec = *(float **)(object + 0x36C);
    func_00335E38(object + 0x324, vec[0] + D_L00_001AE1A0,
                 vec[1] + D_L00_001AE1A4, 0.0f, 0.0f);
    if (flags & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 2) % 3;
    } else if (flags & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 1) % 3;
    } else if (D_00138340.w0 & 0x8000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(D_001A7B94 + 12) - 6;
            *(int *)(D_001A7B94 + 12) = value < 0 ? 0 : value;
            break;
        }
        case 1: {
            int value = *(int *)(D_001A7B94 + 8) - 6;
            *(int *)(D_001A7B94 + 8) = value < 0 ? 0 : value;
            break;
        }
        }
    } else if (D_00138340.w0 & 0x2000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(D_001A7B94 + 12) + 6;
            *(int *)(D_001A7B94 + 12) = value > 1024 ? 1024 : value;
            break;
        }
        case 1: {
            int value = *(int *)(D_001A7B94 + 8) + 6;
            *(int *)(D_001A7B94 + 8) = value > 1024 ? 1024 : value;
            break;
        }
        }
    } else if (flags & 0x40) {
        if (*(int *)(object + 0x2D8) == 2) {
            int value;
            func_002E5E58(4, 0, 0);
            value = *(int *)(D_001A7B94 + 4) == 0;
            *(int *)(D_001A7B94 + 4) = value;
            func_00132938(!value);
        } else {
            func_002E5E58(5, 0, 0);
        }
    }
    func_00336B98(object + 0x324, *(int *)(D_001A7B94 + 8));
    func_00336B98(object + 0x2DC, *(int *)(D_001A7B94 + 12));
    func_002E4860();
    return (flags >> 6) & 1;
}
