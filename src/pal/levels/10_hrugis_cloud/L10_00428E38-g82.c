#include "include_asm.h"

#include "common.h"
typedef int GateQuad __attribute__((mode(TI)));
typedef union {
    struct {
        float x, y, z, w;
    } v;
    GateQuad q;
} GateVec;
typedef struct GatePath {
    int count;
    char pad04[12];
    GateVec points[0];
} GatePath;
typedef struct GateObject {
    char pad00[0x10];
    GateVec position;
    char pad20[0x10];
    u8 opacity, pad31;
    u16 drawFlags, flags;
    char pad36[0x32];
    void *state;
    char pad6c[0x3e];
    short classId;
    char padac[0x14];
    GateVec forward, right, up;
} GateObject;
extern int D_L10_001B13A4 __attribute__((sda));
extern GateObject *D_L10_001B1400 __attribute__((sda));
extern GateObject *D_L10_001B1404 __attribute__((sda));
extern char *D_L10_001B1408 __attribute__((sda));
extern float D_L10_001B140C __attribute__((sda)), D_L10_001B1410 __attribute__((sda));
extern int D_L10_001B1414 __attribute__((sda)), D_L10_001B1418 __attribute__((sda));
extern int D_L10_001B141C __attribute__((sda));
extern int D_L10_001B1434 __attribute__((sda));
extern int D_L10_001B3550 MACRO_ADDR;
typedef struct {
    char pad[0x2c];
    int field2c;
    char pad30[8];
    int field38;
} GateGlobals;
extern GateGlobals D_L10_00221CD0;
extern GatePath *D_L10_001FE340[];
extern char *D_L10_001B251C[] __attribute__((sda));
extern char D_L10_001B9680[];
extern int D_001A79F0;
extern unsigned char D_0019B278[];
extern void func_002B7320(void), func_L10_00425798(void), func_L05_0037B210(void);
extern void func_L05_00379F28(int), func_L05_00379F18(int);
extern GateObject **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern GateObject *func_L05_00379ED0(int);
extern int func_L00_0042B730(void *);
extern void func_PAL_L05_0037D9D0(void *, int);
extern GateObject *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *), func_00282E48(void *, void *);
extern void func_PAL_L10_00429620(void *, int), func_L10_00423500(void *);
extern int func_00282948(int *);
extern char *func_00288FB8(int);
extern void func_PAL_L00_0030FBC0(void *, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_L05_0037ADD8(float);
extern void func_L05_00424980(void *, int), func_L05_00424970(void *, int);
extern char *func_PAL_L05_00432530(void *, int, int, int);

void func_PAL_L10_00429E20(GateObject *p)
{
    GateVec up, pos, v1, v2;
    char *st = p->state, *other;
    GatePath *path;
    GateObject *obj;
    GateObject **list;
    int count, i;
    float d1, d2;

    up.q = 0;
    up.v.z = 1;

    if (!D_L10_001B13A4) {
        D_L10_001B140C = -1;
        D_L10_001B1410 = -1;
        D_L10_001B13A4 = 1;
        D_L10_001B1400 = 0;
        D_L10_001B1404 = 0;
        D_L10_001B1414 = 0;
        D_L10_001B1418 = 0;
        D_L10_001B141C = 0;
        D_L10_001B3550 = 0;
        D_L10_00221CD0.field2c = 0;
        func_002B7320();
        func_L10_00425798();
        if (D_L10_001B1408)
            func_0029F338(D_L10_001B1408);
        func_L05_0037B210();
        D_L10_001B1408 = 0;
        func_L05_00379F28(1);
        D_L10_00221CD0.field38 = *(int *)(st + 0x20);
        func_L05_00379F18(0);
        list = func_L05_00379EB8();
        count = func_L00_004272A0();
        for (i = 0; i < count; i++) {
            if (list[i]->classId == 0xf82)
                func_PAL_L05_0037D9D0(list[i], 1);
        }
        path = D_L10_001FE340[*(int *)(st + 0x20)];
        while ((!D_L10_001B1400 || !D_L10_001B1404) && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                obj = func_0029EFD0(0x114a);
                obj->opacity = 255;
                obj->drawFlags = 0x1ff;
                obj->flags |= 0x100;
                if (!D_L10_001B1400)
                    D_L10_001B1400 = obj;
                else
                    D_L10_001B1404 = obj;
                if (D_L10_001B1418 == path->count - 1) {
                    func_00282CF0(&obj->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    func_00282F20(&obj->forward, &obj->forward, -1);
                } else {
                    func_00282CF0(&obj->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    func_00282F20(&obj->forward, &obj->forward, 1);
                }
                func_00282DD8(&obj->right, &obj->forward, &up);
                func_00282F20(&obj->right, &obj->right, 1);
                func_00282DD8(&obj->up, &obj->right, &obj->forward);
                qcopy(&obj->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                obj->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    if (!D_L10_001B1400 && !D_L10_001B1404 && !D_L10_001B1434) {
        func_PAL_L10_00429620(p, 3);
        return;
    }

    if (func_L00_0042B730(func_L05_00379ED0(0xf82))) {
        D_L10_001B1434 = 1;
        if (func_00282948((int *)(st + 0x50))) {
            D_L10_001B1434 = 0;
            *(int *)(st + 0x50) = 200;
            func_L10_00423500(p);
            func_L05_0037B210();
        } else
            goto warning;
    } else if (D_L10_001B141C >= 12) {
        D_L10_001B1434 = 1;
        if (!func_00282948((int *)(st + 0x50))) {
        warning:
            func_PAL_L00_0030FBC0(func_00288FB8(0x10F6), -1);
        } else {
            D_L10_001B1434 = 0;
            func_L10_00423500(p);
            func_L05_0037B210();
            *(int *)(st + 0x50) = 200;
        }
    }

    if (D_L10_001B1434)
        return;
    D_L10_001B3550 = D_L10_001B3550 + 1;
    if (D_L10_001B3550 < 2)
        return;

    other = D_L10_001B251C[0] + (*(int *)(st + 0x24) << 8);
    qcopy(&pos, D_L10_001B9680);
    func_00282CF0(&v2, &pos, &D_L10_001B1400->position);
    func_00282F20(&v2, &v2, 1);
    func_00282CF0(&v1, other + 0x10, &D_L10_001B1400->position);
    func_00282F20(&v1, &v1, 1);
    d1 = func_00282DB0(&D_L10_001B1400->forward, &v1);
    d2 = func_00282DB0(&D_L10_001B1400->forward, &v2);

    if ((d1 != D_L10_001B140C && d1 > 0) || (d2 != D_L10_001B1410 && d2 > 0)) {
        path = D_L10_001FE340[*(int *)(st + 0x20)];
        if (func_00282E48(&pos, &D_L10_001B1400->position) <= 1.25f
            || func_00282E48(other + 0x10, &D_L10_001B1400->position) <= 1.25f) {
            func_002E5DA0(15, 0, p, 0xfbf);
            func_L05_0037ADD8(0.5f);
        } else {
            func_L05_0037ADD8(-0.75f);
            D_L10_001B141C++;
        }
        func_0029F338(D_L10_001B1400);
        D_L10_001B1400 = D_L10_001B1404;
        D_L10_001B1404 = 0;
        while (!D_L10_001B1404 && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                obj = func_0029EFD0(0x114a);
                obj->opacity = 255;
                obj->drawFlags = 0x1ff;
                obj->flags |= 0x100;
                D_L10_001B1404 = obj;
                if (D_L10_001B1418 == path->count - 1) {
                    func_00282CF0(&obj->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    func_00282F20(&obj->forward, &obj->forward, -1);
                } else {
                    func_00282CF0(&obj->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    func_00282F20(&obj->forward, &obj->forward, 1);
                }
                func_00282DD8(&obj->right, &obj->forward, &up);
                func_00282F20(&obj->right, &obj->right, 1);
                func_00282DD8(&obj->up, &obj->right, &obj->forward);
                qcopy(&obj->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                obj->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    D_L10_001B140C = d1;
    D_L10_001B1410 = d2;

    if (D_L10_001B1400) {
        func_L05_00424980(D_L10_001B1400, 1);
        if (D_L10_001B1404)
            func_L05_00424970(D_L10_001B1400, 0x40008000);
        else
            func_L05_00424970(D_L10_001B1400, 0x4000c6ff);
    }

    if (D_L10_001B1404) {
        func_L05_00424980(D_L10_001B1404, 1);
        func_L05_00424970(D_L10_001B1404, 0x40808000);
    } else if (!D_L10_001B141C && !D_L10_001B1408 && !D_0019B278[D_001A79F0 * 4]) {
        D_L10_001B1408 = func_PAL_L05_00432530(&D_L10_001B1400->position, 0, -1, -1);
    }
}
