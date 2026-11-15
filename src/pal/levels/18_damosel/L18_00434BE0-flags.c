#include "include_asm.h"

#include "common.h"
extern int FloatToInt(float);
extern float IntToFloat(int);
extern u8 *CreateMoby(int);
extern void func_002A0F48(u8 *);
extern void moby_transform_joint_to_world(int, int, void *);
extern void moby_mark_spawned(void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern int path_build_route_nodes(u8 *, int, u8 *, int);
extern void moby_set_state(u8 *, int, int);
typedef struct { float value[16]; } __attribute__((packed)) InitValues;
extern InitValues D_L18_001B1570;
#define W(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(short *)((p) + (o)))
#define U(p, o) (*(unsigned short *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define CHILD(o) (*(u8 **)(s + (o)))

void func_PAL_L18_004352C8(u8 *a) {
    float pos[4] __attribute__((aligned(16)));
    InitValues values;
    u8 *s = *(u8 **)(a + 0x68);
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
    F(s, 0x12C) = 0.004f;
    F(s, 0x10C) = F(s, 0x108) = 0.375f;
    F(s, 0x110) = 1.5707965f;
    if (W(s, 0x798) != -1) W(s, 0x13C) = W(s, 0x798);

    CHILD(0x7C0) = CreateMoby(0xF0B);
    if (CHILD(0x7C0) == 0) goto fail;
    CHILD(0x7C0)[0x30] = a[0x30];
    U(CHILD(0x7C0), 0x32) = U(a, 0x32);
    *(u64 *)(CHILD(0x7C0) + 0x38) = *(u64 *)(a + 0x38);
    func_002A0F48(CHILD(0x7C0));
    W(CHILD(0x7C0), 0x98) = 0;
    moby_transform_joint_to_world((int)a, 0, pos);
    qcopy_nc(CHILD(0x7C0) + 0x10, pos);
    qcopy_nc(CHILD(0x7C0) + 0xF0, a + 0xF0);
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

    if (H(s, 0x7FC)) CHILD(0x7C8) = CreateMoby(0xF0D);
    else CHILD(0x7C8) = CreateMoby(0xF0E);
    if (CHILD(0x7C8) == 0) goto fail;
    CHILD(0x7C8)[0x30] = a[0x30];
    U(CHILD(0x7C8), 0x32) = U(a, 0x32);
    *(u64 *)(CHILD(0x7C8) + 0x38) = *(u64 *)(a + 0x38);
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
            vec_random_direction(p1, -3.1415927f, 3.1415927f); p1 += 0xA0;
            vec_random_direction(p2, -3.1415927f, 3.1415927f); p2 += 0xA0;
            vec_random_direction(p3, 0.2792527f, 0.34906593f); p3 += 0xA0;
            vec_random_direction(p4, 0.2792527f, 0.34906593f); p4 += 0xA0;
            vec_random_direction(p5, 1, 1.7f); p5 += 0xA0;
            vec_random_direction(p6, 1, 1.7f); p6 += 0xA0;
        }
    }
    goto spawned;

fail:
    /* One release path for both failed spawns. */
    moby_mark_spawned(a);
    return;

spawned:
    if (!math_random_int_below(2)) {
        U(a, 0x34) |= 0x8000;
        U(CHILD(0x7C0), 0x34) |= 0x8000;
    }
    if (W(s, 0x7D4) != -1)
        W(s, 0x780) = path_build_route_nodes(a, W(s, 0x7D4), s + 0x210, 0x20);
    if (H(s, 0x7FC)) H(s, 0x804) = math_random_int_below(150);
    U(s, 0x7F6) = U(s, 0x7F4);
    if (H(s, 0x7F8)) {
        moby_set_state(a, 1, 0);
        W(a, 0x98) = 0;
        U(a, 0x34) = (U(a, 0x34) & 0xEFFF) | 0x43;
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
        moby_set_state(a, 4, 1);
        F(s, 0x7E8) = 1.5f;
    }
    F(a, 0x2C) = F(*(u8 **)(a + 0x24), 0x24) * F(s, 0x7E8);
    if (CHILD(0x7C0))
        F(CHILD(0x7C0), 0x2C) = F(*(u8 **)(CHILD(0x7C0) + 0x24), 0x24) * F(s, 0x7E8);
    if (CHILD(0x7C8))
        F(CHILD(0x7C8), 0x2C) = F(*(u8 **)(CHILD(0x7C8) + 0x24), 0x24) * F(s, 0x7E8);
    if (CHILD(0x7C4))
        F(CHILD(0x7C4), 0x2C) = F(*(u8 **)(CHILD(0x7C4) + 0x24), 0x24) * F(s, 0x7E8);
}
