#include "common.h"

/* func_L00_002B0968: places the hero's item mobys (seven slots, up to three attachments each) on their
 * joints and drives the glow effect of slot 3's second attachment. RAC1 counterpart: update_hero_item_mobys
 * (func_L00_0020FC18, src/overlays/shared/hero_animation_slots.c); RAC2 adds the default argument, the third
 * attachment, the cinematic scaling and the quaternion/position blending. Its own unit for -G8.
 *
 * Source forms that matter here (all measured):
 * - joint_mtx is set in the outer loop and added as RAC1 does, (joint * 0x40) + (s32)joint_mtx. That keeps
 *   the joint matrix base out of the inner loop's invariant set, so loop.c still hoists the matrix pointer
 *   (sp+0x30) into the inner preheader, as retail stores it there.
 * - The slot pointer is computed inside the inner loop: loop.c hoists its 80 together with the body's, so the
 *   constant is reloaded after the mtlo and i/j land in s7/fp.
 * - The nested cinematic test lets loop.c hoist the constant 2, which reload rematerialises for both tests.
 * - random_range is a function-wide constant (RAC1: scale_ticks(0x78)); reload rematerialises it into v1.
 */

typedef struct {
    u8 prefix[0x12E8];
    int item2;
    u8 rest[0x2290 - 0x12EC];
    u8 *moby;
} AttachmentRoot;

