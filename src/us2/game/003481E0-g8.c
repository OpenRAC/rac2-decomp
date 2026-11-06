#include "include_asm.h"
/* func_US2_003481E0, the USA v2.00 copy of func_00347468: the same C without the 0x2e8 and 0x330 label
 * elements, a smaller object (fields 0x60 lower, 0x38 for the selection indices), and func_US2_00280440
 * for the captions. */
extern void func_00335E68(void *, int);
extern void func_00335E38(void *,float,float,float,float);
extern void func_00336320(void *),func_00336828(void *);
extern void func_00336920(void *,int,int);
extern int func_00288FB8(int);
extern void func_US2_00280440(int,int,unsigned long,int,int,int,float);
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
void func_US2_003481E0(char *o)
{
 MenuIntegerPair pos=ref_00347468_00[0];
 int id=ref_00347468_10[*(int *)(o+0x4c4)+*(int *)(o+0x4c8)*4].id;
 float *v;
 { char *a=o+0x318,*b=o+0x3a0,*c=o+0x3ec;
 func_00335E68(a,0);func_00335E68(b,0);func_00335E68(c,0);
 v=*(float **)(o+0x438);func_00335E38(b,v[0]+ref_00347468_02,v[1]+ref_00347468_07,0.0f,0.0f);
 v=*(float **)(o+0x438);func_00335E38(c,v[0]+ref_00347468_01,v[1]+ref_00347468_06,0.0f,0.0f);
 func_00335E38(a,(float)pos.x,(float)pos.y,0.0f,0.0f);
 if(D_001A7A80[id]&1) {
  int x,y;
  func_00336920(a,0xea98,0);
  func_00335E68(a,1);func_00335E68(b,1);func_00335E68(c,1);
  func_00336320(b);func_00336320(c);
  v=*(float **)(o+0x438);x=(int)(v[0]+ref_00347468_04);y=(int)(v[1]+ref_00347468_08);
  func_US2_00280440(x,y,0x80f0f0f0UL,func_00288FB8(0x3065),-1,0xaf,0.7f);
 } else if(D_001A7A80[id]&4) {
  int x,y;
  func_00336920(a,0xea98,1);
  func_00335E68(a,1);func_00335E68(b,1);func_00335E68(c,1);
  func_00336320(b);func_00336320(c);
  v=*(float **)(o+0x438);x=(int)(v[0]+ref_00347468_04);y=(int)(v[1]+ref_00347468_08);
  func_US2_00280440(x,y,0x80f0f0f0UL,func_00288FB8(0x3064),-1,0xaf,0.7f);
 }
 func_00336828(o+0x318);
 }
 if(D_001A7A80[id]&0x10) {
  int x,y;
  char *a=o+0x318,*b=o+0x3a0,*c=o+0x3ec;
  func_00336920(a,0xea98,2);
  func_00335E38(a,(float)pos.x,(float)(pos.y+45),0.0f,0.0f);
  func_00335E68(a,1);func_00335E68(b,1);func_00335E68(c,1);
  v=*(float **)(o+0x438);func_00335E38(b,v[0]+ref_00347468_02,(v[1]+ref_00347468_07)+ref_00347468_03,0.0f,0.0f);
  v=*(float **)(o+0x438);func_00335E38(c,v[0]+ref_00347468_01,(v[1]+ref_00347468_06)+ref_00347468_03,0.0f,0.0f);
  func_00336320(b);func_00336320(c);
  v=*(float **)(o+0x438);x=(int)(v[0]+ref_00347468_05);y=(int)(v[1]+ref_00347468_09);
  func_US2_00280440(x,y,0x80f0f0f0UL,func_00288FB8(0x3066),-1,0xaf,0.7f);
  func_00336828(a);
 }
}
