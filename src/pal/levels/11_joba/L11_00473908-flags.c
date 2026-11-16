#include "include_asm.h"

#include "common.h"
typedef union { struct { float x,y,z,w; } v; unsigned int quad __attribute__((mode(TI))); } V1078;
typedef struct { unsigned char b[8]; } P1078;
extern const P1078 g_spark_orb_table_a, g_spark_orb_table_b;
extern const V1078 g_spark_orb_bounds[2];
extern void gfx_draw_orbiting_sparks(char *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void FastVecScale(void *, void *, float);
extern void *part_spawn_object_following_effect(void *, void *, int, float, int, int, float, int, int, int);
extern float math_random_float_range(float,float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_set_state(void *,int,int);
extern void gfx_add_draw_callback_third(void (*)(char *),void *);
extern void vec_local_offset_to_world(void *,void *,float,float,float);
extern void FastVecSub(void *,void *,void *);
extern float mat_fast_helper_a(float,float);
extern float vec_distance_xy(void *,void *);
extern float fast_subtract_rotations(float,float);
extern float math_random_signed_float_range(float,float);
extern float fast_vec_dist(void *,void *);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void part_l00_spawn_spark_burst_pal(void *,void *,float,void *,float,int,int,float,float,float);
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_kill(int);
extern char *moby_l00_spawn_child(void *,int,int);
extern int math_fast_float_d(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern int math_random_int_range(int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern void vec_random_direction(void *,float,float);

/* Per-frame update of the Joba spark orb: a ball of sparks circles it until it is hit, then it blows into pieces and sparks (PAL: 50 Hz timings). */
void spark_orb_update_pal(char *moby) {
 P1078 piece_table_a = g_spark_orb_table_a, piece_table_b = g_spark_orb_table_b;
 V1078 bounds[2], small, offset;
 V1078 temp, center, hover_pos, axis;
 char *data=*(char **)(moby+0x68);
 int sound=0x10eb;
 float height=18;
 int none=-1;
 bounds[0].quad=g_spark_orb_bounds[0].quad; bounds[1].quad=g_spark_orb_bounds[1].quad;
 small.quad=0;small.v.z=0.14000002f;
 if(H(moby,0xaa)==0x118c) {height=21;sound=0x118d;}
 offset.quad=0;offset.v.z=height;
 switch(B(moby,0x20)) {
 case 0: {
 int i;
 float radius,azimuth,elevation;
 F(data,0x18)=1;
 if(I(data,0x10)>8) I(data,0x10)=8;
 FastVecScale(&offset,&offset,F(moby,0x2c));
 I(data,4)=part_spawn_object_following_effect(&offset,moby,0x1fffffff,315000.0f,-1,0,0.0f,-1,0,-1);
 I(data,8)=part_spawn_object_following_effect(&offset,moby,0x3f106060,315000.0f,-1,1,0.0f,-1,0,-1);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 radius=math_random_float_range(0.75f,1.25f); azimuth=math_random_angle(); elevation=math_random_angle();
 vec_build_spherical_offset(point,radius,azimuth,elevation); FastVecAdd(point,moby+0x10,point);
 }
 moby_set_state(moby,1,-1); break;
 }
 case 1: {
 int i;
 float radius,azimuth,elevation,distance;
 gfx_add_draw_callback_third(gfx_draw_orbiting_sparks,moby);
 vec_local_offset_to_world(moby,&center,0,0,height);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 FastVecSub(&temp,moby+0x10,point);
 radius=mat_fast_helper_a(point->v.x-center.v.x,point->v.y-center.v.y);
 distance=vec_distance_xy(&center,point);
 azimuth=mat_fast_helper_a(distance,point->v.z-center.v.z);
 radius=fast_subtract_rotations(radius,0.0523598827f);
 elevation=math_random_signed_float_range(1,3);
 azimuth=fast_subtract_rotations(azimuth,elevation*0.0174532942f);
 if(azimuth>1.1f)azimuth=1.1f; if(azimuth< -1.1f)azimuth= -1.1f;
 distance=fast_vec_dist(&center,point);
 distance+=math_random_signed_float_range(0.020000001f,0.020000001f);
 if(distance>1.05f)distance=1.05f;if(distance<0.75f)distance=0.75f;
 vec_build_spherical_offset(point,distance,radius,azimuth); FastVecAdd(point,&center,point);
 }
 if(part_find_owned_effect_slot(moby,0x04010000,0) && !I(data,0)) {
 moby_set_state(moby,2,-1);
 } B(moby,0xa8)=255; break;
 }
 case 2:
 part_explode_object_into_pieces_pal(moby,bounds,&piece_table_b,&piece_table_a,65535,0,-1,0,65535,255,0);
 part_l00_spawn_spark_burst_pal(moby,&offset,0.1f,&small,0.18f,80,3,1,20,1);
 temp.quad=0;
 vec_local_offset_to_world(moby,&offset,0,0,18);
 SpawnExplosionEffects_pal(moby,&temp,&offset,0,0,10,3,5,0,1,9,0.5f,-1,0,0,0,none,0,0x810001);
 part_kill(I(data,4));part_kill(I(data,8));moby_l00_spawn_child(moby,sound,0);
 *(unsigned short *)(moby+0x34)|=1;I(moby,0x98)=0;B(moby,0x31)=0;
 I(data,0xc)=100; I(data,0x14)=500;moby_set_state(moby,3,-1);break;
 case 3: {
 int i,n;
 float radius;
 if(math_fast_float_d(data+0xc) || I(data,0xc)>=76) {
 temp.quad=0;temp.v.x=0.040000003f;temp.v.z=0.040000003f;
 matrix_mul_vec3(&temp,&temp,moby+0xc0);
 radius=19; if(H(moby,0xaa)==0x10ea) radius=17; offset.v.z=radius;
 part_l00_spawn_spark_burst_pal(moby,&offset,0,&temp,0.040000003f,math_random_int_range(3,6),0,0.5f,15,1);
 temp.v.x=-0.040000003f;temp.v.z=0.048000004f;
 matrix_mul_vec3(&temp,&temp,moby+0xc0);
 part_l00_spawn_spark_burst_pal(moby,&offset,0,&temp,0.040000003f,math_random_int_range(3,6),1,0.5f,15,1);
 I(data,0xc)=((s32)(math_random_int_range(45,90)) * 5 + 2) / 6;
 }
 vec_local_offset_to_world(moby,&hover_pos,0,0,18);
 if(!math_fast_float_d(data+0x14)) {
 gfx_add_draw_callback_third(gfx_draw_orbiting_sparks,moby);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 FastVecSub(&temp,point,moby+0x10);temp.v.z=0;
 vec_scale_to_length(&temp,&temp,1);
 axis.quad=0;axis.v.z=1;
 math_apply_axis_rotation_to_quat(&center,&temp,&axis,(float)I(data,0x14)*-0.002617994323372841f);
 vec_random_direction(&temp,1,1);
 radius=math_random_float_range(-0.25f,0.75f); center.v.z+=radius;
 FastVecAdd(&center,&temp,&center);
 radius=math_random_float_range(0.020000001f,0.020000001f);
 vec_scale_to_length(&center,&center,radius+radius);FastVecAdd(point,&center,point);
 }
 }
 if(I(data,0x14)<50) F(data,0x18)=(float)I(data,0x14)*0.02f;
 break;
 }
 }
}
