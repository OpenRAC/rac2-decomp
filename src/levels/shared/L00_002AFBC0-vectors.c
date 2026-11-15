#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern char D_00189EA0[];
extern int D_L00_001A8FF0 __attribute__((sda));
extern char D_0018A0E0[];
extern char *D_0018C0B0;
extern void func_00282F20(char *, void *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_L00_0031EC88(char *, char *);

void func_L00_002B47A8(char *first, char *second, float x, float y, int mode)
{
    char buffer[16] __attribute__((aligned(16)));
    Quad work;
    char *p;
    float r;

    if (mode) {
        if (D_L00_001A8FF0)
            vec_scale_to_length(buffer, D_0018A0E0, -y);
        else
            vec_scale_to_length(buffer, D_0018C0B0 + 0xe0, y);
        p = (char *)&D_00189EA0;
        FastVecAdd(second, p, buffer);
        if (D_L00_001A8FF0)
            vec_scale_to_length(buffer, p + 0x240, -x);
        else
            vec_scale_to_length(buffer, *(char **)(p + 0x2210) + 0xe0, x);
        FastVecAdd(first, (char *)&D_00189EA0, buffer);
        work = *(Quad *)first;
        func_L00_0031EC88((char *)&work, second);
    } else {
        qcopy(buffer, &D_00189EA0);
        qcopy(second, buffer);
        r = *(float *)(second + 8) + y;
        *(float *)(second + 8) = r;
        if (r < 0.0f)
            *(float *)(second + 8) = 0.0f;
        qcopy(first, buffer);
        *(float *)(first + 8) += x;
    }
}
