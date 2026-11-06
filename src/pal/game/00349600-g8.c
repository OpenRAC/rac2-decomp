/* func_PAL_00349600, the PAL copy of func_00347468: the same C, where the fields past 0x2e8 move, the
   string ids and sizes change, and the draw call becomes func_PAL_002802D8 with a width limit. */
#include "include_asm.h"
extern void func_00335E68(void *, int);
extern void func_00335E38(void *,float,float,float,float);
extern void func_00336320(void *),func_00336A78(void *),func_00336828(void *);
extern void func_00336920(void *,int,int);
extern void func_00336A38(void *,int);
extern int func_00288FB8(int);
extern void func_PAL_002802D8(int,int,unsigned long,int,int,int,float);
typedef struct {int x,y;} MenuIntegerPair;
extern MenuIntegerPair ref_00347468_00[];
extern float ref_00347468_01 __attribute__((sda));
extern float ref_00347468_02 __attribute__((sda));
extern float ref_00347468_03 __attribute__((sda));
extern float ref_00347468_04 __attribute__((sda));
extern float ref_00347468_05 __attribute__((sda));
extern float ref_00347468_06,ref_00347468_07,ref_00347468_08,ref_00347468_09;
typedef struct {short a,b,c,id,e;} MenuGridEntry;
extern MenuGridEntry ref_00347468_10[];
extern unsigned char D_001A7A80[] __attribute__((sda));
void func_PAL_00349600(char *o)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(o+0x574)+*(int *)(o+0x578)*4].id;
 float *v;
 { char *a=o+0x3c8,*b=o+0x450,*c=o+0x49c;
 func_00335E68(a,0);func_00335E68(b,0);func_00335E68(c,0);
 v=*(float **)(o+0x4e8);func_00335E38(b,v[0]+ref_00347468_02,v[1]+ref_00347468_07,0.0f,0.0f);
 v=*(float **)(o+0x4e8);func_00335E38(c,v[0]+ref_00347468_01,v[1]+ref_00347468_06,0.0f,0.0f);
 func_00335E38(a,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(D_001A7A80[id]&1) {
  int x,y;
  func_00336A38(o+0x318,func_00288FB8(3828));func_00336920(a,0xea98,0);
  func_00335E68(a,1);func_00335E68(b,1);func_00335E68(c,1);
  func_00336320(b);func_00336320(c);
  v=*(float **)(o+0x4e8);x=(int)(v[0]+ref_00347468_04);y=(int)(v[1]+ref_00347468_08);
  func_PAL_002802D8(x,y,0x80f0f0f0UL,func_00288FB8(4327),-1,175,0.7f);
 } else if(D_001A7A80[id]&4) {
  int x,y;
  func_00336A38(o+0x318,func_00288FB8(3827));func_00336920(a,0xea98,1);
  func_00335E68(a,1);func_00335E68(b,1);func_00335E68(c,1);
  func_00336320(b);func_00336320(c);
  v=*(float **)(o+0x4e8);x=(int)(v[0]+ref_00347468_04);y=(int)(v[1]+ref_00347468_08);
  func_PAL_002802D8(x,y,0x80f0f0f0UL,func_00288FB8(4326),-1,175,0.7f);
 }
 func_00336A78(o+0x318);func_00336828(o+0x3c8);
 }
 if(D_001A7A80[id]&0x10) {
  int x,y;char *t=o+0x370;
  char *a=o+0x3c8,*b=o+0x450,*c=o+0x49c;
  func_00336A38(t,func_00288FB8(3829));func_00336920(a,0xea98,2);
  func_00335E38(a,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  func_00335E68(a,1);func_00335E68(b,1);func_00335E68(c,1);
  v=*(float **)(o+0x4e8);func_00335E38(b,v[0]+ref_00347468_02,(v[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  v=*(float **)(o+0x4e8);func_00335E38(c,v[0]+ref_00347468_01,(v[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  func_00336320(b);func_00336320(c);
  v=*(float **)(o+0x4e8);x=(int)(v[0]+ref_00347468_05);y=(int)(v[1]+ref_00347468_09);
  func_PAL_002802D8(x,y,0x80f0f0f0UL,func_00288FB8(4328),-1,175,0.7f);
  func_00336828(a);func_00336A78(t);
 }
}
