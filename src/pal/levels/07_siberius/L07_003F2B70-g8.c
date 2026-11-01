#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_0029F338(int);
extern float func_002A7940();
extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(char *, int);
extern void func_L07_003EECE0(char *);
extern int func_002B3868(char *);
extern float func_PAL_L07_003F3290(char *);
extern int func_002A8508(int, int);
extern int func_00282948(void *);
extern int func_002B38B8(char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002E5CF8(int, int, char *);
extern void func_PAL_L07_003EB648(char *, void *, void *, char *, int);
extern void func_PAL_L07_003EFFD0(char *, void *, void *, char *, int);
extern float func_002AA2E8(void *, float, float);
extern int func_002A9640(char *, int, int);
extern float func_PAL_002AA108(char *, int);
extern void func_PAL_002B15D8(char *, int, void *, int, float, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_0032F3B8(char *, void *, void *, float);
extern char D_00189EA0[];
extern char D_L07_001B9200[];
extern int D_L07_001B0C50 __attribute__((sda));
extern unsigned short *D_L07_001FAD60[];
extern char *D_L07_001B22DC[] __attribute__((sda));
extern int D_L07_001B22F8[] __attribute__((sda));
extern void *D_L07_002A3380[];
typedef struct {
    char pad00[0x20];
    float f20;
    short h24;
    char pad26[0x60 - 0x26];
    char b60[0x30];
    int f90;
    char pad94[0x9C - 0x94];
    int ids[7];
    char padB8[0xF0 - 0xB8];
    char b0F0[0x10];
    char pad100[0x104 - 0x100];
    float f104;
    float f108;
    char pad10C[0x110 - 0x10C];
    int f110;
    float f114;
    float f118;
    char pad11C[0x120 - 0x11C];
    int idx;
    int f124;
} L07State;

/* The object's six states, state 0 to 5 (anything above only runs the tail). The dispatch reads the
   level's own jump table (six code addresses in the level's data at 0x2A3380: the bodies come in
   the order 0, 1, 4, 2, 3, 5); `cases` only keeps the labels alive. */
void func_PAL_L07_003F2B70(char *a0)
{
    static void *cases[6] = {&&c0, &&c1, &&c4, &&c2, &&c3, &&c5};
    char *s1 = a0;
    L07State *s3;
    unsigned int sel;

    sel = *(unsigned char *)(s1 + 0x20);
    s3 = *(L07State **)(s1 + 0x68);
    if (sel < 6)
        goto *D_L07_002A3380[sel];
    goto tail;
c0:
    if (s3->h24 == 0) {
        s3->h24 = 0x28;
        s3->f20 = 40.0f;
    }
    s3->f104 = func_002A7940();
    s3->f108 = func_002A7940();
    *(TI128 *)s3->b0F0 = *(TI128 *)(s1 + 0x10);
    func_002A7750(s1, 1, -1);
    *(int *)(s1 + 0x98) = 0;
    *(unsigned short *)(s1 + 0x34) = (*(unsigned short *)(s1 + 0x34) | 0x41) & 0xEFFF;
    goto tail;
c1:
    if (s3->f90 != -1) {
        if (func_002ACBC8(D_00189EA0, s3->f90))
            func_L07_003EECE0(s1);
    }
    goto tail;
c4: {
    int i;

    if (func_002B3868(s1))
        s3->f124 = 0x32;
    func_PAL_L07_003F3290(s1);
    i = s3->idx;
    if (i >= 6 || s3->ids[i + 1] == -1) {
        func_002A7750(s1, 5, -1);
    } else {
        if (func_002A8508(s3->ids[i], -1) == 0) {
            if (func_00282948(&s3->f124)) {
                s3->idx = s3->idx + 1;
                func_002A7750(s1, 3, -1);
            }
        }
    }
    goto tail;
}
c2:
    func_PAL_L07_003F3290(s1);
    if (func_002B38B8(s1))
        func_002A7750(s1, 3, -1);
    goto tail;
c3: {
    float f;
    unsigned short *p;
    char *e;
    char buf[16];

    f = func_PAL_L07_003F3290(s1);
    if (f < 3.0f) {
        if (s3->ids[s3->idx] != -1) {
            func_00283098(buf, &D_L07_001B0C50, s1 + 0xC0);
            func_00282CC0(buf, buf, s1 + 0x10);
            for (p = D_L07_001FAD60[s3->ids[s3->idx]];
                 (s3->ids[s3->idx] & 0xFF) != 0xFF &&
                 s3->ids[s3->idx] <= D_L07_001B22F8[0] && p != 0 &&
                 ((short)p[-1] >= 0 || p == D_L07_001FAD60[s3->ids[s3->idx]]);
                 p++) {
                e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(unsigned char *)(e + 0x20) != 0xFE) {
                    if (*(unsigned char *)(e + 0x20) != 0xFD) {
                        switch (*(short *)(e + 0xAA)) {
                        case 0xD29:
                            func_002E5CF8(0, 0, s1);
                            func_PAL_L07_003EB648(e, buf, e + 0x10, s1, s3->f110);
                            break;
                        case 0xD2A:
                            func_002E5CF8(0, 0, s1);
                            func_PAL_L07_003EFFD0(e, buf, e + 0x10, s1, s3->f110);
                            break;
                        }
                    }
                }
            }
        }
        func_002A7750(s1, 4, -1);
    }
    goto tail;
}
c5: {
    func_PAL_L07_003F3290(s1);
    func_002AA2E8(&s3->f114, 0.20000002f, 0.0012f);
    s3->f118 += s3->f114;
    if (30.0f < s3->f118) {
        if (*(unsigned char *)(s1 + 0x31) == 0) {
            func_0029F338((int)s1);
            return;
        }
    }
}
tail:
    if (*(unsigned char *)(s1 + 0x20) < 2)
        return;
    if (s3->f110 != 0)
        return;
    {
        char buf2[16];
        int t;
        float f2;

        t = func_002A9640(s1, 0x10000, 0);
        f2 = func_PAL_002AA108(s1, t);
        func_002AA2E8(&s3->f20, 0.0f, f2);
        *(unsigned char *)(s1 + 0xA8) = 0xFF;
        if (s3->f20 == 0.0f) {
            func_PAL_002B15D8(s1, 0x7F7, s3->b60, 0xFF, 5.0f, 10.0f, 5.0f, 10.0f);
            func_00282CF0(buf2, D_L07_001B9200, s1 + 0x10);
            func_00282F20(buf2, buf2, 1.0f);
            func_PAL_0032F3B8(s1, s1 + 0x10, buf2, 0.0f);
            func_002E5CF8(2, 0, s1);
            func_0029F338((int)s1);
        }
    }
}
