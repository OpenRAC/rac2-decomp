#include "include_asm.h"
extern int D_L30_001B2A68 __attribute__((sda));
extern short D_0018A000;
extern unsigned long long D_00138180[];
extern unsigned char D_L30_001B3D30[];
extern void *D_L30_00260E30[];
extern int D_L30_00260F30[][2];
extern void func_2EDB20(void *, void *);
extern void func_323FB0(void *, int, int);
extern void func_L30_004135A0(char *);
extern int func_326868(void *, int);
extern int func_32B1B0(int, int, int);
extern void func_320FD0(void *, int, int);
extern int func_32C070(void *);
extern char *func_L30_00413490(void *);
extern void func_L30_00413528(void *, void *, void *, int, int, int);
extern char D_00189EA0[];
extern long D_00138320;
extern char D_L30_001B1E28[];
extern char D_L30_001B1E30[];
extern char D_L30_001B1E48[];
extern char D_L30_001B1E60[];
extern char D_L30_001B1E78[];
extern char D_L30_001B1E90[];
extern char D_L30_001B1EA0[];
extern char D_L30_001B1EA8[];
extern char D_L30_001B1EB0[];
extern char D_L30_001B1EB8[];
extern char D_L30_001B1ED0[];
extern char D_L30_001B1EE0[];
char *func_L30_004153D8(void *, float, int, int, int, int, int, int, int, int, int, int);

extern void func_002FC560(int, int);
extern void func_0027DE50(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } D_001A6480;
extern void func_L05_0042F4E8(void *, int, float, float, float, float, float, int);

extern void func_42C028(int);
extern void func_316DB8(char *);
extern int D_0018C0E8;

void func_L30_00418670(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    func_42C028(3);
    D_0018C0E8 = *(int *)(st + 0x5C);
    func_316DB8(*(char **)(st + 0x50));
}


void func_L30_004130E8(char *obj) {
    int *st = *(int **)(obj + 0x68);
    int step = 0;
    D_L30_001B2A68 = 1;
    D_0018A000 = 5;
    func_2EDB20(func_L30_004135A0, obj);
    if (D_00138180[0x1A0 / 8] & 0x9000000000ULL) {
        func_316DB8(obj);
        return;
    }
    if (((int *)D_00138180)[0x1A4 / 4] & 0x4000) {
        func_323FB0(st, st[1] - 1, 1);
        if (st[2] < st[0] - 15) st[2]++;
    } else if (((int *)D_00138180)[0x1A4 / 4] & 0x1000) {
        func_323FB0(st, 0, 1);
        if (st[0] < st[2]) st[2]--;
    } else if (((int *)D_00138180)[0x1A0 / 4] & 0x2000) {
        step = (((int *)D_00138180)[0x1A0 / 4] & 15) ? 5 : 1;
    } else if (((int *)D_00138180)[0x1A0 / 4] & 0x8000) {
        step = (((int *)D_00138180)[0x1A0 / 4] & 15) ? -5 : -1;
    }
    if (step && *(unsigned short *)(obj + 0x96) >= 5) {
        *(unsigned short *)(obj + 0x96) = 0;
        switch (D_L30_001B3D30[st[0]]) {
        case 0: {
            int value = *(int *)D_L30_00260E30[st[0]];
            value += step;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(int *)D_L30_00260E30[st[0]] = value;
            break;
        }
        case 1: {
            float value = *(float *)D_L30_00260E30[st[0]] + step * 0.01f;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(float *)D_L30_00260E30[st[0]] = value;
            break;
        }
        case 2: {
            unsigned char value = *(unsigned char *)D_L30_00260E30[st[0]];
            value += step;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(unsigned char *)D_L30_00260E30[st[0]] = value;
            break;
        }
        case 3: {
            short value = *(short *)D_L30_00260E30[st[0]];
            value += step;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(short *)D_L30_00260E30[st[0]] = value;
            break;
        }
        }
    }
    (*(unsigned short *)(obj + 0x96))++;
}


/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


