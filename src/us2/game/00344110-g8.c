#include "include_asm.h"

typedef unsigned char u8;
extern int func_00343060(u8 *);
extern void func_00335E68(u8 *, int);
extern void func_00335E38(void *, float, float, float, float);
extern float D_001AE214;
extern float D_001AE210 __attribute__((sda));

void func_US2_003444E8(u8 *a0) {
    if (func_00343060(a0 + 0x2C8) == 0) {
        func_00335E68(a0 + 0x208, 0);
    } else {
        int *v = *(int **)(a0 + 0x2B8);
        func_00335E38(a0 + 0x208, D_001AE210 + *(float *)v,
                      D_001AE214 + *(float *)((u8 *)v + 4), 0.0f, 0.0f);
    }
}

extern const char *func_00288FB8(int);
extern void func_00115DA8(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern void func_00115AC0(void *, int, int);
extern char D_001AE220[];
extern char D_001ADBC8[];
extern float D_001AE218 __attribute__((sda));
extern float D_001AE21C;

void func_US2_00344558(char *object)
{
    char buffer[256];
    float *position;
    func_00335E68((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x2C4)) {
    case 0:
        func_00115DA8(buffer, D_001AE220, func_00288FB8(0x2BE7), func_00288FB8(0x2BEB));
        break;
    case 2:
        func_00115DA8(buffer, D_001AE220, func_00288FB8(0x2BEA), func_00288FB8(0x2BEB));
        break;
    case 1:
        func_00115DA8(buffer, D_001AE220, func_00288FB8(0x2BE8), func_00288FB8(0x2BEB));
        break;
    }
    if (func_001157AC(buffer) >= 49)
        func_00115DA8(object + 0x120, D_001ADBC8, func_00288FB8(0));
    else
        func_00115AC0(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x2B8);
    func_00335E38(object + 0x1B0, D_001AE218 + position[0], D_001AE21C + position[1], 0.0f, 0.0f);
}
