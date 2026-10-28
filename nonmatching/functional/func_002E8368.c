/* functional: medium (fcheck covers 4 calls; the phase-end branch is probably not exercised). Hand-decoded from the assembly (not attempted as a match): per-frame update of the intro/transition controller at 0x1B8840; the same reads, writes and calls in the same order with the same arguments. Field names are offsets only. Returns 1 once when the last phase ends and the flag at 0x1A7284 is set. */
#define W(p, o)  (*(int *)((char *)(p) + (o)))
#define H(p, o)  (*(short *)((char *)(p) + (o)))
#define B(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define F(p, o)  (*(float *)((char *)(p) + (o)))

extern void func_002F5220(void);
extern void func_002F52B8(void);
extern void func_00133220(void);
extern void func_00133230(void);
extern int func_00132028(void);
extern void func_001329F0(int, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_0029F390(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002A0F48(void *);
extern void func_002A10E8(void *);
extern void func_002EC1C0(void);
extern void func_002ED260(int);
extern void func_00132AA0(void);
extern int func_001163B0(void);
extern void func_00132858(int);
extern void func_00132818(void);
extern void func_002E80B0(void);
extern void func_00282A60(void *, int, int);
extern void func_00294070(int);
extern void func_002E6A60(void);
extern void func_0027AB40(void);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_002E64A0(int);

extern float D_001B15A0;
extern char D_001B8840[];        /* controller state */
extern char D_00152C00[];        /* mode block: +0x64 index, +0x68 phase */
extern int D_001B2130[];         /* [0] +0, [1] +4, [3] +0xC */
extern int D_001B2148[];         /* null-terminated entity list */
extern int D_00214920[];         /* null-terminated entity list */
extern int D_001ABEB0;
extern int D_001A7280;
extern int D_001A7284;
extern int D_001B22B0;
extern int D_001BAEC0[];
extern int D_001886D0[];
extern char D_00261F30[];        /* 16-byte entries */
extern char D_001B20D0[];
extern char D_001AC0C0[];
extern char D_001AC0D0[];
extern char D_001AC120[];
extern float D_001AC150[];
extern float D_001AC168[];
extern float D_001ABDD4;
extern float D_001ABF10;
extern char D_001B9040[];        /* view: +0xB0 float */

int func_002E8368(void)
{
    char *S = D_001B8840;
    char *g = D_00152C00;
    float sp0[4], sp10[4], sp20[12];
    float f20;
    int i, fp;

    func_002F5220();
    {
        float v = D_001B15A0 - 0.25f;
        W(S, 0x38) = W(S, 0x38) + 1;
        W(S, 0x34) = W(S, 0x34) + 1;
        D_001B15A0 = v;
        if (v < 0.0f)
            D_001B15A0 = 0.0f;
    }
    if (W(S, 0x34) == 1) {
        int n;
        func_00133220();
        n = W(g, 0x64);
        func_001329F0(D_001B2130[n], 0, 0x400, 0, 0, 0, 0, (int)D_001886D0 + n * 0x70);
        func_00133230();
        func_00132028();
    }
    if (W(S, 0x34) < H(S, 0x40)) {
        goto running;
    }
    /* the phase has ended */
    for (i = 0; i < H(S, 0x44); i++) {
        void *p = (void *)W(S, 0x18C + i * 4);
        if (p != 0) {
            void *q = (void *)W(p, 0x24);
            B(q, 0xC) = B(q, 0xC) - 1;
            q = (void *)W(p, 0x24);
            W(q, 0x48 + B(q, 0xC) * 4) = 0;
            func_0029F338(p);
        }
    }
    if (D_001ABEB0 != 0) {
        func_002EC1C0();
        D_001ABEB0 = 0;
    }
    func_002ED260(0x240450);
    if (D_001A7280 < 2)
        W(g, 0x68) = 0;
    if (W(g, 0x68) < 2) {
        if (W(g, 0x64) != 2) {
            func_00132AA0();
            while (func_00132028() != 0)
                ;
        }
        if (W(g, 0x68) == 0) {
            int r = func_001163B0() >> 16;
            W(g, 0x64) = (W(g, 0x64) + (r % 3) + 1) & 3;
        } else {
            W(g, 0x64) = 4;
            func_00133220();
            func_00132858(D_001B2130[0]);
            func_00132858(D_001B2130[1]);
            func_00132858(D_001B2130[3]);
            func_00133230();
            while (func_00132028() != 0)
                ;
            func_00132818();
            D_001A7284 = 0;
            func_002E80B0();
        }
        W(g, 0x68) = W(g, 0x68) + 1;
        {
            int *dst = (int *)D_001AC0D0, *src = (int *)D_001AC0C0;
            dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3];
        }
        func_00282A60(S, 0, 0x1D0);
        {
            int a2 = D_001B22B0;
            int a1 = D_001BAEC0[6];
            int *a2p, *a3;
            int *t0;
            int t1;
            W(S, 0x6C) = D_001BAEC0[3] + a2;
            W(S, 0x70) = D_001BAEC0[4] + a2;
            a2p = (int *)(a1 + 0x50 + W(g, 0x64) * 4);
            a1 = a1 + W((void *)a1, 4);
            a3 = (int *)(a1 + *a2p);
            if (a3[1] != 0) {
                t0 = (int *)(S + 0x74);
                t1 = 0;
                do {
                    int v0 = a3[0];
                    t1++;
                    a3 += 2;
                    *t0 = a1 + *a2p + (v0 + 0x800);
                    t0++;
                    if (!(t1 < 0x46))
                        break;
                } while (a3[1] != 0);
            }
        }
        func_00294070(0);
        goto after;
    } else {
        if (D_001A7284 == 0)
            return 0;
        D_001A7284 = 0;
        return 1;
    }

running:
    if (!(W(S, 0x38) < 0x60)) {
        W(S, 0x3C) = W(S, 0x3C) + 1;
        func_00294070(W(S, 0x3C));
    }
after:
    func_002E6A60();
    {
        float t = D_001AC168[W(g, 0x64)];
        if (F(D_001B9040, 0xB0) < t)
            F(D_001B9040, 0xB0) = t;
    }
    func_0027AB40();
    f20 = 1.0f;
    if (W(g, 0x64) == 4) {
        f20 = (float)(H(S, 0x40) - W(S, 0x34)) / (float)H(S, 0x40);
        func_00282D30(sp0, D_001AC120, f20);
        func_00282CC0(D_001AC0D0, D_001AC0D0, sp0);
    }
    func_00282D30(D_001B20D0, D_00261F30 + W(g, 0x64) * 16, (float)(W(S, 0x34) - 0x78) * (f20 * 20.0f));
    D_001ABDD4 = D_001AC150[W(g, 0x64)];
    for (i = 0; i < H(S, 0x44); i = fp) {
        char *o;
        int s1, s2;
        float r;
        char *s0m;
        s1 = W(S, 0x38);
        o = (char *)W(S, 0x18C + i * 4);
        fp = i + 1;
        r = func_00283CE0(s1 & 1);
        s1 = s1 >> 1;
        s2 = s1 + 1;
        s0m = (char *)W(o, 0x68);
        F(o, 0x44) = r * 0.5f;
        func_00282D30(sp0, s0m + s1 * 16, 1.0f - r * 0.5f);
        func_00282D30(sp10, s0m + s2 * 16, F(o, 0x44));
        func_00282CC0(o + 0x10, sp0, sp10);
        {
            char *d = (char *)W(o, 0x24);
            B(o, 0x42) = B(d, 0xC) - 1;
            B(o, 0x40) = s1;
            B(o, 0x41) = s2;
            B(o, 0x43) = B(d, 0xC) - 1;
        }
        func_0029F390(o);
        H(o, 0x32) = 0x1FF;
        if (H(o, 0xAA) == 0xD54) {
            if (D_001B2148[0] != 0) {
                func_0029FC20(o, 0, sp20);
                B(o, 0x63) = 0;
                H(o, 0x32) = 0;
                if (D_001B2148[0] != 0) {
                    int a3 = 0;
                    do {
                        char *e = (char *)D_001B2148[a3];
                        int k;
                        int *q;
                        B(e, 0x63) = 0;
                        e = (char *)D_001B2148[a3];
                        H(e, 0x32) = 0x1FF;
                        e = (char *)D_001B2148[a3];
                        q = (int *)(o + 0x10);
                        ((int *)(e + 0x10))[0] = q[0]; ((int *)(e + 0x10))[1] = q[1];
                        ((int *)(e + 0x10))[2] = q[2]; ((int *)(e + 0x10))[3] = q[3];
                        for (k = 0; k < 3; k++) {
                            e = (char *)D_001B2148[a3];
                            F(e, 0xC0 + k * 16) = sp20[k * 4];
                            F(e, 0xC4 + k * 16) = sp20[k * 4 + 1];
                            F(e, 0xC8 + k * 16) = sp20[k * 4 + 2];
                        }
                        func_002A10E8((void *)D_001B2148[a3]);
                        a3 = a3 + 1;
                    } while (D_001B2148[a3] != 0);
                }
            } else {
                func_002E64A0(W(S, 0x54));
            }
            B(o, 0x95) = 0xE8;
        }
        B(o, 0x62) = 0xFF;
        B(o, 0x61) = 0xFF;
        func_002A0F48(o);
        {
            char *d = (char *)W(o, 0x24);
            B(o, 0x42) = B(d, 0xC) - 1;
            B(o, 0x43) = B(d, 0xC) - 1;
            if (W(g, 0x64) == 4) {
                int a0 = H(S, 0x40);
                int v1 = W(S, 0x34);
                if (a0 - 0x28 < v1) {
                    float f1 = (float)(a0 - v1 - 4) * 0.027777778f;
                    if (f1 < 0.0f)
                        f1 = 0.0f;
                    F(o, 0x2C) = F(d, 0x24) * f1;
                    D_001ABF10 = f1;
                    if (D_001B2148[0] != 0) {
                        char *e = (char *)D_001B2148[0];
                        F(e, 0x2C) = F((char *)W(e, 0x24), 0x24) * f1;
                    }
                    B(o, 0x95) = (int)(f1 * 232.0f);
                    if (H(o, 0xAA) == 0xD54) {
                        if (D_001B2148[0] == 0) {
                            int *p;
                            H(g, 0x2C) = 1;
                            p = D_00214920;
                            if (*p != 0) {
                                do {
                                    char *e = (char *)*p;
                                    p++;
                                    F(e, 0x2C) = F((char *)W(e, 0x24), 0x24) * f1;
                                } while (*p != 0);
                            }
                        }
                    }
                }
            }
        }
    }
    func_002F52B8();
    return 0;
}
