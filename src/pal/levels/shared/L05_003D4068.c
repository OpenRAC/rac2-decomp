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

/* Gives the object its reach: the table's entry for the object's id picks the record, and
 * the record takes the cone the object was given. */
void func_PAL_L05_003D4068(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_002ED688(obj) + 0x148) = 1;
    func_PAL_L05_0037D610(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1BC) = -1;
    *(int *)(sub + 0x1C0) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(obj + 0x2C) = 0.06f;
    a = func_002A7878(0.0f, *(float *)table);
    b = func_002A7940();
    c = func_002A7940();
    func_002AF000(obj + 0x10, a, b, c);
    func_00282CC0(obj + 0x10, table + 0x30, obj + 0x10);
}


