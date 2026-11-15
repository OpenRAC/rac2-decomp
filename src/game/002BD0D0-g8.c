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
extern float D_001B168C __attribute__((sda));
extern float fast_vec_dist(void *,void *);
extern char g_camera_eye_state[];
extern char *part_spawn_falling_drop(void *,void *,int,int,float,int,int);
typedef struct { float v[4]; } GravityTable;
extern GravityTable D_001AA350;
/* Updates a falling drop. It falls, fades near the end and near the camera, and splashes into a small drop when it lands. */
void part_update_falling_drop(char *particle)
{
 char *motion=particle+32,*pos;
 struct { Quad saved; GravityTable gravity; } local;
 float life_ratio,camera_distance,size;
 int color,alpha,end_color,drop_type;
 local.gravity=D_001AA350;
 if(*(short *)(motion+26)==3 && D_001B168C>0.95f) FastDecTimer(particle+10);
 if(FastDecTimer(particle+10)) {part_kill(particle);return;}
 pos=particle+16;
 life_ratio=IntToFloat(*(short *)(particle+10));
 *(int *)(particle+4)=moby_forward_two_values_and_amount(*(int *)(motion+20),*(int *)(motion+16),life_ratio/IntToFloat(*(short *)(motion+24)));
 alpha=*(int *)(particle+4)>>24;
 camera_distance=fast_vec_dist(pos,g_camera_eye_state);
 if(*(short *)(particle+10)<6) alpha=alpha* *(short *)(particle+10)/6;
 if(camera_distance<4.0f) {part_kill(particle);return;}
 if(camera_distance<8.0f) alpha=FloatToInt(IntToFloat(alpha)*(camera_distance-4.0f)*0.25f);
 *(int *)(particle+4)=(alpha<<24)|(*(int *)(particle+4)&0xffffff);
 FastVecAdd(pos,pos,motion);
 drop_type=*(short *)(motion+26);
 *(float *)(motion+8)-=local.gravity.v[drop_type];
 qcopy(&local.saved,pos);
 if(*(float *)(particle+24)<*(float *)(motion+12)) {
  if(drop_type==1) {
   life_ratio=math_random_float_range(0.25f,1.0f);
   color=moby_forward_two_values_and_amount(0x7f000000,0x7f182030,life_ratio);
   life_ratio=math_random_float_range(0.5f,1.0f);
   end_color=moby_forward_two_values_and_amount(0,0x5f5f5f,life_ratio);
   *(float *)(motion+8)=0.0f;
   size=math_random_float_range(200000.0f,300000.0f);
   part_spawn_falling_drop(pos,motion,color,end_color,size,math_random_int_range(90,150),3);
  }
  part_kill(particle);
 } else particle[8]=(unsigned char)particle[8]+1;
}
