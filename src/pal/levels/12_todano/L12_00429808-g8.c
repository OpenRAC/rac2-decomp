/* func_PAL_L12_00429808, the PAL copy of func_L12_00424370: the same C at 50 Hz, with its timers, turn rates and blend counts rescaled. */

#include "common.h"

typedef struct { u8 pad0[0x20]; f32 f20; u16 f24; u8 pad26[0xA]; f32 f30;
    u8 pad34[0x1C]; f32 f50, f54, f58, f5c, f60;
    u8 pad64[0x1C]; f32 f80, f84; s32 f88; u8 pad8c[0x10]; void *f9c;
} L12PathState;

#define SI(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define SF(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define SH(p,o) (*(u16 *)((u8 *)(p)+(o)))
extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags, g_wanderer_flag_table;
extern u8 g_moby_nibble_table[], g_moby_group_flags[], g_hero_prev_position[], g_wanderer_ground_hit[];
extern u8 g_collected_item_flags[] __attribute__((sda));
typedef struct { u8 pad[0x80]; f32 pos[4]; u8 pad90[0x530]; u8 *target; } PlayerState;
extern PlayerState g_hero_state;
extern s32 g_current_map_index MACRO_ADDR;
extern s32 D_001A79F0_gp SDATA(D_001A79F0);
extern u8 *g_moby_list_start MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern s32 *g_path_zone_table[];
extern s32 g_frame_l12_counter MACRO_ADDR;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern f32 g_wanderer_speed_scale __attribute__((sda)), g_wanderer_timer_rate __attribute__((sda)), g_wanderer_slow_move_rate __attribute__((sda)), g_wanderer_fast_move_rate __attribute__((sda));
extern f32 g_wanderer_spin_rate __attribute__((sda)), g_wanderer_smooth_target __attribute__((sda));
extern s32 g_wanderer_pulse_colors[] __attribute__((sda));
extern void moby_mark_spawned(void *), helper_clear_states(void *), beam_restore_child_collision(void *);
extern s32 helper_has_live_object(void *);
extern f32 fast_vec_dist(void *, void *), vec_distance_xy(void *, void *);
extern void moby_update_ground_check(void *), moby_set_state(void *,s32,s32);
extern void anim_start_blended_pal(void *,s32,s32,s32);
extern s32 math_random_int_below(s32), flag_set_first_pending(void *), flag_is_third_pending_set(void *);
extern f32 math_step_int_toward_target(s32 *,s32,s32);
extern void moby_set_controller_speed_limits(void *,f32,f32,f32,f32);
extern s32 moby_l01_turn_toward_target_pal(void *,void *), path_pick_random_visible_point(void *,s32), path_find_visible_point(void *);
extern void spark_timer_restart_sound_pal(void *), path_find_nearby_point_at_hero_height(void *);
extern s32 CollLine(void *,void *,s32,void *,s32);
extern f32 FastVecDot(void *,void *), mat_fast_helper_a(f32,f32);
extern s32 moby_start_effect_from_entry(void *,f32);
extern void pushable_moby_update_pal(void *,void *,f32,f32,f32,s32);
extern u8 *CreateMoby(s32);
extern s32 moby_pack_handle(void *), IsPointInCuboid(void *,s32);
extern void FastVecAdd(void *,void *,void *), vec_fast_normalize_helper(void *,void *,f32);
extern f32 vec_length_xy(void *);
extern s32 coll_test_point(void *,s32,void *,f32);
extern void vec_scale_to_length(void *,void *,f32), vec_fast_normalize(void *,void *,void *), FastVecScale(void *,void *,f32), vec_clear_128(void *);
extern f32 FastAddRotations(f32,f32);
extern s32 PulseColor(s32,s32,f32);
extern void value_set_and_smooth_pal(void *,f32 *,f32,s32,s32);

