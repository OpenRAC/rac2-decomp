/* func_PAL_L07_003FCC48, the PAL copy of func_L07_003F8430: the same C, where 1.0f / 6.0f becomes
   0.20000002f; 0.000290888245f becomes 0.0003490659f; and the two timer values stored at 0x440 take
   the 50 Hz scale. */
#include "common.h"
extern void func_2E4340(void *,void *,void *);
extern void func_31B090(void *,void *,void *,s32);
extern void func_313DD8(void *,f32,f32);
extern f32 func_2E4508(void *,void *);
extern s32 func_2E3F80(s32 *);
extern f32 func_L07_003F90E8(s32,s32,f32,f32);
extern s32 func_2E5470(f32);
extern s32 func_310AD8(s32,s32);
extern f32 func_310B30(f32,f32);
extern f32 func_2E49C8(f32,f32);
extern f32 func_2E5360(f32,f32);
extern f32 func_2E5318(f32,f32);
extern f32 func_2E4900(f32);
extern f32 func_2E4918(f32);
extern void func_2E4310(void *,void *,void *);
extern f32 D_L07_001B1090 __attribute__((sda));
extern f32 D_L07_001B1030;
extern f32 D_L07_001B1020 __attribute__((sda));
extern f32 D_L07_001B1094 __attribute__((sda));
extern f32 D_L07_001B1098 __attribute__((sda));
extern f32 D_L07_001B109C __attribute__((sda));
extern f32 D_L07_001B10A4 __attribute__((sda));
extern f32 D_L07_001B10B0 __attribute__((sda));
extern f32 D_L07_001B10B4 __attribute__((sda));
extern s32 D_L07_001B10A8 __attribute__((sda));
extern s32 D_L07_001B10AC;
typedef struct { u8 pad[0x140]; f32 pos[6]; f32 angle; } Target;
extern Target D_L07_001B90C0;
typedef struct {u8 pad[0x38];f32 value;u8 rest[0x80-0x3c];} Record;
extern Record *D_L07_001B23CC;
void func_PAL_L07_003FCC48(u8 *obj)
{
 f32 v[4];
 u8 *p=*(u8 **)(obj+0x68);
 s32 change;
 f32 dist,angle,step;
 if (!obj[0x95]) {
  func_2E4340(v,p+0x140,*(u8 **)(p+0x418)+0x10);
  func_31B090(*(u8 **)(p+0x418),v,v,0);
  if (*(s32 *)(p+0x420)) func_313DD8(p+0x3e0,v[0]-D_L07_001B1090,0.20000002f);
  else func_313DD8(p+0x3e0,v[0]+D_L07_001B1090,0.20000002f);
  if (*(f32 *)(p+0x3e0)>D_L07_001B1030) *(f32 *)(p+0x3e0)=D_L07_001B1030;
  else if (*(f32 *)(p+0x3e0)<D_L07_001B1020) *(f32 *)(p+0x3e0)=D_L07_001B1020;
  func_313DD8(p+0x3e4,v[1],0.20000002f);
  if (*(f32 *)(p+0x3e4)>5.0f) *(f32 *)(p+0x3e4)=5.0f;
  else if (*(f32 *)(p+0x3e4)<-5.0f) *(f32 *)(p+0x3e4)=-5.0f;
 } else {
  if (*(s32 *)(p+0x440)<0) *(s32 *)(p+0x440)=-*(s32 *)(p+0x440);
  else if (func_2E4508(obj+0x10,p+0x3e0)<2.0f) {
   change=0;
   dist=func_2E4508(p+0x140,obj+0x10);
   if(dist<D_L07_001B1094) change=1;
   else if(dist>D_L07_001B1098) change=1;
   if(func_2E3F80((s32 *)(p+0x440))) {
    change=1;
    *(s32 *)(p+0x440)=((s32)(func_2E5470(func_L07_003F90E8(5,15,(f32)D_L07_001B10A8,(f32)D_L07_001B10AC))) * 5 + 2) / 6;
    *(s32 *)(p+0x440)+=((s32)(func_310AD8(0,60)) * 5 + 2) / 6;
   }
   if(change) {
    step=func_310B30(10.0f,40.0f)*0.017453294f;
    angle=func_2E49C8(*(f32 *)(obj+0x10)-D_L07_001B90C0.pos[0],*(f32 *)(obj+0x14)-D_L07_001B90C0.pos[1]);
    if(func_2E5360(angle,D_L07_001B90C0.angle)*step>0.0f) step=-step;
    angle=func_2E5318(D_L07_001B90C0.angle,step);
    *(f32 *)(p+0x3e0)=func_2E4900(angle)*D_L07_001B109C;
    *(f32 *)(p+0x3e4)=func_2E4918(angle)*D_L07_001B109C;
    *(f32 *)(p+0x3e8)=0.0f;
    func_2E4310(p+0x3e0,p+0x3e0,p+0x140);
   }
  }
  *(f32 *)(p+0x454)=func_2E5318(*(f32 *)(p+0x454),D_L07_001B10B4*0.0003490659f);
  angle=func_2E4918(*(f32 *)(p+0x454));
  *(f32 *)(p+0x3e8)=D_L07_001B23CC[*(s32 *)(p+0x174)].value+D_L07_001B10A4+D_L07_001B10B0*angle;
 }
}
