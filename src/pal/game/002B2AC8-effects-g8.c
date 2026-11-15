#include "include_asm.h"

#include "common.h"
extern void moby_get_anim_entry_count(void *,int *,int *);
extern int FloatToInt(float);
extern float math_random_signed_float_range(float,float),math_random_float_range(float,float);
extern float FastAddRotations(float,float),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void *func_PAL_002735D0(void *,int,int,int,void *,void *,void *,int,float,float);
extern int snd_play_from_global_bank(int,int,int);
extern struct {char pad[0x158];float angle;} g_active_camera __attribute__((nosda));
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
        moby_get_anim_entry_count(obj,&flags,&unused);
        value=health->current;
        if(value<0.0f)value=0.0f;
        fraction=FloatToInt(value/health->maximum*255.0f);
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
        fraction=FloatToInt(
            value/health->maximum*255.0f);
        for(i=0;i<15;i++,bit<<=1) {
            if((*(unsigned short *)(obj+0x7c)&bit) && fraction<thresholds->threshold[i]) {
                angle=FastAddRotations(math_random_signed_float_range(90.0f,120.0f)*0.01745329424738884f,g_active_camera.angle);
                speed=math_random_float_range(2.0f,4.0f)*0.020000001f;
                v[0]=math_fast_sin_or_cos_a(angle)*speed;
                v[1]=math_fast_sin_or_cos_b(angle)*speed;
                v[2]=0;
                v[2]=math_random_float_range(5.0f,8.0f)*0.020000001f;
                effect=func_PAL_002735D0(obj,1,*(short *)(obj+0xaa),i,obj+0x10,obj+0xf0,v,255,D_001AA030,15.0f);
                if(effect) *(void (**)(unsigned char *))((char *)effect+0x64)=func_PAL_003120C0;
                *(unsigned short *)(obj+0x7c)&=~bit;
                if(!any)snd_play_from_global_bank(7,0,0);
                any=1;
            }
        }
    }
    thresholds->previous=health->current;
    return any;
}
