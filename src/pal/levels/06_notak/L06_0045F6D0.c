#include "include_asm.h"


extern float D_L06_001B234C __attribute__((sda));
extern float D_001B2350 __attribute__((sda));
extern int func_002A9640(char *, int, int);
extern void func_L01_003D6B00(char *, int, float, float, float, float);
extern int func_002E5CF8(int, int, char *);

void func_PAL_L06_00460E58(char *a0)
{
    char *p;
    int n;

    if (*(unsigned char *)(a0 + 0x20) == 0) {
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned short *)(a0 + 0x34) |= 0x800;
    }

    p = (char *)func_002A9640(a0, 0x4010000, 0);
    if (p != 0 && *(short *)(*(char **)(p + 0x20) + 0xAA) != 0xFE5) {
        n = 3;
        if (D_L06_001B234C < 0.8999999761581421f && D_001B2350 < 0.8999999761581421f)
            n = 0xE;

        func_L01_003D6B00(a0, n, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.14000002f);
        func_002E5CF8(0, 0, a0);
        func_0029F338(a0);
    } else {
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
    }
}




#include "common.h"
extern int func_00273B70(char *);
extern void func_002A7750(char *, int, int);
extern void func_0029F338(char *);
extern void func_L06_0045C350(unsigned char *);

void func_PAL_L06_00461470(unsigned char *a0)
{
    switch (a0[0x20]) {
    case 0:
        if (func_00273B70((char *)a0) != 0) {
            func_002A7750((char *)a0, 1, -1);
            *(unsigned short *)(a0 + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_00273B70((char *)a0);
        if (a0[0x23] < 2) {
            func_0029F338((char *)a0);
        } else {
            a0[0x23] -= 2;
        }
        break;
    }
}

typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char D_00188660[];
extern char D_00189EA0[];
/* Keep this absolute address as one assembler macro under -G0. */
extern char D_L06_001A8F20[] __attribute__((sda));
extern int func_0035CBA0(char *, int, int);
extern void func_002A8598(int, int);
extern int func_003A0948(int, int, char *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int,
                                   float, float, int, int, int, int);
extern void func_PAL_002B15D8(char *, int, void *, int, float, float, float, float);
extern void func_PAL_L00_003281C0(char *, int, float);
extern void func_00350388(char *);
extern int func_002A7820(int, int);
extern float func_00282E80(void *, void *);
extern int func_00282948(void *);
extern void func_002E59F8(int);
extern void func_PAL_L06_00461850(char *);

/* func_PAL_L06_00461504, the PAL copy of func_L06_0045C3E8: the same C, where the three
   countdowns written to state take the 50 Hz scale. */
void func_PAL_L06_00461504(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    char *hit;
    float pos[4];
    *(unsigned char *)(a0 + 0x23) = 0x80;
    if (!state) {
        return;
    }
    hit = (char *)func_0035CBA0(a0, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(unsigned char *)(a0 + 0x20) == 1) {
            func_002A8598(*(unsigned char *)(a0 + 0x21), 0);
        }
        func_003A0948(1, 0, a0);
        *(NotakQuad *)pos = 0;
        pos[2] = 1.0f;
        func_00282CC0(pos, pos, a0 + 0x10);
        func_PAL_L00_003FB330(pos, 1, 25, 20, 20, 20, 45, 1, 1.25f, 20.0f, 1, 1, 0, 0);
        func_PAL_002B15D8(a0, 0x7F, D_L06_001A8F20, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_PAL_L00_003281C0(a0, 1, 0.0f);
        func_00350388(a0);
    }
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x23) = 0x80;
        *(int *)state = ((s32)(func_002A7820(40, 250)) * 5 + 2) / 6;
        a0[0x20] = 2;
        *(int *)(state + 8) = -1;
        break;
    case 1:
        if (func_00282E80(a0 + 0x10, D_00189EA0) < 32.0f) {
            func_PAL_L06_00461850(a0);
        }
        if (func_00282948(state + 4)) {
            *(int *)state = ((s32)(func_002A7820(200, 250)) * 5 + 2) / 6;
            if (*(int *)(state + 8) != -1) {
                char *snd = D_00188660 + *(int *)(state + 8) * 0x70;
                if (*(char **)(snd + 0x88) == a0 && *(unsigned char *)(snd + 0x74)) {
                    func_002E59F8(*(int *)(state + 8));
                }
            }
            *(int *)(state + 8) = -1;
            a0[0x20] = 2;
            func_002A8598(*(unsigned char *)(a0 + 0x21), 0);
        }
        break;
    case 2:
        if (func_00282948(state) && *(unsigned char *)(a0 + 0xBC) == 0) {
            char *snd;
            *(int *)(state + 4) = ((s32)(func_002A7820(200, 250)) * 5 + 2) / 6;
            snd = D_00188660 + *(int *)(state + 8) * 0x70;
            if (*(char **)(snd + 0x88) != a0 || !*(unsigned char *)(snd + 0x74)) {
                *(int *)(state + 8) = func_003A0948(0, 4, a0);
            }
            a0[0x20] = 1;
            func_002A8598(*(unsigned char *)(a0 + 0x21), 1);
        }
        break;
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
}



