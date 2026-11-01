#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282C88(void *);
extern int func_002AAE98(float, float, float, float);
void func_002B9180(void *);
int func_00282978(short *);
extern void func_00282CC0(char *, char *, char *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern char D_001BAFA0[];
extern void func_00282CC0(char *, char *, char *);
extern int func_002AAE98(float, float, float, float);
extern void func_00282CC0(char *, char *, char *);

/* func_002C38E0 is in the -G8 sibling. */

/* Advances a spark, stops it on collision, and decays its RGBA channels. */
void func_PAL_002C4810(char *p) {
 float v[4];char *q;
 if(!p)return;
 q=p+32;*(float *)(p+12)+=-120.00001f;
 func_00282CC0((char *)v,p+16,q);
 if(*(float *)q!=0 || *(float *)(q+4)!=0 || *(float *)(q+8)!=0){
 if(func_002761F8(p+16,v,2,p,0)){*(U128 *)(p+16)=*(U128 *)D_001BAFA0;func_00282C88(q);*(float *)(p+12)+=*(float *)(p+12);}
 else {*(U128 *)(p+16)=*(U128 *)v;if(*(float *)(q+12)!=0)*(float *)(q+8)+=*(float *)(q+12);else *(float *)(q+8)+=-0.009072f;}}
 if(*(float *)(q+28)<=0 || func_00282978((short *)(p+10)) || *(float *)(p+12)<0 || v[0]<0.01f || v[1]<0.01f || v[2]<0.01f){func_002B9180(p);return;}
 *(float *)(q+16)+=-0.012f;if(*(float *)(q+16)<0)*(float *)(q+16)=0;
 *(float *)(q+20)+=-0.036012f;if(*(float *)(q+20)<0)*(float *)(q+20)=0;
 *(float *)(q+24)+=-0.060000002f;if(*(float *)(q+24)<0)*(float *)(q+24)=0;
 if(*(float *)(q+28)<0)*(float *)(q+28)=0;
 *(int *)(p+4)=func_002AAE98(*(float *)(q+16),*(float *)(q+20),*(float *)(q+24),*(float *)(q+28));p[8]--;
}
