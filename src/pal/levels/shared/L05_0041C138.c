#include "include_asm.h"

#include "common.h"
extern char *D_L05_001B2614 __attribute__((sda));
extern int D_L05_00221D10[];
extern char *func_002ED688(char *object);
extern void func_PAL_L05_0037D610(char *object, int flag);
extern float func_002A7878(float a, float b);
extern float func_002A7940(void);
extern void func_002AF000(char *dst, float a, float b, float c);
extern void func_00282CC0(char *dst, char *src, char *src2);

/* Spawns the object's effect: marks the object, takes one record of the shared
   128-byte table by the global index and gives it a random position. */
void func_PAL_L05_0041C138(char *object)
{
    char *sub = *(char **)(object + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(object + 0x20) = 1;
    *(unsigned short *)(object + 0x34) = *(unsigned short *)(object + 0x34) | 0x100;
    *(int *)(func_002ED688(object) + 0x148) = 1;
    func_PAL_L05_0037D610(object, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1C8) = 0x64;
    *(int *)(sub + 0x1C0) = -1;
    *(int *)(sub + 0x1C4) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    a = func_002A7878(0.0f, *(float *)table);
    b = func_002A7940();
    c = func_002A7940();
    func_002AF000(object + 0x10, a, b, c);
    func_00282CC0(object + 0x10, table + 0x30, object + 0x10);
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(object + 0x2C) = 0.02f;
}


