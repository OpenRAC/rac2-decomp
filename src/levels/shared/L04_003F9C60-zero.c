#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern int func_002A77E0(int);
extern float func_002A7878_range(float,float) __asm__("func_002A7878");
extern void func_00282F20(char *,char *,float);
extern void func_002B9180(void *);
extern int func_002A7820(int,int);
extern void func_L04_00358AE8(void *,void *,int,int,float);
extern unsigned char *func_002BDCE8(void *,float,float,float,float,int,void *,int,int);
/* Frees the 17 effects attached to the moby and, if asked, bursts sparks and puffs of smoke around it. */
void func_L04_003F9C60(unsigned char *moby,int sparks) {
    unsigned char *vars;
    unsigned char **effectSlot;
    int i=16, j, color, sign;
    int baseColor, negativeSign;
    union { Q16_B0e5d8f83 q; float f[4]; } scratch;
    unsigned char *puff,*puffData;
    vars=*(unsigned char **)(moby+0x68);
    effectSlot=(unsigned char **)(vars+0x1C);
    for(;i>=0;i--,effectSlot++) {
        if(*effectSlot)KillParticle(*effectSlot);
        *effectSlot=0;
    }
    if(sparks) {
        union { Q16_B0e5d8f83 q; float f[4]; } randomDir;
        float *velocity=randomDir.f;
        for(i=4;i>=0;i--) {
            randomDir.q=0;
            randomDir.f[0]=func_002A7878_range(-1,1);
            randomDir.f[1]=func_002A7878_range(-1,1);
            randomDir.f[2]=func_002A7878_range(-1,1);
            scratch.q=randomDir.q;
            vec_scale_to_length((char *)velocity,(char *)&scratch,func_002A7878_range(0.05000000447034836f,0.10000000894069672f));
            SpawnVelocityParticle(moby+0x10,velocity,0x7F2F4F6F,RandomIntRange(10,15),35000.0f);
        }
    }
    baseColor=0x606060; negativeSign=-1;
    for(j=2;j>=0;j--) {
        color=(RandomIntRange(32,128)<<24)|baseColor;
        sign=RandomIntBelow(2)?negativeSign:1;
        scratch.q=0; scratch.f[2]=1; scratch.f[3]=1;
        scratch.f[2]=func_002A7878_range(0.01f,0.025f);
        puff=SpawnSpinningSparkParticle(moby+0x10,0.2f,1,1.02f,140000.0f,sign,&scratch,color,0);
        if(puff) {
            puffData=puff+0x20;
            *(short *)(puff+0xA)=RandomIntRange(50,80);
            puffData[0xA]=color>>24;
            *(int *)(puffData+4)=2;
            puffData[0xB]=puff[0xA];
            if(RandomIntBelow(2))puff[3]=0x44;
        }
    }
}
