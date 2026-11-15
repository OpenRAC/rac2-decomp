#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern char g_hero_position[];
extern int D_L00_001A8FF0 __attribute__((sda));
extern char D_0018A0E0[];
extern char *g_hero_moby;
extern void vec_scale_to_length(char *, void *, float);
extern void FastVecAdd(char *, char *, char *);
extern void coll_push_vector_from_negative_axes(char *, char *);

void BuildOffsetVectorPair(char *first, char *second, float x, float y, int mode)
{
    char buffer[16] __attribute__((aligned(16)));
    Quad work;
    char *p;
    float r;

    if (mode) {
        if (D_L00_001A8FF0)
            vec_scale_to_length(buffer, D_0018A0E0, -y);
        else
            vec_scale_to_length(buffer, g_hero_moby + 0xe0, y);
        p = (char *)&g_hero_position;
        FastVecAdd(second, p, buffer);
        if (D_L00_001A8FF0)
            vec_scale_to_length(buffer, p + 0x240, -x);
        else
            vec_scale_to_length(buffer, *(char **)(p + 0x2210) + 0xe0, x);
        FastVecAdd(first, (char *)&g_hero_position, buffer);
        work = *(Quad *)first;
        coll_push_vector_from_negative_axes((char *)&work, second);
    } else {
        qcopy(buffer, &g_hero_position);
        qcopy(second, buffer);
        r = *(float *)(second + 8) + y;
        *(float *)(second + 8) = r;
        if (r < 0.0f)
            *(float *)(second + 8) = 0.0f;
        qcopy(first, buffer);
        *(float *)(first + 8) += x;
    }
}
