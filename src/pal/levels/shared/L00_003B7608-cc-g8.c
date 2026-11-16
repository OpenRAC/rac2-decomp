#include "names.h"
/* func_PAL_L00_003B7608, the PAL copy of func_L00_003B3C40: the same C, where rename func_002BDCE8 becomes func_PAL_002BE9A8; scale D_L00_001AF904; wrap D_L00_001AF908 / func_00283CE0(angle) (({e}) * 1.2f). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern char *func_PAL_002BE9A8(char *, float, float, float, float, int, char *, int, int);
extern char g_camera_l00_position[];
extern char g_default_vector[] MACRO_ADDR;
extern float g_spark_burst_speed __attribute__((sda));
extern int g_spark_burst_color __attribute__((sda));
extern int g_spark_burst_angle_count __attribute__((sda));
extern float g_spark_burst_depth __attribute__((sda));
extern float g_spark_second_speed __attribute__((sda));
extern int g_spark_second_color __attribute__((sda));
extern int g_spark_second_alpha __attribute__((sda));

void func_PAL_L00_003B7608(char *object)
{
    union { Quad q; float f[4]; } position;
    float a[4], b[4], c[4], d[4];
    int angle;
    int r;
    float t;
    char *p;
    position.q = 0;
    position.f[2] = g_spark_burst_depth;
    FastVecSub(a, g_camera_l00_position, object + 0x10);
    math_apply_axis_rotation_to_quat(b, &position, a, math_random_angle());
    FastVecAdd(c, object + 0x10, b);
    r = math_random_int_below(0x10);
    if (math_random_int_below(2))
        r = -r;
    angle = (((int)(g_spark_burst_angle_count) * 5 + 2) / 6);
    t = ((g_spark_burst_depth / IntToFloat(angle)) * 1.2f);
    vec_scale_to_length(d, b, -t);
    p = func_PAL_002BE9A8((char *)c, 0.5f, 1.0f, 0.99f, g_spark_burst_speed * 210000.0f, r, (char *)d, g_spark_burst_color, 0);
    if (p) {
        char *s = p + 0x20;
        *(short *)(p + 0xA) = angle;
        *(int *)(s + 4) = 3;
        s[0xA] = 0x7F;
        s[0xB] = *(unsigned char *)(p + 0xA);
    }
    if (math_random_int_below(3) == 0) {
        vec_scale_to_length(a, a, -0.5f);
        FastVecAdd(c, object + 0x10, a);
        p = func_PAL_002BE9A8((char *)c, 0.1f, 1.0f, 0.8f, g_spark_second_speed * 210000.0f, r, g_default_vector, (g_spark_second_color & 0xFFFFFF) | (g_spark_second_alpha << 24), 0);
        if (p) {
            char *s = p + 0x20;
            *(short *)(p + 0xA) = 0x32;
            p[3] = 0x44;
            *(int *)(s + 4) = 3;
            s[0xA] = *(unsigned char *)&g_spark_second_alpha;
            s[0xB] = *(unsigned char *)(p + 0xA);
        }
    }
}
