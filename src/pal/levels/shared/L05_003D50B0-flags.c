#include "include_asm.h"

#include "common.h"
extern void func_002AF000(void *, float, float, float);
extern int D_L05_00221D10[];
extern float func_002A7878(float, float);
extern char *func_002ED688(char *);
extern void func_00282CC0(void *, void *, void *);
extern int D_L05_00221D10[];
extern char *D_L05_001B2614 __attribute__((sda));
extern void func_PAL_L05_0037D610(char *, int);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);

/* func_L05_003D1368 is in L05_003D1368-g8.c. */

/* func_L05_003D15E8 is in L05_003D15E8.c. */

void func_PAL_L05_003D5628(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_002ED688(obj) + 0x148) = 5;
    func_PAL_L05_0037D610(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(float *)(sub + 0x180) = 5.0f;
    *(int *)(sub + 0x2F0) = -1;
    *(int *)(sub + 0x2F4) = -1;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.04f;
    a = func_002A7878(0.0f, *(float *)table);
    b = func_002A7940();
    c = func_002A7940();
    func_002AF000(obj + 0x10, a, b, c);
    func_00282CC0(obj + 0x10, table + 0x30, obj + 0x10);
    *(int *)(sub + 0x26C) = 0;
}
