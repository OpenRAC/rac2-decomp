/* functional: high. Transcribed from retail branch by branch (52 voice entries of 0x70 bytes from 0x188660, three scratch arrays of 52 words); the call arguments are the retail ones. The two voice callbacks are passed as named functions (func_002E60E8, func_002E60A0), not literal addresses, which differ per level program. fcheck SAME on boot and level-00 calls. */
extern char D_00188660[];
extern char D_00189F70[];
extern char D_001B5340[];
extern float D_0018A150;
extern int D_001B5600;
extern int D_001A8BB0;
extern int D_001A8C88;
extern int D_001A8B80;
extern int D_001B1688;
extern short D_00152C20;

extern void func_00132028(void);
extern void func_00133710(int, int, int, int, int);
extern void func_00133788(int, int, int, int);
extern void func_002E4478(void *);
extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00132888(int, int);
extern void func_00282A60(void *, int, int);
extern void func_00283098(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_002E46C0(void *, void *);
extern int func_00283150(void *, int);
extern int func_002E4528(void *, void *);
extern int func_002E4708(void *, void *);
extern int func_00283CF0(float);
extern int func_00133988(int);
extern void func_00132A70(int);
extern void func_00132B58(int, int, int);
extern void func_00132BC0(int, int, int, int, int, int, int, int);
extern void func_00132A10(int, int, int, int, int, int, int, int);
extern void func_002B7578(void);
extern void func_00133230(void);
extern void func_00133220(void);
extern void func_002E60E8(void);
extern void func_002E60A0(void);

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U8(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define UH(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define FL(p, o) (*(float *)((char *)(p) + (o)))

static void copy16(void *dst, void *src)
{
    ((long *)dst)[0] = ((long *)src)[0];
    ((long *)dst)[1] = ((long *)src)[1];
}

int func_002E4AC8(void)
{
    char *B = D_00188660;
    char *tab = D_00188660 + 0xB4;          /* 0x188714: a 36-byte row per voice at +0x70*i */
    float f22 = 0.0f;
    float f20, f0, f4;
    int flagA = D_001B5600;
    int i, k, n, s0, a3, s3, s1, s4v, s7v;
    int cnt;
    unsigned char spbuf[16] __attribute__((aligned(16)));
    unsigned char vec[16] __attribute__((aligned(16)));
    unsigned char tmp[16] __attribute__((aligned(16)));
    unsigned char qs[16] __attribute__((aligned(16)));
    int arrA[52], arrB[52], arrC[52];
    char *E;

    if (flagA != 0)
        f22 = D_0018A150;
    func_00132028();

    {
        int a0 = U8(B, 0x6B);
        if (a0 & 8)
            func_00133710(2, 0, 0, 0, 0);
        else if (a0 & 0x13)
            func_00133710(2, U8(B, 0x68), I(B, 0x64), U8(B, 0x69), U8(B, 0x6A));
        else if (a0 & 4)
            func_00133788(2, I(B, 0x64), 0xC, 3);
    }
    U8(B, 0x6B) = 0;

    if (D_001A8BB0 == 0 || D_001A8BB0 == 2) {
        if (D_001A8C88 == 0)
            func_002E4478(spbuf);
    }
    ((long *)vec)[0] = 0;
    ((long *)vec)[1] = 0;

    /* ring of four quads at B[0..0x3F], index at B+0x40 */
    k = (I(B, 0x40) + 1) % 4;
    I(B, 0x40) = k;
    copy16(B + k * 16, D_001B5340);

    s4v = 0;
    f0 = func_00282DF0(D_00189F70);
    a3 = I(B, 0x40);
    s0 = (a3 + 3) % 4;
    f20 = f0;
    if (s0 != a3) {
        do {
            func_00282CF0(tmp, B + a3 * 16, B + s0 * 16);
            f0 = func_00282DF0(tmp);
            if (!(f0 < f20 + 1.0f))
                break;
            func_00282CC0(vec, vec, tmp);
            s4v++;
            a3 = s0;
            s0 = (a3 + 3) % 4;
        } while (s0 != I(B, 0x40));
    }
    if (s4v >= 2) {
        f0 = func_00283CE0(s4v);
        func_00282D30(vec, vec, 1.0f / f0);
    }

    {
        int P1 = D_001A8B80;
        int mode = D_001A8BB0;
        f4 = (float)I(B, 0x48);
        if (P1 == 0 && H(B, 0x17B8) <= 0) {
            if (mode == 2 || (mode == 6 && (D_00152C20 == 3 || D_00152C20 == 0))) {
                func_00132888(1, 0);
                func_00132888(0, I(B, 0x48) / 2);
                func_00132888(3, I(B, 0x54) / 2);
            } else {
                func_00132888(1, flagA ? (I(B, 0x4C) * 3) / 5 : I(B, 0x4C));
                func_00132888(0, I(B, 0x48));
                func_00132888(3, I(B, 0x54));
            }
        } else {
            short c;
            f0 = 1.0f;
            if (P1 != 0) {
                if (H(B, 0x17B8) == 0) {
                    if (P1 == 2) {
                        H(B, 0x17B8) = 2;
                    } else {
                        H(B, 0x17BA) = 30;
                        H(B, 0x17B8) = 1;
                    }
                }
            } else if (H(B, 0x17B8) == 2) {
                H(B, 0x17BA) = 30;
                H(B, 0x17B8) = 3;
            }
            c = UH(B, 0x17BA) - 1;
            UH(B, 0x17BA) = c;
            switch (H(B, 0x17B8)) {
            case 2:
                f0 = 4.0f;
                break;
            case 1:
                f0 = ((1.0f - (float)c * 0.033333335f) * 3.0f) + 1.0f;
                if (!(c > 0))
                    H(B, 0x17B8) = 2;
                break;
            case 3:
                f0 = (float)c * 0.10000001f + 1.0f;
                if (!(c > 0))
                    H(B, 0x17B8) = 0;
                break;
            default:
                break;
            }
            f4 = f4 / f0;
            s1 = (int)f4;
            func_00132888(0, s1);
            func_00132888(3, s1);
        }
    }

    func_00132888(2, I(B, 0x50));
    func_00132888(5, I(B, 0x5C));
    func_00132888(6, I(B, 0x50));
    func_00282A60(arrA, 0, 0xD0);
    func_00282A60(arrC, 0, 0xD0);
    func_00282A60(arrB, 0, 0xD0);

    /* pass 1: classify every voice */
    for (i = 0; i < 52; i++) {
        int st, obj, a0, cap;
        char *va;
        E = B + 0x70 * i;
        st = U8(E, 0x74);
        if (st != 7) {
            if (I(E, 0x70) == 0 || I(E, 0x70) == -1)
                continue;
        }
        obj = I(E, 0x88);
        a0 = 0;
        if (obj != 0) {
            int t = U8(obj, 0x20);
            if (t == 0xFE || t == 0xFD)
                a0 = 1;
        }
        if (a0 != 0)
            I(E, 0x88) = 0;
        st = U8(E, 0x74);
        if (st == 4) {
            arrA[i] = 0x20;
            continue;
        }
        if (st != 6 && a0 != 0 && U8(I(E, 0x78), 0x18) != 0) {
            arrA[i] = 0x20;
            continue;
        }
        if (D_001A8BB0 != 0 && D_001A8BB0 != 2 && D_001A8BB0 != 6 && U8(E, 0x74) != 7) {
            arrA[i] = 0x10;
            continue;
        }
        va = B + 0x90 + 0x70 * i;
        obj = I(E, 0x88);
        if (obj == 0 || (U8(E, 0x75) & 8)) {
            ((long *)tmp)[0] = 0;
            ((long *)tmp)[1] = 0;
        } else if (U8(E, 0x75) & 0x40) {
            func_00283098(qs, E + 0xA0);
            func_00282CC0(qs, qs, (char *)obj + 0x10);
            func_00282CF0(tmp, qs, va);
            copy16(va, qs);
        } else {
            float x = FL(E, 0x98);
            FL(E, 0x98) = x - 1.0f;
            func_00282CF0(tmp, (char *)obj + 0x10, va);
            copy16(va, (char *)I(E, 0x88) + 0x10);
            FL(E, 0x98) = FL(E, 0x98) + 1.0f;
        }
        func_00282CF0(tmp, tmp, vec);
        func_00282CF0(qs, D_001B5340, va);
        func_00282F20(qs, qs, 1.0f);
        arrB[i] = 0;
        *(float *)&arrB[i] = func_00282DB0(qs, tmp);
        if (U8(E, 0x75) & 0x10) {
            cap = 0x400;
            arrC[i] = H(E, 0x80);
        } else {
            cap = func_002E46C0(E + 0x70, va);
            arrC[i] = (H(E, 0x80) * cap) / 1024;
            if (!(U8(I(E, 0x78), 0x19) & 2))
                arrA[i] |= 8;
        }
        if (flagA != 0) {
            if (!(U8(I(E, 0x78), 0x19) & 4)) {
                if (f22 < FL(E, 0x98))
                    arrC[i] = arrC[i] / 2;
            }
        }
        arrA[i] |= 1;
        if (cap < 0x20 && arrC[i] < 0x20) {
            if (U8(E, 0x75) & 4) {
                arrA[i] = 0x20;
                continue;
            }
        }
        if (U8(E, 0x75) & 1)
            continue;
        {
            int old = arrA[i];
            arrA[i] = old | 2;
            if (!(U8(E, 0x75) & 0x20) && !(U8(I(E, 0x78), 0x19) & 0x10))
                arrA[i] = old | 6;
        }
    }

    /* pass 2: loudness scaling for voices flagged 8 */
    for (i = 0; i < 52; i++) {
        int sc;
        E = B + 0x70 * i;
        if (!(arrA[i] & 8))
            continue;
        if (U8(E, 0x74) == 7) {
            if (!(D_001A8BB0 == 0 || D_001A8BB0 == 2))
                continue;
            if (D_001A8C88 != 0)
                continue;
            if (D_001B1688 != I(B, 0x1738)) {
                for (k = 0; k < 6; k++)
                    func_002E4478(B + 0x1740 + 16 * k);
                I(B, 0x1738) = D_001B1688;
            }
            s3 = 0;
            s0 = 0;
            n = 0;
            do {
                int r = func_002E4528(E + 0x70, B + 0x1740 + 16 * n);
                int j;
                tab[0x70 * i + s0] = r;
                for (j = 1; j <= 5; j++)
                    tab[0x70 * i + s0 + j] = tab[0x70 * i + s0];
                if (tab[0x70 * i + s0] != 0)
                    s3 += 6;
                n++;
                s0 += 6;
            } while (s0 < 0x24);
            sc = s3;
        } else {
            if ((D_001A8BB0 == 0 || D_001A8BB0 == 2) && D_001A8C88 == 0) {
                int cond;
                int r;
                UH(E, 0x82) = (UH(E, 0x82) + 1) % 36;
                if (U8(E, 0x75) & 4)
                    cond = (i ^ D_001B1688) & 1;
                else
                    cond = ((D_001B1688 ^ i) & 3) == 0;
                if (cond) {
                    r = func_002E4528(E + 0x70, spbuf);
                    tab[0x70 * i + UH(E, 0x82)] = r;
                } else {
                    tab[0x70 * i + UH(E, 0x82)] = tab[0x70 * i + (UH(E, 0x82) + 35) % 36];
                }
            }
            sc = func_00283150(tab + 0x70 * i, 0x24);
        }
        if (sc >= 0x24) {
            arrC[i] = 0;
        } else if (sc >= 0x13) {
            arrC[i] = ((0x24 - sc) * arrC[i]) / 0x12;
        }
    }

    /* pass 3: start, update or stop the voices */
    for (i = 0; i < 52; i++) {
        int a0 = arrA[i];
        int s2;
        E = B + 0x70 * i;
        if (a0 == 0)
            continue;
        s2 = I(E, 0x70);
        I(E, 0x70) = -1;
        if (a0 & 0x20) {
            if (U8(E, 0x74) == 7) {
                U8(E, 0x74) = 0;
                I(E, 0x88) = 0;
                I(E, 0x8C) = 0;
            } else {
                func_00132A70(s2);
                U8(E, 0x74) = 6;
                func_00132B58(s2, (int)func_002E60E8, (int)(B + 0x70 * i + 0x70));
            }
            continue;
        }
        if (a0 & 0x10) {
            func_00132B58(s2, (int)func_002E60E8, (int)(B + 0x70 * i + 0x70));
            continue;
        }
        {
            int s4 = I(E, 0x84);
            s1 = s4 ? 0x11 : 1;
            s7v = 0;
            s3 = 0;
            if (a0 & 2) {
                s1 |= 6;
                s7v = func_002E4708(B + 0x70 * i + 0x70, B + 0x70 * i + 0x90);
            }
            if (arrA[i] & 4) {
                float m = (U8(E, 0x75) & 2) ? 500.0f : 300.0f;
                s1 |= 8;
                s3 = func_00133988(func_00283CF0(*(float *)&arrB[i] * m));
            }
            if (flagA != 0 && !(U8(I(E, 0x78), 0x19) & 8)) {
                s1 |= 8;
                s3 -= 0x5F4;
            }
            if (U8(E, 0x74) != 7) {
                func_00132BC0(s2, s1, arrC[i], s7v, s3, s4, (int)func_002E60E8, (int)(B + 0x70 * i + 0x70));
            } else {
                int o = I(E, 0x78);
                int x;
                if (o == 0) {
                    I(E, 0x88) = 0;
                    I(E, 0x8C) = 0;
                    U8(E, 0x74) = 0;
                } else {
                    x = I(B, 0x17A0 + 4 * I(o, 0x1C));
                    if (x == -1 || x == 0) {
                        I(E, 0x88) = 0;
                        I(E, 0x8C) = 0;
                        U8(E, 0x74) = 0;
                    } else {
                        U8(E, 0x74) = 1;
                        func_00132A10(x, H(o, 0x1A), arrC[i], s7v, s3, s4, (int)func_002E60A0, (int)(B + 0x70 * i + 0x70));
                    }
                }
            }
        }
    }

    func_002B7578();
    func_00133230();
    func_00132028();
    func_00133220();
    I(B, 0x6C) = 0;
    return 0;
}
