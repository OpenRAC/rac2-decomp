#include "names.h"
/* func_PAL_L09_00408290, the PAL copy of func_L09_00403398: the same delta, where 0.033333335f becomes
   0.040000003f; 0.087266475f becomes 0.10471977f; 0.026179943f becomes 0.031415932f. */
#include "common.h"

extern s32 g_max_l09_group_id __attribute__((sda));
extern u8 *g_moby_record_table MACRO_ADDR;
extern u16 *g_track_entry_table[];

extern f32 g_dobbo_height_limit_offset __attribute__((sda));
extern f32 g_dobbo_height_base_offset __attribute__((sda));
extern f32 g_dobbo_height_top_offset __attribute__((sda));
extern f32 g_dobbo_height_blend_up __attribute__((sda));
extern f32 g_dobbo_height_blend_down __attribute__((sda));
extern f32 g_dobbo_separation_range __attribute__((sda));
extern u8 *g_hero_moby NOT_SDA;

extern void FastVecSub(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern f32 math_square(f32);
extern void math_update_wrapped_angle_offset(u8 *, void *, void *, f32, f32, f32);
extern void moby_scale_owner_words_by_angles(u8 *, void *, void *, f32, f32, f32);

/* Keeps the object at a smooth height above the ground and pushes it away from others in its group (PAL: 50 Hz rates). */
void dobbo_update_height_separation_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    f32 probe_pos[4] __attribute__((aligned(16)));
    f32 push[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    u8 *target_moby;
    u16 *track_ids;
    u8 *other;
    f32 goal_height, cur_height, len, weight;
    f32 height;

    *(f32 *)(state + 0x288) = *(f32 *)(moby + 0x18);
    if (moby[0x20] != 9 && moby[0x20] != 4) {
        height = *(f32 *)(state + 0x294) - 0.040000003f;
        *(f32 *)(state + 0x294) = height;
        qcopy(probe_pos, moby + 0x10);
        probe_pos[2] = height + (g_dobbo_height_top_offset - g_dobbo_height_base_offset);
        target_moby = *(u8 **)(state + 0x188);
        if (target_moby == 0 || (target_moby != g_hero_moby && *(s16 *)(target_moby + 0xAA) != 0xD57 &&
                       *(s16 *)(*(u8 **)(target_moby + 0x24) + 0x46) >= 11)) {
            goal_height = *(f32 *)(state + 0x288) + g_dobbo_height_base_offset;
            cur_height = *(f32 *)(state + 0x294);
            if (cur_height < goal_height)
                *(f32 *)(state + 0x294) = cur_height + (goal_height - cur_height) * g_dobbo_height_blend_up;
        }
        goal_height = *(f32 *)(state + 0x264) + g_dobbo_height_base_offset;
        cur_height = *(f32 *)(state + 0x294);
        if (cur_height < goal_height)
            *(f32 *)(state + 0x294) = cur_height + (goal_height - cur_height) * g_dobbo_height_blend_up;
        if (moby[0x20] >= 6 && moby[0x20] <= 8) {
            goal_height = *(f32 *)(*(u8 **)(state + 0x230) + 0x18) + g_dobbo_height_limit_offset;
            cur_height = *(f32 *)(state + 0x294);
            if (cur_height < goal_height)
                *(f32 *)(state + 0x294) = cur_height + (goal_height - cur_height) * g_dobbo_height_blend_down;
        }
        *(f32 *)(moby + 0x18) = *(f32 *)(state + 0x294);
        qzero_nc(push);
        track_ids = g_track_entry_table[moby[0x21]];
        for (;
             moby[0x21] != 0xFF && moby[0x21] <= g_max_l09_group_id && track_ids != 0 &&
             ((track_ids != 0 && (s16)track_ids[-1] >= 0) || track_ids == g_track_entry_table[moby[0x21]]);
             track_ids++) {
            other = g_moby_record_table + ((*track_ids & 0x7FFF) << 8);
            if (other == 0)
                break;
            FastVecSub(delta, moby + 0x10, other + 0x10);
            len = FastVecLength(delta);
            if (len > g_dobbo_separation_range)
                len = g_dobbo_separation_range;
            else if (len < 0.0f)
                len = 0.0f;
            weight = 1.0f - len / g_dobbo_separation_range;
            math_square(weight);
            vec_scale_to_length(delta, delta, len * weight);
            FastVecAdd(push, push, delta);
        }
        FastVecAdd(moby + 0x10, moby + 0x10, push);
        math_update_wrapped_angle_offset(moby, state + 0x278, state + 0x27C, 0.1f, 0.10471977f, *(f32 *)(moby + 0x18));
        moby_scale_owner_words_by_angles(moby, state + 0x280, state + 0x284, 0.13962635f, 0.031415932f, 0.031415932f);
    } else {
        *(f32 *)(state + 0x294) = *(f32 *)(moby + 0x18);
    }
}