void func_L30_00415090(char *obj) {
    char *st = *(char **)(obj + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(obj + 0x1C) = 0;
        func_320FD0(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(st + 0x3C) != -1 && func_326868(D_00189EA0, *(int *)(st + 0x3C))) {
            func_32B1B0(1, 0x27E6, 1);
            buttons = D_00138320;
            buttons &= 3;
            if (buttons == 3) func_320FD0(obj, 2, -1);
        }
        break;
    case 2:
        if (func_32C070(obj)) {
            *(char **)(st + 0x2C) = func_L30_00413490(obj);
            func_L30_00413528(*(void **)(st + 0x2C), st + 4, D_L30_001B1E28, 1, 0, 1);
            func_L30_00413528(*(void **)(st + 0x2C), st + 12, D_L30_001B1E30, 0, 0, 50);
            func_L30_00413528(*(void **)(st + 0x2C), st + 16, D_L30_001B1E48, 0, 0, 50);
            func_L30_00413528(*(void **)(st + 0x2C), st + 20, D_L30_001B1E60, 0, 0, 50);
            func_L30_00413528(*(void **)(st + 0x2C), st + 24, D_L30_001B1E78, 0, 0, 50);
            func_L30_00413528(*(void **)(st + 0x2C), st + 28, D_L30_001B1E90, 0, 0, 50);
            func_L30_00413528(*(void **)(st + 0x2C), st + 32, D_L30_001B1EA0, 0, 0, 255);
            func_L30_00413528(*(void **)(st + 0x2C), st + 36, D_L30_001B1EA8, 0, 0, 255);
            func_L30_00413528(*(void **)(st + 0x2C), st + 40, D_L30_001B1EB0, 0, 0, 255);
            func_L30_00413528(*(void **)(st + 0x2C), st + 48, D_L30_001B1EB8, 0, 0, 1);
            func_L30_00413528(*(void **)(st + 0x2C), st + 52, D_L30_001B1ED0, 0, 0, 1);
            func_L30_00413528(*(void **)(st + 0x2C), st + 8, D_L30_001B1EE0, 0, 0, 1);

        }
        func_32B1B0(1, 0, 1);
        menu = *(char **)(st + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            func_320FD0(obj, 1, -1);
        }
        break;
    }
    if (*(float *)(obj + 0x1C) >= 45.0f) {
        int color;
        *(int *)(obj + 0x1C) = 0;
        color = (*(int *)(st + 40) << 16) | (*(int *)(st + 36) << 8) | *(int *)(st + 32);
        *(char **)st = func_L30_004153D8(obj + 0x10, *(float *)(st + 4), *(int *)(st + 8), *(int *)(st + 12), *(int *)(st + 16), *(int *)(st + 20), *(int *)(st + 24), *(int *)(st + 28), *(int *)(st + 48), *(int *)(st + 52), *(int *)(st + 56), color);
    }
    *(float *)(obj + 0x1C) += 1.0f;
}

/* func_L30_004153D8 is defined in L30_004153D8.c. */

/* func_L30_004158B0 is defined in L30_004158B0-g8.c. */

/* func_L30_00416A88 is defined in L30_00416A88-g8.c. */

/* func_L30_00416D88 is defined in L30_00416D88-g8.c. */

/* func_L30_00417988 is defined in L30_00417988-g8.c. */

typedef unsigned short u16;

extern char *func_316A50(int);
extern void func_32BFF0(void *, void *);
extern void func_2F56B0(void *, void *);

void func_L30_00418570(char *a0) {
    char *st = *(char **)(a0 + 0x68);
    char *o;

    o = func_316A50(0xB28);
    if (o == 0) return;
    func_32BFF0(o, a0);
    func_2F56B0(o + 0xC0, o + 0xF0);
    *(u16 *)(o + 0x34) |= 0x100;
    *(char **)(st + 0x50) = o;
}


INCLUDE_ASM("asm/levels", func_L30_004186B0);

void func_L30_004191E0(char *obj) {
    char *st = *(char **)(obj + 0x68);
    if (*(short *)(st + 2) - *(short *)st < 2 && *(short *)(st + 4)) {
        if (*(int *)(st + 0x1C)) {
            func_002FC560(0x42, 0x48);
            func_0027DE50(0, D_001A6480.y, 0, D_001A6480.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(st + 0x18)) {
        if (*(short *)(st + 2) - *(short *)st < 10) {
            float t = (*(short *)(st + 2) - *(short *)st) * 0.1f;
            func_L05_0042F4E8(obj + 0x10, 0x3C, *(float *)(st + 8) + (*(float *)(st + 12) - *(float *)(st + 8)) * t, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)st - 0x2E) < 4) {
            float t = (*(short *)st - 0x2D) * 0.1f;
            func_L05_0042F4E8(obj + 0x10, 0x3C, *(float *)(st + 8) + (*(float *)(st + 12) - *(float *)(st + 8)) * t, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

extern int func_2F4B08(char *);
extern void func_2EDD78(void *, char *);
extern void func_L00_00415AA0(char *);

void func_L30_0041A848(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    if (func_2F4B08(st) == 0) {
        func_2F4B08(st + 4);
        func_2EDD78((void *)func_L00_00415AA0, a0);
    } else {
        func_316DB8(a0);
    }
}

/* func_L30_0041B848 is defined in L30_0041B848.c. */
