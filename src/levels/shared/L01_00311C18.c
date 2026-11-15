#include "include_asm.h"
#include "names.h"
typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_fabs(float);

/* Finds the point on a line segment that is closest to a given point and writes it out. Returns how far along the line the point falls. */
float math_closest_point_on_segment(Vector16 *out, Vector16 *start,
                      Vector16 *end, Vector16 *point)
{
    Vector16 edge, relative, other, perpendicular;
    float determinant, t, fraction;
    FastVecSub(&edge, end, start);
    FastVecSub(&other, start, point);
    /* This planar construction defines x/y only; retail leaves the other lanes. */
    perpendicular.f[0] = edge.f[1];
    perpendicular.f[1] = -edge.f[0];
    FastVecAdd(&perpendicular, point, &perpendicular);
    FastVecSub(&relative, point, &perpendicular);
    determinant = edge.f[1] * relative.f[0] - edge.f[0] * relative.f[1];
    if (math_fabs(determinant) < 0.0001f) {
        out->q = start->q;
        return 0.0f;
    }
    determinant = 1.0f / determinant;
    t = (relative.f[1] * other.f[0] - relative.f[0] * other.f[1]) * determinant;
    fraction = t < 0.0f ? 0.0f : t;
    fraction = fraction > 1.0f ? 1.0f : fraction;
    FastVecScale(out, &edge, fraction);
    FastVecAdd(out, out, start);
    return t;
}
