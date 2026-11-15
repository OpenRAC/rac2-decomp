#include "common.h"
extern void FastVecAdd(void *,void *,void *),FastVecScale(void *,void *,float),make_hit_descriptor(void *,u8 *,int,void *,float),moby_set_state(u8 *,u8,int),part_l00_spawn_spark_burst_3(void *,int,int),vec_random_direction(float *,float,float),moby_mark_spawned(u8 *);
extern int CollLine(void *,void *,int,int,void *),FastDecTimer(void *),math_random_int_below(int);
extern float math_random_float_range(float,float);
extern void part_spawn_gravity_fade(void *,void *,int,int,int,int,int,float,float,float,int);
extern u8 D_L03_001A8F20[] __attribute__((sda));
extern u8 D_L03_001BFDE0[];
/* Moves a fired shot, leaves sparkles behind it, and removes it when it hits something or runs out of time. */
void spark_l03_shot_update(u8 *moby) {
 float next[4],matrix[12],pos[4],step[4],particle[4];
 u8 *vars=*(u8 **)(moby+0x68);int i,color;float size;
 switch(moby[0x20]) {
 case 0:
 FastVecAdd(next,moby+0x10,vars);
 if(*(short *)(vars+0x12)<12)(*(short *)(vars+0x12))++;
 make_hit_descriptor(matrix,moby,0x10001,D_L03_001A8F20,(float)*(int *)(vars+0x18));
 if(CollLine(moby+0x10,next,0,*(int *)(vars+0x14),matrix)){
 *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;moby_set_state(moby,1,-1);
 part_l00_spawn_spark_burst_3(D_L03_001BFDE0,10,1);goto finishmove;
 }
 if(FastDecTimer(vars+0x10)){
 *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;moby_set_state(moby,1,-1);goto finishmove;
 }
 qcopy(pos,moby+0x10);FastVecScale(step,vars,0.2f);
 for(i=4;i>=0;i--){
 size=math_random_float_range(0.1f,0.3f);color=math_random_int_below(255);
 vec_random_direction(particle,0.0f,0.1f);FastVecAdd(particle,particle,pos);
 part_spawn_gravity_fade(particle,D_L03_001A8F20,15,0x808080,color,32,0,size*210000.0f,size*42000.0f,0.0f,0);
 FastVecAdd(pos,pos,step);
 }
 finishmove:
 qcopy(moby+0x10,next);break;
 case 1:
 if(--*(short *)(vars+0x12)==-1)moby_mark_spawned(moby);break;
 }
}
