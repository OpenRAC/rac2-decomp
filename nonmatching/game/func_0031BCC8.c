/* First complete ordinary-C reconstruction, 2026-11-03; retained, not linked.
 * Profile: -O2 -G8 -ffunction-sections in an isolated 0031BCC8-g8.c unit.
 * Current US check.py: 1916/1996 bytes, 0/2 placements (boot and one level).
 * Relocation bindings remain unqualified because the size check fails.
 * The 0x90 frame agrees, but this source saves an additional s6. Initializer,
 * child-field allocation, group-scan/control-flow layout and scheduling differ.
 * All three child factories keep their actual pointer returns and 64-bit render
 * words. The joint producer writes a complete 64-byte matrix including its last
 * position row, which the later vector addition reads. Every constructor/helper
 * integer/FP input and the final status-output short are retained.
 * Switching the four independent copies to reviewed qcopy_nc produces the same
 * 1916-byte output; the conservative clobbering qcopy form is kept here.
 * Reopen on independently evidenced init-block/group-scan and pointer lifetimes.
 * Retail dereferences child allocations without checking them; allocation failure
 * behavior and a complete native-port semantic gate are not established.
 */
#include "common.h"

#define F(p,o) (*(float *)((u8 *)(p) + (o)))
#define I(p,o) (*(s32 *)((u8 *)(p) + (o)))
#define H(p,o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p,o) (*(u16 *)((u8 *)(p) + (o)))
#define P(p,o) (*(u8 **)((u8 *)(p) + (o)))
#define W(p,o) (*(u64 *)((u8 *)(p) + (o)))

extern u8 D_001BAFA0[];
extern u8 *D_001B1C4C[] __attribute__((sda));
extern u8 *D_001B1B5C[] __attribute__((sda));
extern s16 *D_001EE5A0[];
extern s32 D_001B1B78 __attribute__((sda));
extern float D_001AFAF8[] SDATA(D_001AFAF8);
extern void *func_002B60B0(void *, float, float, float, float);
extern void func_0029FCC0(void *, s32, void *);
extern void func_0029FC20(void *, s32, void *);
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern float func_002A89A8(void *, s32, float);
extern void func_002A7750(void *, s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern u8 *func_0029EFD0(s32);
extern void func_002A0F48(void *);
extern void func_002AF1D0(void *, void *, s32, s32);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002B0ED8(void *, void *, s32);
extern void func_0031C720(u8 *);
extern s32 func_002A8508(s32, s32);
extern s32 func_002B3670(void *, s32 *, s32, s32, void *, float, float);

/* Build each attached child using its real 64-bit render word and joint. */
#define CREATE_CHILD(offset,joint) { \
    P(state,offset) = func_0029EFD0(0xAA2); \
    P(state,offset)[0x30] = object[0x30]; \
    U(P(state,offset),0x32) = U(object,0x32); \
    P(state,offset)[0x31] = 1; \
    W(P(state,offset),0x38) = W(object,0x38); \
    F(P(state,offset),0x2C) *= D_001AFAF8[0]; \
    func_002A0F48(P(state,offset)); \
    func_002AF1D0(object,P(state,offset),joint,0); \
}

/* Initialize the actor and its three children, then propagate activation to its group.
 * The joint producer writes a complete 64-byte matrix, including position at +0x30.
 * Retail does not guard the three child factory results before dereferencing them.
 */
