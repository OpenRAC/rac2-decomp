#include "include_asm.h"


typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
extern void func_00282CF0(char *, char *, char *);
extern f32 func_002E73F8(f32);
extern f32 func_00313F98(f32, f32);
extern f32 func_00313F38(f32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern s32 func_002829D8(char *);
extern void func_00282CF0(char *, char *, char *);
extern s32 func_002A7820(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_002C3150(char *, char *, u32, u32, f32, u32, u32);
extern s32 func_00283CF0(f32);

/* spawns the level's score pickup effect for this object */
void func_PAL_L16_00424590(char *arg0) {
    char buf[0x10];
    char *st = *(char **)(arg0 + 0x68);
    char *obj;
    s32 handle;
    s32 a;

    func_00282CF0(buf, arg0 + 0x10, st);
    handle = ((s32)(func_002A7820(3, 7)) * 5 + 2) / 6 & 0xFF;
    a = func_00313EA0(0xFF) & 0xFF;
    obj = (char *)func_002C3150(buf, st, 0x60006080, handle, 2.5f, a, 0);
    if (obj == 0)
        return;
    obj[9] = (u8)(func_00283CF0(4.0f) - 16);
}

