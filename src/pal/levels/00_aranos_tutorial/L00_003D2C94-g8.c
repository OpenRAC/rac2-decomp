#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    int color;
    int mode;
    char gap[2];
    unsigned char alpha, brightness;
} ExhaustTail;
extern int func_002A77E0(int);
extern int func_00282948(char *);
extern int func_00283CF0(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_PAL_002BE9A8(void *, float, float, float, int, void *, float, int, int);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_002AEF28(void *, void *, void *, float, float, float);
extern float D_L00_001B0168 __attribute__((sda));
extern float D_L00_001B016C __attribute__((sda));
extern float D_L00_001B0170 __attribute__((sda));
extern float D_L00_001B0174 __attribute__((sda));
extern float D_L00_001B0178 __attribute__((sda));

void func_PAL_L00_003D4858(unsigned char *obj) {
    struct {
        Vec velocity, forward, position, up, side;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *first, *second, *child;
    if ((unsigned char)obj[0x20] == 0) {
        *(int *)(ctx + 0x10) = ((s32)(func_002A77E0(40)) * 5 + 2) / 6;
        obj[0x20] = 1;
        obj[0x30] = 100;
        *(int *)(ctx + 0x18) = 0;
        *(float *)(ctx + 0x28) = *(float *)(obj + 0x18);
    }
    if ((unsigned char)obj[0x20] == 1) {
        if (func_00282948(ctx + 0x10)) obj[0x20] = 2;
        {
            int angle;
            func_00282F20(&frame.velocity, obj + 0xC0, -0.15f);
            angle = func_002A77E0(16);
            if (func_002A77E0(2)) angle = -angle;
            qcopy(&frame.position, obj + 0x10);
            func_00282F20(&frame.forward, obj + 0xC0, -2.3f);
            func_00282CC0(&frame.position, &frame.position, &frame.forward);
            func_00282F20(&frame.up, obj + 0xE0, 0.75f);
            func_00282CC0(&frame.position, &frame.position, &frame.up);
            func_00282F20(&frame.side, obj + 0xD0, 0.25f);
            func_00282CC0(&frame.position, &frame.side, &frame.position);
            first = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = func_PAL_002BE9A8(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = func_00283CF0(4.0f);
                *(short *)(child + 10) = 17;
                child[9] = brightness + 112;
                child[8] = func_002A77E0(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            angle = func_002A77E0(16);
            if (func_002A77E0(2)) angle = -angle;
            func_00282F20(&frame.side, obj + 0xD0, -0.5f);
            func_00282CC0(&frame.position, &frame.side, &frame.position);
            first = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = func_PAL_002BE9A8(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = func_00283CF0(4.0f);
                *(short *)(child + 10) = 17;
                child[9] = brightness + 112;
                child[8] = func_002A77E0(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
        }
    }
    if ((unsigned char)obj[0x20] == 2) {
        func_002AEE70(obj, ctx + 0xC, ctx, D_L00_001B0168,
            D_L00_001B016C * 0.0003490659f, *(float *)(ctx + 0x28));
        func_002AEF28(obj, ctx + 4, ctx + 8,
            D_L00_001B0178 * 0.017453294f, D_L00_001B0170 * 0.0003490659f,
            D_L00_001B0174 * 0.0003490659f);
        {
            int angle;
            func_00282F20(&frame.velocity, obj + 0xC0, -0.15f);
            angle = func_002A77E0(16);
            if (func_002A77E0(2)) angle = -angle;
            qcopy(&frame.position, obj + 0x10);
            func_00282F20(&frame.forward, obj + 0xC0, -2.3f);
            func_00282CC0(&frame.position, &frame.position, &frame.forward);
            func_00282F20(&frame.up, obj + 0xE0, 0.75f);
            func_00282CC0(&frame.position, &frame.position, &frame.up);
            func_00282F20(&frame.side, obj + 0xD0, 0.25f);
            func_00282CC0(&frame.position, &frame.side, &frame.position);
            first = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = func_PAL_002BE9A8(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = func_00283CF0(4.0f);
                child[9] = brightness + 112;
                *(short *)(child + 10) = 17;
                child[8] = func_002A77E0(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            angle = func_002A77E0(16);
            if (func_002A77E0(2)) angle = -angle;
            func_00282F20(&frame.side, obj + 0xD0, -0.5f);
            func_00282CC0(&frame.position, &frame.side, &frame.position);
            first = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = func_PAL_002BE9A8(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 17;
                first[9] = func_00283CF0(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = func_PAL_002BE9A8(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = func_00283CF0(4.0f);
                *(short *)(child + 10) = 17;
                child[9] = brightness + 112;
                child[8] = func_002A77E0(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
        }
    }
}
