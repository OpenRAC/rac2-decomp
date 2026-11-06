#include "include_asm.h"

/* func_PAL_L08_0042A6A0, the PAL copy of func_L08_00424FF8: the same C, where the per-frame 0.0166667f
   becomes 0.02f and the three particle timers are scaled to 50 Hz. */
#include "common.h"
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

static __inline__ void vzero(float *v) {
    qzero(v);
}

/* The same dust burst as func_L08_00422190, except that a moby in state 5 hands the particles
   part of its own motion: 0.8 of the vector at vars + 0xD0 joins their velocity and 0.4 of
   that becomes their acceleration. */
void func_PAL_L08_0042A6A0(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], motion[4];
    int a, b, c;
    char *particle;
    char *vars = *(char **)(m + 0x68);

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
            if (*(u8 *)(m + 0x20) == 5) {
                qcopy(motion, vars + 0xD0);
                motion[2] = 0;
                func_00282D30(motion, vars + 0xD0, 0.8f);
                func_00282CC0(velocity, velocity, motion);
                func_00282D30(accel, motion, 0.4f);
            } else {
                vzero(accel);
            }
            func_00282CC0(offset, offset, position);
            offset[2] += -0.75f;
            velocity[3] = size;
            accel[3] = endSize;
            a = func_00283CF0((func_002A7878(15.0f, 25.0f) * 5.0f + 2.0f) * 0.16666667f);
            b = func_00283CF0((func_002A7878(20.0f, 40.0f) * 5.0f + 2.0f) * 0.16666667f);
            c = func_00283CF0((func_002A7878(50.0f, 70.0f) * 5.0f + 2.0f) * 0.16666667f);
            particle = func_002BAA28(offset, velocity, accel, 0x70204050, 0x7F7F7F, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}
