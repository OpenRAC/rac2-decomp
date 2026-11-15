#include "include_asm.h"
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_2E4DD8(void *,void *);
extern u8 *func_306498(s32);
extern void func_31F9E0(void *,void *);
extern void func_2E4B70(void *,void *);
extern void func_2E47F8(void *,void *,void *);
extern void func_2E4EB8(void *,void *,void *);
extern float func_308EE8(void *);
extern void func_2E4340(void *,void *,void *);
extern void func_3152C0(void *,void *);
extern void func_317618(void *,void *,void *,void *);
extern void func_313DD8(void *,f32,f32);
extern void func_355188(s32);
extern u8 g_sound_state[];
typedef struct { f32 v[4]; } Vec;
extern Vec D_L07_001B1790[2] __attribute__((sda));
extern Vec D_L07_001B17B0[2] __attribute__((sda));
typedef struct {u8 pad[0x108];u8 *children[2];f32 angles[2];} State;
/* Creates the two side parts and the top attachment of a Siberius ship and keeps them attached to its body every frame. */
void ship_update_attached_parts(u8 *moby)
{
 f32 mat[16],oldpos[4],oldrot[4],delta[4],rot[4];
 u8 *vars=*(u8 **)(moby+0x68),*child,*part_vars,*sound;
 s32 i,sound_id,side;
 u8 *attachment;
 u8 *new_part_vars;
 State *parts=(State *)vars;
 func_2E4DD8(mat,moby+0xc0);
 qcopy(mat+12,moby+0x10);
 mat[15]=1.0f;
 for(i=0;i<2;i++) {
  child=parts->children[i];
  if(child==0) {
   child=func_306498(i?0x11e2 /* moby class 4578 */:0x11e1 /* moby class 4577 */);
   if(child) {
    func_31F9E0(child,moby);
    *(u16 *)(child+0x34)|=0x120;
    new_part_vars=*(u8 **)(child+0x68);
    *(u8 **)(new_part_vars+8)=new_part_vars+0x20;
    *(u32 *)(new_part_vars+0x5c)|=2;
    func_2E4B70(child+0xc0,child+0xf0);
   }
   parts->children[i]=child;
   parts->angles[i]=i?1.2f:-1.2f;
  } else {
   qcopy_nc(oldpos,child+0x10);
   qcopy_nc(oldrot,child+0xf0);
   func_2E47F8(child+0x10,&D_L07_001B1790[i],mat);
   qzero_nc(rot);
   rot[1]=parts->angles[i];
   func_2E4B70(child+0xc0,rot);
   func_2E4EB8(child+0xc0,mat,child+0xc0);
   func_308EE8(child);
   part_vars=*(u8 **)(child+0x68);
   func_2E4340(delta,child+0x10,oldpos);
   func_3152C0(child+0xc0,child+0xf0);
   func_317618(part_vars+0x20,delta,oldrot,child+0xf0);
  }
 }
 attachment=*(u8 **)(vars+0x16c0);
 if(attachment==0) {
  attachment=func_306498(0xd3b /* moby class 3387 */);
  if(attachment) {
   func_31F9E0(attachment,moby);
   *(f32 *)(attachment+0x2c)=*(f32 *)(*(u8 **)(attachment+0x24)+0x24)*1.1f;
   *(u16 *)(attachment+0x34)=(*(u16 *)(attachment+0x34)&0xffdf)|0x102;
   *(u8 **)(vars+0x16c0)=attachment;
  }
 } else if((*(u16 *)(attachment+0x34)^1)&1) {
  if(*(f32 *)(vars+0x16c8)!=0.0f) {
   func_313DD8(vars+0x16c4,*(f32 *)(vars+0x16c8),1.0f/30.0f);
   if(*(f32 *)(vars+0x16c4)>=*(f32 *)(vars+0x16c8)) {
    sound_id=*(s32 *)(vars+0x16cc);
    if(sound_id!=-1) {
     sound=g_sound_state+sound_id*0x70;
     if(*(u8 **)(sound+0x88)==moby && sound[0x74]) func_355188(sound_id);
    }
    *(s32 *)(vars+0x16cc)=-1;
    attachment[0x31]=0;
    *(u16 *)(attachment+0x34)|=1;
   }
  }
  side=*(s16 *)(moby+0xaa)!=0x11d9 /* moby class 4569 */;
  qcopy(attachment+0x10,&D_L07_001B17B0[side]);
  *(f32 *)(attachment+0x18)+=*(f32 *)(vars+0x16c4);
  func_2E47F8(attachment+0x10,attachment+0x10,mat);
  *(TI128 *)oldpos=0;
  oldpos[2]=1.5707964f;
  func_2E4B70(attachment+0xc0,oldpos);
  func_2E4EB8(attachment+0xc0,mat,attachment+0xc0);
  func_308EE8(attachment);
 }
}
