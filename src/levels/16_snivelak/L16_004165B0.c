#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

/* func_L16_004165B0 is defined in L16_004165B0-fx-g8.c. */

extern void func_002E74B8(char *, char *, char *);
extern void func_002E7788(char *, char *, f32);
extern void func_003E9FF0(char *, char *, char *, f32);
extern void func_00357288(s32, s32, char *);
extern f32 func_002E73F8(f32);
extern f32 func_00313F98(f32, f32);
extern f32 func_00313F38(f32, f32);
extern void func_002D4CC8(char *, s32, s32, s32, char *, char *, char *, s32, f32, f32);
extern void func_003140C0(char *, f32, f32);
extern char D_001B9B00[];

/* lays the object's ten measurement points out along a ring and asks the engine to arm them */
void func_L16_00416D08(char *arg0) {
    char buf0[0x10];
    char buf1[0x10];
    f32 f20;
    f32 f30;
    s16 h;
    s32 i;

    func_002E74B8(buf0, D_001B9B00, arg0 + 0x10);
    func_002E7788(buf0, buf0, 1.0f);
    func_003E9FF0(arg0, arg0 + 0x10, buf0, 0.0f);
    func_00357288(0, 0, arg0);
    for (i = 0; i < 5; i++) {
        func_003140C0(buf1, 0.0833333358168602f, 0.25f);
        *(f32 *)(buf1 + 8) = func_002E73F8(*(f32 *)(buf1 + 8));
        h = *(s16 *)(arg0 + 0xAA);
        f20 = func_00313F98(90.0f, 180.0f);
        f30 = func_00313F38(10.0f, 20.0f);
        func_002D4CC8(arg0, 2, h, i, arg0 + 0x10, arg0 + 0xF0, buf1, 0xFF, f20, f30);
    }
}

/* the horizontal speed the object carries in its data block */
f32 func_L16_00416EB8(char *arg0) {
    return *(f32 *)(*(char **)(arg0 + 0x68) + 0x78);
}

/* func_L16_00416EC8 uses its dedicated quadword-copy and G16 profile. */

INCLUDE_ASM("asm/levels", func_L16_00416FB0);

/* func_L16_00417210 is defined in L16_00417210-g8.c. */

/* the model index the object's data block points at */
s32 func_L16_00417788(char *arg0) {
    char *p = *(char **)(arg0 + 0x68);
    return *(s32 *)(p + 0x60);
}

INCLUDE_ASM("asm/levels", func_L16_00417798);

/* func_L16_00417990 is defined in L16_00417990-g8.c. */

/* func_L16_00417DB0 is defined in L16_00417DB0.c. */



/* func_L16_004189A0 is defined in L16_004189A0.c. */

INCLUDE_ASM("asm/levels", func_L16_00418E38);

/* func_L16_00419140 is defined in L16_00419140-g8.c. */


extern char D_00189E20[];
extern void func_00315728(char *, char *, s32, char *, f32);
extern void func_00315948(char *, char *);

extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern s32 func_002829D8(char *);
extern void func_L16_0041C948(char *);
extern void func_002A7750(char *, s32, s32);

/* Controls the timed rotation cycle and restores the original settings. */
void func_L16_0041C7A0(char *self) {
    char *st = *(char **)(self + 0x68);
    f32 a, b, angle;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(s32 *)(st + 0) = 0;
        *(s32 *)(st + 4) = 0;
        *(s32 *)(st + 8) = 0;
        *(s32 *)(st + 12) = 0;
        *(s32 *)(st + 16) = 0;
        a = *(f32 *)(st + 20);
        angle = *(f32 *)(self + 0xF0);
        b = *(f32 *)(st + 24);
        *(f32 *)(st + 40) = angle;
        *(s32 *)(st + 36) = *(u8 *)(self + 0xBC);
        *(f32 *)(st + 32) = b;
        *(f32 *)(st + 28) = a;
        func_002A7750(self, 1, -1);
        break;
    case 1:
        if (*(u8 *)(self + 0xBC))
            func_002A7750(self, 4, -1);
        break;
    case 4:
        if (*(s32 *)(st + 16) < 180) {
            *(f32 *)(self + 0xF0) = func_00283B98(*(f32 *)(self + 0xF0), 0.0872664749622345f);
            *(s32 *)(st + 16) += 5;
        } else func_002A7750(self, 2, -1);
        break;
    case 2:
        if (func_002829D8(st + 20)) func_002A7750(self, 3, -1);
        break;
    case 3:
        if (func_002829D8(st + 24)) func_002A7750(self, 5, -1);
        func_L16_0041C948(self);
        break;
    case 5:
        if (*(s32 *)(st + 16) > 0) {
            *(f32 *)(self + 0xF0) = func_00283BE0(*(f32 *)(self + 0xF0), 0.0872664749622345f);
            *(s32 *)(st + 16) -= 5;
        } else {
            *(u8 *)(self + 0xBC) = *(u8 *)(st + 36);
            *(f32 *)(st + 20) = *(f32 *)(st + 28);
            *(f32 *)(st + 24) = *(f32 *)(st + 32);
            a = *(f32 *)(st + 40);
            *(f32 *)(self + 0xF0) = a;
            func_002A7750(self, 1, -1);
        }
        break;
    }
}


INCLUDE_ASM("asm/levels", func_L16_0041C990);


INCLUDE_ASM("asm/levels", func_L16_0041CF80);

/* func_L16_0041E370 lives in L16_0041E370.c. */


/* func_L16_0041ECF8 lives in L16_004165B0-g8.c (it takes the address of a $gp global). */

/* func_L16_0041EE90 is defined in L16_0041EE90-g8.c. */

extern void func_002E74B8(char *, char *, char *);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern s32 func_002E8648(f32);

/* spawns the level's score pickup effect for this object */
void func_L16_0041F150(char *arg0) {
    char buf[0x10];
    char *st = *(char **)(arg0 + 0x68);
    char *obj;
    s32 handle;
    s32 a;

    func_002E74B8(buf, arg0 + 0x10, st);
    handle = func_00313EE0(3, 7) & 0xFF;
    a = func_00313EA0(0xFF) & 0xFF;
    obj = (char *)func_003320E0(buf, st, 0x60006080, handle, 2.5f, a, 0);
    if (obj == 0)
        return;
    obj[9] = (u8)(func_002E8648(4.0f) - 16);
}

/* func_L16_0041F1F0 lives in L16_0041F1F0.c. */

/* func_L16_0041F360 is defined in L16_0041F360-g8.c. */


