/* functional: low (SAME on one captured call only, most paths unexercised). Written from the assembly: same reads, writes and calls with the same arguments in the same order; the three func_00294D80 results are stored as 64-bit values as in retail. */
extern char D_001F2840[];       /* C: the menu/pad block */
extern char D_001C4FA0[];       /* Q: the selection state */
extern char D_00138180[];       /* P: the pad block, flags at +0x1C4 */
extern int D_00139768[];
extern char D_0014B540[];
extern int D_001A72D4;
extern int D_001A7478;
extern int D_001A79F0;
extern int *D_001AA4F0;
extern unsigned char D_001A7AFD;
extern unsigned char D_001A7BE8[];
extern char D_001A63A8[];
extern char D_001BAD40[];

extern void func_00295D00(void);
extern void func_002C9E60(int);
extern void func_00288AA0(void *, int, int, int);
extern void func_00288BE8(void *);
extern int func_00295A10(int);
extern void func_00295C50(int);
extern void func_002E5E58(int, int, int);
extern void func_0029D830(void);
extern int func_00295828(int);
extern int func_00295A80(void);
extern void func_00295788(int, int);
extern void func_0029D4D0(int, int);
extern int func_002DE550(int);
extern void func_00295BE8(int, int, int, int);
extern void func_00297730(int, int, int, int);
extern void func_00297400(int, int, int);
extern long long func_00294D80(int, int, int, int, int, int);
extern void func_0029D0E0(void);
extern void func_002DE618(int);
extern void func_0029DEA8(int, int);
extern int func_002956E8(void);
extern int func_002958B8(void);
extern void func_002EEED0(int, int, int, int, int);
extern void func_002B7B18(int, int, int);

#define CW(o) (*(int *)(D_001F2840 + (o)))
#define QW(o) (*(int *)(D_001C4FA0 + (o)))
#define PW(o) (*(int *)(D_00138180 + (o)))

