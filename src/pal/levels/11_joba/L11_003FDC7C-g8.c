/* func_PAL_L11_003FDC7C, the PAL copy of func_L02_00401ED8: the same C, with its timers scaled to 50 Hz
   (the initial timer read as an int) and func_L02_00402300 becoming func_PAL_L02_00406D40. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int D_L02_001B17C0 __attribute__((sda)), D_L02_001B17C4 __attribute__((sda)), D_L02_001B17C8 __attribute__((sda)), D_L02_001B17CC __attribute__((sda)), D_L02_001B17D0 __attribute__((sda));
extern float D_L02_001B17D4 __attribute__((sda)), D_L02_001B17D8 __attribute__((sda)), D_L02_001B17DC __attribute__((sda));
extern char g_hero_position[], g_sound_state[];
extern void euler_rotation_basis(void *,void *), moby_set_state(void *,int,int), gfx_add_draw_callback_third(void *,void *), moby_place_by_state(void *), func_PAL_L02_00406D40(void *), FastVecSub(void *,void *,void *), snd_stop_voice(int);
extern int FastDecTimer(void *);
extern f32 coll_project_point_on_segment(void *,void *,void *,void *);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern int math_fast_helper_a(void *,float),snd_is_voice_playing_for_owner(void *,int),snd_start_in_slot(int,int,void *);
extern float vec_distance_squared_xy(void *,void *),FastVecLength(void *);
struct State401ED8 { char pad[0x30]; short timer30, timer32, timer34, sound; };
void func_PAL_L11_003FDC7C(char *o) {
    char *p; Vec point,a,b,c,d,e; float t; int initialTimer;
    euler_rotation_basis(o+0xC0,o+0xF0);
    p=*(char **)(o+0x68);
    switch (*(unsigned char *)(o+0x20)) {
    case 0:
        p[9]=0; p[8]=3; *(int *)(p+0x10)=0; o[0x31]=0; initialTimer=D_L02_001B17C0;
        *(unsigned short *)(o+0x34)=(*(unsigned short *)(o+0x34)&0xEFFF)|1;
        ((struct State401ED8 *)p)->timer30=0; ((struct State401ED8 *)p)->timer32=((s32)(initialTimer) * 5 + 2) / 6; ((struct State401ED8 *)p)->sound=-1;
        moby_set_state(o,1,-1); break;
    case 1:
        if (((struct State401ED8 *)p)->timer32==0) {
            if (((struct State401ED8 *)p)->timer30!=0) {
                ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17C4+D_L02_001B17C8) * 5 + 2) / 6;
                ((struct State401ED8 *)p)->timer34=D_L02_001B17CC;
                moby_set_state(o,2,-1);
            }
        } else if (((struct State401ED8 *)p)->timer30!=0) FastDecTimer(p+0x32);
        break;
    case 2:
        if (((struct State401ED8 *)p)->timer34==0) {
            ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17D0) * 5 + 2) / 6;
            moby_set_state(o,3,-1);
        } else if (((struct State401ED8 *)p)->timer32>D_L02_001B17C8) gfx_add_draw_callback_third(moby_place_by_state,o);
        else if (((struct State401ED8 *)p)->timer32==0) {
            ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17C4+D_L02_001B17C8) * 5 + 2) / 6;
            FastDecTimer(p+0x34);
        }
        FastDecTimer(p+0x32); break;
    case 3:
        if (((struct State401ED8 *)p)->timer32!=0) {
            a.q=0;
            a.f[0]=*(float *)(o+0x10); a.f[1]=*(float *)(o+0x14); a.f[2]=*(float *)(o+0x18); a.f[3]=1;
            point.q=a.q;
            if(math_fast_helper_a(&point,128.0f)>0) {
                if(vec_distance_squared_xy(o+0x10,g_hero_position)<4.0f) {
                    qcopy(&a,o+0x10); qcopy(&b,o+0x10); b.f[2]+=D_L02_001B17D4;
                    coll_project_point_on_segment(&c,&a,&b,g_hero_position);
                    FastVecSub(&d,&a,&c); FastVecSub(&e,&a,&b);
                    t=FastVecLength(&d); t/=FastVecLength(&e);
                    if(t<0)t=0; if(t>1)t=1;
                    coll_sweep_from_object(o,&c,0x10001,0,1,0,D_L02_001B17D8+(D_L02_001B17DC-D_L02_001B17D8)*t,(unsigned char)p[0x14],1);
                } else coll_sweep_from_object(o,o+0x10,0x10001,0,1,0,D_L02_001B17D8,(unsigned char)p[0x14],1);
                func_PAL_L02_00406D40(o); gfx_add_draw_callback_third(moby_place_by_state,o);
            }
            FastDecTimer(p+0x32);
            if(!snd_is_voice_playing_for_owner(o,((struct State401ED8 *)p)->sound)) ((struct State401ED8 *)p)->sound=snd_start_in_slot(17,4,o);
        } else {
            ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17C0) * 5 + 2) / 6;
            if(((struct State401ED8 *)p)->sound!=-1) {
                unsigned char *s=(unsigned char *)g_sound_state+((struct State401ED8 *)p)->sound*0x70;
                if(*(char **)(s+0x88)==o && (unsigned char)s[0x74])snd_stop_voice(((struct State401ED8 *)p)->sound);
            }
            ((struct State401ED8 *)p)->sound=-1;moby_set_state(o,1,-1);
        } break;
    }
}
