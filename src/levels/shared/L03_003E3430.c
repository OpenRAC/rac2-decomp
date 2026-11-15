#include "common.h"
extern float D_L03_0029BBF0[][4], D_L03_001B9BC0[][4];
extern void func_00283098(void *, void *, void *);
extern float func_00282DB0(void *, void *), func_00283248(float,float), func_00283BE0(float,float);
void func_L03_003E3430(u8 *p) {
 float v[4];
 u8 *q=*(u8 **)(p+0x68);
 int count=0, i, j, best;
 u8 *list=q+0x40;
 float x,y,angle,score;
 for(j=0;j<8;j++) { if(list[j]==255)break; count++; }
 switch(count) {
 case 0: *(short *)(q+0x52)=*(unsigned short *)(q+0x50); break;
 case 1: *(short *)(q+0x52)=q[0x40];break;
 default: {
 matrix_mul_vec3(v,D_L03_0029BBF0[*(short *)(q+0x52)],p+0xC0);
 score=-10.0f;
 x=FastVecDot(v,D_L03_001B9BC0[0]);
 best=-1;
 y=FastVecDot(v,D_L03_001B9BC0[1]);
 angle=func_00283248(x,y);
 for(i=0;i<count;i++) {
 if(*(q+i+0x40)==*(short *)(q+0x52))continue;
 if(*(q+i+0x40)==255)break;
 {u8 *base=q+0x40; u8 *entry=base+i; float delta;
 matrix_mul_vec3(v,D_L03_0029BBF0[*entry],p+0xC0);
 x=FastVecDot(v,D_L03_001B9BC0[0]);
 y=FastVecDot(v,D_L03_001B9BC0[1]);
 delta=fast_subtract_rotations(func_00283248(x,y),angle);
 if(delta>0.0f)delta-=6.2831854820251465f;
 if(delta>score){score=delta;best=*entry;}
 }
 }
 if(best!=-1)*(short *)(q+0x52)=best;
 }
 }
}

