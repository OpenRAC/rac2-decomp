/* func_US2_L00_003AB8F8, the USA v2.00 copy of func_L00_003AA4C8: the 5 stored at 0x78 becomes a fifth argument, which its caller passes as 5. */
#include "common.h"
#define FIELD_F32(p,o) (*(float *)((char *)(p)+(o)))
#define FIELD_S32(p,o) (*(int *)((char *)(p)+(o)))
#define FIELD_S16(p,o) (*(short *)((char *)(p)+(o)))
#define FIELD_U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void cam_compute_view_direction(void *,void *,int);
extern void vec_scale_to_length(void *,void *,float);
extern char *CreateMoby(int);
extern unsigned char D_00139580;
typedef struct { char pad[0x50]; float scale; char tail[0x8C]; } EffectTiming;
extern EffectTiming g_weapon_l00_table[];
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void get_moby_color(void *,int *,int *,int *);
extern void FastVecCross(void *,void *,void *);
extern void anim_start_immediate(void *,int,int);
extern int part_alloc_effect_slot(void *,float,float,float,int);
char *func_US2_L00_003AB8F8(void *position,void *velocity,void *unused,void *owner,int value)
{
 float axis[4];
 int r,g,b;
 char *m=CreateMoby(0xD01),*d;
 float duration, inverse, denominator;
 int ticks;
 if(m) {
 FIELD_U8(m,0x30)=255; FIELD_S16(m,0x32)=255; FIELD_U8(m,0x31)=1; FIELD_U8(m,0x20)=0;
 d=*(char **)(m+0x68);
 denominator=((EffectTiming *)((char *)g_weapon_l00_table+D_00139580*sizeof(EffectTiming)))->scale*(1.0f/60.0f);
 duration=40.0f/denominator;
 ticks=FloatToInt(duration);
 inverse=1.0f/duration;
 FIELD_S32(d,0x74)=(int)owner; FIELD_S32(d,0x14)=0;FIELD_S32(d,0x30)=0; FIELD_S32(d,0x24)=0;FIELD_S32(d,0x28)=0;FIELD_S32(d,0x2C)=0;
 FIELD_S32(d,0x78)=value; FIELD_F32(d,0x20)=3.141592741f;FIELD_S16(d,0x18)=ticks;FIELD_F32(d,0x34)=inverse;
 FIELD_S16(d,0x1A)=math_random_int_below(255);
 FIELD_S32(d,0x3C)=0;FIELD_S32(d,0x1C)=0;FIELD_S32(d,0x7C)=0;FIELD_S32(d,0x58)=0;FIELD_F32(d,0x50)=0.5f;FIELD_S32(d,0x5C)=-1;
 get_moby_color(m,&r,&g,&b);
 FIELD_S32(d,0x38)=(b<<16)|(g<<8)|r;
 FIELD_F32(m,0x2C)*=1.5f;
 qcopy(m+0x10,position);
 qcopy(d,velocity);
 FIELD_S16(m,0x34)|=0x100;
 cam_compute_view_direction(m+0x10,axis,1);
 vec_scale_to_length(m+0xC0,d,1.0f);
 FastVecCross(m+0xD0,m+0xC0,axis);
 vec_scale_to_length(m+0xD0,m+0xD0,1.0f);
 FastVecCross(m+0xE0,m+0xD0,m+0xC0);
 anim_start_immediate(m,2,0);
 FIELD_S32(d,0x70)=part_alloc_effect_slot(m,1.0f,1.0f,1.0f,0);
 }
 return m;
}
