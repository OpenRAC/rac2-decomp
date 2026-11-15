#include "include_asm.h"
#include "names.h"

/* Bodies whose retail bytes reach their globals through $gp: this file is built -G8.
   Measured here: cc1 emits `sw $r,SYM` as a macro and GAS expands it. Outside a delay
   slot it always becomes `lui $at,%hi ; sw %lo($at)` (HI16/LO16) whatever the attribute;
   inside a delay slot (.set nomacro: one instruction only) it becomes the $gp-relative
   form with a GPREL16 relocation, whose symbol must therefore be named GP + the retail
   displacement. `sda` only adds `.extern SYM,size`. */

extern unsigned int D_L04_001A8ED0;

extern unsigned int D_L04_001B0908 __attribute__((sda));

/* Sets two level-04 race state flags. */
void race_set_state_flags_a(void)
{
    D_L04_001A8ED0 = 2;
    D_L04_001B0908 = 1;
}

extern unsigned int D_L04_001B0910 __attribute__((sda));

/* Sets one level-04 race state flag. */
void race_set_state_flag_b(void)
{
    D_L04_001B0910 = 1;
}

/* func_L04_0040AC30 reaches its globals off $gp too, but its body is not matched
   yet; its marker stays in L04_00402D90.c and the attempt is in the wave-8 drafts. */

/* 0x001A8ED0 is absolute in func_L04_0040AC80 and $gp-relative here, so it is
   reached under a second name, declared small data.  The store to 0x001A8EE4 is
   written last in the source: cc1 emits the last store of a straight-line run
   first and then the source order, which is the order retail has. */
extern unsigned int D_L04_001A8ED0_1 __attribute__((sda));

extern unsigned int D_L04_001A8EE4;

/* Sets three level-04 race state flags. */
void race_set_state_flags_c(void)
{
    D_L04_001A8EE4 = 1;
    D_L04_001A8ED0_1 = 2;
    D_L04_001B0908 = 2;
}

/* The record func_L04_004044B8 walks: the fields it uses, at the retail's offsets. */
typedef struct {
    unsigned char pad0[0x84];
    int f84;
    int f88;
    char *f8c;
    unsigned char pad1[0x15C - 0x90];
    int f15c;
    int f160;
    unsigned char *f164;
    unsigned char pad2[0x1A0 - 0x168];
    int f1a0;
    unsigned char pad3[0x1B0 - 0x1A4];
    float f1b0;
    unsigned char pad3b[4];
    int f1b8;
    unsigned char pad4[0x2D0 - 0x1BC];
    float f2d0;
} L04_004044B8_Record;

extern int IsPointInCuboid(void *, int);

extern void anim_start_blended(char *, int, int, int);

/* 0x001A7B90 is the boot's resident data, reached off $gp in the delay slot. */
extern int g_is_pal_video __attribute__((sda));

extern int g_race_time_ticks;

/* Updates the record's flag from the two point tests, prints the message when the
   record has one and its counter runs, then advances the counter and the value. */
void racer_update_checkpoint_progress(void *racer, L04_004044B8_Record *record)
{
    char *racerPos = (char *)racer + 0x10;
    int counter;

    if (IsPointInCuboid(racerPos, record->f88)) {
        record->f15c = 1;
    }
    if (!IsPointInCuboid(racerPos, record->f84)) {
        return;
    }
    if (record->f15c == 0) {
        return;
    }
    counter = record->f160;
    if (record->f8c && counter > 0) {
        anim_start_blended(record->f8c, 9, 0, 0xC);
        counter = record->f160;
    }
    if (counter < 4) {
        float frames = (float)record->f1b8;
        float seconds;
        float newValue;

        if (g_is_pal_video != 0) {
            seconds = frames * 0.02f;
        } else {
            seconds = frames * 0.016666667f;
        }
        newValue = record->f2d0 + record->f1b0 - seconds;
        record->f2d0 = newValue;
        if (newValue < 0.0f) {
            record->f2d0 = 0.0f;
        }
        record->f1b8 = 0;
        record->f15c = 0;
        record->f160 = record->f160 + 1;
        if (record->f160 != 3) {
            return;
        }
        if (*(unsigned char *)(record->f164 + 0x20) == 2) {
            record->f1a0 = g_race_time_ticks;
        }
    }
}

