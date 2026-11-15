#include "common.h"

extern void func_00282CF0(char *, char *, char *);
extern float func_00282DF0(char *);
extern void func_00282DD8(char *, char *, char *);
extern float func_00282DB0(char *, char *);
extern float func_002831B0(float);
extern float func_002703B0(int, float, float, float, float, float);
extern float func_00283198(float);
extern void func_00282F20(char *, char *, float);
extern float func_00283180(float);
extern void func_002ACDE8(char *, char *, char *);

void func_L00_00320B70(char *from, char *vec, char *to, int mode, float p0, float p1, float p2, char *side, float p3,
                       char *out)
{
    char delta[16];
    char axis[16];
    char quat[16];
    float length;
    float dot;
    float norm;
    float angle;
    float half;

    FastVecSub(delta, to, from);
    length = FastVecLength(delta);
    if (length == 0.0f)
        return;
    FastVecCross(axis, delta, vec);
    dot = FastVecDot(vec, delta);
    norm = FastVecLength(vec);
    norm *= FastVecLength(delta);
    if (norm == 0.0f)
        return;
    angle = 1.5707964f - func_002831B0(dot / norm);
    if (angle > 2.8797936f) {
        FastVecCross(quat, vec, side);
        FastVecCross(axis, quat, vec);
        side = quat;
    } else {
        side = quat;
        if (length < p3 && angle < 1.5707965f) {
            p1 = 1.0f;
            p0 = 0.5f;
        }
    }
    half = func_002703B0(mode, 0.0f, angle, p0, p1, p2) * 0.5f;
    vec_scale_to_length(side, axis, func_00283198(half));
    *(float *)(quat + 12) = func_00283180(half);
    func_002ACDE8(vec, vec, side);
    if (out != 0)
        qcopy(out, side);
}
