#include "include_asm.h"

/* func_PAL_00317768, the PAL copy of func_00316248: the same C, where the angle step 0.125f
   becomes 0.15f and the callee func_003169D0 is the PAL copy func_PAL_00317EF8. */
extern float D_001AF57C __attribute__((sda));
extern char D_001B2520[] __attribute__((sda));
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern int func_00283D38(int, int, float);
extern void func_PAL_00317EF8(void *);
extern void func_00281EB8(char *, int, unsigned int, int, float, float, float);

void func_PAL_00317768(void *object)
{
    float angle = func_00283B98(D_001AF57C, 0.15f);
    float scale;
    float size_a;
    float size_b;
    float size_c;
    int colour_a;
    int colour_b;
    int colour_c;

    D_001AF57C = angle;
    scale = func_00283180(angle);
    scale = (scale + 1.0f) * 0.5f;
    size_b = scale * 0.0625f + 0.0625f;
    size_c = scale * 0.19999999f + 0.15f;
    size_a = scale * 0.125f + 0.125f;

    colour_a = func_00283D38(0x2F007F00, 0x3F007F00, scale);
    colour_b = func_00283D38(0x2F7F7F7F, 0x5F7F7F7F, scale);
    colour_c = func_00283D38(0x10003F00, 0x10003F00, scale);

    func_PAL_00317EF8(object);
    func_00281EB8(D_001B2520, 0x31, colour_a, 1, size_a, 0.125f, 0.0f);
    func_00281EB8(D_001B2520, 0x31, colour_b, 1, size_b, 0.124f, 0.0f);
    func_00281EB8(D_001B2520, 0x0B, colour_c, 1, size_c, 0.123f, 0.0f);
}
