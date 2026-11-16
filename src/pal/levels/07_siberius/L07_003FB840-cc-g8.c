#include "names.h"
/* func_PAL_L07_003FB840, the PAL copy of func_L07_003F7048: the same C, where rename func_L07_003F7BF0 becomes func_PAL_L07_003FC408; rename func_L07_003F8780 becomes func_PAL_L07_003FCFE0; rename func_L00_002B9D60 becomes func_PAL_L00_002B9CD8; rename func_L07_003F80B8 becomes func_PAL_L07_003FC8D0; rename func_L07_003F9028 becomes func_PAL_L07_003FD928; rename func_L07_003F8908 becomes func_PAL_L07_003FD168; rename func_L07_003F9088 becomes func_PAL_L07_003FD988; rename func_002AEB60 becomes func_PAL_002AF6C0; rename func_L07_003F8CD0 becomes func_PAL_L07_003FD5D0; rename func_002A7470 becomes func_PAL_002A7E68; rename func_002A6C58 becomes func_PAL_002A7650; rename func_L07_003F8D90 becomes func_PAL_L07_003FD690; .... */
#include "common.h"

#define W(p,o) (*(s32 *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define F(p,o) (*(f32 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
extern u8 g_hero_position[] NOT_SDA;
extern u8 g_boss_started_flag NOT_SDA;
extern u8 g_boss_request_queue[] NOT_SDA;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 rest[0x40]; } PathRec;
extern PathRec *g_shooter_mount_table[] __attribute__((sda));
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern f32 g_boss_l07_turn_rate_2;
extern s32 g_boss_active_flag;
extern s32 g_boss_frame_offset;
extern s32 g_game_l07_mode_state;
extern f32 g_boss_float_param NOT_SDA;
extern s32 g_hero_mode NOT_SDA;
extern void UpdatePhasedDamageState_pal(u8 *);
extern void boss_setup_screen_effect_pal(u8 *);
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
extern void hero_reset_position_and_direction_pal(void *,void *,s32,s32);
extern void boss_move_toward_target_pal(u8 *,f32);
extern s32 flag_set_first_pending(u8 *);
extern void boss_select_idle_anim_pal(u8 *);
extern s32 enemy_choose_action_pal(u8 *);
extern void moby_start_timer_state(u8 *,s32,s32);
extern void moby_store_attached_pos(u8 *,void *);
extern s32 FloatToInt(f32);
extern int PlayMobySound(s32,s32,u8 *);
extern void boss_select_attack_anim_pal(u8 *);
extern s32 math_is_value_within_step_pal(u8 *,f32);
extern void boss_fire_beam_attack(u8 *);
extern void joint_query_pose_effect(u8 *);
extern void group_spawn_member_effect(u8 *);
extern void group_launch_members_pal(u8 *);
extern s32 math_fast_float_d(void *);
extern void anim_start_blended_pal(u8 *,s32,s32,s32);
extern f32 ApproachValue(f32 *,f32,f32);
extern void boss_reset_with_children(u8 *);
extern void SetDeathBits_pal(u8 *,s32,s32);
extern s32 coll_sweep_from_object(u8 *,void *,s32,f32,f32,f32,s32,s32,s32);
extern void path_reset_follower_to_point(u8 *);
extern void moby_mark_flag_and_append_to_list(s32);
extern void data_set_small_value_and_refresh(s32,s32);
extern void siberius_gun_update_aim_pal(u8 *);