/* Updates an enemy that wanders between path points, walks or runs to a new point, and turns to face the hero when it is targeted (PAL: 50 Hz timings). */
void path_wandering_enemy_update_pal(u8 *self)
{
    f32 old_pos[4], ray_from[4], ray_to[4];
    u8 *vars = *(u8 **)(self+0x68);
    s32 *path;
    s32 had_helper0=0, had_helper1=0;
    u16 object_id=SH(self,0xb2);
    if (g_object_flags.flags[(s16)object_id]) { moby_mark_spawned(self); return; }
    { s32 flags=g_moby_nibble_table[((s16)object_id>>1)+(g_current_map_index<<10)];
    flags = ((object_id & 1) ? flags >> 4 : flags) & 7;
    if(flags) { moby_mark_spawned(self); return; } }
    path=g_path_zone_table[SI(vars,0x298)];
    if (helper_has_live_object(g_moby_list_start+(SI(vars,0x2c4)<<8))) had_helper0=1;
    if (helper_has_live_object(g_moby_list_start+(SI(vars,0x2c8)<<8))) had_helper1=1;
    if (SI(vars,0x2c4)!=-1) beam_restore_child_collision(g_moby_list_start+(SI(vars,0x2c4)<<8));
    if (SI(vars,0x2c8)!=-1) beam_restore_child_collision(D_L12_001B2E9C_gp+(SI(vars,0x2c8)<<8));
    SF(self,0x2c)=SF(*(u8 **)(self+0x24),0x24)*g_wanderer_speed_scale;
    qcopy(old_pos,self+0x10);
    if (self[0x31] && fast_vec_dist(self+0x10,g_hero_prev_position)<24.0f) {
        moby_update_ground_check(self); self[0x6f]=22;
    }
    if (!self[0x95]) {
        if (self==g_hero_state.target) {
            moby_set_state(self,5,1); qcopy(vars+0x150,self+0x10);
        } else {
            if (vec_distance_xy(self+0x10,g_hero_state.pos)<SF(vars,0x178)) SH(self,0x34)|=0x1000;
            else SH(self,0x34)&=0xefff;
        }
    }
    switch(self[0x20]) {
    case 0:
        ((L12PathState *)vars)->f24=1;
        ((L12PathState *)vars)->f20=1.0f; ((L12PathState *)vars)->f30=1.5f; ((L12PathState *)vars)->f84=0.05f;
        ((L12PathState *)vars)->f54=0.2f; ((L12PathState *)vars)->f50=0.825f; ((L12PathState *)vars)->f58=0.4f; ((L12PathState *)vars)->f5c=0.4f;
        ((L12PathState *)vars)->f60=1.5707964897155762f; ((L12PathState *)vars)->f80=0.523598849773407f;
        ((L12PathState *)vars)->f88|=1; ((L12PathState *)vars)->f9c=vars+0x190;
        SI(vars,0x2b0)=0; qcopy(self+0x10,(u8 *)path+0x10);
        self[0x20]=1; self[0x30]=128; SH(self,0x34)|=0x1000;
        break;
    case 1:
        if (flag_set_first_pending(self)) {
            s32 anim=self[0x43]; if(anim!=math_random_int_below(2)) anim_start_blended_pal(self,math_random_int_below(2),0,8);
            SI(vars,0x2b8)=vec_distance_xy(self+0x10,(SI(vars,0x2b4)*16+0x10)+(u8 *)path)>24.0f?25:150;
        }
        if (SI(vars,0x2b8)<SH(self,0x96)) {
            if (SI(vars,0x2b0)<SI(vars,0x2b4) && vec_distance_xy(self+0x10,(SI(vars,0x2b4)*16+0x10)+(u8 *)path)>20.0f)
                moby_set_state(self,4,-1);
            else moby_set_state(self,2,-1);
        }
        break;
    case 4:
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=5) anim_start_blended_pal(self,5,0,17);
            math_step_int_toward_target((s32 *)(vars+0x2b0),SI(vars,0x2b4),1);
            { f32 speed=g_wanderer_fast_move_rate;
              moby_set_controller_speed_limits(self,0.0032000002f,speed*0.020000001f,0.005026549f,0.25132746f); }
        }
        if(SI(vars,0x2b0)<SI(vars,0x2b4)) {
            qcopy(ray_from,self+0x10); ray_from[2]+=0.5f;
            qcopy(ray_to,(SI(vars,0x2b0)*16)+(u8 *)path+0x20); ray_to[2]+=0.5f;
            if(!CollLine(ray_from,ray_to,2,self,0)) SI(vars,0x2b0)++;
        }
        moby_l01_turn_toward_target_pal(self,(SI(vars,0x2b0)*16+0x10)+(u8 *)path);
        if(vec_distance_xy(self+0x10,(SI(vars,0x2b4)*16+0x10)+(u8 *)path)<8.0f) moby_set_state(self,1,-1);
        break;
    case 2:
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=4) anim_start_blended_pal(self,4,0,17);
            { s32 next=path_pick_random_visible_point(self,1);
            f32 rate=g_wanderer_slow_move_rate*0.020000001f; SI(vars,0x2b0)=next;
            moby_set_controller_speed_limits(self,0.0016000001f,rate,0.0012566373f,0.12566373f); }
            SI(vars,0x2b8)=vec_distance_xy(self+0x10,(SI(vars,0x2b4)*16+0x10)+(u8 *)path)>24.0f?750:250;
        }
        if((moby_l01_turn_toward_target_pal(self,(SI(vars,0x2b0)*16+0x10)+(u8 *)path)&128)||SH(self,0x96)>=250) moby_set_state(self,1,-1);
        break;
    case 3:
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=5) anim_start_blended_pal(self,5,0,17);
            { s32 next=path_pick_random_visible_point(self,0);
            f32 rate=g_wanderer_fast_move_rate*0.020000001f; SI(vars,0x2b0)=next;
            moby_set_controller_speed_limits(self,0.0056000003f,rate,0.005026549f,0.5026549f); }
        }
        if(moby_l01_turn_toward_target_pal(self,(SI(vars,0x2b0)*16+0x10)+(u8 *)path)&128) SI(vars,0x2b0)=path_pick_random_visible_point(self,1);
        if(SH(self,0x96)>=350) moby_set_state(self,1,-1);
        break;
    case 5: {
        f32 dot;
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=7) anim_start_blended_pal(self,7,0,8);
            SI(vars,0x2c0)=0;
        }
        dot=FastVecDot(self+0xc0,vars+0x140);
        if(dot< -0.040000003f) { if(self[0x43]!=10) anim_start_blended_pal(self,10,0,8); }
        else if(dot>0.040000003f) { if(self[0x43]!=9) anim_start_blended_pal(self,9,0,8); }
        else { if(self[0x43]!=7) anim_start_blended_pal(self,7,0,8); }
        moby_start_effect_from_entry(self,mat_fast_helper_a(g_hero_state.pos[0]-SF(self,0x10),g_hero_state.pos[1]-SF(self,0x14)));
        if(helper_has_live_object(g_moby_list_start+(SI(vars,0x2c4)<<8))) had_helper0=1;
        if(helper_has_live_object(g_moby_list_start+(SI(vars,0x2c8)<<8))) had_helper1=1;
        if(SI(vars,0x2c4)!=-1) beam_restore_child_collision(g_moby_list_start+(SI(vars,0x2c4)<<8));
        if(SI(vars,0x2c8)!=-1) beam_restore_child_collision(D_L12_001B2E9C_gp+(SI(vars,0x2c8)<<8));
        pushable_moby_update_pal(self,vars+0x140,0.7f,0.5f,0.1f,SI(vars,0x360));
        spark_timer_restart_sound_pal(self);
        if(flag_is_third_pending_set(self)) moby_set_state(self,6,-1);
        else if(self!=g_hero_state.target) { moby_set_state(self,3,0); goto choose_path; }
        break;
    }
    case 6:
        if(flag_set_first_pending(self)) { if(self[0x43]!=10) anim_start_blended_pal(self,10,0,8); }
        moby_start_effect_from_entry(self,mat_fast_helper_a(g_hero_state.pos[0]-SF(self,0x10),g_hero_state.pos[1]-SF(self,0x14)));
        spark_timer_restart_sound_pal(self);
        break;
    case 8:
        if(flag_set_first_pending(self)) {
            u8 *child=CreateMoby(0x9bb);
            if(child) {
                u8 *child_vars;
                *(u8 **)(child+0xb8)=self; child[0x30]=255; qcopy(child+0x10,self+0x10);
                child_vars=*(u8 **)(child+0x68); *(u8 **)(child_vars+0x10)=self;
                SI(child_vars,0x20)=SH(self,0x34); SI(child_vars,0x30)=moby_pack_handle(self);
                SI(self,0x98)=0; SH(self,0x34)=(SH(self,0x34)|0x41)&0xefff;
            }
        }
        SI(self,0x98)=0; SH(self,0x34)=(SH(self,0x34)|0x41)&0xefff;
        if(SH(self,0x96)>50) {
            g_wanderer_flag_table.flags[*(s16 *)(self+0xb2)]=self[0xb0]+2;
            { s32 saveid=self[0xb0];
            if(saveid==255 || (!(g_collected_item_flags[(u8)saveid]&128) && (g_moby_group_flags[(u8)saveid+(D_001A79F0_gp<<4)]&128)))
                g_object_flags.flags[*(s16 *)(self+0xb2)]=saveid+2; }
            moby_mark_spawned(self); return;
        }
        break;
    case 7:
        FastVecAdd(self+0x10,self+0x10,vars+0x2a0);
        SF(vars,0x2a8)-=g_wanderer_timer_rate*0.00040000002f;
        spark_timer_restart_sound_pal(self);
        if(IsPointInCuboid(self+0x10,SI(vars,0x29c))) {
            f32 length_xy=vec_length_xy(vars+0x2a0);
            if(length_xy>0.020000001f) length_xy=0.020000001f;
            vec_fast_normalize_helper(vars+0x2a0,vars+0x2a0,length_xy);
        }
        qcopy(ray_from,self+0x10); ray_from[2]+=0.5f;
        if(coll_test_point(ray_from,0,self,0.5f)) {
            qcopy(self+0x10,g_wanderer_ground_hit); SF(self,0x18)-=0.5f;
            vec_scale_to_length(g_wanderer_ground_hit+0x10,g_wanderer_ground_hit+0x10,1.0f);
            if(FastVecDot(g_wanderer_ground_hit+0x10,vars+0x2a0)<0.0f) {
                vec_fast_normalize(vars+0x2a0,vars+0x2a0,g_wanderer_ground_hit+0x10);
                FastVecScale(vars+0x2a0,vars+0x2a0,0.5f);
            }
            if(SF(g_wanderer_ground_hit,0x18)>=0.95f) {
                SH(self,0x34)|=0x1000; moby_set_state(self,1,0);
                qcopy(vars+0x150,self+0x10); vec_clear_128(vars+0x140);
            choose_path:
                SI(vars,0x2b0)=path_find_visible_point(self);
            }
        }
        break;
    }
    if(SI(vars,0x2c4)!=-1 && !had_helper0) helper_clear_states(g_moby_list_start+(SI(vars,0x2c4)<<8));
    if(SI(vars,0x2c8)!=-1 && !had_helper1) helper_clear_states(g_moby_list_start+(SI(vars,0x2c8)<<8));
    if(!(g_frame_l12_counter&15)) path_find_nearby_point_at_hero_height(self);
    if(self[0x31]) {
        SF(vars,0x2bc)=FastAddRotations(SF(vars,0x2bc),g_wanderer_spin_rate*0.0003490659f);
        SI(self,0x78)=PulseColor(g_wanderer_pulse_colors[0],g_wanderer_pulse_colors[1],SF(vars,0x2bc));
    }
    SH(self,0x96)++;
    qcopy(vars+0x2d0,self+0x10);
    value_set_and_smooth_pal(self,(f32 *)(vars+0x2e0),g_wanderer_smooth_target,2,1);
}
