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

extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern char D_L13_001B98C0[];
extern int D_L13_001B163C __attribute__((sda));
extern int D_L13_001B1640 __attribute__((sda));
extern int D_L13_001B1644 __attribute__((sda));
extern int D_L13_001B1648 __attribute__((sda));
extern int D_L13_001B164C __attribute__((sda));
extern float D_L13_001B1660[4][2] SDATA(D_L13_001B1660);

void func_L13_0041AD00(char *m) {
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

    func_00283410(M1, (char *)d + 0x650);
    func_00283698(M2, M1);
    qcopy_nc(&M1[12], m + 0x10);
    func_00282CF0(v230, D_L13_001B98C0, m + 0x10);
    func_00283098(v230, v230, M2);
    tex = func_0027C878(D_L13_001B163C);
    flags = (long)D_L13_001B1640;
    flags |= (long)D_L13_001B1644 << 2;
    flags |= (long)D_L13_001B1648 << 4;
    flags |= (long)D_L13_001B164C << 6;
    flags |= 0x8000L << 24;
    P[0].state = P[1].state = P[2].state = 0xFF9000000260L;
    P[0].tex = P[1].tex = P[2].tex = tex;
    P[0].zero = P[1].zero = P[2].zero = 0;
    P[0].flags = P[1].flags = P[2].flags = flags;
    for (t = 0; t < corners; t++) {
        float v = D_L13_001B1660[t][1];
        int col;
        P[2].uv[t][1] = v;
        P[1].uv[t][1] = v;
        P[0].uv[t][1] = v;
        col = src->color;
        P[2].color[t] = col;
        P[1].color[t] = col;
        P[0].color[t] = col;
    }
    func_00282C88(v250);
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
                func_00282CF0(v270, path->pts[i], ahead->pts[i + 2]);
                func_00282CF0(v260, mid->pts[i + 1], v230);
                func_00282DD8(v250, v260, v270);
                func_00282F20(v250, v250, 0.1f);
            } else {
                func_00282C88(v250);
            }
            for (k = 0; k < 4; k++) {
                if (k < kh) {
                    qcopy(P[0].corner[k], near->pts[i]);
                    if (k & odd)
                        func_00282CC0(P[0].corner[k], P[0].corner[k], v240);
                    else
                        func_00282CF0(P[0].corner[k], P[0].corner[k], v240);
                } else {
                    qcopy(P[0].corner[k], far->pts[i + 1]);
                    if (k & odd2)
                        func_00282CC0(P[0].corner[k], P[0].corner[k], v250);
                    else
                        func_00282CF0(P[0].corner[k], P[0].corner[k], v250);
                }
                P[0].uv[k][0] = D_L13_001B1660[k][0] + func_00283CE0(i - i / 4 * 4) * 0.25f;
            }
            func_00280B90(&P[0], M1, mode);
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
            func_00282C88(v250);
            c = cnt->cnt[j];
            if (c >= cmax)
                continue;
            if (c < cnone)
                continue;
            for (n = 0; n < 3; n++) {
                qcopy(v240, v250);
                if (n < rlast) {
                    func_00282CF0(v270, seg->seg[n][j], ahead2->seg[n + 2][j]);
                    func_00282CF0(v260, mid2->seg[n + 1][j], v230);
                    func_00282DD8(v250, v260, v270);
                    func_00282F20(v250, v250, 0.1f);
                } else {
                    func_00282C88(v250);
                }
                if (n == 0)
                    qcopy(v240, v250);
                for (k = 0; k < 4; k++) {
                    if (k < kh2) {
                        qcopy(P[0].corner[k], near2->seg[n][j]);
                        if (k & odd3)
                            func_00282CC0(P[0].corner[k], P[0].corner[k], v240);
                        else
                            func_00282CF0(P[0].corner[k], P[0].corner[k], v240);
                    } else {
                        qcopy(P[0].corner[k], d->seg[n + 1][j]);
                        if (k & odd4)
                            func_00282CC0(P[0].corner[k], P[0].corner[k], v250);
                        else
                            func_00282CF0(P[0].corner[k], P[0].corner[k], v250);
                    }
                    P[0].uv[k][0] = D_L13_001B1660[k][0] + func_00283CE0(n - n / 4 * 4) * 0.25f;
                }
                func_00280B90(&P[0], M1, mode2);
            }
        }
    }
}
