#include "include_asm.h"


#include "common.h"
typedef int GornQuad __attribute__((mode(TI)));
extern char *D_L15_001FE480[];
extern int func_002ED688(unsigned char *);
extern int func_00282948(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002EE920(void *, void *);
extern int func_00283CF0(float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282DD8(void *, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern char *D_L15_001B261C __attribute__((sda));
typedef struct GornOwner {
    char pad00[0x11C];
    int flag11C;
    char *target;
    char pad124[0xC];
    int timer;
} GornOwner;
extern char D_L15_002B6CF0[];
extern char *D_L15_001BFC18[];
extern int D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_00188660[];
extern char *func_PAL_L05_0037DB90(int, int);
extern int func_L05_0037B538(void *, int, int, int);
extern int func_002EEB00(void *);
extern void func_002EE678(void *, int);
extern void func_PAL_L05_0037E8E0(void *);
extern int func_00283DB8(void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002E59F8(int);
extern void func_002AB6D8(void *, void *);
extern char *func_PAL_L05_0042A240(void *, int, int, float, int, int, int, int, int, int, int, int);
extern void func_L15_00435838(char *);
extern void func_PAL_L15_0043BF88(char *);
extern void func_PAL_L15_0043C0D8(void *);
extern void func_PAL_L15_0043BDC8(void *, int);
extern void func_L15_00434D28(void *);

void func_PAL_L15_0043A270(char *object, int flag) {
    float z[4], point[4], matrix[16];
    char *state = *(char **)(object + 0x68);
    GornOwner *owner;
    char *spawn, *data, *route, *entry;
    int i, j, next, n, sound;
    *(GornQuad *)z = 0;
    z[2] = 1.0f;
    owner = (GornOwner *)func_002ED688((unsigned char *)object);
    owner->flag11C = 1;
    owner->target = D_L15_001B261C + (*(int *)(state + 0x260) << 8);
    if (func_00282948(state + 0x444)) {
        *(int *)(state + 0x444) = 250;
        for (i = *(int *)(state + 0x440) * 3; i < *(int *)(state + 0x440) * 3 + 3; i++) {
            qcopy_nc(point, D_L15_002B6CF0 + i * 16);
            func_00283098(point, point, object + 0xC0);
            func_00282CC0(point, point, object + 0x10);
            spawn = func_PAL_L05_0037DB90(0x957, 1);
            if (spawn) {
                data = (char *)func_002ED688((unsigned char *)spawn);
                qcopy_nc(spawn + 0x10, point);
                func_00282F20(spawn + 0xC0, object + 0xD0, *(int *)(state + 0x440) ? -1.0f : 1.0f);
                qcopy_nc(data + 0x90, spawn + 0xC0);
                func_00282DD8(spawn + 0xD0, spawn + 0xC0, z);
                func_00282F20(spawn + 0xD0, spawn + 0xD0, 1.0f);
                func_00282DD8(spawn + 0xE0, spawn + 0xD0, spawn + 0xC0);
                func_00282D30(data + 0x60, spawn + 0xC0, 10.0f);
                func_00282CC0(data + 0x60, spawn + 0x10, data + 0x60);
                *(int *)(data + 0x130) = 417;
            }
        }
        *(int *)(state + 0x440) ^= 1;
    }
    if (*(int *)(state + 0x264)) {
        for (j = 0; j < 6; j++) {
            qcopy_nc(point, D_L15_002B6CF0 + j * 16);
            func_00283098(point, point, object + 0xC0);
            func_00282CC0(point, point, object + 0x10);
        }
    }
    func_L15_00435838(object);
    route = D_L15_001FE480[*(int *)(state + 0x448)];
    if (func_002EEB00(object)) {
        next = *(int *)(state + 0x44C);
        *(int *)(state + 0x44C) = next + 1;
        func_002EE920(object, route + 16 + next * 16);
        owner->timer = 1666667;
        if (*(int *)(state + 0x44C) >= *(int *)route) *(int *)(state + 0x44C) = 0;
    }
    func_002EE678(object, 2);
    func_PAL_L05_0037E8E0(object);
    qcopy_nc(point, object + 0x10);
    point[3] = *(float *)(object + 0xC) * 0.0009765599970705807f;
    if (func_00283DB8(point, 100.0f) != -1 &&
        func_002761F8(object + 0x10, owner->target + 0x10, 0, object, 0) &&
        D_L15_001BFC18[0] && *(short *)(D_L15_001BFC18[0] + 0xAA) == *(short *)(owner->target + 0xAA))
        func_PAL_L15_0043BF88(object);
    if (func_00283DB8(point, 192.0f) != -1 && (unsigned char)object[0x20] != 2)
        func_PAL_L15_0043C0D8(object);
    if (!flag && func_L05_0037B538(object, 1, 1, 1)) {
        object[0x20] = 6;
        func_002E5CF8(1, 0, object);
        sound = *(int *)(state + 0x458);
        if (sound != -1) {
            entry = (char *)(D_00188660 + sound * 0x70);
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74)) func_002E59F8(sound);
        }
        *(int *)(state + 0x458) = -1;
        qcopy_nc(matrix, object + 0xC0);
        qcopy_nc(matrix + 4, object + 0xD0);
        qcopy_nc(matrix + 8, object + 0xE0);
        func_002AB6D8(matrix, state + 0x400);
    }
    if ((unsigned char)object[0x20] == 4) {
        if (*(float *)(state + 0x180) <= 400.0f) {
            *(int *)(state + 0x268) = 0;
            if (!*(int *)(state + 0x45C)) {
                func_002E5CF8(4, 0, object);
                *(int *)(state + 0x45C) = 1;
            }
            n = func_00283CF0(*(float *)(state + 0x180) * 0.02f);
            if (n < 7 && n != *(int *)(state + 0x26C)) {
                func_PAL_L05_0042A240(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                func_0029FCC0(object, D_L15_001B17B0[7-n], matrix);
                func_PAL_L05_0042A240(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                func_PAL_L15_0043BDC8(object, n-1);
            }
            func_L15_00434D28(object);
            *(int *)(state + 0x26C) = n;
            if (n > 0) *(short *)(object + 0x7C) = (1 << (n-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
    else {
        if (*(float *)(state + 0x180) <= 100.0f) {
            *(int *)(state + 0x268) = 0;
            if (!*(int *)(state + 0x45C)) {
                func_002E5CF8(4, 0, object);
                *(int *)(state + 0x45C) = 1;
            }
            n = func_00283CF0(*(float *)(state + 0x180) * 0.08f);
            if (n < 7 && n != *(int *)(state + 0x26C)) {
                func_PAL_L05_0042A240(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                func_0029FCC0(object, D_L15_001B17B0[7-n], matrix);
                func_PAL_L05_0042A240(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                func_PAL_L15_0043BDC8(object, n-1);
            }
            func_L15_00434D28(object);
            *(int *)(state + 0x26C) = n;
            if (n > 0) *(short *)(object + 0x7C) = (1 << (n-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
}

