#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_00283658(void *,void *);
extern u8 *func_0029EFD0(s32);
extern void func_002B37E8(void *,void *);
extern void func_002833F0(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00283738(void *,void *,void *);
extern void func_002A0F48(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
extern void func_002AA2E8(void *,f32,f32);
extern void func_002E59F8(s32);
extern u8 D_00188660[];
typedef struct { f32 v[4]; } Vec;
extern Vec D_L07_001B1790[2] __attribute__((sda));
extern Vec D_L07_001B17B0[2] __attribute__((sda));
typedef struct {u8 pad[0x108];u8 *children[2];f32 angles[2];} State;

void func_PAL_L07_00414008(u8 *obj)
{
 f32 mat[16],oldpos[4],oldrot[4],delta[4],rot[4];
 u8 *p=*(u8 **)(obj+0x68),*child,*state,*sound;
 s32 i,id,index;
 u8 *attachment;
 u8 *createdState;
 State *ps=(State *)p;
 func_00283658(mat,obj+0xc0);
 qcopy(mat+12,obj+0x10);
 mat[15]=1.0f;
 for(i=0;i<2;i++) {
  child=ps->children[i];
  if(child==0) {
   child=func_0029EFD0(i?0x11e2:0x11e1);
   if(child) {
    func_002B37E8(child,obj);
    *(u16 *)(child+0x34)|=0x120;
    createdState=*(u8 **)(child+0x68);
    *(u8 **)(createdState+8)=createdState+0x20;
    *(u32 *)(createdState+0x5c)|=2;
    func_002833F0(child+0xc0,child+0xf0);
   }
   ps->children[i]=child;
   ps->angles[i]=i?1.2f:-1.2f;
  } else {
   qcopy_nc(oldpos,child+0x10);
   qcopy_nc(oldrot,child+0xf0);
   func_002830C0(child+0x10,&D_L07_001B1790[i],mat);
   qzero_nc(rot);
   rot[1]=ps->angles[i];
   func_002833F0(child+0xc0,rot);
   func_00283738(child+0xc0,mat,child+0xc0);
   func_002A0F48(child);
   state=*(u8 **)(child+0x68);
   func_00282CF0(delta,child+0x10,oldpos);
   func_002AB6D8(child+0xc0,child+0xf0);
   func_002AD6F0(state+0x20,delta,oldrot,child+0xf0);
  }
 }
 attachment=*(u8 **)(p+0x16c0);
 if(attachment==0) {
  attachment=func_0029EFD0(0xd3b);
  if(attachment) {
   func_002B37E8(attachment,obj);
   *(f32 *)(attachment+0x2c)=*(f32 *)(*(u8 **)(attachment+0x24)+0x24)*1.1f;
   *(u16 *)(attachment+0x34)=(*(u16 *)(attachment+0x34)&0xffdf)|0x102;
   *(u8 **)(p+0x16c0)=attachment;
  }
 } else if((*(u16 *)(attachment+0x34)^1)&1) {
  if(*(f32 *)(p+0x16c8)!=0.0f) {
   func_002AA2E8(p+0x16c4,*(f32 *)(p+0x16c8),0.040000003f);
   if(*(f32 *)(p+0x16c4)>=*(f32 *)(p+0x16c8)) {
    id=*(s32 *)(p+0x16cc);
    if(id!=-1) {
     sound=D_00188660+id*0x70;
     if(*(u8 **)(sound+0x88)==obj && sound[0x74]) func_002E59F8(id);
    }
    *(s32 *)(p+0x16cc)=-1;
    attachment[0x31]=0;
    *(u16 *)(attachment+0x34)|=1;
   }
  }
  index=*(s16 *)(obj+0xaa)!=0x11d9;
  qcopy(attachment+0x10,&D_L07_001B17B0[index]);
  *(f32 *)(attachment+0x18)+=*(f32 *)(p+0x16c4);
  func_002830C0(attachment+0x10,attachment+0x10,mat);
  *(TI128 *)oldpos=0;
  oldpos[2]=1.5707964f;
  func_002833F0(attachment+0xc0,oldpos);
  func_00283738(attachment+0xc0,mat,attachment+0xc0);
  func_002A0F48(attachment);
 }
}
