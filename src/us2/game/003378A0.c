#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned long u64;

extern int func_00336A40(void *);
extern u64 func_US2_0027CED8(int);
extern void func_US2_0027FCB0(float, float, u64, u8 *, int, float, u64, u8 *);
extern float func_US2_002804C0(u8 *, int, int, float);
extern void func_0027F110(void);
extern void func_0027F120(void);

/* func_US2_003378A0, the USA v2.00 copy of func_00336A78: the same C with a new start, which sets
   the mode word func_0027F110/func_0027F120 write from +0x54, and with +0x48 set stores the
   fitted scale of func_US2_002804C0 and turns it into a vertical offset for the text. */
void func_US2_003378A0(char *o)
{
    float x;
    float y;
    float offset;
    int width;
    u64 texture;
    int color;
    float *scale;

    if (*(int *)(o + 0x54) != 0) {
        func_0027F110();
    } else {
        func_0027F120();
    }
    offset = 0.0f;
    if (*(int *)(o + 0x48) != 0) {
        **(float **)(o + 4) = func_US2_002804C0(*(u8 **)(o + 0x40), -1, *(int *)(o + 0x4C), *(float *)(o + 0x50));
        offset = 3.0f - (**(float **)(o + 4) - *(float *)(o + 0x50)) * 10.0f;
    }
    if (*(float *)(*(char **)(o + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(o + 64) == 0) {
        return;
    }
    width = func_00336A40(o);
    x = *(float *)(*(char **)(o));
    switch (*(int *)(o + 68)) {
    case 0:
        break;
    case 1:
        x = x - (float)(width >> 1);
        break;
    case 2:
        x = x - (float)width;
        break;
    }
    y = *(float *)(*(char **)(o) + 4) + offset;
    color = *(int *)(*(char **)(o + 12));
    scale = *(float **)(o + 4);
    texture = func_US2_0027CED8(*(int *)(o + 56));
    func_US2_0027FCB0(x, y, color, *(u8 **)(o + 64), width, *scale, texture, *(u8 **)(o + 52));
}

INCLUDE_ASM("asm/us2/game", func_US2_00337A38);
