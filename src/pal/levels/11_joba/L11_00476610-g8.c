#include "common.h"

extern int D_L11_001CAE40[];
extern unsigned int D_00138324 __attribute__((nosda));
extern u8 D_00189EA0[];
extern int *D_L11_001FF580[];
extern float D_L11_001B2978 __attribute__((sda));
extern float D_L11_001B297C __attribute__((sda));
extern int D_L11_001AED08;
extern void func_002B60B0(void *, float, float, float, float);
extern void func_L02_0031E9E8(float *, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_002A7750(u8 *, int, int);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(u8 *, int, int, int);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_002A7820(int, int);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_L07_00321D68(char *, void *);
extern void func_002A7CA0(void *, float *, float, float, float, float);
extern void func_0029F338(void *);
extern float func_00283248(float, float);
extern void func_002AEE70(float *, float *, float *, float, float, float);
extern void func_PAL_L01_00323068(char *, char *);
extern void func_002A7A00(float *, float, float);
extern u8 *func_PAL_L11_00399B70(u8 *, float *, float *);
extern void *func_002A9640(void *, unsigned int, int);
extern void func_PAL_002B14F8(void *, float *, float, int, int);
#define VF(offset) (*(float *)(vars + (offset)))
#define VI(offset) (*(int *)(vars + (offset)))

/* func_PAL_L11_00476610, the PAL copy of func_L11_004702F0: the same C, with speeds and rates
 * rescaled for 50 Hz and frame counts written ((s32)(x) * 5 + 2) / 6.
 * Level-11 creature update, a state machine on object[0x20]: wanders between random points
 * near its spawn, follows a path from D_L11_001FF580, or turns away from the hero; when hit it
 * bursts into 14 pieces (func_PAL_L11_00399B70), counts towards D_L11_001AED08 and deletes itself. */
void func_PAL_L11_00476610(u8 *object) {
    float motion[4], previous[4];
    u8 *vars;
    int *path;
    float *point;
    float angle, distance;
    int first, second;
    u16 timer;
    if (D_L11_001CAE40[0]) return;
    vars = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        *(u8 **)(vars + 0x18) = vars + 0x20;
        *(float *)(object + 0x2C) *= 1.5f;
        qcopy(vars + 0x110, object + 0x10);
        VF(0x24) = VF(0x20) = 0.4f;
        VF(0x54) = 0.25f;
        VF(0x2C) = VF(0x28) = 0.6f;
        VF(0x50) = VF(0x30) = 1.48353004f;
        VF(0x4C) = 0.002f;
        func_002B60B0(object, 0.00080000004f, 0.020000001f, 0.0016755164f, 0.12566373f);
        func_L02_0031E9E8((float *)(vars + 0x120), 4.0f);
        func_00282CC0((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
        func_002A7750(object, VI(0x130), -1);
        object[0x30] = 255;
        first = func_002A77E0(8);
        second = func_002A77E0(18);
        func_PAL_002A7E68(object, 0, first, ((s32)second * 5 + 2) / 6);
        VI(0x144) = 0;
        if (VI(0x140) != -1 && VI(0x130) != 8) {
            *(float *)(object + 0x2C) *= 1.5f;
            if (object[0x43] != 4) {
                first = func_002A77E0(3);
                second = func_002A77E0(8);
                func_PAL_002A7E68(object, 4, first, ((s32)(second + 10) * 5 + 2) / 6);
            }
            func_002A7750(object, 7, -1);
        }
        break;
    case 2:
        if (func_00282E48(object + 0x10, D_00189EA0) < 9.0f) {
            if (object[0x43] != 3) func_PAL_002A7E68(object, 3, 0, 8);
            func_002A7750(object, 4, -1);
            break;
        }
        if (*(int *)(D_00189EA0 + 0x11C8) != 10 && *(int *)(D_00189EA0 + 0x11C8) != 13 && (D_00138324 & 0x20)) {
            if (!(func_00282E80(object + 0x10, D_00189EA0) < 64.0f) || VI(0x150)) break;
            VF(0x134) = (float)func_002A7820(170, 190);
            if (object[0x43] != 4) func_PAL_002A7E68(object, 4, 0, 8);
            VF(0x138) = 0.10000001f;
            func_002A7750(object, 6, -1);
        }
        break;
    case 4:
        if (object[0x60] & 2) {
            VF(0x134) = (float)func_002A7820(170, 190);
            if (object[0x43] != 4) func_PAL_002A7E68(object, 4, 0, 8);
            VF(0x138) = 0.040000003f;
            func_002A7750(object, 5, -1);
        }
        break;
    case 5:
        VF(0x138) += 0.012f;
        if (VF(0x138) > 0.14000001f) VF(0x138) = 0.14000001f;
        qcopy(previous, object + 0x10);
        angle = func_00283B98(*(float *)(object + 0xF8), VF(0x134) * 0.017453294f);
        func_002AF000(motion, VF(0x138), angle, 2.96706009f);
        func_L07_00321D68((char *)object, motion);
        if (func_00282E80(object + 0x10, previous) < VF(0x138)) {
            angle = func_00283B98(*(float *)(object + 0xF8), 3.141593f);
            func_002A7CA0(object, (float *)(vars + 0x13C), angle, 0.000199999995f, 0.00200000009f, 0.04f);
        }
        if (func_00282E80(object + 0x10, D_00189EA0) > 64.0f) {
            func_0029F338(object);
            return;
        }
        func_002AEE70((float *)object, (float *)(vars + 0x148), (float *)(vars + 0x14C), D_L11_001B2978, D_L11_001B297C * 0.0003490659f, -1.0f);
        break;
    case 6:
        VF(0x138) += 0.012f;
        if (VF(0x138) > 0.50000006f) VF(0x138) = 0.50000006f;
        angle = func_00283B98(*(float *)(object + 0xF8), VF(0x134) * 0.017453294f);
        func_002AF000(motion, VF(0x138), angle, 2.96706009f);
        func_00282CC0((float *)(object + 0x10), (float *)(object + 0x10), motion);
        if (func_00282E80(object + 0x10, D_00189EA0) > 64.0f) {
            func_0029F338(object);
            return;
        }
        break;
    case 7:
        path = D_L11_001FF580[VI(0x140)];
        distance = func_00282E80(object + 0x10, path + 4 + VI(0x144) * 4);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = func_00283248(distance, point[6] - *(float *)(object + 0x18));
        func_002AF000(motion, 0.14000001f, *(float *)(object + 0xF8), angle);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = func_00283248(point[4] - *(float *)(object + 0x10), point[5] - *(float *)(object + 0x14));
        func_002A7CA0(object, (float *)(vars + 0x13C), angle, 9.99999975e-05f, 0.00100000005f, 0.02f);
        func_00282CC0((float *)(object + 0x10), (float *)(object + 0x10), motion);
        if (object[0x43] != 4) func_PAL_002A7E68(object, 4, 0, 8);
        if (func_00282E80(object + 0x10, path + 4 + VI(0x144) * 4) < 0.6f) {
            ++VI(0x144);
            if (VI(0x144) >= *path - 1) VI(0x144) = *path - 1;
        }
        func_002AEE70((float *)object, (float *)(vars + 0x148), (float *)(vars + 0x14C), D_L11_001B2978, D_L11_001B297C * 0.0003490659f, -1.0f);
        break;
    case 8:
        if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 8);
        if (func_00282E80(object + 0x10, vars + 0x120) < 0.5f ||
            VI(0xA0) || *(u16 *)(object + 0x96) >= 240) {
            *(u16 *)(object + 0x96) = 0;
            VI(0xA0) = 0;
            func_L02_0031E9E8((float *)(vars + 0x120), 4.0f);
            func_00282CC0((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
            if (func_002A77E0(4) == 1) {
                if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 8);
                func_002A7750(object, 9, -1);
            }
        } else {
            func_PAL_L01_00323068((char *)object, (char *)vars + 0x120);
        }
        if (func_00282E48(object + 0x10, D_00189EA0) < 10.0f) {
            if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 8);
            func_002A7750(object, 4, -1);
        }
        break;
    case 9:
        if (object[0x60] & 2) {
            func_002A7750(object, 8, -1);
            if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 8);
        }
        if (func_00282E48(object + 0x10, D_00189EA0) < 10.0f) {
            if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 8);
            func_002A7750(object, 4, -1);
        }
        break;
    }
    timer = *(u16 *)(object + 0x96);
    if (timer < 65535) *(short *)(object + 0x96) = timer + 1;
    if (object[0x42] == 4) *(float *)(object + 0x48) = 2.5f;
    else if (object[0x42]) *(float *)(object + 0x48) = 1.0f;
    if (func_002A9640(object, 0x10000, 0)) {
        int i;
        for (i = 0; i < 14; i++) {
            u8 *particle;
            func_002A7A00(motion, 0.080000006f, 0.120000005f);
            particle = func_PAL_L11_00399B70(object, (float *)(object + 0x10), motion);
            particle[0x30] = *(u16 *)(particle + 0x32) = 255;
        }
        ++D_L11_001AED08;
        func_0029F338(object);
    } else {
        func_PAL_002B14F8(object, (float *)(vars + 0x160), 2.5f, 0, 1);
    }
}
