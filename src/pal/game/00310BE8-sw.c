#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[0x14];
    u8 *target;
    f32 f18;
    f32 f1C;
    f32 f20;
} FollowVars;
extern char D_00189E20[];
extern u32 D_00138320;
extern unsigned int func_PAL_0026F580(int);
extern unsigned int func_PAL_0026F5B8(int, int);
extern void func_0026F770(int, int, float);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_0027CDC8(void (*)(char *), char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern s32 func_PAL_00311D98(s32 arg0, f32 fparg0);
extern void func_0030F408(char *);


