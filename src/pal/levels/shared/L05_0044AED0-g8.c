#include "names.h"
/* func_PAL_L05_0044AED0, the PAL copy of func_L05_00444B20: the same C, where the four timers are scaled for 50 Hz. */
#include "common.h"
extern void gfx_convert_float_pair_bias_coords(void *,int *,int *,int);
extern void DrawSpriteRing(u8,u8,float,float,float,float,u8,u8);
extern float IntToFloat(int),FastAddRotations(float,float);
extern int FloatToInt(float);
extern int ref_L05_00444B20_00(int,int,void *,int);
extern void ref_L05_00444B20_01(int);
extern int D_L05_002A1968[];
extern int D_L05_001B1B04 __attribute__((sda)), D_L05_001B1B0C __attribute__((sda));
extern int D_L05_001B1B00 __attribute__((sda)), D_L05_001B1B08 __attribute__((sda));
extern char g_sound_state[];
void func_PAL_L05_0044AED0(char *object)
{
 int point[2];
 char *state=*(char **)(object+0x68);
 if (*(char **)(state+0x14)) {
 int threshold, duration;
 gfx_convert_float_pair_bias_coords(*(char **)(state+0x14)+0x10,&point[0],&point[1],0);
 if (D_L05_002A1968[0]) {threshold=(D_L05_001B1B04*5+2)/6;duration=(D_L05_001B1B0C*5+2)/6;}
 else {threshold=(D_L05_001B1B00*5+2)/6;duration=(D_L05_001B1B08*5+2)/6;}
 if (*(int *)(state+0x1c)>threshold) {
 float fraction=IntToFloat(*(int *)(state+0x1c)-threshold)/IntToFloat(duration);
 float fade=(1.0f-fraction)*2.0f;
 float size=fraction*5.0f+1.0f;
 unsigned char alpha;
 float x,y;
 char *effect;
 if(fade>1.0f)fade=1.0f;
 alpha=FloatToInt(fade*96.0f);
 x=IntToFloat(point[0]);y=IntToFloat(point[1]);
 DrawSpriteRing(255,0,x,y,size,*(float *)(state+0x27c),0,alpha);
 *(float *)(state+0x27c)=FastAddRotations(*(float *)(state+0x27c),0.01745329424738884f);
 *(char **)(state+0x18)=*(char **)(state+0x14);
 effect=g_sound_state+*(int *)(state+0x270)*0x70;
 if (*(char **)(effect+0x88)!=object || !*(unsigned char *)(effect+0x74))
 *(int *)(state+0x270)=ref_L05_00444B20_00(9,4,object,0xfbf);
 } else {
 float x,y;
 if(!*(int *)(state+0x26c)) {ref_L05_00444B20_00(8,0,object,0xfbf);*(int *)(state+0x26c)=1;}
 x=IntToFloat(point[0]);y=IntToFloat(point[1]);
 DrawSpriteRing(0,255,x,y,1.0f,0.0f,0,96);
 }
 } else {
 int id=*(int *)(state+0x270);
 if(id!=-1) {
 char *effect=g_sound_state+id*0x70;
 if(*(char **)(effect+0x88)==object && *(unsigned char *)(effect+0x74))ref_L05_00444B20_01(id);
 }
 *(int *)(state+0x26c)=0;
 *(int *)(state+0x270)=-1;
 }
}
