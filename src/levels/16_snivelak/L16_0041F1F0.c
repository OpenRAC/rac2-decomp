#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern char *func_0029EFD0(s32);
extern void func_002B37E8(char *, s32);
extern void func_002A7A00(char *, f32, f32);
extern void func_002833F0(char *, char *);
extern f32 func_002A78D8(f32, f32);
extern void func_002ACE78(char *, char *, f32);
extern void func_002AEC18(char *, u32);
extern void func_002A7750(char *, s32, s32);
typedef int quad __attribute__((mode(TI)));

/* Creates a spinning fragment and initializes its lifetime and velocity. */
char *func_L16_0041F1F0(s32 owner, char *position, char *velocity, s32 kind, f32 speed, f32 life) {
    char *obj = CreateMoby(0x12BE);
    char *st;
    if (obj) {
        InitChildObjectFromParent(obj, owner);
        *(quad *)(obj + 0x10) = *(quad *)position;
        RandomDirectionVector(obj + 0xF0, -3.141592741012573f, 3.141592741012573f);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        st = *(char **)(obj + 0x68);
        *(u16 *)(obj + 0x34) |= 0x100;
        RandomDirectionVector(st + 0x10, 1.0f, 1.0f);
        SetDirectionWithComplement(st + 0x10, st + 0x10, RandomSignedFloatRange(180.0f, 360.0f) * 0.01745329424738884f);
        *(quad *)st = *(quad *)velocity;
        *(f32 *)(st + 0x24) = speed;
        *(s32 *)(st + 0x20) = kind;
        *(f32 *)(st + 0x28) = life;
        *(f32 *)(obj + 0x2C) = *(f32 *)(*(char **)(obj + 0x24) + 0x24) * 0.2f;
        SetMobyLightColor(obj, 0x800000C0);
        SetMobyState(obj, 0, -1);
    }
    return obj;
}
