#include "include_asm.h"

#include "common.h"
#define S32_AT(p, o) (*(int *)((u8 *)(p) + (o)))
#define F32_AT(p, o) (*(float *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x84]; u8 first; u8 pad85; u8 second; u8 pad87[2]; u8 third; } PurchaseParts;
typedef struct { u8 pad[0x37]; u8 planet; } PurchaseSave;
typedef struct { u8 pad[0x80]; int cost; u8 tail[0x5C]; } PurchaseLevelInfo;
typedef struct { u8 pad[0xE0]; float x; float y; } PurchaseHero;
extern u8 D_00189EA0[], D_L18_0026BCF0[], D_L18_001BF9C0[];
extern PurchaseParts D_001395B8;
extern PurchaseSave D_00139568;
extern int D_001397F8 NOT_SDA;
extern int D_001A79F8;
extern int D_00138324 NOT_SDA;
extern u8 D_001A7B2F;
extern u8 D_0013959F NOT_SDA;
extern u8 D_001A7A40;
extern int D_L18_001A8F00;
extern int D_L18_001B2564[] __attribute__((sda));
extern u8 *D_L18_001B290C, *D_L18_001B281C;
extern void func_L04_00423178(void *), func_L01_003128C0(void *), func_L01_003246D0(void *);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int), func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern int func_L01_003245E0(void *, int, float);
extern void func_L01_00324550(int, int, int), func_L00_0030C710(int), func_002A0430(int);
extern void func_00288308(int), func_002AD860(int), func_US2_002B1880(int, int), func_US2_00289840(int, int);
extern void func_002DF3F8(void *, void *), func_0029B3E0(int, int), func_0029F338(void *);
extern int func_00282948(void *), func_00282978(void *), func_00283CF0(float);
extern float func_002A7878(float, float), func_00282E80(void *, void *), func_00283248(float, float);
extern float func_00283C80(float, float), func_00282DF0(void *), func_00283B98(float, float);
extern float func_00283BE0(float, float), func_00282E20(void *);
extern void func_002A7470(void *, int, int, int), func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_002AEC48(void *, void *, int, float, float);

