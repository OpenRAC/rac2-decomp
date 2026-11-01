#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282C10(float);
extern float func_002B0360(void *);
extern void func_00282C88(void *);
extern void func_00282CC0(char *, char *, char *);
typedef union { Vector128 q; float f[4]; } MotionVector;
extern void func_PAL_L13_0040ED20(char *, char *, char *, int);
extern float func_L02_00329C48(char *, Vector128 *, char *);
extern void func_L02_003294D8(char *, float *, float);
extern void func_002AFEB8(char *, char *, char *, float, char *);
extern void func_002AC9F8(float *, float);
extern float func_002AFF08(char *, char *, char *);
extern void func_L00_003253A0(u8 *, float *, float *, float);
extern float func_002AFF38(char *, char *, char *);
extern void func_002AAC80(float *, float, float, float, float);
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));

void func_PAL_L13_0040E5B0(char *object, char *data, void *target, Vector128 *input, void *unused0, void *unused1, char *transform) {
    MotionVector desired, change;
    float vertical;
    float heading, distance, speed, height, drop;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        func_PAL_L13_0040ED20(object, data, (char *)input, (int)transform);
    heading = 0.0f;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        heading = func_L02_00329C48(object, input, transform);
    if (*(float *)(data + 0x30) < heading) {
        func_00282C88(&desired.q);
    } else {
        float gap;
        distance = func_00282E48(object + 0x10, target);
        *(float *)(data + 0xCC) = distance;
        gap = *(float *)(data + 0x34);
        if (distance <= gap) {
            qzero(&desired);
        } else {
            gap = distance - gap;
            speed = func_00282C10((gap + gap) * *(float *)(data + 0x24));
            if (*(float *)(data + 0x28) < speed)
                speed = *(float *)(data + 0x28);
            func_L02_003294D8(object, desired.f, speed);
        }
    }
    func_00282CF0(change.f, desired.f, (float *)(data + 0xA0));
    func_002AFEB8(object, (char *)&change, (char *)&change, 0.0f, transform);
    if (func_00282DB0(&desired, data + 0xA0) > 0.0f)
        func_002AC9F8(change.f, *(float *)(data + 0x20));
    else
        func_002AC9F8(change.f, *(float *)(data + 0x24));
    func_00282CC0(data + 0xA0, data + 0xA0, &change);
    *(float *)(data + 0xB0) = func_002AFF08(object, data + 0xA0, transform);
    if (!(*(unsigned int *)(data + 0x38) & 4)) {
        height = func_002B0360(object + 0x10);
        if (*(float *)(data + 0x90) < height) {
            func_L00_003253A0((u8 *)object, (float *)(data + 0xA0), (float *)(data + 0xA0), *(float *)(data + 0x2C));
            if (*(short *)(data + 0xC0) == 0)
                *(unsigned int *)(data + 0x94) |= 0x20;
        } else {
            vertical = func_002AFF38(object, data + 0xA0, transform);
            drop = vertical;
            if (*(float *)(data + 0x90) - height < drop)
                vertical = *(float *)(data + 0x90) - height;
            else if (vertical < 0.0f)
                vertical = 0.0f;
            func_002AAC80(&vertical, *(float *)(data + 0x90) - height, 0.016f, 0.016f, 1.0f);
            func_002AFEB8(object, data + 0xA0, data + 0xA0, vertical, transform);
        }
    }
}

