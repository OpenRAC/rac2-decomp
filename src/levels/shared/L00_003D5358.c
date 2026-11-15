#include "names.h"
/* func_L00_003D5358 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float func_002A7878(float low, float high);
extern void func_0029FCC0(char *object, int joint, void *out);
extern void func_L00_0033C0D0(char *object, void *position, void *velocity, void *parameters, int mode);
extern char D_L00_001B02E8 __attribute__((sda));
extern char D_L00_001B02F8 __attribute__((sda));
extern char D_L00_001B0308 __attribute__((sda));


extern char D_00189E20[] __attribute__((nosda));
extern float func_00283CE0(int value);
extern float func_00283180(float angle);
extern float func_00283198(float angle);
extern float func_002831B0(float value);
extern void func_00282F20(void *out, void *vector, float scale);
extern void func_00282CC0(void *out, void *left, void *right);
extern void func_00282CF0(void *out, void *left, void *right);
extern void func_00282D30(void *out, void *vector, float scale);
extern float func_00282DB0(void *left, void *right);
extern float func_00282DF0(void *vector);
extern float func_002AA898(float *position, float target, float *velocity, float acceleration, float damping, float limit, int direction);


extern float D_L00_001B03D4 __attribute__((sda));
extern float D_L00_001B03DC __attribute__((sda));
extern float D_L00_001B03E0 __attribute__((sda));
extern float D_L00_001B03E4 __attribute__((sda));
extern int func_L00_002AE888(void *axis, int mode, int flag, float value, float z, float low, float high);
extern void func_002FDF40(void *velocity, void *position, int handle, int mode, float a, float b, float c, float d);
extern void func_002ACEC0(void *out, void *source, void *axis, float angle);

/* Turns the object toward a target point, easing its angle with the given speed, damping and limit. */
void func_L00_003D5358(char *object, void *target, float *velocity, float acceleration, float damping, float limit)
{
    Vector difference, projection;
    char *base;
    float angle, magnitude;
    float zero;
    FastVecSub(&difference, target, object + 0x10);
    base = gHeroState;
    zero = 0.0f;
    angle = FastVecDot(&difference, *(char **)(base + 0x2290) + 0xe0);
    FastVecScale(&projection, *(char **)(base + 0x2290) + 0xe0, angle);
    FastVecSub(&difference, &difference, &projection);
    angle = FastVecDot(&difference, *(char **)(base + 0x2290) + 0xc0);
    magnitude = FastVecLength(&difference);
    if (magnitude != zero) {
        angle = FastAngleHelper(angle / magnitude);
        angle = 1.5707964f - angle;
        if (FastVecDot(&difference, *(char **)(base + 0x2290) + 0xd0) < zero)
            angle = -angle;
        ApproachWithVelocity((float *)(object + 0xf8), angle, velocity, acceleration, damping, limit, 0);
    }
}
