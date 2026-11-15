#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern int math_random_int_below(int);
extern float func_002A7878_range(float,float) __asm__("func_002A7878");
extern void vec_scale_to_length(char *,char *,float);
extern void part_kill(void *);
extern int math_random_int_range(int,int);
extern void part_spawn_velocity_particle(void *,void *,int,int,float);
extern unsigned char *SpawnSpinningSparkParticle(void *,float,float,float,float,int,void *,int,int);
/* func_PAL_L04_003FDE38, the PAL copy of func_L04_003F9C60: the same C, where two random
   float ranges grow by 6/5, the 10 to 15 range and the 50 to 80 value shrink by 5/6, and the
   divisor, counter and base colour are set before the loop in retail's order. */
void func_PAL_L04_003FDE38(unsigned char *m,int sparks) {
    unsigned char *s;
    unsigned char **slot;
    int i=16, j, color, sign, divisor, baseColor;
    union { Q16_B0e5d8f83 q; float f[4]; } tmp;
    unsigned char *p,*d;
    s=*(unsigned char **)(m+0x68);
    slot=(unsigned char **)(s+0x1C);
    for(;i>=0;i--,slot++) {
        if(*slot)part_kill(*slot);
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
            vec_scale_to_length((char *)velocity,(char *)&tmp,func_002A7878_range(0.060000002f,0.120000005f));
            part_spawn_velocity_particle(m+0x10,velocity,0x7F2F4F6F,math_random_int_range(8,12),35000.0f);
        }
    }
    divisor=6; j=2; baseColor=0x606060;
    for(;j>=0;j--) {
        color=(math_random_int_range(32,128)<<24)|baseColor;
        sign=math_random_int_below(2)?-1:1;
        tmp.q=0; tmp.f[2]=1; tmp.f[3]=1;
        tmp.f[2]=func_002A7878_range(0.01f,0.025f)*1.2f;
        p=SpawnSpinningSparkParticle(m+0x10,0.2f,1,1.02f,140000.0f,sign,&tmp,color,0);
        if(p) {
            d=p+0x20;
            *(short *)(p+0xA)=(math_random_int_range(50,80)*5+2)/divisor;
            *(int *)(d+4)=2;
            d[0xA]=color>>24;
            d[0xB]=p[0xA];
            if(math_random_int_below(2))p[3]=0x44;
        }
    }
}
