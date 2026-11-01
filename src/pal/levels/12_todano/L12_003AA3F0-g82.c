#include "include_asm.h"

#include "common.h"
typedef struct { float pad[32]; float x, y, z; } Target;
extern Target D_00189E20;
extern u8 D_00189EA0[];
extern u8 D_00188660[];
extern float D_L12_001AFC70 __attribute__((sda));
extern float D_L12_001AFC74 __attribute__((sda));
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_L00_00326620(void *, int, int);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern int func_002A9640(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern float func_002AAA00(void *, float, void *, int, float, float, float);
extern void func_002AEC48(void *, void *, int, float, float);

void func_PAL_L12_003C21C8(u8 *o) {
    u8 *d = *(u8 **)(o + 0x68);
    float yaw = 0, pitch = 0;
    float acceleration, damping;
    float half_pitch, half_yaw;

    *(u16 *)(o + 0x34) |= 4;
    switch (o[0x20]) {
    case 0:
        func_002A7750(o, 1, -1);
        break;
    case 1:
        yaw = 0;
        if (func_00282E80(o + 0x10, D_00189EA0) < 16.0f) {
            o[0x20] = 2;
            if (o[0x43] != 1)
                func_PAL_002A7E68(o, 1, 0, 25);
        }
        if (func_002A9640(o, 0x4010000, 0) && !*(int *)(d + 0x110))
            func_002A7750(o, 3, -1);
        o[0xA8] = 255;
        break;
    case 2: {
        float *target;

        yaw = func_00283B98(func_00283BE0(func_00283248(D_00189E20.x - *(float *)(o + 0x10), D_00189E20.y - *(float *)(o + 0x14)), *(float *)(o + 0xF8)), 1.5707964897155762f);
        target = &D_00189E20.x;
        pitch = func_00283248(func_00282E80(target, o + 0x10), *(float *)(o + 0x18) - D_00189E20.z);
        if (func_00282E80(o + 0x10, target) > 20.0f) {
            o[0x20] = 1;
            if (o[0x43] != 0)
                func_PAL_002A7E68(o, 0, 0, 25);
        }
        if (func_002A9640(o, 0x4010000, 0) && !*(int *)(d + 0x110))
            func_002A7750(o, 3, -1);
        o[0xA8] = 255;
        break;
    }
    case 3:
        func_L00_00326620(o, 0x1132, o[0x30]);
        func_002E5CF8(0, 0, o);
        {
            int id = *(int *)(d + 0x114);
            u8 *effect;

            if (id != -1) {
                effect = D_00188660 + id * 0x70;
                if (*(u8 **)(effect + 0x88) == o && effect[0x74])
                    func_002E59F8(id);
            }
        }
        *(int *)(d + 0x114) = -1;
        func_0029F338(o);
        return;
    }
    if (func_00282C48(func_00283BE0(yaw, *(float *)(d + 0x100))) > D_L12_001AFC74 * 0.017453294f) {
        u8 *effect = D_00188660 + *(int *)(d + 0x114) * 0x70;

        if (*(u8 **)(effect + 0x88) != o || !effect[0x74])
            *(int *)(d + 0x114) = func_002E5CF8(1, 4, o);
    } else {
        int id = *(int *)(d + 0x114);
        u8 *effect;

        if (id != -1) {
            effect = D_00188660 + id * 0x70;
            if (*(u8 **)(effect + 0x88) == o && effect[0x74])
                func_002E59F8(id);
        }
        *(int *)(d + 0x114) = -1;
    }
    acceleration = 0.0432f;
    func_002AAA00(d + 0x100, yaw, d + 0x108, 0, 0.0025132746f, 0.0025132746f, 0.12566373f);
    damping = 0.43200004f;
    func_002AAA00(d + 0x104, pitch, d + 0x10C, 0, 0.0025132746f, 0.0025132746f, 0.12566373f);
    half_pitch = *(float *)(d + 0x104) * 0.5f;
    half_yaw = *(float *)(d + 0x100) * 0.5f;
    *(float *)(d + 0x68) = half_yaw;
    *(float *)(d + 0x60) = half_pitch;
    *(float *)(d + 0xE0) = half_pitch;
    *(float *)(d + 0xE8) = half_yaw;
    func_002AEC48(o, d, 0, acceleration, damping);
    func_002AEC48(o, d + 0x80, 1, acceleration, damping);
    func_002A0F48(o);
    *(float *)(o + 0xC) = D_L12_001AFC70;
}
