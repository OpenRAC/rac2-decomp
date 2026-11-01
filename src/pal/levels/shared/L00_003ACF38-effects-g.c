#include "include_asm.h"

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

char *func_PAL_L00_003ADC68(void *position,void *velocity,void *unused,void *owner)
{
 float axis[4];
 int r,g,b;
 char *m=func_0029EFD0(0xD01),*d;
 float duration, inverse, denominator;
 int ticks;
 if(m) {
 FIELD_U8(m,0x30)=255; FIELD_S16(m,0x32)=255; FIELD_U8(m,0x31)=1; FIELD_U8(m,0x20)=0;
 d=*(char **)(m+0x68);
 denominator=((EffectTiming *)((char *)D_L00_00262570+D_00139580*sizeof(EffectTiming)))->scale*(0.020000001f);
 duration=40.0f/denominator;
 ticks=func_00283CF0(duration);
 inverse=1.0f/duration;
 FIELD_S32(d,0x74)=(int)owner; FIELD_S32(d,0x14)=0;FIELD_S32(d,0x30)=0; FIELD_S32(d,0x24)=0;FIELD_S32(d,0x28)=0;FIELD_S32(d,0x2C)=0;
 FIELD_S32(d,0x78)=4; FIELD_F32(d,0x20)=3.141592741f;FIELD_S16(d,0x18)=ticks;FIELD_F32(d,0x34)=inverse;
 FIELD_S16(d,0x1A)=func_002A77E0(255);
 FIELD_S32(d,0x3C)=0;FIELD_S32(d,0x1C)=0;FIELD_S32(d,0x7C)=0;FIELD_S32(d,0x58)=0;FIELD_F32(d,0x50)=0.5f;FIELD_S32(d,0x5C)=-1;
 func_002A04B8(m,&r,&g,&b);
 FIELD_S32(d,0x38)=(b<<16)|(g<<8)|r;
 FIELD_F32(m,0x2C)*=1.5f;
 qcopy(m+0x10,position);
 qcopy(d,velocity);
 FIELD_S16(m,0x34)|=0x100;
 func_002AFFD8(m+0x10,axis,1);
 func_00282F20(m+0xC0,d,1.0f);
 func_00282DD8(m+0xD0,m+0xC0,axis);
 func_00282F20(m+0xD0,m+0xD0,1.0f);
 func_00282DD8(m+0xE0,m+0xD0,m+0xC0);
 func_002A7398(m,2,0);
 FIELD_S32(d,0x70)=func_002FED90(m,1.0f,1.0f,1.0f,0);
 }
 return m;
}
