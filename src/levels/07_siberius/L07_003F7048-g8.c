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
extern s32 req_launch_queued(void *);
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
extern int PlayMobySound(s32,s32,u8 *);
extern void boss_select_attack_anim(u8 *);
extern s32 math_is_value_within_step(u8 *,f32);
extern void boss_fire_beam_attack(u8 *);
extern void joint_query_pose_effect(u8 *);
extern void group_spawn_member_effect(u8 *);
extern void group_launch_members(u8 *);
extern s32 math_fast_float_d(void *);
extern void anim_start_blended(u8 *,s32,s32,s32);
extern f32 ApproachValue(f32 *,f32,f32);
extern void boss_reset_with_children(u8 *);
extern void SetDeathBits(u8 *,s32,s32);
extern s32 coll_sweep_from_object(u8 *,void *,s32,f32,f32,f32,s32,s32,s32);
extern void path_reset_follower_to_point(u8 *);
extern void moby_mark_flag_and_append_to_list(s32);
extern void data_set_small_value_and_refresh(s32,s32);
extern void siberius_gun_update_aim(u8 *);

/* Updates the boss. It runs the boss's states: waiting, intro, walking, several attacks, taking hits and the final death, and keeps its parts up to date every frame. */
void boss_update(u8 *moby)
{
    f32 pos[4];
    f32 rot[4];
    u8 *vars = P(moby,0x68);
    UpdatePhasedDamageState(moby);
    switch (moby[0x95]) {
    case 0:
    case 1:
        if (moby[0x20] != 3 && moby[0x20] != 11) boss_setup_screen_effect(moby);
        if (moby[0x95] == 0) D_L07_001B2CB8 = 0.6981318f;
        break;
    case 2:
        if (P(vars,0x450)) {
            cam_end_override(P(vars,0x450));
            P(vars,0x450)=0;
        }
        break;
    }
    switch (moby[0x20]) {
    case 1:
        if (IsPointInCuboid(g_hero_position,W(vars,0x170))) {
            D_L07_001B104C=1;
            if (!D_0013962A) {
                if (req_push_queue(D_L07_001BF400,0x4f)) {
                    req_launch_queued(D_L07_001BF400);
                    moby_set_state(moby,2,-1);
                    goto start_path;
                }
            }
            boss_start_move_tier(moby,0,2);
            qcopy_nc(vars+0x3e0,D_L07_001B23CC[0][W(vars,0x174)].pos);
            F(vars,0x3e8)+=1.5f;
start_path:
            script_queue_keyed_request(W(vars,0x18c),-1);
        }
        break;
    case 2:
        if (!game_is_either_mode_two()) {
            D_0013962A=1;
            vec_scale_to_length(pos,(u8 *)&D_L07_001B23CC[0][W(vars,0x174)]+0x10,8.0f);
            FastVecAdd(pos,pos,D_L07_001B23CC[0][W(vars,0x174)].pos);
            qzero_nc(rot);
            rot[2]=mat_fast_helper_a(D_L07_001B23CC[0][W(vars,0x174)].pos[0]-pos[0],D_L07_001B23CC[0][W(vars,0x174)].pos[1]-pos[1]);
            hero_reset_position_and_direction(pos,rot,0,1);
            boss_start_move_tier(moby,0,2);
            qcopy_nc(vars+0x3e0,D_L07_001B23CC[0][W(vars,0x174)].pos);
            F(vars,0x3e8)+=1.5f;
        }
        break;
    case 3:
        boss_move_toward_target(moby,-1.0f);
        if (H(moby,0x96)>=121) moby_set_state(moby,4,-1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            boss_select_idle_anim(moby);
            W(vars,0x42c)=60;
        }
        boss_move_toward_target(moby,-1.0f);
        if (!W(vars,0x42c)) {
            W(vars,0x43c)=enemy_choose_action(moby);
            moby_set_state(moby,5,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) boss_select_idle_anim(moby);
        boss_move_toward_target(moby,-1.0f);
        if (H(moby,0x96)==W(vars,0x444)-W(vars,0x448))
            moby_start_timer_state(P(vars,0x414),W(vars,0x448),W(vars,0x448)+10);
        else if (H(moby,0x96)==W(vars,0x444)-D_L07_001B1044)
            moby_store_attached_pos(moby,vars+0x140);
        else if (W(vars,0x444)<H(moby,0x96))
            moby_set_state(moby,W(vars,0x43c),-1);
        if (W(vars,0x43c)==7) {
            s32 n = FloatToInt(45.3f);
            if (H(moby,0x96)==W(vars,0x444)-n) PlayMobySound(8,0,moby);
        }
        break;
    case 6: case 7: case 8: case 9:
        if (flag_set_first_pending(moby)) boss_select_attack_anim(moby);
        boss_move_toward_target(moby,-1.0f);
        if (moby[0x42]==moby[0x43]) {
            if (math_is_value_within_step(moby,1.0f)) {
                switch (moby[0x20]) {
                case 7: boss_fire_beam_attack(moby); break;
                case 6: joint_query_pose_effect(moby); break;
                case 9: group_spawn_member_effect(moby); break;
                case 8: group_launch_members(moby); break;
                }
            } else if (moby[0x60]&2) {
                if (math_fast_float_d(vars+0x438)) moby_set_state(moby,4,-1);
                else moby_set_state(moby,5,-1);
            }
        }
        break;
    case 10:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]!=7) anim_start_blended(moby,7,0,20);
        }
        boss_move_toward_target(moby,-1.0f);
        if (moby[0x60]&2) moby_set_state(moby,11,-1);
        break;
    case 11:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]!=4) anim_start_blended(moby,4,0,20);
            F(vars,0x434)=1.0833334f;
        }
        boss_move_toward_target(moby,F(vars,0x434));
        ApproachValue((f32 *)(vars+0x434),0.0f,0.0055555557f);
        ApproachValue((f32 *)(vars+0x3e8),18.0f,0.033333335f);
        if (!moby[0x31]) {
            moby_set_state(moby,1,2);
            boss_reset_with_children(moby);
        }
        break;
    case 12:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]!=7) anim_start_blended(moby,7,0,20);
            F(vars,0x3e8)+=1.0f;
            W(vars,0x440)=600;
            if (F(vars,0x20)==0.0f && !moby[0x7f]) SetDeathBits(moby,10,3);
        }
        boss_move_toward_target(moby,-1.0f);
        if (F(vars,0x20)<=0.0f) {
            D_0018C2C4=40.0f;
            coll_sweep_from_object(moby,D_L07_001B23CC[0][W(vars,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        }
        if (moby[0x60]&2) {
            if (F(vars,0x20)<=0.0f) moby_set_state(moby,13,2);
            else {
                switch(W(vars,0x420)) {
                case 3: break;
                case 4: path_reset_follower_to_point(g_moby_l07_array[0]+(W(vars,0x178)<<8)); break;
                case 5: path_reset_follower_to_point(g_moby_l07_array[0]+(W(vars,0x17c)<<8)); break;
                }
                moby_set_state(moby,4,-1);
                W(vars,0x440)=0;
            }
        }
        break;
    case 13:
        if (req_push_queue(D_L07_001BF400,0x50)) {
            req_push_queue(D_L07_001BF400,0x51);
            req_push_queue(D_L07_001BF400,8);
            req_push_queue(D_L07_001BF400,0x52);
            req_launch_queued(D_L07_001BF400);
            moby_set_state(moby,14,-1);
        }
        break;
    case 14:
        if (((H(moby,0x34)^1)&1) && D_L07_001A8F00==2) boss_reset_with_children(moby);
        coll_sweep_from_object(moby,D_L07_001B23CC[0][W(vars,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        if (!game_is_either_mode_two() && D_L07_001A8F00!=2 && D_L07_001A8F00!=1 && D_0018C0BC!=20) {
            moby_mark_flag_and_append_to_list(8);
            data_set_small_value_and_refresh(8,1);
        }
        break;
    }
    siberius_gun_update_aim(moby);
}
