/* functional: medium. Written from the assembly: plain floats, the scratch vectors are one local array as on retail's stack; the dead stores retail makes to a stack record (the packet words at sp+272..304) are left out, the calls that produce them are kept; the roles of the draw helpers (func_002FC560 sets a GS register, func_00281810 submits vertices) and of the data words are taken from their use here. */

extern int D_0018C0B4;
extern int D_L09_001A8A48;
extern int D_001A79F0;                      /* the level number */
extern char D_L09_001BDF00[];               /* two floats at +552/+556 are changed for the draw and restored */
extern float D_L09_001B9C30[];              /* a matrix */
extern float D_L09_001B9A00[4];             /* the eye */
extern float D_L09_001B3120;
extern float D_L09_001B3110[4];             /* two (u, v) offsets */
extern float D_L09_001AEC38[2];             /* two scales */
extern int D_L09_002339A0[12];              /* 6 pairs of colours */
extern float D_L09_002336A0[36];            /* 6 pairs of points */
extern int D_L09_00233EA0[24];              /* 6 pairs of zero texture coordinates */
extern float D_L09_00233AA0[64 * 3];        /* the cell vertices */
extern int D_L09_00233DA0[64];              /* their colours */
extern float D_L09_002340A0[64 * 2];        /* their texture coordinates */

extern void func_002FC560(unsigned int, unsigned long);
extern unsigned long func_0027C878(int);
extern void func_00280328(void);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern void func_00282D30(void *, void *, float);
extern void func_00281810(int, void *, void *, void *, int);
extern float func_00282E20(void *);
extern void func_00282A28(void);

/* Draws a fan of screen-space strips for an object (`self`, its variables at +104): it sets the
   GS state, builds the four corners of a quad from two rotated axes, submits a 12-vertex strip
   whose colours blend the two colours at vars+0 and vars+4, and then, in two passes, covers a 4 by 4 grid
   of cells of size vars+24 around the eye with textured vertices whose colour fades with the
   distance from the eye. The two floats at D_L09_001BDF00+552/556 are set up front and restored. */
