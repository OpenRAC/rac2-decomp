#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x80]; float x, y; } PositionBase;
extern PositionBase D_00189E20 __attribute__((nosda));
extern char D_00189EA0[] __attribute__((nosda));
extern float D_L00_001B0788 __attribute__((sda));
extern float D_L00_001B078C __attribute__((sda));
extern float D_L00_001B0790 __attribute__((sda));
extern float D_L00_001B07B8 __attribute__((sda));
extern float D_L00_001B07BC __attribute__((sda));
extern float D_L00_001B07C0 __attribute__((sda));
extern float D_L00_001B07C4 __attribute__((sda));
extern float D_L00_001B07C8 __attribute__((sda));
extern void ref_L00_003EBC68_00(void *, void *, void *);
extern float ref_L00_003EBC68_01(void *, void *);
extern void ref_L00_003EBC68_02(void *, void *, void *, float, float, float);
extern void ref_L00_003EBC68_03(void *, void *, float);
extern void ref_L00_003EBC68_04(void *, void *, void *);
extern void ref_L00_003EBC68_05(void *, void *, float);
extern int ref_L00_003EBC68_06(void *, void *, int, float, float, float);
extern float ref_L00_003EBC68_07(void *);
extern float ref_L00_003EBC68_08(float, float);
extern float ref_L00_003EBC68_09(float);
extern float ref_L00_003EBC68_10(float);
extern float ref_L00_003EBC68_11(float, float);
extern void ref_L00_003EBC68_12(void *, void *, void *, float, float, float);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003EFF80);

