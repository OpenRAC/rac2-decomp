#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float,float);
extern char *func_0035CBA0(char *,int,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00350388(char *);
extern void func_L00_00326110(char *,float,int);
extern void func_L01_0031A278(char *,float,float,float,void *);
extern void func_002A0F48(char *);
extern float func_002A96A0(char *,char *);
extern void func_002AB800(char *,void *);
extern void func_002AB8C0(char *,void *);
extern int func_002B3868(char *);
extern void func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int func_003A0948(int,int,char *);
extern float func_00283B98(float,float);
extern int func_002A8C28(char *,void *,float,float,float,int,int,int,int);
extern void func_002B0A68(char *,int,void *,int,float,float,float,float);
extern void func_L06_00464F40(char *);
extern int D_0018C0B4 __attribute__((nosda));
extern float D_L06_001B1D70 __attribute__((sda));
extern float D_L06_001B1D70_4[] MACRO_ADDR;
extern struct { char pad[0x160]; float f160; int pad164, n168, n16c; char pad170[16]; float f180; int pad184,n188; } D_L06_001B9700 __attribute__((nosda));
/* The two height tests read their own values: with -frac2-gcse-unsplit-edges gcse leaves both
   loads in place, and reorg skips the second ground load on the first test's failure edge. */
void func_L06_004649F0(char *o) {
 float pos[4],v[4];
 char *s=*(char **)(o+0x68);
 float damage,t;
 int i;
 switch(*(unsigned char *)(o+0x20)) {
 case 0:
 *(short *)(s+0x24)=6; *(float *)(s+0x20)=6; *(int *)(s+0x80)=0;
 *(Quad *)v=0; v[0]=0.06666667f; v[2]=func_002A7878(6,9)*0.0166666675f;
 *(Quad *)pos=*(Quad *)v;
 func_002A0F48(o);
 matrix_mul_vec3(s+0x70,pos,o+0xC0);
 func_002A7750(o,1,-1); break;
 case 1:
 damage=func_002A96A0(o,func_0035CBA0(o,0x230000,0));
 if(damage>0) {
 ((unsigned char *)s)[0x57]=255; ((unsigned char *)s)[0x58]=128; ((unsigned char *)s)[0x59]=128;
 func_002AB800(o,s+0x50);
 *(float *)(s+0x20)-=damage;
 }
 if(*(float *)(s+0x20)<0) func_002A7750(o,2,-1);
 func_002AB8C0(o,s+0x50); ((unsigned char *)o)[0xA8]=255; break;
 case 2:
 if(func_002B3868(o)) {
 SpawnExplosion(o+0x10,1,25,20,20,20,45,1,1,20,1,1,0,0);
 func_003A0948(1,0,o);
 }
 func_002AB8C0(o,s+0x50);
 *(float *)(s+0x68)+=0.000290888245f;
 *(float *)(o+0xF4)=FastAddRotations(*(float *)(o+0xF4),*(float *)(s+0x68));
 if(*(float *)(o+0xF4)>0.628318548f && D_0018C0B4!=140) {
 *(int *)(o+0x98)=0;
 for(i=0;i<6;i++) {
 t=i*0.2f;
 func_L01_0031A278(o,t*1.5f+(-0.5f),0,t*7+2,pos);
 func_002A8C28(o,pos,0.8f,4,1,0x30009,0,1,0);
 }
 func_L01_0031A278(o,D_L06_001B1D70,D_L06_001B1D70_4[1],D_L06_001B1D70_4[2],pos);
 func_002A8C28(o,pos,2.5f,4,1,0x4030000,0,1,0);
 }
 if(*(float *)(o+0xF4)>1.2566371f) func_002A7750(o,3,-1);
 break;
 case 3:
 if(func_002B3868(o)) {
 *(Quad *)pos=0; pos[2]=0.06666667f;
 func_002B0A68(o,0x6FF,pos,255,3,6,3,7);
 func_003A0948(0,0,o);
 func_L00_00326110(o,0,9);
 D_L06_001B9700.f180=0.1f;
 D_L06_001B9700.n188=90;
 D_L06_001B9700.f160=0.2f;
 D_L06_001B9700.n168=60;
 D_L06_001B9700.n16c=0;
 *(unsigned short *)(o+0x7C)=0x8100;
 matrix_mul_vec3(v,&D_L06_001B1D70,o+0xC0);
 FastVecAdd(o+0x10,o+0x10,v);
 }
 func_002A8C28(o,o+0x10,2.5f,4,1,0x4030000,0,1,0);
 FastVecAdd(o+0x10,o+0x10,s+0x70);
 *(float *)(s+0x78)-=0.003f;
 if (!*(int *)(s+0x80) && *(float *)(o+0x18) < *(float *)(s+0x6C)) {
     func_L06_00464F40(o);
     *(int *)(s+0x80)=1;
 } else if (*(float *)(o+0x18) < *(float *)(s+0x6C)-4.0f)
     func_00350388(o);
 break;
 }
}
