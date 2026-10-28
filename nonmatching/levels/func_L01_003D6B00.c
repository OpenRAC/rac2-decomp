/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por.
 * Compiled 396 bytes; retail 396 bytes.
 * Carrying checks: 0/2 in us, pal and us2. No strict linked qualification.
 * Right size; the loop body agrees substantially, but the count save/guard prologue and emitter argument schedule differ. A separate decrement-at-start loop grew to 408 bytes; disabling rerun-loop-opt gave 392 with an extra saved pointer and different constant motion; G8 did not fix it. Reopen with a genuine counter lifetime hypothesis.
 */
#include "common.h"
typedef union { int whole __attribute__((mode(TI))); float f[4]; } EffectVector;
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003263D0(void *, void *, int, int, void *, unsigned int, void *, float, float, float, float);

void func_L01_003D6B00(char *object, int count, float low, float high, float radius, float speed)
{
    EffectVector position, velocity;
    float angle;
    position.whole = 0;
    velocity.whole = 0;
    if (count > 0) {
        do {
        angle = func_002A7878(-3.1415927410125732f, 3.1415927410125732f);
        position.f[0] = radius * func_00283180(angle);
        position.f[1] = radius * func_00283198(angle);
        position.f[2] = func_002A7878(0.0f, 1.0f);
        func_00282F20(&velocity, &position, func_002A7878(speed * 0.75f, speed * 1.25f));
        position.f[2] = func_002A7878(low, high);
        func_00282CC0(&position, object + 0x10, &position);
        func_L00_003263D0(object, &position, 1, 1, &velocity, 0x50808040, 0,
                         0.0f, 0.0f, 1.0f, 5.5f);
        count--;
        } while (count != 0);
    }
}
