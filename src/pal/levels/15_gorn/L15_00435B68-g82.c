#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x30]; unsigned char alpha; char pad31; unsigned short colour, flags; } PathObject;
typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; float f[4]; } PathVector;
typedef struct { int pointCount; int pad[3]; PathVector point[1]; } PathRoute;
typedef struct { char pad[0x2C]; int reset; char gap[8]; int route; } PathPhase;
extern PathPhase D_L15_00221E10 NOT_SDA;
extern PathRoute *D_L15_001FE480[] NOT_SDA;
extern int D_L15_001B3698 MACRO_ADDR;
extern char *D_L15_001B261C MACRO_ADDR;
extern PathVector D_L15_001B97C0 NOT_SDA;
extern int D_001A79F0;
extern unsigned char D_0019B278[];
extern void func_002B7320(void), func_0029F338(void *), func_L05_0037B210(void), func_L05_00379F28(int), func_L05_00379F18(int), func_PAL_L05_0037D9D0(char *, int);
extern char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void), func_L00_0042B730(void *), func_00282948(int *);
extern char *func_0029EFD0(int), *func_L05_00379ED0(int);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *), func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *), func_00282E48(void *, void *);
extern void func_PAL_L15_00436118(void *, int), func_L15_0042FD40(void *);
extern void *func_00288FB8(int);
extern void func_PAL_L00_0030FBC0(void *, int), func_L05_0037ADD8(float), func_L05_00424980(void *, int), func_L05_00424970(void *, unsigned int);
extern int func_002E5DA0(int, int, void *, int);
extern char *func_PAL_L05_00432530(void *, int, int, int);
extern int D_L15_001B1534 __attribute__((sda));
extern char * D_L15_001B1584 __attribute__((sda));
extern char * D_L15_001B1588 __attribute__((sda));
extern char * D_L15_001B158C __attribute__((sda));
extern float D_L15_001B1590 __attribute__((sda));
extern float D_L15_001B1594 __attribute__((sda));
extern int D_L15_001B1598 __attribute__((sda));
extern int D_L15_001B159C __attribute__((sda));
extern int D_L15_001B15A4 __attribute__((sda));
extern int D_L15_001B15C0 __attribute__((sda));
extern int D_L15_001B3698_1 __attribute__((sda));
#define init D_L15_001B1534
#define first D_L15_001B1584
#define next D_L15_001B1588
#define effect D_L15_001B158C
#define oldHero D_L15_001B1590
#define oldCamera D_L15_001B1594
#define index D_L15_001B159C
#define misses D_L15_001B15A4
#define waiting D_L15_001B15C0
#define count D_L15_001B3698_1

