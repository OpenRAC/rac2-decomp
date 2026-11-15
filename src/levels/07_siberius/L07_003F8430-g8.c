#include "common.h"
extern void func_2E4340(void *,void *,void *);
extern void func_31B090(void *,void *,void *,s32);
extern void func_313DD8(void *,f32,f32);
extern f32 func_2E4508(void *,void *);
extern s32 func_2E3F80(s32 *);
extern f32 math_interpolate_between_limits(s32,s32,f32,f32);
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
/* Works out where a flying enemy should drift next. In one mode it follows its parent; in the other it picks a new circling direction around the player every so often and bobs up and down. */
void flyer_steer(u8 *moby)
{
 f32 offset[4];
 u8 *vars=*(u8 **)(moby+0x68);
 s32 needsNewHeading;
 f32 distance,angle,turnStep;
 if (!moby[0x95]) {
  func_2E4340(offset,vars+0x140,*(u8 **)(vars+0x418)+0x10);
  func_31B090(*(u8 **)(vars+0x418),offset,offset,0);
  if (*(s32 *)(vars+0x420)) func_313DD8(vars+0x3e0,offset[0]-D_L07_001B1090,1.0f/6.0f);
  else func_313DD8(vars+0x3e0,offset[0]+D_L07_001B1090,1.0f/6.0f);
  if (*(f32 *)(vars+0x3e0)>D_L07_001B1030) *(f32 *)(vars+0x3e0)=D_L07_001B1030;
  else if (*(f32 *)(vars+0x3e0)<D_L07_001B1020) *(f32 *)(vars+0x3e0)=D_L07_001B1020;
  func_313DD8(vars+0x3e4,offset[1],1.0f/6.0f);
  if (*(f32 *)(vars+0x3e4)>5.0f) *(f32 *)(vars+0x3e4)=5.0f;
  else if (*(f32 *)(vars+0x3e4)<-5.0f) *(f32 *)(vars+0x3e4)=-5.0f;
 } else {
  if (*(s32 *)(vars+0x440)<0) *(s32 *)(vars+0x440)=-*(s32 *)(vars+0x440);
  else if (func_2E4508(moby+0x10,vars+0x3e0)<2.0f) {
   needsNewHeading=0;
   distance=func_2E4508(vars+0x140,moby+0x10);
   if(distance<D_L07_001B1094) needsNewHeading=1;
   else if(distance>D_L07_001B1098) needsNewHeading=1;
   if(func_2E3F80((s32 *)(vars+0x440))) {
    needsNewHeading=1;
    *(s32 *)(vars+0x440)=func_2E5470(math_interpolate_between_limits(5,15,(f32)D_L07_001B10A8,(f32)D_L07_001B10AC));
    *(s32 *)(vars+0x440)+=func_310AD8(0,60);
   }
   if(needsNewHeading) {
    turnStep=func_310B30(10.0f,40.0f)*0.017453294f;
    angle=func_2E49C8(*(f32 *)(moby+0x10)-D_L07_001B90C0.pos[0],*(f32 *)(moby+0x14)-D_L07_001B90C0.pos[1]);
    if(func_2E5360(angle,D_L07_001B90C0.angle)*turnStep>0.0f) turnStep=-turnStep;
    angle=func_2E5318(D_L07_001B90C0.angle,turnStep);
    *(f32 *)(vars+0x3e0)=func_2E4900(angle)*D_L07_001B109C;
    *(f32 *)(vars+0x3e4)=func_2E4918(angle)*D_L07_001B109C;
    *(f32 *)(vars+0x3e8)=0.0f;
    func_2E4310(vars+0x3e0,vars+0x3e0,vars+0x140);
   }
  }
  *(f32 *)(vars+0x454)=func_2E5318(*(f32 *)(vars+0x454),D_L07_001B10B4*0.000290888245f);
  angle=func_2E4918(*(f32 *)(vars+0x454));
  *(f32 *)(vars+0x3e8)=D_L07_001B23CC[*(s32 *)(vars+0x174)].value+D_L07_001B10A4+D_L07_001B10B0*angle;
 }
}
