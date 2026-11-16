#include "include_asm.h"


#include "common.h"
extern void FastVecAdd(void *,void *,void *),FastVecScale(void *,void *,float),make_hit_descriptor(void *,u8 *,int,void *,float),moby_set_state(u8 *,u8,int),part_l00_spawn_spark_burst_3_pal(void *,int,int),vec_random_direction(float *,float,float),moby_mark_spawned(u8 *);
extern int CollLine(void *,void *,int,int,void *),FastDecTimer(void *),math_random_int_below(int);
extern float math_random_float_range(float,float);
extern void *part_spawn_gravity_fade(void *,void *,int,int,int,int,int,float,float,float,int);
extern u8 g_effect_descriptor_default[] __attribute__((sda));
extern u8 g_collision_start_point[];

/* Advances the trail, resolves a collision, then settles and fades the object. (PAL: 50 Hz timers) */
void trail_l03_l03_projectile_update_pal_2(u8 *moby) {
 float next_position[4],matrix[12],trail_position[4],trail_step[4],particle_position[4];
 u8 *vars=*(u8 **)(moby+0x68);int i,color;float size;
 switch(moby[0x20]) {
 case 0:
 FastVecAdd(next_position,moby+0x10,vars);
 if(*(short *)(vars+0x12)<12)(*(short *)(vars+0x12))++;
 make_hit_descriptor(matrix,moby,0x10001,g_effect_descriptor_default,(float)*(int *)(vars+0x18));
 if(CollLine(moby+0x10,next_position,0,*(int *)(vars+0x14),matrix)){
 *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;moby_set_state(moby,1,-1);
 part_l00_spawn_spark_burst_3_pal(g_collision_start_point,10,1);goto finishmove;
 }
 if(FastDecTimer(vars+0x10)){
 *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;moby_set_state(moby,1,-1);goto finishmove;
 }
 qcopy(trail_position,moby+0x10);FastVecScale(trail_step,vars,0.2f);
 for(i=4;i>=0;i--){
 size=math_random_float_range(0.1f,0.3f);color=math_random_int_below(255);
 vec_random_direction(particle_position,0.0f,0.1f);FastVecAdd(particle_position,particle_position,trail_position);
 part_spawn_gravity_fade(particle_position,g_effect_descriptor_default,12,0x808080,color,32,0,size*210000.0f,size*42000.0f,0.0f,0);
 FastVecAdd(trail_position,trail_position,trail_step);
 }
 finishmove:
 qcopy(moby+0x10,next_position);break;
 case 1:
 if(--*(short *)(vars+0x12)==-1)moby_mark_spawned(moby);break;
 }
}


