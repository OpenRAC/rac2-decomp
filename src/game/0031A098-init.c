#include "common.h"

typedef int QuadA098 __attribute__((mode(TI)));
extern QuadA098 D_001AFAA0[4];

/* The four 16-byte blocks the record carries and scales. */
#ifndef RAC2_T_BLOCK_0031A340
#define RAC2_T_BLOCK_0031A340
typedef struct {
    float q[4];
} Block_0031a340;
#endif

/* The 240-byte record func_0031A340 builds: a scaled matrix, a colour, the
   looked-up handle, the fixed fields and the two computed vectors. */
#ifndef RAC2_T_LOC_0031A340
#define RAC2_T_LOC_0031A340
typedef struct {
    Block_0031a340 b0;
    Block_0031a340 b1;
    Block_0031a340 b2;
    Block_0031a340 b3;
    int k0;
    int k1;
    int k2;
    int k3;
    int z80;
    int z84;
    int z88;
    float f92;
    float f96;
    int z100;
    float f104;
    float f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float v192;
    float v196;
    float v200;
    float v204;
    float v208;
    float f212;
    float f216;
    float v220;
    float e0;
    float e1;
    float e2;
    float e3;
} Loc_0031a340;
#endif

/* Fills the record func_0031A340 builds: the four template blocks with their second
   and third components doubled, then the fixed fields. */
void func_0031A098(Loc_0031a340 *p)
{
    QuadA098 local[4];
    Block_0031a340 *src = (Block_0031a340 *)local;
    Block_0031a340 *out = &p->b0;
    int i;
    float scale = 2.0f;

    local[0] = D_001AFAA0[0];
    local[1] = D_001AFAA0[1];
    local[2] = D_001AFAA0[2];
    local[3] = D_001AFAA0[3];
    for (i = 3; i >= 0; i--) {
        qcopy(out, src);
        out->q[1] *= scale;
        out->q[2] *= scale;
        src++;
        out++;
    }
    p->v112 = 0;
    p->z80 = 0;
    p->z84 = 0;
    p->z88 = 0;
    p->f92 = 1.0f;
    p->f96 = 1.0f;
    p->z100 = 0;
    p->f104 = 1.0f;
    p->f108 = 1.0f;
    p->v128 = 0x0000FF9000000260LL;
}
