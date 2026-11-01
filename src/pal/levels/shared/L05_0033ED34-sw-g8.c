#include "include_asm.h"

#include "common.h"
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U(p, o) (*(u8 *)((char *)(p) + (o)))
#define S(p, o) (*(s8 *)((char *)(p) + (o)))
#define H(p, o) (*(u16 *)((char *)(p) + (o)))
extern int func_PAL_002B2618(void *, int, int *, float *, float *, float *, float *,
                         float *, float *, float *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002AC290(void *, void *);
extern int D_001A8CA0;
extern float func_002AFF38(void *, void *, int);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_002AE730(void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B1CC8(void *, void *, void *, float, float, float);
extern float func_00282E20(void *);
extern void func_00282F70(void *, void *, float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);

/* Select a reaction animation and initialize its velocity and timers. */
int func_PAL_L05_0033F3A8(char *object, char *state, float *vector, int reaction)
{
    float forward[4];
    float projected[4];
    float backward[4];
    int index;
    float horizontal, vertical, duration, delay, a, b, scale;
    int valid = 1;
    float length;

    duration = F(state, 0x24);
    delay = F(state, 0x28);
    horizontal = F(state, 0x1c);
    vertical = F(state, 0x20);
    scale = F(state, 0x2c);
    switch (reaction) {
    default:
    case 1:
        U(state, 7) = 255;
        break;
    case 2:
        U(state, 7) = 255;
        if (func_PAL_002B2618(object, 0, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale))
            goto play;
        if (func_PAL_002B2618(object, 1, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale))
            break;
        if (U(state, 0x11) != 255) {
            horizontal *= 0.5f;
            vertical *= 0.5f;
            a = S(state, 0x6c);
            b = S(state, 0x6d);
            func_PAL_002A7E68(object, U(state, 0x11), 0, 2);
            break;
        }
        valid = 0;
        break;
    case 3:
        U(state, 7) = 255;
        if (func_PAL_002B2618(object, 1, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale))
            goto play;
        if (func_PAL_002B2618(object, 0, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale))
            goto play;
        if (U(state, 0x12) != 255) {
            horizontal *= 0.75f;
            vertical *= 0.75f;
            a = S(state, 0x6e);
            b = S(state, 0x6f);
            func_PAL_002A7E68(object, U(state, 0x12), 0, 2);
            break;
        }
        valid = 0;
        break;
    case 6:
        U(state, 7) = 255;
        if (func_PAL_002B2618(object, 5, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale)) {
            func_PAL_002A7E68(object, index, 0, 2);
        } else {
            valid = 0;
        }
        break;
    case 4:
        U(state, 7) = 255;
        H(state, 0x38) |= 1;
        I(object, 0x98) = 0;
        H(object, 0x34) &= 0xefff;
        if (func_PAL_002B2618(object, 3, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale)) {
play:
            func_PAL_002A7E68(object, index, 0, 2);
            break;
        }
        if (U(state, 0x16) != 255) {
            a = S(state, 0x72);
            b = S(state, 0x73);
            func_PAL_002A7E68(object, U(state, 0x16), 0, 2);
            break;
        }
        valid = 0;
        goto update;
    case 5:
        U(state, 7) = 255;
        H(state, 0x38) |= 2;
        I(object, 0x98) = 0;
        H(object, 0x34) &= 0xefff;
        if (func_PAL_002B2618(object, 4, &index, &horizontal, &vertical, &duration, &delay, &a, &b, &scale)) {
            func_PAL_002A7E68(object, index, 0, 2);
        } else if (U(state, 0x17) != 255) {
            horizontal *= 1.5f;
            vertical *= 1.5f;
            a = S(state, 0x72);
            b = S(state, 0x73);
            func_PAL_002A7E68(object, U(state, 0x17), 0, 2);
        } else {
            valid = 0;
        }
        F(state, 0x90) = 0.12566373f;
        F(state, 0x94) = 0.5026549f;
        break;
    }
update:
    func_PAL_002AC290(object, state);
    if (reaction == 1)
        goto done;
    if (!valid)
        goto done;
    if (D_001A8CA0) {
        length = func_002AFF38(object, vector, 0);
        if (length < 1.0f)
            length = 1.0f;
        func_002AFFD8(object + 0x10, forward, 0);
        func_00282F20(backward, vector, -1.0f);
        func_002AE730(backward, state + 0x64);
        {
            float dot = func_00282DB0(forward, vector);
            func_00282F20(projected, forward, dot);
        }
        func_00282CF0(vector, vector, projected);
        if (func_00282DF0(vector) < 1.0f)
            func_00282F20(vector, vector, 1.0f);
        func_00282D30(state + 0x80, vector, horizontal);
        func_00282F20(projected, forward, -vertical * length);
        func_00282CC0(state + 0x80, state + 0x80, projected);
    } else {
        func_002B1CC8(object, vector, vector, 5.0f, 0.7853982448577881f, 4.0f);
        if (func_00282E20(vector) < 1.0f)
            func_00282F70(vector, vector, 1.0f);
        if (vector[2] < 1.0f)
            vector[2] = 1.0f;
        F(state, 0x80) = vector[0] * horizontal;
        F(state, 0x84) = vector[1] * horizontal;
        F(state, 0x88) = vector[2] * vertical;
        F(state, 0x64) = func_00283B98(func_00283248(vector[0], vector[1]), 3.14159f);
    }
    if (U(state, 0x76) && reaction < 4) {
        F(state, 0x4c) = 0.0f;
        F(state, 0x50) = 0.0f;
        F(state, 0x54) = -1.0f;
        F(state, 0x60) = -1.0f;
    } else {
        F(state, 0x54) = a;
        F(state, 0x60) = b;
        F(state, 0x4c) = duration;
        F(state, 0x50) = delay;
        F(state, 0x2c) = scale;
    }
    return 1;
done:
    return 0;
}
