#include "include_asm.h"

#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
#define I(p, o) (*(s32 *)((p) + (o)))
#define B(p, o) (*(u8 *)((p) + (o)))
#define H(p, o) (*(u16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
extern u8 D_001A7BD8[] MACRO_ADDR, D_L17_001A7C88[] MACRO_ADDR, D_001A7A40 MACRO_ADDR;
#define D_001A7BDA D_001A7BD8[2]
#define D_L17_001A7C8F D_L17_001A7C88[7]
extern s32 D_L17_001B2964[] MACRO_ADDR;
#define BUSY D_L17_001B2964[1]
extern s32 D_001397F0 NOT_SDA, D_00138324 NOT_SDA;
extern s32 D_001A79F8 MACRO_ADDR;
extern s32 D_L17_001A8F00 MACRO_ADDR, D_L17_001B2D0C MACRO_ADDR, D_L17_001B2C1C MACRO_ADDR;
extern u8 D_L17_001BFDC0[];
typedef struct { char pad[0x30]; s32 lo; s32 hi; } PriceTable;
extern PriceTable D_L17_0028C550;
extern s32 D_L17_0028C580 NOT_SDA, D_L17_0028C584 NOT_SDA;
#define PRICE_LT(m) (D_L17_001A7C8F ? (m) < D_L17_0028C584 : (m) < D_L17_0028C580)
typedef struct { char pad[0x80]; char obj[0x60]; V pos; } HeroRecord;
extern HeroRecord D_00189E20;
extern void func_L04_00423178(s32);
extern void func_002A7750(s32, s32, s32);
extern void func_L01_003128C0(s32);
extern int func_002ACBC8(void *, s32);
extern int func_00288AA0(void *, s32);
extern void func_L01_003246D0(s32), func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(s32, s32, s32, s32);
extern int func_L01_003245E0(s32, s32, float);
extern void func_L00_0030C710(s32), func_L01_00324550(s32, s32, s32);
extern void func_002AD7B8(s32), func_US2_002AFF10(s32), func_0029B3E0(s32, s32), func_0029F338(s32);
extern int func_00282978(s32), func_00282948(s32);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_002A7470(s32, s32, s32, s32);
extern float func_00282E80(s32, void *), func_00283248(float, float), func_00283C80(float, float);
extern float func_00282DF0(void *), func_00283B98(float, float);
extern void func_002AF000(s32, float, float, float), func_00282CC0(s32, s32, s32);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283BE0(float, float), func_00282E20(void *);
extern void func_002AEC48(s32, s32, s32, float, float);
/* A constant rate reaches the argument register directly, so each call loads it again. */
static inline void update_joint(s32 obj, s32 joint, s32 index, float speed, float rate) {
    func_002AEC48(obj, joint, index, speed, rate);
}

