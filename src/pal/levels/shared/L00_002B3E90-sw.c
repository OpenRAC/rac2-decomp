#include "include_asm.h"

typedef struct {
    unsigned char prefix[0x40F];
    unsigned char alternate;
    unsigned char gap[0x1EA8];
    unsigned char special;
    unsigned char gap2[0x1FF];
    float speed;
} MovementView;
extern char D_00189E20[];
extern int func_L00_002ADEA0(int index);
extern void func_L00_002B3EF8(int index, float a, float b, float c);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002B3E90);

