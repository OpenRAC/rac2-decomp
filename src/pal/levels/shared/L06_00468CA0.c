#include "include_asm.h"


#include "common.h"
extern char *CreateMoby(int);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void vec_scale_to_length(void *, void *, float);

char *func_PAL_L06_00469110(char *moby, void *position, void *velocity, int kind, float size, float life)
{
    char *obj = CreateMoby(0x11B7);
    u8 *st;
    int r, g, b, ga;
    if (obj) {
        obj[0x30] = moby[0x30];
        st = *(u8 **)(obj + 0x68);
        *(unsigned short *)(obj + 0x32) = (u8)moby[0x30];
        obj[0x20] = 0;
        *(float *)(st + 0x38) = life;
        *(float *)(st + 0x34) = size * 0.12483149f;
        *(float *)(st + 0x44) = math_random_float_range(0.5f, 1.0f) * 0.020000001f;
        st[0x4C] = kind;
        qcopy(obj + 0x10, position);
        qcopy(st, position);
        qcopy(st + 0x20, velocity);
        qcopy(st + 0x10, velocity);
        *(float *)(st + 0x18) = 0;
        vec_scale_to_length(st + 0x10, st + 0x10, 1.0f);
        if (!kind) {
            *(unsigned short *)(obj + 0x34) &= ~1;
            obj[0x23] = 0x50;
            obj[0x31] = 1;
            *(short *)(obj + 0x7C) = (1 << math_random_int_below(4)) - 0x8000;
        } else {
            obj[0x31] = 0;
            *(unsigned short *)(obj + 0x34) |= 1;
            st[0x4E] = 0x44;
            st[0x4F] = 0x46;
            obj[0x23] = 0x7F;
            if (math_random_int_below(2)) { u8 t = st[0x4E]; st[0x4E] = st[0x4F]; st[0x4F] = t; }
            st[0x4D] = math_random_int_below(2);
            if ((u8)st[0x4D]) {
                *(float *)(st + 0x50) = math_random_float_range(0.2f, 0.3f);
                *(float *)(st + 0x54) = math_random_float_range(0.1f, 0.15f);
            } else {
                *(float *)(st + 0x50) = math_random_float_range(0.1f, 0.15f);
                *(float *)(st + 0x54) = math_random_float_range(0.2f, 0.3f);
            }
            r = math_random_int_range(100,127);
            g = math_random_int_range(100,127);
            b = math_random_int_range(100,127);
            ga = (g << 8) | 0x7F000000;
            *(u32 *)(st + 0x58) = (r << 16) | ga | b;
        }
    }
    return obj;
}

