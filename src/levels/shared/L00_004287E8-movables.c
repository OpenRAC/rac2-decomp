#include "common.h"

typedef struct Hero_4287E8 {
 char pad0[0x88]; float z;
 char pad8c[0xC]; float yaw;
 char pad9c[0xA38]; char *swing;
 char padad8[8]; float max_height;
 char padae4[0x17B0]; int state;
} Hero_4287E8;
extern Hero_4287E8 D_00189E20_6;
typedef struct CameraGlobals_4287E8 {char pad[0x190];char *follow;} CameraGlobals_4287E8;
extern CameraGlobals_4287E8 D_L00_001B8C80_1;
extern char g_hero_position[];
/* Bank order as the callers set it up: the object pointer travels in a0 either way. */
extern float math_step_spring_damper_stored(float, float, char *, float, float, float);
extern void func_00282CC0_4(char *, char *, char *);
extern f32 ApproachValue(char *,float,float);
extern void FastVecSub(char *,char *,char *);
extern void vec_scale_to_length(char *,char *,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecDot(char *,char *);
extern float FastVecLength(char *);
extern float mat_fast_helper_a(float,float);
extern int FastDecTimer(char *);
extern int g_current_map_index MACRO_ADDR;
extern short *D_L00_001FA920[];
extern char *D_L00_001B1E9C MACRO_ADDR;
/* Updates the swingshot camera each frame. It turns towards the nearest swingshot node the hero is facing, then places the camera behind the hero. */
void cam_swingshot_update(char *camera)
{
 char out[16] __attribute__((aligned(16)));
 char diff[16] __attribute__((aligned(16)));
 char unit[16] __attribute__((aligned(16)));
 float axis[4] __attribute__((aligned(16)));
 char *vars=*(char **)(camera+0x70),*cfg=vars+0xA0,*part=vars+0x40,*angle=vars+0xB8;
 char *swing,*best_node,*node,*turn;
 float height,dist,aim_dot,score,closest;
 short *list;
 if(D_00189E20_6.swing && D_00189E20_6.state==0x2B) {
  float aim_dot=*(float *)(D_00189E20_6.swing+0x18)-D_00189E20_6.z;
  if(aim_dot>D_00189E20_6.max_height) aim_dot=D_00189E20_6.max_height;
  else if(aim_dot<0.0f) aim_dot=0.0f;
  aim_dot/=D_00189E20_6.max_height;
  height=aim_dot+3.65f; dist=aim_dot+aim_dot;
 } else {height=4.64f;dist=2.0f;}
 ApproachValue(*(char **)(D_L00_001B8C80_1.follow+0x70)+0xA0,height,0.13333334f);
 ApproachValue(*(char **)(D_L00_001B8C80_1.follow+0x70)+0xB0,dist,0.06666667f);
 ApproachValue(*(char **)(D_L00_001B8C80_1.follow+0x70)+0x8C,dist-0.5f,0.13333334f);
 if(D_00189E20_6.state==0x2B) {
  if((g_current_map_index!=14 && g_current_map_index!=7 && g_current_map_index!=9) || (D_00189E20_6.swing && *(unsigned char *)(D_00189E20_6.swing+0x21)==255)) {
   *(float *)angle=math_step_spring_damper_stored(*(float *)angle,D_00189E20_6.yaw,angle+4,0.00125f,0.175f,0.0f);
  } else {
   turn=angle+4; best_node=0; closest=1000.0f;
   swing=D_00189E20_6.swing;
   list=D_L00_001FA920[*(unsigned char *)(swing+0x21)];
   if(list) do {
    node=D_L00_001B1E9C+(*list&0x7FFF)*0x100;
    if(node!=swing && (*(short *)(node+0xAA)==MOBY_CLASS_SWINGSHOT_NODE_2 || *(short *)(node+0xAA)==MOBY_CLASS_SWINGSHOT_NODE)) {
     FastVecSub(diff,node+0x10,swing+0x10);
     vec_scale_to_length(unit,diff,1.0f);
     axis[0]=math_fast_sin_or_cos_a(D_00189E20_6.yaw);
     axis[1]=math_fast_sin_or_cos_b(D_00189E20_6.yaw);axis[2]=0.0f;
     aim_dot=FastVecDot(unit,(char *)axis);
     if(aim_dot>0.0f) {score=FastVecLength(diff)-aim_dot*10.0f;if(score<closest){best_node=node;closest=score;}}
    }
   } while(*list++>=0);
   if(best_node) {
    FastVecSub(diff,best_node+0x10,swing+0x10);
    *(float *)angle=math_step_spring_damper_stored(*(float *)angle,mat_fast_helper_a(*(float *)diff,*(float *)(diff+4)),turn,0.00125f,0.175f,0.0f);
   } else if(*(int *)(part+0x40)==1)
    *(float *)angle=math_step_spring_damper_stored(*(float *)angle,*(float *)(*(char **)(part+0x44)+0xF8),turn,0.00125f,0.175f,0.0f);
   else
    *(float *)angle=math_step_spring_damper_stored(*(float *)angle,D_00189E20_6.yaw,turn,0.00125f,0.175f,0.0f);
  }
 } else if(D_00189E20_6.state==0x24) {
  if(*(int *)(part+0x40)==1)
   *(float *)angle=math_step_spring_damper_stored(*(float *)angle,*(float *)(*(char **)(part+0x44)+0xF8),angle+4,0.00125f,0.175f,0.0f);
  else
   *(float *)angle=math_step_spring_damper_stored(*(float *)angle,D_00189E20_6.yaw,angle+4,0.00125f,0.175f,0.0f);
 }
 *(float *)(part+0x30)=math_fast_sin_or_cos_a(*(float *)angle);
 *(float *)(part+0x34)=math_fast_sin_or_cos_b(*(float *)angle);
 *(float *)(part+0x38)=0.0f;*(float *)(part+0x3C)=*(float *)(part+0x38);
 vec_scale_to_length(out,part+0x30,-*(float *)cfg);
 *(float *)(out+8)+=*(float *)(cfg+0x10);
 func_00282CC0_4(out,out,g_hero_position);
 if(FastDecTimer(vars+0x1E)) {qcopy(camera+0x30,out);} else {qcopy(camera+0x30,out);}
}
