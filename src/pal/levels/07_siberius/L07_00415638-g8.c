#include "include_asm.h"
#include "common.h"
extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 g_unused_float_param __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 g_boss_cam_distance __attribute__((sda));
extern f32 g_boss_cam_height __attribute__((sda));
extern f32 g_bomb_scale __attribute__((sda));
extern f32 g_beam_fade_in_rate __attribute__((sda));
extern f32 g_beam_fade_out_rate __attribute__((sda));
extern f32 g_beam_spin_rate __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    u8 *state;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} SibObj;
typedef struct {
    u8 pad00[0xCC];
    s32 groupCC;
    s32 groupD0;
} SibGroups;
extern f32 g_hero_reset_offset_z;
extern u8 g_hero_l07_reset_position __attribute__((sda));
extern u16 **g_group_l07_id_lists;
extern u8 *g_joint_record_table;
extern u8 *g_matrix_l07_record_table;
extern s32 g_ship_phase_state;
extern void hero_reset_position_and_direction(void *obj, void *pos, s32 a2, s32 a3);
extern void gfx_setup_scale_record(s32 id, s32 a1);

/* Switches the object to its second phase. */
void boss_enter_second_phase_pal(SibObj *a0)
{
    f32 arg[4];
    f32 v[4];
    SibGroups *state;
    u16 *p;
    u16 *q;
    u8 *e;

    *(TI128 *)v = 0;
    v[2] = g_hero_reset_offset_z;
    *(TI128 *)arg = *(TI128 *)v;
    state = (SibGroups *)a0->state;
    hero_reset_position_and_direction(&g_hero_l07_reset_position, arg, 0, 1);
    a0->flags34 |= 2;
    a0->f98 = 0;
    for (p = g_group_l07_id_lists[state->groupD0];
         p != 0 && ((s16)p[-1] >= 0 || p == g_group_l07_id_lists[state->groupD0]) &&
         (e = g_joint_record_table + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] &= 0xFB;
    }
    for (p = g_group_l07_id_lists[state->groupCC];
         p != 0 && ((s16)p[-1] >= 0 || p == g_group_l07_id_lists[state->groupCC]) &&
         (e = g_joint_record_table + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] |= 4;
    }
    for (q = g_group_l07_id_lists[state->groupCC];
         q != 0 && ((s16)q[-1] >= 0 || q == g_group_l07_id_lists[state->groupCC]) &&
         (e = g_matrix_l07_record_table + ((*q & 0x7FFF) << 6)) != 0;
         q++) {
        *(f32 *)(e + 0x38) -= 100.0f;
        gfx_setup_scale_record(*q & 0x7FFF, 1);
    }
    g_ship_phase_state = 2;
}
