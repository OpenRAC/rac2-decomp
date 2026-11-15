#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

extern int func_002E5CF8(int, int, u8 *);

extern void func_0029F338(u8 *object);

/* the steering constants of the homing shot */
extern float D_L23_001B1914 __attribute__((sda));

extern float D_L23_001B1918 __attribute__((sda));

extern float D_L23_001B191C __attribute__((sda));

extern float D_L23_001B1920 __attribute__((sda));

extern float D_L23_001B192C __attribute__((sda));

extern float D_L23_001B1930 __attribute__((sda));

/* Absolute scalar view; the surrounding object extent is unqualified. */
extern float D_L23_001B3700[] __attribute__((sda));

extern u8 D_L23_001A8F20[] __attribute__((sda));

/* the last hit reported by the collision query */
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L23Hit1C0A80;

extern L23Hit1C0A80 D_L23_001C0A80;

/* the record the collision query and the damage call read */
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

extern void func_002ABBB8(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);

extern void func_00277F48(void *, s32, s32, void *, float);

extern void func_L00_00320B70(void *, void *, void *, void *, void *, void *, float, float, float, float);

/* EE ABI: retain integer and float argument order within their register banks. */
extern void func_002C65A0(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

void func_L23_00422E08(u8 *obj) {
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
    ApproachValue((float *)(vars + 0x1C), 2.3333335f, 0.055555556f);
    vec_scale_to_length(vel, obj + 0xC0, *(float *)(vars + 0x1C));
    vec_scale_to_length(axis, up, 1.0f);
    FastVecCross(quat, obj + 0xE0, axis);
    FastVecScale(quat, quat, D_L23_001B192C * 0.5f);
    len = FastVecLength(quat);
    quat[3] = -square_root(1.0f - len * len);
    quaternion_to_rotation_basis(quat, mtx);
    multiply_matrix3x3(obj + 0xC0, mtx, obj + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            FastVecScale(c, *(u8 **)(vars + 0x18) + 0xE0, D_L23_001B1930);
            FastVecAdd(b, *(u8 **)(vars + 0x18) + 0x10, c);
            func_L00_00320B70(obj + 0x10, obj + 0xC0, b, vars + 0x20, up, a,
                              D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B1920);
            vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
            FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x91) {
                FastVecSub(a, obj + 0x10, *(u8 **)(vars + 0x2C));
                if (FastVecDot(a, vel) < 0.0f) {
                    func_L00_00320B70(obj + 0x10, obj + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, b,
                                      D_L23_001B1914, D_L23_001B1918, 0.0f, D_L23_001B191C);
                    vec_scale_to_length(obj + 0xC0, obj + 0xC0, 1.0f);
                    FastVecScale(vel, obj + 0xC0, *(float *)(vars + 0x1C));
                }
            }
        } else {
            FastVecScale(vel, vars + 0x30, *(float *)(vars + 0x1C));
            vec_scale_to_length(a, vel, 1.0f);
            qcopy(obj + 0xC0, a);
        }
    }
    qcopy(b, obj + 0x10);
    FastVecScale(c, vel, 0.7f);
    r = func_002A7878(0.1f, 0.3f);
    n = func_002A77E0(0xFF);
    func_002A7A00(a, 0.0f, 0.1f);
    FastVecAdd(a, a, b);
    func_002C65A0(a, D_L23_001A8F20, 0xF, 0x808080, n, 0x20, 0, r * 210000.0f, r * 42000.0f, 0.0f, 0);
    FastVecAdd(b, b, c);
    qcopy(a, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, vel);
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
    if (obj[0xBC] == 0 && CollLine(a, obj + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
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
                PlayMobySound(2, 0, obj);
                flag = 1;
            }
        }
        if (flag == 0) {
            PlayMobySound(0, 0, obj);
        }
    } else if (func_00282948(vars + 0x14) != 0) {
        func_0029F338(obj);
        return;
    }
    if (obj[0xBC] != 0) {
        SpawnExplosionEffects(obj, D_L23_001A8F20, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        func_00277F48(obj + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        func_0029F338(obj);
    }
}
