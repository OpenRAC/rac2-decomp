/* functional: medium. Written from the assembly: same reads, writes and calls with the same arguments in the same order; the divide-by-zero checks retail emits for the divisions by W(0x34) and by a stored count are dropped. */
extern char D_001A63A8[];       /* the state block */
extern char D_001AA1B0[];
extern char D_001AA1C0[];
extern char D_001AA1D0[];

extern int func_00282948(void *);
extern void func_002B6E78(short, short, short);
extern void func_002B6F70(short, short, short);
extern int func_002B7088(short, short, short, short);
extern void func_002B6958(int, int, int, int);
extern void func_002B6D80(short, short, short);
extern void func_002B7380(void *);
extern void func_002B7B18(int, int, int);
extern void func_00132B88(int, int, int, int, int, int, int, int);
extern void func_00133400(int);
extern int func_00133580(int);
extern void func_0026FEB8(void *, ...);
extern void func_002B7FF0(void);

#define S D_001A63A8
#define H(o)  (*(short *)(S + (o)))
#define HU(o) (*(unsigned short *)(S + (o)))
#define W(o)  (*(int *)(S + (o)))
#define B(o)  (*(unsigned char *)(S + (o)))

void func_002B7578(void)
{
    int a2, a0, a1, v;
    void (*cb)(int, int);
    int fn;

    if (B(7) != 0)
        return;

    if (!(H(0x50) & 0x8000) && !(H(0x4E) & 0x8000)) {
        if (W(0x44) == 0) {
            if ((HU(0x4C) & 1) && H(0x3C) == -1)
                func_002B6E78(H(0x48), (short)HU(0x4C), H(0x4A));
        } else if (W(0x44) != -1 && H(0x4E) == 8) {
            func_002B6F70(H(0x48), H(0x4C), H(0x4A));
        }
    }

    if (func_00282948(S + 0x38) != 0) {
        a0 = H(0x3C);
        if (a0 != -1 && H(0x2C) == 0) {
            if (H(0x48) == a0) {
                H(0x3C) = -1;
            } else if (H(0x3E) == -1) {
                if (H(0x4E) & 0x8000) {
                    H(0x4E) = 5;
                    H(0x2C) = 3;
                } else {
                    H(0x2C) = 6;
                    W(0xA4) = 0xF;
                    W(0x34) = 0xF;
                }
                W(0x38) = 0x12C;
            } else if (func_002B7088(a0, H(0x3E), H(0x4C), H(0x4A)) != 0) {
                W(0x38) = 0x1A4;
            }
        }
    }

    a0 = W(0x24);
    if (a0 >= 0) {
        if (W(0x68) == 0) {
            func_002B6958(a0, 0, W(0x28), 0x400);
            W(0x28) = 0;
            W(0x24) = -1;
        } else if ((unsigned)(HU(0x72) - 6) >= 2) {
            H(0x72) = 5;
        }
    }

    if (H(0x4E) != 9 && W(0x44) != -1
        && !(H(0x50) & 0x8000) && !(H(0x4E) & 0x8000)) {
        if (H(0x3E) != -1 && ((H(0x98) & 0x8000) || (H(0x96) & 0x8000)))
            goto final;
        if ((unsigned)((short)(HU(0x2C) - 2)) <= 4u) {
            switch ((short)(HU(0x2C) - 2)) {
            case 0:
                a2 = (H(0x4A) * (W(0x34) - (W(0x30) - W(0xA4)))) / W(0x34);
                if (a2 > 0 && ((H(0x96) == 4 && H(0x9C) != 0) || W(0x8C) != 0)
                    && W(0x44) != 0) {
                    if (H(0x4E) != 9) {
                        a0 = W(0x44);
                        W(0x44) = -1;
                        func_00132B88(a0, 5, a2, 0, 0, 0, (int)func_002B7FF0, (int)(S + 0x44));
                    }
                } else {
                    H(0x2C) = 3;
                    H(0x4E) = 5;
                }
                break;
            case 1:
                if (H(0x4E) == 0 && (H(0x9C) != 0 || W(0x8C) == 0)) {
                    func_002B6D80(H(0x3C), H(0x4C), H(0x4A));
                    H(0x2C) = 4;
                    H(0x3C) = -1;
                }
                break;
            case 2:
                if (H(0x4E) == 3
                    && (W(0xA4) < W(0x34) || H(0x96) != 4 || (H(0x9C) == 0 && W(0x8C) == 0))) {
                    func_00133400(W(0x44));
                    H(0x2C) = 5;
                    H(0x4E) = 8;
                }
                break;
            case 3:
                if (H(0x96) != 4 || H(0x9C) == 0)
                    H(0x2C) = 0;
                break;
            case 4:
                a0 = W(0xA4);
                a2 = (H(0x4A) * a0) / W(0x34);
                a0 = W(0x44);
                W(0x44) = -1;
                func_00132B88(a0, 5, a2, 0, 0, 0, (int)func_002B7FF0, (int)(S + 0x44));
                if (func_00282948(S + 0xA4) != 0) {
                    H(0x4E) = 5;
                    H(0x2C) = 3;
                }
                break;
            }
        }
    }

final:
    func_002B7380(S + 0x44);
    func_002B7380(S + 0x8C);
    func_002B7380(S + 0x68);
    if (B(6) != 0) {
        func_0026FEB8(D_001AA1B0);
        if (func_00133580(1) != 0)
            return;
        H(4) = 0;
        B(6) = 0;
        func_0026FEB8(D_001AA1C0);
        fn = W(0x18);
        if (fn != 0) {
            a1 = W(0x1C);
            W(0x1C) = 0;
            W(0x18) = 0;
            func_0026FEB8(D_001AA1D0);
            ((void (*)(int, int))fn)(a1, 0);
        }
        return;
    }
    v = H(4);
    if (v == 2) {
        H(4) = 0;
        func_002B7B18(W(0x14), W(8), W(0x10));
        if (H(4) == 0)
            H(4) = v;
    }
}
