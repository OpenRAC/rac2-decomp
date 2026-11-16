#include "common.h"

/* func_PAL_L12_00419BD8, the PAL copy of func_L12_00414C60: the same C, with the timer
   period scaled to 50 Hz and the per-frame steps at 0.02 and 0.04. */

extern f32 g_guard_hand_aim_speed __attribute__((sda));
extern s32 g_guard_attack_sequence_value __attribute__((sda));
extern f32 g_guard_near_distance __attribute__((sda));
extern f32 vec_distance_xy(void *, void *);
extern s32 FastDecTimer(void *);
extern s32 guard_is_line_of_sight_blocked(void *, s32, s32, s32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern char *moby_spawn_aimed_effect(void *, void *, f32, void *);

typedef struct { char pad[0x2F0]; u8 *slots[2]; } SlotVars;

/* Fires the helper object held in the guard's hand toward the target, while limiting how
   steeply it can aim up or down (PAL: 50 Hz timings). */
void guard_aim_hand_helper_at_target_pal(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    s32 near = 1;
    s32 side, shift;
    u8 *hand;
    f32 hand_pos[4] __attribute__((aligned(16)));
    f32 aim_vec[4] __attribute__((aligned(16)));
    if (!(vec_distance_xy(self+0x10, *(u8 **)(vars+0x200)+0x10) < g_guard_near_distance)) near=0;
    if (*(u8 **)(vars+0x2F8) == 0) return;
    if (!FastDecTimer(vars+0x2E4)) return;
    side = (*(u16 *)(self+0x96) / (((s32)g_guard_attack_sequence_value * 5 + 2) / 6)) & 1;
    shift = side ? 5 : 4;
    if ((*(u16 *)(*(u8 **)(vars+0x2F8)+0x7C) >> shift) & 1) {
        if (!guard_is_line_of_sight_blocked(self,1,0,*(u8 *)(vars+0x30D)!=0)) return;
        hand = ((SlotVars *)vars)->slots[side];
        if (hand && *(s16 *)(hand+0xAA)==0xD66 /* moby class 3430 */ && hand[0x20]!=0xFE && hand[0x20]!=0xFD) {
            *(u16 *)(vars+0x2E4)=((s32)g_guard_attack_sequence_value * 5 + 2) / 6;
            moby_transform_joint_to_world(((SlotVars *)vars)->slots[side],0,hand_pos);
            FastVecSub(aim_vec,vars+0x1F0,hand_pos);
            vec_scale_to_length(aim_vec,aim_vec,g_guard_hand_aim_speed * 0.020000001f);
            if (!near && !vars[0x30D]) {
                if (aim_vec[2] > 0.040000003f) aim_vec[2]=0.040000003f;
                else if (aim_vec[2] < -0.040000003f) aim_vec[2]=-0.040000003f;
            }
            vec_scale_to_length(aim_vec,aim_vec,g_guard_hand_aim_speed * 0.020000001f);
            moby_spawn_aimed_effect(self,aim_vec,(f32)vars[0x34],hand_pos);
        }
    } else *(u16 *)(vars+0x2E4)=((s32)g_guard_attack_sequence_value * 5 + 2) / 6;
}
