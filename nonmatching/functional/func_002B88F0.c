/* functional: medium. Pad frame update (parse the raw report into sticks, pressures, button edges, a 30-frame history) written from the retail assembly: same reads, writes and calls in retail order. The three-way left/right swap of word 0x1A0 stores 0 when neither bit is set, exactly as retail does. Float constants are the retail words (1/255 = 0x3B808081, 0.9f = 0x3F666666, 0.96 = 0x3F75BE0D). */
extern float func_00283CE0(int);
extern float func_00282E20(float *);
extern float func_00283248(float, float);
extern unsigned char D_001A7A44;
extern float func_00283C80(float, float);

void func_002B88F0(char *p, unsigned char *raw, int type) {
    int *w = (int *)p;
    float *f = (float *)p;
    float *hist_a = (float *)(p + 0x2D0);
    float *hist_b = (float *)(p + 0x258);
    int *hist_c = (int *)(p + 0x1E0);
    int s6 = type < 0x12;
    int i, k, v, t0, a0, a1, a2, a3, m;
    float f20, f21, d, x;
    unsigned char ub;

    v = ((raw[0] << 8) | raw[1]) ^ 0xFFFF;
    w[0x1B0 / 4] = v;
    w[0x1A0 / 4] = v;
    for (i = 0; i < 16; i++) {
        w[0x100 / 4 + i] = 0;
    }
    if (type >= 6) {
        for (i = 0; i < 4; i++) {
            a1 = raw[2 + i] - 0x7F;
            if (a1 < 0) {
                a1 = -a1;
            }
            if (a1 < 0x30) {
                continue;
            }
            f20 = func_00283CE0(a1 - 0x30);
            f20 = f20 / func_00283CE0(0x4C);
            f[0x100 / 4 + i] = f20;
            if (1.0f < f20) {
                f[0x100 / 4 + i] = 1.0f;
            }
            if (raw[2 + i] < 0x7F) {
                f[0x100 / 4 + i] = -f[0x100 / 4 + i];
            }
        }
    }
    if (s6 == 0 || type < 6) {
        for (i = 4; i < 16; i++) {
            f[0x100 / 4 + i] = func_00283CE0(raw[2 + i]) * 0.003921569f;
        }
    }
    if (D_001A7A44 != 0) {
        f[0x108 / 4] = -f[0x108 / 4];
        f[0x100 / 4] = -f[0x100 / 4];
        v = w[0x1A0 / 4];
        if (v & 0x8000) {
            v = (v & 0xFFFF7FFF) | 0x2000;
        } else if (v & 0x2000) {
            v = (v & ~0x2000) | 0x8000;
        } else {
            v = 0;
        }
        w[0x1A0 / 4] = v;
        w[0x1B0 / 4] = w[0x1A0 / 4];
    }
    for (i = 0; i < 16; i++) {
        w[0x140 / 4 + i] = w[0x100 / 4 + i];
    }
    if (f[0x108 / 4] == 0.0f && f[0x10C / 4] == 0.0f) {
        w[0x1D8 / 4] = 0;
    } else {
        w[0x1D8 / 4] = 1;
    }
    if (f[0x108 / 4] < 0.0f) {
        w[0x1A0 / 4] |= 0x8000;
    }
    if (0.0f < f[0x108 / 4]) {
        w[0x1A0 / 4] |= 0x2000;
    }
    if (f[0x10C / 4] < 0.0f) {
        w[0x1A0 / 4] |= 0x1000;
    }
    if (0.0f < f[0x10C / 4]) {
        w[0x1A0 / 4] |= 0x4000;
    }
    t0 = w[0x1A0 / 4];
    a3 = w[0x1AC / 4];
    a2 = w[0x1BC / 4];
    a1 = w[0x1B0 / 4];
    w[0x1D4 / 4] = (t0 & 0xF000) == 0;
    w[0x1D0 / 4] = t0 == 0;
    w[0x1B4 / 4] = ~a3 & a1;
    w[0x1B8 / 4] = ~t0 & a2;
    a0 = ~a3 & t0;
    a1 = ~t0 & a3;
    w[0x1C4 / 4] = a0;
    w[0x1C8 / 4] = a1;
    w[0x1A4 / 4] = a0;
    w[0x1A8 / 4] = a1;
    w[0x1C0 / 4] = t0;
    w[0x348 / 4] = t0;
    if (D_001A7A44 != 0) {
        f[0x148 / 4] = -f[0x148 / 4];
        f[0x140 / 4] = -f[0x140 / 4];
        if (t0 & 0x8000) {
            v = (t0 & 0xFFFF7FFF) | 0x2000;
        } else if (t0 & 0x2000) {
            v = (t0 & ~0x2000) | 0x8000;
        } else {
            v = 0;
        }
        w[0x1C0 / 4] = v;
        v = w[0x1C4 / 4];
        if (v & 0x8000) {
            w[0x1C4 / 4] = (v & 0xFFFF7FFF) | 0x2000;
        } else if (v & 0x2000) {
            w[0x1C4 / 4] = (v & ~0x2000) | 0x8000;
        }
        v = w[0x1C8 / 4];
        if (v & 0x8000) {
            w[0x1C8 / 4] = (v & 0xFFFF7FFF) | 0x2000;
        } else if (v & 0x2000) {
            w[0x1C8 / 4] = (v & ~0x2000) | 0x8000;
        }
    }
    if (w[0x1CC / 4] == 1) {
        w[0x1A0 / 4] &= 0xFFFFAFCF;
        w[0x1A4 / 4] &= 0xFFFFAFCF;
        w[0x1A8 / 4] &= 0xFFFFAFCF;
        w[0x100 / 4] = 0;
        w[0x104 / 4] = 0;
        w[0x1CC / 4] = 0;
    }
    if (w[0x1CC / 4] == 2) {
        w[0x1A0 / 4] &= 0x900;
        w[0x1A4 / 4] &= 0x900;
        w[0x1A8 / 4] &= 0x900;
        w[0x1B0 / 4] &= 0x900;
        w[0x1D4 / 4] = 1;
        w[0x108 / 4] = 0;
        w[0x10C / 4] = 0;
        w[0x1CC / 4] = 0;
    }
    {
        float xy[2];

        xy[0] = f[0x108 / 4];
        xy[1] = f[0x10C / 4];
        f20 = func_00282E20(xy);
        f21 = func_00283248(xy[0], xy[1]);
    }
    k = *(short *)(p + 0x18E);
    hist_a[k] = f20;
    hist_b[*(short *)(p + 0x18E)] = f21;
    if (0.9f < f20) {
        a1 = *(short *)(p + 0x18E) + 29;
        a0 = a1 % 30;
        if (!(0.9f < hist_a[a0])) {
            v = a1;
            a2 = 1;
            for (;;) {
                if (hist_a[a0] < 0.25f) {
                    w[0x1A4 / 4] |= 0x10000;
                    break;
                }
                a2++;
                if (a2 >= 4) {
                    break;
                }
                v--;
                a0 = v % 30;
                if (0.9f < hist_a[a0]) {
                    break;
                }
            }
        }
        if ((w[0x1A4 / 4] & 0x10000) == 0) {
            for (i = 1; i < 5; i++) {
                x = func_00283C80(hist_b[(*(short *)(p + 0x18E) - i + 30) % 30], f21);
                if (0.96050000f < x) {
                    w[0x1A4 / 4] |= 0x10000;
                    break;
                }
            }
        }
    }
    hist_c[*(short *)(p + 0x18E)] = w[0x1A4 / 4];
    v = w[0x190 / 4] + 1;
    *(short *)(p + 0x18E) = (*(short *)(p + 0x18E) + 1) % 30;
    w[0x190 / 4] = v;
    if (v >= 0x1F) {
        w[0x190 / 4] = 30;
    }
    ub = *(unsigned char *)(p + 0x34E);
    if (ub != 0) {
        v = w[0x1A0 / 4];
        if (v != 0 && v == w[0x1AC / 4]) {
            a0 = (unsigned char)(*(unsigned char *)(p + 0x34F) - 1);
            *(unsigned char *)(p + 0x34F) = a0;
            if (a0 == 0 || a0 == 0xFF) {
                w[0x1A4 / 4] = v;
                *(unsigned char *)(p + 0x34F) = ub;
            }
        } else {
            *(unsigned char *)(p + 0x34F) = *(unsigned char *)(p + 0x34D);
        }
    }
}
