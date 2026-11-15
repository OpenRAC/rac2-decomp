#include "common.h"

/* The two rate pairs the state table selects and the four scales the emitter applies. */
extern f32 D_L12_001B17F4 __attribute__((sda));
extern f32 D_L12_001B17F8 __attribute__((sda));
extern f32 D_L12_001B17FC __attribute__((sda));
extern f32 D_L12_001B1800 __attribute__((sda));
extern f32 D_L12_001B1804 __attribute__((sda));
extern f32 D_L12_001B1808 __attribute__((sda));

extern void moby_set_controller_speed_limits(u8 *, f32, f32, f32, f32);
extern void anim_start_blended(void *, s32, s32, s32);

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
void guard_switch_animation(u8 *moby, s32 animId, s32 animFlags, s32 blendFrames) {
    StateData *vars = *(StateData **)(moby + 0x68);
    f32 rate0, rate1, rate2, rate3;
    u8 *owner;

    if (animId == 12) {
        rate0 = D_L12_001B17F4;
        rate1 = D_L12_001B17F8;
        rate2 = D_L12_001B1804;
        rate3 = D_L12_001B1808;
        moby_set_controller_speed_limits(moby, rate0 * 0.00027777778f, rate1 * 0.016666668f,
            rate2 * 4.8481375e-06f,
            rate3 * 0.00029088824f);
        vars->field_118 = vars->field_118 * 2.0f;
    } else {
        rate0 = D_L12_001B17FC;
        rate1 = D_L12_001B1800;
        rate2 = D_L12_001B1804;
        rate3 = D_L12_001B1808;
        moby_set_controller_speed_limits(moby, rate0 * 0.00027777778f, rate1 * 0.016666668f,
            rate2 * 4.8481375e-06f,
            rate3 * 0.00029088824f);
        vars->field_118 = vars->field_118 * 2.0f;
    }
    if ((u32)(animId - 13) < 3) {
        vars->field_6C = 0;
        vars->field_70 = 0;
        vars->field_74 = 0;
        vars->field_78 = 0;
        vars->field_7C = 0;
        vars->field_61 = 0xF;
        vars->field_62 = 0xF;
        vars->field_BC = 7;
        vars->field_BD = 0x13;
        vars->field_BE = 7;
        vars->field_BF = 0x13;
        vars->field_66 = 0xF;
        vars->field_C2 = 7;
        vars->field_C3 = 0x13;
        vars->field_C6 = 1;
    } else if (animId == 0x10) {
        vars->field_74 = 0.0041666669f;
        vars->field_62 = 0x11;
        vars->field_C6 = 0;
        vars->field_6C = 0.36666667f;
        vars->field_70 = 0.1166666746f;
        vars->field_78 = 0.008333334f;
        vars->field_7C = 0.0041666669f;
        vars->field_61 = 0x12;
        vars->field_66 = 0x14;
        vars->field_BC = 5;
        vars->field_BD = 9;
        vars->field_BE = 4;
        vars->field_BF = 7;
        vars->field_C2 = 0xA;
        vars->field_C3 = 0x11;
    }
    if (*(u8 *)(moby + 0x43) != animId)
        anim_start_blended(moby, animId, animFlags, blendFrames);
    owner = vars->field_2F8;
    if (owner != 0 && owner[0x43] != animId)
        anim_start_blended(owner, animId, animFlags, blendFrames);
}
