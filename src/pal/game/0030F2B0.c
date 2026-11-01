#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_0030F2B0);

INCLUDE_ASM("asm/pal/game", func_PAL_0030F460);

#include "common.h"
extern char *func_002A9640(char *, int, int);
extern void func_00282948(int *);
extern void func_002E5CF8(int, int, char *);
extern void func_PAL_002AC290(char *, char *);
extern void func_002ACB48(float *, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_PAL_002AC3C0(char *, char *);

void func_PAL_0030FB38(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit = func_002A9640(object, 0x30001, 0);
    float direction[4];

    func_00282948((int *)(state + 0x28));
    func_00282948((int *)(state + 0x2C));
    if (hit != 0 && (*(int *)(hit + 0x20) != *(int *)(state + 0x34) ||
                     *(int *)(state + 0x28) == 0)) {
        *(int *)(state + 0x34) = *(int *)(hit + 0x20);
        *(int *)(state + 0x28) = 25;
        if (*(int *)(state + 0x2C) == 0) {
            if (*(unsigned short *)(hit + 0x28) == 0x101 && *(int *)(state + 0x30) == 0) {
                *(int *)(state + 0x2C) = 83;
                *(int *)(state + 0x30) = 1;
            } else {
                *(int *)(state + 0x30) = 0;
            }
        }
        func_002E5CF8(0, 0, object);
        *(float *)(state + 0x24) -= *(float *)(hit + 0x2C);
        func_PAL_002AC290(object, state);
        if (*(float *)(state + 0x24) < 0.0f) {
            func_002ACB48(direction, 0.6f);
            func_PAL_002AC718(object, direction, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            object[0x20] = 6;
        }
    }
    ((unsigned char *)object)[0xA8] = 0xFF;
    func_PAL_002AC3C0(object, state);
}


/* func_PAL_0030FCE8 is defined in 0030F2B0-spring.c. */

