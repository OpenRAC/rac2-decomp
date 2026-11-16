#include "include_asm.h"

#include "common.h"
extern f32 g_guard_anim_rate_a __attribute__((sda));
extern f32 g_guard_anim_rate_b __attribute__((sda));
extern f32 g_guard_switch_rate_a __attribute__((sda));
extern f32 g_guard_switch_rate_b __attribute__((sda));
extern f32 g_guard_anim_rate_c __attribute__((sda));
extern f32 g_guard_anim_rate_d __attribute__((sda));
extern void moby_set_controller_speed_limits(u8 *, f32, f32, f32, f32);
extern void anim_start_blended_pal(void *, s32, s32, s32);
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
void guard_switch_animation_pal(u8 *moby, s32 anim_id, s32 anim_flags, s32 blend_frames) {
    StateData *vars = *(StateData **)(moby + 0x68);
    f32 rate_a, rate_b, rate_c, rate_d;
    u8 *owner;

    if (anim_id == 12) {
        rate_a = g_guard_anim_rate_a;
        rate_b = g_guard_anim_rate_b;
        rate_c = g_guard_anim_rate_c;
        rate_d = g_guard_anim_rate_d;
        moby_set_controller_speed_limits(moby, rate_a * 0.00040000002f, rate_b * 0.020000001f,
            rate_c * 6.981318e-06f,
            rate_d * 0.0003490659f);
        vars->field_118 = vars->field_118 * 2.0f;
    } else {
        rate_a = g_guard_switch_rate_a;
        rate_b = g_guard_switch_rate_b;
        rate_c = g_guard_anim_rate_c;
        rate_d = g_guard_anim_rate_d;
        moby_set_controller_speed_limits(moby, rate_a * 0.00040000002f, rate_b * 0.020000001f,
            rate_c * 6.981318e-06f,
            rate_d * 0.0003490659f);
        vars->field_118 = vars->field_118 * 2.0f;
    }
    if ((u32)(anim_id - 13) < 3) {
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
    } else if (anim_id == 0x10) {
        vars->field_74 = 0.006f;
        vars->field_62 = 0x11;
        vars->field_C6 = 0;
        vars->field_6C = 0.44000003f;
        vars->field_70 = 0.14000002f;
        vars->field_78 = 0.012f;
        vars->field_7C = 0.006f;
        vars->field_61 = 0x12;
        vars->field_66 = 0x14;
        vars->field_BC = 5;
        vars->field_BD = 9;
        vars->field_BE = 4;
        vars->field_BF = 7;
        vars->field_C2 = 0xA;
        vars->field_C3 = 0x11;
    }
    if (*(u8 *)(moby + 0x43) != anim_id)
        anim_start_blended_pal(moby, anim_id, anim_flags, blend_frames);
    owner = vars->field_2F8;
    if (owner != 0 && owner[0x43] != anim_id)
        anim_start_blended_pal(owner, anim_id, anim_flags, blend_frames);
}