void func_US2_L18_00441C08(u8 *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    float speed, yaw, pitch, random_yaw;
    float blend = 0.3f;
    int active;

    func_L04_00423178(obj);
    switch (U8_AT(obj, 0x20)) {
    case 0:
        if (D_001A7B2F)
            goto remove_object;
        if (D_001397F8 & 0x10000)
            func_002A7750(obj, 3, -1);
        else
            func_002A7750(obj, 1, -1);
        func_L01_003128C0(obj);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, S32_AT(state, 0x120)) && func_00288AA0(D_L18_001BF9C0, 0x90)) {
            func_L01_003246D0(obj);
            func_00288BE8(D_L18_001BF9C0);
            func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        D_L18_001B2564[1] = 1;
        if (D_L18_001A8F00 == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            func_L00_002B9D60(D_L18_001B290C + S32_AT(state, 0x120) * 128 + 0x30,
                              D_L18_001B290C + S32_AT(state, 0x120) * 128 + 0x70, 0, 1);
            U8_AT(obj, 0x31) = 1;
            U16_AT(obj, 0x34) &= 0xFFFE;
            D_L18_001B2564[1] = 0;
            func_002A7750(obj, 3, -1);
        }
        break;
    case 3:
        if (D_001395B8.first && D_001395B8.second && D_001395B8.third) {
            if (D_001A79F8 >= ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_0013959F].cost)
                func_002A7750(obj, 5, -1);
            else
                func_002A7750(obj, 4, -1);
        } else if (func_L01_003245E0(obj, 10, 1.0f)) {
            int count = 3;
            if (D_001395B8.first)
                count = 2;
            if (D_001395B8.second)
                count--;
            if (D_001395B8.third)
                count--;
            func_L01_00324550(0x132B, count, -1);
            func_L01_003246D0(obj);
        }
        break;
    case 4:
        if (((PurchaseLevelInfo *)D_L18_0026BCF0)[D_00139568.planet].cost < D_001A79F8) {
            func_002A7750(obj, 5, -1);
        } else if (func_L01_003245E0(obj, 10, 1.0f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x132C, ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_00139568.planet].cost, -1);
            func_L01_003246D0(obj);
        }
        break;
    case 5:
        if (D_001A79F8 < ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_00139568.planet].cost) {
            func_L00_0030C710(180);
            func_002A7750(obj, 4, -1);
        } else if (func_L01_003245E0(obj, 10, 1.0f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x132D, ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_00139568.planet].cost, -1);
            func_L01_003246D0(obj);
            if ((D_00138324 & 16) && func_00288AA0(D_L18_001BF9C0, 0x91)) {
                func_00288BE8(D_L18_001BF9C0);
                func_002A7750(obj, 6, -1);
                func_002A0430(U8_AT(obj, 0xB0));
            }
        }
        break;
    case 6:
        if (D_L18_001A8F00 == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        {
            unsigned int timer = U16_AT(obj, 0x96);
            unsigned int elapsed = timer++;
            U16_AT(obj, 0x96) = timer;
            if (elapsed >= 20) {
                D_L18_001B2564[1] = 1;
                if (!func_002F5D10()) {
                    D_L18_001B2564[1] = 0;
                    U8_AT(obj, 0x31) = 1;
                    U16_AT(obj, 0x34) &= 0xFFFE;
                    if (!D_001A7B2F) {
                        D_001A79F8 -= ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_0013959F].cost;
                        func_L00_0030C710(180);
                        if (S32_AT(state, 0x124) != -1)
                            U8_AT(D_L18_001B281C + S32_AT(state, 0x124) * 256, 0xBC) = 1;
                        func_00288308(55);
                        func_002AD860(55);
                    }
                    func_002A7750(obj, 7, -1);
                    U8_AT(obj, 0x31) = 0;
                    U16_AT(obj, 0x34) |= 1;
                }
            }
        }
        break;
    case 7: {
        unsigned int timer = U16_AT(obj, 0x96);
        unsigned int elapsed = timer++;
        U16_AT(obj, 0x96) = timer;
        if (elapsed >= 41) {
            func_US2_002B1880(0x1231, -1);
            func_US2_00289840(0xA11, 0x68);
            func_002DF3F8(D_00189EA0, D_00189EA0 + 16);
            func_0029B3E0(0, -1);
        remove_object:
            func_0029F338(obj);
            return;
        }
        break;
    }
    }
    if (U8_AT(obj, 0x20)) {
        if (!U8_AT(obj, 0x43) && func_00282978(state + 0x11E)) {
            U16_AT(state, 0x11E) = func_00283CF0(func_002A7878(1200, 2400));
            if (U8_AT(obj, 0x43) != 1)
                func_002A7470(obj, 1, 0, 10);
        } else if ((U8_AT(obj, 0x60) & 2) && U8_AT(obj, 0x43)) {
            func_002A7470(obj, 0, 0, 10);
        }
    }
    speed = 0.02f;
    active = 0;
    if (!U8_AT(obj, 0x43)) {
        active = 1;
        if (func_00282E80(obj + 0x10, D_00189EA0) < 8 &&
            func_00283C80(F32_AT(obj, 0xF8),
                          func_00283248(((PurchaseHero *)(D_00189EA0 - 128))->x - F32_AT(obj, 0x10),
                                        ((PurchaseHero *)(D_00189EA0 - 128))->y - F32_AT(obj, 0x14))) < 1.5707965f) {
            if (func_00282DF0(D_00189EA0 + 0x90) > 0.01f)
                S32_AT(state, 0x114) = 120;
            else
                func_00282948(state + 0x114);
        } else if (S32_AT(state, 0x114)) {
            S32_AT(state, 0x114) = 0;
            qcopy_nc(state + 0x100, D_00189EA0 + 0x60);
        }
        if (func_00282948(state + 0x118)) {
            S32_AT(state, 0x118) = func_00283CF0(func_002A7878(180, 300));
            random_yaw = func_00283B98(F32_AT(obj, 0xF8), func_002A7878(-90, 90) * 0.017453294f);
            pitch = func_002A7878(0, 30);
            func_002AF000(state + 0x100, 6, random_yaw, pitch * 0.017453294f);
            func_00282CC0(state + 0x100, state + 0x100, obj + 0x10);
        }
        if (S32_AT(state, 0x114)) {
            qcopy_nc(target, D_00189EA0 + 0x60);
            speed = 0.04f;
        } else {
            qcopy_nc(target, state + 0x100);
        }
    }
    if (active) {
        qcopy_nc(position, obj + 0x10);
        position[2] += 2;
        func_00282CF0(delta, target, position);
        yaw = func_00283BE0(func_00283248(delta[0], delta[1]), F32_AT(obj, 0xF8));
        pitch = -func_00283248(func_00282E20(delta), delta[2]);
        if (yaw > 1.5707965f)
            yaw = 1.5707965f;
        else if (yaw < -1.5707965f)
            yaw = -1.5707965f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F32_AT(state, 0x64) = pitch;
        F32_AT(state, 0x68) = yaw * 0.6f;
        F32_AT(state, 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40)
        F32_AT(state, 0x70) = 2.75f;
    func_002AEC48(obj, state, 0, speed, blend);
    func_002AEC48(obj, state + 0x80, 1, speed, blend);
}
