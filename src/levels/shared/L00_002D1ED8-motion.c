#include "common.h"

extern char D_00189E20_8[];
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_L00_0031EC88(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_L00_002D3EA8(void *);
extern float func_L00_002D3B00(void *);
extern int func_002A88A0(float *, float *, float, float, float);
extern char D_L00_001BF240[];

extern char D_L00_001BF220[];
typedef int MotionQuad __attribute__((mode(TI)));

/* Solve the forward collision time for each of the resident movement modes. */
float func_L00_002D2A10(float time, float acceleration, float height)
{
    float end[4], direction[4], curve[4], start[4];
    float root0a, root0b, root1a, root1b, root2a, root2b;
    float speed, position;
    char *state = D_00189E20_8;
    switch (*(unsigned char *)(state + 0x22C3)) {
    case 0: {
        float half;
        if (height < 0.0f) {
            char *pos = state + 0x80;
            FastVecScale(end, state + 0xF0, time);
            end[2] -= (time * time + time) * (acceleration * 0.5f);
            FastVecAdd(end, end, pos);
            *(MotionQuad *)direction = *(MotionQuad *)(state + 0x80);
            func_L00_0031EC88(direction, end);
            qcopy(direction, pos);
            if (CollLine(direction, end, 0x22, 0, 0)) {
                if (func_L00_002D3EA8(D_L00_001BF240) <= 0.8726647f)
                    height = *(float *)(D_L00_001BF240 - 0x18);
            }
        }
        if (height > 0.0f) {
            char *root = D_00189E20_8;
            half = acceleration * -0.5f;
            if (func_002A88A0(&root0a, &root0b, half,
                    *(float *)(root + 0xF8) - half,
                    *(float *)(root + 0x88) - height) > 0
                    && root0a > 0.0f)
                return root0a;
        }
        break;
    } case 1: {
        float half;
        char *velocity;
        char *pos;
        qcopy(direction, state + 0x2A0);
        velocity = state + 0xF0;
        vec_scale_to_length(direction, direction, acceleration);
        pos = state + 0x80;
        FastVecScale(direction, direction, -1.0f);
        FastVecScale(end, velocity, time);
        FastVecScale(curve, direction, (time * time + time) * (acceleration * 0.5f));
        FastVecAdd(end, curve, end);
        FastVecAdd(end, pos, end);
        *(MotionQuad *)start = *(MotionQuad *)(pos);
        func_L00_0031EC88(start, end);
        if (CollLine(pos, end, 0x22, 0, 0)) {
            half = acceleration * -0.5f;
            speed = func_L00_002D3B00(velocity) - half;
            position = func_L00_002D3B00(pos);
            position -= func_L00_002D3B00(D_L00_001BF220);
            if (func_002A88A0(&root1a, &root1b, half, speed, position) > 0
                    && root1a > 0.0f)
                return root1a;
        }
        break;
    } case 2: {
        float half;
        char *velocity = state + 0xF0;
        char *pos = state + 0x80;
        curve[2] = 100.0f;
        curve[1] = 100.0f;
        curve[0] = 100.0f;
        FastVecSub(direction, pos, curve);
        vec_scale_to_length(direction, direction, acceleration);
        FastVecScale(direction, direction, -1.0f);
        FastVecScale(end, velocity, time);
        FastVecScale(curve, direction, (time * time + time) * (acceleration * 0.5f));
        FastVecAdd(end, curve, end);
        FastVecAdd(end, pos, end);
        *(MotionQuad *)start = *(MotionQuad *)(pos);
        func_L00_0031EC88(start, end);
        if (CollLine(pos, end, 0x22, 0, 0)) {
            half = acceleration * -0.5f;
            speed = func_L00_002D3B00(velocity) - half;
            position = func_L00_002D3B00(pos);
            position -= func_L00_002D3B00(D_L00_001BF220);
            if (func_002A88A0(&root2a, &root2b, half, speed, position) > 0
                    && root2a > 0.0f)
                return root2a;
        }
        break;
    } }
    return time;
}
