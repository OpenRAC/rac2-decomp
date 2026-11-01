#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00390F48);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00391958);


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00392250);

extern int F6eb4f363_FUN_002A77E0(int mode);
extern float F6eb4f363_FUN_002A90F8(char *object, char *local);
extern void F6eb4f363_FUN_00282D30(char *local, int value, float scale);
extern float F6eb4f363_FUN_002A7878(float low, float high);
extern void F6eb4f363_FUN_002BF728(char *object, char *local, float amount, float base);

/* func_00303568 is defined in 00303568.c. */




/* func_00303E20 is defined in 00303E20.c. */

/* func_00304128 is defined in 00304128.c. */

/* func_00304210 is defined in 00304210-g8.c. */

/* func_00304AD0 uses the profile in 00304AD0-g8-qcopy.c. */

void func_PAL_L00_00392500(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (F6eb4f363_FUN_002A77E0(4))
        return;
    base = F6eb4f363_FUN_002A90F8(object + 16, local);
    F6eb4f363_FUN_00282D30(local, value, 0.25f);
    F6eb4f363_FUN_002BF728(object + 16, local, F6eb4f363_FUN_002A7878(0.05f, 0.1f) * 210000.0f, base);
}


extern int func_002A77E0(int mode);
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef float f32;
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;
extern void func_0029F338(NativeUpdate775View *object);
typedef union { TI128 quad; float f[4]; } ParticleUpdateVector;
typedef struct { int color[4]; } ParticleUpdateColors;
extern ParticleUpdateColors D_L00_001AF010;
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002AAFA0(int, int);
extern void func_002BAE50(void *, void *, int, int, int, int, int, int);
extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003253A0(void *, void *, void *, float);
extern float func_00283CE0(int);
extern int func_00282978(short *);

void func_PAL_L00_00392718(char *object)
{
    ParticleUpdateColors colors;
    ParticleUpdateVector direction, random;
    char *state = *(char **)(object + 0x68);
    int enabled = 1;
    if (*(int *)(state + 0x20) != 0)
        if (func_002A77E0(2))
            enabled = 0;
    if ((*(unsigned char *)(object + 0xBC) & 1) && enabled) {
        int color;
        colors = D_L00_001AF010;
        random.quad = 0;
        random.f[0] = func_002A7878(-1.0f, 1.0f);
        random.f[1] = func_002A7878(-1.0f, 1.0f);
        random.f[2] = func_002A7878(-1.0f, 1.0f);
        direction.quad = random.quad;
        func_00282F20(&direction, &direction, 0.020000001f);
        if (*(unsigned char *)(object + 0xBC) & 0xFE) {
            color = func_002AAFA0(colors.color[func_002A77E0(4)],
                                *(unsigned char *)(object + 0xBC) >> 1);
            func_002BAE50(object + 0x10, &direction, color,
                         func_002AAFA0(0x4FFF, *(unsigned char *)(object + 0xBC) >> 1),
                         37, 50, 120, 1);
        } else {
            func_002BAE50(object + 0x10, &direction, colors.color[func_002A77E0(4)],
                         0x4FFF, 37, 50, 120, 1);
        }
    }
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), *(float *)(state + 0x10));
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    func_00282CC0(object + 0x10, object + 0x10, state);
    func_L00_003253A0(object, state, state, 0.00584f);
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f ||
        *(float *)(object + 0x18) < 0.0f) {
        func_0029F338((NativeUpdate775View *)object);
        return;
    }
    if (*(short *)(state + 0x18) < *(short *)(state + 0x1A) / 4) {
        float amount = func_00283CE0(*(short *)(state + 0x18));
        *(float *)(object + 0x2C) = *(float *)(state + 0x1C) * amount /
                                  func_00283CE0(*(short *)(state + 0x1A) / 4);
    }
    if (func_00282978((short *)(state + 0x18)))
        func_0029F338((NativeUpdate775View *)object);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003929E0);
