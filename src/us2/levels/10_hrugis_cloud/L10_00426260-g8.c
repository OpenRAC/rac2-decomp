/* func_US2_L10_00426260, the v2.00 course step of Hrugis Cloud's path markers: the same C as
 * func_US2_L15_00432BA8 with this level's state offsets, its extra func_L10_00425798 call and
 * func_L10_00424528's order in the second expiry arm. Its own unit: the $gp-relative state
 * needs -G8, and retail clears the stack vector at 0($sp) with a materialised por zero
 * (-frac2-zero-ti-por). */
#include "common.h"
typedef struct { char pad[0x30]; unsigned char alpha; char pad31; unsigned short colour, flags; } PathObject;
typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; float f[4]; } PathVector;
typedef struct { int pointCount; int pad[3]; PathVector point[1]; } PathRoute;
typedef struct { char pad[0x2C]; int reset; char gap[8]; int route; } PathPhase;
extern PathPhase D_L10_00221CD0 NOT_SDA;
extern PathRoute *D_L10_001FE340[] NOT_SDA;
extern int D_L10_001B3550 MACRO_ADDR;
extern char *D_L10_001B251C MACRO_ADDR;
extern PathVector D_L10_001B9680 NOT_SDA;
extern int D_001A79F0;
extern unsigned char D_0019B278[];
extern void func_002B7320(void), func_L10_00425798(void), func_0029F338(void *), func_L05_0037B210(void), func_L05_00379F28(int), func_L05_00379F18(int), func_L05_0037B280(char *, int);
extern char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void), func_L00_0042B730(void *), func_00282948(int *);
extern char *func_0029EFD0(int), *func_L05_00379ED0(int);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *), func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *), func_00282E48(void *, void *);
extern void func_US2_L10_00425A78(void *, int), func_L10_00423500(void *);
extern void *func_00288FB8(int);
extern void func_L00_0032B280(unsigned int);
extern void func_US2_L00_0030EFB8(void *, int), func_L05_0037ADD8(float), func_L05_00424980(void *, int), func_L05_00424970(void *, unsigned int);
extern int func_002E5DA0(int, int, void *, int);
extern char *func_L05_0042C928(void *, int, int, int);
extern int D_L10_001B13A4 __attribute__((sda));
extern char * D_L10_001B1400 __attribute__((sda));
extern char * D_L10_001B1404 __attribute__((sda));
extern char * D_L10_001B1408 __attribute__((sda));
extern float D_L10_001B140C __attribute__((sda));
extern float D_L10_001B1410 __attribute__((sda));
extern int D_L10_001B1414 __attribute__((sda));
extern int D_L10_001B1418 __attribute__((sda));
extern int D_L10_001B141C __attribute__((sda));
extern int D_L10_001B1434 __attribute__((sda));
/* Retail reads this counter absolutely and writes the same address via $gp: D_L10_001B3550 through a second small-data declaration. */
extern int D_L10_001B3550_1 __attribute__((sda));
void func_US2_L10_00426260(char *self)
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
    if (!D_L10_001B13A4) {
        D_L10_001B1410 = D_L10_001B140C = -1;
        D_L10_001B13A4 = 1;
        D_L10_001B1400 = 0; D_L10_001B1404 = 0;
        D_L10_001B1414 = 0; D_L10_001B1418 = 0; D_L10_001B141C = 0;
        D_L10_001B3550 = 0; D_L10_00221CD0.reset = 0;
        func_002B7320();
        func_L10_00425798();
        if (D_L10_001B1408) func_0029F338(D_L10_001B1408);
        func_L05_0037B210(); D_L10_001B1408 = 0;
        func_L05_00379F28(1);
        D_L10_00221CD0.route = *(int *)(state + 0x20);
        func_L05_00379F18(0);
        list = func_L05_00379EB8(); n = func_L00_004272A0();
        for (i = 0; i < n; i++) if (*(short *)(list[i] + 0xAA) == 0xF82) func_L05_0037B280(list[i], 1);
        path = D_L10_001FE340[*(int *)(state + 0x20)];
        while ((!D_L10_001B1400 || !D_L10_001B1404) && D_L10_001B1418 != path->pointCount) {
            if (path->point[D_L10_001B1418].f[3] != -1) {
            object = func_0029EFD0(0x114A);
            ((unsigned char *)object)[0x30] = 0xFF;
            objectFlags = *(unsigned short *)(object + 0x34);
            oldFirst = D_L10_001B1400;
            *(short *)(object + 0x32) = 0x1FF;
            *(unsigned short *)(object + 0x34) = objectFlags | 0x100;
            if (!oldFirst) D_L10_001B1400 = object; else D_L10_001B1404 = object;
            if (D_L10_001B1418 == path->pointCount - 1) {
                func_00282CF0(object + 0xC0, &path->point[D_L10_001B1418 - 1], &path->point[D_L10_001B1418]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, -1);
            } else {
                func_00282CF0(object + 0xC0, &path->point[D_L10_001B1418 + 1], &path->point[D_L10_001B1418]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, 1);
            }
            func_00282DD8(object + 0xD0, object + 0xC0, &up);
            func_00282F20(object + 0xD0, object + 0xD0, 1);
            func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[D_L10_001B1418]);
            *(int *)(object + 0x1C) = 0;
            }
            D_L10_001B1418++;
        }
    }
    if (!D_L10_001B1400 && !D_L10_001B1404 && !D_L10_001B1434) { func_US2_L10_00425A78(self, 3); return; }
    if (func_L00_0042B730(func_L05_00379ED0(0xF82))) {
        D_L10_001B1434 = 1;
        if (func_00282948((int *)(state + 0x50))) { D_L10_001B1434 = 0; *(int *)(state + 0x50) = 240; func_L10_00423500(self); func_L05_0037B210(); }
        else { func_L00_0032B280(10); func_US2_L00_0030EFB8(func_00288FB8(0x3074), -1); }
    } else if (D_L10_001B141C >= 12) {
        D_L10_001B1434 = 1;
        if (!func_00282948((int *)(state + 0x50))) { func_L00_0032B280(10); func_US2_L00_0030EFB8(func_00288FB8(0x3074), -1); }
        else { D_L10_001B1434 = 0; func_L10_00423500(self); func_L05_0037B210(); *(int *)(state + 0x50) = 240; }
    }
    if (D_L10_001B1434) return;
    D_L10_001B3550_1 = D_L10_001B3550 + 1;
    if (D_L10_001B3550_1 < 2) return;
    hero = D_L10_001B251C + (*(int *)(state + 0x24) << 8);
    qcopy(&camera, &D_L10_001B9680);
    func_00282CF0(&fromCamera, &camera, D_L10_001B1400 + 0x10);
    func_00282F20(&fromCamera, &fromCamera, 1);
    func_00282CF0(&fromHero, hero + 0x10, D_L10_001B1400 + 0x10);
    func_00282F20(&fromHero, &fromHero, 1);
    heroDot = func_00282DB0(D_L10_001B1400 + 0xC0, &fromHero);
    cameraDot = func_00282DB0(D_L10_001B1400 + 0xC0, &fromCamera);
    if ((heroDot != D_L10_001B140C && heroDot > 0) || (cameraDot != D_L10_001B1410 && cameraDot > 0)) {
        path = D_L10_001FE340[*(int *)(state + 0x20)];
        if (func_00282E48(&camera, D_L10_001B1400 + 0x10) <= 1.25f || func_00282E48(hero + 0x10, D_L10_001B1400 + 0x10) <= 1.25f) {
            func_002E5DA0(15, 0, self, 0xFBF); func_L05_0037ADD8(0.5f);
        } else { func_L05_0037ADD8(-0.75f); D_L10_001B141C++; }
        func_0029F338(D_L10_001B1400); D_L10_001B1400 = D_L10_001B1404; D_L10_001B1404 = 0;
        while (!D_L10_001B1404 && D_L10_001B1418 != path->pointCount) {
            if (path->point[D_L10_001B1418].f[3] != -1) {
            object = func_0029EFD0(0x114A);
            ((PathObject *)object)->alpha = 0xFF; ((PathObject *)object)->colour = 0x1FF; ((PathObject *)object)->flags |= 0x100;
            D_L10_001B1404 = object;
            if (D_L10_001B1418 == path->pointCount - 1) {
                func_00282CF0(object + 0xC0, &path->point[D_L10_001B1418 - 1], &path->point[D_L10_001B1418]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, -1);
            } else {
                func_00282CF0(object + 0xC0, &path->point[D_L10_001B1418 + 1], &path->point[D_L10_001B1418]);
                *(int *)(object + 0xCC) = 0;
                func_00282F20(object + 0xC0, object + 0xC0, 1);
            }
            func_00282DD8(object + 0xD0, object + 0xC0, &up);
            func_00282F20(object + 0xD0, object + 0xD0, 1);
            func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[D_L10_001B1418]);
            *(int *)(object + 0x1C) = 0;
            }
            D_L10_001B1418++;
        }
    }
    D_L10_001B140C = heroDot; D_L10_001B1410 = cameraDot;
    if (D_L10_001B1400) {
        func_L05_00424980(D_L10_001B1400, 1);
        if (D_L10_001B1404) func_L05_00424970(D_L10_001B1400, 0x40008000);
        else func_L05_00424970(D_L10_001B1400, 0x4000C6FF);
    }
    if (D_L10_001B1404) { func_L05_00424980(D_L10_001B1404, 1); func_L05_00424970(D_L10_001B1404, 0x40808000); }
    else if (!D_L10_001B141C && !D_L10_001B1408 && !D_0019B278[D_001A79F0 * 4]) D_L10_001B1408 = func_L05_0042C928(D_L10_001B1400 + 0x10, 0, -1, -1);
}
