/* func_US2_L11_0044709C, the USA v2.00 copy of func_L11_004456A0: the same C, with v2.00's message ids,
   and the x position read from an int table indexed by the byte D_US2_001A7BBC. */
#include "common.h"

extern void func_L11_00443940(char *, int);
extern int func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(float, float, long long, char *, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern int func_L11_0043E108(int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern int func_00115DA8(char *, char *, ...);

extern float D_L11_001B1808 __attribute__((sda));
extern int D_L11_001B180C __attribute__((sda));
extern int D_L11_001B1810[] SDATA(D_L11_001B1810);
extern unsigned char D_US2_001A7BBC;
extern int D_L11_001B1814 __attribute__((sda));
extern int D_L11_001B1818 __attribute__((sda));
extern int D_L11_001B181C __attribute__((sda));
extern int D_L11_001B1820 __attribute__((sda));
extern int D_L11_001B1824 __attribute__((sda));
extern int D_L11_001B1828 __attribute__((sda));
extern int D_L11_001B182C __attribute__((sda));
extern int D_L11_001B1830 __attribute__((sda));
extern int D_L11_001B1834;
extern int D_L11_001B1838;
extern int D_L11_001B183C;
extern int D_L11_001B1840 __attribute__((sda));
extern float D_L11_001B3E04;
extern char D_L11_001B15A0[];
extern char D_L11_002A3AD0[];
extern u8 D_001395B8[0x100];

extern int D_L11_001B3E00;

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

void func_US2_L11_0044709C(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    func_L11_00443940(a0, 0);
    half = 0.5f;
    state = *(char **)(a0 + 0x68);
    text = (char *)func_00288FB8(0x2DDB);
    one = 1;
    s = D_L11_001B3E04;
    x = (float)D_L11_001B1810[D_US2_001A7BBC];
    r0 = scaled_coord(D_L11_001B1814, s, half, one);
    func_0027F640(x, (float)r0, D_L11_001B180C, text, D_L11_001B1808, -1,
                  func_0027C878(1), D_L11_002A3AD0);
    s = D_L11_001B3E04;
    r1 = scaled_coord(D_L11_001B1830, s, half, one);
    r2 = scaled_coord(D_L11_001B1834, s, half, one);
    r3 = scaled_coord(D_L11_001B1820, s, half, one);
    func_002802E0(buf1, r1, r2, D_L11_001B1838, D_L11_001B183C, D_L11_001B181C, r3,
                  D_L11_001B1840, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && D_001395B8[func_L11_0043E108(0)] < 2) {
        text = (char *)func_00288FB8(0x2E2C);
        func_00280270(buf1, D_L11_001B1818, text, func_001157AC(text));
    } else if (*(s16 *)(state + 0x1E8) == 1 && D_001395B8[func_L11_0043E108(1)] < 2) {
        text = (char *)func_00288FB8(0x2E2D);
        func_00280270(buf1, D_L11_001B1818, text, func_001157AC(text));
    } else {
        text = (char *)func_00288FB8(0x2DF8);
        msg = (char *)func_00288FB8(0x2DF4);
        func_00115DA8(buf2, D_L11_001B15A0, text, *(int *)(state + 0x1E0), msg);
        func_00280270(buf1, D_L11_001B1818, buf2, func_001157AC(buf2));
    }
    text = (char *)func_00288FB8(0x2DDD);
    {
        float half = 0.5f;
        int one = 1;

        s = D_L11_001B3E04;
        r1 = scaled_coord(D_L11_001B1830, s, half, one);
        r2 = scaled_coord(D_L11_001B1834, s, half, one);
        r3 = scaled_coord(D_L11_001B182C, s, half, one);
        func_002802E0(buf1, r1, r2, D_L11_001B1838, D_L11_001B183C, D_L11_001B1828, r3,
                      D_L11_001B1840, 3);
    }
    func_00280190(buf1, D_L11_001B1824, text, func_001157AC(text));
}
