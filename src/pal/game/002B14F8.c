#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern u8 D_00139648;
extern u8 D_001A7A47 __attribute__((sda));
extern void moby_update_eased_node(void *a0, void *a1, int a2, float f12, float f13);
extern u8 g_item_slot_to_record[];
extern u8 g_weapon_table[];
extern u8 D_001A7A60[] __attribute__((sda));

/* Stores the third argument (or 1.0f) in the object's float at 0x70, and, when the fifth argument
   is set and that float differs from the one at 0x20, calls func_002AEC48 with the object's two
   first arguments, the fourth argument and the pair 0.03f, 0.3f. */
void func_PAL_002B14F8(void *a0, float *a1, float f12, int a2, int a3)
{
    if (D_001A7A47 != 0) {
        a1[28] = f12;
    } else {
        a1[28] = 1.0f;
    }
    if (a3 != 0) {
        if (a1[28] != a1[8]) {
            moby_update_eased_node(a0, a1, a2, 0.0432f, 0.43200004f);
        }
    }
}


void func_PAL_002B1588(int first, int second)
{
    extern int GetLocalizedString(int);
    extern void func_0029CC98(int, int);
    func_0029CC98(GetLocalizedString(first), second);
}

extern void func_0029CC50(int, int, int);

void func_PAL_002B15B8(int first, int second, int third) {
    func_0029CC50(first, second, third);
}

extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(float *dst, float *src, char *table);
extern void FastVecAdd(float *dst, float *src, float *arg);
extern int D_L00_001A8FF0_1 __attribute__((sda));
extern void func_PAL_002735D0(char *self, int a1, int a2, int a3, char *p4, char *p5,
                    float *buf, int b3, float fa, float fb);

/* Walks selected mask bits, evaluates three stored curve components, optionally transforms the vector, and dispatches one object operation per selected bit. */
void func_PAL_002B15D8(char *self, int mask, float *arg2,
                                        unsigned char arg3,
                                        float f0, float f1, float f2, float f3)
{
    /* Vector primitives read/write all 16 bytes; retail initializes only xyz. */
    float buf[4] __attribute__((aligned(16)));
    float v;
    float k;
    float fa;
    float fb;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        v = math_random_angle();
        k = math_random_float_range(f0, f1) * (0.020000001f);
        buf[0] = math_fast_sin_or_cos_a(v) * k;
        buf[1] = math_fast_sin_or_cos_b(v) * k;
        buf[2] = 0.0f;
        buf[2] = math_random_float_range(f2, f3) * (0.020000001f);
        if (D_L00_001A8FF0_1 != 0)
            matrix_mul_vec3(buf, buf, self + 192);
        FastVecAdd(buf, buf, arg2);
        fa = math_random_float_range(90.0f, 270.0f);
        fb = math_random_float_range(10.0f, 20.0f);
        func_PAL_002735D0(self, 2, *(short *)(self + 170), i, self + 16, self + 240,
                buf, arg3, fa, fb);
    }
}