void func_0031BCC8(u8 *object)
{
    float matrix[4][4] __attribute__((aligned(16)));
    u8 *state = P(object,0x68);
    s16 *group;
    u8 *other;
    u8 *otherState;
    s32 event;

    if (object[0x20] == 0) {
        P(state,0x18) = state + 0x110;
        I(state,0x290) = 1;
        I(state,0x27C) = 0;
        I(state,0x28C) = 0;
        F(state,0x254) *= 0.01745329424738884f;
        qcopy(state + 0x5A0,object + 0x10);
        I(state,0x294) = I(state,0x298) = 0;
        F(state,0x90) = F(state,0x94) = F(state,0x114) = 0.5f;
        state[0x77] = 24;
        state[0x70] = 15;
        I(state,0xA8) = 5;
        state[0x71] = 19;
        state[0x72] = 21;
        state[0x76] = 23;
        F(state,0x7C) = 0.10000000894069672f;
        F(state,0x80) = 0.06666667014360428f;
        F(state,0x88) = 0.008333333767950535f;
        F(state,0x8C) = 0.004166666883975267f;
        state[0xD3] = 0xFF;
        F(state,0x110) = 0.8f;
        F(state,0x11C) = 0.4f;
        F(state,0x120) = 1.134464144706726f;
        F(state,0x140) = 0.523598849773407f;
        F(state,0x13C) = 0.0055555556900799274f;
        F(state,0x84) = 0.004166666883975267f;
        F(state,0x9C) = 0.4f;
        state[0xCC] = state[0xCD] = state[0xCE] = state[0xCF] = state[0xD2] = 0xFF;
        F(state,0x118) = 0.4f;
        func_002B60B0(object,0.004444444552063942f,0.13333334028720856f,
                     0.0011635529808700085f,0.10471977293491364f);
        qcopy(state + 0x200,object + 0x10);
        I(state,0x250) = 0;
        F(state,0x210) = 1.0f;
        F(state,0x21C) = 5.0f;
        F(state,0x220) = 10.0f;
        state[0x28] = 3;
        func_0029FCC0(object,3,state + 0x350);
        F(state,0x358) += 20.0f;
        func_0029FCC0(object,3,state + 0x360);
        if (func_002761F8(state + 0x360,state + 0x350,0,object,0))
            qcopy(state + 0x350,D_001BAFA0);
        if (I(state,0x24C) == 0 && I(state,0x258) == -1) {
            F(object,0x18) = func_002A89A8(object + 0x10,0,0.5f);
            func_002A7750(object,1,0);
            if (object[0x43]) func_002A7470(object,0,0,0);
        } else {
            func_002A7750(object,3,2);
            if (object[0x43] != 12) func_002A7470(object,12,0,0);
        }
        if (I(state,0x258) != -1) {
            func_002A7750(object,2,0);
            qcopy(state + 0x350,D_001B1C4C[0] + (I(state,0x258) << 7) + 0x30);
        }
        object[0x30] = 0x80;
        CREATE_CHILD(0x270,0);
        CREATE_CHILD(0x274,1);
        CREATE_CHILD(0x278,2);
        func_0029FCC0(object,3,state + 0x360);
        func_0029FCC0(object,4,state + 0x370);
        func_0029FCC0(object,5,state + 0x380);
        func_0029FC20(object,6,matrix);
        func_00282C88(state + 0x390);
        I(state,0x398) = 0;
        F(state,0x390) = 0.25f;
        func_002830C0(state + 0x390,state + 0x390,matrix);
        func_00282CC0(state + 0x390,state + 0x390,matrix[3]);
        func_002AF1D0(object,P(state,0x270),0,0);
        func_002AF1D0(object,P(state,0x274),1,0);
        func_002AF1D0(object,P(state,0x278),2,0);
    }
    event = func_002B0ED8(object,state + 0x60,0);
    if (event) {
        if (event == 5) {
            I(state,0xF0) = 0;
            F(state,0xF4) = 0.8377581834793091f;
        }
        func_0031C720(object);
        if ((u32)(event - 4) < 2 && object[0x21] <= D_001B1B78 &&
            func_002A8508(object[0x21],-1) >= 2) {
            group = D_001EE5A0[object[0x21]];
            do {
                other = D_001B1B5C[0] + ((*group & 0x7FFF) << 8);
                if (H(other,0xAA) == 0x9B4) {
                    otherState = P(other,0x68);
                    if (!I(otherState,0x2A4)) { I(otherState,0x2A4) = 1; break; }
                } else if (H(other,0xAA) == 0x9B5) {
                    otherState = P(other,0x68);
                    if (!I(otherState,0x264)) { I(otherState,0x264) = 1; break; }
                }
            } while (*group++ >= 0);
        }
    }
    if (F(object,0x18) - func_002A89A8(object + 0x10,0,0.5f) > 20.0f &&
        object[0x21] <= D_001B1B78 && !I(state,0x298)) {
        I(state,0x298) = 1;
        if (func_002A8508(object[0x21],-1) >= 2) {
            group = D_001EE5A0[object[0x21]];
            do {
                other = D_001B1B5C[0] + ((*group & 0x7FFF) << 8);
                if (H(other,0xAA) == 0x9B4) {
                    otherState = P(other,0x68);
                    if (!I(otherState,0x2A4)) { I(otherState,0x2A4) = 1; break; }
                } else if (H(other,0xAA) == 0x9B5) {
                    otherState = P(other,0x68);
                    if (!I(otherState,0x264)) { I(otherState,0x264) = 1; break; }
                }
            } while (*group++ >= 0);
        }
    }
    H(state,0x244) = func_002B3670(object,(s32 *)(state + 0x248),I(state,0x230),
                                  I(state,0x234),state + 0x5A0,F(state,0x238),F(state,0x23C));
}
