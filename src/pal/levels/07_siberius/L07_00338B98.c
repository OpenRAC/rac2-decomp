#include "include_asm.h"

#include "common.h"
extern char *func_002B9030(int);
extern int func_002A7820(int,int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A7878(float,float);
extern unsigned char *D_L07_001FEEA4, *D_L07_001FEF00;
extern int D_L07_001B2534 __attribute__((sda));

/* func_L07_002F2C70 is defined in L07_002BE770-g8.c (it reads small data through $gp). */

char *func_PAL_L07_00338B98(void *a, void *b, int c, int d)
{
 char *p=func_002B9030(0x68); char *q;
 if(p) {
 q=p+0x20;
 *(int *)(q+0x10)=func_002A7820(32,80);
 *(int *)(p+4)=0x808080;
 p[9]=func_00283CF0(2.0f)-16; p[1]=0; p[3]=0x48;
 if(func_002A77E0(2)) p[2]=D_L07_001FEEA4[0]; else p[2]=D_L07_001FEF00[0];
 *(float *)(p+12)=func_002A7878(0.1f,0.24f)*210000.0f;
 p[8]=func_002A77E0(255);
 qcopy(p+16,a); qcopy(q,b);
 *(short *)(p+10)=1<<func_002A7820(6,10);
 if(c) {*(short *)(p+10)=100; *(int *)(q+20)=1;}
 if(d) *(int *)(p+4)+=*(int *)(q+16)<<24;
 { float f=func_002A7820(0,100); int n=D_L07_001B2534; *(float *)(q+12)=f; D_L07_001B2534=n+1; }
 }
 return p;
}

