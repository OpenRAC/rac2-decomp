/* func_PAL_L05_0044AED0, the PAL copy of func_L05_00444B20: the same C, where the four timers are scaled for 50 Hz. */
#include "common.h"
extern void func_L05_00444D60(void *,int *,int *,int);
extern void func_L05_00444DF8(u8,u8,float,float,float,float,u8,u8);
extern float func_00283CE0(int),func_00283B98(float,float);
extern int func_00283CF0(float);
extern int ref_L05_00444B20_00(int,int,void *,int);
extern void ref_L05_00444B20_01(int);
extern int D_L05_002A1968[];
extern int D_L05_001B1B04 __attribute__((sda)), D_L05_001B1B0C __attribute__((sda));
extern int D_L05_001B1B00 __attribute__((sda)), D_L05_001B1B08 __attribute__((sda));
extern char D_00188660[];
void func_PAL_L05_0044AED0(char *object)
{
 int point[2];
 char *state=*(char **)(object+0x68);
 if (*(char **)(state+0x14)) {
 int threshold, duration;
 func_L05_00444D60(*(char **)(state+0x14)+0x10,&point[0],&point[1],0);
 if (D_L05_002A1968[0]) {threshold=(D_L05_001B1B04*5+2)/6;duration=(D_L05_001B1B0C*5+2)/6;}
 else {threshold=(D_L05_001B1B00*5+2)/6;duration=(D_L05_001B1B08*5+2)/6;}
 if (*(int *)(state+0x1c)>threshold) {
 float fraction=func_00283CE0(*(int *)(state+0x1c)-threshold)/func_00283CE0(duration);
 float fade=(1.0f-fraction)*2.0f;
 float size=fraction*5.0f+1.0f;
 unsigned char alpha;
 float x,y;
 char *effect;
 if(fade>1.0f)fade=1.0f;
 alpha=func_00283CF0(fade*96.0f);
 x=func_00283CE0(point[0]);y=func_00283CE0(point[1]);
 func_L05_00444DF8(255,0,x,y,size,*(float *)(state+0x27c),0,alpha);
 *(float *)(state+0x27c)=func_00283B98(*(float *)(state+0x27c),0.01745329424738884f);
 *(char **)(state+0x18)=*(char **)(state+0x14);
 effect=D_00188660+*(int *)(state+0x270)*0x70;
 if (*(char **)(effect+0x88)!=object || !*(unsigned char *)(effect+0x74))
 *(int *)(state+0x270)=ref_L05_00444B20_00(9,4,object,0xfbf);
 } else {
 float x,y;
 if(!*(int *)(state+0x26c)) {ref_L05_00444B20_00(8,0,object,0xfbf);*(int *)(state+0x26c)=1;}
 x=func_00283CE0(point[0]);y=func_00283CE0(point[1]);
 func_L05_00444DF8(0,255,x,y,1.0f,0.0f,0,96);
 }
 } else {
 int id=*(int *)(state+0x270);
 if(id!=-1) {
 char *effect=D_00188660+id*0x70;
 if(*(char **)(effect+0x88)==object && *(unsigned char *)(effect+0x74))ref_L05_00444B20_01(id);
 }
 *(int *)(state+0x26c)=0;
 *(int *)(state+0x270)=-1;
 }
}
