#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } BarlowVector;
extern u8 D_L04_001BF880[];
extern int D_L04_001A8F00;
extern int D_L04_001B2224[] __attribute__((sda));
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
extern u8 D_001A7A40;
extern void func_L01_003128C0(void *);
extern int func_L01_003245E0(void *, int, f32);
extern void func_L01_003246D0(int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_002A7750(void *, int, int);
extern int func_00282948(int *);
extern f32 func_002A7878(f32, f32);
extern int func_00283CF0(f32);
extern void func_002A7470(void *, int, int, int);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern f32 func_00282DF0(void *);
extern f32 func_00283B98(f32, f32);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00282E20(void *);
extern void func_002AEC48(void *, void *, int, f32, f32);
extern u32 D_0013979C __attribute__((nosda));
extern u8 D_001A7BCD;
extern u8 D_00139605 __attribute__((nosda));
extern int D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern void func_L04_00423178(void *);
extern void func_L00_00427290(void);
extern void func_002F5CC8(void);
extern void func_002AD7B8(int);
extern void func_00288308(int);
extern void func_US2_002AFF10(int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_0029B3E0(int, int);
extern void func_0029F338(void *);

/* Advances the conversation states and turns the two manipulators toward the
 * hero or a periodically chosen idle target. */
void func_US2_L04_00424978(u8 *object) {
    BarlowVector target, origin, delta;
    u8 *data = *(u8 **)(object + 0x68);
    unsigned int state;
    f32 rate, heading, yaw, pitch;
    f32 blend = 0.3f;
    int look;
    func_L04_00423178(object);
    state = object[0x20];
    switch (state) {
    case 0:
    if (D_001A7BCD) {
        func_0029F338(object);
        return;
    }
    func_L01_003128C0(object);
    if (D_0013979C & 0x800000) func_002A7750(object, 3, -1);
    else func_002A7750(object, 1, -1);
    goto stateDone;
    case 1:
    if (func_L01_003245E0(object, 10, 4.0f)) {
        func_L01_003246D0((int)object);
        if (func_00288AA0(D_L04_001BF880, 0x37)) {
            func_00288BE8(D_L04_001BF880);
            func_002A7750(object, 2, -1);
        }
    }
    goto stateDone;
    case 2:
    D_L04_001B2224[1] = 1;
    if (D_L04_001A8F00 == 2) {
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
    }
    if (!func_002F5D10()) {
        D_L04_001B2224[1] = 0;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) &= ~1;
        func_L00_00427290();
        func_002A7750(object, 3, -1);
    }
    goto stateDone;
    case 3:
    if (D_00139605 && func_L01_003245E0(object, 10, 2.5f)) {
        func_L01_003246D0((int)object);
        if (func_00288AA0(D_L04_001BF880, 0x39)) {
            func_00288AA0(D_L04_001BF880, 5);
            func_00288AA0(D_L04_001BF880, 0x3A);
            func_00288BE8(D_L04_001BF880);
            func_002F5CC8();
            func_002A7750(object, 4, -1);
        }
    }
    goto stateDone;
    case 4:
    D_L04_001B2224[1] = 1;
    if (D_L04_001A8F00 == 2) {
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
    }
    if (!func_002F5D10()) {
        D_L04_001B2224[1] = 0;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) &= ~1;
        func_002AD7B8(5);
        func_00288308(0x30);
        func_US2_002AFF10(5);
        if (object[0xB0] != 0xFF) {
            int channel = object[0xB0];
            if (!(D_0019B2E8[channel + D_001A79F0 * 16] & 0x80))
                func_002A0430(channel);
            func_002DF3F8(&((Hero *)D_00189E20)->q[0x80 / 16], &((Hero *)D_00189E20)->q[0x90 / 16]);
        } else {
            func_0029B3E0(0, -1);
        }
        func_0029F338(object);
        return;
    }
    }
stateDone:
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && func_00282948((int *)(data + 0x11C))) {
            *(int *)(data + 0x11C) = func_00283CF0(func_002A7878(1200.0f, 2400.0f));
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            func_002A7470(object, 0, 0, 10);
        }
    }
    rate = 0.02f;
    look = 0;
    if (object[0x43] == 0) {
        look = 1;
        if (func_00282E80(object + 0x10, &((Hero *)D_00189E20)->q[0x80 / 16]) < 8.0f &&
            func_00283C80(*(f32 *)(object + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0xE0 / 4] - *(f32 *)(object + 0x10), ((Hero *)D_00189E20)->f[0xE4 / 4] - *(f32 *)(object + 0x14))) < 1.5707964897155762f) {
            if (func_00282DF0(&((Hero *)D_00189E20)->f[0x110 / 4]) > 0.01f)
                *(int *)(data + 0x114) = 120;
            else
                func_00282948((int *)(data + 0x114));
        } else if (*(int *)(data + 0x114)) {
            *(int *)(data + 0x114) = 0;
            qcopy((data + 0x100), &((Hero *)D_00189E20)->q[0xE0 / 16]);
        }
        if (func_00282948((int *)(data + 0x118))) {
            *(int *)(data + 0x118) = func_00283CF0(func_002A7878(180.0f, 300.0f));
            heading = func_00283B98(*(f32 *)(object + 0xF8), func_002A7878(-90.0f, 90.0f) * 0.01745329424738884f);
            pitch = func_002A7878(0.0f, 30.0f) * 0.01745329424738884f;
            func_002AF000(data + 0x100, 6.0f, heading, pitch);
            func_00282CC0(data + 0x100, data + 0x100, object + 0x10);
        }
        if (*(int *)(data + 0x114)) {
            qcopy(&target, &((Hero *)D_00189E20)->q[0xE0 / 16]);
            rate = 0.04f;
        } else {
            qcopy(&target, (data + 0x100));
        }
    }
    if (look) {
        qcopy(&origin, (object + 0x10));
        origin.f[2] += 2.0f;
        func_00282CF0(&delta, &target, &origin);
        yaw = func_00283BE0(func_00283248(delta.f[0], delta.f[1]), *(f32 *)(object + 0xF8));
        pitch = -func_00283248(func_00282E20(&delta), delta.f[2]);
        if (yaw > 1.5707964897155762f)
            yaw = 1.5707964897155762f;
        else if (yaw < -1.5707964897155762f)
            yaw = -1.5707964897155762f;
        /* This object's update computes pitch but only applies yaw. */
        if (pitch > 0.523598849773407f)
            pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f)
            pitch = -0.523598849773407f;
        *(f32 *)(data + 0x68) = yaw * 0.6f;
        *(f32 *)(data + 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40)
        *(f32 *)(data + 0x70) = 2.75f;
    func_002AEC48(object, data, 0, rate, blend);
    func_002AEC48(object, data + 0x80, 1, rate, blend);
}
