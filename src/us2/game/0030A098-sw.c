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
extern void draw_joint_aligned_beam_effect(void), beam_spawn_trail_particles(void *);

/* Adapted from RAC1 update_beam_effect_lifecycle (OpenRAC, GPL-3.0). */
void beam_effect_update_us2(void *object) {
    O_4198 *moby = (O_4198 *)object;
    V_4198 *vars = moby->vars;
    s32 flag = 0;
    s32 hero_move_state;

    if ((&g_hero_state)->i1338 == 3 || stub_empty_29(3) == 8) {
        if (moby->state == 1 || moby->state == 3) {
            hero_move_state = (&g_hero_state)->i2294;
            if ((u32)(hero_move_state - 0xB) < 4
                || (hero_move_state == 0x1B && ((u8 *)(&g_hero_state)->p2290)[0x42] == ((u8 *)(&g_hero_state)->p2290)[0x43]
                    && (&g_hero_state)->fC38 >= 6.0f && (&g_hero_state)->fC38 <= 16.0f)) {
                if (!(&g_hero_state)->i49E) flag = 1;
            }
            if ((&g_hero_state)->i2294 == 0x82 && (g_pad_pressed_flags & 0x40)) flag = 1;
            if ((&g_hero_state)->i2294 == 0x10) {
                if ((&g_hero_state)->i1B8 < 44) {
                    flag = 1;
                }
            }
            if ((&g_hero_state)->i2294 == 0x21) {
                if ((&g_hero_state)->i1B8 < 15
                    || (33 < (&g_hero_state)->i1B8 && (&g_hero_state)->i34E != 0)) {
                    flag = 1;
                }
            }
            if ((&g_hero_state)->i2294 == 8) flag = 1;
            if ((&g_hero_state)->i2294 == 0x82) flag = 1;
        }
    }
    switch (moby->state) {
    case 0:
        moby->f18 += 0.5f;
        moby->state = 1;
        moby->u30 = 0xFF;
        moby->u34 |= 1;
        break;
    case 1:
        if ((stub_empty_29(3) != 3 && stub_empty_29(3) != 8) || !g_hero_state.i1314) {
            moby_mark_spawned(moby);
        } else if (flag != 0) {
            moby->state = 2;
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
        gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect, moby);
        if (math_fast_float_d(vars) != 0) {
            moby->state = 3;
            vars->f20 = 0.0125f;
            vars->f24 = 0.2f;
            vars->f28 = 0.05f;
            vars->iC = 0;
            vars->f2C = 0.025f;
        }
        break;
    case 3:
        vars->i8 = (&g_hero_state)->i1310;
        gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect, moby);
        if (flag == 0) {
            moby->state = 4;
            vars->i0 = 8;
            vars->f30 = 0.0125f / 8;
            vars->f34 = 0.2f / 8;
            vars->f38 = 0.05f / 8;
            vars->f3C = 0.025f / 8;
        } else {
            vars->f20 = 0.0125f;
            beam_spawn_trail_particles(moby);
        }
        break;
    case 4:
        if (math_fast_float_d(vars) != 0) {
            moby->state = 1;
        } else {
            vars->f20 -= vars->f30;
            vars->f24 -= vars->f34;
            vars->f28 -= vars->f38;
            vars->f2C -= vars->f3C;
            vars->i8 = (&g_hero_state)->i1310;
            gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect, moby);
        }
        break;
    }
}
