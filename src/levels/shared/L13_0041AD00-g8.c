#include "names.h"
/* func_L13_0041AD00: electric beam draw (RAC1 draw_electric_beam shape).
 * Spill slots follow gcse's PRE hash-bucket order, S = (insns at gcse / 2) | 1;
 * retail's order needs S = 181. The set-once constant locals and copies of d
 * read inside the loops each add one insn at gcse and leave the final code
 * unchanged (cprop folds them); j is declared before n for the PRE numbering.
 */
#include "common.h"

typedef struct Pkt {
    float corner[4][4];
    unsigned int color[4];
    float uv[4][2];
    long zero;
    long tex;
    long state;
    long flags;
} Pkt;

typedef struct {
    int idx;
    char pad4[0x10];
    int color;
    unsigned char cnt[4];
    char pad1c[4];
    float pts[64][4];
    float seg[4][4][4];
} Beam;

extern void euler_to_matrix(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_clear_128(void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern char g_camera_l13_position[];
extern int g_electric_beam_texture __attribute__((sda));
extern int g_electric_beam_tex_flags_a __attribute__((sda));
extern int g_electric_beam_tex_flags_b __attribute__((sda));
extern int g_electric_beam_tex_flags_c __attribute__((sda));
extern int g_electric_beam_tex_flags_d __attribute__((sda));
extern float g_electric_beam_uv_table[4][2] SDATA(D_L13_001B1660);

/* Draws the electric beam as a few glowing strips running through its points. */
void gfx_draw_electric_beam(char *m) {
    Beam *d = *(Beam **)(m + 0x68);
    Pkt P[3];
    float M1[16] __attribute__((aligned(16)));
    float M2[16] __attribute__((aligned(16)));
    float v230[4] __attribute__((aligned(16)));
    float v240[4] __attribute__((aligned(16)));
    float v250[4] __attribute__((aligned(16)));
    float v260[4] __attribute__((aligned(16)));
    float v270[4] __attribute__((aligned(16)));
    long tex;
    long flags;
    int j;
    int n;
    int k;
    int c;
    int t;
    Beam *src = d;
    int corners = 4;

    euler_to_matrix(M1, (char *)d + 0x650);
    matrix_from_basis_rows(M2, M1);
    qcopy_nc(&M1[12], m + 0x10);
    FastVecSub(v230, g_camera_l13_position, m + 0x10);
    matrix_mul_vec3(v230, v230, M2);
    tex = GetEffectTextureDescriptor(g_electric_beam_texture);
    flags = (long)g_electric_beam_tex_flags_a;
    flags |= (long)g_electric_beam_tex_flags_b << 2;
    flags |= (long)g_electric_beam_tex_flags_c << 4;
    flags |= (long)g_electric_beam_tex_flags_d << 6;
    flags |= 0x8000L << 24;
    P[0].state = P[1].state = P[2].state = 0xFF9000000260L;
    P[0].tex = P[1].tex = P[2].tex = tex;
    P[0].zero = P[1].zero = P[2].zero = 0;
    P[0].flags = P[1].flags = P[2].flags = flags;
    for (t = 0; t < corners; t++) {
        float v = g_electric_beam_uv_table[t][1];
        int col;
        P[2].uv[t][1] = v;
        P[1].uv[t][1] = v;
        P[0].uv[t][1] = v;
        col = src->color;
        P[2].color[t] = col;
        P[1].color[t] = col;
        P[0].color[t] = col;
    }
    vec_clear_128(v250);
    {
        int i;
        int segs = 31;
        int last = 30;
        int kh = 2;
        int odd2 = 1;
        int odd = 1;
        int mode = 0;
        Beam *path = d;
        Beam *near = d;
        Beam *far = d;
        Beam *mid = d;
        Beam *ahead = d;
        for (i = 0; i < segs; i++) {
            qcopy(v240, v250);
            if (i < last) {
                FastVecSub(v270, path->pts[i], ahead->pts[i + 2]);
                FastVecSub(v260, mid->pts[i + 1], v230);
                FastVecCross(v250, v260, v270);
                vec_scale_to_length(v250, v250, 0.1f);
            } else {
                vec_clear_128(v250);
            }
            for (k = 0; k < 4; k++) {
                if (k < kh) {
                    qcopy(P[0].corner[k], near->pts[i]);
                    if (k & odd)
                        FastVecAdd(P[0].corner[k], P[0].corner[k], v240);
                    else
                        FastVecSub(P[0].corner[k], P[0].corner[k], v240);
                } else {
                    qcopy(P[0].corner[k], far->pts[i + 1]);
                    if (k & odd2)
                        FastVecAdd(P[0].corner[k], P[0].corner[k], v250);
                    else
                        FastVecSub(P[0].corner[k], P[0].corner[k], v250);
                }
                P[0].uv[k][0] = g_electric_beam_uv_table[k][0] + IntToFloat(i - i / 4 * 4) * 0.25f;
            }
            draw_world_quad(&P[0], M1, mode);
        }
    }
    {
        int beams = 4;
        int cmax = 0x1F;
        int rlast = 2;
        int kh2 = 2;
        int odd4 = 1;
        int odd3 = 1;
        int mode2 = 0;
        Beam *cnt = d;
        Beam *seg = d;
        int cnone = 0;
        Beam *near2 = d;
        Beam *mid2 = d;
        Beam *ahead2 = d;
        for (j = 0; j < beams; j++) {
            vec_clear_128(v250);
            c = cnt->cnt[j];
            if (c >= cmax)
                continue;
            if (c < cnone)
                continue;
            for (n = 0; n < 3; n++) {
                qcopy(v240, v250);
                if (n < rlast) {
                    FastVecSub(v270, seg->seg[n][j], ahead2->seg[n + 2][j]);
                    FastVecSub(v260, mid2->seg[n + 1][j], v230);
                    FastVecCross(v250, v260, v270);
                    vec_scale_to_length(v250, v250, 0.1f);
                } else {
                    vec_clear_128(v250);
                }
                if (n == 0)
                    qcopy(v240, v250);
                for (k = 0; k < 4; k++) {
                    if (k < kh2) {
                        qcopy(P[0].corner[k], near2->seg[n][j]);
                        if (k & odd3)
                            FastVecAdd(P[0].corner[k], P[0].corner[k], v240);
                        else
                            FastVecSub(P[0].corner[k], P[0].corner[k], v240);
                    } else {
                        qcopy(P[0].corner[k], d->seg[n + 1][j]);
                        if (k & odd4)
                            FastVecAdd(P[0].corner[k], P[0].corner[k], v250);
                        else
                            FastVecSub(P[0].corner[k], P[0].corner[k], v250);
                    }
                    P[0].uv[k][0] = g_electric_beam_uv_table[k][0] + IntToFloat(n - n / 4 * 4) * 0.25f;
                }
                draw_world_quad(&P[0], M1, mode2);
            }
        }
    }
}
