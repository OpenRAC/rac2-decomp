#include "common.h"

typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;

#define I(p, o) (*(s32 *)((p) + (o)))
#define B(p, o) (*(u8 *)((p) + (o)))
#define H(p, o) (*(u16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

extern u8 D_001A7AFF MACRO_ADDR, D_001A7B28[] MACRO_ADDR, D_001A7B61 MACRO_ADDR;
#define D_001A7B29 D_001A7B28[1]
extern u8 D_L14_001A7C88[] MACRO_ADDR, D_001A7A40 MACRO_ADDR;
#define D_L14_001A7C8F D_L14_001A7C88[7]
extern s32 D_L14_001B22E4[] MACRO_ADDR;
#define BUSY D_L14_001B22E4[1]

extern s32 D_00138324 NOT_SDA;
extern s32 D_001A79F8 MACRO_ADDR; /* the player's bolts */
extern s32 D_L14_001A8F00 MACRO_ADDR;
extern u8 D_L14_001BF700[];
extern char D_00139768[];

typedef struct { char pad[0x28]; s32 lo; s32 hi; } PriceTable;
extern PriceTable D_L14_00291850;
extern s32 D_L14_00291878 NOT_SDA, D_L14_0029187C NOT_SDA;
#define PRICE_LT(m) (D_L14_001A7C8F ? (m) < D_L14_0029187C : (m) < D_L14_00291878)

typedef struct { char pad[0x80]; char obj[0x60]; V pos; } HeroRecord;
extern HeroRecord D_00189E20;

extern void func_L01_003209F8(s32, s32, s32, float);
extern int func_L14_00425C08(s32);
extern void func_002A7750(s32, s32, s32);
extern void func_L01_003128C0(s32);
extern int func_00288AA0(void *, s32);
extern void func_L01_003246D0(s32), func_00288BE8(void *);
extern int func_002F5D10(void);
extern int func_L01_003245E0(s32, s32, float);
extern void func_L00_0030C710(s32), func_L01_00324550(s32, s32, s32);
extern void func_0029B3E0(s32, s32), func_0029F338(s32), func_002A8598(s32, s32);
extern int func_00282948(s32);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_002A7470(s32, s32, s32, s32);
extern float func_00282E80(s32, void *), func_00283248(float, float), func_00283C80(float, float);
extern float func_00282DF0(void *), func_00283B98(float, float);
extern void func_002AF000(s32, float, float, float), func_00282CC0(s32, s32, s32);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283BE0(float, float), func_00282E20(void *);
extern void func_002AEC48(s32, s32, s32, float, float);
extern void func_002AF1D0(s32, s32, s32, s32);

static inline void update_joint(s32 obj, s32 joint, s32 index, float speed, float rate) {
    func_002AEC48(obj, joint, index, speed, rate);
}

