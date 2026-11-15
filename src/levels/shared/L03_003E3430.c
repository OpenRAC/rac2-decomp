#include "common.h"
extern float D_L03_0029BBF0[][4], D_L03_001B9BC0[][4];
extern void func_00283098(void *, void *, void *);
extern float func_00282DB0(void *, void *), func_00283248(float,float), func_00283BE0(float,float);
/* Picks which node the puzzle moves to next from the nodes that are open, preferring the one that turns furthest around. */
void func_L03_003E3430(u8 *moby) {
 float v[4];
 u8 *vars=*(u8 **)(moby+0x68);
 int count=0, i, j, best;
 u8 *list=vars+0x40;
 float x,y,angle,score;
 for(j=0;j<8;j++) { if(list[j]==255)break; count++; }
 switch(count) {
 case 0: *(short *)(vars+0x52)=*(unsigned short *)(vars+0x50); break;
 case 1: *(short *)(vars+0x52)=vars[0x40];break;
 default: {
 matrix_mul_vec3(v,D_L03_0029BBF0[*(short *)(vars+0x52)],moby+0xC0);
 score=-10.0f;
 x=FastVecDot(v,D_L03_001B9BC0[0]);
 best=-1;
 y=FastVecDot(v,D_L03_001B9BC0[1]);
 angle=FastMatrixHelperA(x,y);
 for(i=0;i<count;i++) {
 if(*(vars+i+0x40)==*(short *)(vars+0x52))continue;
 if(*(vars+i+0x40)==255)break;
 {u8 *base=vars+0x40; u8 *entry=base+i; float delta;
 matrix_mul_vec3(v,D_L03_0029BBF0[*entry],moby+0xC0);
 x=FastVecDot(v,D_L03_001B9BC0[0]);
 y=FastVecDot(v,D_L03_001B9BC0[1]);
 delta=fast_subtract_rotations(FastMatrixHelperA(x,y),angle);
 if(delta>0.0f)delta-=6.2831854820251465f;
 if(delta>score){score=delta;best=*entry;}
 }
 }
 if(best!=-1)*(short *)(vars+0x52)=best;
 }
 }
}

