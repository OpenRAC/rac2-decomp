#include "names.h"
/* func_PAL_L11_0045DCE0 (2,500 bytes): the PAL copy of func_L11_004580E8
 * (src/levels/11_joba/L11_004580E8-fighter-g8.c). 50 Hz changes: gravity 1/360 -> 0.004, particle
 * life 120 -> 100, spark frame count n -> (n * 5 + 2) / 6, case 5 rates and the spin clamp
 * (0.004..0.12) rescaled. A `Quad *c` for scratch.v.c makes gcse PRE number sp+0x40 before sp+0x30.
 * -frac2-sched-fp-const-temp-first orders the particle-loop preheader constants (1.0 first);
 * -frac2-ga-addr-equiv-no-new-save keeps `axis` out of $fp so reload rematerialises it as `la`
 * at the call, as in the v1.01 copy.
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
void func_PAL_L11_0045DCE0(char *p) {
 char *q=*(char **)(p+0x68),*other,*entry;
 union { struct { float a[4],b[4],c[4]; } v; char damage[48]; } scratch;
 float f; int i,n; unsigned int r,g,blue;
 switch(*(u8 *)(p+0x20)) {
 case 0: {
  *(u8 *)(q+0x148)=FloatToInt(15);*(u8 *)(q+0x14A)=FloatToInt(4);
  {float speed, max, damping, turn, gravity, limit;
  *(float *)(q+0x160)=math_random_float_range(-*(float *)(q+0x160),*(float *)(q+0x160))*0.017453294f;
  *(u8 *)(p+0x30)=128;*(int *)(q+0x24)=0;
  speed=0.3f;max=0.75f;damping=0.5f;turn=1.134464144706726f;gravity=0.004f;limit=0.523598849773407f;
  *(u8 *)(q+0x128)=3;*(int *)(q+0x130)=0;
  *(float *)(q+0x4C)=gravity;
  *(float *)(q+0x20)=speed;*(float *)(q+0x28)=max;*(float *)(q+0x2C)=damping;*(float *)(q+0x30)=turn;*(float *)(q+0x50)=limit;*(float *)(q+0x54)=0.1f;
  *(int *)(q+0x58)|=0x14;*(float *)(p+0x2C)*=g_joba_shot_speed_scale;*(int *)(q+0x170)=-1;
  *(u16 *)(p+0x34)=(*(u16 *)(p+0x34)&0xEFFF)|0x41;*(int *)(p+0x98)=0;
  }
  moby_set_state(p,1,-1);return;
 }
 case 2:case 3:
  FastVecAdd(scratch.v.a,p+0x10,q+0xC0);
  *(float *)(q+0xC8)-=*(float *)(q+0x4C);
  if(*(u8 *)(p+0x20)==3 && *(float *)(q+0xC8)<0) *(u8 *)(p+0x20)=2;
  FastDecTimer(q+0x16C);
  if(*(s16 *)(q+0x16C)) {
   Quad *axis=&g_identity_l11_matrix;
   for(i=0;i<3;i++) {float third=0.3333f,scale=45000; /* FAKEMATCH: set-once copies so loop pass 1 hoists both */
    {Quad *c=(Quad *)scratch.v.c;*c=*(Quad *)(p+0x10);LerpVector4(scratch.v.b,c,scratch.v.a,(float)i*third);}
    n=math_random_int_below(6);if(math_random_int_below(2))n=-n;
    f=IntToFloat((g_joba_shot_lifetime*5+2)/6);
    {
    float t=(float)*(s16 *)(q+0x16C)/f*scale+5000;
    Particle *particle;
    particle=SpawnSpinningSparkParticle(scratch.v.b,n,0.025f,1,1,axis,0x80808080,0,t);
    if(particle) {ParticleAttributes *attributes;particle->lifetime=100;attributes=&particle->attributes;attributes->mode=2;attributes->alpha=127;attributes->duration=(u8)particle->lifetime;}
    }
   }
  }
  if(CollLine(p+0x10,scratch.v.a,0,p,0) && !func_IsOwnerClass(g_collision_l11_result.hit,q)) qcopy(p+0x10,g_collision_l11_result.point);
  else qcopy(p+0x10,scratch.v.a);
  if(!coll_test_point(p+0x10,0,p,g_joba_shot_probe_distance))break;
  if(*(u8 *)(p+0x20)!=2) {Collision *col=&g_collision_l11_result;if(!(*(float *)(p+0x18)-col->point[2]<0))break;}
  {Collision *col=&g_collision_l11_result;
  if(func_IsOwnerClass(col->hit,q))break;}
  vec_scale_to_length(scratch.v.b,g_collision_l11_result.normal,g_joba_shot_probe_distance);
  FastVecAdd(p+0x10,g_collision_l11_result.point,scratch.v.b);
  vec_fast_normalize(q+0xC0,q+0xC0,g_collision_l11_result.normal);
  PlayMobySound(1,0,p);
  if(*(u8 *)(p+0x20)==2) {float bounce;*(u8 *)(p+0x20)=3;bounce=g_joba_shot_bounce_scale;(*(u16 *)(q+0x16E))++;FastVecScale(q+0xC0,q+0xC0,bounce);}
  if(*(s16 *)(q+0x16E)>=g_joba_shot_max_bounces) *(u8 *)(p+0x20)=5;
  break;
 case 4: {
  float f;
  if(flag_set_first_pending(p)){int duration=g_joba_shot_duration;*(int *)(q+0x150)=duration;*(float *)(q+0x154)=1/IntToFloat(duration);}
  *(FadeColor *)scratch.v.a=g_joba_shot_fade_color;
  f=(float)*(int *)(q+0x150)**(float *)(q+0x154);
  r=FloatToInt((scratch.v.a[0]-255)*f+255);g=FloatToInt(scratch.v.a[1]*f);blue=FloatToInt(scratch.v.a[2]*f);
  {unsigned int color=blue<<16;
  color|=0xFF000000;
  color|=g<<8;
  color|=r;
  *(unsigned int *)(p+0x78)=color;}
  if(math_fast_float_d(q+0x150))moby_set_state(p,6,-1);
  break;
 }
 case 5: {
  float f,t;
  if(flag_set_first_pending(p)) {
   p[0xBC]=0;f=math_random_float_range(15,40)*0.017453294f;if(math_random_int_below(2))f=-f;
   t=g_joba_shot_float_param;
   *(float *)(q+0x160)=f;moby_set_controller_speed_limits(p,(t+t)*0.0004000000189989805f,t*0.020000001415610313f,0.0016755163669586182f,0.12566372752189636f);
  } else if(!*(u8 *)(p+0xBC)) {
   other=arena_get_center_point(*(void **)(p+0xB8));
   if(*(float *)(p+0x18)<*(float *)(other+8)+g_joba_shot_height_offset) {
    float *height=(float *)(p+0x18);
    other=arena_get_center_point(*(void **)(p+0xB8));
    math_step_value_toward_target(height,q+0xC8,*(float *)(other+8)+g_joba_shot_height_offset,*(float *)(q+0x40),*(float *)(q+0x40),*(float *)(q+0x48));
   }else p[0xBC]=1;
  }else if(*(u8 *)(p+0xBC)==1) {
   if(*(u8 *)(p+0x31))moby_turn_toward_target_and_step(p,*(char **)(q+0x164)+16,*(float *)(q+0x160));
   other=arena_get_center_point(*(void **)(p+0xB8));*(float *)(p+0x18)=*(float *)(other+8)+g_joba_shot_height_offset;
   if(*(u8 *)(p+0x31)) {f=vec_distance_squared_xy(p+0x10,*(char **)(q+0x164)+16);if(f<g_joba_shot_trigger_distance*g_joba_shot_trigger_distance)moby_set_state(p,4,-1);}
  }
  if(!snd_is_voice_playing_for_owner(p,*(int *)(q+0x170))) *(int *)(q+0x170)=PlayMobySound(2,4,p);
  break;
 }
 case 6:
  if(flag_set_first_pending(p)) {
   SpawnExplosion(p+16,1,10,10,2,20,60,1,g_joba_shot_explosion_size,0,1,1,0,0);
   PlayMobySound(0,0,p);part_init_effect_record(scratch.damage,p,0x810001,*(float *)(q+0x158));
   scratch.damage[24]=2;scratch.damage[25]=1;*(u16 *)(scratch.damage+26)=*(u16 *)(p+0xAA);
   coll_process_hit(g_joba_shot_hit_damage,p+16,16,p,scratch.damage);
   *(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;moby_set_state(p,1,-1);
  if(snd_is_voice_playing_for_owner(p,*(int *)(q+0x170))) {
   int sound=*(int *)(q+0x170);if(sound!=-1){entry=g_sound_state+sound*0x70;if(*(char **)(entry+0x88)==p&&*(u8 *)(entry+0x74))snd_stop_voice(sound);}
   *(int *)(q+0x170)=-1;
  }return;
  }
  break;
 default: case 1: break;
 }
 {
  float f;
  float min,max;
  f=vec_length_xy(q+0xC0);min=0.004000000189989805f;max=0.12000000476837158f;
  if(f<min)f=min;if(f>max)f=max;
  f=f-min;
  *(float *)(p+0xF4)=FastAddRotations(
    ({float fraction=f/0.11600000411272049f;
      (fraction*7+1)*0.017453294f;}),*(float *)(p+0xF4));
 }
 if(*(u8 *)(p+0x20)>=2)gfx_add_draw_callback_third(joba_shot_spawn_smoke,p);
 if(*(void **)(p+0xB8)) {other=arena_get_center_point(*(void **)(p+0xB8));if(*(float *)(p+0x18)<*(float *)(other+8)-1){*(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;moby_set_state(p,1,-1);}}
 if(part_find_owned_effect_slot(p,0x10000,0))moby_set_state(p,6,-1);
 *(u8 *)(p+0xA8)=255;if(*(u16 *)(p+0x96)<0xFFFF)(*(u16 *)(p+0x96))++;
}
