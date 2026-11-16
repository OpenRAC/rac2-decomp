#include "names.h"
/* func_PAL_L04_00413590, the PAL copy of func_L04_0040EF50: the same C, where rename func_L04_0040E460 becomes func_PAL_L04_00412AA0; rename func_L04_0040C0C0 becomes func_PAL_L04_00410678; rename func_L04_003F9320 becomes func_PAL_L04_003FD4F8; rename func_L04_003FA5A8 becomes func_PAL_L04_003FE7B0; rename func_L04_003FBD80 becomes func_PAL_L04_003FFF88; lit 3 becomes 2. */

/* Bodies whose retail bytes reach their globals through $gp: this file is built -G8.
   Measured here: cc1 emits `sw $r,SYM` as a macro and GAS expands it. Outside a delay
   slot it always becomes `lui $at,%hi ; sw %lo($at)` (HI16/LO16) whatever the attribute;
   inside a delay slot (.set nomacro: one instruction only) it becomes the $gp-relative
   form with a GPREL16 relocation, whose symbol must therefore be named GP + the retail
   displacement. `sda` only adds `.extern SYM,size`. */

/* func_L04_0040AC30 reaches its globals off $gp too, but its body is not matched
   yet; its marker stays in L04_00402D90.c and the attempt is in the wave-8 drafts. */

/* 0x001A8ED0 is absolute in func_L04_0040AC80 and $gp-relative here, so it is
   reached under a second name, declared small data.  The store to 0x001A8EE4 is
   written last in the source: cc1 emits the last store of a straight-line run
   first and then the source order, which is the order retail has. */
/* The record func_L04_004044B8 walks: the fields it uses, at the retail's offsets. */
/* 0x001A7B90 is the boot's resident data, reached off $gp in the delay slot. */
/* Updates the record's flag from the two point tests, prints the message when the
   record has one and its counter runs, then advances the counter and the value. */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(unsigned char **)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
typedef unsigned int AttackQuad __attribute__((mode(TI)));
typedef struct { int v[5]; } AttackChoices;
extern AttackChoices g_attack_choices;
extern struct { unsigned char pad[0x80]; float position[4]; unsigned char pad90[0x2290-0x90]; unsigned char *hero; } g_hero_state;
typedef struct {
 unsigned char pad0[0x260]; int trigger_list;
 unsigned char pad264[0x10]; short elevated;
 unsigned char pad276[6]; float height;
 unsigned char pad280[4]; float tilt;
 unsigned char pad288[8]; float offset[4];
 unsigned char pad2a0[0x6c]; float length;
 unsigned char pad310[0x50]; int state, duration, timer;
 unsigned char pad36c[0x16c]; int alternate, alternate_timer;
 unsigned char pad4e0[0x284]; int cooldown, ready;
} AttackState;
typedef struct { int unused, flags; unsigned char pad8[0x38]; } AttackSettings;
extern AttackSettings g_race_challenge_table[];

