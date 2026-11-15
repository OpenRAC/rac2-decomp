#include "include_asm.h"

#include "common.h"
#define W(p,o) (*(s32 *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define F(p,o) (*(f32 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
extern u8 g_hero_position[] NOT_SDA;
extern u8 D_0013962A NOT_SDA;
extern u8 D_L07_001BF400[] NOT_SDA;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 rest[0x40]; } PathRec;
extern PathRec *D_L07_001B23CC[] __attribute__((sda));
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern f32 D_L07_001B2CB8;
extern s32 D_L07_001B104C;
extern s32 D_L07_001B1044;
extern s32 D_L07_001A8F00;
extern f32 D_0018C2C4 NOT_SDA;
extern s32 D_0018C0BC NOT_SDA;
extern void UpdatePhasedDamageState(u8 *);
extern void boss_setup_screen_effect(u8 *);
extern void cam_end_override(u8 *);
extern s32 IsPointInCuboid(void *,s32);
extern s32 req_push_queue(void *,s32);
extern void req_launch_queued(void *);
extern void moby_set_state(u8 *,s32,s32);
extern void boss_start_move_tier(u8 *,s32,s32);
extern void script_queue_keyed_request(s32,s32);
extern s32 game_is_either_mode_two(void);
extern void vec_scale_to_length(void *,void *,f32);
extern void FastVecAdd(void *,void *,void *);
extern f32 mat_fast_helper_a(f32,f32);
extern void hero_reset_position_and_direction(void *,void *,s32,s32);
extern void boss_move_toward_target(u8 *,f32);
extern s32 flag_set_first_pending(u8 *);
extern void boss_select_idle_anim(u8 *);
extern s32 enemy_choose_action(u8 *);
extern void moby_start_timer_state(u8 *,s32,s32);
extern void moby_store_attached_pos(u8 *,void *);
extern s32 FloatToInt(f32);
extern void PlayMobySound(s32,s32,u8 *);
extern void boss_select_attack_anim(u8 *);
extern s32 func_US2_002AF9C8(u8 *,f32);
extern void boss_fire_beam_attack(u8 *);
extern void joint_query_pose_effect(u8 *);
extern void group_spawn_member_effect(u8 *);
extern void group_launch_members(u8 *);
extern s32 math_fast_float_d(void *);
extern void anim_start_blended(u8 *,s32,s32,s32);
extern f32 ApproachValue(f32 *,f32,f32);
extern void boss_reset_with_children(u8 *);
extern void func_US2_002A7AA8(u8 *,s32,s32);
extern s32 coll_sweep_from_object(u8 *,void *,s32,f32,f32,f32,s32,s32,s32);
extern void path_reset_follower_to_point(u8 *);
extern void moby_mark_flag_and_append_to_list(s32);
extern void data_set_small_value_and_refresh(s32,s32);
extern void siberius_gun_update_aim(u8 *);

