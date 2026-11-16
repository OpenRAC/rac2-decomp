/* func_US2_L00_003AB8F8, the USA v2.00 copy of func_L00_003AA4C8: the 5 stored at 0x78 becomes a fifth argument, which its caller passes as 5. */
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
/* Creates the owned seeker effect moby (class 0xD01) at a position with a velocity, timed from the weapon table (US2: the mode is a fifth argument). */
char *effect_spawn_owned_moby_us2(void *position,void *velocity,void *unused,void *owner,int mode)
{
 float axis[4];
 int red,green,blue;
 char *effect=CreateMoby(0xD01),*vars;
 float duration, inverse, denominator;
 int ticks;
 if(effect) {
 FIELD_U8(effect,0x30)=255; FIELD_S16(effect,0x32)=255; FIELD_U8(effect,0x31)=1; FIELD_U8(effect,0x20)=0;
 vars=*(char **)(effect+0x68);
 denominator=((EffectTiming *)((char *)g_weapon_l00_table+g_seeker_weapon_index*sizeof(EffectTiming)))->scale*(1.0f/60.0f);
 duration=40.0f/denominator;
 ticks=FloatToInt(duration);
 inverse=1.0f/duration;
 FIELD_S32(vars,0x74)=(int)owner; FIELD_S32(vars,0x14)=0;FIELD_S32(vars,0x30)=0; FIELD_S32(vars,0x24)=0;FIELD_S32(vars,0x28)=0;FIELD_S32(vars,0x2C)=0;
 FIELD_S32(vars,0x78)=mode; FIELD_F32(vars,0x20)=3.141592741f;FIELD_S16(vars,0x18)=ticks;FIELD_F32(vars,0x34)=inverse;
 FIELD_S16(vars,0x1A)=math_random_int_below(255);
 FIELD_S32(vars,0x3C)=0;FIELD_S32(vars,0x1C)=0;FIELD_S32(vars,0x7C)=0;FIELD_S32(vars,0x58)=0;FIELD_F32(vars,0x50)=0.5f;FIELD_S32(vars,0x5C)=-1;
 get_moby_color(effect,&red,&green,&blue);
 FIELD_S32(vars,0x38)=(blue<<16)|(green<<8)|red;
 FIELD_F32(effect,0x2C)*=1.5f;
 qcopy(effect+0x10,position);
 qcopy(vars,velocity);
 FIELD_S16(effect,0x34)|=0x100;
 cam_compute_view_direction(effect+0x10,axis,1);
 vec_scale_to_length(effect+0xC0,vars,1.0f);
 FastVecCross(effect+0xD0,effect+0xC0,axis);
 vec_scale_to_length(effect+0xD0,effect+0xD0,1.0f);
 FastVecCross(effect+0xE0,effect+0xD0,effect+0xC0);
 anim_start_immediate(effect,2,0);
 FIELD_S32(vars,0x70)=part_alloc_effect_slot(effect,1.0f,1.0f,1.0f,0);
 }
 return effect;
}