void func_PAL_L15_00436A10(char *self)
{
    PathVector up, camera, fromHero, fromCamera;
    char *state = *(char **)(self + 0x68), *object, *hero;
    PathRoute *path;
    char **list;
    float heroDot, cameraDot;
    int n, i;
    unsigned short objectFlags;
    char *oldFirst;
    up.q = 0;
    up.f[2] = 1;
    if (!init) {
        first = 0; next = 0;
        oldCamera = oldHero = -1;
        init = 1;
        D_L15_001B1598 = 0; index = 0; misses = 0;
        D_L15_001B3698 = 0; D_L15_00221E10.reset = 0;
        func_002B7320();
        if (effect) func_0029F338(effect);
        func_L05_0037B210(); effect = 0;
        func_L05_00379F28(1);
        D_L15_00221E10.route = *(int *)(state + 0x30);
        func_L05_00379F18(0);
        list = func_L05_00379EB8(); n = func_L00_004272A0();
        for (i = 0; i < n; i++) if (*(short *)(list[i] + 0xAA) == 0xF82) func_PAL_L05_0037D9D0(list[i], 1);
        path = D_L15_001FE480[*(int *)(state + 0x30)];
        while ((!first || !next) && index != path->pointCount) {
            if (path->point[index].f[3] != -1) {
            object = func_0029EFD0(0x114A);
            ((unsigned char *)object)[0x30] = 0xFF;
            objectFlags = *(unsigned short *)(object + 0x34);
            oldFirst = first;
            *(short *)(object + 0x32) = 0x1FF;
            *(unsigned short *)(object + 0x34) = objectFlags | 0x100;
            if (!oldFirst) first = object; else next = object;
            if (index == path->pointCount - 1) {
                func_00282CF0(object + 0xC0, &path->point[index - 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, -1);
            } else {
                func_00282CF0(object + 0xC0, &path->point[index + 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, 1);
            }
            func_00282DD8(object + 0xD0, object + 0xC0, &up);
            func_00282F20(object + 0xD0, object + 0xD0, 1);
            func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[index]);
            *(int *)(object + 0x1C) = 0;
            }
            index++;
        }
    }
    if (!first && !next && !waiting) { func_PAL_L15_00436118(self, 3); return; }
    if (func_L00_0042B730(func_L05_00379ED0(0xF82))) {
        waiting = 1;
        if (func_00282948((int *)(state + 0x64))) { waiting = 0; *(int *)(state + 0x64) = 200; func_L15_0042FD40(self); func_L05_0037B210(); }
        else func_PAL_L00_0030FBC0(func_00288FB8(0x10F6), -1);
    } else if (misses >= 12) {
        waiting = 1;
        if (!func_00282948((int *)(state + 0x64))) func_PAL_L00_0030FBC0(func_00288FB8(0x10F6), -1);
        else { waiting = 0; *(int *)(state + 0x64) = 200; func_L15_0042FD40(self); func_L05_0037B210(); }
    }
    if (waiting) return;
    count = D_L15_001B3698 + 1;
    if (count < 2) return;
    hero = D_L15_001B261C + (*(int *)(state + 0x20) << 8);
    qcopy(&camera, &D_L15_001B97C0);
    func_00282CF0(&fromCamera, &camera, first + 0x10);
    func_00282F20(&fromCamera, &fromCamera, 1);
    func_00282CF0(&fromHero, hero + 0x10, first + 0x10);
    func_00282F20(&fromHero, &fromHero, 1);
    heroDot = func_00282DB0(first + 0xC0, &fromHero);
    cameraDot = func_00282DB0(first + 0xC0, &fromCamera);
    if ((heroDot != oldHero && heroDot > 0) || (cameraDot != oldCamera && cameraDot > 0)) {
        path = D_L15_001FE480[*(int *)(state + 0x30)];
        if (func_00282E48(&camera, first + 0x10) <= 1.25f || func_00282E48(hero + 0x10, first + 0x10) <= 1.25f) {
            func_002E5DA0(15, 0, self, 0xFBF); func_L05_0037ADD8(0.5f);
        } else { func_L05_0037ADD8(-0.75f); misses++; }
        func_0029F338(first); first = next; next = 0;
        while (!next && index != path->pointCount) {
            if (path->point[index].f[3] != -1) {
            object = func_0029EFD0(0x114A);
            ((PathObject *)object)->alpha = 0xFF; ((PathObject *)object)->colour = 0x1FF; ((PathObject *)object)->flags |= 0x100;
            next = object;
            if (index == path->pointCount - 1) {
                func_00282CF0(object + 0xC0, &path->point[index - 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, -1);
            } else {
                func_00282CF0(object + 0xC0, &path->point[index + 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, 1);
            }
            func_00282DD8(object + 0xD0, object + 0xC0, &up);
            func_00282F20(object + 0xD0, object + 0xD0, 1);
            func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[index]);
            *(int *)(object + 0x1C) = 0;
            }
            index++;
        }
    }
    oldHero = heroDot; oldCamera = cameraDot;
    if (first) {
        func_L05_00424980(first, 1);
        if (next) func_L05_00424970(first, 0x40008000);
        else func_L05_00424970(first, 0x4000C6FF);
    }
    if (next) { func_L05_00424980(next, 1); func_L05_00424970(next, 0x40808000); }
    else if (!misses && !effect && !D_0019B278[D_001A79F0 * 4]) effect = func_PAL_L05_00432530(first + 0x10, 0, -1, -1);
}
