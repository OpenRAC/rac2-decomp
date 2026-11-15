#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
extern u8 *g_hero_moby NOT_SDA;
extern s32 D_L23_001B13D4 __attribute__((sda));
extern s32 D_L23_001B3718;
extern void part_queue_impact_effect(void *,void *,s32,const TI16 *,const float *,f32);
extern void part_start_effect_default_table(void *,void *,s32,const TI16 *,f32);
/* Plays a camera or hero effect on a target, either with extra settings or without. */
void cam_play_effect_on_target(u8 *target,s32 flags,s32 duration,TI16 *position,float *settings,s32 save)
{
    TI16 copy=*position;
    if(settings!=0)
        part_queue_impact_effect(g_hero_moby,target,flags,&copy,settings,(f32)duration);
    else
        part_start_effect_default_table(g_hero_moby,target,flags,&copy,(f32)duration);
    if((flags&4)!=0 || save!=0) D_L23_001B3718=D_L23_001B13D4;
}
