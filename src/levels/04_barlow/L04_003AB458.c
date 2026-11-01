#include "include_asm.h"

typedef unsigned short u16;

extern void func_00282978(void *);
extern void func_002A0488(void *, int, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002AB8C0(void *, void *);
extern void func_L00_002E6CF0(void *);
extern void func_L04_003A21F8(void *, int);
extern char D_L04_002AF6C0[];

extern void func_0029FCC0(void *, int, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L04_003E53D0(void *, void *);
extern void func_L04_003E55E0(void *, void *);

typedef struct L04_003E5318_BUF {
    float f[6];
    int z;
} L04_003E5318_BUF;

/* func_L04_003E5298 is defined in L02_003CE9A8-g8.c. */

typedef unsigned int TI2338 __attribute__((mode(TI)));
typedef struct {
    char pad[0x280];
    TI2338 position;
    char pad290[0x60];
    int slots[4];
    char pad300[6];
    unsigned char current;
} Private2338;
typedef struct {
    char pad[0x30];
    TI2338 position;
    char pad40[0x40];
} Record2338;
extern void func_00115484(void *, int, int);
extern void func_00282A28(void);
extern int func_002A7820(int, int);
extern char *D_L04_001B25CC __attribute__((sda));

void func_L04_003E5318(char *a0)
{
    char *s0 = a0;
    char *p = *(char **)(s0 + 0x68);
    char *q = *(char **)(p + 0x2AC);
    L04_003E5318_BUF buf;

    if (q != 0) {
        char *r = *(char **)(q + 0x68);

        func_0029FCC0(*(char **)(r + 0x288), 0, &buf);
        buf.f[4] = func_00283180(*(float *)(s0 + 0xF8)) * 0.1f;
        buf.f[5] = func_00283198(*(float *)(s0 + 0xF8)) * 0.1f;
        buf.z = 0;
        func_00282CC0(&buf, &buf, buf.f + 4);
        buf.f[2] = buf.f[2] - 0.05f;
        func_L04_003E53D0(s0, &buf);
        func_L04_003E55E0(s0, &buf);
    }
}

void func_L04_003E51F0(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);
    u16 v;

    func_002AB8C0(a0, s0 + 0x50);
    func_00282978(s0 + 0x2A0);
    func_00282978(s0 + 0x2A2);
    v = *(u16 *)(a0 + 0x96);
    if (v <= 0xFFFE) {
        *(u16 *)(a0 + 0x96) = v + 1;
    }
}

void func_L04_003E5250(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);

    if (*(char **)(s0 + 0x2AC) != 0) {
        func_002A7470(*(char **)(s0 + 0x2AC), 9, 0, 3);
        *(int *)(*(char **)(*(char **)(s0 + 0x2AC) + 0x68) + 0x27C) = 0;
        *(char **)(s0 + 0x2AC) = 0;
    }
}

void func_L04_003E7FE8(void)
{
    func_L04_003A21F8(D_L04_002AF6C0, 10);
}

typedef unsigned char u8;
typedef int s32;
typedef float f32;
extern u8 D_00188660[];
extern char D_00189EA0[];
extern s32 func_00342228(void *, s32);
extern s32 func_00382FF0(s32, s32, void *);
extern s32 func_0033D168(s32, s32);
extern void func_00382AF8(s32);
extern void func_003317E8(void *);
extern f32 func_0030EFA8(void *, void *);

void func_L04_003AB458(u8 *a0)
{
    u8 *s0 = *(u8 **)(a0 + 0x68);

    if (func_00342228(D_00189EA0, *(s32 *)s0) != 0) {
        u8 *p = D_00188660 + *(s32 *)(s0 + 8) * 0x70;
        if (*(u8 **)(p + 0x88) != a0 || *(u8 *)(p + 0x74) == 0) {
            *(s32 *)(s0 + 8) = func_00382FF0(0x17, 4, a0);
        }
    }
    if (func_0033D168(*(s32 *)(s0 + 4), -1) < 7) {
        s32 id = *(s32 *)(s0 + 8);
        if (id != -1) {
            u8 *p = D_00188660 + id * 0x70;
            if (*(u8 **)(p + 0x88) == a0 && *(u8 *)(p + 0x74) != 0)
                func_00382AF8(id);
        }
        *(s32 *)(s0 + 8) = -1;
        func_003317E8(a0);
    } else {
        u8 *p = D_00188660 + *(s32 *)(s0 + 8) * 0x70;
        if (*(u8 **)(p + 0x88) == a0 && *(u8 *)(p + 0x74) != 0) {
            if (func_0030EFA8(a0 + 0x10, D_00189EA0) > 50.0f) {
                s32 id = *(s32 *)(s0 + 8);
                if (id != -1) {
                    u8 *q = D_00188660 + id * 0x70;
                    if (*(u8 **)(q + 0x88) == a0 && *(u8 *)(q + 0x74) != 0)
                        func_00382AF8(id);
                }
                *(s32 *)(s0 + 8) = -1;
            }
        }
    }
}



void func_L04_003E22B0(char *a0, int a1, int a2, int a3, int a4)
{
    char *s2 = *(char **)(a0 + 0x68);

    if (*(char **)(s2 + 0x2AC) != 0) {
        func_002A7470(a0, a1, a3, a4);
        func_002A7470(*(char **)(s2 + 0x2AC), a2, a3, a4);
    } else if (*(unsigned char *)(a0 + 0x43) != a1) {
        func_002A7470(a0, a1, a3, a4);
    }
}

void func_L04_003E2338(char *a0)
{
    Private2338 *s4 = *(Private2338 **)(a0 + 0x68);
    int values[3];
    int cur;
    int count = 0;
    int *p = s4->slots;
    int neg = -1;

    func_00115484(values, 0, 12);
    cur = 0;
    for (;;) {
        if (cur != s4->current) {
            if (*(int *)p != neg) {
                count++;
                if (count < 4)
                    values[count - 1] = cur;
                else
                    func_00282A28();
            }
        }
        cur++;
        if (cur >= 4)
            break;
        p++;
    }
    if (count != 0) {
        int idx = func_002A7820(0, count - 1);
        s4->current = (unsigned char)values[idx];
        s4->position = ((Record2338 *)D_L04_001B25CC)[s4->slots[s4->current]].position;
    }
}

/* func_L04_003E4C00 is defined in L04_003E4C00.c. */

/* func_L04_003E5B10 is defined in L04_003E5B10.c. */

/* func_L04_003E7E68 is defined in L04_003E7E68-g32.c. */

/* func_L04_003E8010 is defined in L04_003E8010.c. */

/* func_L04_003EB8D8 is defined in L04_003EB8D8.c. */

/* func_L04_003EC140 is defined in L04_003EC140-g8.c. */

/* func_L04_003ED3D8 is defined in L04_003ED3D8.c. */

/* func_L04_003ED740 is defined in L04_003ED740.c. */





/* Defined in L04_00412AF8.c. */

/* func_L04_00422318 is defined in L04_00422318-g8.c. */
