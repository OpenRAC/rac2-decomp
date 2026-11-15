#include "common.h"
typedef unsigned int TurnQuad __attribute__((mode(TI)));
typedef union { TurnQuad q; float f[4]; } TurnVector;
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern float func_00282C48(float);
extern float func_00283CE0(int);
extern float func_002A7C00(float,float,float);
extern void func_002AB600(void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_00282978(void *);
extern void func_00283810(void *,void *,void *,float);
extern void func_00283958(void *,void *);
extern short D_L05_001B1BC8 __attribute__((sda)), D_L05_001B1BC4 __attribute__((sda));
/* Smoothly turns the ship toward a new heading over a short time. Returns 1 while the turn is in progress. */
int func_L05_00442F90(char *object)
{
 TurnVector up, first, second, third, result;
 char *state = *(char **)(object+0x70)+0x50;
 up.q=0;up.f[2]=1.0f;up.f[3]=1.0f;
 {
 float angle = FastVecDot(&up,object+0x20);
 if ((*(unsigned long *)(state+0x18)&0xFFFFFF00000000UL)==0x2000000000000UL) {
 *(float *)(state+0x24)=1.5707963705062866f-FastAngleHelper(angle);
 if (*(float *)(state+0x24)<1.5707964897155762f) *(short *)(state+0x1c)=D_L05_001B1BC8;
 else *(short *)(state+0x1c)=D_L05_001B1BC4;
 *(float *)(state+0x20)=1.0f/IntToFloat(*(short *)(state+0x1c));
 }
 }
 if (*(short *)(state+0x1c)) {
 TransformMatrixViaCopy(state+0x30,object);
 qcopy(&first,object);
 FastVecCross(&second,&first,&up);
 vec_scale_to_length(&second,&second,1.0f);
 FastVecCross(&third,&second,&first);
 TransformMatrixViaCopy(state+0x40,&first);
 if (FastDecTimer(state+0x1c)) {*(unsigned char *)(state+0x1e)=0;return 1;}
 else if (FloatAbs(FastVecDot(&up,object))>=0.75f) {*(unsigned char *)(state+0x1e)=0;return 1;}
 else {
 float amount=CosineBlend(0.0f,1.0f,IntToFloat(*(short *)(state+0x1c))* *(float *)(state+0x20));
 FastVectorNormalize3(&result,state+0x40,state+0x30,amount);
 quaternion_to_rotation_basis(&result,object);
 }
 return 1;
 }
 return 0;
}
