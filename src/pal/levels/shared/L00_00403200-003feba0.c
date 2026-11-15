#include "include_asm.h"
#include "names.h"

extern int math_random_int_below(int);
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern void vec_random_direction(char *,float,float);
extern char *func_PAL_002BE9A8(float,float,float,float,char *,int,char *,unsigned int,int);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Spawn six sparks along a segment centred on pos and running along direction. */
void func_PAL_L00_00403480(void *unused, void *pos, void *direction)
{
    float out[4], scaled[4], local[4];
    float length = FastVecLength(direction);
    float speed;
    int i;
    unsigned int shade, packed, color;
    unsigned int alpha;
    char *spark;

    if (length == 0.0f)
        return;

    {
        float inverse;

        inverse = 1.0f / length;
        FastVecScale(scaled, direction, inverse * 0.5f);
    }
    FastVecAdd(out, pos, scaled);

    alpha = 0x7f000000U;
    for (i = 5; i >= 0; i--) {
        math_random_int_below(2);
        math_random_int_below(2);
        speed = math_random_float_range(70000.0f, 150000.0f);
        shade = math_random_int_range(10, 127);
        packed = (shade << 8) | alpha;
        color = (shade << 16) | packed;
        shade = color | shade;
        vec_random_direction((char *)local, 2.0000003e-05f, 0.008f);
        spark = func_PAL_002BE9A8(0.3f, 1.0f, 1.01f, speed, (char *)out, 0, (char *)local, shade, 1);
        if (spark != 0) {
            char *ext = spark + 32;

            *(short *)(spark + 10) = 100;
            *(int *)(ext + 4) = 2;
            ext[10] = 127;
            ext[11] = *(unsigned char *)(spark + 10);
        }
    }
}