#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(unsigned char **)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
typedef unsigned int AttackQuad __attribute__((mode(TI)));
typedef struct { int v[5]; } AttackChoices;
extern AttackChoices D_L04_001B0A10;
extern struct { unsigned char pad[0x80]; float position[4]; unsigned char pad90[0x2290-0x90]; unsigned char *hero; } g_hero_state;
typedef struct {
 unsigned char pad0[0x260]; int triggerList;
 unsigned char pad264[0x10]; short elevated;
 unsigned char pad276[6]; float height;
 unsigned char pad280[4]; float tilt;
 unsigned char pad288[8]; float offset[4];
 unsigned char pad2a0[0x6c]; float length;
 unsigned char pad310[0x50]; int state, duration, timer;
 unsigned char pad36c[0x16c]; int alternate, alternateTimer;
 unsigned char pad4e0[0x284]; int cooldown, ready;
} AttackState;
typedef struct { int unused, flags; unsigned char pad8[0x38]; } AttackSettings;
extern AttackSettings g_race_challenge_table[];

extern unsigned char *D_L04_001C3B40[];
extern int g_current_race_index __attribute__((sda));
extern int D_00138320 NOT_SDA,D_00138324 NOT_SDA;
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_process_hit(void *,float,int,void *,int);
extern int moby_is_in_special_class_range(void *);
extern void part_queue_impact_effect(void *,void *,int,void *,void *,float);
extern void racer_update_boost(void *);
extern int GetFirstMobyInGroup(void *,int,int,int);
extern int GetNextMobyInGroup(void *,void *,int,int);
extern void FastVecSub(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int math_random_int_range(int,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void part_l04_spawn_burst(void *,void *,int,int);
extern int math_fast_float_d(void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void add_vectors(void *,void *,void *);
extern void SpawnHomingShot(void *,void *,void *,int);
extern int PlayMobySound(int,int,void *);
extern unsigned char *bike_find_aim_target(void *,void *,void *,void *,void *,void *,float,float);
extern int queue_copy_record_by_index(int);
extern void * homing_rocket_spawn(void *,void *,void *,float,float,float,float,float);
extern void * shield_dome_spawn(void *,void *);
/* Lets the racer pick up item boxes and fire its chosen weapon: shots, homing rockets or a dome blast. */
void racer_update_item_use(unsigned char *racer)
{
 AttackChoices choices;
 float origin[4],dir[4],delta[4],probe[4],temp[4];
 unsigned char *target; float pitch,yaw,aimPitch,aimYaw,extra; AttackState *racerState=*(AttackState **)(racer+0x68); unsigned char *boxVars; int count,i,state,choice;
 choices=D_L04_001B0A10;
 FastVecScale(probe,racerState->offset,3);
 FastVecAdd(probe,probe,((unsigned char *)&g_hero_state + 0xe0));
 count=coll_process_hit(probe,0.7f,0,g_hero_state.hero,0);
 if(count) {
  FastVecScale(delta,racerState->offset,7);
  for(i=0;i<count;i++) if(moby_is_in_special_class_range(D_L04_001C3B40[i]) || H(D_L04_001C3B40[i],0xaa)==0x85 /* moby class 133 */)
   part_queue_impact_effect(D_L04_001C3B40[i],g_hero_state.hero,0x10000,g_hero_state.position,delta,1);
 }
 racer_update_boost(racer);
 if((g_race_challenge_table[g_current_race_index].flags&1) && racerState->triggerList!=-1) {
  GetFirstMobyInGroup(&target,racerState->triggerList,0,0);
  while(target) {
   if(H(target,0xaa)==0xab8 /* Hoverbike Race Item Box */) {
    boxVars=P(target,0x68);FastVecSub(delta,target+16,racer+16);
    if(!I(boxVars,0) && func_L00_002EE290(delta)<1) {
     choice=racerState->state;state=choice;
     if(I(boxVars,4)==-1) do {choice=math_random_int_range(1,4);} while(state==choice && I(boxVars,4)==-1);
     if(choice==4) {racerState->alternate=1;racerState->alternateTimer=choices.v[4];}
     else {int duration; racerState->state=choice;duration=choices.v[choice];racerState->timer=0;racerState->duration=duration;}
     if(racer[0x20]!=3)snd_play_from_class_bank(0,0,racer,0xab8 /* Hoverbike Race Item Box */);
     part_l04_spawn_burst(target+16,racerState->offset,8,0);I(boxVars,0)=300;
    }
   }
   GetNextMobyInGroup(&target,target,0,0);
  }
 }
 if(racerState->alternate) {
  racerState->ready=0;
  if(math_fast_float_d(&racerState->alternateTimer)) {racerState->alternate=0;racerState->ready=1;}
 }
 if(racerState->ready && math_fast_float_d(&racerState->cooldown)) {racerState->ready=0;racerState->cooldown=40;}
 if(racer[0x20]==3)return;
 switch(racerState->state) {
 case 0: break;
 case 1:
  if(math_fast_float_d(&racerState->timer) && (D_00138320&5)) {
   racerState->timer=3;moby_transform_joint_to_world(racer,((racerState->duration^1)&1),origin);
   if(racerState->elevated)vec_build_spherical_offset(dir,racerState->length+0.5f,F(racer,0xf8),-racerState->tilt);
   else vec_build_spherical_offset(dir,racerState->length+0.5f,F(racer,0xf8),-F(racer,0xf4));
   add_vectors(temp,origin,dir);SpawnHomingShot(racer,origin,dir,120);PlayMobySound(7,0,racer);
   if(math_fast_float_d(&racerState->duration))racerState->state=0;
  }return;
 case 2: {
  unsigned char *target; float tilt;
  if(math_fast_float_d(&racerState->timer) && (D_00138324&5)) {
   yaw=0;extra=0;racerState->timer=30;moby_transform_joint_to_world(racer,((racerState->duration^1)&1),origin);tilt=F(racer,0xf8);
   if(racerState->elevated)vec_build_spherical_offset(dir,racerState->length+0.5f+racerState->height,tilt,yaw);
   else {vec_build_spherical_offset(dir,racerState->length+0.5f+racerState->height,tilt,-F(racer,0xf4));yaw=F(racer,0xf4);}
   pitch=tilt;yaw-=0.3490659f;
   target=bike_find_aim_target(racer,origin,dir,&aimPitch,&aimYaw,&extra,0.78539824f,30);
   if(target) {
    FastVecSub(delta,origin,target+16);
    if(func_L00_002EE290(delta)<25) {pitch=aimPitch;yaw=aimYaw;}
   } else {aimPitch=pitch;aimYaw=yaw;extra=0.2f;}
   queue_copy_record_by_index(47);add_vectors(temp,origin,dir);
   homing_rocket_spawn(racer,origin,target,aimPitch,aimYaw,extra,pitch,yaw);PlayMobySound(8,0,racer);
   if(math_fast_float_d(&racerState->duration))racerState->state=0;
  }return; }
 case 3:
  if(math_fast_float_d(&racerState->timer) && (D_00138324&5)) {
   racerState->timer=30;FastVecAdd(temp,racer+16,racerState->offset);*(AttackQuad *)origin=*(AttackQuad *)temp;shield_dome_spawn(racer,origin);
   if(math_fast_float_d(&racerState->duration))racerState->state=0;
  }
  break;
 }
}
