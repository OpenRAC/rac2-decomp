#include "names.h"
/* Builds one 16-byte record (a default value with two angles overwritten) and walks it through
   three helpers; the owner's second block supplies the radius. Needs -frac2-zero-ti-por. */
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Quad_3CA688;

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_draw_glow_quad(void *, int);
extern void DrawTaperedBeam(void *, char *, int, int, float, float);

/* Places a small glow effect in front of the object and starts a short effect at that spot. */
void part_spawn_glow_in_front(char *owner)
{
    Quad_3CA688 point;
    char *vars = *(char **)(owner + 0x68);

    point.q = 0;
    point.f[0] = -0.3f;
    point.f[3] = 1.0f;
    matrix_mul_vec3(&point, &point, owner + 0xC0);
    FastVecAdd(&point, &point, owner + 0x10);
    part_draw_glow_quad(&point, 0x103080);
    DrawTaperedBeam(&point, vars + 0x10, 0x103080, 4, *(float *)(vars + 0x64), 0.25f);
}
