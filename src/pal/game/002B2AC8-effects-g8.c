#include "include_asm.h"

#include "common.h"
extern void func_0029F648(void *,int *,int *);
extern int func_00283CF0(float);
extern float func_002A78D8(float,float),func_002A7878(float,float);
extern float func_00283B98(float,float),func_00283180(float),func_00283198(float);
extern void *func_PAL_002735D0(void *,int,int,int,void *,void *,void *,int,float,float);
extern void func_002E5E58(int,int,int);
extern struct {char pad[0x158];float angle;} D_001B5200 __attribute__((nosda));
extern float D_001AA030 __attribute__((sda));
extern void func_PAL_003120C0(unsigned char *);
typedef struct { unsigned char threshold[16];float previous;} DamageThresholds;
typedef struct {float current;short maximum;} DamageHealth;

int func_PAL_002B3F18(char *obj,DamageThresholds *thresholds,DamageHealth *health)
{
    float v[4];
    int flags,unused;
    int any=0;
    float value,angle,speed;
    void *effect;
    if(thresholds->previous==0.0f && health->current!=0.0f) {
        int i;
        unsigned char fraction;
        func_0029F648(obj,&flags,&unused);
        value=health->current;
        if(value<0.0f)value=0.0f;
        fraction=func_00283CF0(value/health->maximum*255.0f);
        for(i=0;i<15;i++) {
            int bit=1<<i;
            if((bit&flags) && thresholds->threshold[i] && thresholds->threshold[i]<fraction)
                *(unsigned short *)(obj+0x7c)|=bit;
        }
    }
    if(health->current<thresholds->previous) {
        int bit,i;
        unsigned char fraction;
        value=health->current;
        if(value<0.0f)value=0.0f;
        bit=1;
        fraction=func_00283CF0(
            value/health->maximum*255.0f);
        for(i=0;i<15;i++,bit<<=1) {
            if((*(unsigned short *)(obj+0x7c)&bit) && fraction<thresholds->threshold[i]) {
                angle=func_00283B98(func_002A78D8(90.0f,120.0f)*0.01745329424738884f,D_001B5200.angle);
                speed=func_002A7878(2.0f,4.0f)*0.020000001f;
                v[0]=func_00283180(angle)*speed;
                v[1]=func_00283198(angle)*speed;
                v[2]=0;
                v[2]=func_002A7878(5.0f,8.0f)*0.020000001f;
                effect=func_PAL_002735D0(obj,1,*(short *)(obj+0xaa),i,obj+0x10,obj+0xf0,v,255,D_001AA030,15.0f);
                if(effect) *(void (**)(unsigned char *))((char *)effect+0x64)=func_PAL_003120C0;
                *(unsigned short *)(obj+0x7c)&=~bit;
                if(!any)func_002E5E58(7,0,0);
                any=1;
            }
        }
    }
    thresholds->previous=health->current;
    return any;
}
