#include "include_asm.h"

extern void func_L02_003FDDE8(char *, int);
extern int func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(float, float, long long, char *, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_L02_003F9B70(int);
extern unsigned char D_001395B8[0x100];
extern unsigned char D_US2_001A7BBC;
extern int D_US2_L02_001B1460[2] __attribute__((sda));
extern float D_US2_L02_001B1458 __attribute__((sda));
extern int D_US2_L02_001B145C __attribute__((sda));
extern int D_US2_L02_001B1478 __attribute__((sda));
extern int D_US2_L02_001B147C __attribute__((sda));
extern int D_US2_L02_001B1480 __attribute__((sda));
extern int D_US2_L02_001B1484 __attribute__((sda));
extern int D_US2_L02_001B1488 __attribute__((sda));
extern int D_US2_L02_001B148C __attribute__((sda));
extern int D_US2_L02_001B1490 __attribute__((sda));
extern int D_US2_L02_001B1498 __attribute__((sda));
extern int D_US2_L02_001B14A8 __attribute__((sda));
extern int D_US2_L02_001B149C;
extern int D_US2_L02_001B14A0;
extern int D_US2_L02_001B14A4;
extern float D_US2_L02_001B3E04;
extern int D_US2_L02_001B3E00;
extern char D_US2_L02_001B11E8[];
extern char D_US2_L02_0028EA10[];

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_US2_L02_001B3E00;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* func_US2_L02_00400E04, the v2.00 copy of func_PAL_L02_00403FF0 (src/pal/levels/02_maktar_nebula/
   L02_00403FF0-g8.c), itself the PAL copy of func_L02_003FF6E8: the same C with this release's data
   and text ids 0x2DDB, 0x2DDC, 0x2DF8, 0x2DF4 and 0x2DDD. The first x is taken per language from
   D_US2_L02_001B1460, as in PAL. Its data is named D_US2_L02_<v2.00 address>. */
void func_US2_L02_00400E04(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    func_L02_003FDDE8(a0, 0);
    half = 0.5f;
    state = *(char **)(a0 + 0x68);
    text = (char *)func_00288FB8(0x2DDB);
    one = 1;
    s = D_US2_L02_001B3E04;
    x = (float)D_US2_L02_001B1460[D_US2_001A7BBC];
    r0 = scaled_coord(D_US2_L02_001B1478, s, half, one);
    func_0027F640(x, (float)r0, D_US2_L02_001B145C, text, D_US2_L02_001B1458, -1,
                  func_0027C878(1), D_US2_L02_0028EA10);
    s = D_US2_L02_001B3E04;
    r1 = scaled_coord(D_US2_L02_001B1498, s, half, one);
    r2 = scaled_coord(D_US2_L02_001B149C, s, half, one);
    r3 = scaled_coord(D_US2_L02_001B1484, s, half, one);
    func_002802E0(buf1, r1, r2, D_US2_L02_001B14A0, D_US2_L02_001B14A4, D_US2_L02_001B1480, r3,
                  D_US2_L02_001B14A8, 3);
    if (*(short *)(state + 0x118) == 0 && D_001395B8[func_L02_003F9B70(0)] < 2) {
        text = (char *)func_00288FB8(0x2DDC);
        func_00280270(buf1, D_US2_L02_001B147C, text, func_001157AC(text));
    } else {
        text = (char *)func_00288FB8(0x2DF8);
        msg = (char *)func_00288FB8(0x2DF4);
        func_00115DA8(buf2, D_US2_L02_001B11E8, text, *(int *)(state + 0x110), msg);
        func_00280270(buf1, D_US2_L02_001B147C, buf2, func_001157AC(buf2));
    }
    text = (char *)func_00288FB8(0x2DDD);
    {
        float half = 0.5f;
        int one = 1;

        s = D_US2_L02_001B3E04;
        r1 = scaled_coord(D_US2_L02_001B1498, s, half, one);
        r2 = scaled_coord(D_US2_L02_001B149C, s, half, one);
        r3 = scaled_coord(D_US2_L02_001B1490, s, half, one);
        func_002802E0(buf1, r1, r2, D_US2_L02_001B14A0, D_US2_L02_001B14A4, D_US2_L02_001B148C, r3,
                      D_US2_L02_001B14A8, 3);
    }
    func_00280190(buf1, D_US2_L02_001B1488, text, func_001157AC(text));
}
