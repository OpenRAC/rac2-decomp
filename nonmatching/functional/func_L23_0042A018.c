/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * GPT-6.1 Sol high, 2026-10-29: USA v1.01, 1052/1052 bytes, 0/1 places.
 * Standalone L23_0042A018-g8.c, -O2 -G8 -ffunction-sections -g
 * -frac2-hazard-labels. Other releases were not checked this time.
 * 19 instruction rows remain: the alpha addition swaps its source registers at
 * +0x130; color allocation and outer-loop setup differ at +0x22C..+0x274.
 * qzero_nc fixes the matrix/state lifetime and argument-address regeneration;
 * the first three independent matrix rows use qcopy_nc, while the fourth uses
 * qcopy because its W component is overwritten. The grouped first ALPHA pair
 * fixes the load/shift schedule. -g plus hazard-labels fixes the division guard.
 * Explicit UV start pointers, 2D pointers and named U/V fields tie. Reversing
 * alpha addition changes its load/result registers; unsigned addition ties.
 * MACRO_ADDR on the UV table changes its hoisted base and worsens the loop.
 * Reopen with new color/loop lifetime evidence; retained packet/matrix extents
 * are unchanged. This is closer than the historical 25 October draft.
 * Required declarations follow below; no custom helper or volatile cast.
 */
#include "common.h"

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

extern float func_00283B98(float, float);

extern float func_00283198(float);

extern float func_00283180(float);

extern float func_00283C28(float);

extern float func_002A7878(float, float);

extern long long func_0027C878(s32);

extern void func_002FC560(u32, u64);

extern void func_00282D30(void *, void *, float);

extern void func_002833F0(void *, void *);

extern void func_00283738(void *, void *, void *);

extern void func_00280B90(void *, void *, s32);

/* updates the spin state at +0x68 and draws 72 quads of four corners each (corner positions from
   one table, uv from another; the colour and two GS words sit in the packet), the packet's matrix
   being the object's rotation rows turned about the spin angle */
void func_L23_0042A018(u8 *moby) {
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

    if (D_L23_001B1484_2 != 0) {
        vars = *(L23Spin **)(moby + 0x68);
        D_L23_001B39D0 = D_L23_001B1470 * 1.1f;
        vars->turn = func_00283B98(vars->turn, (float)D_L23_001B1480 * 0.00029088825f);
        f = func_00283198((float)(*(u16 *)(moby + 0x96) % D_L23_001B1474) * (1.0f / (float)D_L23_001B1474) * 3.1415927f);
        vars->alpha = D_L23_001B147C + (s32)(f * D_L23_001B1478);
        reg = D_L23_001B1BAC | ((s64)D_L23_001B1BB0 << 2);
        reg |= (s64)D_L23_001B1BB4 << 4;
        reg |= (s64)D_L23_001B1BB8 << 6;
        reg |= (s64)vars->alpha << 32;
        pkt.tail[3] = reg;
        tex = func_0027C878(D_L23_001B1BC0);
        pkt.tail[2] = 0xFF9000000260LL;
        pkt.tail[1] = tex;
        pkt.tail[0] = 0;
        func_002FC560(0x47, 0x53001);
        /* The first three rows are independent stack writes until the matrix calls.
         * Row four keeps qcopy because C overwrites its w field immediately. */
        hero = D_L23_001B1484_2;
        qcopy_nc(&m[0], hero + 0xC0);
        qcopy_nc(&m[1], hero + 0xD0);
        qcopy_nc(&m[2], hero + 0xE0);
        qcopy(&m[3], hero + 0x10);
        ((float *)&m[3])[3] = 1.0f;
        qzero_nc(axis);
        ((float *)axis)[2] = vars->turn;
        func_002833F0(rot, axis);
        func_00283738(m, m, rot);
        if (D_L23_001B3714 == 0) {
            col = (vars->alpha << 24) + (D_L23_001B1BC4 & 0xFFFFFF);
        } else {
            col = (vars->alpha << 24) + (D_L23_001B1BC8 & 0xFFFFFF);
        }
        pkt.col[3] = col;
        pkt.col[2] = col;
        pkt.col[1] = col;
        pkt.col[0] = col;
        for (i = 0; i < 0x48; i++) {
            L23Corner *e = D_L23_002A68D0[i];
            float *uvy = &pkt.uv[0][1];
            float *uvx = &pkt.uv[0][0];
            TI16 *pos = pkt.pos;

            for (k = 3; k >= 0; k--) {
                s32 b = e->b;

                func_00282D30(pos, &D_L23_002A6390[e->a], D_L23_001B39D0);
                vars->spin = func_00283B98(vars->spin, D_L23_001B1BCC * 0.00029088825f);
                func_00283C28(vars->spin);
                if (D_L23_001B3714 == 0) {
                    fa = func_00283180(vars->spin) * D_L23_001B1BD8;
                    fb = func_00283198(vars->spin) * D_L23_001B1BDC;
                    fc = func_00283180(vars->spin) * D_L23_001B1BE0;
                    fd = func_00283198(vars->spin) * D_L23_001B1BE4;
                } else {
                    fa = func_00283180(vars->spin) * D_L23_001B1BF0;
                    fb = func_00283198(vars->spin) * D_L23_001B1BF4;
                    fc = func_00283180(vars->spin) * D_L23_001B1BF8;
                    fd = func_00283198(vars->spin) * D_L23_001B1BFC;
                }
                f = func_002A7878(D_L23_001B1BD0, D_L23_001B1BD4);
                *uvx = (D_L23_002A6D50[b][0] * fa + fb) * f;
                *uvy = D_L23_002A6D50[b][1] * fc + fd;
                pos++;
                e++;
                uvx += 2;
                uvy += 2;
            }
            func_00280B90(&pkt, m, 0);
        }
    }
}
