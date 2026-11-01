#include "include_asm.h"

#include "common.h"
typedef union { struct { float x,y,z,w; } v; unsigned int quad __attribute__((mode(TI))); } V1078;
typedef struct { unsigned char b[8]; } P1078;
extern const P1078 D_L11_001B2930, D_L11_001B2938;
extern const V1078 D_L11_001B2940[2];
extern void func_L11_004701A0(char *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void func_00282D30(void *, void *, float);
extern int func_L00_0033E220(void *, void *, int, float, int, int, float, int, int, int);
extern float func_002A7878(float,float);
extern float func_002A7940(void);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002A7750(void *,int,int);
extern void func_L00_002E6EF8(void (*)(char *),void *);
extern void func_L00_00324F18(void *,void *,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern float func_00283248(float,float);
extern float func_00282E80(void *,void *);
extern float func_00283BE0(float,float);
extern float func_002A78D8(float,float);
extern float func_00282E48(void *,void *);
extern int func_002A9640(void *,int,int);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void func_PAL_L00_002ED7E8(void *,void *,float,void *,float,int,int,float,float,float);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_002B9180(int);
extern char *func_L00_00326620(void *,int,int);
extern int func_00282948(void *);
extern void func_00283098(void *,void *,void *);
extern int func_002A7820(int,int);
extern void func_00282F20(void *,void *,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_002A7A00(void *,float,float);

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
 func_00282D30(&offset,&offset,F(obj,0x2c));
 I(data,4)=func_L00_0033E220(&offset,obj,0x1fffffff,315000.0f,-1,0,0.0f,-1,0,-1);
 I(data,8)=func_L00_0033E220(&offset,obj,0x3f106060,315000.0f,-1,1,0.0f,-1,0,-1);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 a=func_002A7878(0.75f,1.25f); b=func_002A7940(); c=func_002A7940();
 func_002AF000(point,a,b,c); func_00282CC0(point,obj+0x10,point);
 }
 func_002A7750(obj,1,-1); break;
 }
 case 1: {
 int i;
 float a,b,c,r;
 func_L00_002E6EF8(func_L11_004701A0,obj);
 func_L00_00324F18(obj,&center,0,0,height);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 func_00282CF0(&temp,obj+0x10,point);
 a=func_00283248(point->v.x-center.v.x,point->v.y-center.v.y);
 r=func_00282E80(&center,point);
 b=func_00283248(r,point->v.z-center.v.z);
 a=func_00283BE0(a,0.0523598827f);
 c=func_002A78D8(1,3);
 b=func_00283BE0(b,c*0.0174532942f);
 if(b>1.1f)b=1.1f; if(b< -1.1f)b= -1.1f;
 r=func_00282E48(&center,point);
 r+=func_002A78D8(0.020000001f,0.020000001f);
 if(r>1.05f)r=1.05f;if(r<0.75f)r=0.75f;
 func_002AF000(point,r,a,b); func_00282CC0(point,&center,point);
 }
 if(func_002A9640(obj,0x04010000,0) && !I(data,0)) {
 func_002A7750(obj,2,-1);
 } B(obj,0xa8)=255; break;
 }
 case 2:
 func_PAL_L00_0032C328(obj,bounds,&q,&p,65535,0,-1,0,65535,255,0);
 func_PAL_L00_002ED7E8(obj,&offset,0.1f,&small,0.18f,80,3,1,20,1);
 temp.quad=0;
 func_L00_00324F18(obj,&offset,0,0,18);
 func_PAL_002AC718(obj,&temp,&offset,0,0,10,3,5,0,1,9,0.5f,-1,0,0,0,none,0,0x810001);
 func_002B9180(I(data,4));func_002B9180(I(data,8));func_L00_00326620(obj,sound,0);
 *(unsigned short *)(obj+0x34)|=1;I(obj,0x98)=0;B(obj,0x31)=0;
 I(data,0xc)=100; I(data,0x14)=500;func_002A7750(obj,3,-1);break;
 case 3: {
 int i,n;
 float a;
 if(func_00282948(data+0xc) || I(data,0xc)>=76) {
 temp.quad=0;temp.v.x=0.040000003f;temp.v.z=0.040000003f;
 func_00283098(&temp,&temp,obj+0xc0);
 a=19; if(H(obj,0xaa)==0x10ea) a=17; offset.v.z=a;
 func_PAL_L00_002ED7E8(obj,&offset,0,&temp,0.040000003f,func_002A7820(3,6),0,0.5f,15,1);
 temp.v.x=-0.040000003f;temp.v.z=0.048000004f;
 func_00283098(&temp,&temp,obj+0xc0);
 func_PAL_L00_002ED7E8(obj,&offset,0,&temp,0.040000003f,func_002A7820(3,6),1,0.5f,15,1);
 I(data,0xc)=((s32)(func_002A7820(45,90)) * 5 + 2) / 6;
 }
 func_L00_00324F18(obj,&v,0,0,18);
 if(!func_00282948(data+0x14)) {
 func_L00_002E6EF8(func_L11_004701A0,obj);
 for(i=0;i<I(data,0x10);i++) {
 V1078 *point=(V1078 *)(data+0x20+i*16);
 func_00282CF0(&temp,point,obj+0x10);temp.v.z=0;
 func_00282F20(&temp,&temp,1);
 axis.quad=0;axis.v.z=1;
 func_002ACEC0(&center,&temp,&axis,(float)I(data,0x14)*-0.002617994323372841f);
 func_002A7A00(&temp,1,1);
 a=func_002A7878(-0.25f,0.75f); center.v.z+=a;
 func_00282CC0(&center,&temp,&center);
 a=func_002A7878(0.020000001f,0.020000001f);
 func_00282F20(&center,&center,a+a);func_00282CC0(point,&center,point);
 }
 }
 if(I(data,0x14)<50) F(data,0x18)=(float)I(data,0x14)*0.02f;
 break;
 }
 }
}
