#include "include_asm.h"

#include "common.h"
extern int FloatToInt(float f);
extern int FastTweenColor(int a, int b, float f);
extern float math_random_float_range(float a, float b);
extern char *part_alloc(int kind);
extern int math_random_int_below(int a);
extern int math_random_int_range(int a, int b);
extern char *g_object_particle_byte;

/* Create a type-0x6D object with two vector records and a packed identifier. */
char *func_PAL_L00_003436B0(char *a0, char *a1, int a2, float f)
{
    char *s1 = part_alloc(0x6D);
    char *s0;
    float f2;

    if (s1) {
        qcopy(s1 + 0x10, a0);
        s0 = s1 + 0x20;
        {
            int value = FloatToInt(4.0f) + 0x40;
            *(unsigned char *)(s1 + 3) = a2;
            *(unsigned char *)(s1 + 1) = 0;
            *(unsigned char *)(s1 + 9) = value;
        }
        *(unsigned char *)(s1 + 8) = math_random_int_below(0xFF);
        *(unsigned char *)(s1 + 2) = *(unsigned char *)g_object_particle_byte;
        *(unsigned short *)(s1 + 0xA) = ((s32)(math_random_int_range(5, 0x32)) * 5 + 2) / 6;
        qcopy(s0, a1);
        *(float *)(s1 + 0xC) = f * 525000.0f;
        *(unsigned int *)(s0 + 0x10) = math_random_int_range(0x40, 0x80);
        f2 = math_random_float_range(0.0f, 0.5f);
        *(unsigned int *)(s1 + 4) = FastTweenColor(0x103080, 0, f2) |
                                    (*(unsigned int *)(s0 + 0x10) << 24);
    }
    return s1;
}