extern AttachmentRoot D_00189E20 NOT_SDA;
extern int D_0018C0B0 NOT_SDA;
extern int D_L00_001A8F00[] __attribute__((sda));
extern u8 D_00139568[];
extern u8 D_L00_00262570[];
extern int D_L00_001A7CEC __attribute__((sda));
extern float D_L00_001A7CE4 __attribute__((sda));
extern float D_L00_001A7CE0 __attribute__((sda));
extern int D_L00_001B19C8[] __attribute__((sda));
extern u8 D_L00_0025BDC0[], D_L00_001B2E00[];
extern u8 D_L00_001A7D08[], D_L00_001B3000[];
extern u8 D_L00_001A7D18[], D_L00_001B3200[];
extern u8 D_L00_001A7D30[], D_L00_001B3300[];
extern u8 D_L00_001B2D80[], D_L00_0025C0F0[];
extern void func_002AB6D8(void *, void *);
extern void func_002A05A8(void *), func_002A0F48(void *), func_002A10E8(void *);
extern void func_L00_002B0528(void *, void *, int);
extern int func_L00_002ADED8(int), func_L00_002ADF10(int), func_L00_002ADF38(int);
extern void func_00283678(void *, void *), func_002AB028(void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282E20(void *), func_00283248(float, float);
extern void func_L00_002AA200(void *, void *, int, int, int);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282D08(void *, void *, void *, float);
extern void func_002A91F0(void *, void *), func_00283810(void *, void *, void *, float), func_00283958(void *, void *);
extern u8 *func_0029EFD0(int);
extern void func_0029FC20(void *, int, void *), func_L00_002A7A10(void);
extern float func_00283CE0(int), func_00283198(float);
extern int func_00283CF0(float);

typedef int ItemQuad __attribute__((mode(TI)));
extern struct {
    u8 pad[0x2E0];
    float scale0[3];
    u8 gap[0x390 - 0x2EC];
    float scale1[3];
} D_L00_0025BE10;

void func_L00_002B0968(int value)
{
    union {
        float direction[4];
        ItemQuad saved[2];
    } scratch __attribute__((aligned(16)));
    float quaternion[4] __attribute__((aligned(16)));
    float matrix[4][4] __attribute__((aligned(16)));
    int i, j, joint, first, second, third;
    u8 *moby;
    u8 *joint_mtx;
    int random_range = 120;

    if (!value)
        value = D_0018C0B0;
    for (i = 0; i < 7; i++) {
        if (D_L00_001A8F00[0] == 2 || D_L00_001A8F00[0] == 6) {
            if (!(i == 2 && D_00189E20.item2 == 47) && i != 1 && i != 4)
                continue;
        }
        joint_mtx = (u8 *)&D_00189E20 + 0xC50;
        for (j = 0; j < 3; j++) {
            u8 *slot_mobys;
            if (j > 0 && i != 1 && i != 3 && i != 4)
                break;
            slot_mobys = (u8 *)&D_00189E20 + i * 80;
            moby = *(u8 **)(slot_mobys + 0x1220);
            if (j == 1)
                moby = *(u8 **)(slot_mobys + 0x1224);
            else if (j == 2)
                moby = *(u8 **)(slot_mobys + 0x1228);
            if (moby) {
                u8 *slot = (u8 *)&D_00189E20 + i * 80;
                *(u64 *)(moby + 0x38) = *(u64 *)(D_00189E20.moby + 0x38);
                {
                    u8 *def = D_L00_00262570 + D_00139568[*(int *)(slot + 0x1248)] * 224;
                    joint = *(int *)(def + 0x10);
                    if (i == 1 && j == 1)
                        joint = 3;
                    if (slot[0x123A]) {
                        qcopy((u8 *)&D_00189E20 + 0x1200 + i * 80, (u8 *)&D_00189E20 + 0xC80 + joint * 64);
                        func_002AB6D8((u8 *)(joint * 64 + (int)joint_mtx), (u8 *)&D_00189E20 + 0x1210 + i * 80);
                        func_002A05A8(moby);
                        func_002A0F48(moby);
                        *(u16 *)(moby + 0x34) &= 0xFFFB;
                    } else {
                        qcopy(moby + 0x10, (u8 *)&D_00189E20 + 0xC80 + joint * 64);
                        if (!D_L00_001A7CEC || !*(int *)(def + 0x1C)) {
                            if (i == 0)
                                func_L00_002B0528(moby, (u8 *)(joint * 64 + (int)joint_mtx), 0);
                            first = func_L00_002ADED8(i);
                            second = func_L00_002ADF10(i);
                            third = func_L00_002ADF38(i);
                            if (!first && !second && !third)
                                func_002A05A8(moby);
                            func_002A0F48(moby);
                            func_00283678(moby + 0xC0, (u8 *)(joint * 64 + (int)joint_mtx));
                            if (!first && !second && !third)
                                func_002AB028(moby + 0xC0);
                            scratch.direction[0] = 1.0f;
                            scratch.direction[1] = 0;
                            scratch.direction[2] = 0;
                            func_00283098(scratch.direction, scratch.direction, moby + 0xC0);
                            *(float *)(moby + 0xF4) =
                                -func_00283248(func_00282E20(scratch.direction), scratch.direction[2]);
                            *(float *)(moby + 0xF8) = func_00283248(scratch.direction[0], scratch.direction[1]);
                            func_002A10E8(moby);
                            *(u16 *)(moby + 0x34) |= 6;
                            if (first) {
                                func_L00_002AA200(D_L00_0025BDC0, D_L00_001B2E00, *(int *)(moby + 0x24), 0, value);
                                *(int *)(moby + 0x44) = 0;
                                *(int *)(moby + 0x40) = 0;
                                *(u8 **)(moby + 0x58) = D_L00_001B2E00;
                                *(u8 **)(moby + 0x5C) = D_L00_001B2E00;
                            } else if (second) {
                                func_L00_002AA200(D_L00_001A7D08, D_L00_001B3000, *(int *)(moby + 0x24), 0, value);
                                *(int *)(moby + 0x44) = 0;
                                *(int *)(moby + 0x40) = 0;
                                *(u8 **)(moby + 0x58) = D_L00_001B3000;
                                *(u8 **)(moby + 0x5C) = D_L00_001B3000;
                            } else if (third) {
                                int k;
                                if (D_L00_001A8F00[0] == 2 || D_L00_001A8F00[0] == 6) {
                                    u8 *p = D_L00_001B2D80;
                                    for (k = 1; k >= 0; k--, p += 64) {
                                        *(float *)(p + 32) = 1;
                                        *(float *)(p + 36) = 1;
                                        *(float *)(p + 40) = 1;
                                    }
                                } else {
                                    u8 *saved_pose = D_L00_0025C0F0;
                                    scratch.saved[0] = *(ItemQuad *)saved_pose;
                                    scratch.saved[1] = *(ItemQuad *)(saved_pose + 0xB0);
                                    D_L00_0025BE10.scale0[0] = 1;
                                    D_L00_0025BE10.scale0[1] = 1;
                                    D_L00_0025BE10.scale0[2] = 1;
                                    D_L00_0025BE10.scale1[0] = 1;
                                    D_L00_0025BE10.scale1[1] = 1;
                                    D_L00_0025BE10.scale1[2] = 1;
                                }
                                if (!j) {
                                    func_L00_002AA200(D_L00_001A7D18, D_L00_001B3200, *(int *)(moby + 0x24), 0, value);
                                    *(u8 **)(moby + 0x58) = D_L00_001B3200;
                                    *(u8 **)(moby + 0x5C) = D_L00_001B3200;
                                } else {
                                    func_L00_002AA200(D_L00_001A7D30, D_L00_001B3300, *(int *)(moby + 0x24), 0, value);
                                    *(u8 **)(moby + 0x58) = D_L00_001B3300;
                                    *(u8 **)(moby + 0x5C) = D_L00_001B3300;
                                }
                                *(int *)(moby + 0x40) = 0;
                                *(int *)(moby + 0x44) = 0;
                                if (D_L00_001A8F00[0] == 2 || D_L00_001A8F00[0] == 6) {
                                    u8 *p = D_L00_001B2D80;
                                    for (k = 1; k >= 0; k--, p += 64) {
                                        *(float *)(p + 32) = 0.01f;
                                        *(float *)(p + 36) = 0.01f;
                                        *(float *)(p + 40) = 0.01f;
                                    }
                                } else {
                                    *(ItemQuad *)D_L00_0025C0F0 = scratch.saved[0];
                                    *(ItemQuad *)(D_L00_0025C0F0 + 0xB0) = scratch.saved[1];
                                }
                            }
                        } else {
                            u8 *p;
                            func_002A05A8(moby);
                            if (!D_L00_001A7CEC || i != 0)
                                func_002AB6D8((u8 *)(joint * 64 + (int)joint_mtx), moby + 0xF0);
                            else
                                func_L00_002B0528(moby, (u8 *)(joint * 64 + (int)joint_mtx), 1);
                            p = (u8 *)&D_00189E20;
                            if (*(float *)(p + 0x14F8) > 0 && !*(int *)(p + 0x1500)) {
                                float step = D_L00_001A7CE4 * 0.00027777778f;
                                func_002AA548((float *)(p + 0x14F8), (float *)(p + 0x14FC), 0.0f, step, step,
                                              D_L00_001A7CE0 * 0.016666668f);
                                func_00283098(scratch.direction, p + 0x14A0, p);
                                func_00282CC0(scratch.direction, scratch.direction, p + 0x80);
                                func_00282D08(moby + 0x10, moby + 0x10, scratch.direction, *(float *)(p + 0x14F8));
                                func_002A91F0(&scratch.saved[1], moby + 0xF0);
                                func_00283810(quaternion, &scratch.saved[1], p + 0x14C0, *(float *)(p + 0x14F8));
                                func_00283958(quaternion, moby + 0xC0);
                                func_002AB6D8(moby + 0xC0, moby + 0xF0);
                            }
                            func_002A0F48(moby);
                            func_002A10E8(moby);
                            *(u16 *)(moby + 0x34) |= 6;
                        }
                    }
                }
            }
            if (i == 3 && j == 1 && moby) {
                u8 *p = (u8 *)&D_00189E20;
                u8 *effect;
                u8 *created;
                if (!*(u8 **)(p + 0x131C)) {
                    *(u8 **)(p + 0x131C) = func_0029EFD0(0x4B4);
                    if (*(u8 **)(p + 0x131C)) {
                        *(int *)(*(u8 **)(p + 0x131C) + 0x78) = 0x801432D7;
                        created = *(u8 **)(p + 0x131C);
                        qcopy(created + 0x10, p + 0x80);
                        qcopy(created + 0xF0, p + 0x90);
                        *(u16 *)(created + 0x32) = 0x40;
                        (*(u8 **)(p + 0x131C))[0x31] = 1;
                        (*(u8 **)(p + 0x131C))[0x30] = 0;
                        *(u16 *)(*(u8 **)(p + 0x131C) + 0x34) = 0;
                        *(float *)(*(u8 **)(p + 0x131C) + 0x2C) *= 1.3f;
                        func_002A0F48(*(u8 **)(p + 0x131C));
                    }
                }
                if (*(u8 **)(p + 0x131C)) {
                    effect = *(u8 **)(p + 0x131C);
                    if (((*(u16 *)(effect + 0x34) ^ 1) & 1) != 0) {
                        float angle;
                        int red, green, blue, color_red;
                        func_0029FC20(moby, 8, matrix);
                        /* The glow position and its draw request, as one step. */
                        {
                            qcopy(p + 0x2010, matrix[3]);
                            func_L00_002A7A10();
                        }
                        qcopy(effect + 0x10, matrix[3]);
                        func_00283678(effect + 0xC0, matrix);
                        func_002A0F48(effect);
                        *(u64 *)(effect + 0x38) = *(u64 *)(*(u8 **)(p + 0x2290) + 0x38);
                        angle = func_00283198(((float)(D_L00_001B19C8[0] % random_range) / func_00283CE0(random_range)
                                               * 2.0f) * 3.1415927f + (-3.1415927f));
                        color_red = func_00283CF0(angle * 90.0f);
                        green = func_00283CF0(angle * 50.0f);
                        blue = func_00283CF0(angle * 10.0f);
                        blue = ((blue + 20) << 16) | 0x80000000;
                        red = color_red + 215;
                        if (red > 255)
                            red = 255;
                        *(u16 *)(effect + 0x34) |= 16;
                        *(int *)(effect + 0x78) = blue | ((green + 50) << 8) | red;
                    }
                }
            }
        }
    }
}
