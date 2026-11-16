#include "names.h"
/* func_PAL_003188D8, the PAL copy of func_003173B0: the same C, with the animation rates,
   the draw scale and the timers changed for 50 Hz. */
#include "common.h"

extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int math_random_int_range(int, int);
extern void moby_set_state(void *, int, int), func_PAL_002A7E68(void *, int, int, int);
extern float FastAddRotations(float angle, float step);
extern float math_fast_sin_or_cos_b(float angle);
extern int math_fast_float_d(void *timer);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern int func_PAL_003192E0(char *);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind_pal(char *, char *);
extern void snd_stop_voice(int);
extern void *func_PAL_0032DF28(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int PlayMobySound(int, int, void *);
extern void SetDeathBits_pal(void *, int, int);
extern void moby_mark_spawned(void *);
extern void func_002A677C(void *);
extern int moby_turn_toward_target_and_step_pal(void *, void *, float);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);
extern void flyer_tick_timers_pal(char *);
extern unsigned char g_sound_state[];
extern unsigned char g_hero_state[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *g_path_table[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");
void func_PAL_003188D8(char *self)
{
    char *d = FP(self,0x68);
    int flags, n, i;
    char *sound, *path;
    float target[4], delta[4];
    float f, height, savedHeight;
    /* Written out here and at the end of state 3, not shared through a label: cross-jumping
       merges the two after sched1, which has to see func_0029F338 in the same block as the
       explosion's calls for it to set a3..t3 up before a0..a2. */
    if (func_PAL_003192E0(self)) {
        moby_mark_spawned(self);
        return;
    }
    switch (FB(self,0x95)) {
    case 0:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.0096f,0.080000006f,1.0053098f,1.0053098f);
        if (FI(d,0x258)==1 && math_fast_float_d(d+0x2A4) && FI(d,0x2AC)) {
            if (FI(d,0x294)==-1) {
                moby_set_state(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) func_PAL_002A7E68(self,2,0,4);
            } else moby_set_state(self,4,2);
        } else if (FH(d,0x276)) {
            moby_set_state(self,3,1);
            FH(d,0x276)=0;
            if (FH(d,0x270)<250) FH(d,0x270)=(((int)(math_random_int_range(480,600)) * 5 + 2) / 6);
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 1:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.0096f,0.080000006f,1.0053098f,1.0053098f);
        if ((FI(d,0x258)==1 || FI(d,0x25C)==1) && FI(d,0x2AC)) {
            if (FI(d,0x294)!=-1) moby_set_state(self,4,2);
            else {
                moby_set_state(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) func_PAL_002A7E68(self,2,0,4);
            }
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 2:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.0096f,0.080000006f,1.0053098f,1.0053098f);
        if (FI(d,0x258)!=1 && FI(d,0x25C)!=1 && FB(self,0x20)!=4) {
            moby_set_state(self,1,1);
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,17);
            FH(d,0x270)=(((int)(math_random_int_range(580,600)) * 5 + 2) / 6);
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind_pal(self,d+0x60);
        if (flags&1) {
            n=FI(d,0x2A8);
            if (n!=-1) {
                sound=(char *)g_sound_state+n*0x70;
                if (FP(sound,0x88)==self && FB(sound,0x74)) snd_stop_voice(n);
            }
            FI(d,0x2A8)=-1;
            func_PAL_0032DF28(self+0x10,0,0,0,0,20,45,1,0.3f,20.0f,1,0,0,0);
            PlayMobySound(0,0,self);
            SetDeathBits_pal(self,0,3);
            moby_mark_spawned(self);
            return;
        }
        if (flags&2) {
            if (FI(d,0x258)==1 || FI(d,0x25C)==1) {
                moby_set_state(self,5,2);
                if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,4);
                if (FI(d,0x294)!=-1) moby_set_state(self,4,2);
            } else {
                moby_set_state(self,3,1);
                FH(d,0x270)=(((int)(math_random_int_range(580,600)) * 5 + 2) / 6);
            }
        }
        break;
    }
    switch (FB(self,0x20)) {
    case 1:
        if (FU(self,0x96)>=26) {
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,4);
            moby_set_state(self,2,-1);
            FF(self,0x18)=FF(d,0x28C);
        } else {
            f=math_fast_sin_or_cos_b((float)FU(self,0x96)*0.14842157f)*0.02f;
            if (FF(self,0x18)>FF(d,0x28C)) FF(self,0x18)-=f;
            else FF(self,0x18)+=f;
        }
        break;
    case 4:
        path=g_path_table[FI(d,0x294)];
        if (FI(d,0x298)>=FI(path,0)) {
            FI(d,0x294)=-1;
            FF(d,0x28C)=coll_probe_ground_height_below(self+0x10,0,0.5f)+0.5f;
            moby_set_state(self,5,-1);
        } else {
            qcopy(target,path+0x10+FI(d,0x298)*16);
            FastVecSub(delta,target,self+0x10);
            vec_scale_to_length(delta,delta,FF(d,0x1C0));
            FastVecAdd(self+0x10,self+0x10,delta);
            if (vec_distance_xy(self+0x10,target)<0.5f) FI(d,0x298)++;
            if (FI(d,0x298)>=FI(path,0)-6 && FF(d,0x1C0)>=0.120000005f)
                FF(d,0x1C0)-=0.0032000002f;
            height=coll_probe_ground_height_below(self+0x10,0,0.5f)+0.5f;
            if (FF(self,0x18)<height) FF(self,0x18)=height;
            FF(d,0x28C)=FF(self,0x18);
            func_002A677C(self);
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 5:
        savedHeight=FF(self,0x18);
        moby_turn_toward_target_and_step_pal(self,d+0x230,FF(d,0x290));
        FF(self,0x18)=savedHeight;
        if (vec_distance_xy(self+0x10,FP(d,0x240)+0x10)<1.3f) moby_set_state(self,7,-1);
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 6:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)!=3) func_PAL_002A7E68(self,3,0,4);
            changeMode3173Six(self,8,-1);
        }
        break;
    case 8:
        height=1.75f;
        FF(self,0x48)=height;
        for (i=0;i<4;i++) coll_test_hit_at_bone(self,i,0.17f,FF(d,0x2B0),1,1.0f,0,1,0);
        if (((Hero3173 *)g_hero_state)->target==self) moby_set_state(self,9,-1);
        if (vec_distance_xy(self+0x10,FP(d,0x240)+0x10)>1.3f && (float)FU(self,0x96)>120.0f) {
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,12);
            moby_set_state(self,5,-1);
            FF(self,0x48)=1.0f;
        }
        break;
    case 9:
        if ((float)FU(self,0x96)>20.0f) {
            moby_set_state(self,10,-1);
            if (FB(self,0x43)!=4) func_PAL_002A7E68(self,4,0,4);
            FF(self,0x48)=1.0f;
        }
        break;
    case 10:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,12);
            moby_set_state(self,5,-1);
        }
        break;
    case 7:
        if (FU(self,0x96)>=30) {
            moby_set_state(self,6,-1);
            if (FB(self,0x43)!=1) func_PAL_002A7E68(self,1,0,2);
            FF(self,0x48)=1.0f;
        }
        break;
    }
    if (FB(self,0x20)!=4 && FB(self,0x95)==2 && FF(self,0x18)<FF(d,0x28C)) FF(self,0x18)=FF(d,0x28C);
    flyer_tick_timers_pal(self);
}
