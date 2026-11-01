#include "include_asm.h"

#include "common.h"
extern int D_L20_001A8F00;
extern struct {
    u8 reserved[0x2D8];
    float height;
} D_00189E20;
extern struct {
    u8 reserved[0x158];
    float yaw;
} D_L20_001B9E80;
extern u32 D_L20_001B2AC8;
extern float D_L20_001B2420 __attribute__((sda));
extern float D_L20_001B2430[4] SDATA(D_L20_001B2430);
extern void func_0029F338(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282F70(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_PAL_L20_004502D0(char *);
extern int func_002B3868(u8 *);
extern int func_002E5CF8(int, int, char *);
extern float func_PAL_L20_00450568(char *);
extern void func_002A7750(u8 *, int, int);
extern void func_PAL_002A7E68(u8 *, int, int, int);
extern u8 *func_L20_004448A8(u8 *, u8 *);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A89A8(void *, int, float);
extern char *func_PAL_L20_0039F488(u8 *, void *, void *, float);
extern void func_PAL_L20_004504B0(char *);

/* Alternates between target selection and directed projectile bursts. */
void func_PAL_L20_0044FE40(u8 *moby)
{
    float target[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *selected;
    float *aim;
    float angle, radius, savedHeight, x;
    func_PAL_L20_004502D0((char *)moby);
    if (D_L20_001A8F00 == 2) { func_0029F338(moby); return; }
    switch (moby[0x20]) {
    case 2:
        if (func_002B3868(moby)) *(int *)(state + 0x1b8) = func_002E5CF8(0, 4, (char *)moby);
        *(int *)(*(u8 **)(moby + 0xb8) + 0x98) = 0;
        if (func_PAL_L20_00450568((char *)moby) < 0.1f) func_002A7750(moby, 3, -1);
        *(int *)(*(u8 **)(moby + 0xb8) + 0x98) = *(int *)(*(u8 **)(*(u8 **)(moby + 0xb8) + 0x24) + 0x10);
        break;
    case 3:
        if (*(unsigned short *)(moby + 0x96) > 50) func_002A7750(moby, 4, -1);
        break;
    case 4:
        if (func_002B3868(moby)) {
            if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 12);
            selected = func_L20_004448A8(*(u8 **)(moby + 0xb8), moby);
            *(u8 **)(state + 0x1b0) = selected;
            if (func_002A77E0(2)) *(u8 **)(state + 0x1b0) = 0;
            selected = *(u8 **)(state + 0x1b0);
            aim = (float *)(state + 0x140);
            if (selected) {
                *(u8 **)(state + 0x150) = selected;
                qcopy(aim, selected + 0x10);
            }
            angle = func_00283B98(D_L20_001B9E80.yaw, func_002A78D8(20.0f, 70.0f) * 0.017453294f);
            radius = func_002A7878(5.0f, 15.0f);
            savedHeight = *(float *)(state + 0x198);
            *(float *)(state + 0x190) = func_00283180(angle) * radius;
            *(float *)(state + 0x194) = func_00283198(angle) * radius;
            *(float *)(state + 0x198) = 0.0f;
            func_00282CC0(state + 0x190, state + 0x190, aim);
            if (D_00189E20.height != 0.0f) {
                D_00189E20.height += func_002A7878(1.5f, 2.5f);
                *(float *)(state + 0x198) = D_00189E20.height;
            } else *(float *)(state + 0x198) = savedHeight;
        }
        if (func_PAL_L20_00450568((char *)moby) < 0.1f) func_002A7750(moby, 5, -1);
        break;
    case 5:
        if (func_002B3868(moby)) {
            if (moby[0x43] != 1) func_PAL_002A7E68(moby, 1, 0, 12);
            if (*(int *)(state + 0x1b0)) *(float *)(state + 0x1b4) = 0.0f;
            else *(float *)(state + 0x1b4) = -func_002A7878(4.0f, 6.0f);
            func_002E5CF8(1, 0, (char *)moby);
        }
        if ((D_L20_001B2AC8 & 15) == (((int)moby >> 8) & 15)) {
            func_00282CF0(target, state + 0x140, moby + 0x10);
            target[2] = 0.0f;
            x = func_00282E20(target) + *(float *)(state + 0x1b4);
            if (x < 1.0f) x = 1.0f;
            func_00282F70(target, target, x);
            func_00282CC0(target, target, moby + 0x10);
            target[2] = func_002A89A8(target, 0, 0.5f);
            if (target[2] == 0.0f) target[2] = *(float *)(state + 0x148);
            func_00283098(origin, D_L20_001B2430, moby + 0xc0);
            func_00282CC0(origin, origin, moby + 0x10);
            func_00282CF0(velocity, target, origin);
            func_00282F20(velocity, velocity, D_L20_001B2420 * 0.020000001f);
            func_PAL_L20_0039F488(moby, origin, velocity, (float)state[0x34]);
            func_002AA2E8((float *)(state + 0x1b4), 4.0f, 1.0f);
        }
        if (*(float *)(state + 0x1b4) >= 4.0f) func_002A7750(moby, 4, -1);
        break;
    }
    func_PAL_L20_004504B0((char *)moby);
}
