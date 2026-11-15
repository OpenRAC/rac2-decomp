#include "common.h"
extern f32 D_L12_001B1810 __attribute__((sda));
extern s32 D_L12_001B1828 __attribute__((sda));
extern f32 D_L12_001B1814 __attribute__((sda));
extern f32 vec_distance_xy(void *, void *);
extern s32 FastDecTimer(void *);
extern s32 guard_is_line_of_sight_blocked(void *, s32, s32, s32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void moby_spawn_aimed_effect(void *, void *, f32, void *);

typedef struct { char pad[0x2F0]; u8 *slots[2]; } SlotVars;

/* Fires the helper object held in the guard's hand toward the target, while limiting how
   steeply it can aim up or down. */
void guard_aim_hand_helper_at_target(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 near = 1;
    s32 side, shift;
    u8 *hand;
    f32 handPos[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    if (!(vec_distance_xy(moby+0x10, *(u8 **)(vars+0x200)+0x10) < D_L12_001B1814)) near=0;
    if (*(u8 **)(vars+0x2F8) == 0) return;
    if (!FastDecTimer(vars+0x2E4)) return;
    side = (*(u16 *)(moby+0x96) / D_L12_001B1828) & 1;
    shift = side ? 5 : 4;
    if ((*(u16 *)(*(u8 **)(vars+0x2F8)+0x7C) >> shift) & 1) {
        if (!guard_is_line_of_sight_blocked(moby,1,0,*(u8 *)(vars+0x30D)!=0)) return;
        hand = ((SlotVars *)vars)->slots[side];
        if (hand && *(s16 *)(hand+0xAA)==0xD66 /* moby class 3430 */ && hand[0x20]!=0xFE && hand[0x20]!=0xFD) {
            *(u16 *)(vars+0x2E4)=D_L12_001B1828;
            moby_transform_joint_to_world(((SlotVars *)vars)->slots[side],0,handPos);
            FastVecSub(delta,vars+0x1F0,handPos);
            vec_scale_to_length(delta,delta,D_L12_001B1810 * 0.016666668f);
            if (!near && !vars[0x30D]) {
                if (delta[2] > 0.033333335f) delta[2]=0.033333335f;
                else if (delta[2] < -0.033333335f) delta[2]=-0.033333335f;
            }
            vec_scale_to_length(delta,delta,D_L12_001B1810 * 0.016666668f);
            moby_spawn_aimed_effect(moby,delta,(f32)vars[0x34],handPos);
        }
    } else *(u16 *)(vars+0x2E4)=D_L12_001B1828;
}
