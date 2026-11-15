#include "common.h"

#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define I(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[] NOT_SDA;
extern u8 D_0019B4A8[] NOT_SDA;
extern struct { u8 header[0x464]; u8 collected[0]; } D_L01_0021E4B0;
extern u8 D_00189EA0[] NOT_SDA;
extern s32 func_002ACBC8(void *, s32);
extern void func_002A7750(void *, s32, s32);
extern f32 func_00283180(f32);
extern void func_00282D30(void *, void *, f32);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_002AA150(f32, f32, f32);
extern s32 func_00282948(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L01_003D1A48(void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Saves the starting transform, waits for a trigger or saved activation, and
   eases the position and Euler angles through the outgoing and returning states.
   The branch-local counter pointers and blend values have separate lifetimes. */
void func_L01_003D1F40(u8 *m)
{
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 oldAngle[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[12] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(m + 0x68);
    s32 level, bits;
    u16 uid;
    u8 *entry;

    qcopy(oldPos, m + 0x10);
    qcopy(oldAngle, m + 0xF0);
    switch (m[0x20]) {
    case 0:
        qcopy(s + 0x60, m + 0x10);
        qcopy(s + 0x70, m + 0xF0);
        level = D_001A79F0[0];
        I(s, 0xAC) = 0;
        I(s, 0xB8) = 0;
        if ((D_0019B2E8[m[0xB0] + (level << 4)] & 0x80) ||
            (uid = *(u16 *)(m + 0xB2), D_L01_0021E4B0.collected[(s16)uid]) ||
            (entry = D_0019B4A8 + (((s16)uid >> 1) + (level << 10)),
            (bits = *entry, (uid & 1) ? (bits >> 4) & 7 : bits & 7))) {
            s[0xA8] = 1;
            func_002A7750(m, 2, -1);
        } else {
            func_002A7750(m, 1, -1);
        }
        break;
    case 1: {
        u16 uid;

        if (m[0xBC])
            func_002A7750(m, 2, -1);
        if (I(s, 0xA0) != -1 && IsPointInCuboid(D_00189EA0, I(s, 0xA0))) {
            uid = *(u16 *)(m + 0xB2);
            if (uid & 1) {
                u8 *entry = D_0019B4A8 + (((s16)uid >> 1) + (D_001A79F0[0] << 10));
                if (((*entry >> 4) & 7) != 7)
                    *entry += 0x10;
            } else {
                u8 *entry = D_0019B4A8 + (((s16)uid >> 1) + (D_001A79F0[0] << 10));
                if ((*entry & 7) != 7)
                    ++*entry;
            }
            s[0xA8] = 1;
            func_002A7750(m, 2, -1);
        }
        break;
    }
    case 2: {
        f32 t;

        F(s, 0xAC) += 1.0f / F(s, 0xA4);
        if (F(s, 0xAC) > 1.0f)
            F(s, 0xAC) = 1.0f;
        else if (F(s, 0xAC) < 0.0f)
            F(s, 0xAC) = 0.0f;
        t = 1.0f - func_00283180(F(s, 0xAC) * 3.14159274f);
        t = t * 0.5f;
        FastVecScale(delta, s + 0x80, t);
        euler_rotation_basis(rotation, s + 0x70);
        matrix_mul_vec3(delta, delta, rotation);
        FastVecAdd(m + 0x10, s + 0x60, delta);
        F(m, 0xF8) = func_002AA150(F(s, 0x78), FastAddRotations(F(s, 0x78), F(s, 0x98)), t);
        F(m, 0xF4) = func_002AA150(F(s, 0x74), FastAddRotations(F(s, 0x74), F(s, 0x94)), t);
        F(m, 0xF0) = func_002AA150(F(s, 0x70), FastAddRotations(F(s, 0x70), F(s, 0x90)), t);
        if (F(s, 0xAC) >= 1.0f) {
            I(s, 0xB0) = H(s, 0xAA);
            func_002A7750(m, 3, -1);
        }
        break;
    }
    case 3: {
        u16 uid;

        if (I(s, 0xA0) != -1 && IsPointInCuboid(D_00189EA0, I(s, 0xA0))) {
            uid = *(u16 *)(m + 0xB2);
            if (uid & 1) {
                u8 *entry = D_0019B4A8 + (((s16)uid >> 1) + (D_001A79F0[0] << 10));
                if (((*entry >> 4) & 7) != 7)
                    *entry += 0x10;
            } else {
                u8 *entry = D_0019B4A8 + (((s16)uid >> 1) + (D_001A79F0[0] << 10));
                if ((*entry & 7) != 7)
                    ++*entry;
            }
            s[0xA8] = 1;
        }
        if (!s[0xA8] && !m[0xBC] && func_00282948(s + 0xB0))
            func_002A7750(m, 4, -1);
        break;
    }
    case 4: {
        f32 t;

        F(s, 0xAC) -= 1.0f / F(s, 0xA4);
        if (F(s, 0xAC) > 1.0f)
            F(s, 0xAC) = 1.0f;
        else if (F(s, 0xAC) < 0.0f)
            F(s, 0xAC) = 0.0f;
        t = 1.0f - func_00283180(F(s, 0xAC) * 3.14159274f);
        t = t * 0.5f;
        FastVecScale(delta, s + 0x80, t);
        euler_rotation_basis(rotation, s + 0x70);
        matrix_mul_vec3(delta, delta, rotation);
        FastVecAdd(m + 0x10, s + 0x60, delta);
        F(m, 0xF8) = func_002AA150(F(s, 0x78), FastAddRotations(F(s, 0x78), F(s, 0x98)), t);
        F(m, 0xF4) = func_002AA150(F(s, 0x74), FastAddRotations(F(s, 0x74), F(s, 0x94)), t);
        F(m, 0xF0) = func_002AA150(F(s, 0x70), FastAddRotations(F(s, 0x70), F(s, 0x90)), t);
        if (F(s, 0xAC) >= 1.0f)
            func_002A7750(m, 1, -1);
        if (m[0xBC])
            func_002A7750(m, 2, -1);
        if (I(s, 0xA0) != -1 && IsPointInCuboid(D_00189EA0, I(s, 0xA0))) {
            s[0xA8] = 1;
            func_002A7750(m, 2, -1);
        }
        break;
    }
    }
    if (H(m, 0xAA) == 0xA9D && m[0x20] >= 2 && m[0x20] < 5)
        func_L00_002E6CF0(func_L01_003D1A48, m);
    if (m[0x20] < 5) {
        FastVecSub(delta, m + 0x10, oldPos);
        func_002AD6F0(s + 0x20, delta, oldAngle, m + 0xF0);
    }
    if (s[0xA9])
        m[0xBC] = 0;
}