int func_002D6F38(void)
{
    int s2, s0, s1, s3, s4, s5, s6, s7;
    int a1, base, X, Y, Z, k, idx, a3, bit;
    long long r;

    func_00295D00();

    if (CW(0x14) == 0x25E680) {
        QW(0x28) = 1;
    } else {
        s2 = QW(0x230);
        if (PW(0x1C4) & 0xD00) {
            if (CW(0x134) == 0)
                return 1;
        }
        if (PW(0x1C4) & 0x10) {
            int v = *(int *)(CW(0x14) + 0xE0);
            if (v != 0) {
                CW(0x18) = v;
                return 0;
            }
            return CW(0x134) == 0 ? -1 : 0;
        }
        if (PW(0x1C4) & 0x40)
            CW(0x18) = 0x25A498;

        if (PW(0x1C4) & 0x20) {
            a1 = QW(0x230);
            if (a1 >= 0 && *(unsigned char *)(D_001F2840 + 0xDB) == 0) {
                s2 = (a1 == 0) ? 0x15 : a1;
                if (s2 == 0x18)
                    s2 = 0;
                a1 = QW(0x230);
                if (a1 < 0)
                    return 1;
                if (((D_00139768[a1 >> 2] >> (a1 & 0x1F)) & 1) == 0)
                    return 1;
                D_001A72D4 = CW(0x28);
                func_002C9E60(0);
                CW(0x140) = D_001A7478;
                CW(0x100) = CW(0x14);
                CW(0x104) = CW(0x8);
                CW(0xF4) = QW(0x230);
                D_001A7478 = 2;
                func_00288AA0(D_001BAD40, s2, CW(0x14), 2);
                func_00288BE8(D_001BAD40);
                return 1;
            }
        }

        s0 = func_00295A10(QW(0x230));
        if (s0 >= 0) {
            if (PW(0x1C4) & 8) {
                if (s0 < 0x1B) {
                    a1 = D_001AA4F0[s0 + 1];
                    if (a1 != 0)
                        func_00295C50(a1);
                }
            }
            if (PW(0x1C4) & 4) {
                if (s0 != 0) {
                    a1 = D_001AA4F0[s0 - 1];
                    if (a1 != 0)
                        func_00295C50(a1);
                }
            }
        }
        if (QW(0x230) != s2) {
            func_002E5E58(3, 0, 0);
            func_0029D830();
        }
        if (CW(0x14) == 0x25E680)
            QW(0x28) = 1;
    }

    s7 = QW(0x230);
    if (D_001A7AFD != 0)
        s7 = s7 + 0x100;
    s0 = func_00295828(s7);
    if (QW(0x230) != QW(0x234) && s0 != -1) {
        s1 = func_00295A80();
        if (QW(0x288) != 0 && s1 > 0) {
            func_00295788(s1, 0);
            if (s0 == 0)
                s0 = s1;
        }
        func_0029D4D0(QW(0x288 + 4 * s0), QW(0x248));
        s2 = QW(0x248);
        s6 = s2 + *(int *)(s2 + 8);
        s5 = s2 + *(int *)(s2 + 0xC);
        s4 = func_002DE550(0);
        if (s4 != 0) {
            a3 = QW(0x248);
            if (QW(0x230) == D_001A79F0) {
                func_00295BE8(s5, s6, s5, QW(0xC));
            } else {
                k = QW(0x230);
                if (D_001A7BE8[k] != 0) {
                    func_00297730(s4, 0x18D278 + (k << 11), a3 + *(int *)(s2 + 4), a3);
                } else {
                    a1 = a3 + *(int *)(s2 + 0) + 8;
                    func_00297400(s4, a1, a1);
                }
                func_00295BE8(s5, s6, s5, s4);
            }
        }
        X = QW(0x248) + *(int *)(s2 + 0x10);
        Y = QW(0x248) + *(int *)(s2 + 0x18);
        Z = QW(0x248) + *(int *)(s2 + 0x14);
        r = func_00294D80(7, 7, X + 0x20, X + 0x420, QW(0x250), QW(0x254));
        *(long long *)(D_001C4FA0 + 0x268) = r;
        r = func_00294D80(7, 7, X + 0x20, Z + 0x420, QW(0x250), QW(0x258));
        *(long long *)(D_001C4FA0 + 0x270) = r;
        r = func_00294D80(7, 7, X + 0x20, Y + 0x420, QW(0x250), QW(0x25C));
        *(long long *)(D_001C4FA0 + 0x278) = r;
        if (s4 != 0)
            func_00294D80(9, 9, s5, s5, 0x3FF000, QW(0x24C));
        func_0029D0E0();
        if (s4 != 0)
            func_002DE618(s4);
        a1 = QW(0x230);
        QW(0x288) = s6;
        QW(0x234) = a1;
        func_0029DEA8(a1, 0);
    }

    if (*(short *)(D_001A63A8 + 4) == 0) {
        if (QW(0x2B0) != -1) {
            *(unsigned char *)(D_001F2840 + 0xDB) = 0;
            QW(0x29C + 4 * QW(0x2B0)) ^= 0x1000;
            QW(0x2B0) = -1;
        }
    }

    s4 = -1;
    if (QW(0x28) != 0 && *(short *)(D_001A63A8 + 4) == 0) {
        s4 = func_002956E8();
        if (s4 != -1) {
            s3 = func_002958B8();
            if (s3 != -1) {
                bit = (D_001A79F0 + QW(0x23C)) ? 0x100 : 0;
                if (bit == s3) {
                    func_002EEED0(QW(0x288 + 4 * s4), QW(0x238), 0, QW(0x240), 0);
                    QW(0x2B4 + 4 * s4) = QW(0x240);
                } else {
                    char *tbl = D_0014B540;
                    int a2v;
                    if (s3 & 0x100) {
                        idx = s3 ^ 0x100;
                        a3 = *(int *)(tbl + 0x15D0 + idx * 8);
                        a2v = *(int *)(tbl + 0x15D4 + idx * 8);
                    } else {
                        a3 = *(int *)(tbl + 0x14F0 + s3 * 8);
                        a2v = *(int *)(tbl + 0x14F4 + s3 * 8);
                    }
                    func_002B7B18(QW(0x288 + 4 * s4), a3 + *(int *)(tbl + 0x36C), a2v);
                    QW(0x2B4 + 4 * s4) = (int)(a2v << 11) >> 4;
                    *(unsigned char *)(D_001F2840 + 0xDB) = 1;
                }
                QW(0x29C + 4 * s4) = s3 | 0x1000;
                QW(0x2B0) = s4;
            }
        }
    }

    s0 = func_00295828(s7);
    if (QW(0x230) != QW(0x234) && *(short *)(D_001A63A8 + 4) == 0 && s0 == -1 && s4 == s0)
        func_00295A80();
    return 0;
}
