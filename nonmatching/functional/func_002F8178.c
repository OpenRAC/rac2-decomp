/* functional: high. Written from the assembly with the near miss's structure, one fix: the 5 stored before func_0026F748 goes to D_001A8BB0 (retail forms 0x1B0000-0x7450; the near miss named 0x1B8BB0). Shop fields are plain offsets from D_0021F240; the 16-byte lq/sq copies are word copies. */
extern char D_0021F240[];          /* the shop, 0x760 bytes */
extern char D_001BAEC0[];          /* load buffers: +0x0C, +0x10 */
extern char D_00189E20[];          /* +0x1248 hero mode, +0x22B5, +0x22BC flags */
extern char D_001B5340[];
extern char D_001C2AC0[];
extern float D_001AD1E0[4], D_001AD1F0[4], D_001AD210[4], D_001AD220[4];
extern float D_001AD234, D_001AD238;
extern float D_001B2280, D_001B15A0;
extern short D_001A7A18;
extern short D_00152CE4;
extern unsigned char D_001A7BB1, D_001A7BB4;
extern int D_001A7B90, D_001A7AF0, D_001A7340, D_001A7344;
extern int D_001AD1C0, D_001AD1C4, D_001AD230;
extern int D_001B2238, D_001B2244, D_001B2248, D_001B2284, D_001B2288, D_001B228C, D_001B2290,
    D_001B2294, D_001B2298;
extern int D_001A8BB0;
extern int D_001B15A4;

