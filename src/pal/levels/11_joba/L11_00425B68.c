#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_00425B68);

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_00429B30);

typedef unsigned char u8;
typedef float f32;
extern u8 D_L04_001395C7;
extern u8 D_L04_002CA518;
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_001395B8[];
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern u8 D_00189EA0[];
extern u8 D_0019B2E8[];
extern u8 D_L04_001BF880[];
extern u8 D_L04_001B9680[];
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern f32 func_00282C48(f32);
extern u8 D_00189EA0[];
extern u8 D_L04_001B1218[];
extern u8 D_L04_001B1230[];
extern u8 D_L04_001B12B0[] __attribute__((sda));
extern u8 D_L04_001B12E8[] __attribute__((sda));
extern u8 D_L04_001B1300[] __attribute__((sda));
extern u8 D_L04_001B1330[] __attribute__((sda));
extern u8 D_L04_001B1348[] __attribute__((sda));
extern u8 D_L04_001B3280[] __attribute__((sda));
extern u8 D_L04_001B32B0[] __attribute__((sda));
extern u8 D_L04_001B32E0[] __attribute__((sda));
extern u8 D_L04_001B3300[] __attribute__((sda));
extern u8 D_L04_001B3320[] __attribute__((sda));
extern u8 D_L04_001B3330[] __attribute__((sda));
extern u8 D_L04_001B3360[] __attribute__((sda));
extern u8 D_L04_001B3378[] __attribute__((sda));
extern u8 D_L04_001B33A0[] __attribute__((sda));
extern u8 D_L04_001B33B0[] __attribute__((sda));
extern u8 D_L04_001B33B8[] __attribute__((sda));
extern u8 D_L04_001B33D8[] __attribute__((sda));
extern u8 D_L04_001B33E8[] __attribute__((sda));
extern u8 D_L04_001B3418[] __attribute__((sda));
extern u8 D_L04_001B3430[] __attribute__((sda));
extern u8 D_L04_001B3458[] __attribute__((sda));
extern u8 D_L04_001B3468[] __attribute__((sda));
extern u8 D_L04_001B3470[] __attribute__((sda));
extern u8 D_L04_001B3474[] __attribute__((sda));
extern u8 D_L04_001B3478[] __attribute__((sda));
extern u8 D_L04_001B347C[] __attribute__((sda));
extern u8 D_L04_001B3480[] __attribute__((sda));
extern u8 D_L04_001B3484[] __attribute__((sda));
extern u8 D_L04_001B3488[] __attribute__((sda));
extern u8 D_L04_0026D370[];
extern u8 D_L04_0026D3E0[];
extern u8 D_L04_0026D490[];
extern u8 D_L04_0026D4F0[];
extern u8 D_L04_002CA3E0[];
extern u8 D_L04_002CA438[];
extern f32 func_30F468(f32 a, f32 b);
extern f32 func_30FE88(f32 a, f32 b);
extern f32 func_30FE40(f32 a, f32 b);
extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, f32, f32);
extern void func_002AAA00(void *, f32, f32, f32, f32, void *, int);
extern f32 func_00283C80(f32, f32);
extern void func_002AA548(void *, void *, f32, f32, f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7EA0(void *, void *, void *, f32, f32, f32, f32, int);

int func_PAL_L11_0042A858(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin) {
    f32 delta[4], displacement[4], destination[4];
    f32 angle, frameSpeed = 0.0f;
    u8 *data = *(u8 **)(object + 0x68);
    int done = 0;
    f32 distance, acceleration;
    func_00282CF0(delta, target, object + 0x10);
    delta[2] = 0.0f;
    distance = func_00282DF0(delta);
    acceleration = speed * 0.0012f;
    if (stopDistance < distance) {
        int collision = *(int *)(data + 0x520);
        angle = 0.0f;
        func_L02_0032E998(object + 0x10, target, &angle, data + 0x320, collision, data + 0x530, data + 0x534, margin, 0.4f);
        func_002AAA00(object + 0xF8, angle, 0.010053098f, 0.005026549f, 0.25132746f, data + 0x27C, 0);
        if (func_00283C80(*(f32 *)(object + 0xF8), angle) < 0.523598849773407f) {
            func_002AA548(&frameSpeed, data + 0x538, distance, acceleration, acceleration, speed * 0.020000001f);
        } else {
            *(f32 *)(data + 0x538) = 0.0f;
        }
    } else {
        func_002AAA00(object + 0xF8, desiredHeading, 0.010053098f, 0.28800002f, 0.25132746f, data + 0x27C, 0);
        func_002AA2E8((f32 *)(data + 0x538), 0.0f, acceleration);
        if (*(f32 *)(data + 0x538) == 0.0f && func_00283C80(*(f32 *)(object + 0xF8), desiredHeading) < 0.0872664749622345f) {
            *(f32 *)(data + 0x27C) = 0.0f;
            done = 1;
        }
    }
    func_00282F20(displacement, object + 0xC0, *(f32 *)(data + 0x538));
    func_00282CC0(destination, displacement, object + 0x10);
    if (!func_002A7EA0(object, object + 0x10, destination, 0.75f, 0.75f, 0.4f, 0.523598849773407f, 0))
        *(int *)(data + 0x53C) += 1;
    if (*(int *)(data + 0x53C) >= 30) {
        *(int *)(data + 0x53C) = 0;
        done = 1;
    }
    return done;
}


typedef unsigned short u16;
extern void func_PAL_002AC3C0(char *object, char *p);
extern void func_00282978(char *p);
extern void func_002AEC48(char *object, char *p, int kind, float f12, float f13);
extern void func_PAL_002B14F8(char *object, char *p, int kind, int a3, float f12);

/* re-arms the object's two guard nodes and restarts its measurement window */
void func_PAL_L11_0042AB20(char *object)
{
    char *p = *(char **)(object + 0x68);

    func_PAL_002AC3C0(object, p + 0x50);
    func_00282978(p + 0x260);
    func_00282978(p + 0x26);
    if (*(u16 *)(object + 0x96) <= 0xFFFE)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_002AEC48(object, p + 0x2A0, 4, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(object, p + 0x2A0, 4, 1, 3.5f);
}

