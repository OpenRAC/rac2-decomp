#include "include_asm.h"

#include "common.h"
typedef struct {
    char p0[0x1B8];
    s32 i1B8;
    char p1BC[0x34E - 0x1BC];
    s16 i34E;
    char p350[0x49E - 0x350];
    u8 i49E;
    char p49F[0xC38 - 0x49F];
    f32 fC38;
    char pC3C[0x1310 - 0xC3C];
    s32 i1310, i1314;
    char p1318[0x1338 - 0x1318];
    s32 i1338;
    char p133C[0x2290 - 0x133C];
    void *p2290;
    s32 i2294;
} G_4198;
typedef struct {
    s32 i0;
    char pad4[4];
    s32 i8;
    s32 iC;
    char pad10[0x10];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
} V_4198;
typedef struct {
    char pad00[0x18];
    f32 f18;
    char pad1C[4];
    u8 state;
    char pad21[0xF];
    u8 u30;
    char pad31[3];
    u16 u34;
    char pad36[0x32];
    V_4198 *vars;
} O_4198;
extern G_4198 g_hero_state;
extern s32 g_pad_pressed_flags;
extern s32 stub_empty_29(s32), math_fast_float_d(void *);
extern void moby_mark_spawned(void *), gfx_register_overlay_draw_callback(void *, void *);
extern void draw_joint_aligned_beam_effect_pal(void), beam_spawn_trail_particles_pal(void *);
extern s32 ref_PAL_0030A560_00(s32), math_fast_float_d(void *);

/* Adapted from RAC1 update_beam_effect_lifecycle (OpenRAC, GPL-3.0). */
void beam_effect_update_pal(void *obj) {
    O_4198 *beam = (O_4198 *)obj;
    V_4198 *vars = beam->vars;
    s32 flag = 0;
    s32 hero_move;

    if ((&g_hero_state)->i1338 == 3 || ref_PAL_0030A560_00(3) == 8) {
        if (beam->state == 1 || beam->state == 3) {
            hero_move = (&g_hero_state)->i2294;
            if ((u32)(hero_move - 0xB) < 4
                || (hero_move == 0x1B && ((u8 *)(&g_hero_state)->p2290)[0x42] == ((u8 *)(&g_hero_state)->p2290)[0x43]
                    && (&g_hero_state)->fC38 >= 6.0f && (&g_hero_state)->fC38 <= 16.0f)) {
                if (!(&g_hero_state)->i49E) flag = 1;
            }
            if ((&g_hero_state)->i2294 == 0x82 && (g_pad_pressed_flags & 0x40)) flag = 1;
            if ((&g_hero_state)->i2294 == 0x10) {
                if ((&g_hero_state)->i1B8 < 37) {
                    flag = 1;
                }
            }
            if ((&g_hero_state)->i2294 == 0x21) {
                if ((&g_hero_state)->i1B8 < 12
                    || (27 < (&g_hero_state)->i1B8 && (&g_hero_state)->i34E != 0)) {
                    flag = 1;
                }
            }
            if ((&g_hero_state)->i2294 == 8) flag = 1;
            if ((&g_hero_state)->i2294 == 0x82) flag = 1;
        }
    }
    switch (beam->state) {
    case 0:
        beam->f18 += 0.5f;
        beam->state = 1;
        beam->u30 = 0xFF;
        beam->u34 |= 1;
        break;
    case 1:
        if ((ref_PAL_0030A560_00(3) != 3 && ref_PAL_0030A560_00(3) != 8) || !g_hero_state.i1314) {
            moby_mark_spawned(beam);
        } else if (flag != 0) {
            beam->state = 2;
            vars->i0 = 2;
            vars->f30 = 0.0125f / 2;
            vars->f34 = 0.2f / 2;
            vars->f38 = 0.05f / 2;
            vars->f3C = 0.025f / 2;
            vars->f20 = 0.0f;
            vars->f24 = 0.0f;
            vars->f28 = 0.0f;
            vars->f2C = 0.0f;
        }
        break;
    case 2:
        vars->f20 += vars->f30;
        vars->f24 += vars->f34;
        vars->f28 += vars->f38;
        vars->f2C += vars->f3C;
        vars->i8 = (&g_hero_state)->i1310;
        gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect_pal, beam);
        if (math_fast_float_d(vars) != 0) {
            beam->state = 3;
            vars->f20 = 0.0125f;
            vars->f24 = 0.2f;
            vars->f28 = 0.05f;
            vars->iC = 0;
            vars->f2C = 0.025f;
        }
        break;
    case 3:
        vars->i8 = (&g_hero_state)->i1310;
        gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect_pal, beam);
        if (flag == 0) {
            beam->state = 4;
            vars->i0 = 7;
            vars->f30 = 0.0017857144f;
            vars->f34 = 0.02857143f;
            vars->f38 = 0.0071428576f;
            vars->f3C = 0.0035714288f;
        } else {
            vars->f20 = 0.0125f;
            beam_spawn_trail_particles_pal(beam);
        }
        break;
    case 4:
        if (math_fast_float_d(vars) != 0) {
            beam->state = 1;
        } else {
            vars->f20 -= vars->f30;
            vars->f24 -= vars->f34;
            vars->f28 -= vars->f38;
            vars->f2C -= vars->f3C;
            vars->i8 = (&g_hero_state)->i1310;
            gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect_pal, beam);
        }
        break;
    }
}
