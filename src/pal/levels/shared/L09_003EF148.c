#include "include_asm.h"


extern void func_002E5CF8(int a, int b, char *c);
extern void func_002A6C58(char *a, int b, int c);
extern void func_0029F338(void *entry);
extern void func_0032C700(void *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                          float f1, float f2, int s1, int s2, int s3, int s4);
extern void func_0029F338(void *entry);

void func_PAL_L09_003EF588(char *object)
{
    func_002E5CF8(2, 0, object);
    func_002A6C58(object, 0, 3);
    func_0032C700(object + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                  1.0f, 20.0f, 1, 1, 0, 0);
    func_0029F338(object);
}

