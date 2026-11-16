#include "include_asm.h"

#include "common.h"
extern s32 math_random_int_below(int a);
extern float math_random_float_range(float a, float b);
extern unsigned int math_random_int_range(int a, int b);
extern void vec_random_direction(char *p, float a, float b);
extern char *part_spawn_spinning_spark_pal(float fa, float fb, float fc, float fd, char *p, int z,
                     char *direction, unsigned int color, int one);

/* Runs 20 direction iterations; the first two calls each pass integer 2 to the same bound target; on each non-null final result, stores a short at +10, an int at +36, and bytes at +42 and +43. */
void part_l00_spawn_spark_shower_pal(char *unused, char *origin)
{
    char direction[16];
    float spark_speed;
    int i;
    unsigned int color;
    unsigned int color_hi;
    unsigned int color_mid;
    char *spark;

    i = 19;
    do {
        math_random_int_below(2);
        i = i - 1;
        math_random_int_below(2);
        spark_speed = math_random_float_range(70000.0f, 1.5e+05f);
        color = math_random_int_range(10, 127);
        color_hi = (color << 8) | 0x7f000000U;
        color_mid = (color << 16) | color_hi;
        color = color_mid | color;
        vec_random_direction(direction, 2.0000003e-05f,
                0.008f);
        spark = part_spawn_spinning_spark_pal(0.3f, 1.0f, 1.01f, spark_speed, origin, 0, direction, color, 1);
        if (spark != 0) {
            char *spark_data = spark + 32;

            *(short *)(spark + 10) = 100;
            *(int *)(spark_data + 4) = 2;
            *(char *)(spark_data + 10) = 127;
            *(char *)(spark_data + 11) = *(unsigned char *)(spark + 10);
        }
    } while (i >= 0);
}
