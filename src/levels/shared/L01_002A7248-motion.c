#include "common.h"

extern char D_L01_00189E20[];
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void coll_push_vector_from_negative_axes(void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float cam_get_view_space_angle(void *);
extern float cam_get_view_space_height(void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern char D_L01_001BF940[];

extern char g_coll_line_hit_point[];
typedef int MotionQuad __attribute__((mode(TI)));

/* Solve the forward collision time for each of the resident movement modes. */
float hero_solve_fall_collision_time(float time, float acceleration, float height)
{
    float end[4], direction[4], curve[4], start[4];
    float root0a, root0b, root1a, root1b, root2a, root2b;
    float speed, position;
    char *state = D_L01_00189E20;
    switch (*(unsigned char *)(state + 0x22C3)) {
    case 0: {
        float half;
        if (height < 0.0f) {
            char *pos = state + 0x80;
            FastVecScale(end, state + 0xF0, time);
            end[2] -= (time * time + time) * (acceleration * 0.5f);
            FastVecAdd(end, end, pos);
            *(MotionQuad *)direction = *(MotionQuad *)(state + 0x80);
            coll_push_vector_from_negative_axes(direction, end);
            qcopy(direction, pos);
            if (CollLine(direction, end, 0x322, 0, 0)) {
                if (cam_get_view_space_angle(D_L01_001BF940) <= 0.8726647f)
                    height = *(float *)(D_L01_001BF940 - 0x18);
            }
        }
        if (height > 0.0f) {
            char *root = D_L01_00189E20;
            half = acceleration * -0.5f;
            if (math_solve_quadratic(&root0a, &root0b, half,
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
        coll_push_vector_from_negative_axes(start, end);
        if (CollLine(pos, end, 0x322, 0, 0)) {
            half = acceleration * -0.5f;
            speed = cam_get_view_space_height(velocity) - half;
            position = cam_get_view_space_height(pos);
            position -= cam_get_view_space_height(g_coll_line_hit_point);
            if (math_solve_quadratic(&root1a, &root1b, half, speed, position) > 0
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
        coll_push_vector_from_negative_axes(start, end);
        if (CollLine(pos, end, 0x322, 0, 0)) {
            half = acceleration * -0.5f;
            speed = cam_get_view_space_height(velocity) - half;
            position = cam_get_view_space_height(pos);
            position -= cam_get_view_space_height(g_coll_line_hit_point);
            if (math_solve_quadratic(&root2a, &root2b, half, speed, position) > 0
                    && root2a > 0.0f)
                return root2a;
        }
        break;
    } }
    return time;
}
