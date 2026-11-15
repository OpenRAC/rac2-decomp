#include "common.h"
extern void moby_get_anim_entry_count(void *,int *,int *);
extern int FloatToInt(float);
extern float math_random_signed_float_range(float,float),math_random_float_range(float,float);
extern float FastAddRotations(float,float),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void *cam_moby_create(void *,int,int,int,void *,void *,void *,int,float,float);
extern void snd_play_from_global_bank(int,int,int);
extern struct {char pad[0x158];float angle;} g_active_camera __attribute__((nosda));
extern float D_001AA030 __attribute__((sda));
extern void moby_fade_out_update(unsigned char *);
typedef struct { unsigned char threshold[16];float previous;} DamageThresholds;
typedef struct {float current;short maximum;} DamageHealth;
/* Breaks off pieces of an object as its health drops past set levels, and tells the caller if any came off. */
int part_spawn_damage_debris(char *moby,DamageThresholds *thresholds,DamageHealth *health)
{
    float velocity[4];
    int partFlags,unusedFlags;
    int anyBroke=0;
    float healthValue,throwAngle,throwSpeed;
    void *debris;
    if(thresholds->previous==0.0f && health->current!=0.0f) {
        int i;
        unsigned char healthFraction;
        moby_get_anim_entry_count(moby,&partFlags,&unusedFlags);
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
                throwAngle=FastAddRotations(math_random_signed_float_range(90.0f,120.0f)*0.01745329424738884f,g_active_camera.angle);
                throwSpeed=math_random_float_range(2.0f,4.0f)*0.01666666753590107f;
                velocity[0]=math_fast_sin_or_cos_a(throwAngle)*throwSpeed;
                velocity[1]=math_fast_sin_or_cos_b(throwAngle)*throwSpeed;
                velocity[2]=0;
                velocity[2]=math_random_float_range(5.0f,8.0f)*0.01666666753590107f;
                debris=cam_moby_create(moby,1,*(short *)(moby+0xaa),i,moby+0x10,moby+0xf0,velocity,255,D_001AA030,15.0f);
                if(debris) *(void (**)(unsigned char *))((char *)debris+0x64)=moby_fade_out_update;
                *(unsigned short *)(moby+0x7c)&=~partBit;
                if(!anyBroke)snd_play_from_global_bank(7,0,0);
                anyBroke=1;
            }
        }
    }
    thresholds->previous=health->current;
    return anyBroke;
}
