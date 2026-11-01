#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } BarlowVector;
extern u8 *D_L04_001B24DC MACRO_ADDR;
extern u8 D_L04_001BF880[];
extern int D_L04_001A8F00 MACRO_ADDR;
extern int D_L04_001B2224[] __attribute__((sda));
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
extern BarlowVector D_00189F00;
extern f32 D_00189F30[4];
extern u8 D_001A7A40 MACRO_ADDR;
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
extern u32 D_001397A4;
typedef union { u8 b[0x200]; u32 w[0x80]; } GameFlags;
extern u8 D_001395B8[];
extern void func_L04_00439870(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CD8(void *, void *, void *);
extern void func_L00_002B9D60(void *, void *, int, int);
extern int func_00288FB8(int);
extern void func_00285828(int, int, int, int);
extern void func_00285788(int, int);
extern int func_002B49E0(int, int, int, int, unsigned char *);

void func_US2_L04_0043B090(u8 *object) {
    BarlowVector target, origin, delta;
    u8 *data = *(u8 **)(object + 0x68);
    u8 *linked;
    int message;
    f32 rate;
    f32 blend = 0.3f;
    f32 heading, yaw, pitch;
    int look;
    func_L04_00439870(object);
    switch (object[0x20]) {
    case 0:
        linked = D_L04_001B24DC + *(int *)(data + 0x120) * 256;
        *(int *)(linked + 0x98) = 0;
        linked[0x31] = 0;
        *(u16 *)(linked + 0x34) |= 1;
        func_L01_003128C0(object);
        if (D_001397A4 & 0x20000000) func_002A7750(object, 4, -1);
        else func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_L01_003245E0(object, 10, 6.5f)) {
            func_L01_003246D0((int)object);
            func_00288AA0(D_L04_001BF880, 0x3D);
            func_00288BE8(D_L04_001BF880);
            func_002A7750(object, 2, -1);
        }
        break;
    case 2:
        if (D_L04_001A8F00 == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        D_L04_001B2224[1] = 1;
        if (!func_002F5D10()) {
            D_L04_001B2224[1] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= ~1;
            func_00282F20(&target, object + 0xC0, 4.0f);
            func_00282CD8(&origin, &target, object + 0x10);
            func_L00_002B9D60(&target, &((Hero *)D_00189E20)->q[0x90 / 16], 0, 1);
            func_002A7750(object, 3, -1);
        }
        break;
    case 3:
        if (!((GameFlags *)D_001395B8)->b[0xA4]) {
            ((GameFlags *)D_001395B8)->b[0xA4] = 1;
            message = func_00288FB8(0x31C3);
            func_00285828(message, 0, func_00288FB8(0x312C), 1);
            func_00285788(0x40, 0);
            func_002B49E0(4, 1, 10, 0, 0);
            func_002A7750(object, 4, -1);
        }
        break;
    case 4:
        break;
    }
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && func_00282948((int *)(data + 0x11C))) {
            *(int *)(data + 0x11C) = func_00283CF0(func_002A7878(1200.0f, 2400.0f));
            if (object[0x43] != 1)
                func_002A7470(object, 1, 0, 10);
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
            if (func_00282DF0(&((Hero *)D_00189E20)->q[0x110 / 16]) > 0.01f)
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
        if (pitch > 0.174532949924469f)
            pitch = 0.174532949924469f;
        else if (pitch < -0.174532949924469f)
            pitch = -0.174532949924469f;
        *(f32 *)(data + 0x64) = pitch;
        *(f32 *)(data + 0x68) = yaw * 0.6f;
        *(f32 *)(data + 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40)
        *(f32 *)(data + 0x70) = 2.75f;
    func_002AEC48(object, data, 0, rate, blend);
    func_002AEC48(object, data + 0x80, 1, rate, blend);
}
