#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void moby_set_state(char *, int, int);
extern float math_random_float_range(float,float);
extern char *part_find_owned_effect_slot(char *,int,int);
extern void FastVecAdd(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void moby_mark_spawned(char *);
extern void part_spawn_scaled_bolts_pal(char *,float,int);
extern void moby_compute_local_point(char *,float,float,float,void *);
extern void func_002A0F48(char *);
extern float moby_update_aim_target_strength_pal(char *,char *);
extern void func_PAL_002AC290(char *,void *);
extern void func_PAL_002AC3C0(char *,void *);
extern int flag_set_first_pending(char *);
extern char *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int PlayMobySound(int,int,char *);
extern float FastAddRotations(float,float);
extern int coll_sweep_from_object(char *,void *,float,float,float,int,int,int,int);
extern void func_PAL_002B15D8(char *,int,void *,int,float,float,float,float);
extern void part_spawn_crash_debris_pal(char *);
extern int g_game_mode __attribute__((nosda));
extern float g_breakable_local_point __attribute__((sda));
extern float D_L06_001B1D70_4[] MACRO_ADDR;
extern struct { char pad[0x160]; float f160; int pad164, n168, n16c; char pad170[16]; float f180; int pad184,n188; } g_camera_state __attribute__((nosda));

/* The two height tests read their own values: with -frac2-gcse-unsplit-edges gcse leaves both
   loads in place, and reorg skips the second ground load on the first test's failure edge. */
void breakable_machine_update_pal(char *o) {
 float pos[4],v[4];
 char *s=*(char **)(o+0x68);
 float damage,t;
 int i;
 switch(*(unsigned char *)(o+0x20)) {
 case 0:
 *(short *)(s+0x24)=6; *(float *)(s+0x20)=6; *(int *)(s+0x80)=0;
 *(Quad *)v=0; v[0]=0.080000006f; v[2]=math_random_float_range(6,9)*0.020000001f;
 *(Quad *)pos=*(Quad *)v;
 func_002A0F48(o);
 matrix_mul_vec3(s+0x70,pos,o+0xC0);
 moby_set_state(o,1,-1); break;
 case 1:
 damage=moby_update_aim_target_strength_pal(o,part_find_owned_effect_slot(o,0x230000,0));
 if(damage>0) {
 ((unsigned char *)s)[0x57]=255; ((unsigned char *)s)[0x58]=128; ((unsigned char *)s)[0x59]=128;
 func_PAL_002AC290(o,s+0x50);
 *(float *)(s+0x20)-=damage;
 }
 if(*(float *)(s+0x20)<0) moby_set_state(o,2,-1);
 func_PAL_002AC3C0(o,s+0x50); ((unsigned char *)o)[0xA8]=255; break;
 case 2:
 if(flag_set_first_pending(o)) {
 SpawnExplosion_pal(o+0x10,1,25,20,20,20,45,1,1,20,1,1,0,0);
 PlayMobySound(1,0,o);
 }
 func_PAL_002AC3C0(o,s+0x50);
 *(float *)(s+0x68)+=0.0004188791f;
 *(float *)(o+0xF4)=FastAddRotations(*(float *)(o+0xF4),*(float *)(s+0x68));
 if(*(float *)(o+0xF4)>0.628318548f && g_game_mode!=140) {
 *(int *)(o+0x98)=0;
 for(i=0;i<6;i++) {
 t=i*0.2f;
 moby_compute_local_point(o,t*1.5f+(-0.5f),0,t*7+2,pos);
 coll_sweep_from_object(o,pos,0.8f,4,1,0x30009,0,1,0);
 }
 moby_compute_local_point(o,g_breakable_local_point,D_L06_001B1D70_4[1],D_L06_001B1D70_4[2],pos);
 coll_sweep_from_object(o,pos,2.5f,4,1,0x4030000,0,1,0);
 }
 if(*(float *)(o+0xF4)>1.2566371f) moby_set_state(o,3,-1);
 break;
 case 3:
 if(flag_set_first_pending(o)) {
 *(Quad *)pos=0; pos[2]=0.080000006f;
 func_PAL_002B15D8(o,0x6FF,pos,255,3,6,3,7);
 PlayMobySound(0,0,o);
 part_spawn_scaled_bolts_pal(o,0,9);
 g_camera_state.f180=0.1f;
 g_camera_state.n188=75;
 g_camera_state.f160=0.2f;
 g_camera_state.n168=50;
 g_camera_state.n16c=0;
 *(unsigned short *)(o+0x7C)=0x8100;
 matrix_mul_vec3(v,&g_breakable_local_point,o+0xC0);
 FastVecAdd(o+0x10,o+0x10,v);
 }
 coll_sweep_from_object(o,o+0x10,2.5f,4,1,0x4030000,0,1,0);
 FastVecAdd(o+0x10,o+0x10,s+0x70);
 *(float *)(s+0x78)-=0.0043200003f;
 if (!*(int *)(s+0x80) && *(float *)(o+0x18) < *(float *)(s+0x6C)) {
     part_spawn_crash_debris_pal(o);
     *(int *)(s+0x80)=1;
 } else if (*(float *)(o+0x18) < *(float *)(s+0x6C)-4.0f)
     moby_mark_spawned(o);
 break;
 }
}
