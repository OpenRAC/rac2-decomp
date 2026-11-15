#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern int func_002A77E0(int);
extern float func_002A7878_range(float,float) __asm__("func_002A7878");
extern void func_00282F20(char *,char *,float);
extern void func_002B9180(void *);
extern int func_002A7820(int,int);
extern void func_L04_00358AE8(void *,void *,int,int,float);
extern unsigned char *func_002BDCE8(void *,float,float,float,float,int,void *,int,int);
void func_L04_003F9C60(unsigned char *m,int sparks) {
    unsigned char *s;
    unsigned char **slot;
    int i=16, j, color, sign;
    int baseColor, negativeSign;
    union { Q16_B0e5d8f83 q; float f[4]; } tmp;
    unsigned char *p,*d;
    s=*(unsigned char **)(m+0x68);
    slot=(unsigned char **)(s+0x1C);
    for(;i>=0;i--,slot++) {
        if(*slot)func_002B9180(*slot);
        *slot=0;
    }
    if(sparks) {
        union { Q16_B0e5d8f83 q; float f[4]; } v;
        float *velocity=v.f;
        for(i=4;i>=0;i--) {
            v.q=0;
            v.f[0]=func_002A7878_range(-1,1);
            v.f[1]=func_002A7878_range(-1,1);
            v.f[2]=func_002A7878_range(-1,1);
            tmp.q=v.q;
            vec_scale_to_length((char *)velocity,(char *)&tmp,func_002A7878_range(0.05000000447034836f,0.10000000894069672f));
            func_L04_00358AE8(m+0x10,velocity,0x7F2F4F6F,func_002A7820(10,15),35000.0f);
        }
    }
    baseColor=0x606060; negativeSign=-1;
    for(j=2;j>=0;j--) {
        color=(func_002A7820(32,128)<<24)|baseColor;
        sign=func_002A77E0(2)?negativeSign:1;
        tmp.q=0; tmp.f[2]=1; tmp.f[3]=1;
        tmp.f[2]=func_002A7878_range(0.01f,0.025f);
        p=SpawnSpinningSparkParticle(m+0x10,0.2f,1,1.02f,140000.0f,sign,&tmp,color,0);
        if(p) {
            d=p+0x20;
            *(short *)(p+0xA)=func_002A7820(50,80);
            d[0xA]=color>>24;
            *(int *)(d+4)=2;
            d[0xB]=p[0xA];
            if(func_002A77E0(2))p[3]=0x44;
        }
    }
}
