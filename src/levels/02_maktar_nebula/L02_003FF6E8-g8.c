#include "include_asm.h"

typedef unsigned char u8;
typedef short s16;

extern void func_L02_003FDDE8(char *, int);
extern int func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(float, float, long long, char *, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern int func_L02_003F9B70(int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern int func_00115DA8(char *, char *, ...);

extern float D_L02_001B1438 __attribute__((sda));
extern int D_L02_001B143C __attribute__((sda));
extern int D_L02_001B1440 __attribute__((sda));
extern int D_L02_001B1444 __attribute__((sda));
extern int D_L02_001B1448 __attribute__((sda));
extern int D_L02_001B144C __attribute__((sda));
extern int D_L02_001B1450 __attribute__((sda));
extern int D_L02_001B1454 __attribute__((sda));
extern int D_L02_001B1458 __attribute__((sda));
extern int D_L02_001B145C __attribute__((sda));
extern int D_L02_001B1460 __attribute__((sda));
extern int D_L02_001B1464;
extern int D_L02_001B1468;
extern int D_L02_001B146C;
extern int D_L02_001B1470 __attribute__((sda));
extern float D_L02_001B3E04;
extern char D_L02_001B1228[];
extern char D_L02_0028E990[];
extern u8 D_001395B8[0x100];

extern int D_L02_001B3E00;

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* Level 2 copy of func_L11_004456A0 (src/levels/11_joba/L11_004456A0-g8.c), transcribed
   with this level's data. */
void func_L02_003FF6E8(char *a0) {
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
    text = (char *)func_00288FB8(0x2F45);
    one = 1;
    s = D_L02_001B3E04;
    x = (float)D_L02_001B1440;
    r0 = scaled_coord(D_L02_001B1444, s, half, one);
    func_0027F640(x, (float)r0, D_L02_001B143C, text, D_L02_001B1438, -1,
                  func_0027C878(1), D_L02_0028E990);
    s = D_L02_001B3E04;
    r1 = scaled_coord(D_L02_001B1460, s, half, one);
    r2 = scaled_coord(D_L02_001B1464, s, half, one);
    r3 = scaled_coord(D_L02_001B1450, s, half, one);
    func_002802E0(buf1, r1, r2, D_L02_001B1468, D_L02_001B146C, D_L02_001B144C, r3,
                  D_L02_001B1470, 3);
    if (*(s16 *)(state + 0x118) == 0 && D_001395B8[func_L02_003F9B70(0)] < 2) {
        text = (char *)func_00288FB8(0x2F46);
        func_00280270(buf1, D_L02_001B1448, text, func_001157AC(text));
    } else {
        text = (char *)func_00288FB8(0x2F62);
        msg = (char *)func_00288FB8(0x2F5E);
        func_00115DA8(buf2, D_L02_001B1228, text, *(int *)(state + 0x110), msg);
        func_00280270(buf1, D_L02_001B1448, buf2, func_001157AC(buf2));
    }
    text = (char *)func_00288FB8(0x2F47);
    {
        float half = 0.5f;
        int one = 1;

        s = D_L02_001B3E04;
        r1 = scaled_coord(D_L02_001B1460, s, half, one);
        r2 = scaled_coord(D_L02_001B1464, s, half, one);
        r3 = scaled_coord(D_L02_001B145C, s, half, one);
        func_002802E0(buf1, r1, r2, D_L02_001B1468, D_L02_001B146C, D_L02_001B1458, r3,
                      D_L02_001B1470, 3);
    }
    func_00280190(buf1, D_L02_001B1454, text, func_001157AC(text));
}
