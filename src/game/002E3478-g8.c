/* func_002E3478 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections). */
#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

extern float *D_001B1990;
extern int D_001B20F0[] __attribute__((sda));
extern float ref_L00_00261DD0_00[];
extern float func_00283B98(float a, float b);
extern void func_00283430(int *a, float *b);

/* Blends the rotation of one view toward its target and passes it on as a transform. */
void func_002E3478(int viewIndex)
{
    float buf[3];

    ((float *)ref_L00_00261DD0_00)[viewIndex * 3] =
        FastAddRotations(((float *)ref_L00_00261DD0_00)[viewIndex * 3], D_001B1990[viewIndex * 3]);
    ((float *)((char *)ref_L00_00261DD0_00 + 4))[viewIndex * 3] =
        FastAddRotations(((float *)((char *)ref_L00_00261DD0_00 + 4))[viewIndex * 3], D_001B1990[viewIndex * 3 + 1]);
    ((float *)((char *)ref_L00_00261DD0_00 + 8))[viewIndex * 3] =
        FastAddRotations(((float *)((char *)ref_L00_00261DD0_00 + 8))[viewIndex * 3], D_001B1990[viewIndex * 3 + 2]);
    buf[0] = ((float *)ref_L00_00261DD0_00)[viewIndex * 3];
    buf[1] = ((float *)((char *)ref_L00_00261DD0_00 + 4))[viewIndex * 3];
    buf[2] = ((float *)((char *)ref_L00_00261DD0_00 + 8))[viewIndex * 3];
    FastMatrixHelperB(D_001B20F0, buf);
}
