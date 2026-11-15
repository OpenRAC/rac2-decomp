#include "common.h"

/* Built with -g (config/cflags.txt): the line boundary before the ratio
   division supplies retail's two padding nops in front of its div.s. */

extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(u8 *);
extern void func_0029FCC0(int, int, void *);
extern void func_0029F338(void *);
extern void func_002A7A00(void *, float, float);
extern int func_002A77E0(int);
extern int func_L02_0032E508(u8 *, int, u8 *, int);
extern void func_002A7750(u8 *, int, int);

/* Sixteen floats copied as a block with unaligned doubleword moves. */
typedef struct { float value[16]; } __attribute__((packed)) InitValues;
extern InitValues D_L18_001B1570;

#define W(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(short *)((p) + (o)))
#define U(p, o) (*(unsigned short *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define CHILD(o) (*(u8 **)(s + (o)))

/* Sets up an Extermibot when it is created: it fills in the robot's health and speeds, then spawns its torso and arm parts and attaches them. If a part cannot be created, the robot is removed. */
void func_L18_004302B0(u8 *moby) {
    float pos[4] __attribute__((aligned(16)));
    InitValues values;
    u8 *s = *(u8 **)(moby + 0x68);
    int i;

    s[0x48] = FloatToInt(15);
    s[0x4A] = FloatToInt(16);
    s[0x60] = 13;
    W(s, 0x98) = 2;
    F(s, 0x84) = F(s, 0x80) = 1.5f;
    F(s, 0xA8) = 0.1f;
    F(s, 0xAC) = 0.33f;
    W(s, 0xCC) = W(s, 0x798);
    F(s, 0x8C) = 0.4f;
    if (!H(s, 0x24)) {
        F(s, 0x20) = 16;
        H(s, 0x24) = 16;
    }
    s[0x28] = 3;
    F(s, 0x30) = 1;
    s[0x2E] = 1;
    F(s, 0x104) = 0.4f;
    F(s, 0x100) = 1.25f;
    F(s, 0x12C) = 0.0027777778f;
    F(s, 0x10C) = F(s, 0x108) = 0.375f;
    F(s, 0x110) = 1.5707965f;
    if (W(s, 0x798) != -1) W(s, 0x13C) = W(s, 0x798);

    CHILD(0x7C0) = CreateMoby(0xF0B /* Extermibot Torso */);
    if (CHILD(0x7C0) == 0) goto fail;
    CHILD(0x7C0)[0x30] = moby[0x30];
    U(CHILD(0x7C0), 0x32) = U(moby, 0x32);
    *(u64 *)(CHILD(0x7C0) + 0x38) = *(u64 *)(moby + 0x38);
    func_002A0F48(CHILD(0x7C0));
    W(CHILD(0x7C0), 0x98) = 0;
    TransformMobyJointToWorld((int)moby, 0, pos);
    qcopy_nc(CHILD(0x7C0) + 0x10, pos);
    qcopy_nc(CHILD(0x7C0) + 0xF0, moby + 0xF0);
    values = D_L18_001B1570;
    {
        float *v;
        i = 0;
        v = values.value;
        for (; i < 15; i++) {
            float divisor = IntToFloat(H(s, 0x24));
            float n = *v++;
            float ratio = n / divisor;
            *((u8 *)*(int *)(CHILD(0x7C0) + 0x68) + i + 0x20) = FloatToInt(ratio * 255.0f);
        }
    }

    if (H(s, 0x7FC)) CHILD(0x7C8) = CreateMoby(0xF0D /* moby class 3853 */);
    else CHILD(0x7C8) = CreateMoby(0xF0E /* moby class 3854 */);
    if (CHILD(0x7C8) == 0) goto fail;
    CHILD(0x7C8)[0x30] = moby[0x30];
    U(CHILD(0x7C8), 0x32) = U(moby, 0x32);
    *(u64 *)(CHILD(0x7C8) + 0x38) = *(u64 *)(moby + 0x38);
    func_002A0F48(CHILD(0x7C8));
    W(CHILD(0x7C8), 0x98) = 0;

    if (!H(s, 0x7FC)) {
        int j;
        u8 *p6, *p5, *p4, *p3, *p2, *p1;

        p6 = s + 0x6A0;
        p5 = s + 0x690;
        p4 = s + 0x680;
        p3 = s + 0x670;
        p2 = s + 0x660;
        p1 = s + 0x650;
        for (j = 1; j >= 0; j--) {
            RandomDirectionVector(p1, -3.1415927f, 3.1415927f); p1 += 0xA0;
            RandomDirectionVector(p2, -3.1415927f, 3.1415927f); p2 += 0xA0;
            RandomDirectionVector(p3, 0.2327106f, 0.290888249874115f); p3 += 0xA0;
            RandomDirectionVector(p4, 0.2327106f, 0.290888249874115f); p4 += 0xA0;
            RandomDirectionVector(p5, 1, 1.7f); p5 += 0xA0;
            RandomDirectionVector(p6, 1, 1.7f); p6 += 0xA0;
        }
    }
    goto spawned;

fail:
    /* One release path for both failed spawns. */
    MarkMobySpawned(moby);
    return;

spawned:
    if (!RandomIntBelow(2)) {
        U(moby, 0x34) |= 0x8000;
        U(CHILD(0x7C0), 0x34) |= 0x8000;
    }
    if (W(s, 0x7D4) != -1)
        W(s, 0x780) = BuildRouteNodes(moby, W(s, 0x7D4), s + 0x210, 0x20);
    if (H(s, 0x7FC)) H(s, 0x804) = RandomIntBelow(150);
    U(s, 0x7F6) = U(s, 0x7F4);
    if (H(s, 0x7F8)) {
        SetMobyState(moby, 1, 0);
        W(moby, 0x98) = 0;
        U(moby, 0x34) = (U(moby, 0x34) & 0xEFFF) | 0x43;
        if (CHILD(0x7C0)) {
            U(CHILD(0x7C0), 0x34) |= 0x41;
            U(CHILD(0x7C0), 0x34) &= 0xEFFF;
            W(CHILD(0x7C0), 0x98) = 0;
            U(CHILD(0x7C0), 0x34) |= 2;
        }
        if (CHILD(0x7C4)) {
            U(CHILD(0x7C4), 0x34) |= 0x41;
            U(CHILD(0x7C4), 0x34) &= 0xEFFF;
            W(CHILD(0x7C4), 0x98) = 0;
            U(CHILD(0x7C4), 0x34) |= 2;
        }
        if (CHILD(0x7C8)) {
            U(CHILD(0x7C8), 0x34) |= 0x41;
            U(CHILD(0x7C8), 0x34) &= 0xEFFF;
            W(CHILD(0x7C8), 0x98) = 0;
            U(CHILD(0x7C8), 0x34) |= 2;
        }
        F(s, 0x7E8) = 1;
    } else {
        SetMobyState(moby, 4, 1);
        F(s, 0x7E8) = 1.5f;
    }
    F(moby, 0x2C) = F(*(u8 **)(moby + 0x24), 0x24) * F(s, 0x7E8);
    if (CHILD(0x7C0))
        F(CHILD(0x7C0), 0x2C) = F(*(u8 **)(CHILD(0x7C0) + 0x24), 0x24) * F(s, 0x7E8);
    if (CHILD(0x7C8))
        F(CHILD(0x7C8), 0x2C) = F(*(u8 **)(CHILD(0x7C8) + 0x24), 0x24) * F(s, 0x7E8);
    if (CHILD(0x7C4))
        F(CHILD(0x7C4), 0x2C) = F(*(u8 **)(CHILD(0x7C4) + 0x24), 0x24) * F(s, 0x7E8);
}