/* Updates the boss. It runs the boss's states: waiting, intro, walking, several attacks, taking hits and the final death, and keeps its parts up to date every frame. */
void boss_update_pal(u8 *moby)
{
    f32 position[4];
    f32 rotation[4];
    u8 *vars = P(moby,0x68);
    UpdatePhasedDamageState_pal(moby);
    switch (moby[0x95]) {
    case 0:
    case 1:
        if (moby[0x20] != 3 && moby[0x20] != 11) boss_setup_screen_effect_pal(moby);
        if (moby[0x95] == 0) g_boss_l07_turn_rate_2 = 0.6981318f;
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
            g_boss_active_flag=1;
            if (!g_boss_started_flag) {
                if (req_push_queue(g_boss_request_queue,0x4f)) {
                    req_launch_queued(g_boss_request_queue);
                    moby_set_state(moby,2,-1);
                    goto start_path;
                }
            }
            boss_start_move_tier(moby,0,2);
            qcopy_nc(vars+0x3e0,g_shooter_mount_table[0][W(vars,0x174)].pos);
            F(vars,0x3e8)+=1.5f;
start_path:
            script_queue_keyed_request(W(vars,0x18c),-1);
        }
        break;
    case 2:
        if (!game_is_either_mode_two()) {
            g_boss_started_flag=1;
            vec_scale_to_length(position,(u8 *)&g_shooter_mount_table[0][W(vars,0x174)]+0x10,8.0f);
            FastVecAdd(position,position,g_shooter_mount_table[0][W(vars,0x174)].pos);
            qzero_nc(rotation);
            rotation[2]=mat_fast_helper_a(g_shooter_mount_table[0][W(vars,0x174)].pos[0]-position[0],g_shooter_mount_table[0][W(vars,0x174)].pos[1]-position[1]);
            hero_reset_position_and_direction_pal(position,rotation,0,1);
            boss_start_move_tier(moby,0,2);
            qcopy_nc(vars+0x3e0,g_shooter_mount_table[0][W(vars,0x174)].pos);
            F(vars,0x3e8)+=1.5f;
        }
        break;
    case 3:
        boss_move_toward_target_pal(moby,-1.0f);
        if (H(moby,0x96)>=101) moby_set_state(moby,4,-1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            boss_select_idle_anim_pal(moby);
            W(vars,0x42c)=50;
        }
        boss_move_toward_target_pal(moby,-1.0f);
        if (!W(vars,0x42c)) {
            W(vars,0x43c)=enemy_choose_action_pal(moby);
            moby_set_state(moby,5,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) boss_select_idle_anim_pal(moby);
        boss_move_toward_target_pal(moby,-1.0f);
        if (H(moby,0x96)==W(vars,0x444)-W(vars,0x448))
            moby_start_timer_state(P(vars,0x414),W(vars,0x448),W(vars,0x448)+10);
        else if (H(moby,0x96)==W(vars,0x444)-(((int)(g_boss_frame_offset) * 5 + 2) / 6))
            moby_store_attached_pos(moby,vars+0x140);
        else if (W(vars,0x444)<H(moby,0x96))
            moby_set_state(moby,W(vars,0x43c),-1);
        if (W(vars,0x43c)==7) {
            s32 frame = FloatToInt(38.083336f);
            if (H(moby,0x96)==W(vars,0x444)-frame) PlayMobySound(8,0,moby);
        }
        break;
    case 6: case 7: case 8: case 9:
        if (flag_set_first_pending(moby)) boss_select_attack_anim_pal(moby);
        boss_move_toward_target_pal(moby,-1.0f);
        if (moby[0x42]==moby[0x43]) {
            if (math_is_value_within_step_pal(moby,1.0f)) {
                switch (moby[0x20]) {
                case 7: boss_fire_beam_attack(moby); break;
                case 6: joint_query_pose_effect(moby); break;
                case 9: group_spawn_member_effect(moby); break;
                case 8: group_launch_members_pal(moby); break;
                }
            } else if (moby[0x60]&2) {
                if (math_fast_float_d(vars+0x438)) moby_set_state(moby,4,-1);
                else moby_set_state(moby,5,-1);
            }
        }
        break;
    case 10:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]!=7) anim_start_blended_pal(moby,7,0,17);
        }
        boss_move_toward_target_pal(moby,-1.0f);
        if (moby[0x60]&2) moby_set_state(moby,11,-1);
        break;
    case 11:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]!=4) anim_start_blended_pal(moby,4,0,17);
            F(vars,0x434)=1.3000001f;
        }
        boss_move_toward_target_pal(moby,F(vars,0x434));
        ApproachValue((f32 *)(vars+0x434),0.0f,0.008f);
        ApproachValue((f32 *)(vars+0x3e8),18.0f,0.040000003f);
        if (!moby[0x31]) {
            moby_set_state(moby,1,2);
            boss_reset_with_children(moby);
        }
        break;
    case 12:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43]!=7) anim_start_blended_pal(moby,7,0,17);
            F(vars,0x3e8)+=1.0f;
            W(vars,0x440)=500;
            if (F(vars,0x20)==0.0f && !moby[0x7f]) SetDeathBits_pal(moby,10,3);
        }
        boss_move_toward_target_pal(moby,-1.0f);
        if (F(vars,0x20)<=0.0f) {
            g_boss_float_param=40.0f;
            coll_sweep_from_object(moby,g_shooter_mount_table[0][W(vars,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
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
        if (req_push_queue(g_boss_request_queue,0x50)) {
            req_push_queue(g_boss_request_queue,0x51);
            req_push_queue(g_boss_request_queue,8);
            req_push_queue(g_boss_request_queue,0x52);
            req_launch_queued(g_boss_request_queue);
            moby_set_state(moby,14,-1);
        }
        break;
    case 14:
        if (((H(moby,0x34)^1)&1) && g_game_l07_mode_state==2) boss_reset_with_children(moby);
        coll_sweep_from_object(moby,g_shooter_mount_table[0][W(vars,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        if (!game_is_either_mode_two() && g_game_l07_mode_state!=2 && g_game_l07_mode_state!=1 && g_hero_mode!=20) {
            moby_mark_flag_and_append_to_list(8);
            data_set_small_value_and_refresh(8,1);
        }
        break;
    }
    siberius_gun_update_aim_pal(moby);
}
