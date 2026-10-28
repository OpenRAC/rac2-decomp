/* functional: medium. Transcribed from the assembly: fills the draw/display state at D_001A6480 and the GS packets (draw environment, 16-step clamp tables, display lists) in the same order with the same constants as retail; the table loops are written as plain loops. Return value: retail falls out with whatever func_0011AEA0 left, treated as void. */
typedef unsigned long u64;
typedef unsigned int u32;

extern unsigned char D_001A6480[];
extern unsigned char *D_001A742C __attribute__((sda));
extern int D_001A72D8, D_001A72DC, D_001A72E0, D_001A7BB8;
extern int D_001A7438, D_001A743C, D_001A7440, D_001A7444, D_001A7448;
extern int D_001A744C __attribute__((sda));
extern int D_001A7450, D_001A7454, D_001A7458, D_001A745C, D_001A7460, D_001A7464;
extern u64 D_001A6860[], D_001A6600[], D_001A6D40[], D_001A6E90[];
extern u64 D_00138850[], D_00138990[], D_00138AD0[], D_00138DC0[], D_001390B0[];

extern void func_00125A20(void *, int, int, int, int, int);
extern void func_00125F20(void *, int, int, int, int, int);
extern void func_00284088(int, int);
extern void func_00282AB0(void *, void *, int);
extern void func_0011AEA0(int);

#define SH(o) (*(short *)(S + (o)))
#define Q64(o) (*(u64 *)(S + (o)))

