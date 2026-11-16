#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad bits; float f[4]; } Vector;
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern Quad g_lens_flare_quads[4] SDATA(D_L00_001AECC0);

void func_PAL_L00_00390728(char *object)
{
    Vector colour;
    char *data = *(char **)(object + 0x68);
    float fraction;
    unsigned int r, g, b, c;
    colour.bits = 0;
    colour.f[0] = 128.0f;
    colour.f[1] = 128.0f;
    colour.f[2] = 128.0f;
    colour.f[3] = 255.0f;
    math_fast_float_d((int *)(data + 0x10));
    fraction = IntToFloat(*(int *)(data + 0x10));
    fraction /= IntToFloat(25);
    r = FloatToInt((colour.f[0] - 255.0f) * fraction + 255.0f);
    g = FloatToInt((colour.f[1] - 64.0f) * fraction + 64.0f);
    b = FloatToInt((colour.f[2] - 64.0f) * fraction + 64.0f);
    c = (g << 8) | 0xFF000000;
    *(unsigned int *)(object + 0x78) = ((b << 16) | c) | r;
}
