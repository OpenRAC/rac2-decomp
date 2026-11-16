/* Creates an owned effect with a scaled lifetime and an orientation from its velocity. */
#include "common.h"
#define FIELD_F32(p,o) (*(float *)((char *)(p)+(o)))
#define FIELD_S32(p,o) (*(int *)((char *)(p)+(o)))
#define FIELD_S16(p,o) (*(short *)((char *)(p)+(o)))
#define FIELD_U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void cam_compute_view_direction(void *,void *,int);
extern void vec_scale_to_length(void *,void *,float);
extern char *CreateMoby(int);
extern unsigned char g_seeker_weapon_index;
typedef struct { char pad[0x50]; float scale; char tail[0x8C]; } EffectTiming;
extern EffectTiming g_weapon_l00_table[];
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void get_moby_color(void *,int *,int *,int *);
extern void FastVecCross(void *,void *,void *);
extern void anim_start_immediate(void *,int,int);
extern int part_alloc_effect_slot(void *,float,float,float,int);
char *effect_spawn_owned_moby(void *position,void *velocity,void *unused,void *owner)
{
 float axis[4];
 int r,g,b;
 char *moby=CreateMoby(0xD01 /* moby class 3329 */),*vars;
 float duration, inverse, denominator;
 int ticks;
 if(moby) {
 FIELD_U8(moby,0x30)=255; FIELD_S16(moby,0x32)=255; FIELD_U8(moby,0x31)=1; FIELD_U8(moby,0x20)=0;
 vars=*(char **)(moby+0x68);
 denominator=((EffectTiming *)((char *)g_weapon_l00_table+g_seeker_weapon_index*sizeof(EffectTiming)))->scale*(1.0f/60.0f);
 duration=40.0f/denominator;
 ticks=FloatToInt(duration);
 inverse=1.0f/duration;
 FIELD_S32(vars,0x74)=(int)owner; FIELD_S32(vars,0x14)=0;FIELD_S32(vars,0x30)=0; FIELD_S32(vars,0x24)=0;FIELD_S32(vars,0x28)=0;FIELD_S32(vars,0x2C)=0;
 FIELD_S32(vars,0x78)=5; FIELD_F32(vars,0x20)=3.141592741f;FIELD_S16(vars,0x18)=ticks;FIELD_F32(vars,0x34)=inverse;
 FIELD_S16(vars,0x1A)=math_random_int_below(255);
 FIELD_S32(vars,0x3C)=0;FIELD_S32(vars,0x1C)=0;FIELD_S32(vars,0x7C)=0;FIELD_S32(vars,0x58)=0;FIELD_F32(vars,0x50)=0.5f;FIELD_S32(vars,0x5C)=-1;
 get_moby_color(moby,&r,&g,&b);
 FIELD_S32(vars,0x38)=(b<<16)|(g<<8)|r;
 FIELD_F32(moby,0x2C)*=1.5f;
 qcopy(moby+0x10,position);
 qcopy(vars,velocity);
 FIELD_S16(moby,0x34)|=0x100;
 cam_compute_view_direction(moby+0x10,axis,1);
 vec_scale_to_length(moby+0xC0,vars,1.0f);
 FastVecCross(moby+0xD0,moby+0xC0,axis);
 vec_scale_to_length(moby+0xD0,moby+0xD0,1.0f);
 FastVecCross(moby+0xE0,moby+0xD0,moby+0xC0);
 anim_start_immediate(moby,2,0);
 FIELD_S32(vars,0x70)=part_alloc_effect_slot(moby,1.0f,1.0f,1.0f,0);
 }
 return moby;
}
