#include "common.h"

extern char *D_L00_001B1844;
extern float D_L00_001B1650 __attribute__((sda));
extern float D_L00_001B1654 __attribute__((sda));
extern int D_L00_001B1658 __attribute__((sda));
extern char D_L00_001BF220[];
extern float FastVecLength(void *), IntToFloat(int);
extern float coll_project_point_on_segment(void *, void *, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Samples expanding collision spheres along a camera segment. A collision
   projects the contact onto that segment and shortens the requested endpoint. */
void cam_clamp_segment_by_collision(char *camera, char *out, char *start, char *end)
{
    float a[4], b[4], c[4], d[4], e[4], f[4];
    char *entry = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84) * 32 + 0x1c);
    float lo = D_L00_001B1650, hi = D_L00_001B1654;
    int count = D_L00_001B1658;
    float length;
    int i;
    qcopy(out, end);
    a[0] = *(float *)(entry + 0x30);
    a[3] = 0;
    a[2] = *(float *)(entry + 0x34);
    a[1] = 0;
    length = FastVecLength(a);
    for (i = 0; i < count; i++) {
        int hit;
        {
            float t, radius;
            t = IntToFloat(i) / IntToFloat(count - 1) * 0.9f + 0.1f;
            lerp_vector(b, start, end, t);
            radius = (hi - lo) * t;
            hit = coll_test_point(b, 16, *(void **)(entry + 0x20), lo + radius);
        }
        if (hit) {
            float t, radius;
            t = coll_project_point_on_segment(e, start, end, D_L00_001BF220);
            FastVecSub(f, e, D_L00_001BF220);
            radius = lo + (hi - lo) * t;
            if (FastVecLength(f) <= radius) {
                vec_scale_to_length(f, f, radius);
                FastVecAdd(f, D_L00_001BF220, f);
                FastVecSub(c, f, start);
                vec_scale_to_length(d, c, length);
                FastVecAdd(end, start, d);
                qcopy(out, end);
            }
        }
    }
}
