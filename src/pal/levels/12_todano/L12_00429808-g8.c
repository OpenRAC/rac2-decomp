/* func_PAL_L12_00429808, the PAL copy of func_L12_00424370: the same C at 50 Hz, with its timers, turn rates and blend counts rescaled. */

#include "common.h"

typedef struct { u8 pad0[0x20]; f32 f20; u16 f24; u8 pad26[0xA]; f32 f30;
    u8 pad34[0x1C]; f32 f50, f54, f58, f5c, f60;
    u8 pad64[0x1C]; f32 f80, f84; s32 f88; u8 pad8c[0x10]; void *f9c;
} L12PathState;

#define SI(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define SF(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define SH(p,o) (*(u16 *)((u8 *)(p)+(o)))
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0, D_L12_0021E180;
extern u8 D_0019B4A8[], D_0019B2E8[], D_L12_001B9E00[], D_L12_001C0270[];
extern u8 D_L12_001B2CE0[] __attribute__((sda));
typedef struct { u8 pad[0x80]; f32 pos[4]; u8 pad90[0x530]; u8 *target; } PlayerState;
extern PlayerState g_hero_state;
extern s32 g_current_map_index MACRO_ADDR;
extern s32 D_001A79F0_gp SDATA(D_001A79F0);
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern s32 *D_L12_001FEAC0[];
extern s32 D_L12_001B29C8 MACRO_ADDR;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern f32 D_L12_001B20A0 __attribute__((sda)), D_L12_001B20A4 __attribute__((sda)), D_L12_001B20A8 __attribute__((sda)), D_L12_001B20AC __attribute__((sda));
extern f32 D_L12_001B20B0 __attribute__((sda)), D_L12_001B20C8 __attribute__((sda));
extern s32 D_L12_001B20B8[] __attribute__((sda));
extern void moby_mark_spawned(void *), helper_clear_states(void *), beam_restore_child_collision(void *);
extern s32 helper_has_live_object(void *);
extern f32 fast_vec_dist(void *, void *), vec_distance_xy(void *, void *);
extern void moby_update_ground_check(void *), moby_set_state(void *,s32,s32);
extern void func_PAL_002A7E68(void *,s32,s32,s32);
extern s32 math_random_int_below(s32), flag_set_first_pending(void *), flag_is_third_pending_set(void *);
extern f32 math_step_int_toward_target(s32 *,s32,s32);
extern void moby_set_controller_speed_limits(void *,f32,f32,f32,f32);
extern s32 func_PAL_L01_00323068(void *,void *), path_pick_random_visible_point(void *,s32), path_find_visible_point(void *);
extern void func_PAL_L12_0042A8E0(void *), path_find_nearby_point_at_hero_height(void *);
extern s32 CollLine(void *,void *,s32,void *,s32);
extern f32 FastVecDot(void *,void *), mat_fast_helper_a(f32,f32);
extern s32 moby_start_effect_from_entry(void *,f32);
extern void func_PAL_L01_0031C9C0(void *,void *,f32,f32,f32,s32);
extern u8 *CreateMoby(s32);
extern s32 moby_pack_handle(void *), IsPointInCuboid(void *,s32);
extern void FastVecAdd(void *,void *,void *), vec_fast_normalize_helper(void *,void *,f32);
extern f32 vec_length_xy(void *);
extern s32 coll_test_point(void *,s32,void *,f32);
extern void vec_scale_to_length(void *,void *,f32), vec_fast_normalize(void *,void *,void *), FastVecScale(void *,void *,f32), vec_clear_128(void *);
extern f32 FastAddRotations(f32,f32);
extern s32 PulseColor(s32,s32,f32);
extern void func_PAL_002B14F8(void *,f32 *,f32,s32,s32);

