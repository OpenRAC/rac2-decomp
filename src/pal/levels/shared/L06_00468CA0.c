#include "include_asm.h"


#include "common.h"
extern char *CreateMoby(int);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void vec_scale_to_length(void *, void *, float);

/* Creates one small flying particle object (moby class 4535) at the given spot, moving in the given direction. */
char *part_spawn_spark_moby_pal(char *moby, void *position, void *velocity, int kind, float size, float life)
{
    char *obj = CreateMoby(0x11B7 /* moby class 4535 */);
    u8 *vars;
    int red, green, blue, green_alpha;
    if (obj) {
        obj[0x30] = moby[0x30];
        vars = *(u8 **)(obj + 0x68);
        *(unsigned short *)(obj + 0x32) = (u8)moby[0x30];
        obj[0x20] = 0;
        *(float *)(vars + 0x38) = life;
        *(float *)(vars + 0x34) = size * 0.12483149f;
        *(float *)(vars + 0x44) = math_random_float_range(0.5f, 1.0f) * 0.020000001f;
        vars[0x4C] = kind;
        qcopy(obj + 0x10, position);
        qcopy(vars, position);
        qcopy(vars + 0x20, velocity);
        qcopy(vars + 0x10, velocity);
        *(float *)(vars + 0x18) = 0;
        vec_scale_to_length(vars + 0x10, vars + 0x10, 1.0f);
        if (!kind) {
            *(unsigned short *)(obj + 0x34) &= ~1;
            obj[0x23] = 0x50;
            obj[0x31] = 1;
            *(short *)(obj + 0x7C) = (1 << math_random_int_below(4)) - 0x8000;
        } else {
            obj[0x31] = 0;
            *(unsigned short *)(obj + 0x34) |= 1;
            vars[0x4E] = 0x44;
            vars[0x4F] = 0x46;
            obj[0x23] = 0x7F;
            if (math_random_int_below(2)) { u8 t = vars[0x4E]; vars[0x4E] = vars[0x4F]; vars[0x4F] = t; }
            vars[0x4D] = math_random_int_below(2);
            if ((u8)vars[0x4D]) {
                *(float *)(vars + 0x50) = math_random_float_range(0.2f, 0.3f);
                *(float *)(vars + 0x54) = math_random_float_range(0.1f, 0.15f);
            } else {
                *(float *)(vars + 0x50) = math_random_float_range(0.1f, 0.15f);
                *(float *)(vars + 0x54) = math_random_float_range(0.2f, 0.3f);
            }
            red = math_random_int_range(100,127);
            green = math_random_int_range(100,127);
            blue = math_random_int_range(100,127);
            green_alpha = (green << 8) | 0x7F000000;
            *(u32 *)(vars + 0x58) = (red << 16) | green_alpha | blue;
        }
    }
    return obj;
}

