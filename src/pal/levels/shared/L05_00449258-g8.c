/* func_PAL_L05_00449258, the PAL copy of func_L05_00442F90: the same C, with the turn time scaled for 50 Hz. */
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
extern int D_L05_001B1BC8 __attribute__((sda)), D_L05_001B1BC4 __attribute__((sda));
int func_PAL_L05_00449258(char *object)
{
 TurnVector up, first, second, third, result;
 char *state = *(char **)(object+0x70)+0x50;
 up.q=0;up.f[2]=1.0f;up.f[3]=1.0f;
 {
 float angle = func_00282DB0(&up,object+0x20);
 if ((*(unsigned long *)(state+0x18)&0xFFFFFF00000000UL)==0x2000000000000UL) {
 *(float *)(state+0x24)=1.5707963705062866f-func_002831B0(angle);
 if (*(float *)(state+0x24)<1.5707964897155762f) *(short *)(state+0x1c)=((D_L05_001B1BC8 * 5 + 2) / 6);
 else *(short *)(state+0x1c)=((D_L05_001B1BC4 * 5 + 2) / 6);
 *(float *)(state+0x20)=1.0f/func_00283CE0(*(short *)(state+0x1c));
 }
 }
 if (*(short *)(state+0x1c)) {
 func_002AB600(state+0x30,object);
 qcopy(&first,object);
 func_00282DD8(&second,&first,&up);
 func_00282F20(&second,&second,1.0f);
 func_00282DD8(&third,&second,&first);
 func_002AB600(state+0x40,&first);
 if (func_00282978(state+0x1c)) {*(unsigned char *)(state+0x1e)=0;return 1;}
 else if (func_00282C48(func_00282DB0(&up,object))>=0.75f) {*(unsigned char *)(state+0x1e)=0;return 1;}
 else {
 float amount=func_002A7C00(0.0f,1.0f,func_00283CE0(*(short *)(state+0x1c))* *(float *)(state+0x20));
 func_00283810(&result,state+0x40,state+0x30,amount);
 func_00283958(&result,object);
 }
 return 1;
 }
 return 0;
}
