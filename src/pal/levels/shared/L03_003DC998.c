#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003DC998);

#include "common.h"
extern void func_00282CC0(void *,void *,void *),func_00282D30(void *,void *,float),func_002A8C00(void *,u8 *,int,void *,float),func_002A7750(u8 *,u8,int),func_PAL_L00_003E74D8(void *,int,int),func_002A7A00(float *,float,float),func_0029F338(u8 *);
extern int func_002761F8(void *,void *,int,int,void *),func_00282978(void *),func_002A77E0(int);
extern float func_002A7878(float,float);
extern void func_002C65A0(void *,void *,int,int,int,int,int,float,float,float,int);
extern u8 D_L03_001A8F20[] __attribute__((sda));
extern u8 D_L03_001BFDE0[];

void func_PAL_L03_003DD8A8(u8 *p) {
 float next[4],matrix[12],pos[4],step[4],particle[4];
 u8 *q=*(u8 **)(p+0x68);int i,color;float size;
 switch(p[0x20]) {
 case 0:
 func_00282CC0(next,p+0x10,q);
 if(*(short *)(q+0x12)<12)(*(short *)(q+0x12))++;
 func_002A8C00(matrix,p,0x10001,D_L03_001A8F20,(float)*(int *)(q+0x18));
 if(func_002761F8(p+0x10,next,0,*(int *)(q+0x14),matrix)){
 *(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;func_002A7750(p,1,-1);
 func_PAL_L00_003E74D8(D_L03_001BFDE0,10,1);goto finishmove;
 }
 if(func_00282978(q+0x10)){
 *(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;func_002A7750(p,1,-1);goto finishmove;
 }
 qcopy(pos,p+0x10);func_00282D30(step,q,0.2f);
 for(i=4;i>=0;i--){
 size=func_002A7878(0.1f,0.3f);color=func_002A77E0(255);
 func_002A7A00(particle,0.0f,0.1f);func_00282CC0(particle,particle,pos);
 func_002C65A0(particle,D_L03_001A8F20,12,0x808080,color,32,0,size*210000.0f,size*42000.0f,0.0f,0);
 func_00282CC0(pos,pos,step);
 }
 finishmove:
 qcopy(p+0x10,next);break;
 case 1:
 if(--*(short *)(q+0x12)==-1)func_0029F338(p);break;
 }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003DDB50);
