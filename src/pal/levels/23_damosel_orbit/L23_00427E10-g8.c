#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
typedef struct View_00422A30 {
    u8 pad0[0x188C];
    u8 *f188C;
    u8 pad1[0x2290 - 0x1890];
    u8 *f2290;
    s32 f2294;
} View_00422A30;
extern View_00422A30 D_00189E20;
extern float D_L23_001B1910 __attribute__((sda));
extern float D_L23_001B1928 __attribute__((sda));
extern u8 *D_L23_001B1484 __attribute__((sda));
extern s32 D_L23_001B36E0;
extern TI16 D_L23_001B1FB0 MACRO_ADDR;
extern u8 *func_0029EFD0(s32);
extern void func_002B37E8(u8 *, u8 *);
extern void func_L23_00418650(void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002B0360(void *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern s32 func_L23_0041B948(void);
extern s32 func_002E5CF8(s32, s32, u8 *);

/* Creates the follower object for `src` (the effect that tracks `target`, or the hero, or nothing): copies
   the pose rows, fills the state, and when it has a live target works out the direction, the distance and
   the aim test, dropping the target when the aim, the range or the helper says so. */
u8 *func_PAL_L23_00427E10(u8 *src, TI16 *pos, u8 *target, s32 a3, s32 a4) {
    u8 *obj;
    u8 *st;
    TI16 loc[4];
    float f20;
    float f21;
    float f22;
    float dot;
    s32 flag;
    u8 *hero;
    TI16 c0;
    TI16 c1;
    TI16 c2;
    TI16 *reverse;

    obj = func_0029EFD0(0x118F);
    if (obj != 0) {
        st = *(u8 **)(obj + 0x68);
        func_002B37E8(obj, src);
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) * D_L23_001B1910;
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x100;
        *(float *)(st + 0x1C) = 0.40000004f;
        c0 = *(TI16 *)(src + 0xC0);
        *(TI16 *)(obj + 0xC0) = c0;
        c1 = *(TI16 *)(src + 0xD0);
        *(TI16 *)(obj + 0xD0) = c1;
        c2 = *(TI16 *)(src + 0xE0);
        *(TI16 *)(obj + 0xE0) = c2;
        *(u8 **)(st + 0x10) = src;
        qcopy(obj + 0x10, pos);
        *(s32 *)(st + 0x14) = 0x7D;
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) + *(float *)(obj + 0x2C);
        st[0x28] = a3;
        st[0x29] = a4;
        hero = D_L23_001B1484;
        if (target != 0) {
            *(u8 **)(st + 0x18) = target;
            *(s32 *)(st + 0x24) = 0x890000;
        } else {
            if (hero != 0) {
                *(u8 **)(st + 0x18) = hero;
                if (*(s16 *)(hero + 0xAA) == 0xF7F) {
                    *(s32 **)(st + 0x2C) = &D_L23_001B36E0;
                } else {
                    *(u8 **)(st + 0x2C) = hero + 0x10;
                }
                *(s32 *)(st + 0x24) = 0x890000;
            } else {
                *(s32 *)(st + 0x18) = 0;
                *(s32 *)(st + 0x24) = 0x890000;
                st[0x29] = 0;
                st[0x28] = 0;
            }
        }
        if (src == D_00189E20.f2290) {
            st[0x29] = 1;
        }
        if (st[0x28] == 0 && *(s32 *)(st + 0x18) != 0) {
            qcopy(&loc[0], *(void **)(st + 0x2C));
            func_L23_00418650(&loc[0], 0.0f);
            func_00282CF0(st + 0x30, *(u8 **)(st + 0x2C), obj + 0x10);
            qcopy(&loc[1], obj + 0x10);
            func_L23_00418650(&loc[1], 0.0f);
            func_00282CF0(&loc[2], &loc[0], &loc[1]);
            flag = 0;
            func_00282F20(&loc[2], &loc[2], 1.0f);
            func_00282F20(st + 0x30, st + 0x30, 1.0f);
            f21 = func_002B0360(src + 0x10);
            f20 = func_002B0360(*(u8 **)(st + 0x2C));
            f22 = func_00282E48(&loc[0], &loc[1]);
            if (f22 < 5.0f) {
                if (func_00282C48(f21 - f20) > 10.0f) {
                    flag = 1;
                }
            }
            qcopy(&loc[3], obj + 0xC0);
            dot = func_00282DB0(&loc[2], &loc[3]);
            if ((src == D_00189E20.f2290 && *(*(u8 **)(st + 0x18) + 0x31) == 0) ||
                dot < D_L23_001B1928 || 50.0f < f22 || flag != 0 || func_L23_0041B948() != 0) {
                *(s32 *)(st + 0x18) = 0;
            }
            if (src == D_00189E20.f2290) {
                if (*(s32 *)(st + 0x18) != 0) {
                    D_00189E20.f188C = st + 0x30;
                } else if (D_00189E20.f2294 == 0x5B) {
                    reverse = (TI16 *)(src + 0xE0);
                    qcopy(&D_L23_001B1FB0, reverse);
                    func_00282D30(&D_L23_001B1FB0, &D_L23_001B1FB0, -1.0f);
                    D_00189E20.f188C = (u8 *)&D_L23_001B1FB0;
                    qcopy(st + 0x30, &D_L23_001B1FB0);
                    st[0x28] = 0;
                    *(s32 *)(st + 0x18) = 1;
                    st[0x29] = 0;
                }
            }
        }
        *(s32 *)(st + 0x20) = 0;
        func_002E5CF8(1, 0, obj);
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x41;
        obj[0xBC] = 0;
    }
    return obj;
}