void func_L09_0037FCE8(char *self)
{
    char *vars = *(char **)(self + 104);
    float *state = (float *)(D_L09_001BDF00 + 552);
    float saved_a = state[0];
    float saved_b = state[1];
    float L[40];                    /* the stack vectors: 0 tmp, 4 tmp, 8 A, 12 B, 16 C, 20 E, 24 D, 28 F, 32 G, 36 H */
    float *tmp = L;
    float *tmp2 = L + 4;
    float *A = L + 8;
    float *B = L + 12;
    float *C = L + 16;
    float *E = L + 20;
    float *D = L + 24;
    float *F = L + 28;
    float *G = L + 32;
    float *H = L + 36;
    float *corner;
    int c0, c1;
    int i, k, n;
    float r, f20, f21, g, ox, oy, zbase;

    if (D_0018C0B4 != 28) {
        if (D_L09_001A8A48 == 0) {
            state[0] = 255.0f;
            state[1] = 249.9f;
        }
    }

    func_002FC560(66, (0xC800UL << 22) | 0x44);
    func_002FC560(8, 0);
    func_002FC560(20, (0xFF90UL << 32) | 0x260);
    if (*(int *)(vars + 56) != 0) {
        func_002FC560(71, 0x5310B);
    } else {
        func_002FC560(71, 0x513F1);
    }
    func_002FC560(6, func_0027C878(22));
    func_00280328();

    A[0] = 1.0f;
    A[1] = 0.0f;
    A[2] = 0.0f;
    A[3] = 1.0f;
    func_00283098(A, A, D_L09_001B9C30);
    B[0] = 0.0f;
    B[1] = 1.0f;
    B[2] = 0.0f;
    B[3] = 1.0f;
    func_00283098(B, B, D_L09_001B9C30);
    if (D_001A79F0 != 13) {
        A[2] = 0.0f;
    }
    func_00282F20(A, A, 1.0f);
    if (D_001A79F0 != 13) {
        B[2] = 0.0f;
    }
    func_00282F20(B, B, 1.0f);

    func_00282F20(tmp, A, -75.0f);
    func_00282F20(tmp2, B, -87.0f);
    func_00282CC0(C, tmp, tmp2);
    func_00282F20(tmp2, B, 87.0f);
    func_00282CC0(D, tmp, tmp2);
    func_00282F20(tmp, A, *(float *)(vars + 40));
    func_00282F20(tmp2, B, -750.0f);
    func_00282CC0(E, tmp, tmp2);
    func_00282F20(tmp2, B, 750.0f);
    func_00282CC0(F, tmp, tmp2);
    corner = C;
    for (i = 0; i < 4; i++) {
        func_00282CC0(corner, corner, D_L09_001B9A00);
        corner[2] = D_L09_001B3120;
        corner += 4;
    }
    func_00282CF0(G, E, C);
    func_00282CF0(H, F, D);

    for (k = 0; k < 12; k += 2) {
        int color;

        f20 = func_00283CE0(k) * 0.1f;
        color = func_00283D38(*(int *)vars, *(int *)(vars + 4), func_00283CE0(k) / 10.0f);
        i = k / 2;
        func_00282D30(tmp, G, f20);
        D_L09_002339A0[i * 2] = color;
        D_L09_00233EA0[i * 4] = 0;
        D_L09_00233EA0[i * 4 + 1] = 0;
        func_00282CC0(tmp, tmp, C);
        D_L09_002336A0[i * 6] = tmp[0];
        D_L09_002336A0[i * 6 + 1] = tmp[1];
        D_L09_002336A0[i * 6 + 2] = tmp[2];
        func_00282D30(tmp, H, f20);
        D_L09_002339A0[i * 2 + 1] = color;
        D_L09_00233EA0[i * 4 + 2] = 0;
        D_L09_00233EA0[i * 4 + 3] = 0;
        func_00282CC0(tmp, tmp, D);
        D_L09_002336A0[i * 6 + 3] = tmp[0];
        D_L09_002336A0[i * 6 + 4] = tmp[1];
        D_L09_002336A0[i * 6 + 5] = tmp[2];
    }
    func_00281810(12, D_L09_002336A0, D_L09_002339A0, D_L09_00233EA0, 1);

    func_0027C878(22);
    func_002FC560(66, 0x8000000048UL);
    func_002FC560(8, 0);
    func_002FC560(20, (0xFF90UL << 32) | 0x260);
    func_002FC560(71, 0x513F1);
    c0 = func_00283D38(0, *(int *)(vars + 12), 1.0f);
    c1 = func_00283D38(0, *(int *)(vars + 16), 1.0f);

    for (i = 0; i < 2; i++) {
        func_002FC560(6, func_0027C878(*(int *)(vars + 28) + i + 63));
        r = *(float *)(vars + 24);
        f21 = r * -2.0f;
        if (f21 < r + r) {
            do {
                n = 0;
                f20 = r * -2.0f;
                if (f20 < r + r) {
                    g = D_L09_001AEC38[i];
                    ox = D_L09_001B3110[i * 2];
                    oy = D_L09_001B3110[i * 2 + 1];
                    zbase = D_L09_001B3120 + (float)(i + 1) * 0.05f;
                    do {
                        int j;

                        for (j = 0; j < 4; j++) {
                            float x = (j >= 2) ? f20 + r : f20;
                            float y = (j & 1) ? f21 + r : f21;

                            D_L09_002340A0[(n + j) * 2] = (x / (r + r)) * g + ox;
                            D_L09_002340A0[(n + j) * 2 + 1] = (y / (r + r)) * g + oy;
                            D_L09_00233AA0[(n + j) * 3] = x + D_L09_001B9A00[0] + 1.0f;
                            D_L09_00233AA0[(n + j) * 3 + 1] = y + D_L09_001B9A00[1] + 1.0f;
                            D_L09_00233AA0[(n + j) * 3 + 2] = zbase;
                        }
                        for (j = 0; j < 4; j++) {
                            float dist;

                            tmp[0] = D_L09_00233AA0[(n + j) * 3] - D_L09_001B9A00[0];
                            tmp[1] = D_L09_00233AA0[(n + j) * 3 + 1] - D_L09_001B9A00[1];
                            tmp[2] = D_L09_00233AA0[(n + j) * 3 + 2] - D_L09_001B9A00[2];
                            tmp[3] = 1.0f;
                            dist = func_00282E20(tmp) / (*(float *)(vars + 24) + *(float *)(vars + 24));
                            if (1.0f < dist) {
                                dist = 1.0f;
                            }
                            D_L09_00233DA0[n + j] = func_00283D38(c0, c1, dist);
                        }
                        n += 4;
                        if (!(n < 64)) {
                            func_00282A28();
                        }
                        r = *(float *)(vars + 24);
                        f20 += r;
                    } while (f20 < r + r);
                }
                func_00281810(n, D_L09_00233AA0, D_L09_00233DA0, D_L09_002340A0, 1);
                r = *(float *)(vars + 24);
                f21 += r;
            } while (f21 < r + r);
        }
    }

    state[0] = saved_a;
    state[1] = saved_b;
    func_002FC560(71, 0x5360B);
}
