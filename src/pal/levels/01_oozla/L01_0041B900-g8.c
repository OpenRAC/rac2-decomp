#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x60 - 0x1C];
    f32 f60;
    f32 f64;
    f32 f68;
} State_397870;
typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Class_397870;
typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    u8 b20;
    u8 pad2[0x24 - 0x21];
    Class_397870 *cls;
    u8 pad3[0x2C - 0x28];
    f32 f2C;
    u8 pad4[0x68 - 0x30];
    State_397870 *st;
    u8 pad5[0xF0 - 0x6C];
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
} Obj_397870;
extern void func_PAL_L01_0041C560(Obj_397870 *a0);
extern float D_L01_001AF50C __attribute__((sda));
extern float D_L01_001AF510 __attribute__((sda));
extern float D_L01_001AF514 __attribute__((sda));
extern float D_L01_001AF528 __attribute__((sda));
extern int D_L01_001AF54C __attribute__((sda));
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_002A77E0(int);
extern void func_PAL_L01_0041C0D8(Obj_397870 *);

INCLUDE_ASM("asm/pal/levels", func_PAL_L01_0041BF10);