void func_L14_00425CB0(s32 obj) {
    V target, raised, delta;
    s32 data = I(obj, 0x68), p;
    float speed, yaw, pitch, ang;

    func_L01_003209F8(obj, 0, 0x11D3, 2.5f);
    switch (B(obj, 0x20)) {
    case 0:
        I(data, 0x120) = 0;
        if (D_001A7AFF || D_001A7B29 || (p = (s32)D_00139768, I(p, 0x7C) < 0)) {
            func_0029F338(obj);
            return;
        }
        func_L01_003128C0(obj);
        if (I(p, 0x7C) & 0x40000000) {
            if (func_L14_00425C08(obj)) func_002A7750(obj, 2, -1);
        } else {
            func_002A7750(obj, 1, -1);
        }
        break;
    case 1:
        if (func_L01_003245E0(obj, 10, 2.5f)) {
            func_L01_003246D0(obj);
            if (func_00288AA0(D_L14_001BF700, 0x7E)) {
                func_00288BE8(D_L14_001BF700);
                func_002A7750(obj, 2, -1);
            }
        }
        break;
    case 2:
        BUSY = 1;
        if (D_L14_001A8F00 == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            F(obj, 0xf8) = func_00283B98(F(obj, 0xf8), 3.1415927f);
            BUSY = 0;
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            if (func_L14_00425C08(obj)) {
                if (B(obj, 0x43) != 1) func_002A7470(obj, 1, 0, 10);
                {
                    s32 bolts = D_001A79F8;
                    if (PRICE_LT(bolts)) func_002A7750(obj, 3, -1);
                    else func_002A7750(obj, 4, -1);
                }
            }
        }
        break;
    case 3:
        {
            s32 bolts = D_001A79F8;
            if (D_L14_001A7C8F ? D_L14_00291850.hi <= bolts : D_L14_00291850.lo <= bolts) {
                func_002A7750(obj, 4, -1);
                break;
            }
        }
        if (func_L01_003245E0(obj, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x27d5, D_L14_001A7C8F ? D_L14_00291850.hi : D_L14_00291850.lo, -1);
            func_L01_003246D0(obj);
        }
        break;
    case 4:
        {
            s32 bolts = D_001A79F8;
            if (D_L14_001A7C8F ? bolts < D_L14_00291850.hi : bolts < D_L14_00291850.lo) {
                func_L00_0030C710(180);
                func_002A7750(obj, 3, -1);
                break;
            }
        }
        if (func_L01_003245E0(obj, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x27d6, D_L14_001A7C8F ? D_L14_00291850.hi : D_L14_00291850.lo, -1);
            func_L01_003246D0(obj);
            if (D_00138324 & 0x10) {
                {
                    s32 bolts = D_001A79F8;
                    D_001A79F8 = bolts - (D_L14_001A7C8F ? D_L14_00291850.hi : D_L14_00291850.lo);
                }
                if (func_00288AA0(D_L14_001BF700, 0x7f)) {
                    func_00288BE8(D_L14_001BF700);
                    func_002A7750(obj, 5, -1);
                }
            }
        }
        break;
    case 5:
        BUSY = 1;
        if (D_L14_001A8F00 == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (I(data, 0x120) && D_L14_001A8F00 == 2) {
            H(I(data, 0x120), 0x34) |= 1;
            B(I(data, 0x120), 0x31) = 0;
        }
        if (!func_002F5D10()) {
            BUSY = 0;
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            if (B(obj, 0x21) != 0xff) func_002A8598(B(obj, 0x21), 1);
            if (I(data, 0x120)) {
                func_0029F338(I(data, 0x120));
                I(data, 0x120) = 0;
            }
            if (!D_001A7B29) {
                D_001A7B29 = 1;
                D_001A7B61 = 1;
            }
            func_0029B3E0(0, -1);
            F(obj, 0xf8) = func_00283B98(F(obj, 0xf8), 3.1415927f);
            if (B(obj, 0x43)) func_002A7470(obj, 0, 0, 10);
            func_002A7750(obj, 6, -1);
        }
        break;
    }

    if (B(obj, 0x20) == 1 || B(obj, 0x20) == 2 || B(obj, 0x20) == 6) {
        if (!B(obj, 0x43) && func_00282948(data + 0x11C))
            I(data, 0x11C) = func_00283CF0(func_002A7878(1200.f, 2400.f));
        else if ((B(obj, 0x60) & 2) && B(obj, 0x43))
            func_002A7470(obj, 0, 0, 10);
    }

    speed = .02f;
    if (func_00282E80(obj + 0x10, D_00189E20.obj) < 8.f
        && func_00283C80(F(obj, 0xf8), func_00283248(D_00189E20.pos.f[0] - F(obj, 0x10),
                                                     D_00189E20.pos.f[1] - F(obj, 0x14))) < 1.5707964897155762f) {
        if (func_00282DF0(D_00189E20.obj + 0x90) > .01f) I(data, 0x114) = 120;
        else func_00282948(data + 0x114);
    } else if (I(data, 0x114)) {
        I(data, 0x114) = 0;
        qcopy((void *)(data + 0x100), &D_00189E20.pos);
    }
    if (func_00282948(data + 0x118)) {
        I(data, 0x118) = func_00283CF0(func_002A7878(180.f, 300.f));
        ang = func_00283B98(F(obj, 0xf8), func_002A7878(-90.f, 90.f) * 0.01745329424738884f);
        pitch = func_002A7878(0.f, 30.f) * 0.01745329424738884f;
        func_002AF000(data + 0x100, 6.f, ang, pitch);
        func_00282CC0(data + 0x100, data + 0x100, obj + 0x10);
    }
    if (I(data, 0x114)) {
        qcopy(&target, &D_00189E20.pos);
        speed = .04f;
    } else {
        qcopy(&target, (void *)(data + 0x100));
    }
    qcopy(&raised, (void *)(obj + 0x10));
    raised.f[2] += 2.f;
    func_00282CF0(&delta, &target, &raised);
    yaw = func_00283BE0(func_00283248(delta.f[0], delta.f[1]), F(obj, 0xf8));
    pitch = -func_00283248(func_00282E20(&delta), delta.f[2]);
    if (yaw > .8726647f) yaw = .8726647f;
    else if (yaw < -.8726647f) yaw = -.8726647f;
    if (pitch > .52359885f) pitch = .52359885f;
    else if (pitch < -.017453294f) pitch = -.017453294f;
    F(data, 0x64) = pitch;
    F(data, 0x68) = yaw * .5f;
    F(data, 0xe8) = yaw * .3f;
    if (I(data, 0x120)) func_002AF1D0(obj, I(data, 0x120), 2, 0);
    if (D_001A7A40) F(data, 0x70) = 2.75f;
    update_joint(obj, data, 0, speed, .3f);
    update_joint(obj, data + 0x80, 1, speed, .3f);
}
