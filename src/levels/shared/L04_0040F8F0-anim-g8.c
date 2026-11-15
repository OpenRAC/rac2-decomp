/* func_L04_004167B0 needs -G8 and -g (the line labels give the nop pair before its
 * div.s), so it has a unit of its own; see config/cflags.txt. */
#include "common.h"
typedef int Quad1006 __attribute__((mode(TI)));
typedef struct { char pad0[0x24]; float scale; } Model1006;
typedef struct {
 char pad0[0x10];
 Quad1006 pos;
 char pad20[0x4];
 Model1006 * model;
 char pad28[0x4];
 float scale;
 u8 state;
 u8 enabled;
 s16 opacity;
 u16 flags;
 char pad36[0xc];
 u8 animState;
 u8 anim;
 char pad44[0x4];
 float animSpeed;
 char pad4c[0x14];
 u8 flags60;
 char pad61[0x5f];
 Quad1006 axis0;
 Quad1006 axis1;
 Quad1006 axis2;
 Quad1006 rotation;
} Object1006;


#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(void **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))

extern int D_L04_001B08F0 __attribute__((sda));
extern float mat_fast_helper_a(float,float);
extern float FastAddRotations(float,float);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float math_fabs(float);
extern float fast_subtract_rotations(float,float);
extern float math_approach_with_velocity(void *,float,void *,float,float,float,int);
extern char *g_moby_l04_pool;
extern float D_0018C2D8 NOT_SDA;
extern float D_00138288 NOT_SDA;
extern float D_0018A138 NOT_SDA;
/* Read as D_001A7A40[1]: an sda array at a nonzero offset is one unsplit lui+lbu pair. */
extern unsigned char D_001A7A40[] __attribute__((sda));
extern unsigned char D_00139605 NOT_SDA;
extern int g_race_time_ticks __attribute__((sda));
extern Object1006 *D_L04_001B08F4 __attribute__((sda));
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void anim_start_blended(void *,int,int,int);
extern void math_fast_float_d(void *);
extern void FastVecSub(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern void *CreateMoby(int);
extern void moby_init_child_from_parent(void *,void *);
extern void moby_copy_joint_transform_to_object(void *,void *,int,int);
extern void moby_transform_joint_point(void *,int,void *);
extern void mat_build_rotation_from_angles(void *,void *);
extern void racer_spawn_exhaust_effects(void *);
extern void EmitTrailEffects(char *,void *,void *,float);

/* Animates the racer bike and its rider each frame: leans the bike in turns, plays the rider animations, positions the second effect object and updates the trail effects. */
void racer_update_bike_animation(char *moby,char *vars) {
 float v[4] __attribute__((aligned(16)));
 float matrix[16] __attribute__((aligned(16)));
 float speed_sum,lean_squared,speed_blend,target,scale,lean_curve,angle,period=0.5f; Object1006 *obj;
 if(!B(moby,0xbc)) return;
 speed_sum=F(vars,0x30c)+F(vars,0x27c);
 if(speed_sum<0.083333336f) speed_sum=0.083333336f;
 lean_squared=F(vars,0x308)*13.750985f;
 speed_blend=speed_sum*3.0f;
 lean_curve=F(vars,0x308)*22.918308f;
 lean_squared*=math_fabs(lean_squared);
 lean_curve=1.0f-(1.0f-lean_curve)*(1.0f-lean_curve);
 if(speed_blend>1.0f) speed_blend=1.0f;
 if(F(vars,0x4c8)!=0.0f) {
  if(math_fabs(F(moby,0xf0)-F(vars,0x4c8))<0.003f) F(vars,0x4c8)=0;
  scale=5.0f;
  target=F(vars,0x4c8);
 } else {
  scale=1.0f;
  target=(1.0f-speed_blend)*lean_squared+speed_blend*lean_curve;
  if(target>1.0f) target=1.0f;
  if(target<-1.0f) target=-1.0f;
  target*=-0.52359885f;
  if(B(moby,0x20)!=3 && D_0018C2D8<0.2f) target=0;
 }
 math_approach_with_velocity(moby+0xf0,target,vars+0x300,scale*0.035f,0.45f,scale*0.027634384f,0);
 obj=(Object1006 *)(g_moby_l04_pool+(I(vars,0x1dc)<<8));
 if(obj) {
  obj->scale=obj->model->scale*0.25f;
  obj->opacity=127; obj->enabled=1;
  obj->pos=*(Quad1006 *)(moby+0x10); obj->rotation=*(Quad1006 *)(moby+0xf0);
  obj->state=0;
  func_002A05A8(obj);func_002A0F48(obj);
  obj->flags|=6;
  if((obj->flags60&2) && (unsigned)(obj->animState-2)<4) anim_start_blended(obj,0,0,3);
  if(!I(vars,0x36c)) {
   if(H(vars,0x274) && (obj->anim==0 || obj->anim==2)) anim_start_blended(obj,1,0,12);
   if(!H(vars,0x274) && obj->anim==1) {
    if(H(vars,0x276)>=16) anim_start_blended(obj,2,0,3);
    else anim_start_blended(obj,0,0,6);
   }
  } else math_fast_float_d(vars+0x36c);
  if(obj->anim<2) {
   obj->animSpeed=F(vars,0x30c)*3.0f/period;
   if(F(vars,0x30c)>0.33333334f) obj->animSpeed*=3.0f;
  }
  if(B(moby,0xbc)==5) {
   F(vars,0x428)=D_00138288*-0.5f;
   F(vars,0x424)=math_fabs(F(moby,0xf0))*-0.6f-F(moby,0xf4);
  } else { F(vars,0x424)=F(vars,0x428)=0; }
  if(P(vars,0x3b0) && g_race_time_ticks>=121) {
   FastVecSub(v,(char *)P(vars,0x3b0)+0x10,moby+0x10);
   if(func_L00_002EE290(v)<9.0f) {
    angle=mat_fast_helper_a(v[0],v[1]);
    angle=fast_subtract_rotations(F(moby,0xf8),angle);
    if(math_fabs(angle)<1.5707964f) {
     if(I(vars,0x3b4)<180) { I(vars,0x424)=0; F(vars,0x428)=-angle; }
     I(vars,0x3b4)++;
    }
    if(I(vars,0x3b4)>=601) I(vars,0x3b4)=0;
   }
  }
  if(D_001A7A40[1]) F(vars,0x430)=2.5f; else F(vars,0x430)=1.0f;
  moby_update_eased_node(obj,vars+0x3c0,0,0.08f,0.5f);
  if(!D_L04_001B08F4) {
   if(D_00139605) D_L04_001B08F4=CreateMoby(0x12df /* moby class 4831 */); else D_L04_001B08F4=CreateMoby(0x50a /* moby class 1290 */);
   if(D_L04_001B08F4) {
    moby_init_child_from_parent(D_L04_001B08F4,obj);
    D_L04_001B08F4->scale=D_L04_001B08F4->model->scale*0.25f;
    D_L04_001B08F4->flags|=0x106;
   }
  } else {
   moby_copy_joint_transform_to_object(obj,D_L04_001B08F4,1,0);
   moby_transform_joint_point(obj,1,matrix);
   FastVecScale(v,matrix+8,-0.03f);
   FastVecAdd((char *)D_L04_001B08F4+0x10,(char *)D_L04_001B08F4+0x10,v);
   qcopy_nc((char *)D_L04_001B08F4+0xc0,matrix);
   qcopy_nc((char *)D_L04_001B08F4+0xd0,matrix+4);
   qcopy_nc((char *)D_L04_001B08F4+0xe0,matrix+8);
   func_002A05A8(D_L04_001B08F4);func_002A0F48(D_L04_001B08F4);
  }
 }
  if(D_L04_001B08F0) {
   *(Quad1006 *)v=*(Quad1006 *)(moby+0x10);v[2]=D_0018A138;*(Quad1006 *)matrix=*(Quad1006 *)(moby+0x10);
   EmitTrailEffects(moby,matrix,vars+0x290,F(vars,0x30c)+F(vars,0x27c));
  }
  F(vars,0x6c0)=FastAddRotations(F(vars,0x6c0),(F(vars,0x30c)+F(vars,0x27c)*4.0f)*0.2f+0.01f);
  mat_build_rotation_from_angles(vars+0x450,vars+0x6c0);
  racer_spawn_exhaust_effects(moby);
}
