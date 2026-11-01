#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
extern int func_002E5CF8(int, int, u8 *);
extern void func_0029F338(u8 *object);
extern float D_L22_001B1524 __attribute__((sda));
extern float D_L22_001B1528 __attribute__((sda));
extern float D_L22_001B152C __attribute__((sda));
extern float D_L22_001B1530 __attribute__((sda));
extern float D_L22_001B153C __attribute__((sda));
extern float D_L22_001B1540 __attribute__((sda));
extern float D_L22_001A93E0[] __attribute__((sda));
extern u8 D_L22_001A8F20[] __attribute__((sda));
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L22Hit1C00C0;
extern L22Hit1C00C0 D_L22_001C00C0;
typedef struct {
    float v[4] __attribute__((aligned(16)));
    u8 *obj;
    s32 flags;
    u8 b18;
    u8 b19;
    u16 h1A;
    float f1C;
    s32 f20;
} L22Rec;
extern void func_002AFFD8(void *, void *, s32);
extern float func_002AA2E8(float *, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00282C10(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
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

void func_PAL_L22_0041858C(u8 *obj) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float mtx[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    L22Rec rec;
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
    func_00282D30(quat, quat, D_L22_001B153C * 0.5f);
    len = func_00282DF0(quat);
    quat[3] = -func_00282C10(1.0f - len * len);
    func_00283958(quat, mtx);
    func_00283738(obj + 0xC0, mtx, obj + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            func_00282D30(c, *(u8 **)(vars + 0x18) + 0xE0, D_L22_001B1540);
            func_00282CC0(b, *(u8 **)(vars + 0x18) + 0x10, c);
            func_L00_00320B70(obj + 0x10, obj + 0xC0, b, vars + 0x20, up, a,
                              D_L22_001B1524, D_L22_001B1528, 0.0f, D_L22_001B1530);
            func_00282F20(obj + 0xC0, obj + 0xC0, 1.0f);
            func_00282D30(vel, obj + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x79) {
                func_00282CF0(a, obj + 0x10, *(u8 **)(vars + 0x2C));
                if (func_00282DB0(a, vel) < 0.0f) {
                    func_L00_00320B70(obj + 0x10, obj + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, b,
                                      D_L22_001B1524, D_L22_001B1528, 0.0f, D_L22_001B152C);
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
    func_002C65A0(a, D_L22_001A8F20, 0xC, 0x808080, n, 0x20, 0, r * 210000.0f, r * 42000.0f, 0.0f, 0);
    func_00282CC0(b, b, c);
    qcopy(a, obj + 0x10);
    func_00282CC0(obj + 0x10, obj + 0x10, vel);
    if (*(float *)(obj + 0x10) < 0.0f || *(float *)(obj + 0x14) < 0.0f || *(float *)(obj + 0x18) < 0.0f) {
        func_0029F338(obj);
        return;
    }
    rec.obj = obj;
    rec.flags = 0x8B0003;
    rec.f1C = D_L22_001A93E0[0];
    rec.f20 = 0;
    rec.b18 = 3;
    rec.b19 = 3;
    rec.h1A = *(u16 *)(obj + 0xAA);
    if (obj[0xBC] == 0 && func_002761F8(a, obj + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
        hit = D_L22_001C00C0.f18;
        if (hit != 0) {
            if (hit != *(u8 **)(obj + 0xB8)) {
                obj[0xBC] = 2;
                qcopy(obj + 0x10, &D_L22_001C00C0.f20);
            }
        } else if (D_L22_001C00C0.f1C > 0) {
            obj[0xBC] = 1;
            qcopy(obj + 0x10, &D_L22_001C00C0.f20);
        }
        flag = 0;
        other = D_L22_001C00C0.f18;
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
        func_PAL_002AC718(obj, D_L22_001A8F20, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        func_00277F48(obj + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        func_0029F338(obj);
    }
}
