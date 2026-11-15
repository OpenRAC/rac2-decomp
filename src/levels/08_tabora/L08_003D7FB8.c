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

/* Shoots out a burst of 200 yellow sparks from the object that inherit its movement. */
void func_L08_003D7FB8(char *moby, char *baseVelocity) {
    float position[4];
    float velocity[4];
    float acceleration[4];
    int burst;
    int spark;
    float direction;
    float speed;
    float upSpeed;
    int colorStart;
    int colorEnd;
    char *mobyPos = moby + 0x10;

    for (burst = 0; burst < 20; burst++) {
        *(TI128 *)position = *(TI128 *)mobyPos;
        AddRandomOffsetToVector(position, 0.25f);
        position[2] += 0.25f;
        direction = RandomAngle();
        speed = RandomFloatRange(1.0f, 8.0f);
        upSpeed = RandomFloatRange(2.0f, 6.0f);
        FastVecScale(velocity, baseVelocity, RandomFloatRange(0.0f, 0.0f) * 0.016666668f);
        velocity[0] += FastSinOrCosA(direction) * 0.016666668f * speed;
        velocity[1] += FastSinOrCosB(direction) * 0.016666668f * speed;
        velocity[2] += upSpeed * 0.016666668f;
        *(TI128 *)acceleration = *(TI128 *)velocity;
        acceleration[2] -= 0.16666667f;
        for (spark = 0; spark < 10; spark++) {
            float sizeScale = RandomFloatRange(0.5f, 1.5f);

            velocity[3] = sizeScale * 0.125f;
            acceleration[3] = sizeScale * 0.065f;
            AddRandomOffsetToVector(position, 0.125f);
            AddRandomOffsetToVector(acceleration, 0.0083333338f);
            colorStart = FastTweenColor(0x8000EEEE, 0x8000FF90, RandomFloatRange(0.0f, 1.0f));
            colorEnd = FastTweenColor(0xFFEE, 0xFFEE, RandomFloatRange(0.0f, 1.0f));
            SpawnTrailParticle_002BAA28(position, velocity, acceleration, colorStart, colorEnd, 10, 30, FloatToInt(RandomFloatRange(15.0f, 75.0f)), -1);
        }
    }
}
