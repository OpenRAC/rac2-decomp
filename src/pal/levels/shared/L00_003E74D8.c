#include "include_asm.h"

#include "common.h"
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int);
extern int FloatToInt(float value);
extern char D_0018A0E0[];
extern unsigned char *D_L00_001FEA14;
extern char g_camera_l00_position[];
extern char D_L00_001A8F20_1[] __attribute__((sda));
extern void FastVecSub(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int math_random_int_below(int);
extern char *func_PAL_002BE9A8(float *, float, float, int, float *, float, float, unsigned, int);
extern char *func_PAL_002C23B8(float *, float *, int, int, unsigned, int, float, float, float, float, float);
extern char g_camera_l00_position[];
extern void FastVecSub(char *dst, char *src, char *arg);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
#include "common.h"

/* Emit twenty paired particles around a position, optionally adding two final flashes. */
void func_PAL_L00_003E74D8(float *pos, int unused, int extra)
{
    float v[4], dir[4], out[4];
    float angle, speed, scale, mag, direction;
    int id, i, n;
    char *p, *d;
    FastVecSub((char *)v, g_camera_l00_position, (char *)pos);
    angle = mat_fast_helper_a(v[0], v[1]);
    for (i = 19; i >= 0; i--) {
        FastVecScale(dir, D_0018A0E0, -(math_random_float_range(0.2f, 3.0f) * 0.020000001f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        speed = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        out[0] = pos[0] + math_random_signed_float_range(0.0f, 0.2f);
        out[1] = pos[1] + math_random_signed_float_range(0.0f, 0.2f);
        out[2] = pos[2] + math_random_signed_float_range(0.0f, 0.2f);
        p = func_PAL_002BE9A8(out, 0.0f, 1.0f, id, dir, 1.01f, speed, 0x7F202020, 1);
        if (p) {
            p[3] = 68;
            *(short *)(p + 10) = 75;
            d = p + 32;
            p[9] = FloatToInt(4.0f) + 64;
            *(float *)(d + 28) = IntToFloat(4);
            *(int *)(d + 4) = 3;
            d[10] = 48;
            d[11] = p[10];
        }
        scale = math_random_float_range(1.0f, 2.0f);
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        direction = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, direction, mag);
        out[0] = pos[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = pos[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = pos[2] + math_random_signed_float_range(0.0f, 0.1f);
        func_PAL_002C23B8(out, dir, 25, 127, 0x7F7F7F, id,
            math_random_float_range(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
    if (extra == 1) {
        char *last;
        speed = 525000.0f;
        n = math_random_int_below(255);
        last = func_PAL_002C23B8(pos, (float *)D_L00_001A8F20_1, 4, 127, 0x207080, n, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
        last = func_PAL_002C23B8(pos, (float *)D_L00_001A8F20_1, 4, 127, 0x207080, (n + 128) & 255, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
    }
}


