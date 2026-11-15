/* func_PAL_L23_0042F560, the PAL copy of func_L23_0042A018: the same C. */
#include "common.h"

/* func_PAL_L23_0042F560 is a unit of its own: it reads its globals through $gp (-G8) and needs
 * -frac2-hazard-labels (see config/cflags.txt). */

typedef int TI16 __attribute__((mode(TI)));

/* the state object word, read through an absolute access */
extern u8 *D_L23_001B1484_2;

extern float D_L23_001B1470;

extern float D_L23_001B1478;

extern s32 D_L23_001B1474;

extern s32 D_L23_001B1480;

extern s32 D_L23_001B147C;

extern float D_L23_001B39D0;

extern s32 D_L23_001B3714;

extern s32 D_L23_001B1BAC __attribute__((sda));

extern s32 D_L23_001B1BB0 __attribute__((sda));

extern s32 D_L23_001B1BB4 __attribute__((sda));

extern s32 D_L23_001B1BB8 __attribute__((sda));

extern s32 D_L23_001B1BC0 __attribute__((sda));

extern s32 D_L23_001B1BC4 __attribute__((sda));

extern s32 D_L23_001B1BC8 __attribute__((sda));

extern float D_L23_001B1BCC __attribute__((sda));

extern float D_L23_001B1BD0 __attribute__((sda));

extern float D_L23_001B1BD4 __attribute__((sda));

extern float D_L23_001B1BD8 __attribute__((sda));

extern float D_L23_001B1BDC __attribute__((sda));

extern float D_L23_001B1BE0 __attribute__((sda));

extern float D_L23_001B1BE4 __attribute__((sda));

extern float D_L23_001B1BF0 __attribute__((sda));

extern float D_L23_001B1BF4 __attribute__((sda));

extern float D_L23_001B1BF8 __attribute__((sda));

extern float D_L23_001B1BFC __attribute__((sda));

/* the quad record handed to the draw helper */
typedef struct {
    TI16 pos[4];
    u32 col[4];
    float uv[4][2];
    s64 tail[4];
} L23Quad;

/* the spin state at object + 0x68 */
typedef struct {
    float turn;
    s32 alpha;
    float spin;
} L23Spin;

typedef struct {
    s16 a;
    s16 b;
} L23Corner;

extern L23Corner D_L23_002A68D0[][4];

extern TI16 D_L23_002A6390[];

extern float D_L23_002A6D50[][2];

extern float FastAddRotations(float, float);

extern float math_fast_sin_or_cos_b(float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_float_g(float);

extern float math_random_float_range(float, float);

extern long long GetEffectTextureDescriptor(s32);

extern void VU1_addGSregister(u32, u64);

extern void FastVecScale(void *, void *, float);

extern void euler_rotation_basis(void *, void *);

extern void multiply_matrix3x3(void *, void *, void *);

extern void draw_world_quad(void *, void *, s32);

/* updates the spin state at +0x68 and draws 72 quads of four corners each (corner positions from
   one table, uv from another; the colour and two GS words sit in the packet), the packet's matrix
   being the object's rotation rows turned about the spin angle */
void func_PAL_L23_0042F560(u8 *moby) {
    L23Spin *vars;
    L23Quad pkt;
    TI16 m[4];
    TI16 axis[1];
    TI16 rot[3];
    float f;
    float fa;
    float fb;
    float fc;
    float fd;
    s32 i;
    u8 *hero;
    s32 k;
    u32 col;
    s64 reg;
    s64 tex;
    float *uvy0;
    float *uvx0;

    if (D_L23_001B1484_2 != 0) {
        vars = *(L23Spin **)(moby + 0x68);
        D_L23_001B39D0 = D_L23_001B1470 * 1.1f;
        vars->turn = FastAddRotations(vars->turn, (float)D_L23_001B1480 * 0.0003490659f);
        f = math_fast_sin_or_cos_b((float)(*(u16 *)(moby + 0x96) % D_L23_001B1474) * (1.0f / (float)D_L23_001B1474) * 3.1415927f);
        vars->alpha = (s32)(f * D_L23_001B1478);
        vars->alpha += D_L23_001B147C;
        reg = D_L23_001B1BAC | ((s64)D_L23_001B1BB0 << 2);
        reg |= (s64)D_L23_001B1BB4 << 4;
        reg |= (s64)D_L23_001B1BB8 << 6;
        reg |= (s64)vars->alpha << 32;
        pkt.tail[3] = reg;
        tex = GetEffectTextureDescriptor(D_L23_001B1BC0);
        pkt.tail[2] = 0xFF9000000260LL;
        pkt.tail[1] = tex;
        pkt.tail[0] = 0;
        VU1_addGSregister(0x47, 0x53001);
        hero = D_L23_001B1484_2;
        qcopy_nc(&m[0], hero + 0xC0);
        qcopy_nc(&m[1], hero + 0xD0);
        qcopy_nc(&m[2], hero + 0xE0);
        qcopy(&m[3], hero + 0x10);
        ((float *)&m[3])[3] = 1.0f;
        qzero_nc(axis);
        ((float *)axis)[2] = vars->turn;
        euler_rotation_basis(rot, axis);
        multiply_matrix3x3(m, m, rot);
        if (D_L23_001B3714 == 0) {
            col = (vars->alpha << 24) + (D_L23_001B1BC4 & 0xFFFFFF);
            pkt.col[3] = col;
            pkt.col[2] = col;
            pkt.col[1] = col;
            pkt.col[0] = col;
        } else {
            col = (vars->alpha << 24) + (D_L23_001B1BC8 & 0xFFFFFF);
            pkt.col[3] = col;
            pkt.col[2] = col;
            pkt.col[1] = col;
            pkt.col[0] = col;
        }
        for (i = 0, uvx0 = &pkt.uv[0][0], uvy0 = &pkt.uv[0][1]; i < 0x48; i++) {
            L23Corner (*tab)[4] = D_L23_002A68D0;
            L23Corner *e = tab[i];
            float *uvy = uvy0;
            float *uvx = uvx0;
            TI16 *pos = pkt.pos;

            for (k = 3; k >= 0; k--) {
                s32 b = e->b;

                FastVecScale(pos, &D_L23_002A6390[e->a], D_L23_001B39D0);
                vars->spin = FastAddRotations(vars->spin, D_L23_001B1BCC * 0.0003490659f);
                math_fast_float_g(vars->spin);
                if (D_L23_001B3714 == 0) {
                    fa = math_fast_sin_or_cos_a(vars->spin) * D_L23_001B1BD8;
                    fb = math_fast_sin_or_cos_b(vars->spin) * D_L23_001B1BDC;
                    fc = math_fast_sin_or_cos_a(vars->spin) * D_L23_001B1BE0;
                    fd = math_fast_sin_or_cos_b(vars->spin) * D_L23_001B1BE4;
                } else {
                    fa = math_fast_sin_or_cos_a(vars->spin) * D_L23_001B1BF0;
                    fb = math_fast_sin_or_cos_b(vars->spin) * D_L23_001B1BF4;
                    fc = math_fast_sin_or_cos_a(vars->spin) * D_L23_001B1BF8;
                    fd = math_fast_sin_or_cos_b(vars->spin) * D_L23_001B1BFC;
                }
                f = math_random_float_range(D_L23_001B1BD0, D_L23_001B1BD4);
                *uvx = (D_L23_002A6D50[b][0] * fa + fb) * f;
                *uvy = D_L23_002A6D50[b][1] * fc + fd;
                pos++;
                e++;
                uvx += 2;
                uvy += 2;
            }
            draw_world_quad(&pkt, m, 0);
        }
    }
}
