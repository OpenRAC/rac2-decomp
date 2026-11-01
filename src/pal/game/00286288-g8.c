#include "include_asm.h"

extern char D_L00_001B8FF0[];
extern void func_00283738(char *a, char *b, char *c);
extern void func_002ACE78(char *a, char *b, float f);
extern void func_00283958(char *a, char *b);
extern float D_L00_001A8DD0 __attribute__((sda));

void func_PAL_00288638(float *arg0) { char temp[0x40]; float value = *arg0 * 0.0003490659f * D_L00_001A8DD0; func_002ACE78(temp, D_L00_001B8FF0, value); func_00283958(temp, temp + 0x10); func_00283738(D_L00_001B8FF0, temp + 0x10, D_L00_001B8FF0); }

typedef struct { char pad[48]; } Block48_F8c659bbc;
typedef struct { char pad[16]; } Block16_F8c659bbc;
extern char D_L00_001B1B10[] __attribute__((sda));
extern char D_L00_001B8DC0[];
extern char D_L00_001A8E30 __attribute__((sda));
extern void func_00282CF0(char *a, char *b, char *c);
extern void func_00282F20(char *a, char *b, float f);
extern void func_002833F0(char *a, char *b);
extern void func_00282DD8(char *a, char *b, char *c);
extern float func_00282DF0(char *a);
extern void func_002AAC80(char *a, float f1, float f2, float f3, float f4);

void func_PAL_002884F0(char *arg0, int arg1)
{
    Block48_F8c659bbc a;
    Block48_F8c659bbc b;
    Block48_F8c659bbc c;
    Block16_F8c659bbc d;
    Block16_F8c659bbc e;
    float v;

    func_00282CF0((char *)&e, D_L00_001B8DC0, D_L00_001B1B10);
    func_00282F20((char *)&e, (char *)&e, 1.0f);
    func_002833F0((char *)&c, (char *)&D_L00_001A8E30);
    func_00283738((char *)&b, D_L00_001B8DC0 + 560, (char *)&c);
    func_00282DD8((char *)&d, (char *)&b, (char *)&e);
    v = func_00282DF0((char *)&d) * 0.5f;
    if (arg1 != 0) {
        func_002ACE78((char *)&d, (char *)&d, -v);
    } else {
        func_002AAC80(arg0, v, 0.0008377582f,
                0.0008377582f,
                0.062831864f);
        func_002ACE78((char *)&d, (char *)&d, -*(float *)arg0);
    }
    func_00283958((char *)&d, (char *)&a);
    func_00283738(D_L00_001B8FF0, (char *)&a, D_L00_001B8FF0);
}
