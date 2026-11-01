#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
extern int func_001163B0(void);
extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *, char *, char *);
extern float func_002A7878(float, float);
extern void func_002AF000(float *, float, float, float);
extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *dst, char *src, char *arg);
extern float func_002A7878(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern void ref_L00_003E5340_00(float *, float *, int, int, int);
#include "common.h"

/* Emits ten particles at POSITION: one thrown towards D_L00_001B8DC0 with a random spread, then
   nine at random upward angles turned by the object's matrix, about a third of them (rand() % 3
   == 0) in mode 1. */
void func_PAL_L00_003E95C0(char *object, float *position)
{
    Vector delta, velocity, random;
    float distance;
    int divisor = 3;
    int i = 8;
    int mode;

    func_00282CF0((char *)delta, D_L00_001B8DC0, (char *)position);
    distance = func_00282DF0(delta);
    *(VectorBits *)random = 0;
    random[0] = func_002A7878(-1.0f, 1.0f);
    random[1] = func_002A7878(-1.0f, 1.0f);
    random[2] = func_002A7878(-1.0f, 1.0f);
    delta[2] += distance * 0.5f;
    *(VectorBits *)velocity = *(VectorBits *)random;
    func_00282F20(velocity, velocity, distance * 0.004f);
    func_00282F20(delta, delta, (distance + distance) * 0.020000001f);
    func_00282CC0(velocity, velocity, delta);
    func_00282FB8(velocity, velocity, 0.20000002f);
    ref_L00_003E5340_00(position, velocity, func_002A7820(50, 75), 0, 0);
    for (; i >= 0; i--) {
        float pitch, yaw, speed;

        mode = 0;
        pitch = func_002A7878(0.2617994248867035f, 1.3089970350265503f);
        yaw = func_002A7940();
        speed = func_002A7878(8.0f, 12.0f);
        func_002AF000(random, speed * 0.020000001f, yaw, pitch);
        random[2] += 0.060000002f;
        if (func_001163B0() % divisor == 0)
            mode = 1;
        func_00283098(random, random, object + 0xC0);
        ref_L00_003E5340_00(position, random, func_002A7820(50, 75), mode, 0);
    }
}