void func_00284268(int a0, int a1, int a2, int a3, int a4, int a5)
{
    unsigned char *S = D_001A6480;
    u64 *w;
    u64 v, v2;
    int i, t;
    int g72d8 = D_001A72D8 >> 13;
    int g72dc = D_001A72DC >> 13;
    int g72e0 = D_001A72E0 >> 13;

    SH(0x150) = a0;
    SH(0x152) = a1;
    SH(0x15C) = 1;
    SH(0x16C) = 0x31;
    SH(0x15E) = g72d8;
    SH(0x156) = g72dc;
    SH(0x16E) = g72e0;
    D_001A742C = S;
    *(int *)(S + 0x170) = 0;
    SH(0x158) = a2;
    SH(0x15A) = a3;
    SH(0x168) = a4;
    SH(0x16A) = a5;
    SH(0x154) = 0;
    SH(0x164) = 0;
    func_00125A20(S, 1, (short)a2, (short)a3, (short)a4, (short)a5);

    S = D_001A742C;
    Q64(0x10) = (Q64(0x10) & -0x200L) | (SH(0x15E) & 0x1FF);
    if (D_001A7BB8 != 0)
        Q64(0x18) = ((((0xDFA7L << 16 | 0xF804) << 19) | 0xD050) << 2);

    S = D_001A742C;
    D_001A7438 = (int)(Q64(0x18) & 0xFFF);
    D_001A743C = (int)((Q64(0x18) >> 12) & 0x7FF);
    D_001A7440 = (int)((Q64(0x18) >> 23) & 0xF);
    D_001A7444 = (int)((Q64(0x18) >> 27) & 3);
    D_001A7448 = (int)(*(u32 *)(S + 0x1C) & 0xFFF);
    v = (Q64(0x18) >> 44) & 0x7FF;
    D_001A7450 = D_001A7438;
    D_001A7454 = D_001A743C;
    D_001A7458 = D_001A7440;
    D_001A7460 = D_001A7448;
    D_001A745C = D_001A7444;
    D_001A7464 = (int)v;
    D_001A744C = (int)v;
    func_00125F20(S + 0x40, SH(0x154), SH(0x150), SH(0x152), 3, SH(0x16C));

    S = D_001A742C;
    Q64(0x40) = (Q64(0x40) & -0x200L) | (SH(0x156) & 0x1FF);
    Q64(0x50) = (u64)(long)SH(0x16E) | ((u64)((unsigned short)SH(0x16C) & 0xF) << 24);
    Q64(0x30) = 0;
    Q64(0x38) = 0;
    S = D_001A742C;
    v = Q64(0x30);
    v2 = Q64(0x38);
    v = ((((v & -0x8000L) | 8) | 0x8000) & 0x0FFFFFFFFFFFFFFFL) | 0x1000000000000000L;
    v2 = (v2 & -16L) | 14;
    Q64(0x38) = v2;
    Q64(0x30) = v;
    func_00125F20(S + 0xD0, SH(0x15C), SH(0x158), SH(0x15A), 0, 0);

    S = D_001A742C;
    Q64(0xE0) = 0x8000L << 17;
    Q64(0xD0) = (Q64(0xD0) & -0x200L) | (SH(0x15E) & 0x1FF);
    Q64(0xC0) = 0;
    Q64(0xC8) = 0;
    S = D_001A742C;
    v = Q64(0xC0);
    v2 = Q64(0xC8);
    v = (((((v & -0x8000L) | 8) | 0x8000) & 0x0FFFFFFFFFFFFFFFL) | 0x1000000000000000L);
    v2 = (v2 & -16L) | 14;
    Q64(0xC8) = v2;
    Q64(0xC0) = v;

    w = D_001A6860;
    w[0] = ((0x8116L << 16 | 0x8000) << 31) | 1;
    w[1] = 0xEEEE;
    w[2] = 0x30000;
    w[3] = 0x47;
    w[4] = 5;
    w[5] = 8;
    w[6] = (0x8000L << 17) | 0x261;
    w[7] = 0x14;
    S = D_001A742C;
    w[9] = 6;
    w[10] = (0x8800L << 47) | 0x8010;
    w[11] = 0x5353;
    w[8] = (u64)(long)(((unsigned short)SH(0x150) >> 6 & 0x3F) << 14 | SH(0x156) << 5)
           | ((u64)(long)SH(0x154) << 20) | (0xEA80L << 20);

    if (D_001A7BB8 != 0) {
        int t1 = 0x8000, t2 = 0x8280;

        w = D_001A6860 + 12;
        for (i = 0; i < 16; i++) {
            *w++ = (u64)(long)(i * SH(0x150));
            S = D_001A742C;
            *w++ = (u64)(long)(t1 - (SH(0x158) << 3)) | ((u64)(long)(0x7FF8 - (SH(0x15A) << 3)) << 16);
            t1 += 0x280;
            S = D_001A742C;
            *w++ = (u64)(long)((i + 1) * SH(0x150)) | ((u64)(long)SH(0x152) << 20);
            S = D_001A742C;
            *w++ = (u64)(long)(t2 - (SH(0x158) << 3)) | ((u64)(long)((SH(0x15A) << 3) + 0x7FF8) << 16);
            t2 += 0x280;
            S = D_001A742C;
        }
    } else {
        w = D_001A6860 + 12;
        for (i = 0; i < 16; i++) {
            *w++ = (u64)(long)(i * SH(0x150));
            S = D_001A742C;
            *w++ = (u64)(long)(i * SH(0x158) + 0x8000 - (SH(0x158) << 3)) | ((u64)(long)(0x7FF8 - (SH(0x15A) << 3)) << 16);
            S = D_001A742C;
            *w++ = (u64)(long)((i + 1) * SH(0x150)) | ((u64)(long)SH(0x152) << 20);
            S = D_001A742C;
            *w++ = (u64)(long)((i + 1) * SH(0x158) + 0x8000 - (SH(0x158) << 3)) | ((u64)(long)((SH(0x15A) << 3) + 0x7FF8) << 16);
            S = D_001A742C;
        }
    }

    w = D_001A6860;
    w[0x270 / 8] = 0x181;
    w[0x278 / 8] = 0x8000L << 16;
    w[0x260 / 8] = (0x8800L << 47) | 0x8001;
    w[0x268 / 8] = 0x4410;
    S = D_001A742C;
    w[0x280 / 8] = (u64)(long)(0x7FF8 - (SH(0x158) << 3)) | ((u64)(long)(0x7FF8 - (SH(0x15A) << 3)) << 16);
    S = D_001A742C;
    w[0x288 / 8] = (u64)(long)(0x7FF8 - (SH(0x158) << 3)) | ((u64)(long)((SH(0x15A) << 3) + 0x7FF8) << 16);
    func_00284088(0, 0);

    w = D_001A6600;
    w[0] = ((0x8116L << 16 | 0x8000) << 31) | 1;
    w[5] = 8;
    w[6] = (0x8000L << 17) | 0x261;
    w[7] = 0x14;
    w[1] = 0xEEEE;
    w[2] = 0x31001;
    w[3] = 0x47;
    w[4] = 5;
    S = D_001A742C;
    w[9] = 6;
    w[10] = (0x8800L << 47) | 0x8010;
    w[11] = 0x5353;
    w[8] = (u64)(long)(((unsigned short)SH(0x150) >> 6 & 0x3F) << 14 | SH(0x156) << 5)
           | ((u64)(long)SH(0x154) << 20) | (0xEA80L << 20);
    {
        int t0 = 0x7000, t5 = 0x200, t6 = 0x7200;

        w = D_001A6600 + 12;
        for (i = 0; i < 16; i++) {
            *w++ = (u64)(long)(i << 9);
            S = D_001A742C;
            *w++ = (u64)(long)t0 | ((u64)(long)(0x8000 - (SH(0x152) << 3)) << 16);
            t0 += 0x200;
            S = D_001A742C;
            *w++ = (u64)(long)t5 | ((u64)(long)SH(0x152) << 20);
            t5 += 0x200;
            S = D_001A742C;
            *w++ = (u64)(long)t6 | ((u64)(long)((SH(0x152) << 3) + 0x7FF0) << 16);
            t6 += 0x200;
        }
    }

    w = D_001A6D40;
    w[0] = 0x8000L << 45 | 1;
    w[4] = (0x9000L << 46) | 0x8001;
    w[1] = 0xE;
    w[2] = 0x30000;
    w[3] = 0x47;
    w[5] = 0x10;
    w[6] = 0x106;
    w[7] = 0x8000L << 16;
    w[8] = (0x9000L << 46) | 0x8010;
    w[9] = 0x44;
    {
        int a = 0x6FF8, b = 0x71F8;

        w = D_001A6D40 + 10;
        for (i = 0; i < 16; i++) {
            S = D_001A742C;
            *w++ = (u64)(long)a | ((u64)(long)(0x7FF8 - (SH(0x152) << 3)) << 16);
            a += 0x200;
            S = D_001A742C;
            *w++ = (u64)(long)b | ((u64)(long)((SH(0x152) << 3) + 0x7FF8) << 16);
            b += 0x200;
        }
    }
    func_00282AB0(D_001A6E90, D_001A6D40, 0x150);

    {
        int a = 0x6FF8, b = 0x71F8;

        w = D_00138850 + 8;
        for (i = 0; i < 16; i++) {
            S = D_001A742C;
            *w++ = (u64)(long)a | ((u64)(long)(0x7FF8 - (SH(0x152) << 3)) << 16);
            a += 0x200;
            S = D_001A742C;
            *w++ = (u64)(long)b | ((u64)(long)((SH(0x152) << 3) + 0x7FF8) << 16);
            b += 0x200;
        }
    }

    w = D_00138990 + 8;
    for (i = 0; i < 16;) {
        S = D_001A742C;
        if (D_001A7BB8 != 0) {
            *w++ = (u64)(long)(i * 0x280 + 0x6BF8) | ((u64)(long)(0x7FF8 - (SH(0x15A) << 3)) << 16);
            i++;
            S = D_001A742C;
            *w++ = (u64)(long)(i * 0x280 + 0x6BF8) | ((u64)(long)((SH(0x15A) << 3) + 0x7FF8) << 16);
        } else {
            *w++ = (u64)(long)((i << 9) + 0x6FF8) | ((u64)(long)(0x7FF8 - (SH(0x15A) << 3)) << 16);
            i++;
            S = D_001A742C;
            *w++ = (u64)(long)((i << 9) + 0x6FF8) | ((u64)(long)((SH(0x15A) << 3) + 0x7FF8) << 16);
        }
    }

    t = 0;
    w = D_00138AD0 + 24;
    {
        int a = 0;

        for (i = 0; i < 16; i++) {
            *w++ = (u32)a;
            *w++ = (u32)t;
            a += 0x200;
            t += 0x100;
            S = D_001A742C;
            *w++ = (u64)(u32)a | ((u64)(long)SH(0x152) << 20);
            *w++ = (u64)(u32)(t | 0x10000000);
        }
    }

    t = 0;
    w = D_00138DC0 + 24;
    {
        int a = 0;

        for (i = 0; i < 16; i++) {
            *w++ = (u32)a;
            *w++ = (u32)t;
            a += 0x200;
            t += 0x40;
            S = D_001A742C;
            *w++ = (u64)(u32)a | ((u64)(long)SH(0x152) << 20);
            *w++ = (u64)(u32)(t | 0x04000000);
        }
    }

    {
        int d = D_001A72DC;

        D_001390B0[10] = (u64)(long)(d >> 8) | 0x24020000 | (0xC800L << 19);
        D_001390B0[2] = (u64)((long)d >> 13) | (((((0xFFFFL << 16) | 0xFF00) << 20 | 0x8000) << 4));
    }
    func_0011AEA0(0);
}
