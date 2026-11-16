#include "include_asm.h"

#include "common.h"
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void snd_stop_voice(int);
extern char g_sound_state[], g_hero_position[];
extern u8 *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(float *, const float *, const float *);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern char g_sound_state[];
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void vec_random_direction(void *,float,float);
extern float IntToFloat(int);
extern int snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern void make_hit_descriptor(void *,void *,int,void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern void part_spawn_large_spark_smoke_pal(char *,int);
extern struct { u8 pad[24];u8 *object;u8 pad1[4];float position[4] __attribute__((aligned(16))); } g_hero_ground_hit;
extern int g_frame_l18_counter __attribute__((sda));
typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern char g_sound_state[];
extern char g_hero_position[];
extern void snd_stop_voice(int);

/* Runs the Extermibot's electric beam: it charges, shoots out to the target, sticks to what it hits, and then pulls back. It also throws sparks where the beam lands. (PAL: 50 Hz timings) */
void extermibot_beam_update_pal(u8 *obj) {
 float beam_start[4] __attribute__((aligned(16))),beam_end[4] __attribute__((aligned(16))),dir[4] __attribute__((aligned(16)));
 struct { float direction[4] __attribute__((aligned(16))); int owner,mode; u8 type,flags;u16 id; float distance;int enabled; } hit;
 u8 *vars=P(obj,0x68),*other;float frac;
 moby_transform_joint_to_world(P(vars,0x7c8),0,beam_start);moby_transform_joint_to_world(P(vars,0x7c8),1,beam_end);F(vars,0x7e0)=0;
 switch(H(vars,0x806)) {
 case 0:
  qcopy(vars+0x610,beam_start);qcopy(vars+0x620,beam_end);qcopy(vars+0x6b0,beam_end);qcopy(vars+0x6c0,beam_start);
  if(I(vars,0x7f0)!=-1) {
   u8 *entry=g_sound_state+I(vars,0x7f0)*0x70;
   if(P(entry,0x88)==obj && entry[0x74])snd_stop_voice(I(vars,0x7f0));
  }
  I(vars,0x7f0)=-1;break;
 case 1:
  qcopy(vars+0x610,beam_start);qcopy(vars+0x620,beam_end);qcopy(vars+0x6b0,beam_end);qcopy(vars+0x6c0,beam_start);
  coll_sweep_from_object(obj,beam_start,0x10001,0,1,0,0.2f,(float)vars[0x34],1);
  if(H(vars,0x804)>=6) {
   u8 *target=vars+0x760;
   u8 *p3=vars+0x6a0,*p2=vars+0x690,*p1=vars+0x680,*p0=vars+0x670;
   int i;
   for(i=1;i>=0;i--) {
    vec_random_direction(p0,0.2792527f,0.34906593f);
    vec_random_direction(p1,0.2792527f,0.34906593f);
    vec_random_direction(p2,2,5);vec_random_direction(p3,2,5);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   }
   H(vars,0x804)=0;H(vars,0x806)=2;
   if(!snd_is_voice_playing_for_owner(obj,I(vars,0x7f0)))I(vars,0x7f0)=PlayMobySound(1,4,obj);
   if(P(vars,0x7bc))qcopy(target,P(vars,0x7bc)+0x10);else qcopy(target,vars+0x1f0);
  } else F(vars,0x7e0)=IntToFloat(H(vars,0x804))/IntToFloat(5);
  break;
 case 2:
  qcopy(vars+0x610,beam_start);qcopy(vars+0x6b0,beam_end);
  coll_sweep_from_object(obj,beam_start,0x10001,0,1,0,0.2f,(float)vars[0x34],1);
  if(H(vars,0x804)<5) {
   frac=IntToFloat(H(vars,0x804))/IntToFloat(4);
   F(vars,0x620)=beam_start[0]+(F(vars,0x760)-beam_start[0])*frac;
   F(vars,0x624)=beam_start[1]+(F(vars,0x764)-beam_start[1])*frac;
   F(vars,0x628)=beam_start[2]+(F(vars,0x768)-beam_start[2])*frac;
   qcopy(vars+0x6c0,vars+0x620);
   FastVecSub(dir,vars+0x620,vars+0x610);vec_scale_to_length(dir,dir,0.040000003f);
   make_hit_descriptor(&hit,obj,0x210001,dir,(float)vars[0x34]);
   hit.type=5;hit.flags=3;hit.id=*(u16 *)(obj+0xaa);
   if(CollLine(vars+0x610,vars+0x620,0,obj,&hit)) {
    part_spawn_large_spark_smoke_pal(vars+0x620,15);qcopy(vars+0x760,vars+0x620);H(vars,0x804)=0;
    if(g_hero_ground_hit.object) {
     float *point=g_hero_ground_hit.position;
     u8 *attached;
     H(vars,0x806)=3;attached=g_hero_ground_hit.object;P(vars,0x7e4)=attached;
     qcopy(vars+0x620,point);qcopy(vars+0x770,attached+0x10);
    } else H(vars,0x806)=4;
   }
  } else {H(vars,0x806)=4;part_spawn_large_spark_smoke_pal(vars+0x620,10);}
  break;
 case 3:
  qcopy(vars+0x610,beam_start);qcopy(vars+0x6b0,beam_end);
  if(H(vars,0x804)<43 && (other=P(vars,0x7e4)) && other[0x20]!=254 && other[0x20]!=253) {
   FastVecSub(dir,other+0x10,vars+0x770);FastVecAdd(vars+0x620,vars+0x620,dir);
   qcopy(vars+0x6c0,vars+0x620);qcopy(vars+0x770,P(vars,0x7e4)+0x10);
   if((g_frame_l18_counter&15)==(((int)obj>>8)&15))part_spawn_large_spark_smoke_pal(vars+0x620,1);
  } else {
   DamoselBeamState *state=(DamoselBeamState *)vars;
   state->attached=0;state->mode=4;state->timer=0;
  }
  break;
 case 4:
  qcopy(vars+0x610,beam_start);qcopy(vars+0x6b0,beam_end);
  if(H(vars,0x804)<4) {
   frac=IntToFloat(H(vars,0x804))/IntToFloat(4);
   F(vars,0x620)=F(vars,0x760)+(beam_start[0]-F(vars,0x760))*frac;
   F(vars,0x624)=F(vars,0x764)+(beam_start[1]-F(vars,0x764))*frac;
   F(vars,0x628)=F(vars,0x768)+(beam_start[2]-F(vars,0x768))*frac;
   F(vars,0x6c0)=F(vars,0x760)+(beam_end[0]-F(vars,0x760))*frac;
   F(vars,0x6c4)=F(vars,0x764)+(beam_end[1]-F(vars,0x764))*frac;
   F(vars,0x6c8)=F(vars,0x768)+(beam_end[2]-F(vars,0x768))*frac;
  } else {
   H(vars,0x804)=0;H(vars,0x806)=0;
   { u8 *p3=vars+0x6a0,*p2=vars+0x690,*p1=vars+0x680,*p0=vars+0x670;
   int i;
   for(i=1;i>=0;i--) {
    vec_random_direction(p0,0.2792527f,0.34906593f);
    vec_random_direction(p1,0.2792527f,0.34906593f);
    vec_random_direction(p2,1,1.7f);vec_random_direction(p3,1,1.7f);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   } }
  }
 }
 extermibot_update_arc_offsets(obj);
}
