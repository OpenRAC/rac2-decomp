/* Creates an owned effect with a scaled lifetime and an orientation from its velocity. */
#include "common.h"
#define FIELD_F32(p,o) (*(float *)((char *)(p)+(o)))
#define FIELD_S32(p,o) (*(int *)((char *)(p)+(o)))
#define FIELD_S16(p,o) (*(short *)((char *)(p)+(o)))
#define FIELD_U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void func_002AFFD8(void *,void *,int);
extern void func_00282F20(void *,void *,float);
extern char *func_0029EFD0(int);
extern unsigned char D_00139580;
typedef struct { char pad[0x50]; float scale; char tail[0x8C]; } EffectTiming;
extern EffectTiming D_L00_00262570[];
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002A04B8(void *,int *,int *,int *);
extern void func_00282DD8(void *,void *,void *);
extern void func_002A7398(void *,int,int);
extern int func_002FED90(void *,float,float,float,int);
char *func_L00_003AA4C8(void *position,void *velocity,void *unused,void *owner)
{
 float axis[4];
 int r,g,b;
 char *moby=CreateMoby(0xD01 /* moby class 3329 */),*vars;
 float duration, inverse, denominator;
 int ticks;
 if(moby) {
 FIELD_U8(moby,0x30)=255; FIELD_S16(moby,0x32)=255; FIELD_U8(moby,0x31)=1; FIELD_U8(moby,0x20)=0;
 vars=*(char **)(moby+0x68);
 denominator=((EffectTiming *)((char *)gWeaponTable_L00+D_00139580*sizeof(EffectTiming)))->scale*(1.0f/60.0f);
 duration=40.0f/denominator;
 ticks=FloatToInt(duration);
 inverse=1.0f/duration;
 FIELD_S32(vars,0x74)=(int)owner; FIELD_S32(vars,0x14)=0;FIELD_S32(vars,0x30)=0; FIELD_S32(vars,0x24)=0;FIELD_S32(vars,0x28)=0;FIELD_S32(vars,0x2C)=0;
 FIELD_S32(vars,0x78)=5; FIELD_F32(vars,0x20)=3.141592741f;FIELD_S16(vars,0x18)=ticks;FIELD_F32(vars,0x34)=inverse;
 FIELD_S16(vars,0x1A)=RandomIntBelow(255);
 FIELD_S32(vars,0x3C)=0;FIELD_S32(vars,0x1C)=0;FIELD_S32(vars,0x7C)=0;FIELD_S32(vars,0x58)=0;FIELD_F32(vars,0x50)=0.5f;FIELD_S32(vars,0x5C)=-1;
 get_moby_color(moby,&r,&g,&b);
 FIELD_S32(vars,0x38)=(b<<16)|(g<<8)|r;
 FIELD_F32(moby,0x2C)*=1.5f;
 qcopy(moby+0x10,position);
 qcopy(vars,velocity);
 FIELD_S16(moby,0x34)|=0x100;
 ComputeViewDirection(moby+0x10,axis,1);
 vec_scale_to_length(moby+0xC0,vars,1.0f);
 FastVecCross(moby+0xD0,moby+0xC0,axis);
 vec_scale_to_length(moby+0xD0,moby+0xD0,1.0f);
 FastVecCross(moby+0xE0,moby+0xD0,moby+0xC0);
 StartAnimationImmediate(moby,2,0);
 FIELD_S32(vars,0x70)=AllocEffectSlot_002FED90(moby,1.0f,1.0f,1.0f,0);
 }
 return moby;
}
