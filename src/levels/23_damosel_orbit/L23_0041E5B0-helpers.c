#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
extern u8 *D_0018C0B0 NOT_SDA;
extern s32 D_L23_001B13D4 __attribute__((sda));
extern s32 D_L23_001B3718;
extern void func_002A8F70(void *,void *,s32,const TI16 *,const float *,f32);
extern void func_002A90C8(void *,void *,s32,const TI16 *,f32);
/* Plays a camera or hero effect on a target, either with extra settings or without. */
void func_L23_0041E5B0(u8 *target,s32 flags,s32 duration,TI16 *position,float *settings,s32 save)
{
    TI16 copy=*position;
    if(settings!=0)
        QueueImpactEffect(gHeroMoby_0018C0B0,target,flags,&copy,settings,(f32)duration);
    else
        StartEffectWithDefaultTable(gHeroMoby_0018C0B0,target,flags,&copy,(f32)duration);
    if((flags&4)!=0 || save!=0) D_L23_001B3718=D_L23_001B13D4;
}
