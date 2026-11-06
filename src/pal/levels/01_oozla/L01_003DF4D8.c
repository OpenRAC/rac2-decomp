/* func_PAL_L01_003DF4D8, the PAL copy of func_L01_003DAE58: the same C at 50 Hz, with its frame counts,
   rates and accelerations rescaled and the random wait in state 3 scaled by 5/6. */
#include "common.h"

extern void func_L01_003DD3A0(void *);
extern void func_PAL_L01_003E1648(void *);
extern void func_PAL_L01_003E05D0(void *);
extern void func_PAL_L01_003E1DB0(void *);
extern void func_L01_003DCE70(void *, void *);
extern void func_PAL_L01_003E1448(void *, void *);
extern void func_PAL_L01_003E14E0(void *, void *);
extern void func_PAL_L01_003E0710(void *, s32);
extern void func_L01_003DBB88(void *, s32);
extern void func_L01_003E9CF8(void *, s32, s32);
extern s32 func_00282978(void *);
extern s32 func_001163B0(void);
extern s32 func_002A7820(s32, s32);
extern s32 func_002A77E0(s32);
extern s32 func_002B1C20(void *, void *);
extern s32 func_L00_0031BE88(void *);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);
extern void func_PAL_002A7650(void *, s32, s32);
extern f32 func_00282C48(f32);
extern f32 func_00282DF0(void *);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_0029F530(void *);
extern f32 func_002A78D8(f32, f32);
extern f32 func_002A89A8(void *, s32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00283098(void *, void *, void *);
extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern f32 func_L00_0031CDD0(void *, void *, void *, f32, f32);
extern void func_002A7CA0(void *, f32, f32, f32, f32, void *);
extern f32 func_002AAA00(void *, f32, f32, f32, f32, void *, s32);
extern void func_002A8D70(void *, s32, s32, s32, s32, s32, f32, f32, f32);
extern u8 D_00189E20[];
extern u8 D_L01_001AC5A0[] MACRO_ADDR;

/* A 16-bit struct stays in HImode, so a local copy loads with lhu and tests with sll. */
typedef struct { s16 value; } Timer16;
typedef unsigned int UpdateQuad __attribute__((mode(TI)));

#define F(p, o) (*(f32 *)((p) + (o)))
#define I(p, o) (*(s32 *)((p) + (o)))
#define H(p, o) (*(s16 *)((p) + (o)))
#define U(p, o) (*(u16 *)((p) + (o)))

/* Runs the moby's state machine on obj[0x95]; from state 3 on, except 5, it then eases the
   rotation at 0xF4 and 0xF0 towards a direction, each angle clamped to 40 degrees. */
void func_PAL_L01_003DF4D8(u8 *obj)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    f32 inverse[16] __attribute__((aligned(16)));
    f32 oldInverse[16] __attribute__((aligned(16)));
    f32 height;
    u8 *state = *(u8 **)(obj + 0x68);
    f32 rate, speed, angle, pitch;
    s32 result;

    if (obj[0x95])
        func_L01_003DD3A0(obj);
    switch (obj[0x95]) {
    case 0:
        func_PAL_L01_003E1648(obj);
        break;
    case 1:
        if (state[0x3D0]) {
            U(obj, 0x34) |= 1;
            I(obj, 0x98) = 0;
            obj[0x31] = 0;
        }
        if (I(state, 0x2F4) == 1 && func_00282978(state + 0x3D4)) {
            if (state[0x3D0]) {
                func_L01_003DCE70(obj, pos);
                func_00282CF0(delta, pos, obj + 0x10);
                rate = 0.033333335071802139282f;
                if (func_00282DF0(delta) * rate < 0.16000001f)
                    speed = func_00282DF0(delta) * rate;
                else
                    speed = 0.16000001f;
                func_00282F20(delta, delta, speed);
                height = 0;
                delta[2] = func_L00_0031CDD0(obj + 0x10, pos, &height, speed, -0.0072000003f);
                qcopy(state + 0x190, delta);
                qcopy(state + 0x390, pos);
                if (obj[0x43] != 12)
                    func_PAL_002A7E68(obj, 12, 0, 2);
                if (height > 0)
                    F(obj, 0x48) = 51.0f / height;
                I(obj, 0x98) = I(*(u8 **)(obj + 0x24), 0x10);
                obj[0x31] = 1;
                U(obj, 0x34) &= 0xfffe;
                func_002A7750(obj, 0, 2);
            } else {
                if (I(state, 0x41C) != -1)
                    I(state, 0x3F8) = I(state, 0x41C);
                if (obj[0x43] != 7)
                    func_PAL_002A7E68(obj, 7, 0, func_002A7820(7, 12));
                func_002A7750(obj, 3, 3);
            }
        }
        break;
    case 2: {
        f32 distance;

        func_00282CC0(obj + 0x10, obj + 0x10, state + 0x190);
        func_002A7CA0(obj, func_00283248(F(state, 0x2E0) - F(obj, 0x10), F(state, 0x2E4) - F(obj, 0x14)),
                      F(state, 0x1D4), F(state, 0x1E4), F(state, 0x1DC) * 2, state + 0x274);
        F(state, 0x198) -= 0.0072000003f;
        if (F(state, 0x198) <= 0 && func_00282C48(F(obj, 0x18) - F(state, 0x398)) < -F(state, 0x198)) {
            F(obj, 0x48) = 1;
            F(obj, 0x18) = F(state, 0x398);
            F(state, 0x198) = 0;
            distance = func_00282E80(obj + 0x10, state + 0x390);
            if (distance < func_00282DF0(state + 0x190)) {
                qcopy(obj + 0x10, state + 0x390);
                qzero(state + 0x190);
            }
            if (obj[0x60] & 2) {
                qcopy(state + 0x2B0, obj + 0x10);
                if (obj[0x43] != 6)
                    func_PAL_002A7E68(obj, 6, 0, 10);
                F(obj, 0x48) = 1;
                F(state, 0x3DC) = func_002A78D8(20, 45) * 0.01745329424738884f;
                if (I(state, 0x41C) != -1)
                    I(state, 0x3F8) = I(state, 0x41C);
                if (state[0x3D3])
                    func_002A7750(obj, 2, 3);
                else {
                    if (I(state, 0x3C0) != -1)
                        I(state, 0x1FC) = I(state, 0x3C0);
                    func_002A7750(obj, 3, 3);
                }
            }
        }
        break;
    }
    case 3:
        switch (obj[0x20]) {
        case 1:
            if ((obj[0x60] & 2) && !H(state, 0x3D8)) {
                int wait = func_002A7820(180, 440);

                wait = ((s32)(wait) * 5 + 2) / 6;
                H(state, 0x3D8) = wait;
                if (obj[0x43] != 6)
                    func_PAL_002A7E68(obj, 6, 7, func_002A7820(7, 12));
                func_002A7750(obj, 2, -1);
            }
            break;
        case 2:
            func_PAL_L01_003E1448(obj, state + 0x2B0);
            if (!obj[0x40]) {
                if ((I(state, 0x2F4) == 1 || H(state, 0x3D6)) &&
                    (I(state, 0x408) != -1 || (**(s32 **)(state + 0x400) == H(obj, 0xB2) && !I(state, 0x404)))) {
                    if (I(state, 0x3C0) != -1)
                        I(state, 0x1FC) = I(state, 0x3C0);
                    H(state, 0x3D6) = 300;
                    if (I(state, 0x408) != -1) {
                        if (obj[0x43] != 7)
                            func_PAL_002A7E68(obj, 7, 0, func_002A7820(7, 12));
                        func_002A7750(obj, 3, -1);
                    } else {
                        if (obj[0x43] != (func_001163B0() & 1) + 2)
                            func_PAL_002A7E68(obj, (func_001163B0() & 1) + 2, 0, func_002A7820(7, 12));
                        func_002A7750(obj, 5, -1);
                    }
                } else {
                    Timer16 timer = *(Timer16 *)(state + 0x3D8);

                    if (H(state, 0x3D8))
                        break;
                    if (!H(state, 0x3D6) && I(state, 0x408) == -1) {
                        H(state, 0x3D8) = 100;
                        if (obj[0x43] != (func_001163B0() & 1))
                            func_PAL_002A7E68(obj, func_001163B0() & 1, 0, 12);
                        func_002A7750(obj, 1, 3);
                    } else if (!timer.value && I(state, 0x408) == -1) {
                        if (obj[0x43] != (func_001163B0() & 1) + 4)
                            func_PAL_002A7E68(obj, (func_001163B0() & 1) | 4, 0, 12);
                        func_002A7750(obj, 1, 3);
                    }
                }
            }
            break;
        case 3: {
            f32 distance;

            func_PAL_L01_003E14E0(obj, state + 0x390);
            distance = func_00282E80(obj + 0x10, state + 0x390);
            if (obj[0x60] & 2) {
                if ((H(*(u8 **)(state + 0x2F0), 0xAA) != 0xB1A && distance <= 3) ||
                    (H(*(u8 **)(state + 0x2F0), 0xAA) == 0xB1A && distance < 1)) {
                    I(state, 0x404) = 150;
                    F(state, 0x3F4) = 0.3f;
                    I(state, 0x3F0) = 0;
                    if (obj[0x43] != 8)
                        func_PAL_002A7E68(obj, 8, 0, func_002A7820(4, 7));
                    func_002A7750(obj, 0, 4);
                }
                if (I(state, 0x2F4) != 1 && !H(state, 0x3D6) && I(state, 0x408) == -1 && !func_002A77E0(39)) {
                    if (!func_002A77E0(3)) {
                        I(state, 0x404) = 150;
                        F(state, 0x3F4) = 0.3f;
                        I(state, 0x3F0) = 0;
                        if (obj[0x43] != 8)
                            func_PAL_002A7E68(obj, 8, 0, func_002A7820(4, 7));
                        func_002A7750(obj, 0, 4);
                    } else {
                        if (obj[0x43] != 6)
                            func_PAL_002A7E68(obj, 6, 0, func_002A7820(12, 18));
                        func_002A7750(obj, 4, 3);
                    }
                }
            }
            break;
        }
        case 4:
            func_PAL_L01_003E1448(obj, state + 0x2B0);
            if (obj[0x60] & 2) {
                if (!I(state, 0x404) || func_00282E80(obj + 0x10, D_00189E20 + 0x80) > 7) {
                    H(state, 0x3D8) = 50;
                    if (obj[0x43] != (func_001163B0() & 1) + 4)
                        func_PAL_002A7E68(obj, (func_001163B0() & 1) | 4, 0, 12);
                    func_002A7750(obj, 1, 3);
                }
            }
            break;
        case 5:
            func_002A7CA0(obj, func_00283248(F(state, 0x2E0) - F(obj, 0x10), F(state, 0x2E4) - F(obj, 0x14)),
                          F(state, 0x1D4) * 2, F(state, 0x1E4), F(state, 0x1DC) * 2, state + 0x274);
            if (obj[0x60] & 2) {
                if (obj[0x43] != 7)
                    func_PAL_002A7E68(obj, 7, 0, func_002A7820(7, 12));
                func_002A7750(obj, 3, -1);
            }
            break;
        }
        break;
    case 4: {
        f32 distance;
        u8 *target;

        distance = func_0029F530(obj);
        target = *(u8 **)(state + 0x2F0);
        func_002AAA00(obj + 0xF8, func_00283248(F(target, 0x10) - F(obj, 0x10), F(target, 0x14) - F(obj, 0x14)),
                      F(state, 0x1D4), F(state, 0x1D8), F(state, 0x1DC), state + 0x274, 0);
        if (obj[0x42] == 8 && distance >= 18 && distance <= 23) {
            F(obj, 0x48) = 0.4f;
            func_002A8D70(obj, 0, 0x4000001, 0, 1, 0, 0.2f, (f32)state[0x34], 1);
            func_PAL_L01_003E0710(obj, 0);
        } else {
            F(obj, 0x48) = 1;
            func_PAL_L01_003E0710(obj, 1);
        }
        if (obj[0x42] == 8 && distance >= 25) {
            F(state, 0x380) = func_00283180(F(obj, 0xF8)) * 3.25f;
            F(state, 0x384) = func_00283198(F(obj, 0xF8)) * 3.25f;
            I(state, 0x388) = 0;
            func_00282CC0(state + 0x380, state + 0x380, obj + 0x10);
            F(state, 0x388) = func_002A89A8(state + 0x380, 0, 0.5f) + 0.025f;
            func_L01_003DBB88(obj, 1);
        }
        if (obj[0x60] & 2) {
            if (obj[0x43] != 6)
                func_PAL_002A7E68(obj, 6, 0, func_002A7820(12, 18));
            func_002A7750(obj, 4, 3);
        }
        break;
    }
    case 5:
        result = func_002B1C20(obj, state + 0x110);
        if (result & 1)
            func_002A7750(obj, 0, 6);
        else if (result & 2) {
            I(state, 0x410) = -1;
            func_PAL_L01_003E05D0(obj);
            if (I(state, 0x3C0) != -1)
                I(state, 0x1FC) = I(state, 0x3C0);
            if (I(state, 0x41C) != -1)
                I(state, 0x3F8) = I(state, 0x41C);
            H(state, 0x3D6) = 500;
            H(state, 0x3D8) = 25;
            if (obj[0x43] != (func_001163B0() & 1) + 4)
                func_PAL_002A7E68(obj, (func_001163B0() & 1) | 4, 0, 12);
            func_002A7750(obj, 1, 3);
        }
        break;
    case 6:
        func_PAL_002A7650(obj, 0, 3);
        func_PAL_L01_003E05D0(obj);
        func_L01_003DBB88(obj, 1);
        func_L01_003E9CF8(obj, 0, 0);
        break;
    }
    if (obj[0x95] != 5 && obj[0x95] >= 3) {
        *(UpdateQuad *)pos = 0;
        pos[2] = F(obj, 0xF8);
        *(UpdateQuad *)delta = *(UpdateQuad *)pos;
        func_00283410(matrix, delta);
        func_00283698(inverse, matrix);
        func_00283698(oldInverse, obj + 0xC0);
        {
            f32 *v;
            u8 *target = *(u8 **)(state + 0x248);

            if (target && !func_L00_0031BE88(target)) {
                v = pos;
                qcopy(v, D_L01_001AC5A0);
            } else
                func_00282F20(pos, state + 0x210, 1);
            v = pos;
            func_00283098(v, v, inverse);
        }
        angle = func_00283248(pos[2], pos[0]);
        pitch = -func_00283248(pos[2], pos[1]);
        if (angle > 0.69813179969787597656f)
            angle = 0.69813179969787597656f;
        else if (angle < -0.69813179969787597656f)
            angle = -0.69813179969787597656f;
        if (pitch > 0.69813179969787597656f)
            pitch = 0.69813179969787597656f;
        else if (pitch < -0.69813179969787597656f)
            pitch = -0.69813179969787597656f;
        func_002AAA00(obj + 0xF4, angle, 0.0025132746f, 0.0025132746f,
                      0.12566373f, state + 0x3EC, 0);
        func_002AAA00(obj + 0xF0, pitch, 0.0025132746f, 0.0025132746f,
                      0.12566373f, state + 0x3E8, 0);
    }
    func_PAL_L01_003E1DB0(obj);
}
