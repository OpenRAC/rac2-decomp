#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_clear_128(void *);
extern int gfx_pack_color_floats(float, float, float, float);
void part_kill(void *);
int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern int CollLine(void *, void *, int, void *, void *);
extern char D_001BAFA0[];
extern void FastVecAdd(char *, char *, char *);
extern int gfx_pack_color_floats(float, float, float, float);
extern void FastVecAdd(char *, char *, char *);

/* func_002C38E0 is in the -G8 sibling. */

/* Advances a spark, stops it on collision, and decays its RGBA channels. */
void func_PAL_002C4810(char *p) {
 float v[4];char *q;
 if(!p)return;
 q=p+32;*(float *)(p+12)+=-120.00001f;
 FastVecAdd((char *)v,p+16,q);
 if(*(float *)q!=0 || *(float *)(q+4)!=0 || *(float *)(q+8)!=0){
 if(CollLine(p+16,v,2,p,0)){*(U128 *)(p+16)=*(U128 *)D_001BAFA0;vec_clear_128(q);*(float *)(p+12)+=*(float *)(p+12);}
 else {*(U128 *)(p+16)=*(U128 *)v;if(*(float *)(q+12)!=0)*(float *)(q+8)+=*(float *)(q+12);else *(float *)(q+8)+=-0.009072f;}}
 if(*(float *)(q+28)<=0 || FastDecTimer((short *)(p+10)) || *(float *)(p+12)<0 || v[0]<0.01f || v[1]<0.01f || v[2]<0.01f){part_kill(p);return;}
 *(float *)(q+16)+=-0.012f;if(*(float *)(q+16)<0)*(float *)(q+16)=0;
 *(float *)(q+20)+=-0.036012f;if(*(float *)(q+20)<0)*(float *)(q+20)=0;
 *(float *)(q+24)+=-0.060000002f;if(*(float *)(q+24)<0)*(float *)(q+24)=0;
 if(*(float *)(q+28)<0)*(float *)(q+28)=0;
 *(int *)(p+4)=gfx_pack_color_floats(*(float *)(q+16),*(float *)(q+20),*(float *)(q+24),*(float *)(q+28));p[8]--;
}
