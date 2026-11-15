#include "include_asm.h"
#include "names.h"

/* func_002B41A8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt). The default vectors
   are read-only constants (D_001AA090 serves two locals): their reads must not conflict with the
   store to obj+0x34, which retail schedules after the argument spills. The pointers are set
   before they are tested, and in another order: both orders reach the register allocator. */

extern void FastVecAdd(void *, void *, void *);

typedef int TI16_2B41A8 __attribute__((mode(TI)));
typedef struct { float x, y, z; } Vec3_2B41A8;
extern const Vec3_2B41A8 D_001AA060, D_001AA070, D_001AA080, D_001AA090, D_001AA0A0, D_001AA0B0;
extern float math_random_angle(void);
extern void matrix_mul_vec3(void *, void *, void *);

/* Fills in a movement controller block, using the given values or built-in defaults for each setting. */
void moby_init_controller_params(char *obj, char *dst, char *origin, char *rotation, float *p4, float *p5, float *p6, float *p7,
                   float *p8, float *p9, float *p10)
{
    Vec3_2B41A8 v0, v1, v2, v3, v4, v5, v6;
    float *a, *b, *c, *d, *e, *f, *g;
    float *o0, *o1, *o2, *o3, *o4, *o5, *o6, *o7;
    int i;
    v0 = D_001AA060;
    v1 = D_001AA070;
    v2 = D_001AA080;
    v3 = D_001AA090;
    v4 = D_001AA0A0;
    v5 = D_001AA090;
    *(unsigned short *)(obj + 0x34) |= 0x100;
    v6 = D_001AA0B0;
    if (origin != 0) {
        matrix_mul_vec3(dst, origin, obj + 0xC0);
        FastVecAdd(dst, dst, obj + 0x10);
        *(TI16_2B41A8 *)(dst + 0x10) = *(TI16_2B41A8 *)origin;
    } else {
        *(TI16_2B41A8 *)dst = *(TI16_2B41A8 *)(obj + 0x10);
    }
    if (rotation != 0) {
        *(TI16_2B41A8 *)(dst + 0x20) = *(TI16_2B41A8 *)rotation;
    } else {
        *(TI16_2B41A8 *)(dst + 0x20) = *(TI16_2B41A8 *)(obj + 0xF0);
    }
    f = (float *)&v5;
    g = (float *)&v6;
    d = (float *)&v3;
    e = (float *)&v4;
    b = (float *)&v1;
    a = (float *)&v0;
    c = (float *)&v2;
    if (p5) g = p5;
    if (p4) f = p4;
    if (p8) c = p8;
    if (p7) b = p7;
    if (p9) e = p9;
    if (p6) a = p6;
    if (p10) d = p10;
    o7 = (float *)(dst + 0x90);
    o6 = (float *)(dst + 0x9C);
    o5 = (float *)(dst + 0x84);
    o4 = (float *)(dst + 0x6C);
    o3 = (float *)(dst + 0x54);
    o2 = (float *)(dst + 0x60);
    o1 = (float *)(dst + 0x48);
    o0 = (float *)(dst + 0x78);
    for (i = 0; i < 3; i++) {
        *o0++ = *d++;
        *o1++ = *a++;
        *o2++ = *e++;
        *o3++ = *b++;
        *o4++ = *c++;
        *o5++ = math_random_angle();
        *o6++ = *f++;
        *o7++ = *g++ * 0.00029088825f;
    }
}