extern int func_002E5CF8(int, int, u8 *);
extern void func_0029F338(u8 *object);
extern float D_L23_001B1914 __attribute__((sda));
extern float D_L23_001B1918 __attribute__((sda));
extern float D_L23_001B191C __attribute__((sda));
extern float D_L23_001B1920 __attribute__((sda));
extern float D_L23_001B192C __attribute__((sda));
extern float D_L23_001B1930 __attribute__((sda));
extern float D_L23_001B3700[] __attribute__((sda));
extern u8 D_L23_001A8F20[] __attribute__((sda));
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L23Hit1C0A80;
extern L23Hit1C0A80 D_L23_001C0A80;
typedef struct {
    float v[4] __attribute__((aligned(16)));
    u8 *obj;
    s32 flags;
    u8 b18;
    u8 b19;
    u16 h1A;
    float f1C;
    s32 f20;
} L23Rec;
extern void func_002AFFD8(void *, void *, s32);
extern float func_002AA2E8(float *, float, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282C10(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern void func_002A7A00(void *, float, float);
extern s32 func_002761F8(void *, void *, s32, s32, void *);
extern s32 func_00282948(void *);
extern void func_PAL_002AC718(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);
extern void func_00277F48(void *, s32, s32, void *, float);
extern void func_L00_00320B70(void *, void *, void *, void *, void *, void *, float, float, float, float);
extern void func_002C65A0(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

void func_PAL_L23_004281E8(u8 *obj) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float mtx[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    L23Rec rec;
    u8 *vars;
    u8 *hit;
    u8 *other;
    float len;
    float r;
    s32 n;
    s32 flag;
    u16 cls;

    *(u16 *)(obj + 0x34) &= 0xFFBE;
    vars = *(u8 **)(obj + 0x68);
    func_002AFFD8(obj + 0x10, up, 0);
    func_002AA2E8((float *)(vars + 0x1C), 2.8000002f, 0.080000006f);
    func_00282F20(vel, obj + 0xC0, *(float *)(vars + 0x1C));
    func_00282F20(axis, up, 1.0f);
    func_00282DD8(quat, obj + 0xE0, axis);
    func_00282D30(quat, quat, D_L23_001B192C * 0.5f);
    len = func_00282DF0(quat);
    quat[3] = -func_00282C10(1.0f - len * len);
    func_00283958(quat, mtx);
    func_00283738(obj + 0xC0, mtx, obj + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            func_00282D30(c, *(u8 **)(vars + 0x18) + 0xE0, D_L23_001B1930);
            func_00282CC0(b, *(u8 **)(vars + 0x18) + 0x10, c);
            func_L00_00320B70(obj + 0x10, obj + 0xC0, b, vars + 0x20, up, a,
                              D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B1920);
            func_00282F20(obj + 0xC0, obj + 0xC0, 1.0f);
            func_00282D30(vel, obj + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x79) {
                func_00282CF0(a, obj + 0x10, *(u8 **)(vars + 0x2C));
                if (func_00282DB0(a, vel) < 0.0f) {
                    func_L00_00320B70(obj + 0x10, obj + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, b,
                                      D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B191C);
                    func_00282F20(obj + 0xC0, obj + 0xC0, 1.0f);
                    func_00282D30(vel, obj + 0xC0, *(float *)(vars + 0x1C));
                }
            }
        } else {
            func_00282D30(vel, vars + 0x30, *(float *)(vars + 0x1C));
            func_00282F20(a, vel, 1.0f);
            qcopy(obj + 0xC0, a);
        }
    }
    qcopy(b, obj + 0x10);
    func_00282D30(c, vel, 0.7f);
    r = func_002A7878(0.1f, 0.3f);
    n = func_002A77E0(0xFF);
    func_002A7A00(a, 0.0f, 0.1f);
    func_00282CC0(a, a, b);
    func_002C65A0(a, D_L23_001A8F20, 0xC, 0x808080, n, 0x20, 0, r * 210000.0f, r * 42000.0f, 0.0f, 0);
    func_00282CC0(b, b, c);
    qcopy(a, obj + 0x10);
    func_00282CC0(obj + 0x10, obj + 0x10, vel);
    if (*(float *)(obj + 0x10) < 0.0f || *(float *)(obj + 0x14) < 0.0f || *(float *)(obj + 0x18) < 0.0f) {
        func_0029F338(obj);
        return;
    }
    rec.obj = obj;
    rec.flags = 0x8B0003;
    rec.f1C = D_L23_001B3700[0];
    rec.f20 = 0;
    rec.b18 = 3;
    rec.b19 = 3;
    rec.h1A = *(u16 *)(obj + 0xAA);
    if (obj[0xBC] == 0 && func_002761F8(a, obj + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
        hit = D_L23_001C0A80.f18;
        if (hit != 0) {
            if (hit != *(u8 **)(obj + 0xB8)) {
                obj[0xBC] = 2;
                qcopy(obj + 0x10, &D_L23_001C0A80.f20);
            }
        } else if (D_L23_001C0A80.f1C > 0) {
            obj[0xBC] = 1;
            qcopy(obj + 0x10, &D_L23_001C0A80.f20);
        }
        flag = 0;
        other = D_L23_001C0A80.f18;
        if (other != 0) {
            cls = *(u16 *)(other + 0xAA);
            if (cls == 0xF7E || cls == 0xF7F || (s16)cls == 0x120F) {
                func_002E5CF8(2, 0, obj);
                flag = 1;
            }
        }
        if (flag == 0) {
            func_002E5CF8(0, 0, obj);
        }
    } else if (func_00282948(vars + 0x14) != 0) {
        func_0029F338(obj);
        return;
    }
    if (obj[0xBC] != 0) {
        func_PAL_002AC718(obj, D_L23_001A8F20, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        func_00277F48(obj + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        func_0029F338(obj);
    }
}
