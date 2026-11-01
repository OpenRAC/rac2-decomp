#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_00409AC8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_00409B48);


#include "common.h"
extern int func_L01_00321178(char *, char *);
extern int func_002B4FF0(char *, float *, float);
extern s32 func_325E78(char *a0, s32 a1);
extern f32 func_2EA578(char *a0, char *a1);
extern f32 func_2EA3E0(f32 x);

void func_PAL_L09_00409F00(char *a0, char *a1, s32 a2) {
    char *p = *(char **)(a0 + 0x68);
    if (a2 == 0) {
        func_L01_00321178(a0, a1);
    } else {
        func_002B4FF0(a0, (float *)a1, *(f32 *)(p + 0x33C));
    }
}

extern void func_00282978(char *p);
extern void func_002AEC48(char *a0, char *a1, s32 a2, f32 f12, f32 f13);
extern void func_PAL_002B14F8(char *a0, char *a1, s32 a2, s32 a3, f32 f12);
extern s32 func_002A8508(s32 a0, s32 a1);

void func_PAL_L09_00409F38(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    u16 n;
    func_00282978(s1 + 0x330);
    func_00282978(s1 + 0x332);
    n = *(u16 *)(a0 + 0x96);
    if (n < 0xFFFF) {
        *(u16 *)(a0 + 0x96) = n + 1;
    }
    func_002AEC48(a0, s1 + 0x280, 0, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(a0, s1 + 0x360, 0, 1, 1.5f);
}

