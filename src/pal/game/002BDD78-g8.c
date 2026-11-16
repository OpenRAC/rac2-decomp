#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int moby_forward_two_values_and_amount(int,int,float);
extern void FastVecAdd(void *,void *,void *);
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern float g_frame_time_scale __attribute__((sda));
extern float fast_vec_dist(void *,void *);
extern char g_camera_eye_state[];
extern char *part_spawn_falling_drop(void *,void *,int,int,float,int,int);
typedef struct { float v[4]; } GravityTable;
extern GravityTable g_falling_drop_gravity;

void part_update_falling_drop_pal(char *p)
{
 char *q=p+32,*pos;
 struct { Quad saved; GravityTable gravity; } local;
 float f,d,size;
 int color,alpha,other,kind;
 local.gravity=g_falling_drop_gravity;
 if(*(short *)(q+26)==3 && g_frame_time_scale>0.95f) FastDecTimer(p+10);
 if(FastDecTimer(p+10)) {part_kill(p);return;}
 pos=p+16;
 f=IntToFloat(*(short *)(p+10));
 *(int *)(p+4)=moby_forward_two_values_and_amount(*(int *)(q+20),*(int *)(q+16),f/IntToFloat(*(short *)(q+24)));
 alpha=*(int *)(p+4)>>24;
 d=fast_vec_dist(pos,g_camera_eye_state);
 if(*(short *)(p+10)<5) alpha=alpha* *(short *)(p+10)/5;
 if(d<4.0f) {part_kill(p);return;}
 if(d<8.0f) alpha=FloatToInt(IntToFloat(alpha)*(d-4.0f)*0.25f);
 *(int *)(p+4)=(alpha<<24)|(*(int *)(p+4)&0xffffff);
 FastVecAdd(pos,pos,q);
 kind=*(short *)(q+26);
 *(float *)(q+8)-=local.gravity.v[kind];
 qcopy(&local.saved,pos);
 if(*(float *)(p+24)<*(float *)(q+12)) {
  if(kind==1) {
   f=math_random_float_range(0.25f,1.0f);
   color=moby_forward_two_values_and_amount(0x7f000000,0x7f182030,f);
   f=math_random_float_range(0.5f,1.0f);
   other=moby_forward_two_values_and_amount(0,0x5f5f5f,f);
   *(float *)(q+8)=0.0f;
   size=math_random_float_range(200000.0f,300000.0f);
   part_spawn_falling_drop(pos,q,color,other,size,math_random_int_range(75,125),3);
  }
  part_kill(p);
 } else p[8]=(unsigned char)p[8]+1;
}
