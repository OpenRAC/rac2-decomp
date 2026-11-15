#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002ACB48(float *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_00283CF0(float);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Shoots a shower of small yellow sparks out of a point, moving along with the given speed. */
void func_L08_00422578(char *moby, char *baseVelocity) {
    float position[4];
    float velocity[4];
    float accel[4];
    int burst;
    int i;
    float angle;
    float radius;
    float rise;
    int startColor;
    int endColor;
    char *src = moby + 0x10;

    for (burst = 0; burst < 20; burst++) {
        *(TI128 *)position = *(TI128 *)src;
        AddRandomOffsetToVector(position, 0.25f);
        position[2] += 0.25f;
        angle = RandomAngle();
        radius = RandomFloatRange(1.0f, 8.0f);
        rise = RandomFloatRange(2.0f, 6.0f);
        FastVecScale(velocity, baseVelocity, RandomFloatRange(0.0f, 0.0f) * 0.016666668f);
        velocity[0] += FastSinOrCosA(angle) * 0.016666668f * radius;
        velocity[1] += FastSinOrCosB(angle) * 0.016666668f * radius;
        velocity[2] += rise * 0.016666668f;
        *(TI128 *)accel = *(TI128 *)velocity;
        accel[2] -= 0.16666667f;
        for (i = 0; i < 10; i++) {
            float k = RandomFloatRange(0.5f, 1.5f);

            velocity[3] = k * 0.125f;
            accel[3] = k * 0.065f;
            AddRandomOffsetToVector(position, 0.125f);
            AddRandomOffsetToVector(accel, 0.0083333338f);
            startColor = FastTweenColor(0x8000EEEE, 0x8000FF90, RandomFloatRange(0.0f, 1.0f));
            endColor = FastTweenColor(0xFFEE, 0xFFEE, RandomFloatRange(0.0f, 1.0f));
            SpawnTrailParticle_002BAA28(position, velocity, accel, startColor, endColor, 10, 30, FloatToInt(RandomFloatRange(5.0f, 25.0f)), -1);
        }
    }
}
