#include "include_asm.h"

#include "common.h"
typedef union { struct { float x,y,z,w; } v; unsigned int quad __attribute__((mode(TI))); } V1078;
typedef struct { unsigned char b[8]; } P1078;
extern const P1078 D_L11_001B2930, D_L11_001B2938;
extern const V1078 D_L11_001B2940[2];
extern void gfx_draw_orbiting_sparks(char *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void FastVecScale(void *, void *, float);
extern int part_spawn_object_following_effect(void *, void *, int, float, int, int, float, int, int, int);
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
extern int part_find_owned_effect_slot(void *,int,int);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void func_PAL_L00_002ED7E8(void *,void *,float,void *,float,int,int,float,float,float);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_kill(int);
extern char *moby_l00_spawn_child(void *,int,int);
extern int math_fast_float_d(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern int math_random_int_range(int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern void vec_random_direction(void *,float,float);

void func_PAL_L11_00475BF0(char *obj) {
 P1078 p = D_L11_001B2930, q = D_L11_001B2938;
 V1078 bounds[2], small, offset;
 V1078 temp, center, v, axis;
 char *data=*(char **)(obj+0x68);
 int sound=0x10eb;
 float height=18;
 int none=-1;
 bounds[0].quad=D_L11_001B2940[0].quad; bounds[1].quad=D_L11_001B2940[1].quad;
 small.quad=0;small.v.z=0.14000002f;
 if(H(obj,0xaa)==0x118c) {height=21;sound=0x118d;}
 offset.quad=0;offset.v.z=height;
 switch(B(obj,0x20)) {
 case 0: {
 int i;
 float a,b,c;
 F(data,0x18)=1;
 if(I(data,0x10)>8) I(data,0x10)=8;
 FastVecScale(&offset,&offset,F(obj,0x2c));
 I(data,4)=part_spawn_object_following_effect(&offset,obj,0x1fffffff,315000.0f,-1,0,0.0f,-1,0,-1);
 I(data,8)=part_spawn_object_following_effect(&offset,obj,0x3f106060,315000.0f,-1,1,0.0f,-1,0,-1);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 a=math_random_float_range(0.75f,1.25f); b=math_random_angle(); c=math_random_angle();
 vec_build_spherical_offset(point,a,b,c); FastVecAdd(point,obj+0x10,point);
 }
 moby_set_state(obj,1,-1); break;
 }
 case 1: {
 int i;
 float a,b,c,r;
 gfx_add_draw_callback_third(gfx_draw_orbiting_sparks,obj);
 vec_local_offset_to_world(obj,&center,0,0,height);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 FastVecSub(&temp,obj+0x10,point);
 a=mat_fast_helper_a(point->v.x-center.v.x,point->v.y-center.v.y);
 r=vec_distance_xy(&center,point);
 b=mat_fast_helper_a(r,point->v.z-center.v.z);
 a=fast_subtract_rotations(a,0.0523598827f);
 c=math_random_signed_float_range(1,3);
 b=fast_subtract_rotations(b,c*0.0174532942f);
 if(b>1.1f)b=1.1f; if(b< -1.1f)b= -1.1f;
 r=fast_vec_dist(&center,point);
 r+=math_random_signed_float_range(0.020000001f,0.020000001f);
 if(r>1.05f)r=1.05f;if(r<0.75f)r=0.75f;
 vec_build_spherical_offset(point,r,a,b); FastVecAdd(point,&center,point);
 }
 if(part_find_owned_effect_slot(obj,0x04010000,0) && !I(data,0)) {
 moby_set_state(obj,2,-1);
 } B(obj,0xa8)=255; break;
 }
 case 2:
 func_PAL_L00_0032C328(obj,bounds,&q,&p,65535,0,-1,0,65535,255,0);
 func_PAL_L00_002ED7E8(obj,&offset,0.1f,&small,0.18f,80,3,1,20,1);
 temp.quad=0;
 vec_local_offset_to_world(obj,&offset,0,0,18);
 func_PAL_002AC718(obj,&temp,&offset,0,0,10,3,5,0,1,9,0.5f,-1,0,0,0,none,0,0x810001);
 part_kill(I(data,4));part_kill(I(data,8));moby_l00_spawn_child(obj,sound,0);
 *(unsigned short *)(obj+0x34)|=1;I(obj,0x98)=0;B(obj,0x31)=0;
 I(data,0xc)=100; I(data,0x14)=500;moby_set_state(obj,3,-1);break;
 case 3: {
 int i,n;
 float a;
 if(math_fast_float_d(data+0xc) || I(data,0xc)>=76) {
 temp.quad=0;temp.v.x=0.040000003f;temp.v.z=0.040000003f;
 matrix_mul_vec3(&temp,&temp,obj+0xc0);
 a=19; if(H(obj,0xaa)==0x10ea) a=17; offset.v.z=a;
 func_PAL_L00_002ED7E8(obj,&offset,0,&temp,0.040000003f,math_random_int_range(3,6),0,0.5f,15,1);
 temp.v.x=-0.040000003f;temp.v.z=0.048000004f;
 matrix_mul_vec3(&temp,&temp,obj+0xc0);
 func_PAL_L00_002ED7E8(obj,&offset,0,&temp,0.040000003f,math_random_int_range(3,6),1,0.5f,15,1);
 I(data,0xc)=((s32)(math_random_int_range(45,90)) * 5 + 2) / 6;
 }
 vec_local_offset_to_world(obj,&v,0,0,18);
 if(!math_fast_float_d(data+0x14)) {
 gfx_add_draw_callback_third(gfx_draw_orbiting_sparks,obj);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 FastVecSub(&temp,point,obj+0x10);temp.v.z=0;
 vec_scale_to_length(&temp,&temp,1);
 axis.quad=0;axis.v.z=1;
 math_apply_axis_rotation_to_quat(&center,&temp,&axis,(float)I(data,0x14)*-0.002617994323372841f);
 vec_random_direction(&temp,1,1);
 a=math_random_float_range(-0.25f,0.75f); center.v.z+=a;
 FastVecAdd(&center,&temp,&center);
 a=math_random_float_range(0.020000001f,0.020000001f);
 vec_scale_to_length(&center,&center,a+a);FastVecAdd(point,&center,point);
 }
 }
 if(I(data,0x14)<50) F(data,0x18)=(float)I(data,0x14)*0.02f;
 break;
 }
 }
}
