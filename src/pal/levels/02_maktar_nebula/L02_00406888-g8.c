#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int g_beam_hazard_initial_timer __attribute__((sda)), g_beam_hazard_timer_base __attribute__((sda)), g_beam_hazard_timer_extra __attribute__((sda)), g_beam_hazard_second_timer __attribute__((sda)), g_beam_hazard_reset_timer __attribute__((sda));
extern float g_beam_hazard_height_offset __attribute__((sda)), g_beam_hazard_sweep_radius_start __attribute__((sda)), g_beam_hazard_sweep_radius_end __attribute__((sda));
extern char g_hero_position[], g_sound_state[];
extern void euler_rotation_basis(void *,void *), moby_set_state(void *,int,int), gfx_add_draw_callback_third(void *,void *), moby_place_by_state(void *), part_spawn_twin_puffs_pal(void *), FastVecSub(void *,void *,void *), snd_stop_voice(int);
extern int FastDecTimer(void *);
extern f32 coll_project_point_on_segment(void *,void *,void *,void *);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern int math_fast_helper_a(void *,float),snd_is_voice_playing_for_owner(void *,int),snd_start_in_slot(int,int,void *);
extern float vec_distance_squared_xy(void *,void *),FastVecLength(void *);
struct State401ED8 { char pad[0x30]; short timer30, timer32, timer34, sound; };
/* func_PAL_L02_00406888, the PAL copy of func_L02_00401ED8: the same C, where the five timer32
   values are scaled to 50 Hz and func_L02_00402300 is func_PAL_L02_00406D40. initial_timer is read
   ahead of the stores and is a full int here: PAL loads it with lw and scales it at its store. */
void beam_l02_hazard_update_pal(char *moby) {
    char *vars; Vec point,a,b,c,d,e; float fraction; s32 initial_timer;
    euler_rotation_basis(moby+0xC0,moby+0xF0);
    vars=*(char **)(moby+0x68);
    switch (*(unsigned char *)(moby+0x20)) {
    case 0:
        vars[9]=0; vars[8]=3; *(int *)(vars+0x10)=0; moby[0x31]=0; initial_timer=g_beam_hazard_initial_timer;
        *(unsigned short *)(moby+0x34)=(*(unsigned short *)(moby+0x34)&0xEFFF)|1;
        ((struct State401ED8 *)vars)->timer30=0; ((struct State401ED8 *)vars)->timer32=((s32)initial_timer*5+2)/6; ((struct State401ED8 *)vars)->sound=-1;
        moby_set_state(moby,1,-1); break;
    case 1:
        if (((struct State401ED8 *)vars)->timer32==0) {
            if (((struct State401ED8 *)vars)->timer30!=0) {
                ((struct State401ED8 *)vars)->timer32=((s32)(g_beam_hazard_timer_base+g_beam_hazard_timer_extra)*5+2)/6;
                ((struct State401ED8 *)vars)->timer34=g_beam_hazard_second_timer;
                moby_set_state(moby,2,-1);
            }
        } else if (((struct State401ED8 *)vars)->timer30!=0) FastDecTimer(vars+0x32);
        break;
    case 2:
        if (((struct State401ED8 *)vars)->timer34==0) {
            ((struct State401ED8 *)vars)->timer32=((s32)g_beam_hazard_reset_timer*5+2)/6;
            moby_set_state(moby,3,-1);
        } else if (((struct State401ED8 *)vars)->timer32>g_beam_hazard_timer_extra) gfx_add_draw_callback_third(moby_place_by_state,moby);
        else if (((struct State401ED8 *)vars)->timer32==0) {
            ((struct State401ED8 *)vars)->timer32=((s32)(g_beam_hazard_timer_base+g_beam_hazard_timer_extra)*5+2)/6;
            FastDecTimer(vars+0x34);
        }
        FastDecTimer(vars+0x32); break;
    case 3:
        if (((struct State401ED8 *)vars)->timer32!=0) {
            a.q=0;
            a.f[0]=*(float *)(moby+0x10); a.f[1]=*(float *)(moby+0x14); a.f[2]=*(float *)(moby+0x18); a.f[3]=1;
            point.q=a.q;
            if(math_fast_helper_a(&point,128.0f)>0) {
                if(vec_distance_squared_xy(moby+0x10,g_hero_position)<4.0f) {
                    qcopy(&a,moby+0x10); qcopy(&b,moby+0x10); b.f[2]+=g_beam_hazard_height_offset;
                    coll_project_point_on_segment(&c,&a,&b,g_hero_position);
                    FastVecSub(&d,&a,&c); FastVecSub(&e,&a,&b);
                    fraction=FastVecLength(&d); fraction/=FastVecLength(&e);
                    if(fraction<0)fraction=0; if(fraction>1)fraction=1;
                    coll_sweep_from_object(moby,&c,0x10001,0,1,0,g_beam_hazard_sweep_radius_start+(g_beam_hazard_sweep_radius_end-g_beam_hazard_sweep_radius_start)*fraction,(unsigned char)vars[0x14],1);
                } else coll_sweep_from_object(moby,moby+0x10,0x10001,0,1,0,g_beam_hazard_sweep_radius_start,(unsigned char)vars[0x14],1);
                part_spawn_twin_puffs_pal(moby); gfx_add_draw_callback_third(moby_place_by_state,moby);
            }
            FastDecTimer(vars+0x32);
            if(!snd_is_voice_playing_for_owner(moby,((struct State401ED8 *)vars)->sound)) ((struct State401ED8 *)vars)->sound=snd_start_in_slot(17,4,moby);
        } else {
            ((struct State401ED8 *)vars)->timer32=((s32)g_beam_hazard_initial_timer*5+2)/6;
            if(((struct State401ED8 *)vars)->sound!=-1) {
                unsigned char *voice=(unsigned char *)g_sound_state+((struct State401ED8 *)vars)->sound*0x70;
                if(*(char **)(voice+0x88)==moby && (unsigned char)voice[0x74])snd_stop_voice(((struct State401ED8 *)vars)->sound);
            }
            ((struct State401ED8 *)vars)->sound=-1;moby_set_state(moby,1,-1);
        } break;
    }
}
