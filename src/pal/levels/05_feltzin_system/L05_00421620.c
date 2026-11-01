#include "include_asm.h"


#include "common.h"
extern void func_306630(char *dst, char *src, char *src2);
extern float func_332B50(float a, float b);
extern float func_332C18(void);
extern void func_33B330(char *dst, float a, float b, float c);
extern char *func_379CA0(char *object);
extern void func_37AEC0(char *object, int flag);
extern void func_L05_0041CA70(char *obj);
extern int D_L05_00221D10[];
extern char *D_L05_001B2614 __attribute__((sda));

void func_PAL_L05_00421830(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x268) = 0;
    *(float *)(sub + 0x180) = 5.0f;
    *(float *)(obj + 0x2C) = 0.08f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}


