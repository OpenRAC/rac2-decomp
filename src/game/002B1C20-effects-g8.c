#include "common.h"
extern void func_0029F648(void *,int *,int *);
extern int func_00283CF0(float);
extern float func_002A78D8(float,float),func_002A7878(float,float);
extern float func_00283B98(float,float),func_00283180(float),func_00283198(float);
extern void *func_00273730(void *,int,int,int,void *,void *,void *,int,float,float);
extern void func_002E5E58(int,int,int);
extern struct {char pad[0x158];float angle;} D_001B5200 __attribute__((nosda));
extern float D_001AA030 __attribute__((sda));
extern void func_00310C88(unsigned char *);
typedef struct { unsigned char threshold[16];float previous;} DamageThresholds;
typedef struct {float current;short maximum;} DamageHealth;
/* Breaks off pieces of an object as its health drops past set levels, and tells the caller if any came off. */
int func_002B3380(char *moby,DamageThresholds *thresholds,DamageHealth *health)
{
    float velocity[4];
    int partFlags,unusedFlags;
    int anyBroke=0;
    float healthValue,throwAngle,throwSpeed;
    void *debris;
    if(thresholds->previous==0.0f && health->current!=0.0f) {
        int i;
        unsigned char healthFraction;
        GetMobyAnimationEntryCount(moby,&partFlags,&unusedFlags);
        healthValue=health->current;
        if(healthValue<0.0f)healthValue=0.0f;
        healthFraction=FloatToInt(healthValue/health->maximum*255.0f);
        for(i=0;i<15;i++) {
            int partBit=1<<i;
            if((partBit&partFlags) && thresholds->threshold[i] && thresholds->threshold[i]<healthFraction)
                *(unsigned short *)(moby+0x7c)|=partBit;
        }
    }
    if(health->current<thresholds->previous) {
        int partBit,i;
        unsigned char healthFraction;
        healthValue=health->current;
        if(healthValue<0.0f)healthValue=0.0f;
        partBit=1;
        healthFraction=FloatToInt(
            healthValue/health->maximum*255.0f);
        for(i=0;i<15;i++,partBit<<=1) {
            if((*(unsigned short *)(moby+0x7c)&partBit) && healthFraction<thresholds->threshold[i]) {
                throwAngle=FastAddRotations(RandomSignedFloatRange(90.0f,120.0f)*0.01745329424738884f,gActiveCamera.angle);
                throwSpeed=RandomFloatRange(2.0f,4.0f)*0.01666666753590107f;
                velocity[0]=FastSinOrCosA(throwAngle)*throwSpeed;
                velocity[1]=FastSinOrCosB(throwAngle)*throwSpeed;
                velocity[2]=0;
                velocity[2]=RandomFloatRange(5.0f,8.0f)*0.01666666753590107f;
                debris=CreateCameraMoby(moby,1,*(short *)(moby+0xaa),i,moby+0x10,moby+0xf0,velocity,255,D_001AA030,15.0f);
                if(debris) *(void (**)(unsigned char *))((char *)debris+0x64)=UpdateFadeOutMoby;
                *(unsigned short *)(moby+0x7c)&=~partBit;
                if(!anyBroke)PlaySoundFromGlobalBank(7,0,0);
                anyBroke=1;
            }
        }
    }
    thresholds->previous=health->current;
    return anyBroke;
}
