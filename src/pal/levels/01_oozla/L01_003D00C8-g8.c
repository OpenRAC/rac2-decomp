#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad_0[0x28], field_28, field_29, field_2a, pad_2b[3], field_2e, pad_2f;
    float field_30;
    u8 pad_34[0x14], field_48, pad_49, field_4a, pad_4b[0x35];
    u8 field_80[16], pad_90[0x24];
    int field_b4, field_b8, field_bc;
    u8 pad_c0[8];
    int field_c8;
    u8 pad_cc[4];
    float field_d0, field_d4;
    int *field_d8;
    u8 field_dc, field_dd, pad_de[2];
    int field_e0;
    u8 pad_e4[4];
    int field_e8;
    u8 pad_ec[4];
    int field_f0;
} OozlaSpawnState;
extern s32 FloatToInt(f32);
extern float path_l01_compute_segment_lengths(u32);
extern void anim_start_immediate(u8 *, s32, s32);
extern void moby_set_state(u8 *, s32, s32);
extern int g_oozla_intro_stage[] __attribute__((sda));
extern u32 g_path_l01_table[];
extern u8 *g_moby_l01_table MACRO_ADDR;

/* Sets up the swamp monster arm when it appears, then starts its idle or attack animation (PAL). */
void swamp_monster_arm_init_pal(u8 *moby)
{
    OozlaSpawnState *vars = *(OozlaSpawnState **)(moby + 0x68);

    vars->field_48 = FloatToInt(5.0f);
    vars->field_4a = FloatToInt(32.0f);
    vars->field_29 = 1;
    *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 2.5f;
    qcopy(vars->field_80, moby + 0x10);
    if (!g_oozla_intro_stage[0] && moby[0x21] != 255)
        *vars->field_d8 = 0;
    vars->field_30 = 2.0f;
    vars->field_2a = 8;
    vars->field_28 = 3;
    vars->field_2e = 3;
    vars->field_bc = 0;
    if (vars->field_b8 != -1)
        path_l01_compute_segment_lengths(g_path_l01_table[vars->field_b8]);
    vars->field_f0 = vars->field_e8;
    if (vars->field_dd)
        *(u16 *)(moby + 0x34) |= 0x8000;
    if (vars->field_b4 != -1) {
        vars->field_f0 = vars->field_e0;
        if ((g_moby_l01_table + (vars->field_b4 << 8)) &&
            (g_moby_l01_table + (vars->field_b4 << 8))[0x20] != 254 &&
            (g_moby_l01_table + (vars->field_b4 << 8))[0x20] != 253) {
            *(u16 *)(moby + 0x32) = 0x3FF;
            moby[0x30] = 255;
            if (vars->field_d0 > 0.0f)
                *(float *)(moby + 0x18) = vars->field_d0;
            if (vars->field_c8)
                anim_start_immediate(moby, 8, 0);
            else
                anim_start_immediate(moby, 5, 0);
            moby_set_state(moby, 0, 1);
        } else {
            vars->field_b4 = -1;
        }
    }
    if (vars->field_b4 == -1) {
        if (vars->field_d4 > 0.0f)
            *(float *)(moby + 0x18) = vars->field_d4;
        vars->field_bc = 100;
        anim_start_immediate(moby, 0, 0);
        *(float *)(moby + 0x48) = 0.0f;
        *(u16 *)(moby + 0x34) &= 0xEFFF;
        moby_set_state(moby, 0, 4);
    }
}
