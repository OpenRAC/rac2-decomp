/* func_PAL_L00_003B0230, the PAL copy of func_L00_003ACA60: emits randomized particles along the motion from the previous position. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define FIELD_F32(p,o) (*(float *)((char *)(p)+(o)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
/* The EE assigns integer and floating-point arguments to independent register banks. */
extern void func_00282D30(float,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A78D8(float,float);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern int func_001163B0(void);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern char D_0018A0E0[];
typedef struct {char pad[0x5C]; unsigned char *data;} ParticleGlobals;
extern ParticleGlobals D_L00_001FE940;
extern char *func_PAL_002C23B8(void *,void *,int,int,int,int,float,float,float,float,float);
void func_PAL_L00_003B0230(char *m,void *previous)
{
 float initial[4],velocity[4],position[4],step[4];
 float scale, speed, ratio;
 float *start=initial;
 float *point;
 float *vel;
 float *cursor;
 int n,type,time,flags,color;
 char *particle;
 *(Quadword *)start=*(Quadword *)previous;
 scale=FIELD_F32(*(char **)(m+0x68),0x18);
 n=func_00283CF0(scale*10.0f);
 point=position;
 qcopy(point,start);
 func_00282CF0(step,m+0x10,initial);
 ratio=func_00283CE0(n);
 ratio=scale/ratio;
 func_00282F20(step,step,ratio);
 if(n>0) do {
 type=func_00283CF0(func_002A78D8(1.0f,3.0f));
 func_00282D30(-(func_002A7878(0.2f,1.0f)*0.020000001f),velocity,D_0018A0E0);
 time=func_002A7820(30,45);
 speed=func_002A7878(200.0f,1000.0f);
 if(func_001163B0()&2) {flags=32;color=0x404040;speed+=speed;}
 else {flags=64;color=0x7F7F7F;}
 vel=velocity;
 cursor=position;
 particle=func_PAL_002C23B8(cursor,vel,(time*5+2)/6,flags,color,type,21000.0f,speed,1.0f,0,0);
 func_00282CC0(cursor,cursor,step);
 if(particle) {particle[2]=D_L00_001FE940.data[0];particle[3]=flags==64?0x48:0x44;}
 n--;
 } while(n);
}
