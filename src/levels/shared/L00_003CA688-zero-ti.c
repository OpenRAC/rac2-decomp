#include "names.h"
/* Builds one 16-byte record (a default value with two angles overwritten) and walks it through
   three helpers; the owner's second block supplies the radius. Needs -frac2-zero-ti-por. */
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Quad_3CA688;

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_002EC608(void *, int);
extern void func_L00_002EC970(void *, char *, int, int, float, float);

/* Places a small glow effect in front of the object and starts a short effect at that spot. */
void func_L00_003CA688(char *owner)
{
    Quad_3CA688 point;
    char *vars = *(char **)(owner + 0x68);

    point.q = 0;
    point.f[0] = -0.3f;
    point.f[3] = 1.0f;
    matrix_mul_vec3(&point, &point, owner + 0xC0);
    FastVecAdd(&point, &point, owner + 0x10);
    DrawGlowQuad_L00(&point, 0x103080);
    DrawTaperedBeam(&point, vars + 0x10, 0x103080, 4, *(float *)(vars + 0x64), 0.25f);
}
