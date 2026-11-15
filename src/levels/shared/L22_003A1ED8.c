#include "common.h"

typedef int Quad0792 __attribute__((mode(TI)));
extern int math_random_int_below(int);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_L22_002F3B38(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern Quad0792 D_L22_001C0100;
extern char D_00189ED0[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);
extern float D_L22_001B2AA4 __attribute__((sda));

/* Sends a short test line ahead of the ship. If it hits a surface, it works out a safe point to steer toward and returns 1. */
int space_ship_trace_safe_point_ahead(char *obj) {
    struct { Quad0792 start, end, axis, direction, projection, epsilon, offset, blended; } v;
    char *st = *(char **)(obj + 0x68);
    v.end = 0;
    *(float *)((char *)&v.end + 8) = *(float *)(st + 0x114) + *(float *)(st + 0x110);
    v.axis = 0;
    *(float *)&v.axis = 4.0f;
    v.start = v.end;
    *(float *)((char *)&v.axis + 4) = (float)math_random_int_below(8) * 0.4285714626312256f + -1.5f;
    *(float *)((char *)&v.axis + 8) = *(float *)(st + 0x114) + *(float *)(st + 0x110);
    v.end = v.axis;
    FastVecScale(&v.start, obj + 0xE0, *(float *)((char *)&v.start + 8));
    FastVecAdd(&v.start, &v.start, obj + 0x10);
    matrix_mul_vec3(&v.end, &v.end, obj + 0xC0);
    FastVecAdd(&v.end, &v.end, obj + 0x10);
    if (CollLine(&v.start, &v.end, 0x12, 0, 0)) {
        qcopy(&v.axis, &D_L22_001C0100);
        v.epsilon = 0;
        *(float *)&v.epsilon = 0.0009765625f;
        *(float *)((char *)&v.epsilon + 4) = 0.0009765625f;
        *(float *)((char *)&v.epsilon + 8) = 0.0009765625f;
        func_L22_002F3B38(&v.axis, &v.axis, &v.epsilon);
        vec_scale_to_length(&v.axis, &v.axis, 1.0f);
        FastVecSub(&v.direction, &v.start, (char *)&D_L22_001C0100 - 0x20);
        {
            float dot = FastVecDot(&v.direction, &v.axis);
            FastVecScale(&v.projection, &v.axis, dot);
        }
        FastVecSub(&v.offset, &v.direction, &v.projection);
        vec_scale_to_length(&v.offset, &v.offset, -30.0f);
        FastVecAdd(st + 0x390, obj + 0x10, &v.offset);
        FastVecSub(&v.blended, st + 0x390, D_00189ED0);
        vec_scale_to_length(&v.blended, &v.blended, D_L22_001B2AA4);
        FastVecAdd(&v.blended, &v.blended, D_00189ED0);
        qcopy(st + 0x390, &v.blended);
        *(short *)(st + 0x378) = 1;
        vec_scale_to_length(&v.axis, &v.axis, 10.0f);
        FastVecAdd(&v.axis, &v.axis, (char *)&D_L22_001C0100 - 0x20);
        return 1;
    }
    return 0;
}
