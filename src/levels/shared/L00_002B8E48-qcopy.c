#include "names.h"
typedef struct { float x, y, z, w; } Vec4_L00_002B8E48;

typedef int V4_L00_002B8E48 __attribute__((mode(TI)));

extern float func_00282C10(float);

extern float func_00283248(float, float);

extern void func_00283410(void *, void *);

extern void func_00283698(void *, void *);

extern void func_002830C0(void *, void *, void *);

extern void *g_pHeroMoby;

/* Turns a direction into the hero's own frame and gives back two angles (up/down and left/right) toward it. */
void func_L00_002B8E48(Vec4_L00_002B8E48 *in, float *out)
{
    Vec4_L00_002B8E48 first[4];
    Vec4_L00_002B8E48 second[4];
    Vec4_L00_002B8E48 vector;
    Vec4_L00_002B8E48 *vp = &vector;

    *(volatile V4_L00_002B8E48 *)vp = *(V4_L00_002B8E48 *)in;
    euler_to_matrix(first, (char *)g_pHeroMoby + 0xF0);
    matrix_from_basis_rows(second, first);
    transform_vector(vp, vp, second);
    out[0] = FastMatrixHelperA(square_root(vector.x * vector.x + vector.z * vector.z), vector.y);
    out[1] = -FastMatrixHelperA(vector.z, vector.x);
}
