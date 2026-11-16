#include "common.h"

typedef struct {
    u8 pad0[0x28], field28, field29, field2a, pad2b[3], field2e, pad2f;
    float field30;
    u8 pad34[0x14], field48, pad49, field4a, pad4b[0x35];
    u8 field80[16], pad90[0x24];
    int fieldb4, fieldb8, fieldbc;
    u8 padc0[8];
    int fieldc8;
    u8 padcc[4];
    float fieldd0, fieldd4;
    int *fieldd8;
    u8 fielddc, fielddd, padde[2];
    int fielde0;
    u8 pade4[4];
    int fielde8;
    u8 padec[4];
    int fieldf0;
} OozlaSpawnState;

extern s32 FloatToInt(f32);
extern float path_l01_compute_segment_lengths(u32);
extern void anim_start_immediate(u8 *, s32, s32);
extern void moby_set_state(u8 *, s32, s32);
extern int g_oozla_intro_stage[] __attribute__((sda));
extern u32 g_path_l01_table[];
extern u8 *g_moby_l01_table MACRO_ADDR;

/* Sets up the swamp monster arm when it appears, then starts its idle or attack animation. */
void swamp_monster_arm_init(u8 *moby)
{
    OozlaSpawnState *vars = *(OozlaSpawnState **)(moby + 0x68);

    vars->field48 = FloatToInt(5.0f);
    vars->field4a = FloatToInt(32.0f);
    vars->field29 = 1;
    *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 2.5f;
    qcopy(vars->field80, moby + 0x10);
    if (!g_oozla_intro_stage[0] && moby[0x21] != 255)
        *vars->fieldd8 = 0;
    vars->field30 = 2.0f;
    vars->field2a = 8;
    vars->field28 = 3;
    vars->field2e = 3;
    vars->fieldbc = 0;
    if (vars->fieldb8 != -1)
        path_l01_compute_segment_lengths(g_path_l01_table[vars->fieldb8]);
    vars->fieldf0 = vars->fielde8;
    if (vars->fielddd)
        *(u16 *)(moby + 0x34) |= 0x8000;
    if (vars->fieldb4 != -1) {
        vars->fieldf0 = vars->fielde0;
        if ((g_moby_l01_table + (vars->fieldb4 << 8)) &&
            (g_moby_l01_table + (vars->fieldb4 << 8))[0x20] != 254 &&
            (g_moby_l01_table + (vars->fieldb4 << 8))[0x20] != 253) {
            *(u16 *)(moby + 0x32) = 0x3FF;
            moby[0x30] = 255;
            if (vars->fieldd0 > 0.0f)
                *(float *)(moby + 0x18) = vars->fieldd0;
            if (vars->fieldc8)
                anim_start_immediate(moby, 8, 0);
            else
                anim_start_immediate(moby, 5, 0);
            moby_set_state(moby, 0, 1);
        } else {
            vars->fieldb4 = -1;
        }
    }
    if (vars->fieldb4 == -1) {
        if (vars->fieldd4 > 0.0f)
            *(float *)(moby + 0x18) = vars->fieldd4;
        vars->fieldbc = 120;
        anim_start_immediate(moby, 0, 0);
        *(float *)(moby + 0x48) = 0.0f;
        *(u16 *)(moby + 0x34) &= 0xEFFF;
        moby_set_state(moby, 0, 4);
    }
}
