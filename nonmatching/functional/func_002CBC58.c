/* functional: medium. Written from the assembly: same reads, writes and calls with the same arguments in the same order; the divide-by-zero checks retail emits for the divisions by 2*h and 2*w are dropped. */
extern char D_001F2840[];       /* C: the menu block */
extern char D_00138180[];       /* P: the pad block */
extern char D_00259018[], D_0025A738[], D_0025A498[], D_0025A190[], D_00259EE0[];
extern int func_002DBAD0(), func_002DA118(), func_002D84B0(), func_002DA9A8();
extern int D_001A72DC;
extern int D_001A7344;
extern int D_001AB91C;          /* gp-0x36D4 */
extern int D_001AB910;          /* gp-0x36E0 */
extern int D_001AB92C;          /* gp-0x36C4 */
extern int D_001AB930;          /* gp-0x36C0 */
extern char D_001AB920[];
extern char D_001AB928[];
extern int D_001AA450[];        /* gp-0x4BA0, 14 words */
extern int D_001AA43C;          /* gp-0x4BB4 */
extern unsigned long long D_001A7470; /* gp-0x7B80 */
extern int D_00210AD0;

extern void func_00284F40(int);
extern void func_002FC990(int, int, int);
extern void func_0027B858(void);
extern void func_0027DDC0(int, int, int, int);
extern void func_0027C540(int);
extern void func_0027C660(void);
extern void func_0028E458(void);
extern void func_0029BF08(void);
extern void func_0029C2D0(void);
extern void func_0029C340(void);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_002A0250(void);
extern void func_002A01C8(void);
extern void func_002A01F0(void);
extern void func_002A0220(void);
extern void func_002A0380(void);
extern void func_0026FEB8(void *, ...);
extern void func_00280510(float, int, int, int);
extern void func_00280600(void);
extern void func_0028FDD8(int, int, int, int, int, int, int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern int func_00283CF0(float);
extern void func_002FC3C0(int);
extern void func_0029FEE0(void);

#define CW(o) (*(int *)(D_001F2840 + (o)))
#define CF(o) (*(float *)(D_001F2840 + (o)))
#define PW(o) (*(int *)(D_00138180 + (o)))

void func_002CBC58(int mode)
{
    int s7 = 0;
    int i, fp, s1, s2, s3, s4, s5, s6, w;
    int fl, widget, a1;
    int t0, t1, t2, t3, a2, a3, rect;
    int x, y;
    float f1, f0;

    func_00284F40(0);
    func_002FC990(CW(0x20), D_001A72DC, D_001A7344 << 11);
    if (mode != 0)
        return;
    func_0027B858();
    func_0027DDC0(0, 0, 0, 0x38);
    if (CW(0) != 4)
        return;
    if (CW(4) == 0)
        return;

    if (D_001AB91C != 0) {
        s1 = CW(0x14);
        if (s1 == (int)D_00259018) {
            func_0027C540(0);
            ((void (*)(void))D_00210AD0)();
            func_0027C660();
            return;
        }
        if (s1 == (int)D_0025A738) {
            func_0027C540(0);
            func_0028E458();
            func_0029BF08();
            func_0027C660();
            return;
        }
        if (s1 == (int)D_0025A498) {
            if (D_001AB910 == 0) {
                func_0027C540(0);
                func_0029C2D0();
                func_0027C660();
            }
        } else if (CW(0x14) == (int)D_0025A190) {
            if (D_001AB910 == 0) {
                func_0027C540(0);
                func_0029C340();
                func_0027C660();
                return;
            }
        }
    }

    func_002FC560(0x47, 0x5360BULL);
    if (CW(0x168) != 0) {
        func_002A0250();
        func_002A01C8();
        func_002A01F0();
    }
    a1 = CW(0x14);
    if (a1 != 0)
        s7 = a1 + 0xEC;
    if ((PW(0x1A0) & 0xF) == 0xF && (PW(0x1C4) & 0xF) != 0)
        func_0026FEB8(D_001AB920);

    for (i = 0; i < 14; i++) {
        if (D_001AA450[i] == 0)
            continue;
        if (s7 == 0)
            continue;
        widget = *(int *)(s7 + 4 * i);
        if (widget == 0)
            continue;
        rect = CW(0x14) + (i << 4);
        *(int *)(widget + 0x18) = *(int *)(rect + 0) - *(int *)(rect + 8) / 2;
        widget = *(int *)(s7 + 4 * i);
        rect = CW(0x14) + (i << 4);
        *(int *)(widget + 0x1C) = *(int *)(rect + 4) - *(int *)(rect + 0xC) / 2;
        widget = *(int *)(s7 + 4 * i);
        *(int *)(widget + 0x20) = *(int *)(CW(0x14) + (i << 4) + 8);
        widget = *(int *)(s7 + 4 * i);
        *(int *)(widget + 0x24) = *(int *)(CW(0x14) + (i << 4) + 0xC);
        widget = *(int *)(s7 + 4 * i);
        if (widget == (int)D_00259EE0)
            *(int *)(widget + 0x24) = 0x100;
    }

    if ((PW(0x1A0) & 0xF) == 0xF && (PW(0x1C4) & 0xF) != 0)
        func_0026FEB8(D_001AB928);
    s6 = 1;
    for (fp = 0; fp < 2; fp++) {
        for (i = 0; i < 14; i = s5) {
            s5 = i + 1;
            if (s7 == 0)
                break;
            widget = *(int *)(s7 + 4 * i);
            if (widget == 0)
                continue;
            a1 = *(int *)(widget + 0x10);
            if (a1 & 4)
                continue;
            if (D_001AA450[i] == 0)
                continue;
            if (*(int *)(widget + 4) == 0)
                continue;
            if (fp == 0 && !(a1 & 2))
                continue;
            if (fp == 1 && (a1 & 2))
                continue;
            if (a1 & 1) {
                ((void (*)(int))*(int *)(widget + 4))(widget);
                continue;
            }
            x = *(int *)(widget + 0x18);
            y = *(int *)(widget + 0x1C);
            s4 = *(int *)(widget + 0x20);
            s3 = *(int *)(widget + 0x24);
            s2 = 7;
            if (s4 > 0x80) {
                do {
                    s2++;
                } while ((1 << s2) < s4);
            }
            s1 = 7;
            if (s3 > 0x80) {
                do {
                    s1++;
                } while ((1 << s1) < s3);
            }
            while (s2 + s1 >= 0x12)
                s1--;
            {
                int cb = *(int *)(*(int *)(s7 + 4 * i) + 4);
                if ((cb == (int)func_002DBAD0 || cb == (int)func_002DA118 || cb == (int)func_002D84B0 || cb == (int)func_002DA9A8)
                    && !(*(int *)(*(int *)(s7 + 4 * i) + 0x10) & 8)) {
                    func_00280510(1.0f, s2, s1, 0);
                    func_0028FDD8(0, 0, s6 << s2, s6 << s1, D_001AA43C, 0, 0);
                    widget = *(int *)(s7 + 4 * i);
                    fl = ((int (*)(int))*(int *)(widget + 4))(widget);
                    func_00280600();
                } else {
                    widget = *(int *)(s7 + 4 * i);
                    fl = ((int (*)(int))*(int *)(widget + 4))(widget);
                }
            }
            func_002FC560(0x42, 0x8000000064ULL);
            func_002FC560(0x47, 0x43ULL);
            if (fl & 1)
                continue;
            a2 = s6 << s2;
            a3 = s6 << s1;
            t0 = 0;
            t1 = 0;
            t2 = a2;
            t3 = a3;
            if (fl & 2) {
                t2 = s4;
                t3 = s3;
            } else if (fl & 8) {
                t0 = (t2 - s4) / 2;
                t1 = (t3 - s3) / 2;
                t2 = t2 - t0;
                t3 = t3 - t1;
                if (a3 < t3)
                    t3 = a3;
                if (a2 < t2)
                    t2 = a2;
                if (t0 < 0)
                    t0 = 0;
                if (t1 < 0)
                    t1 = 0;
            } else if (fl & 4) {
                if (s4 < s3) {
                    t0 = t2 / 2 - (s4 * t2) / (s3 << 1);
                    t2 = t2 - t0;
                } else {
                    t1 = t3 / 2 - (s3 * t3) / (s4 << 1);
                    t3 = t3 - t1;
                }
            } else if (!(fl & 0x10)) {
                continue;
            }
            if (D_001AB92C == 0)
                continue;
            func_0027E018(x, y, s4, s3, t0, t1, t2 - t0, t3 - t1, 0x80808080ULL, D_001A7470);
        }
        if (D_001AB930 != 0 && fp == 0) {
            if (CW(0x168) != 0) {
                func_002A0220();
                func_002A0380();
                func_002FC3C0(0x10);
                func_0029FEE0();
                CW(0x16C) = 0;
                CW(0x168) = 0;
            }
        }
    }

    func_0027B858();
    f1 = CF(0x1C0);
    f0 = CF(0x1C8);
    if (f1 != f0) {
        f1 = f0 - f1;
        f0 = CF(0x1C4);
        if (f0 < f1) {
            f1 = f0;
        } else {
            f0 = -f0;
            if (f1 < f0)
                f1 = f0;
        }
        CF(0x1C0) = CF(0x1C0) + f1;
    }
    f1 = CF(0x1C0);
    if (f1 != 0.0f) {
        i = func_00283CF0(f1 * 128.0f);
        func_0027DDC0(0, 0, 0, i);
    }
    func_002FC560(0x42, 0x8000000044ULL);
    func_002FC560(0x47, 0x5360BULL);
}
