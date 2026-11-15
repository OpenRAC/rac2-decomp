#include "include_asm.h"


#include "common.h"
extern void FastVecAdd(void *,void *,void *),FastVecScale(void *,void *,float),make_hit_descriptor(void *,u8 *,int,void *,float),moby_set_state(u8 *,u8,int),func_PAL_L00_003E74D8(void *,int,int),vec_random_direction(float *,float,float),moby_mark_spawned(u8 *);
extern int CollLine(void *,void *,int,int,void *),FastDecTimer(void *),math_random_int_below(int);
extern float math_random_float_range(float,float);
extern void part_spawn_gravity_fade(void *,void *,int,int,int,int,int,float,float,float,int);
extern u8 D_L03_001A8F20[] __attribute__((sda));
extern u8 D_L03_001BFDE0[];

void func_PAL_L03_003DD8A8(u8 *p) {
 float next[4],matrix[12],pos[4],step[4],particle[4];
 u8 *q=*(u8 **)(p+0x68);int i,color;float size;
 switch(p[0x20]) {
 case 0:
 FastVecAdd(next,p+0x10,q);
 if(*(short *)(q+0x12)<12)(*(short *)(q+0x12))++;
 make_hit_descriptor(matrix,p,0x10001,D_L03_001A8F20,(float)*(int *)(q+0x18));
 if(CollLine(p+0x10,next,0,*(int *)(q+0x14),matrix)){
 *(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;moby_set_state(p,1,-1);
 func_PAL_L00_003E74D8(D_L03_001BFDE0,10,1);goto finishmove;
 }
 if(FastDecTimer(q+0x10)){
 *(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;moby_set_state(p,1,-1);goto finishmove;
 }
 qcopy(pos,p+0x10);FastVecScale(step,q,0.2f);
 for(i=4;i>=0;i--){
 size=math_random_float_range(0.1f,0.3f);color=math_random_int_below(255);
 vec_random_direction(particle,0.0f,0.1f);FastVecAdd(particle,particle,pos);
 part_spawn_gravity_fade(particle,D_L03_001A8F20,12,0x808080,color,32,0,size*210000.0f,size*42000.0f,0.0f,0);
 FastVecAdd(pos,pos,step);
 }
 finishmove:
 qcopy(p+0x10,next);break;
 case 1:
 if(--*(short *)(q+0x12)==-1)moby_mark_spawned(p);break;
 }
}