extern unsigned char *g_special_moby_list[];
extern int g_current_race_index __attribute__((sda));
extern int g_pad_pressed_flags NOT_SDA,g_pad_held_flags NOT_SDA;
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_process_hit(void *,float,int,void *,int);
extern int moby_is_in_special_class_range(void *);
extern void part_queue_impact_effect(void *,void *,int,void *,void *,float);
extern void racer_update_boost_pal(void *);
extern int GetFirstMobyInGroup(void *,int,int,int);
extern int GetNextMobyInGroup(void *,void *,int,int);
extern void FastVecSub(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int math_random_int_range(int,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void part_l04_spawn_burst_pal(void *,void *,int,int);
extern int math_fast_float_d(void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void add_vectors(void *,void *,void *);
extern unsigned char *SpawnHomingShot_pal(void *,void *,void *,int);
extern int PlayMobySound(int,int,void *);
extern unsigned char *bike_find_aim_target(void *,void *,void *,void *,void *,void *,float,float);
extern int queue_copy_record_by_index(int);
extern void * homing_rocket_spawn_pal(void *,void *,void *,float,float,float,float,float);
extern void * shield_dome_spawn_pal(void *,void *);
/* Handles the racer item use each frame: collects item boxes, then fires the current weapon (shot,
   homing rocket or shield dome) when the fire button is pressed (PAL: 50 Hz timings). */
void racer_update_item_use_pal(unsigned char *moby)
{
 AttackChoices choices;
 float origin[4],dir[4],delta[4],probe[4],temp[4];
 unsigned char *target; float pitch,yaw,aim_pitch,aim_yaw,extra; AttackState *vars=*(AttackState **)(moby+0x68); unsigned char *item_box_vars; int count,i,state,choice;
 choices=g_attack_choices;
 FastVecScale(probe,vars->offset,3);
 FastVecAdd(probe,probe,((unsigned char *)&g_hero_state + 0xe0));
 count=coll_process_hit(probe,0.7f,0,g_hero_state.hero,0);
 if(count) {
  FastVecScale(delta,vars->offset,7);
  for(i=0;i<count;i++) if(moby_is_in_special_class_range(g_special_moby_list[i]) || H(g_special_moby_list[i],0xaa)==0x85)
   part_queue_impact_effect(g_special_moby_list[i],g_hero_state.hero,0x10000,g_hero_state.position,delta,1);
 }
 racer_update_boost_pal(moby);
 if((g_race_challenge_table[g_current_race_index].flags&1) && vars->trigger_list!=-1) {
  GetFirstMobyInGroup(&target,vars->trigger_list,0,0);
  while(target) {
   if(H(target,0xaa)==MOBY_CLASS_HOVERBIKE_RACE_ITEM_BOX) {
    item_box_vars=P(target,0x68);FastVecSub(delta,target+16,moby+16);
    if(!I(item_box_vars,0) && func_L00_002EE290(delta)<1) {
     choice=vars->state;state=choice;
     if(I(item_box_vars,4)==-1) do {choice=math_random_int_range(1,4);} while(state==choice && I(item_box_vars,4)==-1);
     if(choice==4) {vars->alternate=1;vars->alternate_timer=choices.v[4];}
     else {int duration; vars->state=choice;duration=choices.v[choice];vars->timer=0;vars->duration=duration;}
     if(moby[0x20]!=3)snd_play_from_class_bank(0,0,moby,0xab8);
     part_l04_spawn_burst_pal(target+16,vars->offset,8,0);I(item_box_vars,0)=250;
    }
   }
   GetNextMobyInGroup(&target,target,0,0);
  }
 }
 if(vars->alternate) {
  vars->ready=0;
  if(math_fast_float_d(&vars->alternate_timer)) {vars->alternate=0;vars->ready=1;}
 }
 if(vars->ready && math_fast_float_d(&vars->cooldown)) {vars->ready=0;vars->cooldown=33;}
 if(moby[0x20]==3)return;
 switch(vars->state) {
 case 0: break;
 case 1:
  if(math_fast_float_d(&vars->timer) && (g_pad_pressed_flags&5)) {
   vars->timer=2;moby_transform_joint_to_world(moby,((vars->duration^1)&1),origin);
   if(vars->elevated)vec_build_spherical_offset(dir,vars->length+0.6f,F(moby,0xf8),-vars->tilt);
   else vec_build_spherical_offset(dir,vars->length+0.6f,F(moby,0xf8),-F(moby,0xf4));
   add_vectors(temp,origin,dir);SpawnHomingShot_pal(moby,origin,dir,100);PlayMobySound(7,0,moby);
   if(math_fast_float_d(&vars->duration))vars->state=0;
  }return;
 case 2: {
  unsigned char *target; float tilt;
  if(math_fast_float_d(&vars->timer) && (g_pad_held_flags&5)) {
   yaw=0;extra=0;vars->timer=25;moby_transform_joint_to_world(moby,((vars->duration^1)&1),origin);tilt=F(moby,0xf8);
   if(vars->elevated)vec_build_spherical_offset(dir,vars->length+0.6f+vars->height,tilt,yaw);
   else {vec_build_spherical_offset(dir,vars->length+0.6f+vars->height,tilt,-F(moby,0xf4));yaw=F(moby,0xf4);}
   pitch=tilt;yaw-=0.3490659f;
   target=bike_find_aim_target(moby,origin,dir,&aim_pitch,&aim_yaw,&extra,0.78539824f,30);
   if(target) {
    FastVecSub(delta,origin,target+16);
    if(func_L00_002EE290(delta)<25) {pitch=aim_pitch;yaw=aim_yaw;}
   } else {aim_pitch=pitch;aim_yaw=yaw;extra=0.2f;}
   queue_copy_record_by_index(47);add_vectors(temp,origin,dir);
   homing_rocket_spawn_pal(moby,origin,target,aim_pitch,aim_yaw,extra,pitch,yaw);PlayMobySound(8,0,moby);
   if(math_fast_float_d(&vars->duration))vars->state=0;
  }return; }
 case 3:
  if(math_fast_float_d(&vars->timer) && (g_pad_held_flags&5)) {
   vars->timer=25;FastVecAdd(temp,moby+16,vars->offset);*(AttackQuad *)origin=*(AttackQuad *)temp;shield_dome_spawn_pal(moby,origin);
   if(math_fast_float_d(&vars->duration))vars->state=0;
  }
  break;
 }
}
