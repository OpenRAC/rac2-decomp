#include "common.h"

/* func_PAL_L01_003C0D50, the PAL copy of func_L01_003BD178: the same C, where the 60 Hz step 1/60
   becomes 0.020000001f and the three random lifetimes take the 50 Hz scale, here in float. */

extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);

void func_PAL_L01_003C0D50(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int a, b, c;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = func_00283180(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * func_002A7878(minRadius, maxRadius);
            y = func_00283198(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            y *= func_002A7878(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            func_00283098(offset, offset, m + 0xC0);
            {
                float range = speed * ((maxRadius - func_00282DF0(offset)) * 0.020000001f) / maxRadius;
                func_00282F20(velocity, offset, func_002A7878(range * 0.25f, range));
            }
            velocity[2] += func_002A7878(rise * 0.25f, rise) * 0.020000001f;
            qzero_nc(accel);
            func_00282CC0(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            a = func_00283CF0((func_002A7878(15.0f, 25.0f) * 5.0f + 2.0f) * 0.16666667f);
            b = func_00283CF0((func_002A7878(20.0f, 40.0f) * 5.0f + 2.0f) * 0.16666667f);
            c = func_00283CF0((func_002A7878(30.0f, 60.0f) * 5.0f + 2.0f) * 0.16666667f);
            particle = func_002BAA28(offset, velocity, accel, 0x50204050, 0x7F7F7F, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}
