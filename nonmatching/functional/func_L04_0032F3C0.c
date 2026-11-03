/* functional: high. unchecked: level 4 never calls it in the captures; only level 18's copy has states, and the logic is SAME there (gated through a test copy with level 18's names D_L18_001AD820/D_L18_001AD840/D_L18_001B9680 and the gate's sqrt stand-in). The names here are the addresses level 4's own copy forms (lui 0x1B -10208 = 0x1AD820, lui 0x1B -10176 = 0x1AD840, lui 0x1C -27328 = 0x1B9540; level 18 forms 0x1B9680 for the last). The four constant quadwords are read once at entry, as retail loads them into VU0 registers. Plain floats in place of VU0 code, in its order: cross products as vopmula/vopmsub (ACC = a.yzx*b.zxy, minus b.yzx*a.zxy), dot products as (x + y) + 1*z, vrsqrt as 1/sqrt(|x|), vmax/vmini against 0 and 1, vftoi0 truncation, ppach/ppacb keeping the low byte of each lane. Retail software-pipelines the neighbour loads one cell ahead and also reads the five words around cell 17 of each row (results unused); here each cell's words are read when it is processed. Retail's `qmtc2 zero,$vf0` writes the constant VU0 register and does nothing; its constant 1/128 in vf23 and 0xFFFFFF in t1 are never used. */
extern float sqrtf(float);
extern unsigned int D_L04_001AD820;
extern unsigned char D_L04_001AD840[];
extern unsigned char D_L04_001B9540[];

static float bits_0032F3C0(unsigned int u)
{
    union {
        unsigned int i;
        float f;
    } c;
    c.i = u;
    return c.f;
}

