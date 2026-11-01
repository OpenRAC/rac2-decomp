#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L30_004188D8);


extern int func_002ACBC8(void *, int);
extern int func_002B0CE0(int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
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
char *func_PAL_L30_0041A748(void *, float, int, int, int, int, int, int, int, int, int, int);

/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


void func_PAL_L30_0041A400(char *obj) {
    char *st = *(char **)(obj + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(obj + 0x1C) = 0;
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(st + 0x3C) != -1 && func_002ACBC8(D_00189EA0, *(int *)(st + 0x3C))) {
            func_002B0CE0(1, 0x1338, 1);
            buttons = D_00138320;
            buttons &= 3;
            if (buttons == 3) func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
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
        func_002B0CE0(1, 0, 1);
        menu = *(char **)(st + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            func_002A7750(obj, 1, -1);
        }
        break;
    }
    if (*(float *)(obj + 0x1C) >= 45.0f) {
        int color;
        *(int *)(obj + 0x1C) = 0;
        color = (*(int *)(st + 40) << 16) | (*(int *)(st + 36) << 8) | *(int *)(st + 32);
        *(char **)st = func_PAL_L30_0041A748(obj + 0x10, *(float *)(st + 4), *(int *)(st + 8), *(int *)(st + 12), *(int *)(st + 16), *(int *)(st + 20), *(int *)(st + 24), *(int *)(st + 28), *(int *)(st + 48), *(int *)(st + 52), *(int *)(st + 56), color);
    }
    *(float *)(obj + 0x1C) += 1.0f;
}


#include "common.h"
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L30_0041AC18(void *, void *);
extern struct Player153 {
    char pad[0x140];
    float position[4];
    char pad2[0x10];
    float shakeStrength;
    int pad3;
    int shakeDuration, shakeTimer;
    char pad4[0x200];
    float forward[4];
} D_L30_001B9C80;
typedef struct {
    short life, initialLife, duration;
    short pad;
    float inner, outer, strength, scale;
    int sound, flash, a2, a3, a4, a5, a6, a8, color;
} State153;

char *func_PAL_L30_0041A748(void *pos, float scale, int shake, int a2, int a3, int a4, int a5, int a6, int sound, int a8, int a9, int color) {
    float direction[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float sphere[4] __attribute__((aligned(16)));
    float towardPlayer[4] __attribute__((aligned(16)));
    char *obj = func_0029EFD0(0x11E5);
    State153 *st;
    if (obj) {
        st = *(State153 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        *(unsigned char *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        func_00282CF0(direction, D_L30_001B9C80.position, obj + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(obj + 0x10, normal, 1);
        qcopy(obj + 0xC0, direction);
        func_00282DD8(obj + 0xD0, obj + 0xC0, normal);
        func_00282F20(obj + 0xD0, obj + 0xD0, 1.0f);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        st->initialLife = st->life = 50;
        st->inner = scale + scale;
        st->outer = scale * 4.0f;
        st->a2 = a2;
        st->a3 = a3;
        st->a4 = a4;
        st->a5 = a5;
        st->a6 = a6;
        st->a8 = a8;
        st->flash = a9;
        st->sound = sound;
        st->color = color;
        st->scale = scale;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            st->duration = 8;
            st->strength = 0.125f;
            if (func_00282E48(pos, D_L30_001B9C80.position) < 48.0f && shake) {
                D_L30_001B9C80.shakeTimer = 0;
                D_L30_001B9C80.shakeDuration = 33;
                D_L30_001B9C80.shakeStrength = 0.075f;
            }
            if (st->sound) {
                func_00282CF0(towardPlayer, obj + 0x10, D_L30_001B9C80.position);
                func_00282F20(towardPlayer, towardPlayer, 1.0f);
                if (1.5707963705062866f - func_002831B0(func_00282DB0(towardPlayer, D_L30_001B9C80.forward)) < 0.45378565788269043f)
                    st->sound = 1;
                else
                    st->sound = 0;
            }
        } else {
            st->duration = 0;
            st->sound = 0;
        }
        func_PAL_L30_0041AC18(obj, normal);
    }
    return obj;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L30_0041AC18);