void func_US2_L17_0041F898(s32 obj) {
    V target, raised, delta;
    s32 data = I(obj, 0x68), active;
    float speed, yaw, pitch, ang;

    func_L04_00423178(obj);
    switch (B(obj, 0x20)) {
    case 0:
        if (D_001A7BDA) goto destroy;
        if (D_001397F0 & 0x200) {
            s32 bolts = D_001A79F8;
            if (PRICE_LT(bolts)) func_002A7750(obj, 3, -1);
            else func_002A7750(obj, 4, -1);
        } else {
            func_002A7750(obj, 1, -1);
        }
        func_L01_003128C0(obj);
        break;
    case 1:
        if (func_002ACBC8(D_00189E20.obj, I(data, 0x120)) && func_00288AA0(D_L17_001BFDC0, 0x89)) {
            func_L01_003246D0(obj);
            func_00288BE8(D_L17_001BFDC0);
            func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        BUSY = 1;
        if (D_L17_001A8F00 == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            BUSY = 0;
            {
                s32 p = D_L17_001B2D0C + (I(data, 0x120) << 7);
                func_L00_002B9D60(p + 0x30, p + 0x70, 0, 1);
            }
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            {
                s32 bolts = D_001A79F8;
                if (PRICE_LT(bolts)) func_002A7750(obj, 3, -1);
                else func_002A7750(obj, 4, -1);
            }
        }
        break;
    case 3:
        {
            s32 bolts = D_001A79F8;
            if (D_L17_001A7C8F ? D_L17_0028C550.hi < bolts : D_L17_0028C550.lo < bolts) {
                func_002A7750(obj, 4, -1);
                break;
            }
        }
        if (func_L01_003245E0(obj, 10, 4.f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x1329, D_L17_001A7C8F ? D_L17_0028C550.hi : D_L17_0028C550.lo, -1);
            func_L01_003246D0(obj);
        }
        break;
    case 4:
        {
            s32 bolts = D_001A79F8;
            if (D_L17_001A7C8F ? bolts < D_L17_0028C550.hi : bolts < D_L17_0028C550.lo) {
                func_L00_0030C710(180);
                func_002A7750(obj, 3, -1);
                break;
            }
        }
        if (func_L01_003245E0(obj, 10, 4.f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x132A, D_L17_001A7C8F ? D_L17_0028C550.hi : D_L17_0028C550.lo, -1);
            func_L01_003246D0(obj);
            if ((D_00138324 & 0x10) && func_00288AA0(D_L17_001BFDC0, 0x8a)) {
                func_00288AA0(D_L17_001BFDC0, 0x12);
                func_00288AA0(D_L17_001BFDC0, 0x8b);
                func_00288BE8(D_L17_001BFDC0);
                func_002A7750(obj, 5, -1);
            }
        }
        break;
    case 5:
        BUSY = 1;
        if (D_L17_001A8F00 == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            BUSY = 0;
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            if (!D_001A7BDA) {
                {
                    s32 bolts = D_001A79F8;
                    D_001A79F8 = bolts - (D_L17_001A7C8F ? D_L17_0028C584 : D_L17_0028C580);
                }
                func_L00_0030C710(180);
                func_002AD7B8(0x12);
                func_US2_002AFF10(0x12);
                if (I(data, 0x124) != -1) B((I(data, 0x124) << 8) + D_L17_001B2C1C, 0xbc) = 1;
                func_0029B3E0(0, -1);
destroy:
                func_0029F338(obj);
                return;
            }
        }
        break;
    }

    if (B(obj, 0x20)) {
        if (!B(obj, 0x43) && func_00282978(data + 0x11e))
            H(data, 0x11e) = func_00283CF0(func_002A7878(1200.f, 2400.f));
        else if ((B(obj, 0x60) & 2) && B(obj, 0x43))
            func_002A7470(obj, 0, 0, 10);
    }

    speed = .02f;
    active = 0;
    if (!B(obj, 0x43)) {
        active = 1;
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
    }

    if (active) {
        qcopy(&raised, (void *)(obj + 0x10));
        raised.f[2] += 2.f;
        func_00282CF0(&delta, &target, &raised);
        yaw = func_00283BE0(func_00283248(delta.f[0], delta.f[1]), F(obj, 0xf8));
        pitch = -func_00283248(func_00282E20(&delta), delta.f[2]);
        if (yaw > 1.5707964897155762f) yaw = 1.5707964897155762f;
        else if (yaw < -1.5707964897155762f) yaw = -1.5707964897155762f;
        if (pitch > .52359885f) pitch = .52359885f;
        else if (pitch < -.52359885f) pitch = -.52359885f;
        F(data, 0x64) = pitch;
        F(data, 0x68) = yaw * .6f;
        F(data, 0xe8) = yaw * .4f;
    }

    if (D_001A7A40) F(data, 0x70) = 2.75f;
    update_joint(obj, data, 0, speed, .3f);
    update_joint(obj, data + 0x80, 1, speed, .3f);
}
