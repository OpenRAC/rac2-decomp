/* functional: high. Written from the assembly: same reads, writes and calls with the same arguments in the same order and the same return value; the 128-bit lq/sq and 64-bit ld/sd copies are plain word copies, and the moby-list walk is a do/while with the same exits. Unrun blocks (the I(d,648) paths, the 24.0 distance check, the hit/moby-list walk, the <90.0 and fired tails) read against retail. */
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define SH(p,o) (*(short *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))

/* retail copies these with lq/sq (16 bytes) and ld/sd (8 bytes) */
#define qcopy(dst, src) do { int *qd_ = (int *)(dst); const int *qs_ = (const int *)(src); \
    qd_[0] = qs_[0]; qd_[1] = qs_[1]; qd_[2] = qs_[2]; qd_[3] = qs_[3]; } while (0)
#define dcopy(dst, src) do { int *qd_ = (int *)(dst); const int *qs_ = (const int *)(src); \
    qd_[0] = qs_[0]; qd_[1] = qs_[1]; } while (0)

extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_002A89A8(void *, int, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_00321F60(char *);
extern int func_002A8508(int, int);
extern int func_002B3BA8(void *, int, int, int, float, float);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_002A6C58(void *, int, int);
extern void func_00321E28(char *);

extern char D_001BAFA0[];
extern char *D_001B1C4C;   /* 128-byte records; the position is at +48 */
extern char D_001B5340[];
extern int D_001B1B78;
extern char *D_001B1B5C;   /* moby array, 256 bytes each */
extern short *D_001EE5A0[];

int func_003216E8(char *self)
{
    float matrix[16];
    char *d = P(self, 104);
    char *piece;
    int result;
    int fired;

    if (B(self, 32) == 0) {
        F(self, 44) = F(self, 44) * 1.100000023841858f;
        B(self, 126) = B(self, 126) | 1;
        P(d, 24) = d + 272;
        F(d, 644) = F(d, 644) * 0.01745329424738884f;
        B(d, 72) = (unsigned char)func_00283CF0(20.0f);
        B(d, 74) = (unsigned char)func_00283CF0(16.0f);
        if (func_002A77E0(2) == 1)
            H(self, 52) = H(self, 52) | 0x8000;

        F(d, 144) = 0.5f;
        F(d, 148) = 0.5f;
        F(d, 276) = 0.5f;
        I(d, 704) = -1;
        B(d, 119) = 24;
        B(d, 112) = 15;
        I(d, 168) = 5;
        B(d, 113) = 19;
        B(d, 114) = 21;
        B(d, 118) = 23;
        F(d, 124) = 0.10000000894069672f;
        F(d, 128) = 0.06666667014360428f;
        F(d, 136) = 0.008333333767950535f;
        F(d, 140) = 0.004166666883975267f;
        B(d, 211) = 0xFF;
        F(d, 272) = 0.800000011920929f;
        F(d, 284) = 0.4000000059604645f;
        F(d, 288) = 1.134464144706726f;
        F(d, 320) = 0.523598849773407f;
        F(d, 316) = 0.0055555556900799274f;
        P(d, 344) = d + 976;
        P(d, 348) = d + 1104;
        F(d, 132) = 0.004166666883975267f;
        F(d, 156) = 0.4000000059604645f;
        B(d, 204) = 0xFF;
        B(d, 205) = 0xFF;
        B(d, 206) = 0xFF;
        B(d, 207) = 0xFF;
        B(d, 210) = 0xFF;
        F(d, 280) = 0.4000000059604645f;
        func_002B60B0(self, 0.004444444552063942f, 0.13333334028720856f,
                      0.0011635529808700085f, 0.10471977293491364f);

        qcopy(d + 512, self + 16);
        B(d, 46) = 1;
        I(d, 640) = 0;
        F(d, 528) = 1.0f;
        F(d, 540) = 5.0f;
        F(d, 544) = 10.0f;
        F(d, 664) = (float)B(d, 52);
        B(d, 40) = 3;
        func_0029FCC0(self, 0, d + 896);
        F(d, 904) = F(d, 904) + 20.0f;
        func_0029FCC0(self, 0, d + 912);
        if (func_002761F8(d + 912, d + 896, 0, self, 0))
            qcopy(d + 896, D_001BAFA0);

        if (I(d, 636) == 0 && I(d, 648) == -1) {
            F(self, 24) = func_002A89A8(self + 16, 0, 0.5f);
            func_002A7750(self, 1, 0);
            if (B(self, 67) != 0)
                func_002A7470(self, 0, 0, 0);
        } else {
            func_002A7750(self, 3, 2);
            if (B(self, 67) != 11)
                func_002A7470(self, 11, 0, 0);
            I(self, 152) = 0;
            F(d, 48) = 2.5f;
            piece = func_0029EFD0(2743);
            P(d, 684) = piece;
            if (piece == 0)
                return 1;
            B(piece, 48) = B(self, 48);
            H(P(d, 684), 50) = H(self, 50);
            B(P(d, 684), 49) = 1;
            dcopy(P(d, 684) + 56, self + 56);
            H(P(d, 684), 52) = H(P(d, 684), 52) | 0x41;
            qcopy(P(d, 684) + 16, self + 16);
            func_002A0F48(P(d, 684));
        }

        if (I(d, 648) != -1) {
            func_002A7750(self, 2, 0);
            qcopy(d + 896, D_001B1C4C + I(d, 648) * 128 + 48);
            B(self, 48) = 128;
        }
    }

    if (B(self, 49) != 0 && func_00282E48(self + 16, D_001B5340) < 24.0f) {
        func_002A93B0(self);
        B(self, 111) = 22;
    }

    func_0029FCC0(self, 0, d + 912);
    func_0029FCC0(self, 1, d + 928);
    func_0029FCC0(self, 2, d + 944);
    func_0029FC20(self, 3, matrix);
    func_00282C88(d + 960);
    I(d, 968) = 0;
    F(d, 960) = 0.25f;
    func_002830C0(d + 960, d + 960, matrix);
    func_00282CC0(d + 960, d + 960, matrix + 12);

    fired = (B(d, 46) == 2);
    result = func_002B0ED8(self, d + 96, 0);
    if (result != 0 || fired) {
        F(d, 48) = 0.5f;
        if (result == 5) {
            I(d, 240) = 0;
            F(d, 244) = 0.8377581834793091f;
        }
        func_00321F60(self);
        if ((result == 4 || result == 5 || fired)
            && !(D_001B1B78 < (int)B(self, 33))
            && func_002A8508(B(self, 33), -1) >= 2) {
            short *list = D_001EE5A0[B(self, 33)];
            do {
                char *moby = D_001B1B5C + ((*(unsigned short *)list & 0x7FFF) << 8);
                short kind = SH(moby, 170);
                if (kind == 2826) {
                    char *sub = P(moby, 104);
                    if (I(sub, 660) == 0) {
                        I(sub, 660) = 1;
                        break;
                    }
                } else if (kind == 2827) {
                    char *sub = P(moby, 104);
                    if (I(sub, 660) == 0) {
                        I(sub, 660) = 1;
                        if (I(d, 668) == 0)
                            break;
                    }
                }
            } while (*list++ >= 0);
        }
    }

    I(d, 600) = func_002B3BA8(self, I(d, 592), 0, 0, F(d, 616), 10.0f);
    I(d, 604) = func_002B3BA8(self, I(d, 596), 0, 0, F(d, 620), 10.0f);

    if (F(self, 24) < 90.0f) {
        func_002AC728(self, self + 16, -1, 0.5f, 13.0f);
        func_002A6C58(self, 0, 3);
        return 1;
    }
    if (!fired)
        return 0;
    func_00321E28(self);
    return 1;
}
