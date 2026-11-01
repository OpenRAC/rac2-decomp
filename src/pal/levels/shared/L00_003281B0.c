#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003281B0);

#include "common.h"
extern u8 D_00189EA0[];
extern u32 D_001A79F0 MACRO_ADDR;
extern s32 D_002A0D50[];
extern f32 func_00282E48(u8 *, u8 *);
extern void func_PAL_L00_00323918(u8 *, s32, s32, s32, s32, s32, f32);

void func_PAL_L00_003281C0(u8 *a0, s32 a1, f32 f12) {
    s32 mode = 1;
    u32 i;
    s32 v;

    if (func_00282E48(a0 + 0x10, D_00189EA0) < 7.0f)
        mode = 3;
    i = D_001A79F0;
    if (i > 25)
        i = 25;
    v = D_002A0D50[i] * a1 - 1;
    func_PAL_L00_00323918(a0, v, v, mode, -1, 0, f12);
}


extern void func_0029CC50(void);

void func_PAL_L00_003282B0(void)
{
    func_0029CC50();
}

typedef int TI __attribute__((mode(TI)));
typedef union { TI q; float f[4]; } Vector;
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern char *func_PAL_002735D0(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_PAL_L00_0039E608(char *);
extern void func_002A0488(char *, unsigned long, unsigned long, unsigned long);

/* Spawn count effects around origin, tinted by color (0xAABBGGRR). */
void func_PAL_L00_00328480(char *owner, void *origin, int count, int mode,
                       void *velocity_origin, int color, Vector *fixed_rotation,
                       float radius, float speed, float low_scale, float high_scale)
{
    Vector velocity, position, rotation, random_rotation;
    char *effect, *payload;
    int kind, variant;
    int r, g, b, t;
    u32 packed;
    int i;
    float life;
    for (i = 0; i < count; i++) {
        func_002A7A00(&velocity, 0.0f, speed * 0.020000001f);
        func_00282CC0(&velocity, &velocity, velocity_origin);
        func_002A7A00(&position, 0.0f, radius);
        func_00282CC0(&position, &position, origin);
        random_rotation.q = 0;
        random_rotation.f[0] = func_002A7940();
        random_rotation.f[2] = func_002A7940();
        rotation.q = random_rotation.q;
        if (fixed_rotation != 0)
            qcopy(&rotation, fixed_rotation);
        kind = mode ? 2 : 1;
        variant = func_002A77E0(4);
        life = func_002A7878(10.0f, 20.0f);
        effect = func_PAL_002735D0(owner, kind, 0x43e, variant, &position, &rotation, &velocity,
                               0xff, 180.0f, life);
        if (effect != 0) {
            *(void (**)(char *))(effect + 0x64) = func_PAL_L00_0039E608;
            r = color & 0xff;
            t = (unsigned int)color >> 24;
            *(float *)(effect + 0x2c) = *(float *)(*(char **)(effect + 0x24) + 0x24)
                                        * func_002A7878(low_scale, high_scale);
            b = (color >> 16) & 0xff;
            g = (color >> 8) & 0xff;
            payload = *(char **)(effect + 0x68);
            func_002A0488(effect, r, g, b);
            ((unsigned char *)effect)[0x23] = t;
            if (r != g || r != b)
                t = 1;
            else
                t = 0;
            packed = t << 24;
            packed |= b << 16;
            packed |= g << 8;
            packed |= r;
            *(u32 *)(payload + 0x50) = packed;
        }
    }
}

