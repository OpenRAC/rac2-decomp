/* func_L04_0044DB18: the Barlow beast state machine (10,064 bytes, US and US2;
 * absent from PAL). Both switches are written in retail case-body order. Callee
 * prototypes follow their matched callers: argument registers are loaded in
 * parameter order, so func_002A7EA0 takes its int after the four floats and
 * func_002A8C28 its three floats before the three ints, and func_002B60B0
 * returns nothing (an unused return value moves local-alloc choices).
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } BeastVector;
typedef struct {
    u8 reserved00[0x18]; u8 enabled, count, kind; u8 reserved1B[0x65]; u8 payload[1];
} DispatchContext;
extern u8 D_00139646[];
extern u8 *D_L04_001FE340[];
extern u16 *D_L04_001FB1E0[];
extern u8 *D_L04_001B24DC __attribute__((sda));
extern int D_L04_001B24F8 __attribute__((sda));
extern int func_L04_004502D0(u8 *);
extern int func_002B3890(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern float func_00282C48(float);
extern int func_00282948(void *);
extern void func_002A7470(u8 *, int, int, int);
extern int func_002A7820(int, int), func_002A77E0(int);
extern void func_002A7750(u8 *, u8, int);
extern float func_00282E80(void *, void *), func_00283248(float, float);
extern int func_002B6228(void *, void *, int, int);
extern int func_002B50E0(void *, void *, float);
extern u32 func_002B1C20(void *, DispatchContext *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *);
extern int func_L04_0044DAC8(char *);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(void *), func_002833F0(void *, void *);
extern float func_0029F530(char *), func_002A89A8(void *, int, float);
extern float func_00283180(float), func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A6C58(void *, int, int);
extern void func_L01_003E9CF8(void *, unsigned int, void (*)(void *));
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern float func_002AA2E8(float *, float, float);
extern void func_L01_00318638(void *, void *, void *);
extern float func_00283BE0(float, float), func_00283C80(float, float);
extern int func_002B38B8(u8 *), func_002B6120(char *, char *), func_002A8508(int, int);
extern int func_L04_0033D4B0(u8 *);
struct family_27f9_object;
extern float func_002A7E08(struct family_27f9_object *, float *, float *, float, float, float);
extern void func_L01_00321178(char *, char *);
extern int func_L04_00450D50(u8 *, void *, float, float, float, float);
extern int func_002B4FF0(char *, float *, float);
extern void func_0029FCC0(char *, int, char *);
extern int func_002A8C28(void *, void *, int, float, float, float, int, int, int);
extern void func_L04_00451018(char *);
#define I(o) (*(s32 *)(state + (o)))
#define U(o) (*(u32 *)(state + (o)))
#define F(o) (*(float *)(state + (o)))
#define S(o) (*(s16 *)(state + (o)))
#define US(o) (*(u16 *)(state + (o)))
#define P(o) (*(u8 **)(state + (o)))
#define OF(o) (*(float *)(object + (o)))

/* Updates the beast's rider mode, route following and close-range action states. */
/* Moby update: Tribesman (class 4088, PS3 name). */
void func_L04_0044DB18(u8 *object)
{
    BeastVector offset, target, lateral;
    u8 *state;
    u8 *other, *route, *entity, *linked;
    u16 *ids;
    float oldHeight = OF(0x18);
    float distance, angle, turn, nearest, firstDistance, lastDistance;
    int i, selected, random, animation;
    u32 dispatch;
    state = *(u8 **)(object + 0x68);
    if (func_L04_004502D0(object)) { func_0029F338(object); return; }
    switch (object[0x95]) {
    case 0:
        if (func_002B3890(object))
            func_002B60B0(object, 0.0016666667f, 0.05000000447034836f, 0.0011635529808700085f, 0.10471977f);
        if ((I(0x258) == 1 || (I(0x560) != 0 && S(0x274) == 2)) &&
            func_00282C48(*(float *)(P(0x240) + 0x18) - OF(0x18)) < 2.0f) {
            if (func_00282948(state + 0x2B0)) {
                D_00139646[0] = 1;
                if (I(0x29C) != -1) {
                    if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                    func_002A7750(object, 22, 2);
                } else if (I(0x2A4) == 1) {
                    if (object[0x43] != 31) func_002A7470(object, 31, 0, func_002A7820(10, 20));
                    func_002A7750(object, 17, 2);
                } else {
                    I(0x2A0) = 1;
                    if (func_002A77E0(3) == 1) {
                        if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
                        func_002A7750(object, 17, 3);
                    } else {
                        if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                        func_002A7750(object, 19, 3);
                    }
                }
                goto mode_complete;
            }
        }
        if (S(0x276) != 0) {
            if (I(0x570) != -1 && I(0x574) == 1) {
                if (object[0x43] != 24) func_002A7470(object, 24, 0, func_002A7820(5, 15));
                func_002A7750(object, 6, -1);
            } else if (I(0x570) != -1 && I(0x574) > 1) {
                if (object[0x43] != 12) func_002A7470(object, 12, 0, func_002A7820(5, 15));
                func_002A7750(object, 7, -1);
                func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.003393696155399084f, 0.2617994248867035f);
            } else {
                object[0x95] = 1;
                if (object[0x43] != 24) func_002A7470(object, 24, 0, 20);
            }
            if ((u32)(US(0x274) - 1) < 2 && func_00282C48(*(float *)(P(0x240) + 0x18) - OF(0x18)) < 2.0f) {
                if (I(0x29C) != -1) {
                    if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                    func_002A7750(object, 22, 2);
                } else if (I(0x2A4) == 1) {
                    if (object[0x43] != 31) func_002A7470(object, 31, 0, func_002A7820(10, 20));
                    func_002A7750(object, 17, 2);
                } else {
                    I(0x2A0) = 1;
                    if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
                    func_002A7750(object, 17, 3);
                }
            }
            S(0x276) = 0;
        }
        break;
    case 1:
        if (func_002B3890(object)) {
            func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
            F(0x12C) = 6.0f; F(0x298) = 6.0f;
        }
        if (I(0x258) != 1 && I(0x25C) != 1) break;
        I(0x178) &= ~0x10;
        if (I(0x29C) != -1) {
            if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
            func_002A7750(object, 22, 2);
            selected = 0; nearest = 100.0f;
            for (i = 0; i < *(int *)D_L04_001FE340[I(0x29C)]; i++) {
                float d = vec_distance_xy(object + 0x10, D_L04_001FE340[I(0x29C)] + 0x10 + i * 16);
                if (d < nearest) { nearest = d; selected = i; }
            }
            func_002B6228(object, D_L04_001FE340[I(0x29C)], -1, selected);
        } else if (I(0x2A4) == 1) {
            if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
            func_002A7750(object, 21, 2);
        } else {
            I(0x2A0) = 1;
            if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
            func_002A7750(object, 17, 3);
        }
        break;
    case 2:
        if (func_002B3890(object))
            func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977293491364f);
        if (I(0x258) == 1 || I(0x25C) == 1 || I(0x560) != 0) break;
        random = func_002A77E0(4);
        if (random == 0) {
            if (object[0x43] != 25) func_002A7470(object, 25, 0, func_002A7820(10, 20));
        } else if (random == 1) {
            if (object[0x43] != 17) func_002A7470(object, 17, 0, func_002A7820(20, 30));
        } else if (random == 2) {
            if (object[0x43] != 30) func_002A7470(object, 30, 0, func_002A7820(20, 30));
        } else if (object[0x43] != 24) func_002A7470(object, 24, 0, func_002A7820(20, 30));
        func_002A7750(object, 12, 1);
        break;
    case 4:
        if (F(0x20) > 0.0f) {
            u8 *position = object + 0x10;
            angle = func_00283248(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
            func_002B50E0(object, position, angle);
        }
        dispatch = func_002B1C20(object, (DispatchContext *)(state + 0x60));
        if (dispatch & 1) { SetDeathBits(object, 0, 3); func_L01_003E9CF8(object, 0, 0); return; }
        if (dispatch & 2) {
            S(0x26) = 0;
            if ((I(0x258) == 1 || I(0x25C) == 1) && func_00282C48(*(float *)(P(0x240) + 0x18) - OF(0x18)) < 2.0f) {
                if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                func_002A7750(object, 21, 2);
                if (state[0x37] != 10) break;
                if (object[0x43] != 14) func_002A7470(object, 14, 9, 4);
                func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
                func_002A7750(object, 23, 2);
            } else if (I(0x570) != -1) {
                if (object[0x43] != 12) func_002A7470(object, 12, 0, func_002A7820(5, 15));
                func_002A7750(object, 7, 0);
                func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.003393696155399084f, 0.2617994248867035f);
            } else {
                if (object[0x43] != 10) func_002A7470(object, 10, 0, 10);
                func_002A7750(object, 12, 1);
                S(0x270) = func_002A7820(580, 600);
            }
        }
        break;
    case 3:
        if (func_002B3890(object))
            func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977293491364f);
        if (I(0x2A4) == 1) {
            if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
            func_002A7750(object, 21, 2);
        }
        if (I(0x258) == 1 || I(0x25C) == 1) break;
        random = func_002A77E0(4);
        if (random == 0) {
            if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
        } else if (random == 1) {
            if (object[0x43] != 17) func_002A7470(object, 17, 0, 20);
        } else if (random == 2) {
            if (object[0x43] != 30) func_002A7470(object, 30, 0, 20);
        } else if (object[0x43] != 24) func_002A7470(object, 24, 0, 20);
        func_002A7750(object, 12, 1);
        break;
    case 5:
        if (P(0x288)) func_002AF1D0(object, P(0x288), 1, 0);
        linked = P(0x284);
        *(Quad *)(object + 0x10) = *(Quad *)(linked + 0x10);
        *(Quad *)(object + 0xF0) = *(Quad *)(linked + 0xF0);
        {
            u8 *rider = P(0x290);
            *(Quad *)(rider + 0x10) = *(Quad *)(object + 0x10);
            *(Quad *)(rider + 0xF0) = *(Quad *)(object + 0xF0);
            *(Quad *)(rider + 0x10) = *(Quad *)(object + 0x10);
            *(float *)(rider + 0x18) += 0.65f;
        }
        if (I(0x27C) == 0) {
            func_002AC728(object, P(0x288) + 0x10, -1, 0.5f, 3.0f);
            if (P(0x288)) { func_0029F338(P(0x288)); P(0x288) = 0; }
            func_0029F338(P(0x290));
            *(u8 **)(*(u8 **)(P(0x284) + 0x68) + 0x2AC) = 0;
            func_002A7750(object, 2, 6);
        } else if (func_L04_0044DAC8((char *)object)) {
            func_002AC728(object, P(0x288) + 0x10, -1, 0.5f, 3.0f);
            if (P(0x288)) { func_0029F338(P(0x288)); P(0x288) = 0; }
            func_0029F338(P(0x290));
            *(u8 **)(*(u8 **)(P(0x284) + 0x68) + 0x2AC) = 0;
            if (object[0x43] != 9) func_002A7470(object, 9, 0, 0);
            func_002A7750(object, 3, 6);
        }
        break;
    case 6:
        if (func_002B3890(object)) {
            P(0x2AC) = CreateMoby(0x9AC);
            if (!P(0x2AC)) { func_0029F338(object); return; }
            P(0x2AC)[0x30] = object[0x30]; *(u16 *)(P(0x2AC) + 0x32) = *(u16 *)(object + 0x32);
            P(0x2AC)[0x31] = 1; *(unsigned long *)(P(0x2AC) + 0x38) = *(unsigned long *)(object + 0x38);
            func_002A0F48(P(0x2AC)); *(int *)(P(0x2AC) + 0x98) = 0;
            func_002AF1D0(object, P(0x2AC), 3, 0);
            I(0x2A0) = 1; OF(0xF0) = 0; OF(0xF4) = 0;
            euler_rotation_basis(object + 0xC0, object + 0xF0);
        }
        break;
    }
    mode_complete:
    switch (object[0x20]) {
    case 1:
        break;
    case 2:
        if (object[0x60] & 2) {
            if (F(0x20) > 0.0f) {
                I(0x178) &= ~0x10; *(u16 *)(object + 0x34) |= 0x5000;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                func_002A7750(object, 12, 1);
                if (S(0x270) < 300) S(0x270) = func_002A7820(480, 600);
                if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
            } else {
                SetDeathBits(object, 0, 3); func_L01_003E9CF8(object, 0, 0); return;
            }
        }
        {
            float dist = func_0029F530((char *)object);
            if (dist >= 10.0f) OF(0x18) = func_002A89A8(object + 0x10, 0, 0.5f);
            if (dist >= 1.5f && dist <= 17.0f) {
                u8 *pos = object + 0x10;
                U(0x178) |= 0x10;
                offset.f[0] = func_00283180(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[1] = func_00283198(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[2] = 0;
                FastVecAdd(&target, pos, &offset);
                lateral.f[0] = func_00283180(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                lateral.f[1] = func_00283198(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                lateral.f[2] = 0;
                FastVecAdd(&target, pos, &lateral);
                func_002A7EA0(object, pos, &target, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
            }
        }
        break;
    case 3:
        if (object[0x60] & 2) {
            if (F(0x20) > 0.0f) {
                I(0x178) &= ~0x10; *(u16 *)(object + 0x34) |= 0x5000;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                func_002A7750(object, 12, 1);
                if (S(0x270) < 300) S(0x270) = func_002A7820(480, 600);
                if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
            } else {
                SetDeathBits(object, 0, 3); func_L01_003E9CF8(object, 0, 0); return;
            }
        }
        {
            float dist = func_0029F530((char *)object);
            if (dist >= 10.0f) OF(0x18) = func_002A89A8(object + 0x10, 0, 0.5f);
            if (dist >= 1.5f && dist <= 17.0f) {
                u8 *pos = object + 0x10;
                U(0x178) |= 0x10;
                offset.f[0] = func_00283180(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[1] = func_00283198(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[2] = 0;
                target.f[0] = func_00283180(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                target.f[1] = func_00283198(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                target.f[2] = 0; lateral.q = *(Quad *)(pos);
                FastVecAdd(&lateral, pos, &target);
                FastVecAdd(&lateral, pos, &offset);
                func_002A7EA0(object, pos, &lateral, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
            }
        }
        break;
    case 4:
        if (F(0x298) > 0.2f) {
            func_00282948(state + 0x294);
            animation = object[0x43];
            if ((animation != 13 && animation != 10) || (animation == 10 && I(0x294) != 0)) {
                if (object[0x43] != 13) func_002A7470(object, 13, 0, 14);
            }
            if (I(0x294) > 20)
                ApproachValue((float *)(state + 0x124), 0.05000000447034836f, 0.0008333333535119891f);
            else
                ApproachValue((float *)(state + 0x124), 0.0f, 0.0008333333535119891f);
            if (object[0x43] == 13) {
                if (I(0x294) == 0) func_002A7470(object, 10, 0, 12);
                func_L01_00318638(object, state + 0x110, state + 0x140);
            } else if (object[0x43] == 10 && (object[0x60] & 2)) {
                I(0x294) = func_002A7820(120, 700);
                if (object[0x43] != 13) func_002A7470(object, 13, 0, 12);
            }
        }
        break;
    case 5:
        if (I(0x564) == 3) {
            float limit = 1.5707964897155762f;
            angle = func_00283248(*(float *)(P(0x56C) + 0x10) - OF(0x10), *(float *)(P(0x56C) + 0x14) - OF(0x14));
            turn = fast_subtract_rotations(angle, OF(0xF8));
            if (func_002B38B8(object)) turn = -turn;
            if (turn > limit) turn = limit;
            else if (turn < -limit) turn = -limit;
            F(0x328) = turn;
        }
        if (I(0x564) == 1 && object[0x42] == 28 && func_002A77E0(200) == 1) {
            if (object[0x43] != 27) func_002A7470(object, 27, 0, 30);
            if (func_002A77E0(3) == 1 && object[0x43] != 26) func_002A7470(object, 26, 0, 30);
        }
        if ((u32)(object[0x42] - 26) < 2 && (object[0x60] & 2)) {
            if (object[0x43] != 29) func_002A7470(object, 29, 0, 30);
            if (*(s16 *)(P(0x56C) + 0xAA) == 0xFF8) {
                *(int *)(*(u8 **)(P(0x56C) + 0x68) + 0x564) = 1; I(0x564) = 2;
            }
        }
        if (object[0x42] == 29 && (object[0x60] & 2)) {
            if (object[0x43] != 30) func_002A7470(object, 30, 0, 30);
            if (I(0x564) == 1 && object[0x43] != 28) func_002A7470(object, 28, 0, 30);
            if (I(0x564) == 3) {
                ids = D_L04_001FB1E0[object[0x21]];
                for (;;) {
                    entity = D_L04_001B24DC + ((*ids & 0x7FFF) << 8);
                    if (*(s8 *)(entity + 0x20) >= 0 && *(s16 *)(entity + 0xAA) == 0xFF8 &&
                        *(int *)(*(u8 **)((D_L04_001B24DC + ((*ids & 0x7FFF) << 8)) + 0x68) + 0x564) == 1) {
                        P(0x56C) = D_L04_001B24DC + ((*ids & 0x7FFF) << 8);
                        break;
                    }
                    if ((s16)*ids++ < 0) break;
                }
            }
        }
        if (I(0x564) == 1 && object[0x42] == 30 && object[0x43] != 29) func_002A7470(object, 29, 0, 20);
        if (I(0x564) == 3 && P(0x56C)[0x42] == 29 && object[0x43] != 29) func_002A7470(object, 29, 0, 35);
        break;
    case 6:
        I(0x2A0) = 1;
        if (object[0x60] & 2) {
            func_002A7750(object, 7, -1);
            if (object[0x43] != 13) func_002A7470(object, 13, 0, 30);
            I(0x2A0) = 0;
        }
        break;
    case 7:
        if (func_002B6120((char *)object, (char *)D_L04_001FE340[I(0x570)])) {
            func_002A7750(object, 9, -1);
            if (object[0x43] != 24) func_002A7470(object, 24, 0, 20);
        }
        break;
    case 9:
        if (object[0x60] & 2) {
            func_002B60B0(object, 0.0016666667f, 0.05000000447034836f, 0.0011635529808700085f, 0.10471977f);
            if (func_002A8508(object[0x21], -1) > 1) {
                P(0x56C) = (u8 *)func_L04_0033D4B0(object);
                func_002A7750(object, 11, -1);
                if (object[0x43] != 28) func_002A7470(object, 28, 0, 30);
                I(0x564) = 1;
                if (P(0x56C)[0x42] == 28) {
                    if (object[0x43] != 30) func_002A7470(object, 30, 0, 30);
                    I(0x564) = 2;
                }
            }
        }
        break;
    case 11: {
        u8 *position = object + 0x10;
        angle = func_00283248(*(float *)(P(0x56C) + 0x10) - OF(0x10), *(float *)(P(0x56C) + 0x14) - OF(0x14));
        func_002B50E0(object, position, angle);
        angle = func_00283248(*(float *)(P(0x56C) + 0x10) - OF(0x10), *(float *)(P(0x56C) + 0x14) - OF(0x14));
        if (FastDiffRots(OF(0xF8), angle) < 0.087266475f) func_002A7750(object, 5, -1);
        break;
    }
    case 12:
        if (F(0x298) > 0.2f) {
            func_002A7E08((struct family_27f9_object *)object, (float *)P(0x240), (float *)(state + 0x28C), 0.001f, 0.01f, 0.1f);
            if (object[0x60] & 2) {
                if (object[0x43] != 22) func_002A7470(object, 22, 0, 20);
                func_002A7750(object, 13, -1); U(0x178) |= 0x10;
                if (I(0x578) != -1) *(Quad *)(state + 0x110) = *(Quad *)(D_L04_001FE340[I(0x578)] + 0x10);
            }
        }
        break;
    case 13:
        func_002A7E08((struct family_27f9_object *)object, (float *)P(0x240), (float *)(state + 0x28C), 0.001f, 0.01f, 0.1f);
        func_002B60B0(object, 0.0005555555690079927f, 0.016666668f, 0.0011635529808700085f, 0.10471977f);
        func_L01_00321178((char *)object, (char *)(state + 0x110));
        if (vec_distance_xy(object + 0x10, state + 0x110) < 2.0f) {
            I(0x178) &= ~0x10; func_002A7750(object, 14, -1);
            if (object[0x43] != 24) func_002A7470(object, 24, 0, 20);
            if (I(0x578) != -1) func_002A7750(object, 16, -1);
        }
        break;
    case 15:
        func_002B60B0(object, 0.0016666667f, 0.05000000447034836f, 0.0037815470714122057f, 0.29670602083206177f);
        if (func_002B6120((char *)object, (char *)D_L04_001FE340[I(0x578)])) {
            func_002A7750(object, 16, -1);
            if (object[0x43] != 24) func_002A7470(object, 24, 0, 20);
        }
        break;
    case 16:
        if (object[0x60] & 2) {
            route = D_L04_001FE340[I(0x578)];
            firstDistance = vec_distance_xy(object + 0x10, route + 0x10);
            lastDistance = vec_distance_xy(object + 0x10, route + *(int *)route * 16);
            if (lastDistance < firstDistance) func_002B6228(object, D_L04_001FE340[I(0x578)], 0, *(int *)route - 1);
            else func_002B6228(object, D_L04_001FE340[I(0x578)], *(int *)route - 1, 0);
            func_002A7750(object, 15, -1);
            if (object[0x43] != 13) func_002A7470(object, 13, 0, 20);
        }
        break;
    case 21:
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 5.0f && F(0x20) > 1.0f) {
            I(0x2A0) = 1;
            func_002B60B0(object, 0.0005555555690079927f, 0.016666668f, 0.0011635529808700085f, 0.10471977f);
            func_002A7750(object, 20, -1);
            if (object[0x43] != 22) func_002A7470(object, 22, 0, 10);
            break;
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            angle = func_00283248(F(0x230) - OF(0x10), F(0x234) - OF(0x14));
            if (FastDiffRots(OF(0xF8), angle) < 0.3490659f) {
                if (object[0x43] != 14) func_002A7470(object, 14, 0, 10);
                func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
                func_002A7750(object, 23, 2);
                break;
            }
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            angle = func_00283248(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
            func_002B50E0(object, object + 0x10, angle);
            break;
        }
        if (I(0x548) != 0) {
            if (func_L04_00450D50(object, state + 0x230, OF(0xF8), 7.0f, 0.25f, F(0x2A8)) &&
                object[0x21] <= D_L04_001B24F8 && func_002A8508(object[0x21], -1) > 1) {
                u16 *list = D_L04_001FB1E0[object[0x21]];
                do {
                    other = *(u8 **)(D_L04_001B24DC + ((*list & 0x7FFF) << 8) + 0x68);
                    if (*(int *)(other + 0x2A4) == 0) {
                        firstDistance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
                        lastDistance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
                        if (firstDistance < lastDistance && *(float *)(other + 0x20) > 0.0f) {
                            *(int *)(other + 0x2A4) = 1; I(0x2A4) = 0;
                            if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
                            func_002A7750(object, 17, 3);
                        }
                        break;
                    }
                } while ((s16)*list++ >= 0);
            }
        } else func_002B4FF0((char *)object, (float *)(state + 0x230), F(0x2A8));
        break;
    case 17:
        I(0x2A0) = 0;
        angle = func_00283248(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
        func_002B50E0(object, object + 0x10, angle);
        if (object[0x60] & 2) {
            distance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
            if (distance < 12.0f) {
                I(0x2A0) = 1;
                if (object[0x43] != 20) func_002A7470(object, 20, 0, 10);
                func_002A7750(object, 18, -1);
            } else {
                I(0x2A0) = 1;
                if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                func_002A7750(object, 19, 3);
            }
            if (I(0x2A4) != 0) {
                if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                func_002A7750(object, 21, 2);
            }
        }
        break;
    case 18:
        func_002A7E08((struct family_27f9_object *)object, (float *)P(0x240), (float *)(state + 0x28C), 0.001f, 0.01f, 0.1f);
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) > 12.0f && func_002A77E0(10) == 1) {
            if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
            func_002A7750(object, 19, -1);
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            if (object[0x43] != 14) func_002A7470(object, 14, 0, 10);
            func_002A7750(object, 23, -1);
        }
        if (func_002A77E0(3) == 1 && (object[0x60] & 2)) {
            if (object[0x43] != 25) func_002A7470(object, 25, 0, 10);
            if (func_002A77E0(3) == 1 && object[0x43] != 24) func_002A7470(object, 24, 0, 10);
            func_002A7750(object, 17, 3);
        }
        break;
    case 19:
        if (I(0x548) != 0) {
            if (func_L04_00450D50(object, state + 0x230, OF(0xF8), 7.0f, 0.25f, F(0x2A8))) {
                if (object[0x43] != 20) func_002A7470(object, 20, 0, 10);
                func_002A7750(object, 18, -1);
            }
        } else {
            func_002B4FF0((char *)object, (float *)(state + 0x230), F(0x2A8));
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 8.0f) {
            if (object[0x43] != 20) func_002A7470(object, 20, 0, 10);
            func_002A7750(object, 18, -1);
        }
        break;
    case 20:
        distance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
        if (distance < 2.5f) {
            angle = func_00283248(F(0x230) - OF(0x10), F(0x234) - OF(0x14));
            if (FastDiffRots(OF(0xF8), angle) < 0.3490659f) {
                if (object[0x43] != 14) func_002A7470(object, 14, 0, 6);
                func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
                func_002A7750(object, 23, 2);
                break;
            }
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            angle = func_00283248(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
            func_002B50E0(object, object + 0x10, angle);
            break;
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) > 9.0f && func_002A77E0(4) == 1) {
            func_002B60B0(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
            goto return_to_follow;
        } else {
            func_002B60B0(object, 0.0005555555690079927f, 0.016666668f, 0.0011635529808700085f, 0.10471977f);
            func_002B4FF0((char *)object, (float *)(state + 0x230), F(0x2A8));
        }
        break;
    case 22:
        F(0x174) = 1.5f;
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            if (object[0x43] != 14) func_002A7470(object, 14, 0, 2);
            func_002A7750(object, 23, -1); I(0x29C) = -1; F(0x164) = 0.0008333333535119891f;
        } else {
            F(0x164) = 0.004166666883975267f;
            if (func_002B6120((char *)object, (char *)D_L04_001FE340[I(0x29C)])) {
                if (I(0x2A4) == 1) {
                    if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                    func_002A7750(object, 21, 2);
                } else {
                    I(0x2A0) = 1;
                    if (func_002A77E0(3) == 1) {
                        if (object[0x43] != 11) func_002A7470(object, 11, 0, 10);
                        func_002A7750(object, 17, 3);
                    } else {
                        if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                        func_002A7750(object, 19, 3);
                    }
                }
                I(0x29C) = -1;
            }
        }
        break;
    case 23:
        I(0x2A0) = 0;
        distance = func_0029F530((char *)object);
        if (object[0x42] == 14) {
            if (distance >= 10.0f && distance <= 15.0f) {
                func_0029FCC0((char *)object, 2, (char *)&offset);
                target.f[0] = func_00283180(OF(0xF8)) * 0.5f;
                target.f[1] = func_00283198(OF(0xF8)) * 0.5f; target.f[2] = 0;
                FastVecAdd(&offset, &offset, &target);
                func_002A8C28(object, &offset, 0x04000001, 0.4f, F(0x2BC), 1.0f, 0, 1, 0);
                target.f[0] = func_00283180(OF(0xF8)); target.f[1] = func_00283198(OF(0xF8)); target.f[2] = 0;
                FastVecAdd(&offset, &offset, &target);
                func_002A8C28(object, &offset, 0x04000001, 0.4f, F(0x2BC), 1.0f, 0, 1, 0);
            }
            if (object[0x42] == 14 && distance < 10.0f) OF(0x48) = 0.65f;
            else OF(0x48) = 1.0f;
        } else OF(0x48) = 1.0f;
        if (object[0x60] & 2) {
            if (F(0x20) > 1.0f) {
                if (object[0x43] != 31) func_002A7470(object, 31, 0, 10);
                func_002A7750(object, 24, -1);
            } else {
                if (object[0x43] != 31) func_002A7470(object, 31, 0, 10);
                func_002A7750(object, 24, -1);
            }
            if (object[0x95] != 2) {
                func_002A7750(object, 18, -1);
                if (object[0x43] != 20) func_002A7470(object, 20, 0, 10);
            }
        }
        break;
    case 24:
        if (object[0x60] & 2) {
            if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            return_to_follow:
                if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                func_002A7750(object, 21, -1);
            } else {
                if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
                func_002A7750(object, 21, -1);
            }
        }
        break;
    }
    func_L04_00451018((char *)object);
    if (func_00282C48(OF(0x18) - oldHeight) < 0.005f) OF(0x18) = oldHeight;
    return;
}
