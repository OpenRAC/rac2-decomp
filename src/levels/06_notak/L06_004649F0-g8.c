#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void moby_set_state(char *, int, int);
extern float math_random_float_range(float,float);
extern int func_0035CBA0(char *,int,int);
extern void FastVecAdd(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void func_00350388(char *);
extern void part_spawn_scaled_bolts(char *,float,int);
extern void moby_compute_local_point(char *,float,float,float,void *);
extern void func_002A0F48(char *);
extern float moby_update_aim_target_strength(char *,char *);
extern void gfx_start_color_fade(char *,void *);
extern void gfx_update_color_fade(char *,void *);
extern int flag_set_first_pending(char *);
extern char *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int func_003A0948(int,int,char *);
extern float FastAddRotations(float,float);
extern int coll_sweep_from_object(char *,void *,float,float,float,int,int,int,int);
extern void part_spawn_masked_debris(char *,int,void *,int,float,float,float,float);
extern void part_spawn_crash_debris(char *);
extern int D_0018C0B4 __attribute__((nosda));
extern float D_L06_001B1D70 __attribute__((sda));
extern float D_L06_001B1D70_4[] MACRO_ADDR;
extern struct { char pad[0x160]; float f160; int pad164, n168, n16c; char pad170[16]; float f180; int pad184,n188; } g_camera_state __attribute__((nosda));
/* The two height tests read their own values: with -frac2-gcse-unsplit-edges gcse leaves both
   loads in place, and reorg skips the second ground load on the first test's failure edge. */
/* Updates a Notak breakable machine: it takes damage until its health runs out, tips over with smoke and sparks, then falls and crashes. */
void breakable_machine_update(char *moby) {
 float pos[4],vel[4];
 char *vars=*(char **)(moby+0x68);
 float damage,frac;
 int i;
 switch(*(unsigned char *)(moby+0x20)) {
 case 0:
 *(short *)(vars+0x24)=6; *(float *)(vars+0x20)=6; *(int *)(vars+0x80)=0;
 *(Quad *)vel=0; vel[0]=0.06666667f; vel[2]=math_random_float_range(6,9)*0.0166666675f;
 *(Quad *)pos=*(Quad *)vel;
 func_002A0F48(moby);
 matrix_mul_vec3(vars+0x70,pos,moby+0xC0);
 moby_set_state(moby,1,-1); break;
 case 1:
 damage=moby_update_aim_target_strength(moby,func_0035CBA0(moby,0x230000,0));
 if(damage>0) {
 ((unsigned char *)vars)[0x57]=255; ((unsigned char *)vars)[0x58]=128; ((unsigned char *)vars)[0x59]=128;
 gfx_start_color_fade(moby,vars+0x50);
 *(float *)(vars+0x20)-=damage;
 }
 if(*(float *)(vars+0x20)<0) moby_set_state(moby,2,-1);
 gfx_update_color_fade(moby,vars+0x50); ((unsigned char *)moby)[0xA8]=255; break;
 case 2:
 if(flag_set_first_pending(moby)) {
 SpawnExplosion(moby+0x10,1,25,20,20,20,45,1,1,20,1,1,0,0);
 func_003A0948(1,0,moby);
 }
 gfx_update_color_fade(moby,vars+0x50);
 *(float *)(vars+0x68)+=0.000290888245f;
 *(float *)(moby+0xF4)=FastAddRotations(*(float *)(moby+0xF4),*(float *)(vars+0x68));
 if(*(float *)(moby+0xF4)>0.628318548f && D_0018C0B4!=140) {
 *(int *)(moby+0x98)=0;
 for(i=0;i<6;i++) {
 frac=i*0.2f;
 moby_compute_local_point(moby,frac*1.5f+(-0.5f),0,frac*7+2,pos);
 coll_sweep_from_object(moby,pos,0.8f,4,1,0x30009,0,1,0);
 }
 moby_compute_local_point(moby,D_L06_001B1D70,D_L06_001B1D70_4[1],D_L06_001B1D70_4[2],pos);
 coll_sweep_from_object(moby,pos,2.5f,4,1,0x4030000,0,1,0);
 }
 if(*(float *)(moby+0xF4)>1.2566371f) moby_set_state(moby,3,-1);
 break;
 case 3:
 if(flag_set_first_pending(moby)) {
 *(Quad *)pos=0; pos[2]=0.06666667f;
 part_spawn_masked_debris(moby,0x6FF,pos,255,3,6,3,7);
 func_003A0948(0,0,moby);
 part_spawn_scaled_bolts(moby,0,9);
 g_camera_state.f180=0.1f;
 g_camera_state.n188=90;
 g_camera_state.f160=0.2f;
 g_camera_state.n168=60;
 g_camera_state.n16c=0;
 *(unsigned short *)(moby+0x7C)=0x8100;
 matrix_mul_vec3(vel,&D_L06_001B1D70,moby+0xC0);
 FastVecAdd(moby+0x10,moby+0x10,vel);
 }
 coll_sweep_from_object(moby,moby+0x10,2.5f,4,1,0x4030000,0,1,0);
 FastVecAdd(moby+0x10,moby+0x10,vars+0x70);
 *(float *)(vars+0x78)-=0.003f;
 if (!*(int *)(vars+0x80) && *(float *)(moby+0x18) < *(float *)(vars+0x6C)) {
     part_spawn_crash_debris(moby);
     *(int *)(vars+0x80)=1;
 } else if (*(float *)(moby+0x18) < *(float *)(vars+0x6C)-4.0f)
     func_00350388(moby);
 break;
 }
}