void func_US2_L07_003F83E8(u8 *a)
{
    f32 pos[4];
    f32 rot[4];
    u8 *s = P(a,0x68);
    UpdatePhasedDamageState(a);
    switch (a[0x95]) {
    case 0:
    case 1:
        if (a[0x20] != 3 && a[0x20] != 11) boss_setup_screen_effect(a);
        if (a[0x95] == 0) D_L07_001B2CB8 = 0.6981318f;
        break;
    case 2:
        if (P(s,0x450)) {
            cam_end_override(P(s,0x450));
            P(s,0x450)=0;
        }
        break;
    }
    switch (a[0x20]) {
    case 1:
        if (IsPointInCuboid(g_hero_position,W(s,0x170))) {
            D_L07_001B104C=1;
            if (!D_0013962A) {
                if (req_push_queue(D_L07_001BF400,0x4f)) {
                    req_launch_queued(D_L07_001BF400);
                    moby_set_state(a,2,-1);
                    goto start_path;
                }
            }
            boss_start_move_tier(a,0,2);
            qcopy_nc(s+0x3e0,D_L07_001B23CC[0][W(s,0x174)].pos);
            F(s,0x3e8)+=1.5f;
start_path:
            script_queue_keyed_request(W(s,0x18c),-1);
        }
        break;
    case 2:
        if (!game_is_either_mode_two()) {
            D_0013962A=1;
            vec_scale_to_length(pos,(u8 *)&D_L07_001B23CC[0][W(s,0x174)]+0x10,8.0f);
            FastVecAdd(pos,pos,D_L07_001B23CC[0][W(s,0x174)].pos);
            qzero_nc(rot);
            rot[2]=mat_fast_helper_a(D_L07_001B23CC[0][W(s,0x174)].pos[0]-pos[0],D_L07_001B23CC[0][W(s,0x174)].pos[1]-pos[1]);
            hero_reset_position_and_direction(pos,rot,0,1);
            boss_start_move_tier(a,0,2);
            qcopy_nc(s+0x3e0,D_L07_001B23CC[0][W(s,0x174)].pos);
            F(s,0x3e8)+=1.5f;
        }
        break;
    case 3:
        boss_move_toward_target(a,-1.0f);
        if (H(a,0x96)>=121) moby_set_state(a,4,-1);
        break;
    case 4:
        if (flag_set_first_pending(a)) {
            boss_select_idle_anim(a);
            W(s,0x42c)=60;
        }
        boss_move_toward_target(a,-1.0f);
        if (!W(s,0x42c)) {
            W(s,0x43c)=enemy_choose_action(a);
            moby_set_state(a,5,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(a)) boss_select_idle_anim(a);
        boss_move_toward_target(a,-1.0f);
        if (H(a,0x96)==W(s,0x444)-W(s,0x448))
            moby_start_timer_state(P(s,0x414),W(s,0x448),W(s,0x448)+10);
        else if (H(a,0x96)==W(s,0x444)-D_L07_001B1044)
            moby_store_attached_pos(a,s+0x140);
        else if (W(s,0x444)<H(a,0x96))
            moby_set_state(a,W(s,0x43c),-1);
        if (W(s,0x43c)==7) {
            s32 n = FloatToInt(45.3f);
            if (H(a,0x96)==W(s,0x444)-n) PlayMobySound(8,0,a);
        }
        break;
    case 6: case 7: case 8: case 9:
        if (flag_set_first_pending(a)) boss_select_attack_anim(a);
        boss_move_toward_target(a,-1.0f);
        if (a[0x42]==a[0x43]) {
            if (func_US2_002AF9C8(a,1.0f)) {
                switch (a[0x20]) {
                case 7: boss_fire_beam_attack(a); break;
                case 6: joint_query_pose_effect(a); break;
                case 9: group_spawn_member_effect(a); break;
                case 8: group_launch_members(a); break;
                }
            } else if (a[0x60]&2) {
                if (math_fast_float_d(s+0x438)) moby_set_state(a,4,-1);
                else moby_set_state(a,5,-1);
            }
        }
        break;
    case 10:
        if (flag_set_first_pending(a)) {
            if (a[0x43]!=7) anim_start_blended(a,7,0,20);
        }
        boss_move_toward_target(a,-1.0f);
        if (a[0x60]&2) moby_set_state(a,11,-1);
        break;
    case 11:
        if (flag_set_first_pending(a)) {
            if (a[0x43]!=4) anim_start_blended(a,4,0,20);
            F(s,0x434)=1.0833334f;
        }
        boss_move_toward_target(a,F(s,0x434));
        ApproachValue((f32 *)(s+0x434),0.0f,0.0055555557f);
        ApproachValue((f32 *)(s+0x3e8),18.0f,0.033333335f);
        if (!a[0x31]) {
            moby_set_state(a,1,2);
            boss_reset_with_children(a);
        }
        break;
    case 12:
        if (flag_set_first_pending(a)) {
            if (a[0x43]!=7) anim_start_blended(a,7,0,20);
            F(s,0x3e8)+=1.0f;
            W(s,0x440)=600;
            if (F(s,0x20)==0.0f && !a[0x7f]) func_US2_002A7AA8(a,10,3);
        }
        boss_move_toward_target(a,-1.0f);
        if (F(s,0x20)<=0.0f) {
            D_0018C2C4=40.0f;
            coll_sweep_from_object(a,D_L07_001B23CC[0][W(s,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        }
        if (a[0x60]&2) {
            if (F(s,0x20)<=0.0f) moby_set_state(a,13,2);
            else {
                switch(W(s,0x420)) {
                case 3: break;
                case 4: path_reset_follower_to_point(g_moby_l07_array[0]+(W(s,0x178)<<8)); break;
                case 5: path_reset_follower_to_point(g_moby_l07_array[0]+(W(s,0x17c)<<8)); break;
                }
                moby_set_state(a,4,-1);
                W(s,0x440)=0;
            }
        }
        break;
    case 13:
        if (req_push_queue(D_L07_001BF400,0x50)) {
            req_push_queue(D_L07_001BF400,0x51);
            req_push_queue(D_L07_001BF400,8);
            req_push_queue(D_L07_001BF400,0x52);
            req_launch_queued(D_L07_001BF400);
            moby_set_state(a,14,-1);
        }
        break;
    case 14:
        if (((H(a,0x34)^1)&1) && D_L07_001A8F00==2) boss_reset_with_children(a);
        coll_sweep_from_object(a,D_L07_001B23CC[0][W(s,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        if (!game_is_either_mode_two() && D_L07_001A8F00!=2 && D_L07_001A8F00!=1 && D_0018C0BC!=20) {
            moby_mark_flag_and_append_to_list(8);
            data_set_small_value_and_refresh(8,1);
        }
        break;
    }
    siberius_gun_update_aim(a);
}
