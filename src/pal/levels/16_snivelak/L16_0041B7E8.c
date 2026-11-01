#include "include_asm.h"


typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, f32);
extern void func_PAL_0032F3B8(char *, char *, char *, f32);
extern void func_002E5CF8(s32, s32, char *);
extern f32 func_00282C48(f32);
extern f32 func_002A78D8(f32, f32);
extern f32 func_002A7878(f32, f32);
extern void func_PAL_002735D0(char *, s32, s32, s32, char *, char *, char *, s32, f32, f32);
extern void func_002A7A00(char *, f32, f32);
extern char D_001B9B00[];
extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern s32 func_002829D8(char *);
extern void func_00282CF0(char *, char *, char *);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern s32 func_002E8648(f32);

/* lays the object's ten measurement points out along a ring and asks the engine to arm them */
void func_PAL_L16_0041BF40(char *arg0) {
    char buf0[0x10];
    char buf1[0x10];
    f32 f20;
    f32 f30;
    s16 h;
    s32 i;

    func_00282CF0(buf0, D_001B9B00, arg0 + 0x10);
    func_00282F20(buf0, buf0, 1.0f);
    func_PAL_0032F3B8(arg0, arg0 + 0x10, buf0, 0.0f);
    func_002E5CF8(0, 0, arg0);
    for (i = 0; i < 5; i++) {
        func_002A7A00(buf1, 0.10000001f, 0.3f);
        *(f32 *)(buf1 + 8) = func_00282C48(*(f32 *)(buf1 + 8));
        h = *(s16 *)(arg0 + 0xAA);
        f20 = func_002A78D8(90.0f, 180.0f);
        f30 = func_002A7878(10.0f, 20.0f);
        func_PAL_002735D0(arg0, 2, h, i, arg0 + 0x10, arg0 + 0xF0, buf1, 0xFF, f20, f30);
    }
}

