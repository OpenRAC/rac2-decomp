#include "include_asm.h"

#include "common.h"
typedef int quad __attribute__((mode(TI)));
extern char D_L16_001BFF60[];
extern f32 D_L16_001B1FF0 __attribute__((sda));
extern f32 D_L16_001B1FF4 __attribute__((sda));
extern void func_00282CC0(char *, char *, char *);
extern void func_PAL_L16_00424590(char *);
extern s32 func_002761F8(char *, char *, s32, s32, s32);
extern void func_002A7750(char *, s32, s32);
extern void func_PAL_L00_003FB330(char *, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_002A8C28(char *, char *, f32, f32, u32, s32, s32, s32, f32);
extern s32 func_002B3868(char *);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_0029F338(char *);
extern void func_L16_0041F360(char *);
extern void func_L00_002E6CF0(void (*)(char *), char *);

/* Moves a fragment until impact and runs its fading shock-wave effect. */
void func_PAL_L16_004242D0(char *self) {
    quad previous;
    char *st = *(char **)(self + 0x68);

    switch (*(u8 *)(self + 0x20)) {
    case 0: {
        char *old = (char *)&previous;
        char *position = self + 16;
        qcopy(old,position);
        func_00282CC0(position, position, st);
        *(f32 *)(st + 8) -= *(f32 *)(st + 0x24);
        func_PAL_L16_00424590(self);
        if (func_002761F8(old, position, 0, *(s32 *)(self + 0xB8), 0)) {
            qcopy(position ,D_L16_001BFF60);
            if (*(s32 *)(st + 0x20)) func_002A7750(self, 2, -1);
            else func_002A7750(self, 1, -1);
        }
        break;
    }
    case 1: {
        char *position = self + 16;
        func_PAL_L00_003FB330(position, 1.0f, 20.0f, 0, 25, 20, 20, 20, 45, 1, 1, 0, 0, 0);
        func_002A8C28(self, position, 2.0f, 6.0f, 0x10001, 0, 1, 0, 1.0f);
        func_0029F338(self);
        break;
    }
    case 2:
        if (func_002B3868(self)) {
            func_PAL_L00_003FB330(self + 16, 0.6660000085830688f, 20.0f, 0, 20, 15, 15, 15, 35, 1, 1, 0, 0, 0);
            *(s32 *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            *(f32 *)(self + 0x18) += 0.5f;
            *(f32 *)(st + 0x30) = 1.0f;
        }
        *(f32 *)(st + 0x34) += 0.080000006f;
        if (*(f32 *)(st + 0x34) > 1.0f) *(f32 *)(st + 0x34) -= 1.0f;
        { f32 radius = *(f32 *)(st + 0x2C);
          f32 growth = D_L16_001B1FF0 * 0.020000001f;
          f32 limit = D_L16_001B1FF4;
          radius += growth;
          *(f32 *)(st + 0x2C) = radius;
        if (radius >= limit) func_002AA2E8((f32 *)(st + 0x30), 0.0f, 0.080000006f);
        }
        if (*(f32 *)(st + 0x30) <= 0.0f) func_0029F338(self);
        else func_L00_002E6CF0(func_L16_0041F360, self);
        break;
    }
}
