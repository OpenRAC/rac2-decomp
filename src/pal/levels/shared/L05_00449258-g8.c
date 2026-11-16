/* func_PAL_L05_00449258, the PAL copy of func_L05_00442F90: the same C, with the turn time scaled for 50 Hz. */
#include "common.h"
typedef unsigned int TurnQuad __attribute__((mode(TI)));
typedef union { TurnQuad q; float f[4]; } TurnVector;
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern float math_fabs(float);
extern float IntToFloat(int);
extern float math_cosine_blend(float,float,float);
extern void mat_transform_via_copy(void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int FastDecTimer(void *);
extern void vec_fast_normalize3(void *,void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *);
extern int g_ship_turn_anim_early __attribute__((sda)), g_ship_turn_anim_default __attribute__((sda));
int func_PAL_L05_00449258(char *object)
{
 TurnVector up, first, second, third, result;
 char *state = *(char **)(object+0x70)+0x50;
 up.q=0;up.f[2]=1.0f;up.f[3]=1.0f;
 {
 float angle = FastVecDot(&up,object+0x20);
 if ((*(unsigned long *)(state+0x18)&0xFFFFFF00000000UL)==0x2000000000000UL) {
 *(float *)(state+0x24)=1.5707963705062866f-math_fast_angle_helper(angle);
 if (*(float *)(state+0x24)<1.5707964897155762f) *(short *)(state+0x1c)=((g_ship_turn_anim_early * 5 + 2) / 6);
 else *(short *)(state+0x1c)=((g_ship_turn_anim_default * 5 + 2) / 6);
 *(float *)(state+0x20)=1.0f/IntToFloat(*(short *)(state+0x1c));
 }
 }
 if (*(short *)(state+0x1c)) {
 mat_transform_via_copy(state+0x30,object);
 qcopy(&first,object);
 FastVecCross(&second,&first,&up);
 vec_scale_to_length(&second,&second,1.0f);
 FastVecCross(&third,&second,&first);
 mat_transform_via_copy(state+0x40,&first);
 if (FastDecTimer(state+0x1c)) {*(unsigned char *)(state+0x1e)=0;return 1;}
 else if (math_fabs(FastVecDot(&up,object))>=0.75f) {*(unsigned char *)(state+0x1e)=0;return 1;}
 else {
 float amount=math_cosine_blend(0.0f,1.0f,IntToFloat(*(short *)(state+0x1c))* *(float *)(state+0x20));
 vec_fast_normalize3(&result,state+0x40,state+0x30,amount);
 quaternion_to_rotation_basis(&result,object);
 }
 return 1;
 }
 return 0;
}
