#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00424EF0);

extern float func_00283248(float x, float y);
extern void func_00282CF0(void *dst, void *a, void *b);
extern float func_002A7878(float a, float b);
extern int func_00283CF0(float value);
extern float D_L00_001B8DC0[];
extern float func_002A7878(float a, float b);
extern float func_002A78D8(float a, float b);
extern int func_00283CF0(float a);
extern float func_00283B98(float a, float b);
extern void func_002AF000(float *p, float a, float b, float c);
extern void func_PAL_002C23B8(float *out, float *in, int a2, int a3, unsigned int a4, int a5,
                           float f1, float f2, float f3, float f4, float f5);

/* Points the level's fixed vector at the given position, then spawns twenty
   particles around it, each one a random offset along the fixed vector.
   `size` is written but never read: that second reference to 210000.0f is what
   makes the compiler hold the constant in a saved float register ($f29) instead
   of rematerialising it at the call, which is what the retail does. */
void func_PAL_L00_004253C0(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float f20;
    float f21;
    float f28;
    float size;
    float r;
    int n;
    int id;

    func_00282CF0(v, D_L00_001B8DC0, pos);
    f28 = func_00283248(v[0], v[1]);
    n = 19;
    do {
        n--;
        f21 = func_002A7878(0.5f, 1.0f);
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        size = func_002A7878(0.05f, 0.2f) * 210000.0f;
        f20 = func_002A7878(0.0f, 1.3962636f);
        r = func_00283B98(f28, func_002A78D8(0.0f, 1.3962636f));
        func_002AF000(dir, f21 * (0.020000001f), r, f20);
        r = func_002A78D8(0.0f, 0.1f);
        out[0] = pos[0] + r;
        r = func_002A78D8(0.0f, 0.1f);
        out[1] = pos[1] + r;
        r = func_002A78D8(0.0f, 0.1f);
        out[2] = pos[2] + r;
        func_PAL_002C23B8(out, dir, 25, 127, 0x7F7F7F, id,
                      func_002A7878(0.05f, 0.2f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    } while (n >= 0);
}