extern void func_00282A60(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_002A0F48(void *);
extern void func_002F9778(void);
extern void func_00132AF8(int);
extern void func_002B72E8(int);
extern int func_00132028(void);
extern void func_002F6608(int);
extern void func_002F71B8(void);
extern void func_002F73A8(void);
extern void func_002F7738(void);
extern void func_0028E408(void);
extern void func_0029B698(int);
extern void func_0029B6D0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00288EA0(void);
extern unsigned int func_0026F748(int, int);
extern void func_0026F720(void);
extern void func_00283098(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_00335438(void *, void *, int, int, int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_00272368(void);

#define S_I(o) (*(int *)(D_0021F240 + (o)))
#define S_F(o) (*(float *)(D_0021F240 + (o)))
#define QCOPY(d, s) do { int *qd_ = (int *)(d); const int *qs_ = (const int *)(s); \
    qd_[0] = qs_[0]; qd_[1] = qs_[1]; qd_[2] = qs_[2]; qd_[3] = qs_[3]; } while (0)

/* Opens a shop: clears its state, picks its mode from a small number (0..3, spawning the
   vendor moby) or from the vendor moby passed in, resets the list and timers, builds the
   list for the mode, starts the music and sounds, and places the shop camera. */
void func_002F8178(char *moby)
{
    int mode = (int)(unsigned long)moby;
    int count, half, visible, v;
    float vec[4];

    func_00282A60(D_0021F240, 0, 0x760);
    if (D_001A7B90 != 0)
        D_001B2280 = 1.0769231f;
    else
        D_001B2280 = 1.0f;
    S_I(0x60) = 0;
    D_001AD1C0 = D_001A7A18;

    if ((unsigned long)moby < 4) {
        S_I(0x60) = 1;
        moby = func_0029EFD0(11);
        *(short *)(moby + 0x32) = 64;
        if (D_001A7BB1 != 0)
            QCOPY(vec, D_001AD1F0);
        else
            QCOPY(vec, D_001AD1E0);
        vec[2] = -vec[2];
        func_00282CC0(moby + 0x10, D_001B5340, vec);
        func_00282C88(moby + 0xF0);
        *(float *)(moby + 0xF8) = 3.1415927f;
        func_002A0F48(moby);
        S_I(0x60) = 1;
        S_I(0x744) = 0;
        moby[0x20] = 3;
        if (mode == 0) {
            S_I(0x50) = 0;
            S_I(0x744) = 0;
        } else if (mode == 1) {
            S_I(0x50) = 1;
        } else if (mode == 2) {
            S_I(0x50) = 2;
            S_F(0xBC) = -1.5707964f;
            S_I(0xA4) = 0;
            S_I(0xB4) = 0;
            S_I(0xB8) = 0;
        } else {
            S_I(0x50) = 3;
        }
    } else if (*(short *)(moby + 0xAA) == 11) {
        S_I(0x744) = 0;
        v = *(int *)(*(char **)(moby + 0x68) + 0x94);
        if (v == 0) {
            S_I(0x50) = 0;
        } else if (v == 1) {
            S_I(0x50) = 1;
            func_002F9778();
        } else if (v == 4) {
            S_I(0x50) = 2;
        } else if (v == 2) {
            S_I(0x50) = 3;
        } else if (v == 3) {
            S_I(0x744) = 1;
            S_I(0x50) = 0;
        }
    } else if (*(short *)(moby + 0xAA) == 0x1309) {
        *(char **)(D_0021F240 + 0x28) = moby;
        S_I(0x50) = 2;
    } else if (*(short *)(moby + 0xAA) == 0xDDC) {
        *(char **)(D_0021F240 + 0x28) = moby;
        S_I(0x50) = 1;
        func_002F9778();
    }

    if (D_001AD1C4 != -1)
        S_I(0x50) = D_001AD1C4;
    v = D_001A7BB4 - 1;
    S_I(0x88) = 0;
    S_I(0x8C) = 0;
    S_I(0x38) = 0;
    S_I(0x44) = v;
    if (v < 0)
        S_I(0x44) = 0;
    S_I(0x68) = -1;
    D_001B2294 = 96;
    D_001AD234 = 0.8f;
    D_001AD238 = 1.0f;
    D_001B2298 = 85;
    S_I(0x78) = -1;
    S_I(0x7C) = -1;
    S_I(0x64) = 0;
    S_I(0x80) = 0;
    D_001B2244 = 0;
    S_I(0x84) = 0;
    D_001B2290 = 96;
    D_001B2248 = 0;
    D_001B2238 = 0;
    D_001AD230 = 0;
    D_001B2284 = 0;
    D_001B2288 = 0;
    D_001B228C = 0;
    func_00132AF8(93);
    func_002B72E8(0);
    func_00132028();

    if (S_I(0x50) == 0)
        func_002F6608(0);
    else if (S_I(0x50) == 3)
        func_002F71B8();
    else if (S_I(0x50) == 1)
        func_002F73A8();
    else if (S_I(0x50) == 2)
        func_002F7738();

    count = S_I(0x740);
    half = count / 2;
    visible = (2 < count) ? half : 1;
    S_I(0x80) = half;
    S_I(0x6C) = (visible - half) * 40;
    func_0028E408();
    if (S_I(0x50) != 2)
        func_0029B698(0x112A880);
    if (S_I(0x50) == 0 && S_I(0x144 + S_I(0x80) * 24) == 1 && *(int *)(D_00189E20 + 0x1248) != 10)
        func_0029B6D0(S_I(0x140 + S_I(0x80) * 24), 0x112A880);

    S_I(0x14) = *(int *)(D_001BAEC0 + 0x0C) + 0x60000;
    S_I(0x1C) = *(int *)(D_001BAEC0 + 0x10) + 0x60000 + D_001A7340 * D_001A7344 * 4;
    S_I(0x00) = 0;
    S_I(0x10) = *(int *)(D_001BAEC0 + 0x10) + 0x60000;
    S_I(0x08) = 0;
    S_I(0x0C) = 1;
    *(char **)(D_0021F240 + 0x28) = moby;
    func_002E5CF8(3, 17, moby);
    S_I(0x4C) = D_001A7AF0;
    S_I(0xA0) = D_00152CE4;
    func_00288EA0();
    D_001A8BB0 = 5;
    D_001B15A0 = 0.0f;
    D_001B15A4 = 0;
    func_0026F748(97, 1);
    *(char *)(D_00189E20 + 0x22B5) = 1;
    *(char *)(D_00189E20 + 0x22BC) = 1;
    func_0026F720();

    if (S_I(0x60) == 0) {
        if (D_001A7BB1 != 0)
            func_00283098(D_0021F240 + 0xD0, D_001AD1F0, *(char **)(D_0021F240 + 0x28) + 0xC0);
        else
            func_00283098(D_0021F240 + 0xD0, D_001AD1E0, *(char **)(D_0021F240 + 0x28) + 0xC0);
        func_00282CC0(D_0021F240 + 0xD0, D_0021F240 + 0xD0, *(char **)(D_0021F240 + 0x28) + 0x10);
        S_F(0xE8) = func_00283B98(*(float *)(*(char **)(D_0021F240 + 0x28) + 0xF8), 3.1415927f);
        func_00335438(D_0021F240 + 0xD0, D_0021F240 + 0xE0, 1, 0, 0);
        QCOPY(vec, D_0021F240 + 0xD0);
        if (S_I(0x50) == 2)
            vec[1] = vec[1] + 5.0f;
        func_00335370(vec);
        func_003353C8(D_0021F240 + 0xE0);
        func_00272368();
    }
    func_00283098(D_001C2AC0 + 0x10, D_001AD210, *(char **)(D_0021F240 + 0x28) + 0xC0);
    QCOPY(D_001C2AC0, D_001AD220);
    ((int *)(D_001C2AC0 + 0x30))[0] = 0;
    ((int *)(D_001C2AC0 + 0x30))[1] = 0;
    ((int *)(D_001C2AC0 + 0x30))[2] = 0;
    ((int *)(D_001C2AC0 + 0x30))[3] = 0;
    ((int *)(D_001C2AC0 + 0x20))[0] = 0;
    ((int *)(D_001C2AC0 + 0x20))[1] = 0;
    ((int *)(D_001C2AC0 + 0x20))[2] = 0;
    ((int *)(D_001C2AC0 + 0x20))[3] = 0;
}