void func_PAL_L12_00429808(u8 *self)
{
    f32 oldpos[4], from[4], to[4];
    u8 *st = *(u8 **)(self+0x68);
    s32 *path;
    s32 was0=0, was1=0;
    u16 id=SH(self,0xb2);
    if (D_L12_0021EDF0.flags[(s16)id]) { moby_mark_spawned(self); return; }
    { s32 flags=D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)];
    flags = ((id & 1) ? flags >> 4 : flags) & 7;
    if(flags) { moby_mark_spawned(self); return; } }
    path=D_L12_001FEAC0[SI(st,0x298)];
    if (helper_has_live_object(D_L12_001B2E9C+(SI(st,0x2c4)<<8))) was0=1;
    if (helper_has_live_object(D_L12_001B2E9C+(SI(st,0x2c8)<<8))) was1=1;
    if (SI(st,0x2c4)!=-1) beam_restore_child_collision(D_L12_001B2E9C+(SI(st,0x2c4)<<8));
    if (SI(st,0x2c8)!=-1) beam_restore_child_collision(D_L12_001B2E9C_gp+(SI(st,0x2c8)<<8));
    SF(self,0x2c)=SF(*(u8 **)(self+0x24),0x24)*D_L12_001B20A0;
    qcopy(oldpos,self+0x10);
    if (self[0x31] && fast_vec_dist(self+0x10,D_L12_001B9E00)<24.0f) {
        moby_update_ground_check(self); self[0x6f]=22;
    }
    if (!self[0x95]) {
        if (self==g_hero_state.target) {
            moby_set_state(self,5,1); qcopy(st+0x150,self+0x10);
        } else {
            if (vec_distance_xy(self+0x10,g_hero_state.pos)<SF(st,0x178)) SH(self,0x34)|=0x1000;
            else SH(self,0x34)&=0xefff;
        }
    }
    switch(self[0x20]) {
    case 0:
        ((L12PathState *)st)->f24=1;
        ((L12PathState *)st)->f20=1.0f; ((L12PathState *)st)->f30=1.5f; ((L12PathState *)st)->f84=0.05f;
        ((L12PathState *)st)->f54=0.2f; ((L12PathState *)st)->f50=0.825f; ((L12PathState *)st)->f58=0.4f; ((L12PathState *)st)->f5c=0.4f;
        ((L12PathState *)st)->f60=1.5707964897155762f; ((L12PathState *)st)->f80=0.523598849773407f;
        ((L12PathState *)st)->f88|=1; ((L12PathState *)st)->f9c=st+0x190;
        SI(st,0x2b0)=0; qcopy(self+0x10,(u8 *)path+0x10);
        self[0x20]=1; self[0x30]=128; SH(self,0x34)|=0x1000;
        break;
    case 1:
        if (flag_set_first_pending(self)) {
            s32 anim=self[0x43]; if(anim!=math_random_int_below(2)) func_PAL_002A7E68(self,math_random_int_below(2),0,8);
            SI(st,0x2b8)=vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)>24.0f?25:150;
        }
        if (SI(st,0x2b8)<SH(self,0x96)) {
            if (SI(st,0x2b0)<SI(st,0x2b4) && vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)>20.0f)
                moby_set_state(self,4,-1);
            else moby_set_state(self,2,-1);
        }
        break;
    case 4:
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=5) func_PAL_002A7E68(self,5,0,17);
            math_step_int_toward_target((s32 *)(st+0x2b0),SI(st,0x2b4),1);
            { f32 speed=D_L12_001B20AC;
              moby_set_controller_speed_limits(self,0.0032000002f,speed*0.020000001f,0.005026549f,0.25132746f); }
        }
        if(SI(st,0x2b0)<SI(st,0x2b4)) {
            qcopy(from,self+0x10); from[2]+=0.5f;
            qcopy(to,(SI(st,0x2b0)*16)+(u8 *)path+0x20); to[2]+=0.5f;
            if(!CollLine(from,to,2,self,0)) SI(st,0x2b0)++;
        }
        func_PAL_L01_00323068(self,(SI(st,0x2b0)*16+0x10)+(u8 *)path);
        if(vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)<8.0f) moby_set_state(self,1,-1);
        break;
    case 2:
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=4) func_PAL_002A7E68(self,4,0,17);
            { s32 next=path_pick_random_visible_point(self,1);
            f32 rate=D_L12_001B20A8*0.020000001f; SI(st,0x2b0)=next;
            moby_set_controller_speed_limits(self,0.0016000001f,rate,0.0012566373f,0.12566373f); }
            SI(st,0x2b8)=vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)>24.0f?750:250;
        }
        if((func_PAL_L01_00323068(self,(SI(st,0x2b0)*16+0x10)+(u8 *)path)&128)||SH(self,0x96)>=250) moby_set_state(self,1,-1);
        break;
    case 3:
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=5) func_PAL_002A7E68(self,5,0,17);
            { s32 next=path_pick_random_visible_point(self,0);
            f32 rate=D_L12_001B20AC*0.020000001f; SI(st,0x2b0)=next;
            moby_set_controller_speed_limits(self,0.0056000003f,rate,0.005026549f,0.5026549f); }
        }
        if(func_PAL_L01_00323068(self,(SI(st,0x2b0)*16+0x10)+(u8 *)path)&128) SI(st,0x2b0)=path_pick_random_visible_point(self,1);
        if(SH(self,0x96)>=350) moby_set_state(self,1,-1);
        break;
    case 5: {
        f32 dot;
        if(flag_set_first_pending(self)) {
            if(self[0x43]!=7) func_PAL_002A7E68(self,7,0,8);
            SI(st,0x2c0)=0;
        }
        dot=FastVecDot(self+0xc0,st+0x140);
        if(dot< -0.040000003f) { if(self[0x43]!=10) func_PAL_002A7E68(self,10,0,8); }
        else if(dot>0.040000003f) { if(self[0x43]!=9) func_PAL_002A7E68(self,9,0,8); }
        else { if(self[0x43]!=7) func_PAL_002A7E68(self,7,0,8); }
        moby_start_effect_from_entry(self,mat_fast_helper_a(g_hero_state.pos[0]-SF(self,0x10),g_hero_state.pos[1]-SF(self,0x14)));
        if(helper_has_live_object(D_L12_001B2E9C+(SI(st,0x2c4)<<8))) was0=1;
        if(helper_has_live_object(D_L12_001B2E9C+(SI(st,0x2c8)<<8))) was1=1;
        if(SI(st,0x2c4)!=-1) beam_restore_child_collision(D_L12_001B2E9C+(SI(st,0x2c4)<<8));
        if(SI(st,0x2c8)!=-1) beam_restore_child_collision(D_L12_001B2E9C_gp+(SI(st,0x2c8)<<8));
        func_PAL_L01_0031C9C0(self,st+0x140,0.7f,0.5f,0.1f,SI(st,0x360));
        func_PAL_L12_0042A8E0(self);
        if(flag_is_third_pending_set(self)) moby_set_state(self,6,-1);
        else if(self!=g_hero_state.target) { moby_set_state(self,3,0); goto choose_path; }
        break;
    }
    case 6:
        if(flag_set_first_pending(self)) { if(self[0x43]!=10) func_PAL_002A7E68(self,10,0,8); }
        moby_start_effect_from_entry(self,mat_fast_helper_a(g_hero_state.pos[0]-SF(self,0x10),g_hero_state.pos[1]-SF(self,0x14)));
        func_PAL_L12_0042A8E0(self);
        break;
    case 8:
        if(flag_set_first_pending(self)) {
            u8 *p=CreateMoby(0x9bb);
            if(p) {
                u8 *ps;
                *(u8 **)(p+0xb8)=self; p[0x30]=255; qcopy(p+0x10,self+0x10);
                ps=*(u8 **)(p+0x68); *(u8 **)(ps+0x10)=self;
                SI(ps,0x20)=SH(self,0x34); SI(ps,0x30)=moby_pack_handle(self);
                SI(self,0x98)=0; SH(self,0x34)=(SH(self,0x34)|0x41)&0xefff;
            }
        }
        SI(self,0x98)=0; SH(self,0x34)=(SH(self,0x34)|0x41)&0xefff;
        if(SH(self,0x96)>50) {
            D_L12_0021E180.flags[*(s16 *)(self+0xb2)]=self[0xb0]+2;
            { s32 saveid=self[0xb0];
            if(saveid==255 || (!(D_L12_001B2CE0[(u8)saveid]&128) && (D_0019B2E8[(u8)saveid+(D_001A79F0_gp<<4)]&128)))
                D_L12_0021EDF0.flags[*(s16 *)(self+0xb2)]=saveid+2; }
            moby_mark_spawned(self); return;
        }
        break;
    case 7:
        FastVecAdd(self+0x10,self+0x10,st+0x2a0);
        SF(st,0x2a8)-=D_L12_001B20A4*0.00040000002f;
        func_PAL_L12_0042A8E0(self);
        if(IsPointInCuboid(self+0x10,SI(st,0x29c))) {
            f32 len=vec_length_xy(st+0x2a0);
            if(len>0.020000001f) len=0.020000001f;
            vec_fast_normalize_helper(st+0x2a0,st+0x2a0,len);
        }
        qcopy(from,self+0x10); from[2]+=0.5f;
        if(coll_test_point(from,0,self,0.5f)) {
            qcopy(self+0x10,D_L12_001C0270); SF(self,0x18)-=0.5f;
            vec_scale_to_length(D_L12_001C0270+0x10,D_L12_001C0270+0x10,1.0f);
            if(FastVecDot(D_L12_001C0270+0x10,st+0x2a0)<0.0f) {
                vec_fast_normalize(st+0x2a0,st+0x2a0,D_L12_001C0270+0x10);
                FastVecScale(st+0x2a0,st+0x2a0,0.5f);
            }
            if(SF(D_L12_001C0270,0x18)>=0.95f) {
                SH(self,0x34)|=0x1000; moby_set_state(self,1,0);
                qcopy(st+0x150,self+0x10); vec_clear_128(st+0x140);
            choose_path:
                SI(st,0x2b0)=path_find_visible_point(self);
            }
        }
        break;
    }
    if(SI(st,0x2c4)!=-1 && !was0) helper_clear_states(D_L12_001B2E9C+(SI(st,0x2c4)<<8));
    if(SI(st,0x2c8)!=-1 && !was1) helper_clear_states(D_L12_001B2E9C+(SI(st,0x2c8)<<8));
    if(!(D_L12_001B29C8&15)) path_find_nearby_point_at_hero_height(self);
    if(self[0x31]) {
        SF(st,0x2bc)=FastAddRotations(SF(st,0x2bc),D_L12_001B20B0*0.0003490659f);
        SI(self,0x78)=PulseColor(D_L12_001B20B8[0],D_L12_001B20B8[1],SF(st,0x2bc));
    }
    SH(self,0x96)++;
    qcopy(st+0x2d0,self+0x10);
    func_PAL_002B14F8(self,(f32 *)(st+0x2e0),D_L12_001B20C8,2,1);
}
