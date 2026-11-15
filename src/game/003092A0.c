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
    V_4198 *v;
} O_4198;
extern G_4198 g_hero_state;
extern s32 D_00138320;
extern s32 stub_empty_29(s32), math_fast_float_d(void *);
extern void moby_mark_spawned(void *), gfx_register_overlay_draw_callback(void *, void *);
extern void draw_joint_aligned_beam_effect(void), beam_spawn_trail_particles(void *);
/* Adapted from RAC1 update_beam_effect_lifecycle (OpenRAC, GPL-3.0). */
/* Switches the beam effect on and off depending on what the player is doing. It grows and shrinks while it is on. */
void beam_effect_update(void *p) {
    O_4198 *beam_obj = (O_4198 *)p;
    V_4198 *v = beam_obj->v;
    s32 want_active = 0;
    s32 hero_mode;

    if ((&g_hero_state)->i1338 == 3 || stub_empty_29(3) == 8) {
        if (beam_obj->state == 1 || beam_obj->state == 3) {
            hero_mode = (&g_hero_state)->i2294;
            if ((u32)(hero_mode - 0xB) < 4
                || (hero_mode == 0x1B && ((u8 *)(&g_hero_state)->p2290)[0x42] == ((u8 *)(&g_hero_state)->p2290)[0x43]
                    && (&g_hero_state)->fC38 >= 6.0f && (&g_hero_state)->fC38 <= 16.0f)) {
                if (!(&g_hero_state)->i49E) want_active = 1;
            }
            if ((&g_hero_state)->i2294 == 0x82 && (D_00138320 & 0x40)) want_active = 1;
            if ((&g_hero_state)->i2294 == 0x10) {
                if ((&g_hero_state)->i1B8 < 44) {
                    want_active = 1;
                }
            }
            if ((&g_hero_state)->i2294 == 0x21) {
                if ((&g_hero_state)->i1B8 < 15
                    || (33 < (&g_hero_state)->i1B8 && (&g_hero_state)->i34E != 0)) {
                    want_active = 1;
                }
            }
            if ((&g_hero_state)->i2294 == 8) want_active = 1;
            if ((&g_hero_state)->i2294 == 0x82) want_active = 1;
        }
    }
    switch (beam_obj->state) {
    case 0:
        beam_obj->f18 += 0.5f;
        beam_obj->state = 1;
        beam_obj->u30 = 0xFF;
        beam_obj->u34 |= 1;
        break;
    case 1:
        if ((stub_empty_29(3) != 3 && stub_empty_29(3) != 8) || !g_hero_state.i1314) {
            moby_mark_spawned(beam_obj);
        } else if (want_active != 0) {
            beam_obj->state = 2;
            v->i0 = 2;
            v->f30 = 0.0125f / 2;
            v->f34 = 0.2f / 2;
            v->f38 = 0.05f / 2;
            v->f3C = 0.025f / 2;
            v->f20 = 0.0f;
            v->f24 = 0.0f;
            v->f28 = 0.0f;
            v->f2C = 0.0f;
        }
        break;
    case 2:
        v->f20 += v->f30;
        v->f24 += v->f34;
        v->f28 += v->f38;
        v->f2C += v->f3C;
        v->i8 = (&g_hero_state)->i1310;
        gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect, beam_obj);
        if (math_fast_float_d(v) != 0) {
            beam_obj->state = 3;
            v->f20 = 0.0125f;
            v->f24 = 0.2f;
            v->f28 = 0.05f;
            v->iC = 0;
            v->f2C = 0.025f;
        }
        break;
    case 3:
        v->i8 = (&g_hero_state)->i1310;
        gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect, beam_obj);
        if (want_active == 0) {
            beam_obj->state = 4;
            v->i0 = 8;
            v->f30 = 0.0125f / 8;
            v->f34 = 0.2f / 8;
            v->f38 = 0.05f / 8;
            v->f3C = 0.025f / 8;
        } else {
            v->f20 = 0.0125f;
            beam_spawn_trail_particles(beam_obj);
        }
        break;
    case 4:
        if (math_fast_float_d(v) != 0) {
            beam_obj->state = 1;
        } else {
            v->f20 -= v->f30;
            v->f24 -= v->f34;
            v->f28 -= v->f38;
            v->f2C -= v->f3C;
            v->i8 = (&g_hero_state)->i1310;
            gfx_register_overlay_draw_callback(draw_joint_aligned_beam_effect, beam_obj);
        }
        break;
    }
}
