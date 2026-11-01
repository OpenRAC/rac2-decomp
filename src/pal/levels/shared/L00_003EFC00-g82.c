#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float func_002A7878(float low, float high);
extern void func_0029FCC0(char *object, int joint, void *out);
extern void func_L00_0033C0D0(char *object, void *position, void *velocity, void *parameters, int mode);
extern char D_L00_001B02E8 __attribute__((sda));
extern char D_L00_001B02F8 __attribute__((sda));
extern char D_L00_001B0308 __attribute__((sda));

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003F0390);

