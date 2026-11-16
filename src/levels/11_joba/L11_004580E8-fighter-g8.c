#include "names.h"
/* func_L11_004580E8 (2,476 bytes, Joba level 11 only). Own unit:
 * -O2 -G8 -ffunction-sections -g -frac2-sched-call-addr-float -frac2-la-float-vars-last
 * (config/cflags.txt). Case 0 stores its floats in retail's order (0x4C gravity, then 0x20,
 * 0x28, 0x2C, 0x30, 0x50 limit, 0x54 0.1f). -frac2-sched-call-addr-float keeps a call's
 * address MEM from depending on pending FP stores (case 5's store order);
 * -frac2-la-float-vars-last allocates FP user variables after temporaries in local-alloc, so
 * 0.1 takes $f0 before gravity and limit (case 0), as retail (docs/build/compiler-notes.md).
 * Owner standard of 12 November 2026; forced on everywhere they change 136 and 436 functions.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int FloatToInt(float);
extern float IntToFloat(int),math_random_float_range(float,float),vec_length_xy(void *),FastAddRotations(float,float),vec_distance_squared_xy(void *,void *);
extern int math_random_int_below(int),CollLine(void *,void *,int,void *,int),coll_test_point(void *,int,void *,float),flag_set_first_pending(void *),math_fast_float_d(void *),snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern void *part_find_owned_effect_slot(void *,unsigned int,int);
extern int moby_turn_toward_target_and_step(void *,void *,float);
extern float math_step_value_toward_target(void *,void *,float,float,float,float);
extern int FastDecTimer(void *);
extern void moby_set_state(void *,int,int),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float),vec_fast_normalize(void *,void *,void *),LerpVector4(void *,void *,void *,float),snd_stop_voice(int),part_init_effect_record(void *,void *,int,float);
extern void gfx_add_draw_callback_third(void (*)(void *),void *);
extern int coll_process_hit(float,void *,int,void *,void *);
typedef struct { int unused; int mode; short unused8; u8 alpha, duration; } ParticleAttributes;
typedef struct { char unused[10]; s16 lifetime; char unused12[20]; ParticleAttributes attributes; } Particle;
extern Particle *SpawnSpinningSparkParticle(void *,int,float,float,float,void *,unsigned,int,float);
extern char *arena_get_center_point(void *);
extern char *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern void joba_shot_spawn_smoke(void *);
typedef struct { char pad0[0x18]; char *hit; int count; float point[4]; float pad30[4]; float normal[4]; } Collision;
extern Collision g_collision_l11_result;
extern char g_sound_state[];
/* Whether the moby hit belongs to the same class as this one's owner. */
static inline int func_IsOwnerClass(char *hit,char *vars) {
 int same=0;
 if(hit && *(char **)(vars+0x15C))same=*(s16 *)(hit+0xAA)==*(s16 *)(*(char **)(vars+0x15C)+0xAA);
 return same;
}
extern Quad g_identity_l11_matrix;
extern float g_joba_shot_probe_distance SDATA(D_L11_001B1F80);
extern float g_joba_shot_speed_scale SDATA(D_L11_001B1F88);
extern float g_joba_shot_bounce_scale SDATA(D_L11_001B1F8C);
extern float g_joba_shot_height_offset SDATA(D_L11_001B1F94);
extern float g_joba_shot_float_param SDATA(D_L11_001B1F98);
extern float g_joba_shot_explosion_size SDATA(D_L11_001B1FA8);
extern float g_joba_shot_hit_damage SDATA(D_L11_001B1FAC);
extern float g_joba_shot_trigger_distance SDATA(D_L11_001B1F9C);
extern int g_joba_shot_lifetime SDATA(D_L11_001B1F84);
extern int g_joba_shot_max_bounces SDATA(D_L11_001B1F90);
extern int g_joba_shot_duration SDATA(D_L11_001B1FA4);
typedef struct { float x,y,z; } FadeColor;
extern FadeColor g_joba_shot_fade_color;
/* Per-frame update of a flying shot (moby class 3616): it bounces off walls, fades its colour, explodes with damage when done, and drops out if it falls below the floor. */
void joba_shot_update(char *moby) {
 char *vars=*(char **)(moby+0x68),*other,*entry;
 union { struct { float a[4],b[4],c[4]; } v; char damage[48]; } scratch;
 float f; int i,n; unsigned int r,g,blue;
 switch(*(u8 *)(moby+0x20)) {
 case 0: {
  *(u8 *)(vars+0x148)=FloatToInt(15);*(u8 *)(vars+0x14A)=FloatToInt(4);
  {float speed, max, damping, turn, gravity, limit;
  *(float *)(vars+0x160)=math_random_float_range(-*(float *)(vars+0x160),*(float *)(vars+0x160))*0.017453294f;
  *(u8 *)(moby+0x30)=128;*(int *)(vars+0x24)=0;
  speed=0.3f;max=0.75f;damping=0.5f;turn=1.134464144706726f;gravity=0.0027777778450399637f;limit=0.523598849773407f;
  *(u8 *)(vars+0x128)=3;*(int *)(vars+0x130)=0;
  *(float *)(vars+0x4C)=gravity;
  *(float *)(vars+0x20)=speed;*(float *)(vars+0x28)=max;*(float *)(vars+0x2C)=damping;*(float *)(vars+0x30)=turn;*(float *)(vars+0x50)=limit;*(float *)(vars+0x54)=0.1f;
  *(int *)(vars+0x58)|=0x14;*(float *)(moby+0x2C)*=g_joba_shot_speed_scale;*(int *)(vars+0x170)=-1;
  *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)&0xEFFF)|0x41;*(int *)(moby+0x98)=0;
  }
  moby_set_state(moby,1,-1);return;
 }
 case 2:case 3:
  FastVecAdd(scratch.v.a,moby+0x10,vars+0xC0);
  *(float *)(vars+0xC8)-=*(float *)(vars+0x4C);
  if(*(u8 *)(moby+0x20)==3 && *(float *)(vars+0xC8)<0) *(u8 *)(moby+0x20)=2;
  FastDecTimer(vars+0x16C);
  if(*(s16 *)(vars+0x16C)) {
   Quad *axis=&g_identity_l11_matrix;
   for(i=0;i<3;i++) {
    *(Quad *)scratch.v.c=*(Quad *)(moby+0x10);LerpVector4(scratch.v.b,scratch.v.c,scratch.v.a,(float)i*0.3333f);
    n=math_random_int_below(6);if(math_random_int_below(2))n=-n;
    f=IntToFloat(g_joba_shot_lifetime);
    {
    int life=120,mode=2,alpha=127;
    float scale=45000;
    Particle *particle=SpawnSpinningSparkParticle(scratch.v.b,n,0.025f,1,1,axis,0x80808080,0,
      ({float lifetime=(float)*(s16 *)(vars+0x16C)/f;
        lifetime*scale+5000;}));
    if(particle) {ParticleAttributes *attributes;particle->lifetime=life;attributes=&particle->attributes;attributes->mode=mode;attributes->alpha=alpha;attributes->duration=(u8)particle->lifetime;}
    }
   }
  }
  if(CollLine(moby+0x10,scratch.v.a,0,moby,0) && !func_IsOwnerClass(g_collision_l11_result.hit,vars)) qcopy(moby+0x10,g_collision_l11_result.point);
  else qcopy(moby+0x10,scratch.v.a);
  if(!coll_test_point(moby+0x10,0,moby,g_joba_shot_probe_distance))break;
  if(*(u8 *)(moby+0x20)!=2) {Collision *col=&g_collision_l11_result;if(!(*(float *)(moby+0x18)-col->point[2]<0))break;}
  {Collision *col=&g_collision_l11_result;
  if(func_IsOwnerClass(col->hit,vars))break;}
  vec_scale_to_length(scratch.v.b,g_collision_l11_result.normal,g_joba_shot_probe_distance);
  FastVecAdd(moby+0x10,g_collision_l11_result.point,scratch.v.b);
  vec_fast_normalize(vars+0xC0,vars+0xC0,g_collision_l11_result.normal);
  PlayMobySound(1,0,moby);
  if(*(u8 *)(moby+0x20)==2) {float bounce;*(u8 *)(moby+0x20)=3;bounce=g_joba_shot_bounce_scale;(*(u16 *)(vars+0x16E))++;FastVecScale(vars+0xC0,vars+0xC0,bounce);}
  if(*(s16 *)(vars+0x16E)>=g_joba_shot_max_bounces) *(u8 *)(moby+0x20)=5;
  break;
 case 4: {
  float f;
  if(flag_set_first_pending(moby)){int duration=g_joba_shot_duration;*(int *)(vars+0x150)=duration;*(float *)(vars+0x154)=1/IntToFloat(duration);}
  *(FadeColor *)scratch.v.a=g_joba_shot_fade_color;
  f=(float)*(int *)(vars+0x150)**(float *)(vars+0x154);
  r=FloatToInt((scratch.v.a[0]-255)*f+255);g=FloatToInt(scratch.v.a[1]*f);blue=FloatToInt(scratch.v.a[2]*f);
  {unsigned int color=blue<<16;
  color|=0xFF000000;
  color|=g<<8;
  color|=r;
  *(unsigned int *)(moby+0x78)=color;}
  if(math_fast_float_d(vars+0x150))moby_set_state(moby,6,-1);
  break;
 }
 case 5: {
  float f,t;
  if(flag_set_first_pending(moby)) {
   moby[0xBC]=0;f=math_random_float_range(15,40)*0.017453294f;if(math_random_int_below(2))f=-f;
   t=g_joba_shot_float_param;
   *(float *)(vars+0x160)=f;moby_set_controller_speed_limits(moby,(t+t)*0.00027777778450399637f,t*0.01666666753590107f,0.0011635529808700085f,0.10471977293491364f);
  } else if(!*(u8 *)(moby+0xBC)) {
   other=arena_get_center_point(*(void **)(moby+0xB8));
   if(*(float *)(moby+0x18)<*(float *)(other+8)+g_joba_shot_height_offset) {
    float *height=(float *)(moby+0x18);
    other=arena_get_center_point(*(void **)(moby+0xB8));
    math_step_value_toward_target(height,vars+0xC8,*(float *)(other+8)+g_joba_shot_height_offset,*(float *)(vars+0x40),*(float *)(vars+0x40),*(float *)(vars+0x48));
   }else moby[0xBC]=1;
  }else if(*(u8 *)(moby+0xBC)==1) {
   if(*(u8 *)(moby+0x31))moby_turn_toward_target_and_step(moby,*(char **)(vars+0x164)+16,*(float *)(vars+0x160));
   other=arena_get_center_point(*(void **)(moby+0xB8));*(float *)(moby+0x18)=*(float *)(other+8)+g_joba_shot_height_offset;
   if(*(u8 *)(moby+0x31)) {f=vec_distance_squared_xy(moby+0x10,*(char **)(vars+0x164)+16);if(f<g_joba_shot_trigger_distance*g_joba_shot_trigger_distance)moby_set_state(moby,4,-1);}
  }
  if(!snd_is_voice_playing_for_owner(moby,*(int *)(vars+0x170))) *(int *)(vars+0x170)=PlayMobySound(2,4,moby);
  break;
 }
 case 6:
  if(flag_set_first_pending(moby)) {
   SpawnExplosion(moby+16,1,10,10,2,20,60,1,g_joba_shot_explosion_size,0,1,1,0,0);
   PlayMobySound(0,0,moby);part_init_effect_record(scratch.damage,moby,0x810001,*(float *)(vars+0x158));
   scratch.damage[24]=2;scratch.damage[25]=1;*(u16 *)(scratch.damage+26)=*(u16 *)(moby+0xAA);
   coll_process_hit(g_joba_shot_hit_damage,moby+16,16,moby,scratch.damage);
   *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;moby_set_state(moby,1,-1);
  if(snd_is_voice_playing_for_owner(moby,*(int *)(vars+0x170))) {
   int sound=*(int *)(vars+0x170);if(sound!=-1){entry=g_sound_state+sound*0x70;if(*(char **)(entry+0x88)==moby&&*(u8 *)(entry+0x74))snd_stop_voice(sound);}
   *(int *)(vars+0x170)=-1;
  }return;
  }
  break;
 default: case 1: break;
 }
 {
  float f;
  float min,max;
  f=vec_length_xy(vars+0xC0);min=0.0033333336468786f;max=0.10000000894069672f;
  if(f<min)f=min;if(f>max)f=max;
  f=f-min;
  *(float *)(moby+0xF4)=FastAddRotations(
    ({float fraction=f/0.09666667878627777f;
      (fraction*7+1)*0.017453294f;}),*(float *)(moby+0xF4));
 }
 if(*(u8 *)(moby+0x20)>=2)gfx_add_draw_callback_third(joba_shot_spawn_smoke,moby);
 if(*(void **)(moby+0xB8)) {other=arena_get_center_point(*(void **)(moby+0xB8));if(*(float *)(moby+0x18)<*(float *)(other+8)-1){*(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;moby_set_state(moby,1,-1);}}
 if(part_find_owned_effect_slot(moby,0x10000,0))moby_set_state(moby,6,-1);
 *(u8 *)(moby+0xA8)=255;if(*(u16 *)(moby+0x96)<0xFFFF)(*(u16 *)(moby+0x96))++;
}
