#include "common.h"


extern float func_002A7878(float, float);
extern void func_00283098(void *, void *, void *);
extern void func_L00_00324F18(float, float, float, void *, void *);
extern int func_00283CF0(float);
extern int func_00283D38(float, int, int);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);

typedef struct { float x, y, z, w; } SparkVector;
void func_L03_002ECF08(unsigned char *object, float *minimumPosition, float *maximumPosition,
                      float *minimumVelocity, float *maximumVelocity, int count, unsigned char style) {
    SparkVector velocity, acceleration, position;
    int flags = 0x1003C;
    float scale;
    float gravity = 0.0013888889f;
    int a, b, c, startColor, endColor;
    int i;

    for (i = 0; i < count; i++) {
        velocity.x = func_002A7878(minimumVelocity[0], maximumVelocity[0]) * 0.016666668f;
        velocity.y = func_002A7878(minimumVelocity[1], maximumVelocity[1]) * 0.016666668f;
        velocity.z = func_002A7878(minimumVelocity[2], maximumVelocity[2]) * 0.016666668f;
        position.x = func_002A7878(minimumPosition[0], maximumPosition[0]);
        position.y = func_002A7878(minimumPosition[1], maximumPosition[1]);
        position.z = func_002A7878(minimumPosition[2], maximumPosition[2]);
        matrix_mul_vec3(&velocity, &velocity, object + 0xC0);
        func_L00_00324F18(position.x, position.y, position.z, object, &position);
        scale = func_002A7878(0.5f, 1.5f);
        a = FloatToInt(scale * 10.0f);
        b = FloatToInt(scale * 35.0f);
        c = FloatToInt(scale * 7.0f);
        velocity.w = func_002A7878(0.1f, 0.4f);
        func_00282C88(&acceleration);
        acceleration.z = -gravity * (float)(a + b + c);
        FastVecAdd(&acceleration, &acceleration, &velocity);
        acceleration.w = 0.01f;
        switch (style) {
        case 1:
            startColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x80102040, 0x801010A0);
            endColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x102040, 0x1010A0);
            break;
        case 3:
            startColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x80201608, 0x80402510);
            endColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x201608, 0x402510);
            break;
        case 2:
            startColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x80104010, 0x8020A020);
            endColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x104010, 0x20A020);
            break;
        case 0:
        default:
            startColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x80004080, 0x80408080);
            endColor = FastTweenColor(func_002A7878(0.0f, 1.0f), 0x4080, 0x408080);
            break;
        }
        func_002BAA28(&position, &velocity, &acceleration, startColor, endColor, a, b, c, flags);
    }
}
