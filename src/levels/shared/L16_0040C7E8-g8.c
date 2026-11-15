#include "include_asm.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

/* Retail index arithmetic establishes the 256/128-byte pool strides and
   the position offsets. The remaining bytes retain their real storage. */
typedef struct { char prefix[0x10]; Quad position; char rest[0xE0]; } ObjectPoolRecord256;
extern ObjectPoolRecord256 *D_L16_001B2B1C __attribute__((sda));
typedef struct { char prefix[0x30]; Quad position; char rest[0x40]; } PointPoolRecord128;
extern PointPoolRecord128 *D_L16_001B2C0C __attribute__((nosda));
typedef struct { int pointIndex; int objectIndex; } PositionChoice;
/* Looks up the position of the launch target, either a point or an object, and copies it out. */
void func_L16_0040C7E8(char *object, Vector *destination) {
    PositionChoice *choice=*(PositionChoice **)(object+0x68);
    int index=choice->objectIndex;
    if (index==-1)
        destination->q=D_L16_001B2C0C[choice->pointIndex].position;
    else
        destination->q=D_L16_001B2B1C[index].position;
}