static int neg_0032F3C0(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

/* d = a x b as VU0 computes it: vopmula ACC, a, b; vopmsub d, b, a. */
static void cross_0032F3C0(float *d, const float *a, const float *b)
{
    float x = a[1] * b[2], y = a[2] * b[0], z = a[0] * b[1];
    d[0] = x - b[1] * a[2];
    d[1] = y - b[2] * a[0];
    d[2] = z - b[0] * a[1];
}

/* Light a 17x17 water/height grid: heights are floats in scratchpad rows of 24 words from 0x70000070 (cell (i, j) at
   0x70000070 + 96 j + 4 i, neighbours at +-4 and +-96). For each cell, the normal from its four neighbours and the grid
   step D_L04_001AD840+0x10 (xy), the point (a0.x + D_L04_001AD840.z + i*step.x, a0.y + D_L04_001AD840.w + j*step.y, h + a0.z), the
   view vector to D_L04_001B9540+0x140 and the light row D_L04_001AD870 give: a colour word (D_L04_001AD820's RGBA bytes times the
   clamped light term, alpha 0xFF) at 0x70001088 + 4n and an environment-map uv (reflected view, or the view itself when
   it faces away, xy * step.z * 0.5 + 0.5) at 0x70000780 + 8n. */
void func_L04_0032F3C0(void *origin)
{
    float *o = origin;
    unsigned int rgba;
    float v15[4], v16[4], v21[4], v20[4];
    float half = bits_0032F3C0(0x3F000000);
    float k = bits_0032F3C0(0x3F12B021);
    float gain = 1.0f + bits_0032F3C0(0x40500000);
    float col[4];
    float a10[3], a11[3], a12[3], a13[3];
    float o0, o1, o2;
    float px, py;
    unsigned char *row = (unsigned char *)0x70000070;
    float *uv = (float *)0x70000780;
    unsigned int *cw = (unsigned int *)0x70001088;
    int i, j, c;

    rgba = D_L04_001AD820;
    for (c = 0; c < 4; c++) {
        v15[c] = ((float *)(D_L04_001AD840 + 16))[c];
    }
    for (c = 0; c < 4; c++) {
        v16[c] = ((float *)D_L04_001AD840)[c];
    }
    for (c = 0; c < 4; c++) {
        v21[c] = ((float *)(D_L04_001AD840 + 48))[c];
    }
    for (c = 0; c < 4; c++) {
        v20[c] = ((float *)(D_L04_001B9540 + 320))[c];
    }
    col[0] = (float)(int)(rgba & 0xFF);
    col[1] = (float)(int)((rgba >> 8) & 0xFF);
    col[2] = (float)(int)((rgba >> 16) & 0xFF);
    col[3] = (float)(int)((rgba >> 24) & 0xFF);
    a10[0] = 0.0f;
    a12[0] = 0.0f;
    a10[1] = 0.0f - v15[1];
    a11[1] = 0.0f + v15[1];
    a12[1] = 0.0f + v15[1];
    a13[1] = 0.0f - v15[1];
    a11[0] = 0.0f - v15[0];
    a13[0] = 0.0f + v15[0];
    o0 = o[0];
    o1 = o[1];
    o2 = o[2];
    py = o1 + v16[3];
    for (j = 0; j < 17; j++) {
        float *h = (float *)row;

        px = o0 + v16[2];
        for (i = 0; i < 17; i++) {
            float hc = h[0], hl = h[-1], hr = h[1], hu = h[-24], hd = h[24];
            float n[3], n2[3], v[3], m[3], r[3];
            float t, q, l, d, pz;
            int ci[4];

            h++;
            hc = 0.0f + hc;
            a10[2] = hc - hd;
            a11[2] = hd - hr;
            a12[2] = hc - hu;
            a13[2] = hu - hl;
            cross_0032F3C0(n, a11, a10);
            cross_0032F3C0(n2, a13, a12);
            for (c = 0; c < 3; c++) {
                n[c] = n[c] + n2[c];
            }
            t = n[0] * n[0] + n[1] * n[1];
            t = t + 1.0f * (n[2] * n[2]);
            if (t < 0.0f) {
                t = -t;
            }
            q = 1.0f / sqrtf(t);
            pz = hc + o2;
            for (c = 0; c < 3; c++) {
                n[c] = n[c] * q;
            }
            v[0] = v20[0] - px;
            v[1] = v20[1] - py;
            v[2] = v20[2] - pz;
            for (c = 0; c < 3; c++) {
                n[c] = 0.0f - n[c];
            }
            t = v[0] * v[0] + v[1] * v[1];
            t = t + 1.0f * (v[2] * v[2]);
            if (t < 0.0f) {
                t = -t;
            }
            q = 1.0f / sqrtf(t);
            l = v21[0] * n[0] + v21[1] * n[1];
            l = l + 1.0f * (v21[2] * n[2]);
            l = l - k;
            l = l * gain;
            l = l + k;
            l = l + half;
            l = (l > 0.0f) ? l : 0.0f;
            l = (l < 1.0f) ? l : 1.0f;
            for (c = 0; c < 3; c++) {
                v[c] = v[c] * q;
            }
            for (c = 0; c < 4; c++) {
                ci[c] = (int)(col[c] * l);
            }
            for (c = 0; c < 3; c++) {
                m[c] = 0.0f - v[c];
            }
            d = m[0] * n[0] + m[1] * n[1];
            d = d + 1.0f * (m[2] * n[2]);
            for (c = 0; c < 3; c++) {
                r[c] = n[c] * d;
                r[c] = r[c] - m[c];
            }
            if (!neg_0032F3C0(d)) {
                for (c = 0; c < 3; c++) {
                    r[c] = r[c] + r[c];
                    v[c] = m[c] + r[c];
                }
            }
            v[0] = v[0] * v15[2];
            v[1] = v[1] * v15[2];
            v[0] = v[0] * half;
            v[1] = v[1] * half;
            v[0] = v[0] + half;
            v[1] = v[1] + half;
            *cw = 0xFF000000u | (unsigned int)(ci[0] & 0xFF) | ((unsigned int)(ci[1] & 0xFF) << 8) | ((unsigned int)(ci[2] & 0xFF) << 16) | ((unsigned int)(ci[3] & 0xFF) << 24);
            uv[0] = v[0];
            uv[1] = v[1];
            px = px + v15[0];
            cw++;
            uv += 2;
        }
        py = py + v15[1];
        row += 96;
    }
}
