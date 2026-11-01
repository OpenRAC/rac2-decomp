#include "include_asm.h"

#include "common.h"
extern float func_002A7878(float min, float max);
extern int func_002A77E0(int count);
extern float func_002A7940(void);
extern float func_002A78D8(float min, float max);
extern void func_002AF000(float *out, float a, float b, float c);
extern unsigned char *func_002C2210(float life, void *position, int size, float secondLife, int color, int mode, int flag, float *vector, float third, int counter);
extern int func_00283CF0(float value);

void func_PAL_L00_003C9708(void *position, int color)
{
    float vector[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale;
    float radius;
    float a;
    float b;
    int sign;
    unsigned char *particle;
    int i = 7;
    do {
        scale = func_002A7878(1.0f, 6.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        radius = func_002A7878(0.5f, 6.0f) * 0.020000001f;
        a = func_002A7940();
        b = func_002A7940();
        func_002AF000(vector, radius, a, b);
        qcopy(offset, position);
        offset[0] += func_002A78D8(0.0f, 0.1f);
        offset[1] += func_002A78D8(0.0f, 0.1f);
        offset[2] += func_002A78D8(0.0f, 0.1f);
        particle = func_002C2210(scale * 0.1f, offset, 17, scale, color | 0x7F000000, 0, sign, vector, 0.0f, 1);
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 112;
        particle = func_002C2210(scale * 0.04f, offset, 17, scale * 0.4f, 0x7F7F7F7F, 1, -sign, vector, 0.0f, 1);
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 112;
        i--;
    } while (i >= 0);
}
