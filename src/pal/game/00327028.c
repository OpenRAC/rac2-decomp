#include "include_asm.h"

extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, int);
extern void func_002C2210(float *, int, int, int, int, float *, int, float, float, float);

void func_PAL_00327028(float *self, int unused, int a2)
{
    float vec[4];
    float scale = func_002A7878(0.10000000149011612f, 0.25f);
    int r = func_002A77E0(2);
    int sign;
    float a, b;

    if (r == 0)
        r = r - 1;
    sign = r;
    a = func_002A7940();
    b = func_002A7878(0.349065899848938f, 1.5358898639678955f);

    func_002AF000(vec, func_002A7878(0.05000000074505806f, 0.10000000149011612f), a, b);
    func_00282CC0(vec, vec, a2);
    self[0] = self[0] + func_002A78D8(0.0f, 0.15000000596046448f);
    self[1] = self[1] + func_002A78D8(0.0f, 0.15000000596046448f);
    func_002C2210(self, 0x19, 0x7F207F7F, 0, sign, vec, 0, scale * 0.10000000149011612f, scale,
                  0.006000000052154064f);
    func_002C2210(self, 0x19, 0x7F7F7F7F, 1, -sign, vec, 0, scale * 0.07000000029802322f,
                  scale * 0.699999988079071f, 0.006000000052154064f);
}

