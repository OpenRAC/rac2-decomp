#include "include_asm.h"




#include "common.h"
extern void FastVecSub(char *local, char *first, char *second);
extern float mat_fast_helper_a(float a, float b);
extern void FastVecScale(char *dst, char *src, float scale);
extern float math_random_float_range(float a, float b);
extern float math_random_signed_float_range(float a, float b);
extern int FloatToInt(float f);
extern float IntToFloat(int v);
extern float FastAddRotations(float a, float b);
extern void vec_build_spherical_offset(float *p, float a, float b, float c);
extern char *func_PAL_002BE9A8(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);
extern void func_PAL_002C23B8(float *out, float *dir, int a, int b, unsigned int color, int id,
                           float fa, float fb, float fc, float fd, float fe);
extern char D_L20_001B9FC0[];
extern char D_0018A0E0[];

void func_PAL_L20_0039F810(float *p)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float scale;
    float mag;
    float angle;
    float f;
    int id;
    int i;
    char *r;
    char *q;

    FastVecSub((char *)v, D_L20_001B9FC0, (char *)p);
    ang = mat_fast_helper_a(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        f = math_random_float_range(0.2f, 3.0f);
        FastVecScale((char *)dir, D_0018A0E0, -(f * 0.020000001f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        f = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        out[0] = p[0] + math_random_signed_float_range(0.0f, 0.2f);
        out[1] = p[1] + math_random_signed_float_range(0.0f, 0.2f);
        out[2] = p[2] + math_random_signed_float_range(0.0f, 0.2f);
        r = func_PAL_002BE9A8((char *)out, 0.0f, 1.0f, 1.01f, f, id, (char *)dir, 0x7F202020, 0);
        if (r != 0) {
            q = r + 32;
            *(unsigned char *)(r + 3) = 0x44;
            *(short *)(r + 10) = 0x4B;
            *(unsigned char *)(r + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(q + 0x1C) = IntToFloat(4);
            *(int *)(q + 4) = 3;
            *(unsigned char *)(q + 0xA) = 0x30;
            *(unsigned char *)(q + 0xB) = *(unsigned char *)(r + 10);
        }
        scale = math_random_float_range(1.0f, 2.0f);
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, mag);
        out[0] = p[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = p[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = p[2] + math_random_signed_float_range(0.0f, 0.1f);
        func_PAL_002C23B8(out, dir, 25, 127, 0x007F7F7F, id,
                      math_random_float_range(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}

