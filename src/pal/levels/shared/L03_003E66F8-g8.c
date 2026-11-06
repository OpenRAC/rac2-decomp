/* func_PAL_L03_003E66F8, the PAL copy of func_L03_003E21B0: the same C, where the four timers are
   words scaled to 50 Hz, the rates become 0.2f and 0.02f, and the limits 900 and 100. */

#include "common.h"
extern int D_L03_001A8F00, D_001A79F0, D_001A7390;
extern int D_00138324 __attribute__((nosda));
extern u8 D_0018C958[], D_00188660[];
extern u16 D_0018D090[];
extern u8 *D_L03_001AC040 MACRO_ADDR;
extern float D_001B2464;
extern int D_L03_001B2768;
extern int D_L03_001B0B50 __attribute__((sda)), D_L03_001B0B58 __attribute__((sda));
extern int D_L03_001B0B5C __attribute__((sda));
extern int D_L03_001B0B60 __attribute__((sda));
extern float D_L03_001B0B74 __attribute__((sda));
extern void func_002A7750(u8 *, int, int);
extern float func_002AA2E8(float *, float, float);
extern void func_002E59F8(int);
extern void func_PAL_L03_003E6CA8(u8 *), func_L03_003E3018(u8 *),func_L03_003E2EC8(u8 *),func_PAL_L03_003E7C78(u8 *),func_L03_003E3430(u8 *),func_PAL_L03_003E8B88(u8 *),func_L03_003E5218(u8 *);
extern int func_L03_003E3800(u8 *);
extern int func_PAL_00289730(int,int);
extern int func_002E5CF8(int,int,u8 *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002E5F40(int,int);
extern int func_002B3868(u8 *);
extern int func_002B4B70(int,int),func_00282978(short *);
extern void func_0029F338(u8 *);
extern void func_L03_003E3A00(u8 *);
extern void func_L00_002E6CF0(void (*)(u8 *),u8 *);

/* The signed halfword members preserve the record/global alias information
 * needed by the timer increment and clamp. */
typedef struct {
    u8 pad00[0x40];
    u8 choices[0x10];
    short current, next, f54, f56;
    float f58;
    short last, length, maximumLength, cursor, depth, pending, timer, active;
    u8 pad6C[0x10];
    int sound;
} PathRecord;

void func_PAL_L03_003E66F8(u8 *p) {
    u8 *q = *(u8 **)(p + 0x68);
    PathRecord *path = (PathRecord *)q;
    int i, h;
    float f;
    u8 *timeRecord;

    if (D_L03_001A8F00 != 7) {
        if (p[0x20])
            func_002A7750(p, 0, -1);
        return;
    }
    func_002AA2E8(&D_001B2464, 0.0f, 0.20000002f);
    D_L03_001B2768 = 1;
    switch (p[0x20]) {
    case 0:
        for (i = 0; i < 52; i++)
            func_002E59F8(i);
        func_PAL_L03_003E6CA8(p);
        *(u16 *)(p + 0x34) |= 0x100;
        func_L03_003E3018(p);
        func_002A7750(p, D_001A79F0 == 11 ? 1 : 3, -1);
        break;
    case 1:
        timeRecord = D_0018C958;
        if ((u32)(((s32)(D_001A7390) * 5 + 2) / 6 - *(u32 *)(timeRecord + 0x73C)) > 900 ||
            !*(u32 *)(timeRecord + 0x73C))
            func_PAL_00289730(0xA43, 0x9A);
        else if (*(u32 *)(timeRecord + 0x73C) < (u32)(((s32)(D_001A7390) * 5 + 2) / 6))
            *(u32 *)(timeRecord + 0x73C) = ((s32)(D_001A7390) * 5 + 2) / 6;
        func_002A7750(p, 3, -1);
        break;
    case 2:
        if (!path->timer) {
            func_002A7750(p, 4, -1);
            break;
        }
        if (func_L03_003E3800(p)) {
            path->active = 1;
            func_L03_003E2EC8(p);
            func_002E5CF8(4, 0, p);
            func_002A7750(p, 3, -1);
        }
        break;
    case 3:
        func_PAL_L03_003E7C78(p);
        if (!path->f56)
            break;
        if (path->pending != -1) {
            *(u16 *)(q + 0x52) = *(u16 *)(q + 0x66);
            path->pending = -1;
        } else {
            func_L03_003E3430(p);
        }
        /* 255 terminates the available-neighbor list. */
        {
            int choice = path->choices[0];
            choice ^= 255;
            if (choice == 0) {
                func_002E5CF8(0, 0, p);
            } else {
                h = func_002E5CF8(1, 0, p);
                if (h != -1) {
                    f = func_00283CE0(path->length);
                    f /= func_00283CE0(D_L03_001B0B50);
                    func_002E5F40(h, func_00283CF0(f * 1024.0f) + 1024);
                }
            }
        }
        if (path->length > path->maximumLength) {
            path->maximumLength = *(u16 *)(q + 0x5E);
            path->timer += ((s32)(D_L03_001B0B60) * 5 + 2) / 6;
            if (path->timer > ((s32)(D_L03_001B0B58) * 5 + 2) / 6)
                path->timer = ((s32)(D_L03_001B0B58) * 5 + 2) / 6;
        }
        if (path->length == D_L03_001B0B50) {
            func_002E5CF8(5, 0, p);
            func_002A7750(p, 5, -1);
        } else {
            func_002A7750(p, 2, -1);
        }
        break;
    case 4:
        if (path->f56) {
            if (path->last != path->current) {
                *(u16 *)(q + 0x52) = *(u16 *)(q + 0x5C);
                func_L03_003E2EC8(p);
                func_002E5CF8(2, 0, p);
            } else {
                path->timer = ((s32)(D_L03_001B0B5C) * 5 + 2) / 6;
                path->active = 0;
                path->maximumLength = 0;
                func_002A7750(p, 2, -1);
            }
        } else {
            func_PAL_L03_003E7C78(p);
        }
        break;
    case 5:
        if (func_002B3868(p))
            *(u16 *)(p + 0x96) = 100;
        if (!*(u16 *)(p + 0x96)) {
            D_0018D090[0] = 65535;
            func_L03_003E5218(D_L03_001AC040);
            goto exit;
        } else {
            --*(u16 *)(p + 0x96);
        }
        break;
    }
    if (D_00138324 & 16) {
        if (p[0x20] == 5)
            func_L03_003E5218(D_L03_001AC040);
    exit:
        func_002B4B70(0, 0);
        func_0029F338(p);
        return;
    }
    if (p[0x20] != 5 && path->active)
        func_00282978(&path->timer);
    if (path->active && path->timer) {
        u8 *r = D_00188660 + *(int *)(q + 0x7C) * 112;
        if (*(u8 **)(r + 0x88) != p || !r[0x74])
            *(int *)(q + 0x7C) = func_002E5CF8(3, 4, p);
    } else {
        int handle = *(int *)(q + 0x7C);
        if (handle != -1) {
            int offset = handle * 112;
            u8 *r = D_00188660 + offset;
            if (*(u8 **)(r + 0x88) == p && r[0x74])
                func_002E59F8(handle);
        }
        *(int *)(q + 0x7C) = -1;
    }
    func_PAL_L03_003E8B88(p);
    *(float *)(q + 0x58) -= D_L03_001B0B74 * 0.020000001f;
    if (*(float *)(q + 0x58) < -1.0f)
        *(float *)(q + 0x58) += 1.0f;
    func_L00_002E6CF0(func_L03_003E3A00, p);
}
