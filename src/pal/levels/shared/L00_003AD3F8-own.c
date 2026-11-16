#include "common.h"
typedef int Quad9C58 __attribute__((mode(TI)));
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void cam_compute_view_direction(void *,void *,int);
extern void part_steer_effect_direction(int,void *,int);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern void lerp_vector(void *,void *,void *,float),vec_fast_normalize(void *,void *,void *);
extern float FastVecLength(void *),FastVecDot(void *,void *);
extern float IntToFloat(int),FastAddRotations(float,float),math_fast_sin_or_cos_b(float),math_fabs(float);
extern int FastDecTimer(void *),math_fast_float_d(void *),math_random_int_below(int);
extern void LerpVector4(void *,void *,void *,float);
extern char *SpawnSpinningSparkParticle(void *,float,float,float,int,void *,float,unsigned int,int);
extern int CollLine(void *,void *,int,void *,int),coll_test_point(void *,int,int,float);
extern int PlayMobySound(int,int,void *);
extern void snd_stop_voice(int),cam_flag_entry_for_hero_mode(void),table_clear_entry_flag(int),moby_mark_spawned(void *),vec_transform_or_copy(void *,void *),part_queue_ground_shadow(void *,float);
extern void projectile_damage_nearby_on_hit(void *,void *,void *,int);
extern char *SpawnExplosion(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
typedef struct { char pad0[10]; union { short lifetime; unsigned char bytes[2]; } age; } Particle9C58;
typedef struct { char pad0[4]; int type; char pad8[2]; unsigned char alpha,life; } Payload9C58;
extern char g_default_vector[] MACRO_ADDR;
extern char g_hero_l00_position[] MACRO_ADDR;
typedef struct { char pad0[0x18]; char *hit; char pad1C[0x14]; float position[4],normal[4]; } Collision9C58;
extern Collision9C58 g_collision_result;
extern char g_scratch_vec_pair[];
typedef struct {
 char pad0[0x1E0]; short control_state; char pad1E2[0x1230-0x1E2];
 int control_mask; char pad1234[0x1248-0x1234]; int state;
 char pad124C[0x2290-0x124C]; int collision_flags; int weapon;
} Hero9C58;
extern Hero9C58 g_hero_state;
typedef struct {
 char pad0[0x108]; float axis_x,axis_y; char pad110[0x1A0-0x110];
 int held,pressed;
} Pad9C58;
extern Pad9C58 g_pad_state;
extern char g_sound_state[];
extern int g_active_tether_object __attribute__((sda));
void func_PAL_L00_003AD3F8(char *m)
{
 float old[4],direction[4],a[4],b[4],c[4];
 char *d=*(char **)(m+0x68),*p;
 int i,n,prior;float scale,speed,t,bounce;
 cam_compute_view_direction(m+0x10,direction,1);
 H(d,0x14)++;
 qcopy(old,m+0x10);
 part_steer_effect_direction(I(d,0x48),d,0);
 scale=0.45f;
 FastVecAdd(m+0x10,m+0x10,d);
 FastDecTimer(d+0x2C);
 if(H(d,0x2C)) {
 short life=42;
 for(i=0;i<3;i++) {
   float third=0.3333f; float one=1.0f; int type=2;
   *(Quad9C58 *)b=*(Quad9C58 *)(m+0x10);
   LerpVector4(a,old,b,IntToFloat(i)*third);
   n=math_random_int_below(6);if(math_random_int_below(2))n=-n;
   t=H(d,0x2C)/IntToFloat(42)*70000.0f+10000.0f;
   { Particle9C58 *particle=(Particle9C58 *)SpawnSpinningSparkParticle(a,0.025f,one,one,n,g_default_vector,t,0x80808080,1);
   if(particle) {
     Payload9C58 *payload;
     particle->age.lifetime=life;
     payload=(Payload9C58 *)((char *)particle+32);
     payload->type=type;payload->alpha=127;
     { int l=particle->age.lifetime&0xFF; payload->life=l; }
   } }
 }
 }
 if(H(d,0x14)<6) {scale=IntToFloat(H(d,0x14))/IntToFloat(6);scale*=0.45f;
 qcopy(a,m+0x10);
 FastVecScale(b,direction,F(d,0x20));FastVecSub(c,m+0x10,b);
 if(CollLine(a,c,18,m,0))FastVecAdd(m+0x10,g_hero_l00_position,b);
 }
 F(d,0x24)=FastAddRotations(F(d,0x24),0.025f);
 FastVecScale(a,direction,F(d,0x28));FastVecSub(m+0x10,m+0x10,a);
 F(d,0x28)=math_fast_sin_or_cos_b(F(d,0x24))*0.25f;
 FastVecScale(a,direction,F(d,0x28));FastVecAdd(m+0x10,m+0x10,a);
 F(m,0xF0)=FastAddRotations(F(m,0xF0),F(d,0x30));
 F(m,0xF4)=FastAddRotations(F(m,0xF4),F(d,0x34));
 F(m,0xF8)=FastAddRotations(F(m,0xF8),F(d,0x38));
 math_fast_float_d(d+0x44);
 if(coll_test_point(m+0x10,0,g_hero_state.collision_flags,scale)) {
   qcopy(m+0x10,g_collision_result.position);
   speed=FastVecLength(d);bounce=speed*0.25f;if(bounce<0.04000000283122063f)bounce=0.04000000283122063f;
   if(g_collision_result.hit) {
     FastVecSub(a,m+0x10,g_collision_result.hit+0x10);
     t=FastVecDot(direction,a);FastVecScale(b,direction,t);
     FastVecAdd(c,g_collision_result.hit+0x10,b);
     FastVecSub(a,m+0x10,c);vec_fast_normalize(d,d,a);
   } else {
     FastVecScale(a,g_collision_result.normal,0.0009765625f);vec_scale_to_length(a,a,1.0f);
     t=FastVecDot(a,direction);t=math_fabs(t);if(t>=0.8f)bounce=speed;
     vec_fast_normalize(d,d,a);
   }
   if(!I(d,0x44)) {PlayMobySound(2,0,m);I(d,0x44)=12;}
   vec_scale_to_length(d,d,bounce);
 }
 lerp_vector(d,d,d+0x50,0.01f);
 p=g_sound_state+I(d,0x40)*0x70;
 if(*(char **)(p+0x88)!=m || !B(p,0x74)) I(d,0x40)=PlayMobySound(0,4,m);
 if(!((g_pad_state.pressed&g_hero_state.control_mask) ||
       (!(g_pad_state.held&g_hero_state.control_mask) && H(d,0x2E)>17) ||
       ((g_hero_state.state!=25 && g_hero_state.state!=70) || B(m,0x20)==1)))goto steer;
 if(H(d,0x14)>=18) {
   B(m,0x20)=1;prior=H(d,0x16);
   if(FastDecTimer(d+0x16)) {
     snd_stop_voice(I(d,0x40));PlayMobySound(1,0,m);
     if(!prior)SpawnExplosion(m+0x10,1,40,20,30,40,50,1,1,1,0,g_active_tether_object,1.5f,20.0f);
     else SpawnExplosion(m+0x10,1,20,15,30,15,30,1,1,0,0,g_active_tether_object,0.6f,20.0f);
     projectile_damage_nearby_on_hit(m,d,m+0x10,1);goto destroy;
   }
 }
steer:
 if(g_pad_state.held&g_hero_state.control_mask) {
   H(d,0x2E)++;
   if(g_hero_state.weapon!=49)g_hero_state.control_state=2;
   cam_flag_entry_for_hero_mode();
   if(g_pad_state.axis_x!=0 || g_pad_state.axis_y!=0) {
     float speed2=FastVecLength(d);
     if(speed2!=0) {
       FastVecScale(a,g_scratch_vec_pair,-g_pad_state.axis_x*0.005000000353902578f);FastVecAdd(d,d,a);
       FastVecScale(a,g_scratch_vec_pair+16,-g_pad_state.axis_y*0.0010000000474974513f);FastVecAdd(d,d,a);
       vec_scale_to_length(d,d,speed2);
     }
   }
 }
 if(F(m,0x10)<2 || F(m,0x10)>1021 || F(m,0x14)<2 || F(m,0x14)>1021 || F(m,0x18)<2 || F(m,0x18)>1021) {
destroy:
   table_clear_entry_flag(I(d,0x48));moby_mark_spawned(m);
 } else {vec_transform_or_copy(m+0x10,m+0x10);part_queue_ground_shadow(m,0.5f);}
}
