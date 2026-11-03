#include "common.h"

/* The two rate pairs the state table selects and the four scales the emitter applies. */
extern f32 D_L12_001B17F4 __attribute__((sda));
extern f32 D_L12_001B17F8 __attribute__((sda));
extern f32 D_L12_001B17FC __attribute__((sda));
extern f32 D_L12_001B1800 __attribute__((sda));
extern f32 D_L12_001B1804 __attribute__((sda));
extern f32 D_L12_001B1808 __attribute__((sda));

extern void func_002B60B0(u8 *, f32, f32, f32, f32);
extern void func_002A7470(void *, s32, s32, s32);

typedef struct StateData {
    u8 pad_0[97];
    u8 field_61;
    u8 field_62;
    u8 pad_63[3];
    u8 field_66;
    u8 pad_67[5];
    f32 field_6C;
    f32 field_70;
    f32 field_74;
    f32 field_78;
    f32 field_7C;
    u8 pad_80[60];
    u8 field_BC;
    u8 field_BD;
    u8 field_BE;
    u8 field_BF;
    u8 pad_C0[2];
    u8 field_C2;
    u8 field_C3;
    u8 pad_C4[2];
    u8 field_C6;
    u8 pad_C7[81];
    f32 field_118;
    u8 pad_11C[476];
    u8 * field_2F8;
} StateData;

/* Fires the object's emitter for the new state, doubles the object's rate, arms the two
   animation tables the state selects and hands the state to both owners. */
void func_L12_00412E50(u8 *a0, s32 a1, s32 a2, s32 a3) {
    StateData *q = *(StateData **)(a0 + 0x68);
    f32 f0, f1, f2, f3;
    u8 *owner;

    if (a1 == 12) {
        f0 = D_L12_001B17F4;
        f1 = D_L12_001B17F8;
        f2 = D_L12_001B1804;
        f3 = D_L12_001B1808;
        func_002B60B0(a0, f0 * 0.00027777778f, f1 * 0.016666668f,
            f2 * 4.8481375e-06f,
            f3 * 0.00029088824f);
        q->field_118 = q->field_118 * 2.0f;
    } else {
        f0 = D_L12_001B17FC;
        f1 = D_L12_001B1800;
        f2 = D_L12_001B1804;
        f3 = D_L12_001B1808;
        func_002B60B0(a0, f0 * 0.00027777778f, f1 * 0.016666668f,
            f2 * 4.8481375e-06f,
            f3 * 0.00029088824f);
        q->field_118 = q->field_118 * 2.0f;
    }
    if ((u32)(a1 - 13) < 3) {
        q->field_6C = 0;
        q->field_70 = 0;
        q->field_74 = 0;
        q->field_78 = 0;
        q->field_7C = 0;
        q->field_61 = 0xF;
        q->field_62 = 0xF;
        q->field_BC = 7;
        q->field_BD = 0x13;
        q->field_BE = 7;
        q->field_BF = 0x13;
        q->field_66 = 0xF;
        q->field_C2 = 7;
        q->field_C3 = 0x13;
        q->field_C6 = 1;
    } else if (a1 == 0x10) {
        q->field_74 = 0.0041666669f;
        q->field_62 = 0x11;
        q->field_C6 = 0;
        q->field_6C = 0.36666667f;
        q->field_70 = 0.1166666746f;
        q->field_78 = 0.008333334f;
        q->field_7C = 0.0041666669f;
        q->field_61 = 0x12;
        q->field_66 = 0x14;
        q->field_BC = 5;
        q->field_BD = 9;
        q->field_BE = 4;
        q->field_BF = 7;
        q->field_C2 = 0xA;
        q->field_C3 = 0x11;
    }
    if (*(u8 *)(a0 + 0x43) != a1)
        func_002A7470(a0, a1, a2, a3);
    owner = q->field_2F8;
    if (owner != 0 && owner[0x43] != a1)
        func_002A7470(owner, a1, a2, a3);
}
