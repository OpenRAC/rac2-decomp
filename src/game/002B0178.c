#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int D_001A8CA0[] __attribute__((sda));
extern int D_001A8CA4[] __attribute__((sda));
extern Vector D_001B17D0;
extern Vector D_001BAFA0;
extern float D_001BAFA8;
extern int CollLine(void *, void *, int, void *, int);
extern void gravity_offset_position(void *, float *, float *, float);
extern float fast_vec_dist(void *, void *);

/* Finds the ground below a position and returns the height or distance to it, also giving the spot that was hit. */
float coll_get_ground_distance_below(Vector *position, void *owner, Vector *output)
{
    Vector low, high;
    float distance, result;
    if (D_001A8CA0[0] == 0) {
        qcopy(&low, position);
        low.f[2] = 0.01f;
        qcopy(&high, position);
        high.f[2] += 0.5f;
        if (CollLine(&high, &low, 2, owner, 0)) {
            if (output != 0)
                qcopy(output, &D_001BAFA0);
            return position->f[2] - D_001BAFA8;
        }
        if (output != 0)
            qcopy(output, position);
        return position->f[2];
    }
    qcopy(&low, &D_001B17D0);
    if (D_001A8CA4[0] != 0) {
        qcopy(&low, position);
        gravity_offset_position(&low, low.f, low.f, -10.0f);
    }
    gravity_offset_position(position, high.f, position->f, -0.5f);
    distance = fast_vec_dist(position, &low);
    if (CollLine(&high, &low, 2, owner, 0)) {
        if (output != 0)
            qcopy(output, &D_001BAFA0);
        result = fast_vec_dist(position, &D_001BAFA0);
        if (distance < fast_vec_dist(&D_001BAFA0, &low))
            result = -result;
        return result;
    }
    if (output != 0)
        qcopy(output, position);
    return distance;
}
